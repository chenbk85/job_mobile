/*
file : CE_CSV_type.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-09-03 17:56:06
comp.: jgame.co.kr
title : 
desc : 
*/

#ifndef __DB_common_ToString_233234sdfsadfINT__
#define __DB_common_ToString_233234sdfsadfINT__
#include "csv_loader.h"

#include "interface/net/jDebugPrint.h"

namespace nMech
{
	inline void jDebugPrint(tcstr szName, EUserGPS msg)	{		jLOG(_T("%s : %s") , szName,ToString(msg));	}
	inline void jDebugPrint(tcstr szName, std::vector<EUserGPS>& msg)	{		jLOG(_T("%s.size()=%d") , szName,msg.size());	}


#ifdef __jINet_OGS_header__
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, nNET::jIP_Address &msg);
#endif

	
}//namespace nDebug

#endif
