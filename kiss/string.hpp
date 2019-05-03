#pragma once

typedef char const*			cstr;
typedef char				utf8;
typedef char32_t			utf32;

#include <string>
#include "stdarg.h"

// Printf that outputs to a std::string
inline void vprints (std::string* s, cstr format, va_list vl) { // print 
	size_t old_size = s->size();
	for (;;) {
		auto ret = vsnprintf(&(*s)[old_size], s->size() -old_size +1, format, vl); // i think i'm technically not allowed to overwrite the null terminator
		ret = ret >= 0 ? ret : 0;
		bool was_bienough = (size_t)ret < (s->size() -old_size +1);
		s->resize(old_size +(size_t)ret);
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
