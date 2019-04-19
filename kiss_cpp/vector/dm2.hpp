// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

#include "dv2.hpp"

namespace vector {
	
	//// matrix forward declarations
	struct dm3;
	struct dm4;
	struct dm2x3;
	struct dm3x4;
	struct fm2;
	
	struct dm2 {
		dv2 arr[2]; // column major for compatibility with OpenGL
		
		//// Accessors
		
		// get cell with r,c indecies (r=row, c=column)
		f64 const& get (int r, int c) const;
		// get matrix column
		dv2 const& get_column (int indx) const;
		// get matrix row
		dv2 get_row (int indx) const;
		
		//// Constructors
		
		dm2 ();
		// supply one value for all cells
		explicit dm2 (f64 all);
		// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
		explicit dm2 (
				f64 c00, f64 c01,
				f64 c10, f64 c11);
		
		// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
		// supply all row vectors
		static dm2 rows (dv2 row0, dv2 row1);
		// supply all cells in row major order
		static dm2 rows (
				f64 c00, f64 c01,
				f64 c10, f64 c11);
		// supply all column vectors
		static dm2 columns (dv2 col0, dv2 col1);
		// supply all cells in column major order
		static dm2 columns (
				f64 c00, f64 c10,
				f64 c01, f64 c11);
		
		// identity matrix
		static dm2 identity ();
		
		// Casting operators
		
		// extend/truncate matrix of other size
		operator dm3 ();
		// extend/truncate matrix of other size
		operator dm4 ();
		// extend/truncate matrix of other size
		operator dm2x3 ();
		// extend/truncate matrix of other size
		operator dm3x4 ();
		// typecast
		operator fm2 ();
		
		// Elementwise operators
		
		dm2& operator+= (f64 r);
		dm2& operator-= (f64 r);
		dm2& operator*= (f64 r);
		dm2& operator/= (f64 r);
		
		// Matrix multiplication
		
		dm2& operator*= (dm2 const& r);
	};
	
	// Elementwise operators
	
	dm2 operator+ (dm2 const& m);
	dm2 operator- (dm2 const& m);
	
	dm2 operator+ (dm2 const& l, dm2 const& r);
	dm2 operator+ (dm2 const& l, f64 r);
	dm2 operator+ (f64 l, dm2 const& r);
	
	dm2 operator- (dm2 const& l, dm2 const& r);
	dm2 operator- (dm2 const& l, f64 r);
	dm2 operator- (f64 l, dm2 const& r);
	
	dm2 mul_elementwise (dm2 const& l, dm2 const& r);
	dm2 operator* (dm2 const& l, f64 r);
	dm2 operator* (f64 l, dm2 const& r);
	
	dm2 div_elementwise (dm2 const& l, dm2 const& r);
	dm2 operator/ (dm2 const& l, f64 r);
	dm2 operator/ (f64 l, dm2 const& r);
	
	// Matrix multiplication
	
	dm2 operator* (dm2 const& l, dm2 const& r);
	dm2x3 operator* (dm2 const& l, dm2x3 const& r);
	dv2 operator* (dm2 const& l, dv2 r);
	dv2 operator* (dv2 l, dm2 const& r);
} // namespace vector
