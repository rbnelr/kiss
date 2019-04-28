#pragma once
#include "include.hpp"
#include "input.hpp"
#include "window.hpp"

#include "sanitize_windows_h.hpp"

#include <mutex>
#include <unordered_map>

namespace kiss {
	struct Thread_Input_State {
		static std::unordered_map<HWND, Thread_Input_State*> window_input_states; // only modified and read from message_loop thread

		std::mutex	mutex; // mutex to lock inp structure
		Input		inp; // input state, gets modified by wndproc, and read (copied) by renderer thread

		inline void set_close () {
			std::unique_lock<std::mutex> lck(mutex);
			inp.close = true;
		}
		inline void set_window_size (iv2 val) {
			std::unique_lock<std::mutex> lck(mutex);
			inp.window_size = val;
		}
		inline void set_mouse_pos (iv2 val) {
			std::unique_lock<std::mutex> lck(mutex);
			inp._mouse_pos = val;
		}

		inline Input get_input () {
			std::unique_lock<std::mutex> lck(mutex);

			Input copy = inp;
			inp.clear();
			return copy;
		}
	};

	// Window message handler
	LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

}
