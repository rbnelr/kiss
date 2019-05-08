#pragma once
#include "move_only.hpp"
#include "vector/vector.hpp"
#include "input.hpp"
#include "string.hpp"
#include "smart_ptr.hpp"
#include "win32_remote_proc_caller.hpp"
#include "win32_window_input.hpp"
#include "clean_windows_h.hpp"
#include <thread>
#include <unordered_map>
#include <mutex>

namespace kiss {
	constexpr LONG WINDOWED_STYLE =					WS_VISIBLE|WS_OVERLAPPEDWINDOW;
	constexpr LONG WINDOWED_EX_STYLE =				WS_EX_APPWINDOW|WS_EX_WINDOWEDGE;

	constexpr LONG BORDERLESS_FULLSCREEN_STYLE =	WS_VISIBLE;
	constexpr LONG BORDERLESS_FULLSCREEN_EX_STYLE =	WS_EX_APPWINDOW;

	RECT find_windows_border_sizes (DWORD style, DWORD exstyle); // Get window border sizes
	ATOM register_standard_window_class (HINSTANCE hinstance);
	void register_raw_input_devices (HWND hwnd);

	LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	class Platform_Window;

	class Window_Thread {
		std::thread thread;
		Remote_Proc_Caller remote_proc_caller;

	public:
		static unique_ptr<Window_Thread> singleton;
		static std::mutex singleton_mtx;

		std::unordered_map<HWND, Platform_Window*> windows;

		HINSTANCE hinstance;
		RECT border_sizes;
		ATOM wnd_classatom;

		HWND open_window (Platform_Window* window, string_view caption, iv2 initial_size, iv2 initial_pos);
		void close_window (Platform_Window* window);

		void register_window (HWND hwnd, Platform_Window* window);
		void unregister_window (HWND hwnd);
		Platform_Window* get_window (HWND hwnd);

		void thread_proc ();
		void message_loop ();

		Window_Thread ();
		~Window_Thread ();

		void execute_on_thread (std::function<void()> f);
	};

	class Platform_Window {
		NO_MOVE_COPY_CLASS(Platform_Window);

		friend HWND Window_Thread::open_window (Platform_Window* window, string_view caption, iv2 initial_size, iv2 initial_pos);

		HWND	hwnd;
		HDC		hdc;

	public:
		Threaded_Input_State input_state;

		inline HWND get_hwnd () { return hwnd; }
		inline HDC get_hdc () { return hdc; }

		// opens a window
		Platform_Window (string_view caption, iv2 initial_size, iv2 initial_pos);
		// closes window
		~Platform_Window();

		// get input for a frame
		Input get_input ();

		void swap_buffers ();
	};
}
