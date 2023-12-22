/*
 *  comp.h
 *  coursework2
 *
 *  Created by Sergi Simon on 05/04/2011.
 *  Copyright 2011 University of Portsmouth. All rights reserved.
 *
 */	


#ifndef COMP_H
#define COMP_H

#include "quat.h"

class Comp: public Quat { 

	public:
		Comp& operator =( const Comp& );
		~Comp ();
		double modulus ( void ) const;
		Comp ( void );
		Comp ( double, double );
		double re ( void ) const;
		double im ( void ) const;
};

#endif
