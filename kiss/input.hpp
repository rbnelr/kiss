#pragma once
#include "include.hpp"

#include "vector/vector.hpp"

namespace kiss {
	struct Button {
		bool	is_down;
		bool	went_down;
		bool	went_up;
		bool	os_repeat;
	};

	//Button _buttons[GLFW_KEY_LAST +1] = {}; // lower 8 indecies are used as mouse button (GLFW_MOUSE_BUTTON_1 - GLFW_MOUSE_BUTTON_8), glfw does not seem to have anything assigned to them

	struct Input {
		bool	close;
		iv2		window_size;

		iv2		_mouse_pos; // top down, we want bottom um, get via method in input.py:Input

		void clear () { // clear frame-by-frame inputs like the close flag
			close = false;

		}
	};

}
