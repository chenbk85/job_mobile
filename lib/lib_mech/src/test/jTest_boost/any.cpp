#include <stdafx.h>
#include <iostream>
#include <string>
#include <boost/any.hpp>

using namespace std;
using namespace boost;

#include "any_sample.h"

// �޽��� �ޱ��� ���� �������̽�
class MessageReceiver
{
public:
	virtual void do_message( int msg, any data ) = 0;
	virtual ~MessageReceiver() {}
};

enum { PRINT_STRING, SET_REPEAT_COUNT };

// �޽����� ���� ��. ���� �󼼴� MessageReceiver�������̽���
// �ڿ� �����, �ܺο� ������ �ʴ´�.
MessageReceiver* create_receiver()
{
	struct A_plus_B
	{
		int operator()(int a, int b) 
		{ 
			cout << a<< " + " <<b<< " = " << a + b <<endl;
			return a + b; 
		}
		bool operator()(long a, long b) 
		{ 
			cout << a << "==" << b << "= " << (a==b) << endl;
			return a == b; 
		}
	};
	class MyReceiver : public MessageReceiver
	{
		int rep;
		virtual void do_message( int msg, any data )
		{
			switch( msg )
			{
			case PRINT_STRING:
				for(int i=0; i!=rep; ++i)
					cout << any_cast<string>(data);
				cout << endl;
				break;
			case SET_REPEAT_COUNT:
				rep = any_cast<int>(data);
				break;
			}
		}
	public:
		MyReceiver() : rep(1) {}
	};
	return new MyReceiver;
}


struct _test1
{
	int i;
	std::string str;
};


bool is__test1(const boost::any & operand)
{
	return operand.type() == typeid(_test1);
}

int main_any()
{
	try
	{
		_test1 test1;
		any any_test1 = test1;
		if( is__test1(any_test1))
		{
			cout << " is__test1 (  )		ok\n" ;
		}
		any a;
		// int���� �� 100�� �ִ´�.
		a = 100;
		// int���� ���� ������.
		cout << any_cast<int>(a) << endl;
		// string���� �� "Hello"�� �ִ´�
		a = string("Hello!");
		// string���� ���� ������.
		cout << any_cast<string>(a) << endl;
		// double���� �� 3.14�� �ִ´�.
		a = 3.14;
		// string���� ���� �������� �Ѵ٣���
		cout << any_cast<string>(a) << endl;
	}
	catch( bad_any_cast& e )
	{
		cout << e.what() << endl;
	}
	return 0;
}

int main_any_msg()
{
	// �޽��� �۽��� ��
	auto_ptr<MessageReceiver> recv( create_receiver() );
	recv->do_message( PRINT_STRING,     string("�۸�") );
	recv->do_message( SET_REPEAT_COUNT, 2 );
	recv->do_message( PRINT_STRING,     string("�Ŀ�") );
	return 0;
}


#include <typeinfo.h>

class Base {
public:
	virtual void vvfunc() {}
};

class Derived : public Base {};

using namespace std;
int main_typeid()
{
	Derived* pd = new Derived;
	Base* pb = pd;
	cout << typeid( pb ).name() << endl;   //prints "class Base *"
	cout << typeid( pd ).name() << endl;   //prints "class Derived *"
	delete pd;
	return 0;
}



#include <iostream>
#include <boost/any.hpp>
using namespace std;

struct Point
{
	Point(int ix=0,int iy=0) : x(ix), y(iy) {}
	int x, y;
};

static char* hw = "hello world.";

int main_any2()
{
	boost::any a, b;
	a = 100; // ������ �ִ´�
	b = hw;  // ���ڿ��� �ִ´�
	a = b;   // any���� ������ ����
	b = Point(10,20); // ���� ������������ ��������

	Point* pp = boost::any_cast<Point>(&b);
	// ���� ����
	cout << boost::any_cast<Point>(b).x << endl;
	if( a.type() == typeid(int) )
		cout << "int�Դϴ�" << endl;
	else if( a.type() == typeid(char*) )
		cout << "���ڿ��Դϴ�" << endl;

	return 0;
}