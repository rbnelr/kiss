// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "f64m3.hpp"

#include "f64m2.hpp"
#include "f64m4.hpp"
#include "f64m2x3.hpp"
#include "f64m3x4.hpp"
#include "m3.hpp"

namespace vector {
	
	//// Accessors
	
	
	f64 f64m3::get (int r, int c) const {
		return arr[c][r];
	}
	
	dv3 f64m3::get_column (int indx) const {
		return arr[indx];
	}
	
	dv3 f64m3::get_row (int indx) const {
		return dv3(arr[0][indx], arr[1][indx], arr[2][indx]);
	}
	
	//// Constructors
	
	
	f64m3::f64m3 () {
		
	}
	
	f64m3::f64m3 (f64 all): 
	arr{
		dv3(all, all, all),
		dv3(all, all, all),
		dv3(all, all, all)} {
		
	}
	
	f64m3::f64m3 (
			f64 c00, f64 c01, f64 c02,
			f64 c10, f64 c11, f64 c12,
			f64 c20, f64 c21, f64 c22): 
	arr{
		dv3(c00, c10, c20),
		dv3(c01, c11, c21),
		dv3(c02, c12, c22)} {
		
	}
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	f64m3 f64m3::rows (dv3 row0, dv3 row1, dv3 row2) {
		return f64m3(
				row0[0], row0[1], row0[2],
				row1[0], row1[1], row1[2],
				row2[0], row2[1], row2[2]);
	}
	
	f64m3 f64m3::rows (
			f64 c00, f64 c01, f64 c02,
			f64 c10, f64 c11, f64 c12,
			f64 c20, f64 c21, f64 c22) {
		return f64m3(
				c00, c01, c02,
				c10, c11, c12,
				c20, c21, c22);
	}
	
	f64m3 f64m3::columns (dv3 col0, dv3 col1, dv3 col2) {
		return f64m3(
				col0[0], col1[0], col2[0],
				col0[1], col1[1], col2[1],
				col0[2], col1[2], col2[2]);
	}
	
	f64m3 f64m3::columns (
			f64 c00, f64 c10, f64 c20,
			f64 c01, f64 c11, f64 c21,
			f64 c02, f64 c12, f64 c22) {
		return f64m3(
				c00, c01, c02,
				c10, c11, c12,
				c20, c21, c22);
	}
	
	
	f64m3 f64m3::identity () {
		return f64m3(
				1,0,0,
				0,1,0,
				0,0,1);
	}
	
	// Casting operators
	
	
	f64m3::operator f64m2 () {
		return f64m2(
				arr[0][0], arr[1][0],
				arr[0][1], arr[1][1]);
	}
	
	f64m3::operator f64m4 () {
		return f64m4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				arr[0][2], arr[1][2], arr[2][2],         0,
				        0,         0,         0,         1);
	}
	
	f64m3::operator f64m2x3 () {
		return f64m2x3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1]);
	}
	
	f64m3::operator f64m3x4 () {
		return f64m3x4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				arr[0][2], arr[1][2], arr[2][2],         0);
	}
	
	f64m3::operator m3 () {
		return m3(
				(f32)arr[0][0], (f32)arr[0][1], (f32)arr[0][2],
				(f32)arr[1][0], (f32)arr[1][1], (f32)arr[1][2],
				(f32)arr[2][0], (f32)arr[2][1], (f32)arr[2][2]);
	}
	
	// Elementwise operators
	
	
	f64m3 f64m3::operator+ (f64m3 m) {
		return f64m3(
				+m.arr[0][0], +m.arr[1][0], +m.arr[2][0],
				+m.arr[0][1], +m.arr[1][1], +m.arr[2][1],
				+m.arr[0][2], +m.arr[1][2], +m.arr[2][2]);
	}
	
	f64m3 f64m3::operator- (f64m3 m) {
		return f64m3(
				-m.arr[0][0], -m.arr[1][0], -m.arr[2][0],
				-m.arr[0][1], -m.arr[1][1], -m.arr[2][1],
				-m.arr[0][2], -m.arr[1][2], -m.arr[2][2]);
	}
	
	f64m3 operator+ (f64m3 l, f64m3 r) {
		return f64m3(
				l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0],
				l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1],
				l.arr[0][2] + r.arr[0][2], l.arr[1][2] + r.arr[1][2], l.arr[2][2] + r.arr[2][2]);
	}
	
	f64m3 operator- (f64m3 l, f64m3 r) {
		return f64m3(
				l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0],
				l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1],
				l.arr[0][2] - r.arr[0][2], l.arr[1][2] - r.arr[1][2], l.arr[2][2] - r.arr[2][2]);
	}
	
	f64m3 operator* (f64m3 l, f64m3 r) {
		return f64m3(
				l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0],
				l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1],
				l.arr[0][2] * r.arr[0][2], l.arr[1][2] * r.arr[1][2], l.arr[2][2] * r.arr[2][2]);
	}
	
	f64m3 operator/ (f64m3 l, f64m3 r) {
		return f64m3(
				l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0],
				l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1],
				l.arr[0][2] / r.arr[0][2], l.arr[1][2] / r.arr[1][2], l.arr[2][2] / r.arr[2][2]);
	}
} // namespace vector
