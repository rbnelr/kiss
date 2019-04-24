#include "string.hpp"

#include "stdio.h"

std::string format (char const* str) {
	return str;
}
std::string format (char const* frmt, Any a1) {
	return format(frmt, 1, &a1);
}
std::string format (char const* frmt, Any a1, Any a2) {
	Any args[] = { a1, a2 };
	return format(frmt, 2, args);
}
std::string format (char const* frmt, Any a1, Any a2, Any a3) {
	Any args[] = { a1, a2, a3 };
	return format(frmt, 3, args);
}

void print (char const* str) {
	fputs(str, stdout);
}
void print (char const* frmt, Any a1) {
	print(format(frmt, 1, &a1).c_str());
}
void print (char const* frmt, Any a1, Any a2) {
	Any args[] = { a1, a2 };
	print(format(frmt, 2, args).c_str());
}
void print (char const* frmt, Any a1, Any a2, Any a3) {
	Any args[] = { a1, a2, a3 };
	print(format(frmt, 3, args).c_str());
}

std::unordered_map<std::type_index, to_string_fp> registered_to_string_funcs = {
	{ std::type_index(typeid(char const*)),	T_to_string<char const*> },
	{ std::type_index(typeid(int)),			T_to_string<int> },
	{ std::type_index(typeid(float)),		T_to_string<float> },
};

std::string any_to_string (Any const& any) {

	auto res = registered_to_string_funcs.find(any.id);
	if (res == registered_to_string_funcs.end()) { // Type in any not registed in registered_to_string_funcs
		auto name = any.id.name();
		return prints("<%s>", name);
	}

	auto func = res->second;
	return func(any);
}

std::string format (char const* frmt, int args_count, Any const args[]) {

	std::string buf;

	char const* cur = frmt;
	int argi = 0;

	while (*cur) {
		if (*cur == '%') {
			cur++;
			buf += any_to_string(args[argi++]);
		} else {
			buf.push_back(*cur++);
		}
	}

	return buf;
}

