/* 
	filename:	jCriticalSection.h
	coder	:	Cho Wook Rea (chowookrea@hotmail)(icq:74456993) 
	comp.	:	-MAEUMNET-
	compiler:	vc++ 6.0
	date	:	2003-12-23¿ÀÈÄ 2:00:23
	title	:	
*/


#ifndef __jCriticalSection_h__
#define __jCriticalSection_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

#if _WIN32_WINNT < 0x0500
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0501  
#endif

#include <assert.h>
namespace nMech
{
//	JBASE_API void jInitializeCriticalSectionAndSpinCount(CRITICAL_SECTION&);
	namespace nUtil
	{
		class jCriticalSection
		{
			CRITICAL_SECTION mSync;
		public:
			jCriticalSection(const jCriticalSection& a)
			{
				//jInitializeCriticalSectionAndSpinCount(mSync);
				ULONG lSpinCount = 2000;
				InitializeCriticalSectionAndSpinCount(&mSync, lSpinCount);

			}
			const jCriticalSection& operator = (const jCriticalSection& d)
			{
				assert(0 &&"const jCriticalSection& operator = (const jCriticalSection& d)");
				return *this;
			}

			jCriticalSection()
			{
				//jInitializeCriticalSectionAndSpinCount(mSync);

				ULONG lSpinCount = 2000;
				InitializeCriticalSectionAndSpinCount(&mSync, lSpinCount);

			}

#if (_WIN32_WINNT >= 0x0400)
			bool TryLock()	{ return TryEnterCriticalSection(&mSync) != 0; }
#endif
			void Lock()
			{
				EnterCriticalSection(&mSync);
			}
			void UnLock()
			{
				LeaveCriticalSection(&mSync );
			}
			~jCriticalSection()
			{
				DeleteCriticalSection(&mSync);
			}
			class Auto
			{
				jCriticalSection* m_cs;
			public:
				Auto(jCriticalSection*cs) :m_cs(cs)	{	cs->Lock();	}
				~Auto(){m_cs->UnLock();}
			};
		};

	}//nHEADER

}



#define jAUTO_LOCK_CS(x) nMech::nUtil::jCriticalSection::Auto UIDEN(_a)(&x);
#define jAUTO_LOCK_CS1(x) nMech::nUtil::jCriticalSection::Auto _a(&x);

#endif //__jCriticalSection_h__
