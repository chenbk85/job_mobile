http://www.gpgstudy.com/forum/viewtopic.php?t=14748&highlight=%C0%AF%B4%CF%C4%DA%B5%E5

#include <iostream>
using namespace std;

void Foo()
{
	   cout<<__FUNCTION__<<endl;
}

void main()
{
	   Foo();
}


아실지도 모르겠지만 유니코드일때는 _T(__FUNCTION__) 
이렇게 해야됩니다 (예전에 이거때문에 고생을...)