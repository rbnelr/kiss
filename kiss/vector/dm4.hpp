// generated by C:\Users\Me\Desktop\kiss\vector_srcgen\srcgen.py
#pragma once

#include "kissmath.hpp"

#include "dv4.hpp"

namespace vector {
	
	//// matrix forward declarations
	struct dm2;
	struct dm3;
	struct dm2x3;
	struct dm3x4;
	struct fm4;
	
	struct dm4 {
		dv4 arr[4]; // column major for compatibility with OpenGL
		
		//// Accessors
		
		
		// get cell with r,c indecies (r=row, c=column)
		inline FORCEINLINE f64 const& get (int r, int c) const {
			return arr[c][r];
		}
		
		// get matrix column
		inline FORCEINLINE dv4 const& get_column (int indx) const {
			return arr[indx];
		}
		// get matrix row
		dv4 get_row (int indx) const;
		
		//// Constructors
		
		
		inline FORCEINLINE dm4 () {
			
		}
		
		// supply one value for all cells
		inline FORCEINLINE explicit dm4 (f64 all): 
		arr{dv4(all, all, all, all),
			dv4(all, all, all, all),
			dv4(all, all, all, all),
			dv4(all, all, all, all)} {
			
		}
		
		// supply all cells, in row major order for readability -> c<r><c> (r=row, c=column)
		inline FORCEINLINE explicit dm4 (f64 c00, f64 c01, f64 c02, f64 c03,
										 f64 c10, f64 c11, f64 c12, f64 c13,
										 f64 c20, f64 c21, f64 c22, f64 c23,
										 f64 c30, f64 c31, f64 c32, f64 c33): 
		arr{dv4(c00, c10, c20, c30),
			dv4(c01, c11, c21, c31),
			dv4(c02, c12, c22, c32),
			dv4(c03, c13, c23, c33)} {
			
		}
		
		// static rows() and columns() methods are preferred over constructors, to avoid confusion if column or row vectors are supplied to the constructor
		// supply all row vectors
		static dm4 rows (dv4 row0, dv4 row1, dv4 row2, dv4 row3);
		// supply all cells in row major order
		static dm4 rows (f64 c00, f64 c01, f64 c02, f64 c03,
						 f64 c10, f64 c11, f64 c12, f64 c13,
						 f64 c20, f64 c21, f64 c22, f64 c23,
						 f64 c30, f64 c31, f64 c32, f64 c33);
		// supply all column vectors
		static dm4 columns (dv4 col0, dv4 col1, dv4 col2, dv4 col3);
		// supply all cells in column major order
		static dm4 columns (f64 c00, f64 c10, f64 c20, f64 c30,
							f64 c01, f64 c11, f64 c21, f64 c31,
							f64 c02, f64 c12, f64 c22, f64 c32,
							f64 c03, f64 c13, f64 c23, f64 c33);
		
		
		// identity matrix
		static inline FORCEINLINE dm4 identity () {
			return dm4(1,0,0,0,
					   0,1,0,0,
					   0,0,1,0,
					   0,0,0,1);
		}
		
		// Casting operators
		
		// extend/truncate matrix of other size
		explicit operator dm2 () const;
		// extend/truncate matrix of other size
		explicit operator dm3 () const;
		// extend/truncate matrix of other size
		explicit operator dm2x3 () const;
		// extend/truncate matrix of other size
		explicit operator dm3x4 () const;
		// typecast
		explicit operator fm4 () const;
		
		// Elementwise operators
		
		dm4& operator+= (f64 r);
		dm4& operator-= (f64 r);
		dm4& operator*= (f64 r);
		dm4& operator/= (f64 r);
		
		// Matrix multiplication
		
		dm4& operator*= (dm4 const& r);
	};
	
	// Elementwise operators
	
	dm4 operator+ (dm4 const& m);
	dm4 operator- (dm4 const& m);
	
	dm4 operator+ (dm4 const& l, dm4 const& r);
	dm4 operator+ (dm4 const& l, f64 r);
	dm4 operator+ (f64 l, dm4 const& r);
	
	dm4 operator- (dm4 const& l, dm4 const& r);
	dm4 operator- (dm4 const& l, f64 r);
	dm4 operator- (f64 l, dm4 const& r);
	
	dm4 mul_elementwise (dm4 const& l, dm4 const& r);
	dm4 operator* (dm4 const& l, f64 r);
	dm4 operator* (f64 l, dm4 const& r);
	
	dm4 div_elementwise (dm4 const& l, dm4 const& r);
	dm4 operator/ (dm4 const& l, f64 r);
	dm4 operator/ (f64 l, dm4 const& r);
	
	// Matrix ops
	
	dm4 operator* (dm4 const& l, dm4 const& r);
	dv4 operator* (dm4 const& l, dv4 r);
	dv4 operator* (dv4 l, dm4 const& r);
	dm4 transpose (dm4 const& m);
	
	f64 det (dm4 const& mat);
	dm4 inverse (dm4 const& mat);
} // namespace vector
