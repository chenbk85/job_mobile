/* file : jPlayerObj.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 17:25:16
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __2323AqDBC23a3c32h32e32U323s2er_432
#define __2323AqDBC23a3c32h32e32U323s2er_432

#pragma once

#include "../TCommonBase/jPlayerBase.h"
#include "../TDBQuery/jPlayerDBSM.h"


struct jPlayerObj : public jPlayerBase
{
public:
	jPlayerBase_DECLEAR(jPlayerObj);

	jPlayerObj() : m_SharedMemory(0){}

	jPlayerDBSM*		m_SharedMemory;
	jPlayerDBSM* GetDB(){return m_SharedMemory;}
	Use_User_id_t Get_uid(){ return GetDB()->Get_uid();}
};

#endif // __2323AqDBC23a3c32h32e32U323s2er_432
