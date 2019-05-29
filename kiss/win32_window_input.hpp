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

		// called on input producer thread (window thread)
		void set_close (bool b) {
			SCOPED_LOCK();
			i.close = b;
		}
		void set_window_size (iv2 sz) {
			SCOPED_LOCK();
			i.window_size = sz;
		}
		void set_mouse_pos (iv2 pos) {
			SCOPED_LOCK();
			i._os_mouse_pos = pos;
		}
		void accum_mouse_delta (iv2 delta) {
			if (!equal(delta, 0)) { // avoid lock
				SCOPED_LOCK();
				i.mouse_delta += delta;
			}
		}

		void set_button (std::string const& button, bool state) {
			SCOPED_LOCK();

			auto& b = i.get_create_button(button);
			if (b.is_down != state) {
				b.went_down	= !b.is_down &&  state;
				b.went_up	=  b.is_down && !state;
				b.is_down	= state;
			}
		}
		
		// called on input consumer thread (frame loop thread)
		Input copy_input () {
			return i;
		}
		Input get_input_for_frame () {
			SCOPED_LOCK();
			auto inp = copy_input();
			i.clear();
			return inp;
		}

		#undef SCOPED_LOCK
	};

	inline char const* raw_input_map_vk_to_button (USHORT vkey, USHORT scancode, bool E0) { // map 
		#define null return nullptr
		switch (vkey) {
			case 0x00: /* NULL? */					null;
			case 0x01: /* VK_LBUTTON */				null; // return "VK_LBUTTON"; // mouse buttons should never happen on RIM_TYPEKEYBOARD
			case 0x02: /* VK_RBUTTON */				null; // return "VK_RBUTTON";
			case 0x03: /* VK_CANCEL */				return "VK_CANCEL";
			case 0x04: /* VK_MBUTTON */				null; // return "VK_MBUTTON";
			case 0x05: /* VK_XBUTTON1 */			null; // return "VK_XBUTTON1";
			case 0x06: /* VK_XBUTTON2 */			null; // return "VK_XBUTTON2";
			case 0x07: /* Undefined */				null;
			case 0x08: /* VK_BACK */					return "BACKSPACE";
			case 0x09: /* VK_TAB */						return "TABULATOR";
			case 0x0A: /* Reserved */				null;
			case 0x0B: /* Reserved */				null;
			case 0x0C: /* CLEAR */					return "VK_CLEAR";
			case 0x0D: /* VK_RETURN */					return E0 ? "NP_ENTER":"ENTER";
			case 0x0E: /* Undefined */				null;
			case 0x0F: /* Undefined */				null;
			case 0x10: /* VK_SHIFT */					return scancode == 0x36 ? "RSHIFT":"LSHIFT"; // LSHIFT: scancode=0x2a  RSHIFT: scancode=0x36
			case 0x11: /* VK_CONTROL */					return E0 ? "RCTRL":"LCTRL";
			case 0x12: /* VK_MENU */					return E0 ? "RALT":"LALT";
			case 0x13: /* VK_PAUSE */				return "VK_PAUSE";
			case 0x14: /* VK_CAPITAL */					return "CAPSLOCK";
			case 0x15: /* VK_HANGUL */				return "VK_HANGUL";
			case 0x16: /* Undefined */				null;
			case 0x17: /* VK_JUNJA */				return "VK_JUNJA";
			case 0x18: /* VK_FINAL */				return "VK_FINAL";
			case 0x19: /* VK_HANJA */				return "VK_HANJA";
			case 0x1A: /* VK_KANJI */				return "VK_KANJI";
			case 0x1B: /* VK_ESCAPE */					return "ESCAPE";
			case 0x1C: /* VK_CONVERT */				return "VK_CONVERT";
			case 0x1D: /* VK_NONCONVERT */			return "VK_NONCONVERT";
			case 0x1E: /* VK_ACCEPT */				return "VK_ACCEPT";
			case 0x1F: /* VK_MODECHANGE */			return "VK_MODECHANGE";
			case 0x20: /* VK_SPACE */					return "SPACE";
			case 0x21: /* VK_PRIOR */					return "PAGE_UP";
			case 0x22: /* VK_NEXT */					return "PAGE_DOWN";
			case 0x23: /* VK_END */						return "END";
			case 0x24: /* VK_HOME */					return "HOME";
			case 0x25: /* VK_LEFT */					return "LEFT";
			case 0x26: /* VK_UP */						return "UP";
			case 0x27: /* VK_RIGHT */					return "RIGHT";
			case 0x28: /* VK_DOWN */					return "DOWN";
			case 0x29: /* VK_SELECT */				return "VK_SELECT";
			case 0x2A: /* VK_PRINT */				return "VK_PRINT";
			case 0x2B: /* VK_EXECUTE */				return "VK_EXECUTE";
			case 0x2C: /* VK_SNAPSHOT */				return "PRINT_SCREEN";
			case 0x2D: /* VK_INSERT */					return "INSERT";
			case 0x2E: /* VK_DELETE */					return "DELETE";
			case 0x2F: /* VK_HELP */				return "VK_HELP";
			case 0x30: /* 0 */							return "0";
			case 0x31: /* 1 */							return "1";
			case 0x32: /* 2 */							return "2";
			case 0x33: /* 3 */							return "3";
			case 0x34: /* 4 */							return "4";
			case 0x35: /* 5 */							return "5";
			case 0x36: /* 6 */							return "6";
			case 0x37: /* 7 */							return "7";
			case 0x38: /* 8 */							return "8";
			case 0x39: /* 9 */							return "9";
			case 0x3A: /* Undefined */				null;
			case 0x3B: /* Undefined */				null;
			case 0x3C: /* Undefined */				null;
			case 0x3D: /* Undefined */				null;
			case 0x3E: /* Undefined */				null;
			case 0x3F: /* Undefined */				null;
			case 0x40: /* Undefined */				null;
			case 0x41: /* A */							return "A";
			case 0x42: /* B */							return "B";
			case 0x43: /* C */							return "C";
			case 0x44: /* D */							return "D";
			case 0x45: /* E */							return "E";
			case 0x46: /* F */							return "F";
			case 0x47: /* G */							return "G";
			case 0x48: /* H */							return "H";
			case 0x49: /* I */							return "I";
			case 0x4A: /* J */							return "J";
			case 0x4B: /* K */							return "K";
			case 0x4C: /* L */							return "L";
			case 0x4D: /* M */							return "M";
			case 0x4E: /* N */							return "N";
			case 0x4F: /* O */							return "O";
			case 0x50: /* P */							return "P";
			case 0x51: /* Q */							return "Q";
			case 0x52: /* R */							return "R";
			case 0x53: /* S */							return "S";
			case 0x54: /* T */							return "T";
			case 0x55: /* U */							return "U";
			case 0x56: /* V */							return "V";
			case 0x57: /* W */							return "W";
			case 0x58: /* X */							return "X";
			case 0x59: /* Y */							return "Y";
			case 0x5A: /* Z */							return "Z";
			case 0x5B: /* L_LOGO */						return "LLOGO";
			case 0x5C: /* VK_RWIN */					return "RLOGO"; // could not test on my desktop since my keyboard replaces the right logo key
			case 0x5D: /* VK_APPS */					return "APP";
			case 0x5E: /* Reserved */				null;
			case 0x5F: /* VK_SLEEP */				return "VK_SLEEP";
			case 0x60: /* VK_NUMPAD0 */					return "NP0";
			case 0x61: /* VK_NUMPAD1 */					return "NP1";
			case 0x62: /* VK_NUMPAD2 */					return "NP2";
			case 0x63: /* VK_NUMPAD3 */					return "NP3";
			case 0x64: /* VK_NUMPAD4 */					return "NP4";
			case 0x65: /* VK_NUMPAD5 */					return "NP5";
			case 0x66: /* VK_NUMPAD6 */					return "NP6";
			case 0x67: /* VK_NUMPAD7 */					return "NP7";
			case 0x68: /* VK_NUMPAD8 */					return "NP8";
			case 0x69: /* VK_NUMPAD9 */					return "NP9";
			case 0x6A: /* VK_MULTIPLY */				return "NP_MULTIPLY";
			case 0x6B: /* VK_ADD */						return "NP_PLUS";
			case 0x6C: /* VK_SEPARATOR */			return "VK_SEPARATOR";
			case 0x6D: /* VK_SUBTRACT */				return "NP_MINUS";
			case 0x6E: /* VK_DECIMAL */					return "NP_DECIMAL";
			case 0x6F: /* VK_DIVIDE */					return "NP_DIVIDE";
			case 0x70: /* VK_F1 */						return "F1";
			case 0x71: /* VK_F2 */						return "F2";
			case 0x72: /* VK_F3 */						return "F3";
			case 0x73: /* VK_F4 */						return "F4";
			case 0x74: /* VK_F5 */						return "F5";
			case 0x75: /* VK_F6 */						return "F6";
			case 0x76: /* VK_F7 */						return "F7";
			case 0x77: /* VK_F8 */						return "F8";
			case 0x78: /* VK_F9 */						return "F9";
			case 0x79: /* VK_F10 */						return "F10";
			case 0x7A: /* VK_F11 */						return "F11";
			case 0x7B: /* VK_F12 */						return "F12";
			case 0x7C: /* VK_F13 */						return "F13";
			case 0x7D: /* VK_F14 */						return "F14";
			case 0x7E: /* VK_F15 */						return "F15";
			case 0x7F: /* VK_F16 */						return "F16";
			case 0x80: /* VK_F17 */						return "F17";
			case 0x81: /* VK_F18 */						return "F18";
			case 0x82: /* VK_F19 */						return "F19";
			case 0x83: /* VK_F20 */						return "F20";
			case 0x84: /* VK_F21 */						return "F21";
			case 0x85: /* VK_F22 */						return "F22";
			case 0x86: /* VK_F23 */						return "F23";
			case 0x87: /* VK_F24 */						return "F24";
			case 0x88: /* Unassigned */				null;
			case 0x89: /* Unassigned */				null;
			case 0x8A: /* Unassigned */				null;
			case 0x8B: /* Unassigned */				null;
			case 0x8C: /* Unassigned */				null;
			case 0x8D: /* Unassigned */				null;
			case 0x8E: /* Unassigned */				null;
			case 0x8F: /* Unassigned */				null;
			case 0x90: /* VK_NUMLOCK */					return "NUMLOCK";
			case 0x91: /* VK_SCROLL */					return "SCROLL_LOCK";
			case 0x92: /* OEM specific */			null;
			case 0x93: /* OEM specific */			null;
			case 0x94: /* OEM specific */			null;
			case 0x95: /* OEM specific */			null;
			case 0x96: /* OEM specific */			null;
			case 0x97: /* Unassigned */				null;
			case 0x98: /* Unassigned */				null;
			case 0x99: /* Unassigned */				null;
			case 0x9A: /* Unassigned */				null;
			case 0x9B: /* Unassigned */				null;
			case 0x9C: /* Unassigned */				null;
			case 0x9D: /* Unassigned */				null;
			case 0x9E: /* Unassigned */				null;
			case 0x9F: /* Unassigned */				null;
			case 0xA0: /* VK_LSHIFT */				null;//return "VK_LSHIFT"; // these should not happen on raw input
			case 0xA1: /* VK_RSHIFT */				null;//return "VK_RSHIFT";
			case 0xA2: /* VK_LCONTROL */			null;//return "VK_LCONTROL";
			case 0xA3: /* VK_RCONTROL */			null;//return "VK_RCONTROL";
			case 0xA4: /* VK_LMENU */				null;//return "VK_LMENU";
			case 0xA5: /* VK_RMENU */				null;//return "VK_RMENU";
			case 0xA6: /* VK_BROWSER_BACK */		return "VK_BROWSER_BACK";
			case 0xA7: /* VK_BROWSER_FORWARD */		return "VK_BROWSER_FORWARD";
			case 0xA8: /* VK_BROWSER_REFRESH */		return "VK_BROWSER_REFRESH";
			case 0xA9: /* VK_BROWSER_STOP */		return "VK_BROWSER_STOP";
			case 0xAA: /* VK_BROWSER_SEARCH */		return "VK_BROWSER_SEARCH";
			case 0xAB: /* VK_BROWSER_FAVORITES */	return "VK_BROWSER_FAVORITES";
			case 0xAC: /* VK_BROWSER_HOME */		return "VK_BROWSER_HOME";
			case 0xAD: /* VK_VOLUME_MUTE */			return "VK_VOLUME_MUTE";
			case 0xAE: /* VK_VOLUME_DOWN */			return "VK_VOLUME_DOWN";
			case 0xAF: /* VK_VOLUME_UP */			return "VK_VOLUME_UP";
			case 0xB0: /* VK_MEDIA_NEXT_TRACK */	return "VK_MEDIA_NEXT_TRACK";
			case 0xB1: /* VK_MEDIA_PREV_TRACK */	return "VK_MEDIA_PREV_TRACK";
			case 0xB2: /* VK_MEDIA_STOP */			return "VK_MEDIA_STOP";
			case 0xB3: /* VK_MEDIA_PLAY_PAUSE */	return "VK_MEDIA_PLAY_PAUSE";
			case 0xB4: /* VK_LAUNCH_MAIL */			return "VK_LAUNCH_MAIL";
			case 0xB5: /* VK_LAUNCH_MEDIA_SELECT */	return "VK_LAUNCH_MEDIA_SELECT";
			case 0xB6: /* VK_LAUNCH_APP1 */			return "VK_LAUNCH_APP1";
			case 0xB7: /* VK_LAUNCH_APP2 */			return "VK_LAUNCH_APP2";
			case 0xB8: /* Reserved */				null;
			case 0xB9: /* Reserved */				null;
			case 0xBA: /* VK_OEM_1 */					return "SEMICOLON";
			case 0xBB: /* VK_OEM_PLUS */				return "EQUALS";
			case 0xBC: /* VK_OEM_COMMA */				return "COMMA";
			case 0xBD: /* VK_OEM_MINUS */				return "MINUS";
			case 0xBE: /* VK_OEM_PERIOD */				return "PERIOD";
			case 0xBF: /* VK_OEM_2 */					return "SLASH";
			case 0xC0: /* VK_OEM_3 */					return "BACK_QUOTE";
			case 0xC1: /* Reserved */				null;
			case 0xC2: /* Reserved */				null;
			case 0xC3: /* Reserved */				null;
			case 0xC4: /* Reserved */				null;
			case 0xC5: /* Reserved */				null;
			case 0xC6: /* Reserved */				null;
			case 0xC7: /* Reserved */				null;
			case 0xC8: /* Reserved */				null;
			case 0xC9: /* Reserved */				null;
			case 0xCA: /* Reserved */				null;
			case 0xCB: /* Reserved */				null;
			case 0xCC: /* Reserved */				null;
			case 0xCD: /* Reserved */				null;
			case 0xCE: /* Reserved */				null;
			case 0xCF: /* Reserved */				null;
			case 0xD0: /* Reserved */				null;
			case 0xD1: /* Reserved */				null;
			case 0xD2: /* Reserved */				null;
			case 0xD3: /* Reserved */				null;
			case 0xD4: /* Reserved */				null;
			case 0xD5: /* Reserved */				null;
			case 0xD6: /* Reserved */				null;
			case 0xD7: /* Reserved */				null;
			case 0xD8: /* Unassigned */				null;
			case 0xD9: /* Unassigned */				null;
			case 0xDA: /* Unassigned */				null;
			case 0xDB: /* VK_OEM_4 */					return "BRACKET_OPEN";
			case 0xDC: /* VK_OEM_5 */					return "BACKSLASH";
			case 0xDD: /* VK_OEM_6 */					return "BRACKET_CLOSE";
			case 0xDE: /* VK_OEM_7 */					return "APOSTROPHE";
			case 0xDF: /* VK_OEM_8 */				return "VK_OEM_8";
			case 0xE0: /* Reserved */				null;
			case 0xE1: /* OEM specific */			null;
			case 0xE2: /* OEM VK_OEM_102 */			return "VK_OEM_102";
			case 0xE3: /* OEM specific */			null;
			case 0xE4: /* OEM specific */			null;
			case 0xE5: /* VK_PROCESSKEY */			return "VK_PROCESSKEY";
			case 0xE6: /* OEM specific */			null;
			case 0xE7: /* VK_PACKET */				return "VK_PACKET";
			case 0xE8: /* Unassigned */				null;
			case 0xE9: /* OEM specific */			null;
			case 0xEA: /* OEM specific */			null;
			case 0xEB: /* OEM specific */			null;
			case 0xEC: /* OEM specific */			null;
			case 0xED: /* OEM specific */			null;
			case 0xEE: /* OEM specific */			null;
			case 0xEF: /* OEM specific */			null;
			case 0xF0: /* OEM specific */			null;
			case 0xF1: /* OEM specific */			null;
			case 0xF2: /* OEM specific */			null;
			case 0xF3: /* OEM specific */			null;
			case 0xF4: /* OEM specific */			null;
			case 0xF5: /* OEM specific */			null;
			case 0xF6: /* VK_ATTN */				return "VK_ATTN";
			case 0xF7: /* VK_CRSEL */				return "VK_CRSEL";
			case 0xF8: /* VK_EXSEL */				return "VK_EXSEL";
			case 0xF9: /* VK_EREOF */				return "VK_EREOF";
			case 0xFA: /* VK_PLAY */				return "VK_PLAY";
			case 0xFB: /* VK_ZOOM */				return "VK_ZOOM";
			case 0xFC: /* VK_NONAME */				return "VK_NONAME";
			case 0xFD: /* VK_PA1 */					return "VK_PA1";
			case 0xFE: /* VK_PLAY */				return "VK_PLAY";
			case 0xFF: /* ? */						null;
			default:								null;
		}
		#undef null
	}
}
