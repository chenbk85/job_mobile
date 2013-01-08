// nUtil.cpp : DLL ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "jUtil.h"
#include "base/jXmlDictionary.h"
#include "interface/xml/jIXml.h"
#include "header/jMemoryChunk.h"
#include "util/jRegistry.h"
#include "interface/net/jINet.h"
#include "Interface/jIConsoleCmd.h"
using namespace nMech;
namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(jUtil);
	namespace nUtil
	{
		HMODULE gDLLHandle = NULL;
	}
}
using namespace nMech::nUtil;

volatile float __aaa;


BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	gDLLHandle = (HMODULE)hModule;
	__aaa = 0; //���� ����������.

	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}
#define USE_NOT_AUTO_CMD

namespace nMech
{
	bool util_process_kill(const std::vector<std::tstring>& arg);
	namespace nCONSOLE
	{
		namespace nIMPL
		{
			extern bool net_configs(const std::vector<std::tstring>& arg);
			extern bool net_start(const std::vector<std::tstring>& arg);
			extern bool net_stop(const std::vector<std::tstring>& arg);
			extern bool con_clear_cmd(const std::vector<std::tstring>& arg);


			void Init_console_cmd()
			{
				jCC(net,configs,0,"�ε��� jConsoleDLL_Net��� ����Ʈ ���.","");
				jCC(net,start,0,"�ε��� jConsoleDLL_Net��⿡�� ��Ʈ������� ���� �Ѵ�.","<net_config_node>");
				jCC(net,stop,0,"�ε��� jConsoleDLL_Net��⿡�� ��Ʈ������� �����Ѵ�.","<net_config_node> [bool:�������]");
				jCC(con,clear_cmd,0,"��ɸ���Ʈ���� �ʱ�ȭ �Ѵ�." ,"");
				jCC(util,process_kill,0,"kill process","<pid | process_name> [wait_time]");
			}
		}
	}
}

JUTIL_API void jUtil_Create()
{
	nCONSOLE::nIMPL::Init_console_cmd();

	int i=0;
	++i;


}

using namespace nMech;
JUTIL_API tcstr Get_Uniq_AppNicName()
{
	static std::tstring s_UniqNicName;
	if(!s_UniqNicName.size())
	{
		nMech::nUtil::CRegistry reg;
		reg.Open(_T("SOFTWARE\\jMech"),HKEY_LOCAL_MACHINE);
		if(!reg[_T("Uniq_AppNicName")].Exists()) 
			reg[_T("Uniq_AppNicName")] = (int)0;
		int name_number = reg[_T("Uniq_AppNicName")];
		if(name_number>99999)
		{
			name_number =0;
		}
		fname_t buf;
		jt_sprintf(buf, _T("%s_%d"),g_ExeEnv.m_szAppNic,name_number);
		s_UniqNicName = buf;
		reg[_T("Uniq_AppNicName")] = name_number+1;

	}
	return s_UniqNicName.c_str();
}
