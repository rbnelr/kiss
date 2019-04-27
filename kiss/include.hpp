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
