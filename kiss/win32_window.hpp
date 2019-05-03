#pragma once
#include "move_only.hpp"
#include "vector/vector.hpp"
#include "input.hpp"
#include "win32_window_proc.hpp"

#include <string>

#include "clean_windows_h.hpp"

namespace kiss {
	class Platform_Window {
		NO_MOVE_COPY_CLASS(Platform_Window);

		HWND	hwnd;
		HDC		hdc;

		Threaded_Input_State input_state;

	public:
		inline HWND get_hwnd () { return hwnd; }
		inline HDC get_hdc () { return hdc; }

		// opens a window
		Platform_Window (std::string const& caption, iv2 initial_size, iv2 initial_pos);
		// closes window
		~Platform_Window();

		// get input for a frame
		Input get_input ();
	};
}
