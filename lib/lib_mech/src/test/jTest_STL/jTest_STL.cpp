//////////////////////////////////////////////////////////////
/// 
/// \file mem_fun_as_functor.cpp
///
/// \brief
///  멤버함수를 일반 함수 개체로 사용하는 예
///
/// mem_fun_*함수군을 이용하셔 멤버함수를 일반 함수 개체로
/// 사용하는 예
///
/// \테스트환경
///  Gcc3.2.2, Comeau4.3.3, VC++6.0, VC++.NET 2003
///
/// \author 
///  Kim, Seungtai( stkim@yujinrobot.com )
/// 
/// \date
///  - 2004-08-10, Kim, Seungtai, Create
/// 
/// \see
///
//////////////////////////////////////////////////////////////
#include <stdafx.h>
#include<string>
#include<algorithm>
#include<functional>
#include<iostream>
#include<vector>
#include <windows.h>


class A
{
private:
	std::string name;

public:

	A() { name = 'a'; }

	bool print() 
	{
		std::cout << name << std::endl;
		return true;
	}

	bool print_1( std::string s ) 
	{
		std::cout << s << name << std::endl;
		return true;
	}
};


int main_memfunc()
{
	std::vector<A> as(1);
	std::cout << "Call Reference" << std::endl;
	std::for_each(as.begin(), as.end(), std::mem_fun_ref(&A::print));

	std::vector<A*> pas;
	pas.push_back(new A);
	std::cout << "Call Pointer" << std::endl;
	std::for_each(pas.begin(), pas.end(), std::mem_fun(&A::print));
	return 0;

}


