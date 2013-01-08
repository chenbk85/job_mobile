//
// Connection.hpp
// ~~~~~~~~~~~~~~
//
// 소켓을 랩핑. length:value 형식의 스트림을 데이터그램화 시킨다.
// Send/Recieve 기능.  boost::asio 예제 클래스를 가져와서 base로 했음.
// recieve 이벤트의 경우 boost::signal2로 publisher/subscriber 패턴 이용
//
// 최초 작성 : 2012.07.30. kts123@neowiz.com
// ~~~~~~~~~~
//

#ifndef PRESENCE_CONNECTION_HPP
#define PRESENCE_CONNECTION_HPP

#include <boost/asio.hpp>
#include <boost/array.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <vector>
#include <queue>

#include "boost/signals2/signal.hpp"

namespace presence {

/// Represents a single Connection from a client.

class ConnectionManager;

class Connection
	: public boost::enable_shared_from_this<Connection>,
	private boost::noncopyable
{
public:

	/// Construct a Connection with the given io_service.
	explicit Connection(boost::asio::io_service& io_service);

	/// Get the socket associated with the Connection.
	boost::asio::ip::tcp::socket& socket();

	/// start the first asynchronous operation for the Connection.
	void start();

	/// stop all asynchronous operations associated with the Connection.
	void stop();

	/// send 버퍼
	typedef boost::shared_ptr<std::vector<char> >  SpBuffer;

	/// 메시지 전송.
	//void send(char* data, size_t len);
	void send(SpBuffer& buffer);		

	//boost::signals2::signal<void (boost::shared_ptr<Connection>& con)> 
	//	accept_handler_;


	boost::signals2::signal<void (	
		boost::shared_ptr<Connection> con,
		const boost::system::error_code& e,
		const boost::asio::const_buffer& buffer)> 
		request_handler_;


private:

	void async_read_header_();
	void async_read_body_(size_t body_length);

	/// Handle completion of a read operation.
	void handle_read_header_(const boost::system::error_code& e,
		std::size_t bytes_transferred);

	void handle_read_body_(
		const boost::system::error_code& e,
		std::size_t bytes_transferred);

	
	void send_queued_packet_();

	/// Handle completion of a write operation.
	void handle_write_(const boost::system::error_code& e);

	// Handle error
	void handle_error_(const boost::system::error_code& e);

	/// Socket for the Connection.
	boost::asio::ip::tcp::socket socket_;

	/// Buffer for receive data.
	static const size_t default_receive_buffer_size = 8192;
	boost::array<char, default_receive_buffer_size> receive_buffer_;

	std::vector<SpBuffer> sending_queue_;
	std::vector<SpBuffer> to_be_send_queue_;

	static const size_t kMaxRecvPacketSize = 4*1024; // 4K

	///// The manager for this Connection.
	//ConnectionManager& connection_manager_;

};

typedef boost::shared_ptr<Connection> SpConnection;	

} // namespace presence

#endif // PRESENCE_CONNECTION_HPP
