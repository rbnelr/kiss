// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "transformations.hpp"

namespace vector {
	
	
	fm2 scale (fv2 v) {
		return fm2(
				v.x,   0,
				  0, v.y
		);
	}
	
	fm2x3 translate (fv2 v) {
		return fm2x3(
				1, 0, v.x,
				0, 1, v.y
		);
	}
	
	
	fm3 scale (fv3 v) {
		return fm3(
				v.x,   0,   0,
				  0, v.y,   0,
				  0,   0, v.z
		);
	}
	
	fm3x4 translate (fv3 v) {
		return fm3x4(
				1, 0, 0, v.x,
				0, 1, 0, v.y,
				0, 0, 1, v.z
		);
	}
} // namespace vector

