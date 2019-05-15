#pragma once
#include "move_only.hpp"
#include "window.hpp"
#include "string.hpp"

#include "opengl_api.hpp"

namespace kiss {
	struct OpenGL_Version {
		int major;
		int minor;
	};

	class Opengl_Context {
		MOVE_ONLY_CLASS(Opengl_Context);

		Window const* wnd;

		void set_framebuffer_srgb (bool on); // only on init
	public:
		// Create an OpenGL context for a Window
		// the window passed in has to stay allocated as long as the Opengl_Context stays allocated!
		// 
		// ex, reverse construction order destruction will handle it in this case.
		//   auto kiss_wnd = kiss::Window("Kiss Test Window", 500);
		//   auto ogl = kiss::Opengl_Context(kiss_wnd);
		//
		// Supposedly on windows pixel formats can only be set once for a window, so this attaching a Opengl_Contexts a second time to a window will probably fail
		Opengl_Context (Window const& wnd, OpenGL_Version version, bool backward_compatible=false, bool initial_vsync=true, bool framebuf_srgb=true);
		~Opengl_Context ();

		void set_vsync (bool on);

		void glSetEnable (GLenum enum_, bool val);

		void swap_buffers ();
	};
	inline void swap (Opengl_Context& l, Opengl_Context& r) {
		std::swap(l.wnd, r.wnd);
	}
}
