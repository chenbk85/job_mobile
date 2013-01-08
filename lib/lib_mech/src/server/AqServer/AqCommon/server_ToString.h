/*
file : CE_CSV_type.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-03 17:56:06
comp.: jgame.co.kr
title : 
desc : 
*/

#ifndef __server_toString343_PR234sdfsadfINT__
#define __server_toString343_PR234sdfsadfINT__

#include "network/common_ToString.h"

namespace nMech
{
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, jServerInfoBase &msg);
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, jServerInfo &msg);
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, std::vector<jServerInfo> &msg);
	

	jNET_COMMON_LIB_API void jDebugPrint(tcstr szName, jServerUserCountInfo&	msg);
	jNET_COMMON_LIB_API void jDebugPrint(tcstr szName, std::vector<jServerUserCountInfo>&	msg);
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, jError &msg);

}//namespace nDebug

#endif
