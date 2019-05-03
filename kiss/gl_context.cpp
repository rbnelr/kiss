#include "gl_context.hpp"

#include "stdio.h"

namespace kiss {

	GLuint global_vao;

	HGLRC setup_gl_context (HDC hdc) {
	
		int	wgl_format;
		{ // choose pixel format for real window 
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
			{
				auto ret = wglChoosePixelFormatARB(hdc, attribs, NULL, 1, &wgl_format, &formats_count);
			}
		}

		//
		{
			PIXELFORMATDESCRIPTOR temp_pfd;

			DescribePixelFormat(hdc, wgl_format, sizeof(temp_pfd), &temp_pfd);

			auto ret = SetPixelFormat(hdc, wgl_format, &temp_pfd);
		}

		int gl_ver_major = 4;
		int gl_ver_minor = 3;

		bool gl_vaos_required = true; // TODO: when are VAOs required?

		bool debug_context = DEBUG;

		HGLRC hglcontext;
		{
			int attribs[] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB,		gl_ver_major,
				WGL_CONTEXT_MINOR_VERSION_ARB,		gl_ver_minor,
				WGL_CONTEXT_LAYER_PLANE_ARB,		0,
				WGL_CONTEXT_FLAGS_ARB,				(debug_context ? WGL_CONTEXT_DEBUG_BIT_ARB : 0), // WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB
				WGL_CONTEXT_PROFILE_MASK_ARB,		WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB, // WGL_CONTEXT_CORE_PROFILE_BIT_ARB
				0
			};

			hglcontext = wglCreateContextAttribsARB(hdc, NULL, attribs);
		}

		wglMakeCurrent(hdc, hglcontext);

		WGL_Api::init_singleton(hdc); // Do I need to call this if i alreay called it on the dummy context?
		GL_Api::init_singleton();

		// setting up some commonly needed opengl state
		if (GLAD_GL_ARB_debug_output) {
			glDebugMessageCallbackARB(ogl_debuproc, 0);
			//glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB); we are already using multithreading for our logging

			// without GL_DEBUG_OUTPUT_SYNCHRONOUS_ARB ogl_debuproc needs to be thread safe
		}
	
		if (gl_vaos_required) {
			glGenVertexArrays(1, &global_vao); // if the user (or the rest of the engine) does not bother to use VAOs we get a blackscreen if we don't bind one global VAO
			glBindVertexArray(global_vao);
		}

		glEnable(GL_FRAMEBUFFER_SRGB); // we dont want to user to forget this and have a gamma incorrect pipeline

		//set_vsync(wnd->vsync_mode);


		return hglcontext;
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

		fprintf(stderr, "OpenGL debug proc: severity: %s src: %s type: %s id: %d  %s\n", severity_str, src_str, type_str, id, message);
	}

}
