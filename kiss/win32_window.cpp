#pragma once
#include "win32_window.hpp"
#include "smart_ptr.hpp"
#include "assert.h"
#include "thread_name.hpp"

namespace kiss {
	//////////////
	// Actual win32 windowing calls all done on one thread
	//////////////

	extern const iv2 default_pos;
	extern const iv2 default_size;

	const iv2 default_pos = CW_USEDEFAULT;
	const iv2 default_size = CW_USEDEFAULT;

	RECT find_windows_border_sizes (DWORD style, DWORD exstyle) { // Get window border sizes
		RECT borders = { 0, 0, 0, 0 };
		auto ret = AdjustWindowRectEx(&borders, style, FALSE, exstyle);

		borders.left = -borders.left;
		borders.top = -borders.top;

		return borders;
	}
	ATOM register_standard_window_class (HINSTANCE hinstance) {
		auto hicon		= LoadIcon(NULL, IDI_WINLOGO);
		auto hcursor	= LoadCursor(NULL, IDC_ARROW);

		WNDCLASS wndclass = {}; // Initialize to zero
		wndclass.style =			CS_OWNDC|CS_HREDRAW|CS_VREDRAW; // CS_HREDRAW|CS_VREDRAW might prevent flicker with opengl apps
		wndclass.lpfnWndProc =		wndproc;
		wndclass.hInstance =		hinstance;
		wndclass.hIcon = 			hicon;
		wndclass.hCursor = 			hcursor;
		wndclass.lpszClassName =	L"kisslib_window";

		auto atom = RegisterClass(&wndclass);
		assert(atom != 0);
		return atom;
	}
	void register_raw_input_devices (HWND hwnd) {
		RAWINPUTDEVICE	rid[2];
		// Mouse
		rid[0].usUsagePage =	1;
		rid[0].usUsage =		2;
		rid[0].dwFlags =		RIDEV_DEVNOTIFY;
		rid[0].hwndTarget =		hwnd;
		// Keyboard
		rid[1].usUsagePage =	1;
		rid[1].usUsage =		6;
		rid[1].dwFlags =		RIDEV_DEVNOTIFY;
		rid[1].hwndTarget =		hwnd;

		// RIDEV_NOLEGACY, RIDEV_NOHOTKEYS ???

		auto res = RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE));
		assert(res != FALSE);
	}

	HWND Window_Thread::open_window (Platform_Window* window, string_view caption, iv2 initial_size, iv2 initial_pos) {
		if (initial_size.x != default_size.x)
			initial_size.x += border_sizes.left + border_sizes.right;
		if (initial_size.y != default_size.y)
			initial_size.y += border_sizes.top + border_sizes.bottom;

		auto hwnd = CreateWindowEx(
			WINDOWED_EX_STYLE, (LPCWSTR)(uptr)wnd_classatom, utf8_to_wchar(caption).c_str(), WINDOWED_STYLE,
			initial_pos.x, initial_pos.y, initial_size.x, initial_size.y,
			NULL, NULL, hinstance, window);
		assert(hwnd != INVALID_HANDLE_VALUE);

		auto hdc = GetDC(hwnd);
		assert(hdc != NULL);

		window->hwnd = hwnd;
		window->hdc = hdc;

		return hwnd;
	}
	void Window_Thread::close_window (Platform_Window* window) {
		auto dc = ReleaseDC(window->get_hwnd(), window->get_hdc());
		assert(dc == 1);

		auto wnd = DestroyWindow(window->get_hwnd());
		assert(wnd != 0);
	}

	void Window_Thread::thread_proc () {
		set_current_thread_name("kisslib_window_message_thread");

		hinstance = GetModuleHandle(NULL);

		border_sizes = find_windows_border_sizes(WINDOWED_STYLE, WINDOWED_STYLE);

		wnd_classatom = register_standard_window_class(hinstance);

		message_loop();

		auto cls = UnregisterClass((LPCWSTR)(uptr)wnd_classatom, hinstance);
		assert(cls != 0);
	}

	void Window_Thread::message_loop () {
		HANDLE rpc_wait = remote_proc_caller.get_wait_for_execute_procedure_handle();

		MSG msg;
		for (;;) {
			auto res = MsgWaitForMultipleObjects(1, &rpc_wait, FALSE, INFINITE, QS_ALLINPUT);

			if (res == WAIT_OBJECT_0) {

				remote_proc_caller.thread_execute_procedure();

			} else if (res == WAIT_FAILED) {

				assert(false);

			} else {

				auto res = GetMessage(&msg, NULL, 0,0);
				if (res < 0) {
					// error, report?
					break;
				} else if (res == 0) { // WM_QUIT
					break;
				} else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}

	/* TODO: improve window resizing
		https://stackoverflow.com/questions/10615272/opengl-flickering-damaged-with-window-resize-and-dwm-active
		https://stackoverflow.com/questions/53000291/how-to-smooth-ugly-jitter-flicker-jumping-when-resizing-windows-especially-drag/53000292#53000292
	*/
	LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		auto* thr = Window_Thread::singleton.get(); // this has to always be constant at this point, threadsafe
		auto* wnd = thr->get_window(hwnd);

		if (!wnd && uMsg != WM_NCCREATE) {
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		switch (uMsg) {

			case WM_NCCREATE: {
				auto* cs = (CREATESTRUCT*)lParam;
				auto* wnd = (Platform_Window*)cs->lpCreateParams;

				thr->register_window(hwnd, wnd);
			} return TRUE;

			case WM_NCDESTROY: {
				thr->unregister_window(hwnd);
			} return 0;

			case WM_CLOSE: {
				wnd->input_state.set_close(true);
			} return 0;

			case WM_SIZE: {
				int w = LOWORD(lParam);
				int h = HIWORD(lParam);
				iv2 sz = iv2(w,h);
				sz = max(sz, 1);

				wnd->input_state.set_window_size(sz);
			} return 0;

			case WM_PAINT: {
					
			} return 0;
			case WM_ERASEBKGND: {
				// flicker prevention
			} return 1;

			default:
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	//////////////
	// Bookkeeping happening between all threads that create windows to handle the message thread being on another thread
	//////////////

	Input Platform_Window::get_input () {
		return input_state.get_input_for_frame();
	}

	unique_ptr<Window_Thread> Window_Thread::singleton;
	std::mutex Window_Thread::singleton_mtx;

	Platform_Window::Platform_Window (string_view caption, iv2 initial_size, iv2 initial_pos) {

		{ // Threadsafe singleton creation
			std::lock_guard<std::mutex> lck(Window_Thread::singleton_mtx);

			if (!Window_Thread::singleton) // Starts window thread when first window is created
				Window_Thread::singleton = make_unique<Window_Thread>();
		}
		auto* thr = Window_Thread::singleton.get();

		thr->execute_on_thread(std::bind(&Window_Thread::open_window, thr, this, caption, initial_size, initial_pos));
	}
	
	Platform_Window::~Platform_Window () {
		auto* thr = Window_Thread::singleton.get();

		thr->execute_on_thread(std::bind(&Window_Thread::close_window, thr, this));

		{ // Threadsafe singleton deletion
			std::lock_guard<std::mutex> lck(Window_Thread::singleton_mtx);

			if (thr->windows.size() == 0) { // Shuts down window thread when last window is closed
				Window_Thread::singleton.reset();
			}
		}
	}

	void Window_Thread::execute_on_thread (std::function<void()> f) {
		remote_proc_caller.execute_on_thread(f);
	}

	Window_Thread::Window_Thread () {
		thread = std::thread(&Window_Thread::thread_proc, this);
	}
	Window_Thread::~Window_Thread () {
		execute_on_thread([] () { PostQuitMessage(0); });

		thread.join();
	}

	void Window_Thread::register_window (HWND hwnd, Platform_Window* window) {
		windows[hwnd] = window;
	}
	void Window_Thread::unregister_window (HWND hwnd) {
		windows.erase(hwnd);
	}
	Platform_Window* Window_Thread::get_window (HWND hwnd) {
		auto res = windows.find(hwnd);
		return res == windows.end() ? nullptr : res->second;
	}

}
