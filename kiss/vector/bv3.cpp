// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "bv3.hpp"

#include "bv2.hpp"
#include "bv4.hpp"
#include "bv3.hpp"
#include "fv3.hpp"
#include "dv3.hpp"
#include "iv3.hpp"
#include "s64v3.hpp"
#include "u8v3.hpp"

namespace vector {
	
	
	// extend vector
	bv3::bv3 (bv2 xy, bool z): x{xy.x}, y{xy.y}, z{z} {
		
	}
	
	// truncate vector
	bv3::bv3 (bv4 v): x{v.x}, y{v.y}, z{v.z} {
		
	}
	
	//// Truncating cast operators
	
	
	bv3::operator bv2 () const {
		return bv2(x, y);
	}
	
	//// Type cast operators
	
	
	//// reducing ops
	
	// all components are true
	bool all (bv3 v) {
		return v.x && v.y && v.z;
	}
	
	// any components is true
	bool any (bv3 v) {
		return v.x || v.y || v.z;
	}
	
	//// arthmethic ops
	
	//// comparison ops
	
	bv3 operator== (bv3 l, bv3 r) {
		return bv3(l.x == r.x, l.y == r.y, l.z == r.z);
	}
	
	bv3 operator!= (bv3 l, bv3 r) {
		return bv3(l.x != r.x, l.y != r.y, l.z != r.z);
	}
	
	// vectors are equal, equivalent to all(l == r)
	bool equal (bv3 l, bv3 r) {
		return all(l == r);
	}
	
	// componentwise ternary c ? l : r
	bv3 select (bv3 c, bv3 l, bv3 r) {
		return bv3(c.x ? l.x : r.x, c.y ? l.y : r.y, c.z ? l.z : r.z);
	}
}// namespace vector

