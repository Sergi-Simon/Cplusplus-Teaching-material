/*
 *  main.cpp
 *  Project name: coursework1a
 *
 */


#include <cstdlib>  // Declare EXIT_SUCCESS.
#include "multinom_tests.h"  // Declare tests.

using std::ofstream;

// Main program. At present, just runs tests.
int main( void )
{
	ofstream myfile;
	
	myfile.open ("example.txt" );
	test_multinomial ( myfile );
	myfile.close();
	
	return EXIT_SUCCESS;
}