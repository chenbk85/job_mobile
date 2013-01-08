#include <stdafx.h>

void Dog(int c)
{
	for(int i=0; i!=c; ++i)
		cout << "BowWow" << endl;
}

void Cat(int c)
{
	for(int i=0; i!=c; ++i)
		cout << "Mewmew" << endl;
}
void Chicken(int c)
{
	for(int i=0; i!=c; ++i)
		cout << "cock-a-doodle-doo" << endl;
}
struct Hello 
{
  void operator()() const
  {
    std::cout << "Hello";
  }
};

struct World
{
  void operator()() const
  {
    std::cout << ", World!" << std::endl;
  }
};

struct GoodMorning
{
  void operator()() const
  {
    std::cout << "... and good morning!" << std::endl;
  }
};

int main_signal()
{
	//boost::signal1<void , int> sig; 똑같은 의미
	boost::signal<void ( int)> sig; // 최신 컴파일러에서

	// 등록
	sig.connect( &Dog );
	sig.connect( &Cat );
	sig.connect( &Chicken );
	sig.connect( &Dog );
	sig.connect( &Cat );

	// 호출
	sig( 2 );



	{

	boost::signal<void ()> sig;

	sig.connect(Hello());
	sig.connect(World());
	sig();


	}


	{

	boost::signal<void ()> sig;
	sig.connect(1, World());
	sig.connect(0, Hello());
	sig();


	sig.connect(GoodMorning());

	}



	return 0;
}

/*
출력예
Mewmew
Mewmew
cock-a-doodle-doo
cock-a-doodle-doo
BowWow
BowWow
*/

#if 0


boost::signal<float (float, float), 
aggregate_values<std::vector<float> > > sig;

sig.connect(&compute_quotient);
sig.connect(&compute_product);
sig.connect(&compute_sum);
sig.connect(&compute_difference);

std::vector<float> results = sig(5, 3);

/*								*/

class Button 
{
	typedef boost::signal<void (int x, int y)> OnClick;
	OnClick onClick;
public:
	void Add_Action(const OnClick::slot_type& slot);
	{
		onClick.connect(slot);
	}
};

void printCoordinates(long x, long y)
{
	std::cout << "(" << x << ", " << y << ")\n";
}

void f(Button& button)
{
	button.Add_Action(&printCoordinates);
}






//=====================

boost::signals::connection c = sig.connect(HelloWorld());

// c 는 아직 시그널에 접속되고 있다
if (c.connected()) 
{
		sig(); // "Hello, World!" 	(을)를 표시한다
}

c.disconnect(); // HelloWorld 오브젝트를 절단.

assert(!c.connected()); // c는 Disconnect되었다.

sig(); // 아무것도 하지 않는다 





{
	boost::signals::scoped_connection c = sig.connect(ShortLived());

	sig(); 	// ShortLived 	호출됨.
}
sig(); // ShortLived는 호출되지 않는다.






#endif