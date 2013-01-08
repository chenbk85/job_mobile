/* file : MultiThreadSync.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:50:41
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __MultiThreadSync_header__
#define __MultiThreadSync_header__
#pragma once

#include "header/jCriticalSection.h"

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{

			template <class T>
			class CMultiThreadSync2
			{
				friend class CThreadSync2;
			public:
				class CThreadSync2
				{
				public:
					CThreadSync2(VOID)
					{
						T::mSync2.Lock();
					}

					~CThreadSync2(VOID)
					{
						T::mSync2.UnLock();
					}
				};

			private:
				static ::nMech::nUtil::jCriticalSection mSync2;
			};

			template <class T>
				nMech::nUtil::jCriticalSection CMultiThreadSync2<T>::mSync2;


			template <class T>
			class CMultiThreadSync
			{
				friend class CThreadSync;
			public:
				class CThreadSync
				{
				private:
					const CMultiThreadSync* mMSync;

				public:
					CThreadSync(const CMultiThreadSync& MSync) : mMSync(&MSync)
					{
						mMSync->mSync.Lock();
					}

					~CThreadSync(VOID)
					{
						mMSync->mSync.UnLock();
					}		
				};

			private:
				mutable nMech::nUtil::jCriticalSection mSync;
			};

#define Sync Sync(*this)

		}

	}

}


#endif // __MultiThreadSync_header__
