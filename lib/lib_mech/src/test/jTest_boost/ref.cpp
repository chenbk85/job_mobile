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

	// �� ȣ���ϴ� ���������iVal�� ���� ������ �� ����
	// (AssigneTmplFunc��T�� int���°� �Ǿ� ������)
	AssigneTmplFunc( iVal, 20 );				cout << iVal << endl;

	// �������� ĳ��Ʈ �� ���� ���� �ȵ�
	AssigneTmplFunc( (int&)(iVal), 30 );	cout << iVal << endl;
	AssigneTmplFunc<int&>( iVal, 40 );		cout << iVal << endl;
	// �̷�  �����
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