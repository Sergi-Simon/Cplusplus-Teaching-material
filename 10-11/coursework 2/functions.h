/*
 *  functions.h
 *  coursework2
 *
 *  Created by Sergi Simon on 04/04/2011.
 *  Copyright 2011 University of Portsmouth. All rights reserved.
 *
 */


#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "quat.h"

double vectornorm ( Comp *v, int dim );
void scalarproduct ( Comp *v, double alpha, int dim );
void product ( Comp **a, Comp *v, Comp *v2, int dim );
int power_iteration ( Comp **a, Comp *b, int dim, int& k, double& tol );
void equalto( Comp *v, Comp *v2 );
int powerandwrite( Comp **a, Comp *b, Comp *c, int dim, ofstream& myfile );

#endif

