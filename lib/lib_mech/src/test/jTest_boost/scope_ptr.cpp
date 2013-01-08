#include <stdafx.h>
#include <string>
#include <iostream>
#include <boost/scoped_ptr.hpp>
using namespace std;
/*
//http://serious-code.net/moin.cgi/BoostSmartPointer

boost::shared_ptr
���۷��� ī������ ����� ����Ʈ ������ Ŭ����. 

boost::weak_ptr
	shared_ptr�� ���� ���. ���� ī��� �������� �ʴ´�.



boost::scoped_ptr

�������� ����� �����ؾ��ϴ� ��ü�� ���� ���, 
�ַ� ����ϰ� �Ǵ� ����Ʈ ������ Ŭ����. 
������ ���� shared_ptr Ŭ������ ���������� �޸� ������ �����ϱ� ���� Ŭ�����ε�, 
�ٸ� ���۷��� ī���ÿ� ���� ���� ��ü�� �����ϴ� ���� �ƴ϶�, 
�������� ����� ���� ��ü�� �����ϴ� Ŭ�����̴�.
*/



/*
�������� delete �� �ְ� �˴ϴ�. 
std::auto_ptr�� �������� �������̶�� �ϴ� ������ ���ٴ� ��
�� ��scoped_ptr �� ������ �� scoped_ptr ��ü�� ���ؼ� delete��.
delete�ñ⸦ �����ҷ��� auto_ptr�̳� shared_ptr�� �̿��Ұ�.
*/

int main_scope_ptr()
{
	boost::scoped_ptr<string> s( new string("Test") );
	cout << *s << endl;
	return 0;
} // ���⼭delete�ȴ�.



#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using namespace std;
using namespace boost;

struct test {
	test(const char* name) : name_(name) {}
	~test() {cout << name_ << " destructed." << endl;}
	void showName() {cout << "Name: " << name_ << endl;}
	const char* name_;
};

int main_weak_ptr()
{

	struct aaa
	{
		aaa(){cout << "create aaa"<<endl;}
		~aaa(){cout << "delete aaa"<< endl;}
	};
	{
		auto_ptr<aaa> ptr(new aaa[2]);
	}
	{
		shared_ptr<aaa> ptr(new aaa[2]);
	}
	cout << "ok";

	/*
	struct A
	{
		shared_ptr<test> sp( new test("ABC") );

	};
	struct B
	{
		weak_ptr<test> wp( sp );

	};

	
	if( shared_ptr<test> tmp = wp.lock() )		
	{
		tmp->showName(); // �����Ͱ� ��ȿ�ϸ� ����
	}
	else						
		cout << "already deleted." << endl;
	
	sp.reset(); // ���⼭delete�ȴ�

	if( shared_ptr<test> tmp = wp.lock() )		
		tmp->showName(); // �����Ͱ� ��ȿ�ϸ� ó��
	else						
		cout << "already deleted." << endl;

*/	return 0;
}


#include <vector>
#include <iostream>
#include <boost/intrusive_ptr.hpp>
using namespace std;
int SharedObject_id=0;
class SharedObject
{
public:
	int SharedObject_id_m;
	SharedObject() : ref_count(1) 
	{
		SharedObject_id_m = SharedObject_id++;
		cout << "SharedObject create" << "[" 
			<< SharedObject_id_m << "]" << endl;
	}
	~SharedObject()
	{
		cout << "SharedObject delete" << "[" 
			<< SharedObject_id_m << "]" << endl;
	}

	int AddRef()  { return ++ref_count; }
	int Release() {
		if( 0 == --ref_count ) delete this;
		return ref_count;
	}
	void Hello()	{ cout << "hello." << endl;	}
//private:
	int ref_count;
};

void intrusive_ptr_add_ref( SharedObject* ptr )
{
	ptr->AddRef();
	cout << "intrusive_ptr_add_ref = " << "[" 
		<< ptr->SharedObject_id_m 
		<< "]"<< ptr->ref_count <<endl;
}

void intrusive_ptr_release( SharedObject* ptr )
{
	cout << "intrusive_ptr_release = " << "[" 
		<< ptr->SharedObject_id_m 
		<< "]"<< ptr->ref_count <<endl;
	ptr->Release();
}

int main_intrusive_ptr()
{
	typedef boost::intrusive_ptr<SharedObject> Ptr;

	Ptr p = Ptr(new SharedObject,false); //addref =false
	vector< Ptr > v;
	cout << endl << endl;
	v.push_back( Ptr(new SharedObject,false) );
	cout << endl << endl;
	v.push_back( Ptr(new SharedObject,false) );
	cout << endl << endl;
	v.push_back( Ptr(new SharedObject,false) );
	cout << endl << endl;
	v.push_back( p );
	cout << endl << endl;

	p->Hello();
	// p (��)�� ���� �� �� �ۿ� ī��������
	//���� ����κ��͵� ���� ����.
	return 0;
} // ���⼭ ���delete�ȴ�.
