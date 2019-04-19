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
	
	s32& iv2::operator[] (int i) {
		return arr[i];
	}
	
	s32 const& iv2::operator[] (int i) const {
		return arr[i];
	}
	
	
	iv2::iv2 () {
		
	}
	
	iv2::iv2 (s32 all): x{all}, y{all} {
		
	}
	
	iv2::iv2 (s32 x, s32 y): x{x}, y{y} {
		
	}
	
	iv2::iv2 (iv3 v): x{v.x}, y{v.y} {
		
	}
	
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
	
	
	iv2 iv2::operator+= (iv2 r) {
		x += r.x;
		y += r.y;
		return *this;
	}
	
	iv2 iv2::operator-= (iv2 r) {
		x -= r.x;
		y -= r.y;
		return *this;
	}
	
	iv2 iv2::operator*= (iv2 r) {
		x *= r.x;
		y *= r.y;
		return *this;
	}
	
	iv2 iv2::operator/= (iv2 r) {
		x /= r.x;
		y /= r.y;
		return *this;
	}
	
	//// arthmethic ops
	
	iv2 operator+ (iv2 v) {
		return iv2(+v.x, +v.y);
	}
	
	iv2 operator- (iv2 v) {
		return iv2(-v.x, -v.y);
	}
	
	iv2 operator+ (iv2 l, iv2 r) {
		return iv2(l.x + r.x, l.y + r.y);
	}
	
	iv2 operator- (iv2 l, iv2 r) {
		return iv2(l.x - r.x, l.y - r.y);
	}
	
	iv2 operator* (iv2 l, iv2 r) {
		return iv2(l.x * r.x, l.y * r.y);
	}
	
	iv2 operator/ (iv2 l, iv2 r) {
		return iv2(l.x / r.x, l.y / r.y);
	}
	
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
	
	bool equal (iv2 l, iv2 r) {
		return all(l == r);
	}
	
	iv2 select (bv2 c, iv2 l, iv2 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y;
	}
	
	//// misc ops
	
	iv2 abs (iv2 v) {
		return iv2(abs(v.x), abs(v.y));
	}
	
	iv2 min (iv2 l, iv2 r) {
		return iv2(min(l.x,r.x), min(l.y,r.y));
	}
	
	iv2 max (iv2 l, iv2 r) {
		return iv2(max(l.x,r.x), max(l.y,r.y));
	}
	
	iv2 clamp (iv2 x, iv2 a, iv2 b) {
		return min(max(x,a), b);
	}
	
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
	
	
	iv2 wrap (iv2 v, iv2 range) {
		return iv2(wrap(v.x,range.x), wrap(v.y,range.y));
	}
	
	iv2 wrap (iv2 v, iv2 a, iv2 b) {
		return iv2(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y));
	}
	
	
	fv2 to_rad (iv2 deg) {
		return (fv2)deg * DEG_TO_RAD;
	}
	
	fv2 deg (iv2 deg) {
		return (fv2)deg * DEG_TO_RAD;
	}
	
	fv2 to_deg (iv2 rad) {
		return (fv2)rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	f32 length (iv2 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y));
	}
	
	s32 length_sqr (iv2 v) {
		return v.x * v.x + v.y * v.y;
	}
	
	f32 distance (iv2 a, iv2 b) {
		return length(a - b);
	}
	
	fv2 normalize (iv2 v) {
		return fv2(v) / length(v);
	}
	
	fv2 normalize_or_zero (iv2 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv2(v) / fv2(len);
	}
	
	s32 dot (iv2 l, iv2 r) {
		return l.x * r.x + l.y * r.y;
	}
	
	s32 cross (iv2 l, iv2 r) {
		return l.x * r.y - l.y * r.x;
	}
	
	iv2 rotate90 (iv2 v) {
		return iv2(-v.y, v.x);
	}
}// namespace vector

