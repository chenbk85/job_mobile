//------------------------------------------------------------------------------------
// Module Name			: ObjectBase(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObjectBase
//------------------------------------------------------------------------------------

#ifndef __Object_H__
#define __Object_H__

#pragma once

#include <string>
#include "../util/Define.h"

#define ERROR_CODE_OK	0L
#define ERROR_CODE_CANCEL	-1L
typedef long KEY_OBJPOOL;

class CObjectBase;
class CObjectMgr;

#define _OBJECTMGR(object)  (dynamic_cast<CObjectMgr*>(object))

typedef struct tagObjectBase{
public:
	tagObjectBase(void){ InittObjectBase(); }
	void InittObjectBase(void){ 
		m_nObjectID=PTR_UINT(this);
		m_pcMotherID=NULL;
		m_nObjectType=0;
	}
	void FreetObjectBase(void){
		m_nObjectID=0;
		m_pcMotherID=NULL;
		m_nObjectType=0;
	}
	void SetMotherID(void* pcMotherID){ m_pcMotherID=pcMotherID; }
	CObjectMgr* GetObjectMgr(void){ return (static_cast<CObjectMgr*>(m_pcMotherID)); }
public:
	unsigned int m_nObjectID;
	unsigned int m_nObjectType;
	void* m_pcMotherID;
}tObjectBase;

class CObjectBase : public tObjectBase
{
public:
	enum {
		OB_WAITING=0,
		OB_ITEM,
		OB_REFILL,
		MAX_VALUE,
	};
public:
	CObjectBase(void){
		InitObjectBase();
	} 

	/*
	CObjectBase(ISGRCContainer* pGRCContainer){
		InitObjectBase(); SetGRCContainer(pGRCContainer);
	} 
	*/

public:
	virtual ~CObjectBase(void){ FreeObjectBase(); }
	void InitObjectBase(void){ InittObjectBase(); }
	void FreeObjectBase(void){ FreetObjectBase(); }
public:
	/*
	virtual void SetGRCContainer(ISGRCContainer* pGRCContainer){ 
		m_pGRCContainer=pGRCContainer; 
		
	}
	*/
//protected:
	//ISGRCContainer* m_pGRCContainer;
public:
	virtual bool CreateObject(void){ return true; }
	virtual void DestroyObject(void){}
};

#endif