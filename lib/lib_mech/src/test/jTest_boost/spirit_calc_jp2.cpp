#include <stdafx.h>
#include <iostream>
#include <stack>
#include <boost/spirit/core.hpp>
using namespace std;
using namespace boost::spirit;
namespace spr_calc_jp2
{

stack<int> stk;
void clear()
{
	stk = stack<int>();
}
int toppop()
{
	int a = stk.top();
	stk.pop();
	return a;
}
void PUSH(int n)
{
	stk.push(n);
}
void EvalNot(const char* const, const char* const)
{
	int a = toppop();
	PUSH(!a);
}
void MUL(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a * b);
}
void DIV(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a / b);
}
void EvalMod(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a % b);
}
void EvalAnd(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a && b);
}
void ADD(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a + b);
}
void SUB(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a - b);
}
void EvalOr(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a || b);
}
void EvalEqual(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a == b);
}
void EvalNotEqual(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a != b);
}
void EvalLessThan(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a < b);
}
void EvalGreaterThan(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a > b);
}
void EvalLessThanEqual(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a <= b);
}
void EvalGreaterThanEqual(const char* const, const char* const)
{
	int b = toppop(), a = toppop();
	PUSH(a >= b);
}
struct calculator : public grammar<calculator> {
	template<typename S> struct definition {
		rule<S> expression, simple_expression, term, factor, compare_operator, addition_operator, multipication_operator;
		definition(const calculator& self)
		{
			expression				= simple_expression >> 
										!(
											(str_p("==") >> simple_expression)[&EvalEqual]				| 
											(str_p("!=") >> simple_expression)[&EvalNotEqual]			| 
											(ch_p('<') >> simple_expression)[&EvalLessThan]				|
											(str_p("<=") >> simple_expression)[&EvalLessThanEqual]		| 
											(ch_p('>') >> simple_expression)[&EvalGreaterThan]			| 
											(str_p(">=") >> simple_expression)[&EvalGreaterThanEqual] 
										);
			simple_expression		= term >> 
										*(
											(ch_p('+') >> term)[&ADD]	| 
											(ch_p('-') >> term)[&SUB]	| 
											(str_p("||") >> term)[&EvalOr]
										 );
			term					= factor >> 
										*(
											(ch_p('*') >> factor)[&MUL]		| 
											(ch_p('/') >> factor)[&DIV]		| 
											(ch_p('%') >> factor)[&EvalMod]		| 
											(str_p("&&") >> factor)[&EvalAnd]
										 );
			factor					=	int_p[&PUSH] 
										|	
										( 
											"!" >> factor )[&EvalNot] 
											| 
											( "(" >> expression >> ")" 
										);
		}
		const rule<S>& start() const { return expression; }	
	};
};

}

int main_spirit_calc_jp2()
{
    string str;
    while (getline(cin, str))
	{
		if(str[0]=='0')break;
		spr_calc_jp2::calculator calc;
		parse_info<> r = parse(str.c_str(), calc, space_p);
		if(r.full)	
			cout << "result = " << spr_calc_jp2::toppop() << endl;
		else	
			cout << "error" << endl;
		spr_calc_jp2::clear();
	}
	return 0;
}
