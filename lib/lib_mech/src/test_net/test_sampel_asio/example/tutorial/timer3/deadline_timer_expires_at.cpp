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
