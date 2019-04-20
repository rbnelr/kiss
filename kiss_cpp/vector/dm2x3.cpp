// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "dm2x3.hpp"

#include "dm2.hpp"
#include "dm3.hpp"
#include "dm4.hpp"
#include "dm3x4.hpp"
#include "fm2x3.hpp"

namespace vector {
	
	//// Accessors
	
	
	// get cell with r,c indecies (r=row, c=column)
	f64 const& dm2x3::get (int r, int c) const {
		return arr[c][r];
	}
	
	// get matrix column
	dv2 const& dm2x3::get_column (int indx) const {
		return arr[indx];
	}
	
	// get matrix row
	dv3 dm2x3::get_row (int indx) const {
		return dv3(arr[0][indx], arr[1][indx], arr[2][indx]);
	}
	
	//// Constructors
	
	
	dm2x3::dm2x3 () {
		
	}
	
	// supply one value for all cells
	dm2x3::dm2x3 (f64 all): 
	arr{
		dv2(all, all),
		dv2(all, all),
		dv2(all, all)} {
		
	}
	
	// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
	dm2x3::dm2x3 (
			f64 c00, f64 c01, f64 c02,
			f64 c10, f64 c11, f64 c12): 
	arr{
		dv2(c00, c10),
		dv2(c01, c11),
		dv2(c02, c12)} {
		
	}
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	// supply all row vectors
	dm2x3 dm2x3::rows (dv3 row0, dv3 row1) {
		return dm2x3(
				row0[0], row0[1], row0[2],
				row1[0], row1[1], row1[2]);
	}
	
	// supply all cells in row major order
	dm2x3 dm2x3::rows (
			f64 c00, f64 c01, f64 c02,
			f64 c10, f64 c11, f64 c12) {
		return dm2x3(
				c00, c01, c02,
				c10, c11, c12);
	}
	
	// supply all column vectors
	dm2x3 dm2x3::columns (dv2 col0, dv2 col1, dv2 col2) {
		return dm2x3(
				col0[0], col1[0], col2[0],
				col0[1], col1[1], col2[1]);
	}
	
	// supply all cells in column major order
	dm2x3 dm2x3::columns (
			f64 c00, f64 c10,
			f64 c01, f64 c11,
			f64 c02, f64 c12) {
		return dm2x3(
				c00, c01, c02,
				c10, c11, c12);
	}
	
	
	// identity matrix
	dm2x3 dm2x3::identity () {
		return dm2x3(
				1,0,0,
				0,1,0);
	}
	
	// Casting operators
	
	
	// extend/truncate matrix of other size
	dm2x3::operator dm2 () const {
		return dm2(
				arr[0][0], arr[1][0],
				arr[0][1], arr[1][1]);
	}
	
	// extend/truncate matrix of other size
	dm2x3::operator dm3 () const {
		return dm3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1],
				        0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	dm2x3::operator dm4 () const {
		return dm4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				        0,         0,         1,         0,
				        0,         0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	dm2x3::operator dm3x4 () const {
		return dm3x4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				        0,         0,         1,         0);
	}
	
	// typecast
	dm2x3::operator fm2x3 () const {
		return fm2x3(
				(f32)arr[0][0], (f32)arr[0][1], (f32)arr[0][2],
				(f32)arr[1][0], (f32)arr[1][1], (f32)arr[1][2]);
	}
	
	// Elementwise operators
	
	
	dm2x3& dm2x3::operator+= (f64 r) {
		*this = *this + r;
		return *this;
	}
	
	dm2x3& dm2x3::operator-= (f64 r) {
		*this = *this - r;
		return *this;
	}
	
	dm2x3& dm2x3::operator*= (f64 r) {
		*this = *this * r;
		return *this;
	}
	
	dm2x3& dm2x3::operator/= (f64 r) {
		*this = *this / r;
		return *this;
	}
	
	// Matrix multiplication
	
	
	dm2x3& dm2x3::operator*= (dm2x3 const& r) {
		*this = *this * r;
		return *this;
	}
	
	// Elementwise operators
	
	
	dm2x3 operator+ (dm2x3 const& m) {
		return dm2x3(
				+m.arr[0][0], +m.arr[1][0], +m.arr[2][0],
				+m.arr[0][1], +m.arr[1][1], +m.arr[2][1]);
	}
	
	dm2x3 operator- (dm2x3 const& m) {
		return dm2x3(
				-m.arr[0][0], -m.arr[1][0], -m.arr[2][0],
				-m.arr[0][1], -m.arr[1][1], -m.arr[2][1]);
	}
	
	
	dm2x3 operator+ (dm2x3 const& l, dm2x3 const& r) {
		return dm2x3(
				l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0],
				l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1]);
	}
	
	dm2x3 operator+ (dm2x3 const& l, f64 r) {
		return dm2x3(
				l.arr[0][0] + r, l.arr[1][0] + r, l.arr[2][0] + r,
				l.arr[0][1] + r, l.arr[1][1] + r, l.arr[2][1] + r);
	}
	
	dm2x3 operator+ (f64 l, dm2x3 const& r) {
		return dm2x3(
				l + r.arr[0][0], l + r.arr[1][0], l + r.arr[2][0],
				l + r.arr[0][1], l + r.arr[1][1], l + r.arr[2][1]);
	}
	
	
	dm2x3 operator- (dm2x3 const& l, dm2x3 const& r) {
		return dm2x3(
				l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0],
				l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1]);
	}
	
	dm2x3 operator- (dm2x3 const& l, f64 r) {
		return dm2x3(
				l.arr[0][0] - r, l.arr[1][0] - r, l.arr[2][0] - r,
				l.arr[0][1] - r, l.arr[1][1] - r, l.arr[2][1] - r);
	}
	
	dm2x3 operator- (f64 l, dm2x3 const& r) {
		return dm2x3(
				l - r.arr[0][0], l - r.arr[1][0], l - r.arr[2][0],
				l - r.arr[0][1], l - r.arr[1][1], l - r.arr[2][1]);
	}
	
	
	dm2x3 mul_elementwise (dm2x3 const& l, dm2x3 const& r) {
		return dm2x3(
				l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0],
				l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1]);
	}
	
	dm2x3 operator* (dm2x3 const& l, f64 r) {
		return dm2x3(
				l.arr[0][0] * r, l.arr[1][0] * r, l.arr[2][0] * r,
				l.arr[0][1] * r, l.arr[1][1] * r, l.arr[2][1] * r);
	}
	
	dm2x3 operator* (f64 l, dm2x3 const& r) {
		return dm2x3(
				l * r.arr[0][0], l * r.arr[1][0], l * r.arr[2][0],
				l * r.arr[0][1], l * r.arr[1][1], l * r.arr[2][1]);
	}
	
	
	dm2x3 div_elementwise (dm2x3 const& l, dm2x3 const& r) {
		return dm2x3(
				l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0],
				l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1]);
	}
	
	dm2x3 operator/ (dm2x3 const& l, f64 r) {
		return dm2x3(
				l.arr[0][0] / r, l.arr[1][0] / r, l.arr[2][0] / r,
				l.arr[0][1] / r, l.arr[1][1] / r, l.arr[2][1] / r);
	}
	
	dm2x3 operator/ (f64 l, dm2x3 const& r) {
		return dm2x3(
				l / r.arr[0][0], l / r.arr[1][0], l / r.arr[2][0],
				l / r.arr[0][1], l / r.arr[1][1], l / r.arr[2][1]);
	}
	
	// Matrix ops
	
	
	dm2x3 operator* (dm2x3 const& l, dm3 const& r) {
		dm2x3 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		ret.arr[2] = l * r.arr[2];
		return ret;
	}
	// dm2x3 * dm3x4 -> 2x4 ; matrix not implemented
	
	dv2 operator* (dm2x3 const& l, dv3 r) {
		dv2 ret;
		ret.x = l.arr[0].x * r.x + l.arr[1].x * r.y + l.arr[2].x * r.z;
		ret.y = l.arr[0].y * r.x + l.arr[1].y * r.y + l.arr[2].y * r.z;
		return ret;
	}
	
	dv3 operator* (dv2 l, dm2x3 const& r) {
		dv3 ret;
		ret.x = l.x * r.arr[0].x + l.y * r.arr[0].y;
		ret.y = l.x * r.arr[1].x + l.y * r.arr[1].y;
		ret.z = l.x * r.arr[2].x + l.y * r.arr[2].y;
		return ret;
	}
	
	// Matrix op shortforms for working with 2x3 matricies as 2x2 matricies plus translation
	
	
	// dm2x3 * dm2 = dm2x3, shortform for dm2x3 * (dm3)dm2 = dm2x3
	dm2x3 operator* (dm2x3 const& l, dm2 const& r) {
		return l * (dm3)r;
	}
	
	// dm2x3 * dm2x3 = dm2x3, shortform for dm2x3 * (dm3)dm2x3 = dm2x3
	dm2x3 operator* (dm2x3 const& l, dm2x3 const& r) {
		return l * (dm3)r;
	}
	
	// dm2x3 * dv2 = dv2, shortform for dm2x3 * dv3(dv2, 1) = dv2
	dv2 operator* (dm2x3 const& l, dv2 r) {
		return l * dv3(r, 1);
	}
} // namespace vector

