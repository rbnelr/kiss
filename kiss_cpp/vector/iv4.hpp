// iv4.hpp generated by vector_srcgen.py
#pragma once

#include "kissmath.hpp"

// forward declarations for conversion operators
union fv4;
union dv4;

union iv4 {
	struct {
		int	x, y, z, w;
	};
	int		arr[4];

	inline int& operator[] (int i) {
		return arr[i];
	}

	inline iv4 () {
	
	}

	inline constexpr iv4 (int all): x{all}, y{all}, z{all}, w{all} {
	
	}

	inline constexpr iv4 (int x, int y, int z, int w): x{x}, y{y}, z{z}, w{w} {
	
	}

	inline iv4 operator+= (iv4 r) {
		x += r.x;
		y += r.y;
		z += r.z;
		w += r.w;
		return *this;
	}
	inline iv4 operator-= (iv4 r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;
		w -= r.w;
		return *this;
	}
	inline iv4 operator*= (iv4 r) {
		x *= r.x;
		y *= r.y;
		z *= r.z;
		w *= r.w;
		return *this;
	}
	inline iv4 operator/= (iv4 r) {
		x /= r.x;
		y /= r.y;
		z /= r.z;
		w /= r.w;
		return *this;
	}

	operator fv4 ();
	operator dv4 ();
};

