// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "iv4.hpp"

#include "iv2.hpp"
#include "iv3.hpp"
#include "bv4.hpp"
#include "bv4.hpp"
#include "fv4.hpp"
#include "dv4.hpp"
#include "s64v4.hpp"
#include "u8v4.hpp"

namespace vector {
	
	
	// extend vector
	iv4::iv4 (iv2 xy, s32 z, s32 w): x{xy.x}, y{xy.y}, z{z}, w{w} {
		
	}
	
	// extend vector
	iv4::iv4 (iv3 xyz, s32 w): x{xyz.x}, y{xyz.y}, z{xyz.z}, w{w} {
		
	}
	
	//// Truncating cast operators
	
	
	iv4::operator iv2 () const {
		return iv2(x, y);
	}
	
	iv4::operator iv3 () const {
		return iv3(x, y, z);
	}
	
	//// Type cast operators
	
	
	iv4::operator bv4 () const {
		return bv4((bool)x, (bool)y, (bool)z, (bool)w);
	}
	
	iv4::operator fv4 () const {
		return fv4((f32)x, (f32)y, (f32)z, (f32)w);
	}
	
	iv4::operator dv4 () const {
		return dv4((f64)x, (f64)y, (f64)z, (f64)w);
	}
	
	iv4::operator s64v4 () const {
		return s64v4((s64)x, (s64)y, (s64)z, (s64)w);
	}
	
	iv4::operator u8v4 () const {
		return u8v4((u8)x, (u8)y, (u8)z, (u8)w);
	}
	
	
	//// arthmethic ops
	
	//// comparison ops
	
	bv4 operator< (iv4 l, iv4 r) {
		return bv4(l.x < r.x, l.y < r.y, l.z < r.z, l.w < r.w);
	}
	
	bv4 operator<= (iv4 l, iv4 r) {
		return bv4(l.x <= r.x, l.y <= r.y, l.z <= r.z, l.w <= r.w);
	}
	
	bv4 operator> (iv4 l, iv4 r) {
		return bv4(l.x > r.x, l.y > r.y, l.z > r.z, l.w > r.w);
	}
	
	bv4 operator>= (iv4 l, iv4 r) {
		return bv4(l.x >= r.x, l.y >= r.y, l.z >= r.z, l.w >= r.w);
	}
	
	bv4 operator== (iv4 l, iv4 r) {
		return bv4(l.x == r.x, l.y == r.y, l.z == r.z, l.w == r.w);
	}
	
	bv4 operator!= (iv4 l, iv4 r) {
		return bv4(l.x != r.x, l.y != r.y, l.z != r.z, l.w != r.w);
	}
	
	// vectors are equal, equivalent to all(l == r)
	bool equal (iv4 l, iv4 r) {
		return all(l == r);
	}
	
	// componentwise ternary c ? l : r
	iv4 select (bv4 c, iv4 l, iv4 r) {
		return iv4(c.x ? l.x : r.x, c.y ? l.y : r.y, c.z ? l.z : r.z, c.w ? l.w : r.w);
	}
	
	//// misc ops
	
	iv4 clamp (iv4 x, iv4 a, iv4 b) {
		return min(max(x,a), b);
	}
	
	// get min component of vector, optionally get component index via min_index
	s32 min_component (iv4 v, int* min_index) {
		int index = 0;
		s32 min_val = v.x;	
		for (int i=1; i<4; ++i) {
			if (v.arr[i] <= min_val) {
				index = i;
				min_val = v.arr[i];
			}
		}
		if (min_index) *min_index = index;
		return min_val;
	}
	
	// get max component of vector, optionally get component index via max_index
	s32 max_component (iv4 v, int* max_index) {
		int index = 0;
		s32 max_val = v.x;	
		for (int i=1; i<4; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	
	fv4 to_rad (iv4 deg) {
		return (fv4)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	fv4 deg (iv4 deg) {
		return (fv4)deg * DEG_TO_RAD;
	}
	
	fv4 to_deg (iv4 rad) {
		return (fv4)rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	// magnitude of vector
	f32 length (iv4 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
	}
	
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	s32 length_sqr (iv4 v) {
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}
	
	// distance between points, equivalent to length(a - b)
	f32 distance (iv4 a, iv4 b) {
		return length(a - b);
	}
	
	// normalize vector so that it has length() = 1, undefined for zero vector
	fv4 normalize (iv4 v) {
		return fv4(v) / length(v);
	}
	
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	fv4 normalize_or_zero (iv4 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv4(v) / fv4(len);
	}
	
	// dot product
	s32 dot (iv4 l, iv4 r) {
		return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
	}
}// namespace vector

