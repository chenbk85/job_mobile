#include <stdafx.h>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>

using namespace std;
using namespace boost;
 
static int f(int a, int b)
{
	cout << "a + b = " << a + b <<endl;
    return a + b;
}


int main_bind_ret()
{

	{
		int x = 104;
		bind<int>(f, _1, _1)(x);		// f(x, x), i.e. zero
		boost::bind(boost::type<int>(), f, _1, _1)(x);
		long a3 =3;
		boost::bind(boost::type<int>(), f, _1, _1)(a3);
		boost::bind(boost::type<long>(), f, _1, _1)(a3);


	}


	return 0;
}



