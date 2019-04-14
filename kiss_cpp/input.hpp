#pragma once

#define WIN32_LEAN_AND_MEAN 1
#include "windows.h"

#include "glad/glad_wgl.h"

#include "vector/vector.hpp"

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

};

// get input for a frame
extern "C" __declspec(dllexport) Input get_input ();

// Window message handler
LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
