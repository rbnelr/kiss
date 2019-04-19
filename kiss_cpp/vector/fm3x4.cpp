// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "fm3x4.hpp"

#include "fm2.hpp"
#include "fm3.hpp"
#include "fm4.hpp"
#include "fm2x3.hpp"
#include "dm3x4.hpp"

namespace vector {
	
	//// Accessors
	
	
	f32 const& fm3x4::get (int r, int c) const {
		return arr[c][r];
	}
	
	fv3 const& fm3x4::get_column (int indx) const {
		return arr[indx];
	}
	
	fv4 fm3x4::get_row (int indx) const {
		return fv4(arr[0][indx], arr[1][indx], arr[2][indx], arr[3][indx]);
	}
	
	//// Constructors
	
	
	fm3x4::fm3x4 () {
		
	}
	
	fm3x4::fm3x4 (f32 all): 
	arr{
		fv3(all, all, all),
		fv3(all, all, all),
		fv3(all, all, all),
		fv3(all, all, all)} {
		
	}
	
	fm3x4::fm3x4 (
			f32 c00, f32 c01, f32 c02, f32 c03,
			f32 c10, f32 c11, f32 c12, f32 c13,
			f32 c20, f32 c21, f32 c22, f32 c23): 
	arr{
		fv3(c00, c10, c20),
		fv3(c01, c11, c21),
		fv3(c02, c12, c22),
		fv3(c03, c13, c23)} {
		
	}
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	fm3x4 fm3x4::rows (fv4 row0, fv4 row1, fv4 row2) {
		return fm3x4(
				row0[0], row0[1], row0[2], row0[3],
				row1[0], row1[1], row1[2], row1[3],
				row2[0], row2[1], row2[2], row2[3]);
	}
	
	fm3x4 fm3x4::rows (
			f32 c00, f32 c01, f32 c02, f32 c03,
			f32 c10, f32 c11, f32 c12, f32 c13,
			f32 c20, f32 c21, f32 c22, f32 c23) {
		return fm3x4(
				c00, c01, c02, c03,
				c10, c11, c12, c13,
				c20, c21, c22, c23);
	}
	
	fm3x4 fm3x4::columns (fv3 col0, fv3 col1, fv3 col2, fv3 col3) {
		return fm3x4(
				col0[0], col1[0], col2[0], col3[0],
				col0[1], col1[1], col2[1], col3[1],
				col0[2], col1[2], col2[2], col3[2]);
	}
	
	fm3x4 fm3x4::columns (
			f32 c00, f32 c10, f32 c20,
			f32 c01, f32 c11, f32 c21,
			f32 c02, f32 c12, f32 c22,
			f32 c03, f32 c13, f32 c23) {
		return fm3x4(
				c00, c01, c02, c03,
				c10, c11, c12, c13,
				c20, c21, c22, c23);
	}
	
	
	fm3x4 fm3x4::identity () {
		return fm3x4(
				1,0,0,0,
				0,1,0,0,
				0,0,1,0);
	}
	
	// Casting operators
	
	
	fm3x4::operator fm2 () {
		return fm2(
				arr[0][0], arr[1][0],
				arr[0][1], arr[1][1]);
	}
	
	fm3x4::operator fm3 () {
		return fm3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1],
				arr[0][2], arr[1][2], arr[2][2]);
	}
	
	fm3x4::operator fm4 () {
		return fm4(
				arr[0][0], arr[1][0], arr[2][0], arr[3][0],
				arr[0][1], arr[1][1], arr[2][1], arr[3][1],
				arr[0][2], arr[1][2], arr[2][2], arr[3][2],
				        0,         0,         0,         1);
	}
	
	fm3x4::operator fm2x3 () {
		return fm2x3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1]);
	}
	
	fm3x4::operator dm3x4 () {
		return dm3x4(
				(f64)arr[0][0], (f64)arr[0][1], (f64)arr[0][2], (f64)arr[0][3],
				(f64)arr[1][0], (f64)arr[1][1], (f64)arr[1][2], (f64)arr[1][3],
				(f64)arr[2][0], (f64)arr[2][1], (f64)arr[2][2], (f64)arr[2][3]);
	}
	
	// Elementwise operators
	
	
	fm3x4& fm3x4::operator+= (f32 r) {
		*this = *this + r;
		return *this;
	}
	
	fm3x4& fm3x4::operator-= (f32 r) {
		*this = *this - r;
		return *this;
	}
	
	fm3x4& fm3x4::operator*= (f32 r) {
		*this = *this * r;
		return *this;
	}
	
	fm3x4& fm3x4::operator/= (f32 r) {
		*this = *this / r;
		return *this;
	}
	
	// Matrix multiplication
	
	
	fm3x4& fm3x4::operator*= (fm3x4 const& r) {
		*this = *this * r;
		return *this;
	}
	
	// Elementwise operators
	
	
	fm3x4 operator+ (fm3x4 const& m) {
		return fm3x4(
				+m.arr[0][0], +m.arr[1][0], +m.arr[2][0], +m.arr[3][0],
				+m.arr[0][1], +m.arr[1][1], +m.arr[2][1], +m.arr[3][1],
				+m.arr[0][2], +m.arr[1][2], +m.arr[2][2], +m.arr[3][2]);
	}
	
	fm3x4 operator- (fm3x4 const& m) {
		return fm3x4(
				-m.arr[0][0], -m.arr[1][0], -m.arr[2][0], -m.arr[3][0],
				-m.arr[0][1], -m.arr[1][1], -m.arr[2][1], -m.arr[3][1],
				-m.arr[0][2], -m.arr[1][2], -m.arr[2][2], -m.arr[3][2]);
	}
	
	
	fm3x4 operator+ (fm3x4 const& l, fm3x4 const& r) {
		return fm3x4(
				l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0], l.arr[3][0] + r.arr[3][0],
				l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1], l.arr[3][1] + r.arr[3][1],
				l.arr[0][2] + r.arr[0][2], l.arr[1][2] + r.arr[1][2], l.arr[2][2] + r.arr[2][2], l.arr[3][2] + r.arr[3][2]);
	}
	
	fm3x4 operator+ (fm3x4 const& l, f32 r) {
		return fm3x4(
				l.arr[0][0] + r, l.arr[1][0] + r, l.arr[2][0] + r, l.arr[3][0] + r,
				l.arr[0][1] + r, l.arr[1][1] + r, l.arr[2][1] + r, l.arr[3][1] + r,
				l.arr[0][2] + r, l.arr[1][2] + r, l.arr[2][2] + r, l.arr[3][2] + r);
	}
	
	fm3x4 operator+ (f32 l, fm3x4 const& r) {
		return fm3x4(
				l + r.arr[0][0], l + r.arr[1][0], l + r.arr[2][0], l + r.arr[3][0],
				l + r.arr[0][1], l + r.arr[1][1], l + r.arr[2][1], l + r.arr[3][1],
				l + r.arr[0][2], l + r.arr[1][2], l + r.arr[2][2], l + r.arr[3][2]);
	}
	
	
	fm3x4 operator- (fm3x4 const& l, fm3x4 const& r) {
		return fm3x4(
				l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0], l.arr[3][0] - r.arr[3][0],
				l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1], l.arr[3][1] - r.arr[3][1],
				l.arr[0][2] - r.arr[0][2], l.arr[1][2] - r.arr[1][2], l.arr[2][2] - r.arr[2][2], l.arr[3][2] - r.arr[3][2]);
	}
	
	fm3x4 operator- (fm3x4 const& l, f32 r) {
		return fm3x4(
				l.arr[0][0] - r, l.arr[1][0] - r, l.arr[2][0] - r, l.arr[3][0] - r,
				l.arr[0][1] - r, l.arr[1][1] - r, l.arr[2][1] - r, l.arr[3][1] - r,
				l.arr[0][2] - r, l.arr[1][2] - r, l.arr[2][2] - r, l.arr[3][2] - r);
	}
	
	fm3x4 operator- (f32 l, fm3x4 const& r) {
		return fm3x4(
				l - r.arr[0][0], l - r.arr[1][0], l - r.arr[2][0], l - r.arr[3][0],
				l - r.arr[0][1], l - r.arr[1][1], l - r.arr[2][1], l - r.arr[3][1],
				l - r.arr[0][2], l - r.arr[1][2], l - r.arr[2][2], l - r.arr[3][2]);
	}
	
	
	fm3x4 mul_elementwise (fm3x4 const& l, fm3x4 const& r) {
		return fm3x4(
				l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0], l.arr[3][0] * r.arr[3][0],
				l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1], l.arr[3][1] * r.arr[3][1],
				l.arr[0][2] * r.arr[0][2], l.arr[1][2] * r.arr[1][2], l.arr[2][2] * r.arr[2][2], l.arr[3][2] * r.arr[3][2]);
	}
	
	fm3x4 operator* (fm3x4 const& l, f32 r) {
		return fm3x4(
				l.arr[0][0] * r, l.arr[1][0] * r, l.arr[2][0] * r, l.arr[3][0] * r,
				l.arr[0][1] * r, l.arr[1][1] * r, l.arr[2][1] * r, l.arr[3][1] * r,
				l.arr[0][2] * r, l.arr[1][2] * r, l.arr[2][2] * r, l.arr[3][2] * r);
	}
	
	fm3x4 operator* (f32 l, fm3x4 const& r) {
		return fm3x4(
				l * r.arr[0][0], l * r.arr[1][0], l * r.arr[2][0], l * r.arr[3][0],
				l * r.arr[0][1], l * r.arr[1][1], l * r.arr[2][1], l * r.arr[3][1],
				l * r.arr[0][2], l * r.arr[1][2], l * r.arr[2][2], l * r.arr[3][2]);
	}
	
	
	fm3x4 div_elementwise (fm3x4 const& l, fm3x4 const& r) {
		return fm3x4(
				l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0], l.arr[3][0] / r.arr[3][0],
				l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1], l.arr[3][1] / r.arr[3][1],
				l.arr[0][2] / r.arr[0][2], l.arr[1][2] / r.arr[1][2], l.arr[2][2] / r.arr[2][2], l.arr[3][2] / r.arr[3][2]);
	}
	
	fm3x4 operator/ (fm3x4 const& l, f32 r) {
		return fm3x4(
				l.arr[0][0] / r, l.arr[1][0] / r, l.arr[2][0] / r, l.arr[3][0] / r,
				l.arr[0][1] / r, l.arr[1][1] / r, l.arr[2][1] / r, l.arr[3][1] / r,
				l.arr[0][2] / r, l.arr[1][2] / r, l.arr[2][2] / r, l.arr[3][2] / r);
	}
	
	fm3x4 operator/ (f32 l, fm3x4 const& r) {
		return fm3x4(
				l / r.arr[0][0], l / r.arr[1][0], l / r.arr[2][0], l / r.arr[3][0],
				l / r.arr[0][1], l / r.arr[1][1], l / r.arr[2][1], l / r.arr[3][1],
				l / r.arr[0][2], l / r.arr[1][2], l / r.arr[2][2], l / r.arr[3][2]);
	}
	
	// Matrix multiplication
	
	
	fm3x4 operator* (fm3x4 const& l, fm4 const& r) {
		fm3x4 ret;
		ret.arr[0] = l * r.arr[0];
		ret.arr[1] = l * r.arr[1];
		ret.arr[2] = l * r.arr[2];
		ret.arr[3] = l * r.arr[3];
		return ret;
	}
	
	fv3 operator* (fm3x4 const& l, fv4 r) {
		fv3 ret;
		ret.x = l.arr[0].x * r.x + l.arr[1].x * r.y + l.arr[2].x * r.z + l.arr[3].x * r.w;
		ret.y = l.arr[0].y * r.x + l.arr[1].y * r.y + l.arr[2].y * r.z + l.arr[3].y * r.w;
		ret.z = l.arr[0].z * r.x + l.arr[1].z * r.y + l.arr[2].z * r.z + l.arr[3].z * r.w;
		return ret;
	}
	
	fv4 operator* (fv3 l, fm3x4 const& r) {
		fv4 ret;
		ret.x = l.x * r.arr[0].x + l.y * r.arr[0].y + l.z * r.arr[0].z;
		ret.y = l.x * r.arr[1].x + l.y * r.arr[1].y + l.z * r.arr[1].z;
		ret.z = l.x * r.arr[2].x + l.y * r.arr[2].y + l.z * r.arr[2].z;
		ret.w = l.x * r.arr[3].x + l.y * r.arr[3].y + l.z * r.arr[3].z;
		return ret;
	}
} // namespace vector

