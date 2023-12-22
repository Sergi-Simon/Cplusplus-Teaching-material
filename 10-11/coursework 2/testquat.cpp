/*
 *  TestQuat.cpp
 *  coursework2
 *
 *  Created by Sergi Simon on 12/04/2011.
 *  Copyright 2011 University of Portsmouth. All rights reserved.
 *
 */


#include "testquat.h"

void testconj ( ofstream& file )
{

	double n, p, q, r, s, t, u, v, norm;
	Quat Q, P, I, J, K;
	// seed for the pseudo-random generator
	srand(time(0));

	for ( int i=0; i<20; i++ )
	{
		
		file << "Testing conjugates: test number " << i << endl;
		cerr << "Testing conjugates: test number " << i << endl;
		// generate random numbers which are neither too large (e.g. larger than 20) nor equal to zero  */
		n = double( abs( rand() % 20 ) + 1 );	p = double( abs( rand() % 20 ) + 1 );
		q = double( abs( rand() % 20 ) + 1 );	r = double( abs( rand() % 20 ) + 1 );
		s = double( abs( rand() % 20 ) + 1 );	t = double( abs( rand() % 20 ) + 1 );
		u = double( abs( rand() % 20 ) + 1 );	v = double( abs( rand() % 20 ) + 1 );

		Q = Quat( n/p, q/r, s/t, u/v );
		file << "The quaternion is " << Q.qa() << "\t" << Q.qb() << "\t" << Q.qc() << "\t" << Q.qd() << endl;
		I = Quat( 0., 1., 0., 0. );
		J = Quat( 0., 0., 1., 0. );
		K = Quat( 0., 0., 0., 1. );

		P = Q + ( ( I * Q ) * I ) + ( ( J * Q ) * J ) + ( ( K * Q ) * K );
		P = P.scalar ( -0.5 );
		file << "The presumed conjugate is " << P.qa() << "\t" << P.qb() << "\t" << P.qc() << "\t" << P.qd() << endl;
		P = P - Q.conj( );
		norm = P.norm( );
		file << "The difference is " << std::setprecision(16) <<norm << endl;
		assert ( norm < 1.e-15 );
		file << "Test passed " << endl;	
	}
	file << endl;	
	return;
}



void testinv ( ofstream& file )
{

	double n, p, q, r, s, t, u, v;
	Quat Q, P, one;
	// seed for the pseudo-random generator
	srand(time(0));

	for ( int i=0; i<20; i++ )
	{
		
		file << "Testing inverses: test number " << i << endl;
		cerr << "Testing inverses: test number " << i << endl;
		// generate random numbers which are neither too large (e.g. larger than 20) nor equal to zero  */
		n = double( abs( rand() % 20 ) + 1 );	p = double( abs( rand() % 20 ) + 1 );
		q = double( abs( rand() % 20 ) + 1 );	r = double( abs( rand() % 20 ) + 1 );
		s = double( abs( rand() % 20 ) + 1 );	t = double( abs( rand() % 20 ) + 1 );
		u = double( abs( rand() % 20 ) + 1 );	v = double( abs( rand() % 20 ) + 1 );

		Q = Quat( n/p, q/r, s/t, u/v );
		file << "The quaternion is " << Q.qa() << "\t" << Q.qb() << "\t" << Q.qc() << "\t" << Q.qd() << endl;

		one = Quat ( 1., 0., 0., 0. );

		P = Q * Q.inv ( );
		file << "The product Q*Qinv is " << P.qa() << "\t" << P.qb() << "\t" << P.qc() << "\t" << P.qd() << endl;
		P = P - one;
		double norm1 = P.norm();

		P = Q.inv ( ) * Q;
		file << "The product Qinv*Q is " << P.qa() << "\t" << P.qb() << "\t" << P.qc() << "\t" << P.qd() << endl;
		P = P - one;
		double norm2 = P.norm();

		file << "The differences are " << norm1 << "\t" << std::setprecision(16) <<norm2 << endl;
		assert ( norm1 + norm2 < 1.e-15 );
		file << "Test passed " << endl;	
	}
	file << endl;	
	return;
}


void testnormscalar ( ofstream& file )
{

	double n, p, q, r, s, t, u, v, alpha;
	Quat Q, P;
	// seed for the pseudo-random generator
	srand(time(0));

	for ( int i=0; i<20; i++ )
	{
		
		file << "Testing norms of scalar products: test number " << i << endl;
		cerr << "Testing norms of scalar products: test number " << i << endl;
		// generate random numbers which are neither too large (e.g. larger than 20) nor equal to zero  */
		n = double( abs( rand() % 20 ) + 1 );	p = double( abs( rand() % 20 ) + 1 );
		q = double( abs( rand() % 20 ) + 1 );	r = double( abs( rand() % 20 ) + 1 );
		s = double( abs( rand() % 20 ) + 1 );	t = double( abs( rand() % 20 ) + 1 );
		u = double( abs( rand() % 20 ) + 1 );	v = double( abs( rand() % 20 ) + 1 );
		alpha = double( abs( rand() % 20 ) + 1 ) / double( abs( rand() % 20 ) + 1 );


		Q = Quat( n/p, q/r, s/t, u/v );
		file << "The quaternion is " << Q.qa() << "\t" << Q.qb() << "\t" << Q.qc() << "\t" << Q.qd() << endl;
		file << "The scalar is " << alpha << endl;

		P = Q.scalar ( alpha );
		double norm1 = P.norm( );
		file << "The norm of the product is " << norm1 << endl;

		double norm2 = fabs( alpha ) * Q.norm( );		
		file << "The product of norms is " << norm2 << endl;
		
		file << "The difference is " << std::setprecision(16) <<norm1 - norm2 << endl;
		assert ( fabs( norm1 - norm2 ) < 1.e-14 );
		file << "Test passed " << endl;	
	}
	file << endl;	
	return;
}




void testnormproduct ( ofstream& file )
{

	double n, p, q, r, s, t, u, v;
	double n1, p1, q1, r1, s1, t1, u1, v1;
	Quat Q, Q1, P;
	// seed for the pseudo-random generator
	srand(time(0));

	for ( int i=0; i<20; i++ )
	{
		
		file << "Testing norms of products: test number " << i << endl;
		cerr << "Testing norms of products: test number " << i << endl;
		// generate random numbers which are neither too large (e.g. larger than 20) nor equal to zero  */
		n = double( abs( rand() % 20 ) + 1 );	p = double( abs( rand() % 20 ) + 1 );
		q = double( abs( rand() % 20 ) + 1 );	r = double( abs( rand() % 20 ) + 1 );
		s = double( abs( rand() % 20 ) + 1 );	t = double( abs( rand() % 20 ) + 1 );
		u = double( abs( rand() % 20 ) + 1 );	v = double( abs( rand() % 20 ) + 1 );

		n1 = double( abs( rand() % 20 ) + 1 );	p1 = double( abs( rand() % 20 ) + 1 );
		q1 = double( abs( rand() % 20 ) + 1 );	r1 = double( abs( rand() % 20 ) + 1 );
		s1 = double( abs( rand() % 20 ) + 1 );	t1 = double( abs( rand() % 20 ) + 1 );
		u1 = double( abs( rand() % 20 ) + 1 );	v1 = double( abs( rand() % 20 ) + 1 );

		Q = Quat( n/p, q/r, s/t, u/v );
		Q1 = Quat( n1/p1, q1/r1, s1/t1, u1/v1 );
		file << "The first quaternion is " << Q.qa() << "\t" << Q.qb() << "\t" << Q.qc() << "\t" << Q.qd() << endl;
		file << "The second quaternion is " << Q1.qa() << "\t" << Q1.qb() << "\t" << Q1.qc() << "\t" << Q1.qd() << endl;
		file << "The product is " << (Q*Q1).qa() << "\t" << (Q*Q1).qb() << "\t" << (Q*Q1).qc() << "\t" << (Q*Q1).qd() << endl;

		P = Q * Q1;

		double norm1 = P.norm( );
		file << "The norm of the product is " << norm1 << endl;

		double norm2 = Q.norm( ) * Q1.norm( );		
		file << "The product of norms is " << norm2 << endl;
		
		file << "The difference is " << std::setprecision(16) << norm1 - norm2 << endl;
		assert ( fabs( norm1 - norm2 ) < 1.e-13 );
		file << "Test passed " << endl;	
	}
	file << endl;	
	return;
}



void testscalarproduct ( ofstream& file )
{

	double q, r, s, t, u, v;
	double q1, r1, s1, t1, u1, v1;
	Quat Q, Q1, P;
	// seed for the pseudo-random generator
	srand(time(0));

	for ( int i=0; i<20; i++ )
	{
		
		file << "Testing scalar products of imaginary quaternions: test number " << i << endl;
		cerr << "Testing scalar products of imaginary quaternions: test number " << i << endl;
		// generate random numbers which are neither too large (e.g. larger than 20) nor equal to zero  */
		q = double( abs( rand() % 20 ) + 1 );	r = double( abs( rand() % 20 ) + 1 );
		s = double( abs( rand() % 20 ) + 1 );	t = double( abs( rand() % 20 ) + 1 );
		u = double( abs( rand() % 20 ) + 1 );	v = double( abs( rand() % 20 ) + 1 );

		q1 = double( abs( rand() % 20 ) + 1 );	r1 = double( abs( rand() % 20 ) + 1 );
		s1 = double( abs( rand() % 20 ) + 1 );	t1 = double( abs( rand() % 20 ) + 1 );
		u1 = double( abs( rand() % 20 ) + 1 );	v1 = double( abs( rand() % 20 ) + 1 );

		Q = Quat( 0., q/r, s/t, u/v );
		Q1 = Quat( 0., q1/r1, s1/t1, u1/v1 );
		
		file << "The first quaternion is " << Q.qa() << "\t" << Q.qb() << "\t" << Q.qc() << "\t" << Q.qd() << endl;
		file << "The second quaternion is " << Q1.qa() << "\t" << Q1.qb() << "\t" << Q1.qc() << "\t" << Q1.qd() << endl;
		double scalar = Q.qa() * Q1.qa() + Q.qb() * Q1.qb() + Q.qc() * Q1.qc() + Q.qd() * Q1.qd();

		file << "The scalar product is " << scalar << endl;

		P = ( ( Q.conj() * Q1 ) + ( Q1.conj() * Q ) ).scalar ( 0.5 );
		file << "The first vector version of the scalar product is " << P.qa() << "\t" << P.qb() << "\t" << P.qc() << "\t" << P.qd() << endl;
		double first = P.qa();
		double rest1 = fabs( P.qb() + P.qc() + P.qd());

		P = ( ( Q * Q1.conj() ) + ( Q1 * Q.conj() ) ).scalar ( 0.5 );
		file << "The second vector version of the scalar product is " << P.qa() << "\t" << P.qb() << "\t" << P.qc() << "\t" << P.qd() << endl;
		double second = P.qa();
		double rest2 = fabs( P.qb() + P.qc() + P.qd());

		file << "The difference is " << std::setprecision(16) << first - scalar << "\t" << std::setprecision(16) << second - scalar << endl;
		file << "The rests are is " << std::setprecision(16) << rest1 << "\t" << std::setprecision(16) << rest2 << endl;

		assert ( fabs( first - scalar ) + fabs( second - scalar ) + fabs( rest1 ) + fabs( rest2 ) < 1.e-13 );
		file << "Test passed " << endl;	
	}
	file << endl;	
	return;
}





void testcrossproduct ( ofstream& file )
{

	double  q, r, s, t, u, v;
	double  q1, r1, s1, t1, u1, v1;
	Quat Q, Q1, P;
	// seed for the pseudo-random generator
	srand(time(0));

	for ( int i=0; i<20; i++ )
	{
		
		file << "Testing cross products of imaginary quaternions: test number " << i << endl;
		cerr << "Testing cross products of imaginary quaternions: test number " << i << endl;
		// generate random numbers which are neither too large (e.g. larger than 20) nor equal to zero  */
		q = double( abs( rand() % 20 ) + 1 );	r = double( abs( rand() % 20 ) + 1 );
		s = double( abs( rand() % 20 ) + 1 );	t = double( abs( rand() % 20 ) + 1 );
		u = double( abs( rand() % 20 ) + 1 );	v = double( abs( rand() % 20 ) + 1 );

		q1 = double( abs( rand() % 20 ) + 1 );	r1 = double( abs( rand() % 20 ) + 1 );
		s1 = double( abs( rand() % 20 ) + 1 );	t1 = double( abs( rand() % 20 ) + 1 );
		u1 = double( abs( rand() % 20 ) + 1 );	v1 = double( abs( rand() % 20 ) + 1 );

		double a1 = q/r, a2 = s/t, a3 = u/v;
		double b1 = q1/r1, b2 = s1/t1, b3 = u1/v1;

		Q = Quat( 0., a1, a2, a3 );
		Q1 = Quat( 0., b1, b2, b3 );
		
		file << "The first quaternion is " << Q.qa() << "\t" << Q.qb() << "\t" << Q.qc() << "\t" << Q.qd() << endl;
		file << "The second quaternion is " << Q1.qa() << "\t" << Q1.qb() << "\t" << Q1.qc() << "\t" << Q1.qd() << endl;
		
		Quat cross( 0., a2 * b3 - b2 * a3, b1 * a3 - a1 * b3, a1 * b2 - b1 * a2 );

		file << "The cross product is " << cross.qa() << "\t" << cross.qb() << "\t" << cross.qc() << "\t" << cross.qd() << endl;

		P = ( ( Q * Q1 ) - ( Q1.conj() * Q.conj() ) ).scalar ( 0.5 );
		file << "The cross product using quaternions is " << P.qa() << "\t" << P.qb() << "\t" << P.qc() << "\t" << P.qd() << endl;

		P = P - cross; 
		file << "The difference is " << std::setprecision(16) << P.norm() << endl;

		assert ( P.norm() < 1.e-14 );
		file << "Test passed " << endl;	
	}
	file << endl;	
	return;
}
