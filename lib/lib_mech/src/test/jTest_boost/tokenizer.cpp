#include <stdafx.h>
#include <iostream>
#include <string>
#include <boost/tokenizer.hpp>
using namespace std;

int main_tokenizer()
{
	{
		string str1 = "this  is a   pen";
		// ����Ʈ������, �ܶ� ����(�����̶���� �޸������) �� �����Ѵ�.
		typedef boost::tokenizer<>  tokenizer1;
		// �Ʒ��� ����
		//typedef boost::tokenizer<char_delimiters_separator<char>>  tokenizer1;
		tokenizer1 tok1( str1 );

		for( tokenizer1::iterator it=tok1.begin(); it!=tok1.end(); ++it )
			cout << "TOKEN: " << *it << endl;
		/* ��� 	TOKEN: this
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
		/* ���			
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

		/* ���			
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
	const int offsets[] = {4,2,2};// 4����,2����,2���ڿ� ������ ����.
	boost::offset_separator ofs( offsets, offsets+3 );
	typedef boost::tokenizer<boost::offset_separator> tokenizer2;
	tokenizer2 tok2( str2, ofs );

	for( tokenizer2::iterator it=tok2.begin(); it!=tok2.end(); ++it )
		cout << "offset_separator TOKEN: " << *it << endl;

	/* ���					offset_separator TOKEN: 2002
							offset_separator TOKEN: 09
							offset_separator TOKEN: 03
							*/


	{
		/*	csv���˿� ���� �и��� ���.
		[\\] [,] [\"]�� ���� �и���ų�� ���
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
				���		
				escaped_list_separator test
				TOKEN :Field 1
				TOKEN :putting quotes around fields, allows commas
				TOKEN :Field 3
		*/
	}

	return 0;
}

