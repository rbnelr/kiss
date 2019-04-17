// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#include "m2x3.hpp"

#include "m2.hpp"
#include "m3.hpp"
#include "m4.hpp"
#include "m3x4.hpp"
#include "f64m2x3.hpp"

namespace vector {
	
	//// Accessors
	
	
	f32 m2x3::get (int r, int c) const {
		return arr[c][r];
	}
	
	fv2 m2x3::get_column (int indx) const {
		return arr[indx];
	}
	
	fv3 m2x3::get_row (int indx) const {
		return fv3(arr[0][indx], arr[1][indx], arr[2][indx]);
	}
	
	//// Constructors
	
	
	m2x3::m2x3 () {
		
	}
	
	m2x3::m2x3 (f32 all): 
	arr{
		fv2(all, all),
		fv2(all, all),
		fv2(all, all)} {
		
	}
	
	m2x3::m2x3 (
			f32 c00, f32 c01, f32 c02,
			f32 c10, f32 c11, f32 c12): 
	arr{
		fv2(c00, c10),
		fv2(c01, c11),
		fv2(c02, c12)} {
		
	}
	
	// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
	
	m2x3 m2x3::rows (fv3 row0, fv3 row1) {
		return m2x3(
				row0[0], row0[1], row0[2],
				row1[0], row1[1], row1[2]);
	}
	
	m2x3 m2x3::rows (
			f32 c00, f32 c01, f32 c02,
			f32 c10, f32 c11, f32 c12) {
		return m2x3(
				c00, c01, c02,
				c10, c11, c12);
	}
	
	m2x3 m2x3::columns (fv2 col0, fv2 col1, fv2 col2) {
		return m2x3(
				col0[0], col1[0], col2[0],
				col0[1], col1[1], col2[1]);
	}
	
	m2x3 m2x3::columns (
			f32 c00, f32 c10,
			f32 c01, f32 c11,
			f32 c02, f32 c12) {
		return m2x3(
				c00, c01, c02,
				c10, c11, c12);
	}
	
	
	m2x3 m2x3::identity () {
		return m2x3(
				1,0,0,
				0,1,0);
	}
	
	// Casting operators
	
	
	m2x3::operator m2 () {
		return m2(
				arr[0][0], arr[1][0],
				arr[0][1], arr[1][1]);
	}
	
	m2x3::operator m3 () {
		return m3(
				arr[0][0], arr[1][0], arr[2][0],
				arr[0][1], arr[1][1], arr[2][1],
				        0,         0,         1);
	}
	
	m2x3::operator m4 () {
		return m4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				        0,         0,         1,         0,
				        0,         0,         0,         1);
	}
	
	m2x3::operator m3x4 () {
		return m3x4(
				arr[0][0], arr[1][0], arr[2][0],         0,
				arr[0][1], arr[1][1], arr[2][1],         0,
				        0,         0,         1,         0);
	}
	
	m2x3::operator f64m2x3 () {
		return f64m2x3(
				(f64)arr[0][0], (f64)arr[0][1], (f64)arr[0][2],
				(f64)arr[1][0], (f64)arr[1][1], (f64)arr[1][2]);
	}
	
	// Elementwise operators
	
	
	m2x3 m2x3::operator+ (m2x3 m) {
		return m2x3(
				+m.arr[0][0], +m.arr[1][0], +m.arr[2][0],
				+m.arr[0][1], +m.arr[1][1], +m.arr[2][1]);
	}
	
	m2x3 m2x3::operator- (m2x3 m) {
		return m2x3(
				-m.arr[0][0], -m.arr[1][0], -m.arr[2][0],
				-m.arr[0][1], -m.arr[1][1], -m.arr[2][1]);
	}
	
	m2x3 operator+ (m2x3 l, m2x3 r) {
		return m2x3(
				l.arr[0][0] + r.arr[0][0], l.arr[1][0] + r.arr[1][0], l.arr[2][0] + r.arr[2][0],
				l.arr[0][1] + r.arr[0][1], l.arr[1][1] + r.arr[1][1], l.arr[2][1] + r.arr[2][1]);
	}
	
	m2x3 operator- (m2x3 l, m2x3 r) {
		return m2x3(
				l.arr[0][0] - r.arr[0][0], l.arr[1][0] - r.arr[1][0], l.arr[2][0] - r.arr[2][0],
				l.arr[0][1] - r.arr[0][1], l.arr[1][1] - r.arr[1][1], l.arr[2][1] - r.arr[2][1]);
	}
	
	m2x3 operator* (m2x3 l, m2x3 r) {
		return m2x3(
				l.arr[0][0] * r.arr[0][0], l.arr[1][0] * r.arr[1][0], l.arr[2][0] * r.arr[2][0],
				l.arr[0][1] * r.arr[0][1], l.arr[1][1] * r.arr[1][1], l.arr[2][1] * r.arr[2][1]);
	}
	
	m2x3 operator/ (m2x3 l, m2x3 r) {
		return m2x3(
				l.arr[0][0] / r.arr[0][0], l.arr[1][0] / r.arr[1][0], l.arr[2][0] / r.arr[2][0],
				l.arr[0][1] / r.arr[0][1], l.arr[1][1] / r.arr[1][1], l.arr[2][1] / r.arr[2][1]);
	}
} // namespace vector
