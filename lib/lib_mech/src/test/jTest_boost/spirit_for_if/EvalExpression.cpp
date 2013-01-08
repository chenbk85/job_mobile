#include "EvalExpression.h"
#pragma warning(disable : 4786)
#pragma warning(disable : 4761)
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>
#include <cstdio>
#include <boost/spirit/core.hpp>

#include "Factor.h"

using namespace std;
using namespace boost::spirit;

//////////////////////////////////////////////////////////////////////////////////////////
//	変数テーブル
//////////////////////////////////////////////////////////////////////////////////////////

class VariableTable { 
	std::map<std::string, int>		m_table;
public:

	bool Construct(const char* name, int value) { return Construct(static_cast<std::string>(name), value); }
	bool Construct(std::string& name, int value);
	bool Destruct(const char* name);

	bool SetValue(const char* name, int value) { return SetValue(static_cast<std::string>(name), value); }
	bool SetValue(std::string& name, int value);
	bool GetValue(const char* name, int& value);

	void PrintAllVariables();
};

VariableTable g_vartable;


bool VariableTable::Construct(string& name, int value)
{
	pair<map<string, int>::iterator, bool> res = m_table.insert(make_pair(name, value));

	return res.second;
}

bool VariableTable::Destruct(const char* name)
{
	map<string, int>::iterator it = m_table.find(static_cast<string>(name));

	if(it != m_table.end())
	{
		m_table.erase(it);
		return true;
	}
	else
	{
		return false;
	}
}

bool VariableTable::SetValue(string& name, int value)
{
	map<string, int>::iterator it = m_table.find(name);

	if(it != m_table.end())
	{
		it->second = value;
		return true;
	}
	else
	{
		return false;
	}
}

bool VariableTable::GetValue(const char* name, int& value)
{
	map<string, int>::iterator it = m_table.find(static_cast<string>(name));

	if(it != m_table.end())
	{
		value = it->second;
		return true;
	}
	else
	{
		return false;
	}
}

void VariableTable::PrintAllVariables()
{
	cout << "VariableTable::PrintAllVariables()" << endl;
	cout << "begin" << endl;

	for(map<string, int>::iterator it = m_table.begin(); it != m_table.end(); ++it)
	{
		cout << it->first << " = " << it->second << endl;
	}

	cout << "end" << endl;
}

//===================================================================

vector<char> r_name;

void BeginName(char c)
{
	r_name.clear();
	r_name.push_back(c);
}

void AckName(char c)
{
	r_name.push_back(c);
}

void EndName(const char* const, const char* const)
{
	r_name.push_back('\0');
}

vector<char> r_string;

void BeginString(const char* const, const char* const)
{
	r_string.clear();
}

void AckString(char c)
{
	r_string.push_back(c);
}

void EndString(const char* const, const char* const)
{
	if(!r_string.empty())
	{
		r_string.pop_back();	// '\"' をポップ
		r_string.push_back('\0');
	}
}

int r_int;

void Int(int i)
{
	r_int = i;
}

//===================================================================

// スタック

stack<Factor> stk;

void stk_clear()
{
	stk = stack<Factor>();
}

Factor stk_pop()
{
	Factor a = stk.top();
	stk.pop();
	return a;
}

void stk_push(Factor& factor)
{
	stk.push(factor);
}


// 変数の代入、宣言

void Assign(const char* const, const char* const)
{
	Factor b = stk_pop();
	Factor a = stk_pop();

	a.SetInt(b.GetInt());

	// debug
	printf("assign %d to %s\n", b.GetInt(), a.GetStr());

	g_vartable.SetValue(a.GetStr(), b.GetInt());

	stk_push(a);
}

void Declare(const char* const, const char* const)
{
	Factor factor(VAR_INT);

	factor.SetStr(static_cast<string>(r_name.begin()));

	g_vartable.Construct(r_name.begin(), 0xdddddddd);

	// debug
	printf("declare %s\n", r_name.begin());

	stk_push(factor);
}


// 因子

void PushInt(int n)
{
	Factor factor(CONST_INT);
	factor.SetInt(n);
	stk_push(factor);
}

void PushVariable(const char* const, const char* const)
{
	Factor factor(VAR_INT);
	factor.SetStr(static_cast<string>(r_name.begin()));

	// 変数テーブルから値を取得
	int value = 0;
	bool res = g_vartable.GetValue(r_name.begin(), value);
	if(res) factor.SetInt(value);
	
	stk_push(factor);
}

void EvalNot(const char* const, const char* const)
{
	Factor a = stk_pop();
	stk_push(!a);
}

// 項

void EvalMul(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a * b);
}

void EvalDiv(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a / b);
}

void EvalMod(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a % b);
}

void EvalAnd(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a && b);
}

// 単純式

void EvalAdd(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a + b);
}

void EvalSub(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a - b);
}

void EvalOr(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a || b);
}

// 式

void EvalEqual(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a == b);
}

void EvalNotEqual(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a != b);
}

void EvalLessThan(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a < b);
}

void EvalGreaterThan(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a > b);
}

void EvalLessThanEqual(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a <= b);
}

void EvalGreaterThanEqual(const char* const, const char* const)
{
	Factor b = stk_pop(), a = stk_pop();
	stk_push(a >= b);
}

//===================================================================

struct sentence_exe : public grammar<sentence_exe> {

	template<typename S> struct definition {

		rule<S> name_r, string_r, int_r;

		rule<S> variable;
		rule<S> simple_expression, term, factor;
		rule<S> declaration, assignment, expression;
		rule<S> sentence;
		rule<S> function;
		rule<S> program;

		definition(const sentence_exe& self)
		{
			// 文字列
			string_r	= '\"' >> *(anychar_p - '\"') >> '\"';

			// 名前
			name_r		= (alpha_p[&BeginName] | ch_p('_')[&BeginName]) >> *( (alnum_p[&AckName] | ch_p('_')[&AckName]) ) >> eps_p[&EndName];

			// 整数
			int_r		= int_p;

			// 変数
			variable	= name_r;

			// 宣言
			declaration = str_p("int") >> +space_p >> name_r[&Declare] >> 
							!( *space_p >> ch_p('=') >> *space_p >> expression >> *space_p >> eps_p[&Assign] );

			// 代入
			assignment = variable[&PushVariable] >> ch_p('=') >> expression >> eps_p[&Assign];

			// 式
			expression				= simple_expression >> 
										!(
											(str_p("==") >> simple_expression)[&EvalEqual]				| 
											(str_p("!=") >> simple_expression)[&EvalNotEqual]			| 
											(ch_p('<') >> simple_expression)[&EvalLessThan]				|
											(str_p("<=") >> simple_expression)[&EvalLessThanEqual]		| 
											(ch_p('>') >> simple_expression)[&EvalGreaterThan]			| 
											(str_p(">=") >> simple_expression)[&EvalGreaterThanEqual] 
										);

			// 単純式
			simple_expression		= term >> 
										*(
											(ch_p('+') >> term)[&EvalAdd]	| 
											(ch_p('-') >> term)[&EvalSub]	| 
											(str_p("||") >> term)[&EvalOr]
										 );
			// 項
			term					= factor >> 
										*(
											(ch_p('*') >> factor)[&EvalMul]		| 
											(ch_p('/') >> factor)[&EvalDiv]		| 
											(ch_p('%') >> factor)[&EvalMod]		| 
											(str_p("&&") >> factor)[&EvalAnd]
										 );
			// 因子
			factor					= int_p[&PushInt] | name_r[&PushVariable] |( "!" >> factor )[&EvalNot] | ( "(" >> expression >> ")" );

			// 文
			sentence	=	( declaration )	|
							( assignment )	|
							( expression )	;
							
			program		= *space_p >> sentence >> *space_p;
		}

		const rule<S>& start() const { return program; }
	};

};



////////////////////////////////////////////////////////////////////////////////////////////////

int EvalExpression::Eval(const char* expression)
{
	sentence_exe se;
	parse(expression, se);

	Factor f = stk_pop();

	return f.GetInt();
}