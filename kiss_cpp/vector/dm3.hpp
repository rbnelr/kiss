// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

#include "dv3.hpp"

namespace vector {
	
	//// matrix forward declarations
	struct dm2;
	struct dm4;
	struct dm2x3;
	struct dm3x4;
	struct fm3;
	
	struct dm3 {
		dv3 arr[3]; // column major for compatibility with OpenGL
		
		//// Accessors
		
		// get cell with r,c indecies (r=row, c=column)
		f64 const& get (int r, int c) const;
		// get matrix column
		dv3 const& get_column (int indx) const;
		// get matrix row
		dv3 get_row (int indx) const;
		
		//// Constructors
		
		dm3 ();
		// supply one value for all cells
		explicit dm3 (f64 all);
		// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
		explicit dm3 (
				f64 c00, f64 c01, f64 c02,
				f64 c10, f64 c11, f64 c12,
				f64 c20, f64 c21, f64 c22);
		
		// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
		// supply all row vectors
		static dm3 rows (dv3 row0, dv3 row1, dv3 row2);
		// supply all cells in row major order
		static dm3 rows (
				f64 c00, f64 c01, f64 c02,
				f64 c10, f64 c11, f64 c12,
				f64 c20, f64 c21, f64 c22);
		// supply all column vectors
		static dm3 columns (dv3 col0, dv3 col1, dv3 col2);
		// supply all cells in column major order
		static dm3 columns (
				f64 c00, f64 c10, f64 c20,
				f64 c01, f64 c11, f64 c21,
				f64 c02, f64 c12, f64 c22);
		
		// identity matrix
		static dm3 identity ();
		
		// Casting operators
		
		// extend/truncate matrix of other size
		operator dm2 ();
		// extend/truncate matrix of other size
		operator dm4 ();
		// extend/truncate matrix of other size
		operator dm2x3 ();
		// extend/truncate matrix of other size
		operator dm3x4 ();
		// typecast
		operator fm3 ();
		
		// Elementwise operators
		
		dm3& operator+= (f64 r);
		dm3& operator-= (f64 r);
		dm3& operator*= (f64 r);
		dm3& operator/= (f64 r);
		
		// Matrix multiplication
		
		dm3& operator*= (dm3 const& r);
	};
	
	// Elementwise operators
	
	dm3 operator+ (dm3 const& m);
	dm3 operator- (dm3 const& m);
	
	dm3 operator+ (dm3 const& l, dm3 const& r);
	dm3 operator+ (dm3 const& l, f64 r);
	dm3 operator+ (f64 l, dm3 const& r);
	
	dm3 operator- (dm3 const& l, dm3 const& r);
	dm3 operator- (dm3 const& l, f64 r);
	dm3 operator- (f64 l, dm3 const& r);
	
	dm3 mul_elementwise (dm3 const& l, dm3 const& r);
	dm3 operator* (dm3 const& l, f64 r);
	dm3 operator* (f64 l, dm3 const& r);
	
	dm3 div_elementwise (dm3 const& l, dm3 const& r);
	dm3 operator/ (dm3 const& l, f64 r);
	dm3 operator/ (f64 l, dm3 const& r);
	
	// Matrix multiplication
	
	dm3 operator* (dm3 const& l, dm3 const& r);
	dm3x4 operator* (dm3 const& l, dm3x4 const& r);
	dv3 operator* (dm3 const& l, dv3 r);
	dv3 operator* (dv3 l, dm3 const& r);
} // namespace vector
