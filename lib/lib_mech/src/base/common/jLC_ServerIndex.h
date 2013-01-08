/* file : jLC_ServerIndex.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2006-01-05 12:20:04
title : 
desc : 

*/

#ifndef __jLC_ServerIndex_header__
#define __jLC_ServerIndex_header__
#pragma once


// assert(INT_MAX == 2147483647)
#ifdef INT_MAX
#define INT_MAX  2147483647
#endif
const int LC_SERVER_INDEX_MAX = INT_MAX; 
const int LC_SERVER_INDEX_GAP = 500000000-1;
enum EServerIndex
{
	EServerIndex_BEGIN		= 0,

	ePLAYER_INDEX_BEGIN		= EServerIndex_BEGIN,
	ePLAYER_INDEX_END			= ePLAYER_INDEX_BEGIN + 10000 ,//1만개 LC_SERVER_INDEX_GAP,

	eMONSTER_INDEX_BEGIN = ePLAYER_INDEX_END + 1,
	eMONSTER_INDEX_END		=	eMONSTER_INDEX_BEGIN + 100000,// 100만개 LC_SERVER_INDEX_GAP,

	eITEM_INDEX_BEGIN = eMONSTER_INDEX_END +1,
	eITEM_INDEX_END = eITEM_INDEX_BEGIN + 100000000 ,// 1억개 LC_SERVER_INDEX_GAP,

	eETC_INDEX_BEGIN = eITEM_INDEX_END+1,
	eETC_INDEX_END = eETC_INDEX_BEGIN + LC_SERVER_INDEX_GAP,

	EServerIndex_END = INT_MAX //2147483647
};

typedef int ServerIndex_t;
typedef int jPlayerID_t;
typedef int jMonsterID_t;
typedef int jItemID_t;

#endif // __jLC_ServerIndex_header__
