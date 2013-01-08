/* file : jService.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-27 18:56:31
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jService_header__
#define __jService_header__
#pragma once

#include "Interface/jIReportEvent.h"

namespace nMech
{

	class jService
	{
	public:
		jService();
		virtual ~jService()
		{

		}

	protected:
		SERVICE_STATUS			mServiceStatus;
		SERVICE_STATUS_HANDLE	mServiceStatusHandle;

		TCHAR					mServiceName[MAX_PATH];

		virtual VOID			OnStarted(VOID)		= 0;
		virtual VOID			OnStopped(VOID)		= 0;

	public:
		BOOL					Install(LPCTSTR serviceName,bool isAutoRun=true);
		BOOL					Uninstall(LPCTSTR serviceName);

		BOOL					Begin(LPTSTR serviceName);
		BOOL					End(VOID);

		VOID					RunCallback(DWORD argumentCount, LPTSTR *arguments);
		virtual					VOID CtrlHandlerCallback(DWORD opCode);
	};

	extern nLOG::jIReportEvent* g_pjIReportEvent;
#define GetRE() if(nMech::g_pjIReportEvent) nMech::g_pjIReportEvent

}//namespace nMech

#endif // __jService_header__
