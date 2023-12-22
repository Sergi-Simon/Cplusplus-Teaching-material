#include "linearsolve.h"
#include "matrix.h"
#include <stdexcept>
#include <cmath>

using std::domain_error;

int LUP ( double **a, int n, int *index, double Tol )
{
	
	int i, j, k, flag, dim = n;
	double aux, M, piv;
	
	// we initialise the index vector
	for ( i=0; i<n; i++ )
		index[i] = i;
	
	
	for ( k=0; k<n-1; k++ ) 
	{
		piv = a[k][k];
		flag = k;
		
		// we look for the term with the largest absolute value
		for ( i=k; i<n; i++ )
		{
			if ( fabs( a[i][k] ) > fabs( piv ) )
			{
				piv = a[i][k];
				flag = i;
			}
		}
		
		if ( fabs( piv ) < Tol )
		{
			cout << "piv = " << piv << endl;
			return ( dim - 1 );
		}
		
		// we swap rows if necessary
		if ( k != flag )
		{
			for ( j=0; j<n; j++ )
			{
				aux = a[k][j];
				a[k][j] = a[flag][j];
				a[flag][j] = aux;
			}
			index[k] = flag;
		}
		
		// we perform Gaussian elimination if pertinent
		for ( i=k+1; i<n; i++ )		
		{
			M = a[i][k] / a[k][k];
			for ( j=k+1; j<n; j++ )
				a[i][j] = a[i][j] - M*a[k][j]; 
			a[i][k] = M;
		}

	}
	
	return dim;
}

/* int LUP ( double **a, int n, int m, int *index, double Tol )
{
	
	int i, j, k, flag, dim = n, kk, K;
	double aux, M, piv;

	// we initialise the index vector
	for ( i=0; i<n; i++ )
		index[i] = i;
	
	K = 0;
	k = 0;
	kk = 0;
	
	while ( kk < m-1 && k < n-1 )
	{
		kk = k+K;
		piv = a[k][kk];
		flag = k;
		
		// we look for the term with the largest absolute value
		for ( i=k; i<n; i++ )
		{
			if ( fabs( a[i][kk] ) > fabs( piv ) )
			{
				piv = a[i][kk];
				flag = i;
			}
		}
		
		// we swap rows if necessary
		if ( k != flag )
		{
			for ( j=0; j<m; j++ )
			{
				aux = a[k][j];
				a[k][j] = a[flag][j];
				a[flag][j] = aux;
			}
			index[k] = flag;
		}

		if ( fabs( piv ) >= Tol )
		{
			for ( i=k+1; i<n; i++ )		
			{
				M = a[i][kk] / a[k][kk];
				for ( j=kk+1; j<m; j++ )
					a[i][j] = a[i][j] - M*a[k][j]; 
				a[i][kk] = M;
			}
			k ++;
		}
		if ( fabs( piv ) < Tol )
		{
			cout << "piv = " << piv << endl;
			K += 1;
		}
	}

	dim = 2 * m - n - K;
	
	return dim;
}
 */

int LUPmatrix_invert ( double **a, int n, int *index, ofstream& file )
{
	int i, j;
	double **B, *E;

	B = new double*[n];
	for ( int i=0; i<n; i++ )
		B[i] = new double [n];

	E = new double[n];

	for ( j=0; j<n; j++ )
	{
		canonical( E, n, j );
		LUPforward ( a, E, n, index );
		LUPbackward ( a, E, n );
		for ( i=0; i<n; i++ )
			B[i][j] = E[i];
	}
	
	matrix_copy( a, B, n );	
	file << "The inverse using Gauss with pivoting is :" << endl;
	write ( B, n, file );
	
	delete []E;
	for ( int i=0; i<n; i++ )
		delete [] B[i];
	delete[] B;
	
	return 0;
}

void LUPbackward ( double **u, double *b, int n )
{
	int i, j;

	for ( i=n-1; i>=0; i-- )
	{
		for ( j=i+1; j<n; j++ )
			b[i] = b[i] - u[i][j] * b[j];
		b[i] = b[i] / u[i][i];
	}

	return;	
}

void LUPforward ( double **L, double *b, int n, int *index )
{
	int i, j;
	double aux, s;  

	for ( i=0; i<n; i++ )
	{
		if ( index[i] != i )
		{
			aux = b[i]; 
			b[i] = b[index[i]];
			b[index[i]] = aux;
		}
	}
	
	for ( i=0; i<n; i++ )
	{		
		s = 0.;
		for ( j=0; j<i; j++ )
			s += L[i][j] * b[j]; 
		b[i] = b[i] - s;
	}
	
	return;
	
}
