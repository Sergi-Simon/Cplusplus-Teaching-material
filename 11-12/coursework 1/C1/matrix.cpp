#include <cmath>
#include <iostream>
#include "matrix.h"

using std::endl;
using std::cout;

double **identity_matrix ( int n )
{

	double **B;
	B = new double*[n];
	for ( int i=0; i<n; i++ )
		B[i] = new double [n];

	for ( int i=0; i<n; i++ )
	{
		B[i][i] = 1.;
		for ( int j = 0; j<n; j++ )
		{
			if ( i!=j )
				B[i][j] = 0.;
		}
	}
	return B;

}

void canonical ( double *E, int n, int j )
{
	for ( int i=0; i<n; i++ )
	{
		if ( i == j )
			E[i] = 1.;
		if ( i != j )
			E[i] = 0.;
	}

	return;
}
	
void copy ( double *V, double *v, int n )
{
	int i;
	for ( i=0; i<n; i++ )
	{
		V[i] = v[i];
	}
	
	return;
	
}

void matrix_copy ( double **A, double **a, int n )
{
	int i, j;
	for ( i=0; i<n; i++ )
	{
		for ( j=0; j<n; j++ )
			A[i][j] = a[i][j];
	}
	
	return;
	
}

void write ( double **a, int n, ofstream& file )
{
	int i, j; 
	
	file << endl;
	for ( i=0; i<n; i++ )
	{
		for ( j=0; j<n; j++ )
			file  << std::setprecision(20) <<  a[i][j] << " "; 
		file  << std::setprecision(20) <<  endl;
	}
	
	return;
}

void write_extended ( double **a, double *b, int n, ofstream& file )
{
	int i, j; 
	
	file << endl;
	for ( i=0; i<n; i++ )
	{
		for ( j=0; j<n; j++ )
			file  << std::setprecision(20) <<  a[i][j] << " ";
		file  << std::setprecision(20) <<  b[i] << endl;
	}
	
	return;

}


void matrix_write ( double **a, double **b, int n, ofstream& file )
{
	int i, j; 

	file << endl;
	file << "Matrix A: " << endl;
	for ( i=0; i<n; i++ )
	{
		for ( j=0; j<n; j++ )
			file  << std::setprecision(20) <<  a[i][j] << " "; 
		file << endl;
	}

	file << endl;
	file << "Matrix B: " << endl;
	for ( i=0; i<n; i++ )
	{
		for ( j=0; j<n; j++ )
			file  << std::setprecision(20) << b[i][j] << " "; 
		file << endl;
	}
	return;
}

double norm ( double *x, int n )
{
	double max = 0.;
	for ( int i=0; i<n; i++ )
	{
		if ( max < fabs( x[i] ) )
			max = fabs ( x[i] );
	}
	return ( max );
}

// function checking that ( a )x = b
int check ( double **a, double *x, double *b, int n, double tol, double &S )
{
	double *r, s;
	r = new double[n];

	for ( int i=0; i<n; i++ )
	{
		s = 0.;
		for ( int j = 0; j<n; j++ )
			s += a[i][j] * x[j];
		r[i] = s - b[i];
	}

	S = norm ( r, n );
	cout << S << endl;

	delete []r;

	if ( S >= tol )
		return 1;
	return 0;
}

double matrix_norm ( double **a, int n )
{
	int i, j; 
	double s, max = 0;

/*	for ( i=0; i<n; i++ )
	{
		for ( j=0; j<n; j++ )
			s += a[i][j] * a[i][j];
		
	}*/
	
	for ( i=0; i<n; i++ )
	{
		s = 0.;
		for ( j=0; j<n; j++ )
			s += fabs( a[i][j] );
		if ( s > max )
			max = s;
	}
	return s;
	
}

// function checking that ( a )( x ) = ( b )
int matrix_check ( double **a, double **x, double **b, int n, double tol, double& S )
{
	double **r, s;
	r = new double*[n];
	for ( int i=0; i<n; i++ )
		r[i] = new double[n];

	for ( int i=0; i<n; i++ )
	{
		for ( int j = 0; j<n; j++ )
		{
			s = 0.;
			for ( int k = 0; k<n; k++ )
				s += a[i][k] * x[k][j];
			r[i][j] = s - b[i][j];
		}
	}

	S = matrix_norm ( r, n );

	for ( int i=0; i<n; i++ )
		delete [] r[i];
	delete []r;

	if ( S >= tol )
		return 1;
	return 0;
}

double **hilbert ( int n )
{
	double **B;
	B = new double*[n];
	for ( int i=0; i<n; i++ )
		B[i] = new double [n];

	for ( int i=0; i<n; i++ )
	{
		for ( int j = 0; j<n; j++ )
		{
			B[i][j] = 1. / ( ( double )( i + j + 1 ) );
		}
	}
	return B;
}

double **other ( int n )
{
	double **B;
	B = new double*[n];
	for ( int i=0; i<n; i++ )
		B[i] = new double [n];
	
	for ( int i=0; i<n; i++ )
	{
		for ( int j = 0; j<n; j++ )
		{
			double aux = ( double )( i-j );
			aux = ( double )( n ) - fabs( aux );
			B[i][j] = aux*aux;
		}
//		B[i][i] += fabs( (double)( i ));
	}
	return B;
}

// function replacing the second argument ( b ) by the difference ( a ) - ( b )
void matrix_difference ( double **a, double **b, int n )
{
	int i, j;
	for ( i=0; i<n; i++ )
		for ( j=0; j<n; j++ )
			b[i][j] = a[i][j] - b[i][j];
	return;
}

// function replacing the second argument ( b ) by the difference ( a ) - ( b )
void matrix_product ( double **a, double **b, int n )
{
	double **r, s;
	r = new double*[n];
	for ( int i=0; i<n; i++ )
		r[i] = new double[n];

	for ( int i=0; i<n; i++ )
	{
		for ( int j = 0; j<n; j++ )
		{
			s = 0.;
			for ( int k = 0; k<n; k++ )
				s += a[i][k] * b[k][j];
			r[i][j] = s;
		}
	}
	matrix_copy( b, r, n );
	
	for ( int i=0; i<n; i++ )
		delete [] r[i];
	delete []r;

	return;
}

long int factorial ( long int n )
{
	if ( n <= 1 )
		return 1;
	return ( n*factorial( n - 1 ) );
}

double **random ( int n )
{
	double **B;
	B = new double*[n];
	for ( int i=0; i<n; i++ )
		B[i] = new double [n];
	
	srand(time(0));
	for ( int i=0; i<n; i++ )
	{
		for ( int j=0; j<n; j++ )
		{
			int K = abs( rand() % n );
			B[i][j] = ( double )( K );
		}
	}
	return B;
	
}