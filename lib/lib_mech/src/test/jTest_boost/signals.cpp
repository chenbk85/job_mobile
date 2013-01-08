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
	//boost::signal1<void , int> sig; �Ȱ��� �ǹ�
	boost::signal<void ( int)> sig; // �ֽ� �����Ϸ�����

	// ���
	sig.connect( &Dog );
	sig.connect( &Cat );
	sig.connect( &Chicken );
	sig.connect( &Dog );
	sig.connect( &Cat );

	// ȣ��
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
��¿�
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

// c �� ���� �ñ׳ο� ���ӵǰ� �ִ�
if (c.connected()) 
{
		sig(); // "Hello, World!" 	(��)�� ǥ���Ѵ�
}

c.disconnect(); // HelloWorld ������Ʈ�� ����.

assert(!c.connected()); // c�� Disconnect�Ǿ���.

sig(); // �ƹ��͵� ���� �ʴ´� 





{
	boost::signals::scoped_connection c = sig.connect(ShortLived());

	sig(); 	// ShortLived 	ȣ���.
}
sig(); // ShortLived�� ȣ����� �ʴ´�.






#endif