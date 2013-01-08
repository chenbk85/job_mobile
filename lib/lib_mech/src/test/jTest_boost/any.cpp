#include <stdafx.h>
#include <iostream>
#include <string>
#include <boost/any.hpp>

using namespace std;
using namespace boost;

#include "any_sample.h"

// 메시지 받기의 범용 인터페이스
class MessageReceiver
{
public:
	virtual void do_message( int msg, any data ) = 0;
	virtual ~MessageReceiver() {}
};

enum { PRINT_STRING, SET_REPEAT_COUNT };

// 메시지의 구현 예. 구현 상세는 MessageReceiver인터페이스의
// 뒤에 숨기고, 외부에 보이지 않는다.
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
		// int형으 값 100을 넣는다.
		a = 100;
		// int형의 값을 빼낸다.
		cout << any_cast<int>(a) << endl;
		// string형의 값 "Hello"를 넣는다
		a = string("Hello!");
		// string형의 값을 빼낸다.
		cout << any_cast<string>(a) << endl;
		// double형의 값 3.14를 넣는다.
		a = 3.14;
		// string형의 값을 빼낼려고 한다！？
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
	// 메시지 송신의 예
	auto_ptr<MessageReceiver> recv( create_receiver() );
	recv->do_message( PRINT_STRING,     string("멍멍") );
	recv->do_message( SET_REPEAT_COUNT, 2 );
	recv->do_message( PRINT_STRING,     string("냐옹") );
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
	a = 100; // 정수를 넣는다
	b = hw;  // 문자열을 넣는다
	a = b;   // any같은 종류의 대입
	b = Point(10,20); // 유저 정의형에서도 들어가버린다

	Point* pp = boost::any_cast<Point>(&b);
	// 값의 꺼내
	cout << boost::any_cast<Point>(b).x << endl;
	if( a.type() == typeid(int) )
		cout << "int입니다" << endl;
	else if( a.type() == typeid(char*) )
		cout << "문자열입니다" << endl;

	return 0;
}