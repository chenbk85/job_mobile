/* file : jGridNode_Client.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-28 23:05:06
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jGridNode_Player_header__
#define __jGridNode_Player_header__
#pragma once

#include "..\TCommonClient\jGridNode_ClientBase.h"

class T_SERVER_LIB_API jGridNode_Client : public jGridNode_ClientBase
{
public:
#pragma warning(disable : 4251)
	jDECLARE_RTTIOBJ(jGridNode_Client);
#pragma warning(default : 4251)
	virtual void Create()
	{
		jGridNode_ClientBase::_Create();
		m_szID[0]=0;
	}
	virtual void Destroy()
	{
		jGridNode_ClientBase::_Destroy();
	}
public:
	player_name_t m_szID;
	serverid_t world;

};



#endif // __jGridNode_Player_header__
