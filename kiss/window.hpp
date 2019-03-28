#pragma once

#define WIN32_LEAN_AND_MEAN 1
#include "windows.h"

#include "vectors.hpp"

static constexpr iv2 default_pos = CW_USEDEFAULT;
static constexpr iv2 default_size = CW_USEDEFAULT;

extern "C" __declspec(dllexport) void open_window (wchar_t const* caption, iv2 initial_size=default_size, iv2 initial_pos=default_pos);
extern "C" __declspec(dllexport) void close_window ();
extern "C" __declspec(dllexport) void swap_buffers ();
