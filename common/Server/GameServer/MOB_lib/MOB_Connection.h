/* file : MOB_Connection.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-26 17:15:54
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __MOB_Connection_header__
#define __MOB_Connection_header__
#pragma once

#include "MOB_net.h"

#define DEF_USE_WRITE_QUEUE
//#define DEF_USE_ASIO_ASYNC_READ

namespace nMOB
{
	using boost::asio::ip::tcp;
	typedef std::deque<MOB_NetPacketBuffer> MOB_NetPacketBuffer_queue_t;
	struct MOB_NetIOModel_TcpServer;
	struct MOB_Connection
		: public MOB_IConnection
		,public boost::enable_shared_from_this<MOB_Connection>
		,private boost::noncopyable
	{

		MOB_Connection(boost::asio::io_service& io_service, MOB_NetIOModel_TcpServer* manager,Plugin_IConnection* pPlugin);
		~MOB_Connection();

	public: //MOB_IConnection 인터페이스 선언.
		virtual bool WritePacket(MOB_NetPacketBuffer* p);
		virtual void DoDisconnect(acstr szErrorReason,int iErrorReason);

	public:
		tcp::socket m_socket;

	//private:
		MOB_IConnection* BaseI(){ return this;}

		void read_socket();

		PPacketHeader m_PPacketHeader_Read;
		char m_pDataBuff_Read[nMOB::BUFFER_SIZE];
		int m_iReadSize;

#ifndef DEF_USE_ASIO_ASYNC_READ
		// async_read_some용. DEF_USE_ASIO_ASYNC_READ가 define안되었을때만 필요.
		char m_pDataBuff_Readed[nMOB::BUFFER_SIZE*8];
		int m_iReadedSize;
		void handle_read(const boost::system::error_code& error, size_t bytes_transferred);
		void _async_read_some();
#endif

#ifdef DEF_USE_WRITE_QUEUE
		MOB_NetPacketBuffer_queue_t m_write_msgs;
#endif

		void handle_read_header(const boost::system::error_code& error);
		void handle_read_body(const boost::system::error_code& error);     //패킷을 받는다.
		void handle_write(const boost::system::error_code& error);                              //패킷을 보내고 난 다음에 불리는 콜백.
		void _send();
		void _async_read();
		void call_MOB_OnDisconnect(acstr szErrorReason,int iErrorReason);
	};


}//namespace nMOB

#endif // __MOB_Connection_header__
