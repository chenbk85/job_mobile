/* file : jGridNode_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:42:03
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"


jDEFINE_YVECTOR_MANAGER(jGridNode_Server, 256,10);

jGridNode_Server::jGridNode_Server()
{
	m_uid = 0;
}

int jGridNode_Server::StartPlayTime()
{
	m_playTime = GetTickCount();
	return 0;
}

int jGridNode_Server::GetPlayTime()
{
	uint32 rTime = GetTickCount() - m_playTime;		
	return rTime > 0 ? rTime / 60000 : 0; //1000*60 ∫–¥‹¿ß
}
