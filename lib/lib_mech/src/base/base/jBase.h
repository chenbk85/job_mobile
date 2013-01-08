/* file : jBase.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-30 09:38:04
title : 
desc : 

*/

#ifndef __jBase_header__
#define __jBase_header__
#pragma once



// 다음 ifdef 블록은 DLL에서 내보내기하는 작업을 쉽게 해 주는 매크로를 만드는 
// 표준 방식입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 JBASE_EXPORTS 기호로
// 컴파일되며, 동일한 DLL을 사용하는 다른 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 들어 있는 다른 모든 프로젝트에서는 
// JBASE_API 함수를 DLL에서 가져오는 것으로 보고,
// 이 DLL은 해당 매크로로 정의된 기호가 내보내지는 것으로 봅니다.
#ifdef NOT_USE_JBASE_API_DLL
#	define JBASE_API 
#else
#	ifdef JBASE_EXPORTS
#		define JBASE_API __declspec(dllexport)
#	else
#		define JBASE_API __declspec(dllimport)
#		pragma comment(lib, "jBase.lib")
#	endif
#endif

#include <assert.h>
#include <windows.h>

#include "header/jHeader.h"

#include "base/juExeEnv.h"
#include "base/m_Debug.h"
#include "base/uStringParsor.h"
#include "base/jFolder.h"
#include "base/UFileName.h"
#include "interface/jILog.h"
#include "interface/jIConsoleVar.h"




//--------------------------------------------------------------------------
// 전역 interface.
//--------------------------------------------------------------------------

#define jSINGLETON_LIST(_N_)\
	_N_(IConsole)\
	_N_(jcIPak)\
	_N_(I3DEngine)\
	_N_(IAISystem)\
	_N_(INetwork)\
	_N_(IEntitySystem)\
	_N_(IRenderer)\
	_N_(jIAniManager)\
	_N_(ILog)\
	_N_(ISystem)\
	\

#define jSINGLETON_DEC(x) struct x;extern JBASE_API x* g_p##x; inline x* Get_##x(){ return g_p##x;}
jSINGLETON_LIST(jSINGLETON_DEC);


namespace nMech
{
	extern JBASE_API cstr g_XmlNULL;

	JBASE_API jIVar* jFindConsoleVar(jID* pD, cstr szName);
	typedef void* jCreateInterface_t(jIE*);
	typedef acstr jGetModuleOwnerName_t();
	JBASE_API void print_memory(cstr szLog);


	//--------------------------------------------------------------------------
	// 임시용 전역변수
	//--------------------------------------------------------------------------
#define jGLOBAL_VAR_LIST(_N_)\
	
	
	//_N_(g_isDevMode)\

#define __JVAR_DECL(x) extern JBASE_API int x;
	jGLOBAL_VAR_LIST(__JVAR_DECL);
#undef __JVAR_DECL


	//--------------------------------------------------------------------------
	// 전역 document.
	//--------------------------------------------------------------------------
#define jGLOBAL_DOC_LIST(_N_) \
	_N_(g_pDocApp)/* xml\AppName.xml*/ \
	_N_(g_pDocUser)/* xml\user.xml*/ \
	_N_(g_pDocLanguge) /* xml\languge.xml */ \
	_N_(g_pDocVKey) /* xml\vkey.xml */\
	_N_(g_pDocPlayer) /* xml\game\jPlayer.xml */\
	_N_(g_pDocGui) 


	namespace nXML{}
#define _DOC_DECL(x) namespace nGLOBAL{ extern JBASE_API nMech::jID* x;}
	jGLOBAL_DOC_LIST(_DOC_DECL);
#undef _DOC_DECL

	//for_each_NamedPointer_ByCategory에서 사용. 리턴값이 true이면 for_each를 그만둔다.
	typedef bool for_each_func_NamedPointer_ByCategory_t(tcstr szName, void* func);

	typedef nInterface::jIInterface* CreateInterface_func_t();
	class JBASE_API jBase
	{
	public:
		static nInterface::jIInterface* jBase::CreateInterface(cstr szName);
		static void jBase::Regist_InterfaceFactory(tcstr szName, CreateInterface_func_t*pFunc);

		static void RegistNamedPointer(tcstr category, tcstr name,void*);
		static void UnRegistNamedPointer(tcstr category, tcstr szName);
		static void* FindNamedPointer(tcstr category, tcstr szName);
		static void for_each_NamedPointer_ByCategory(tcstr category,  for_each_func_NamedPointer_ByCategory_t*pFunc);

	};

	extern JBASE_API jBase g_jBase;

	JBASE_API void jAssertArg( bool is , TCHAR* s , ...);

}

#endif // __jBase_header__


