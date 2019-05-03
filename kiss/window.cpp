#include "window.hpp"

namespace kiss {
	const iv2 default_pos = CW_USEDEFAULT;
	const iv2 default_size = CW_USEDEFAULT;

	Window::Window (std::string caption, iv2 initial_size, iv2 initial_pos) {

		auto window = Windows_Thread::get_singleton().open_window(caption, initial_size, initial_pos);
		
		setup_gl_context(platform->hdc);
	}
	
	constexpr LONG WINDOWED_STYLE =					WS_VISIBLE|WS_OVERLAPPEDWINDOW;
	constexpr LONG WINDOWED_EX_STYLE =				WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;

	constexpr LONG BORDERLESS_FULLSCREEN_STYLE =	WS_VISIBLE;
	constexpr LONG BORDERLESS_FULLSCREEN_EX_STYLE =	WS_EX_APPWINDOW;

	struct Thread_Input_State {
		std::mutex	mutex; // mutex to lock inp structure
		Input		inp; // input state, gets modified by wndproc, and read (copied) by renderer thread

		void set_close () {
			std::unique_lock<std::mutex> lck(mutex);
			inp.close = true;
		}
		void set_window_size (iv2 val) {
			std::unique_lock<std::mutex> lck(mutex);
			inp.window_size = val;
		}
		void set_mouse_pos (iv2 val) {
			std::unique_lock<std::mutex> lck(mutex);
			inp._mouse_pos = val;
		}

		Input get_input () {
			std::unique_lock<std::mutex> lck(mutex);

			Input copy = inp;
			inp.clear();
			return copy;
		}
	};

	struct Platform_Window { // Platform specific
		HWND	hwnd;
		HDC		hdc;
		HGLRC	hglcontext;

		std::thread	thread;

		Thread_Input_State inp_state;
	};
	void delete_Platform_Window (Platform_Window* p) { delete p; }

	std::unordered_map<HWND, Platform_Window*> windows; // only modified and read from message_loop thread
	
	// Window message handler
	LRESULT CALLBACK wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		Platform_Window*	wnd = nullptr;
		Thread_Input_State*	inp = nullptr;

		if (uMsg != WM_NCCREATE) {
			auto it = windows.find(hwnd);
			if (it == windows.end()) {
				return DefWindowProcA(hwnd, uMsg, wParam, lParam); // not one of our windows
			}
			wnd = it->second;
			inp = &wnd->inp_state;
		}
		
		switch (uMsg) {
			case WM_NCCREATE: {
				auto* cs = (CREATESTRUCT*)lParam;
				wnd = (Platform_Window*)cs->lpCreateParams;
				windows[hwnd] = wnd;
				return TRUE;
			}
			case WM_NCDESTROY: {
				windows.erase(hwnd);
				return 0;
			}

			case WM_CLOSE: {
				inp->set_close();
				return 0;
			}

			case WM_SIZE: {
				auto w = LOWORD(lParam);
				auto h = HIWORD(lParam);

				RECT rect;
				{
					auto ret = GetClientRect(hwnd, &rect);
				}

				inp->set_window_size(max(iv2(w,h), 1));

				//if (!fullscreen) {
				//write_window_placement_save(hWnd);
				//}
				return 0;
			}

			case WM_MOUSEMOVE: {
				auto x = LOWORD(lParam);
				auto y = HIWORD(lParam);

				inp->set_mouse_pos(iv2(x,y));

				return 0;
			}

			default:
				return DefWindowProcA(hwnd, uMsg, wParam, lParam);
		}
	}

	RECT find_windows_border_sizes (DWORD style, DWORD exstyle) { // Get window border sizes
		RECT borders = { 0, 0, 0, 0 };
		auto ret = AdjustWindowRectEx(&borders, style, FALSE, exstyle);

		borders.left = -borders.left;
		borders.top = -borders.top;

		return borders;
	}

	// register a window to recieve raw input
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

		auto ret = RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE));
	}

	// open a window with a message queue on the thread this is called on
	HWND open_window (Platform_Window* wnd, char const* caption, iv2 initial_size, iv2 initial_pos) {
		auto hinstance = GetModuleHandle(NULL);

		auto hicon		= LoadIcon(NULL, IDI_WINLOGO);
		auto hcursor	= LoadCursor(NULL, IDC_ARROW);

		DWORD style		= WINDOWED_STYLE;
		DWORD exstyle	= WINDOWED_EX_STYLE;

		RECT border_sizes = find_windows_border_sizes(style, exstyle);

		if (initial_size.x != CW_USEDEFAULT)
			initial_size.x += border_sizes.left + border_sizes.right;
		if (initial_size.y != CW_USEDEFAULT)
			initial_size.y += border_sizes.top + border_sizes.bottom;

		ATOM classatom;
		{
			WNDCLASS wndclass = {}; // Initialize to zero
			wndclass.style =			CS_OWNDC;
			wndclass.lpfnWndProc =		wndproc;
			wndclass.hInstance =		hinstance;
			wndclass.hIcon = 			hicon;
			wndclass.hCursor = 			hcursor;
			wndclass.lpszClassName =	"kisslib_gl_window";

			classatom = RegisterClass(&wndclass);
		}

		// TODO: restore window placement from file

		HWND hwnd = CreateWindowEx(
			exstyle, (LPCSTR)classatom, caption,
			style & ~WS_VISIBLE, // not visible yet
			initial_pos.x, initial_pos.y, initial_size.x, initial_size.y,
			NULL, NULL, hinstance,
			wnd); // Pass window pointer to WindowProc which caches it in a hashmap in WM_NCCREATE

		//
		register_raw_input_devices(hwnd);

		ShowWindow(hwnd, SW_SHOW);

		return hwnd;
	}

	void load_wgl_with_dummy_window () {
		auto hinstance = GetModuleHandle(NULL);

		// create dummy context and window to get access to modern gl creation functions
		ATOM dummy_classatom;
		{
			WNDCLASS wndclass = {}; // Initialize to zero
			wndclass.style =			CS_OWNDC;
			wndclass.lpfnWndProc =		DefWindowProcA;
			wndclass.hInstance =		hinstance;
			wndclass.lpszClassName =	"kisslib_dummy_window";

			dummy_classatom = RegisterClass(&wndclass);
		}

		HWND dummy_hwnd = CreateWindowEx(
			0, (LPCSTR)dummy_classatom, "",
			0,
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
			NULL, NULL, hinstance, NULL);

		//
		HDC dummy_hdc = GetDC(dummy_hwnd);

		{ // set pixelformat of dummy window
			PIXELFORMATDESCRIPTOR pfd = {}; // Initialize to zero

			pfd.nSize =			sizeof pfd;
			pfd.nVersion =		1;
			pfd.dwFlags =		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
			pfd.iPixelType =	PFD_TYPE_RGBA;
			pfd.cColorBits =	24;
			pfd.cAlphaBits =	8;
			pfd.cDepthBits =	24;
			pfd.cStencilBits =	8;
			pfd.iLayerType =	PFD_MAIN_PLANE;

			int pf = ChoosePixelFormat(dummy_hdc, &pfd);
			{
				auto ret = SetPixelFormat(dummy_hdc, pf, &pfd);
			}
		}

		// create dummy gl context
		HGLRC dummy_hglrc = wglCreateContext(dummy_hdc);

		wglMakeCurrent(dummy_hdc, dummy_hglrc);

		//
		//auto wglCreateContext version = glGetString(GL_VERSION);

		//
		WGL_Api::init_singleton(dummy_hdc);

		if (wglChoosePixelFormatARB == NULL)
			int a = 5;

		std::cout << "Thread " << std::this_thread::get_id() <<": "<< wglChoosePixelFormatARB << std::endl;

		// destroy dummy stuff
		wglMakeCurrent(dummy_hdc, NULL);
		wglDeleteContext(dummy_hglrc);

		ReleaseDC(dummy_hwnd, dummy_hdc);
		DestroyWindow(dummy_hwnd);

		UnregisterClass((LPCTSTR)dummy_classatom, hinstance);
	}

	void message_loop () {
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

	Window::~Window () { // closes window

		wglMakeCurrent(platform->hdc, NULL);
		wglDeleteContext(platform->hglcontext);

		ReleaseDC(platform->hwnd, platform->hdc);

		PostMessage(platform->hwnd, WM_QUIT, 0,0);

		platform->thread.join();
	}

	void run_window_thread (Platform_Window* wnd, std::condition_variable& cv,
							std::string caption, iv2 initial_size, iv2 initial_pos) {
		// Open window and write it's hwnd into the Platform_Window structure
		HWND hwnd = open_window(wnd, caption.c_str(), initial_size, initial_pos);

		wnd->hwnd = hwnd;
		cv.notify_all(); // notify and wake up renderer thread that the window is now open and it can init the gl now
		
		message_loop();

		DestroyWindow(hwnd);

		// UnregisterClass not important?
	}

	Input Window::get_input () {
		return platform->inp_state.get_input();
	}

	void Window::swap_buffers () {
		SwapBuffers(platform->hdc);
	}
}
