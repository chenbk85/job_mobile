/* file : jSQ_bind_jBase.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-11 12:04:14
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include <process.h>

#define SQPLUS_CONST_OPT

#include "interface/Squirrel/jISquirrel.h"
#include "base/jSQ_bind.h"
#include "base/jxVar.h"
#include "base/Random.h"
using namespace nMech::nLOG;
using namespace nMech::nCONSOLE;
DECLARE_INSTANCE_TYPE(jIConsoleVar);
DECLARE_INSTANCE_TYPE(jILog);
//DECLARE_INSTANCE_TYPE(StringID);
DECLARE_INSTANCE_TYPE(jID);

using namespace nMech::nUtil;

namespace sq_lib
{
	struct jLib 
	{

	};
	void Sleep(int i)
	{
		::Sleep(i);
	}

		
	struct sq_run_thread_param
	{
#ifdef CALL_THREAD_FUNC_BY_STRING
		tstring func;
#else
		SquirrelObject func;
#endif
		HANDLE hThread;
		HANDLE hThreadRun;
	};
	jLIST_TYPEDEF_map(int, sq_run_thread_param , g_sq_run_thread_param);
	static unsigned __stdcall sq_run_thread( void* v)
	{
		sq_run_thread_param* p = (sq_run_thread_param*)v;
		SetEvent(p->hThreadRun);
		try
		{
#ifdef CALL_THREAD_FUNC_BY_STRING
			SquirrelObject root = GetjISQ()->VM_GetRootTable();
			SquirrelFunction<void> callFunc2(root.GetObjectHandle(),p->func.c_str());
			if(!callFunc2.object.IsNull())
				callFunc2();
#else
			GetjISQ()->VM_BeginCall(p->func);
			GetjISQ()->VM_EndCall();
#endif
		}
		jSQ_CATCH_ERROR();
		return 0;
	}

#if 1
	int StartThread(HSQUIRRELVM v)
	{
		unsigned int idT= 0;
		static int iThread =1;
		int iNewThreadID = iThread++;
		sq_run_thread_param* p = &g_sq_run_thread_param[iNewThreadID];
		StackHandler sa(v);
#ifdef CALL_THREAD_FUNC_BY_STRING
		p->func = sa.GetString(2);
#else
		p->func = sa.GetObjectHandle(2);
#endif
		p->hThreadRun = CreateEvent(0, FALSE, FALSE, 0);
		p->hThread = (HANDLE)::_beginthreadex(NULL, 0, sq_run_thread, p, 0, &idT);
		WaitForSingleObject(p->hThreadRun, INFINITE);
		return iNewThreadID;
	}
	void EndThread(int thread_id)
	{
		g_sq_run_thread_param_it it = g_sq_run_thread_param.find(thread_id);
		if(it==g_sq_run_thread_param.end()) 
		{
			jWARN(_T("SQ}EndThread(%d) not found thread id"),thread_id);
			return;
		}
		sq_run_thread_param* p = &it->second;
		CloseHandle(p->hThreadRun);
		CloseHandle(p->hThread);
		g_sq_run_thread_param.erase(it);
	}
#endif

	jSQ_REGIST_BIND(jBase_lib)
	{
		/*
		SquirrelObject root = GetjISQ()->VM_GetRootTable();
		SquirrelObject tblMech= GetjISQ()->VM_CreateTable();
		root.SetValue(_T("jMech"), tblMech);
		Register(GetjISQ()->VM_GetVMPtr(),tblMech.GetObjectHandle(),Sleep,_T("Sleep"));
		*/

		jSQ_Class(jLib)
			jSQ_sgfn(Randomi, "int min, int max" , "return int ")
			jSQ_sgfn(Randomf, "float min, float max" , "return float")
			jSQ_sgfn(Sleep, "int time" , "")
			jSQ_sgfn(StartThread, "tstring thread_name ,void closure(void)" , "return thread_id")
			//jSQ_sgfn(PauseThread, "int thread_id" , "스레드 잠시 중지")
			jSQ_sgfn(EndThread, "int thread_id" , "스레드 종료")
		jSQ_end();

#if 0
		jSQ_Interface(jIMsgManager)
			jSQ_gfn(jIMsgManager,Regist_Loop,"int iOrder , MsgFunc_t* pFunc, int iArgCount, bool isLoop","")
		jSQ_end();
#endif
	}


}


DECLARE_ENUM_TYPE(nLOG::ELogLevelType);

namespace nSQ_jILog
{
	typedef void _jILog_func_t(tcstr);
	static int jILog_Call_func(HSQUIRRELVM v,_jILog_func_t *log_func)			
	{			
		jSQ_init_pThis(jILog);// paramCount ,arg_This ,pThis , arg_Start=2
		tagSQObjectType type = (tagSQObjectType)sa.GetType(arg_Start);
		if(paramCount==2 && type==OT_STRING)
		{
			tcstr sz =sa.GetString(arg_Start++);
			log_func(sz);
			return SQ_OK;
		}
		
		if(paramCount >= 4)
		{
			StringID* pID_Level= jSQ_GetArg(StringID,arg_Start++);
			StringID* pID_Type= jSQ_GetArg(StringID,arg_Start++);
			if(!pID_Level || !pID_Type) 
			{
				jWARN(_T("arg error :jILog_Call_func") );
				return SQ_ERROR;
			}

			type = (tagSQObjectType)sa.GetType(5);
			if(type!=  OT_STRING) return SQ_ERROR;

			if( g_pjILog->TestLogLevel(*pID_Level , *pID_Type ) )
			{
				log_func(sa.GetString(5));
			}
			return SQ_OK;
		}
		return SQ_OK;
	}

#define for_each_jILogFunc(_X) _X(Log) _X(Warning) _X(Error)
#define DEFINE_jILogFunc(FUNC)	static void _j_jILog_##FUNC(tcstr sz)		{			g_pjILog->FUNC(GetCurrentThreadId(),_T("SQ}%s"),sz);}\
	static void _jILog_##FUNC(HSQUIRRELVM v){ jILog_Call_func(v, _j_jILog_##FUNC);}
	for_each_jILogFunc(DEFINE_jILogFunc);

	jSQ_gfn_DEF2(bool,jILog,TestLogLevel)(tcstr szLogLevel, tcstr szLogType,tcstr sz)
	{
		return g_pjILog->TestLogLevel(jxi(szLogLevel),jxi(szLogType) , 0,0);
	}
	jSQ_gfn_DEF2(void,jILog,ProcessMessage)(tcstr msg)
	{
		g_pjILog->ProcessMessage(msg,0);
	}

	jSQ_gfn_DEF2(tcstr, StringID, _tostring)(StringID* pThis)
	{
		return nString::Get_jIStringTable()->GetName(*pThis);
	}
	jSQ_gfn_DEF2(tcstr, SYSTEMTIME, _tostring)(SYSTEMTIME* p)
	{
		static fname_t buf;
		jt_sprintf(buf,_T("%04d-%02d-%02d %02d:%02d:%02d]"),p->wYear , p->wMonth , p->wDay , p->wHour , p->wMinute , p->wMilliseconds/1000);
		return buf;
	}

	jSQ_REGIST_BIND(jILog_BIND)
	{
		/*
		jSQ_Class(StringID)
			jSQ_var(id,"문자의 고유 인덱스")
			jSQ_gfn(StringID,_tostring,"","해당 스트링 인덱스에 대한 문자를 리턴")
		jSQ_end()
*/
		jSQ_Interface(jILog)
			jSQ_enum_init(ELogLevelType)
			jSQ_enum(nLOG,eLOG_OFF,"해당 카테고리의 로깅을 끈다")
			jSQ_enum(nLOG,eLOG_LEVEL,"해당카테고리에대해 레벨에 맞게 로깅")
			jSQ_enum(nLOG,eLOG_ALWAYS,"항상 로깅")
			jSQ_fn(SetFileName,"cstr filename","로깅파일을 새로 세팅")
			jSQ_fn(GetFileName,"","로깅파일 이름을 리턴")
			jSQ_fn(RunConsoleTool,"","")
			jSQ_fn(LogTimeTag,"bool withFile","")
			jSQ_gfn(jILog,TestLogLevel,"nMech::StringID arg_LogLevel,nMech::StringID arg_logType","")
			jSQ_fn(UpdateLogLevel,"nMech::StringID arg_logLeve, nLOG::ELogLevelType isLogOn","")
			jSQ_fn(PushIndent,"int iWantedIndentCount"
			,"입력(iWantedIndentCount) 갯수만큼 인덴트 한다. 리턴값은 현제 인덴트 적용후 전체 인덴트된 수")
			jSQ_fn(PopIndent,"int iWantedIndentCount"
			,"입력iWantedIndentCount 만큼 인덴트를 제거. 만약 0이면 모든 인덴트를 제거. 전체 인덴트된 수를 리턴")
			jSQ_gfn(jILog,Warning,"tcstr logString","경고출력")
			jSQ_gfn(jILog,Error,"tcstr logString","에러출력후 종료됨")
			jSQ_gfn(jILog,Log,"tcstr logString","")
//			jSQ_gfn(jILog,LogPlus,"tcstr logString","이후 출력되는 로그에 개행문자를 넣지 않는다.")
			jSQ_gfn(jILog,ProcessMessage,"void (msg)","msg: flush_WriteCache ")

		jSQ_end()

		jSQ_Class(SYSTEMTIME)
			jSQ_gfn(SYSTEMTIME,_tostring,"","")
		jSQ_end();

		jSQ_g_var(nInterface::g_pjILog,g_pjILog);
		jSQ_g_var(nGLOBAL::g_pDocApp,g_pDocApp);
		
		//RegisterGlobal(&jILog_Warning, _T("jWarning"));
		//RegisterGlobal(&jILog_Error, _T("jError"));
		//RegisterGlobal(&jILog_Log, _T("jLog"));
		//RegisterGlobal(&jILog_LogPlus, _T("jLogPlus"));

	}//jSQ_REGIST_BIND(jILog_BIND)
}//namespace nSQ_jILog

DECLARE_ENUM_TYPE(jIVar::EElementType);

namespace nSQ_jIVar
{
	static tcstr _jIVar__tostring(jIVar* v)
	{
		static fname_t buf;
		//ScriptStringVar256
		return (v->ToString(buf));
	}
/*
	size_t _jIVar_Get_StringID(jIVar* v)
	{
		return v->Get_StringID().id;
	}
	void _jIVar_Set_StringID(jIVar* v, size_t id)
	{
		v->Set_StringID(StringID::make_StringID(id));
	}
	*/
	tcstr _jIVar_Get_cstr(jIVar* v)
	{
		return v->Get_cstr();
	}
	bool _jIVar__cmp(jIVar* v,jIVar*v2)
	{
		return v->IsEqual(v2);
	}

	// v.InitValue("234;33" , jIVar::EDint2);
	// v.InitValue(234);
	// v.InitValue(234.3);
	// v.InitValue(jS(asdf));
	jIVar* _jIVar_InitValue(HSQUIRRELVM v)
	{
		jSQ_init_pThis(jIVar);// paramCount ,arg_This ,pThis , arg_Start=2
		const int arg_VALUE = 2;
		const int arg_TYPE = 3;
		tcstr szValue = sa.GetString(arg_VALUE);
		if(sa.GetParamCount() == 3)
		{
			jIVar::EElementType eType = (jIVar::EElementType)sa.GetInt(arg_TYPE);
			pThis->InitValue(szValue,eType);
			return pThis;
		}
		switch(sa.GetType(arg_VALUE))
		{
		case OT_INTEGER:
			{
				pThis->InitValue(sa.GetInt(arg_VALUE));
				break;
			}
		case OT_FLOAT:
			{
				pThis->InitValue(sa.GetFloat(arg_VALUE));
				break;
			}
		case OT_BOOL:
			{
				pThis->InitValue(sa.GetBool(arg_VALUE));
				break;
			}
		case OT_STRING:
			{
				pThis->InitValue(sa.GetString(arg_VALUE));
				break;
			}
		case OT_ARRAY:
			{

				break;
			}
		case OT_INSTANCE:
			{
				jIVar* pV = jSQ_GetArg(jIVar,arg_VALUE);
				if(pV) pV->CopyTo(pThis);
				break;
			}
		}
		return pThis;

	}

	//static jIVar* test_Get_jIVar(){	static jxVar v;		v.InitValue(234);		return &v;}

	jSQ_gfn_DEF2(jIVar*,jIConsoleVar, GetVar )(jIConsoleVar* pThis, tcstr szCategory,tcstr var)
	{
		return pThis->GetVar(szCategory,var);
	}
	jSQ_REGIST_BIND(nSQ_jIVar)
	{
		jSQ_Interface(jIVar)
			jSQ_enum_init(EElementType)
#define _jsq_def_enum(enumVal) jSQ_enum(jIVar,enumVal,"")
			_for_each_ENUM_type_jvar(_jsq_def_enum)
			jSQ_gfn(jIVar,_tostring,"","")
			jSQ_fn(FromString,"cstr buf","해당 buf의 내용을 자신의 자료형으로 변환")
			//#define _sq_jIVar_setget_func(TYPE) jSQ_fn(jIVar,Get_##TYPE)jSQ_fn(jIVar,Set_##TYPE)
			//_for_each_simple_type_jvar(_sq_jIVar_setget_func)
			jSQ_fn(Get_int,"","")
			jSQ_fn(Set_int,"int val","")
			jSQ_fn(Get_float,"","")
			jSQ_fn(Set_float,"float val","")
			jSQ_fn(Get_bool,"","")
			jSQ_fn(Set_bool,"bool val","")
			jSQ_fn(Get_uint,"","")
			jSQ_fn(Set_uint,"uint val","")
			//jSQ_gfn(jIVar,Get_StringID,"","")
			//jSQ_gfn(jIVar,Set_StringID,"StringID id","")
			jSQ_gfn(jIVar,Get_cstr,"","")
			jSQ_fn(Set_cstr,"cstr sz","")
			jSQ_fn(DebugPrint,"bool isInsert_CR","isInsert_CR==true이면 라인별로 개행문자를 추가한다.")
			jSQ_fn(CopyTo,"jIVar* pvDest","")
			jSQ_fn(IsContents,"tcstr szData","값이 jIVar::EDstring일때 szData와 일치하면 true리턴")
			jSQ_fn(IsType,"jIVar::EEelementType eType","")
			jSQ_fn(GetType,"","")
			jSQ_fn(SetType,"jIVar::EEelementType eType","해당 자료형으로 변환")
			jSQ_fn(IsEqual,"jIVar* pV","")
			jSQ_fn(Lerp,"jIVar* pIV1, jIVar* pIV2 , float fLerpRatio","")
			jSQ_fn(GetTypeString,"","")
			jSQ_fn(GetArraySize,"","")
			jSQ_gfn(jIVar,_cmp,"","")
#if 0
			jSQ_fn(GetFloat,"","")
			jSQ_fn(GetInt,"","")
			jSQ_fn(IsUserDataOK,"","")
#endif
			jSQ_gfn(jIVar,InitValue,"","")
		jSQ_end();
		//RegisterGlobal(test_Get_jIVar, _T("test_Get_jIVar"));

		jSQ_Interface(jIConsoleVar)
			jSQ_fn(GetDoc,"","return jID")
			jSQ_gfn(jIConsoleVar, GetVar,"category,var","return jIVar")
		jSQ_end();

		jSQ_g_var(nCONSOLE::Get_jIConsoleVar(),g_pjIConsoleVar);

	}

}

#include "base/jMsgManager.h"
using namespace nEVENT;
DECLARE_INSTANCE_TYPE(jIMessage);
DECLARE_INSTANCE_TYPE(jIMsgManager);

namespace nSQ_jIMessage
{
	jSQ_REGIST_BIND(nSQ_jIMessage)
	{
		jSQ_Interface(jIMessage)
		jSQ_end();

		jSQ_Interface(jIMsgManager)
		jSQ_end();
	}
}