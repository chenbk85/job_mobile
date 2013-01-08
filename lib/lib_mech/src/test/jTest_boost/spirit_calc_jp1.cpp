#include <stdafx.h>
#include <iostream>
#include <stack>
#include <boost/spirit/core.hpp>

using namespace std;
using namespace boost::spirit;





struct calculator_jp1 : public grammar<calculator_jp1> {

	template<typename S> struct definition {

		rule<S> expression, simple_expression, term, factor, compare_operator, addition_operator, multipication_operator;

		definition(const calculator_jp1& self)
		{
			
			expression				= simple_expression >> !( compare_operator >> simple_expression );
			simple_expression		= term >> *( addition_operator >> term );
			term					= factor >> *( multipication_operator | factor );
			factor					= int_p | ( "!" >> factor ) | ( "(" >> expression >> ")" );
			compare_operator		= str_p("==") | str_p("!=") | ch_p('<') | str_p("<=") | ch_p('>') | str_p(">=");
			addition_operator		= ch_p('+') | ch_p('-') | str_p("||");
			multipication_operator	= ch_p('*') | ch_p('/') | ch_p('%') | str_p("&&");
		}

		
		const rule<S>& start() const { return expression; }	

	};

};



int main_spirit_calc_jp1()
{
	string str;
	while (getline(cin, str))
	{
		if(str[0]=='0')
			break;
		calculator_jp1 calc;

		
		parse_info<> r = parse(str.c_str(), calc, space_p);

		if(r.full)	
			cout << "ok" << endl;
		else	
			cout << "error" << endl;

	}

	return 0;
}
