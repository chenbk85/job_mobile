/* file : jSyncObject.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-03 14:24:07
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jSyncObject_header__
#define __jSyncObject_header__

#pragma once

#include <Windows.h>
#include <cassert>
#include "header/_NonCopyable.h"

namespace nMech
{
	//--------------------------------------------------------------------------
	class jMutex
	//--------------------------------------------------------------------------
	{
	private:
		HANDLE mutex_;

	public:
		jMutex(bool initialOwner=false , cstr name =NULL , LPSECURITY_ATTRIBUTES sa  =NULL ){mutex_ = CreateMutex(sa, initialOwner, name);}
		jMutex(cstr nameToOpen, uint iAccess=MUTEX_ALL_ACCESS, bool inheritHandle=false ){mutex_ = OpenMutex(iAccess, inheritHandle, nameToOpen);}
		~jMutex(void){	CloseHandle(mutex_);}

		bool Wait(uint mseconds = INFINITE)						{return (WaitForSingleObject(mutex_, mseconds) != WAIT_TIMEOUT);	}
		bool WaitEx(bool alertable, uint mseconds=INFINITE )	{return (WaitForSingleObjectEx(mutex_, mseconds, alertable) != WAIT_TIMEOUT);}

		bool Lock(uint mseconds = INFINITE)						{return Wait(mseconds);	}
		bool Unlock(void){	return (ReleaseMutex(mutex_) == TRUE);}

	private:
		jMutex(const jMutex &);
		const jMutex &operator=(const jMutex &);
	};

	//--------------------------------------------------------------------------
	class jSemaphore
	//--------------------------------------------------------------------------
	{
	private:
		HANDLE semaphore_;

	public:
		jSemaphore(int initialCount, int iMax, cstr name=NULL , LPSECURITY_ATTRIBUTES sa=NULL )
				{semaphore_ = CreateSemaphore(sa, initialCount, iMax, name);}
		jSemaphore(cstr nameToOpen, unsigned int iAccess=SEMAPHORE_ALL_ACCESS , bool inheritHandle=false )
				{semaphore_ = OpenSemaphore(iAccess, inheritHandle, nameToOpen);}
		~jSemaphore(void){CloseHandle(semaphore_);}

		bool Release(int releaseCount, int *previousCount = NULL)
		{
			int tempCount = 0;
			bool result = ReleaseSemaphore(semaphore_, releaseCount, reinterpret_cast<long *>(&tempCount)) == TRUE;
			if (result && previousCount)
				*previousCount = tempCount;
			return result;
		}

		bool Wait(unsigned int mseconds = INFINITE)
					{return (WaitForSingleObject(semaphore_, mseconds) != WAIT_TIMEOUT);		}
		bool WaitEx(bool alertable, unsigned int mseconds=INFINITE )
					{return (WaitForSingleObjectEx(semaphore_, mseconds, alertable) != WAIT_TIMEOUT);		}

		bool Lock(unsigned int mseconds = INFINITE)	{return Wait(mseconds);		}
		bool Unlock(void)								{return Release(1);		}

	private:
		jSemaphore(const jSemaphore &);
		const jSemaphore &operator=(const jSemaphore &);
	};

	//--------------------------------------------------------------------------
	class jAutoResetEvent
	//--------------------------------------------------------------------------
	{
	private:
		HANDLE event_;
	public:
		jAutoResetEvent(bool initialState  = false )	{event_ = CreateEvent(NULL, FALSE, initialState, NULL);}
		~jAutoResetEvent(void)						{CloseHandle(event_);}
		bool Set(void)		{	return (SetEvent(event_) == TRUE);}
		bool Reset(void)	{	return (ResetEvent(event_) == TRUE);}
		bool Pulse(void)	{	return (PulseEvent(event_) == TRUE);}

		bool Wait(unsigned int mseconds = INFINITE)
					{return (WaitForSingleObject(event_, mseconds) != WAIT_TIMEOUT);	}
		bool WaitEx(bool alertable, unsigned int mseconds  = INFINITE )
					{return (WaitForSingleObjectEx(event_, mseconds, alertable) != WAIT_TIMEOUT);}
	private:
		jAutoResetEvent(const jAutoResetEvent &);
		const jAutoResetEvent &operator=(const jAutoResetEvent &);
	};

	//--------------------------------------------------------------------------
	class jManualResetEvent
	//--------------------------------------------------------------------------
	{
	private:
		HANDLE event_;
	public:
		jManualResetEvent(bool initialState = false)	{	event_ = CreateEvent(NULL, TRUE, initialState, NULL);}
		~jManualResetEvent(void)						{	CloseHandle(event_); }

		bool Set(void)	{	return (SetEvent(event_) == TRUE);	}
		bool Reset(void){	return (ResetEvent(event_) == TRUE);}
		bool Pulse(void){	return (PulseEvent(event_) == TRUE);}
		bool Wait(unsigned int mseconds = INFINITE)					{return (WaitForSingleObject(event_, mseconds) != WAIT_TIMEOUT);}
		bool WaitEx(bool alertable, unsigned int mseconds = INFINITE){return (WaitForSingleObjectEx(event_, mseconds, alertable) != WAIT_TIMEOUT);}
	private:
		jManualResetEvent(const jManualResetEvent &);
		const jManualResetEvent &operator=(const jManualResetEvent &);
	};

	

	// ScopedLock
	template<typename T>
	class ScopedLock : private _NonCopyable
	{
	private:
		T &mutex_;
		bool locked_;

	public:
		explicit ScopedLock(T *mutex, bool initiallyLocked = true) : mutex_(*mutex), locked_(false)
		{
			if (initiallyLocked == true)
			{
				Lock();
			}
		}
		explicit ScopedLock(T &mutex, bool initiallyLocked = true) : mutex_(mutex), locked_(false)
		{
			if (initiallyLocked == true)
			{
				Lock();
			}
		}
		~ScopedLock(void)
		{
			if (locked_ == true)
			{
				Unlock();
			}
		}

		void Lock(void)
		{
			if (locked_ == true)
			{
				assert(!"[ScopedLock::Lock()] locked_ must be false.");
				throw "[ScopedLock::Lock()] locked_ must be false.";
			}

			mutex_.Lock();
			locked_ = true;
		}
		void Unlock(void)
		{
			if (locked_ == false)
			{
				assert(!"[ScopedLock::Unlock()] locked_ must be true.");
				throw "[ScopedLock::Unlock()] locked_ must be true.";
			}

			locked_ = false;
			mutex_.Unlock();
		}

		bool IsLocked(void) const
		{
			return locked_;
		}
	};

	// ScopedTimedLock
	template<typename T>
	class ScopedTimedLock : private _NonCopyable
	{
	private:
		T &mutex_;
		bool locked_;

	public:
		ScopedTimedLock(T *mutex, uint mseconds) : mutex_(*mutex), locked_(false)
		{
			TimedLock(mseconds);
		}
		explicit ScopedTimedLock(T *mutex, bool initiallyLocked = true) : mutex_(*mutex), locked_(false)
		{
			if (initiallyLocked == true)
			{
				Lock();
			}
		}
		ScopedTimedLock(T &mutex, uint mseconds) : mutex_(mutex), locked_(false)
		{
			TimedLock(mseconds);
		}
		explicit ScopedTimedLock(T &mutex, bool initiallyLocked = true) : mutex_(mutex), locked_(false)
		{
			if (initiallyLocked == true)
			{
				Lock();
			}
		}
		~ScopedTimedLock(void)
		{
			if (locked_ == true)
			{
				Unlock();
			}
		}

		void Lock(void)
		{
			if (locked_ == true)
			{
				assert(!"[ScopedTimedLock::Lock()] locked_ must be false.");
				throw "[ScopedTimedLock::Lock()] locked_ must be false.";
			}

			mutex_.Lock(INFINITE);
			locked_ = true;
		}
		void TimedLock(uint mseconds)
		{
			if (locked_ == true)
			{
				assert(!"[ScopedTimedLock::TimedLock()] locked_ must be false.");
				throw "[ScopedTimedLock::TimedLock()] locked_ must be false.";
			}

			mutex_.Lock(mseconds);
			locked_ = true;
		}
		void Unlock(void)
		{
			if (locked_ == false)
			{
				assert(!"[ScopedTimedLock::Unlock()] locked_ must be true.");
				throw "[ScopedTimedLock::Unlock()] locked_ must be true.";
			}

			locked_ = false;
			mutex_.Unlock();
		}

		bool IsLocked(void) const
		{
			return locked_;
		}
	};

	// ScopedRWLock
	namespace ScopedRWLockState
	{
		enum TRWLockState
		{
			Unlocked = 0,
			ReadLocked = 1,
			WriteLocked = 2
		};
	}

	template<typename T>
	class ScopedRWLock : private _NonCopyable
	{
	private:
		T &mutex_;
		ScopedRWLockState::TRWLockState state_;

	public:
		ScopedRWLock(T *mutex, ScopedRWLockState::TRWLockState initialState) : mutex_(*mutex), state_(ScopedRWLockState::Unlocked)
		{
			if (initialState == ScopedRWLockState::ReadLocked)
			{
				ReadLock();
			}
			else if (initialState == ScopedRWLockState::WriteLocked)
			{
				WriteLock();
			}
		}
		ScopedRWLock(T &mutex, ScopedRWLockState::TRWLockState initialState) : mutex_(mutex), state_(ScopedRWLockState::Unlocked)
		{
			if (initialState == ScopedRWLockState::ReadLocked)
			{
				ReadLock();
			}
			else if (initialState == ScopedRWLockState::WriteLocked)
			{
				WriteLock();
			}
		}
		~ScopedRWLock(void)
		{
			if (state_ != ScopedRWLockState::Unlocked)
			{
				Unlock();
			}
		}

		void ReadLock(void)
		{
			if (state_ != ScopedRWLockState::Unlocked)
			{
				assert(!"[ScopedRWLock::ReadLock()] state_ must be ScopedRWLockState::Unlocked.");
				throw "[ScopedRWLock::ReadLock()] state_ must be ScopedRWLockState::Unlocked.";
			}

			mutex_.ReadLock();
			state_ = ScopedRWLockState::ReadLocked;
		}
		void WriteLock(void)
		{
			if (state_ != ScopedRWLockState::Unlocked)
			{
				assert(!"[ScopedRWLock::WriteLock()] state_ must be ScopedRWLockState::Unlocked.");
				throw "[ScopedRWLock::WriteLock()] state_ must be ScopedRWLockState::Unlocked.";
			}

			mutex_.WriteLock();
			state_ = ScopedRWLockState::WriteLocked;
		}
		void Unlock(void)
		{
			if (state_ == ScopedRWLockState::Unlocked)
			{
				assert(!"[ScopedRWLock::Unlock()] state_ must not be ScopedRWLockState::Unlocked.");
				throw "[ScopedRWLock::Unlock()] state_ must not be ScopedRWLockState::Unlocked.";
			}

			if (state_ == ScopedRWLockState::ReadLocked)
			{
				mutex_.ReadUnlock();
			}
			else if (state_ == ScopedRWLockState::WriteLocked)
			{
				mutex_.WriteUnlock();
			}
		}

		bool IsLocked(void) const
		{
			return state_ != ScopedRWLockState::Unlocked;
		}
		bool IsReadLocked(void) const
		{
			return state_ == ScopedRWLockState::ReadLocked;
		}
		bool IsWriteLocked(void) const
		{
			return state_ == ScopedRWLockState::WriteLocked;
		}

		ScopedRWLockState::TRWLockState GetState(void) const
		{
			return state_;
		}
	};

	//typedef ScopedRWLock<jCriticalSectionRW> RWCSLock;
}//namespace nMech


#endif // __jSyncObject_header__


