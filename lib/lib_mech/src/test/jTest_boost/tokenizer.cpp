#include <stdafx.h>
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
using namespace std;

int main_tokenizer()
{
	{
		string str1 = "this  is a   pen";
		// 디폴트에서는, 단락 문자(공백이라든지 콤마라든지) 로 분할한다.
		typedef boost::tokenizer<>  tokenizer1;
		// 아래와 동등
		//typedef boost::tokenizer<char_delimiters_separator<char>>  tokenizer1;
		tokenizer1 tok1( str1 );

		for( tokenizer1::iterator it=tok1.begin(); it!=tok1.end(); ++it )
			cout << "TOKEN: " << *it << endl;
		/* 출력 	TOKEN: this
		TOKEN: is
		TOKEN: a
		TOKEN: pen			*/
	}


	//
	{
		cout << endl <<
			"boost::tokenizer<boost::char_separator<char> >  test" << endl ;
		std::string str = ";;Hello|world||-foo--bar;yow;baz|";
		typedef boost::tokenizer<boost::char_separator<char> > 
			tokenizer;
		boost::char_separator<char> sep("-;|");
		tokenizer tokens(str, sep);
		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter)
			std::cout << "TOKEN :" << *tok_iter << endl;
		std::cout << "\n\n";
		/* 출력			
		boost::tokenizer<boost::char_separator<char> >  test
		TOKEN :Hello
		TOKEN :world
		TOKEN :foo
		TOKEN :bar
		TOKEN :yow
		TOKEN :baz	
		*/
	}
	//
	{
		cout << "sep(\"-;\", \"|\", boost::keep_empty_tokens);\n" << endl ;

		std::string str = "-;;Hello|world||-foo--bar;yow;baz| sdf||asdf";

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

		//boost::char_separator<char> sep("-;", "|");

		boost::char_separator<char> sep("-;", "|" , boost::keep_empty_tokens);

		tokenizer tokens(str, sep);

		for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end()
			; ++tok_iter)
		{
			std::cout << "TOKEN : " << *tok_iter << endl;
		}

		std::cout << "\n\n";

		/*
		boost::char_separator<char> sep("-;", "|");

		TOKEN : Hello
		TOKEN : |
		TOKEN : world
		TOKEN : |
		TOKEN : |
		TOKEN : foo
		TOKEN : bar
		TOKEN : yow
		TOKEN : baz
		TOKEN : |
		*/

		/* 출력			
		sep("-;", "|", boost::keep_empty_tokens);
		TOKEN :
		TOKEN :
		TOKEN :
		TOKEN : Hello
		TOKEN : |
		TOKEN : world
		TOKEN : |
		TOKEN :
		TOKEN : |
		TOKEN :
		TOKEN : foo
		TOKEN :
		TOKEN : bar
		TOKEN : yow
		TOKEN : baz
		TOKEN : |
		TOKEN :		
		*/
	}


	string str2 = "20020903";
	const int offsets[] = {4,2,2};// 4문자,2문자,2문자에 분할해 본다.
	boost::offset_separator ofs( offsets, offsets+3 );
	typedef boost::tokenizer<boost::offset_separator> tokenizer2;
	tokenizer2 tok2( str2, ofs );

	for( tokenizer2::iterator it=tok2.begin(); it!=tok2.end(); ++it )
		cout << "offset_separator TOKEN: " << *it << endl;

	/* 출력					offset_separator TOKEN: 2002
							offset_separator TOKEN: 09
							offset_separator TOKEN: 03
							*/


	{
		/*	csv포맷에 대한 분리에 사용.
		[\\] [,] [\"]에 대해 분리시킬때 사용
		Field 1,Field 2,Field 3
		Field 1,"Field 2, with comma",Field 3
		Field 1,Field 2 with \"embedded quote\",Field 3
		Field 1, Field 2 with \n new line,Field 3
		Field 1, Field 2 with embedded \\ ,Field 3
		*/
		using namespace std;
		using namespace boost;

		cout << endl << "escaped_list_separator test"<< endl << endl;


		string s = "Field 1,\"putting quotes around fields,allows commas\",Field 3";
		
		typedef tokenizer<escaped_list_separator<char> > esc_separator_t;
		esc_separator_t tok(s);
		
		for(esc_separator_t::iterator beg=tok.begin()
			; beg!=tok.end();++beg)
		{
				cout << "TOKEN :" <<*beg << "\n";
		}

		/* 
				출력		
				escaped_list_separator test
				TOKEN :Field 1
				TOKEN :putting quotes around fields, allows commas
				TOKEN :Field 3
		*/
	}

	return 0;
}

