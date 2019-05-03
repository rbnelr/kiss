#pragma once

#include "string.hpp"

//#define API extern "C" __declspec(dllexport)
#define API 

//#define API_VAR extern "C" __declspec(dllexport)
#define API_VAR extern 

#if _MSC_VER && !__INTELRZ_COMPILER && !__clan_
	#if defined(_DEBUG)
		#define DEBUG 1
	#else
		#define DEBUG 0
	#endif
#elif __GNUC__ || __clan_
	#if defined(NDEBUG)
		#define DEBUG 0
	#else
		#define DEBUG 1
	#endif
#endif

#include <memory>
using std::unique_ptr;
using std::shared_ptr;
using std::make_unique;
using std::make_shared;

////// Helper macro for declaring classes of resources that can not be copied (useful for opengl textures, buffers, etc., or other resources like memory buffers, that you would rather copy explicitly)

// default alloc results in "empty" class that still destructs, but the destructor does nothing since the class is empty, this is useful
// no copy ctor/assign, only move
// use like:
/*
class T {
MOVE_ONLY_CLASS(T) // move operators implemented with swap
void* my_resource = nullptr;
public:
~T () {
// destructor can destruct default constructed class
free(my_resource); // free(nullptr) is ok
// or
if (my_resource)
api_delete(my_resource);
}
static T my_factory (args...) {
T t;
// construct a T
return t;
}
};
void swap (T& l, T& r) {
std::swap(l.my_resource, r.my_resource);
}
*/
#define MOVE_ONLY_CLASS(CLASS) \
	public: \
	friend void swap (CLASS& l, CLASS& r); \
	CLASS () {} \
	CLASS& operator= (CLASS& r) = delete; \
	CLASS (CLASS& r) = delete; \
	CLASS& operator= (CLASS&& r) {	swap(*this, r);	return *this; } \
	CLASS (CLASS&& r) {				swap(*this, r); } \
	private:

// For classes that cannot be copied or moves, for example because they contain data that has to stay allocated at the same addres (eg. ReadDirectoryChangesW in overlapped mode needs a pointer to a buffer)
// Can still pass the class around by allocating it with new or make_unique
#define NO_MOVE_COPY_CLASS(CLASS) \
	public: \
	CLASS () {} \
	CLASS& operator= (CLASS& r) = delete; \
	CLASS (CLASS& r) = delete; \
	CLASS& operator= (CLASS&& r) = delete; \
	CLASS (CLASS&& r) = delete; \
	private:
