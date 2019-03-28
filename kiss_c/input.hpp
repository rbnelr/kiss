#pragma once

#define WIN32_LEAN_AND_MEAN 1
#include "windows.h"

#include "glad/glad_wgl.h"

#include "vectors.hpp"

struct Input {
	iv2		window_size;

	bool	close;
};

// get input for a frame
extern "C" __declspec(dllexport) Input& get_input ();

// Window message handler
LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
