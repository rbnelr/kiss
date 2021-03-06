// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "dm2.hpp"

#include "dm3.hpp"
#include "dm4.hpp"
#include "dm2x3.hpp"
#include "dm3x4.hpp"
#include "fm2.hpp"

namespace vector {
	
	//// Accessors
	
	
	// get matrix row
	dv2 dm2::get_row (int indx) const {
		return dv2(arr[0][indx], arr[1][indx]);
	}
	
	//// Constructors
	
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	// supply all row vectors
	dm2 dm2::rows (dv2 row0, dv2 row1) {
		return dm2(row0[0], row0[1],
				   row1[0], row1[1]);
	}
	
	// supply all cells in row major order
	dm2 dm2::rows (f64 c00, f64 c01,
				   f64 c10, f64 c11) {
		return dm2(c00, c01,
				   c10, c11);
	}
	
	// supply all column vectors
	dm2 dm2::columns (dv2 col0, dv2 col1) {
		return dm2(col0[0], col1[0],
				   col0[1], col1[1]);
	}
	
	// supply all cells in column major order
	dm2 dm2::columns (f64 c00, f64 c10,
					  f64 c01, f64 c11) {
		return dm2(c00, c01,
				   c10, c11);
	}
	
	
	// Casting operators
	
	
	// extend/truncate matrix of other size
	dm2::operator dm3 () const {
		return dm3(arr[0][0], arr[1][0],         0,
				   arr[0][1], arr[1][1],         0,
				           0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	dm2::operator dm4 () const {
		return dm4(arr[0][0], arr[1][0],         0,         0,
				   arr[0][1], arr[1][1],         0,         0,
				           0,         0,         1,         0,
				           0,         0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	dm2::operator dm2x3 () const {
		return dm2x3(arr[0][0], arr[1][0],         0,
					 arr[0][1], arr[1][1],         0);
	}
	
	// extend/truncate matrix of other size
	dm2::operator dm3x4 () const {
		return dm3x4(arr[0][0], arr[1][0],         0,         0,
					 arr[0][1], arr[1][1],         0,         0,
					         0,         0,         1,         0);
	}
	
	// typecast
	dm2::operator fm2 () const {
		return fm2((f32)arr[0][0], (f32)arr[0][1],
				   (f32)arr[1][0], (f32)arr[1][1]);
	}
	
	// Elementwise operators
	
	
	dm2& dm2::operator+= (f64 r) {
		*this = *this + r;
		return *this;
	}
	
	dm2& dm2::operator-= (f64 r) {
		*this = *this - r;
		return *this;
	}
	
	dm2& dm2::operator*= (f64 r) {
		*this = *this * r;
		return *this;
	}
	
	dm2& dm2::operator/= (f64 r) {
		*this = *this / r;
		return *this;
	}
	
	// Matrix multiplication
	
	
	dm2& dm2::operator*= (dm2 const& r) {
		*this = *this * r;
		return *this;
	}
	
	// Elementwise operators
	
	
	dm2 operator+ (dm2 const& m) {
		return dm2(+m.arr[0][0], +m.arr[1][0],
				   +m.arr[0][1], +m.arr[1][1]);
	}
	
	dm2 operator- (dm2 const& m) {
		return dm2(-m.arr[0][0], -m.arr[1][0],
				   -m.arr[0][1], -m.arr[1][1]);
	}
	
	
	dm2 operator+ (dm2 const& l, dm2 const& r) {
		return dm2(l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0],
				   l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1]);
	}
	
	dm2 operator+ (dm2 const& l, f64 r) {
		return dm2(l.arr[0][0] + r, l.arr[1][0] + r,
				   l.arr[0][1] + r, l.arr[1][1] + r);
	}
	
	dm2 operator+ (f64 l, dm2 const& r) {
		return dm2(l + r.arr[0][0], l + r.arr[1][0],
				   l + r.arr[0][1], l + r.arr[1][1]);
	}
	
	
	dm2 operator- (dm2 const& l, dm2 const& r) {
		return dm2(l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0],
				   l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1]);
	}
	
	dm2 operator- (dm2 const& l, f64 r) {
		return dm2(l.arr[0][0] - r, l.arr[1][0] - r,
				   l.arr[0][1] - r, l.arr[1][1] - r);
	}
	
	dm2 operator- (f64 l, dm2 const& r) {
		return dm2(l - r.arr[0][0], l - r.arr[1][0],
				   l - r.arr[0][1], l - r.arr[1][1]);
	}
	
	
	dm2 mul_elementwise (dm2 const& l, dm2 const& r) {
		return dm2(l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0],
				   l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1]);
	}
	
	dm2 operator* (dm2 const& l, f64 r) {
		return dm2(l.arr[0][0] * r, l.arr[1][0] * r,
				   l.arr[0][1] * r, l.arr[1][1] * r);
	}
	
	dm2 operator* (f64 l, dm2 const& r) {
		return dm2(l * r.arr[0][0], l * r.arr[1][0],
				   l * r.arr[0][1], l * r.arr[1][1]);
	}
	
	
	dm2 div_elementwise (dm2 const& l, dm2 const& r) {
		return dm2(l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0],
				   l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1]);
	}
	
	dm2 operator/ (dm2 const& l, f64 r) {
		return dm2(l.arr[0][0] / r, l.arr[1][0] / r,
				   l.arr[0][1] / r, l.arr[1][1] / r);
	}
	
	dm2 operator/ (f64 l, dm2 const& r) {
		return dm2(l / r.arr[0][0], l / r.arr[1][0],
				   l / r.arr[0][1], l / r.arr[1][1]);
	}
	
	// Matrix ops
	
	
	dm2 operator* (dm2 const& l, dm2 const& r) {
		dm2 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		return ret;
	}
	
	dm2x3 operator* (dm2 const& l, dm2x3 const& r) {
		dm2x3 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		ret.arr[2] = l * r.arr[2];
		return ret;
	}
	
	dv2 operator* (dm2 const& l, dv2 r) {
		dv2 ret;
		ret.x = l.arr[0].x * r.x + l.arr[1].x * r.y;
		ret.y = l.arr[0].y * r.x + l.arr[1].y * r.y;
		return ret;
	}
	
	dv2 operator* (dv2 l, dm2 const& r) {
		dv2 ret;
		ret.x = l.x * r.arr[0].x + l.y * r.arr[0].y;
		ret.y = l.x * r.arr[1].x + l.y * r.arr[1].y;
		return ret;
	}
	
	dm2 transpose (dm2 const& m) {
		return dm2::rows(m.arr[0], m.arr[1]);
	}
	
	#define LETTERIFY \
	f64 a = mat.arr[0][0]; \
	f64 b = mat.arr[0][1]; \
	f64 c = mat.arr[1][0]; \
	f64 d = mat.arr[1][1];
	
	f64 det (dm2 const& mat) {
		// optimized from:  // 2 muls, 1 adds, 0 divs = 3 ops
		// to:              // 2 muls, 1 adds, 0 divs = 3 ops
		LETTERIFY
		
		return a*d - b*c;
	}
	
	dm2 inverse (dm2 const& mat) {
		// optimized from:  // 6 muls, 2 adds, 1 divs = 9 ops
		// to:              // 6 muls, 2 adds, 1 divs = 9 ops
		LETTERIFY
		
		f64 det;
		{ // clac determinate
			det = a*d - b*c;
		}
		f64 inv_det = f64(1) / det;
		f64 ninv_det = -inv_det;
		
		// calc cofactor matrix
		
		f64 cofac_00 = d;
		f64 cofac_01 = c;
		f64 cofac_10 = b;
		f64 cofac_11 = a;
		
		dm2 ret;
		
		ret.arr[0][0] = cofac_00 *  inv_det;
		ret.arr[0][1] = cofac_10 * ninv_det;
		ret.arr[1][0] = cofac_01 * ninv_det;
		ret.arr[1][1] = cofac_11 *  inv_det;
		
		return ret;
	}
	
	#undef LETTERIFY
	
} // namespace vector

