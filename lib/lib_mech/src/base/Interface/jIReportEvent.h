/*
http://www.codeproject.com/KB/system/mctutorial.aspx



*/

// EventLog.h: Schnittstelle f? die Klasse jReportEvent.
//
//////////////////////////////////////////////////////////////////////

/* file : jReportEvent.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-30 23:28:47
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jEventLog_header__
#define __jEventLog_header__
#pragma once


#include "header/jInterface.h"

namespace nMech
{
	namespace nLOG
	{

		enum EEventType
		{
			eEL_SUCCESS = EVENTLOG_SUCCESS                
			,eEL_ERROR = EVENTLOG_ERROR_TYPE             
			,eEL_WARNING = EVENTLOG_WARNING_TYPE          
			,eEL_INFORMATION = EVENTLOG_INFORMATION_TYPE 
			,eEL_AUDIT_SUCCESS = EVENTLOG_AUDIT_SUCCESS  
			,eEL_AUDIT_FAILURE = EVENTLOG_AUDIT_FAILURE  
			,eEL_NULL
		};

#define jINTERFACE_jIReportEvent(X) public:	\
	virtual bool Init(cstr szAppName ,cstr szSourceName,DWORD dwCategoryNum) ##X\
	virtual DWORD RemoveEventSource(cstr szAppName ,cstr szSourceName) ##X\
	\
	/*DWORD dwEventID : jReportEvent_header.h */\
	virtual BOOL Write(EEventType eType, WORD wCategory, DWORD dwEventID, cstr szLog)##X\
	virtual BOOL Write(EEventType eType, WORD wCategory, cstr fmt,...)##X\
	\
	virtual cstr LoadMessage( OUT tname1024_t buf,IN DWORD dwMsgId, ... ) ##X\
	virtual BOOL LaunchViewer(void) ##X\

		jINTERFACE_END_BASE1(jIReportEvent, nInterface::jIInterface);

	}//nLOG

}//namespace nMech

/*
사용법.

nLOG::jIReportEvent* pjIRE = jCREATE_INTERFACE(nMech::nLOG::jIReportEvent);
pjIRE->Init(jS(jServer), netConfigXmlNode, 1);
pjIRE->Release(); // 종료시 자동으로 릴리즈됨.
*/


#endif // __jEventLog_header__
