/* file : MOB_net.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-26 16:34:09
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "MOB_net.h"
#include "MOB_NetIOModel.h"

namespace nMOB
{
	void run_tcp_server(Plugin_INetIOModel* pIO,int port)
	{
		boost::asio::io_service io_service;
		using namespace std; // For atoi.
		MOB_NetIOModel_TcpServer server(pIO,io_service, port );
		std::cerr << "run_tcp_server Start................ \n";
		io_service.run();
	}

}//namespace nMOB
