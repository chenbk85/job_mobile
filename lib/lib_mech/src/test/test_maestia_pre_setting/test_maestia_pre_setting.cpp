// run_by_date.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <windows.h>
#include "stdio.h"
#include <iostream>
using namespace std;
#include "base/jBase.h"
#include "common/jCommon.h"
#include "interface/xml/jIXml.h"
#include "common/jInit.h"
#include "base/uString_stl.h"
using namespace nMech;

static int jCreateProcess1234( TCHAR* szExe ,bool isWait)
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory( &si, sizeof(si) );
	si.cb = sizeof(si);
	ZeroMemory( &pi, sizeof(pi) );
	DWORD exitCode=0;

	// Start the child process. 
	if( !::CreateProcess( NULL, // No module name (use command line). 
		szExe, // Command line. 
		NULL,             // Process handle not inheritable. 
		NULL,             // Thread handle not inheritable. 
		FALSE,            // Set handle inheritance to FALSE. 
		0,                // No creation flags. 
		NULL,             // Use parent's environment block. 
		NULL,             // Use parent's starting directory. 
		&si,              // Pointer to STARTUPINFO structure.
		&pi )             // Pointer to PROCESS_INFORMATION structure.
		) 
	{
		cerr << "Don't create process : " << szExe;
		return 777;
	}
	else
	{
		// Wait until child process exits.
		if(isWait)WaitForSingleObject( pi.hProcess, INFINITE );

		if (GetExitCodeProcess(pi.hProcess, &exitCode))
		{
			// successfully retrieved exit code
		}

		// Close process and thread handles. 
		CloseHandle( pi.hProcess );
		CloseHandle( pi.hThread );
	}
	return exitCode;
}

#define jLAMDA_jxFind_EAC(X,Z) X(cstr,szName) X(cstr ,szAttr) Z(cstr,szContents)
jLAMDA_find_if(jxFind_EAC,jIE*)
{
	if(!it->IsName(szName) )return false;
	jIVar* pV = it->GetAttrVar(szAttr);
	if(!pV) return false;
	if(!pV->IsContents(szContents)) return false;
	return true;
}
jLAMDA_end();

#define jLAMDA_Add_PreprocessorDEF(X,Z) Z(cstr,szADD_DEFINE)
jLAMDA_find_if(Add_PreprocessorDEF,jIE*)
{
	if(!it->IsName(jS(Tool))) return false;
	jIVar* pV = it->GetAttrVar(jS(Name));
	if(!pV || !pV->IsContents(jS(VCCLCompilerTool)) ) return false;
	pV = it->GetAttrVar(jS(PreprocessorDefinitions));
	if(!pV) return false;
	tstring str = pV->Get_cstr();
	tstring str1 = tstring(szADD_DEFINE) + str;
	pV->Set_cstr(str1.c_str());
	return true;
}
jLAMDA_end();

int Replace_String(jIE* pE , cstr szAttr , const tstring& sOrg, const tstring& sChange)
{
	jIVar* pV = pE->GetAttrVar(jS(Value));
	if(!pV) return 302;
	tstring str = pV->Get_cstr();
	nSTL::replace(str , sOrg , tstring(jS(asdf1234asdf1234asdf)));
	nSTL::replace(str , tstring(jS(asdf1234asdf1234asdf)) ,sChange);
	pV->Set_cstr(str.c_str());
	return 0;
}
jIE* g_peSetting =0;
int _tmain(int argc, _TCHAR* argv[])
{
	jMech_Init(true);

	if(argc<4) 
	{
		printf("사용법 : run_by_date.exe [실행파일명] [CONTRY_CODE] [SERVICE_CODE]\n");
		return 998;
	}
	TCHAR szExe_Arg[1024];

	SYSTEMTIME st;
	GetLocalTime(&st);

	tstring g_sEXE = argv[1];
	tstring g_sCONTIRY_CODE = argv[2];
	tstring g_sSERVICE_CODE = argv[3];

	g_peSetting = nGLOBAL::g_pDocApp->Find(jS(Setting));

	tstring szSt = g_peSetting->Find(jS(TIME_STEMP_TYPE))->Get_cstr();
	if(szSt ==jS(DATE))
		jt_sprintf(szExe_Arg, _T("%s %d_%02d_%d %s %s"),g_sEXE.c_str(),st.wYear,st.wMonth,st.wDay,g_sCONTIRY_CODE.c_str(),g_sSERVICE_CODE.c_str());
	else if(szSt==jS(HOUR))
		jt_sprintf(szExe_Arg, _T("%s %d_%02d_%d[%02d] %s %s"),g_sEXE.c_str(),st.wYear,st.wMonth,st.wDay,st.wHour,g_sCONTIRY_CODE.c_str(),g_sSERVICE_CODE.c_str());
	else if(szSt==jS(MIN))
		jt_sprintf(szExe_Arg, _T("%s %d_%02d_%d[%02d-%02d] %s %s"),g_sEXE.c_str(),st.wYear,st.wMonth,st.wDay,st.wHour,st.wMinute ,g_sCONTIRY_CODE.c_str(),g_sSERVICE_CODE.c_str());
	else if(szSt==jS(MONTH))
		jt_sprintf(szExe_Arg, _T("%s %d_%02d %s %s"),g_sEXE.c_str(),st.wYear,st.wMonth,g_sCONTIRY_CODE.c_str(),g_sSERVICE_CODE.c_str());
	else
		jt_sprintf(szExe_Arg, _T("%s %d %s %s"),g_sEXE.c_str(),st.wYear,g_sCONTIRY_CODE.c_str(),g_sSERVICE_CODE.c_str());

	nFileSystem::jFolder dir;
	dir.Goto(g_ExeEnv.m_szModuleDir);

	int ret = jCreateProcess1234(szExe_Arg, true);
	if(ret==777) 
	{
		exit(777);
		return 777;
	}
	if(ret!=0)
	{
		exit(ret);
		return ret;
	}
#if 0
	fname_t szError;
	jt_sprintf(szError,_T("GetLastError = %d"),ret);
	jMB(szError,_T("error") );
#endif

#define jSPREED_SYSTEMTIME1(t) t.wYear,t.wMonth,t.wDay,t.wHour,t.wMinute,t.wSecond
#define jPRINTF_SYSTEMTIME1 _T("%02d-%02d-%02d %02d-%02d-%03d")

	tfname_t szBUILD_START_TIME;
	jt_sprintf(szBUILD_START_TIME, _T("%s %s ") jPRINTF_SYSTEMTIME1,g_sCONTIRY_CODE.c_str(),g_sSERVICE_CODE.c_str(),jSPREED_SYSTEMTIME1(st));

	FILE* fp = jt_fopen(g_peSetting->Find(jS(jMAESTIA_VERSION_FILE))->Get_cstr(),_T("wt"));
	if(!fp) return 999;
	jt_fprintf(fp, _T("//DON'T MODIFY THIS FILE. This file is auto generated!"));
	jt_fprintf(fp, _T("\n#define jMAESTIA_VERSION \"%s\""),szBUILD_START_TIME);
	fclose(fp);
	{
		//jMB("asdf","asdf");
		fname_t szXml;
		int change_solution_publish_mode(jID*,tstring szTEST,tstring szSEVICE);
		int ret_change_solution_publish_mode;
		jID* pD =0;
		jIE* pE =0;
		tstring sSERVICE_ORG , sSERVICE_QA;

		jIE* itSolutionList = nGLOBAL::g_pDocApp->Find(jS(SolutionList))->begin();
		jrFOR(itSolutionList)
		{
			jt_sprintf(szXml,itSolutionList->Get_cstr(),g_sCONTIRY_CODE.c_str());
			pD = GetjIXml()->Load(szXml);
			jvCONTINUE(pD, _T("GetjIXml()->Load(%s);"),szXml);

			cstr szADD_DEFINE = itSolutionList->GetAttr(jS(ADD_DEFINE));
			if(szADD_DEFINE && jt_strlen(szADD_DEFINE))
			{
				pE = pD->BaseI()->find_if(Add_PreprocessorDEF(szADD_DEFINE));
				jvCONTINUE(pE,jS(Add_PreprocessorDEF) _T(" %s ") , szADD_DEFINE);
			}
			sSERVICE_ORG = g_sCONTIRY_CODE + _T("\\") + itSolutionList->GetAttr(jS(ORG_STRING));
			sSERVICE_QA = g_sCONTIRY_CODE + _T("\\") + itSolutionList->GetAttr(jS(CHANGE_STRING));
			ret_change_solution_publish_mode= change_solution_publish_mode(pD , sSERVICE_ORG ,sSERVICE_QA);
			jvCONTINUE(!ret_change_solution_publish_mode ,_T("s_Project_T_Client_QA_vspropsTEST -> QA"));
			pD->Save();
			jt_printf(_T("save doc : %s"), szXml);
			GetjIXml()->UnLoad(pD);
		}
	}
	jMech_Close();
	exit (0);
	return 0;
}

int change_solution_publish_mode(jID* pD,tstring szTEST,tstring szSERVICE)
{
	jIE* pE=0;
	int ret=0;
	//S:\MaestiaBuild\tool\xml\App_pre_setting.xml
	jIE* itList= nGLOBAL::g_pDocApp->Find(jS(ChangeSolutionStringList))->begin();
	jrFOR(itList)
	{
		jIE* it = itList->begin();
		jrFOR(it)
		{
			pE = pD->BaseI()->find_if(jxFind_EAC(itList->GetTagName() , it->GetTagName() ,it->Get_cstr() ) );
			if(pE)
			{
				ret = Replace_String(pE , jS(Value) , szTEST, szSERVICE);
				jvRETURN_ret(303,!ret, _T("Replace_String(pE , %s,%s);"),it->GetTagName(),it->Get_cstr() );
				jt_printf(_T("OK change_solution_publish_mode( %s -> %s\n"), szTEST.c_str(),szSERVICE.c_str());
			}
		}
	}
	return 0;
}