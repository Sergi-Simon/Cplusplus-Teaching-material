#include "linearsolve.h"
#include "matrix.h"
#include <stdexcept>
#include <cmath>

int special_matrices ( int n_max, ofstream& file )
{
	int *index;
	double **a, **A, **B, s1, s2;

	index = new int[n_max];
	a = new double*[n_max];
	for ( int i=0; i<n_max; i++ )
		a[i] = new double [n_max];
	A = hilbert( n_max );
	//A = other( n_max );
	B = identity_matrix( n_max );

	ofstream fileinverses;
	fileinverses.open( "inverses.txt" );
	file << "n\t Norm without pivoting \t Norm with pivoting" << endl;
	for ( int n = 2; n<= n_max; n++ )
	{			
		// Gauss without pivoting
		matrix_copy ( a, A, n );
		matrix_invert ( a, n, fileinverses ); // a = inverse of A
//		matrix_product ( A, a, n ); // a = A.a
//		matrix_difference ( B, a, n ); // a = B - a
		matrix_check ( A, a, B, n, 1.e-16, s1 );
//		double s1 = matrix_norm ( a, n );  // s1 = ||a|| 
		
		// Gauss with pivoting
		matrix_copy ( a, A, n );
		int K = LUP ( a, n, index, 1.e-18 );
		if ( K != n )
		{
			cout << "One of the pivots is close to zero, hence this matrix is close to singular; please check output file" << endl;
			return 1;
		}
		cout << "LU decomposition completed successfully" << endl;
		LUPmatrix_invert ( a, n, index, fileinverses ); // a = inverse of A
//		matrix_product ( A, a, n ); // a = A.a
//		matrix_difference ( B, a, n );  // a = B - a
//		s2 = matrix_norm ( a, n ); // s2 = ||a|| 
		matrix_check ( A, a, B, n, 1.e-16, s2 );
		// we write down the values on the file
		file << n << "\t"  << std::setprecision(20) <<  s1 << "\t"  << std::setprecision(20) <<  s2 << endl; 
	}
	fileinverses.close();
	delete []index;
	for ( int i=0; i<n_max; i++ ){
		delete [] a[i];
		delete [] A[i];
		delete [] B[i];
	}
	delete[] a;
	delete[] A;
	delete[] B;

	return 0;
}

int random_matrices ( int n_max, ofstream& file )
{
	int *index;
	int uiui;
	double **a, **A, **a1, **B, *b, s1, s2;
	
	index = new int[n_max];
	a = new double*[n_max];
	for ( int i=0; i<n_max; i++ )
		a[i] = new double [n_max];	
	a1 = new double*[n_max];
	for ( int i=0; i<n_max; i++ )
		a1[i] = new double [n_max];
	b = new double[n_max];
	for ( int i=0; i<n_max; i++ )
		b[i] = 0.;
	A = random( n_max );
	B = identity_matrix( n_max );
	matrix_copy ( a, A, n_max ); matrix_copy ( a1, A, n_max );
	file << "Preparing the matrix " << endl;
	while ( LUP ( a, n_max, index, 1.e-18 ) != n_max && gauss ( a1, b, n_max, file ) != 0 )
	{
		cout << "uiui" << uiui << endl;
		for ( int i=0; i<n_max; i++ )
			A[i][i] += 1.;
		matrix_copy ( a, A, n_max ); matrix_copy ( a1, A, n_max );
	}
	ofstream fileinverses;
	fileinverses.open( "inverses.txt" );
	fileinverses << "The original matrix is" << endl;
	write ( A, n_max, fileinverses );
	file << "n\t Norm without pivoting \t Norm with pivoting" << endl;
	for ( int n = 2; n<= n_max; n++ )
	{			
		matrix_copy ( a, A, n );		matrix_copy ( a1, A, n );

		// Gauss without pivoting
		matrix_invert ( a, n, fileinverses ); // a = inverse of A
		matrix_check ( A, a, B, n, 1.e-16, s1 );
		
		// Gauss with pivoting
		matrix_copy ( a1, A, n );
		int K = LUP ( a1, n, index, 1.e-18 );
		if ( K != n )
		{
			cout << "One of the pivots is close to zero, hence this matrix is close to singular; please check output file" << endl;
			return 1;
		}
		cout << "LU decomposition completed successfully" << endl;
		LUPmatrix_invert ( a1, n, index, fileinverses ); // a = inverse of A
		matrix_check ( A, a1, B, n, 1.e-16, s2 );

		// we write down the values on the file
		file << n << "\t"  << std::setprecision(20) <<  s1 << "\t"  << std::setprecision(20) <<  s2 << endl; 
	}
	fileinverses.close();
	delete []index;
	delete []b;
	for ( int i=0; i<n_max; i++ ){
		delete [] a[i];
		delete [] a1[i];
		delete [] A[i];
		delete [] B[i];
	}
	delete[] a;
	delete[] a1;
	delete[] A;
	delete[] B;
	
	return 0;
}
