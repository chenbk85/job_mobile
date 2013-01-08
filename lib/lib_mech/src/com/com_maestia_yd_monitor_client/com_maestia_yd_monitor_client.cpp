// com_maestia_yd_monitor_client.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <boost/asio.hpp>
using boost::asio::ip::tcp;

#include "com_maestia_yd_monitor_client.h"
#include "Packet.h"
#include <boost/thread.hpp>


#define yd_log(...) aname1024_t szMsg1234;ja_sprintf(szMsg1234,__VA_ARGS__);Log(szMsg1234,false);
#define yd_error(...) aname1024_t szMsg1234;ja_sprintf(szMsg1234,__VA_ARGS__);Log(szMsg1234,true);

namespace nMech
{
	namespace nYD
	{
		boost::thread *g_thread=0;

		com_maestia_yd_monitor_client_interface* g_com_maestia_yd_monitor_client_interface;

		struct com_maestia_yd_monitor_client : public com_maestia_yd_monitor_client_interface
		{
			jINTERFACE_HEADER(com_maestia_yd_monitor_client_interface);

			DWORD m_notify_time;
			logger_func_t* m_pLogger;
			bool m_isExit;

			void Log(acstr szMsg,bool isCreatical)
			{
				if(m_pLogger) m_pLogger(szMsg,isCreatical);
				else printf(szMsg);
			}

			com_maestia_yd_monitor_client() : m_notify_time(1000*60*5),m_pLogger(0),m_isExit(false)
			{
				g_com_maestia_yd_monitor_client_interface= this;
			}

			int blocking_tcp_client(acstr szIP,acstr port)
			{
				try
				{
					boost::asio::io_service io_service;

					tcp::resolver resolver(io_service);
					tcp::resolver::query query(tcp::v4(), szIP, port);
					tcp::resolver::iterator iterator = resolver.resolve(query);

					tcp::socket s(io_service);
					s.connect(*iterator);

					using namespace std; // For strlen.
					const int iMAX_LENGTH2=1024;
					while(!m_isExit)
					{
						PACKET_MONITORCHO pk;
						ja_strcpy(pk.szEchoMsg,"maestia_yd_monitor_client echo msg");
						//yd_log(__FUNCTION__ " send size = %d, code=%u" , sizeof(pk) ,pk.ulEchoCode);
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
								yd_log( " [YD_ZeroMonitor]reply_length(%d) != sizeof(PACKET_MONITORCHO):%d)\n", reply_length , sizeof(PACKET_MONITORCHO ) );
							}
							else
							{
								PACKET_MONITORCHO pk2;
								memcpy(&pk2, &response[0], sizeof(pk2));
								pk2.szEchoMsg[FILLER-1]=0;
								yd_log( " [YD_ZeroMonitor]recv : code=%u , msg=%s , reply_length=%d\n", pk2.ulEchoCode, pk2.szEchoMsg, reply_length);
							}

						}
						Sleep(m_notify_time);//30초
					}
				}
				catch (std::exception& e)
				{
					yd_error("[ERROR][YD_ZeroMonitor] : "  "thread loop Exception: %s\n" ,e.what());
					std::cerr << "Exception: " << e.what() << "\n";
				}

				return 0;
			}
			void end()
			{
				if(!g_thread) return;
				m_isExit=true;
				//Sleep(m_notify_time);//30초
				g_thread->detach();
				g_thread->join();
				SAFE_DELETE(g_thread);
				yd_log(__FUNCTION__ "[YD_ZeroMonitor]ydc_thread ended\n");
			}


		};// struct com_maestia_yd_monitor_client 


		com_maestia_yd_monitor_client* com_maestia_yd_monitor_client::Base()	{ return this;}
		void com_maestia_yd_monitor_client::set_notify_time(DWORD msec)			{ m_notify_time = msec;}
		void com_maestia_yd_monitor_client::set_logger(logger_func_t* func)		{ m_pLogger = func;}


		struct looper
		{
			string ip;
			string port;
			void set_ip(string _ip,string _port) {ip=_ip;port=_port;}
			void operator()()
			{
				try
				{
					g_com_maestia_yd_monitor_client_interface->Base()->blocking_tcp_client(ip.c_str(), port.c_str());
				}
				catch (std::exception& e)
				{
					#define yd_log2(...) aname1024_t szMsg1234;ja_sprintf(szMsg1234,__VA_ARGS__);g_com_maestia_yd_monitor_client_interface->Base()->Log(szMsg1234,true);
					yd_log2( "[ERROR][YD_ZeroMonitor]Invoke Exception =%s\n",e.what());
				}
			}

		};
		void com_maestia_yd_monitor_client::start(acstr szIP,acstr port)
		{
			if(g_thread) return;
			m_isExit=false;
			looper _looper;
			_looper.set_ip(szIP,port);

			g_thread = new boost::thread(_looper);
			yd_log(__FUNCTION__ "[YD_ZeroMonitor]ydc_thread started\n");
			//blocking_tcp_client(szIP, port);
		}


	}//namespace nMaestia
}//namespace nMech




namespace nMech
{
	namespace nYD
	{
		extern "C"
		{
			__declspec(dllexport) void* jCreateInterface(jIE* pE)
			{
				g_com_maestia_yd_monitor_client_interface = new com_maestia_yd_monitor_client;
				return g_com_maestia_yd_monitor_client_interface;
			}
			__declspec(dllexport) void jDeleteInterface()
			{
				g_com_maestia_yd_monitor_client_interface->Base()->end();
				delete g_com_maestia_yd_monitor_client_interface->Base();
			}
			__declspec(dllexport) acstr jGetModuleOwnerName()
			{
				return "icandoit";
			}

		}
	}
}

