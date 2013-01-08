/* file : MOB_Connection.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-26 17:15:58
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "MOB_Connection.h"
#include "MOB_NetIOModel.h"




MOB_Connection::MOB_Connection(boost::asio::io_service& io_service, MOB_NetIOModel_TcpServer* manager,Plugin_IConnection* pPlugin) 
:m_socket(io_service)
{
	m_pPlugin = pPlugin;
	m_pParent = manager;
	m_pPlugin->m_pMOB_IConnection = this;

	m_iReadSize=0;
#ifndef DEF_USE_ASIO_ASYNC_READ
	m_iReadedSize=0;
#endif
}

MOB_Connection::~MOB_Connection()
{	
	jRETURN(m_pParent);
	jRETURN(m_pParent->m_pPlugin);
	m_pParent->m_pPlugin->Connection_Delete(m_pPlugin);
	m_pPlugin->m_pParent=0;
	m_pParent=0;
}

#ifndef DEF_USE_ASIO_ASYNC_READ
void MOB_Connection::_async_read_some()
{
	m_socket.async_read_some(boost::asio::buffer(m_pDataBuff_Read, BUFFER_SIZE),
		boost::bind(&MOB_Connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}
#endif

void MOB_Connection::_async_read()
{
	boost::asio::async_read(m_socket,boost::asio::buffer(&m_PPacketHeader_Read
		, sizeof(m_PPacketHeader_Read))
		, boost::bind(&MOB_Connection::handle_read_header, shared_from_this()
		, boost::asio::placeholders::error) );
}



void MOB_Connection::read_socket()
{
#ifdef DEF_USE_ASIO_ASYNC_READ
	_async_read();
#else
	_async_read_some();
#endif
}



#ifndef DEF_USE_ASIO_ASYNC_READ
void MOB_Connection::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		jWARN("WARN: %s\n",error.message().c_str());
		jWARN("> category=%s , value=%d\n", error.category().name() ,error.value());
		
		call_MOB_OnDisconnect("socket out error",0);
		return;
	}
	const int iSIZE_m_pDataBuff_Readed = nMOB::BUFFER_SIZE*8;
	const int iHEADER_SIZE= sizeof(int);

	if((bytes_transferred + m_iReadedSize) >= iSIZE_m_pDataBuff_Readed )
	{
		DoDisconnect(("socket out  if((bytes_transferred+ m_iReadedSize)>= iSIZE_m_pDataBuff_Readed)"),0);
		return;
	}

	memcpy(m_pDataBuff_Readed+m_iReadedSize,m_pDataBuff_Read,bytes_transferred);
	m_iReadedSize+=bytes_transferred;

	if(m_iReadedSize<= iHEADER_SIZE)
	{
		_async_read_some();
		return;
	}

	char* pBody = m_pDataBuff_Readed;
	int iLengthBody=0;
	memcpy(&iLengthBody , pBody, iHEADER_SIZE);
	pBody+=iHEADER_SIZE;

	if(iLengthBody<=0 || (iLengthBody>=(BUFFER_SIZE-iHEADER_SIZE) ) )
	{
		DoDisconnect(("socket out  error if(iLengthBody<=0 || (iLengthBody>=(BUFFER_SIZE-iHEADER_SIZE) ) )"),0);
		return;
	}

	if(iLengthBody > (m_iReadedSize-iHEADER_SIZE) )
	{
		// 바디가 iLengthBody만큼 못읽었으모.
		_async_read_some();
		return;
	}

	size_t iStayReadedSize = m_iReadedSize;
	try
	{
		for(;;)
		{
			if(!m_pPlugin->MOB_OnReadPacket(pBody, iLengthBody))
			{
				DoDisconnect(__FUNCTION__,0);
				return;
			}
			iStayReadedSize -= (iLengthBody+iHEADER_SIZE);
			if(iStayReadedSize<=0)
			{
				m_iReadedSize=0;
				break;
			}

			jWARN(_T("data뭉쳐서왔다."));
			if(iStayReadedSize<= iHEADER_SIZE)
			{
				memmove(m_pDataBuff_Readed, pBody, iStayReadedSize);
				m_iReadedSize=iStayReadedSize;
				break;
			}
			//파싱할 패킷이 남았다.
			pBody = pBody+iLengthBody;
			memcpy(&iLengthBody,pBody,iHEADER_SIZE);
			if(iLengthBody > (int)(iStayReadedSize-iHEADER_SIZE ) ) //아직 바디 데이타가 완성안되었으모.
			{
				memmove(m_pDataBuff_Readed, pBody, iLengthBody);
				m_iReadedSize=iLengthBody;
				break;
			}
			pBody+=iHEADER_SIZE;

		}//for(;;)
		_async_read_some();

	}
	catch (...) 
	{
		DoDisconnect("MOB_Connection::handle_read try",0);
	}
}
#endif

void MOB_Connection::handle_read_header(const boost::system::error_code& error)
{
	if(error)
	{
		call_MOB_OnDisconnect( "MOB_Connection::handle_read_header socket out ",0);
		return;
	}
	if (m_PPacketHeader_Read.data_length < 0 && m_PPacketHeader_Read.data_length >= nMOB::BUFFER_SIZE)
	{
		return;
	}
	boost::asio::async_read(m_socket,
		boost::asio::buffer(m_pDataBuff_Read, m_PPacketHeader_Read.data_length ),
		boost::bind(&MOB_Connection::handle_read_body, shared_from_this(),
		boost::asio::placeholders::error));
}

void MOB_Connection::handle_read_body(const boost::system::error_code& error)
{
	if (error)
	{
		printf("WARN: %s",error.message().c_str());
		call_MOB_OnDisconnect(__FUNCTION__,0);
		return;
	}

	if(!m_pPlugin->MOB_OnReadPacket(m_pDataBuff_Read, m_PPacketHeader_Read.data_length))
	{
		DoDisconnect("MOB_Connection::handle_read_body MOB_OnReadPacket",0);
		return;
	}

	this->read_socket();
}



void MOB_Connection::_send()
{
#ifdef DEF_USE_WRITE_QUEUE
	boost::asio::async_write(m_socket,
		boost::asio::buffer(m_write_msgs.front().pBody,m_write_msgs.front().header.data_length),
		boost::bind(&MOB_Connection::handle_write, shared_from_this(),
		boost::asio::placeholders::error));

#else
	boost::asio::async_write(m_socket,
		boost::asio::buffer(m_writeBuff.pBody,m_writeBuff.header.data_length),
		boost::bind(&MOB_Connection::handle_write, shared_from_this(),
		boost::asio::placeholders::error));
#endif
}


//패킷 보낸후 콜백
void MOB_Connection::handle_write(const boost::system::error_code& error)
{
	if (error)
	{
		call_MOB_OnDisconnect(__FUNCTION__,0);
		return;
	}

#ifdef DEF_USE_WRITE_QUEUE
	m_write_msgs.pop_front();
	if(!m_write_msgs.empty())
		this->_send();
#endif
}

bool MOB_Connection::WritePacket(MOB_NetPacketBuffer* p)
{
	assert(p == &m_writeBuff);
#ifdef DEF_USE_WRITE_QUEUE
	//패킷을 보낸다.
	bool write_msgs_empty = m_write_msgs.empty();
	m_write_msgs.push_back(*p);	
	if (write_msgs_empty)
#endif
	{
		this->_send();
	}
	return true;
}

void MOB_Connection::DoDisconnect(acstr szErrorReason,int iErrorReason)
{
	m_socket.close();
	m_pPlugin->m_gid = INVALID_pp_game_id;
	m_pPlugin->MOB_OnDisconnect(szErrorReason,iErrorReason);//테스트 후 필요없으면 삭제할것임.
}

void MOB_Connection::call_MOB_OnDisconnect(acstr szErrorReason,int iErrorReason)
{
	m_pPlugin->m_gid = INVALID_pp_game_id;
	m_pPlugin->MOB_OnDisconnect(szErrorReason,iErrorReason);//테스트 후 필요없으면 삭제할것임.
}
