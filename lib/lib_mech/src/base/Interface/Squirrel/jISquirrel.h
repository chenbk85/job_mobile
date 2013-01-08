/* file : jISquirrel.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-02-25 12:51:11
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jISquirrel_header__
#define __jISquirrel_header__
#pragma once

#ifdef jNOT_USE_JBASE
	#include "header/jDefine.h"
	#include "header/jTypedef_type.h"
	#include "header/Namespace.h"
	//#include "header/jInterface.h"
#else
	#include "base/jBase.h"
#endif
using namespace nMech;

#include "Interface/Squirrel/squirrel.h"
#include "tchar.h"

	#ifdef JSQUIRREL_EXPORTS
		#define JSQUIRREL_API __declspec(dllexport)
	#else
		#define JSQUIRREL_API __declspec(dllimport)
		#ifdef jNOT_USE_JBASE
			#pragma comment(lib, "jSquirrel.lib")
		#endif
	#endif




namespace nMech
{
	namespace nSQ
	{
		// sqplus.h에서 참조하는 클래스
		class SquirrelObject;

		// SquirrelBindingsUtils.h에서 참조하는 구조체
		struct SquirrelClassDecl;
		struct ScriptNamespaceDecl;

		// SquirrelVM.h에서 가져온것
		struct SquirrelError;

		//--------------------------------------------------------------------------
		// jISquirrel 초기화용 구조체.
		//--------------------------------------------------------------------------
		typedef int debug_hook_func_t(HSQUIRRELVM v);
		struct Begin_param
		{

			debug_hook_func_t* m_debug_hook_func;
			tcstr m_SQDBG_DEBUG_HOOK;
			bool m_enabledebuginfo;
			Begin_param()
				:m_SQDBG_DEBUG_HOOK(0)
				,m_enabledebuginfo(SQTrue)
				,m_debug_hook_func(0)
			{
			}
		};


		typedef void bind_module_func_t();
#define SQ_virtual virtual 

#define jINTERFACE_jISquirrel(x) public:	\
	\
	/* 추가된 모듈 */\
	virtual void Begin(Begin_param* param)##x\
	virtual void Bind(tcstr szName,bind_module_func_t*)##x\
	virtual void End()##x\
	/*vm*/\
	SQ_virtual HSQUIRRELVM sq_open(SQInteger initialstacksize) ##x \
	SQ_virtual HSQUIRRELVM sq_newthread(HSQUIRRELVM friendvm, SQInteger initialstacksize) ##x \
	SQ_virtual void sq_seterrorhandler(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_close(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_setforeignptr(HSQUIRRELVM v,SQUserPointer p) ##x \
	SQ_virtual SQUserPointer sq_getforeignptr(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_setprintfunc(HSQUIRRELVM v, SQPRINTFUNCTION printfunc) ##x \
	SQ_virtual SQPRINTFUNCTION sq_getprintfunc(HSQUIRRELVM v) ##x \
	SQ_virtual SQRESULT sq_suspendvm(HSQUIRRELVM v) ##x \
	SQ_virtual SQRESULT sq_wakeupvm(HSQUIRRELVM v,SQBool resumedret,SQBool retval,SQBool raiseerror) ##x \
	SQ_virtual SQInteger sq_getvmstate(HSQUIRRELVM v) ##x \
	\
	/*compiler*/\
	SQ_virtual SQRESULT sq_compile(HSQUIRRELVM v,SQLEXREADFUNC read,SQUserPointer p,const SQChar *sourcename,SQBool raiseerror) ##x \
	SQ_virtual SQRESULT sq_compilebuffer(HSQUIRRELVM v,const SQChar *s,SQInteger size,const SQChar *sourcename,SQBool raiseerror) ##x \
	SQ_virtual void sq_enabledebuginfo(HSQUIRRELVM v, SQBool enable) ##x \
	SQ_virtual void sq_notifyallexceptions(HSQUIRRELVM v, SQBool enable) ##x \
	SQ_virtual void sq_setcompilererrorhandler(HSQUIRRELVM v,SQCOMPILERERROR f) ##x \
	\
	/*stack operations*/\
	SQ_virtual void sq_push(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual void sq_pop(HSQUIRRELVM v,SQInteger nelemstopop) ##x \
	SQ_virtual void sq_poptop(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_remove(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQInteger sq_gettop(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_settop(HSQUIRRELVM v,SQInteger newtop) ##x \
	SQ_virtual void sq_reservestack(HSQUIRRELVM v,SQInteger nsize) ##x \
	SQ_virtual SQInteger sq_cmp(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_move(HSQUIRRELVM dest,HSQUIRRELVM src,SQInteger idx) ##x \
	\
	/*object creation handling*/\
	SQ_virtual SQUserPointer sq_newuserdata(HSQUIRRELVM v,SQUnsignedInteger size) ##x \
	SQ_virtual void sq_newtable(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_newarray(HSQUIRRELVM v,SQInteger size) ##x \
	SQ_virtual void sq_newclosure(HSQUIRRELVM v,SQFUNCTION func,SQUnsignedInteger nfreevars) ##x \
	SQ_virtual SQRESULT sq_setparamscheck(HSQUIRRELVM v,SQInteger nparamscheck,const SQChar *typemask) ##x \
	SQ_virtual SQRESULT sq_bindenv(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual void sq_pushstring(HSQUIRRELVM v,const SQChar *s,SQInteger len) ##x \
	SQ_virtual void sq_pushfloat(HSQUIRRELVM v,SQFloat f) ##x \
	SQ_virtual void sq_pushinteger(HSQUIRRELVM v,SQInteger n) ##x \
	SQ_virtual void sq_pushbool(HSQUIRRELVM v,SQBool b) ##x \
	SQ_virtual void sq_pushuserpointer(HSQUIRRELVM v,SQUserPointer p) ##x \
	SQ_virtual void sq_pushnull(HSQUIRRELVM v) ##x \
	SQ_virtual SQObjectType sq_gettype(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQInteger sq_getsize(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_getbase(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQBool sq_instanceof(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_tostring(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual void sq_tobool(HSQUIRRELVM v, SQInteger idx, SQBool *b) ##x \
	SQ_virtual SQRESULT sq_getstring(HSQUIRRELVM v,SQInteger idx,const SQChar **c) ##x \
	SQ_virtual SQRESULT sq_getinteger(HSQUIRRELVM v,SQInteger idx,SQInteger *i) ##x \
	SQ_virtual SQRESULT sq_getfloat(HSQUIRRELVM v,SQInteger idx,SQFloat *f) ##x \
	SQ_virtual SQRESULT sq_getbool(HSQUIRRELVM v,SQInteger idx,SQBool *b) ##x \
	SQ_virtual SQRESULT sq_getthread(HSQUIRRELVM v,SQInteger idx,HSQUIRRELVM *thread) ##x \
	SQ_virtual SQRESULT sq_getuserpointer(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p) ##x \
	SQ_virtual SQRESULT sq_getuserdata(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p,SQUserPointer *typetag) ##x \
	SQ_virtual SQRESULT sq_settypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer typetag) ##x \
	SQ_virtual SQRESULT sq_gettypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer *typetag) ##x \
	SQ_virtual void sq_setreleasehook(HSQUIRRELVM v,SQInteger idx,SQRELEASEHOOK hook) ##x \
	SQ_virtual SQChar *sq_getscratchpad(HSQUIRRELVM v,SQInteger minsize) ##x \
	SQ_virtual SQRESULT sq_getclosureinfo(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger *nparams,SQUnsignedInteger *nfreevars) ##x \
	SQ_virtual SQRESULT sq_setnativeclosurename(HSQUIRRELVM v,SQInteger idx,const SQChar *name) ##x \
	SQ_virtual SQRESULT sq_setinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer p) ##x \
	SQ_virtual SQRESULT sq_getinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p,SQUserPointer typetag) ##x \
	SQ_virtual SQRESULT sq_newclass(HSQUIRRELVM v,SQBool hasbase) ##x \
	SQ_virtual SQRESULT sq_createinstance(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_setattributes(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_getattributes(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_getclass(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual void sq_weakref(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_getdefaultdelegate(HSQUIRRELVM v,SQObjectType t) ##x \
	\
	/*object manipulation*/\
	SQ_virtual void sq_pushroottable(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_pushregistrytable(HSQUIRRELVM v) ##x \
	SQ_virtual SQRESULT sq_setroottable(HSQUIRRELVM v) ##x \
	SQ_virtual SQRESULT sq_newslot(HSQUIRRELVM v, SQInteger idx, SQBool bstatic) ##x \
	SQ_virtual SQRESULT sq_deleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval) ##x \
	SQ_virtual SQRESULT sq_set(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_get(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_rawget(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_rawset(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_rawdeleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval) ##x \
	SQ_virtual SQRESULT sq_arrayappend(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_arraypop(HSQUIRRELVM v,SQInteger idx,SQBool pushval) ##x \
	SQ_virtual SQRESULT sq_arrayresize(HSQUIRRELVM v,SQInteger idx,SQInteger newsize) ##x \
	SQ_virtual SQRESULT sq_arrayreverse(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_setdelegate(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_getdelegate(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_clone(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_setfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval) ##x \
	SQ_virtual SQRESULT sq_next(HSQUIRRELVM v,SQInteger idx) ##x \
	SQ_virtual SQRESULT sq_getweakrefval(HSQUIRRELVM v,SQInteger idx) ##x \
	\
	/*calls*/\
	SQ_virtual SQRESULT sq_call(HSQUIRRELVM v,SQInteger params,SQBool retval,SQBool raiseerror) ##x \
	SQ_virtual SQRESULT sq_resume(HSQUIRRELVM v,SQBool retval,SQBool raiseerror) ##x \
	SQ_virtual const SQChar *sq_getlocal(HSQUIRRELVM v,SQUnsignedInteger level,SQUnsignedInteger idx) ##x \
	SQ_virtual const SQChar *sq_getfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval) ##x \
	SQ_virtual SQRESULT sq_throwerror(HSQUIRRELVM v,const SQChar *err) ##x \
	SQ_virtual void sq_reseterror(HSQUIRRELVM v) ##x \
	SQ_virtual void sq_getlasterror(HSQUIRRELVM v) ##x \
	\
	/*raw object handling*/\
	SQ_virtual SQRESULT sq_getstackobj(HSQUIRRELVM v,SQInteger idx,HSQOBJECT *po) ##x \
	SQ_virtual void sq_pushobject(HSQUIRRELVM v,HSQOBJECT obj) ##x \
	SQ_virtual void sq_addref(HSQUIRRELVM v,HSQOBJECT *po) ##x \
	SQ_virtual SQBool sq_release(HSQUIRRELVM v,HSQOBJECT *po) ##x \
	SQ_virtual void sq_resetobject(HSQOBJECT *po) ##x \
	SQ_virtual const SQChar *sq_objtostring(HSQOBJECT *o) ##x \
	SQ_virtual SQBool sq_objtobool(HSQOBJECT *o) ##x \
	SQ_virtual SQInteger sq_objtointeger(HSQOBJECT *o) ##x \
	SQ_virtual SQFloat sq_objtofloat(HSQOBJECT *o) ##x \
	SQ_virtual SQRESULT sq_getobjtypetag(HSQOBJECT *o,SQUserPointer * typetag) ##x \
	\
	/*GC*/\
	SQ_virtual SQInteger sq_collectgarbage(HSQUIRRELVM v) ##x \
	\
	/*serialization*/\
	SQ_virtual SQRESULT sq_writeclosure(HSQUIRRELVM vm,SQWRITEFUNC writef,SQUserPointer up) ##x \
	SQ_virtual SQRESULT sq_readclosure(HSQUIRRELVM vm,SQREADFUNC readf,SQUserPointer up) ##x \
	\
	/*mem allocation*/\
	SQ_virtual void *sq_malloc(SQUnsignedInteger size) ##x \
	SQ_virtual void *sq_realloc(void* p,SQUnsignedInteger oldsize,SQUnsignedInteger newsize) ##x \
	SQ_virtual void sq_free(void *p,SQUnsignedInteger size) ##x \
	\
	/*debug*/\
	SQ_virtual SQRESULT sq_stackinfos(HSQUIRRELVM v,SQInteger level,SQStackInfos *si) ##x \
	SQ_virtual void sq_setdebughook(HSQUIRRELVM v) ##x \
	\
	\
	/*sqplus.h에서 가져온 함수 */\
	\
	SQ_virtual void createTableSetGetHandlers(SquirrelObject & so) ##x \
	SQ_virtual void createInstanceSetGetHandlers(SquirrelObject & so) ##x \
	SQ_virtual BOOL CreateConstructNativeClassInstance(HSQUIRRELVM v,const SQChar * className) ##x \
	SQ_virtual BOOL CreateClass(HSQUIRRELVM v,SquirrelObject & newClass,SQUserPointer classType\
														,const SQChar * name,const SQChar * baseName=0) ##x \
	\
	\
	/* SquirrelBindingsUtils.h에서 가져온 함수*/\
	\
	SQ_virtual BOOL BindUtil_CreateStaticNamespace(HSQUIRRELVM v,ScriptNamespaceDecl *sn) ##x \
	SQ_virtual BOOL BindUtil_CreateClass(HSQUIRRELVM v,SquirrelClassDecl *cd) ##x \
	SQ_virtual BOOL BindUtil_CreateNativeClassInstance(HSQUIRRELVM v,const SQChar *classname,SQUserPointer ud,SQRELEASEHOOK hook) ##x \
	\
	\
	/*SquirrelVM.h에서 가져온 함수 */\
	\
	SQ_virtual void VM_Init() ##x \
	SQ_virtual SquirrelObject VM_CompileScript(const SQChar *s) ##x \
	SQ_virtual SquirrelObject VM_CompileBuffer(const SQChar *s,const SQChar * debugInfo=_T("console_buffer")) ##x \
	SQ_virtual SquirrelObject VM_RunScript(const SquirrelObject &o,SquirrelObject *_this = NULL) ##x \
	/*SQ_virtual void VM_PrintFunc(HSQUIRRELVM v,const SQChar* s,...) ##x \ */\
	SQ_virtual BOOL VM_BeginCall(const SquirrelObject &func) ##x \
	SQ_virtual BOOL VM_BeginCall(const SquirrelObject &func,SquirrelObject &_this) ##x \
	SQ_virtual void VM_PushParam(const SquirrelObject &o) ##x \
	SQ_virtual void VM_PushParam(const SQChar *s) ##x \
	SQ_virtual void VM_PushParam(SQInteger n) ##x \
	SQ_virtual void VM_PushParam(SQFloat f) ##x \
	SQ_virtual void VM_PushParam(SQUserPointer up) ##x \
	SQ_virtual void VM_PushParamNull() ##x \
	SQ_virtual SquirrelObject VM_EndCall() ##x \
	SQ_virtual SquirrelObject VM_CreateString(const SQChar *s) ##x \
	SQ_virtual SquirrelObject VM_CreateTable() ##x \
	SQ_virtual SquirrelObject VM_CreateArray(int size) ##x \
	\
	/* oclass is an existing class. Create an 'instance' (OT_INSTANCE) of oclass.*/\
	SQ_virtual SquirrelObject VM_CreateInstance(SquirrelObject &oclass) ##x \
	SQ_virtual SquirrelObject VM_CreateFunction(SQFUNCTION func) ##x \
	SQ_virtual SquirrelObject VM_CreateUserData(int size) ##x \
	\
	SQ_virtual const SquirrelObject &VM_GetRootTable() ##x \
	SQ_virtual HSQUIRRELVM VM_GetVMPtr() ##x \
	\
	SQ_virtual void VM_PushValue(INT val) ##x \
	SQ_virtual void VM_PushValue(FLOAT val) ##x \
	/* Compiler treats SQBool as INT.*/\
	SQ_virtual void VM_PushValue(bool val) ##x \
	SQ_virtual void VM_PushValue(SQChar * val) ##x \
	SQ_virtual void VM_PushValue(SQUserPointer val) ##x \
	SQ_virtual void VM_PushValue(const SQChar * val) ##x \
	SQ_virtual void VM_PushObject(SquirrelObject & so) ##x \
	SQ_virtual void VM_Pop(SQInteger nelemstopop) ##x \
	SQ_virtual void VM_PushRootTable(void) ##x \
	\
	/* Create/bind a function on the table currently on the stack.*/\
	SQ_virtual SquirrelObject VM_CreateFunction(SQFUNCTION func,const SQChar * scriptFuncName,const SQChar * typeMask=0)##x \
	/* Create/bind a function on the table so. typeMask: standard Squirrel types plus: no typemask means no args, \
	"*" means any type of args.*/\
	SQ_virtual SquirrelObject VM_CreateFunction(SquirrelObject & so,SQFUNCTION func,const SQChar * scriptFuncName \
																						,const SQChar * typeMask=0) ##x \
	/* Create/bind a function to the root table. typeMask: standard Squirrel types plus: no typemask means no args, \
	"*" means any type of args. */\
	SQ_virtual SquirrelObject VM_CreateFunctionGlobal(SQFUNCTION func,const SQChar * scriptFuncName,const SQChar * typeMask=0) ##x \
	\
	/* struct SquirrelError의 생성자를 인터페이스로 뽑은것*/\
	SQ_virtual void init_SquirrelError(SquirrelError* se) ##x \
	\

	jINTERFACE_END(jISquirrel);

	typedef void sq_init_func_t();
	inline bool sq_init_call(tcstr szName, void*v ){		((sq_init_func_t*)v)();	return false;	}
	
}; //namespace nSQ

#ifdef jNOT_USE_JBASE
	extern JSQUIRREL_API nSQ::jISquirrel* GetjISQ();
#else
	extern JBASE_API nSQ::jISquirrel* GetjISQ();
#endif

}//namespace nMech

#define jSQ_REGIST_BIND(TAG)	static void TAG##init_SQ();\
															jONCE_RUN( TAG##__initSQ)\
															{\
																jIVar* pvIsStartSQ = jGV(jISquirrel,_IsStartSQ);\
																if(pvIsStartSQ && pvIsStartSQ->Get_bool())			TAG##init_SQ();\
																else			jBase::RegistNamedPointer(jS(nSQ),jS(TAG##init_SQ), TAG##init_SQ);\
															}static void TAG##init_SQ()


#define jSQ_CATCH_ERROR() catch (nSQ::SquirrelError & e){	jWARN(_T("SQ Error: %s \n"),e.desc); }


#include "jSqPlus.h"



#endif // __jISquirrel_header__
