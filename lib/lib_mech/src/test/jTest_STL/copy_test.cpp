#include "stdafx.h"
// alg_copy.cpp
// compile with: /EHsc
#include <vector>
#include <algorithm>
#include <iostream>

int main_copy( )
{
	using namespace std;
	vector <int> v1, v2;
	vector <int>::iterator Iter1, Iter2;

	int i;
	for ( i = 0 ; i <= 5 ; i++ )
	{
		v1.push_back( 10 * i );
	}

	int ii;
	for ( ii = 0 ; ii <= 10 ; ii++ )
	{
		v2.push_back( 3 * ii );
	}

	cout << "v1 = ( " ;
	for ( Iter1 = v1.begin( ) ; Iter1 != v1.end( ) ; Iter1++ )
		cout << *Iter1 << " ";
	cout << ")" << endl;

	cout << "v2 = ( " ;
	for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )
		cout << *Iter2 << " ";
	cout << ")" << endl;

	// To copy the first 3 elements of v1 into the middle of v2
	copy( v1.begin( ), v1.begin( ) + 3, v2.begin( ) + 4 );

	cout << "v2 with v1 insert = ( " ;
	for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )
		cout << *Iter2 << " ";
	cout << ")" << endl;

	// To shift the elements inserted into v2 two positions
	// to the left
	copy( v2.begin( )+4, v2.begin( ) + 7, v2.begin( ) + 2 );

	cout << "v2 with shifted insert = ( " ;
	for ( Iter2 = v2.begin( ) ; Iter2 != v2.end( ) ; Iter2++ )
		cout << *Iter2 << " ";
	cout << ")" << endl;
	return 0;
}



int main( )
{
	using namespace std;
	vector <int> v1, v2;
	vector <int>::iterator it, ie;

	int i;
	for ( i = 0 ; i <= 5 ; i++ )
	{
		v1.push_back( i );
	}

	int ii;
	for ( ii = 0 ; ii <= 10 ; ii++ )
	{
		v2.push_back( 100 * ii );
	}

	v1.resize(v1.size()+v2.size());
	printf("v1= %d , v2= %d\n", v1.size(), v2.size());
	copy( v2.begin( ), v2.begin( )+v2.size()-1 , v1.begin()+v1.size()-1 );
	printf("v1= %d , v2= %d\n", v1.size(), v2.size());
	{
		int i=0;
		for ( it= v1.begin( ) ; it!= v1.end( ) ; it++ )
		{

			int iiii = *it;
			printf("%d =%d\n",i, iiii);
			++i;
		}
	}

}


