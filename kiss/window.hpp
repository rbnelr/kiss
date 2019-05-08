#pragma once
#include "move_only.hpp"
#include "smart_ptr.hpp"
#include "vector/vector.hpp"
#include "input.hpp"
#include "string.hpp"

namespace kiss {
	extern const iv2 default_pos;
	extern const iv2 default_size;

	class Platform_Window;

	class Window {
		MOVE_ONLY_CLASS_DECL(Window);
	public:
		unique_ptr<Platform_Window> platform; // Hide implementation so that user does not need to indirectly include windows.h etc.

		// opens a window
		Window (string_view caption, iv2 initial_size = default_pos, iv2 initial_pos = default_size);
		// closes window
		~Window();

		// get input for a frame
		Input get_input ();

		void swap_buffers ();
	};
	void swap (Window& l, Window& r);
}
