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

#include "../TCommonClient/jDebugPrint_TCommonClient.h"

namespace nMech
{
	inline  void jDebugPrint(nMech::tcstr szName, jError &msg)
	{
		tname1024_t buf;
		msg.ToString(buf);
		jLOG1(_T("%s : (%s)") , szName,buf);
	}
	inline void jDebugPrint(nMech::tcstr szName, jServerInfo &msg)
	{
		tname1024_t buf;
		jLOG("%s : %s" ,szName,ToString(&msg,buf));
	}
	inline void jDebugPrint(nMech::tcstr szName, std::vector<jServerInfo>&msg)
	{
		tname1024_t buf;

		jLOG("%s.size()=%d" , szName , msg.size() );

		for( size_t i =0 ; i< msg.size() ; ++i)
		{
			jLOG("\t%s",ToString(&msg[i],buf));
		}
	}

}//namespace nDebug

#endif
