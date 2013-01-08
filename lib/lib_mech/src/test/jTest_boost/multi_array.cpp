#include <stdafx.h>
#include <iostream>
#include <boost/multi_array.hpp>
using namespace std;

int main_multi_array()
{
	// int�� 3 ���� �迭
	typedef boost::multi_array<int, 3> MyArray;

	// ������� 2��3��4��
	MyArray A( boost::extents[2][3][4] );

	// �̷� ������ ����� �� �ֽ��ϴ�.
	for( int i=0; i!=2; ++i )
		for( int j=0; j!=3; ++j )
			for( int k=0; k!=3; ++k )
			{
				A[i][j][k] = i + j + k;
			}



	// �ణ ������ ��.
	// 3 ���� �迭�� �Ϻκ� A[0-1][1][1-2] (��)�� view[0-1][0-1] (��)��
	// 2 �������� �� �� �ֵ���(����)view(��)�� ����ϴ�.
	typedef MyArray::index_range range;
	MyArray::index_gen           indices;
	MyArray::array_view<2>::type view =
		A[ indices[range(0,2)][1][range(1,3)] ];

	for( MyArray::index i=0; i!=2; ++i )
		for( MyArray::index j=0; j!=2; ++j )
			if( view[i][j] != A[i][1][j+1] )
				cout << "error" << endl;

	return 0;
}


#include <iostream>
#include <boost/multi_array.hpp>
using namespace std;
using namespace boost;
 
int main_multi_array2()
{
    multi_array<int,3> a( extents[2][3][4] );
    for( int i=0; i!=2; ++i )
        for( int j=0; j!=3; ++j )
            for( int k=0; k!=4; ++k )
                a[i][j][k] = i + j + k;
 
    for( int i=0; i!=2; ++i ) {
        for( int j=0; j!=3; ++j ) {
            for( int k=0; k!=4; ++k ) {
                cout << a[i][j][k] << ' ';
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}

 
