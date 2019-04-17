// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


#include <string>

#include "fv3.hpp"
#include "fv4.hpp"

namespace vector {
	
	//// matrix forward declarations
	struct m2;
	struct m3;
	struct m4;
	struct m2x3;
	struct f64m3x4;
	
	struct m3x4 {
		fv3 arr[4]; // column major for compatibility with OpenGL
		
		//// Accessors
		
		// get cell with r,c indecies (r=row, c=column)
		f32 get (int r, int c) const;
		// get matrix column
		fv3 get_column (int indx) const;
		// get matrix row
		fv4 get_row (int indx) const;
		
		//// Constructors
		
		m3x4 ();
		// supply one value for all cells
		m3x4 (f32 all);
		// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
		m3x4 (
				f32 c00, f32 c01, f32 c02, f32 c03,
				f32 c10, f32 c11, f32 c12, f32 c13,
				f32 c20, f32 c21, f32 c22, f32 c23);
		
		// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
		// supply all row vectors
		static m3x4 rows (fv4 row0, fv4 row1, fv4 row2);
		// supply all cells in row major order
		static m3x4 rows (
				f32 c00, f32 c01, f32 c02, f32 c03,
				f32 c10, f32 c11, f32 c12, f32 c13,
				f32 c20, f32 c21, f32 c22, f32 c23);
		// supply all column vectors
		static m3x4 columns (fv3 col0, fv3 col1, fv3 col2, fv3 col3);
		// supply all cells in column major order
		static m3x4 columns (
				f32 c00, f32 c10, f32 c20,
				f32 c01, f32 c11, f32 c21,
				f32 c02, f32 c12, f32 c22,
				f32 c03, f32 c13, f32 c23);
		
		// identity matrix
		static m3x4 identity ();
		
		// Casting operators
		
		// extend/truncate matrix of other size
		operator m2 ();
		// extend/truncate matrix of other size
		operator m3 ();
		// extend/truncate matrix of other size
		operator m4 ();
		// extend/truncate matrix of other size
		operator m2x3 ();
		// typecast
		operator f64m3x4 ();
		
		// Elementwise operators
		
		m3x4 operator+ (m3x4 m);
		m3x4 operator- (m3x4 m);
	};
	
	m3x4 operator+ (m3x4 l, m3x4 r);
	m3x4 operator- (m3x4 l, m3x4 r);
	m3x4 operator* (m3x4 l, m3x4 r);
	m3x4 operator/ (m3x4 l, m3x4 r);
} // namespace vector
