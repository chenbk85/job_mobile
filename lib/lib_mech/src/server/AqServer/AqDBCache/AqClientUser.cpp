/* file : AqServerNode.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:42:03
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqClientUser.h"

jDEFINE_YVECTOR_MANAGER(AqServerNode, 256,10);

AqServerNode::AqServerNode()
{
	m_uid = 0;
}

int AqServerNode::StartPlayTime()
{
	m_playTime = GetTickCount();
	return 0;
}

int AqServerNode::GetPlayTime()
{
	uint32 rTime = GetTickCount() - m_playTime;		
	return rTime > 0 ? rTime / 60000 : 0; //1000*60 ∫–¥‹¿ß
}
