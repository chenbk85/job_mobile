
namespace nMech
{
	namespace nSQ
	{

inline SquirrelObject::SquirrelObject(void)
{
	 GetjISQ()->sq_resetobject(&_o);
}

inline SquirrelObject::~SquirrelObject()
{
	if(GetjISQ() && GetjISQ()->VM_GetVMPtr())
		GetjISQ()->sq_release(GetjISQ()->VM_GetVMPtr(),&_o);
}

inline SquirrelObject::SquirrelObject(const SquirrelObject &o)
{
	_o = o._o;
	GetjISQ()->sq_addref(GetjISQ()->VM_GetVMPtr(),&_o);
}
inline SquirrelObject::SquirrelObject(SquirrelObject &o)
{
	_o = o._o;
	GetjISQ()->sq_addref(GetjISQ()->VM_GetVMPtr(),&_o);
}

inline SquirrelObject::SquirrelObject(HSQOBJECT o)
{
	_o = o;
	GetjISQ()->sq_addref(GetjISQ()->VM_GetVMPtr(),&_o);
}

inline void SquirrelObject::Reset(void) {
  if(GetjISQ()->VM_GetVMPtr())
    GetjISQ()->sq_release(GetjISQ()->VM_GetVMPtr(),&_o);
  GetjISQ()->sq_resetobject(&_o);
} // SquirrelObject::Reset

inline SquirrelObject SquirrelObject::Clone()
{
	SquirrelObject ret;
	if(GetType() == OT_TABLE || GetType() == OT_ARRAY)
	{
		GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
		GetjISQ()->sq_clone(GetjISQ()->VM_GetVMPtr(),-1);
		ret.AttachToStackObject(-1);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),2);
	}
	return ret;

}

inline SquirrelObject & SquirrelObject::operator =(const SquirrelObject &o)
{
	HSQOBJECT t;
	t = o._o;
	GetjISQ()->sq_addref(GetjISQ()->VM_GetVMPtr(),&t);
	GetjISQ()->sq_release(GetjISQ()->VM_GetVMPtr(),&_o);
	_o = t;
	return *this;
}

inline SquirrelObject & SquirrelObject::operator =(int n)
{
	GetjISQ()->sq_pushinteger(GetjISQ()->VM_GetVMPtr(),n);
	AttachToStackObject(-1);
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return *this;
}

inline void SquirrelObject::ArrayAppend(const SquirrelObject &o)
{
	if(sq_isarray(_o)) {
		GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
		GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),o._o);
		GetjISQ()->sq_arrayappend(GetjISQ()->VM_GetVMPtr(),-2);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
}

inline void SquirrelObject::AttachToStackObject(int idx)
{
	HSQOBJECT t;
	HSQUIRRELVM _VM = GetjISQ()->VM_GetVMPtr();
	GetjISQ()->sq_getstackobj(_VM,idx,&t);
	GetjISQ()->sq_addref(_VM,&t);
	GetjISQ()->sq_release(_VM,&_o);
	_o = t;
}

inline BOOL SquirrelObject::SetDelegate(SquirrelObject &obj)
{
	if(obj.GetType() == OT_TABLE ||
		obj.GetType() == OT_NULL) {
			HSQUIRRELVM _VM = GetjISQ()->VM_GetVMPtr();
			switch(_o._type) {
				case OT_USERDATA:
				case OT_TABLE:
					GetjISQ()->sq_pushobject(_VM,_o);
					GetjISQ()->sq_pushobject(_VM,obj._o);
					if(SQ_SUCCEEDED(GetjISQ()->sq_setdelegate(_VM,-2))) {
						GetjISQ()->sq_pop(_VM,1);
						return TRUE;
					}
					GetjISQ()->sq_pop(_VM,1);
					break;
			}
		}
	return FALSE;
}

inline SquirrelObject SquirrelObject::GetDelegate()
{
	SquirrelObject ret;
	if(_o._type == OT_TABLE || _o._type == OT_USERDATA)
	{
		HSQUIRRELVM _VM = GetjISQ()->VM_GetVMPtr();

    int top = GetjISQ()->sq_gettop(_VM);
		GetjISQ()->sq_pushobject(_VM,_o);
		GetjISQ()->sq_getdelegate(_VM,-1);
		ret.AttachToStackObject(-1);
    GetjISQ()->sq_settop(_VM,top);
//		GetjISQ()->sq_pop(_VM,2);
	}
	return ret;
}

inline BOOL SquirrelObject::IsNull() const
{
	return sq_isnull(_o);
}

inline BOOL SquirrelObject::IsNumeric() const
{
	return sq_isnumeric(_o);
}

inline int SquirrelObject::Len() const
{
	int ret = 0;
	if(sq_isarray(_o) || sq_istable(_o) || sq_isstring(_o)) {
		HSQUIRRELVM _VM = GetjISQ()->VM_GetVMPtr();
		GetjISQ()->sq_pushobject(_VM,_o);
		ret = GetjISQ()->sq_getsize(_VM,-1);
		GetjISQ()->sq_pop(_VM,1);
	}
	return ret;
}

#define _SETVALUE_INT_BEGIN \
	BOOL ret = FALSE; \
	int top = GetjISQ()->sq_gettop(GetjISQ()->VM_GetVMPtr()); \
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o); \
	GetjISQ()->sq_pushinteger(GetjISQ()->VM_GetVMPtr(),key);

#define _SETVALUE_INT_END \
	if(SQ_SUCCEEDED(GetjISQ()->sq_rawset(GetjISQ()->VM_GetVMPtr(),-3))) { \
		ret = TRUE; \
	} \
	GetjISQ()->sq_settop(GetjISQ()->VM_GetVMPtr(),top); \
	return ret;

inline BOOL SquirrelObject::SetValue(INT key,const SquirrelObject &val)
{
	_SETVALUE_INT_BEGIN
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),val._o);
	_SETVALUE_INT_END
}

inline BOOL SquirrelObject::SetValue(INT key,INT n)
{
	_SETVALUE_INT_BEGIN
	GetjISQ()->sq_pushinteger(GetjISQ()->VM_GetVMPtr(),n);
	_SETVALUE_INT_END
}

inline BOOL SquirrelObject::SetValue(INT key,FLOAT f)
{
	_SETVALUE_INT_BEGIN
	GetjISQ()->sq_pushfloat(GetjISQ()->VM_GetVMPtr(),f);
	_SETVALUE_INT_END
}

inline BOOL SquirrelObject::SetValue(INT key,const SQChar *s)
{
	_SETVALUE_INT_BEGIN
	GetjISQ()->sq_pushstring(GetjISQ()->VM_GetVMPtr(),s,-1);
	_SETVALUE_INT_END
}

inline BOOL SquirrelObject::SetValue(INT key,bool b)
{
	_SETVALUE_INT_BEGIN
	GetjISQ()->sq_pushbool(GetjISQ()->VM_GetVMPtr(),b);
	_SETVALUE_INT_END
}

inline BOOL SquirrelObject::SetValue(const SquirrelObject &key,const SquirrelObject &val)
{
	BOOL ret = FALSE;
	int top = GetjISQ()->sq_gettop(GetjISQ()->VM_GetVMPtr());
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),key._o);
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),val._o);
	if(SQ_SUCCEEDED(GetjISQ()->sq_rawset(GetjISQ()->VM_GetVMPtr(),-3))) {
		ret = TRUE;
	}
	GetjISQ()->sq_settop(GetjISQ()->VM_GetVMPtr(),top);
	return ret;
}

#define _SETVALUE_STR_BEGIN \
	BOOL ret = FALSE; \
	int top = GetjISQ()->sq_gettop(GetjISQ()->VM_GetVMPtr()); \
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o); \
	GetjISQ()->sq_pushstring(GetjISQ()->VM_GetVMPtr(),key,-1);

#define _SETVALUE_STR_END \
	if(SQ_SUCCEEDED(GetjISQ()->sq_rawset(GetjISQ()->VM_GetVMPtr(),-3))) { \
		ret = TRUE; \
	} \
	GetjISQ()->sq_settop(GetjISQ()->VM_GetVMPtr(),top); \
	return ret;

inline BOOL SquirrelObject::SetValue(const SQChar *key,const SquirrelObject &val)
{
	_SETVALUE_STR_BEGIN
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),val._o);
	_SETVALUE_STR_END
}

inline BOOL SquirrelObject::SetValue(const SQChar *key,INT n)
{
	_SETVALUE_STR_BEGIN
	GetjISQ()->sq_pushinteger(GetjISQ()->VM_GetVMPtr(),n);
	_SETVALUE_STR_END
}

inline BOOL SquirrelObject::SetValue(const SQChar *key,FLOAT f)
{
	_SETVALUE_STR_BEGIN
	GetjISQ()->sq_pushfloat(GetjISQ()->VM_GetVMPtr(),f);
	_SETVALUE_STR_END
}

inline BOOL SquirrelObject::SetValue(const SQChar *key,const SQChar *s)
{
	_SETVALUE_STR_BEGIN
	GetjISQ()->sq_pushstring(GetjISQ()->VM_GetVMPtr(),s,-1);
	_SETVALUE_STR_END
}

inline BOOL SquirrelObject::SetValue(const SQChar *key,bool b)
{
	_SETVALUE_STR_BEGIN
	GetjISQ()->sq_pushbool(GetjISQ()->VM_GetVMPtr(),b);
	_SETVALUE_STR_END
}

// === BEGIN User Pointer, User Data ===

inline BOOL SquirrelObject::SetUserPointer(const SQChar * key,SQUserPointer up) {
  _SETVALUE_STR_BEGIN
  GetjISQ()->sq_pushuserpointer(GetjISQ()->VM_GetVMPtr(),up);
  _SETVALUE_STR_END
} // SquirrelObject::SetUserPointer

inline SQUserPointer SquirrelObject::GetUserPointer(const SQChar * key) {
  SQUserPointer ret = NULL;
  if (GetSlot(key)) {
    GetjISQ()->sq_getuserpointer(GetjISQ()->VM_GetVMPtr(),-1,&ret);
    GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
  } // if
  GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
  return ret;
} // SquirrelObject::GetUserPointer

inline BOOL SquirrelObject::SetUserPointer(INT key,SQUserPointer up) {
  _SETVALUE_INT_BEGIN
  GetjISQ()->sq_pushuserpointer(GetjISQ()->VM_GetVMPtr(),up);
  _SETVALUE_INT_END
} // SquirrelObject::SetUserPointer

inline SQUserPointer SquirrelObject::GetUserPointer(INT key) {
  SQUserPointer ret = NULL;
  if (GetSlot(key)) {
    GetjISQ()->sq_getuserpointer(GetjISQ()->VM_GetVMPtr(),-1,&ret);
    GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
  } // if
  GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
  return ret;
} // SquirrelObject::GetUserPointer

// === User Data ===

inline BOOL SquirrelObject::NewUserData(const SQChar * key,INT size,SQUserPointer * typetag) {
  _SETVALUE_STR_BEGIN
  GetjISQ()->sq_newuserdata(GetjISQ()->VM_GetVMPtr(),size);
  if (typetag) {
    GetjISQ()->sq_settypetag(GetjISQ()->VM_GetVMPtr(),-1,typetag);
  } // if
  _SETVALUE_STR_END
} // SquirrelObject::NewUserData

inline BOOL SquirrelObject::GetUserData(const SQChar * key,SQUserPointer * data,SQUserPointer * typetag) {
  BOOL ret = false;
  if (GetSlot(key)) {
    GetjISQ()->sq_getuserdata(GetjISQ()->VM_GetVMPtr(),-1,data,typetag);
    GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
    ret = true;
  } // if
  GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
  return ret;
} // SquirrelObject::GetUserData

inline BOOL SquirrelObject::RawGetUserData(const SQChar * key,SQUserPointer * data,SQUserPointer * typetag) {
  BOOL ret = false;
  if (RawGetSlot(key)) {
    GetjISQ()->sq_getuserdata(GetjISQ()->VM_GetVMPtr(),-1,data,typetag);
    GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
    ret = true;
  } // if
  GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
  return ret;
} // SquirrelObject::RawGetUserData

// === END User Pointer ===

// === BEGIN Arrays ===

inline BOOL SquirrelObject::ArrayResize(INT newSize) {
//  int top = GetjISQ()->sq_gettop(GetjISQ()->VM_GetVMPtr());
  GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),GetObjectHandle());
  BOOL res = GetjISQ()->sq_arrayresize(GetjISQ()->VM_GetVMPtr(),-1,newSize) == SQ_OK;
  GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
//  GetjISQ()->sq_settop(GetjISQ()->VM_GetVMPtr(),top);
  return res;
} // SquirrelObject::ArrayResize

inline BOOL SquirrelObject::ArrayExtend(INT amount) {
  int newLen = Len()+amount;
  return ArrayResize(newLen);
} // SquirrelObject::ArrayExtend

inline BOOL SquirrelObject::ArrayReverse(void) {
  GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),GetObjectHandle());
  BOOL res = GetjISQ()->sq_arrayreverse(GetjISQ()->VM_GetVMPtr(),-1) == SQ_OK;
  GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
  return res;
} // SquirrelObject::ArrayReverse

inline SquirrelObject SquirrelObject::ArrayPop(SQBool returnPoppedVal) {
  SquirrelObject ret;
  int top = GetjISQ()->sq_gettop(GetjISQ()->VM_GetVMPtr());
  GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),GetObjectHandle());
  if (GetjISQ()->sq_arraypop(GetjISQ()->VM_GetVMPtr(),-1,returnPoppedVal) == SQ_OK) {
    if (returnPoppedVal) {
      ret.AttachToStackObject(-1);
    } // if
  } // if
  GetjISQ()->sq_settop(GetjISQ()->VM_GetVMPtr(),top);
  return ret;
} // SquirrelObject::ArrayPop

// === END Arrays ===

inline SQObjectType SquirrelObject::GetType()
{
	return _o._type;
}

inline BOOL SquirrelObject::GetSlot(INT key) const
{
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
	GetjISQ()->sq_pushinteger(GetjISQ()->VM_GetVMPtr(),key);
	if(SQ_SUCCEEDED(GetjISQ()->sq_get(GetjISQ()->VM_GetVMPtr(),-2))) {
		return TRUE;
	}
	
	return FALSE;
}


inline SquirrelObject SquirrelObject::GetValue(INT key)const
{
	SquirrelObject ret;
	if(GetSlot(key)) {
		ret.AttachToStackObject(-1);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline FLOAT SquirrelObject::GetFloat(INT key) const
{
	FLOAT ret = 0.0f;
	if(GetSlot(key)) {
		GetjISQ()->sq_getfloat(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline INT SquirrelObject::GetInt(INT key) const
{
	INT ret = 0;
	if(GetSlot(key)) {
		GetjISQ()->sq_getinteger(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline const SQChar *SquirrelObject::GetString(INT key) const
{
	const SQChar *ret = NULL;
	if(GetSlot(key)) {
		GetjISQ()->sq_getstring(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline bool SquirrelObject::GetBool(INT key) const
{
	SQBool ret = FALSE;
	if(GetSlot(key)) {
		GetjISQ()->sq_getbool(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret?true:false;
}

inline BOOL SquirrelObject::Exists(const SQChar *key) const
{
	BOOL ret = FALSE;
	if(GetSlot(key)) {
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),2);
		return TRUE;
	}

	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return FALSE;
}
////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

inline BOOL SquirrelObject::GetSlot(const SQChar *name) const
{
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
	GetjISQ()->sq_pushstring(GetjISQ()->VM_GetVMPtr(),name,-1);
	if(SQ_SUCCEEDED(GetjISQ()->sq_get(GetjISQ()->VM_GetVMPtr(),-2))) {
		return TRUE;
	}
	
	return FALSE;
}

inline BOOL SquirrelObject::RawGetSlot(const SQChar *name) const {
  GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
  GetjISQ()->sq_pushstring(GetjISQ()->VM_GetVMPtr(),name,-1);
  if(SQ_SUCCEEDED(GetjISQ()->sq_rawget(GetjISQ()->VM_GetVMPtr(),-2))) {
    return TRUE;
  }
  return FALSE;
} // SquirrelObject::RawGetSlot

inline SquirrelObject SquirrelObject::GetValue(const SQChar *key)const
{
	SquirrelObject ret;
	if(GetSlot(key)) {
		ret.AttachToStackObject(-1);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline FLOAT SquirrelObject::GetFloat(const SQChar *key) const
{
	FLOAT ret = 0.0f;
	if(GetSlot(key)) {
		GetjISQ()->sq_getfloat(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline INT SquirrelObject::GetInt(const SQChar *key) const
{
	INT ret = 0;
	if(GetSlot(key)) {
		GetjISQ()->sq_getinteger(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline const SQChar *SquirrelObject::GetString(const SQChar *key) const
{
	const SQChar *ret = NULL;
	if(GetSlot(key)) {
		GetjISQ()->sq_getstring(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret;
}

inline bool SquirrelObject::GetBool(const SQChar *key) const
{
	SQBool ret = FALSE;
	if(GetSlot(key)) {
		GetjISQ()->sq_getbool(GetjISQ()->VM_GetVMPtr(),-1,&ret);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	}
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return ret?true:false;
}

inline SQUserPointer SquirrelObject::GetInstanceUP(SQUserPointer tag) const
{
	SQUserPointer up;
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
  if (SQ_FAILED(GetjISQ()->sq_getinstanceup(GetjISQ()->VM_GetVMPtr(),-1,(SQUserPointer*)&up,tag))) {
    GetjISQ()->sq_reseterror(GetjISQ()->VM_GetVMPtr());
    up = NULL;
  } // if
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return up;
}

inline BOOL SquirrelObject::SetInstanceUP(SQUserPointer up)
{
	if(!sq_isinstance(_o)) return FALSE;
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
	GetjISQ()->sq_setinstanceup(GetjISQ()->VM_GetVMPtr(),-1,up);
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),1);
	return TRUE;
}

inline SquirrelObject SquirrelObject::GetAttributes(const SQChar *key)
{
	SquirrelObject ret;
	int top = GetjISQ()->sq_gettop(GetjISQ()->VM_GetVMPtr());
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
	if(key)
		GetjISQ()->sq_pushstring(GetjISQ()->VM_GetVMPtr(),key,-1);
	else
		GetjISQ()->sq_pushnull(GetjISQ()->VM_GetVMPtr());
	if(SQ_SUCCEEDED(GetjISQ()->sq_getattributes(GetjISQ()->VM_GetVMPtr(),-2))) {
		ret.AttachToStackObject(-1);
	}
	GetjISQ()->sq_settop(GetjISQ()->VM_GetVMPtr(),top);
	return ret;
}

inline BOOL SquirrelObject::BeginIteration()
{
	if(!sq_istable(_o) && !sq_isarray(_o) && !sq_isclass(_o))
		return FALSE;
	GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),_o);
	GetjISQ()->sq_pushnull(GetjISQ()->VM_GetVMPtr());
	return TRUE;
}

inline BOOL SquirrelObject::Next(SquirrelObject &key,SquirrelObject &val)
{
	if(SQ_SUCCEEDED(GetjISQ()->sq_next(GetjISQ()->VM_GetVMPtr(),-2))) {
		key.AttachToStackObject(-2);
		val.AttachToStackObject(-1);
		GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),2);
		return TRUE;
	}
	return FALSE;
}

inline BOOL SquirrelObject::GetTypeTag(SQUserPointer * typeTag) {
  if (SQ_SUCCEEDED(GetjISQ()->sq_getobjtypetag(&_o,typeTag))) {
    return TRUE;
  } // if
  return FALSE;
} // SquirrelObject::GetTypeTag

inline const SQChar * SquirrelObject::GetTypeName(const SQChar * key) {
#if 1
  // This version will work even if SQ_SUPPORT_INSTANCE_TYPE_INFO is not enabled.
  nSQ::ScriptStringVar256 varNameTag;
  nSQ::getVarNameTag(varNameTag,sizeof(varNameTag),key);
  SQUserPointer data=0;
  if (!RawGetUserData(varNameTag,&data)) {
    return NULL;
  } // if
  nSQ::VarRefPtr vr = (nSQ::VarRefPtr)data;
  return vr->typeName;
#else // This version will only work if SQ_SUPPORT_INSTANCE_TYPE_INFO is enabled.
  SquirrelObject so = GetValue(key);
  if (so.IsNull()) return NULL;
  return so.GetTypeName();
#endif
} // SquirrelObject::GetTypeName

inline const SQChar * SquirrelObject::GetTypeName(INT key) {
  SquirrelObject so = GetValue(key);
  if (so.IsNull()) return NULL;
  return so.GetTypeName();
} // SquirrelObject::GetTypeName

inline const SQChar * SquirrelObject::GetTypeName(void) {
  SQUserPointer typeTag=NULL;
  if (SQ_SUCCEEDED(GetjISQ()->sq_getobjtypetag(&_o,&typeTag))) {
    SquirrelObject typeTable = GetjISQ()->VM_GetRootTable().GetValue(SQ_PLUS_TYPE_TABLE);
    if (typeTable.IsNull()) {
      return NULL; // Not compiled with SQ_SUPPORT_INSTANCE_TYPE_INFO enabled.
    } // if
    return typeTable.GetString(INT((size_t)typeTag));
  } // if
  return NULL;
} // SquirrelObject::GetTypeName

inline const SQChar* SquirrelObject::ToString()
{
	return GetjISQ()->sq_objtostring(&_o);
}

inline SQInteger SquirrelObject::ToInteger()
{
	return GetjISQ()->sq_objtointeger(&_o);
}

inline SQFloat SquirrelObject::ToFloat()
{
	return GetjISQ()->sq_objtofloat(&_o);
}

inline bool SquirrelObject::ToBool()
{
	//<<FIXME>>
	return _o._unVal.nInteger?true:false;
}

inline void SquirrelObject::EndIteration()
{
	GetjISQ()->sq_pop(GetjISQ()->VM_GetVMPtr(),2);
}


}//nSQ
}//nMech