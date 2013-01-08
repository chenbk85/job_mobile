#include <stdafx.h>
#include <iostream>
using namespace std;

static int g_iNo=0;
struct Abc
{
	Abc()
	{ 
		cout << "Abc() :" 
			<< (m_no= ++g_iNo) 
			<< endl; 
	}
	~Abc()
	{ 
		cout << "~Abc():" 
			<< m_no << endl; 	
	}
	int m_no;
};

#include <boost/pool/pool.hpp>
#include <boost/pool/object_pool.hpp>
int main_pool()
{
	{// malloc free 대용 allocater
		boost::pool<> p( sizeof(int) );
		int* x = (int*)p.malloc();
		int* y = (int*)p.malloc();
		int* z = (int*)p.malloc();
		*x = 10;
		p.free(z); // 명시적 free
		
	}// free안해도 pool오브젝트의 수명과 동시에 해제됨

	{// new delete 대용 allocater
		boost::object_pool<Abc> p;
		Abc* x = p.construct();
		Abc* y = p.construct();
		Abc* z = p.construct();
		p.destroy(y);//  명시적으로 소멸자 호출
	}// destroy안해도 pool오브젝트의 수명과 동시에 해제.

	return 0;
}

/*
출력예
Abc() :1
Abc() :2
Abc() :3
~Abc():2
~Abc():1
~Abc():3
*/
