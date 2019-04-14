// u8v3.hpp generated by vector_srcgen.py
#pragma once

#include "kissmath.hpp"

// forward declarations for conversion operators
union fv3;
union dv3;

union u8v3 {
	struct {
		u8	x, y, z;
	};
	u8		arr[3];

	inline u8& operator[] (int i) {
		return arr[i];
	}

	inline u8v3 () {
	
	}

	inline constexpr u8v3 (u8 all): x{all}, y{all}, z{all} {
	
	}

	inline constexpr u8v3 (u8 x, u8 y, u8 z): x{x}, y{y}, z{z} {
	
	}

	inline u8v3 operator+= (u8v3 r) {
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}
	inline u8v3 operator-= (u8v3 r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	inline u8v3 operator*= (u8v3 r) {
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	inline u8v3 operator/= (u8v3 r) {
		x /= r.x;
		y /= r.y;
		z /= r.z;
		return *this;
	}

	operator fv3 ();
	operator dv3 ();
};

