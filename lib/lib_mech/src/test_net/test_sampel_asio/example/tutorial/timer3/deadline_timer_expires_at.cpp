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



#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <iostream>

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
using namespace std;
using namespace boost;



using namespace boost;
using namespace boost::filesystem;
namespace fs = boost::filesystem;




#include <boost/asio.hpp>
#include <boost/test/unit_test.hpp>
using namespace boost::asio;
//using boost::asio::ip;
using boost::asio::ip::tcp;

class jAsyncResolveHandler   
{   
public :   
	std::string &m_addr;
	jAsyncResolveHandler( std::string &addr) : m_addr(addr){}

	void operator() (const boost::system::error_code& e, tcp::resolver::iterator itr )   
	{   
		if ( e )   
		{   
			std::cout << "\n jAsyncResolveHandler e.value(), errorcode_ : "  << e.value() <<endl;
			return;
		}   
		tcp::endpoint endpoint_ = *itr;   
		m_addr = endpoint_.address().to_string();
		std::cout << "ip = " << m_addr <<endl;
	}   
};   


std::string get_ip(const char* szHostName)
{
	boost::asio::io_service io_service;   
	tcp::resolver resolver(io_service);   
	boost::system::error_code error;   
	string ip;
	tcp::resolver::query query(szHostName,"");   
	resolver.async_resolve(query,jAsyncResolveHandler(ip));   
	io_service.run_one(error);
	io_service.reset();   
	return ip;
}


int main()
{
	string ip = get_ip("localhost");
	printf("\nnLinux::get_my_ip localhost = %s\n" , ip.c_str());
	
	ip = get_ip("mob-icandoit");
	printf("\nnLinux::get_my_ip  mob-icandoit = %s\n" , ip.c_str());

	return 0;
}
