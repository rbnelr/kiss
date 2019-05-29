#pragma once
#include "win32_window.hpp"
#include "smart_ptr.hpp"
#include "assert.h"
#include "thread_name.hpp"

namespace kiss {
	//////////////
	// Actual win32 windowing calls all done on one thread
	//////////////

	extern const iv2 default_pos;
	extern const iv2 default_size;

	const iv2 default_pos = CW_USEDEFAULT;
	const iv2 default_size = CW_USEDEFAULT;

	void adjust_window_client_size (HWND hwnd, iv2 initial_size) {
		RECT client_rect, screen_rect;

		auto ret = GetClientRect(hwnd, &client_rect);
		assert(ret != 0);

		iv2 borders = initial_size - iv2(client_rect.right, client_rect.bottom);

		ret = GetWindowRect(hwnd, &screen_rect);
		assert(ret != 0);

		screen_rect.right	+= borders.x;
		screen_rect.bottom	+= borders.y;

		ret = SetWindowPos(hwnd, NULL, 0, 0, screen_rect.right - screen_rect.left, screen_rect.bottom - screen_rect.top, SWP_NOMOVE|SWP_NOZORDER);
		assert(ret != 0);

	}
	ATOM register_standard_window_class (HINSTANCE hinstance) {
		auto hicon		= LoadIcon(NULL, IDI_WINLOGO);
		auto hcursor	= LoadCursor(NULL, IDC_ARROW);

		WNDCLASS wndclass = {}; // Initialize to zero
		wndclass.style =			CS_OWNDC|CS_HREDRAW|CS_VREDRAW; // CS_HREDRAW|CS_VREDRAW might prevent flicker with opengl apps
		wndclass.lpfnWndProc =		wndproc;
		wndclass.hInstance =		hinstance;
		wndclass.hIcon = 			hicon;
		wndclass.hCursor = 			hcursor;
		wndclass.lpszClassName =	L"kisslib_window";

		auto atom = RegisterClass(&wndclass);
		assert(atom != 0);
		return atom;
	}
	void register_raw_input_devices (HWND hwnd) {
		RAWINPUTDEVICE	rid[2];
		// Mouse
		rid[0].usUsagePage =	1;
		rid[0].usUsage =		2;
		rid[0].dwFlags =		RIDEV_DEVNOTIFY;
		rid[0].hwndTarget =		hwnd;
		// Keyboard
		rid[1].usUsagePage =	1;
		rid[1].usUsage =		6;
		rid[1].dwFlags =		RIDEV_DEVNOTIFY;
		rid[1].hwndTarget =		hwnd;

		// RIDEV_NOLEGACY, RIDEV_NOHOTKEYS ???

		auto res = RegisterRawInputDevices(rid, 2, sizeof(RAWINPUTDEVICE));
		assert(res != FALSE);
	}

	HWND Window_Thread::open_window (Platform_Window* window, string_view caption, iv2 initial_size, iv2 initial_pos) {
		auto hwnd = CreateWindowEx(
			WINDOWED_EX_STYLE, (LPCWSTR)(uptr)wnd_classatom, utf8_to_wchar(caption).c_str(), WINDOWED_STYLE & ~WS_VISIBLE,
			initial_pos.x, initial_pos.y, initial_size.x, initial_size.y,
			NULL, NULL, hinstance, window);
		assert(hwnd != INVALID_HANDLE_VALUE);

		adjust_window_client_size(hwnd, initial_size);

		ShowWindow(hwnd, SW_RESTORE);

		register_raw_input_devices(hwnd);

		auto hdc = GetDC(hwnd);
		assert(hdc != NULL);

		window->hwnd = hwnd;
		window->hdc = hdc;

		return hwnd;
	}
	void Window_Thread::close_window (Platform_Window* window) {
		auto dc = ReleaseDC(window->get_hwnd(), window->get_hdc());
		assert(dc == 1);

		auto wnd = DestroyWindow(window->get_hwnd());
		assert(wnd != 0);
	}

	void Window_Thread::thread_proc () {
		set_current_thread_name("kisslib_window_message_thread");

		hinstance = GetModuleHandle(NULL);

		wnd_classatom = register_standard_window_class(hinstance);

		message_loop();

		auto cls = UnregisterClass((LPCWSTR)(uptr)wnd_classatom, hinstance);
		assert(cls != 0);
	}

	void Window_Thread::message_loop () {
		HANDLE rpc_wait = remote_proc_caller.get_wait_for_execute_procedure_handle();

		MSG msg;
		for (;;) {
			auto res = MsgWaitForMultipleObjects(1, &rpc_wait, FALSE, INFINITE, QS_ALLINPUT);

			if (res == WAIT_OBJECT_0) {

				remote_proc_caller.thread_execute_procedure();

			} else if (res == WAIT_FAILED) {

				assert(false);

			} else {

				auto res = GetMessage(&msg, NULL, 0,0);
				if (res < 0) {
					// error, report?
					break;
				} else if (res == 0) { // WM_QUIT
					break;
				} else {
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
			}
		}
	}

	LRESULT CALLBACK wm_input (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam, Platform_Window* wnd) {
		RAWINPUT ri;
		{
			UINT ri_size = sizeof(RAWINPUT);
			auto ret = GetRawInputData((HRAWINPUT)lParam, RID_INPUT, &ri, &ri_size, sizeof(RAWINPUTHEADER));
			assert(ret <= sizeof(RAWINPUT));
		}

		switch (ri.header.dwType) {
			case RIM_TYPEMOUSE: {
				assert(ri.header.dwSize == (sizeof(RAWINPUTHEADER) +sizeof(RAWMOUSE)));
				auto& m = ri.data.mouse;

				iv2 xy = iv2(m.lLastX, m.lLastY);

				if (m.usFlags & MOUSE_ATTRIBUTES_CHANGED) {
					//printf("WM_INPUT: MOUSE_ATTRIBUTES_CHANGED\n");
				}

				// flags & MOUSE_VIRTUAL_DESKTOP; // This is set when running in VM

				if (m.usFlags & MOUSE_MOVE_ABSOLUTE) {
					// got abs mouse input for some reason (touch? in VM?)
					wnd->input_state.set_mouse_pos(xy);
				} else {
					wnd->input_state.accum_mouse_delta(xy);
				}

				struct key {
					USHORT		down_code;
					USHORT		up_code;
					char const*	button_name;
				};
				static constexpr key button_event_flags[] = {
					{ RI_MOUSE_LEFT_BUTTON_DOWN,	RI_MOUSE_LEFT_BUTTON_UP,	"LMB" },
					{ RI_MOUSE_MIDDLE_BUTTON_DOWN,	RI_MOUSE_MIDDLE_BUTTON_UP,	"MMB" },
					{ RI_MOUSE_RIGHT_BUTTON_DOWN,	RI_MOUSE_RIGHT_BUTTON_UP,	"RMB" },
					{ RI_MOUSE_BUTTON_4_DOWN,		RI_MOUSE_BUTTON_4_UP,		"MB4" },
					{ RI_MOUSE_BUTTON_5_DOWN,		RI_MOUSE_BUTTON_5_UP,		"MB5" },
				};

				for (int i=0; i<5; i=++i) {
					bool down =		(m.usButtonFlags & button_event_flags[i].down_code) != 0;
					bool up =		(m.usButtonFlags & button_event_flags[i].up_code) != 0;

					if (down && up) {
						assert(false);
					} else if (down || up) {
						wnd->input_state.set_button(button_event_flags[i].button_name, down);

						//printf("WM_INPUT: RIM_TYPEMOUSE: %s %s\n", button_event_flags[i].button_name, down ? "down" : "up");
					}
				}
			} break;

			case RIM_TYPEKEYBOARD: {
				assert(ri.header.dwSize == (sizeof(RAWINPUTHEADER) +sizeof(RAWKEYBOARD)));
				auto& kb = ri.data.keyboard;

				bool is_down = (kb.Flags & RI_KEY_BREAK) == 0; // true: RI_KEY_MAKE  false: RI_KEY_BREAK
				bool e0 = (kb.Flags & RI_KEY_E0) != 0;
				bool e1 = (kb.Flags & RI_KEY_E1) != 0;

				auto key_name = raw_input_map_vk_to_button(kb.VKey, kb.MakeCode, e0);

				//printf("WM_INPUT: RIM_TYPEKEYBOARD: Key %10s (0x%x) [0x%x] %s %s %s\n", key_name, kb.VKey, kb.MakeCode, is_down ? "down":"  up", e0?"E0":"  ", e1?"E1":"  ");

				wnd->input_state.set_button(key_name, is_down);

			} break;
		}
		#if 0
			
				}
				case RIM_TYPEKEYBOARD: {
					assert(rawInput.header.dwSize == (sizeof(RAWINPUTHEADER) +sizeof(RAWKEYBOARD)));
					auto kb = rawInput.data.keyboard;

					auto flags =	kb.Flags;
					auto message =	kb.Message;
					auto vkey =		kb.VKey;

					bool state = // TODO: Is this reliable? see the failed assert on mismatched  state  and  message
						(flags & 1) == 0 ?
						true : // RI_KEY_MAKE
						false; // RI_KEY_BREAK

							   // Make sure kb.Message matches kb.Flags
					switch (message) {
						case WM_SYSKEYDOWN:
						case WM_KEYDOWN: {
							//assert(state == true); // TODO: This failed while moving camera & pressing multiple keys at the same time
							assertNeverBreak(state == true, "Mismatched raw input key message (", message, ") and flags (", flags, ")");
						} break;
						case WM_SYSKEYUP:
						case WM_KEYUP: {
							//assert(state == false); // TODO: This failed while moving camera & pressing multiple keys at the same time
							assertNeverBreak(state == false, "Mismatched raw input key message (", message, ") and flags (", flags, ")");
						} break;
						default: assert(false);
					}

					bool isExtendedKey;
					{
						bool e0 = (flags & RI_KEY_E0) != 0;
						bool e1 = (flags & RI_KEY_E1) != 0;

						// Docs say e0 -> left version of the key, e1 -> right version of the key
						//  but this seems to be wrong

						isExtendedKey = e0;
					}

					bool changed;
					bool down =		state == true;
					bool up =		state == false;

					switch (vkey) {

						case VK_SHIFT: {
							if (!isExtendedKey) {
								// left SHIFT
							} else {
								// right SHIFT
							}
							changed = shiftState != state;
							shiftState = state;
							// DO pass SHIFT to game input
						} break;

						case VK_MENU: {
							if (!isExtendedKey) {
								// left ALT
							} else {
								// right ALT
							}
							changed = altState != state;
							altState = state;
							return 0; // Don't pass ALT to game input
						} break;

						case VK_F1: {
							changed = f1State != state;
							f1State = state;
							if (changed && down) {
								toggleMouselookCursor(hWnd);
							}
							return 0; // Don't pass F1 to game input
						} break;

						case VK_F4: {
							changed = f4State != state;
							f4State = state;
							if (altState && changed && down) {
								closeApplication();
							}
							return 0; // Don't pass F4 to game input
						} break;

						case VK_F10: {
							changed = f10State != state;
							f10State = state;
							if (changed && down) {
								SYNC_SCOPED_MUTEX_LOCK(shared_state_mutex);
								reloadable_dll_do_reload = shiftState ? RLD_FULL : RLD_PARTIAL;
							}
							return 0; // Don't pass F10 to game input
						} break;

						case VK_F11: {
							changed = f11State != state;
							f11State = state;
							if (changed && down) {
								toggleFullscreen(hWnd);
							}
							return 0; // Don't pass F11 to game input
						} break;

						default: {

						}
					}

					buttons::button_e button;
					auto isKnownKey = mapVirtualKeyToGameKey(vkey, isExtendedKey, &button);

					if (isKnownKey) {
						bool prevState = gameButtonState.get(button +0);

						if (state != prevState) {

							gameButtonState.toggle(button +0);
							{
								SYNC_SCOPED_MUTEX_LOCK(shared_state_mutex);
								if (reloadable_dll_initialized) { // Dont send input to dll while dll is not initialized
									reloadable_dll.input_shared_state_process_button_binding_input(button, state);
								}
							}
						}
					}
					return 0;
				}
				default: assert(false); return 0;
			}
		}
		#endif

		return 0;
	}
	/* TODO: improve window resizing
		https://stackoverflow.com/questions/10615272/opengl-flickering-damaged-with-window-resize-and-dwm-active
		https://stackoverflow.com/questions/53000291/how-to-smooth-ugly-jitter-flicker-jumping-when-resizing-windows-especially-drag/53000292#53000292
	*/
	LRESULT CALLBACK wndproc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
		auto* thr = Window_Thread::singleton.get(); // this has to always be constant at this point, threadsafe
		auto* wnd = thr->get_window(hwnd);

		if (!wnd && uMsg != WM_NCCREATE) {
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}

		switch (uMsg) {

			case WM_NCCREATE: {
				auto* cs = (CREATESTRUCT*)lParam;
				auto* wnd = (Platform_Window*)cs->lpCreateParams;

				thr->register_window(hwnd, wnd);
			} return TRUE;

			case WM_NCDESTROY: {
				thr->unregister_window(hwnd);
			} return 0;

			case WM_CLOSE: {
				wnd->input_state.set_close(true);
			} return 0;

			case WM_SIZE: {
				int w = LOWORD(lParam);
				int h = HIWORD(lParam);
				iv2 sz = iv2(w,h);
				sz = max(sz, 1);

				wnd->input_state.set_window_size(sz);
			} return 0;

			case WM_MOUSEMOVE: {
				int x = LOWORD(lParam);
				int y = HIWORD(lParam);
				iv2 pos = iv2(x,y);

				wnd->input_state.set_mouse_pos(pos);
			} return 0;

			case WM_INPUT:
				return wm_input(hwnd, uMsg, wParam, lParam, wnd);

			case WM_PAINT: {
					
			} return 0;
			case WM_ERASEBKGND: {
				// flicker prevention
			} return 1;

			default:
				return DefWindowProc(hwnd, uMsg, wParam, lParam);
		}
	}

	//////////////
	// Bookkeeping happening between all threads that create windows to handle the message thread being on another thread
	//////////////

	Input Platform_Window::get_input () {
		return input_state.get_input_for_frame();
	}

	unique_ptr<Window_Thread> Window_Thread::singleton;
	std::mutex Window_Thread::singleton_mtx;

	Platform_Window::Platform_Window (string_view caption, iv2 initial_size, iv2 initial_pos) {

		{ // Threadsafe singleton creation
			std::lock_guard<std::mutex> lck(Window_Thread::singleton_mtx);

			if (!Window_Thread::singleton) // Starts window thread when first window is created
				Window_Thread::singleton = make_unique<Window_Thread>();
		}
		auto* thr = Window_Thread::singleton.get();

		thr->execute_on_thread(std::bind(&Window_Thread::open_window, thr, this, caption, initial_size, initial_pos));
	}
	
	Platform_Window::~Platform_Window () {
		auto* thr = Window_Thread::singleton.get();

		thr->execute_on_thread(std::bind(&Window_Thread::close_window, thr, this));

		{ // Threadsafe singleton deletion
			std::lock_guard<std::mutex> lck(Window_Thread::singleton_mtx);

			if (thr->windows.size() == 0) { // Shuts down window thread when last window is closed
				Window_Thread::singleton.reset();
			}
		}
	}

	void Window_Thread::execute_on_thread (std::function<void()> f) {
		remote_proc_caller.execute_on_thread(f);
	}

	Window_Thread::Window_Thread () {
		thread = std::thread(&Window_Thread::thread_proc, this);
	}
	Window_Thread::~Window_Thread () {
		execute_on_thread([] () { PostQuitMessage(0); });

		thread.join();
	}

	void Window_Thread::register_window (HWND hwnd, Platform_Window* window) {
		windows[hwnd] = window;
	}
	void Window_Thread::unregister_window (HWND hwnd) {
		windows.erase(hwnd);
	}
	Platform_Window* Window_Thread::get_window (HWND hwnd) {
		auto res = windows.find(hwnd);
		return res == windows.end() ? nullptr : res->second;
	}

}
