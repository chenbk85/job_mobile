#include <stdafx.h>
#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

//
//  bind_as_compose.cpp - function composition using bind.hpp
//
//  Version 1.00.0001 (2001-08-30)
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//

#include <boost/bind.hpp>
#include <iostream>
#include <string>

std::string f(std::string const & x)
{
    return "f(" + x + ")";
}

std::string g(std::string const & x)
{
    return "g(" + x + ")";
}

std::string h(std::string const & x
			  , std::string const & y)
{
    return "h(" + x + ", " + y + ")";
}

std::string k()
{
    return "k()";
}

template<class F> void test(F f)
{
    std::cout << f("x", "y") << '\n';
}



int main_bind_2_1()
{
    using namespace boost;
    // compose_f_gx
    test( bind(f, bind(g, _1)) );
    // compose_f_hxy
    test( bind(f, bind(h, _1, _2)) );
    // compose_h_fx_gx
    test( bind(h, bind(f, _1), bind(g, _1)) );
    // compose_h_fx_gy
    test( bind(h, bind(f, _1), bind(g, _2)) );
    // compose_f_k
    test( bind(f, bind(k)) );
    return 0;
}
/*
main_bind_2_1 call!!!
f(g(x))
f(h(x, y))
h(f(x), g(x))
h(f(x), g(y))
f(k())



*/

struct X
{
	int f(int i ){
		std::cout << "f = " << i <<std::endl;
		return i +2;
	}
};

int main_bind_null()
{
    //boost::bind(&X::f, 1);     // 에러 X::f 는 두 개의 인수를 취하는
	X x;
    boost::bind(&X::f, _1, 1); // OK
    boost::bind(&X::f, _1, 2)(x); // OK  출력 f = 2

	boost::bind(f, "incompatible");      // OK, 호출하지 않기 때문에
    boost::bind(f, "incompatible")();    // 에러 "incompatible" 는 int 이 아닌
    boost::bind(f, _1);                  // OK
    boost::bind(f, _1)("incompatible");  // 에러 "incompatible" 는 int 이 아닌
	return 0;
}
