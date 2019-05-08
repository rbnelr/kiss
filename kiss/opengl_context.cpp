#include "opengl_context.hpp"
#include "win32_window.hpp"
#include "clean_windows_h.hpp"
#include "opengl_api.hpp"
#include "wgl_api.hpp"

namespace kiss {
	struct Dummy_Window {
		HMODULE hinstance;
		ATOM classatom;
		HWND hwnd;
		HDC hdc;

		Dummy_Window () {
			hinstance = GetModuleHandle(NULL);

			WNDCLASS wndclass = {}; // Initialize to zero
			wndclass.style =			CS_OWNDC;
			wndclass.lpfnWndProc =		DefWindowProc;
			wndclass.hInstance =		hinstance;
			wndclass.lpszClassName =	L"kisslib_dummy_window";
			
			classatom = RegisterClass(&wndclass);
			assert(classatom != 0);

			// Create invisible window
			hwnd = CreateWindowEx(0, (LPCWSTR)(uptr)classatom, L"kisslib_dummy_window", 0,
				CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
				NULL, NULL, hinstance, NULL);
			assert(hwnd != INVALID_HANDLE_VALUE);

			hdc = GetDC(hwnd);
			assert(hdc != NULL);
		}
		~Dummy_Window () {

			auto dc = ReleaseDC(hwnd, hdc);
			assert(dc == 1);

			auto wnd = DestroyWindow(hwnd);
			assert(wnd != 0);

			auto cls = UnregisterClass((LPCWSTR)(uptr)classatom, hinstance);
			assert(cls != 0);
		}
	};

	struct Dummy_Context {
		Dummy_Window wnd;
		HGLRC hglrc;

		Dummy_Context () {
			PIXELFORMATDESCRIPTOR pfd = {0}; // Initialize to zero
			pfd.nSize =			sizeof pfd;
			pfd.nVersion =		1;
			pfd.dwFlags =		PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|PFD_DOUBLEBUFFER;
			pfd.iPixelType =	PFD_TYPE_RGBA;
			pfd.cColorBits =	32;
			pfd.cAlphaBits =	8;
			pfd.cDepthBits =	24;
			pfd.cStencilBits =	8;
			pfd.iLayerType =	PFD_MAIN_PLANE;

			int pf = ChoosePixelFormat(wnd.hdc, &pfd);
			assert(pf > 0);

			auto spf = SetPixelFormat(wnd.hdc, pf, &pfd);
			assert(spf == TRUE);

			// create dummy gl context
			hglrc = wglCreateContext(wnd.hdc);
			assert(hglrc != NULL);

			auto mc = wglMakeCurrent(wnd.hdc, hglrc);
			assert(mc == TRUE);
		}
		~Dummy_Context () {
			auto mc = wglMakeCurrent(wnd.hdc, NULL);
			assert(mc == TRUE);

			auto dc = wglDeleteContext(hglrc);
			assert(dc == TRUE);
		}
	};

	struct Context_Init_Functions {
		// _* to avoid glads macros
		PFNWGLCREATECONTEXTATTRIBSARBPROC	_wglCreateContextAttribsARB = nullptr;
		PFNWGLCHOOSEPIXELFORMATARBPROC		_wglChoosePixelFormatARB = nullptr;
	};

	Context_Init_Functions load_context_init_functions_with_dummy_context () {
		Dummy_Context dummy_context; // makes itself current

		Context_Init_Functions fs;
		fs._wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)wglGetProcAddress("wglCreateContextAttribsARB");
		fs._wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)wglGetProcAddress("wglChoosePixelFormatARB");
		return fs;
	}

	Opengl_Context::Opengl_Context (Window const& wnd) {
		static Context_Init_Functions init_funcs = load_context_init_functions_with_dummy_context(); // static init is threadsafe

		auto hdc = wnd.platform->get_hdc();

		int	wgl_format;
		{ // choose pixel format for real window
			// WGL_STEREO_ARB
			int attribs[] = {
				WGL_DRAW_TO_WINDOW_ARB,				GL_TRUE,
				WGL_SUPPORT_OPENGL_ARB,				GL_TRUE,
				WGL_ACCELERATION_ARB,				WGL_FULL_ACCELERATION_ARB,
				WGL_DOUBLE_BUFFER_ARB,				GL_TRUE,
				WGL_PIXEL_TYPE_ARB,					WGL_TYPE_RGBA_ARB,
				WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT,	GL_TRUE,
				WGL_RED_BITS_ARB,					8,
				WGL_GREEN_BITS_ARB,					8,
				WGL_BLUE_BITS_ARB,					8,
				WGL_DEPTH_BITS_ARB,					24,
				0
			};

			UINT formats_count;
			auto cpf = init_funcs._wglChoosePixelFormatARB(hdc, attribs, NULL, 1, &wgl_format, &formats_count);
			assert(cpf == TRUE);
		}

		{
			PIXELFORMATDESCRIPTOR temp_pfd;

			auto dpf = DescribePixelFormat(hdc, wgl_format, sizeof(temp_pfd), &temp_pfd);
			assert(dpf != 0);

			auto spf = SetPixelFormat(hdc, wgl_format, &temp_pfd);
			assert(spf == TRUE);
		}

		// WIP
		HGLRC hglcontext;
		{
			int attribs[] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB,		4,
				WGL_CONTEXT_MINOR_VERSION_ARB,		3,
				WGL_CONTEXT_LAYER_PLANE_ARB,		0,
				WGL_CONTEXT_FLAGS_ARB,				WGL_CONTEXT_DEBUG_BIT_ARB, // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
				WGL_CONTEXT_PROFILE_MASK_ARB,		WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB
				0
			};

			hglcontext = init_funcs._wglCreateContextAttribsARB(hdc, NULL, attribs);
		}

		wglMakeCurrent(hdc, hglcontext);

		gladLoadWGL(hdc); // how does this work with multiple windows? glad has global func ptrs, can different hdcs even have different wgl func ptr / different extensions
		gladLoadGL();
	}
	Opengl_Context::~Opengl_Context () {

	}
}
