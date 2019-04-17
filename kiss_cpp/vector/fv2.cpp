// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "fv2.hpp"

#include "fv3.hpp"
#include "fv4.hpp"
#include "bv2.hpp"
#include "bv2.hpp"
#include "dv2.hpp"
#include "iv2.hpp"
#include "s64v2.hpp"
#include "u8v2.hpp"

namespace vector {
	
	f32& fv2::operator[] (int i) {
		return arr[i];
	}
	
	f32 fv2::operator[] (int i) const {
		return arr[i];
	}
	
	
	fv2::fv2 () {
		
	}
	
	fv2::fv2 (f32 all): x{all}, y{all} {
		
	}
	
	fv2::fv2 (f32 x, f32 y): x{x}, y{y} {
		
	}
	
	fv2::fv2 (fv3 v): x{v.x}, y{v.y} {
		
	}
	
	fv2::fv2 (fv4 v): x{v.x}, y{v.y} {
		
	}
	
	//// Truncating cast operators
	
	
	//// Type cast operators
	
	
	fv2::operator bv2 () const {
		return bv2((bool)x, (bool)y);
	}
	
	fv2::operator dv2 () const {
		return dv2((f64)x, (f64)y);
	}
	
	fv2::operator iv2 () const {
		return iv2((int)x, (int)y);
	}
	
	fv2::operator s64v2 () const {
		return s64v2((s64)x, (s64)y);
	}
	
	fv2::operator u8v2 () const {
		return u8v2((u8)x, (u8)y);
	}
	
	
	fv2 fv2::operator+= (fv2 r) {
		x += r.x;
		y += r.y;
		return *this;
	}
	
	fv2 fv2::operator-= (fv2 r) {
		x -= r.x;
		y -= r.y;
		return *this;
	}
	
	fv2 fv2::operator*= (fv2 r) {
		x *= r.x;
		y *= r.y;
		return *this;
	}
	
	fv2 fv2::operator/= (fv2 r) {
		x /= r.x;
		y /= r.y;
		return *this;
	}
	
	//// arthmethic ops
	
	fv2 operator+ (fv2 v) {
		return fv2(+v.x, +v.y);
	}
	
	fv2 operator- (fv2 v) {
		return fv2(-v.x, -v.y);
	}
	
	fv2 operator+ (fv2 l, fv2 r) {
		return fv2(l.x + r.x, l.y + r.y);
	}
	
	fv2 operator- (fv2 l, fv2 r) {
		return fv2(l.x - r.x, l.y - r.y);
	}
	
	fv2 operator* (fv2 l, fv2 r) {
		return fv2(l.x * r.x, l.y * r.y);
	}
	
	fv2 operator/ (fv2 l, fv2 r) {
		return fv2(l.x / r.x, l.y / r.y);
	}
	
	//// comparison ops
	
	bv2 operator< (fv2 l, fv2 r) {
		return bv2(l.x < r.x, l.y < r.y);
	}
	
	bv2 operator<= (fv2 l, fv2 r) {
		return bv2(l.x <= r.x, l.y <= r.y);
	}
	
	bv2 operator> (fv2 l, fv2 r) {
		return bv2(l.x > r.x, l.y > r.y);
	}
	
	bv2 operator>= (fv2 l, fv2 r) {
		return bv2(l.x >= r.x, l.y >= r.y);
	}
	
	bv2 operator== (fv2 l, fv2 r) {
		return bv2(l.x == r.x, l.y == r.y);
	}
	
	bv2 operator!= (fv2 l, fv2 r) {
		return bv2(l.x != r.x, l.y != r.y);
	}
	
	bool equal (fv2 l, fv2 r) {
		return all(l == r);
	}
	
	fv2 select (fv2 c, fv2 l, fv2 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y;
	}
	
	//// misc ops
	
	fv2 abs (fv2 v) {
		return fv2(abs(v.x), abs(v.y));
	}
	
	fv2 min (fv2 l, fv2 r) {
		return fv2(min(l.x,r.x), min(l.y,r.y));
	}
	
	fv2 max (fv2 l, fv2 r) {
		return fv2(max(l.x,r.x), max(l.y,r.y));
	}
	
	fv2 clamp (fv2 x, fv2 a, fv2 b) {
		return min(max(x,a), b);
	}
	
	f32 min_component (fv2 v, int* min_index) {
		int index = 0;
		f32 min_val = v.x;	
		for (int i=1; i<2; ++i) {
			if (v.arr[i] <= min_val) {
				index = i;
				min_val = v.arr[i];
			}
		}
		if (min_index) *min_index = index;
		return min_val;
	}
	
	f32 max_component (fv2 v, int* max_index) {
		int index = 0;
		f32 max_val = v.x;	
		for (int i=1; i<2; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	fv2 floor (fv2 v) {
		return fv2(floor(v.x), floor(v.y));
	}
	
	fv2 ceil (fv2 v) {
		return fv2(ceil(v.x), ceil(v.y));
	}
	
	fv2 round (fv2 v) {
		return fv2(round(v.x), round(v.y));
	}
	
	iv2 floori (fv2 v) {
		return iv2(floori(v.x), floori(v.y));
	}
	
	iv2 ceili (fv2 v) {
		return iv2(ceili(v.x), ceili(v.y));
	}
	
	iv2 roundi (fv2 v) {
		return iv2(roundi(v.x), roundi(v.y));
	}
	
	fv2 pow (fv2 v, fv2 e) {
		return fv2(pow(v.x,e.x), pow(v.y,e.y));
	}
	
	fv2 wrap (fv2 v, fv2 range) {
		return fv2(wrap(v.x,range.x), wrap(v.y,range.y));
	}
	
	fv2 wrap (fv2 v, fv2 a, fv2 b) {
		return fv2(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y));
	}
	
	
	fv2 lerp (fv2 a, fv2 b, fv2 t) {
		return a * (fv2(1) - t) + b * t;
	}
	
	fv2 map (fv2 x, fv2 in_a, fv2 in_b) {
		return (x - in_a) / (in_b - in_a);
	}
	
	fv2 map (fv2 x, fv2 in_a, fv2 in_b, fv2 out_a, fv2 out_b) {
		return lerp(out_a, out_b, map(x, in_a, in_b));
	}
	
	fv2 smoothstep (fv2 x) {
		fv2 t = clamp(x);
		return t * t * (fv2(3) - fv2(2) * t);
	}
	
	fv2 bezier (fv2 a, fv2 b, fv2 c, f32 t) {
		fv2 d = lerp(a, b, t);
		fv2 e = lerp(b, c, t);
		fv2 f = lerp(d, e, t);
		return f;
	}
	
	fv2 bezier (fv2 a, fv2 b, fv2 c, fv2 d, f32 t) {
		return bezier(
				lerp(a, b, t),
				lerp(b, c, t),
				lerp(c, d, t),
				t
		);
	}
	
	fv2 bezier (fv2 a, fv2 b, fv2 c, fv2 d, fv2 e, f32 t) {
		return bezier(
				lerp(a, b, t),
				lerp(b, c, t),
				lerp(c, d, t),
				lerp(d, e, t),
				t
		);
	}
	
	//// angle stuff
	
	fv2 to_rad (fv2 deg) {
		return deg * DEG_TO_RAD;
	}
	
	fv2 deg (fv2 deg) {
		return deg * DEG_TO_RAD;
	}
	
	fv2 to_deg (fv2 rad) {
		return rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	f32 length (fv2 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y));
	}
	
	f32 length_sqr (fv2 v) {
		return v.x * v.x + v.y * v.y;
	}
	
	f32 distance (fv2 a, fv2 b) {
		return length(a - b);
	}
	
	fv2 normalize (fv2 v) {
		return fv2(v) / length(v);
	}
	
	fv2 normalize_or_zero (fv2 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv2(v) / fv2(len);
	}
	
	f32 dot (fv2 l, fv2 r) {
		return l.x * r.x + l.y * r.y;
	}
	
	f32 cross (fv2 l, fv2 r) {
		return l.x * r.y - l.y * r.x;
	}
}// namespace vector

