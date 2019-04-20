// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


namespace vector {
	//// forward declarations
	union bv3;
	union bv4;
	union bv2;
	union fv2;
	union dv2;
	union iv2;
	union s64v2;
	union u8v2;
	
	union bv2 {
		struct {
			bool	x, y;
		};
		bool		arr[2];
		
		
		inline FORCEINLINE bool& operator[] (int i) {
			return arr[i];
		}
		
		inline FORCEINLINE bool const& operator[] (int i) const {
			return arr[i];
		}
		
		
		inline FORCEINLINE bv2 () {
			
		}
		
		// sets all components to one value
		// implicit constructor -> v3(x,y,z) * 5 will be turned into v3(x,y,z) * v3(5) by to compiler to be able to execute operator*(v3, v3), which is desirable, also v3 a = 0; works
		inline FORCEINLINE bv2 (bool all): x{all}, y{all} {
			
		}
		
		// supply all components
		inline FORCEINLINE bv2 (bool x, bool y): x{x}, y{y} {
			
		}
		// truncate vector
		bv2 (bv3 v);
		// truncate vector
		bv2 (bv4 v);
		
		//// Truncating cast operators
		
		
		//// Type cast operators
		
	};
	
	//// reducing ops
	// all components are true
	bool all (bv2 v);
	// any components is true
	bool any (bv2 v);
	
	//// arthmethic ops
	
	inline FORCEINLINE bv2 operator! (bv2 v) {
		return bv2(!v.x, !v.y);
	}
	
	inline FORCEINLINE bv2 operator&& (bv2 l, bv2 r) {
		return bv2(l.x && r.x, l.y && r.y);
	}
	
	inline FORCEINLINE bv2 operator|| (bv2 l, bv2 r) {
		return bv2(l.x || r.x, l.y || r.y);
	}
	
	//// comparison ops
	bv2 operator== (bv2 l, bv2 r);
	bv2 operator!= (bv2 l, bv2 r);
	// vectors are equal, equivalent to all(l == r)
	bool equal (bv2 l, bv2 r);
	// componentwise ternary c ? l : r
	bv2 select (bv2 c, bv2 l, bv2 r);
}// namespace vector

