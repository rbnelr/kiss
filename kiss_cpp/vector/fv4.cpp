// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "fv4.hpp"

#include "fv2.hpp"
#include "fv3.hpp"
#include "bv4.hpp"
#include "bv4.hpp"
#include "dv4.hpp"
#include "iv4.hpp"
#include "s64v4.hpp"
#include "u8v4.hpp"

namespace vector {
	
	f32& fv4::operator[] (int i) {
		return arr[i];
	}
	
	f32 const& fv4::operator[] (int i) const {
		return arr[i];
	}
	
	
	fv4::fv4 () {
		
	}
	
	fv4::fv4 (f32 all): x{all}, y{all}, z{all}, w{all} {
		
	}
	
	fv4::fv4 (f32 x, f32 y, f32 z, f32 w): x{x}, y{y}, z{z}, w{w} {
		
	}
	
	fv4::fv4 (fv2 xy, f32 z, f32 w): x{xy.x}, y{xy.y}, z{z}, w{w} {
		
	}
	
	fv4::fv4 (fv3 xyz, f32 w): x{xyz.x}, y{xyz.y}, z{xyz.z}, w{w} {
		
	}
	
	//// Truncating cast operators
	
	
	fv4::operator fv2 () const {
		return fv2(x, y);
	}
	
	fv4::operator fv3 () const {
		return fv3(x, y, z);
	}
	
	//// Type cast operators
	
	
	fv4::operator bv4 () const {
		return bv4((bool)x, (bool)y, (bool)z, (bool)w);
	}
	
	fv4::operator dv4 () const {
		return dv4((f64)x, (f64)y, (f64)z, (f64)w);
	}
	
	fv4::operator iv4 () const {
		return iv4((s32)x, (s32)y, (s32)z, (s32)w);
	}
	
	fv4::operator s64v4 () const {
		return s64v4((s64)x, (s64)y, (s64)z, (s64)w);
	}
	
	fv4::operator u8v4 () const {
		return u8v4((u8)x, (u8)y, (u8)z, (u8)w);
	}
	
	
	fv4 fv4::operator+= (fv4 r) {
		x += r.x;
		y += r.y;
		z += r.z;
		w += r.w;
		return *this;
	}
	
	fv4 fv4::operator-= (fv4 r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;
		w -= r.w;
		return *this;
	}
	
	fv4 fv4::operator*= (fv4 r) {
		x *= r.x;
		y *= r.y;
		z *= r.z;
		w *= r.w;
		return *this;
	}
	
	fv4 fv4::operator/= (fv4 r) {
		x /= r.x;
		y /= r.y;
		z /= r.z;
		w /= r.w;
		return *this;
	}
	
	//// arthmethic ops
	
	fv4 operator+ (fv4 v) {
		return fv4(+v.x, +v.y, +v.z, +v.w);
	}
	
	fv4 operator- (fv4 v) {
		return fv4(-v.x, -v.y, -v.z, -v.w);
	}
	
	fv4 operator+ (fv4 l, fv4 r) {
		return fv4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
	}
	
	fv4 operator- (fv4 l, fv4 r) {
		return fv4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
	}
	
	fv4 operator* (fv4 l, fv4 r) {
		return fv4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
	}
	
	fv4 operator/ (fv4 l, fv4 r) {
		return fv4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
	}
	
	//// comparison ops
	
	bv4 operator< (fv4 l, fv4 r) {
		return bv4(l.x < r.x, l.y < r.y, l.z < r.z, l.w < r.w);
	}
	
	bv4 operator<= (fv4 l, fv4 r) {
		return bv4(l.x <= r.x, l.y <= r.y, l.z <= r.z, l.w <= r.w);
	}
	
	bv4 operator> (fv4 l, fv4 r) {
		return bv4(l.x > r.x, l.y > r.y, l.z > r.z, l.w > r.w);
	}
	
	bv4 operator>= (fv4 l, fv4 r) {
		return bv4(l.x >= r.x, l.y >= r.y, l.z >= r.z, l.w >= r.w);
	}
	
	bv4 operator== (fv4 l, fv4 r) {
		return bv4(l.x == r.x, l.y == r.y, l.z == r.z, l.w == r.w);
	}
	
	bv4 operator!= (fv4 l, fv4 r) {
		return bv4(l.x != r.x, l.y != r.y, l.z != r.z, l.w != r.w);
	}
	
	bool equal (fv4 l, fv4 r) {
		return all(l == r);
	}
	
	fv4 select (bv4 c, fv4 l, fv4 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y, c.z ? l.z : r.z, c.w ? l.w : r.w;
	}
	
	//// misc ops
	
	fv4 abs (fv4 v) {
		return fv4(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
	}
	
	fv4 min (fv4 l, fv4 r) {
		return fv4(min(l.x,r.x), min(l.y,r.y), min(l.z,r.z), min(l.w,r.w));
	}
	
	fv4 max (fv4 l, fv4 r) {
		return fv4(max(l.x,r.x), max(l.y,r.y), max(l.z,r.z), max(l.w,r.w));
	}
	
	fv4 clamp (fv4 x, fv4 a, fv4 b) {
		return min(max(x,a), b);
	}
	
	f32 min_component (fv4 v, int* min_index) {
		int index = 0;
		f32 min_val = v.x;	
		for (int i=1; i<4; ++i) {
			if (v.arr[i] <= min_val) {
				index = i;
				min_val = v.arr[i];
			}
		}
		if (min_index) *min_index = index;
		return min_val;
	}
	
	f32 max_component (fv4 v, int* max_index) {
		int index = 0;
		f32 max_val = v.x;	
		for (int i=1; i<4; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	fv4 floor (fv4 v) {
		return fv4(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
	}
	
	fv4 ceil (fv4 v) {
		return fv4(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
	}
	
	fv4 round (fv4 v) {
		return fv4(round(v.x), round(v.y), round(v.z), round(v.w));
	}
	
	iv4 floori (fv4 v) {
		return iv4(floori(v.x), floori(v.y), floori(v.z), floori(v.w));
	}
	
	iv4 ceili (fv4 v) {
		return iv4(ceili(v.x), ceili(v.y), ceili(v.z), ceili(v.w));
	}
	
	iv4 roundi (fv4 v) {
		return iv4(roundi(v.x), roundi(v.y), roundi(v.z), roundi(v.w));
	}
	
	fv4 pow (fv4 v, fv4 e) {
		return fv4(pow(v.x,e.x), pow(v.y,e.y), pow(v.z,e.z), pow(v.w,e.w));
	}
	
	fv4 wrap (fv4 v, fv4 range) {
		return fv4(wrap(v.x,range.x), wrap(v.y,range.y), wrap(v.z,range.z), wrap(v.w,range.w));
	}
	
	fv4 wrap (fv4 v, fv4 a, fv4 b) {
		return fv4(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y), wrap(v.z,a.z,b.z), wrap(v.w,a.w,b.w));
	}
	
	
	fv4 lerp (fv4 a, fv4 b, fv4 t) {
		return a * (fv4(1) - t) + b * t;
	}
	
	fv4 map (fv4 x, fv4 in_a, fv4 in_b) {
		return (x - in_a) / (in_b - in_a);
	}
	
	fv4 map (fv4 x, fv4 in_a, fv4 in_b, fv4 out_a, fv4 out_b) {
		return lerp(out_a, out_b, map(x, in_a, in_b));
	}
	
	//// angle stuff
	
	fv4 to_rad (fv4 deg) {
		return (fv4)deg * DEG_TO_RAD;
	}
	
	fv4 deg (fv4 deg) {
		return (fv4)deg * DEG_TO_RAD;
	}
	
	fv4 to_deg (fv4 rad) {
		return (fv4)rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	f32 length (fv4 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
	}
	
	f32 length_sqr (fv4 v) {
		return v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w;
	}
	
	f32 distance (fv4 a, fv4 b) {
		return length(a - b);
	}
	
	fv4 normalize (fv4 v) {
		return fv4(v) / length(v);
	}
	
	fv4 normalize_or_zero (fv4 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv4(v) / fv4(len);
	}
	
	f32 dot (fv4 l, fv4 r) {
		return l.x * r.x + l.y * r.y + l.z * r.z + l.w * r.w;
	}
}// namespace vector

