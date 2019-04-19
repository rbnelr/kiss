// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	union fv2;
	union fv4;
	union bv3;
	union bv3;
	union dv3;
	union iv3;
	union s64v3;
	union u8v3;
	
	union fv3 {
		struct {
			f32	x, y, z;
		};
		f32		arr[3];
		
		f32& operator[] (int i);
		f32 const& operator[] (int i) const;
		
		fv3 ();
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		fv3 (f32 all);
		// supply all components
		fv3 (f32 x, f32 y, f32 z);
		// extend vector
		fv3 (fv2 xy, f32 z);
		// truncate vector
		fv3 (fv4 v);
		
		//// Truncating cast operators
		
		explicit operator fv2 () const;
		
		//// Type cast operators
		
		explicit operator bv3 () const;
		explicit operator dv3 () const;
		explicit operator iv3 () const;
		explicit operator s64v3 () const;
		explicit operator u8v3 () const;
		
		fv3 operator+= (fv3 r);
		fv3 operator-= (fv3 r);
		fv3 operator*= (fv3 r);
		fv3 operator/= (fv3 r);
	};
	
	//// arthmethic ops
	fv3 operator+ (fv3 v);
	fv3 operator- (fv3 v);
	fv3 operator+ (fv3 l, fv3 r);
	fv3 operator- (fv3 l, fv3 r);
	fv3 operator* (fv3 l, fv3 r);
	fv3 operator/ (fv3 l, fv3 r);
	
	//// comparison ops
	bv3 operator< (fv3 l, fv3 r);
	bv3 operator<= (fv3 l, fv3 r);
	bv3 operator> (fv3 l, fv3 r);
	bv3 operator>= (fv3 l, fv3 r);
	bv3 operator== (fv3 l, fv3 r);
	bv3 operator!= (fv3 l, fv3 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (fv3 l, fv3 r);
	// componentwise ternary c ? l : r
	fv3 select (bv3 c, fv3 l, fv3 r);
	
	//// misc ops
	fv3 abs (fv3 v);
	fv3 min (fv3 l, fv3 r);
	fv3 max (fv3 l, fv3 r);
	fv3 clamp (fv3 x, fv3 a=fv3(0), fv3 b=fv3(1));
	// get min component of vector, optionally get component index via min_index
	f32 min_component (fv3 v, int* min_index=nullptr);
	// get max component of vector, optionally get component index via max_index
	f32 max_component (fv3 v, int* max_index=nullptr);
	
	fv3 floor (fv3 v);
	fv3 ceil (fv3 v);
	fv3 round (fv3 v);
	iv3 floori (fv3 v);
	iv3 ceili (fv3 v);
	iv3 roundi (fv3 v);
	fv3 pow (fv3 v, fv3 e);
	fv3 wrap (fv3 v, fv3 range);
	fv3 wrap (fv3 v, fv3 a, fv3 b);
	
	// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
	fv3 lerp (fv3 a, fv3 b, fv3 t);
	// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
	fv3 map (fv3 x, fv3 in_a, fv3 in_b);
	// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
	fv3 map (fv3 x, fv3 in_a, fv3 in_b, fv3 out_a, fv3 out_b);
	
	//// angle stuff
	fv3 to_rad (fv3 deg);
	// degress "literal", converts degrees to radiants
	fv3 deg (fv3 deg);
	fv3 to_deg (fv3 rad);
	
	//// linear algebra ops
	// magnitude of vector
	f32 length (fv3 v);
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	f32 length_sqr (fv3 v);
	// distance between points, equivalent to length(a - b)
	f32 distance (fv3 a, fv3 b);
	// normalize vector so that it has length() = 1, undefined for zero vector
	fv3 normalize (fv3 v);
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	fv3 normalize_or_zero (fv3 v);
	// dot product
	f32 dot (fv3 l, fv3 r);
	// 3d cross product
	fv3 cross (fv3 l, fv3 r);
}// namespace vector

