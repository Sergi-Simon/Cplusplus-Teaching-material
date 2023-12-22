#include "vectorfunctions.h"
#include <algorithm>

void push_front ( vector<int> & v, int k )
{
	vector<int>::iterator it;
	it = v.begin( );
	v.insert ( it, 1, k );
	
	return;
}


// there is a better way using templates
vector<int> add ( vector<int> v, vector<int> w )
{
	if ( v.size( ) == 0 )
		return w;
	if ( w.size( ) == 0 )
		return v;
	
	vector<int> Temp;
	vector<int>::reverse_iterator it, it2;
	unsigned int carry, s, It, It2;
	carry = 0;
	it2 = w.rbegin( );
	it = v.rbegin( );
	for ( ; ; )
	{
		It = 0;
		if ( it != v.rend() ) {
			It = *it; 
			it ++ ;
		}
		
		It2 = 0;
		if ( it2 != w.rend() ) {
			It2 = *it2;
			it2 ++;
		}
		
		s = It + It2 + carry;
		if ( s >= 10 ) {
			push_front( Temp, s - 10 );
			carry = 1;
		}
		else {
			push_front( Temp, s );
			carry = 0;
		}
		if ( it == v.rend( ) && it2 == w.rend( ) )
			break;
		
	}
	if ( carry !=0  )
		push_front( Temp, carry );
	
	return Temp;
}

// there is a better way using templates
vector<int> subtract ( vector<int> v, vector<int> w )
{
	vector<int> Temp;
	vector<int>::reverse_iterator it, it2;
	unsigned int carry, s, It, It2;
	
	if ( v == w )	{
		Temp.assign( v.size( ), 0 );
		return Temp;
	}
	carry = 0;
	it2 = w.rbegin( );
	it = v.rbegin( );
	for ( ; ;  )
	{
		It = 0;
		if ( it != v.rend() ) {
			It = *it; 
			it ++ ;
		}
		
		It2 = 0;
		if ( it2 != w.rend() ) {
			It2 = *it2;
			it2 ++;
		}
		
		s = It2 + carry;
		if ( It >= s )
		{
			push_front( Temp, It - s );
			carry = 0;
		}
		else {
			push_front( Temp, 10 + It - s );
			carry = 1;
		}
		if ( it == v.rend( ) && it2 == w.rend( ) )
			break;
	}

	return Temp;
}

// there is a better way using templates
vector<int> vector_scalar ( const vector<int> v, int k )
{
	vector<int> Temp;
	unsigned carry = 0, s;
	for ( vector<int>::const_reverse_iterator it = v.rbegin( ); it != v.rend( ); it++ )
	{
		s = *it * k + carry;
		push_front( Temp, s % 10 );
		carry = s / 10;
	}
	if ( carry != 0 )
		push_front ( Temp, carry );		
	return Temp; 
	
}

// Output stream
ostream& operator <<( ostream & os, const vector<int> x )
{
	vector<int>::const_iterator itde;
	for ( itde = x.begin( ); itde != x.end( ); itde ++ )
		os << *itde << ",";
	
	return os;
}

// overloading comparison operators 
bool operator<(vector<int>& v, vector<int>& w )
{
	if ( v.size( ) < w.size( ) )
		return true;
	if ( v.size( ) == w.size( ) )
		return lexicographical_compare ( v.begin( ), v.end( ), w.begin( ), w.end( ) );
	return false;
}

bool operator>(vector<int>& v, vector<int>& w )
{
	if ( v.size( ) > w.size( ) )
		return true;
	if ( v.size( ) == w.size( ) )
		return lexicographical_compare ( w.begin( ), w.end( ), v.begin( ), v.end( ) );
	return false;
}
