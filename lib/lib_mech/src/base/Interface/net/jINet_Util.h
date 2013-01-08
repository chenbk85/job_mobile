/* file : jINet_OGS_Util.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-08-20 22:15:51
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jINet_OGS_Util_header__
#define __jINet_OGS_Util_header__
#pragma once

namespace nMech
{
	namespace nNET
	{

	#define jINTERFACE_jINet_Util(x) public:	\
		\
		/* ip -> "127.0.0.1:2344" */\
		virtual tcstr Addr2String(jIP_Address& pIP,tname_t buf) ##x \
		\
		/* "127.0.0.1:2344" -> ip */\
		virtual jIP_Address String2Addr(tcstr szIP) ##x \
		virtual jIP_Address String2Addr(tcstr szIP,unsigned short port)##x \
		virtual bool isPrivateIP(acstr strIp) ##x \
		virtual acstr GetPublicIP(aname32_t szBuf)##x \
		virtual acstr GetPrivateIP(aname32_t szBuf)##x \

		jINTERFACE_END(jINet_Util);
	}
}

#include "interface/net/jNet_util.h"


#endif // __jINet_OGS_Util_header__
