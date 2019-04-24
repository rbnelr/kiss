#include "string/string.hpp"

#include "vector/vector.hpp"

template<> inline std::string to_string<v3> (v3 v) {
	return prints("v3(%f, %f, %f)", v.x, v.y, v.z);
}
//REGISTER_TO_STRING(v3)

int main () {
	
	print("Hello World!\n");
	print("Hello World %!\n", 5);
	print("% bottles of %!\n", 99, "beer");
	print("the %th element of % is %\n", 1, v3(1,2,3), v3(1,2,3)[1]);

	return 0;
}
