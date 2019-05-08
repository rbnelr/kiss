#pragma once
#include "window.hpp"

namespace kiss {
	class Opengl_Context {

	public:
		// Create an OpenGL context for a Window
		// the window passed in has to stay allocated as long as the Opengl_Context stays allocated!
		// 
		// ex, reverse construction order destruction will handle it in this case.
		//   auto kiss_wnd = kiss::Window("Kiss Test Window", 500);
		//   auto ogl = kiss::Opengl_Context(kiss_wnd);
		//
		// Supposedly on windows pixel formats can only be set once for a window, so this attaching a Opengl_Contexts a second time to a window will probably fail
		Opengl_Context (Window const& wnd);
		~Opengl_Context ();
	};
}
