// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "fm2x3.hpp"

#include "fm2.hpp"
#include "fm3.hpp"
#include "fm4.hpp"
#include "fm3x4.hpp"
#include "dm2x3.hpp"

namespace vector {
	
	//// Accessors
	
	
	// get matrix row
	fv3 fm2x3::get_row (int indx) const {
		return fv3(arr[0][indx], arr[1][indx], arr[2][indx]);
	}
	
	//// Constructors
	
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	// supply all row vectors
	fm2x3 fm2x3::rows (fv3 row0, fv3 row1) {
		return fm2x3(row0[0], row0[1], row0[2],
					 row1[0], row1[1], row1[2]);
	}
	
	// supply all cells in row major order
	fm2x3 fm2x3::rows (f32 c00, f32 c01, f32 c02,
					   f32 c10, f32 c11, f32 c12) {
		return fm2x3(c00, c01, c02,
					 c10, c11, c12);
	}
	
	// supply all column vectors
	fm2x3 fm2x3::columns (fv2 col0, fv2 col1, fv2 col2) {
		return fm2x3(col0[0], col1[0], col2[0],
					 col0[1], col1[1], col2[1]);
	}
	
	// supply all cells in column major order
	fm2x3 fm2x3::columns (f32 c00, f32 c10,
						  f32 c01, f32 c11,
						  f32 c02, f32 c12) {
		return fm2x3(c00, c01, c02,
					 c10, c11, c12);
	}
	
	
	// Casting operators
	
	
	// extend/truncate matrix of other size
	fm2x3::operator fm2 () const {
		return fm2(arr[0][0], arr[1][0],
				   arr[0][1], arr[1][1]);
	}
	
	// extend/truncate matrix of other size
	fm2x3::operator fm3 () const {
		return fm3(arr[0][0], arr[1][0], arr[2][0],
				   arr[0][1], arr[1][1], arr[2][1],
				           0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	fm2x3::operator fm4 () const {
		return fm4(arr[0][0], arr[1][0], arr[2][0],         0,
				   arr[0][1], arr[1][1], arr[2][1],         0,
				           0,         0,         1,         0,
				           0,         0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	fm2x3::operator fm3x4 () const {
		return fm3x4(arr[0][0], arr[1][0], arr[2][0],         0,
					 arr[0][1], arr[1][1], arr[2][1],         0,
					         0,         0,         1,         0);
	}
	
	// typecast
	fm2x3::operator dm2x3 () const {
		return dm2x3((f64)arr[0][0], (f64)arr[0][1], (f64)arr[0][2],
					 (f64)arr[1][0], (f64)arr[1][1], (f64)arr[1][2]);
	}
	
	// Elementwise operators
	
	
	fm2x3& fm2x3::operator+= (f32 r) {
		*this = *this + r;
		return *this;
	}
	
	fm2x3& fm2x3::operator-= (f32 r) {
		*this = *this - r;
		return *this;
	}
	
	fm2x3& fm2x3::operator*= (f32 r) {
		*this = *this * r;
		return *this;
	}
	
	fm2x3& fm2x3::operator/= (f32 r) {
		*this = *this / r;
		return *this;
	}
	
	// Matrix multiplication
	
	
	fm2x3& fm2x3::operator*= (fm2x3 const& r) {
		*this = *this * r;
		return *this;
	}
	
	// Elementwise operators
	
	
	fm2x3 operator+ (fm2x3 const& m) {
		return fm2x3(+m.arr[0][0], +m.arr[1][0], +m.arr[2][0],
					 +m.arr[0][1], +m.arr[1][1], +m.arr[2][1]);
	}
	
	fm2x3 operator- (fm2x3 const& m) {
		return fm2x3(-m.arr[0][0], -m.arr[1][0], -m.arr[2][0],
					 -m.arr[0][1], -m.arr[1][1], -m.arr[2][1]);
	}
	
	
	fm2x3 operator+ (fm2x3 const& l, fm2x3 const& r) {
		return fm2x3(l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0],
					 l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1]);
	}
	
	fm2x3 operator+ (fm2x3 const& l, f32 r) {
		return fm2x3(l.arr[0][0] + r, l.arr[1][0] + r, l.arr[2][0] + r,
					 l.arr[0][1] + r, l.arr[1][1] + r, l.arr[2][1] + r);
	}
	
	fm2x3 operator+ (f32 l, fm2x3 const& r) {
		return fm2x3(l + r.arr[0][0], l + r.arr[1][0], l + r.arr[2][0],
					 l + r.arr[0][1], l + r.arr[1][1], l + r.arr[2][1]);
	}
	
	
	fm2x3 operator- (fm2x3 const& l, fm2x3 const& r) {
		return fm2x3(l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0],
					 l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1]);
	}
	
	fm2x3 operator- (fm2x3 const& l, f32 r) {
		return fm2x3(l.arr[0][0] - r, l.arr[1][0] - r, l.arr[2][0] - r,
					 l.arr[0][1] - r, l.arr[1][1] - r, l.arr[2][1] - r);
	}
	
	fm2x3 operator- (f32 l, fm2x3 const& r) {
		return fm2x3(l - r.arr[0][0], l - r.arr[1][0], l - r.arr[2][0],
					 l - r.arr[0][1], l - r.arr[1][1], l - r.arr[2][1]);
	}
	
	
	fm2x3 mul_elementwise (fm2x3 const& l, fm2x3 const& r) {
		return fm2x3(l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0],
					 l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1]);
	}
	
	fm2x3 operator* (fm2x3 const& l, f32 r) {
		return fm2x3(l.arr[0][0] * r, l.arr[1][0] * r, l.arr[2][0] * r,
					 l.arr[0][1] * r, l.arr[1][1] * r, l.arr[2][1] * r);
	}
	
	fm2x3 operator* (f32 l, fm2x3 const& r) {
		return fm2x3(l * r.arr[0][0], l * r.arr[1][0], l * r.arr[2][0],
					 l * r.arr[0][1], l * r.arr[1][1], l * r.arr[2][1]);
	}
	
	
	fm2x3 div_elementwise (fm2x3 const& l, fm2x3 const& r) {
		return fm2x3(l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0],
					 l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1]);
	}
	
	fm2x3 operator/ (fm2x3 const& l, f32 r) {
		return fm2x3(l.arr[0][0] / r, l.arr[1][0] / r, l.arr[2][0] / r,
					 l.arr[0][1] / r, l.arr[1][1] / r, l.arr[2][1] / r);
	}
	
	fm2x3 operator/ (f32 l, fm2x3 const& r) {
		return fm2x3(l / r.arr[0][0], l / r.arr[1][0], l / r.arr[2][0],
					 l / r.arr[0][1], l / r.arr[1][1], l / r.arr[2][1]);
	}
	
	// Matrix ops
	
	
	fm2x3 operator* (fm2x3 const& l, fm3 const& r) {
		fm2x3 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		ret.arr[2] = l * r.arr[2];
		return ret;
	}
	// fm2x3 * fm3x4 -> 2x4 ; matrix not implemented
	
	fv2 operator* (fm2x3 const& l, fv3 r) {
		fv2 ret;
		ret.x = l.arr[0].x * r.x + l.arr[1].x * r.y + l.arr[2].x * r.z;
		ret.y = l.arr[0].y * r.x + l.arr[1].y * r.y + l.arr[2].y * r.z;
		return ret;
	}
	
	fv3 operator* (fv2 l, fm2x3 const& r) {
		fv3 ret;
		ret.x = l.x * r.arr[0].x + l.y * r.arr[0].y;
		ret.y = l.x * r.arr[1].x + l.y * r.arr[1].y;
		ret.z = l.x * r.arr[2].x + l.y * r.arr[2].y;
		return ret;
	}
	
	// Matrix op shortforms for working with 2x3 matricies as 2x2 matricies plus translation
	
	
	// fm2x3 * fm2 = fm2x3, shortform for fm2x3 * (fm3)fm2 = fm2x3
	fm2x3 operator* (fm2x3 const& l, fm2 const& r) {
		return l * (fm3)r;
	}
	
	// fm2x3 * fm2x3 = fm2x3, shortform for fm2x3 * (fm3)fm2x3 = fm2x3
	fm2x3 operator* (fm2x3 const& l, fm2x3 const& r) {
		return l * (fm3)r;
	}
	
	// fm2x3 * fv2 = fv2, shortform for fm2x3 * fv3(fv2, 1) = fv2
	fv2 operator* (fm2x3 const& l, fv2 r) {
		return l * fv3(r, 1);
	}
} // namespace vector

