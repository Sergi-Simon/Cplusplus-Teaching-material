/*
 *  multinom.cpp
 *
 *  Project name: coursework1a
 */

#include "factorial.h"  // Declare factorial
#include "multinom.h"  // Declare multinom

using std::domain_error;

long long int multinom (int n, int* k, int m )
{
	// Throw an exception for invalid arguments.
	if (n < 0)
	{
		throw domain_error("Multinomial undefined; n<0.");
	}
	for ( int i = 0; i<m; i++ )
	{
		if ( k[i] < 0 )
		{
			throw domain_error("Multinomial undefined; one of the entries is <0.");
		}
	}
	
	// Now perform the computation using a loop.
	int result = 1;  // Initialize
	for (int i = 0; i < m; ++i)
	{
		result *= factorial( k[i] );  // Same as result = result*factorial( k[i] ).
	}
	
	result = factorial( n ) / result; 

	return result;
}

