// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


#include <string>

#include "fv2.hpp"
#include "fv3.hpp"

namespace vector {
	
	//// matrix forward declarations
	struct m2;
	struct m3;
	struct m4;
	struct m3x4;
	struct f64m2x3;
	
	struct m2x3 {
		fv2 arr[3]; // column major for compatibility with OpenGL
		
		//// Accessors
		
		// get cell with r,c indecies (r=row, c=column)
		f32 get (int r, int c) const;
		// get matrix column
		fv2 get_column (int indx) const;
		// get matrix row
		fv3 get_row (int indx) const;
		
		//// Constructors
		
		m2x3 ();
		// supply one value for all cells
		m2x3 (f32 all);
		// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
		m2x3 (
				f32 c00, f32 c01, f32 c02,
				f32 c10, f32 c11, f32 c12);
		
		// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
		// supply all row vectors
		static m2x3 rows (fv3 row0, fv3 row1);
		// supply all cells in row major order
		static m2x3 rows (
				f32 c00, f32 c01, f32 c02,
				f32 c10, f32 c11, f32 c12);
		// supply all column vectors
		static m2x3 columns (fv2 col0, fv2 col1, fv2 col2);
		// supply all cells in column major order
		static m2x3 columns (
				f32 c00, f32 c10,
				f32 c01, f32 c11,
				f32 c02, f32 c12);
		
		// identity matrix
		static m2x3 identity ();
		
		// Casting operators
		
		// extend/truncate matrix of other size
		operator m2 ();
		// extend/truncate matrix of other size
		operator m3 ();
		// extend/truncate matrix of other size
		operator m4 ();
		// extend/truncate matrix of other size
		operator m3x4 ();
		// typecast
		operator f64m2x3 ();
		
		// Elementwise operators
		
		m2x3 operator+ (m2x3 m);
		m2x3 operator- (m2x3 m);
	};
	
	m2x3 operator+ (m2x3 l, m2x3 r);
	m2x3 operator- (m2x3 l, m2x3 r);
	m2x3 operator* (m2x3 l, m2x3 r);
	m2x3 operator/ (m2x3 l, m2x3 r);
} // namespace vector

