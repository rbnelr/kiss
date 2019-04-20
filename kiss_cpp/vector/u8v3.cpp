// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "u8v3.hpp"

#include "u8v2.hpp"
#include "u8v4.hpp"
#include "bv3.hpp"
#include "bv3.hpp"
#include "fv3.hpp"
#include "dv3.hpp"
#include "iv3.hpp"
#include "s64v3.hpp"

namespace vector {
	
	u8& u8v3::operator[] (int i) {
		return arr[i];
	}
	
	u8 const& u8v3::operator[] (int i) const {
		return arr[i];
	}
	
	
	u8v3::u8v3 () {
		
	}
	
	// sets all components to one value
	// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
	u8v3::u8v3 (u8 all): x{all}, y{all}, z{all} {
		
	}
	
	// supply all components
	u8v3::u8v3 (u8 x, u8 y, u8 z): x{x}, y{y}, z{z} {
		
	}
	
	// extend vector
	u8v3::u8v3 (u8v2 xy, u8 z): x{xy.x}, y{xy.y}, z{z} {
		
	}
	
	// truncate vector
	u8v3::u8v3 (u8v4 v): x{v.x}, y{v.y}, z{v.z} {
		
	}
	
	//// Truncating cast operators
	
	
	u8v3::operator u8v2 () const {
		return u8v2(x, y);
	}
	
	//// Type cast operators
	
	
	u8v3::operator bv3 () const {
		return bv3((bool)x, (bool)y, (bool)z);
	}
	
	u8v3::operator fv3 () const {
		return fv3((f32)x, (f32)y, (f32)z);
	}
	
	u8v3::operator dv3 () const {
		return dv3((f64)x, (f64)y, (f64)z);
	}
	
	u8v3::operator iv3 () const {
		return iv3((s32)x, (s32)y, (s32)z);
	}
	
	u8v3::operator s64v3 () const {
		return s64v3((s64)x, (s64)y, (s64)z);
	}
	
	
	u8v3 u8v3::operator+= (u8v3 r) {
		x += r.x;
		y += r.y;
		z += r.z;
		return *this;
	}
	
	u8v3 u8v3::operator-= (u8v3 r) {
		x -= r.x;
		y -= r.y;
		z -= r.z;
		return *this;
	}
	
	u8v3 u8v3::operator*= (u8v3 r) {
		x *= r.x;
		y *= r.y;
		z *= r.z;
		return *this;
	}
	
	u8v3 u8v3::operator/= (u8v3 r) {
		x /= r.x;
		y /= r.y;
		z /= r.z;
		return *this;
	}
	
	//// arthmethic ops
	
	u8v3 operator+ (u8v3 v) {
		return u8v3(+v.x, +v.y, +v.z);
	}
	
	u8v3 operator- (u8v3 v) {
		return u8v3(-v.x, -v.y, -v.z);
	}
	
	u8v3 operator+ (u8v3 l, u8v3 r) {
		return u8v3(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	
	u8v3 operator- (u8v3 l, u8v3 r) {
		return u8v3(l.x - r.x, l.y - r.y, l.z - r.z);
	}
	
	u8v3 operator* (u8v3 l, u8v3 r) {
		return u8v3(l.x * r.x, l.y * r.y, l.z * r.z);
	}
	
	u8v3 operator/ (u8v3 l, u8v3 r) {
		return u8v3(l.x / r.x, l.y / r.y, l.z / r.z);
	}
	
	//// comparison ops
	
	bv3 operator< (u8v3 l, u8v3 r) {
		return bv3(l.x < r.x, l.y < r.y, l.z < r.z);
	}
	
	bv3 operator<= (u8v3 l, u8v3 r) {
		return bv3(l.x <= r.x, l.y <= r.y, l.z <= r.z);
	}
	
	bv3 operator> (u8v3 l, u8v3 r) {
		return bv3(l.x > r.x, l.y > r.y, l.z > r.z);
	}
	
	bv3 operator>= (u8v3 l, u8v3 r) {
		return bv3(l.x >= r.x, l.y >= r.y, l.z >= r.z);
	}
	
	bv3 operator== (u8v3 l, u8v3 r) {
		return bv3(l.x == r.x, l.y == r.y, l.z == r.z);
	}
	
	bv3 operator!= (u8v3 l, u8v3 r) {
		return bv3(l.x != r.x, l.y != r.y, l.z != r.z);
	}
	
	// vectors are equal, equivalent to all(l == r)
	bool equal (u8v3 l, u8v3 r) {
		return all(l == r);
	}
	
	// componentwise ternary c ? l : r
	u8v3 select (bv3 c, u8v3 l, u8v3 r) {
		return c.x ? l.x : r.x, c.y ? l.y : r.y, c.z ? l.z : r.z;
	}
	
	//// misc ops
	
	u8v3 abs (u8v3 v) {
		return u8v3(abs(v.x), abs(v.y), abs(v.z));
	}
	
	u8v3 min (u8v3 l, u8v3 r) {
		return u8v3(min(l.x,r.x), min(l.y,r.y), min(l.z,r.z));
	}
	
	u8v3 max (u8v3 l, u8v3 r) {
		return u8v3(max(l.x,r.x), max(l.y,r.y), max(l.z,r.z));
	}
	
	u8v3 clamp (u8v3 x, u8v3 a, u8v3 b) {
		return min(max(x,a), b);
	}
	
	// get min component of vector, optionally get component index via min_index
	u8 min_component (u8v3 v, int* min_index) {
		int index = 0;
		u8 min_val = v.x;	
		for (int i=1; i<3; ++i) {
			if (v.arr[i] <= min_val) {
				index = i;
				min_val = v.arr[i];
			}
		}
		if (min_index) *min_index = index;
		return min_val;
	}
	
	// get max component of vector, optionally get component index via max_index
	u8 max_component (u8v3 v, int* max_index) {
		int index = 0;
		u8 max_val = v.x;	
		for (int i=1; i<3; ++i) {
			if (v.arr[i] >= max_val) {
				index = i;
				max_val = v.arr[i];
			}
		}
		if (max_index) *max_index = index;
		return max_val;
	}
	
	
	u8v3 wrap (u8v3 v, u8v3 range) {
		return u8v3(wrap(v.x,range.x), wrap(v.y,range.y), wrap(v.z,range.z));
	}
	
	u8v3 wrap (u8v3 v, u8v3 a, u8v3 b) {
		return u8v3(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y), wrap(v.z,a.z,b.z));
	}
	
	
	fv3 to_rad (u8v3 deg) {
		return (fv3)deg * DEG_TO_RAD;
	}
	
	// degress "literal", converts degrees to radiants
	fv3 deg (u8v3 deg) {
		return (fv3)deg * DEG_TO_RAD;
	}
	
	fv3 to_deg (u8v3 rad) {
		return (fv3)rad * RAD_TO_DEG;
	}
	
	//// linear algebra ops
	
	// magnitude of vector
	f32 length (u8v3 v) {
		return sqrt((f32)(v.x * v.x + v.y * v.y + v.z * v.z));
	}
	
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	u8 length_sqr (u8v3 v) {
		return v.x * v.x + v.y * v.y + v.z * v.z;
	}
	
	// distance between points, equivalent to length(a - b)
	f32 distance (u8v3 a, u8v3 b) {
		return length(a - b);
	}
	
	// normalize vector so that it has length() = 1, undefined for zero vector
	fv3 normalize (u8v3 v) {
		return fv3(v) / length(v);
	}
	
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	fv3 normalize_or_zero (u8v3 v) {
		f32 len = length(v);
		if (len == f32(0)) {
			return f32(0);
		}
		return fv3(v) / fv3(len);
	}
	
	// dot product
	u8 dot (u8v3 l, u8v3 r) {
		return l.x * r.x + l.y * r.y + l.z * r.z;
	}
	
	// 3d cross product
	u8v3 cross (u8v3 l, u8v3 r) {
		return u8v3(
				l.y * r.z - l.z * r.y,
				l.z * r.x - l.x * r.z,
				l.x * r.y - l.y * r.x);
	}
}// namespace vector

