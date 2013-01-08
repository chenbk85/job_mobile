// ScriptObjectVector.h: interface for the CScriptObjectVector class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCRIPTOBJECTVECTOR_H__C72BCA75_0CD6_47F2_9812_177BF43A2018__INCLUDED_)
#define AFX_SCRIPTOBJECTVECTOR_H__C72BCA75_0CD6_47F2_9812_177BF43A2018__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "IScriptSystem.h"

/*! this calss map an 3d vector to a LUA table with x,y,z members
*/
class CScriptObjectVector :
public nMech::nLUA1::_SmartScriptObject
{
public:
	CScriptObjectVector()
	{
	}
	CScriptObjectVector(nMech::nLUA1::IScriptSystem *pScriptSystem,bool bCreateEmpty=false):nMech::nLUA1::_SmartScriptObject(pScriptSystem,bCreateEmpty)
	{
	}
	
	void Set(const nMech::nMath::jVec3 &v)
	{
		if(m_pSO->BeginSetGetChain())
		{
			m_pSO->SetValueChain("x",v.x);
			m_pSO->SetValueChain("y",v.y);
			m_pSO->SetValueChain("z",v.z);
			m_pSO->EndSetGetChain();
		}
	}
	nMech::nMath::jVec3 Get()
	{
		nMech::nMath::jVec3 v(0,0,0);
		if(m_pSO->BeginSetGetChain())
		{
			m_pSO->GetValueChain("x",v.x);
			m_pSO->GetValueChain("y",v.y);
			m_pSO->GetValueChain("z",v.z);
			m_pSO->EndSetGetChain();
		}
		else assert(0 && "validate before calling Get()");

		return v;
	}
/*	nMech::nMath::jVec3& operator=(CScriptObjectVector &vec)
	{
		static nMech::nMath::jVec3 v3;
		vec.Set(v3);
		return v3;
	}*/
	CScriptObjectVector &operator=(const nMech::nMath::jVec3 &v3)
	{
		Set(v3);
		return *this;
	}
};

/*! this calss map an "color" to a LUA table with x,y,z members
*/
class CScriptObjectColor :
public nMech::nLUA1::_SmartScriptObject
{
public:
	CScriptObjectColor(nMech::nLUA1::IScriptSystem *pScriptSystem,bool bCreateEmpty=false):nMech::nLUA1::_SmartScriptObject(pScriptSystem,bCreateEmpty)
	{
	}
	
	void Set(const nMech::nMath::jVec3 &v)
	{
		m_pSO->SetAt(1,v.x);
		m_pSO->SetAt(2,v.y);
		m_pSO->SetAt(3,v.z);
	}
	nMech::nMath::jVec3 &Get()
	{
		static nMech::nMath::jVec3 v(0,0,0);
		m_pSO->GetAt(1,v.x);
		m_pSO->GetAt(2,v.y);
		m_pSO->GetAt(3,v.z);
		return v;
	}
/*	nMech::nMath::jVec3& operator=(CScriptObjectVector &vec)
	{
		static nMech::nMath::jVec3 v3;
		vec.Set(v3);
		return v3;
	}*/
	CScriptObjectColor &operator=(const nMech::nMath::jVec3 &v3)
	{
		Set(v3);
		return *this;
	}
};

#endif // !defined(AFX_SCRIPTOBJECTVECTOR_H__C72BCA75_0CD6_47F2_9812_177BF43A2018__INCLUDED_)
