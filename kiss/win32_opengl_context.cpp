#include "opengl_context.hpp"
#include "win32_window.hpp"
#include "clean_windows_h.hpp"
#include "opengl_api.hpp"
#include "wgl_api.hpp"
#include "stdio.h"

namespace kiss {
	void APIENTRY ogl_debuproc (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, cstr message, void const* userParam);

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

	Opengl_Context::Opengl_Context (Window const& wnd, OpenGL_Version version, bool backward_compatible, bool initial_vsync, bool framebuf_srgb): wnd{&wnd} {
		static Context_Init_Functions init_funcs = load_context_init_functions_with_dummy_context(); // static init is threadsafe

		auto hdc = wnd.platform->get_hdc();

		int	wgl_format;
		{ // choose pixel format for real window
			// WGL_STEREO_ARB
			struct Attrib { int key, val; };
			std::vector<Attrib> attribs;

			attribs.push_back({ WGL_DRAW_TO_WINDOW_ARB,			GL_TRUE						});
			attribs.push_back({ WGL_SUPPORT_OPENGL_ARB,			GL_TRUE						});
			attribs.push_back({ WGL_ACCELERATION_ARB,			WGL_FULL_ACCELERATION_ARB	});
			attribs.push_back({ WGL_DOUBLE_BUFFER_ARB,			GL_TRUE						});
			attribs.push_back({ WGL_PIXEL_TYPE_ARB,				WGL_TYPE_RGBA_ARB			});
			attribs.push_back({ WGL_RED_BITS_ARB,				8							});
			attribs.push_back({ WGL_GREEN_BITS_ARB,				8							});
			attribs.push_back({ WGL_BLUE_BITS_ARB,				8							});
			attribs.push_back({ WGL_DEPTH_BITS_ARB,				24							});

			if (framebuf_srgb)
				attribs.push_back({ WGL_FRAMEBUFFER_SRGB_CAPABLE_EXT, GL_TRUE });
			
			attribs.push_back({0,0});

			UINT formats_count;
			auto cpf = init_funcs._wglChoosePixelFormatARB(hdc, (int*)&attribs[0], NULL, 1, &wgl_format, &formats_count);
			assert(cpf == TRUE);
		}

		{
			PIXELFORMATDESCRIPTOR temp_pfd;

			auto dpf = DescribePixelFormat(hdc, wgl_format, sizeof(temp_pfd), &temp_pfd);
			assert(dpf != 0);

			auto spf = SetPixelFormat(hdc, wgl_format, &temp_pfd);
			assert(spf == TRUE);
		}

	#if _DEBUG
			bool debug = true;
	#else
			bool debug = false;
	#endif

		HGLRC hglcontext;
		{
			struct Attrib { int key, val; };
			std::vector<Attrib> attribs;

			attribs.push_back({ WGL_CONTEXT_MAJOR_VERSION_ARB,			version.major });
			attribs.push_back({ WGL_CONTEXT_MINOR_VERSION_ARB,			version.minor });
			attribs.push_back({ WGL_CONTEXT_LAYER_PLANE_ARB,			0 });
			attribs.push_back({ WGL_CONTEXT_FLAGS_ARB,					(debug ? WGL_CONTEXT_DEBUG_BIT_ARB : 0) | (backward_compatible && version.major >= 3 ? 0 : WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB) });
			attribs.push_back({ WGL_CONTEXT_PROFILE_MASK_ARB,			backward_compatible ? WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB : WGL_CONTEXT_CORE_PROFILE_BIT_ARB });

			attribs.push_back({0,0});

			hglcontext = init_funcs._wglCreateContextAttribsARB(hdc, NULL, (int*)&attribs[0]);
			if (hglcontext == NULL) {
				auto err = GetLastError();
				fprintf(stderr, "wglCreateContextAttribsARB() failed GetLastError: [%d]\n", err);
			}
		}

		wglMakeCurrent(hdc, hglcontext);

		// HACK!: glad loads gl as globals, since wgl and gl potentially return different pointers and extensions with different hdc/opengl versions we this would actually need to be a struct that contains the api functions
		static bool _load_gl_once = [=] () {
			gladLoadWGL(hdc);
			gladLoadGL();
			return true;
		} ();

		if (debug && GLAD_GL_ARB_debug_output) {
			glDebugMessageCallbackARB(ogl_debuproc, NULL);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB); // without GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB ogl_debuproc needs to be thread safe
		}

		set_vsync(initial_vsync);
		set_framebuffer_srgb(framebuf_srgb);
	}
	Opengl_Context::~Opengl_Context () {

	}

	void Opengl_Context::swap_buffers () {
		SwapBuffers(wnd->platform->get_hdc());
	}

	void Opengl_Context::set_framebuffer_srgb (bool on) {
		if (GLAD_GL_ARB_framebuffer_sRGB) {
			glSetEnable(GL_FRAMEBUFFER_SRGB, on);
		} else {
			if (on) {
				fprintf(stderr, "GL_ARB_framebuffer_sRGB not supported, cannot enable srgb_framebuffer\n");
			}
		}
	}
	void Opengl_Context::set_vsync (bool on) {
		if (GLAD_WGL_EXT_swap_control) {
			if (GLAD_WGL_EXT_swap_control_tear) {
				wglSwapIntervalEXT(on ? -1 : 0);
			} else {
				wglSwapIntervalEXT(on ? 1 : 0);
			}
		} else {
			fprintf(stderr, "GLAD_WGL_EXT_swap_control not supported, cannot control vsync\n");
		}
	}

	void Opengl_Context::glSetEnable (GLenum cap, bool on) {
		if (on) {
			glEnable(cap);
		} else {
			glDisable(cap);
		}
	}

	void APIENTRY ogl_debuproc (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, cstr message, void const* userParam) {
		//if (source == GL_DEBUG_SOURCE_SHADER_COMPILER_ARB) return;

		// hiding irrelevant infos/warnings
		switch (id) {
			case 131185: // Buffer detailed info (where the memory lives which is supposed to depend on the usage hint)
						 //case 1282: // using shader that was not compiled successfully
						 //
						 //case 2: // API_ID_RECOMPILE_FRAGMENT_SHADER performance warning has been generated. Fragment shader recompiled due to state change.
						 //case 131218: // Program/shader state performance warning: Fragment shader in program 3 is being recompiled based on GL state.
						 //
						 //			 //case 131154: // Pixel transfer sync with rendering warning
						 //
						 //			 //case 1282: // Wierd error on notebook when trying to do texture streaming
						 //			 //case 131222: // warning with unused shadow samplers ? (Program undefined behavior warning: Sampler object 0 is bound to non-depth texture 0, yet it is used with a program that uses a shadow sampler . This is undefined behavior.), This might just be unused shadow samplers, which should not be a problem
						 //			 //case 131218: // performance warning, because of shader recompiling based on some 'key'
				return;
		}

		cstr src_str = "<unknown>";
		switch (source) {
			case GL_DEBUG_SOURCE_API_ARB:				src_str = "GL_DEBUG_SOURCE_API_ARB";				break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:		src_str = "GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB";		break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:	src_str = "GL_DEBUG_SOURCE_SHADER_COMPILER_ARB";	break;
			case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:		src_str = "GL_DEBUG_SOURCE_THIRD_PARTY_ARB";		break;
			case GL_DEBUG_SOURCE_APPLICATION_ARB:		src_str = "GL_DEBUG_SOURCE_APPLICATION_ARB";		break;
			case GL_DEBUG_SOURCE_OTHER_ARB:				src_str = "GL_DEBUG_SOURCE_OTHER_ARB";				break;
		}

		cstr type_str = "<unknown>";
		switch (source) {
			case GL_DEBUG_TYPE_ERROR_ARB:				type_str = "GL_DEBUG_TYPE_ERROR_ARB";				break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:	type_str = "GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB";	break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:	type_str = "GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB";	break;
			case GL_DEBUG_TYPE_PORTABILITY_ARB:			type_str = "GL_DEBUG_TYPE_PORTABILITY_ARB";			break;
			case GL_DEBUG_TYPE_PERFORMANCE_ARB:			type_str = "GL_DEBUG_TYPE_PERFORMANCE_ARB";			break;
			case GL_DEBUG_TYPE_OTHER_ARB:				type_str = "GL_DEBUG_TYPE_OTHER_ARB";				break;
		}

		cstr severity_str = "<unknown>";
		switch (severity) {
			case GL_DEBUG_SEVERITY_HIGH_ARB:			severity_str = "GL_DEBUG_SEVERITY_HIGH_ARB";		break;
			case GL_DEBUG_SEVERITY_MEDIUM_ARB:			severity_str = "GL_DEBUG_SEVERITY_MEDIUM_ARB";		break;
			case GL_DEBUG_SEVERITY_LOW_ARB:				severity_str = "GL_DEBUG_SEVERITY_LOW_ARB";			break;
		}

		fprintf(stderr, "OpenGL debug proc: severity: %s src: %s type: %s id: %d  %s\n",
			severity_str, src_str, type_str, id, message);
	}
}
