// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "iv2.hpp"

#include "iv3.hpp"
#include "iv4.hpp"
#include "bv2.hpp"
#include "bv2.hpp"
#include "fv2.hpp"
#include "dv2.hpp"
#include "s64v2.hpp"
#include "u8v2.hpp"

namespace vector {
	
	
	// truncate vector
	iv2::iv2 (iv3 v): x{v.x}, y{v.y} {
		
	}
	
	// truncate vector
	iv2::iv2 (iv4 v): x{v.x}, y{v.y} {
		
	}
	
	//// Truncating cast operators
	
	
	//// Type cast operators
	
	
	iv2::operator bv2 () const {
		return bv2((bool)x, (bool)y);
	}
	
	iv2::operator fv2 () const {
		return fv2((f32)x, (f32)y);
	}
	
	iv2::operator dv2 () const {
		return dv2((f64)x, (f64)y);
	}
	
	iv2::operator s64v2 () const {
		return s64v2((s64)x, (s64)y);
	}
	
	iv2::operator u8v2 () const {
		return u8v2((u8)x, (u8)y);
	}
	
	
	//// arthmethic ops
	
	//// comparison ops
	
	bv2 operator< (iv2 l, iv2 r) {
		return bv2(l.x < r.x, l.y < r.y);
	}
	
	bv2 operator<= (iv2 l, iv2 r) {
		return bv2(l.x <= r.x, l.y <= r.y);
	}
	
	bv2 operator> (iv2 l, iv2 r) {
		return bv2(l.x > r.x, l.y > r.y);
	}
	
	bv2 operator>= (iv2 l, iv2 r) {
		return bv2(l.x >= r.x, l.y >= r.y);
	}
	
	bv2 operator== (iv2 l, iv2 r) {
		return bv2(l.x == r.x, l.y == r.y);
	}
	
	bv2 operator!= (iv2 l, iv2 r) {
		return bv2(l.x != r.x, l.y != r.y);
	}
	
	// vectors are equal, equivalent to all(l == r)
	bool equal (iv2 l, iv2 r) {
		return all(l == r);
	}
	
	// componentwise ternary c ? l : r
	iv2 select (bv2 c, iv2 l, iv2 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y;
	}
	
	//// misc ops
	
	iv2 clamp (iv2 x, iv2 a, iv2 b) {
		return min(max(x,a), b);
	}
	
	// get min component of vector, optionally get component index via min_index
	s32 min_component (iv2 v, int* min_index) {
		int index = 0;
		s32 min_val = v.x;	
		for (int i=1; i<2; ++i) {
			if (v.arr[i] <= min_val) {
				index = i;
				min_val = v.arr[i];
			}
		}
		if (min_index) *min_index = index;
		return min_val;
	}
	
	// get max component of vector, optionally get component index via max_index
	s32 max_component (iv2 v, int* max_index) {
		int index = 0;
		s32 max_val = v.x;	
		for (int i=1; i<2; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	
	fv2 to_rad (iv2 deg) {
		return (fv2)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	fv2 deg (iv2 deg) {
		return (fv2)deg * DEG_TO_RAD;
	}
	
	fv2 to_deg (iv2 rad) {
		return (fv2)rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	// magnitude of vector
	f32 length (iv2 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y));
	}
	
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	s32 length_sqr (iv2 v) {
		return v.x * v.x + v.y * v.y;
	}
	
	// distance between points, equivalent to length(a - b)
	f32 distance (iv2 a, iv2 b) {
		return length(a - b);
	}
	
	// normalize vector so that it has length() = 1, undefined for zero vector
	fv2 normalize (iv2 v) {
		return fv2(v) / length(v);
	}
	
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	fv2 normalize_or_zero (iv2 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv2(v) / fv2(len);
	}
	
	// dot product
	s32 dot (iv2 l, iv2 r) {
		return l.x * r.x + l.y * r.y;
	}
	
	// 
	// 2d cross product hack for convinient 2d stuff
	// same as cross(v3(l, 0), v3(r, 0)).z,
	// ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)
	// 
	s32 cross (iv2 l, iv2 r) {
		return l.x * r.y - l.y * r.x;
	}
	
	// rotate 2d vector counterclockwise 90 deg, ie. iv2(-y, x) which is fast
	iv2 rotate90 (iv2 v) {
		return iv2(-v.y, v.x);
	}
}// namespace vector
