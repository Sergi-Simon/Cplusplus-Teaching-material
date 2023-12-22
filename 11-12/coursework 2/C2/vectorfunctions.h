/*
 *  functions.h
 *  coursework2
 *
 *  Created by Sergi Simon on 04/04/2011.
 *
 */


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
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

//using std::vector<int>iterator;
//using namespace std;
void push_front ( vector<int> & v, int k );
vector<int> add ( vector<int> v, vector<int> w );
vector<int> subtract ( vector<int> v, vector<int> w );
vector<int> vector_scalar ( const vector<int> v, int k );

ostream& operator <<( ostream & os, vector<int> x );
void cap ( vector<int> & v );
bool operator<(vector<int>& v, vector<int>& w);
bool operator>(vector<int>& v, vector<int>& w);
#endif

