// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

//// forward declarations
union bv2;
union bv3;
union bv4;

union bv4 {
	struct {
		bool	x, y, z, w;
	};
	bool		arr[4];
	
	bool& operator[] (int i);
	bool operator[] (int i) const;
	
	bv4 ();
	// sets all components to one value
	constexpr bv4 (bool all);
	// supply all components
	constexpr bv4 (bool x, bool y, bool z, bool w);
	// extend vector
	constexpr bv4 (bv2 xy, bool z, bool w);
	// extend vector
	constexpr bv4 (bv3 xyz, bool w);
	
};

//// reducing ops
// all components are true
constexpr bool all (bv4 v);
// any components is true
constexpr bool any (bv4 v);

//// arthmethic ops
constexpr bv4 operator! (bv4 v);
constexpr bv4 operator&& (bv4 l, bv4 r);
constexpr bv4 operator|| (bv4 l, bv4 r);

//// comparison ops
constexpr bv4 operator== (bv4 l, bv4 r);
constexpr bv4 operator!= (bv4 l, bv4 r);
// vectors are equal, equivalent to all(l == r)
constexpr bool equal (bv4 l, bv4 r);
// componentwise ternary c ? l : r
constexpr bv4 select (bv4 c, bv4 l, bv4 r);

