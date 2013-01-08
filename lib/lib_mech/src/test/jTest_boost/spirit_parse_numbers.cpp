#include <stdafx.h>
///////////////////////////////////////////////////////////////////////////////
//
//  A parser for a comma separated list of numbers
//
//  [ JDG 5/10/2002 ]
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/core.hpp>
#include <iostream>
#include <vector>
///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace spirit;
///////////////////////////////////////////////////////////////////////////////
//
//  Our comma separated list parser
//
///////////////////////////////////////////////////////////////////////////////
static void test()
{
	{
		// rule�� �ļ� ������Ʈ�� �����塱�� �� �ִ�. �̰͵鿡 ���ؼ���
		// �ڿ� �������� �켱 rule�� � ������ ���¶�� �����ϸ� ����
		rule<> r1, r2, r3;
		chlit<char> x('X');     // x �̶�� �̸��� �ļ��� ����
		r1 = chlit<char>('X');  //  ������� ����
		r2 = x;                    //  x�� �̿��� ��
		r3 = ch_p('X');           //  ���׷����͸� �̿��� ��
	}

	{
		strlit<>("Hello World");
		str_p("Hello World");
		std::string msg("Hello World");
		//strlit<>(msg.begin(), msg.end());
	}
	{
		chseq<>("ABCDEFG");
		chseq_p("ABCDEFG");
		chseq<>("ABCDEFG");
		/*
		ABCDEFG
		A B C D E F G
		AB CD EFG
		*/
	}
	{
		uint_parser<unsigned, 10, 1, 3> uint3_p;        //  1 ~ 3 �ڸ���
		uint_parser<unsigned, 10, 3, 3> uint3_3_p;      //  ��ƴ���� 3�ڸ���
		rule<> ts_num_p = (uint3_p >> *(',' >> uint3_3_p));    
		//  3�ڸ� ���� �ܶ� ������ ��ġ�� �ļ�
	}
}
bool parse_numbers(char const* str
				   , vector<double>& v)
{
	return parse( 	str  //�Է¹���
		,( 	real_p[append(v)] 
			>> *(',' >> real_p[append(v)]) 
		) 
		, space_p // �Ľ� ��ŵ �ļ�( ���� )
	).full;
}

bool parse_numbers1(char const* str, vector<double>& v)
{
	uint_parser<unsigned, 10, 1, 3> uint3_p; //  1 ~ 3 �ڸ���
	uint_parser<unsigned, 10, 3, 3> uint3_3_p;//��ƴ���� 3�ڸ���
	return parse(str,
		//  Begin grammar
		(
		(uint3_p[append(v)] >> *(',' >> uint3_3_p[append(v)]))
		)
		,
		//  End grammar
		space_p).full;
}

bool parse_numbers(char const* str)
{
	return parse(str, real_p >> *(',' >> real_p), space_p).full;
}

#if 0
bool parse_str(char const* str, vector<string>& v)
{

	return parse(str,
		//  Begin grammar
		(
			confix_p('"', *c_escape_ch_p, '"')
		)
		,
		//  End grammar
		space_p).full;
}
#endif

////////////////////////////////////////////////////////////////////////////
//
//  Main program
//
////////////////////////////////////////////////////////////////////////////
int
main_parse_numbers()
{
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tA comma separated list parser for Spirit...\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "Give me a comma separated list of numbers.\n";
	cout << "The numbers will be inserted in a vector of numbers\n";
	cout << "Type [q or Q] to quit\n\n";
	for (;;)
	{
		char str[256];
		cin.getline(str, 256);
		if (str[0] == 'q' || str[0] == 'Q')
			break;
		vector<double> v;
		if (parse_numbers1(str, v))
		{
			cout << "-------------------------\n";
			cout << "Parsing succeeded\n";
			cout << str << " Parses OK: " << endl;
			for (int i = 0; i < v.size(); ++i)
				cout << i << ": " << v[i] << endl;
			cout << "-------------------------\n";
		}
		else
		{
			cout << "-------------------------\n";
			cout << "Parsing failed\n";
			cout << "-------------------------\n";
		}
	}
	cout << "Bye... :-) \n\n";
	return 0;
}
