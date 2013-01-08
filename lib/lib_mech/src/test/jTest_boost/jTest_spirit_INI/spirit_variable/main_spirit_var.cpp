#pragma warning(disable : 4786)
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>
#include <cstdio>
#include <boost/spirit/core.hpp>
using namespace std;
using namespace boost::spirit;
#include "comment_parser.h"
#include "Factor.h"
class VariableTable { 
	std::map<std::string, Factor*>		m_table;
public:
	bool Construct(const char* name, const Factor& value) { return Construct(static_cast<std::string>(name), value); }
	bool Construct(std::string& name, const Factor& value);
	bool Destruct(const char* name);
	bool SetValue(const char* name, const Factor& value) { return SetValue(static_cast<std::string>(name), value); }
	bool SetValue(std::string& name, const Factor& value);
	bool GetValue(const char* name, Factor& value);
	void PrintAllVariables();
};
VariableTable g_vartable;
bool VariableTable::Construct(string& name, const Factor& value)
{
	Factor* pnewfactor = new Factor(value);
	pair<map<string, Factor*>::iterator, bool> res = m_table.insert(make_pair(name, pnewfactor));
	if(!res.second) delete pnewfactor;
	return res.second;
}
bool VariableTable::Destruct(const char* name)
{
	map<string, Factor*>::iterator it = m_table.find(static_cast<string>(name));
	if(it != m_table.end())
	{
		delete it->second;
		m_table.erase(it);
		return true;
	}
	else
	{
		return false;
	}
}
bool VariableTable::SetValue(string& name, const Factor& value)
{
	map<string, Factor*>::iterator it = m_table.find(name);
	if(it != m_table.end())
	{
		*(it->second) = value;
		return true;
	}
	else
	{
		return false;
	}
}
bool VariableTable::GetValue(const char* name, Factor& value)
{
	map<string, Factor*>::iterator it = m_table.find(static_cast<string>(name));
	if(it != m_table.end())
	{
		value = *it->second;
		return true;
	}
	else
	{
		return false;
	}
}
void VariableTable::PrintAllVariables()
{
	cout << endl << "VariableTable::PrintAllVariables()" << endl;
	cout << "begin" << endl;
	for(map<string, Factor*>::iterator it = m_table.begin(); it != m_table.end(); ++it)
	{
		cout << it->first << " = " << it->second->GetInt() << " : " << it->second->GetStr() << endl;
	}
	cout << "end" << endl;
}
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
		r_string.pop_back();	
		r_string.push_back('\0');
	}
}
int r_int;
void Int(int i)
{
	r_int = i;
}
FACTOR_TYPE r_decleartype;
void DeclareInt(const char* const, const char* const)
{
	r_decleartype = VAR_INT;
}
void DeclareString(const char* const, const char* const)
{
	r_decleartype = VAR_STR;
}
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
void Assign(const char* const, const char* const)
{
	Factor b = stk_pop();
	Factor a = stk_pop();
	a.Assign(b);
	if(CONST_INT == b.GetType())
	{
		printf("assign %d to %s\n", b.GetInt(), a.GetName().c_str());
	}
	else
	{
		printf("assign %s to %s\n", b.GetStr().c_str(), a.GetName().c_str());
	}
	g_vartable.SetValue(a.GetName(), b);
	stk_push(a);
}
void Declare(const char* const, const char* const)
{
	Factor factor;
	if(VAR_INT == r_decleartype)
	{
		factor.SetType(VAR_INT);
	}
	else
	{
		factor.SetType(VAR_STR);
	}
	string str12 = (char*)&r_name[0];
	factor.SetName(str12);
	g_vartable.Construct(&r_name[0], factor);
	printf("declare %s\n", factor.GetName().c_str());
	stk_push(factor);
}
void PushInt(int n)
{
	Factor factor(CONST_INT);
	factor.SetInt(n);
	stk_push(factor);
}
void PushString(const char* const, const char* const)
{
	Factor factor(CONST_STR);
	factor.SetStr(static_cast<string>(&r_string[0]));
	stk_push(factor);
}
void PushVariable(const char* const, const char* const)
{
	Factor factor;
	bool res = g_vartable.GetValue(&r_name[0], factor);
	stk_push(factor);
}
void EvalNot(const char* const, const char* const)
{
	Factor a = stk_pop();
	stk_push(!a);
}
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
			string_r	= '\"' >> eps_p[&BeginString] >> *(anychar_p[&AckString] - '\"') >> '\"' >> eps_p[&EndString];
			name_r		= (alpha_p[&BeginName] | ch_p('_')[&BeginName]) >> *( (alnum_p[&AckName] | ch_p('_')[&AckName]) ) >> eps_p[&EndName];
			int_r		= int_p;
			variable	= name_r;
			declaration = (str_p("int")[&DeclareInt] | str_p("string")[&DeclareString]) >> +space_p >> name_r[&Declare] >> 
							!( *space_p >> ch_p('=') >> *space_p >> expression >> *space_p >> eps_p[&Assign] );
			assignment = variable[&PushVariable] >> ch_p('=') >> expression >> eps_p[&Assign];
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
											(ch_p('+') >> term)[&EvalAdd]	| 
											(ch_p('-') >> term)[&EvalSub]	| 
											(str_p("||") >> term)[&EvalOr]
										 );
			term					= factor >> 
										*(
											(ch_p('*') >> factor)[&EvalMul]		| 
											(ch_p('/') >> factor)[&EvalDiv]		| 
											(ch_p('%') >> factor)[&EvalMod]		| 
											(str_p("&&") >> factor)[&EvalAnd]
										 );
			factor					= int_p[&PushInt] | string_r[&PushString] | name_r[&PushVariable] |( "!" >> factor )[&EvalNot] | ( "(" >> expression >> ")" );
			sentence	=	( declaration )	|
							( assignment )	|
							( expression )	;
			program		= *space_p >> sentence >> *space_p;
		}
		const rule<S>& start() const { return program; }
	};
};
#include <windows.h>
#include <boost/filesystem/operations.hpp>
int main_spirit_var()
{
	boost::filesystem::path foo(boost::filesystem::initial_path() / "../jTest/spirit_var_test.txt" );
	string str1 = foo.normalize().native_directory_string();
	string source;
	FILE* fp = fopen(str1.c_str(), "r");
	if(!fp) return -1;
	char strbuf[512];
	sentence_exe se;
	comment_parser comment;
	while(NULL != fgets(strbuf, 512, fp))
	{
		parse(strbuf, se, comment);
	}
	fclose(fp);
	g_vartable.PrintAllVariables();
	return 0;
}
