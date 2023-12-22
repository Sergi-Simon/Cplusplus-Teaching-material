/*
 *  factorial.cpp
 *  Implementation of the factorial function: iterative, non-recursive version (using a loop)
 *  Project name: coursework1a
 *
 */


#include <cassert>  // declaration of assert

#include "factorial.h"  // declaration of factorial

using std::domain_error;

// Function implementation.
long long int factorial( int n )
{
  // Throws an exception for invalid arguments.
  if (n < 0)
  {
    throw domain_error("Factorial undefined; n<0.");
  }
  // Now perform the computation using a loop.
  long long int result = 1;  // Identity for multiplication.
  for (long int i = 1; i <= n; ++i)
  {
    result *= i;  // result = result * i
  }
  
	return result;
}

long long int binomial ( int n, int m )
{
	return ( factorial( n ) / ( factorial( m ) * factorial( n-m ) ) );
}
