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
		// rule은 파서 오브젝트를 ”저장”할 수 있다. 이것들에 대해서는
		// 뒤에 말하지만 우선 rule은 어떤 종류의 형태라고 생각하면 좋다
		rule<> r1, r2, r3;
		chlit<char> x('X');     // x 이라는 이름의 파서를 선언
		r1 = chlit<char>('X');  //  명시적인 선언
		r2 = x;                    //  x를 이용한 것
		r3 = ch_p('X');           //  제네레이터를 이용한 것
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
		uint_parser<unsigned, 10, 1, 3> uint3_p;        //  1 ~ 3 자리수
		uint_parser<unsigned, 10, 3, 3> uint3_3_p;      //  빈틈없이 3자리수
		rule<> ts_num_p = (uint3_p >> *(',' >> uint3_3_p));    
		//  3자리 수로 단락 지어진 수치의 파서
	}
}
bool parse_numbers(char const* str
				   , vector<double>& v)
{
	return parse( 	str  //입력문자
		,( 	real_p[append(v)] 
			>> *(',' >> real_p[append(v)]) 
		) 
		, space_p // 파싱 스킵 파서( 공백 )
	).full;
}

bool parse_numbers1(char const* str, vector<double>& v)
{
	uint_parser<unsigned, 10, 1, 3> uint3_p; //  1 ~ 3 자리수
	uint_parser<unsigned, 10, 3, 3> uint3_3_p;//빈틈없이 3자리수
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
