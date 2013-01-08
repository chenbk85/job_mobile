#include <stdafx.h>
#include <boost/ref.hpp>
using namespace std;

void assign( int& a, int b )                
{ 
	a = b; 
}
template<typename T> void AssigneTmplFunc( T x, int val ) 
{ 
	assign( x, val ); 
}

int main_ref()
{
	int iVal = 10;
	cout << iVal << endl;

	// 이 호출하는 방법에서는iVal의 값을 변경할 수 없다
	// (AssigneTmplFunc의T가 int형태가 되어 버린다)
	AssigneTmplFunc( iVal, 20 );				cout << iVal << endl;

	// 참조형에 캐스트 해 봐도 역시 안됨
	AssigneTmplFunc( (int&)(iVal), 30 );	cout << iVal << endl;
	AssigneTmplFunc<int&>( iVal, 40 );		cout << iVal << endl;
	// 이런  방법도
	AssigneTmplFunc( boost::ref(iVal), 50 ); cout << iVal << endl;

	return 0;
}

/*
main_ref call!!!
10 : cout << iVal << endl; 
10 : AssigneTmplFunc( iVal, 20 )
10 : AssigneTmplFunc( (int&)(iVal), 30 )
40 : AssigneTmplFunc<int&>( iVal, 40 )
50 : AssigneTmplFunc( boost::ref(iVal), 50 )

*/