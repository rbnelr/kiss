// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

//// forward declarations
union fv2;
union fv3;
union bv4;
union iv4;
union s64v4;
union u8v4;

union fv4 {
	struct {
		f32	x, y, z, w;
	};
	f32		arr[4];
	
	f32& operator[] (int i);
	f32 operator[] (int i) const;
	
	fv4 ();
	// sets all components to one value
	constexpr fv4 (f32 all);
	// supply all components
	constexpr fv4 (f32 x, f32 y, f32 z, f32 w);
	// extend vector
	constexpr fv4 (fv2 xy, f32 z, f32 w);
	// extend vector
	constexpr fv4 (fv3 xyz, f32 w);
	
	fv4 operator+= (fv4 r);
	fv4 operator-= (fv4 r);
	fv4 operator*= (fv4 r);
	fv4 operator/= (fv4 r);
	
	//// Conversion operators
	operator iv4 () const;
	operator s64v4 () const;
	operator u8v4 () const;
};

//// arthmethic ops
constexpr fv4 operator+ (fv4 v);
constexpr fv4 operator- (fv4 v);
constexpr fv4 operator+ (fv4 l, fv4 r);
constexpr fv4 operator- (fv4 l, fv4 r);
constexpr fv4 operator* (fv4 l, fv4 r);
constexpr fv4 operator/ (fv4 l, fv4 r);

//// comparison ops
constexpr bv4 operator< (fv4 l, fv4 r);
constexpr bv4 operator<= (fv4 l, fv4 r);
constexpr bv4 operator> (fv4 l, fv4 r);
constexpr bv4 operator>= (fv4 l, fv4 r);
constexpr bv4 operator== (fv4 l, fv4 r);
constexpr bv4 operator!= (fv4 l, fv4 r);
// vectors are equal, equivalent to all(l == r)
constexpr bool equal (fv4 l, fv4 r);
// componentwise ternary c ? l : r
constexpr fv4 select (fv4 c, fv4 l, fv4 r);

//// misc ops
fv4 abs (fv4 v);
fv4 min (fv4 l, fv4 r);
fv4 max (fv4 l, fv4 r);
fv4 clamp (fv4 x, fv4 a=fv4(0), fv4 b=fv4(1));
// get min component of vector, optionally get component index via min_index
f32 min_component (fv4 v, int* min_index=nullptr);
// get max component of vector, optionally get component index via max_index
f32 max_component (fv4 v, int* max_index=nullptr);

fv4 floor (fv4 v);
fv4 ceil (fv4 v);
fv4 round (fv4 v);
iv4 floori (fv4 v);
iv4 ceili (fv4 v);
iv4 roundi (fv4 v);
fv4 pow (fv4 v, fv4 e);
fv4 wrap (fv4 v, fv4 range);
fv4 wrap (fv4 v, fv4 a, fv4 b);

//// linear algebra ops
// magnitude of vector
f32 length (fv4 v);
// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
f32 length_sqr (fv4 v);
// distance between points, equivalent to length(a - b)
f32 distance (fv4 a, fv4 b);
// normalize vector so that it has length() = 1, undefined for zero vector
fv4 normalize (fv4 v);
// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
fv4 normalize_or_zero (fv4 v);

// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
fv4 lerp (fv4 a, fv4 b, fv4 t);
// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
fv4 map (fv4 x, fv4 in_a, fv4 in_b);
// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
fv4 map (fv4 x, fv4 in_a, fv4 in_b, fv4 out_a, fv4 out_b);
fv4 smoothstep (fv4 x);
fv4 bezier (fv4 a, fv4 b, fv4 c, f32 t);
fv4 bezier (fv4 a, fv4 b, fv4 c, fv4 d, f32 t);
fv4 bezier (fv4 a, fv4 b, fv4 c, fv4 d, fv4 e, f32 t);

//// angle stuff
constexpr fv4 to_rad (fv4 deg);
// degress "literal", converts degrees to radiants
constexpr fv4 deg (fv4 deg);
constexpr fv4 to_deg (fv4 rad);

