/* file : PlugIn_ToBackEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 10:51:11
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_ToBackEnd_header__
#define __PlugIn_ToBackEnd_header__
#pragma once


#include "../AqCommon/net_StringID.h"


class PlugIn_ToBackEnd : public jIPlugIn_Net_SQ<PlugIn_ToBackEnd,jPlugIn_BE_Helper > 
{
public:
	jPLUGIN_BACK_END_header_code(PlugIn_ToBackEnd);

	jIPacketSocket_IOCP* m_pDBSocket;
	
};

DECLARE_INSTANCE_TYPE(PlugIn_ToBackEnd);


#endif // __PlugIn_ToBackEnd_header__
