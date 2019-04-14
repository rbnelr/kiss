// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

//// forward declarations
union iv2;
union iv4;
union bv3;
union fv3;
union dv3;

union iv3 {
	struct {
		int	x, y, z;
	};
	int		arr[3];
	
	int& operator[] (int i);
	int operator[] (int i) const;
	
	iv3 ();
	// sets all components to one value
	constexpr iv3 (int all);
	// supply all components
	constexpr iv3 (int x, int y, int z);
	// extend vector
	constexpr iv3 (iv2 xy, int z);
	// truncate vector
	constexpr iv3 (iv4 v);
	
	iv3 operator+= (iv3 r);
	iv3 operator-= (iv3 r);
	iv3 operator*= (iv3 r);
	iv3 operator/= (iv3 r);
	
	//// Conversion operators
	operator fv3 () const;
	operator dv3 () const;
};

//// arthmethic ops
constexpr iv3 operator+ (iv3 v);
constexpr iv3 operator- (iv3 v);
constexpr iv3 operator+ (iv3 l, iv3 r);
constexpr iv3 operator- (iv3 l, iv3 r);
constexpr iv3 operator* (iv3 l, iv3 r);
constexpr iv3 operator/ (iv3 l, iv3 r);

//// comparison ops
constexpr bv3 operator< (iv3 l, iv3 r);
constexpr bv3 operator<= (iv3 l, iv3 r);
constexpr bv3 operator> (iv3 l, iv3 r);
constexpr bv3 operator>= (iv3 l, iv3 r);
constexpr bv3 operator== (iv3 l, iv3 r);
constexpr bv3 operator!= (iv3 l, iv3 r);
// vectors are equal, equivalent to all(l == r)
constexpr bool equal (iv3 l, iv3 r);
// componentwise ternary c ? l : r
constexpr iv3 select (iv3 c, iv3 l, iv3 r);

//// misc ops
iv3 abs (iv3 v);
iv3 min (iv3 l, iv3 r);
iv3 max (iv3 l, iv3 r);
iv3 clamp (iv3 x, iv3 a=iv3(0), iv3 b=iv3(1));
// get min component of vector, optionally get component index via min_index
int min_component (iv3 v, int* min_index=nullptr);
// get max component of vector, optionally get component index via max_index
int max_component (iv3 v, int* max_index=nullptr);

iv3 wrap (iv3 v, iv3 range);
iv3 wrap (iv3 v, iv3 a, iv3 b);

//// linear algebra ops
// magnitude of vector
f32 length (iv3 v);
// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
int length_sqr (iv3 v);
// distance between points, equivalent to length(a - b)
f32 distance (iv3 a, iv3 b);
// normalize vector so that it has length() = 1, undefined for zero vector
fv3 normalize (iv3 v);
// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
fv3 normalize_or_zero (iv3 v);


