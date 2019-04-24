#pragma once

///////////////////
#include <typeinfo>
#include <typeindex>
#include <type_traits>
#include "string.h"
#include "assert.h"

template <typename T, typename DECAYED_T>
struct fix_cstr { typedef T type; };

template<typename T>
struct fix_cstr<T, char*> { typedef char const* type; };

struct Any {
	std::type_index		id;
	char				value[16];

	template <typename T>
	Any (T const& x): id{std::type_index(typeid( fix_cstr<T, std::decay<T>::type>::type ))} {
		this->set< fix_cstr<T, std::decay<T>::type>::type >(x);
	}

	template <typename T>
	void set (T const& x) {
		if (sizeof(T) <= sizeof(value)) {
			memcpy(value, &x, sizeof(T)); // store value directly in value if it fits
		} else {
			T const* ptr = &x;
			memcpy(value, &ptr, sizeof(ptr)); // or store pointer to it 
		}
	}

	template <typename T>
	T const& get () const { // returns reference to either value of this Any or reference to value stored wherever this Any was created from
		assert(id == std::type_index(typeid(T)));

		T* ptr;
		if (sizeof(T) <= sizeof(value)) {
			ptr = (T*)value;
		} else {
			memcpy(ptr, value, sizeof(ptr));
		}
		return *ptr;
	}
};

////////////////////
#include <string>

#include "stdarg.h"
namespace replace_me {
	typedef char const* cstr;
	// Printf that outputs to a std::string
	inline void vprints (std::string* s, cstr format, va_list vl) { // print 
		size_t old_size = s->size();
		for (;;) {
			auto ret = vsnprintf(&(*s)[old_size], s->size() -old_size +1, format, vl); // i think i'm technically not allowed to overwrite the null terminator
			ret = ret > 0 ? ret : 0;
			bool was_big_enough = (int)ret < (s->size() -old_size +1);
			s->resize(old_size +(int)ret);
			if (was_big_enough) break;
			// buffer was too small, buffer size was increased
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
}
using namespace replace_me;

std::string format (char const* frmt, int args_count, Any const args[]);

std::string format (char const* str);
std::string format (char const* frmt, Any a1);
std::string format (char const* frmt, Any a1, Any a2);
std::string format (char const* frmt, Any a1, Any a2, Any a3);

void print (char const* str);
void print (char const* frmt, Any a1);
void print (char const* frmt, Any a1, Any a2);
void print (char const* frmt, Any a1, Any a2, Any a3);

#include <unordered_map>

typedef std::string (*to_string_fp)(Any const& x);

template <typename T>
inline std::string to_string (T s);

template<> inline std::string to_string<char const*> (char const* s) {
	return s;
}
template<> inline std::string to_string<int> (int i) {
	return prints("%d", i);
}
template<> inline std::string to_string<float> (float f) {
	return prints("%f", f);
}

template <typename T>
inline std::string T_to_string (Any const& x) {
	return to_string(x.get<T>());
}

extern std::unordered_map<std::type_index, to_string_fp> registered_to_string_funcs;

template <typename T>
inline void register_to_string () {
	registered_to_string_funcs.emplace( std::type_index(typeid(T)), T_to_string<T> );
}

template <typename T>
inline int _register_to_string_dummy_var () {
	register_to_string<T>();
	return 0;
}

#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

#define CONCAT(a,b) a##b

#define _REGISTER_TO_STRING(T, VARNAME) auto VARNAME = _register_to_string_dummy_var<T>();
#define REGISTER_TO_STRING(T) _REGISTER_TO_STRING(T, CONCAT(_register_to_string_dummy_var_, T))

