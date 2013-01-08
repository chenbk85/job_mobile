#include <stdafx.h>
#include <iostream>
#include <boost/multi_array.hpp>
using namespace std;

int main_multi_array()
{
	// int의 3 차원 배열
	typedef boost::multi_array<int, 3> MyArray;

	// 사이즈는 2×3×4로
	MyArray A( boost::extents[2][3][4] );

	// 이런 느낌에 사용할 수 있습니다.
	for( int i=0; i!=2; ++i )
		for( int j=0; j!=3; ++j )
			for( int k=0; k!=3; ++k )
			{
				A[i][j][k] = i + j + k;
			}



	// 약간 복잡한 예.
	// 3 차원 배열의 일부분 A[0-1][1][1-2] (을)를 view[0-1][0-1] (와)과
	// 2 차원에서 볼 수 있도록(듯이)view(을)를 만듭니다.
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

 
