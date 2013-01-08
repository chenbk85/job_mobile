/* file : MOB_NetIOModel_TcpServer.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-26 17:01:55
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "MOB_NetIOModel.h"


MOB_NetIOModel_TcpServer::MOB_NetIOModel_TcpServer( Plugin_INetIOModel* pIO,boost::asio::io_service& io_service, short port ) 
: m_io_service(io_service), m_acceptor(io_service, tcp::endpoint(tcp::v4(), port))
{
	m_pPlugin= pIO;
	m_pPlugin->m_pMOB_INetIOModel=this;
	start_accept();
}

MOB_NetIOModel_TcpServer::~MOB_NetIOModel_TcpServer()
{

}

void MOB_NetIOModel_TcpServer::start_accept()
{
	Plugin_IConnection* pPlugin = m_pPlugin->Connection_Create();
	jRETURN(pPlugin);//대개는 허용 접속갯수 초과시 NULL이 된다.

	pPlugin->m_pParent = m_pPlugin;
	MOB_Connection_sptr_t pCon(new MOB_Connection(m_io_service, this,pPlugin));
	m_acceptor.async_accept(pCon->m_socket,
		boost::bind(&MOB_NetIOModel_TcpServer::handle_accept, this, pCon,
		boost::asio::placeholders::error));

	jLOG(_T("Client Connect Wait............\n"));

}

void MOB_NetIOModel_TcpServer::handle_accept(MOB_Connection_sptr_t pCon, const boost::system::error_code& error)
{
	if (error)
	{
		jWARN(_T("%s"), error.message().c_str());
	}
	else
	{
		pCon->m_pPlugin->m_gid = INVALID_pp_game_id;
		pCon->m_pPlugin->MOB_OnConnect(m_pPlugin);
		//그리고 스타트 시킨다.
		pCon->read_socket();

		//유저를 리스트에 넣는다
		m_listMOB_Connection.push_back(pCon);
		jLOG(_T("User Add count = %d") , m_listMOB_Connection.size());
	}

	//클라이언트를 기다린다.
	start_accept();
}



void MOB_NetIOModel_TcpServer::for_each(boost::function<void (MOB_IConnection*)> &func)
{
	MOB_Connection_list_it it;
	jFOR(m_listMOB_Connection,it)
	{
		MOB_Connection_sptr_t pCon = (MOB_Connection_sptr_t) *it;
		func(pCon->BaseI());
	}
}

Plugin_IConnection* MOB_NetIOModel_TcpServer::find_if(boost::function<bool (MOB_IConnection*)> &func)
{
	MOB_Connection_list_it it;
	jFOR(m_listMOB_Connection,it)
	{
		MOB_Connection_sptr_t pCon = (MOB_Connection_sptr_t) *it;
		if(func(pCon->BaseI()))
		{
			return pCon->m_pPlugin;
		}
	}
	return 0;

}
void MOB_NetIOModel_TcpServer::erase_if(boost::function<bool (MOB_IConnection*)> &func)
{
	MOB_Connection_list_it it;
	jFOR(m_listMOB_Connection,it)
	{
		MOB_Connection_sptr_t pCon = (MOB_Connection_sptr_t) *it;
		if(func(pCon->BaseI()))
			m_listMOB_Connection.erase(it);
	}

}

typedef boost::asio::deadline_timer MOB_Timer;
static void timer_handle(MOB_Timer_handler_t func,const boost::system::error_code& error)
{
	if (error == boost::asio::error::operation_aborted) 
	{
		jLOG(_T("Timer was canceled"));
		return;
	}
	func();
}

MOB_ITimer*			MOB_NetIOModel_TcpServer::Timer_Create(int iTime,MOB_Timer_handler_t& func)
{
	jLOG("%s",jFUNC);
	MOB_Timer* pTimer = new MOB_Timer(m_io_service, boost::posix_time::seconds(iTime));
	pTimer->async_wait(boost::bind(timer_handle,func, boost::asio::placeholders::error));
	return (MOB_ITimer*)pTimer;
}

void				MOB_NetIOModel_TcpServer::Timer_Delete(MOB_ITimer*p)
{
	jLOG("%s",jFUNC);
	if(!p) return;
	MOB_Timer* pTimer= (MOB_Timer*)p;
	pTimer->cancel();
	SAFE_DELETE(pTimer);
}
