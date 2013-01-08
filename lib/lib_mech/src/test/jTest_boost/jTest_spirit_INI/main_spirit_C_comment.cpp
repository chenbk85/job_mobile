#pragma warning(disable : 4786)
#pragma warning(disable : 4761)
#include <iostream>
#include <string>
#include <cstdio>
#include <boost/spirit/core.hpp>
using namespace std;
using namespace boost::spirit;
void Print(char c)
{
	printf("%c", c);
}

struct comment_parser : public grammar<comment_parser> {
	template<typename S> struct definition {
		rule<S> comment;
		definition(const comment_parser& self)
		{
			comment		=	"//" >> *(anychar_p - '\n') >> '\n' | 
							"/*" >> *(anychar_p - "*/") >> "*/"	;
		}
		const rule<S>& start() const { return comment; }
	};
};



struct output_parser : public grammar<output_parser> {
	template<typename S> struct definition {
		rule<S> body;
		definition(const output_parser& self)
		{
			body		=	*anychar_p[&Print];
		}
		const rule<S>& start() const { return body; }
	};
};
#include <windows.h>
#include <boost/filesystem/operations.hpp>

int main_C_comment()
{
	boost::filesystem::path foo(boost::filesystem::initial_path() / "../jTest/c_comment.txt" );
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
	comment_parser comment;
	output_parser output;
	parse_info<> r = parse(str.c_str(), output, comment);
	if(r.full)	
		cout << "ok" << endl;
	else	
		cout << "error" << endl;
	return 0;
}
