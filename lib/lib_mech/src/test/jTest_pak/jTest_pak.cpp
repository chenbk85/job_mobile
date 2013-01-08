// jTest_pak.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "interface\\jIPak.h"
#include "interface\\jILua.h"
#include "common/jInit.h"

void _jConsolePrinterFunc( cstr szString,bool bAdd )
{
	if(bAdd)
		jt_printf(_T("%s"), szString);
	else
		jt_printf(_T("%s\n"), szString);
}
void _jvsprinter(TCHAR* outBuffer,int i,cstr szFormat, va_list args )
{
	jt_vsnprintf(outBuffer, i,szFormat, args);
}
void a1(cstr szFormat,...)
{
	va_list	ArgList;
TCHAR		szBuffer[1024];
	va_start(ArgList, szFormat);
	_jvsprinter(szBuffer,sizeof(szBuffer), szFormat, ArgList);
	va_end(ArgList);
	jt_printf(szBuffer);
}

// pack_test
int _tmain_pack_test(int argc, _TCHAR* argv[])
{
	GetjILog()->SetPrinter(_jConsolePrinterFunc);
/* *_* by icandoit : 2005-07-09 21:38:35

	cstr szFileName1 = "objects\\characters\\animations\\human_male\\aidle_usaim_loop.gaf";
	//	fp = nInterface::g_pjIPak->FOpen(szFileName1,"r");
	fname_t bufFull;
	cstr szFullPath = nInterface::g_pjIPak->AdjustFileName(szFileName1, bufFull, 0);
	jICachedFileData *pFileData = nInterface::g_pjIPak->GetFileDataI(szFullPath);
	int asdf =0;
	if (pFileData)
		asdf = pFileData->GetUnCompFileSize();

	/* *_* by icandoit : 2005-07-08 15:52:03

	string str = g_ExeEnv.m_szModuleDir;
	_chdir("..");
	GetCurrentDirectory(sizeof(g_ExeEnv.m_szStartDir), g_ExeEnv.m_szStartDir);
	string str1 = g_ExeEnv.m_szStartDir;

	nFileSystem::UFileName fn("xml\\jGame.xml");
	jID* nGLOBAL::g_pDocApp = Getj23IXml()->Load(fn	);
	jInterfaceLorder* g_pInterfaceLoader = new jInterfaceLorder(nGLOBAL::g_pDocApp);
	*/ //*_* by icandoit : 2005-07-08 15:52:07

	fname_t buf12;
	jt_strcpy(buf12, _T("klsdfj2lfjlkdfjlsdjfal;kdsjf"));
	nInterface::g_pjILog->Log(_T("\002ok! %s"), buf12);

	float f1 = 0.23423434234;
	float f2 = 12432136443.2323342;
	a1(_T("\002ok! %s , %f %f"), buf12,f1,f2);
	//nInterface::g_pjILog->Error(TEXT("\002ok! %s , %f %f"), buf12,f1,f2);
	FILE* fp1 = nInterface::g_pjIPak->FOpen("effects\\blood.prt","r");
	if(fp1)
	{
		nInterface::g_pjIPak->FClose(fp1);
	}

	FILE* fp = nInterface::g_pjIPak->FOpen(("gui\\jGui.xml"),"rt");
	if(fp)
	{
		int iLen = nInterface::g_pjIPak->FileLen(fp);
		char* buf = new char[iLen+1];
		buf[iLen]=0;
		nInterface::g_pjIPak->FRead(buf,iLen,1, fp);
#ifdef UNICODE
		wstring str1 = nUNI::mbs_to_wcs(buf);
		jID* pD = GetjIXml()->Load(_T("jTestUnitjGui.xml"), str1.c_str());
#else
		jID* pD = GetjIXml()->Load(_T("jTestUnitjGui.xml"), buf);
#endif
		delete buf;
		pD->DebugPrint(nInterface::g_pjILog);
		nInterface::g_pjIPak->FClose(fp);
	}

	nFileSystem::UFileName fn(_T("gui\\jGui.xml"));
	jID* pD1 = GetjIXml()->Load(fn.buffer);
	if(pD1)
		pD1->DebugPrint(nInterface::g_pjILog);

	nInterface::g_pjILog->Log(_T("\002 ok!"));

	if(nInterface::g_pjILua)
		nInterface::g_pjILua->ExecuteFile("script\\test.lua");

	//delete g_pInterfaceLoader;
	return 0;
}

int _tmain_testXml(int argc, _TCHAR* argv[])
{
	GetjILog()->SetPrinter(_jConsolePrinterFunc);
	nFileSystem::UFileName fn(_T("gui\\gui_var.xml"));
	jID* pD = GetjIXml()->Load(fn.buffer);
	//pD->DebugPrint(nInterface::g_pjILog);

	pD->Find(jS(FILES))->InsertChildElement(jS(asdf));
	pD->Find(jS(FILES))->InsertChildElement(jS(asdf));
	pD->Find(jS(FILES))->InsertChildElement(jS(asdf));
	pD->Find(jS(FILES))->InsertChildElement(jS(asdf));
	pD->Find(jS(FILES))->InsertChildElement(jS(aaa3),3);
	pD->DebugPrint(nInterface::g_pjILog);



	//delete g_pInterfaceLoader;
	return 0;
}

int _tmain_luasinktest(int argc, _TCHAR* argv[])
{
	GetjILog()->SetPrinter(_jConsolePrinterFunc);

	nInterface::g_pjILog->Log(_T("\002 ok!"));
	nInterface::g_pjILua->ExecuteFile(("script\\jTest_jLuaSink.lua"));
	return 0;
}

//--------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
//--------------------------------------------------------------------------
{
	jMech_Init();

	//_tmain_luasinktest(argc,argv);
	_tmain_pack_test(argc,argv);
	jMech_Close();
}
