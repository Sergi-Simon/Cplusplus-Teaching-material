#include "real.h"

int newton_raphson ( real& x0, real (*f) ( real x ), real (*df) ( real x ), int max_iterations,  long long int Tol )
{
	vector<int> in;
	vector<int>::iterator it;
	real x, X, diff;
	int iterations = 0;
	x = x0;

	do {

		X = x - f( x ) / df ( x ); 
		diff = X - x;
		in = diff.qinteger( );
		diffsize = in.size( ); 
		it = in.begin( );
		diffvalue = *it;
		diffdigits = diff.Tol_digit( );
		x = X;
		iterations ++;

	} while ( ( diffdigits < Tol || diffsize != 1 || diffvalue != 0 ) && iterations < max_iterations );	
	
	if ( iterations >= max_iterations )
		return 1;
	x0 = x;

	return 0;
}
