#include <stdafx.h>
#include <iostream>
#include <boost/utility.hpp>
using namespace std;

class Base
{
public :
	int m_base_id;
	Base( int id ) 
	{ 
		m_base_id = id;
		cout << id << " created." << endl; 
	}
};

class Derived
	: private boost::base_from_member<int>
	,  public Base
{
	typedef boost::base_from_member<int> id;
	//std::string str;
public:
	// base classBase보다 먼저ID번호를 초기화
	Derived::Derived() : id( 999), m_derived_id(id::member+10),Base( id::member ) 
	{
		string str = "test";
		cout << "derived  id = " << id::member << endl;
	}
	int m_derived_id;
};


int main_base_from_member()
{

	Derived d;
	d.m_derived_id=10;
	cout << "d.m_derived_id = " << d.m_derived_id<<endl;
	cout << "d.m_base_id = " << d.m_base_id<<endl;


	//... // 너무 좋은 예가 아니다...

	return 0;
}
/*
출력예
178 created.

*/