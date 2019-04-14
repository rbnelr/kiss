// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

//// forward declarations
union s64v3;
union s64v4;
union bv2;
union fv2;
union dv2;

union s64v2 {
	struct {
		s64	x, y;
	};
	s64		arr[2];
	
	s64& operator[] (int i);
	s64 operator[] (int i) const;
	
	s64v2 ();
	// sets all components to one value
	constexpr s64v2 (s64 all);
	// supply all components
	constexpr s64v2 (s64 x, s64 y);
	// truncate vector
	constexpr s64v2 (s64v3 v);
	// truncate vector
	constexpr s64v2 (s64v4 v);
	
	s64v2 operator+= (s64v2 r);
	s64v2 operator-= (s64v2 r);
	s64v2 operator*= (s64v2 r);
	s64v2 operator/= (s64v2 r);
	
	//// Conversion operators
	operator fv2 () const;
	operator dv2 () const;
};

//// arthmethic ops
constexpr s64v2 operator+ (s64v2 v);
constexpr s64v2 operator- (s64v2 v);
constexpr s64v2 operator+ (s64v2 l, s64v2 r);
constexpr s64v2 operator- (s64v2 l, s64v2 r);
constexpr s64v2 operator* (s64v2 l, s64v2 r);
constexpr s64v2 operator/ (s64v2 l, s64v2 r);

//// comparison ops
constexpr bv2 operator< (s64v2 l, s64v2 r);
constexpr bv2 operator<= (s64v2 l, s64v2 r);
constexpr bv2 operator> (s64v2 l, s64v2 r);
constexpr bv2 operator>= (s64v2 l, s64v2 r);
constexpr bv2 operator== (s64v2 l, s64v2 r);
constexpr bv2 operator!= (s64v2 l, s64v2 r);
// vectors are equal, equivalent to all(l == r)
constexpr bool equal (s64v2 l, s64v2 r);
// componentwise ternary c ? l : r
constexpr s64v2 select (s64v2 c, s64v2 l, s64v2 r);

//// misc ops
s64v2 abs (s64v2 v);
s64v2 min (s64v2 l, s64v2 r);
s64v2 max (s64v2 l, s64v2 r);
s64v2 clamp (s64v2 x, s64v2 a=s64v2(0), s64v2 b=s64v2(1));
// get min component of vector, optionally get component index via min_index
s64 min_component (s64v2 v, int* min_index=nullptr);
// get max component of vector, optionally get component index via max_index
s64 max_component (s64v2 v, int* max_index=nullptr);

s64v2 wrap (s64v2 v, s64v2 range);
s64v2 wrap (s64v2 v, s64v2 a, s64v2 b);

//// linear algebra ops
// magnitude of vector
f64 length (s64v2 v);
// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
s64 length_sqr (s64v2 v);
// distance between points, equivalent to length(a - b)
f64 distance (s64v2 a, s64v2 b);
// normalize vector so that it has length() = 1, undefined for zero vector
dv2 normalize (s64v2 v);
// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
dv2 normalize_or_zero (s64v2 v);


