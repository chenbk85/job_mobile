#include "StdAfx.h"
#include "interface/jILog.h"
#include "server_ToString.h"

namespace nMech
{
	using namespace nMech;
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, jError &msg)
	{
		fname_t buf;
		msg.ToString(buf);
		GetjILog()->LogPlus(_T("%s : (%s)") , szName,buf);
	}

}//namespace nDebug
