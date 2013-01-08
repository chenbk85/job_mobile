// dllmain.cpp : DLL 응용 프로그램의 진입점을 정의합니다.
#include "stdafx.h"
#include "interface/jISystemPlugIn.h"
//#include "header/jBoost.h"
#include <boost/bind.hpp>

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
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

extern "C"
{
	__declspec(dllexport) void* jCreateInterface(jIE* pE)
	{
		nInterface::g_pjIOrb = &g_jOrb;
		g_jOrb._Create(pE);
		if(pE->GetAttrVar(jS(AUTO_START))->Get_bool() )
		{
			cstr szSERVICE_REQUEST_LIST = pE->GetAttr(jS(SERVICE_REQUEST_LIST));
			cstr szSERVICE_PROVIDE = pE->GetAttr(jS(SERVICE_PROVIDE));
			g_jOrb.Start(jIOrb_system_callback,szSERVICE_REQUEST_LIST,szSERVICE_PROVIDE);
		}

		jSystemPlugIn_func fn;
		fn.m_SetLocalWnd= boost::bind(&jOrb::SetLocalWnd , &g_jOrb,jBOOST__PLACEHODER_1 );
		//fn.m_Close = bind(&jOrb::Close , &g_jOrb);
		Get_jISystemPlugIn()->Regist(nInterface::g_pjIOrb,&fn );


		return nInterface::g_pjIOrb;
	}
	__declspec(dllexport) void jDeleteInterface()
	{
		GetjILog()->SetPrinter(0);
		g_jOrb.DisconnectAll();
		g_jOrb._Delete();
		nInterface::g_pjIOrb=0;
	}
	__declspec(dllexport) acstr jGetModuleOwnerName()
	{
		return "icandoit";
	}

}
