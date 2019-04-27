#pragma once
#include "include.hpp"
#include "input.hpp"

#include "sanitize_windows_h.hpp"

namespace kiss {
	extern Input inp; // only one window supported, so only one input state

	// Window message handler
	LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

}
