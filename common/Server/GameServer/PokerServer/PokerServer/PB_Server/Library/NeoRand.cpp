#include "stdafx.h"
#if !defined(DEF_LINUX)
#include <windows.h>
#endif
#include "NeoRand.h"
#include <time.h>

#include <stdlib.h>

//define NeoRand class static variable
unsigned int	NeoRand::_nIndex=0;
long			NeoRand::_pool[3]= {0x00,};

ptrdiff_t  NeoRand::operator() (ptrdiff_t max)
{		
	// choose random_pool as _nIndex
	unsigned int nIndex=++_nIndex%3;
    	
	// update random_pool. X'= (aX+b)%m  see CRT's rand.c file	
	return static_cast<ptrdiff_t> 
		((((_pool[nIndex]=_pool[nIndex] * 214013L + 2531011L) >> 16) & 0x7fff) % max);
}


// add entropy data into _pool
NeoRand::NeoRand()
{	
	/*
	long garbage[3];		 // not initialize because we want stack garbage memory data
	long *entropy=garbage; // indirectly define entropy variable because compiler_warning 4700
	
	// get entropy with tick count
	//entropy[0] ^= static_cast<long>(::timeGetTime());
	entropy[0] ^= static_cast<long>(time(0));
	
	// get entropy with GUID
	GUID guid;
	::CoCreateGuid(&guid);
	long* p=reinterpret_cast<long*>(&guid);
	for(int i=0; i<sizeof(guid)/sizeof(long) ; ++i)
		entropy[1] ^= p[i];
	
	// get entropy with ThreadTimes
	FILETIME ft[4];
	::GetThreadTimes(GetCurrentThread(),ft, ft+1,ft+2,ft+3);
	p=reinterpret_cast<long*>(ft);
	for(int i=0; i<sizeof(ft)/sizeof(long) ; ++i)
		entropy[2] ^= p[i];

	// mix entropy and add into entropy pool
	unsigned int nIndex=++_nIndex%3;
	_pool[nIndex++%3]+=(entropy[0]^entropy[1]);
	_pool[nIndex++%3]+=(entropy[1]^entropy[2]);
	_pool[nIndex++%3]+=(entropy[2]^entropy[0]);
	*/
}