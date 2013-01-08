// AqCommon.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "TestCommon.h"
#include "base/jFileDebugger.h"

#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

AQ_SERVER_LIB_API jTestCommon g_jTestCommon;


AQ_SERVER_LIB_API void init_common_AQ()
{
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

