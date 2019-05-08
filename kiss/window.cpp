#pragma once
#include "window.hpp"
#include "win32_window.hpp"

namespace kiss {
	MOVE_ONLY_CLASS_DEF(Window);
	
	void swap (Window& l, Window& r) {
		std::swap(l.platform, r.platform);
	}

	Window::Window (string_view caption, iv2 initial_size, iv2 initial_pos):
			platform{make_unique<Platform_Window>(caption, initial_size, initial_pos)} {
		
	}

	Window::~Window() = default;

	Input Window::get_input () {
		return platform->get_input();
	}

	void Window::swap_buffers () {
		platform->swap_buffers();
	}
}
