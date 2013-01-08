/*

http://jacking75.gafe24.com/Boost/Spirit/primitives.html

*/
#include <stdafx.h>
// ������ ���� ���α׷�

#include <iostream>
#include <string>
#include <stack>
#include <boost/spirit.hpp>
using namespace std;
using namespace boost::spirit;

// �׼��� ����
#if 1

namespace calc_action
{
	stack<int> stk;
	void clear() { stk = stack<int>(); }
	int answer() { return stk.top(); }
	int toppop() { int a = stk.top(); stk.pop(); return a; }

	void test_push(int n)	{ cout << "test_push"<<endl; }
	void PUSH(int n)	{		stk.push( n ); 	}
	void ADD(const char*, const char*)
	{
		int b = toppop(), a = toppop(); stk.push(a+b);
	}
	void SUB(const char*, const char*)
	{
		int b = toppop(), a = toppop(); stk.push(a-b);
	}
	void MUL(const char*, const char*)
	{
		int b = toppop(), a = toppop(); stk.push(a*b);
	}
	void DIV(const char*, const char*)
	{
		int b = toppop(), a = toppop(); stk.push(a/b);
	}
}

#else

namespace calc_action
{
	stack<int> stk;

	void clear() { stk = stack<int>(); }
	int answer() { return stk.top(); }
	int toppop() { int a = stk.top(); stk.pop(); return a; }

	void test_push(int n)
	{
		cout << "test_push"<<endl;
	}

	void PUSH(int n)
	{
		cout << "PUSH(" << n << ")"<<endl;
		stk.push( n );
	}
	void ADD(const char*, const char*)
	{
		int b = toppop(), a = toppop();
		cout << "ADD(" << a << "+" << b <<") =" << a+b<<endl;
		stk.push(a+b);
	}
	void SUB(const char*, const char*)
	{
		int b = toppop(), a = toppop();
		cout << "SUB(" << a << "-" << b <<") = " << a-b <<endl;
		stk.push(a-b);
	}
	void MUL(const char*, const char*)
	{
		int b = toppop(), a = toppop();
		cout << "MUL(" << a << "*" << b <<") = " << a*b <<endl;
		stk.push(a*b);
	}
	void DIV(const char*, const char*)
	{
		int b = toppop(), a = toppop();
		cout << "DIV(" << a << "/" << b <<") = "<< a/b <<endl;
		stk.push(a/b);
	}
}
#endif 

/*
������ EBNF ������ ���� �ļ������̴�.

group       ::= '(' expression ')'
factor      ::= integer | group
term        ::= factor (('*' factor) | ('/' factor))*
expression  ::= term (('+' term) | ('-' term))*

boost::spirit�� ����� �̿��� ������ ���� ǥ���Ҽ� �ִ�.

group       = '(' >> expression >> ')';
factor      = integer | group;
term        = factor >> *(('*' >> factor) | ('/' >> factor));
expression  = term >> *(('+' >> term) | ('-' >> term));
*/

// ������ �����ߴ� definition ���ø��� ����� ������

// ���� ����
//   expression ::= term ('+' term | '-' term)*
//   term ::= factor ('*' factor | '/' factor)*
//   factor ::= int | '(' expression ')'
//
// ���� ��ȣ
//   expression

struct calc : public grammar<calc>
{
	template<typename S> struct definition
	{
		rule<S> expression, term, factor;
		definition(const calc& self)
		{
			using namespace calc_action;
			expression	= term		>> *( ('+' >> term)[&ADD] 
										| ('-' >> term)[&SUB] );

			term		= factor	>> *( ('*' >> factor)[&MUL] 
										| ('/' >> factor)[&DIV] );

			factor		=				int_p[&PUSH][&test_push] 
										| '(' >> expression >> ')';
		}

		const rule<S>& start() const { return expression; }
	};
};

// ��뿹

int main_spirit()
{
	for(string str; getline(cin,str) && str.size()>0; )
	{
		calc calc;
		
		parse_info<> r 
			= parse(str.c_str()
					, calc		// calc������ ���� �Ľ�
					, space_p);// ������ �����ϸ鼭 �ؼ�

		if( r.full )			// ��� �Ľ��� �Ǿ�����
			cout << calc_action::answer() << endl;
		else
			cout << "error" << endl;

		calc_action::clear();
	}
	return 0;
}

/*

��� ���
1+2
3
1+2*3
7
(1+2)*3
9
1-2+3*4/6-5-3
-7
hello
error

*/

