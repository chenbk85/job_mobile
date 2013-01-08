/* file : jIGridNode.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __TServerNode_header__
#define __TServerNode_header__
#pragma once

// 서버간 연결시 연결노드에 대한 객체
#include "interface/net/jINetGrid.h"

#define declare_rtti_class_jGridNode_Server(name,serverid_begin,TAG)\
struct jGridNode_##name : public jServerInfo ,public nNET::jIGridNode \
{\
	jDECLARE_RTTIOBJ(jGridNode_##name); \
	virtual void Create();\
	virtual void Destroy();\
};

for_each_SERVER_TYPE(declare_rtti_class_jGridNode_Server);

inline jServerInfo* ToServerInfo(jIGridNode* pGN)
{
	if(!pGN) return 0;
#define GetServerInfo_jNetGridHelper_234(name,serverid_begin,TAG)\
	if(!jt_strcmp(pGN->GetGridName() ,jS(jGridNode_##name) ) )\
	{\
		jGridNode_##name* pRTTI = (jGridNode_##name*)pGN;\
		return (jServerInfo*)pRTTI;\
	}

	for_each_SERVER_TYPE(GetServerInfo_jNetGridHelper_234);
	return 0;
}

#define jSI(pGN) jServerInfo* si = ToServerInfo(pGN);if(!si){ jWARN("(line=%d) si==NULL", __LINE__);return;}
#define jSI_ret(pGN,ret) jServerInfo* si = ToServerInfo(pGN);if(!si) { jWARN("(line=%d) si==NULL", __LINE__);return ret;}


#endif // __TServerNode_header__
