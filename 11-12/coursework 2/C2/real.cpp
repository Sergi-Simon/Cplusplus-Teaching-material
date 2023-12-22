/*
 *  real.cpp
 *  CW2
 *
 */

#include "real.h"
#include "vectorfunctions.h"

// 1. constructors

//Default constructor
real::real ( void )
{
	sign = 1;
	n = 0;
	m = 0;
	integer.resize( n );
	decimal.resize( m );

	return;
}

real::real ( int _sign, vector<int> in, vector<int> de )  // more practical constructor
{
	sign = _sign;	
	n = in.size( );
	m = de.size( );
	integer = in;
	decimal = de;

	return;
}

// constructors from integer and double
real::real ( long k )
{
	unsigned q;
	decimal.push_back( 0 );
	
	sign = 1;
	if ( k < 0 )
		sign = - 1;
	long int K = abs( k );
	do	{
		q = K / 10;
		K = K % 10;
		integer.push_back( ( int ) K );	
		K = q;
	} while ( K != 0 );
	
	n = integer.size( );
	m = decimal.size( );

	return;	
}

real::real ( double x, long int digits )
{
	int q;
	sign = 1;
	if ( x < 0 )
		sign = -1;
	long int K = ( long int )( fabs( x ) );
	n = 0;
	do	{
		n ++;
		q = K / 10;
		K = K % 10;
		integer.push_back( ( int ) K );	
		K = q;
	} while ( K != 0 );

	double decimalpart = fabs( x - ( int )( x ) );
	m = 0; 
	do	{
		decimalpart *= 10;
		decimal.push_back ( decimalpart );
		decimalpart = decimalpart - ( int )( decimalpart );
		m ++;		
	} while ( m != digits );
	
	return;	
}

real::real ( int _sign, vector<int> v, long int _m )
{	
	vector<int>::reverse_iterator it;
	for ( it = v.rbegin(); it != v.rbegin( ) + _m; it++ )
		push_front( decimal, *it );
	for ( it = v.rbegin()+_m; it != v.rend( ); it++ )
		integer.push_back( *it );
	n = integer.size( );
	m = _m;
	sign = _sign;
	
	return;
}

// 2. Copy constructor
real::real ( const real& other )
{
	n = other.n;
	m = other.m;
	sign = other.sign;
	integer = other.integer;
	decimal = other.decimal;

	return;
}

// 3. Assignment operator
real& real::operator =( const real& other )
{
	// Standard self - assignment avoidance technique
	if ( this != &other )
	{
		n = other.n;
		m = other.m;
		sign = other.sign;
		integer = other.integer;
		decimal = other.decimal;
	}		
	// Return a reference to current object in order to allow assignment chaining
	return *this;
}

// 4. Destructor 
// Destroy an object 
real::~ real ()
{
	// Nothing needed here
	return;
}

// 5. Inspector functions 
int real::qsign ( void ) const
{
	return sign;
}

int real::qn ( void ) const
{
	return n;
}

int real::qm ( void ) const
{
	return m;
}

vector<int> real::qinteger ( void ) const
{
	return integer;
}

vector<int> real::qdecimal ( void ) const
{
	return decimal;
}

vector<int> real::Vector ( void ) const
{

	vector<int> Temp;
	vector<int>::const_iterator it2;
	
	Temp = decimal;
	for ( it2 = integer.begin(); it2 != integer.end( ); it2++ )
		push_front( Temp, *it2 );
	//Temp.push_back( decimal );
	
	return Temp; 
	
}

long int real::Int ( void ) const
{
	long int K = 1, s = 0;
	long int k;
	vector<int> in;
	vector<int>::iterator it;
	in = integer;
	for ( it = in.begin( ); it != in.end( ); it ++ )
	{	
		k = ( long ) ( *it );
		s = s + k*K;
		if ( it != integer.end( ) )
			K *= 10;
	}
	
	if ( sign == -1 )
		return -s;
	return s;
}

double real::Double ( void ) const
{
	double S = 0., aux, Aux = 0.1;
	long int K = 1, s = 0;
	long int k;
	vector<int>::const_iterator it;
	
	for ( it = integer.begin( ); it != integer.end( ); it++ )
	{	
		
		k = ( long ) ( *it );
		s = s + k*K;
		if ( it != integer.end( ) )
			K *= 10;
	}

	for ( it = decimal.begin( ); it != decimal.end( ); it++ )
	{	
		aux = ( double ) ( *it );
		S = S + aux*Aux;
		if ( it != decimal.end( ) )
			Aux /= 10.;
	}
	double _sign = ( double )sign;
	return  _sign* (( double )( s ) + S);
	
}

real real::operator +( const real R  ) const
{
	
	vector<int> w, v, vr;
	int _sign;
	real Temp;
	
	if ( sign != R.sign )
	{
		Temp = realabs() - R.realabs();
		if ( sign == -1 )
			Temp = Temp.negative ( );
		return Temp;
	}
	
	_sign = sign;	

	v = Vector();
	vr = R.Vector();
	
	long int digits = m;
	if ( m < R.m ) {
		digits = R.m;
		v.resize( v.size( ) + R.m - m );
	}
	if ( m > R.m ) {
		digits = m;
		vr.resize( vr.size( ) + m - R.m );
	}
	w = add ( v, vr );
	
	Temp = real( _sign, w, digits );
	Temp.cap( );
	return Temp;
}

real real::operator -( const real R  ) const
{
	vector<int> w, v, vr;
	int _sign;
	real Temp;
	
	if ( sign != R.sign )
	{		
		Temp = realabs() + R.realabs();
		if ( sign == -1 ) {
			return Temp.negative( );
		}
		return Temp;
	}
	_sign = sign;	

	v = Vector();
	vr = R.Vector();
	long int digits = m;
	if ( m < R.m ) {
		digits = R.m;
		v.resize( v.size( ) + R.m - m );
	}
	if ( m > R.m ) {
		digits = m;
		vr.resize( vr.size( ) + m - R.m );
	}
	if ( v < vr )	{
		vector<int> aux = v; 
		v = vr; 
		vr = aux;
		_sign *= -1;
	}
	
	w = subtract ( v, vr );

	Temp = real( _sign, w, digits );
	Temp.cap( );
	return Temp;
}

real real::scalar ( const int k ) const
{	
	vector<int> in, de;
	int s, _sign = 1;
	if ( k < 0 )
		_sign = -1;

	unsigned carry = 0;
	for ( vector<int>::size_type i=m-1; i>=0; i-- )
	{
		s = decimal[i] * k + carry;
		if ( s >= 10 )
		{
			push_front( de, s % 10 );
			carry = s / 10;
		}
		else {
			push_front( de, s );
			carry = 0;
		}
	}
	
	unsigned flag = 0;
	for ( vector<int>::size_type i=0; i<n && flag == 0; i++ )
	{
		s = integer[i] * k + carry;
		if ( s == 0 )
			flag = 1;
		if ( s >= 10 )
		{
			push_front( in, s % 10 );
			carry = s / 10;
		}
		if ( s > 0 && s < 10 )
		{
			push_front( in, s );
			carry = 0;
		}
	}

	real Temp( sign*_sign, in, de );
	
	return Temp; 
}

real real::operator *( const real Q ) const
{
	unsigned int mm = m+Q.m;
	vector<int> p, q, aux, s;
	vector<int>::const_reverse_iterator it;
	int k;
	long int i;
	
	p = Vector( ); //cout << p << endl;
	q = Q.Vector( ); //cout << q << endl;	

	for ( i = 0, it = p.rbegin( ); it != p.rend( ); i++, it ++ )
	{
		k = *it;
		aux = vector_scalar ( q, k );
		aux.resize( aux.size( ) + i );
		s = add ( s, aux );
	}		

	real Temp( sign*Q.sign, s, mm );
	Temp.cap();
	return Temp;
}
	
real inverse ( long int K1, long int digits )
{
	if ( K1 == 1 )
		return real( 1 );
	if ( K1 == 0 )
		return zero( );
	int _sign = 1;
	if ( K1 < 0 )
		_sign = -1;

	vector<int> de, in;
	vector<int>::iterator it, it2, it3;
	long int K = abs( K1 ), k, j=1, q, r;

	in.push_back( 0 );
	while( j <= K )
	{
		j = j * 10;
		de.push_back( 0 );
	}
	
	de.pop_back( );
	
	q = j / K;
	r = j % K;
	de.push_back( q );
	for ( k=0; k<digits; k++ )
	{	
		r = r * 10;
		q = r / K;
		r = r % K;
		de.push_back( q );
	}

	real Temp( _sign, in, de );

	return Temp;
}

real real::negative ( void ) const
{
	real Temp( -sign, integer, decimal );
	return Temp;
}

real real::realabs ( void ) const
{
	if ( sign == -1 )
		return negative();
	return *this;
}
							 
void real::shift ( long int digits, int direction )
{
	vector<int>::iterator it;

	if ( direction > 0 )
	{
		for ( vector<int>::size_type i=0; i<digits; i++ )
		{
			if ( i >= m )
				integer.push_back( 0 );
			else
				integer.push_back( decimal[0] );
			decimal.erase( decimal.begin( ) );
		}				
	}		

	if ( direction < 0 )
	{
		for ( vector<int>::size_type i=0; i<digits; i++ )
		{
			if ( i >= n )
				push_front( decimal, 0 );
			else
				push_front ( decimal, integer[0] );
			integer.erase( integer.begin( ) );
		}				
	}		

	return;
}	



void real::cap ( void )
{
	vector<int>::reverse_iterator it, it2;
	
	it = integer.rbegin( );
	if ( *it == 0 )
	{
		it2 = it + 1; 
		if ( it2 != integer.rend( ) )
		{
			integer.pop_back( );
			n --;				
			cap ( );
		}
	}
	
	return;
}

void real::decimal_cap ( long int digits )
{
	long int k = 0;
	while( k < m - digits )
	{
		decimal.pop_back( );
		k++;	
	}
	m = digits;
	
	return;
}


real real::operator /( const real Q ) const
{

	vector<int> vp, vq, aux, aux2, s, vquo, inp, inq;
	vector<int>::const_iterator itp, itq;
	vector<int>::iterator itaux, its;
	
	vp = Vector( );
	vq = Q.Vector( );
	itp = vp.begin( ); 
	itq = vq.begin( ); 
	int kq = *itq;
	aux.assign ( itp, itp + vq.size( ) ); // first vq.size( ) entries of vp

	while ( itp != vp.end( ) )
	{
		cout << " aux = " << aux;
		cout << " vq = " << vq;
		cout << " vp = " << vp << endl;
			
		while ( aux < vq )
		{
			itp ++;
			aux.push_back( *itp );
		}
		itaux = aux.begin( );
		int kaux = *itaux;
		int k = kaux / kq;
		if ( k == 0 )
			k ++;

		do {
			aux2 = vector_scalar ( vq, k );
			int M = aux.size( ) - aux2.size( );
			for ( int i = 0; i < M; i++ )
				push_front( aux2, 0 );
			s = subtract( aux, aux2 );
			its = s.begin( );
			k ++;
		} while ( *its != 0 );
		k --;
		vquo.push_back( k );
		cout << vquo << endl;
		its ++;
		aux.assign( its, s.end( ) );
	}

	int places = 0;
/*
	inp = integer;
	inq = Q.integer;
	int places = 0;
	while ( inp < inq )
	{
		places ++;
		inp.push_back( 0 );
	}
	inp = integer;
	while ( inp < inq )
	{
		places ++;
		inp.push_back( 0 );
	}

*/	
	
	return real( sign*Q.sign, vquo, places ); 

} 


// Output stream
ostream& operator <<( ostream & os, const real x )
{
	vector<int> in, de; 
	in = x.qinteger( );
	de = x.qdecimal( );
	
	if ( x.qsign( ) == -1 )
			os << " - ";
	vector<int>::const_iterator itde;
	vector<int>::reverse_iterator itin;
	for ( itin = in.rbegin( ); itin != in.rend( ); itin ++ )
		os << *itin;
	os << ".";
	for ( itde = de.begin( ); itde != de.end( ); itde ++ )
		os << *itde;
	
     	return os;
}

real zero ( void )
{
	
	vector<int> in ( 1, 0 );
	vector<int> de ( 1, 0 );
	
	return real ( 1, in, de );
}

real one ( void )
{
	
	vector<int> in ( 1, 1 );
	vector<int> de ( 1, 0 );
	
	return real ( 1, in, de );
}

long int real::Tol_digit ( void ) const
{
	vector<int>::const_iterator itde;
	if ( integer.size( ) != 1 || integer[0] != 0 )
		return -1;
	int k = 0, digits = 0;
	for ( itde = decimal.begin(); itde != decimal.end( ) && k == 0; itde ++ )
	{
		digits ++;
		k = *itde;
	}
	
	return digits;
}
