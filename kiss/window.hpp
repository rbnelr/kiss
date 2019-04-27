#pragma once
#include "include.hpp"
#include "input.hpp"
#include "vector/vector.hpp"

#include <thread>

namespace kiss {
	API_VAR const iv2 default_pos;
	API_VAR const iv2 default_size;

	struct Platform_Window;
	void delete_Platform_Window (Platform_Window* p);

	struct Window {

		unique_ptr<Platform_Window, decltype(&delete_Platform_Window)> platform; // pointer to platform specific to hide windows.h

		Window (char const* caption, iv2 initial_size=default_size, iv2 initial_pos=default_pos); // opens a window
		~Window (); // closes window

		Input get_input (); // get input for a frame
		void swap_buffers ();

		inline Window (Window&& r): platform{std::move(r.platform)} {}
	};
}
