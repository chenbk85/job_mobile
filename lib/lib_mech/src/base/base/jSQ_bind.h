/* file : jSQ_bind_jBase.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-11 12:04:12
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jSQ_bind_jBase_header__
#define __jSQ_bind_jBase_header__
#pragma once


#include "interface/squirrel/jISquirrel.h"
#include "interface/jIScriptHelper.h"

#define jSQ_Class(class_n) { nSQ::SQClassDef<class_n> a(jS(class_n)); \
													typedef class_n curr_type;\
													nMech::Get_jIScriptHelper()->BeginClass(jS(class_n));

#define jSQ_Interface(class_n) { nSQ::SQClassDefNoConstructor<class_n> a(jS(class_n)); \
													typedef class_n curr_type;\
													nMech::Get_jIScriptHelper()->BeginClass(jS(class_n));

	#define jSQ_sgfn(func_n,arg,help) a.staticFunc(func_n,jS(func_n) );\
												nMech::Get_jIScriptHelper()->RegistFuncHelp(jS(func_n),_T(arg),_T(help),jS(sgfn));

	#define jSQ_fn(func_n,arg,help) a.func(&curr_type::func_n,jS(func_n));\
												nMech::Get_jIScriptHelper()->RegistFuncHelp(jS(func_n),_T(arg),_T(help),jS(fn));

	#define jSQ_gfn(class_n,fn,arg,help) a.globMembFunc(&_jJOIN_4(_,class_n,_,fn),jS(fn));\
												nMech::Get_jIScriptHelper()->RegistFuncHelp(jS(fn),_T(arg),_T(help),jS(gfn));

	#define jSQ_var(var_n,help) a.var(&curr_type::var_n,jS(var_n));\
												nMech::Get_jIScriptHelper()->RegistVarHelp(jS(var_n),_T(help),_T(""));

	#define jSQ_var2(var_n,opt,help) a.var(&curr_type::var_n,jS(var_n),opt);\
												nMech::Get_jIScriptHelper()->RegistVarHelp(jS(var_n),_T(help),jS(opt));

	#define jSQ_enum_init(enum_table) nMech::Get_jIScriptHelper()->BeginEnum(jS(enum_table));

	#define jSQ_enum(scope,var,help) a.enumInt(scope::var,jS(var));\
												nMech::Get_jIScriptHelper()->RegistEnumHelp(jS(scope),jS(var),_T(help));

#define jSQ_end() nMech::Get_jIScriptHelper()->EndClass();}

#define jSQ_g_var(var,name)  nSQ::BindVariable(var,jS(name));nMech::Get_jIScriptHelper()->RegistGlobalVar(jS(var),jS(name));


#define jSQ_gfn_DEF(ret , class_n,fn_n) ret _jJOIN_4(_,class_n,_,fn_n)(HSQUIRRELVM v)
#define jSQ_gfn_DEF2(ret , class_n,fn_n) ret _jJOIN_4(_,class_n,_,fn_n)

// paramCount ,arg_This ,pThis , arg_Start=2
#define jSQ_init_pThis(THIS_TYPE)	StackHandler sa(v);	\
	int				paramCount = sa.GetParamCount();\
	const int arg_This =1;\
	THIS_TYPE	*pThis = jSQ_GetArg(THIS_TYPE,arg_This);	if(!pThis) return 0;\
	int arg_Start = 2;

#define jSQ_GetArg(TYPE,IDX) Get(TypeWrapper<TYPE*>(),v, IDX);

#include "interface/xml/jIXml.h"

using namespace nMech;
using namespace nMech::nSQ;
using namespace nMech::nXML;
using namespace nMech::nInterface;


DECLARE_INSTANCE_TYPE(jIVar);
DECLARE_INSTANCE_TYPE(jIA);
DECLARE_INSTANCE_TYPE(SYSTEMTIME);
DECLARE_INSTANCE_TYPE(uint64);
DECLARE_INSTANCE_TYPE(uint8);
DECLARE_INSTANCE_TYPE(uint16);
DECLARE_INSTANCE_TYPE(wstring);
DECLARE_INSTANCE_TYPE(astring);

#ifdef UNICODE
#else
//DECLARE_INSTANCE_TYPE(int8);
#endif



#define for_each_net_string(_F) _F(8) _F(16) _F(32) _F(64) _F(128) _F(256)

namespace nMech
{
	typedef nSQ::ScriptStringVarBase	net_string;
#define jDEF_net_string_typedef(SIZE) typedef nSQ::ScriptStringVar<SIZE>   net_string##SIZE;
	for_each_net_string(jDEF_net_string_typedef);

	namespace nSQ
	{
		inline SquirrelObject jSQ_GetEnumTable(){return GetjISQ()->VM_GetRootTable().GetValue(_T("Enum"));		}

#ifdef UNICODE
		//typedef char* char_ptr_t;
		//DECLARE_INSTANCE_TYPE(char_ptr_t);
		inline void Push<>(struct SQVM *,char const *){}
		inline char const * __cdecl Get<>(struct nMech::nSQ::TypeWrapper<char const *>,struct SQVM *,int){ return "";}
		inline bool Match<>(struct nMech::nSQ::TypeWrapper<char const *>,struct SQVM *,int){return true;}
#else
		//DECLARE_INSTANCE_TYPE(WCHAR);
		inline void Push<>(struct SQVM *,WCHAR const *){}
		inline WCHAR const * __cdecl Get<>(struct nMech::nSQ::TypeWrapper<WCHAR const *>,struct SQVM *,int){ return L"";}
		inline bool Match<>(struct nMech::nSQ::TypeWrapper<WCHAR const *>,struct SQVM *,int){return true;}
#endif


	}
}

#endif // __jSQ_bind_jBase_header__
