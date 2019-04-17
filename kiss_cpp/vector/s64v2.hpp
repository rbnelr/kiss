// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	union s64v3;
	union s64v4;
	union bv2;
	union bv2;
	union fv2;
	union dv2;
	union iv2;
	union u8v2;
	
	union s64v2 {
		struct {
			s64	x, y;
		};
		s64		arr[2];
		
		s64& operator[] (int i);
		s64 operator[] (int i) const;
		
		s64v2 ();
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		s64v2 (s64 all);
		// supply all components
		s64v2 (s64 x, s64 y);
		// truncate vector
		s64v2 (s64v3 v);
		// truncate vector
		s64v2 (s64v4 v);
		
		//// Truncating cast operators
		
		
		//// Type cast operators
		
		operator bv2 () const;
		operator fv2 () const;
		operator dv2 () const;
		operator iv2 () const;
		operator u8v2 () const;
		
		s64v2 operator+= (s64v2 r);
		s64v2 operator-= (s64v2 r);
		s64v2 operator*= (s64v2 r);
		s64v2 operator/= (s64v2 r);
	};
	
	//// arthmethic ops
	s64v2 operator+ (s64v2 v);
	s64v2 operator- (s64v2 v);
	s64v2 operator+ (s64v2 l, s64v2 r);
	s64v2 operator- (s64v2 l, s64v2 r);
	s64v2 operator* (s64v2 l, s64v2 r);
	s64v2 operator/ (s64v2 l, s64v2 r);
	
	//// comparison ops
	bv2 operator< (s64v2 l, s64v2 r);
	bv2 operator<= (s64v2 l, s64v2 r);
	bv2 operator> (s64v2 l, s64v2 r);
	bv2 operator>= (s64v2 l, s64v2 r);
	bv2 operator== (s64v2 l, s64v2 r);
	bv2 operator!= (s64v2 l, s64v2 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (s64v2 l, s64v2 r);
	// componentwise ternary c ? l : r
	s64v2 select (s64v2 c, s64v2 l, s64v2 r);
	
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
	// dot product
	s64 dot (s64v2 l, s64v2 r);
	// 2d cross product hack for convinient 2d stuff
	// same as cross(v3(l, 0), v3(r, 0)).z, ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)
	s64 cross (s64v2 l, s64v2 r);
}// namespace vector

