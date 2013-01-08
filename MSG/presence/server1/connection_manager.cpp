//
// connection_manager.cpp
// ~~~~~~~~~~~~~~~~~~~~~~
//
// Connection들의 life-cycle관리. 
// shared_ptr 형태로 관리되는 Connection을 connection_manager가 쥐고 있음.
// 정상 
//
// 최초 작성 : 2012.07.30. kts123@neowiz.com
// ~~~~~~~~~~
//
#include "stdafx.h"


#include <set>
#include <algorithm>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include "ug_request_handler.hpp"
#include "connection.hpp"
#include "connection_manager.hpp"


namespace presence {

// new_connection을 등록하고 start 시킨다.
void ConnectionManager::start(SpConnection& new_connection)
{
	// new_connection 의 subscriber 에 request_handler_를 연결시킨다.
	new_connection->request_handler_.connect(
		boost::bind(ug_request_handler::handle_message, 
					kInvalidGameId, _1, _2, _3));

	// set 에 등록한 후 .
	connections_.insert(new_connection);

	// 시작시킨다.
	new_connection->start();
}

// connection을 등록 해제하고
// connection을 stop 시킨다.
// 등록이 해제 되었기 때문에 이 함수가 리턴된 후에는 
// 참조 카운트 관리에 의해 실제 객체가 삭제될 수 있다.
void ConnectionManager::stop(SpConnection& connection)
{
	connections_.erase(connection);
	connection->stop();
}

// 메시지를 송신한다.
// 실제 작업은 Connection 객체에서 이뤄지지만
// 모듈간 dependency, visibie scope 등을 고려하여 manager를 통해서 전송하게 한다.
void ConnectionManager::send(SpConnection& connection, Connection::SpBuffer& buffer)
{
	connection->send(buffer);
}

// 등록된 모든 컨넥션의 등록을 해제하고 
// stop 시킨다.
void ConnectionManager::stop_all()
{
	std::for_each(connections_.begin(), connections_.end(),
				boost::bind(&Connection::stop, _1));
	connections_.clear();
}


// send buffer
// 성능 이슈가 생기면 Pool 기법을 사용한다.
Connection::SpBuffer ConnectionManager::get_buffer(size_t len)
{
	Connection::SpBuffer packet(new std::vector<char>(len));
	return packet;
}

//singleton
ConnectionManager&  get_connection_manager()
{
	static ConnectionManager the_manager_;
	return the_manager_;
}

} // namespace presence

