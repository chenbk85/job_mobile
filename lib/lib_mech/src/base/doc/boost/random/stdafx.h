// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>



// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#include "d3dx9math.h"
#include <map>
#include <set>
#include <assert.h>
#include <Mmsystem.h>
#include <time.h>
#include <random>
#include <boost/random.hpp>
#include <ctime>


#define jUSE_BOOST
#ifdef jUSE_BOOST
//Z:\lib\boost\boost_1_45_0
//Z:\lib\boost\boost_1_45_0\Win32
#include <boost/random.hpp>
#endif



using namespace std;
#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0])-1)
#define ArraySize(a) (sizeof(a)/sizeof(a[0]));
#ifndef RDTSC
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

#define RDTSC_GET(s,e)  (e - s) 
#define RDTSC_EX_GET(s,e)  ((*(int64*)&e - *(int64*)&s) )

#else
#include <intrin.h>
#pragma intrinsic(__rdtsc)
//unsigned __int64 low;
#define RDTSC(low) low =__rdtsc();
#define RDTSC_EX( low , high )
#endif
#endif



#ifndef jLIST_TYPEDEF_set
#define jLIST_TYPEDEF_set(x,var) typedef std::set<x> 	var##_t; typedef x var##_vt; typedef var##_t::iterator var##_it; var##_t var;
#endif


#define	_pi			   3.1415926535f 
#define	_pi_2_angle(a) (((double)(a) * 360.0f) / (2.0f * _pi))


#include "test.h"
