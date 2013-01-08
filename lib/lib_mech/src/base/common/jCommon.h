#ifndef __jCommon_header__
#define __jCommon_header__
// 다음 ifdef 블록은 DLL에서 내보내기하는 작업을 쉽게 해 주는 매크로를 만드는 
// 표준 방식입니다. 이 DLL에 들어 있는 파일은 모두 명령줄에 정의된 JCOMMON_EXPORTS 기호로
// 컴파일되며, 동일한 DLL을 사용하는 다른 프로젝트에서는 이 기호를 정의할 수 없습니다.
// 이렇게 하면 소스 파일에 이 파일이 들어 있는 다른 모든 프로젝트에서는 
// jCOMMON_API 함수를 DLL에서 가져오는 것으로 보고,
// 이 DLL은 해당 매크로로 정의된 기호가 내보내지는 것으로 봅니다.
#ifdef JCOMMON_EXPORTS
#define jCOMMON_API __declspec(dllexport)
#else
#define jCOMMON_API __declspec(dllimport)
#pragma comment(lib, "jCommon.lib")
#endif

#include "base\\jBase.h"
#include "util/jUtil.h"

#include "interface/xml/jIXml.h"
#include "interface\\jILog.h"
#include "common/jGlobal.h"


#define jGET_INTERFACE_BY_DOC(x,doc) doc->Find(#x)? (x*)doc->Find(#x)->GetUserData():0

namespace nMech
{
	namespace nLUA
	{

		struct _ScriptableBinder;
		typedef void jLuaObjList_for_each_func_t(_ScriptableBinder*);
		class jCOMMON_API jLuaObjList
		{
		public:
			static void push_back(_ScriptableBinder*);
			static void for_each(jLuaObjList_for_each_func_t*);
			static _ScriptableBinder* find(cstr sz);
		};


		struct IScriptSystem;
		struct _ScriptableBinder2
		{
			virtual void InitializeTemplate(nLUA1::IScriptSystem*)=0;
			virtual void ReleaseTemplate()=0;
			virtual cstr GetName()=0;
		};
		typedef void jLuaObjList_for_each_func_t2(_ScriptableBinder2*);

		class jCOMMON_API jLuaObjList2
		{
		public:
			static void push_back(_ScriptableBinder2*);
			static void for_each(jLuaObjList_for_each_func_t2*);
			static _ScriptableBinder2* find(cstr sz);
		};	
	}

}

#endif //__jCommon_header__