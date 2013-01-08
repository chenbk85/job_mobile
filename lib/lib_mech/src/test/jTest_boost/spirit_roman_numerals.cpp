#include <stdafx.h>
/*=============================================================================
Copyright (c) 2002-2003 Joel de Guzman
http://spirit.sourceforge.net/

Use, modification and distribution is subject to the Boost Software
License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
///////////////////////////////////////////////////////////////////////////////
//
//  A Roman Numerals Parser (demonstrating the symbol table). This is 
//  discussed in the "Symbols" chapter in the Spirit User's Guide.
//
//  [ JDG 8/22/2002 ]
//
///////////////////////////////////////////////////////////////////////////////
#include <boost/spirit/core.hpp>
#include <boost/spirit/symbols/symbols.hpp>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////////////////////
using namespace std;
using namespace boost::spirit;

///////////////////////////////////////////////////////////////////////////////
//
//  Parse jRoman_grammer jHundreds (100..900) numerals using the symbol table.
//  Notice that the data associated with each slot is passed
//  to attached semantic actions.
//
///////////////////////////////////////////////////////////////////////////////
struct jHundreds : symbols<unsigned>
{
	jHundreds()
	{
		add
			("C"    , 100)
			("CC"   , 200)
			("CCC"  , 300)
			("CD"   , 400)
			("D"    , 500)
			("DC"   , 600)
			("DCC"  , 700)
			("DCCC" , 800)
			("CM"   , 900)
			;
	}

} g_Sym_Hundreds_p;

///////////////////////////////////////////////////////////////////////////////
//
//  Parse jRoman_grammer jTens (10..90) numerals using the symbol table.
//
///////////////////////////////////////////////////////////////////////////////
struct jTens : symbols<unsigned>
{
	jTens()
	{
		add
			("X"    , 10)
			("XX"   , 20)
			("XXX"  , 30)
			("XL"   , 40)
			("L"    , 50)
			("LX"   , 60)
			("LXX"  , 70)
			("LXXX" , 80)
			("XC"   , 90)
			;
	}

} g_Sym_tens_p;

///////////////////////////////////////////////////////////////////////////////
//
//  Parse jRoman_grammer jOnes (1..9) numerals using the symbol table.
//
///////////////////////////////////////////////////////////////////////////////
struct jOnes : symbols<unsigned>
{
	jOnes()
	{
		add
			("I"    , 1)
			("II"   , 2)
			("III"  , 3)
			("IV"   , 4)
			("V"    , 5)
			("VI"   , 6)
			("VII"  , 7)
			("VIII" , 8)
			("IX"   , 9)
			;
	}

} g_Sym_ones_p;

///////////////////////////////////////////////////////////////////////////////
//
//  Semantic actions
//
///////////////////////////////////////////////////////////////////////////////
struct add_1000_func
{
	add_1000_func(unsigned& r_) : uintVall(r_) {}
	void operator()(char) const 
	{ 
		uintVall += 1000; 
		cout << "add_1000_func = " << uintVall <<endl;
	}
	unsigned& uintVall;
};

struct add_roman_func
{
	add_roman_func(unsigned& r_) : uintVall(r_) {}
	void operator()(unsigned n) const 
	{ 
		uintVall += n; 
	}
	unsigned& uintVall;
};

///////////////////////////////////////////////////////////////////////////////
//
//  jRoman_grammer (numerals) grammar
//
///////////////////////////////////////////////////////////////////////////////
struct jRoman_grammer : public grammar<jRoman_grammer>
{
	template <typename ScannerT>
	struct definition
	{
		definition(jRoman_grammer const& self)
		{
			first
				=   g_Sym_tens_p      [add_roman_func(self.m_uintVall)]
				||  g_Sym_ones_p      [add_roman_func(self.m_uintVall)];

		}

		rule<ScannerT> first;
		rule<ScannerT> const&
			start() const { return first; }
	};

	jRoman_grammer(unsigned& r_) : m_uintVall(r_) {}
	unsigned& m_uintVall;
};

///////////////////////////////////////////////////////////////////////////////
//
//  Main driver code
//
///////////////////////////////////////////////////////////////////////////////
int
main_spirit_roman_numerals()
{
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tRoman Numerals Parser\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "Type a Roman Numeral ...or [q or Q] to quit\n\n";

	//  Start grammar definition

	string str;
	while (getline(cin, str))
	{
		if (str.empty() || str[0] == 'q' || str[0] == 'Q')
			break;

		unsigned n = 0;
		jRoman_grammer roman_p(n);
		if (parse(str.c_str(), roman_p).full)
		{
			cout << "parsing succeeded\n";
			cout << "result = " << n << "\n\n";
		}
		else
		{
			cout << "parsing failed\n\n";
		}
	}

	cout << "Bye... :-) \n\n";

	return 0;
}
