/* 
	filename:	jRTTI.h
	coder	:	Cho Hyun Min (by icandoit) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-10-20 ¿ÀÈÄ 4:39:53


*/


#ifndef __jRtti_h__
#define __jRtti_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

#include "header\\yVector.h"

namespace nMech
{

#define jDECLARE_RTTIOBJ(className)                    \
	jDECLEAR_SIMPLE_MEMORY(className)\
	static nMech::jRttiConcrete<className> ms_RTTI;      \
	virtual nMech::jRTTI* getClassRep() const;\
	static cstr getClassName() { return ms_RTTI.getClassName(); }


#define jDEFINE_RTTIOBJ(className,scope,iObj , iSlot)\
	jDEFINE_SIMPLE_MEMORY(className,iObj,iSlot);\
	nMech::jRTTI* className::getClassRep() const { return &className::ms_RTTI; }           \
	nMech::jRttiConcrete<className> className::ms_RTTI(_T(#className),_T(#scope));

#define jDEFINE_RTTIOBJ_BY_SCOPE(className,scope,iObj , iSlot)\
	jDEFINE_SIMPLE_MEMORY(className,iObj,iSlot);\
	nMech::jRTTI* className::getClassRep() const { return &className::ms_RTTI; }           \
	nMech::jRttiConcrete<className> className::ms_RTTI(_T(#className),_T(#scope),true);

#define jDEFINE_RTTIOBJ_BY_SCOPE_NICK(className,scope,NICK,iObj , iSlot)\
	jDEFINE_SIMPLE_MEMORY(className,iObj,iSlot);\
	nMech::jRTTI* className::getClassRep() const { return &className::ms_RTTI; }           \
	nMech::jRttiConcrete<className> className::ms_RTTI(_T(#NICK),_T(#scope),true);


	class jRttiObj;
	//---------------------------------------------------------------
	class JBASE_API jRTTI
		//----------------------------------------------------------------
	{
	public:
		cstr	m_szScope;
		cstr	m_szClassName;
		cstr getClassName() const	{		return m_szClassName;	}
		static jRttiObj* New(cstr  in_pClassName, cstr szScope=0);
		static void Del(jRttiObj* pO);
	protected:
		static void registerClassRep(jRTTI*,bool bScopeFirst=false);

		virtual jRttiObj* __New      () const = 0;
		virtual void __Del(jRttiObj* pO) =0;
	};

	//---------------------------------------------------------------
	template <class T>		class jRttiConcrete : public jRTTI
		//----------------------------------------------------------------
	{
	public:

		friend class jRttiObj;

		jRttiConcrete(cstr name,cstr szScope,bool bScopeFirst=false)
		{
			m_szScope = szScope;
			m_szClassName = name;
			registerClassRep(this,bScopeFirst);
		};

		virtual ~jRttiConcrete() { }

	public:
		/// Wrap constructor.
		jRttiObj* __New() const { return T::_push_back(); }
		void __Del(jRttiObj* pO) { T::_erase( (T*)pO); 	}
	};

	//---------------------------------------------------------------
	class JBASE_API jRttiObj : public nDataStruct::ySimpleNode<jRttiObj>
		//----------------------------------------------------------------
	{
	public:
		virtual jRTTI* getClassRep()const { return 0;}
		virtual void* GetInterfaceRTTI(StringID id){ return 0;}
		virtual void Create()	{	};
		virtual void Destroy()	{	};
		void CopyFrom(const jRttiObj& o){}
	};
}

#endif //__jRtti_h__

