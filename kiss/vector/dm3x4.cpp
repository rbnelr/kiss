// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "dm3x4.hpp"

#include "dm2.hpp"
#include "dm3.hpp"
#include "dm4.hpp"
#include "dm2x3.hpp"
#include "fm3x4.hpp"

namespace vector {
	
	//// Accessors
	
	
	// get matrix row
	dv4 dm3x4::get_row (int indx) const {
		return dv4(arr[0][indx], arr[1][indx], arr[2][indx], arr[3][indx]);
	}
	
	//// Constructors
	
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	// supply all row vectors
	dm3x4 dm3x4::rows (dv4 row0, dv4 row1, dv4 row2) {
		return dm3x4(row0[0], row0[1], row0[2], row0[3],
					 row1[0], row1[1], row1[2], row1[3],
					 row2[0], row2[1], row2[2], row2[3]);
	}
	
	// supply all cells in row major order
	dm3x4 dm3x4::rows (f64 c00, f64 c01, f64 c02, f64 c03,
					   f64 c10, f64 c11, f64 c12, f64 c13,
					   f64 c20, f64 c21, f64 c22, f64 c23) {
		return dm3x4(c00, c01, c02, c03,
					 c10, c11, c12, c13,
					 c20, c21, c22, c23);
	}
	
	// supply all column vectors
	dm3x4 dm3x4::columns (dv3 col0, dv3 col1, dv3 col2, dv3 col3) {
		return dm3x4(col0[0], col1[0], col2[0], col3[0],
					 col0[1], col1[1], col2[1], col3[1],
					 col0[2], col1[2], col2[2], col3[2]);
	}
	
	// supply all cells in column major order
	dm3x4 dm3x4::columns (f64 c00, f64 c10, f64 c20,
						  f64 c01, f64 c11, f64 c21,
						  f64 c02, f64 c12, f64 c22,
						  f64 c03, f64 c13, f64 c23) {
		return dm3x4(c00, c01, c02, c03,
					 c10, c11, c12, c13,
					 c20, c21, c22, c23);
	}
	
	
	// Casting operators
	
	
	// extend/truncate matrix of other size
	dm3x4::operator dm2 () const {
		return dm2(arr[0][0], arr[1][0],
				   arr[0][1], arr[1][1]);
	}
	
	// extend/truncate matrix of other size
	dm3x4::operator dm3 () const {
		return dm3(arr[0][0], arr[1][0], arr[2][0],
				   arr[0][1], arr[1][1], arr[2][1],
				   arr[0][2], arr[1][2], arr[2][2]);
	}
	
	// extend/truncate matrix of other size
	dm3x4::operator dm4 () const {
		return dm4(arr[0][0], arr[1][0], arr[2][0], arr[3][0],
				   arr[0][1], arr[1][1], arr[2][1], arr[3][1],
				   arr[0][2], arr[1][2], arr[2][2], arr[3][2],
				           0,         0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	dm3x4::operator dm2x3 () const {
		return dm2x3(arr[0][0], arr[1][0], arr[2][0],
					 arr[0][1], arr[1][1], arr[2][1]);
	}
	
	// typecast
	dm3x4::operator fm3x4 () const {
		return fm3x4((f32)arr[0][0], (f32)arr[0][1], (f32)arr[0][2], (f32)arr[0][3],
					 (f32)arr[1][0], (f32)arr[1][1], (f32)arr[1][2], (f32)arr[1][3],
					 (f32)arr[2][0], (f32)arr[2][1], (f32)arr[2][2], (f32)arr[2][3]);
	}
	
	// Elementwise operators
	
	
	dm3x4& dm3x4::operator+= (f64 r) {
		*this = *this + r;
		return *this;
	}
	
	dm3x4& dm3x4::operator-= (f64 r) {
		*this = *this - r;
		return *this;
	}
	
	dm3x4& dm3x4::operator*= (f64 r) {
		*this = *this * r;
		return *this;
	}
	
	dm3x4& dm3x4::operator/= (f64 r) {
		*this = *this / r;
		return *this;
	}
	
	// Matrix multiplication
	
	
	dm3x4& dm3x4::operator*= (dm3x4 const& r) {
		*this = *this * r;
		return *this;
	}
	
	// Elementwise operators
	
	
	dm3x4 operator+ (dm3x4 const& m) {
		return dm3x4(+m.arr[0][0], +m.arr[1][0], +m.arr[2][0], +m.arr[3][0],
					 +m.arr[0][1], +m.arr[1][1], +m.arr[2][1], +m.arr[3][1],
					 +m.arr[0][2], +m.arr[1][2], +m.arr[2][2], +m.arr[3][2]);
	}
	
	dm3x4 operator- (dm3x4 const& m) {
		return dm3x4(-m.arr[0][0], -m.arr[1][0], -m.arr[2][0], -m.arr[3][0],
					 -m.arr[0][1], -m.arr[1][1], -m.arr[2][1], -m.arr[3][1],
					 -m.arr[0][2], -m.arr[1][2], -m.arr[2][2], -m.arr[3][2]);
	}
	
	
	dm3x4 operator+ (dm3x4 const& l, dm3x4 const& r) {
		return dm3x4(l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0], l.arr[3][0] + r.arr[3][0],
					 l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1], l.arr[3][1] + r.arr[3][1],
					 l.arr[0][2] + r.arr[0][2], l.arr[1][2] + r.arr[1][2], l.arr[2][2] + r.arr[2][2], l.arr[3][2] + r.arr[3][2]);
	}
	
	dm3x4 operator+ (dm3x4 const& l, f64 r) {
		return dm3x4(l.arr[0][0] + r, l.arr[1][0] + r, l.arr[2][0] + r, l.arr[3][0] + r,
					 l.arr[0][1] + r, l.arr[1][1] + r, l.arr[2][1] + r, l.arr[3][1] + r,
					 l.arr[0][2] + r, l.arr[1][2] + r, l.arr[2][2] + r, l.arr[3][2] + r);
	}
	
	dm3x4 operator+ (f64 l, dm3x4 const& r) {
		return dm3x4(l + r.arr[0][0], l + r.arr[1][0], l + r.arr[2][0], l + r.arr[3][0],
					 l + r.arr[0][1], l + r.arr[1][1], l + r.arr[2][1], l + r.arr[3][1],
					 l + r.arr[0][2], l + r.arr[1][2], l + r.arr[2][2], l + r.arr[3][2]);
	}
	
	
	dm3x4 operator- (dm3x4 const& l, dm3x4 const& r) {
		return dm3x4(l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0], l.arr[3][0] - r.arr[3][0],
					 l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1], l.arr[3][1] - r.arr[3][1],
					 l.arr[0][2] - r.arr[0][2], l.arr[1][2] - r.arr[1][2], l.arr[2][2] - r.arr[2][2], l.arr[3][2] - r.arr[3][2]);
	}
	
	dm3x4 operator- (dm3x4 const& l, f64 r) {
		return dm3x4(l.arr[0][0] - r, l.arr[1][0] - r, l.arr[2][0] - r, l.arr[3][0] - r,
					 l.arr[0][1] - r, l.arr[1][1] - r, l.arr[2][1] - r, l.arr[3][1] - r,
					 l.arr[0][2] - r, l.arr[1][2] - r, l.arr[2][2] - r, l.arr[3][2] - r);
	}
	
	dm3x4 operator- (f64 l, dm3x4 const& r) {
		return dm3x4(l - r.arr[0][0], l - r.arr[1][0], l - r.arr[2][0], l - r.arr[3][0],
					 l - r.arr[0][1], l - r.arr[1][1], l - r.arr[2][1], l - r.arr[3][1],
					 l - r.arr[0][2], l - r.arr[1][2], l - r.arr[2][2], l - r.arr[3][2]);
	}
	
	
	dm3x4 mul_elementwise (dm3x4 const& l, dm3x4 const& r) {
		return dm3x4(l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0], l.arr[3][0] * r.arr[3][0],
					 l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1], l.arr[3][1] * r.arr[3][1],
					 l.arr[0][2] * r.arr[0][2], l.arr[1][2] * r.arr[1][2], l.arr[2][2] * r.arr[2][2], l.arr[3][2] * r.arr[3][2]);
	}
	
	dm3x4 operator* (dm3x4 const& l, f64 r) {
		return dm3x4(l.arr[0][0] * r, l.arr[1][0] * r, l.arr[2][0] * r, l.arr[3][0] * r,
					 l.arr[0][1] * r, l.arr[1][1] * r, l.arr[2][1] * r, l.arr[3][1] * r,
					 l.arr[0][2] * r, l.arr[1][2] * r, l.arr[2][2] * r, l.arr[3][2] * r);
	}
	
	dm3x4 operator* (f64 l, dm3x4 const& r) {
		return dm3x4(l * r.arr[0][0], l * r.arr[1][0], l * r.arr[2][0], l * r.arr[3][0],
					 l * r.arr[0][1], l * r.arr[1][1], l * r.arr[2][1], l * r.arr[3][1],
					 l * r.arr[0][2], l * r.arr[1][2], l * r.arr[2][2], l * r.arr[3][2]);
	}
	
	
	dm3x4 div_elementwise (dm3x4 const& l, dm3x4 const& r) {
		return dm3x4(l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0], l.arr[3][0] / r.arr[3][0],
					 l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1], l.arr[3][1] / r.arr[3][1],
					 l.arr[0][2] / r.arr[0][2], l.arr[1][2] / r.arr[1][2], l.arr[2][2] / r.arr[2][2], l.arr[3][2] / r.arr[3][2]);
	}
	
	dm3x4 operator/ (dm3x4 const& l, f64 r) {
		return dm3x4(l.arr[0][0] / r, l.arr[1][0] / r, l.arr[2][0] / r, l.arr[3][0] / r,
					 l.arr[0][1] / r, l.arr[1][1] / r, l.arr[2][1] / r, l.arr[3][1] / r,
					 l.arr[0][2] / r, l.arr[1][2] / r, l.arr[2][2] / r, l.arr[3][2] / r);
	}
	
	dm3x4 operator/ (f64 l, dm3x4 const& r) {
		return dm3x4(l / r.arr[0][0], l / r.arr[1][0], l / r.arr[2][0], l / r.arr[3][0],
					 l / r.arr[0][1], l / r.arr[1][1], l / r.arr[2][1], l / r.arr[3][1],
					 l / r.arr[0][2], l / r.arr[1][2], l / r.arr[2][2], l / r.arr[3][2]);
	}
	
	// Matrix ops
	
	
	dm3x4 operator* (dm3x4 const& l, dm4 const& r) {
		dm3x4 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		ret.arr[2] = l * r.arr[2];
		ret.arr[3] = l * r.arr[3];
		return ret;
	}
	
	dv3 operator* (dm3x4 const& l, dv4 r) {
		dv3 ret;
		ret.x = l.arr[0].x * r.x + l.arr[1].x * r.y + l.arr[2].x * r.z + l.arr[3].x * r.w;
		ret.y = l.arr[0].y * r.x + l.arr[1].y * r.y + l.arr[2].y * r.z + l.arr[3].y * r.w;
		ret.z = l.arr[0].z * r.x + l.arr[1].z * r.y + l.arr[2].z * r.z + l.arr[3].z * r.w;
		return ret;
	}
	
	dv4 operator* (dv3 l, dm3x4 const& r) {
		dv4 ret;
		ret.x = l.x * r.arr[0].x + l.y * r.arr[0].y + l.z * r.arr[0].z;
		ret.y = l.x * r.arr[1].x + l.y * r.arr[1].y + l.z * r.arr[1].z;
		ret.z = l.x * r.arr[2].x + l.y * r.arr[2].y + l.z * r.arr[2].z;
		ret.w = l.x * r.arr[3].x + l.y * r.arr[3].y + l.z * r.arr[3].z;
		return ret;
	}
	
	// Matrix op shortforms for working with 3x4 matricies as 3x3 matricies plus translation
	
	
	// dm3x4 * dm3 = dm3x4, shortform for dm3x4 * (dm4)dm3 = dm3x4
	dm3x4 operator* (dm3x4 const& l, dm3 const& r) {
		return l * (dm4)r;
	}
	
	// dm3x4 * dm3x4 = dm3x4, shortform for dm3x4 * (dm4)dm3x4 = dm3x4
	dm3x4 operator* (dm3x4 const& l, dm3x4 const& r) {
		return l * (dm4)r;
	}
	
	// dm3x4 * dv3 = dv3, shortform for dm3x4 * dv4(dv3, 1) = dv3
	dv3 operator* (dm3x4 const& l, dv3 r) {
		return l * dv4(r, 1);
	}
} // namespace vector

