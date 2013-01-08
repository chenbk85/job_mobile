#include "stdafx.h"
//
// blocking_tcp_echo_client.cpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Packet.h"
#include <boost/thread.hpp>
#include "conio.h"

#include "./../com/com_maestia_yd_monitor_client/com_maestia_yd_monitor_client.h"
//#include "../com/com_maestia_yd_monitor_client/com_maestia_yd_monitor_client_interface.h"
//#include "z:/src/com/com_maestia_yd_monitor_client/com_maestia_yd_monitor_client.h"

using namespace nMech;

void logger_func(const char* szMsg,bool)
{
	printf(szMsg);
	printf("\n");
}
 //--------------------------------------------------------------------------
// cyd 121.253.15.51 20100
//--------------------------------------------------------------------------
namespace nMech
{
	namespace nYD
	{
		HMODULE g_hDLL_com_maestia_yd_monitor_client_interface=0;
		tcstr szDLL_com_maestia_yd_monitor_client=_T("com_maestia_yd_monitor_client.dll");
	}
}


int com_maestia_yd_monitor(int argc, char* argv[])
{
	nYD::com_maestia_yd_monitor_client_interface* pCYD = nYD::Create_com_maestia_yd_monitor_client();

	pCYD->set_notify_time(1000);
	pCYD->set_logger(logger_func);
	pCYD->start(argv[1], argv[2]);
	_getch();
	nYD::Delete_com_maestia_yd_monitor_client();
	_getch();
	return 0;
}

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

// ydc 121.253.15.51 20100


struct ydc_thread
{
	string ip;
	string port;

	ydc_thread(string _ip,string _port) : ip(_ip),port(_port){ }
	void operator()()
	{
		try
		{
			boost::asio::io_service io_service;

			tcp::resolver resolver(io_service);
			tcp::resolver::query query(tcp::v4(), ip, port);
			tcp::resolver::iterator iterator = resolver.resolve(query);

			tcp::socket s(io_service);
			s.connect(*iterator);
			printf(__FUNCTION__ " connect ok : %s:%s",ip.c_str(),port.c_str());

			using namespace std; // For strlen.
			const int iMAX_LENGTH2=1024;
			while(1)
			{
				PACKET_MONITORCHO pk;
				ja_strcpy(pk.szEchoMsg,"maestia_yd_monitor_client echo msg");
				printf(__FUNCTION__ "\nsend size = %d, code=%u\n" , sizeof(pk) ,pk.ulEchoCode);
				boost::asio::write(s, boost::asio::buffer(&pk, sizeof(pk) ) );
				const int YD_MONITOR_CLIENT_BUFFER_SIZE=1024;
				boost::system::error_code error ;

				boost::array<char, YD_MONITOR_CLIENT_BUFFER_SIZE> response;
				std::size_t reply_length =0;
				if(reply_length = s.read_some(
					boost::asio::buffer(response), error))
				{
					if(reply_length!= sizeof(PACKET_MONITORCHO))
					{
						printf(__FUNCTION__ " reply_length(%d) != sizeof(PACKET_MONITORCHO):%d)\n", reply_length , sizeof(PACKET_MONITORCHO ) );
					}
					else
					{
						PACKET_MONITORCHO pk2;
						memcpy(&pk2, &response[0], sizeof(pk2));
						pk2.szEchoMsg[FILLER-1]=0;
						printf(__FUNCTION__ " recv : code=%u , msg=%s , reply_length=%d\n", pk2.ulEchoCode, pk2.szEchoMsg, reply_length);
					}

				}

				// if (error != boost::asio::error::eof)	throw boost::system::system_error(error);

				Sleep(1000);//1√ 
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Exception: " << e.what() << "\n";
		}
	}
};

int maestia_yd_monitor_client(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: maestia_yd_monitor_client <host> <port>\n";
		return 1;
	}

	ydc_thread ydc(argv[1],argv[2]);
	boost::thread t(ydc);
	printf(" ydc_thread started \n");
	_getch();
	t.detach();
	t.join();
	printf(" ydc_thread ended\n");
	_getch();
	return 0;
}
