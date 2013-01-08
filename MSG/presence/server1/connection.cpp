//
// Connection.cpp
// ~~~~~~~~~~~~~~
//
#include "stdafx.h"

#include <vector>
#include <boost/bind.hpp>
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "../proto/presence.pb.h"
#include "connection.hpp"
#include "connection_manager.hpp"


#define no_error(e) (!(e))
#define is_error(e) (e)

namespace presence {

using namespace boost;
using namespace boost::asio::ip;

Connection::Connection(	asio::io_service& io_service)
	:	socket_(io_service)//,	connection_manager_(manager)
{
}

tcp::socket& Connection::socket()
{
	return socket_;
}

void Connection::start()
{
	async_read_header_();
}

//void Connection::close()
//{
//	connection_manager_.stop(shared_from_this());
//}

void Connection::stop()
{
	system::error_code ignored_ec;
	socket_.shutdown(tcp::socket::shutdown_both, ignored_ec);
	socket_.close();
}

//-----------------------------------------------------------
//  Receive 구현
//-----------------------------------------------------------

// call chain
//   start() 
//     => async_read_header_() => handle_read_header_() 
//     => async_read_body_() => handle_read_body_() (call message handler)
//     => async_read_header_() => ...

void Connection::async_read_header_()
{
	asio::async_read(
		socket_, 
		asio::buffer(receive_buffer_, 4),
		bind(	&Connection::handle_read_header_, 
				shared_from_this(),
				asio::placeholders::error,
				asio::placeholders::bytes_transferred));
}

void Connection::handle_read_header_(
					const system::error_code& e,
					std::size_t /*bytes_transferred*/)
{
	if (is_error(e))
	{
		handle_error_(e);
		return;
	}

	int *p_length = (int*)&receive_buffer_[0];
	std::size_t body_length = std::size_t(*p_length);

	if (kMaxRecvPacketSize < body_length)
	{
		// 워닝 로그를 찍으시오
		handle_error_(e); // e ?
		return;
	}

	async_read_body_(body_length);

	return;
}

void Connection::async_read_body_(size_t body_length)
{
	asio::async_read(
				socket_, 
				asio::buffer(receive_buffer_, body_length),
				bind(	&Connection::handle_read_body_, 
						shared_from_this(),
						asio::placeholders::error,
						asio::placeholders::bytes_transferred));
}


void Connection::handle_read_body_(
					const system::error_code& e,
					std::size_t bytes_transferred)
{
	if (is_error(e))
	{
		handle_error_(e);
		return;
	}

	request_handler_(
			shared_from_this(), 
			e, 
			asio::const_buffer(&receive_buffer_[0], bytes_transferred));

	async_read_header_();
}

//-----------------------------------------------------------
//  Send 구현
//-----------------------------------------------------------

void Connection::send(SpBuffer& buffer)
{
	// 1. header packet 만들기
	static const int header_len = 4;
	SpBuffer header = the_connection_manager.get_buffer(header_len);
	int size_4byte = static_cast<int> (buffer->size());
	memcpy(header->data(), &size_4byte, header_len);

	// 2. packet 들을 대기 큐에 넣기. 
	to_be_send_queue_.push_back(header);
	to_be_send_queue_.push_back(buffer);

	// 3. 이미 전송과정이 진행 중인 경우 바로 리턴
	//    이 경우에는 나중에 handle_write 에서 전송해 줄 것이다.
	if (sending_queue_.empty() == false)
		return;

	// 4. 대기 큐의 패킷들을 전송함.
	send_queued_packet_();	

	return;
}

void Connection::send_queued_packet_()
{
	// 0. 이미 진행 중인 send 작업이 없음이 보장되어야 함.
	assert(sending_queue_.empty());

	// 1. to_be_send_queue_ 의 패킷들을 모두 sending_queue 로 이동시킴
	sending_queue_.swap(to_be_send_queue_);

	// 2. sending_queue 의 패킷들을 참조하는 buffer sequence 객체를 만듦.
	std::vector<asio::const_buffer> buffer_sequence(sending_queue_.size());
	for (size_t i = 0; i < sending_queue_.size(); ++i)
		buffer_sequence.push_back(asio::buffer(*sending_queue_[i]));

	// 3. buffer sequence 에 대한 전송 요청
	asio::async_write(socket_, buffer_sequence, 
		bind(	&Connection::handle_write_,
				shared_from_this(),
				asio::placeholders::error));
}

void Connection::handle_write_(const system::error_code& e)
{
	if (is_error(e))
	{
		handle_error_(e);
		return;
	}

	//1. 이미 전송 완료된 패킷들 비우기
	//   이 시점에서 send buffer의 ref_count 값이 0 이 되어 release 됨.
	sending_queue_.clear();

	//2. 대기 큐가 비어 있으면  바로 리턴
	if (to_be_send_queue_.empty() == true)
		return;

	//3. 대기 큐의 패킷들을 전송함.
	send_queued_packet_();

	return;
}

//-----------------------------------------------------------
//  에러 핸들링 구현
//-----------------------------------------------------------
void Connection::handle_error_(const system::error_code& e)
{
	request_handler_(shared_from_this(), e, asio::const_buffer());
}

} // namespace presence
