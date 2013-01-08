/* file : jSupportXmlInit.cpp
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-15 14:57:59
title : 
desc : 

*/

#include "stdafx.h"
#include "common/jInit.h"
#include "interface/jIDebugCallStack.h"
#include "jMessageObject.h"
#include "interface/ITimer.h"
#include "base/jTestUnit.h"
#include "Interface/xml/jIVar_op.h"
#include "Interface/jIINI_File.h"
#include "interface/jISystemPlugIn.h"
#include "functor/_jXmlAutoLoader.h"
#include "interface/jICpuInfo.h"
#include "interface/net/jINet.h"
#include "base/jTestUnit.h"
#include "base/jWindow_Util.h"
#include "functor/_jXmlAutoLoader.h"
#include "InterfaceLoader.h"
#include "interface/Squirrel/jISquirrel.h"
#include "interface/xml/jIXmlUtil.h"
#include "interface\\jIConsole.h"
#include "interface/jIOrb.h"
#include "interface/jIThread.h"
#include "interface/jIConsoleCmd.h"

namespace nMech
{
	jCOMMON_API void jCommon_Init()
	{
		printf("");
	}
	jIVar* pvUseSQ =0;

	struct IBindable;
	typedef void jLoadModelPanel_t(IBindable* pB);
	jCOMMON_API jUnLoadModelPanel_t* g_jUnLoadModelPanel=0;
	jCOMMON_API jLoadModelPanel_t* g_jLoadModelPanel=0;
	jCOMMON_API is_func_t* g_IsInGameMode=0; // 값이 0 이면 게임client로 실행시킨것이고 값이 있으면 현제 jWorldTool.exe로 실행시킨것이다.
	jCOMMON_API void_func_cstr_t* g_jReloadSelectObj=0;

	//---------------------------------------------------------------
	// Xml 관련 초기화.
	//----------------------------------------------------------------
	typedef void sq_init_func_t();
	inline bool sq_init_call(tcstr szName, void*v ){		((sq_init_func_t*)v)();	return false;	}

	//---------------------------------------------------------------
	bool jGetFlag(jIE* pE , cstr szFlag)
		//----------------------------------------------------------------
	{
		pE = pE->Find(szFlag);
#ifdef _DEBUG
		if(!pE) return false;
		assert(pE->GetType() == jIVar::EDint || pE->GetType() == jIVar::EDbool );
#endif
		if(pE && pE->GetVar()->intValue())		return true;
		return false;
	}

	jInterfaceLorder *g_pInterfaceLoader;
	static bool call_jMech_Close(tcstr szName, void* func)
	{
		if(!func ) return false;
		typedef void f_t();
		f_t* pFunc  = (f_t*)func;
		pFunc();
		return false;
	}

	jCOMMON_API void jMech_Close()
	{
		nCONSOLE::Get_jIConsoleVar()->SaveToFile();

		bool is12 = pvUseSQ->Get_bool();
		jBase::for_each_NamedPointer_ByCategory(jS(jMech_Close), call_jMech_Close);
		Get_jISystemPlugIn()->Close();
		jInterfaceLorder *a = g_pInterfaceLoader;
		SAFE_DELETE(a);
		g_pInterfaceLoader=0;
		nCONSOLE::Get_jIConsoleVar()->Release();
		Get_jISystemPlugIn()->UnRegistAll();
		GetjIXml_close();
		if(is12 && GetjISQ())GetjISQ()->End();

	}

	void callback_dev_console_var(cstr szName, jIVar* pvInSection)
	{
		jIVar* pV= nInterface::g_pjIConsole->jGetVar( szName );
		if(!pV|| !pvInSection) return;
		fname_t buf;
		pV->FromString(pvInSection->ToString(buf) );
	}

	namespace nEVENT
	{
		extern JBASE_API bool jIMessage_print(const std::vector<std::tstring>& arg);
	}
	bool sq_load_file(const std::vector<std::tstring>& arg);
	bool sq_Class(const std::vector<std::tstring>& arg);
	bool sq_global(const std::vector<std::tstring>& arg);
	bool sq_Enum(const std::vector<std::tstring>& arg);


	//---------------------------------------------------------------
	jCOMMON_API void jMech_Init(bool isMulti,bool debugException)
	//----------------------------------------------------------------
	{
		using namespace nEVENT;
		jCC(jIMessage,print,0,"print jIMsgManager data", "");

		jCC(sq,load_file,0,"squirrel file로딩","<sq_file.nut>");
		jCC(sq,Class,0,"squirrel class 리스트 출력","[class] [function]");
		jCC(sq,global,0,"squirrel 전역변수 출력","");
		jCC(sq,Enum,0,"squirrel Enum 출력","[enum name]");


		jUtil_Create();

		static bool isInit=0;
		if(isInit) return;
		isInit=true;

		//--------------------------------------------------------------------------
		// g_ExeEnv & MSXML.DLL setting
		//--------------------------------------------------------------------------
		// 멀티 실행체크.
		if(!isMulti)
		{
			if(nUtil::nWIN::Check_multi_run(g_ExeEnv.m_szAppNic))		
				throw "MULTI EXE";
		}

		nFileSystem::jFileName fn;
		//--------------------------------------------------------------------------
		// db doc load
		GetjIXml()->Init(); // Database역활을 하는 xml파일로딩. Load()함수보다 항상 맨처음 실행되야함.
		//--------------------------------------------------------------------------
		// app doc load
		//--------------------------------------------------------------------------
		assert(nGLOBAL::g_pDocApp);


		nGLOBAL::g_pDocApp->BaseI()->for_each(_jXmlAutoLoader(nGLOBAL::g_pDocApp->GetPath()) );


		extern int g_FadeSpeed;
		extern int g_FadeMode;

		//--------------------------------------------------------------------------
		// interface setting load.
		//--------------------------------------------------------------------------
		g_pInterfaceLoader = new jInterfaceLorder(nGLOBAL::g_pDocApp);
#ifndef _DEBUG
		if(debugException)
		{
			// *_* by icandoit : 2006-05-10 18:47:38
			nUtil::nDebug::jIDebugCallStack* pjIDebugCallStack = jCREATE_INTERFACE(nMech::nUtil::nDebug::jIDebugCallStack);
			pjIDebugCallStack->Init();
			//--------------------------------------------------------------------------
			// pjIDebugCallStack->AddUserModule
			//--------------------------------------------------------------------------
			jIVar* pV = nCONSOLE::Get_jIConsoleVar()->CreateVar(_T("exe")
				,_T("MODULE_OWNER")
				,_T("icandoit")
				,nCONSOLE::eCPP_ONLY_DEFINE
				,_T("module owner mail account name")
				);
			nFileSystem::jFileName fn1(g_ExeEnv.m_szExeName);
			fname_t buf;
			fn1.GetName(buf);
			jt_strlwr(buf);
			pjIDebugCallStack->AddUserModule(nUNI::scb256_t(pV->Get_cstr()).getA(), nUNI::scb256_t(buf).getA() );
		}

#endif

		nTIME::Get_ITimer()->Init();

		//--------------------------------------------------------------------------
		jLOG(_T("Version: '%s'"),g_ExeEnv.m_szVersion);
		jLOG(_T("OS User name: '%s'"),g_ExeEnv.m_szUserName);
		jLOG(_T("Computer name: '%s'"),g_ExeEnv.m_szComputerName);
		/*
		nOS::jICpuInfo* pjICpuInfo = jCREATE_INTERFACE(nMech::nOS::jICpuInfo);
		pjICpuInfo->Detect();
		SAFE_RELEASE(pjICpuInfo);
*/
		//[dev_console_var]
		//--------------------------------------------------------------------------
		if( nInterface::g_pjIConsole&&jt_strstr(g_ExeEnv.m_szModuleDir , _T("x:\\")) && g_ExeEnv.GetArg(jS(jDEV)))
		{
			if(g_ExeEnv.Get_INI())
				g_ExeEnv.Get_INI()->for_each_Section(_T("dev_console_var"),callback_dev_console_var );
		}
		jBase::for_each_NamedPointer_ByCategory(jS(jMech_Init), call_jMech_Close);
		pvUseSQ = jCV(exe,UseSquirrelBind,true,0,"use sq scrpit binding module");
		if( pvUseSQ->Get_bool() && GetjISQ())
		{
			jBase::for_each_NamedPointer_ByCategory(jS(nSQ) , sq_init_call);
			nFileSystem::jFolder dir;
			jIVar * sq_main_file= jCV(jISquirrel,sq_main_file,(tcstr)_T("sq\\sq_main.nut"),0,"auto load sq scirpt file(entry script)");
			if( dir.Is_Exist( sq_main_file->Get_cstr()  ) )
			{
				try
				{
					nSQ::SquirrelObject sq = GetjISQ()->VM_CompileScript(sq_main_file->Get_cstr());
					GetjISQ()->VM_RunScript(sq);
				}
				jSQ_CATCH_ERROR()
			}
		}

		jVar var = g_ExeEnv.Get_INI()->FindData(jS(exe),jS(run_test_unit));
		if(var.full() && var->Get_bool() )
		{
			nTest::Get_jITestUnit()->RunTest();
		}


	}


	//--------------------------------------------------------------------------
	// xml orb
	//--------------------------------------------------------------------------

	jCOMMON_API void Send_COPYDATA_XMLELEMENT_MOVEPOSITION(cstr szOrbServiceName, jIE* pE , int iOrder)
	{
		jORB2_void(pOrb,szOrbServiceName);
		jIE* pePacket = pOrb->FindProtocal(jS(SC_XMLELEMENT_MOVEPOSITION));
		GetjIXml()->GetXmlUtil()->SetXPath(pePacket, pE,0);
		pePacket->Find(jS(ORDER))->GetVar()->intValue() = iOrder;
		pOrb->Send(pePacket);
	}

	//---------------------------------------------------------------
	jCOMMON_API void Send_jeCopyData_CHANGE_STAGE_XMLDATA(cstr szOrbServiceName , jIE* pE, jIA* pA )
	{
		jORB2_void(pOrb,szOrbServiceName);

		jIE* pePacket = pOrb->FindProtocal(jS(CHANGE_STAGE_XMLDATA));

		if(pE->GetType() == jIVar::ETelement || pE->GetVar()->IsNULL())
		{
			assert(pA);
		}
		GetjIXml()->GetXmlUtil()->SetXPath(pePacket, pE, pA);
		jIVar* pV = pA ? pA->GetVar() : pE->GetVar();
		fname_t buf;
		pePacket->Find(jS(DATA))->GetVar()->Set_cstr(pV->ToString(buf) );

		pOrb->Send(pePacket);
	}

	//---------------------------------------------------------------
	jCOMMON_API void Send_jeCopyData_CHANGE_GUI_SELECT(cstr szOrbServiceName,jIE* pE)
	{
		jLOG(_T("! Send_jeCopyData_CHANGE_GUI_SELECT(%s : %s)"), pE->GetTagName() 
			, pE->GetAttr(jx(NAME))?pE->GetAttr(jx(NAME)):_T("") );

		jORB2_void(pOrb,szOrbServiceName);
		jIE* pePacket = pOrb->FindProtocal(_T("CHANGE_GUI_SELECT"));

		if(_tcsncmp(pE->GetTagName(), jS(jGui) , 4))
		{
			fname_t buf;
			jt_sprintf(buf, _T("%s의 이름 jGui로 시작하는 이름으로 바꿔주세요"),pE->GetTagName());
			jMB(buf,_T("gui contorl의 이름이 jGui로 시작하지 않았읍니다."));
			return;
		}
		GetjIXml()->GetXmlUtil()->SetXPath(pePacket, pE, 0);
		pOrb->Send(pePacket);
	}

	jCOMMON_API jID* jGET_PRELOAD_DOC(cstr szDocNic,jID*doc)
	{
		jIE* pE = doc->Find(jS(FILES))->Find(szDocNic);
		if(!pE) return 0;
		jID* pD = (jID*)pE->GetUserData();
		if(!pD)
		{
			nFileSystem::jFileName fn(pE->Get_cstr());
			pD = GetjIXml()->Load(fn.buffer);
			pE->SetUserData(pD);
			if(!pD)
			{
				jERROR(_T("file not found : %s"), pE->Get_cstr());
				jMB(_T("file not found" ), pE->Get_cstr());
				return 0;
			}
		}
		return pD;
	}

}

