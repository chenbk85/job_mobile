/* file : jCriticalSectionRW.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-03 15:52:08
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jCriticalSectionRW_header__
#define __jCriticalSectionRW_header__
#pragma once

#include "header/jSyncObject.h"

namespace nMech
{

	class JBASE_API jCriticalSectionRW
	{
	private:
		int waitingReaders_;            // Number of readers waiting for access
		int waitingWriters_;            // Number of writers waiting for access
		int active_;                    // Number of threads currently with access
		// (0=no threads, >0=# of readers, -1=1 writer)
#pragma warning(disable : 4251)
		nUtil::jCriticalSection cs_;
		jSemaphore readSemaP;       // Readers wait on this if a writer has access
		jSemaphore writeSemaP;      // Writers wait on this if a reader has access
#pragma warning(default : 4251)

	public:
		jCriticalSectionRW(void) : waitingReaders_(0), waitingWriters_(0), active_(0), readSemaP(0, MAXLONG), writeSemaP(0, MAXLONG){}
		~jCriticalSectionRW(void){	assert(active_ == 0);	}

		void ReadLock(void);
		void WriteLock(void);

		void ReadUnlock(void){InternalUnlock();}
		void WriteUnlock(void){InternalUnlock();}

	private:
		void InternalUnlock(void);

	private:
		jCriticalSectionRW(const jCriticalSectionRW &);
		const jCriticalSectionRW &operator=(const jCriticalSectionRW &);
	};



}//namespace nMech

#endif // __jCriticalSectionRW_header__
