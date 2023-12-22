/*
 *  quat.cpp
 *  coursework2
 *
 *  Created by Sergi Simon on 04/04/2011.
 *  Copyright 2011 University of Portsmouth. All rights reserved.
 *
 */


#include "quat.h"

// 1. Default constructor
Quat::Quat ( void )
{
	a = 0.;
	b = 0.;
	c = 0.;
	d = 0.;
	return;
}
// 1. New constructor
Quat::Quat ( double A, double B, double C, double D )
{
	a = A;
	b = B;
	c = C;
	d = D;
	return;
}

// 2. Copy constructor 
Quat::Quat ( const Quat& other )
{

	a = other.a;
	b = other.b;
	c = other.c;
	d = other.d;
	return;
}

// 3. Assignment operator: assigns this object the value of another
Quat& Quat::operator =( const Quat& other )
{
	// Standard self - assignment avoidance technique
	if ( this != &other )
	{
		a = other.a;
		b = other.b;
		c = other.c;
		d = other.d;
	}		
	// Return a reference to current object in order to allow assignment chaining
	return *this ;
}

// 4. Destructor 
// Destroy an object 
Quat::~ Quat ()
{
	// Nothing needed here .
	return;
}

// 5. Inspector functions 
double Quat::qa ( void ) const
{
	return a;
}

double Quat::qb ( void ) const
{
	return b;
}

double Quat::qc ( void ) const
{
	return c;
}

double Quat::qd ( void ) const
{
	return d;
}


// 6. Basic arithmetic 
Quat Quat::operator +( const Quat Q  ) const
{
	Quat Temp;

	Temp.a = a + Q.a;
	Temp.b = b + Q.b;
	Temp.c = c + Q.c;
	Temp.d = d + Q.d;

	return Temp; 
}

Quat Quat::operator -( const Quat Q  ) const
{
	Quat Temp;

	Temp.a = a - Q.a;
	Temp.b = b - Q.b;
	Temp.c = c - Q.c;
	Temp.d = d - Q.d;

	return Temp; 
}

Quat Quat::operator *( const Quat Q ) const
{

	Quat Temp;
	double x = Q.a, y = Q.b, z = Q.c, t = Q.d;

	Temp.a = ( a * x ) - ( b * y ) - ( c * z ) - ( d * t );
	Temp.b = ( a * y ) + ( b * x ) + ( c * t ) - ( d * z );
	Temp.c = ( a * z ) + ( c * x ) + ( d * y ) - ( b * t );
	Temp.d = ( a * t ) + ( d * x ) + ( b * z ) - ( c * y );

	return Temp; 
}	
	

Quat Quat::conj ( void )
{
	return Quat ( a, - b, - c, -d );
}

Quat Quat::scalar ( double alpha )
{
	return Quat ( alpha * a, alpha * b, alpha * c, alpha * d );
}

double Quat::norm ( void ) const
{
	return ( sqrt ( a*a + b*b + c*c + d*d ) );
}

Quat Quat::inv ( void )
{
	return conj( ).scalar ( 1. / ( norm( )*norm( ) ) );
}


