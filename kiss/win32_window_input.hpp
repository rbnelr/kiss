#pragma once
#include "win32_window.hpp"
#include "clean_windows_h.hpp"

#include <mutex>

namespace kiss {
	
	class Threaded_Input_State {
		Input i;

		std::mutex mtx;
	public:
		#define SCOPED_LOCK() std::lock_guard<std::mutex> lck(mtx)

		void set_close (bool b) {
			SCOPED_LOCK();
			i.close = b;
		}
		
		Input copy_input () {
			return i;
		}
		Input get_input_for_frame () {
			auto inp = copy_input();
			i.clear();
			return inp;
		}

		#undef SCOPED_LOCK
	};
}
