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
	{// malloc free ��� allocater
		boost::pool<> p( sizeof(int) );
		int* x = (int*)p.malloc();
		int* y = (int*)p.malloc();
		int* z = (int*)p.malloc();
		*x = 10;
		p.free(z); // ����� free
		
	}// free���ص� pool������Ʈ�� ����� ���ÿ� ������

	{// new delete ��� allocater
		boost::object_pool<Abc> p;
		Abc* x = p.construct();
		Abc* y = p.construct();
		Abc* z = p.construct();
		p.destroy(y);//  ��������� �Ҹ��� ȣ��
	}// destroy���ص� pool������Ʈ�� ����� ���ÿ� ����.

	return 0;
}

/*
��¿�
Abc() :1
Abc() :2
Abc() :3
~Abc():2
~Abc():1
~Abc():3
*/
