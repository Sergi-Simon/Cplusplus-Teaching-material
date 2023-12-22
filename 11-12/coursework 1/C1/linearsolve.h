#ifndef LINEARSOLVE_H
#define LINEARSOLVE_H

#include <iostream>
#include <cassert>
#include <cmath>


#include <cstdlib>
#include <fstream>
#include <stdexcept>


using std::ofstream;
using std::ifstream;
using std::endl;
using std::cout;
using std::cin;
using std::exception;
using std::string;
using std::ios;
using std::domain_error;


int matrixgauss ( double **a, double **b, int n, ofstream& file );
int gauss ( double **a, double *b, int n, ofstream &file );
void backward ( double **u, double *b, int n, ofstream& file, int flag );
int matrix_invert ( double **a, int n, ofstream& file );

int LUP ( double **a, int n, int *index, double Tol );
void LUPbackward ( double **u, double *b, int n );
void LUPforward ( double **L, double *b, int n, int *index );
int LUPmatrix_invert ( double **a, int n, int *index, ofstream& file );

int special_matrices ( int n_max, ofstream& file );
int random_matrices ( int n_max, ofstream& file );
#endif
