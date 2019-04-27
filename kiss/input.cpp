#include "input.hpp"
#include "wndproc.hpp"

namespace kiss {
	// get input for a frame
	Input get_input () {

		{ // Pump messages
			MSG msg;
			while (PeekMessageA(&msg, NULL, 0,0, PM_REMOVE)) {

				if (msg.message == WM_QUIT)
					inp.close = true;

				TranslateMessage(&msg);
				DispatchMessageA(&msg);
			}
		}

		return inp;
	}
}
