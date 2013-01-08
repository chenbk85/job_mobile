#include <stdafx.h>
#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>


using namespace std;

bool is_ordered( int a, int b, int c )
{ 	
	return a<=b && b<=c; 
}

int main_bind()
{
	{
		// 7 �̻� 12 ������ ������ ��Ҹ� ã�´�. 
		// is_ordered�� ������bind�� (���� �ٿ� ) 
		// ��is_ordered(7, ù ��° �μ�, 12)���� ���
		// �Լ� ������Ʈ�� ����� �ִ� ���Դϴ�. 

		int arr[] = {1,2,3,4,5,6,7,8,9,10};
		const int len = sizeof(arr) / sizeof(arr[0]);

		int* f = find_if( arr, arr+len,
			boost::bind(is_ordered, 7, _1, 12) );
		cout << *f << endl;
	}
	{
		// �� ĳ���� ������ 4��°�� ���ڸ� ������ cout�� ����Ѵ�. 
		// ��ù ��° �μ�.at( 3 )���� ��� �Լ� ������Ʈ��
		// ����� �ֽ��ϴ�. bind�� ��� �Լ��� �ǳ��ָ�
		// �ڵ������� Ŭ���� ������ ù ��° �μ��� ���ϴ� �Լ���
		// �о� �ٲپ� �ݴϴ�. 
		// boost::mem_fn����. 

		string arr[] = {"hello","my_name","is_k","inaba.","bye!"};
		const int len = sizeof(arr) / sizeof(arr[0]);

		transform( arr, arr+len, ostream_iterator<char>(cout),
			boost::bind(&string::at, _1, 3) );
		cout << endl;
	}
	{
		// ū ������ �þ���� ��ü. 
		// ��less<int>()(��2 �μ� , ���� �μ�)��
		// �� ��� �Լ� ������Ʈ�Դϴ�. �μ��� �ݴ�� ���� ��. 

		int arr[] = {7,3,4,9,1,2,5,8};
		const int len = sizeof(arr) / sizeof(arr[0]);

		sort( arr, arr+len,
			boost::bind(less<int>(), _2, _1) );
		copy( arr, arr+len, ostream_iterator<int>(cout) );

		printf("\n");
		{
			int arr[] = {7,3,4,9,1,2,5,8};
			sort( arr, arr+len,
				boost::bind(greater <int>(), _1, _2) );
			copy( arr, arr+len, ostream_iterator<int>(cout) );
		}
		cout << endl;
	}

	return 0;
}

/*
main_bind call!!!
7
lnkb!
98754321
98754321
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <boost/mem_fn.hpp>
using namespace std;

struct SomeObject
{
public:
	SomeObject( const char* szName ) 
		: m_szName( szName ) {}

	void Print() 
	{ 
		cout << "m_szName=" << m_szName << endl; 
	}
	void Print1(const char* szArg1) 
	{ 
		cout << m_szName <<"-"<<szArg1<< endl; 
	}
	void Print2(const char* szArg1
				,const char* szArg2) 
	{ 
		cout << m_szName <<"-"
			<<szArg1<<"-:"<<szArg2<< endl; 
	}
	void Print3(const char* szArg1,
				SomeObject* szArg2) 
	{ 
		cout << m_szName <<"-"<<szArg1 
			<<"-:"<<szArg2->m_szName<< endl; 
	}
	const char* m_szName;
};

int main_mem_fn()
{
	vector<SomeObject> v;
	v.push_back(SomeObject("Taro"));
	v.push_back(SomeObject("Jiro"));
	v.push_back(SomeObject("Saburo"));
	v.push_back(SomeObject("Shiro"));
	v.push_back(SomeObject("Goro"));

	// std::mem_fun_ref �� ������ 
	for_each( v.begin(), v.end(),
		boost::mem_fn(&SomeObject::Print) );

	cout << "--------------" << endl;

	vector<SomeObject*> vp;
	vp.push_back(new SomeObject("Rokuro"));
	vp.push_back(new SomeObject("Shichiro"));
	vp.push_back(new SomeObject("Hachiro"));
	vp.push_back(new SomeObject("Kuro"));

	// ���� ���·� std::mem_fun�� ����� �� �ִ�.
	for_each( vp.begin(), vp.end()
		, boost::mem_fn(&SomeObject::Print) );

	for_each( vp.begin(), vp.end()
		, boost::bind(&SomeObject::Print2 , _1 
		, "[Print2]","1234") );
	for_each( vp.begin(), vp.end()
		, boost::bind(&SomeObject::Print3 , _1 
		, "[Print3]",_1 ) );
	return 0;
}
/*

main_mem_fn call!!!
name=Taro
name=Jiro
name=Saburo
name=Shiro
name=Goro
--------------
name=Rokuro
name=Shichiro
name=Hachiro
name=Kuro

Rokuro-[Print2]-:1234
Shichiro-[Print2]-:1234
Hachiro-[Print2]-:1234
Kuro-[Print2]-:1234

Rokuro-[Print3]-:Rokuro
Shichiro-[Print3]-:Shichiro
Hachiro-[Print3]-:Hachiro
Kuro-[Print3]-:Kuro

*/



int a_plus_b(int a, int b)
{
	cout << "a + b = " << a + b <<endl;
	return a + b;
}

int a_plus_b_plus_c(int a, int b, int c)
{
	cout << "a + b +c= " << a + b +c<<endl;
	return a + b + c;
}

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
static void test_A_plus_B()
{
	A_plus_B a_b;
	int x = 104;
	//bind<int>(a_b, _1, _1)(x);		// a_b(x, x), i.e. zero
	boost::bind(boost::type<int>(), a_b, _1, _1)(x);//104 + 104 = 208
	long a3 =3;
	boost::bind(boost::type<int>(), a_b, _1, _1)(a3);//3==3= true
	boost::bind(boost::type<long>(), a_b, _1, _1)(a3);//3==3= true
}


struct Print_A
{
	bool print(int a){
		cout << "a=" << a << endl;
		return (bool)a;

	}
};

static void test_Print_A()
{
	Print_A x;
	
	boost::shared_ptr<Print_A> p(new Print_A);
	
	int i = 5;

	boost::bind(&Print_A::print, boost::ref(x), _1)(i);		
	// x.print(i)
	//a=5

	boost::bind(&Print_A::print, &x, _1)(boost::cref(i+i));			
	//(&x)->print(i)
	//a=10

	boost::bind(&Print_A::print, x, _1)(i);			
	// (internal copy of x).print(i)
	//a=5

	boost::bind(&Print_A::print, p, _1)(i);			
	// (internal copy of p)->print(i)
	//a=5
}

int f1( int i)
{
	i *=10;
	cout << "f1 = " << i  << endl;
	return i;
}

int g1( int i)
{
	i +=10;
	cout << "g1 = " << i  << endl;
	return i;
}

void static test_f1_g1()
{
	int x = 5;
	bind(f1, bind(g1, _1))(x); // f1(g1(x))  
	//bind(g1, _1)(x) �� �켱 �� 
	// g1(x) �ǰ� ������ bind(f1, g1(x))(x) 
	//�� �򰡵Ǿ� �������� ����� f1(g1(x)) �ȴ�.
	/* ���			
				g1 = 15
				f1 = 150
	*/
}
//for_each( a.begin(), a.end(), bind(&Obj::InitStepTwo, bind(&Obj::InitStepOne,_1) )
int main_bind_2()
{
	/*
	ǥ�� ���̺귯���� mem_fun�� �̿��ϸ� ptr->Func()�� 
	mem_fun(&Class::Func)( ptr ) �� ǥ���Ҽ����� 
	
	�� ���·� �� �θ�  for_each ���� �˰����� 
	��� �Լ��� ���ؼ��� �̿��� �� �ְ� �Ǿ� ���մϴ�. 

	�ٸ� �̳༮�� obj.Func()�� ���� mem_fun_ref(&Class::Func)( obj ) �� ����
	�ٸ� mem_fun_ref�� �ʿ��ϰ� �μ��� ������ �ʴ�  �Լ� �ۿ� ����� �� ���⿡ 
	���� ����� �������� �����մϴ�. 

	boost::mem_fn�� �����Ϳ� ����, const �� �������
	�μ��� ���� 2�� �̻󿡼��� ��밡��.
*/

	{
		int i = 5;
		bind(a_plus_b, i, _1)(boost::cref(i+i)); //a + b = 15

	}
	{
		int i = 55;
		int ii = 23;
		bind(a_plus_b, boost::ref(i), _1)(ii);//a + b = 78
		bind(a_plus_b, boost::cref(42), _1)(boost::cref(1));//a + b = 43
	}
	test_A_plus_B();

	{
		int x = 8;
		cout << "aaa = " <<bind(std::less<int>(), _1, 9)(x) << endl;	// x < 9
		//aaa = true
	}

	test_Print_A();
	test_f1_g1();
	return 0;
}
/*
main_bind_2 call!!!
a + b = 15
a + b = 78
a + b = 43
104 + 104 = 208
3==3= true
3==3= true
aaa = true
a=5
a=10
a=5
a=5
g1 = 5
f1 = 5

*/


