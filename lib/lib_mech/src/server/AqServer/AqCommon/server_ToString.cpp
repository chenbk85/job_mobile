#include "StdAfx.h"
#include "interface/jILog.h"
#include "server_ToString.h"

namespace nMech
{
	using namespace nMech;
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, jServerInfoBase &msg)
	{
	}

	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, jServerInfo &msg)
	{
	};
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, jError &msg)
	{
		fname_t buf;
		msg.ToString(buf);
		GetjILog()->Log(_T("%s : (%s)") , szName,buf);
	}
	jNET_COMMON_LIB_API void jDebugPrint(tcstr szName, jServerUserCountInfo&msg){}
	jNET_COMMON_LIB_API void jDebugPrint(tcstr szName, std::vector<jServerUserCountInfo>&msg){GetjILog()->Log(_T("%s.size()=%d") , szName,msg.size());}
	jNET_COMMON_LIB_API void jDebugPrint(nMech::tcstr szName, std::vector<jServerInfo>&msg){GetjILog()->Log(_T("%s.size()=%d") , szName,msg.size());}

}//namespace nDebug
