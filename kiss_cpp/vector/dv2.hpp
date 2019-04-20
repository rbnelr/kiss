// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	union dv3;
	union dv4;
	union bv2;
	union bv2;
	union fv2;
	union iv2;
	union s64v2;
	union u8v2;
	
	union dv2 {
		struct {
			f64	x, y;
		};
		f64		arr[2];
		
		
		inline FORCEINLINE f64& operator[] (int i) {
			return arr[i];
		}
		
		inline FORCEINLINE f64 const& operator[] (int i) const {
			return arr[i];
		}
		
		
		inline FORCEINLINE dv2 () {
			
		}
		
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		inline FORCEINLINE dv2 (f64 all): x{all}, y{all} {
			
		}
		
		// supply all components
		inline FORCEINLINE dv2 (f64 x, f64 y): x{x}, y{y} {
			
		}
		// truncate vector
		dv2 (dv3 v);
		// truncate vector
		dv2 (dv4 v);
		
		//// Truncating cast operators
		
		
		//// Type cast operators
		
		explicit operator bv2 () const;
		explicit operator fv2 () const;
		explicit operator iv2 () const;
		explicit operator s64v2 () const;
		explicit operator u8v2 () const;
		
		
		inline FORCEINLINE dv2 operator+= (dv2 r) {
			x += r.x;
			y += r.y;
			return *this;
		}
		
		inline FORCEINLINE dv2 operator-= (dv2 r) {
			x -= r.x;
			y -= r.y;
			return *this;
		}
		
		inline FORCEINLINE dv2 operator*= (dv2 r) {
			x *= r.x;
			y *= r.y;
			return *this;
		}
		
		inline FORCEINLINE dv2 operator/= (dv2 r) {
			x /= r.x;
			y /= r.y;
			return *this;
		}
	};
	
	//// arthmethic ops
	
	inline FORCEINLINE dv2 operator+ (dv2 v) {
		return dv2(+v.x, +v.y);
	}
	
	inline FORCEINLINE dv2 operator- (dv2 v) {
		return dv2(-v.x, -v.y);
	}
	
	inline FORCEINLINE dv2 operator+ (dv2 l, dv2 r) {
		return dv2(l.x + r.x, l.y + r.y);
	}
	
	inline FORCEINLINE dv2 operator- (dv2 l, dv2 r) {
		return dv2(l.x - r.x, l.y - r.y);
	}
	
	inline FORCEINLINE dv2 operator* (dv2 l, dv2 r) {
		return dv2(l.x * r.x, l.y * r.y);
	}
	
	inline FORCEINLINE dv2 operator/ (dv2 l, dv2 r) {
		return dv2(l.x / r.x, l.y / r.y);
	}
	
	//// comparison ops
	bv2 operator< (dv2 l, dv2 r);
	bv2 operator<= (dv2 l, dv2 r);
	bv2 operator> (dv2 l, dv2 r);
	bv2 operator>= (dv2 l, dv2 r);
	bv2 operator== (dv2 l, dv2 r);
	bv2 operator!= (dv2 l, dv2 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (dv2 l, dv2 r);
	// componentwise ternary c ? l : r
	dv2 select (bv2 c, dv2 l, dv2 r);
	
	//// misc ops
	
	inline FORCEINLINE dv2 abs (dv2 v) {
		return dv2(abs(v.x), abs(v.y));
	}
	
	inline FORCEINLINE dv2 min (dv2 l, dv2 r) {
		return dv2(min(l.x,r.x), min(l.y,r.y));
	}
	
	inline FORCEINLINE dv2 max (dv2 l, dv2 r) {
		return dv2(max(l.x,r.x), max(l.y,r.y));
	}
	dv2 clamp (dv2 x, dv2 a=dv2(0), dv2 b=dv2(1));
	// get min component of vector, optionally get component index via min_index
	f64 min_component (dv2 v, int* min_index=nullptr);
	// get max component of vector, optionally get component index via max_index
	f64 max_component (dv2 v, int* max_index=nullptr);
	
	
	inline FORCEINLINE dv2 floor (dv2 v) {
		return dv2(floor(v.x), floor(v.y));
	}
	
	inline FORCEINLINE dv2 ceil (dv2 v) {
		return dv2(ceil(v.x), ceil(v.y));
	}
	
	inline FORCEINLINE dv2 round (dv2 v) {
		return dv2(round(v.x), round(v.y));
	}
	s64v2 floori (dv2 v);
	s64v2 ceili (dv2 v);
	s64v2 roundi (dv2 v);
	
	inline FORCEINLINE dv2 pow (dv2 v, dv2 e) {
		return dv2(pow(v.x,e.x), pow(v.y,e.y));
	}
	
	inline FORCEINLINE dv2 wrap (dv2 v, dv2 range) {
		return dv2(wrap(v.x,range.x), wrap(v.y,range.y));
	}
	
	inline FORCEINLINE dv2 wrap (dv2 v, dv2 a, dv2 b) {
		return dv2(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y));
	}
	
	// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
	dv2 lerp (dv2 a, dv2 b, dv2 t);
	// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
	dv2 map (dv2 x, dv2 in_a, dv2 in_b);
	// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
	dv2 map (dv2 x, dv2 in_a, dv2 in_b, dv2 out_a, dv2 out_b);
	
	//// angle stuff
	dv2 to_rad (dv2 deg);
	// degress "literal", converts degrees to radiants
	dv2 deg (dv2 deg);
	dv2 to_deg (dv2 rad);
	
	//// linear algebra ops
	// magnitude of vector
	f64 length (dv2 v);
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	f64 length_sqr (dv2 v);
	// distance between points, equivalent to length(a - b)
	f64 distance (dv2 a, dv2 b);
	// normalize vector so that it has length() = 1, undefined for zero vector
	dv2 normalize (dv2 v);
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	dv2 normalize_or_zero (dv2 v);
	// dot product
	f64 dot (dv2 l, dv2 r);
	// 
	// 2d cross product hack for convinient 2d stuff
	// same as cross(v3(l, 0), v3(r, 0)).z,
	// ie. the cross product of the 2d vectors on the z=0 plane in 3d space and then return the z coord of that (signed mag of cross product)
	// 
	f64 cross (dv2 l, dv2 r);
	// rotate 2d vector counterclockwise 90 deg, ie. dv2(-y, x) which is fast
	dv2 rotate90 (dv2 v);
}// namespace vector

