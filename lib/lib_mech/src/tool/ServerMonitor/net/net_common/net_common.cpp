// AqCommon.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "net_Common.h"
#include "base/jFileDebugger.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

AQ_SERVER_LIB_API jTestCommon g_jTestCommon;
AQ_SERVER_LIB_API jIE* g_peServerExeList=0;

void SocketDebugPrint_SendFile(nNET::jIPacketSocket_IOCP* pS,nNET::SocketDebugPrint_SendFile_Info* info)
{
	static int i=0;
	++i;
	if((i%10)==0)
		jLOG_T("%d:%d,size=%d(%d),%s",info->cookie,info->remainFileCount,info->iFileSize,info->iCurrSize,info->szFile);
}

AQ_SERVER_LIB_API void init_common_AQ()
{
	g_pjINet_OGS->SetDebugger_SendFile(SocketDebugPrint_SendFile);
	printf(" ");
}

namespace nMech
{
#ifndef jError_USING_DEV_MODE
	jError::server_tcstr jError::ToStringS()
	{
		jEnumString* pErr = StringID_ServerResult::Get(iServer);
		if(pErr)
			return pErr->m_szName;

		return _T("");
	}

	jError::client_tcstr jError::ToStringC()
	{
		jEnumString* pErr = StringID_ClientResult::Get(iClient);
		if(pErr)
			return pErr->m_szName;

		return _T("");
	}

	std::pair<jError::server_tcstr ,jError::client_tcstr> jError::ToString(fname_t buf)
	{
		tcstr s=_T("?"),c=_T("?");
		jEnumString* pErr = StringID_ServerResult::Get(iServer);
		if(pErr)
			s=pErr->m_szName;

		pErr = StringID_ClientResult::Get(iClient);
		if(pErr)
			c=pErr->m_szName;

		if(buf)
		{
			const int tot = sizeof(fname_t)/sizeof(TCHAR)-1;
			jt_snprintf(buf, tot, _T("%s : %s"),s,c);
			buf[tot] =0;
		}
		return std::make_pair(s,c);
	}
#endif

}

acstr jTestCommon::jConvertToHostIP(aname32_t szIP)
{
	if(!ja_strcmp(szIP , "PRIVATE_IP") )
		return g_pjINet_OGS->GetUtil()->GetPrivateIP(szIP);
	else if(ja_strcmp(szIP,"PUBLIC_IP") )
		return g_pjINet_OGS->GetUtil()->GetPublicIP(szIP);
	return szIP;
}



AQ_SERVER_LIB_API bool CheckSeverType(tcstr sz)
{
	jIE* pE = g_peServerExeList->Find(sz,1);
	if(!pE) return false;
	jIVar* pV = pE->GetAttrVar(jS(ENABLE));
	if(!pV || pV->Get_bool()==true) return true;
	return false;
}

AQ_SERVER_LIB_API tcstr ToServerTypeHelp(tcstr szServerType)
{
	jIE* pE = g_peServerExeList->Find(szServerType);
	jRETURN_ret(jS(NULL), pE);
	jASSERT(pE->GetVar()->IsType(jIVar::EDcstr));
	return pE->Get_cstr();
}