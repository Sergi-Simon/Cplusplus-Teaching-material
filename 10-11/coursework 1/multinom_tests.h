/*
 *  multinom_tests.h
 *  Project name: coursework1a
 *
 *  Sergi Simon -- 28/02/2011.
 *  University of Portsmouth
 *
 */

#ifndef MULTINOM_TESTS_H
#define MULTINOM_TESTS_H

#include <fstream>

using std::ofstream;

void test_examples ( ofstream& file );
void test_boundaries ( ofstream& file );
void test_relations ( ofstream& file  );
void test_multinomial ( ofstream& file );

#endif
