/******************************************************************************
Module name: OptEx.c
Written by:  Jeffrey Richter
Purpose:     Implements the jOptMutex (optimized mutex) synchronization object
******************************************************************************/
#include "stdafx.h"
#include <windows.h>
#include "OptEx.h"


///////////////////////////////////////////////////////////////////////////////
namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{

			BOOL OPTEX_Initialize (jOptMutexP poptex) {

				poptex->lLockCount = -1;   // No threads have enterred the jOptMutex
				poptex->dwThreadId = 0;    // The jOptMutex is unowned
				poptex->lRecurseCount = 0; // The jOptMutex is unowned
				poptex->hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
				return(poptex->hEvent != NULL);  // TRUE if the event is created
			}


			///////////////////////////////////////////////////////////////////////////////


			VOID OPTEX_Delete (jOptMutexP poptex) {

				// No in-use check
				CloseHandle(poptex->hEvent);  // Close the event
			}


			///////////////////////////////////////////////////////////////////////////////


			DWORD OPTEX_Enter (jOptMutexP poptex, DWORD dwTimeout) {

				DWORD dwThreadId = GetCurrentThreadId();  // The calling thread's ID

				// Assume that the thread waits successfully
				DWORD dwRet = WAIT_OBJECT_0;  

				if (InterlockedIncrement(&poptex->lLockCount) == 0) {

					// ---> No thread owns the jOptMutex
					poptex->dwThreadId = dwThreadId; // We own it
					poptex->lRecurseCount = 1;       // We own it once

				} else {

					// ---> Some thread owns the jOptMutex
					if (poptex->dwThreadId == dwThreadId) {

						// ---> We already own the jOptMutex
						poptex->lRecurseCount++;     // We own it again

					} else {

						// ---> Another thread owns the jOptMutex
						// Wait for the owning thread to release the jOptMutex
						dwRet = WaitForSingleObject(poptex->hEvent, dwTimeout);
						if (dwRet != WAIT_TIMEOUT) {

							// ---> We got ownership of the jOptMutex
							poptex->dwThreadId = dwThreadId; // We own it now
							poptex->lRecurseCount = 1;       // We own it once
						}
					}
				}

				// Return why we continue execution
				return(dwRet);
			}


			///////////////////////////////////////////////////////////////////////////////


			VOID OPTEX_Leave (jOptMutexP poptex) {

				if (--poptex->lRecurseCount > 0) {

					// We still own the jOptMutex
					InterlockedDecrement(&poptex->lLockCount);

				} else {

					// We don't own the jOptMutex
					poptex->dwThreadId = 0;
					if (InterlockedDecrement(&poptex->lLockCount) >= 0) {
						// Other threads are waiting, wake one on them
						SetEvent(poptex->hEvent);
					}
				}
			}
		}// nDB
	}// nUTIL
}// nMech


///////////////////////////////// End of File /////////////////////////////////
