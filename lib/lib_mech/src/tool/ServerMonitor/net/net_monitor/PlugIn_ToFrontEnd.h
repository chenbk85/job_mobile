/* file : PlugIn_ToFrontEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:37
comp.: wiki.test.com
title : 
desc : 

*/

#ifndef __PlugIn_ToFrontEnd_header__
#define __PlugIn_ToFrontEnd_header__
#pragma once

#include "../net_common/jServerUser.h"
#include "AqClientUser.h"

class PlugIn_ToFrontEnd: public jServerUsers<jAgentNode,dummy_id_t>
{
public:
	jPLUGIN_header_code(PlugIn_ToFrontEnd);

};
extern PlugIn_ToFrontEnd* g_pCurrPlugInFE;

struct _jxFindTestClient_by_name
{
	tcstr szID;
	_jxFindTestClient_by_name(tcstr sz):szID(sz){}
	bool operator()(jAgentNode& pUser){return !jt_stricmp(pUser.m_szComputerName , szID);}
};

#endif // __PlugIn_ToFrontEnd_header__
