/* file : BB_Plugin_NetIOModel.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 11:04:31
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __BB_Plugin_NetIOModel_header__
#define __BB_Plugin_NetIOModel_header__
#pragma once



//#--------------------------------------------------------------------------
struct BB_Plugin_NetIOModel : public nMOB::Plugin_INetIOModel
//#--------------------------------------------------------------------------
{
public:
	MOB_DECLEAR_CONNECTION_MANAGER(BB_Plugin_Connection);
	MOB_DECLARE_ROOM_MANAGER(BB_Room);
};

extern BB_Plugin_NetIOModel g_BB_Plugin_NetIOModel; //MOB_IMPLEMENT_CONNECTION_MANAGER()에 정의 되어 있다.

#endif // __BB_Plugin_NetIOModel_header__

