#include <iostream>
#include <stack>
#include <vector>
#include <cstdio>
#include <boost/spirit/core.hpp>
#include <boost/spirit/dynamic/if.hpp>
#include <boost/spirit/utility/functor_parser.hpp>
#include "boost/filesystem/fstream.hpp"    // ditto
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/exception.hpp>

#include "INIFile.h"
using namespace std;
using namespace boost::spirit;
namespace
{

vector<char> r_name;
void BeginName(char c)
{
	cout << "BeginName = " << c << endl;
	r_name.clear();
	r_name.push_back(c);
}
void AckName(char c)
{
	cout << "AckName = " << c << endl;
	r_name.push_back(c);
}
void EndName(const char* const, const char* const)
{
	cout << "EndName" << endl;
	r_name.push_back('\0');
}
vector<char> r_string;
void BeginString(const char* const, const char* const)
{
	cout << "BeginString" << endl;
	r_string.clear();
}
void AckString(char c)
{
	cout << "AckString = " <<  c << endl;
	r_string.push_back(c);
}
void EndString(const char* const, const char* const)
{
	cout << "EndString" <<  endl;
	if(!r_string.empty())
	{
		r_string.pop_back();	// '\"' ‚ð?ƒbƒv
		r_string.push_back('\0');
	}
}
int r_int;
void Int(int i)
{
	cout << "Int" <<  i <<endl;
	r_int = i;
}
/////////////////////////////////////////////////////////////////////////////////
INIFile g_inifile;
string g_section;
string g_key;
void MOV_name_section(const char* const, const char* const)
{
	if(!r_name.empty())
		g_section = &r_name[0];
	else
		g_section = "";
}
void MOV_name_key(const char* const, const char* const)
{
	if(!r_name.empty())
		g_key = &r_name[0];
	else
		g_key = "";
}
void AddKeyInt(const char* const, const char* const)
{
	boost::any a = r_int;
	g_inifile.AddKey(g_section.c_str(), g_key.c_str(), a);
	printf("AddKey : %s %s %d\n", g_section.c_str(), g_key.c_str(), r_int);
}
void AddKeyString(const char* const, const char* const)
{
	boost::any a = static_cast<string>(&r_string[0]);
	g_inifile.AddKey(g_section.c_str(), g_key.c_str(), a);
	if(!r_string.empty())
		printf("AddKey : %s %s \"%s\"\n", g_section.c_str(), g_key.c_str(), &r_string[0]);
	else
		printf("AddKey : %s %s \"%s\"\n", g_section.c_str(), g_key.c_str(), "");
}
//-----------------------------------------------------------------------------
//	
//-----------------------------------------------------------------------------
struct ini_parser : public grammar<ini_parser> {
	template<typename S> struct definition {
		rule<S> name_r, string_r, int_r;
		rule<S> ini, section, key;
		definition(const ini_parser& self)
		{
			ini			= *space_p >> *section >> *space_p;

			section		= '[' >> name_r >> ']' 
						>> eps_p[&MOV_name_section] 
						>> +space_p 
						>> *(key >> +space_p);

			name_r		=	(alpha_p[&BeginName] | ch_p('_')[&BeginName]) 
						>> *( (alnum_p[&AckName] | ch_p('_')[&AckName]) ) 
						>> eps_p[&EndName];

			key			= name_r[&MOV_name_key] 
						>> *space_p >> '=' >> *space_p 
						>> (int_r[&AddKeyInt] | string_r[&AddKeyString]);

			string_r	= '\"' >> eps_p[&BeginString] 
						>> *(anychar_p[&AckString] - '\"') 
						>> '\"' 
						>> eps_p[&EndString];

			int_r		= int_p[&Int];

		}
		//
		const rule<S>& start() const { return ini; }
	};
};
}
#include <windows.h>
int main()
{
	boost::filesystem::path foo(boost::filesystem::initial_path() / "../jTest/test.ini" );
	string str1 = foo.normalize().native_directory_string();
	string str;
	FILE* fp = fopen(str1.c_str(), "r");
	if(!fp) return -1;
	char strbuf[512];
	while(NULL != fgets(strbuf, 512, fp))
	{
		str += strbuf;
	}
	fclose(fp);
	ini_parser ini;
	// 
	parse_info<> r = parse(str.c_str(), ini);
	if(r.full)	// 
		cout << "ok" << endl;
	else	// 
		cout << "error" << endl;
	char dest[512];
	// check
	cout << "get section1 key1 : " << g_inifile.GetInt("section1", "key1") << endl;
	g_inifile.GetString("section1", "key2", dest);
	cout << "get section1 key2 : " << dest << endl<<endl <<endl;

#define CALL_X(X) printf("\n\n %s call!!! \n",#X);int X(); X();
	//CALL_X(	main_spirit_XML);
	//CALL_X(	main_C_comment);
	//CALL_X(	main_spirit_var);
	//CALL_X(	main_C_comment);
	//CALL_X(	main_C_comment);
	//CALL_X(	main_C_comment);
	//CALL_X(	main_C_comment);
	//CALL_X(	main_C_comment);
	//CALL_X(	main_C_comment);

	return 0;
}
