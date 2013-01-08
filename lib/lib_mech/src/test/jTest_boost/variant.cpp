#include <stdafx.h>
#include <iostream>
#include <string>

#include <boost/variant.hpp>
using namespace std;

struct do_double : boost::static_visitor<void>
{// 2��� ����� Visitor
	template<typename T>
	  void operator()( T& t ) const { t = t + t; }
};

int main_variant()
{
	boost::variant<int,double,std::string> v;
	v = -2;
	assert( v.which() == 0 ); // ������ int ���� Ȯ��
	cout << boost::get<int>(v) << endl; // int�� �� ������

	v = 3.14;
	assert( v.which() == 1 ); // ������double���� Ȯ��
	cout << v << endl;        // ��� get<...>�� �ʿ� ����

	v = "hoge";
	assert( v.which() == 2 );// ������string���� Ȯ��
	boost::apply_visitor( do_double(), v ); // Visitor�� ȣ��
	cout << v << endl;

	return 0;
}

/*
��¿�
-2
3.14
hogehoge

*/
