#include <stdafx.h>


/*

http://serious-code.net/moin.cgi/StlSnippets#head-a67ef7673173600ca6ee9046739845337d07733a

8 객체의 리스트를 횡단하면서 멤버 함수 호출하기
예를 들어 다음과 같은 클래스들이 있다고 하자. 
class myclass
{
public:
    void heartbeat() { ... }
    void set(int param) { ... }
};

list<myclass> obj_list;
list<myclass*> ptr_list;

오브젝트 자체로 이루어진 리스트들 돌면서 myclass의 heartbeat 함수를 호출하려면 다음과 같이 한다. 
for_each(obj_list.begin(), obj_list.end(), 
    mem_fun(&myclass::heartbeat));
포인터로 이루어진 리스트를 돌면서 myclass의 heartbeat 함수를 호출하려면 다음과 같이 한다. for_each(ptr_list.begin(), ptr_list.end(), 
    mem_fun<void, myclass>(&myclass::heartbeat));
포인터로 이루어진 리스트를 돌면서 myclass의 set 함수를 호출하려면 다음과 같이 한다. for_each(ptr_list.begin(), ptr_list.end(), 
    bind2nd(mem_fun1<void, myclass, int>(&myclass::heartbeat), 99));
개인적으로는 이 정도까지는 추천하지 않는다. 차라리 for 루프 돌면서 하는 게 관리하기가 편하기 때문이다. 

당연하지만, vector 및 deque 등에도 적용할 수 있다. 

*/
