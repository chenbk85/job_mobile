
#include <stdafx.h>
#include <boost/optional.hpp>
using namespace std;
using namespace boost;

// √x 를 넘지 않는 최대의 정수를 돌려주는 함수
// 음수일때는 optional<>는 false값을 가진다.
optional<int> sqrt( int x )
{
	if( x < 0 )
		return optional<int>();//비초기화된 int를 리턴
	int i;
	for(i=0; i*i<=x; ++i) {}
	return optional<int>(i-1);//초기화된 int형을 리턴
}

int main_optional()
{
	for(int j=-5; j<=5; ++j)
	{
		optional<int> x = sqrt(j);
		if( x ) // int형값을 보관 유지하고 있는지 체크
			cout << j << " => " << *x << endl; 
			//올바르면 dereference처리로 값을 가져옴
		else
			cout << j << " => " << "invalid" << endl;
	}
	return 0;
}

/*
출력예
invalid
invalid
invalid
invalid
invalid
0
1
1
1
2
2

*/
