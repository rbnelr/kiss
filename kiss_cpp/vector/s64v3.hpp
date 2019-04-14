// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

//// forward declarations
union s64v2;
union s64v4;
union bv3;
union fv3;
union dv3;

union s64v3 {
	struct {
		s64	x, y, z;
	};
	s64		arr[3];
	
	s64& operator[] (int i);
	s64 operator[] (int i) const;
	
	s64v3 ();
	// sets all components to one value
	constexpr s64v3 (s64 all);
	// supply all components
	constexpr s64v3 (s64 x, s64 y, s64 z);
	// extend vector
	constexpr s64v3 (s64v2 xy, s64 z);
	// truncate vector
	constexpr s64v3 (s64v4 v);
	
	s64v3 operator+= (s64v3 r);
	s64v3 operator-= (s64v3 r);
	s64v3 operator*= (s64v3 r);
	s64v3 operator/= (s64v3 r);
	
	//// Conversion operators
	operator fv3 () const;
	operator dv3 () const;
};

//// arthmethic ops
constexpr s64v3 operator+ (s64v3 v);
constexpr s64v3 operator- (s64v3 v);
constexpr s64v3 operator+ (s64v3 l, s64v3 r);
constexpr s64v3 operator- (s64v3 l, s64v3 r);
constexpr s64v3 operator* (s64v3 l, s64v3 r);
constexpr s64v3 operator/ (s64v3 l, s64v3 r);

//// comparison ops
constexpr bv3 operator< (s64v3 l, s64v3 r);
constexpr bv3 operator<= (s64v3 l, s64v3 r);
constexpr bv3 operator> (s64v3 l, s64v3 r);
constexpr bv3 operator>= (s64v3 l, s64v3 r);
constexpr bv3 operator== (s64v3 l, s64v3 r);
constexpr bv3 operator!= (s64v3 l, s64v3 r);
// vectors are equal, equivalent to all(l == r)
constexpr bool equal (s64v3 l, s64v3 r);
// componentwise ternary c ? l : r
constexpr s64v3 select (s64v3 c, s64v3 l, s64v3 r);

//// misc ops
s64v3 abs (s64v3 v);
s64v3 min (s64v3 l, s64v3 r);
s64v3 max (s64v3 l, s64v3 r);
s64v3 clamp (s64v3 x, s64v3 a=s64v3(0), s64v3 b=s64v3(1));
// get min component of vector, optionally get component index via min_index
s64 min_component (s64v3 v, int* min_index=nullptr);
// get max component of vector, optionally get component index via max_index
s64 max_component (s64v3 v, int* max_index=nullptr);

s64v3 wrap (s64v3 v, s64v3 range);
s64v3 wrap (s64v3 v, s64v3 a, s64v3 b);

//// linear algebra ops
// magnitude of vector
f64 length (s64v3 v);
// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
s64 length_sqr (s64v3 v);
// distance between points, equivalent to length(a - b)
f64 distance (s64v3 a, s64v3 b);
// normalize vector so that it has length() = 1, undefined for zero vector
dv3 normalize (s64v3 v);
// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
dv3 normalize_or_zero (s64v3 v);


