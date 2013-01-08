#include <stdafx.h>
#include <iostream>
#include <boost/rational.hpp>
using namespace std;

int main_rational()
{
	boost::rational<int> a( 4, 3 ); // 4/3
	boost::rational<int> b( 1, 2 ); // 1/2

	boost::rational<int> c = a + b; // 4/3 + 1/2 = 11/6
	cout << c << endl;

	a = c - 5; // 11/6 - 5 = -19/6
	cout << a << endl;

	c = 4;
	b *= -c; // 1/2 * -4 = -2
	cout << b << endl;

	double d = boost::rational_cast<double>( a );
	cout << d << endl;

	int n = boost::rational_cast<int>( b );
	cout << n << endl;

	return 0;
}
/*
Ãâ·Â¿¹
11/6
-19/6
-2/1
-3.16667
-2

*/