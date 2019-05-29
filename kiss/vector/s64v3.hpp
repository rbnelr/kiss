// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	struct s64v2;
	struct s64v4;
	struct bv3;
	struct bv3;
	struct fv3;
	struct dv3;
	struct iv3;
	struct u8v3;
	
	struct s64v3 {
		union {
			struct {
				s64	x, y, z;
			};
			s64		arr[3];
		};
		
		inline FORCEINLINE s64& operator[] (int i) {
			return arr[i];
		}
		
		inline FORCEINLINE s64 const& operator[] (int i) const {
			return arr[i];
		}
		
		
		inline FORCEINLINE s64v3 () {
			
		}
		
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		inline FORCEINLINE s64v3 (s64 all): x{all}, y{all}, z{all} {
			
		}
		
		// supply all components
		inline FORCEINLINE s64v3 (s64 x, s64 y, s64 z): x{x}, y{y}, z{z} {
			
		}
		// extend vector
		s64v3 (s64v2 xy, s64 z);
		// truncate vector
		s64v3 (s64v4 v);
		
		//// Truncating cast operators
		
		explicit operator s64v2 () const;
		
		//// Type cast operators
		
		explicit operator bv3 () const;
		explicit operator fv3 () const;
		explicit operator dv3 () const;
		explicit operator iv3 () const;
		explicit operator u8v3 () const;
		
		
		inline FORCEINLINE s64v3 operator+= (s64v3 r) {
			x += r.x;
			y += r.y;
			z += r.z;
			return *this;
		}
		
		inline FORCEINLINE s64v3 operator-= (s64v3 r) {
			x -= r.x;
			y -= r.y;
			z -= r.z;
			return *this;
		}
		
		inline FORCEINLINE s64v3 operator*= (s64v3 r) {
			x *= r.x;
			y *= r.y;
			z *= r.z;
			return *this;
		}
		
		inline FORCEINLINE s64v3 operator/= (s64v3 r) {
			x /= r.x;
			y /= r.y;
			z /= r.z;
			return *this;
		}
	};
	
	//// arthmethic ops
	
	inline FORCEINLINE s64v3 operator+ (s64v3 v) {
		return s64v3(+v.x, +v.y, +v.z);
	}
	
	inline FORCEINLINE s64v3 operator- (s64v3 v) {
		return s64v3(-v.x, -v.y, -v.z);
	}
	
	inline FORCEINLINE s64v3 operator+ (s64v3 l, s64v3 r) {
		return s64v3(l.x + r.x, l.y + r.y, l.z + r.z);
	}
	
	inline FORCEINLINE s64v3 operator- (s64v3 l, s64v3 r) {
		return s64v3(l.x - r.x, l.y - r.y, l.z - r.z);
	}
	
	inline FORCEINLINE s64v3 operator* (s64v3 l, s64v3 r) {
		return s64v3(l.x * r.x, l.y * r.y, l.z * r.z);
	}
	
	inline FORCEINLINE s64v3 operator/ (s64v3 l, s64v3 r) {
		return s64v3(l.x / r.x, l.y / r.y, l.z / r.z);
	}
	
	//// comparison ops
	bv3 operator< (s64v3 l, s64v3 r);
	bv3 operator<= (s64v3 l, s64v3 r);
	bv3 operator> (s64v3 l, s64v3 r);
	bv3 operator>= (s64v3 l, s64v3 r);
	bv3 operator== (s64v3 l, s64v3 r);
	bv3 operator!= (s64v3 l, s64v3 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (s64v3 l, s64v3 r);
	// componentwise ternary c ? l : r
	s64v3 select (bv3 c, s64v3 l, s64v3 r);
	
	//// misc ops
	
	inline FORCEINLINE s64v3 abs (s64v3 v) {
		return s64v3(abs(v.x), abs(v.y), abs(v.z));
	}
	
	inline FORCEINLINE s64v3 min (s64v3 l, s64v3 r) {
		return s64v3(min(l.x,r.x), min(l.y,r.y), min(l.z,r.z));
	}
	
	inline FORCEINLINE s64v3 max (s64v3 l, s64v3 r) {
		return s64v3(max(l.x,r.x), max(l.y,r.y), max(l.z,r.z));
	}
	s64v3 clamp (s64v3 x, s64v3 a=s64v3(0), s64v3 b=s64v3(1));
	// get min component of vector, optionally get component index via min_index
	s64 min_component (s64v3 v, int* min_index=nullptr);
	// get max component of vector, optionally get component index via max_index
	s64 max_component (s64v3 v, int* max_index=nullptr);
	
	
	inline FORCEINLINE s64v3 wrap (s64v3 v, s64v3 range) {
		return s64v3(wrap(v.x,range.x), wrap(v.y,range.y), wrap(v.z,range.z));
	}
	
	inline FORCEINLINE s64v3 wrap (s64v3 v, s64v3 a, s64v3 b) {
		return s64v3(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y), wrap(v.z,a.z,b.z));
	}
	
	dv3 to_rad (s64v3 deg);
	// degress "literal", converts degrees to radiants
	dv3 deg (s64v3 deg);
	dv3 to_deg (s64v3 rad);
	
	//// linear algebra ops
	// magnitude of vector
	f64 length (s64v3 v);
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	s64 length_sqr (s64v3 v);
	// distance between points, equivalent to length(a - b)
	f64 distance (s64v3 a, s64v3 b);
	// normalize vector so that it has length() = 1, undefined for zero vector
	dv3 normalize (s64v3 v);
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	dv3 normalize_or_zero (s64v3 v);
	// dot product
	s64 dot (s64v3 l, s64v3 r);
	// 3d cross product
	s64v3 cross (s64v3 l, s64v3 r);
}// namespace vector

