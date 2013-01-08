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

#include "../TestCommon/jServerUser.h"
#include "AqClientUser.h"

class PlugIn_ToFrontEnd: public jServerUsers<AqTestClientNode,dummy_id_t>
{
public:
	jPLUGIN_header_code(PlugIn_ToFrontEnd);

	jLIST_TYPEDEF_vector(AqTestClientNode* , m_listAqMonitor);

};
extern PlugIn_ToFrontEnd* g_pCurrPlugInFE;

struct _jxFindTestClient_by_name
{
	tcstr szID;
	_jxFindTestClient_by_name(tcstr sz):szID(sz){}
	bool operator()(AqTestClientNode& pUser){return !jt_stricmp(pUser .m_szID , szID);}
};

#endif // __PlugIn_ToFrontEnd_header__
