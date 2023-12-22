/*
 *  multinom.cpp
 *  Test file for the multinomial function
 *  Project name: coursework1a
 *
 */

#include <cstdlib>  // declare EXIT_SUCCESS
#include <cassert>  // declare assert
#include <iostream>  // declare std::cerr, etc
#include <fstream>  // declare std::ofstream
#include <ctime> // needed in order to seed the pseudo-random number algorithm

#include "factorial.h"  // Declare factorial
#include "multinom.h"  // Declare multinom
#include "multinom_tests.h"  // Declare multinomial tests

using std::cerr;  // cerr without std:: prefix
using std::endl;  // endl without std:: prefix
using std::ofstream; // ofstream without std:: prefix

//int multinom ( int, int*, int );
void test_examples( ofstream& file )
{
	int* k;
	
	file << "Testing examples..." << endl;
	cerr << "Testing examples..." << endl;
	
	// allocate for the maximum length
	k = new int[5];
	
	k[0] = 3; k[1] = 2; 
	assert( 10 == multinom(5, k, 2) );
	file << "Example" << 5 << k[0] << k[1] << "passed" << endl;
	
	k[0] = 3; k[1] = 2; k[2] = 5; 
	assert( 2520 == multinom(10, k, 3) );
	file << "Example" << 10 << k[0] << k[1] << k[2] << "passed" << endl;
	
	k[0] = 3; k[1] = 2; k[2] = 5; k[3] = 1; 
	assert( 27720 == multinom(11, k, 4) );
	file << "Example" << 11 << k[0] << k[1] << k[2] << k[3] << "passed" << endl;

	k[0] = 3; k[1] = 2; k[2] = 5; k[3] = 1; k[4] = 4; 
	assert( 37837800 == multinom(15, k, 5 ) );

	file << "Example" << 13 << k[0] << k[1] << k[2] << k[3] << k[4] << "passed" << endl;

/* 
	k[0] = 3; k[1] = 2; k[2] = 5; k[3] = 1; k[4] = 4; 
	assert( 27837800 == multinom(15, k, 2) );
	file << "Example" << 15 << k[0] << k[1] << k[2] << k[3] << k[4] << "passed" << endl;
*/ 
	
	// deallocate 
	delete[] k;
	k = NULL;

	return;
}


// Test edge cases
void test_boundaries ( ofstream& file )
{
	int* k;
	int sum, n, mult, mult0, aux, m;
	
	file << "Testing boundaries..." << endl;
	cerr << "Testing boundaries..." << endl;
	
	// allocate for the maximum length
	k = new int[6];
	
	// seed for the pseudo-random generator
	srand(time(0));
	
	for ( m=2; m<=6; m++ )
	{
		file << "Testing boundaries... for m=" << m << endl;
		cerr << "Testing boundaries... for m=" << m << endl;
		// generate random numbers which are neither too large (e.g. larger than 6) nor equal to zero  */
		n = abs( rand() % 5 ) + 5;
		for ( int i=1; i<m; ++i )
 			k[i] = 0;
 		k[0] = n;
		mult = multinom(n, k, m);	
		
		for ( int j=0; j<m; j++ )
		{
			for ( int i=0; i<m; ++i )
				k[i] = 0;
			k[j] = n;
			mult0 = multinom(n, k, m);	
			assert ( mult == mult0 );
			file << "Test passed for m=" << m << "and vector \t";		
			for ( int i=0; i<m; i++ )
				file << k[i] << ",";	
			file << "\n";
		}
	}
		
	delete[] k;
	k = NULL;
	
	return;
}

// Test recurrence relation.
void test_relations ( ofstream& file )
{
  
	int* k;
	int sum, n, mult, aux, m;
	
	file << "Testing relations..." << endl;
	cerr << "Testing relations..." << endl;
	
	// allocate for the maximum length
	k = new int[6];
	
	// seed for the pseudo-random generator
	srand(time(0));
	
	for ( m=2; m<=6; m++ )
	{
		file << "Testing relations... for m=" << m << endl;
		cerr << "Testing relations... for m=" << m << endl;
		// generate random numbers which are neither too large (e.g. larger than 6) nor equal to zero  */
		n = 0;
		for ( int i=0; i<m; ++i )
		{
			k[i] = abs( rand() % 5 ) + 1;
			n += k[i];
		}
		mult = multinom(n, k, m);	
		aux = 1;
		for ( int i=0; i<m; i++ )
		{
			sum = 0;
			for ( int j=0; j<=i; j++ )
			{
				sum += k[j];
			}	
			aux *= binomial( sum, k[i] );
		}
		assert ( mult == aux );
		file << "Test passed for m=" << m << "and vector \t";		
		for ( int i=0; i<m; i++ )
			file << k[i] << ",";	
		file << "\n";
	}
	
	delete[] k;
	k = NULL;
	
	return;	
}


// Package all tests into one function.
void test_multinomial ( ofstream& file )
{
	test_examples( file );
	test_boundaries( file );
	test_relations ( file );
	cerr << "All tests passed." << endl;
	file << "All test passed \n";
  return;
}
