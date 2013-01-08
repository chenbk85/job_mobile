/* file : PlugIn_Connect.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_Connect_header__
#define __PlugIn_Connect_header__
#pragma once


#include "../TCommonServer/net_StringID.h"


class PlugIn_Connect : public jIPlugIn_Net_SQ<PlugIn_Connect,jPlugIn_ConnnectBase > 
{
public:
	jPLUGIN_HEADER_CODE_Connect(PlugIn_Connect);

};

DECLARE_INSTANCE_TYPE(PlugIn_Connect);


#endif // __PlugIn_Connect_header__
