/* file : jRDTSC.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-02 23:40:38
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jRDTSC_header__
#define __jRDTSC_header__
#pragma once

#ifndef RDTSC
#ifdef DEF_WINDOWS
#ifndef _WIN64
	#define RDTSC(low) { \
		__asm __emit 0fh \
		__asm __emit 031h \
		__asm mov low, eax			}

	#define RDTSC_EX( low , high ) { \
		__asm __emit 0fh \
		__asm __emit 031h \
		__asm mov low, eax \
		__asm mov high, edx		}

	#define CUPID { __asm  __emit 0fh  __asm  __emit 0a2h }
	#define RDTSC_GET(s,e)  (e - s) 
	#define RDTSC_EX_GET(s,e)  ((*(int64*)&e - *(int64*)&s) )

#else
	#include <intrin.h>
	#pragma intrinsic(__rdtsc)
	#define RDTSC(low) __rdtsc();
	#define RDTSC_EX( low , high )
#endif
#else

#include<sys/time.h>
#include<time.h>
#include<stdio.h>
typedef unsigned long long ticks;

static __inline__ ticks getticks(void)
{
	unsigned a, d;
	asm("cpuid");
	asm volatile("rdtsc" : "=a" (a), "=d" (d));

	return (((ticks)a) | (((ticks)d) << 32));
}
#define RDTSC(low) __rdtsc();

#endif

#endif//#ifndef RDTSC


namespace nMech
{

	namespace nTIME
	{
		//http://www.npteam.net/380
		inline unsigned __int64 getMisteryCount() 
		{ 
#ifndef _WIN64
			__asm  
			{   
				mov    edx,dword ptr ds:[7FFE000Ch]
				mov    eax,dword ptr ds:[7FFE0008h] 
			} 
#else
			return __rdtsc();		
#endif
		} 
		inline unsigned int getElapsedMilliSecond() 
		{ 
			return static_cast< unsigned int >
				( getMisteryCount()/10000 ); 
		} 
		struct jTimer
		{
			uint64 s,e;
			void start(){s= getMisteryCount();}
			void stop(){e=getMisteryCount();}
			uint64 getClock(){return e-s;}
			uint64 getMilliSecond(){ return getClock()/10000;}
		};

	}
}


#endif // __jRDTSC_header__
