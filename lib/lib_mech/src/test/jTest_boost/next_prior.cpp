/*
http://j2k.naver.com/j2k_frame.php/korean/www.kmonos.net/alang/boost/utility.html
*/
#include <stdafx.h>
#include <list>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>

#include <boost/utility.hpp>
using namespace std;

int main_next()
{
	list<int> lst( 2 );
	*lst.begin() = 10;
	*boost::next( lst.begin() ) = 20;
	transform(lst.begin() ,lst.end() 
		,std::ostream_iterator<int>(cout),negate<int>());

	return 0;
}



#include <boost/utility.hpp>

class SomeThing : boost::noncopyable
{
	int i;
	string str;
};

int main_noncopyable()
{
	SomeThing a, b;
	// a = b; // ���⼭ compile error�� �ȴ�
	//SomeThing c( a ); // �̰͵� ����

	return 0;
}

#include <iostream>
#include <string>
#include <boost/utility/value_init.hpp>
using namespace std;


int main_value_initialized()
{
	int x;
	// ���� !!! 	cout << x << endl;

	boost::value_initialized<int> y;
	cout << y << endl;  // or cout << y.data() << endl

	string s;
	cout << s.size() << endl;

	boost::value_initialized<string> t;
	cout << t.data().size() << endl;

	return 0;
}
/*
��¿�
0
0
0

*/

#include <iostream>
#include <boost/io/ios_state.hpp>
using namespace std;

void print_hex( int n )
{
	boost::io::ios_flags_saver ifs( cout );
	cout << hex << n << endl;
} // ���⼭ ifs �� �Ҹ��ڰ� �Ҹ���.

int main_ios_flags_saver()
{
	print_hex( 90 );
	cout << 90 << endl;

	return 0;
}
/*
��¿�

5a
90

����� ���κ��� �ܼ��ϰ� ios_flags_save (��)�� ������ ������, 2��°�� ��¿�����16 ��ǥ�ð� �Ǿ� �����ϴ�.
*/


#include <iostream>
#include <boost/timer.hpp>
using namespace std;

int main_timer()
{
	boost::timer t;
	unsigned int a=0;
	for( unsigned int i=0; i<10000; ++i )
		for( unsigned int j=0; j<60000; ++j )
			a += i; // �����ϰ� �ð� �� ������ ���� �� ���� ó��

	cout << t.elapsed() << "�� �ɷȽ��ϴ�" << endl;
	return 0;
}
/*
��¿�
2.093
�� �ɷȽ��ϴ�

*/


#include <boost/progress.hpp>

int main_progress_timer2()
{
	boost::progress_timer t;
	unsigned int a=0;
	for( unsigned int i=0; i<10000; ++i )
		for( unsigned int j=0; j<60000; ++j )
			a += i; // �����ϰ� �ð� �� ������ ���� �� ���� ó��

	return 0;
} // t�� �Ҹ��ڰ� �ҷ� �� ���⼭ �ð�ǥ��

void DoSomething(int i )
{
	for(int j = 0; j < 100 ; ++j)
	{
			int aa  =0;
			++aa;
	}

}


#include <boost/progress.hpp>

int main_progress_display()
{
	const int MAX = 10000000;

	boost::progress_display show_progress( MAX );
	for( int i=0; i<MAX; ++i )
	{
		DoSomething(i);  // �����ΰ� ó��
		++show_progress;
	}
	return 0;
}


#include <iostream>
#include <boost/dynamic_bitset.hpp>
int main_dynamic_bitset() {
  const boost::dynamic_bitset<> mask(12, 2730ul); 
  std::cout << "mask = " << mask << std::endl;

  boost::dynamic_bitset<> x(12);

  std::cout << "Enter a 12-bit bitset in binary: " << std::flush;
  if (std::cin >> x) {
    std::cout << "input number:     " << x << std::endl;
    std::cout << "As unsigned long: " << x.to_ulong() << std::endl;
    std::cout << "And with mask:    " << (x & mask) << std::endl;
    std::cout << "Or with mask:     " << (x | mask) << std::endl;
    std::cout << "Shifted left:     " << (x << 1) << std::endl;
    std::cout << "Shifted right:    " << (x >> 1) << std::endl;
  }
  return EXIT_SUCCESS;
}

/*
The output is

mask = 101010101010
Enter a 12-bit bitset in binary: 100110101101
input number =    100110101101
As unsigned long: 2477
And with mask:    100010101000
Or with mask:     101110101111
Shifted left:     001101011010
Shifted right:    010011010110

*/
