/* file : jCriticalSectionRW.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-03 15:52:18
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jCriticalSectionRW.h"


namespace nMech
{
	void jCriticalSectionRW::ReadLock(void)
	{
		cs_.Lock();

		// Are there writers waiting or is a writer writing?
		bool writePending = (waitingWriters_ || (active_ < 0));
		if (writePending == true)
		{
			// This reader must wait, increment the count of waiting readers
			++waitingReaders_;
		}
		else
		{
			// This reader can read, increment the count of active readers
			++active_;
		}

		cs_.UnLock();

		if (writePending == true)
		{
			// This thread must wait
			readSemaP.Wait();
		}
	}


	void jCriticalSectionRW::WriteLock(void)
	{
		cs_.Lock();

		bool owned = active_ != 0;
		if (owned == true)
		{
			// This writer must wait, increment the count of waiting writers
			++waitingWriters_;
		}
		else
		{
			// This writer can write, decrement the count of active writers
			active_ = -1;
		}

		cs_.UnLock();

		if (owned == true)
		{
			// This thread must wait
			writeSemaP.Wait();
		}
	}

	void jCriticalSectionRW::InternalUnlock(void)
	{
		cs_.Lock();

		if (active_ > 0)
		{
			// Readers have control so a reader must be done
			--active_;
		}
		else
		{
			// Writers have control so a writer must be done
			++active_;
		}

		jSemaphore *semaphore = NULL;
		long count = 1;

		if (active_ == 0)
		{
			// No thread has access, who should wake up?
			// NOTE: It is possible that readers could never get access
			//       if there are always writers wanting to write
			if (waitingWriters_ > 0)
			{
				// Writers are waiting and they take priority over readers
				active_ = -1;                 // A writer will get access
				--waitingWriters_;            // One less writer will be waiting
				semaphore = &writeSemaP; // Writers wait on this semaphore
				// NOTE: The semaphore will release only 1 writer thread
			}
			else if (waitingReaders_ > 0)
			{
				// Readers are waiting and no writers are waiting
				active_ = waitingReaders_;        // All readers will get access
				waitingReaders_ = 0;                     // No readers will be waiting
				semaphore = &readSemaP;             // Readers wait on this semaphore
				count = active_;                         // jSemaphore releases all readers
			}
			else
			{
				// There are no threads waiting at all; no semaphore gets released
			}
		}

		cs_.UnLock();

		if (semaphore != NULL)
		{
			// Some threads are to be released
			semaphore->Release(count, NULL);
		}
	}

}//namespace nMech
