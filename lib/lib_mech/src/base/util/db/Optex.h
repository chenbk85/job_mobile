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


			JUTIL_API BOOL  OPTEX_Initialize (jOptMutexP poptex);
			JUTIL_API VOID  OPTEX_Delete     (jOptMutexP poptex);
			JUTIL_API DWORD OPTEX_Enter      (jOptMutexP poptex, DWORD dwTimeout);
			JUTIL_API VOID  OPTEX_Leave      (jOptMutexP poptex);


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
