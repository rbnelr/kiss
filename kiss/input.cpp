#include "input.hpp"

Input inp; // only one window supported, so only one input state

// get input for a frame
Input& get_input () {
	
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

// Window message handler
LRESULT CALLBACK wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
		case WM_CLOSE: {
			PostQuitMessage(0);
			return 0;
		}

		case WM_SIZE: {
			auto w = LOWORD(lParam);
			auto h = HIWORD(lParam);

			RECT rect;
			{
				auto ret = GetClientRect(hwnd, &rect);
			}

			inp.window_size.x = max(w, 1);
			inp.window_size.y = max(h, 1);

			//if (!fullscreen) {
			//write_window_placement_save(hWnd);
			//}
			return 0;
		}


		default:
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);
	}
}
