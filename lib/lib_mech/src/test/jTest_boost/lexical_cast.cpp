#include <stdafx.h>

#include <string>
#include <boost/lexical_cast.hpp>
using namespace std;

int main_lexical_cast()
{
	using boost::lexical_cast;

	string str_thousand = "1000";
	int    int_ninety   = 90;

	int    a = lexical_cast<int>( str_thousand );
	string s = lexical_cast<string>( int_ninety );
		// a에는1000,s에는"90"이 들어갑니다.
	cout << "lexical_cast lexical_cast<int>( str_thousand )= "<< a <<endl;
	cout << "lexical_cast<string>( int_ninety ) = " << s <<endl;

	return 0;
}

