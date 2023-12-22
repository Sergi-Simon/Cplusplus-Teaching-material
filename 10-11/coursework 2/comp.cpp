/*
 *  comp.cpp
 *  coursework2
 *
 *  Created by Sergi Simon on 06/04/2011.
 *  Copyright 2011 University of Portsmouth. All rights reserved.
 *
 */

//#include "comp.h"
#include "quat.h"

// Assignment operator: assigns this object the value of another
Comp& Comp::operator =( const Comp& other )
{		
	if ( this != &other )
	{
		a = other.a;
		b = other.b;
		c = 0.;
		d = 0.;
	}		
	// Return a reference to current object in order to allow assignment chaining
	return *this ;
}


Comp::Comp ( const Comp& other )
{

	a = other.a;
	b = other.b;
	c = other.c;
	d = other.d;
	return;
}

Comp::~ Comp ()
{
	// Nothing needed here .
	return;
}


double Comp::modulus ( void ) const
{
	return norm( );
}

Comp::Comp ( void )
{
	a = b = c = d = 0.;
	
	return;
}

Comp::Comp ( double a1, double b1 )
{

	a = a1;
	b = b1;
	c = 0.;
	d = 0.;
	
	return;
}
	

double Comp::re ( void ) const
{
	return a;
}

double Comp::im ( void ) const
{
	return b;
}


