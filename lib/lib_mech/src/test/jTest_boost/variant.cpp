#include <stdafx.h>
#include <iostream>
#include <string>

#include <boost/variant.hpp>
using namespace std;

struct do_double : boost::static_visitor<void>
{// 2배로 만드는 Visitor
	template<typename T>
	  void operator()( T& t ) const { t = t + t; }
};

int main_variant()
{
	boost::variant<int,double,std::string> v;
	v = -2;
	assert( v.which() == 0 ); // 내용이 int 인지 확인
	cout << boost::get<int>(v) << endl; // int형 값 꺼내기

	v = 3.14;
	assert( v.which() == 1 ); // 내용이double것을 확인
	cout << v << endl;        // 사실 get<...>은 필요 없다

	v = "hoge";
	assert( v.which() == 2 );// 내용이string인지 확인
	boost::apply_visitor( do_double(), v ); // Visitor를 호출
	cout << v << endl;

	return 0;
}

/*
출력예
-2
3.14
hogehoge

*/
