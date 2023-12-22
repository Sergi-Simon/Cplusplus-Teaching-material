#ifndef MATRIX_H
#define MATRIX_H

#include <fstream>
#include <iomanip>
using std::ofstream;

double **identity_matrix ( int n );
void canonical ( double *E, int n, int j );
void matrix_copy ( double **A, double **a, int n );
void copy ( double *V, double *v, int n );
void write ( double **a, int n, ofstream& file );
void write_extended ( double **a, double *b, int n, ofstream& file );
void matrix_write ( double **a, double **b, int n, ofstream& file );
double norm ( double *x, int n );
int check ( double **a, double *x, double *b, int n, double tol, double &S );
double matrix_norm ( double **a, int n );
int matrix_check ( double **a, double **x, double **b, int n, double tol, double& S );
double **hilbert ( int n );
double **other ( int n );
void matrix_difference ( double **a, double **b, int n );
void matrix_product ( double **a, double **b, int n );
long int factorial ( long int n );
double **random ( int n );
#endif
