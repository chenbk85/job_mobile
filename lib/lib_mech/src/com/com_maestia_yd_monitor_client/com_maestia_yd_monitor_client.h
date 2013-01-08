/* file : com_maestia_yd_monitor_client.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-11 20:49:25
comp.: rocworks.co.kr
title : 
desc : 


다음 코드를 정의 해야한다.

	namespace nMech
	{
		namespace nYD
		{
			HMODULE g_hDLL_com_maestia_yd_monitor_client_interface=0;
			tcstr szDLL_com_maestia_yd_monitor_client=_T("com_maestia_yd_monitor_client.dll");
		}
	}


사용법.

	nYD::com_maestia_yd_monitor_client_interface* pCYD = nYD::Create_com_maestia_yd_monitor_client();

	pCYD->set_notify_time(1000);
	pCYD->set_logger(logger_func);
	pCYD->start("127.0.0.1","1234");
	_getch();
	pCYD->end();
	nYD::Delete_com_maestia_yd_monitor_client();
	return 0;


*/

#ifndef __com_maestia_yd_monitor_client_header__
#define __com_maestia_yd_monitor_client_header__
#pragma once


namespace nMech
{
	namespace nYD
	{
		typedef void logger_func_t(acstr szMsg,bool isCreatical);

		#define jINTERFACE_com_maestia_yd_monitor_client_interface(x) public:	\
			virtual void set_notify_time(DWORD msec) ##x \
			virtual void set_logger(logger_func_t* func) ##x \
			virtual void start(acstr szIP,acstr port)##x \
			virtual struct com_maestia_yd_monitor_client *Base()##x\

		jINTERFACE_END(com_maestia_yd_monitor_client_interface);

		extern HMODULE g_hDLL_com_maestia_yd_monitor_client_interface;
		extern tcstr szDLL_com_maestia_yd_monitor_client;
		inline com_maestia_yd_monitor_client_interface* Create_com_maestia_yd_monitor_client()
		{
			HMODULE hDLL;
			hDLL = ::LoadLibrary(szDLL_com_maestia_yd_monitor_client);
			if(!hDLL)
			{
				MessageBox(0,_T("load fial com_maestia_yd_monitor_client.dll"), _T("error"),MB_OK);
				return 0;
			}
			g_hDLL_com_maestia_yd_monitor_client_interface = hDLL;
			typedef void* jCreateInterface_t(jIE* pE);

			jCreateInterface_t* func = (jCreateInterface_t*)::GetProcAddress(hDLL, "jCreateInterface" );
			if(!func)
			{
				MessageBox(0,_T("find fail jCreateInterface in com_maestia_yd_monitor_client.dll"), _T("error"),MB_OK);
				return 0;
			}
			return (com_maestia_yd_monitor_client_interface*)func(0);

		}

		inline void Delete_com_maestia_yd_monitor_client()
		{
			HMODULE hDLL=g_hDLL_com_maestia_yd_monitor_client_interface;
			if(!hDLL) return;
			typedef void* jDeleteInterface_t();

			jDeleteInterface_t* func = (jDeleteInterface_t*)::GetProcAddress(hDLL, "jDeleteInterface" );
			if(!func)
			{
				return;
			}
			func();

		}


	}//namespace nYD
}//namespace nMech




#endif // __com_maestia_yd_monitor_client_header__
