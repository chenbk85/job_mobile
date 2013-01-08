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
	// int(와)과int(을)를 취해bool을 돌려주는 2인수 함수를 격납할 
	// 수 있는 함수 오브젝트.  우선 보통 함수를 넣어 본다.
	boost::function2<bool, int, int> cmp = &f;
	if( cmp(4, 20) )
	{
		cout << 1 << endl;
	}

	// 도중에 함수 오브젝트를 대입
	cmp = std::not2( std::less<int>() );
	if( cmp(4, 20) )
	{
		cout << 2 << endl;
	}

	// int(을)를 취해int(을)를 돌려주는 함수.
	// std::binder1st< std::mem_fun1_t<int,SomeObject,int> >
	// 등이라고 하는 이유 몰라요 형태의 변수로 받지 않아도 보관 유지할 수 있다
	SomeObject t( 3 );
	boost::function1<int, int> g =
		std::bind1st( std::mem_fun(&SomeObject::Do), &t );
	if( 45 == g(15) )
	{
		cout << 3 << endl;
	}

	return 0;
}

