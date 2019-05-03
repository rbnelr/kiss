#pragma once
#include "window.hpp"
#include "win32_window.hpp"

namespace kiss {
	MOVE_ONLY_CLASS_DEF(Window);
	
	void swap (Window& l, Window& r) {
		std::swap(l.impl, r.impl);
	}

	Window::Window (std::string const& caption, iv2 initial_size, iv2 initial_pos):
			impl{make_unique<Platform_Window>(caption, initial_size, initial_pos)} {
		
	}

	Window::~Window() = default;

	Input Window::get_input () {
		return impl->get_input();
	}

	void swap_buffers (Window& wnd) {
		
	}
}
