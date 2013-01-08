#ifndef __jCommon_header__
#define __jCommon_header__
// ���� ifdef ����� DLL���� ���������ϴ� �۾��� ���� �� �ִ� ��ũ�θ� ����� 
// ǥ�� ����Դϴ�. �� DLL�� ��� �ִ� ������ ��� ����ٿ� ���ǵ� JCOMMON_EXPORTS ��ȣ��
// �����ϵǸ�, ������ DLL�� ����ϴ� �ٸ� ������Ʈ������ �� ��ȣ�� ������ �� �����ϴ�.
// �̷��� �ϸ� �ҽ� ���Ͽ� �� ������ ��� �ִ� �ٸ� ��� ������Ʈ������ 
// jCOMMON_API �Լ��� DLL���� �������� ������ ����,
// �� DLL�� �ش� ��ũ�η� ���ǵ� ��ȣ�� ���������� ������ ���ϴ�.
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