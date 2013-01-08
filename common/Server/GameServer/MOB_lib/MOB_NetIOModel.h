/* file : MOB_NetIOModel.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-26 17:01:51
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __MOB_NetIOModel_header__
#define __MOB_NetIOModel_header__
#pragma once

#include "MOB_net.h"
#include "MOB_Connection.h"

namespace nMOB
{
	typedef boost::shared_ptr<MOB_Connection> MOB_Connection_sptr_t;
	jLIST_TYPEDEF_list_typedef(MOB_Connection_sptr_t,MOB_Connection_list);

	//--------------------------------------------------------------------------
	struct MOB_NetIOModel_TcpServer : public MOB_INetIOModel
	//--------------------------------------------------------------------------
	{
	public:
		// MOB_INetIOModel구현부.
		virtual MOB_ITimer*			Timer_Create(int iTime,MOB_Timer_handler_t& func);
		virtual void				Timer_Delete(MOB_ITimer*);
		virtual void				for_each(boost::function<void (MOB_IConnection*)> &func);
		virtual Plugin_IConnection* find_if(boost::function<bool (MOB_IConnection*)> &func);
		virtual void				erase_if(boost::function<bool (MOB_IConnection*)> &func);

	public:
		MOB_NetIOModel_TcpServer(Plugin_INetIOModel* pIO,boost::asio::io_service& io_service, short port);
		~MOB_NetIOModel_TcpServer();

		void start_accept();
		void handle_accept(MOB_Connection_sptr_t user, const boost::system::error_code& error);

	private:
		boost::asio::io_service& m_io_service;
		tcp::acceptor m_acceptor;
		MOB_Connection_list_t m_listMOB_Connection;
	};




}//namespace nMOB



#endif // __MOB_NetIOModel_header__
