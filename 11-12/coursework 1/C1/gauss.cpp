#include "linearsolve.h"
#include "matrix.h"
#include <cmath>


int gauss ( double **a, double *b, int n, ofstream& file )
{
	int i, j, k;
	double tol = 1.e-16, m;
	
	file << "The matrix is: " << endl;
	write ( a, n, file );
	file << endl;
	file << endl;

	for ( k=0; k<n-1; k++ )
	{
		if ( fabs( a[k][k] ) >= tol )
		{
			for ( i=k+1; i<n; i++ )		
			{
				m = a[i][k] / a[k][k];
				b[i] = b[i] - m*b[k];
				for ( j=0; j<n; j++ )
				{
					a[i][j] = a[i][j] - m*a[k][j]; 
				}
			}
			file << "Step " << k << " of the elimination process is complete:" << endl;
			write_extended ( a, b, n, file );
		}
		else
		{
			file << "Pivot n." << k << " is close to zero, hence this step of gaussian elimination was not possible: " << fabs( a[k][k] ) << endl;
			return ( 1 );
		}
	}

	return 0;
}


void backward ( double **u, double *v, int n, ofstream& file, int flag )
{

	int i, j;
	double s; 

	if ( flag == 1 )
		file << "The entries of the solution are the following: " << endl;
	for ( i=n-1; i>=0; i-- )
	{
		s = 0.;
		for ( j=i+1; j<n; j++ )
				s += u[i][j] * v[j]; 
		v[i] = ( v[i] - s ) / u[i][i]; 
		if ( flag == 1 )
			file << "x[" << i << "]= " << v[i] << endl;
	}

	return;
}

int matrixgauss ( double **a, double **b, int n, ofstream& file )
{
	int i, j, k;
	double tol = 1.e-16, m;

	for ( k=0; k<n-1; k++ )
	{
		if ( fabs( a[k][k] ) >= tol )
		{
			for ( i=k+1; i<n; i++ )		
			{
				m = a[i][k] / a[k][k];
				for ( j=0; j<n; j++ )
				{
					a[i][j] = a[i][j] - m*a[k][j]; 
					b[i][j] = b[i][j] - m*b[k][j];
				}
			}
			file << "Step " << k << " of the elimination process is complete:" << endl;
			matrix_write ( a, b, n, file );
		}
		else
		{
			file << "Pivot n." << k << " is close to zero, hence this step of gaussian elimination was not possible: " << fabs( a[k][k] ) << endl;
			return ( 1 );
		}
	}

	return 0;
}

int matrix_invert ( double **a, int n, ofstream& file )
{

	double **B, *E;
	
	E = new double[n];
	B = identity_matrix( n );
	
	if ( matrixgauss ( a, B, n, file ) )
	{
		cout << "The method was unsuccessful; please check the output file" << endl;
		return 1;
	}
	else
	{
		for ( int j = 0; j<n; j++ )
		{
			for ( int i = 0; i<n; i++ )
				E[i] = B[i][j];
			try 
			{
				backward ( a, E, n, file, 0 );
				for ( int i=0; i<n; i++ )
					B[i][j] = E[i];
			}	
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
		}	
		matrix_copy ( a, B, n );
		write( a, n, file );
	}

	delete []E;
	for ( int i=0; i<n; i++ )
		delete [] B[i];
	delete[] B;
	
	return 0;
	
}
