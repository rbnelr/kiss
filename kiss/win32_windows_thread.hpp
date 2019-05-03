#pragma once
#include "win32_window.hpp"
#include "smart_ptr.hpp"
#include "clean_windows_h.hpp"

#include <thread>

namespace kiss {
	class Windows_Thread {
		static unique_ptr<Windows_Thread> singleton;
		static Windows_Thread& get_singleton ();

		std::thread thread;

		RECT border_sizes;
		ATOM wnd_classatom;

		void thread_proc ();

	public:
		Windows_Thread ();
		~Windows_Thread ();

		static void open_window (Platform_Window* wnd, std::string const& caption, iv2 initial_size, iv2 initial_pos);
		static void close_window (Platform_Window* wnd);
	};
}
