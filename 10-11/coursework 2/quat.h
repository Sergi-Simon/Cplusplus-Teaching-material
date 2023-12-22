/*
 *  quat.h
 *  coursework2
 *
 *  Created by Sergi Simon on 04/04/2011.
 *  Copyright 2011 University of Portsmouth. All rights reserved.
 *
 */


#ifndef QUAT_H
#define QUAT_H

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>  // declaration of std::ofstream
#include <ctime> // needed in order to seed the pseudo-random number algorithm
#include <iomanip>

using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::ofstream; 

class Quat
{	
	protected :
	// Data items for each object are declared here
	double a, b, c, d;	
	
//	private:
	
	public:
	// 1. Constructors: make a new object
	Quat (  );  // fills in for default constructor
	Quat ( double, double, double, double ); // more practical constructor
	// 2. Copy constructor 
	Quat ( const Quat& other );
	// 3. Assignment operator
	Quat& operator =( const Quat& );
	// 4. Destructor : destroy an object
	~Quat ();
	// 5. Inspectors : functions to read private values
	// We declare the functions const, since it should not change the values
	double qa ( void ) const;
	double qb ( void ) const;
	double qc ( void ) const;
	double qd ( void ) const;

	// 6. Basic arithmetic 
	Quat operator +( const Quat ) const;
	Quat operator -( const Quat ) const;
	Quat operator *( const Quat ) const;
	Quat conj ( );
	Quat scalar ( double );
	Quat inv ( );
	// 7. Norm of quaternion 
	double norm ( void ) const;

};

class Comp: public Quat { 

	public:
		Comp& operator =( const Comp& );
		~Comp ();
		double modulus ( void ) const;
		Comp ( void );
		Comp ( double, double );
		double re ( void ) const;
		double im ( void ) const;

		Comp ( const Comp& other );
		using Quat::operator=;
		
	//	Comp operator +( const Comp Q ) const;
//  { using Quat::operator +; Quat::operator+(Q); }

};


# endif // QUAT_H
