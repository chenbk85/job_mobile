#include <stdafx.h>
#include <boost/config.hpp>

#if defined(BOOST_MSVC)
#pragma warning(disable: 4786)  // identifier truncated in debug info
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4711)  // function selected for automatic inline expansion
#pragma warning(disable: 4514)  // unreferenced inline removed
#endif

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace boost;


class button
{
public:
	boost::function<bool (int, int)> cmp1;
	//boost::function<int (HWND wnd, MSG msg, int wparam, int lparam)> wndProc;
	boost::function<void (void)> onClick;
	boost::function<void (int ,std::string)> onClick1;
};

class player
{
public:
	void play(){ 	cout << "player::play()" << endl; }
	void stop(int i, std::string str)
	{ 
		cout << i << " > player::stop() - "<< str << endl; 
	}
};

button playButton, stopButton;
player thePlayer;

void connect()
{
	playButton.onClick = boost::bind(&player::play, &thePlayer);
	stopButton.onClick1 = boost::bind(&player::stop, &thePlayer, _1 , _2);
	playButton.onClick();
	stopButton.onClick1(23, "sdtdsfd");
}

/*================================================================*/

struct SomeObject
{
	SomeObject( int i_n ) : n( i_n ) {}
	int Do( int x ) { return x*n; }
	const int n;
};

bool f( int x, int y )
{
	return x*x < y;
}

struct __aaa23
{
	function < void (int)> asdf;
	function < void (int)> asdf2;
	__aaa23(){ memset(this, 0 , sizeof(*this));}
};
int main_fucntion1()
{
	function < void (int)> asdf;
	if(!asdf.empty())	
		asdf(23);

//	__aaa23 aaa;
//	assert( aaa.asdf.empty());

	connect();
	// int(��)��int(��)�� ����bool�� �����ִ� 2�μ� �Լ��� �ݳ��� 
	// �� �ִ� �Լ� ������Ʈ.  �켱 ���� �Լ��� �־� ����.
	boost::function2<bool, int, int> cmp = &f;
	if( cmp(4, 20) )
	{
		cout << 1 << endl;
	}

	// ���߿� �Լ� ������Ʈ�� ����
	cmp = std::not2( std::less<int>() );
	if( cmp(4, 20) )
	{
		cout << 2 << endl;
	}

	// int(��)�� ����int(��)�� �����ִ� �Լ�.
	// std::binder1st< std::mem_fun1_t<int,SomeObject,int> >
	// ���̶�� �ϴ� ���� ����� ������ ������ ���� �ʾƵ� ���� ������ �� �ִ�
	SomeObject t( 3 );
	boost::function1<int, int> g =
		std::bind1st( std::mem_fun(&SomeObject::Do), &t );
	if( 45 == g(15) )
	{
		cout << 3 << endl;
	}

	return 0;
}

