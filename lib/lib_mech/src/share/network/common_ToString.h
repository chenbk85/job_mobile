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

#include "interface/net/net_ToString.h"

namespace nMech
{
	inline void jDebugPrint(nMech::tcstr szName, jServerUserID &msg)	{		GetjILog()->Log(_T("%s : (sid=%d uid=%d)") , szName,msg.sid, msg.uid);	}
	inline void jDebugPrint(tcstr szName, db_uid_type& id)	{		GetjILog()->Log(_T("%s : %I64") , szName,id.m_db_id);	}

	inline void jDebugPrint(tcstr szName, EUserGPS msg)	{		GetjILog()->Log(_T("%s : %s") , szName,ToString(msg));	}
	inline void jDebugPrint(tcstr szName, std::vector<EUserGPS>& msg)	{		GetjILog()->Log(_T("%s.size()=%d") , szName,msg.size());	}

	inline void jDebugPrint(tcstr szName, userid_t id)	{		GetjILog()->Log(_T("%s : %I64d:%d") , szName,id.m_id,id.m_dc_handle);	}
	inline void jDebugPrint(tcstr szName, std::vector<userid_t> &msg)	{		GetjILog()->Log(_T("%s.size()=%d") , szName,msg.size());	}


#ifdef __jINet_OGS_header__
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, nNET::jIP_Address &msg);
#endif
	inline void jDebugPrint(tcstr szName, jNoticeInfo&	msg){}

	inline void jDebugPrint(tcstr szName, jTownPlayerCookie &msg){}
	inline void jDebugPrint(tcstr szName, std::vector<jTownPlayerCookie> &msg){}

	inline void jDebugPrint(tcstr szName, jWorldServerInfo& msg){}
	inline void jDebugPrint(tcstr szName, vector<jWorldServerInfo>& msg){}

	
}//namespace nDebug

#endif
