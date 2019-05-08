#pragma once

#if defined(_WIN32) && !defined(APIENTRY)
	#pragma push_macro("APIENTRY")

	// don't include windows.h
	#define APIENTRY __stdcall

	#include "glad/glad.h"
	
	#pragma pop_macro("APIENTRY")
#else
	#include "glad/glad.h"
#endif

