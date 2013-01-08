/* file : net_StringID.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-07-29 14:29:03
comp.: actoz.com
title : 
desc : 

*/

#ifndef __net_StringID_header__
#define __net_StringID_header__
#pragma once


#ifdef jError_USING_DEV_MODE


#else //jError_USING_DEV_MODE

#include "../TCommonClient/excel/StringID_ClientResult.h"
#include "../TCommonClient/excel/StringID_ServerResult.h"

#define for_each_net_StringID(X)\
	X(StringID_ClientResult)\
	X(StringID_ServerResult)\


typedef nMech::StringID_ClientResult CR_t;
typedef nMech::StringID_ServerResult SR_t;

namespace nMech
{
	inline bool operator ==(jError & e, SR_t::EStringID id)
	{
		return (e.iServer == (uint16)id);
	}
	inline bool operator ==(jError & e, CR_t::EStringID id)
	{
		return (e.iClient== (uint16)id);
	}
}
#endif //jError_USING_DEV_MODE

#endif // __net_StringID_header__
