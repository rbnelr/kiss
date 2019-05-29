#pragma once
#include "vector/vector.hpp"
#include <unordered_map>
#include <string>

namespace kiss {
	/*
		Platform independent button names:



		LMB
		MMB
		RMB
		MB4
		MB5

		A-Z				= 'A'-'Z' and 'a'-'z'
		0-9				= '0'-'9'

		NP0-NP9

		BACK_QUOTE		= '`'
		TABULATOR		= '\t'
		SPACE			= ' '
		BACKSLASH		= '\\'

		MINUS			= '-'
		EQUALS			= '='

		BRACKET_OPEN	= '['
		BRACKET_CLOSE	= ']'
		SEMICOLON		= ';'
		APOSTROPHE		= '\''
		COMMA			= ','
		PERIOD			= '.'
		SLASH			= '/'

		ESCAPE

		F1-F24

		CAPSLOCK
		LSHIFT
		RSHIFT
		LCTRL
		RCTRL
		LLOGO
		RLOGO
		LALT
		RALT
		APP
		ENTER
		BACKSPACE

		PRINT_SCREEN
		SCROLL_LOCK
		PAUSE
		
		INSERT
		DELETE
		HOME
		END
		PAGE_UP
		PAGE_DOWN

		RIGHT
		UP
		LEFT
		DOWN

		NUMLOCK
		NP_DIVIDE
		NP_MULTIPLY
		NP_MINUS
		NP_PLUS
		NP_ENTER
		NP_DECIMAL
	*/
	inline char const* map_button_shorthand (char c) {
		static constexpr char const* alpha[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z" };
		static constexpr char const* nums[] = { "0","1","2","3","4","5","6","7","8","9" };
		if (c >= 'A' && c <= 'Z')
			return alpha[c -'A'];
		else if (c >= 'a' && c <= 'z')
			return alpha[c -'a'];
		if (c >= '0' && c <= '9')
			return nums[c -'0'];

		switch (c) {
			case '\t':	return "TABULATOR"; 
			case ' ':	return "SPACE"; 
			case '\\':	return "BACKSLASH"; 
			
			case '-':	return "MINUS"; 
			case '=':	return "EQUALS"; 
			
			case '[':	return "BRACKET_OPEN"; 
			case ']':	return "BRACKET_CLOSE"; 
			case ';':	return "SEMICOLON"; 
			case '\'':	return "APOSTROPHE"; 
			case ',':	return "COMMA"; 
			case '.':	return "PERIOD"; 
			case '/':	return "SLASH"; 
		}

		return nullptr;
	}

	struct Button_Input {
		bool is_down	: 1;
		bool went_down	: 1;
		bool went_up	: 1;
	};
	struct Input {
		bool	close = false;
		iv2		window_size = 0;
		iv2		_os_mouse_pos = 0;
		iv2		mouse_delta = 0;

		std::unordered_map<std::string, Button_Input> buttons;

		// get mouse position (bottom up)
		inline iv2 get_mouse_pos () {
			iv2 pos = _os_mouse_pos;
			pos.y = window_size.y - pos.y - 1;
			return pos;
		}
		inline v2 get_mouse_pos_pixel_center () {
			iv2 posi = get_mouse_pos();
			return (v2)posi + 0.5f;
		}
		inline v2 get_mouse_pos_uv () {
			v2 pos = get_mouse_pos_pixel_center();
			return pos / (v2)window_size;
		}

		inline Button_Input& get_create_button (std::string const& button) {
			return buttons.insert({ button, Button_Input{ false, false, false } }).first->second;
		}

		inline Button_Input get_button (std::string const& button) {
			auto it = buttons.find(button);
			if (it != buttons.end())
				return it->second;
			else	
				return { false, false, false };
		}
		inline Button_Input get_button (char button_shorthand) {
			auto button = map_button_shorthand(button_shorthand);
			if (button)
				return get_button(button);
			else
				return { false, false, false };
		}

		inline bool is_down (std::string const& button) {
			return get_button(button).is_down;
		}
		inline bool went_down (std::string const& button) {
			return get_button(button).went_down;
		}
		inline bool went_up (std::string const& button) {
			return get_button(button).went_up;
		}

		inline bool is_down (char button) {
			return get_button(button).is_down;
		}
		inline bool went_down (char button) {
			return get_button(button).went_down;
		}
		inline bool went_up (char button) {
			return get_button(button).went_up;
		}

		// clear input that is frame-by-frame like mouse deltas or the close flag
		inline void clear () {
			close = false;
			mouse_delta = 0;
			for (auto& it : buttons) {
				it.second.went_down = false;
				it.second.went_up = false;
			}
		}
	};
}
