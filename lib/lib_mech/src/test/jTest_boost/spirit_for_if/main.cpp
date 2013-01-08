#pragma warning(disable : 4786)
#pragma warning(disable : 4761)
#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <map>
#include <cstdio>
#include <boost/spirit/core.hpp>

#include "comment_parser.h"
#include "Executable.h"

using namespace std;
using namespace boost::spirit;


//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////


#include <windows.h>

int main()
{
    string source;

	FILE* fp = fopen("script.txt", "r");
	if(!fp) return -1;

	char strbuf[512];

	while(NULL != fgets(strbuf, 512, fp))
	{
		source += strbuf;
	}

	fclose(fp);

	Executable exe(source);
	exe.PrintState();
	exe.Exec();

	getchar();

	return 0;
}
