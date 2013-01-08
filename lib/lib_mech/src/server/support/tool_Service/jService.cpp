/* file : jService.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-27 18:56:40
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jService.h"

namespace nMech
{

	nLOG::jIReportEvent* g_pjIReportEvent=0;

	jService *gOwner = NULL;
	jService::jService()
	{
		ZeroMemory(mServiceName, sizeof(mServiceName));

		gOwner = this;
	}

	VOID WINAPI RunCallback(DWORD argumentCount, LPTSTR *arguments)
	{
		gOwner->RunCallback(argumentCount, arguments);
	}

	VOID WINAPI CtrlHandlerCallback(DWORD opCode)
	{
		gOwner->CtrlHandlerCallback(opCode);
	}

	VOID jService::RunCallback(DWORD argumentCount, LPTSTR *arguments)
	{
		DWORD Status;

		mServiceStatus.dwServiceType				= SERVICE_WIN32;
		mServiceStatus.dwCurrentState				= SERVICE_START_PENDING;
		mServiceStatus.dwControlsAccepted			= SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
		mServiceStatus.dwWin32ExitCode				= 0;
		mServiceStatus.dwServiceSpecificExitCode	= 0;
		mServiceStatus.dwCheckPoint					= 0;
		mServiceStatus.dwWaitHint					= 0;

		mServiceStatusHandle = RegisterServiceCtrlHandler(mServiceName, nMech::CtrlHandlerCallback);

		if (mServiceStatusHandle == (SERVICE_STATUS_HANDLE) 0)
			return;

		Status = NO_ERROR;

		mServiceStatus.dwCurrentState	= SERVICE_RUNNING;
		mServiceStatus.dwCheckPoint		= 0;
		mServiceStatus.dwWaitHint		= 0;

		if (!SetServiceStatus(mServiceStatusHandle, &mServiceStatus))
			return;
	}

	VOID jService::CtrlHandlerCallback(DWORD opCode)
	{
		switch (opCode)
		{
		case SERVICE_CONTROL_PAUSE:
			mServiceStatus.dwCurrentState = SERVICE_PAUSED;
			break;
		case SERVICE_CONTROL_CONTINUE:
			mServiceStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		case SERVICE_CONTROL_STOP:
			mServiceStatus.dwWin32ExitCode	= 0;
			mServiceStatus.dwCurrentState	= SERVICE_STOPPED;
			mServiceStatus.dwCheckPoint		= 0;
			mServiceStatus.dwWaitHint		= 0;
			break;
		case SERVICE_CONTROL_INTERROGATE:
			break;
		}
		GetRE()->Write(nLOG::eEL_INFORMATION,1,_T("%s contorl message = %d"),mServiceName,opCode);
		if (!SetServiceStatus(mServiceStatusHandle, &mServiceStatus))
			return;
	}

	BOOL jService::Install(LPCTSTR serviceName,bool isAutoRun)
	{
		TCHAR		ServiceFileName[MAX_PATH]	= {0,};
		SC_HANDLE	ServiceControlManager		= NULL;
		SC_HANDLE	ServiceHandle				= NULL;

		if (!serviceName)
			return FALSE;

		ServiceFileName[0]		= '"';
		GetModuleFileName(NULL, ServiceFileName + 1, MAX_PATH - 1);
		_tcscat(ServiceFileName, _T("\""));

		ServiceControlManager	= OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if (!ServiceControlManager)
			return FALSE;

		ServiceHandle			= CreateService(ServiceControlManager,
			serviceName,
			serviceName,
			SERVICE_ALL_ACCESS,
			SERVICE_WIN32_OWN_PROCESS,/*|SERVICE_INTERACTIVE_PROCESS,*/
			isAutoRun ? SERVICE_AUTO_START : SERVICE_DEMAND_START,
			SERVICE_ERROR_NORMAL,
			ServiceFileName,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL);

		if (!ServiceHandle)
		{
			CloseServiceHandle(ServiceControlManager);
			return FALSE;
		}

		CloseServiceHandle(ServiceHandle);
		CloseServiceHandle(ServiceControlManager);

		return TRUE;
	}

	BOOL jService::Uninstall(LPCTSTR serviceName)
	{
		SC_HANDLE ServiceControlManager	= NULL;
		SC_HANDLE ServiceHandle			= NULL;

		if (!serviceName)
			return FALSE;

		ServiceControlManager	= OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
		if (!ServiceControlManager)
			return FALSE;

		ServiceHandle			= OpenService(ServiceControlManager, serviceName, DELETE);
		if (!ServiceHandle)
		{
			CloseServiceHandle(ServiceControlManager);
			return FALSE;
		}

		if (!DeleteService(ServiceHandle))
		{
			CloseServiceHandle(ServiceHandle);
			CloseServiceHandle(ServiceControlManager);

			return FALSE;
		}

		CloseServiceHandle(ServiceHandle);
		CloseServiceHandle(ServiceControlManager);

		return TRUE;
	}

	BOOL jService::Begin(LPTSTR serviceName)
	{
		if (!serviceName)
			return FALSE;

		SERVICE_TABLE_ENTRY DispatchTable[] = 
		{
			{serviceName,	nMech::RunCallback},
			{NULL,			NULL}
		};

		_tcscpy(mServiceName, serviceName);

		this->OnStarted();

		if (!StartServiceCtrlDispatcher(DispatchTable))
		{
			_tprintf(_T("## Debug console mode ##\n"));
			getchar();
		}

		return TRUE;
	}

	BOOL jService::End(VOID)
	{
		this->OnStopped();

		return TRUE;
	}

}//namespace nMech