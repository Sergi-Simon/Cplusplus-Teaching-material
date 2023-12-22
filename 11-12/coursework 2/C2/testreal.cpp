/*
 *  testreal.cpp
 *  C2
 *
 *  Created by Sergi Simon on 21/03/2012.
 *  Copyright 2012 University of Portsmouth. All rights reserved.
 *
 */

#include "testreal.h"


void test_inverse ( ofstream& file, long digits )
{
	real A, B, C, D; 
	
	file << "Testing the inverse: " << endl;	
	cout << "Testing the inverse: " << endl;

	for ( long int k = -20; k < 20; k++ )
	{
		if ( k == 0 )
			continue;
		A = inverse ( k, digits );
		B = real ( k );
		C = A*B;
		C.cap( ); 
		D = C - real ( 1,digits );
		cout << D << endl;
		long dt = D.Tol_digit( );
		cout << dt << endl;
		assert ( dt >= 14 );
		file << "1/" << k << " : " << dt << " " << A << endl;
	}

	cout << "Successfully tested inverse and product: " << endl;
	
	file << "Testing inverse and product: " << endl;
	cout << "Testing inverse and product: " << endl;
	for ( long int k = -200; k < 200; k++ )
	{
		double K = ( double )k;
		for ( long int j = -200; j < 200; j++ )
		{
			if( j == 0 )
				continue;
			
			double J = ( double )j;
			double KJ = K/J;
			A = real ( KJ, digits );
			B = inverse( j, digits );
			C = real( k );
			C = C*B;
			C.cap();
			
			D = C - A;
			D.cap( );
			long dt = D.Tol_digit( );
			assert ( dt >= 15 );
			file << k << "/" << j << ": " << " ~ 1.e-" << dt << " " << endl;
		}
	}
	cout << "Successfully tested inverse and product: " << endl;
	
	return;	
}

void test_sum ( ofstream& file, long digits )
{
	real A, B, C, D; 
	
	file << "Testing the sums: " << endl;
	cout << "Testing the sums: " << endl;
	srand(time(0));
	
	for ( long int k = -20; k < 20; k++ )
	{

		double K = ( double )k;
		for ( long int j = -20; j < 20; j++ )
		{
			if( j == 0 )
				continue;

			double J = ( double )j;
			double KJ = K/J;
			
			A = real ( KJ, digits );
			assert( fabs(  A.Double( ) - KJ  ) <= 1.e-14 );

			double k1 = ( double )( abs( rand() % 20 ) + 1 );
			double k2 = ( double )( abs( rand() % 20 ) + 1 );
			double L = k1/k2;
			
			B = real( L, digits );
			assert( fabs(  B.Double( ) - L  ) <= 1.e-14 );

			double res = KJ + L;
			B = A+B;
			assert( fabs(  B.Double( ) - res  ) <= 1.e-14 );

			C = real( res, digits ); 
			assert( fabs(  C.Double( ) - res  ) <= 1.e-14 );

			D = C - B;
			assert( fabs(  D.Double( ) ) <= 1.e-14 );
			D.cap( );
			long dt = D.Tol_digit( );
			assert ( dt >= 15 );
			
			file << L << "+" << KJ << ": " << " ~ 1.e-" << dt << " " << endl;
			
		}
	}
	cout << "Successfully tested sum " << endl;
	
	return;
	
}


void test_subtract ( ofstream& file, long digits )
{
	real A, B, C, D; 
	
	file << "Testing the substractions: " << endl;
	cout << "Testing the substractions: " << endl;
	srand(time(0));
	
	for ( long int k = -20; k < 20; k++ )
	{

		double K = ( double )k;
		for ( long int j = -20; j < 20; j++ )
		{
			if( j == 0 )
				continue;

			double J = ( double )j;
			double KJ = K/J;
			A = real ( KJ, digits );
			// cout << fabs(  A.Double( ) - KJ  ) << endl;
			assert( fabs(  A.Double( ) - KJ  ) <= 1.e-14 );
			
			double k1 = ( double )( abs( rand() % 20 ) + 1 );
			double k2 = ( double )( abs( rand() % 20 ) + 1 );
			double L = k1/k2;
			B = real( L, digits );
			assert( fabs(  B.Double( ) - L  ) <= 1.e-14 );

			double res = L - KJ;
			B = B-A;
			assert( fabs(  B.Double( ) - res  ) <= 1.e-14 );
			
			C = real( L - KJ, digits ); 
			assert( fabs(  C.Double( ) - res  ) <= 1.e-14 );
			
			D = C - B;
			assert( fabs(  D.Double( ) ) <= 1.e-14 );
			D.cap( );
//			cout << "L - K/J   " << res;
//			cout << " res = " << C.Double() << endl;
			long dt = D.Tol_digit( );
//			cout << dt << endl;
			assert ( dt >= 15 );
			
			file << L << "+" << K/J << ": " << " ~ 1.e-" << dt << " " << endl;
			//		file << "Double version: " << L << "+" << K/J << ": " << " ~ 1.e-" << dt << " " << endl;
			
		}
	}
	cout << "Successfully tested substractions " << endl;
	
	return;
}

void test_product ( ofstream& file, long digits )
{
	real A, B, C, D; 
	
	file << "Testing the products: " << endl;
	cout << "Testing the products: " << endl;
	srand(time(0));
	
	for ( long int k = -20; k < 20; k++ )
	{
		
		double K = ( double )k;
		for ( long int j = -20; j < 20; j++ )
		{
			if( j == 0 )
				continue;
			
			double J = ( double )j;
			double KJ = K/J;
			
			A = real ( KJ, digits );
			assert( fabs(  A.Double( ) - KJ  ) <= 1.e-14 );
			
			double k1 = ( double )( abs( rand() % 50 ) + 1 );
			double k2 = ( double )( abs( rand() % 50 ) + 1 );
			double L = k1/k2;
			
			B = real( L, digits );
			assert( fabs(  B.Double( ) - L  ) <= 1.e-14 );
			
			double res = KJ * L;
			B = A*B;
			// cout << B.Double( ) - res << endl;
			assert( fabs(  B.Double( ) - res  ) <= 1.e-14 );
			
			C = real( res, digits ); 
			assert( fabs(  C.Double( ) - res  ) <= 1.e-14 );
			
			D = C - B;
			// cout << "C=" << std::setprecision( 20 ) <<  C << "B=" << std::setprecision( 20 ) <<   B << "D=" << std::setprecision( 20 ) <<   D << endl;
			assert( fabs(  D.Double( ) ) <= 1.e-14 );
			long dt = D.Tol_digit( );
			assert ( dt >= 15 );
			
			file << L << "+" << KJ << ": " << " ~ 1.e-" << dt << " " << endl;
			
		}
	}
	cout << "Successfully tested products " << endl;
	
	return;
}
