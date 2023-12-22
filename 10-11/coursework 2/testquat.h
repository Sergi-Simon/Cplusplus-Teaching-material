/*
 *  TestQuat.h
 *  coursework2
 *
 *  Created by Sergi Simon on 12/04/2011.
 *  Copyright 2011 University of Portsmouth. All rights reserved.
 *
 */


#ifndef TESTQUAT_H
#define TESTQUAT_H

#include <cassert>
#include "quat.h"


void testconj ( ofstream& file );
void testinv ( ofstream& file );
void testnormscalar ( ofstream& file );
void testnormproduct ( ofstream& file );
void testscalarproduct ( ofstream& file );
void testcrossproduct ( ofstream& file );

# endif // TESTQUAT_H
