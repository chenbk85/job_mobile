//
//XErr.h
//


/************************************************************************
*                                                                       *
*   XErr.h --  Error code definitions for XLibrary functions			*
*                                                                       *
*                                             - 2004.02.23              *
************************************************************************/



#ifndef _XERR_H
#define _XERR_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//Reference - windows error code format
//
//  Values are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +---+-+-+-----------------------+-------------------------------+
//  |Sev|C|R|     Facility          |               Code            |
//  +---+-+-+-----------------------+-------------------------------+
//
//  where
//
//      Sev - is the severity code
//
//          00 - Success
//          01 - Informational
//          10 - Warning
//          11 - Error
//
//      C - is the Customer code flag
//
//      R - is a reserved bit
//
//      Facility - is the facility code
//
//      Code - is the facility's status code
//

//////////////////////////////////////////////////////////////////////////
//		This is Util-Macro for using custom's errorcode

#define SER				0		//win32 system error
#define CER				1		//custom error

#define _make_cer(srcerr) ((unsigned long)(srcerr) | 0x10000000)   	//make custom error code
#define _is_cer(err) ((unsigned long)(err) >> 28 == CER)

	//SetLastError and GetLastError
#define _set_lastcer(src) ::SetLastError(_make_cer(src))
#define SET_ERROR(src, issvcerr) ((issvcerr) == CER ? _set_lastcer(src) : ::SetLastError(src))

#define _get_lastcer(perr) ((unsigned long)(perr) ^ 0x10000000)
#define _get_error(err) (_is_cer(err) ? _get_lastcer(err) : err)
#define GET_ERROR()	_get_error(::GetLastError())


	//WSAGetLastError and WSAGetLastError
#define _wsa_set_lastcer(src) ::WSASetLastError(_make_cer(src))
#define WSASET_ERROR(src, issvcerr) ((issvcerr) == CER ? _wsa_set_lastcer(src) : ::WSASetLastError(src))

#define _get_lastcer(perr) ((unsigned long)(perr) ^ 0x10000000)
#define _get_error(err) (_is_cer(err) ? _get_lastcer(err) : err)
#define WSAGET_ERROR()	_get_error(::WSAGetLastError())


	/*	-- sample code	--	*/
	/*
	//sample 1 - custom errorcode 
#define ERROR_TEST 19000L			// Set custom errorcode in xlibrary
	SET_ERROR(ERROR_TEST, CER);		//CER mean custom error

	//1-1 : recommendation
	DWORD dwErr = GET_ERROR();
	if(dwErr == ERROR_TEST) return false;

	//1-2
	DWORD dwErr2 = ::GetLastError();
	if(_is_cer(dwErr2))
	{
		dwErr2 = GET_ERROR();
		if(dwErr2 == ERROR_TEST)
			return false;
	}


	//sample 2 - windows errorcode 
	SET_ERROR(ERROR_INVALID_PARAMETER, SER);	//Set windows errorcode
	DWORD dwErr3 = GET_ERROR();					//or ::GetLastError();
	if(dwErr3 == ERROR_INVALID_PARAMETER)
		return false;
		*/

/////////////////////////////////////////////////////////////////////////////////
//XLibrary's errorcode defintion
//
//
//recommendation error code : with the exption of Windows Error Code 											
//

//////////////////////////////////////////////////////////////
//common

//	case: not initialize
//
#define ERROR_INTERNAL_MEMBER			19000L

//////////////////////////////////////////////////////////////
//XTP									20000L ~

//
//
#define ERROR_XTP_INVALID_HANDLE		20000L

//
//
#define ERROR_XTP_INVALID_PALAMETER		20002L

//
//
#define ERROR_XTP_INTERNAL_MEMBER		20004L

//////////////////////////////////////////////////////////////
//XLstn									21000L~
//////////////////////////////////////////////////////////////
//XSig									22000L~

//
//
#define ERROR_XSIG_NOTINITIALIZED_QUEUE	22002L

//////////////////////////////////////////////////////////////
//XMB									23000L~
//////////////////////////////////////////////////////////////
//XLink									24000L~

//
//
#define ERROR_XLINK_HANDLE_OVERFLOW		24002L

//
//
#define ERROR_XLINK_UNKNOWNLINK			24004L

//
//
#define ERROR_XLINK_INVALID_HANDLE		24006L
//////////////////////////////////////////////////////////////
//XLinkSig
//////////////////////////////////////////////////////////////
//XDBG
//////////////////////////////////////////////////////////////
//XSEH

#endif //_XERR_H