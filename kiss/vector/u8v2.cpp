// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "u8v2.hpp"

#include "u8v3.hpp"
#include "u8v4.hpp"
#include "bv2.hpp"
#include "bv2.hpp"
#include "fv2.hpp"
#include "dv2.hpp"
#include "iv2.hpp"
#include "s64v2.hpp"

namespace vector {
	
	
	// truncate vector
	u8v2::u8v2 (u8v3 v): x{v.x}, y{v.y} {
		
	}
	
	// truncate vector
	u8v2::u8v2 (u8v4 v): x{v.x}, y{v.y} {
		
	}
	
	//// Truncating cast operators
	
	
	//// Type cast operators
	
	
	u8v2::operator bv2 () const {
		return bv2((bool)x, (bool)y);
	}
	
	u8v2::operator fv2 () const {
		return fv2((f32)x, (f32)y);
	}
	
	u8v2::operator dv2 () const {
		return dv2((f64)x, (f64)y);
	}
	
	u8v2::operator iv2 () const {
		return iv2((s32)x, (s32)y);
	}
	
	u8v2::operator s64v2 () const {
		return s64v2((s64)x, (s64)y);
	}
	
	
	//// arthmethic ops
	
	//// comparison ops
	
	bv2 operator< (u8v2 l, u8v2 r) {
		return bv2(l.x < r.x, l.y < r.y);
	}
	
	bv2 operator<= (u8v2 l, u8v2 r) {
		return bv2(l.x <= r.x, l.y <= r.y);
	}
	
	bv2 operator> (u8v2 l, u8v2 r) {
		return bv2(l.x > r.x, l.y > r.y);
	}
	
	bv2 operator>= (u8v2 l, u8v2 r) {
		return bv2(l.x >= r.x, l.y >= r.y);
	}
	
	bv2 operator== (u8v2 l, u8v2 r) {
		return bv2(l.x == r.x, l.y == r.y);
	}
	
	bv2 operator!= (u8v2 l, u8v2 r) {
		return bv2(l.x != r.x, l.y != r.y);
	}
	
	// vectors are equal, equivalent to all(l == r)
	bool equal (u8v2 l, u8v2 r) {
		return all(l == r);
	}
	
	// componentwise ternary c ? l : r
	u8v2 select (bv2 c, u8v2 l, u8v2 r) {
		return u8v2(c.x ? l.x : r.x, c.y ? l.y : r.y);
	}
	
	//// misc ops
	
	u8v2 clamp (u8v2 x, u8v2 a, u8v2 b) {
		return min(max(x,a), b);
	}
	
	// get min component of vector, optionally get component index via min_index
	u8 min_component (u8v2 v, int* min_index) {
		int index = 0;
		u8 min_val = v.x;	
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
	u8 max_component (u8v2 v, int* max_index) {
		int index = 0;
		u8 max_val = v.x;	
		for (int i=1; i<2; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	
	fv2 to_rad (u8v2 deg) {
		return (fv2)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	fv2 deg (u8v2 deg) {
		return (fv2)deg * DEG_TO_RAD;
	}
	
	fv2 to_deg (u8v2 rad) {
		return (fv2)rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	// magnitude of vector
	f32 length (u8v2 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y));
	}
	
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	u8 length_sqr (u8v2 v) {
		return v.x * v.x + v.y * v.y;
	}
	
	// distance between points, equivalent to length(a - b)
	f32 distance (u8v2 a, u8v2 b) {
		return length(a - b);
	}
	
	// normalize vector so that it has length() = 1, undefined for zero vector
	fv2 normalize (u8v2 v) {
		return fv2(v) / length(v);
	}
	
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	fv2 normalize_or_zero (u8v2 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv2(v) / fv2(len);
	}
	
	// dot product
	u8 dot (u8v2 l, u8v2 r) {
		return l.x * r.x + l.y * r.y;
	}
	
	// 
	// 2d cross product hack for convinient 2d stuff
	// same as cross(v3(l, 0), v3(r, 0)).z,
	// ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)
	// 
	u8 cross (u8v2 l, u8v2 r) {
		return l.x * r.y - l.y * r.x;
	}
	
	// rotate 2d vector counterclockwise 90 deg, ie. u8v2(-y, x) which is fast
	u8v2 rotate90 (u8v2 v) {
		return u8v2(-v.y, v.x);
	}
}// namespace vector

