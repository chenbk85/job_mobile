#ifndef _SQPLUS_FUNCTION_CALL_IMPL_H_
#define _SQPLUS_FUNCTION_CALL_IMPL_H_

#ifdef GCC_INLINE_WORKAROUND
# define SQINLINE
#else
# define SQINLINE inline
#endif

SQINLINE void Push(HSQUIRRELVM v,char value)           { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,unsigned char value)  { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,short value)          { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,unsigned short value) { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,int value)            { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,unsigned int value)   { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,long value)           { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,unsigned long value)  { GetjISQ()->sq_pushinteger(v,value); }
SQINLINE void Push(HSQUIRRELVM v,double value)         { GetjISQ()->sq_pushfloat(v,(FLOAT)value); }
SQINLINE void Push(HSQUIRRELVM v,float value)          { GetjISQ()->sq_pushfloat(v,(FLOAT)value); }
SQINLINE void Push(HSQUIRRELVM v,const SQChar * value) { GetjISQ()->sq_pushstring(v,value,-1); }
SQINLINE void Push(HSQUIRRELVM v,SQChar * value) { GetjISQ()->sq_pushstring(v,value,-1); }
SQINLINE void Push(HSQUIRRELVM v,const SquirrelNull &) { GetjISQ()->sq_pushnull(v); }
SQINLINE void Push(HSQUIRRELVM v,SQFUNCTION value)     { GetjISQ()->sq_pushuserpointer(v,(void*)value); }
SQINLINE void Push(HSQUIRRELVM v,SQAnythingPtr value)  { GetjISQ()->sq_pushuserpointer(v,(void*)value); } // Cast to SQAnythingPtr instead of void * if USE_ARGUMENT_DEPENDANT_OVERLOADS can't be used by your compiler.
SQINLINE void Push(HSQUIRRELVM v,SquirrelObject & so)  { GetjISQ()->sq_pushobject(v,so.GetObjectHandle()); }


#ifdef USE_ARGUMENT_DEPENDANT_OVERLOADS
#ifdef _MSC_VER
#pragma warning (disable:4675) // Disable warning: "resolved overload was found by argument-dependent lookup" when class/struct pointers are used as function arguments.
#endif
// === BEGIN Argument Dependent Overloads ===
SQINLINE void Push(HSQUIRRELVM v,bool value)                  { GetjISQ()->sq_pushbool(v,value); }               // Pass bool as int if USE_ARGUMENT_DEPENDANT_OVERLOADS can't be used by your compiler.
SQINLINE void Push(HSQUIRRELVM v,const void * value)          { GetjISQ()->sq_pushuserpointer(v,(void*)value); } // Pass SQAnythingPtr instead of void * "                                             "
SQINLINE void Push(HSQUIRRELVM v,const SQUserPointer & value) { GetjISQ()->sq_pushuserpointer(v,(void*)value); }
// === END Argument Dependent Overloads ===
#endif

#define SQPLUS_CHECK_GET(res) if (!SQ_SUCCEEDED(res)) throw SquirrelError(_T("sq_get*() failed (type error)"))

SQINLINE bool	Match(TypeWrapper<bool>,HSQUIRRELVM v,int idx)           { return GetjISQ()->sq_gettype(v,idx) == OT_BOOL; }
SQINLINE bool	Match(TypeWrapper<char>,HSQUIRRELVM v,int idx)           { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<unsigned char>,HSQUIRRELVM v, int idx) { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<short>,HSQUIRRELVM v,int idx)          { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<unsigned short>,HSQUIRRELVM v,int idx) { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<int>,HSQUIRRELVM v,int idx)            { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<unsigned int>,HSQUIRRELVM v,int idx)   { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<long>,HSQUIRRELVM v,int idx)           { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<unsigned long>,HSQUIRRELVM v,int idx)  { return GetjISQ()->sq_gettype(v,idx) == OT_INTEGER; }
SQINLINE bool	Match(TypeWrapper<float>,HSQUIRRELVM v,int idx)          { int type = GetjISQ()->sq_gettype(v,idx); return type == OT_FLOAT; }
SQINLINE bool	Match(TypeWrapper<double>,HSQUIRRELVM v,int idx)         { int type = GetjISQ()->sq_gettype(v,idx); return type == OT_FLOAT; }
SQINLINE bool	Match(TypeWrapper<const SQChar *>,HSQUIRRELVM v,int idx) { return GetjISQ()->sq_gettype(v,idx) == OT_STRING; }
SQINLINE bool	Match(TypeWrapper<SQChar *>,HSQUIRRELVM v,int idx)       { return GetjISQ()->sq_gettype(v,idx) == OT_STRING; }
SQINLINE bool	Match(TypeWrapper<HSQUIRRELVM>,HSQUIRRELVM v,int idx)    { return true; } // See Get() for HSQUIRRELVM below (v is always present).
SQINLINE bool	Match(TypeWrapper<void*>,HSQUIRRELVM v,int idx)          { return GetjISQ()->sq_gettype(v,idx) == OT_USERPOINTER; }
SQINLINE bool	Match(TypeWrapper<SquirrelObject>,HSQUIRRELVM v,int idx) { return true; } // See sq_getstackobj(): always returns true.

SQINLINE void           Get(TypeWrapper<void>,HSQUIRRELVM v,int)                {}
SQINLINE bool           Get(TypeWrapper<bool>,HSQUIRRELVM v,int idx)            { SQBool b; SQPLUS_CHECK_GET(GetjISQ()->sq_getbool(v,idx,&b)); return b != 0; }
SQINLINE char           Get(TypeWrapper<char>,HSQUIRRELVM v,int idx)            { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return static_cast<char>(i); }
SQINLINE unsigned char  Get(TypeWrapper<unsigned char>,HSQUIRRELVM v,int idx)   { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return static_cast<unsigned char>(i); }
SQINLINE short          Get(TypeWrapper<short>,HSQUIRRELVM v,int idx)           { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return static_cast<short>(i); }
SQINLINE unsigned short	Get(TypeWrapper<unsigned short>,HSQUIRRELVM v,int idx)  { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return static_cast<unsigned short>(i); }
SQINLINE int            Get(TypeWrapper<int>,HSQUIRRELVM v,int idx)             { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return i; }
SQINLINE unsigned int   Get(TypeWrapper<unsigned int>,HSQUIRRELVM v,int idx)    { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return static_cast<unsigned int>(i); }
SQINLINE long           Get(TypeWrapper<long>,HSQUIRRELVM v,int idx)            { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return static_cast<long>(i); }
SQINLINE unsigned long  Get(TypeWrapper<unsigned long>,HSQUIRRELVM v,int idx)   { INT i; SQPLUS_CHECK_GET(GetjISQ()->sq_getinteger(v,idx,&i)); return static_cast<unsigned long>(i); }
SQINLINE float          Get(TypeWrapper<float>,HSQUIRRELVM v,int idx)           { FLOAT f; SQPLUS_CHECK_GET(GetjISQ()->sq_getfloat(v,idx,&f)); return f; }
SQINLINE double         Get(TypeWrapper<double>,HSQUIRRELVM v,int idx)          { FLOAT f; SQPLUS_CHECK_GET(GetjISQ()->sq_getfloat(v,idx,&f)); return static_cast<double>(f); }
SQINLINE const SQChar * Get(TypeWrapper<const SQChar *>,HSQUIRRELVM v,int idx)  { const SQChar * s; SQPLUS_CHECK_GET(GetjISQ()->sq_getstring(v,idx,&s)); return s; }
SQINLINE SquirrelNull   Get(TypeWrapper<SquirrelNull>,HSQUIRRELVM v,int idx)    { (void)v, (void)idx; return SquirrelNull();  }
SQINLINE void *         Get(TypeWrapper<void *>,HSQUIRRELVM v,int idx)          { SQUserPointer p; SQPLUS_CHECK_GET(sq_getuserpointer(v,idx,&p)); return p; }
SQINLINE HSQUIRRELVM    Get(TypeWrapper<HSQUIRRELVM>,HSQUIRRELVM v,int /*idx*/) { GetjISQ()->sq_poptop(v); return v; } // GetjISQ()->sq_poptop(v): remove UserData from stack so GetParamCount() matches normal behavior.
SQINLINE SquirrelObject Get(TypeWrapper<SquirrelObject>,HSQUIRRELVM v,int idx)  { HSQOBJECT o; SQPLUS_CHECK_GET(sq_getstackobj(v,idx,&o)); return SquirrelObject(o); }

#ifdef SQPLUS_SUPPORT_STD_STRING
SQINLINE void Push(HSQUIRRELVM v,const std::string& value) { GetjISQ()->sq_pushstring(v,value.c_str(),-1); }
SQINLINE bool Match(TypeWrapper<const std::string&>, HSQUIRRELVM v, int idx) { return GetjISQ()->sq_gettype(v,idx) == OT_STRING; }
SQINLINE std::string Get(TypeWrapper<const std::string&>,HSQUIRRELVM v,int idx) { const SQChar * s; SQPLUS_CHECK_GET(GetjISQ()->sq_getstring(v,idx,&s)); return std::string(s); } 
#endif

// Added jflanglois suggestion, 8/20/06. jcs
#ifdef SQPLUS_SUPPORT_SQ_STD_STRING
typedef std::basic_string<SQChar> sq_std_string;
SQINLINE void Push(HSQUIRRELVM v,const sq_std_string & value) { GetjISQ()->sq_pushstring(v,value.c_str(),-1); }
SQINLINE bool Match(TypeWrapper<const sq_std_string &>, HSQUIRRELVM v, int idx) { return GetjISQ()->sq_gettype(v,idx) == OT_STRING; }
SQINLINE sq_std_string Get(TypeWrapper<const sq_std_string &>,HSQUIRRELVM v,int idx) { const SQChar * s; SQPLUS_CHECK_GET(GetjISQ()->sq_getstring(v,idx,&s)); return sq_std_string(s); } 
#endif

// Specialization to support void return type.
SQINLINE void GetRet(TypeWrapper<void>,HSQUIRRELVM v,int idx) { GetjISQ()->sq_pop(v,2); }

#endif // _SQPLUS_FUNCTION_CALL_IMPL_H_
