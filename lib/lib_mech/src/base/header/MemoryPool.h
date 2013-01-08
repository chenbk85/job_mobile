/* file : MemoryPool.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:52:17
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __MemoryPool_header__
#define __MemoryPool_header__
#pragma once

#include "header/MultiThreadSync.h"

namespace nMech
{
	namespace nNET
	{
		namespace nUTIL
		{

			template <class T, int ALLOC_BLOCK_SIZE = 50>
			class CMemoryPool : public CMultiThreadSync2<T>
			{
			public:
				static VOID* operator new(std::size_t allocLength)
				{
					CThreadSync2 Sync2;

					assert(sizeof(T) == allocLength);
					assert(sizeof(T) >= sizeof(UCHAR*));

					if (!mFreePointer)
						allocBlock();

					UCHAR *ReturnPointer = mFreePointer;
					mFreePointer = *reinterpret_cast<UCHAR**>(ReturnPointer);

					return ReturnPointer;
				}

				static VOID	operator delete(VOID* deletePointer)
				{
					CThreadSync2 Sync2;

					*reinterpret_cast<UCHAR**>(deletePointer) = mFreePointer;
					mFreePointer = static_cast<UCHAR*>(deletePointer);
				}

			private:
				static VOID	allocBlock()
				{
					mFreePointer		= new UCHAR[sizeof(T) * ALLOC_BLOCK_SIZE];

					UCHAR **Current = reinterpret_cast<UCHAR **>(mFreePointer);
					UCHAR *Next		= mFreePointer;

					for (INT i=0;i<ALLOC_BLOCK_SIZE-1;++i)
					{
						Next		+= sizeof(T);
						*Current	= Next;
						Current		= reinterpret_cast<UCHAR**>(Next);
					}

					*Current = 0;
				}

			private:
				static UCHAR	*mFreePointer;

			protected:
				~CMemoryPool()
				{
				}
			};

			template <class T, int ALLOC_BLOCK_SIZE>
				UCHAR* CMemoryPool<T, ALLOC_BLOCK_SIZE>::mFreePointer;

		}
	}
}

#endif // __MemoryPool_header__
