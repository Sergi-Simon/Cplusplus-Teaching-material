#include "quat.h"
//#include "comp.h"
#include "testquat.h"

int main ( void ) {

	ofstream myfile;
	cout << 2 << endl;
	
	myfile.open ("example0.txt" );
	testconj ( myfile );
	testinv ( myfile );
	testnormscalar ( myfile );
	testnormproduct ( myfile );
	testscalarproduct ( myfile );
	testcrossproduct ( myfile );
	myfile.close();
	
	Comp Q( 3., 1. ), P( -3., 2. ), R;

	R = P + Q;
	cout << R.re() << "\t" << R.im() << endl;
	cout << R.qa() << "\t" << R.qb() << "\t" << R.qc() << "\t" << R.qd() << endl;

	R = (Q * P).scalar( -1 );
	cout << R.re() << "\t" << R.im() << endl;
	cout << R.qa() << "\t" << R.qb() << "\t" << R.qc() << "\t" << R.qd() << endl;
	
	return 0;
}
