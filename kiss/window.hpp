#pragma once
#include "include.hpp"
#include "input.hpp"
#include "vector/vector.hpp"

namespace kiss {
	API_VAR const iv2 default_pos;
	API_VAR const iv2 default_size;

	struct Platform_Window;

	struct Window {
		MOVE_ONLY_CLASS(Window)

		Platform_Window* platform_impl; // pointer to platform specific to hide windows.h

		Window (std::string caption, iv2 initial_size=default_size, iv2 initial_pos=default_pos); // opens a window
		~Window (); // closes window

		Input get_input (); // get input for a frame
		void swap_buffers ();
	};
	inline void swap (Window& l, Window& r) {
		std::swap(l.platform_impl, r.platform_impl);
	}
}
