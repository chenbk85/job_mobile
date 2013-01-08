// jCommon.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "jCommon.h"
using namespace nMech;
#include "interface/jIConsoleCmd.h"
#include "interface/Squirrel/jISquirrel.h"
#include "header/_ScriptableEx.h"
#include "Interface/gui/jIGuiDefine.h"
#include "jc/jcMemoryManager.h"

nMech::StringID g_Current_LogLevel_jStringID = jx(jCommon);

volatile float __f__=10;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{

	__f__++;
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

namespace nMech
{
#define USE_NOT_AUTO_CMD

#ifdef USE_NOT_AUTO_CMD
	bool sq_load_file(const std::vector<std::tstring>& arg)
#else
	jCONSOLE_CMD_AUTO(sq,load_file,0,"squirrel file로딩","<sq_file.nut>")
#endif
	{
		using namespace nSQ;
		try
		{
			SquirrelObject file = GetjISQ()->VM_CompileScript(arg[0].c_str());
			GetjISQ()->VM_RunScript(file);
		}
		jSQ_CATCH_ERROR();
		return true;
	}

#ifdef USE_NOT_AUTO_CMD
	bool sq_Class(const std::vector<std::tstring>& arg)
#else
	jCONSOLE_CMD_AUTO(sq,Class,0,"squirrel class 리스트 출력","[class] [function]")
#endif
	{
		using namespace nSQ;
		jIE* pD = GetjIXml()->GetObj(jS(jIScriptHelper))->Find(jS(Class));
		if(arg.size()==0)
		{
			jIE* it = pD->begin();
			jrFOR(it)
			{
				jLOG(it->GetTagName());
			}
			return true;
		}
		jIE* pEClass = pD->Find(arg[0].c_str());
		if(!pEClass)
		{
			jLOG(_T("sq class %s not found"),arg[0].c_str());
			return false;
		}

		if(arg.size()==1)
		{
			jIE* it = pEClass->begin();
			jrFOR(it)
			{
				it->DebugPrint(true);
			}
			return true;
		}
		jIE* pE = pEClass->Find(jS(Function))->Find(arg[1].c_str());
		if(!pE)
		{
			jLOG(_T("sq class function %s::%s not found"),arg[0].c_str(),arg[1].c_str());
			return false;
		}

		pE->DebugPrint(true);
		return true;
	}

#ifdef USE_NOT_AUTO_CMD
	bool sq_global(const std::vector<std::tstring>& arg)
#else
	jCONSOLE_CMD_AUTO(sq,global,0,"squirrel 전역변수 출력","")
#endif
	{
		using namespace nSQ;
		jIE* pD = GetjIXml()->GetObj(jS(jIScriptHelper))->Find(jS(GlobalVar));
		if(arg.size()==0)
		{
			jIE* it = pD->begin();
			jrFOR(it)
			{
				jLOG(it->GetTagName());
			}
			return true;
		}
		return true;
	}

#ifdef USE_NOT_AUTO_CMD
	bool sq_Enum(const std::vector<std::tstring>& arg)
#else
	jCONSOLE_CMD_AUTO(sq,Enum,0,"squirrel Enum 출력","[enum name]")
#endif
	{
		using namespace nSQ;
		jIE* pD = GetjIXml()->GetObj(jS(jIScriptHelper))->Find(jS(Enum));
		if(arg.size()==0)
		{
			jIE* it = pD->begin();
			jrFOR(it)
			{
				jLOG(it->GetTagName());
			}
			return true;
		}
		else
		{
			jIE* pE = pD->Find(arg[0].c_str());
			pE->DebugPrint(true);
		}
		return true;
	}


	namespace nLUA
	{
		// *_* by icandoit : 2006-06-09 15:15:26
		// lua sink 새로운버젼 



		//--------------------------------------------------------------------------
		// lua script object manager buffer
		//--------------------------------------------------------------------------

		static std::vector<_ScriptableBinder*> s_jLuaObjList;
		void jLuaObjList::push_back(_ScriptableBinder* pO)
		{
			s_jLuaObjList.push_back(pO);
		}
		void jLuaObjList::for_each(jLuaObjList_for_each_func_t* pFunc)
		{
			std::for_each(s_jLuaObjList.begin(), s_jLuaObjList.end(), pFunc);
		}

		_ScriptableBinder* jLuaObjList::find(cstr sz)
		{
			size_t tot =s_jLuaObjList.size();
			for(uint i=0; i < tot ; ++i)
			{
				if(!jt_strcmp(s_jLuaObjList[i]->GetName() , sz))
				{
					return s_jLuaObjList[i];
				}
			}
			return 0;
		}
		//--------------------------------------------------------------------------
		// lua script object manager buffer 2
		//--------------------------------------------------------------------------

		static std::vector<_ScriptableBinder2*> s_jLuaObjList2;
		void jLuaObjList2::push_back(_ScriptableBinder2* pO)
		{
			s_jLuaObjList2.push_back(pO);
		}
		void jLuaObjList2::for_each(jLuaObjList_for_each_func_t2* pFunc)
		{
			std::for_each(s_jLuaObjList2.begin(), s_jLuaObjList2.end(), pFunc);
		}

		_ScriptableBinder2* jLuaObjList2::find(cstr sz)
		{
			size_t tot =s_jLuaObjList2.size();
			for(uint i=0; i < tot ; ++i)
			{
				if(!jt_strcmp(s_jLuaObjList2[i]->GetName() , sz))
				{
					return s_jLuaObjList2[i];
				}
			}
			return 0;
		}


		//--------------------------------------------------------------------------
		// lua scirpt objet용 help api
		//--------------------------------------------------------------------------
	}

	namespace nGUI
	{

		//--------------------------------------------------------------------------
		// jGui handler buffer
		//--------------------------------------------------------------------------
		typedef std::list<jGuiHandlerInfo> jGuiHandlerInfo_L_t;
		typedef jGuiHandlerInfo_L_t::iterator jGuiHandlerInfo_L_it;
		typedef std::map<tstring,jGuiHandlerInfo_L_t> jGuiHandlerInfoList_t;
		typedef jGuiHandlerInfoList_t::iterator jGuiHandlerInfoList_it;

		static jGuiHandlerInfoList_t g_jGuiHandlerInfoList;
		static jGuiHandlerInfoList_it itStage;
		static jGuiHandlerInfo_L_it it,ie;
		void jGuiHandlerInfoList::push_back(cstr szStage, jGuiHandlerInfo a)
		{
			g_jGuiHandlerInfoList[szStage].push_back(a);
		}
		void jGuiHandlerInfoList::GotoBegin(){ it = itStage->second.begin(); ie = itStage->second.end();}
		jGuiHandlerInfo* jGuiHandlerInfoList::Get(){ return &(*(it++)); }

		bool jGuiHandlerInfoList::IsEnd(){ return it==ie ;}

		bool jGuiHandlerInfoList::Find(cstr sz)
		{ 
			itStage = g_jGuiHandlerInfoList.find(sz);
			return itStage==g_jGuiHandlerInfoList.end() ? false:true;
		}
		jGuiHandlerInfoList& jGuiHandlerInfoList::This()
		{
			static jGuiHandlerInfoList a;
			return a;
		}

	}

}
