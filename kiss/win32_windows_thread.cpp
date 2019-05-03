#pragma once
#include "win32_windows_thread.hpp"

namespace kiss {
	unique_ptr<Windows_Thread> Windows_Thread::singleton;

	//// Runs on any thread
	Windows_Thread& Windows_Thread::get_singleton () {
		if (!singleton)
			singleton = make_unique<Windows_Thread>();
		return *singleton.get();
	}

	void Windows_Thread::open_window (Platform_Window* wnd, std::string const& caption, iv2 initial_size, iv2 initial_pos) {
		auto& thr = get_singleton();
	}
	void Windows_Thread::close_window (Platform_Window* wnd) {
		
	}

	Windows_Thread::Windows_Thread () {
		thread = std::thread(&Windows_Thread::thread_proc, this);
	}

	//// Runs on windows thread
	constexpr LONG WINDOWED_STYLE =					WS_VISIBLE|WS_OVERLAPPEDWINDOW;
	constexpr LONG WINDOWED_EX_STYLE =				WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;

	constexpr LONG BORDERLESS_FULLSCREEN_STYLE =	WS_VISIBLE;
	constexpr LONG BORDERLESS_FULLSCREEN_EX_STYLE =	WS_EX_APPWINDOW;

	LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	RECT find_windows_border_sizes (DWORD style, DWORD exstyle) { // Get window border sizes
		RECT borders = { 0, 0, 0, 0 };
		auto ret = AdjustWindowRectEx(&borders, style, FALSE, exstyle);

		borders.left = -borders.left;
		borders.top = -borders.top;

		return borders;
	}
	ATOM register_standard_window_class () {
		auto hinstance = GetModuleHandle(NULL);

		auto hicon		= LoadIcon(NULL, IDI_WINLOGO);
		auto hcursor	= LoadCursor(NULL, IDC_ARROW);

		WNDCLASS wndclass = {}; // Initialize to zero
		wndclass.style =			CS_OWNDC;
		wndclass.lpfnWndProc =		wndproc;
		wndclass.hInstance =		hinstance;
		wndclass.hIcon = 			hicon;
		wndclass.hCursor = 			hcursor;
		wndclass.lpszClassName =	"kisslib_window";

		return RegisterClass(&wndclass);
	}

	void Windows_Thread::thread_proc () {

		DWORD style		= WINDOWED_STYLE;
		DWORD exstyle	= WINDOWED_EX_STYLE;

		border_sizes = find_windows_border_sizes(style, exstyle);

		wnd_classatom = register_standard_window_class();

		// Pump messages
		MSG msg;
		for (;;) {
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

	Windows_Thread::~Windows_Thread () {
		
		thread.join();
	}

	LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

		switch (uMsg) {

			default:
				return DefWindowProcA(hwnd, uMsg, wParam, lParam);
		}
	}
}
