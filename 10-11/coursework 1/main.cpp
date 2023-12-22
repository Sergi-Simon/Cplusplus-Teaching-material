/*
 *  main.cpp
 *  Project name: coursework1a
 *
 */

#include <cstdlib>  // declaration of EXIT_SUCCESS
#include "multinom_tests.h"  // declaration of tests

using std::ofstream;

// Main program. At present, just runs tests.
int main( void )
{
	
	int a = 2;
	//std::cout << "hello";
	ofstream myfile;
	
	myfile.open ("example.txt" );
	test_multinomial ( myfile );
	myfile.close();
	
	return EXIT_SUCCESS;
}
