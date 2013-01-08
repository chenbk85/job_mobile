/* file : jIGridNode.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:42:03
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCommonServer_Header.h"
#include "jGridNode_Server.h"


#define define_rtti_class_jGridNode_Server(name,serverid_begin,TAG)	\
	jDEFINE_RTTIOBJ(jGridNode_##name,jINetGrid,10,50);\
	void jGridNode_##name::Destroy(){m_szName[0]=0;jLOG("jGridNode_%s::Destroy()",_T(#name));}\
	void jGridNode_##name::Create(){m_eType=e##name;m_szName[0]=0;jLOG("jGridNode_%s::Create()",_T(#name));}\

for_each_SERVER_TYPE(define_rtti_class_jGridNode_Server);


