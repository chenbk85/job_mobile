#include <stdafx.h>
#include <string>
#include <iostream>
#include <boost/scoped_ptr.hpp>
using namespace std;
/*
//http://serious-code.net/moin.cgi/BoostSmartPointer

boost::shared_ptr
레퍼런스 카운팅이 적용된 스마트 포인터 클래스. 

boost::weak_ptr
	shared_ptr과 같이 사용. 레퍼 카운스를 조작하지 않는다.



boost::scoped_ptr

스코프를 벗어나면 삭제해야하는 객체가 있을 경우, 
주로 사용하게 되는 스마트 포인터 클래스. 
위에서 나온 shared_ptr 클래스와 마찬가지로 메모리 누수를 방지하기 위한 클래스인데, 
다만 레퍼런스 카운팅에 의해 실제 객체를 삭제하는 것이 아니라, 
스코프를 벗어나면 실제 객체를 삭제하는 클래스이다.
*/



/*
마지막에 delete 해 주게 됩니다. 
std::auto_ptr과 차이점은 소유권이라고 하는 개념이 없다는 것
한 번scoped_ptr 에 넣으면 그 scoped_ptr 객체에 의해서 delete됨.
delete시기를 제어할려면 auto_ptr이나 shared_ptr를 이용할것.
*/

int main_scope_ptr()
{
	boost::scoped_ptr<string> s( new string("Test") );
	cout << *s << endl;
	return 0;
} // 여기서delete된다.



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
		tmp->showName(); // 포인터가 유효하면 실행
	}
	else						
		cout << "already deleted." << endl;
	
	sp.reset(); // 여기서delete된다

	if( shared_ptr<test> tmp = wp.lock() )		
		tmp->showName(); // 포인터가 유효하면 처리
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
	// p (은)는 조금 전 그 밖에 카피했지만
	//아직 여기로부터도 참조 가능.
	return 0;
} // 여기서 모두delete된다.
