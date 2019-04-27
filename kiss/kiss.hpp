#pragma once

#include "vector/vector.hpp"

#include "input.hpp"
#include "window.hpp"

// Include gl interface without including windows.h
#ifdef _WIN32
#define APIENTRY __stdcall
#endif

#include "glad/glad.h"
