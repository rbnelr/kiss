#include "window.hpp"
#include "input.hpp"

#include "glad/glad_wgl.h"

#include "sanitize_windows_h.hpp"

#include "wndproc.hpp"
#include "gl_context.hpp"

namespace kiss {
	struct Window {

		HWND	hwnd = NULL;
		HDC		hdc;
		HGLRC	hglcontext;

		~Window ();
	};

	const iv2 default_pos = CW_USEDEFAULT;
	const iv2 default_size = CW_USEDEFAULT;

	constexpr LONG WINDOWED_STYLE =					WS_VISIBLE|WS_OVERLAPPEDWINDOW;
	constexpr LONG WINDOWED_EX_STYLE =				WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;

	constexpr LONG BORDERLESS_FULLSCREEN_STYLE =	WS_VISIBLE;
	constexpr LONG BORDERLESS_FULLSCREEN_EX_STYLE =	WS_EX_APPWINDOW;

	Window wnd; // only one window supported

	RECT find_windows_border_sizes (DWORD style, DWORD exstyle) { // Get window border sizes
		RECT borders = { 0, 0, 0, 0 };
		auto ret = AdjustWindowRectEx(&borders, style, FALSE, exstyle);

		borders.left = -borders.left;
		borders.top = -borders.top;

		return borders;
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

		auto ret = RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE));
	}

	HWND _open_window (char const* caption, iv2 initial_size, iv2 initial_pos) {
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
			wndclass.cbWndExtra =		sizeof(Window*);

			classatom = RegisterClass(&wndclass);
		}

		// TODO: restore window placement from file

		HWND hwnd = CreateWindowEx(
			exstyle, (LPCSTR)classatom, caption,
			style & ~WS_VISIBLE, // not visible yet
			initial_pos.x, initial_pos.y, initial_size.x, initial_size.y,
			NULL, NULL, hinstance, NULL);

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
		gladLoadWGL(dummy_hdc);

		// destroy dummy stuff
		wglMakeCurrent(dummy_hdc, NULL);
		wglDeleteContext(dummy_hglrc);

		ReleaseDC(dummy_hwnd, dummy_hdc);
		DestroyWindow(dummy_hwnd);

		UnregisterClass((LPCTSTR)dummy_classatom, hinstance);
	}

	void open_window (char const* caption, iv2 initial_size, iv2 initial_pos) {
	
		HWND hwnd = _open_window(caption, initial_size, initial_pos);
		
		// TODO: if we want to better be able to handle window resizing (since that blocks the message queue, we can seperate message processing into its own thread (or did the the message pump always have to be on the main thread?))
		//////////////////// In renderer thread
		////

		load_wgl_with_dummy_window();

		HDC hdc = GetDC(hwnd);
		HGLRC hglcontext = setup_gl_context(hdc);

		////
		///////////////////////////////

		wnd.hwnd = hwnd;
		wnd.hdc = hdc;
		wnd.hglcontext = hglcontext;
	}

	void close_window () {
		if (wnd.hwnd != NULL) {
			wglMakeCurrent(wnd.hdc, NULL);
			wglDeleteContext(wnd.hglcontext);

			ReleaseDC(wnd.hwnd, wnd.hdc);
			DestroyWindow(wnd.hwnd);

			// UnregisterClass not important?

			wnd.hwnd = NULL;
			wnd.hdc = NULL;
			wnd.hglcontext = NULL;
		}
	}

	Window::~Window () {
		close_window();
	}

	void swap_buffers () {
		SwapBuffers(wnd.hdc);
	}
}
