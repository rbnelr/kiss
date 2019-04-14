// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

//// forward declarations
union dv2;
union dv3;
union bv4;
union iv4;
union s64v4;
union u8v4;

union dv4 {
	struct {
		f64	x, y, z, w;
	};
	f64		arr[4];
	
	f64& operator[] (int i);
	f64 operator[] (int i) const;
	
	dv4 ();
	// sets all components to one value
	constexpr dv4 (f64 all);
	// supply all components
	constexpr dv4 (f64 x, f64 y, f64 z, f64 w);
	// extend vector
	constexpr dv4 (dv2 xy, f64 z, f64 w);
	// extend vector
	constexpr dv4 (dv3 xyz, f64 w);
	
	dv4 operator+= (dv4 r);
	dv4 operator-= (dv4 r);
	dv4 operator*= (dv4 r);
	dv4 operator/= (dv4 r);
	
	//// Conversion operators
	operator iv4 () const;
	operator s64v4 () const;
	operator u8v4 () const;
};

//// arthmethic ops
constexpr dv4 operator+ (dv4 v);
constexpr dv4 operator- (dv4 v);
constexpr dv4 operator+ (dv4 l, dv4 r);
constexpr dv4 operator- (dv4 l, dv4 r);
constexpr dv4 operator* (dv4 l, dv4 r);
constexpr dv4 operator/ (dv4 l, dv4 r);

//// comparison ops
constexpr bv4 operator< (dv4 l, dv4 r);
constexpr bv4 operator<= (dv4 l, dv4 r);
constexpr bv4 operator> (dv4 l, dv4 r);
constexpr bv4 operator>= (dv4 l, dv4 r);
constexpr bv4 operator== (dv4 l, dv4 r);
constexpr bv4 operator!= (dv4 l, dv4 r);
// vectors are equal, equivalent to all(l == r)
constexpr bool equal (dv4 l, dv4 r);
// componentwise ternary c ? l : r
constexpr dv4 select (dv4 c, dv4 l, dv4 r);

//// misc ops
dv4 abs (dv4 v);
dv4 min (dv4 l, dv4 r);
dv4 max (dv4 l, dv4 r);
dv4 clamp (dv4 x, dv4 a=dv4(0), dv4 b=dv4(1));
// get min component of vector, optionally get component index via min_index
f64 min_component (dv4 v, int* min_index=nullptr);
// get max component of vector, optionally get component index via max_index
f64 max_component (dv4 v, int* max_index=nullptr);

dv4 floor (dv4 v);
dv4 ceil (dv4 v);
dv4 round (dv4 v);
s64v4 floori (dv4 v);
s64v4 ceili (dv4 v);
s64v4 roundi (dv4 v);
dv4 pow (dv4 v, dv4 e);
dv4 wrap (dv4 v, dv4 range);
dv4 wrap (dv4 v, dv4 a, dv4 b);

//// linear algebra ops
// magnitude of vector
f64 length (dv4 v);
// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
f64 length_sqr (dv4 v);
// distance between points, equivalent to length(a - b)
f64 distance (dv4 a, dv4 b);
// normalize vector so that it has length() = 1, undefined for zero vector
dv4 normalize (dv4 v);
// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
dv4 normalize_or_zero (dv4 v);

// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
dv4 lerp (dv4 a, dv4 b, dv4 t);
// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
dv4 map (dv4 x, dv4 in_a, dv4 in_b);
// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
dv4 map (dv4 x, dv4 in_a, dv4 in_b, dv4 out_a, dv4 out_b);
dv4 smoothstep (dv4 x);
dv4 bezier (dv4 a, dv4 b, dv4 c, f64 t);
dv4 bezier (dv4 a, dv4 b, dv4 c, dv4 d, f64 t);
dv4 bezier (dv4 a, dv4 b, dv4 c, dv4 d, dv4 e, f64 t);

//// angle stuff
constexpr dv4 to_rad (dv4 deg);
// degress "literal", converts degrees to radiants
constexpr dv4 deg (dv4 deg);
constexpr dv4 to_deg (dv4 rad);

