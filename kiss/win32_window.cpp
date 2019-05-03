#pragma once
#include "win32_window.hpp"
#include "win32_windows_thread.hpp"

namespace kiss {
	extern const iv2 default_pos;
	extern const iv2 default_size;

	const iv2 default_pos = CW_USEDEFAULT;
	const iv2 default_size = CW_USEDEFAULT;
	
	Platform_Window::Platform_Window (std::string const& caption, iv2 initial_size, iv2 initial_pos) {
		Windows_Thread::open_window(this, caption, initial_size, initial_pos);
	}
	
	Platform_Window::~Platform_Window () {
		Windows_Thread::close_window(this);
	}

	Input Platform_Window::get_input () {
		return {};
	}
}
