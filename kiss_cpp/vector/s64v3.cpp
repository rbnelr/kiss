// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "s64v3.hpp"

#include "s64v2.hpp"
#include "s64v4.hpp"
#include "bv3.hpp"
#include "bv3.hpp"
#include "fv3.hpp"
#include "dv3.hpp"
#include "iv3.hpp"
#include "u8v3.hpp"

namespace vector {
	
	s64& s64v3::operator[] (int i) {
		return arr[i];
	}
	
	s64 const& s64v3::operator[] (int i) const {
		return arr[i];
	}
	
	
	s64v3::s64v3 () {
		
	}
	
	s64v3::s64v3 (s64 all): x{all}, y{all}, z{all} {
		
	}
	
	s64v3::s64v3 (s64 x, s64 y, s64 z): x{x}, y{y}, z{z} {
		
	}
	
	s64v3::s64v3 (s64v2 xy, s64 z): x{xy.x}, y{xy.y}, z{z} {
		
	}
	
	s64v3::s64v3 (s64v4 v): x{v.x}, y{v.y}, z{v.z} {
		
	}
	
	//// Truncating cast operators
	
	
	s64v3::operator s64v2 () const {
		return s64v2(x, y);
	}
	
	//// Type cast operators
	
	
	s64v3::operator bv3 () const {
		return bv3((bool)x, (bool)y, (bool)z);
	}
	
	s64v3::operator fv3 () const {
		return fv3((f32)x, (f32)y, (f32)z);
	}
	
	s64v3::operator dv3 () const {
		return dv3((f64)x, (f64)y, (f64)z);
	}
	
	s64v3::operator iv3 () const {
		return iv3((s32)x, (s32)y, (s32)z);
	}
	
	s64v3::operator u8v3 () const {
		return u8v3((u8)x, (u8)y, (u8)z);
	}
	
	
	s64v3 s64v3::operator+= (s64v3 r) {
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}
	
	s64v3 s64v3::operator-= (s64v3 r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	
	s64v3 s64v3::operator*= (s64v3 r) {
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	
	s64v3 s64v3::operator/= (s64v3 r) {
		x /= r.x;
		y /= r.y;
		z /= r.z;
		return *this;
	}
	
	//// arthmethic ops
	
	s64v3 operator+ (s64v3 v) {
		return s64v3(+v.x, +v.y, +v.z);
	}
	
	s64v3 operator- (s64v3 v) {
		return s64v3(-v.x, -v.y, -v.z);
	}
	
	s64v3 operator+ (s64v3 l, s64v3 r) {
		return s64v3(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	
	s64v3 operator- (s64v3 l, s64v3 r) {
		return s64v3(l.x - r.x, l.y - r.y, l.z - r.z);
	}
	
	s64v3 operator* (s64v3 l, s64v3 r) {
		return s64v3(l.x * r.x, l.y * r.y, l.z * r.z);
	}
	
	s64v3 operator/ (s64v3 l, s64v3 r) {
		return s64v3(l.x / r.x, l.y / r.y, l.z / r.z);
	}
	
	//// comparison ops
	
	bv3 operator< (s64v3 l, s64v3 r) {
		return bv3(l.x < r.x, l.y < r.y, l.z < r.z);
	}
	
	bv3 operator<= (s64v3 l, s64v3 r) {
		return bv3(l.x <= r.x, l.y <= r.y, l.z <= r.z);
	}
	
	bv3 operator> (s64v3 l, s64v3 r) {
		return bv3(l.x > r.x, l.y > r.y, l.z > r.z);
	}
	
	bv3 operator>= (s64v3 l, s64v3 r) {
		return bv3(l.x >= r.x, l.y >= r.y, l.z >= r.z);
	}
	
	bv3 operator== (s64v3 l, s64v3 r) {
		return bv3(l.x == r.x, l.y == r.y, l.z == r.z);
	}
	
	bv3 operator!= (s64v3 l, s64v3 r) {
		return bv3(l.x != r.x, l.y != r.y, l.z != r.z);
	}
	
	bool equal (s64v3 l, s64v3 r) {
		return all(l == r);
	}
	
	s64v3 select (bv3 c, s64v3 l, s64v3 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y, c.z ? l.z : r.z;
	}
	
	//// misc ops
	
	s64v3 abs (s64v3 v) {
		return s64v3(abs(v.x), abs(v.y), abs(v.z));
	}
	
	s64v3 min (s64v3 l, s64v3 r) {
		return s64v3(min(l.x,r.x), min(l.y,r.y), min(l.z,r.z));
	}
	
	s64v3 max (s64v3 l, s64v3 r) {
		return s64v3(max(l.x,r.x), max(l.y,r.y), max(l.z,r.z));
	}
	
	s64v3 clamp (s64v3 x, s64v3 a, s64v3 b) {
		return min(max(x,a), b);
	}
	
	s64 min_component (s64v3 v, int* min_index) {
		int index = 0;
		s64 min_val = v.x;	
		for (int i=1; i<3; ++i) {
			if (v.arr[i] <= min_val) {
				index = i;
				min_val = v.arr[i];
			}
		}
		if (min_index) *min_index = index;
		return min_val;
	}
	
	s64 max_component (s64v3 v, int* max_index) {
		int index = 0;
		s64 max_val = v.x;	
		for (int i=1; i<3; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	s64v3 wrap (s64v3 v, s64v3 range) {
		return s64v3(wrap(v.x,range.x), wrap(v.y,range.y), wrap(v.z,range.z));
	}
	
	s64v3 wrap (s64v3 v, s64v3 a, s64v3 b) {
		return s64v3(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y), wrap(v.z,a.z,b.z));
	}
	
	
	dv3 to_rad (s64v3 deg) {
		return (dv3)deg * DEG_TO_RADd;
	}
	
	dv3 deg (s64v3 deg) {
		return (dv3)deg * DEG_TO_RADd;
	}
	
	dv3 to_deg (s64v3 rad) {
		return (dv3)rad * RAD_TO_DEGd;
	}
	
	//// linear algebra ops
	
	f64 length (s64v3 v) {
		return sqrt((f64)(v.x * v.x + v.y * v.y + v.z * v.z));
	}
	
	s64 length_sqr (s64v3 v) {
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
	
	f64 distance (s64v3 a, s64v3 b) {
		return length(a - b);
	}
	
	dv3 normalize (s64v3 v) {
		return dv3(v) / length(v);
	}
	
	dv3 normalize_or_zero (s64v3 v) {
		f64 len = length(v);
		if (len == f64(0)) {
			return f64(0);
		}
		return dv3(v) / dv3(len);
	}
	
	s64 dot (s64v3 l, s64v3 r) {
		return l.x * r.x + l.y * r.y + l.z * r.z;
	}
	
	s64v3 cross (s64v3 l, s64v3 r) {
		return s64v3(
				l.y * r.z - l.z * r.y,
				l.z * r.x - l.x * r.z,
				l.x * r.y - l.y * r.x);
	}
}// namespace vector

