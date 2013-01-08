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

#include "interface/net/jDebugPrint.h"
#include "jDebugPrint_TCommonClient.h"

namespace nMech
{
	inline void jDebugPrint(nMech::tcstr szName, jServerUserID &msg)	{		jLOG1(_T("%s : (sid=%d uid=%d)") , szName,msg.sid, msg.uid);	}
	inline void jDebugPrint(tcstr szName, db_uid_type& id)	{		jLOG1(_T("%s : %I64") , szName,id.m_db_id);	}

	inline void jDebugPrint(tcstr szName, EUserGPS msg)	{		jLOG1(_T("%s : %s") , szName,ToString(msg));	}
	inline void jDebugPrint(tcstr szName, std::vector<EUserGPS>& msg)	{		jLOG1(_T("%s.size()=%d") , szName,msg.size());	}

	inline void jDebugPrint(tcstr szName, player_id_t id)	{		jLOG1(_T("%s : %I64d:%d") , szName,id.m_id,id.m_dc_handle);	}
	inline void jDebugPrint(tcstr szName, std::vector<player_id_t> &msg)	{		jLOG1(_T("%s.size()=%d") , szName,msg.size());	}


	inline void jDebugPrint(tcstr szName, jNoticeInfo&	msg){}

	inline void jDebugPrint(tcstr szName, jChannelPlayerCookie &msg){}
	inline void jDebugPrint(tcstr szName, std::vector<jChannelPlayerCookie> &msg){}

	inline void jDebugPrint(tcstr szName, jWorldServerInfo& msg){}
	inline void jDebugPrint(tcstr szName, vector<jWorldServerInfo>& msg){}

#ifdef __jINet_OGS_header__
	inline void jDebugPrint(tcstr szName, nNET::jIP_Address &msg)
	{
		tname1024_t buf;
		jLOG1(_T("%s : %s") , szName, nInterface::g_pjINet_OGS->GetUtil()->Addr2String(msg,buf));
	}
#endif

	inline void jDebugPrint(tcstr szName, jErrorInfo& msg)
	{
		tname1024_t buf_e;
		msg.e.ToString(buf_e);
		tname256_t buf_pid;

		jLOG1(_T("%s : pid=%s action=%d e=[%s] msg=[%s]"),szName,ToString(msg.pid,buf_pid) ,msg.eAction , buf_e ,jT(msg.sFunction) );
	}


	
}//namespace nDebug

#endif
