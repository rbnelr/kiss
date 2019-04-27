#pragma once
#include "include.hpp"

#include "vector/vector.hpp"

namespace kiss {
	API_VAR const iv2 default_pos;
	API_VAR const iv2 default_size;

	API void open_window (char const* caption, iv2 initial_size=default_size, iv2 initial_pos=default_pos);
	API void close_window ();
	API void swap_buffers ();
}
