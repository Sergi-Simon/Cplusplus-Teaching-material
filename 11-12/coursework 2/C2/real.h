/*
 *  real.h
 *  C2
 *
 *  Created by Sergi Simon on 12/03/2011
 *  Copyright 2012 University of Portsmouth. All rights reserved.
 *
 */


#ifndef REAL_H
#define REAL_H

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <cmath>
#include <fstream>  // declaration of std::ofstream
#include <ctime> // needed in order to seed the pseudo-random number algorithm
#include <iomanip>
#include <vector>

using std::vector;
using std::cin;
using std::cerr;
using std::cout;
using std::endl;
using std::ofstream; 
using std::ostream; 
using std::domain_error;

class real
{	
	private :
	// Data items for each object are declared here
	int sign;
	long int n, m;
	vector<int> integer, decimal;	
	
//	protected:
	
	public:
	// 1. Constructors: make a new object
	real ( void );  // fills in for default constructor
	real ( int sign, vector<int> in, vector<int> de );  // more practical constructor
	real ( long int k );
	real ( double x, long int digits );
	real ( int _sign, vector<int> v, long int m );
	// 2. Copy constructor 
	real ( const real& other );
	// 3. Assignment operator
	real& operator =( const real& );
	// 4. Destructor : destroy an object
	~real ();
	// 5. Inspectors : functions to read private values
	// We declare the functions const, since it should not change the values
	int qsign ( void ) const;
	int qn ( void ) const;
	int qm ( void ) const;
	vector<int> qinteger ( void ) const;
	vector<int> qdecimal ( void ) const;
	vector<int> Vector ( void ) const;

	// 6. Special inspectors : requiring some computations
	// We declare the functions const, since it should not change the values
	long int Int ( void ) const;
	double Double ( void ) const;

	// 7. Basic arithmetic
	real operator +( const real ) const;
	real operator -( const real ) const;
	real scalar ( const int k ) const;
	real operator *( const real ) const;
	real operator /( const real ) const;
	real negative( void ) const;
	real realabs ( void ) const; // better not to overload abs
	void shift ( long int digits, int direction );
	void cap ( void );
	void decimal_cap ( long int );
	long int Tol_digit ( void ) const;
};

real inverse ( long int K, long int digits );
real zero( void );
real one ( void );
ostream& operator <<( ostream & os, const real x );

# endif // REAL_H
