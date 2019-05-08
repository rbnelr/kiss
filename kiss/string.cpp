#include "string.hpp"
#include "clean_windows_h.hpp"

namespace kiss {
	std::basic_string<wchar_t> utf8_to_wchar (string_view utf8) {

		// overallocate, this might be more performant than having to process the utf8 twice
		std::basic_string<wchar_t> wstr (utf8.size() +1, '\0'); // wchar string can never be longer than number of utf8 bytes, right?

		auto res = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8.c_str(), -1, &wstr[0], (int)wstr.size());
		assert(res > 0 && res <= wstr.size());

		wstr.resize(res -1);

		return wstr;
	}
	std::string wchar_to_utf8 (basic_string_view<wchar_t> wchar) {

		// overallocate, this might be more performant than having to process the wchar twice
		std::string utf8 (wchar.size() * 4 +1, '\0'); // utf8 string can never be longer than 4x the number of wchars, right?

													  // WC_NO_BEST_FIT_CHARS sometimes throws erros ?
		auto res = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wchar.c_str(), -1, &utf8[0], (int)utf8.size(), NULL, NULL);
		assert(res > 0 && res <= utf8.size());

		utf8.resize(res -1);

		return utf8;
	}
}
