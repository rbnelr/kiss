#pragma once

// don't include windows.h
#ifdef _WIN32
	#define APIENTRY __stdcall
#endif

#include "glad/glad.h"
