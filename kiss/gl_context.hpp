#pragma once
#include "include.hpp"

#include "sanitize_windows_h.hpp"

#include "gl_api.hpp"
#include "wgl_api.hpp"

namespace kiss {
	void APIENTRY ogl_debuproc (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, char const* message, void const* userParam);

	HGLRC setup_gl_context (HDC hdc);
}
