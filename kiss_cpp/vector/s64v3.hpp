// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	union s64v2;
	union s64v4;
	union bv3;
	union bv3;
	union fv3;
	union dv3;
	union iv3;
	union u8v3;
	
	union s64v3 {
		struct {
			s64	x, y, z;
		};
		s64		arr[3];
		
		s64& operator[] (int i);
		s64 const& operator[] (int i) const;
		
		s64v3 ();
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		s64v3 (s64 all);
		// supply all components
		s64v3 (s64 x, s64 y, s64 z);
		// extend vector
		s64v3 (s64v2 xy, s64 z);
		// truncate vector
		s64v3 (s64v4 v);
		
		//// Truncating cast operators
		
		explicit operator s64v2 () const;
		
		//// Type cast operators
		
		explicit operator bv3 () const;
		explicit operator fv3 () const;
		explicit operator dv3 () const;
		explicit operator iv3 () const;
		explicit operator u8v3 () const;
		
		s64v3 operator+= (s64v3 r);
		s64v3 operator-= (s64v3 r);
		s64v3 operator*= (s64v3 r);
		s64v3 operator/= (s64v3 r);
	};
	
	//// arthmethic ops
	s64v3 operator+ (s64v3 v);
	s64v3 operator- (s64v3 v);
	s64v3 operator+ (s64v3 l, s64v3 r);
	s64v3 operator- (s64v3 l, s64v3 r);
	s64v3 operator* (s64v3 l, s64v3 r);
	s64v3 operator/ (s64v3 l, s64v3 r);
	
	//// comparison ops
	bv3 operator< (s64v3 l, s64v3 r);
	bv3 operator<= (s64v3 l, s64v3 r);
	bv3 operator> (s64v3 l, s64v3 r);
	bv3 operator>= (s64v3 l, s64v3 r);
	bv3 operator== (s64v3 l, s64v3 r);
	bv3 operator!= (s64v3 l, s64v3 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (s64v3 l, s64v3 r);
	// componentwise ternary c ? l : r
	s64v3 select (bv3 c, s64v3 l, s64v3 r);
	
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
	
	dv3 to_rad (s64v3 deg);
	// degress "literal", converts degrees to radiants
	dv3 deg (s64v3 deg);
	dv3 to_deg (s64v3 rad);
	
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
	// dot product
	s64 dot (s64v3 l, s64v3 r);
	// 3d cross product
	s64v3 cross (s64v3 l, s64v3 r);
}// namespace vector

