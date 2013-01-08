/*
 *  xadlInclude.h
 *  iNetwork
 *
 *  Created by Kevin Ahn on 7/29/10.
 *  Copyright 2010 neowiz games. All rights reserved.
 *
 */

//#pragma once

#ifndef XADLINCLUDE2_H
#define XADLINCLUDE2_H

#ifndef _Poker

#define _MSC_VER 1500

#import <string>
#import <vector>
#import <list>
#import <map>
#import <sys/socket.h>
#import <netinet/in.h>
#import <arpa/inet.h>
#import <netdb.h>



using namespace std;


typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef long LONG;
typedef unsigned char* LPBYTE;
typedef DWORD* LPDWORD  ;
typedef char* LPCSTR ;
typedef char* LPSTR;
typedef wchar_t WCHAR;
typedef WCHAR* LPWSTR;
typedef const WCHAR* LPCWSTR;
typedef unsigned int UINT;
typedef int64_t __int64;
typedef unsigned char BYTE;
typedef unsigned long DWORD_PTR;
typedef size_t	strpos;
typedef const BYTE * LPCBYTE;
typedef void * LPVOID;
typedef u_int64_t LONGLONG;
//typedef unsigned short WORD;
typedef WORD* BSTR;
typedef char CHAR;

#define MAKEWORD(a, b)      ((WORD)(((BYTE)((DWORD_PTR)(a) & 0xff)) | ((WORD)((BYTE)((DWORD_PTR)(b) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)((DWORD_PTR)(a) & 0xffff)) | ((DWORD)((WORD)((DWORD_PTR)(b) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)((DWORD_PTR)(l) & 0xffff))
#define HIWORD(l)           ((WORD)((DWORD_PTR)(l) >> 16))
#define LOBYTE(w)           ((BYTE)((DWORD_PTR)(w) & 0xff))
#define HIBYTE(w)           ((BYTE)((DWORD_PTR)(w) >> 8))
#define FALSE	0
#define TRUE	1

#define lstrlenA	strlen
#define BOOL		int

#define _NO_XLIB 
#define _XADL

#define ERROR_INVALID_PARAMETER         87L    // dderror
#define ERROR_INSUFFICIENT_BUFFER       122L    // dderror
#define ASSERT
#define __stdcall

//#import "XADLBER.h"
//#import "AdlEncryptedMsg.h"
//#import "AdlEncryptedMsg_b.h"
//#import "AdlNSAP.h"
//#import "AdlNSAP_b.h"
//#import "AdlBLRBCommon.h"
//#import "AdlBLRBCommon_b.h"
//#import "AdlCommonStruct.h"
//#import "AdlCommonStruct_b.h"
//#import "xUtil.h"
//#import "xtmpl.h"
//#import "dualgoAdlHeaders.h"
//#import "sgsHeaders.h"

#include "XADLBER.h"
#include "xtmpl.h"
#include "AdlEncryptedMsg.h"
#include "AdlEncryptedMsg_b.h"
#include "AdlNSAP.h"
#include "AdlNSAP_b.h"
#include "AdlBLRBCommon.h"
#include "AdlBLRBCommon_b.h"
#include "AdlCommonStruct.h"
#include "AdlCommonStruct_b.h"
#include "xUtil.h"


#define _IPHONE
#define NPOS (string::npos)
#define ZeroMemory(a, b) { memset(a, 0, b); }

typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME;

//void GetLocalTime(PSYSTEMTIME st) {};

//int _vsnwprintf(WCHAR* bf, int size, LPCWSTR fmt, va_list vl) { return 0; };

using namespace adl;

#undef _MSC_VER

#endif

#endif