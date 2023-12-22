#include "real.h"
#include "vectorfunctions.h"
#include "testreal.h"
#include "part2.h"

int main ( void ) {

	ofstream myfile ( "results.txt" );

	test_inverse ( myfile, 50 );
	test_sum ( myfile, 50 );
	test_subtract ( myfile, 50 );
	test_product ( myfile, 50 );

	real A( 2, 100 ), B( -3, 1 ), C(-2,1 ), D( 3, 1 ), E1, E2, E3, E4, E5;

	E1 = real_arctan( inverse( 57,100 ), 110, 100, 1000 );

	cout << "arctan(1/57)=" << E1 << endl;
	cout << "ln ( 0.5 ) =" << real_ln( real( 0.5, 200 ), 150, 100, 10000 ) << endl;

	myfile.close();
	return 0;
}
