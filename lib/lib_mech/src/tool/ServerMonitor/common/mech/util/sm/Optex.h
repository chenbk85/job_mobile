/* file : Optex.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 16:02:23
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __Optex_header_23412389dfioasdfkdfjalksdjfwieo_
#define __Optex_header_23412389dfioasdfkdfjalksdjfwieo_
#pragma once


#define JBASE_API_NULL
/******************************************************************************
Module name: OptEx.h
Written by:  Jeffrey Richter
Purpose:     Defines the jOptMutex (optimized mutex) synchronization object
******************************************************************************/

namespace nMech
{
	namespace nUtil
	{
			// The opaque jOptMutex data structure
			typedef struct {
				LONG   lLockCount;
				DWORD  dwThreadId;
				LONG   lRecurseCount;
				HANDLE hEvent;
			} jOptMutex, *jOptMutexP;


			///////////////////////////////////////////////////////////////////////////////


			JBASE_API_NULL BOOL  OPTEX_Initialize (jOptMutexP poptex);
			JBASE_API_NULL VOID  OPTEX_Delete     (jOptMutexP poptex);
			JBASE_API_NULL DWORD OPTEX_Enter      (jOptMutexP poptex, DWORD dwTimeout);
			JBASE_API_NULL VOID  OPTEX_Leave      (jOptMutexP poptex);


			///////////////////////////////////////////////////////////////////////////////


#ifdef _USE_OPTEX_INSTEAD_OF_CRITICAL_SECTIONS_

#define CRITICAL_SECTION                      jOptMutex
#define InitializeCriticalSection(poptex)     ((VOID) OPTEX_Initialize(poptex))
#define DeleteCriticalSection(poptex)         OPTEX_Delete(poptex)
#define EnterCriticalSection(poptex)          ((VOID) OPTEX_Enter(poptex,                                                                   INFINITE))
#define LeaveCriticalSection(poptex)          OPTEX_Leave(poptex)

#endif   // _USE_OPTEX_INSTEAD_OF_CRITICAL_SECTIONS_
	}// nUTIL
}// nMech


///////////////////////////////// End of File /////////////////////////////////

#endif // __Optex_header_23412389dfioasdfkdfjalksdjfwieo_
