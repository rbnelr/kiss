// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	union fv2;
	union fv3;
	union bv4;
	union bv4;
	union dv4;
	union iv4;
	union s64v4;
	union u8v4;
	
	union fv4 {
		struct {
			f32	x, y, z, w;
		};
		f32		arr[4];
		
		
		inline FORCEINLINE f32& operator[] (int i) {
			return arr[i];
		}
		
		inline FORCEINLINE f32 const& operator[] (int i) const {
			return arr[i];
		}
		
		
		inline FORCEINLINE fv4 () {
			
		}
		
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		inline FORCEINLINE fv4 (f32 all): x{all}, y{all}, z{all}, w{all} {
			
		}
		
		// supply all components
		inline FORCEINLINE fv4 (f32 x, f32 y, f32 z, f32 w): x{x}, y{y}, z{z}, w{w} {
			
		}
		// extend vector
		fv4 (fv2 xy, f32 z, f32 w);
		// extend vector
		fv4 (fv3 xyz, f32 w);
		
		//// Truncating cast operators
		
		explicit operator fv2 () const;
		explicit operator fv3 () const;
		
		//// Type cast operators
		
		explicit operator bv4 () const;
		explicit operator dv4 () const;
		explicit operator iv4 () const;
		explicit operator s64v4 () const;
		explicit operator u8v4 () const;
		
		
		inline FORCEINLINE fv4 operator+= (fv4 r) {
			x += r.x;
			y += r.y;
			z += r.z;
			w += r.w;
			return *this;
		}
		
		inline FORCEINLINE fv4 operator-= (fv4 r) {
			x -= r.x;
			y -= r.y;
			z -= r.z;
			w -= r.w;
			return *this;
		}
		
		inline FORCEINLINE fv4 operator*= (fv4 r) {
			x *= r.x;
			y *= r.y;
			z *= r.z;
			w *= r.w;
			return *this;
		}
		
		inline FORCEINLINE fv4 operator/= (fv4 r) {
			x /= r.x;
			y /= r.y;
			z /= r.z;
			w /= r.w;
			return *this;
		}
	};
	
	//// arthmethic ops
	
	inline FORCEINLINE fv4 operator+ (fv4 v) {
		return fv4(+v.x, +v.y, +v.z, +v.w);
	}
	
	inline FORCEINLINE fv4 operator- (fv4 v) {
		return fv4(-v.x, -v.y, -v.z, -v.w);
	}
	
	inline FORCEINLINE fv4 operator+ (fv4 l, fv4 r) {
		return fv4(l.x + r.x, l.y + r.y, l.z + r.z, l.w + r.w);
	}
	
	inline FORCEINLINE fv4 operator- (fv4 l, fv4 r) {
		return fv4(l.x - r.x, l.y - r.y, l.z - r.z, l.w - r.w);
	}
	
	inline FORCEINLINE fv4 operator* (fv4 l, fv4 r) {
		return fv4(l.x * r.x, l.y * r.y, l.z * r.z, l.w * r.w);
	}
	
	inline FORCEINLINE fv4 operator/ (fv4 l, fv4 r) {
		return fv4(l.x / r.x, l.y / r.y, l.z / r.z, l.w / r.w);
	}
	
	//// comparison ops
	bv4 operator< (fv4 l, fv4 r);
	bv4 operator<= (fv4 l, fv4 r);
	bv4 operator> (fv4 l, fv4 r);
	bv4 operator>= (fv4 l, fv4 r);
	bv4 operator== (fv4 l, fv4 r);
	bv4 operator!= (fv4 l, fv4 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (fv4 l, fv4 r);
	// componentwise ternary c ? l : r
	fv4 select (bv4 c, fv4 l, fv4 r);
	
	//// misc ops
	
	inline FORCEINLINE fv4 abs (fv4 v) {
		return fv4(abs(v.x), abs(v.y), abs(v.z), abs(v.w));
	}
	
	inline FORCEINLINE fv4 min (fv4 l, fv4 r) {
		return fv4(min(l.x,r.x), min(l.y,r.y), min(l.z,r.z), min(l.w,r.w));
	}
	
	inline FORCEINLINE fv4 max (fv4 l, fv4 r) {
		return fv4(max(l.x,r.x), max(l.y,r.y), max(l.z,r.z), max(l.w,r.w));
	}
	fv4 clamp (fv4 x, fv4 a=fv4(0), fv4 b=fv4(1));
	// get min component of vector, optionally get component index via min_index
	f32 min_component (fv4 v, int* min_index=nullptr);
	// get max component of vector, optionally get component index via max_index
	f32 max_component (fv4 v, int* max_index=nullptr);
	
	
	inline FORCEINLINE fv4 floor (fv4 v) {
		return fv4(floor(v.x), floor(v.y), floor(v.z), floor(v.w));
	}
	
	inline FORCEINLINE fv4 ceil (fv4 v) {
		return fv4(ceil(v.x), ceil(v.y), ceil(v.z), ceil(v.w));
	}
	
	inline FORCEINLINE fv4 round (fv4 v) {
		return fv4(round(v.x), round(v.y), round(v.z), round(v.w));
	}
	iv4 floori (fv4 v);
	iv4 ceili (fv4 v);
	iv4 roundi (fv4 v);
	
	inline FORCEINLINE fv4 pow (fv4 v, fv4 e) {
		return fv4(pow(v.x,e.x), pow(v.y,e.y), pow(v.z,e.z), pow(v.w,e.w));
	}
	
	inline FORCEINLINE fv4 wrap (fv4 v, fv4 range) {
		return fv4(wrap(v.x,range.x), wrap(v.y,range.y), wrap(v.z,range.z), wrap(v.w,range.w));
	}
	
	inline FORCEINLINE fv4 wrap (fv4 v, fv4 a, fv4 b) {
		return fv4(wrap(v.x,a.x,b.x), wrap(v.y,a.y,b.y), wrap(v.z,a.z,b.z), wrap(v.w,a.w,b.w));
	}
	
	// linear interpolation t=0 -> a ; t=1 -> b ; t=0.5 -> (a+b)/2
	fv4 lerp (fv4 a, fv4 b, fv4 t);
	// linear mapping (reverse linear interpolation), map(70, 0,100) -> 0.7 ; map(0.5, -1,+1) -> 0.75
	fv4 map (fv4 x, fv4 in_a, fv4 in_b);
	// linear mapping, lerp(out_a, out_b, map(x, in_a, in_b))
	fv4 map (fv4 x, fv4 in_a, fv4 in_b, fv4 out_a, fv4 out_b);
	
	//// angle stuff
	fv4 to_rad (fv4 deg);
	// degress "literal", converts degrees to radiants
	fv4 deg (fv4 deg);
	fv4 to_deg (fv4 rad);
	
	//// linear algebra ops
	// magnitude of vector
	f32 length (fv4 v);
	// squared magnitude of vector, cheaper than length() because it avoids the sqrt(), some algorithms only need the squared magnitude
	f32 length_sqr (fv4 v);
	// distance between points, equivalent to length(a - b)
	f32 distance (fv4 a, fv4 b);
	// normalize vector so that it has length() = 1, undefined for zero vector
	fv4 normalize (fv4 v);
	// normalize vector so that it has length() = 1, returns zero vector if vector was zero vector
	fv4 normalize_or_zero (fv4 v);
	// dot product
	f32 dot (fv4 l, fv4 r);
}// namespace vector

