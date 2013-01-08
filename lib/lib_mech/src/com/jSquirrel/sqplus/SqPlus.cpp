#include "stdafx.h"
#include <stdio.h>

#ifdef SQPLUS_SMARTPOINTER_OPT
#define SQPLUS_SMARTPOINTER_CPP_DECLARATION
#include "SqPlusSmartPointer.h"
#endif

namespace nMech{
namespace nSQ {

static int getVarInfo(StackHandler & sa,VarRefPtr & vr) {
  HSQOBJECT htable = sa.GetObjectHandle(1);
  SquirrelObject table(htable);
#ifdef _DEBUG
  SQObjectType type = (SQObjectType)sa.GetType(2);
#endif
  const SQChar * el = sa.GetString(2);
  ScriptStringVar256 varNameTag;
  getVarNameTag(varNameTag,sizeof(varNameTag),el);
  SQUserPointer data=0;
  if (!table.RawGetUserData(varNameTag,&data)) {
//    throw SquirrelError("getVarInfo: Could not retrieve UserData");
    return sa.ThrowError(_T("getVarInfo: Could not retrieve UserData")); // Results in variable not being found error.
  } // if
  vr = (VarRefPtr)data;
  return SQ_OK;
} // getVarInfo

static int getInstanceVarInfo(StackHandler & sa,VarRefPtr & vr,SQUserPointer & data) {
  HSQOBJECT ho = sa.GetObjectHandle(1);
  SquirrelObject instance(ho);
#ifdef _DEBUG
  SQObjectType type = (SQObjectType)sa.GetType(2);
#endif
  const SQChar * el = sa.GetString(2);
  ScriptStringVar256 varNameTag;
  getVarNameTag(varNameTag,sizeof(varNameTag),el);
  SQUserPointer ivrData=0;
  if (!instance.RawGetUserData(varNameTag,&ivrData)) {
//    throw SquirrelError("getInstanceVarInfo: Could not retrieve UserData");
    return sa.ThrowError(_T("getInstanceVarInfo: Could not retrieve UserData")); // Results in variable not being found error.
  } // if
  vr = (VarRefPtr)ivrData;
  unsigned char * up;
  if (!(vr->m_access & (VAR_ACCESS_STATIC|VAR_ACCESS_CONSTANT))) {
#ifdef SQ_USE_CLASS_INHERITANCE
    SQUserPointer typetag; instance.GetTypeTag(&typetag);
    if (typetag != vr->instanceType) {
      SquirrelObject typeTable = instance.GetValue(SQ_CLASS_OBJECT_TABLE_NAME);
      up = (unsigned char *)typeTable.GetUserPointer(INT((size_t)vr->instanceType)); // <TODO> 64-bit compatible version.
      if (!up) {
        throw SquirrelError(_T("Invalid Instance Type"));
      } // if
    } else {
      up = (unsigned char *)instance.GetInstanceUP(0);
    } // if
#else
    up = (unsigned char *)instance.GetInstanceUP(0);
#endif

#ifdef SQPLUS_SMARTPOINTER_OPT
#define SQPLUS_SMARTPOINTER_INSTANCE_VARINFO
#include "SqPlusSmartPointer.h"
#endif

    up += (size_t)vr->offsetOrAddrOrConst;         // Offset
  } else {
    up = (unsigned char *)vr->offsetOrAddrOrConst; // Address
  } // if
  data = up;
  return SQ_OK;
} // getInstanceVarInfo


// If not static/global, message can (and will) disappear before arriving at catch (G++)
static ScriptStringVar256 g_msg_throw;

static int setVar(StackHandler & sa,VarRef * vr,void * data) {
  if (vr->m_access & (VAR_ACCESS_READ_ONLY|VAR_ACCESS_CONSTANT)) {
    const SQChar * el = sa.GetString(2);
    SCSNPRINTF(g_msg_throw.s,sizeof(g_msg_throw),_T("setVar(): Cannot write to constant: %s"),el);
    throw SquirrelError(g_msg_throw.s);
  } // if
  switch (vr->m_type) {
  case TypeInfo<INT>::TypeID: {
    INT * val = (INT *)data; // Address
    if (val) {
        INT v = sa.GetInt(3);
        // Support for different int sizes
        switch( vr->m_size ) {
          case 1: v = (*(char*)val = (char)v); break;  
          case 2: v = (*(short*)val = (short)v); break;  
#ifdef _SQ64
          case 4: v = (*(int*)val = (int)v); break;
#endif            
          default: *val = v;
        }
      //*val = sa.GetInt(3);
      //return sa.Return(*val);
       return sa.Return(v);
    } // if
    break;
  } // case
  case TypeInfo<unsigned>::TypeID: {
	  unsigned * val = (unsigned *)data; // Address
	  if (val) {
		  *val = sa.GetInt(3);
		  return sa.Return(static_cast<INT>(*val));
	  } // if
	  break;
  } // case
  case TypeInfo<FLOAT>::TypeID: {
    FLOAT * val = (FLOAT *)data; // Address
    if (val) {
      *val = sa.GetFloat(3);
      return sa.Return(*val);
    } // if
    break;
  } // case
  case TypeInfo<bool>::TypeID: {
    bool * val = (bool *)data; // Address
    if (val) {
      *val = sa.GetBool(3) ? true : false;
      return sa.Return(*val);
    } // if
    break;
  } // case
  case VAR_TYPE_INSTANCE: {
    HSQUIRRELVM v = sa.GetVMPtr();
    // vr->copyFunc is the LHS variable type: the RHS var's type is ClassType<>::type() (both point to ClassType<>::copy()).
    // src will be null if the LHS and RHS types don't match.
    SQUserPointer src = sa.GetInstanceUp(3,(SQUserPointer)vr->copyFunc); // Effectively performs: ClassType<>::type() == ClassType<>getCopyFunc().
    if (!src) throw SquirrelError(_T("INSTANCE type assignment mismatch"));
    vr->copyFunc(data,src);
#if 0 // Return an instance on the stack (allocates memory)
    if (!CreateNativeClassInstance(sa.GetVMPtr(),vr->typeName,data,0)) { // data = address
      SCSNPRINTF(g_msg_throw.s,sizeof(g_msg_throw),_T("getVar(): Could not create instance: %s"),vr->typeName);
      throw SquirrelError(g_msg_throw.s);
    } // if
    return 1;
#else // Don't return on stack.
    return 0;
#endif
  }
  case TypeInfo<SQUserPointer>::TypeID: {
    const SQChar * el = sa.GetString(2);
    SCSNPRINTF(g_msg_throw.s,sizeof(g_msg_throw),_T("setVar(): Cannot write to an SQUserPointer: %s"),el);
    throw SquirrelError(g_msg_throw.s);
  } // case
  case TypeInfo<ScriptStringVarBase>::TypeID: {
    ScriptStringVarBase * val = (ScriptStringVarBase *)data; // Address
    if (val) {
      const SQChar * strVal = sa.GetString(3);
      if (strVal) {
        *val = strVal;
        return sa.Return(val->s);
      } // if
    } // if
    break;
  } // case
  } // switch
  return SQ_ERROR;
} // setVar

static int getVar(StackHandler & sa,VarRef * vr,void * data) {
  switch (vr->m_type) {
  case TypeInfo<INT>::TypeID: {
    if (!(vr->m_access & VAR_ACCESS_CONSTANT)) {
      INT * val = (INT *)data; // Address
      if (val) {
          INT v;
          // Support for different int sizes
          switch( vr->m_size ){
            case 1: v = *(char*)val; break;  
            case 2: v = *(short*)val; break;  
#ifdef _SQ64
            case 4: v = *(int*)val; break;
#endif            
            default: v = *val;
          }
          return sa.Return(v);
      } // if
    } else {
      INT * val = (INT *)&data; // Constant value
      return sa.Return(*val);
    } // if
    break;
  } // case
  case TypeInfo<unsigned>::TypeID: {
	  if (!(vr->m_access & VAR_ACCESS_CONSTANT)) {
		  unsigned * val = (unsigned *)data; // Address
		  if (val) {
			  return sa.Return(static_cast<INT>(*val));
		  } // if
	  } else {
		  unsigned * val = (unsigned *)&data; // Constant value
		  return sa.Return(static_cast<INT>(*val));
	  } // if
	  break;
  } // case
  case TypeInfo<FLOAT>::TypeID: {
    if (!(vr->m_access & VAR_ACCESS_CONSTANT)) {
      FLOAT * val = (FLOAT *)data; // Address
      if (val) {
        return sa.Return(*val);
      } // if
    } else {
      FLOAT * val = (FLOAT *)&data; // Constant value
      return sa.Return(*val);
    } // if
    break;
  } // case
  case TypeInfo<bool>::TypeID: {
    if (!(vr->m_access & VAR_ACCESS_CONSTANT)) {
      bool * val = (bool *)data; // Address
      if (val) {
        return sa.Return(*val);
      } // if
    } else {
      bool * val = (bool *)&data; // Constant value
      return sa.Return(*val);
    } // if
    break;
  } // case
  case VAR_TYPE_INSTANCE:
    if (!GetjISQ()->BindUtil_CreateNativeClassInstance(sa.GetVMPtr(),vr->typeName,data,0)) { // data = address. Allocates memory.
      SCSNPRINTF(g_msg_throw.s,sizeof(g_msg_throw),_T("getVar(): Could not create instance: %s"),vr->typeName);
      throw SquirrelError(g_msg_throw.s);
    } // if
    return 1;
  case TypeInfo<SQUserPointer>::TypeID: {
    return sa.Return(data); // The address of member variable, not the variable itself.
  } // case
  case TypeInfo<ScriptStringVarBase>::TypeID: {
    if (!(vr->m_access & VAR_ACCESS_CONSTANT)) {
      ScriptStringVarBase * val = (ScriptStringVarBase *)data; // Address
      if (val) {
        return sa.Return(val->s);
      } // if
    } else {
      throw SquirrelError(_T("getVar(): Invalid type+access: 'ScriptStringVarBase' with VAR_ACCESS_CONSTANT (use VAR_ACCESS_READ_ONLY instead)"));
    } // if
    break;
  } // case
  case TypeInfo<const SQChar *>::TypeID: {
    if (!(vr->m_access & VAR_ACCESS_CONSTANT)) {
      if( vr->m_access==VAR_ACCESS_READ_WRITE )
        throw SquirrelError(_T("getVar(): Invalid type+access: 'const SQChar *' without VAR_ACCESS_CONSTANT"));
      // It is OK to read from a SQChar* if requested
      return sa.Return(*(const SQChar **)data); // Address
    } else {
      return sa.Return((const SQChar *)data); // Address
    } // if
    break;
  } // case
  } // switch
  return SQ_ERROR;
} // getVar

// === Global Vars ===

int setVarFunc(HSQUIRRELVM v) {
  StackHandler sa(v);
  if (sa.GetType(1) == OT_TABLE) {
    VarRefPtr vr;
    int res = getVarInfo(sa,vr);
    if (res != SQ_OK) return res;
    return setVar(sa,vr,vr->offsetOrAddrOrConst);
  } // if
  return SQ_ERROR;
} // setVarFunc

int getVarFunc(HSQUIRRELVM v) {
  StackHandler sa(v);
  if (sa.GetType(1) == OT_TABLE) {
    VarRefPtr vr;
    int res = getVarInfo(sa,vr);
    if (res != SQ_OK) return res;
    return getVar(sa,vr,vr->offsetOrAddrOrConst);
  } // if
  return SQ_ERROR;
} // getVarFunc

// === Instance Vars ===

int setInstanceVarFunc(HSQUIRRELVM v) {
  StackHandler sa(v);
  if (sa.GetType(1) == OT_INSTANCE) {
    VarRefPtr vr;
    void * data;
    int res = getInstanceVarInfo(sa,vr,data);
    if (res != SQ_OK) return res;
    return setVar(sa,vr,data);
  } // if
  return SQ_ERROR;
} // setInstanceVarFunc

int getInstanceVarFunc(HSQUIRRELVM v) {
  StackHandler sa(v);
  if (sa.GetType(1) == OT_INSTANCE) {
    VarRefPtr vr;
    void * data;
    int res = getInstanceVarInfo(sa,vr,data);
    if (res != SQ_OK) return res;
    return getVar(sa,vr,data);
  } // if
  return SQ_ERROR;
} // getInstanceVarFunc

// === Classes ===

BOOL jSquirrel::CreateClass(HSQUIRRELVM v,SquirrelObject & newClass,SQUserPointer classType,const SQChar * name,const SQChar * baseName) {
  int n = 0;
  int oldtop = sq_gettop(v);
  sq_pushroottable(v);
  sq_pushstring(v,name,-1);
  if (baseName) {
    sq_pushstring(v,baseName,-1);
    if (SQ_FAILED(sq_get(v,-3))) { // Make sure the base exists if specified by baseName.
      sq_settop(v,oldtop);
      return FALSE;
    } // if
  } // if
  if (SQ_FAILED(sq_newclass(v,baseName ? 1 : 0))) { // Will inherit from base class on stack from sq_get() above.
    sq_settop(v,oldtop);
    return FALSE;
  } // if
  newClass.AttachToStackObject(-1);
  sq_settypetag(v,-1,classType);
  sq_createslot(v,-3);
  sq_pop(v,1);
  return TRUE;
} // CreateClass

SquirrelObject RegisterClassType(HSQUIRRELVM v,const SQChar * scriptClassName,SQUserPointer classType,SQFUNCTION constructor) {
  int top = sq_gettop(v);
  SquirrelObject newClass;
  if (GetjISQ()->CreateClass(v,newClass,classType,scriptClassName)) {
    SquirrelVM::CreateFunction(newClass,constructor,_T("constructor"));
  } // if
  sq_settop(v,top);
  return newClass;
} // RegisterClassType


//--------------------------------------------------------------------------
BOOL jSquirrel::CreateConstructNativeClassInstance(HSQUIRRELVM v,const SQChar * className) 
//--------------------------------------------------------------------------
{
	int oldtop = sq_gettop(v);
	sq_pushroottable(v);
	sq_pushstring(v,className,-1);
	if (SQ_FAILED(sq_rawget(v,-2))) { // Get the class (created with sq_newclass()).
		sq_settop(v,oldtop);
		return FALSE;
	} // if
#if 0
	sq_remove(v,-3); // Remove the root table.
	sq_push(v,1);    // Push the 'this'.
#else // Kamaitati's change. 5/28/06 jcs.
	sq_remove(v,-2); // Remove the root table. 
	sq_pushroottable(v); // Push the 'this'.
#endif
	if (SQ_FAILED(sq_call(v,1,SQTrue,SQ_CALL_RAISE_ERROR))) { // Call ClassName(): creates new instance and calls constructor (instead of sq_createinstance() where constructor is not called).
		sq_settop(v,oldtop);
		return FALSE;
	} // if
	sq_remove(v,-2); // Remove the class.
	//  int newtop = sq_gettop(v);
	return TRUE;
} // CreateConstructNativeClassInstance



//--------------------------------------------------------------------------
void jSquirrel::createInstanceSetGetHandlers(SquirrelObject & so) 
//--------------------------------------------------------------------------
{
	if (!so.Exists(_T("_set"))) {
		SquirrelVM::CreateFunction(so,setInstanceVarFunc,_T("_set"),_T("sn|b|s|x")); // String var name = number(int or float) or bool or string or instance.
		SquirrelVM::CreateFunction(so,getInstanceVarFunc,_T("_get"),_T("s"));      // String var name.
	} // if
} // createInstanceSetGetHandlers


//--------------------------------------------------------------------------
void jSquirrel::createTableSetGetHandlers(SquirrelObject & so) 
//--------------------------------------------------------------------------
{
	SquirrelObject delegate = so.GetDelegate();
	if (!delegate.Exists(_T("_set"))) {
		delegate = SquirrelVM::CreateTable();
		SquirrelVM::CreateFunction(delegate,setVarFunc,_T("_set"),_T("sn|b|s")); // String var name = number(int or float) or bool or string.
		SquirrelVM::CreateFunction(delegate,getVarFunc,_T("_get"),_T("s"));      // String var name.
		so.SetDelegate(delegate);
	} // if
} // createTableSetGetHandlers



///////////////////////////////////////////////////////////////////////////
// GCC often has problems with finding inline functions at link time
// (that also have a template definition). To solve the problem,
// non-inlines goes here.
#ifdef GCC_INLINE_WORKAROUND
# include "SqPlusFunctionCallImpl.h"
#endif  // GCC_INLINE_WORKAROUND 
///////////////////////////////////////////////////////////////////////////

}; // namespace nSQ
} //nMech

// sqPlus
