/*
 *  part2.h
 *  C2
 *
 *  Created by Sergi Simon on 21/03/2012.
 *
 */

#ifndef PART2_H
#define PART2_H
#include "real.h"
#include "vectorfunctions.h"


real real_ln ( real x, long digits, long final_digits, long max_iterations );
real real_exp ( real x, long digits, long final_digits, long max_iterations );
real real_arctan ( real x, long digits, long final_digits, long max_iterations );
#endif
