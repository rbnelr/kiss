// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "fm3.hpp"

#include "fm2.hpp"
#include "fm4.hpp"
#include "fm2x3.hpp"
#include "fm3x4.hpp"
#include "dm3.hpp"

namespace vector {
	
	//// Accessors
	
	
	// get cell with r,c indecies (r=row, c=column)
	f32 const& fm3::get (int r, int c) const {
		return arr[c][r];
	}
	
	// get matrix column
	fv3 const& fm3::get_column (int indx) const {
		return arr[indx];
	}
	
	// get matrix row
	fv3 fm3::get_row (int indx) const {
		return fv3(arr[0][indx], arr[1][indx], arr[2][indx]);
	}
	
	//// Constructors
	
	
	fm3::fm3 () {
		
	}
	
	// supply one value for all cells
	fm3::fm3 (f32 all): 
	arr{
		fv3(all, all, all),
		fv3(all, all, all),
		fv3(all, all, all)} {
		
	}
	
	// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
	fm3::fm3 (
			f32 c00, f32 c01, f32 c02,
			f32 c10, f32 c11, f32 c12,
			f32 c20, f32 c21, f32 c22): 
	arr{
		fv3(c00, c10, c20),
		fv3(c01, c11, c21),
		fv3(c02, c12, c22)} {
		
	}
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	// supply all row vectors
	fm3 fm3::rows (fv3 row0, fv3 row1, fv3 row2) {
		return fm3(
				row0[0], row0[1], row0[2],
				row1[0], row1[1], row1[2],
				row2[0], row2[1], row2[2]);
	}
	
	// supply all cells in row major order
	fm3 fm3::rows (
			f32 c00, f32 c01, f32 c02,
			f32 c10, f32 c11, f32 c12,
			f32 c20, f32 c21, f32 c22) {
		return fm3(
				c00, c01, c02,
				c10, c11, c12,
				c20, c21, c22);
	}
	
	// supply all column vectors
	fm3 fm3::columns (fv3 col0, fv3 col1, fv3 col2) {
		return fm3(
				col0[0], col1[0], col2[0],
				col0[1], col1[1], col2[1],
				col0[2], col1[2], col2[2]);
	}
	
	// supply all cells in column major order
	fm3 fm3::columns (
			f32 c00, f32 c10, f32 c20,
			f32 c01, f32 c11, f32 c21,
			f32 c02, f32 c12, f32 c22) {
		return fm3(
				c00, c01, c02,
				c10, c11, c12,
				c20, c21, c22);
	}
	
	
	// identity matrix
	fm3 fm3::identity () {
		return fm3(
				1,0,0,
				0,1,0,
				0,0,1);
	}
	
	// Casting operators
	
	
	// extend/truncate matrix of other size
	fm3::operator fm2 () const {
		return fm2(
				arr[0][0], arr[1][0],
				arr[0][1], arr[1][1]);
	}
	
	// extend/truncate matrix of other size
	fm3::operator fm4 () const {
		return fm4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				arr[0][2], arr[1][2], arr[2][2],         0,
				        0,         0,         0,         1);
	}
	
	// extend/truncate matrix of other size
	fm3::operator fm2x3 () const {
		return fm2x3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1]);
	}
	
	// extend/truncate matrix of other size
	fm3::operator fm3x4 () const {
		return fm3x4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				arr[0][2], arr[1][2], arr[2][2],         0);
	}
	
	// typecast
	fm3::operator dm3 () const {
		return dm3(
				(f64)arr[0][0], (f64)arr[0][1], (f64)arr[0][2],
				(f64)arr[1][0], (f64)arr[1][1], (f64)arr[1][2],
				(f64)arr[2][0], (f64)arr[2][1], (f64)arr[2][2]);
	}
	
	// Elementwise operators
	
	
	fm3& fm3::operator+= (f32 r) {
		*this = *this + r;
		return *this;
	}
	
	fm3& fm3::operator-= (f32 r) {
		*this = *this - r;
		return *this;
	}
	
	fm3& fm3::operator*= (f32 r) {
		*this = *this * r;
		return *this;
	}
	
	fm3& fm3::operator/= (f32 r) {
		*this = *this / r;
		return *this;
	}
	
	// Matrix multiplication
	
	
	fm3& fm3::operator*= (fm3 const& r) {
		*this = *this * r;
		return *this;
	}
	
	// Elementwise operators
	
	
	fm3 operator+ (fm3 const& m) {
		return fm3(
				+m.arr[0][0], +m.arr[1][0], +m.arr[2][0],
				+m.arr[0][1], +m.arr[1][1], +m.arr[2][1],
				+m.arr[0][2], +m.arr[1][2], +m.arr[2][2]);
	}
	
	fm3 operator- (fm3 const& m) {
		return fm3(
				-m.arr[0][0], -m.arr[1][0], -m.arr[2][0],
				-m.arr[0][1], -m.arr[1][1], -m.arr[2][1],
				-m.arr[0][2], -m.arr[1][2], -m.arr[2][2]);
	}
	
	
	fm3 operator+ (fm3 const& l, fm3 const& r) {
		return fm3(
				l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0],
				l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1],
				l.arr[0][2] + r.arr[0][2], l.arr[1][2] + r.arr[1][2], l.arr[2][2] + r.arr[2][2]);
	}
	
	fm3 operator+ (fm3 const& l, f32 r) {
		return fm3(
				l.arr[0][0] + r, l.arr[1][0] + r, l.arr[2][0] + r,
				l.arr[0][1] + r, l.arr[1][1] + r, l.arr[2][1] + r,
				l.arr[0][2] + r, l.arr[1][2] + r, l.arr[2][2] + r);
	}
	
	fm3 operator+ (f32 l, fm3 const& r) {
		return fm3(
				l + r.arr[0][0], l + r.arr[1][0], l + r.arr[2][0],
				l + r.arr[0][1], l + r.arr[1][1], l + r.arr[2][1],
				l + r.arr[0][2], l + r.arr[1][2], l + r.arr[2][2]);
	}
	
	
	fm3 operator- (fm3 const& l, fm3 const& r) {
		return fm3(
				l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0],
				l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1],
				l.arr[0][2] - r.arr[0][2], l.arr[1][2] - r.arr[1][2], l.arr[2][2] - r.arr[2][2]);
	}
	
	fm3 operator- (fm3 const& l, f32 r) {
		return fm3(
				l.arr[0][0] - r, l.arr[1][0] - r, l.arr[2][0] - r,
				l.arr[0][1] - r, l.arr[1][1] - r, l.arr[2][1] - r,
				l.arr[0][2] - r, l.arr[1][2] - r, l.arr[2][2] - r);
	}
	
	fm3 operator- (f32 l, fm3 const& r) {
		return fm3(
				l - r.arr[0][0], l - r.arr[1][0], l - r.arr[2][0],
				l - r.arr[0][1], l - r.arr[1][1], l - r.arr[2][1],
				l - r.arr[0][2], l - r.arr[1][2], l - r.arr[2][2]);
	}
	
	
	fm3 mul_elementwise (fm3 const& l, fm3 const& r) {
		return fm3(
				l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0],
				l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1],
				l.arr[0][2] * r.arr[0][2], l.arr[1][2] * r.arr[1][2], l.arr[2][2] * r.arr[2][2]);
	}
	
	fm3 operator* (fm3 const& l, f32 r) {
		return fm3(
				l.arr[0][0] * r, l.arr[1][0] * r, l.arr[2][0] * r,
				l.arr[0][1] * r, l.arr[1][1] * r, l.arr[2][1] * r,
				l.arr[0][2] * r, l.arr[1][2] * r, l.arr[2][2] * r);
	}
	
	fm3 operator* (f32 l, fm3 const& r) {
		return fm3(
				l * r.arr[0][0], l * r.arr[1][0], l * r.arr[2][0],
				l * r.arr[0][1], l * r.arr[1][1], l * r.arr[2][1],
				l * r.arr[0][2], l * r.arr[1][2], l * r.arr[2][2]);
	}
	
	
	fm3 div_elementwise (fm3 const& l, fm3 const& r) {
		return fm3(
				l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0],
				l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1],
				l.arr[0][2] / r.arr[0][2], l.arr[1][2] / r.arr[1][2], l.arr[2][2] / r.arr[2][2]);
	}
	
	fm3 operator/ (fm3 const& l, f32 r) {
		return fm3(
				l.arr[0][0] / r, l.arr[1][0] / r, l.arr[2][0] / r,
				l.arr[0][1] / r, l.arr[1][1] / r, l.arr[2][1] / r,
				l.arr[0][2] / r, l.arr[1][2] / r, l.arr[2][2] / r);
	}
	
	fm3 operator/ (f32 l, fm3 const& r) {
		return fm3(
				l / r.arr[0][0], l / r.arr[1][0], l / r.arr[2][0],
				l / r.arr[0][1], l / r.arr[1][1], l / r.arr[2][1],
				l / r.arr[0][2], l / r.arr[1][2], l / r.arr[2][2]);
	}
	
	// Matrix ops
	
	
	fm3 operator* (fm3 const& l, fm3 const& r) {
		fm3 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		ret.arr[2] = l * r.arr[2];
		return ret;
	}
	
	fm3x4 operator* (fm3 const& l, fm3x4 const& r) {
		fm3x4 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		ret.arr[2] = l * r.arr[2];
		ret.arr[3] = l * r.arr[3];
		return ret;
	}
	
	fv3 operator* (fm3 const& l, fv3 r) {
		fv3 ret;
		ret.x = l.arr[0].x * r.x + l.arr[1].x * r.y + l.arr[2].x * r.z;
		ret.y = l.arr[0].y * r.x + l.arr[1].y * r.y + l.arr[2].y * r.z;
		ret.z = l.arr[0].z * r.x + l.arr[1].z * r.y + l.arr[2].z * r.z;
		return ret;
	}
	
	fv3 operator* (fv3 l, fm3 const& r) {
		fv3 ret;
		ret.x = l.x * r.arr[0].x + l.y * r.arr[0].y + l.z * r.arr[0].z;
		ret.y = l.x * r.arr[1].x + l.y * r.arr[1].y + l.z * r.arr[1].z;
		ret.z = l.x * r.arr[2].x + l.y * r.arr[2].y + l.z * r.arr[2].z;
		return ret;
	}
	
	fm3 transpose (fm3 m) {
		return fm3::rows(m.arr[0], m.arr[1], m.arr[2]);
	}
	
	
	f32 det (fm3 m) {
		// optimized from:  // 9 muls, 6 adds, 0 divs = 15 ops
		// to:              // 9 muls, 6 adds, 0 divs = 15 ops
		f32 a = m.arr[0][0];
		f32 b = m.arr[0][1];
		f32 c = m.arr[0][2];
		f32 d = m.arr[1][0];
		f32 e = m.arr[1][1];
		f32 f = m.arr[1][2];
		f32 g = m.arr[2][0];
		f32 h = m.arr[2][1];
		f32 i = m.arr[2][2];
		
		
		// 2D minors
		f32 det_a = e*i - f*h;
		f32 det_b = d*i - f*g;
		f32 det_c = d*h - e*g;
		
		return +a*det_a -b*det_b +c*det_c;
	}
} // namespace vector

