#pragma once

#include "vector/vector.hpp"

extern "C" __declspec(dllexport) const iv2 default_pos;
extern "C" __declspec(dllexport) const iv2 default_size;

extern "C" __declspec(dllexport) void open_window (char const* caption, iv2 initial_size=default_size, iv2 initial_pos=default_pos);
extern "C" __declspec(dllexport) void close_window ();
extern "C" __declspec(dllexport) void swap_buffers ();
