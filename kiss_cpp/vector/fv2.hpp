// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	union fv3;
	union fv4;
	union bv2;
	union bv2;
	union dv2;
	union iv2;
	union s64v2;
	union u8v2;
	
	union fv2 {
		struct {
			f32	x, y;
		};
		f32		arr[2];
		
		f32& operator[] (int i);
		f32 operator[] (int i) const;
		
		fv2 ();
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		fv2 (f32 all);
		// supply all components
		fv2 (f32 x, f32 y);
		// truncate vector
		fv2 (fv3 v);
		// truncate vector
		fv2 (fv4 v);
		
		//// Truncating cast operators
		
		
		//// Type cast operators
		
		operator bv2 () const;
		operator dv2 () const;
		operator iv2 () const;
		operator s64v2 () const;
		operator u8v2 () const;
		
		fv2 operator+= (fv2 r);
		fv2 operator-= (fv2 r);
		fv2 operator*= (fv2 r);
		fv2 operator/= (fv2 r);
	};
	
	//// arthmethic ops
	fv2 operator+ (fv2 v);
	fv2 operator- (fv2 v);
	fv2 operator+ (fv2 l, fv2 r);
	fv2 operator- (fv2 l, fv2 r);
	fv2 operator* (fv2 l, fv2 r);
	fv2 operator/ (fv2 l, fv2 r);
	
	//// comparison ops
	bv2 operator< (fv2 l, fv2 r);
	bv2 operator<= (fv2 l, fv2 r);
	bv2 operator> (fv2 l, fv2 r);
	bv2 operator>= (fv2 l, fv2 r);
	bv2 operator== (fv2 l, fv2 r);
	bv2 operator!= (fv2 l, fv2 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (fv2 l, fv2 r);
	// componentwise ternary c ? l : r
	fv2 select (fv2 c, fv2 l, fv2 r);
	
	//// misc ops
	fv2 abs (fv2 v);
	fv2 min (fv2 l, fv2 r);
	fv2 max (fv2 l, fv2 r);
	fv2 clamp (fv2 x, fv2 a=fv2(0), fv2 b=fv2(1));
	// get min component of vector, optionally get component index via min_index
	f32 min_component (fv2 v, int* min_index=nullptr);
	// get max component of vector, optionally get component index via max_index
	f32 max_component (fv2 v, int* max_index=nullptr);
	
	fv2 floor (fv2 v);
	fv2 ceil (fv2 v);
	fv2 round (fv2 v);
	iv2 floori (fv2 v);
	iv2 ceili (fv2 v);
	iv2 roundi (fv2 v);
	fv2 pow (fv2 v, fv2 e);
	fv2 wrap (fv2 v, fv2 range);
	fv2 wrap (fv2 v, fv2 a, fv2 b);
	
	// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
	fv2 lerp (fv2 a, fv2 b, fv2 t);
	// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
	fv2 map (fv2 x, fv2 in_a, fv2 in_b);
	// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
	fv2 map (fv2 x, fv2 in_a, fv2 in_b, fv2 out_a, fv2 out_b);
	fv2 smoothstep (fv2 x);
	fv2 bezier (fv2 a, fv2 b, fv2 c, f32 t);
	fv2 bezier (fv2 a, fv2 b, fv2 c, fv2 d, f32 t);
	fv2 bezier (fv2 a, fv2 b, fv2 c, fv2 d, fv2 e, f32 t);
	
	//// angle stuff
	fv2 to_rad (fv2 deg);
	// degress "literal", converts degrees to radiants
	fv2 deg (fv2 deg);
	fv2 to_deg (fv2 rad);
	
	//// linear algebra ops
	// magnitude of vector
	f32 length (fv2 v);
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	f32 length_sqr (fv2 v);
	// distance between points, equivalent to length(a - b)
	f32 distance (fv2 a, fv2 b);
	// normalize vector so that it has length() = 1, undefined for zero vector
	fv2 normalize (fv2 v);
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	fv2 normalize_or_zero (fv2 v);
	// dot product
	f32 dot (fv2 l, fv2 r);
	// 2d cross product hack for convinient 2d stuff
	// same as cross(v3(l, 0), v3(r, 0)).z, ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)
	f32 cross (fv2 l, fv2 r);
}// namespace vector

