#include <stdafx.h>
#include <iostream>
#include "boost/tuple/tuple.hpp"
#include "boost/tuple/tuple_comparison.hpp"

using namespace std;
using namespace boost;

boost::tuple<int,int,int,double> add_sub_mul_div(int a, int b)
{
	// 사칙 연산 결과를 전부 돌려주는 함수
	return boost::make_tuple(
		a+b,
		a-b,
		a*b,
		double(a)/double(b)
		);
}


struct A
{

};
bool operator==(A, A) { std::cout << "All the same to me..."; return true; }

#include <boost/tuple/tuple_io.hpp>
int main_tuple()
{
	boost::tuple<int, int, int, double> t = add_sub_mul_div( 3, 2 );
	cout << t << endl;

	// 각 요소를 취득해 본다
	cout << "0: " << t.get<0>() << endl;
	cout << "1: " << t.get<1>() << endl;
	cout << "2: " << t.get<2>() << endl;
	cout << "3: " << t.get<3>() << endl;

	{
		boost::tuple<float, int, std::string> a(1.0f,  2, std::string("Howdy folks!"));
		cout <<"tuple<float, int, std::string> --> cout "<< a << endl;
		cout << boost::tuples::set_open('[') 
			<< boost::tuples::set_close(']') 
			<< boost::tuples::set_delimiter(',') 
			<< a<<endl; 
	}

	/*	//boost::tuple<float, int> a = std::make_pair(1, 'a');

	tuple<std::string, int, A> t1(std::string("same?"), 2, A());
	tuple<std::string, long, A> t2(std::string("same?"), 2, A());
	tuple<std::string, long, A> t3(std::string("different"), 3, A());
	//	t1 == t2; 		// true
	//	t1 == t3;
	*/

	int i; char c; double d; 
	boost::tie(i, c, d) = boost::make_tuple(1,'a', 5.5);
	std::cout <<"tie(i, c, d) = make_tuple(1,'a', 5.5);" 
		<< i << " " <<  c << " " << d <<endl;
	{
		int i; char c;
		tie(i, c) = std::make_pair(1, 'a');
	}

	{
		char c;
		tie(tuples::ignore, c) = std::make_pair(1, 'a');

	}
	return 0;
}

/*
출력예
(5 1 6 1.5)
0: 5
1: 1
2: 6
3: 1.5
*/