/* file : jRandom.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-06-23 23:42:51

title : 
desc : 

*/

#ifndef __jRandom_header__
#define __jRandom_header__
#pragma once


namespace nMech
{
	int	random_my(int nMin, int nMax);
	int random_api(int min,int max);
	int random_boost(int min,int max);
	typedef int	GetRandomValue_t(int nMin, int nMax);
	void test_random(GetRandomValue_t* pRandom, const char* tag, int SleepTime);


}


#endif // __jRandom_header__
