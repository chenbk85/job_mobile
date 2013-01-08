#include <stdafx.h>
 
bool is_even( int x )
{
	cout << "is_even = " << x <<endl;
	if(x%7 == 0)
		cout << "is_event ok: " << x<<endl;
    return x%2 == 0;
}
 
int main_functional()
{
		//std::의 <functional>해더에 있는 각종 유틸 함수객체에 동일.
		//참조의 참조형에 대한 번거로움을 해결.
       int arr[] = {1,2,3,4,5,6,7,8,9,10};
 
       // 보통 함수를std::not1에 건네 주려면 ptr_fun가 필요
       // × std::find_if( arr, arr+10, std::not1(is_even) );
       std::find_if( arr, arr+10, std::not1(std::ptr_fun(is_even)) );
 
       // boost::not1는 그대로 건네줄 수가 있다
       std::find_if( arr, arr+10, boost::not1(is_even) );
 
       return 0;
}
