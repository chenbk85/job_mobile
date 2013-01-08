// jSquirrel.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "jSquirrel.h"
#include "header/jCriticalSection.h"
#include "sqplus/SquirrelVM.h"



#ifdef _MANAGED
#pragma managed(push, off)
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
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

#ifdef _MANAGED
#pragma managed(pop)
#endif



namespace nMech
{

	namespace nSQ
	{
		static nSQ::jISquirrel* g_pjISQ=0;
#ifdef jNOT_USE_JBASE
		//--------------------------------------------------------------------------
		JSQUIRREL_API nSQ::jISquirrel* GetjISQ()\
		{
			if(g_pjISQ) return g_pjISQ;
			static nUtil::jCriticalSection s_cs;
			s_cs.Lock();
			if(g_pjISQ)	return g_pjISQ;
			static nSQ::jSquirrel s_SQ;
			g_pjISQ = &s_SQ;
			s_cs.UnLock();
			return g_pjISQ;
		}

#else
		extern "C"
		{
			JSQUIRREL_API void* jCreateInterface(jIE*)
			{
				//std::locale::global( std::locale( g_ExeEnv.GetDefaultLocale() ) ); 

				if(g_pjISQ) 
					return g_pjISQ;
				g_pjISQ = new jSquirrel;
				return (jSquirrel*)g_pjISQ;
			}
			JSQUIRREL_API void jDeleteInterface()
			{
				SAFE_DELETE(g_pjISQ);
			}
			JSQUIRREL_API acstr jGetModuleOwnerName()
			{
				return "icandoit";
			}
		}
#endif



		#define SQDBG_DEBUG_HOOK _T("_sqdebughook_")

		void jSquirrel::Begin(Begin_param* param)
		{
			jRAISE(param);
			SquirrelVM::Init();
			HSQUIRRELVM _v = SquirrelVM::GetVMPtr();
			sq_pushregistrytable(_v);
			sq_pushstring(_v,SQDBG_DEBUG_HOOK,-1);
			sq_pushuserpointer(_v,this);
			sq_newclosure(_v,param->m_debug_hook_func,1);
			sq_createslot(_v,-3);
			sq_pushstring(_v,SQDBG_DEBUG_HOOK,-1);
			sq_rawget(_v,-2);
			sq_setdebughook(_v);
			sq_pop(_v,1);

			sq_enabledebuginfo(_v,param->m_enabledebuginfo);

			m_isBegin=true;

			SquirrelObject root = SquirrelVM::GetRootTable();
			SquirrelObject tblEnum = SquirrelVM::CreateTable();
			root.SetValue(_T("Enum"), tblEnum);

			jFOR_EACH(m_binder, bind_module_func_caller);

		}
		void jSquirrel::Bind(tcstr szName,bind_module_func_t* pFunc)
		{
			m_binder_it it = m_binder.find(szName);
			if(it!=m_binder.end())
			{
				MessageBox(0,szName, _T("jSquirrel::Bind() 중복등록"),MB_OK);
				throw szName;
			}
			m_binder[szName] = pFunc;
			if(m_isBegin)
			{
				pFunc();
			}
		}
		void jSquirrel::End()
		{
			SquirrelVM::Shutdown();
		}


		HSQUIRRELVM jSquirrel::sq_open(SQInteger initialstacksize)
		{ 
			return ::sq_open(initialstacksize);
		}

		HSQUIRRELVM jSquirrel::sq_newthread(HSQUIRRELVM friendvm, SQInteger initialstacksize)
		{ 
			return ::sq_newthread(friendvm,initialstacksize);
		}

		void jSquirrel::sq_seterrorhandler(HSQUIRRELVM v)
		{ 
			::sq_seterrorhandler(v);
		}

		void jSquirrel::sq_close(HSQUIRRELVM v)
		{ 
			::sq_close(v);
		}

		void jSquirrel::sq_setforeignptr(HSQUIRRELVM v,SQUserPointer p)
		{ 
			::sq_setforeignptr(v,p);
		}

		SQUserPointer jSquirrel::sq_getforeignptr(HSQUIRRELVM v)
		{ 
			return ::sq_getforeignptr(v);
		}

		void jSquirrel::sq_setprintfunc(HSQUIRRELVM v, SQPRINTFUNCTION printfunc)
		{ 
			::sq_setprintfunc(v,printfunc);
		}

		SQPRINTFUNCTION jSquirrel::sq_getprintfunc(HSQUIRRELVM v)
		{ 
			return ::sq_getprintfunc(v);
		}

		SQRESULT jSquirrel::sq_suspendvm(HSQUIRRELVM v)
		{ 
			return ::sq_suspendvm(v);
		}

		SQRESULT jSquirrel::sq_wakeupvm(HSQUIRRELVM v,SQBool resumedret,SQBool retval,SQBool raiseerror)
		{ 
			return ::sq_wakeupvm(v,resumedret,retval,raiseerror);
		}

		SQInteger jSquirrel::sq_getvmstate(HSQUIRRELVM v)
		{ 
			return ::sq_getvmstate(v);
		}

		/*compiler*/
		SQRESULT jSquirrel::sq_compile(HSQUIRRELVM v,SQLEXREADFUNC read,SQUserPointer p,const SQChar *sourcename,SQBool raiseerror)
		{ 
			return ::sq_compile(v,read,p,sourcename,raiseerror);
		}

		SQRESULT jSquirrel::sq_compilebuffer(HSQUIRRELVM v,const SQChar *s,SQInteger size,const SQChar *sourcename,SQBool raiseerror)
		{ 
			return ::sq_compilebuffer(v,s,size,sourcename,raiseerror);
		}

		void jSquirrel::sq_enabledebuginfo(HSQUIRRELVM v, SQBool enable)
		{ 
			::sq_enabledebuginfo(v, enable);
		}

		void jSquirrel::sq_notifyallexceptions(HSQUIRRELVM v, SQBool enable)
		{ 
			::sq_notifyallexceptions(v,enable);
		}

		void jSquirrel::sq_setcompilererrorhandler(HSQUIRRELVM v,SQCOMPILERERROR f)
		{ 
			::sq_setcompilererrorhandler(v,f);
		}

		/*stack operations*/
		void jSquirrel::sq_push(HSQUIRRELVM v,SQInteger idx)
		{ 
			::sq_push(v,idx);
		}

		void jSquirrel::sq_pop(HSQUIRRELVM v,SQInteger nelemstopop)
		{ 
			::sq_pop(v,nelemstopop);
		}

		void jSquirrel::sq_poptop(HSQUIRRELVM v)
		{ 
			::sq_poptop(v);
		}

		void jSquirrel::sq_remove(HSQUIRRELVM v,SQInteger idx)
		{ 
			::sq_remove(v,idx);
		}

		SQInteger jSquirrel::sq_gettop(HSQUIRRELVM v)
		{ 
			return ::sq_gettop(v);
		}

		void jSquirrel::sq_settop(HSQUIRRELVM v,SQInteger newtop)
		{ 
			::sq_settop(v,newtop);
		}

		void jSquirrel::sq_reservestack(HSQUIRRELVM v,SQInteger nsize)
		{ 
			::sq_reservestack(v,nsize);
		}

		SQInteger jSquirrel::sq_cmp(HSQUIRRELVM v)
		{ 
			return ::sq_cmp(v);
		}

		void jSquirrel::sq_move(HSQUIRRELVM dest,HSQUIRRELVM src,SQInteger idx)
		{ 
			::sq_move(dest,src,idx);
		}

		/*object creation handling*/
		SQUserPointer jSquirrel::sq_newuserdata(HSQUIRRELVM v,SQUnsignedInteger size)
		{ 
			return ::sq_newuserdata(v,size);
		}

		void jSquirrel::sq_newtable(HSQUIRRELVM v)
		{ 
			::sq_newtable(v);
		}

		void jSquirrel::sq_newarray(HSQUIRRELVM v,SQInteger size)
		{ 
			::sq_newarray(v,size);
		}

		void jSquirrel::sq_newclosure(HSQUIRRELVM v,SQFUNCTION func,SQUnsignedInteger nfreevars)
		{ 
			::sq_newclosure(v,func,nfreevars);
		}

		SQRESULT jSquirrel::sq_setparamscheck(HSQUIRRELVM v,SQInteger nparamscheck,const SQChar *typemask)
		{ 
			return ::sq_setparamscheck(v,nparamscheck,typemask);
		}

		SQRESULT jSquirrel::sq_bindenv(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_bindenv(v,idx);
		}

		void jSquirrel::sq_pushstring(HSQUIRRELVM v,const SQChar *s,SQInteger len)
		{ 
			::sq_pushstring(v,s,len);
		}

		void jSquirrel::sq_pushfloat(HSQUIRRELVM v,SQFloat f)
		{ 
			::sq_pushfloat(v,f);
		}

		void jSquirrel::sq_pushinteger(HSQUIRRELVM v,SQInteger n)
		{ 
			::sq_pushinteger(v,n);
		}

		void jSquirrel::sq_pushbool(HSQUIRRELVM v,SQBool b)
		{ 
			::sq_pushbool(v,b);
		}

		void jSquirrel::sq_pushuserpointer(HSQUIRRELVM v,SQUserPointer p)
		{ 
			::sq_pushuserpointer(v,p);
		}

		void jSquirrel::sq_pushnull(HSQUIRRELVM v)
		{ 
			::sq_pushnull(v);
		}

		SQObjectType jSquirrel::sq_gettype(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_gettype(v,idx);
		}

		SQInteger jSquirrel::sq_getsize(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_getsize(v,idx);
		}

		SQRESULT jSquirrel::sq_getbase(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_getbase(v,idx);
		}

		SQBool jSquirrel::sq_instanceof(HSQUIRRELVM v)
		{ 
			return ::sq_instanceof(v);
		}

		void jSquirrel::sq_tostring(HSQUIRRELVM v,SQInteger idx)
		{ 
			::sq_tostring(v,idx);
		}

		void jSquirrel::sq_tobool(HSQUIRRELVM v, SQInteger idx, SQBool *b)
		{ 
			return ::sq_tobool(v,idx,b);
		}

		SQRESULT jSquirrel::sq_getstring(HSQUIRRELVM v,SQInteger idx,const SQChar **c)
		{ 
			return ::sq_getstring(v,idx,c);
		}

		SQRESULT jSquirrel::sq_getinteger(HSQUIRRELVM v,SQInteger idx,SQInteger *i)
		{ 
			return ::sq_getinteger(v,idx,i);
		}

		SQRESULT jSquirrel::sq_getfloat(HSQUIRRELVM v,SQInteger idx,SQFloat *f)
		{ 
			return ::sq_getfloat(v,idx,f);
		}

		SQRESULT jSquirrel::sq_getbool(HSQUIRRELVM v,SQInteger idx,SQBool *b)
		{ 
			return ::sq_getbool(v,idx,b);
		}

		SQRESULT jSquirrel::sq_getthread(HSQUIRRELVM v,SQInteger idx,HSQUIRRELVM *thread)
		{ 
			return ::sq_getthread(v,idx,thread);
		}

		SQRESULT jSquirrel::sq_getuserpointer(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p)
		{ 
			return ::sq_getuserpointer(v,idx,p);
		}

		SQRESULT jSquirrel::sq_getuserdata(HSQUIRRELVM v,SQInteger idx,SQUserPointer *p,SQUserPointer *typetag)
		{ 
			return ::sq_getuserdata(v,idx,p,typetag);
		}

		SQRESULT jSquirrel::sq_settypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer typetag)
		{ 
			return ::sq_settypetag(v,idx,typetag);
		}

		SQRESULT jSquirrel::sq_gettypetag(HSQUIRRELVM v,SQInteger idx,SQUserPointer *typetag)
		{ 
			return ::sq_gettypetag(v,idx,typetag);
		}

		void jSquirrel::sq_setreleasehook(HSQUIRRELVM v,SQInteger idx,SQRELEASEHOOK hook)
		{ 
			::sq_setreleasehook(v,idx,hook);
		}

		SQChar *jSquirrel::sq_getscratchpad(HSQUIRRELVM v,SQInteger minsize)
		{ 
			return sq_getscratchpad(v,minsize);
		}

		SQRESULT jSquirrel::sq_getclosureinfo(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger *nparams,SQUnsignedInteger *nfreevars)
		{ 
			return ::sq_getclosureinfo(v,idx,nparams,nfreevars);
		}

		SQRESULT jSquirrel::sq_setnativeclosurename(HSQUIRRELVM v,SQInteger idx,const SQChar *name)
		{ 
			return ::sq_setnativeclosurename(v,idx,name);
		}

		SQRESULT jSquirrel::sq_setinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer p)
		{ 
			return ::sq_setinstanceup(v,idx,p);
		}

		SQRESULT jSquirrel::sq_getinstanceup(HSQUIRRELVM v, SQInteger idx, SQUserPointer *p,SQUserPointer typetag)
		{ 
			return ::sq_getinstanceup(v,idx,p,typetag);
		}

		SQRESULT jSquirrel::sq_newclass(HSQUIRRELVM v,SQBool hasbase)
		{ 
			return ::sq_newclass(v,hasbase);
		}

		SQRESULT jSquirrel::sq_createinstance(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_createinstance(v,idx);
		}

		SQRESULT jSquirrel::sq_setattributes(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_setattributes(v,idx);
		}

		SQRESULT jSquirrel::sq_getattributes(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_getattributes(v,idx);
		}

		SQRESULT jSquirrel::sq_getclass(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_getclass(v,idx);
		}

		void jSquirrel::sq_weakref(HSQUIRRELVM v,SQInteger idx)
		{ 
			::sq_weakref(v,idx);
		}

		SQRESULT jSquirrel::sq_getdefaultdelegate(HSQUIRRELVM v,SQObjectType t)
		{ 
			return ::sq_getdefaultdelegate(v,t);
		}

		/*object manipulation*/
		void jSquirrel::sq_pushroottable(HSQUIRRELVM v)
		{ 
			::sq_pushroottable(v);
		}

		void jSquirrel::sq_pushregistrytable(HSQUIRRELVM v)
		{ 
			::sq_pushregistrytable(v);
		}

		SQRESULT jSquirrel::sq_setroottable(HSQUIRRELVM v)
		{ 
			return ::sq_setroottable(v);
		}

		SQRESULT jSquirrel::sq_newslot(HSQUIRRELVM v, SQInteger idx, SQBool bstatic)
		{ 
			return ::sq_newslot(v,idx,bstatic);
		}

		SQRESULT jSquirrel::sq_deleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval)
		{ 
			return ::sq_deleteslot(v,idx,pushval);
		}

		SQRESULT jSquirrel::sq_set(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_set(v,idx);
		}

		SQRESULT jSquirrel::sq_get(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_get(v,idx);
		}

		SQRESULT jSquirrel::sq_rawget(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_rawget(v,idx);
		}

		SQRESULT jSquirrel::sq_rawset(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_rawset(v,idx);
		}

		SQRESULT jSquirrel::sq_rawdeleteslot(HSQUIRRELVM v,SQInteger idx,SQBool pushval)
		{ 
			return ::sq_rawdeleteslot(v,idx,pushval);
		}

		SQRESULT jSquirrel::sq_arrayappend(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_arrayappend(v,idx);
		}

		SQRESULT jSquirrel::sq_arraypop(HSQUIRRELVM v,SQInteger idx,SQBool pushval)
		{ 
			return ::sq_arraypop(v,idx,pushval);
		} 

		SQRESULT jSquirrel::sq_arrayresize(HSQUIRRELVM v,SQInteger idx,SQInteger newsize)
		{ 
			return ::sq_arrayresize(v,idx,newsize);
		} 

		SQRESULT jSquirrel::sq_arrayreverse(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_arrayreverse(v,idx);
		} 

		SQRESULT jSquirrel::sq_setdelegate(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_setdelegate(v,idx);
		}

		SQRESULT jSquirrel::sq_getdelegate(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_getdelegate(v,idx);
		}

		SQRESULT jSquirrel::sq_clone(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_clone(v,idx);
		}

		SQRESULT jSquirrel::sq_setfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval)
		{ 
			return ::sq_setfreevariable(v,idx,nval);
		}

		SQRESULT jSquirrel::sq_next(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_next(v,idx);
		}

		SQRESULT jSquirrel::sq_getweakrefval(HSQUIRRELVM v,SQInteger idx)
		{ 
			return ::sq_getweakrefval(v,idx);
		}

		/*calls*/
		SQRESULT jSquirrel::sq_call(HSQUIRRELVM v,SQInteger params,SQBool retval,SQBool raiseerror)
		{ 
			return ::sq_call(v,params,retval,raiseerror);
		}

		SQRESULT jSquirrel::sq_resume(HSQUIRRELVM v,SQBool retval,SQBool raiseerror)
		{ 
			return ::sq_resume(v,retval, raiseerror);
		}

		const SQChar *jSquirrel::sq_getlocal(HSQUIRRELVM v,SQUnsignedInteger level,SQUnsignedInteger idx)
		{ 
			return ::sq_getlocal(v,level,idx);

		}

		const SQChar *jSquirrel::sq_getfreevariable(HSQUIRRELVM v,SQInteger idx,SQUnsignedInteger nval)
		{ 
			return ::sq_getfreevariable(v,idx,nval);
		}

		SQRESULT jSquirrel::sq_throwerror(HSQUIRRELVM v,const SQChar *err)
		{ 
			return ::sq_throwerror(v,err);
		}

		void jSquirrel::sq_reseterror(HSQUIRRELVM v)
		{ 
			::sq_reseterror(v);
		}

		void jSquirrel::sq_getlasterror(HSQUIRRELVM v)
		{ 
			::sq_getlasterror(v);
		}

		/*raw object handling*/
		SQRESULT jSquirrel::sq_getstackobj(HSQUIRRELVM v,SQInteger idx,HSQOBJECT *po)
		{ 
			return ::sq_getstackobj(v,idx,po);
		}

		void jSquirrel::sq_pushobject(HSQUIRRELVM v,HSQOBJECT obj)
		{ 
			::sq_pushobject(v,obj);
		}

		void jSquirrel::sq_addref(HSQUIRRELVM v,HSQOBJECT *po)
		{ 
			::sq_addref(v,po);
		}

		SQBool jSquirrel::sq_release(HSQUIRRELVM v,HSQOBJECT *po)
		{ 
			return ::sq_release(v,po);
		}

		void jSquirrel::sq_resetobject(HSQOBJECT *po)
		{ 
			::sq_resetobject(po);
		}

		const SQChar *jSquirrel::sq_objtostring(HSQOBJECT *o)
		{ 
			return ::sq_objtostring(o);
		}

		SQBool jSquirrel::sq_objtobool(HSQOBJECT *o)
		{ 
			return ::sq_objtobool(o);
		}

		SQInteger jSquirrel::sq_objtointeger(HSQOBJECT *o)
		{ 
			return ::sq_objtointeger(o);
		}

		SQFloat jSquirrel::sq_objtofloat(HSQOBJECT *o)
		{ 
			return ::sq_objtofloat(o);
		}

		SQRESULT jSquirrel::sq_getobjtypetag(HSQOBJECT *o,SQUserPointer * typetag)
		{ 
			return ::sq_getobjtypetag(o,typetag);
		}

		/*GC*/
		SQInteger jSquirrel::sq_collectgarbage(HSQUIRRELVM v)
		{ 
			return ::sq_collectgarbage(v);
		}

		/*serialization*/
		SQRESULT jSquirrel::sq_writeclosure(HSQUIRRELVM vm,SQWRITEFUNC writef,SQUserPointer up)
		{ 
			return ::sq_writeclosure(vm,writef,up);
		}

		SQRESULT jSquirrel::sq_readclosure(HSQUIRRELVM vm,SQREADFUNC readf,SQUserPointer up)
		{ 
			return ::sq_readclosure(vm,readf,up);
		}

		/*mem allocation*/
		void *jSquirrel::sq_malloc(SQUnsignedInteger size)
		{ 
			return ::sq_malloc(size);
		}

		void *jSquirrel::sq_realloc(void* p,SQUnsignedInteger oldsize,SQUnsignedInteger newsize)
		{ 
			return ::sq_realloc(p,oldsize,newsize);
		}

		void jSquirrel::sq_free(void *p,SQUnsignedInteger size)
		{ 
			::sq_free(p,size);
		}

		/*debug*/
		SQRESULT jSquirrel::sq_stackinfos(HSQUIRRELVM v,SQInteger level,SQStackInfos *si)
		{ 
			return ::sq_stackinfos(v,level, si);
		}

		void jSquirrel::sq_setdebughook(HSQUIRRELVM v)
		{ 
			::sq_setdebughook(v);
		}
	}//namespace nSQ
}
