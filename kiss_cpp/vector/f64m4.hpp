// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"


#include <string>

#include "dv4.hpp"

namespace vector {
	
	//// matrix forward declarations
	struct f64m2;
	struct f64m3;
	struct f64m2x3;
	struct f64m3x4;
	struct m4;
	
	struct f64m4 {
		dv4 arr[4]; // column major for compatibility with OpenGL
		
		//// Accessors
		
		// get cell with r,c indecies (r=row, c=column)
		f64 get (int r, int c) const;
		// get matrix column
		dv4 get_column (int indx) const;
		// get matrix row
		dv4 get_row (int indx) const;
		
		//// Constructors
		
		f64m4 ();
		// supply one value for all cells
		f64m4 (f64 all);
		// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
		f64m4 (
				f64 c00, f64 c01, f64 c02, f64 c03,
				f64 c10, f64 c11, f64 c12, f64 c13,
				f64 c20, f64 c21, f64 c22, f64 c23,
				f64 c30, f64 c31, f64 c32, f64 c33);
		
		// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
		// supply all row vectors
		static f64m4 rows (dv4 row0, dv4 row1, dv4 row2, dv4 row3);
		// supply all cells in row major order
		static f64m4 rows (
				f64 c00, f64 c01, f64 c02, f64 c03,
				f64 c10, f64 c11, f64 c12, f64 c13,
				f64 c20, f64 c21, f64 c22, f64 c23,
				f64 c30, f64 c31, f64 c32, f64 c33);
		// supply all column vectors
		static f64m4 columns (dv4 col0, dv4 col1, dv4 col2, dv4 col3);
		// supply all cells in column major order
		static f64m4 columns (
				f64 c00, f64 c10, f64 c20, f64 c30,
				f64 c01, f64 c11, f64 c21, f64 c31,
				f64 c02, f64 c12, f64 c22, f64 c32,
				f64 c03, f64 c13, f64 c23, f64 c33);
		
		// identity matrix
		static f64m4 identity ();
		
		// Casting operators
		
		// extend/truncate matrix of other size
		operator f64m2 ();
		// extend/truncate matrix of other size
		operator f64m3 ();
		// extend/truncate matrix of other size
		operator f64m2x3 ();
		// extend/truncate matrix of other size
		operator f64m3x4 ();
		// typecast
		operator m4 ();
		
		// Elementwise operators
		
		f64m4 operator+ (f64m4 m);
		f64m4 operator- (f64m4 m);
	};
	
	f64m4 operator+ (f64m4 l, f64m4 r);
	f64m4 operator- (f64m4 l, f64m4 r);
	f64m4 operator* (f64m4 l, f64m4 r);
	f64m4 operator/ (f64m4 l, f64m4 r);
} // namespace vector
