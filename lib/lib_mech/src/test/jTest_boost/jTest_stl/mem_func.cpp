#include <stdafx.h>


/*

http://serious-code.net/moin.cgi/StlSnippets#head-a67ef7673173600ca6ee9046739845337d07733a

8 ��ü�� ����Ʈ�� Ⱦ���ϸ鼭 ��� �Լ� ȣ���ϱ�
���� ��� ������ ���� Ŭ�������� �ִٰ� ����. 
class myclass
{
public:
    void heartbeat() { ... }
    void set(int param) { ... }
};

list<myclass> obj_list;
list<myclass*> ptr_list;

������Ʈ ��ü�� �̷���� ����Ʈ�� ���鼭 myclass�� heartbeat �Լ��� ȣ���Ϸ��� ������ ���� �Ѵ�. 
for_each(obj_list.begin(), obj_list.end(), 
    mem_fun(&myclass::heartbeat));
�����ͷ� �̷���� ����Ʈ�� ���鼭 myclass�� heartbeat �Լ��� ȣ���Ϸ��� ������ ���� �Ѵ�. for_each(ptr_list.begin(), ptr_list.end(), 
    mem_fun<void, myclass>(&myclass::heartbeat));
�����ͷ� �̷���� ����Ʈ�� ���鼭 myclass�� set �Լ��� ȣ���Ϸ��� ������ ���� �Ѵ�. for_each(ptr_list.begin(), ptr_list.end(), 
    bind2nd(mem_fun1<void, myclass, int>(&myclass::heartbeat), 99));
���������δ� �� ���������� ��õ���� �ʴ´�. ���� for ���� ���鼭 �ϴ� �� �����ϱⰡ ���ϱ� �����̴�. 

�翬������, vector �� deque ��� ������ �� �ִ�. 

*/
