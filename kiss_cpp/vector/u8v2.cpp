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
	
	u8& u8v2::operator[] (int i) {
		return arr[i];
	}
	
	u8 u8v2::operator[] (int i) const {
		return arr[i];
	}
	
	
	u8v2::u8v2 () {
		
	}
	
	u8v2::u8v2 (u8 all): x{all}, y{all} {
		
	}
	
	u8v2::u8v2 (u8 x, u8 y): x{x}, y{y} {
		
	}
	
	u8v2::u8v2 (u8v3 v): x{v.x}, y{v.y} {
		
	}
	
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
		return iv2((int)x, (int)y);
	}
	
	u8v2::operator s64v2 () const {
		return s64v2((s64)x, (s64)y);
	}
	
	
	u8v2 u8v2::operator+= (u8v2 r) {
		x += r.x;
		y += r.y;
		return *this;
	}
	
	u8v2 u8v2::operator-= (u8v2 r) {
		x -= r.x;
		y -= r.y;
		return *this;
	}
	
	u8v2 u8v2::operator*= (u8v2 r) {
		x *= r.x;
		y *= r.y;
		return *this;
	}
	
	u8v2 u8v2::operator/= (u8v2 r) {
		x /= r.x;
		y /= r.y;
		return *this;
	}
	
	//// arthmethic ops
	
	u8v2 operator+ (u8v2 v) {
		return u8v2(+v.x, +v.y);
	}
	
	u8v2 operator- (u8v2 v) {
		return u8v2(-v.x, -v.y);
	}
	
	u8v2 operator+ (u8v2 l, u8v2 r) {
		return u8v2(l.x + r.x, l.y + r.y);
	}
	
	u8v2 operator- (u8v2 l, u8v2 r) {
		return u8v2(l.x - r.x, l.y - r.y);
	}
	
	u8v2 operator* (u8v2 l, u8v2 r) {
		return u8v2(l.x * r.x, l.y * r.y);
	}
	
	u8v2 operator/ (u8v2 l, u8v2 r) {
		return u8v2(l.x / r.x, l.y / r.y);
	}
	
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
	
	bool equal (u8v2 l, u8v2 r) {
		return all(l == r);
	}
	
	u8v2 select (u8v2 c, u8v2 l, u8v2 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y;
	}
	
	//// misc ops
	
	u8v2 abs (u8v2 v) {
		return u8v2(abs(v.x), abs(v.y));
	}
	
	u8v2 min (u8v2 l, u8v2 r) {
		return u8v2(min(l.x,r.x), min(l.y,r.y));
	}
	
	u8v2 max (u8v2 l, u8v2 r) {
		return u8v2(max(l.x,r.x), max(l.y,r.y));
	}
	
	u8v2 clamp (u8v2 x, u8v2 a, u8v2 b) {
		return min(max(x,a), b);
	}
	
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
	
	
	u8v2 wrap (u8v2 v, u8v2 range) {
		return u8v2(wrap(v.x,range.x), wrap(v.y,range.y));
	}
	
	u8v2 wrap (u8v2 v, u8v2 a, u8v2 b) {
		return u8v2(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y));
	}
	
	
	//// linear algebra ops
	
	f32 length (u8v2 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y));
	}
	
	u8 length_sqr (u8v2 v) {
		return v.x * v.x + v.y * v.y;
	}
	
	f32 distance (u8v2 a, u8v2 b) {
		return length(a - b);
	}
	
	fv2 normalize (u8v2 v) {
		return fv2(v) / length(v);
	}
	
	fv2 normalize_or_zero (u8v2 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv2(v) / fv2(len);
	}
	
	u8 dot (u8v2 l, u8v2 r) {
		return l.x * r.x + l.y * r.y;
	}
	
	u8 cross (u8v2 l, u8v2 r) {
		return l.x * r.y - l.y * r.x;
	}
}// namespace vector

