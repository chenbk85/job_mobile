//
// connection_manager.hpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Connection들의 life-cycle관리. 
// shared_ptr 형태로 관리되는 Connection을 connection_manager가 쥐고 있음.
// 정상 
//
// 최초 작성 : 2012.07.30. kts123@neowiz.com
// ~~~~~~~~~~
//

#ifndef PRESENCE_CONNECTION_MANAGER_HPP
#define PRESENCE_CONNECTION_MANAGER_HPP

#include <set>
#include <boost/noncopyable.hpp>
#include "connection.hpp"


namespace presence {

// 연결된 컨넥션을 관리한다.
// 주 목적은 서버가 셧다운 될 때 연결된 소켓 정리하기 위함이다.

class ConnectionManager
	: private boost::noncopyable
{
public:
	// new_connection을 등록하고 start 시킨다.
	void start(SpConnection& new_connection);

	// connection을 등록 해제하고
	// connection을 stop 시킨다.
	// 등록이 해제 되었기 때문에 이 함수가 리턴된 후에는 
	// 참조 카운트 관리에 의해 실제 객체가 삭제될 수 있다.
	void stop(SpConnection& connection);

	// 등록된 모든 컨넥션의 등록을 해제하고 
	// stop 시킨다.
	void stop_all();

	// 메시지를 송신한다.
	// 실제 작업은 Connection 객체에서 이뤄지지만
	// 모듈간 dependency, visibie scope 등을 고려하여 manager를 통해서 전송하게 한다.
	void send(SpConnection& connection, Connection::SpBuffer& buffer);


	// send buffer allocate
	Connection::SpBuffer get_buffer(size_t len);

	
private:
	// 생성 막기
	ConnectionManager() {}

	// singlton 객체 접근 함수
	friend ConnectionManager& get_connection_manager();

	// 관리되는 컨넥션
	std::set<SpConnection> connections_;
};

// singlton 객체 접근
extern ConnectionManager& get_connection_manager();
#define the_connection_manager get_connection_manager()

} // namespace presence

#endif // PRESENCE_CONNECTION_MANAGER_HPP
