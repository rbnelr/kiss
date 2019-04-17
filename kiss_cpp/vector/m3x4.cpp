// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "m3x4.hpp"

#include "m2.hpp"
#include "m3.hpp"
#include "m4.hpp"
#include "m2x3.hpp"
#include "f64m3x4.hpp"

namespace vector {
	
	//// Accessors
	
	
	f32 m3x4::get (int r, int c) const {
		return arr[c][r];
	}
	
	fv3 m3x4::get_column (int indx) const {
		return arr[indx];
	}
	
	fv4 m3x4::get_row (int indx) const {
		return fv4(arr[0][indx], arr[1][indx], arr[2][indx], arr[3][indx]);
	}
	
	//// Constructors
	
	
	m3x4::m3x4 () {
		
	}
	
	m3x4::m3x4 (f32 all): 
	arr{
		fv3(all, all, all),
		fv3(all, all, all),
		fv3(all, all, all),
		fv3(all, all, all)} {
		
	}
	
	m3x4::m3x4 (
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
	
	m3x4 m3x4::rows (fv4 row0, fv4 row1, fv4 row2) {
		return m3x4(
				row0[0], row0[1], row0[2], row0[3],
				row1[0], row1[1], row1[2], row1[3],
				row2[0], row2[1], row2[2], row2[3]);
	}
	
	m3x4 m3x4::rows (
			f32 c00, f32 c01, f32 c02, f32 c03,
			f32 c10, f32 c11, f32 c12, f32 c13,
			f32 c20, f32 c21, f32 c22, f32 c23) {
		return m3x4(
				c00, c01, c02, c03,
				c10, c11, c12, c13,
				c20, c21, c22, c23);
	}
	
	m3x4 m3x4::columns (fv3 col0, fv3 col1, fv3 col2, fv3 col3) {
		return m3x4(
				col0[0], col1[0], col2[0], col3[0],
				col0[1], col1[1], col2[1], col3[1],
				col0[2], col1[2], col2[2], col3[2]);
	}
	
	m3x4 m3x4::columns (
			f32 c00, f32 c10, f32 c20,
			f32 c01, f32 c11, f32 c21,
			f32 c02, f32 c12, f32 c22,
			f32 c03, f32 c13, f32 c23) {
		return m3x4(
				c00, c01, c02, c03,
				c10, c11, c12, c13,
				c20, c21, c22, c23);
	}
	
	
	m3x4 m3x4::identity () {
		return m3x4(
				1,0,0,0,
				0,1,0,0,
				0,0,1,0);
	}
	
	// Casting operators
	
	
	m3x4::operator m2 () {
		return m2(
				arr[0][0], arr[1][0],
				arr[0][1], arr[1][1]);
	}
	
	m3x4::operator m3 () {
		return m3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1],
				arr[0][2], arr[1][2], arr[2][2]);
	}
	
	m3x4::operator m4 () {
		return m4(
				arr[0][0], arr[1][0], arr[2][0], arr[3][0],
				arr[0][1], arr[1][1], arr[2][1], arr[3][1],
				arr[0][2], arr[1][2], arr[2][2], arr[3][2],
				        0,         0,         0,         1);
	}
	
	m3x4::operator m2x3 () {
		return m2x3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1]);
	}
	
	m3x4::operator f64m3x4 () {
		return f64m3x4(
				(f64)arr[0][0], (f64)arr[0][1], (f64)arr[0][2], (f64)arr[0][3],
				(f64)arr[1][0], (f64)arr[1][1], (f64)arr[1][2], (f64)arr[1][3],
				(f64)arr[2][0], (f64)arr[2][1], (f64)arr[2][2], (f64)arr[2][3]);
	}
	
	// Elementwise operators
	
	
	m3x4 m3x4::operator+ (m3x4 m) {
		return m3x4(
				+m.arr[0][0], +m.arr[1][0], +m.arr[2][0], +m.arr[3][0],
				+m.arr[0][1], +m.arr[1][1], +m.arr[2][1], +m.arr[3][1],
				+m.arr[0][2], +m.arr[1][2], +m.arr[2][2], +m.arr[3][2]);
	}
	
	m3x4 m3x4::operator- (m3x4 m) {
		return m3x4(
				-m.arr[0][0], -m.arr[1][0], -m.arr[2][0], -m.arr[3][0],
				-m.arr[0][1], -m.arr[1][1], -m.arr[2][1], -m.arr[3][1],
				-m.arr[0][2], -m.arr[1][2], -m.arr[2][2], -m.arr[3][2]);
	}
	
	m3x4 operator+ (m3x4 l, m3x4 r) {
		return m3x4(
				l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0], l.arr[3][0] + r.arr[3][0],
				l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1], l.arr[3][1] + r.arr[3][1],
				l.arr[0][2] + r.arr[0][2], l.arr[1][2] + r.arr[1][2], l.arr[2][2] + r.arr[2][2], l.arr[3][2] + r.arr[3][2]);
	}
	
	m3x4 operator- (m3x4 l, m3x4 r) {
		return m3x4(
				l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0], l.arr[3][0] - r.arr[3][0],
				l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1], l.arr[3][1] - r.arr[3][1],
				l.arr[0][2] - r.arr[0][2], l.arr[1][2] - r.arr[1][2], l.arr[2][2] - r.arr[2][2], l.arr[3][2] - r.arr[3][2]);
	}
	
	m3x4 operator* (m3x4 l, m3x4 r) {
		return m3x4(
				l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0], l.arr[3][0] * r.arr[3][0],
				l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1], l.arr[3][1] * r.arr[3][1],
				l.arr[0][2] * r.arr[0][2], l.arr[1][2] * r.arr[1][2], l.arr[2][2] * r.arr[2][2], l.arr[3][2] * r.arr[3][2]);
	}
	
	m3x4 operator/ (m3x4 l, m3x4 r) {
		return m3x4(
				l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0], l.arr[3][0] / r.arr[3][0],
				l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1], l.arr[3][1] / r.arr[3][1],
				l.arr[0][2] / r.arr[0][2], l.arr[1][2] / r.arr[1][2], l.arr[2][2] / r.arr[2][2], l.arr[3][2] / r.arr[3][2]);
	}
} // namespace vector
