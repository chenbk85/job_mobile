#include "StdAfx.h"
#include "csv_loader.h"
#include "interface/jILog.h"
#include "common_ToString.h"

namespace nMech
{

#ifdef __jINet_OGS_header__
	jNET_COMMON_LIB_API void jDebugPrint(tcstr szName, nNET::jIP_Address &msg)
	{
		name_t buf;
		jLOG(_T("%s : %s") , szName, nInterface::g_pjINet_OGS->GetUtil()->Addr2String(msg,buf));
	}
#endif

}//namespace nDebug
