
#include "stdafx.h"

jINetClient* g_Net=0;

void Init_net()
{
	using namespace nMech;
	
	HMODULE hDLL =::LoadLibrary( _T("jNetDLL_Loader.dll"));
	typedef void* jCreateInterface_t(tcstr logFilePath, tcstr dllName,tcstr netConfigXml,tcstr netConfigXmlNode);
	jCreateInterface_t *pjCreateInterface= (jCreateInterface_t*)::GetProcAddress(hDLL, "jCreateInterface");

	//typedef void jDeleteInterface_t();
	//jDeleteInterface_t *pjDeleteInterface= (jDeleteInterface_t*)::GetProcAddress(hDLL, "jDeleteInterface");

	g_Net = (jINetClient*)pjCreateInterface(_T("C:\\Temp\\client")
		,_T("TestClient.dll")
		,_T("xml\\net\\AqTestServer_NetConfig.xml")
		,_T("TestClient"));
	void Set_CallBack();Set_CallBack();
}

