/* file : SAMPLE_Plugin_NetIOModel.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 11:04:31
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __SAMPLE_Plugin_NetIOModel_header__
#define __SAMPLE_Plugin_NetIOModel_header__
#pragma once



//#--------------------------------------------------------------------------
struct SAMPLE_Plugin_NetIOModel : public nMOB::Plugin_INetIOModel
//#--------------------------------------------------------------------------
{
public:
	MOB_DECLEAR_CONNECTION_MANAGER(SAMPLE_Plugin_Connection);
	MOB_DECLARE_ROOM_MANAGER(SAMPLE_Room);
};

extern SAMPLE_Plugin_NetIOModel g_SAMPLE_Plugin_NetIOModel; //MOB_IMPLEMENT_CONNECTION_MANAGER()에 정의 되어 있다.

#endif // __SAMPLE_Plugin_NetIOModel_header__

