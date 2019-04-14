// bv3.hpp generated by vector_srcgen.py
#pragma once

#include "kissmath.hpp"

union bv3 {
	struct {
		bool	x, y, z;
	};
	bool		arr[3];

	inline bool& operator[] (int i) {
		return arr[i];
	}

	inline  bv3 () {
	
	}

	inline constexpr bv3 (bool all): x{all}, y{all}, z{all} {
	
	}

	inline constexpr bv3 (bool x, bool y, bool z): x{x}, y{y}, z{z} {
	
	}
