#include "linearsolve.h"
#include "matrix.h"
#include <fstream>
#include <sstream> //for ostringstream
#include <cstdlib>

int main ( void )
{

	double **a, *b, *v, **A, **B, S;
	int n, k, *index, K;

	ofstream file( "result.txt" );
	ifstream filein( "matrices.txt" );

	cout << "Decide whether you wish to" << endl;
	cout << "(1) solve a system using non-pivoting Gauss," << endl; 
	cout << "(2) invert the matrix using non-pivoting Gauss, " << endl;
	cout << "(3) solve a system using pivoting Gauss by means of an LU decomposition," << endl; 
	cout << "(4) invert the matrix using pivoting Gauss by means of an LU decomposition," << endl;
	cout << "(5) compare both methods on an array of Hilbert matrices." << endl;
	cin >> k;

	// we allocate and, if necessary, input matrices and vectors for every case
	if ( k <= 4 )
	{
		filein >> n;
		cout << "Dimension is " << n << endl;
		a = new double*[n];
		for ( int i=0; i<n; i++ )
			a[i] = new double [n];
		A = new double*[n];
		for ( int i=0; i<n; i++ )
			A[i] = new double [n];

		for ( int i=0; i<n; i++ )
		{
			for ( int j=0; j<n; j++ )
			{
				filein >> a[i][j]; 
				cout << a[i][j] << ", ";
			}
			cout << endl;
		}
		matrix_copy ( A, a, n );
	}

	if ( k == 3 || k == 4 )
	{
		index = new int[n];
		K = LUP ( a, n, index, 1.e-12 );
		if ( K != n )
		{
			cout << "One of the pivots is close to zero, hence this matrix is close to singular; please check output file" << endl;
			return 1;
		}
		cout << "LU decomposition completed successfully" << endl;
		file << "LU decomposition completed successfully: " << endl;
		write( a, n, file );
		
	}

	if ( k == 1 || k == 3 )
	{
		b = new double[n];
		v = new double[n];

		for ( int i=0; i<n; i++ )
		{
			filein >> b[i]; 
			cout << "b[" << i << "] = " << b[i] << endl;
		}
		
		copy ( v, b, n );
	}

	if ( k == 2 || k == 4 )
		B = identity_matrix( n );

	// We perform the desired procedure for every case of k
	if ( k == 1 )
	{
		if ( gauss ( a, b, n, file ) )
			cout << "The method was unsuccessful; please check the output file" << endl;
		else
		{
			try 
			{
				backward ( a, b, n, file, 1 );
			}	
			catch ( exception& e )
			{
				cout << e.what() << endl;
			}
		}
		if ( check ( A, b, v, n, 1.e-12, S ) )
			cout << "Non-pivoted solution seems to be UNsuccessful for the given tolerance: " << std::setprecision(20) << S << endl;
		else 
			cout << "Non-pivoted solution seems to be successful for the given tolerance: " << std::setprecision(20) <<  S << endl;
	}

	if ( k == 2 )
	{
		if ( matrix_invert ( a, n, file ) )
			cout << "The method was unsuccessful in inverting the matrix; please check the output file" << endl;
		else
		{
			if ( matrix_check ( A, a, B, n, 1.e-12, S ) )
				cout << "Problems with the tolerance in non-pivoted matrix inversion: " << std::setprecision(20) << S << endl;
			else 
				cout << "Non-pivoted matrix inversion succesful with respect to tolerance: " << std::setprecision(20) << S << endl;
		}
	}
	
	if ( k == 3 )
	{
		try {
			LUPforward ( a, b, n, index );
			LUPbackward ( a, b, n );
		}	
		catch (exception& e)
		{
			cout << e.what() << endl;
		}
		if ( check ( A, b, v, n, 1.e-12, S ) )
			cout << "LUP solution seems to be UNsuccessful for the given tolerance: " << std::setprecision(20) << S << endl;
		else 
			cout << "LUP solution seems to be successful for the given tolerance: " << std::setprecision(20) << S << endl;
		write_extended( a, b, n, file );
	}

	if ( k == 4 )
	{
		LUPmatrix_invert ( a, n, index, file );
		if ( matrix_check ( A, a, B, n, 1.e-12, S ) )
				cout << "Problems with the tolerance in LU matrix inversion: " << std::setprecision(20) << S << endl;
		else 
		{
			cout << "LUP matrix inversion succesful with respect to tolerance: " << std::setprecision(20) << S << endl;
			file << "LUP inversion complete:" << endl;
			matrix_write ( A, a, n, file );
		}
	}

	if ( k == 5 )
	{
		special_matrices( 20, file );
		random_matrices( 20, file );
	}

	// we de-allocate memory and close files
	if ( k <= 4 )
	{
		for ( int i=0; i<n; i++ ){
			delete [] a[i];
			delete [] A[i];
		}			
		delete[] a;
		delete[] A;
	}
	
	if ( k == 3 || k == 4 )
		delete []index;

	if ( k == 1 || k == 3 )
	{
		delete []b;
		delete []v;
	}

	if ( k == 2 || k == 4 )
	{
		for ( int i=0; i<n; i++ )
			delete [] B[i];
		delete[] B;
	}

	file.close( );
	filein.close( );

	return EXIT_SUCCESS;

}




















