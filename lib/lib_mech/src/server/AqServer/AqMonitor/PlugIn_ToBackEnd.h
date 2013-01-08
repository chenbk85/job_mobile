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

#include "network/protocal/PT_CentralServer_Enum.h"
#include "network/protocal/PT_TestServer_Enum.h"

using namespace nMech::nNET::nCentralServer;
using namespace nMech::nNET::nTestServer;

class PlugIn_ToBackEnd : public jIPlugIn_Net_SQ<PlugIn_ToBackEnd,jPlugIn_BE_Helper > 
{
public:
	jPLUGIN_BACK_END_header_code(PlugIn_ToBackEnd);

#define for_each_PT_MEMEBER(func)\
	func(nTestServer,TS_HELLO)\
	func(nTestServer,TS_ONLINE)\

	for_each_PT_MEMEBER(jPT_MEMBER);

	jIPacketSocket_IOCP* m_pToTestServer;
};

DECLARE_INSTANCE_TYPE(PlugIn_ToBackEnd);


extern PlugIn_ToBackEnd *g_pCurrPlugInBE;

#endif // __PlugIn_ToBackEnd_header__
