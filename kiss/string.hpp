#pragma once
#include "stdarg.h"
#include "assert.h"
#include <string>

#define ANSI_COLOUR_CODE_RED	"\033[1;31m"
#define ANSI_COLOUR_CODE_YELLOW	"\033[1;33m"
#define ANSI_COLOUR_CODE_NC		"\033[0m"

namespace kiss {

	template <typename T>
	struct basic_string_view {
		T const*	begin;
		T const*	end;

		/*constexpr*/ T const* c_str () const { return begin; } // constexpr caused a internal compiler error in MSVC17 at some point
		/*constexpr*/ size_t size () const { return end -begin; }

		constexpr basic_string_view (std::basic_string<T> const& s): begin{s.data()}, end{s.data() + s.size()} {}
		constexpr basic_string_view (char const* s): begin{s}, end{s + strlen(s)} {}

		explicit operator std::basic_string<T> () { return std::basic_string<T>(begin, size()); }
	};

	using string_view = basic_string_view<char>;

	typedef char const* cstr;

	// Printf that outputs to a std::string
	inline void vprints (std::string* s, cstr format, va_list vl) { // print 
		size_t old_size = s->size();
		for (;;) {
			auto ret = vsnprintf(&(*s)[old_size], s->size() -old_size +1, format, vl); // i think i'm technically not allowed to overwrite the null terminator
			ret = ret >= 0 ? ret : 0;
			bool was_bienough = (size_t)ret < (s->size() -old_size +1);
			s->resize(old_size +ret);
			if (was_bienough) break;
			// buffer was to small, buffer size was increased
			// now snprintf has to succeed, so call it again
		}
	}
	inline void prints (std::string* s, cstr format, ...) {
		va_list vl;
		va_start(vl, format);

		vprints(s, format, vl);

		va_end(vl);
	}
	inline std::string prints (cstr format, ...) {
		va_list vl;
		va_start(vl, format);

		std::string ret;
		vprints(&ret, format, vl);

		va_end(vl);

		return ret;
	}

	inline bool is_lower (char c) {
		return c >= 'a' && c <= 'z';
	}
	inline bool is_upper (char c) {
		return c >= 'A' && c <= 'Z';
	}

	inline char to_lower (char c) {
		return is_upper(c) ? c +('a' -'A') : c;
	}
	inline char to_upper (char c) {
		return is_lower(c) ? c +('A' -'a') : c;
	}

	std::basic_string<wchar_t> utf8_to_wchar (string_view utf8);
	std::string wchar_to_utf8 (basic_string_view<wchar_t> wchar);
}
