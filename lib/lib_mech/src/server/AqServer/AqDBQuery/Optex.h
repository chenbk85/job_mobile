/* file : Optex.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 16:02:23
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __Optex_header__
#define __Optex_header__
#pragma once



/******************************************************************************
Module name: OptEx.h
Written by:  Jeffrey Richter
Purpose:     Defines the jOptMutex (optimized mutex) synchronization object
******************************************************************************/

namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{


			// The opaque jOptMutex data structure
			typedef struct {
				LONG   lLockCount;
				DWORD  dwThreadId;
				LONG   lRecurseCount;
				HANDLE hEvent;
			} jOptMutex, *jOptMutexP;


			///////////////////////////////////////////////////////////////////////////////


			BOOL  OPTEX_Initialize (jOptMutexP poptex);
			VOID  OPTEX_Delete     (jOptMutexP poptex);
			DWORD OPTEX_Enter      (jOptMutexP poptex, DWORD dwTimeout);
			VOID  OPTEX_Leave      (jOptMutexP poptex);


			///////////////////////////////////////////////////////////////////////////////


#ifdef _USE_OPTEX_INSTEAD_OF_CRITICAL_SECTIONS_

#define CRITICAL_SECTION                      jOptMutex
#define InitializeCriticalSection(poptex)     ((VOID) OPTEX_Initialize(poptex))
#define DeleteCriticalSection(poptex)         OPTEX_Delete(poptex)
#define EnterCriticalSection(poptex)          ((VOID) OPTEX_Enter(poptex,                                                                   INFINITE))
#define LeaveCriticalSection(poptex)          OPTEX_Leave(poptex)

#endif   // _USE_OPTEX_INSTEAD_OF_CRITICAL_SECTIONS_

		}// nDB
	}// nUTIL
}// nMech


///////////////////////////////// End of File /////////////////////////////////

#endif // __Optex_header__
