/* file : jGridNode_DummyClient.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-28 23:05:06
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jGridNode_Player_header__DTjGridNode_DummyClient
#define __jGridNode_Player_header__DTjGridNode_DummyClient
#pragma once


class T_SERVER_LIB_API jGridNode_DummyClient : public nNET::jIGridNode
{
public:
#pragma warning(disable : 4251)
	jDECLARE_RTTIOBJ(jGridNode_DummyClient);
#pragma warning(default : 4251)
	virtual void Create()
	{
	}
	virtual void Destroy()
	{
	}
public:

};



#endif // __jGridNode_Player_header__DTjGridNode_DummyClient
