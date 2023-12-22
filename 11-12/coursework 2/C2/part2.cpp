/*
 *  part2.cpp
 *  C2
 *  Created by Sergi Simon on 21/03/2012.
 */

#include "part2.h"

real real_ln ( real x, long digits, long final_digits, long max_iterations )
{
	real s( 0 ), o( 1 ), x1, aux1, D;
	long k = 0;

	x1 = x - o;
	do {
		k ++;
		o = o * x1;
//		cout << " s = " << s << "o = " << o << endl;; 
		s = s + o * inverse( k, digits );
	//	cout << " and s = " << s <<  endl;
	//	cout << k << " " << o.Tol_digit( ) << endl;
		o = o.negative();
		o.decimal_cap( digits );
		s.decimal_cap( digits );
	} while ( o.Tol_digit() <= final_digits );
	
	return s;	
}


real real_exp ( real x, long digits, long final_digits, long max_iterations )
{
	real s( 1 ), o( 1 ), x1, aux1(1), D;
	long k = 0;

	x1 = x;
	do {
		k ++;
		o = o * x1 * inverse( k, digits );
		//		cout << " s = " << s << "o = " << o << endl;; 
		s = s + o;
		//	cout << " and s = " << s <<  endl;
		cout << k << " " << o.Double() << " " << s <<  endl;
		o.decimal_cap( digits );
		s.decimal_cap( digits );

	} while ( o.Tol_digit() <= final_digits );
	
	return s;	
}

real real_arctan ( real x, long digits, long final_digits, long max_iterations )
{
	real s,  o ,x1, aux1, D;
	long k = 0;
	
	x1 = x*x;
	s = x;
	o = x;
	do {
		k ++;
		o = o * x1;
		o = o.negative();
		s = s + o * inverse( 2*k+1, digits );
		o.decimal_cap( digits );
		s.decimal_cap( digits );
		x1.decimal_cap( digits );
	
		
	} while ( o.Tol_digit() <= final_digits );
	
	return s;	
}
