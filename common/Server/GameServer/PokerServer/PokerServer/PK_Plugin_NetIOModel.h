/* file : PK_Plugin_NetIOModel.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 11:04:31
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __PK_Plugin_NetIOModel_header__
#define __PK_Plugin_NetIOModel_header__
#pragma once



//#--------------------------------------------------------------------------
struct PK_Plugin_NetIOModel : public nMOB::Plugin_INetIOModel
//#--------------------------------------------------------------------------
{
public:
	MOB_DECLEAR_CONNECTION_MANAGER(PK_Plugin_Connection);
	MOB_DECLARE_ROOM_MANAGER(PK_Room);
};

extern PK_Plugin_NetIOModel g_PK_Plugin_NetIOModel;

#endif // __PK_Plugin_NetIOModel_header__

