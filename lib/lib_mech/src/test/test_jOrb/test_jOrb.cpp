// test_jOrb.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//
#include "stdafx.h"
#include "conio.h"
#include "common/jCommon.h"
#include "common/jInit.h"
using namespace nMech;
#include "interface/jIOrb.h"
#include "interface/jIWinUtil.h"
#include "interface/jIConsoleCmd.h"

//	test_jOrb.exe app_nic_name:jOrbClient
//	test_jOrb.exe app_nic_name:jOrbTool 
#if 0

static bool console_parser(cstr sz)
{
	jt_sprintf(_T("cmd : %s\n"),sz);
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	jID* pD = GetjIXml()->Load(_T("gui\\test\\asdf.xml"));
	if(pD)pD->DebugPrint(true);
	jt_printf(_T("하하하"));
	//GetjILog()->SetFileName(logFilePath);

	nCONSOLE::Get_jIConsoleCmd()->Regist_ConsoleParser(g_ExeEnv.m_szAppNic , console_parser );
	jMech_Init(true);
	nUtil::jIWinUtil* pjIWinUtil= jCREATE_INTERFACE(nMech::nUtil::jIWinUtil);
	pjIWinUtil->LoadConsolePos(g_ExeEnv.m_szAppNic);
	if(!nInterface::g_pjIOrb)
	{
		jWARN(_T("jOrb.dll을 포함하세요"));
		jMech_Close();
		return 0;
	}
	//if(nInterface::g_pjIOrb)nInterface::g_pjIOrb->Start(jIOrb_system_callback,_T("ORB_ConsoleMonitor;ORB_ToolGui"),NULL);

	char ch;
	do
	{
		ch = _getch();
		jLOG(_T("%c"),ch);
	} while( ch != 27 );	
	pjIWinUtil->SaveConsolePos(g_ExeEnv.m_szAppNic);
	jMech_Close();
	return 0;
}

jORB_HANDLER(ORB_ConsoleMonitor,H_SEND_LOG)
{
	std::pair<tcstr,bool> *arg = (std::pair<tcstr,bool> *)m_peArg;
	jt_printf(_T("%s"), arg->first);

}
#endif