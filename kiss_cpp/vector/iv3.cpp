// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "iv3.hpp"

#include "iv2.hpp"
#include "iv4.hpp"
#include "bv3.hpp"
#include "bv3.hpp"
#include "fv3.hpp"
#include "dv3.hpp"
#include "s64v3.hpp"
#include "u8v3.hpp"

namespace vector {
	
	s32& iv3::operator[] (int i) {
		return arr[i];
	}
	
	s32 const& iv3::operator[] (int i) const {
		return arr[i];
	}
	
	
	iv3::iv3 () {
		
	}
	
	iv3::iv3 (s32 all): x{all}, y{all}, z{all} {
		
	}
	
	iv3::iv3 (s32 x, s32 y, s32 z): x{x}, y{y}, z{z} {
		
	}
	
	iv3::iv3 (iv2 xy, s32 z): x{xy.x}, y{xy.y}, z{z} {
		
	}
	
	iv3::iv3 (iv4 v): x{v.x}, y{v.y}, z{v.z} {
		
	}
	
	//// Truncating cast operators
	
	
	iv3::operator iv2 () const {
		return iv2(x, y);
	}
	
	//// Type cast operators
	
	
	iv3::operator bv3 () const {
		return bv3((bool)x, (bool)y, (bool)z);
	}
	
	iv3::operator fv3 () const {
		return fv3((f32)x, (f32)y, (f32)z);
	}
	
	iv3::operator dv3 () const {
		return dv3((f64)x, (f64)y, (f64)z);
	}
	
	iv3::operator s64v3 () const {
		return s64v3((s64)x, (s64)y, (s64)z);
	}
	
	iv3::operator u8v3 () const {
		return u8v3((u8)x, (u8)y, (u8)z);
	}
	
	
	iv3 iv3::operator+= (iv3 r) {
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}
	
	iv3 iv3::operator-= (iv3 r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	
	iv3 iv3::operator*= (iv3 r) {
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	
	iv3 iv3::operator/= (iv3 r) {
		x /= r.x;
		y /= r.y;
		z /= r.z;
		return *this;
	}
	
	//// arthmethic ops
	
	iv3 operator+ (iv3 v) {
		return iv3(+v.x, +v.y, +v.z);
	}
	
	iv3 operator- (iv3 v) {
		return iv3(-v.x, -v.y, -v.z);
	}
	
	iv3 operator+ (iv3 l, iv3 r) {
		return iv3(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	
	iv3 operator- (iv3 l, iv3 r) {
		return iv3(l.x - r.x, l.y - r.y, l.z - r.z);
	}
	
	iv3 operator* (iv3 l, iv3 r) {
		return iv3(l.x * r.x, l.y * r.y, l.z * r.z);
	}
	
	iv3 operator/ (iv3 l, iv3 r) {
		return iv3(l.x / r.x, l.y / r.y, l.z / r.z);
	}
	
	//// comparison ops
	
	bv3 operator< (iv3 l, iv3 r) {
		return bv3(l.x < r.x, l.y < r.y, l.z < r.z);
	}
	
	bv3 operator<= (iv3 l, iv3 r) {
		return bv3(l.x <= r.x, l.y <= r.y, l.z <= r.z);
	}
	
	bv3 operator> (iv3 l, iv3 r) {
		return bv3(l.x > r.x, l.y > r.y, l.z > r.z);
	}
	
	bv3 operator>= (iv3 l, iv3 r) {
		return bv3(l.x >= r.x, l.y >= r.y, l.z >= r.z);
	}
	
	bv3 operator== (iv3 l, iv3 r) {
		return bv3(l.x == r.x, l.y == r.y, l.z == r.z);
	}
	
	bv3 operator!= (iv3 l, iv3 r) {
		return bv3(l.x != r.x, l.y != r.y, l.z != r.z);
	}
	
	bool equal (iv3 l, iv3 r) {
		return all(l == r);
	}
	
	iv3 select (bv3 c, iv3 l, iv3 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y, c.z ? l.z : r.z;
	}
	
	//// misc ops
	
	iv3 abs (iv3 v) {
		return iv3(abs(v.x), abs(v.y), abs(v.z));
	}
	
	iv3 min (iv3 l, iv3 r) {
		return iv3(min(l.x,r.x), min(l.y,r.y), min(l.z,r.z));
	}
	
	iv3 max (iv3 l, iv3 r) {
		return iv3(max(l.x,r.x), max(l.y,r.y), max(l.z,r.z));
	}
	
	iv3 clamp (iv3 x, iv3 a, iv3 b) {
		return min(max(x,a), b);
	}
	
	s32 min_component (iv3 v, int* min_index) {
		int index = 0;
		s32 min_val = v.x;	
		for (int i=1; i<3; ++i) {
			if (v.arr[i] <= min_val) {
				index = i;
				min_val = v.arr[i];
			}
		}
		if (min_index) *min_index = index;
		return min_val;
	}
	
	s32 max_component (iv3 v, int* max_index) {
		int index = 0;
		s32 max_val = v.x;	
		for (int i=1; i<3; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	iv3 wrap (iv3 v, iv3 range) {
		return iv3(wrap(v.x,range.x), wrap(v.y,range.y), wrap(v.z,range.z));
	}
	
	iv3 wrap (iv3 v, iv3 a, iv3 b) {
		return iv3(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y), wrap(v.z,a.z,b.z));
	}
	
	
	fv3 to_rad (iv3 deg) {
		return (fv3)deg * DEG_TO_RAD;
	}
	
	fv3 deg (iv3 deg) {
		return (fv3)deg * DEG_TO_RAD;
	}
	
	fv3 to_deg (iv3 rad) {
		return (fv3)rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	f32 length (iv3 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y + v.z * v.z));
	}
	
	s32 length_sqr (iv3 v) {
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
	
	f32 distance (iv3 a, iv3 b) {
		return length(a - b);
	}
	
	fv3 normalize (iv3 v) {
		return fv3(v) / length(v);
	}
	
	fv3 normalize_or_zero (iv3 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv3(v) / fv3(len);
	}
	
	s32 dot (iv3 l, iv3 r) {
		return l.x * r.x + l.y * r.y + l.z * r.z;
	}
	
	iv3 cross (iv3 l, iv3 r) {
		return iv3(
				l.y * r.z - l.z * r.y,
				l.z * r.x - l.x * r.z,
				l.x * r.y - l.y * r.x);
	}
}// namespace vector

