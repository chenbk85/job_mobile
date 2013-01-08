#include <stdafx.h>
#include <iostream>
#include <string>
#include <map>
#include <boost/property_map.hpp>
using namespace std;

// Associative-Map
typedef map<string,string> StrStrMap;
typedef boost::associative_property_map<StrStrMap> Name2AdrMap;

// 값인도입니다만
void foo( Name2AdrMap address )
{
	address[ string("Taro") ] = "Osaka";

	string old_address = get( address, string("Hanako") );
	put( address, string("Hanako"), old_address+"@Japan" );
}

int main_property_map()
{
	StrStrMap n2a;
	n2a.insert( make_pair( string("Taro"), string("Tokyo") ) );
	n2a.insert( make_pair( string("Hanako"), string("Kyoto") ) );
	cout << "org \n";
	for( StrStrMap::iterator i = n2a.begin(); i!=n2a.end(); ++i )
		cout << i->first << ": " << i->second << endl;

	Name2AdrMap address_map( n2a );

	foo( address_map );

	// 호출측의 값도 써 바뀝니다
	for( StrStrMap::iterator i = n2a.begin(); i!=n2a.end(); ++i )
		cout << i->first << ": " << i->second << endl;

	return 0;
}
/*
출력예
Hanako: Kyoto@Japan
Taro: Osaka

*/