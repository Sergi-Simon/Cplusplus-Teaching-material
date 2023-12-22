/*
 *  testreal.h
 *  C2
 *
 *  Created by Sergi Simon on 21/03/2012.
 *  Copyright 2012 University of Portsmouth. All rights reserved.
 *
 */


#ifndef TEST_REAL
#define TEST_REAL
#include "real.h"
#include "vectorfunctions.h"
#include<cassert>
void test_inverse ( ofstream& file, long digits );
void test_sum ( ofstream& file, long digits );
void test_subtract ( ofstream& file, long digits );
void test_product ( ofstream& file, long digits );
#endif
