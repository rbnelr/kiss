#include "wndproc.hpp"

namespace kiss {
	std::unordered_map<HWND, Thread_Input_State*> Thread_Input_State::window_input_states;

	// Window message handler
	LRESULT CALLBACK wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		auto it = Thread_Input_State::window_input_states.find(hwnd);
		if (it == Thread_Input_State::window_input_states.end()) {
			return DefWindowProcA(hwnd, uMsg, wParam, lParam); // not one of our windows
		}
		auto* inp = it->second;

		switch (uMsg) {
			case WM_CLOSE: {
				inp->set_close();
				return 0;
			}

			case WM_SIZE: {
				auto w = LOWORD(lParam);
				auto h = HIWORD(lParam);

				RECT rect;
				{
					auto ret = GetClientRect(hwnd, &rect);
				}

				inp->set_window_size(max(iv2(w,h), 1));

				//if (!fullscreen) {
				//write_window_placement_save(hWnd);
				//}
				return 0;
			}

			case WM_MOUSEMOVE: {
				auto x = LOWORD(lParam);
				auto y = HIWORD(lParam);

				inp->set_mouse_pos(iv2(x,y));

				return 0;
			}
			
			default:
				return DefWindowProcA(hwnd, uMsg, wParam, lParam);
		}
	}

}
