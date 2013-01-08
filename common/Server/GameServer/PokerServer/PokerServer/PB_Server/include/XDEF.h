//
// XDef.h
//

#ifndef XDEF_H
#define XDEF_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

///////////////////////// Pragma message helper macro /////////////////////////

#define _mkSTR(x)	   #x
#define mkSTR(x)	   _mkSTR(x)
#define mkMSG(desc) __FILE__ "(" mkSTR(__LINE__) "):" desc
#define prMSG(desc) message(__FILE__ "(" mkSTR(__LINE__) "):" desc)

#ifdef NOOMSG
#define oMSG(desc)
#else
#define oMSG(desc) message(__FILE__ "(" mkSTR(__LINE__) "):" desc)
#endif

//////////////////////// Windows Version Build Option /////////////////////////

#if defined(_WIN32_WINNT)
#pragma oMSG("[_WIN32_WINNT] - defined")
#ifndef WINVER
#define WINVER _WIN32_WINNT
#endif
#elif defined(_WIN32_WINDOWS)
#pragma oMSG("[_WIN32_WINDOWS] - defined")
#ifndef _WIN32_DCOM
#define _WIN32_DCOM
#endif
#ifndef WINVER
#define WINVER _WIN32_WINDOWS
#endif
#elif defined(_WIN32_DCOM)
#pragma oMSG("[_WIN32_DCOM] - defined(now WINVER=0x40A)")
#ifndef _WIN32_WINDOWS
#define _WIN32_WINDOWS 0x40A
#endif
#ifndef WINVER
#define WINVER _WIN32_WINDOWS
#endif
#else // nothing defined...
#pragma oMSG("[_WIN32_WINNT] - default 0x0500")
#define _WIN32_WINNT 0x500
#define WINVER _WIN32_WINNT
#endif

///////////////////////////////////////////////////////////////////////////////
//////////////////////////// Unicode Build Option /////////////////////////////
///////////////////////////////////////////////////////////////////////////////

// If we are not compiling for an x86 CPU, we always compile using Unicode.
#ifndef _M_IX86
#pragma oMSG("[NON-x86CPU] - default UNICODE")
#define UNICODE
#define _UNICODE
#endif
// When using Unicode Windows functions, use Unicode C-Runtime functions too.
#ifdef UNICODE
#pragma oMSG("[UNICODE] - defined")
#ifndef _UNICODE
#define _UNICODE
#endif
#else
#pragma oMSG("[UNICODE] - NOT defined")
#ifdef _UNICODE
#undef _UNICODE
#endif
#endif


///////////////////////////////////////////////////////////////////////////////
////////////// Allow code to compile cleanly at warning level 4 ///////////////
///////////////////////////////////////////////////////////////////////////////

// nonstandard extension 'single line comment' was used
#pragma warning(disable:4001)
// switch statement contains 'default' but no 'case' labels
#pragma warning(disable:4065)
// typedef-name used as synonym for class-name
#pragma warning(disable:4097)
// unreferenced formal parameter
#pragma warning(disable:4100)
// conditional expression is constant
#pragma warning(disable:4127)
// Note: Creating precompiled header 
#pragma warning(disable:4699)
// Note: copy constructor could not be generated 
#pragma warning(disable:4511)
// unreferenced inline function has been removed
#pragma warning(disable:4514)
// 'identifier' : identifier was truncated to 'number' characters in the debug information
#pragma warning(disable:4786)
// function not inlined
#pragma warning(disable:4710)

///////////////////////////////////////////////////////////////////////////////
///////////////////////// Include Windows Definitions /////////////////////////
///////////////////////////////////////////////////////////////////////////////

// use warning level 4 except windows.h
#pragma warning(push, 3)

// Exclude rarely-used stuff from Windows headers
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#if !defined(DEF_LINUX)
#include <Windows.h>
#include <Windef.h>
#include <MMSystem.h>
#include <ObjBase.h>
#include <comdef.h>
#endif

#include <Tchar.h>
#include <Process.h>
#include <LIMITS.h>
#include <malloc.h>

#pragma warning(pop) 
#pragma warning(push, 4)

///////////////////////////////////////////////////////////////////////////////
///////////////////////// include XLibrary Errorcode Definitios ///////////////
///////////////////////////////////////////////////////////////////////////////
#include "XErr.h"

///////////////////////////////////////////////////////////////////////////////
///////////// Verify that the proper header files are being used //////////////
///////////////////////////////////////////////////////////////////////////////

#if (_WIN32_WINNT >= 0x500)
#ifndef WT_EXECUTEINPERSISTENTIOTHREAD
#pragma oMSG("You are not using the latest Platform SDK header/library")
#pragma oMSG("files. This may prevent the project from building correctly.")
#endif
#endif

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// Macro Utilitys /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


//////////////////////////// RTTI Macros /////////////////////////////

#define IS_KIND_OF(x, T) (NULL != dynamic_cast<T*>(x))
#ifdef _CPPRTTI
#define ASSERT_IS_KIND_OF(x,T) ASSERT(IS_KIND_OF(x,T))
#else
#define ASSERT_IS_KIND_OF(x,T)
#endif

///////////////////////////// chBEGINTHREADEX Macro ///////////////////////////
// This macro function calls the C runtime's _beginthreadex function. 
// The C runtime library doesn't want to have any reliance on Windows' data 
// types such as HANDLE. This means that a Windows programmer needs to cast
// values when using _beginthreadex. Since this is terribly inconvenient, 
// I created this macro to perform the casting.
#ifdef _MT

typedef unsigned (__stdcall *PTHREAD_START) (void *);

#define _BeginThread(psa, cbStack, pfnStartAddr,	\
		pvParam, fdwCreate, pdwThreadId)            \
      ((HANDLE)_beginthreadex(                      \
         (void *)        (psa),                     \
         (unsigned)      (cbStack),                 \
         (PTHREAD_START) (pfnStartAddr),            \
         (void *)        (pvParam),                 \
         (unsigned)      (fdwCreate),               \
         (unsigned *)    (pdwThreadId)))

inline HANDLE BeginThread(
  LPSECURITY_ATTRIBUTES lpThreadAttributes, // SD
  DWORD dwStackSize,                        // initial stack size
  LPTHREAD_START_ROUTINE lpStartAddress,    // thread function
  LPVOID lpParameter,                       // thread argument
  DWORD dwCreationFlags,                    // creation option
  LPDWORD lpThreadId                        // thread identifier
)
{
	return _BeginThread( lpThreadAttributes,
						dwStackSize,
						lpStartAddress,
						lpParameter,
						dwCreationFlags,
						lpThreadId );
}

#endif


////////////////////////////// _inrange Macro ////////////////////////////////
// This macro evaluates to test a number in range [lo, hi)
#ifndef _inrange
#define _inrange(lo, num, hi) (((lo) <= (num)) && ((num) < (hi)))
#endif
#ifndef _incloserange
#define _incloserange(lo, num, hi) (((lo) <= (num)) && ((num) <= (hi)))
#endif
#ifndef _inopenrange
#define _inopenrange(lo, num, hi) (((lo) < (num)) && ((num) < (hi)))
#endif

//////////////////////////////// _dimof Macro ////////////////////////////////
// This macro evaluates to the number of elements in an array. 
#ifndef _dimof
#define _dimof(array) (sizeof(array)/sizeof(array[0]))
#endif

///////////////////////////////////////////////////////////////////////////////
////////////////////////////// Debug Utilitys /////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

////////////////// DebugBreak Improvement for x86 platforms ///////////////////
#ifdef _X86_
#define _DebugBreak()    _asm { int 3 }
#endif

///////////////////////////////////////////////////////////////////////////////
// base types

typedef unsigned long DWORD;
typedef const BYTE * LPCBYTE;
typedef const char * LPCSTR;

#define DWORD_MAX DWORD(-1)
#define MAKEDWORD(lo,hi) ((DWORD)MAKELONG((lo),(hi)))

///////////////////////////////////////////////////////////////////////////////

#define _valid_handle(hdl) (((hdl) != NULL) && ((hdl) != INVALID_HANDLE_VALUE))

#define _wait_message(dw, s) ((dw) == (WAIT_OBJECT_0 + (s)))

#define _wait_object(dw, s) _inrange(WAIT_OBJECT_0, dw, (WAIT_OBJECT_0 + s))
#define _wait_object_index(dw) ((dw) - WAIT_OBJECT_0)
#define _wait_object0(dw) ((dw) == WAIT_OBJECT_0)

#define _wait_abandoned(dw, s) _inrange(WAIT_ABANDONED_0, dw, (WAIT_ABANDONED_0 + s))
#define _wait_abandoned_index(dw) ((dw) - WAIT_ABANDONED_0)
#define _wait_abandoned0(dw) ((dw) == WAIT_ABANDONED_0)

#define _wait_index(dw, s) (_wait_object((dw),(s)) ? _wait_object_index(dw) : _wait_abandoned_index(dw))

#define _wait_failed(dw) ((dw) == WAIT_FAILED)
#define _wait_timeout(dw) ((dw) == WAIT_TIMEOUT)
#define _wait_io_completion(dw) ((dw) == WAIT_IO_COMPLETION)

#endif //!XDEF_H
