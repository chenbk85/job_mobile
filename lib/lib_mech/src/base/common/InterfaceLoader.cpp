/* file : jGlobal.cpp
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-07 23:16:12
title : 
desc : 

*/

#include "stdafx.h"
#include "functor\\_jXmlAutoLoader.h"
#include "Interface/jIDebugCallStack.h"
#include "InterfaceLoader.h"

namespace nMech
{

	struct _jxLoadDll
	{
		void operator()(jIE* pE)
		{
			if(pE->GetType()!= jIVar::EDcstr) return;
			if(!pE->GetAttrVar(_T("ENABLE"))->Get_bool()) return;
			HMODULE hM = ::LoadLibrary( pE->Get_cstr() );
			if(!hM)
			{
				jMB(pE->Get_cstr(), _T("LOADING FAIL") );
				assert(0);
				return;
			}
			
			jCreateInterface_t* pFunc = (jCreateInterface_t*)::GetProcAddress(hM, "jCreateInterface");
			assert(pFunc);
			void* v = pFunc(pE);
			pE->SetUserData( v );

		}
	};


	struct _jxUnLoadDll
	{
		void operator()(jIE* pE)
		{
			if(pE->GetType()!= jIVar::EDcstr) return;
			if(!pE->GetAttrVar(_T("ENABLE"))->intValue()) return;
			HMODULE hM = ::LoadLibrary( pE->Get_cstr() );
			if(!hM) return;
			typedef void jDeleteInterface_t();
			jDeleteInterface_t* pFunc = (jDeleteInterface_t*)::GetProcAddress(hM, "jDeleteInterface");
			if(pFunc)	pFunc();
			FreeLibrary(hM);
		}
	};

#define jGET_DOC(y) (peFile = pE->Find(_T(#y))) ? (jID*)peFile->GetUserData():0;

	//--------------------------------------------------------------------------
	jInterfaceLorder::jInterfaceLorder(jID* pDocApp)
		//--------------------------------------------------------------------------
	{
		m_pD = pDocApp;
		jIE* pE;
		pE = pDocApp->Find(jS(FILES));
		if(pE)
		{
			pE->for_each(_jXmlAutoLoader(pDocApp->GetPath()) );

			jIE* peFile;
			nGLOBAL::g_pDocGui = jGET_DOC(jGuiConfig);
			nGLOBAL::g_pDocVKey = jGET_DOC(vk_key_enum);
			nGLOBAL::g_pDocPlayer = jGET_DOC(jPlayer);

		}

		nFileSystem::jFolder dm;
		dm.Goto(g_ExeEnv.m_szModuleDir);
		pDocApp->Find(_T("DLL"))->for_each(_jxLoadDll() );
		dm.GoBack();
		//if(nInterface::g_pjILua&& nInterface::g_pjIPak)		nInterface::g_pjILua->ExecuteFile("script\\jLua.lua");

	}

	jInterfaceLorder::~jInterfaceLorder()
	{
		nFileSystem::jFolder dm;
		dm.Goto(g_ExeEnv.m_szModuleDir);
		jIE* peDLL = m_pD->Find(_T("DLL"));
		if(peDLL->size()==0) return;
		jIE* it = peDLL->FindByOrder(peDLL->size()-1);
		_jxUnLoadDll a;
		for ( ;; it = it->GetLeft())
		{
			a(it);
			if( it == peDLL->begin())
				break;
		}
	}
}
