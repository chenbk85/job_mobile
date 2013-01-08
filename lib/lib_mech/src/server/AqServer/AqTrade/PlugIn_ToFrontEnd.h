/* file : PlugIn_ToFrontEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:37
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_ToFrontEnd_header__
#define __PlugIn_ToFrontEnd_header__
#pragma once

#include "AqClientUser.h"
#include "../AqCommon/jServerUser.h"

class PlugIn_ToFrontEnd: public jIPlugIn_Server_IOCP ,public jServerUsers<AqServerNode>
{
public:
	jPLUGIN_header_code(PlugIn_ToFrontEnd);

};

struct _jxFindUser_by_name
{
	acstr szID;
	_jxFindUser_by_name(acstr sz):szID(sz){}
	bool operator()(AqServerNode& pUser){return !ja_stricmp(pUser .m_szID , szID);}
};


#endif // __PlugIn_ToFrontEnd_header__
