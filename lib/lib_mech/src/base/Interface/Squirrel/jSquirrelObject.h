#ifndef _SQUIRREL_OBJECT_H_
#define _SQUIRREL_OBJECT_H_


#pragma warning(disable : 4521)

namespace nMech{	namespace nSQ	{

class SquirrelObject
{
	friend class SquirrelVM;
public:
	SquirrelObject();
	virtual ~SquirrelObject();
	SquirrelObject(const SquirrelObject & o);
	SquirrelObject(SquirrelObject & o);
	SquirrelObject(HSQOBJECT o);
  template <typename _ty>
  SquirrelObject(const _ty & val) { nMech::GetjISQ()->sq_resetobject(&_o); Set((_ty &)val); } // Cast away const to avoid compiler nMech::nSQ::Push() match issue.
  template <typename _ty>
  SquirrelObject(_ty & val) { nMech::GetjISQ()->sq_resetobject(&_o); Set(val); }
  template <typename _ty>
  SquirrelObject(_ty * val) { nMech::GetjISQ()->sq_resetobject(&_o); SetByValue(val); } // Set() would also be OK here. SetByValue() to save potential compiler overhead.
  SquirrelObject & operator =(const SquirrelObject &o);
  SquirrelObject & operator =(int n);
  void AttachToStackObject(int idx);
  void Reset(void); // Release (any) reference and reset _o.
  SquirrelObject Clone();
  BOOL SetValue(const SquirrelObject &key,const SquirrelObject &val);
  
  BOOL SetValue(SQInteger key,const SquirrelObject &val);
  BOOL SetValue(INT key,bool b); // Compiler treats SQBool as INT.
  BOOL SetValue(INT key,INT n);
  BOOL SetValue(INT key,FLOAT f);
  BOOL SetValue(INT key,const SQChar *s);

  BOOL SetValue(const SQChar *key,const SquirrelObject &val);
  BOOL SetValue(const SQChar *key,bool b);
  BOOL SetValue(const SQChar *key,INT n);
  BOOL SetValue(const SQChar *key,FLOAT f);
  BOOL SetValue(const SQChar *key,const SQChar *s);

  BOOL SetUserPointer(const SQChar * key,SQUserPointer up);
  SQUserPointer GetUserPointer(const SQChar * key);
  BOOL SetUserPointer(INT key,SQUserPointer up);
  SQUserPointer GetUserPointer(INT key);

  BOOL NewUserData(const SQChar * key,INT size,SQUserPointer * typetag=0);
  BOOL GetUserData(const SQChar * key,SQUserPointer * data,SQUserPointer * typetag=0);
  BOOL RawGetUserData(const SQChar * key,SQUserPointer * data,SQUserPointer * typetag=0);

  // === BEGIN Arrays ===

  BOOL ArrayResize(INT newSize);
  BOOL ArrayExtend(INT amount);
  BOOL ArrayReverse(void);
  SquirrelObject ArrayPop(SQBool returnPoppedVal=SQTrue);

  void ArrayAppend(const SquirrelObject &o);

  template<typename T>
  BOOL ArrayAppend(T item);

  // === END Arrays ===

  BOOL SetInstanceUP(SQUserPointer up);
  BOOL IsNull() const;
  int IsNumeric() const;
  int Len() const;
  BOOL SetDelegate(SquirrelObject &obj);
  SquirrelObject GetDelegate();
  const SQChar* ToString();
  bool ToBool();
  SQInteger ToInteger();
  SQFloat ToFloat();
  SQUserPointer GetInstanceUP(SQUserPointer tag) const;
  SquirrelObject GetValue(const SQChar *key) const;
  BOOL Exists(const SQChar *key) const;
  FLOAT GetFloat(const SQChar *key) const;
  INT GetInt(const SQChar *key) const;
  const SQChar *GetString(const SQChar *key) const;
  bool GetBool(const SQChar *key) const;
  SquirrelObject GetValue(INT key) const;
  FLOAT GetFloat(INT key) const;
  INT GetInt(INT key) const;
  const SQChar *GetString(INT key) const;
  bool GetBool(INT key) const;
  SquirrelObject GetAttributes(const SQChar *key = NULL);
  SQObjectType GetType();
  HSQOBJECT & GetObjectHandle(){return _o;}
  BOOL BeginIteration();
  BOOL Next(SquirrelObject &key,SquirrelObject &value);
  void EndIteration();

  BOOL GetTypeTag(SQUserPointer * typeTag);

  // === Get the type name of item/object through string key in a table or class. Returns NULL if the type name is not set (not an SqPlus registered type).
  const SQChar * GetTypeName(const SQChar * key);
  // === Get the type name of item/object through INT key in a table or class. Returns NULL if the type name is not set (not an SqPlus registered type).
  const SQChar * GetTypeName(INT key);
  // === Get the type name of this object, else return NULL if not an SqPlus registered type.
  const SQChar * GetTypeName(void);

#if 1 // SqPlus.h에서 가져왔음
  // === BEGIN code suggestion from the Wiki ===
  // Get any bound type from this SquirrelObject. Note that Squirrel's handling of references and pointers still holds here.
  template<typename _ty>
  inline _ty Get(void) {
    nMech::GetjISQ()->sq_pushobject(GetjISQ()->VM_GetVMPtr(),GetObjectHandle());
    _ty val = nMech::nSQ::Get(nMech::nSQ::TypeWrapper<_ty>(),GetjISQ()->VM_GetVMPtr(),-1);
    nMech::GetjISQ()->sq_poptop(GetjISQ()->VM_GetVMPtr());
    return val;
  }

  // Set any bound type to this SquirrelObject. Note that Squirrel's handling of references and pointers still holds here.
  template<typename _ty>
  inline SquirrelObject SetByValue(_ty val) { // classes/structs should be passed by ref (below) to avoid an extra copy.
    nMech::nSQ::Push(GetjISQ()->VM_GetVMPtr(),val);
    AttachToStackObject(-1);
    nMech::GetjISQ()->sq_poptop(GetjISQ()->VM_GetVMPtr());
    return *this;
  }

  // Set any bound type to this SquirrelObject. Note that Squirrel's handling of references and pointers still holds here.
  template<typename _ty>
  inline SquirrelObject Set(_ty & val) {
    nMech::nSQ::Push(GetjISQ()->VM_GetVMPtr(),val);
    AttachToStackObject(-1);
    nMech::GetjISQ()->sq_poptop(GetjISQ()->VM_GetVMPtr());
    return *this;
  }
#else
	// === BEGIN code suggestion from the Wiki ===
	// Get any bound type from this SquirrelObject. Note that Squirrel's handling of references and pointers still holds here.
	template<typename _ty>
	_ty Get(void);

	// Set any bound type to this SquirrelObject. Note that Squirrel's handling of references and pointers still holds here.
	template<typename _ty>
	SquirrelObject SetByValue(_ty val); // classes/structs should be passed by ref (below) to avoid an extra copy.

	// Set any bound type to this SquirrelObject. Note that Squirrel's handling of references and pointers still holds here.
	template<typename _ty>
	SquirrelObject &Set(_ty & val);
#endif


  // === END code suggestion from the Wiki ===

private:
  BOOL GetSlot(const SQChar *name) const;
  BOOL RawGetSlot(const SQChar *name) const;
  BOOL GetSlot(INT key) const;
  HSQOBJECT _o;
};

struct StackHandler {
	StackHandler(HSQUIRRELVM v) {
		_top = nMech::GetjISQ()->sq_gettop(v);
		this->v = v;
	}
	SQFloat GetFloat(int idx) {
		SQFloat x = 0.0f;
		if(idx > 0 && idx <= _top) {
			nMech::GetjISQ()->sq_getfloat(v,idx,&x);
		}
		return x;
	}
	SQInteger GetInt(int idx) {
		SQInteger x = 0;
		if(idx > 0 && idx <= _top) {
			nMech::GetjISQ()->sq_getinteger(v,idx,&x);
		}
		return x;
	}
	HSQOBJECT GetObjectHandle(int idx) {
		HSQOBJECT x;
		if(idx > 0 && idx <= _top) {
			nMech::GetjISQ()->sq_resetobject(&x);
			nMech::GetjISQ()->sq_getstackobj(v,idx,&x);
		}
		return x;
	}
	const SQChar *GetString(int idx)
	{
    const SQChar *x = NULL;
		if(idx > 0 && idx <= _top) {
			nMech::GetjISQ()->sq_getstring(v,idx,&x);
		}
		return x;
	}
	SQUserPointer GetUserPointer(int idx)
	{
		SQUserPointer x = 0;
		if(idx > 0 && idx <= _top) {
			nMech::GetjISQ()->sq_getuserpointer(v,idx,&x);
		}
		return x;
	}
	SQUserPointer GetInstanceUp(int idx,SQUserPointer tag)
	{
		SQUserPointer self;
		if(SQ_FAILED(nMech::GetjISQ()->sq_getinstanceup(v,idx,(SQUserPointer*)&self,tag)))
			return NULL;
		return self;
	}
	SQUserPointer GetUserData(int idx,SQUserPointer tag=0)
	{
		SQUserPointer otag;
		SQUserPointer up;
		if(idx > 0 && idx <= _top) {
			if(SQ_SUCCEEDED(nMech::GetjISQ()->sq_getuserdata(v,idx,&up,&otag))) {
				if(tag == otag)
					return up;
			}
		}
		return NULL;
	}
	BOOL GetBool(int idx)
	{
		SQBool ret;
		if(idx > 0 && idx <= _top) {
			if(SQ_SUCCEEDED(nMech::GetjISQ()->sq_getbool(v,idx,&ret)))
				return ret;
		}
		return FALSE;
	}
	int GetType(int idx)
	{
		if(idx > 0 && idx <= _top) {
			return nMech::GetjISQ()->sq_gettype(v,idx);
		}
		return -1;
	}
	
	int GetParamCount() {
		return _top;
	}
	int Return(const SQChar *s)
	{
		nMech::GetjISQ()->sq_pushstring(v,s,-1);
		return 1;
	}
	int Return(FLOAT f)
	{
		nMech::GetjISQ()->sq_pushfloat(v,f);
		return 1;
	}
	int Return(INT i)
	{
		nMech::GetjISQ()->sq_pushinteger(v,i);
		return 1;
	}
	int Return(bool b)
	{
		nMech::GetjISQ()->sq_pushbool(v,b);
		return 1;
	}
  int Return(SQUserPointer p) {
    nMech::GetjISQ()->sq_pushuserpointer(v,p);
    return 1;
  }
	int Return(SquirrelObject &o)
	{
		nMech::GetjISQ()->sq_pushobject(v,o.GetObjectHandle());
		return 1;
	}
	int Return() { return 0; }
	int ThrowError(const SQChar *error) {
		return GetjISQ()->sq_throwerror(v,error);
	}
  HSQUIRRELVM GetVMPtr() { return v; }
private:
	int _top;
	HSQUIRRELVM v;
};


template<typename T>
inline BOOL SquirrelObject::ArrayAppend(T item) {
	jISquirrel* pSQ =  GetjISQ();
	HSQUIRRELVM _VM = pSQ->VM_GetVMPtr();
	pSQ->sq_pushobject(_VM,GetObjectHandle() );
	GetjISQ()->VM_PushValue(item);
	BOOL res = pSQ->sq_arrayappend(_VM,-2) == SQ_OK;
	pSQ->sq_pop(_VM,1);
	return res;
} // ArrayAppend


	}//namespace nSQ
}
#pragma warning(default : 4521)

#endif //_SQUIRREL_OBJECT_H_
