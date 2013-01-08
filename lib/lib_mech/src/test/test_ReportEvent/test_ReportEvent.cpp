#include <stdafx.h>
#include "header/jReportEvent_header.h"
#include "interface/jIReportEvent.h"
using namespace nMech;

void __cdecl wmain(int argc, LPWSTR *argv)
{
	jMech_Init();

	tcstr szAppName = jS(jServer);               // The event log name.
	tcstr szSourceName = jS(jCentral);  // The event source name.

	nLOG::jIReportEvent* pjIRE = jCREATE_INTERFACE(nMech::nLOG::jIReportEvent);
	pjIRE->Init(szAppName,szSourceName,1);

	nLOG::jIReportEvent* pjIRE1 = jCREATE_INTERFACE(nMech::nLOG::jIReportEvent);
	pjIRE1->Init(szAppName,jS(TESTEVENT),1);

	pjIRE->LaunchViewer();
	pjIRE->Write(nLOG::eEL_ERROR, 1, EVT_NORMAL ,_T("하하하"));
	pjIRE->Write(nLOG::eEL_ERROR, 1, _T("zzz %s = %u"),_T("ㅎ호호"),1234);

	
	GetjILog()->SetReportEvent(0,pjIRE);
	GetjILog()->SetReportEvent(jS(TESTEVENT),pjIRE1);

	jLOG_T("{} %s=%d",jS(NULL), 1234);
	jLOG_T("{TESTEVENT} %s=%d",jS(NULL), 2234);
	jWARN_T("{WARNEVENT} %s = %d",jS(TEST), 9887);
	
	jIVar* pV = jGV(jILog,ERROR_CHECK_TYPE);
	pV->Set_cstr(jS(NULL));
	jERROR_T("{TESTEVENTASDFASDLKAWEJFOIQWEJASDLKFFWOEI} %s=%d",jS(lksadf),19823);

	pjIRE->Release(); // 종료시 자동으로 릴리즈됨.
	pjIRE1->Release();

	jMech_Close();

	return;
}
