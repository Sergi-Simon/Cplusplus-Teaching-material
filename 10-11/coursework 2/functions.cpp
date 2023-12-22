#include "functions.h"

double vectornorm ( Comp *v, int dim )
{
	double Temp = 0.; 

	for ( int i=0; i<dim; i++ )
	{
		if( v[i].modulus( ) > Temp )
			Temp = v[i].modulus( );
	}

	return ( Temp ); 
}

void scalarproduct ( Comp *v, double alpha, int dim )
{

	for ( int i = 0; i<dim; i++ )
		v[i] = v[i].scalar( alpha );
	return;
}

void product ( Comp **a, Comp *v, Comp *v2, int dim )
{
	
	for ( int i = 0; i<dim; i++ )
	{
		v2[i] = Comp( 0., 0. );
		for ( int j = 0; j < dim; j++ )		
		{
			v2[i] = v2[i] + ( a[i][j] * v[j] );
		}
	}
	
	return;

}

void equalto( Comp *v, Comp *v2, int dim )
{
	for ( int i=0; i<dim; i++ )
		v[i] = v2[i];
	return;
}

int power_iteration ( Comp **a, Comp *b, int dim, int& k, double& tol )
{
	
	
	double diff;
	Comp *c = new Comp[dim];
	Comp *Temp = new Comp[dim];
	
	tol = 1.e-15;
	k = 0; 	
	do {
		product( a, b, c, dim );
		scalarproduct ( c, 1./ vectornorm( c, dim ), dim );
		for ( int i = 0; i < dim; i ++ )
			Temp[i] = b[i] - c[i];
		diff = vectornorm( Temp, dim );
		equalto ( b, c, dim );
		k ++;
	} while ( k < 1000 && diff >= tol );
	
	delete [] c;
	delete [] Temp;

	if ( k >= 1000 )
		return 1;
	return 0;		

}


int powerandwrite( Comp **a, Comp *b, Comp *c, int dim, ofstream& myfile )
{
	int j; 
	double tol;

	myfile << "The matrix has entries" << endl;
	myfile << a[0][0].re() << "+" << a[0][0].im() << "i\t" << a[0][1].re() << "+" << a[0][1].im() << "i\t" << a[0][2].re() << "+" << a[0][2].im()  << "i" << endl;
	myfile << a[1][0].re() << "+" << a[1][0].im() << "i\t" << a[1][1].re() << "+" << a[1][1].im() << "i\t" << a[1][2].re() << "+" << a[1][2].im() << "i" << endl;
	myfile << a[2][0].re() << "+" << a[2][0].im() << "i\t" << a[2][1].re() << "+" << a[2][1].im() << "i\t" << a[2][2].re() << "+" << a[2][2].im() << "i" << endl;
	myfile << "The initial condition was" << endl;
	myfile << b[0].re() << "+" << b[0].im() << "i" << endl;
	myfile << b[1].re() << "+" << b[1].im() << "i" << endl;
	myfile << b[2].re() << "+" << b[2].im() << "i" << endl;

	int k = power_iteration ( a, b, dim, j, tol );
	Comp Temp, Temp2, Temp3;
	Comp eigenvalue;
	int flag;
	double temp = 0.;		
	if ( k == 0 ) {
		myfile << "the method converged in " << j << " iterations using tolerance " << tol << " to eigenvector" << endl;	

		myfile << std::setprecision(16) << b[0].re() << "+" << std::setprecision(16) << b[0].im() << "i" << endl;
		myfile << std::setprecision(16) << b[1].re() << "+" << std::setprecision(16) << b[1].im() << "i" << endl;
		myfile << std::setprecision(16) << b[2].re() << "+" << std::setprecision(16) << b[2].im() << "i" << endl;
		
		for ( int i =0; i<dim; i++ )
		{		
			if ( b[i].modulus( ) >= temp )
			{
				Temp = b[i]; 
				temp = b[i].modulus( );
				flag = i;
			}
		}
		product ( a, b, c, dim );
		eigenvalue = c[flag] * Temp.inv();
		myfile << "having dominant eigenvalue " << std::setprecision(16) << eigenvalue.re() << "+" << std::setprecision(16) << eigenvalue.im() << "i" << endl;								
		temp = 0.;
		for ( int i =0; i<dim; i++ )
		{		
			Temp2 = eigenvalue * b[i];
			Temp3 = c[i]-Temp2;
			
			if ( Temp3.modulus( ) >= temp )
			{
				temp = Temp3.modulus( );
			}
		}

		myfile << "The norm of the difference Av-lambda v is " << temp << endl;
	}
	else {
		myfile << "The method failed to converge with this initial condition" << endl;
		return 1;
	}

	return 0;

}
