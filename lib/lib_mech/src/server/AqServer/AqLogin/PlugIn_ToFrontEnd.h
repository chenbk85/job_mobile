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

class PlugIn_ToFrontEnd: public jServerUsers<AqClientUser_L,userid_t>
{
public:
	jPLUGIN_header_code(PlugIn_ToFrontEnd);
	
	bool m_isClientVerCheck;

};


#define jLAMDA_jxFind_ByIDName(X,Z) \
	Z(acstr ,szID)
jLAMDA_find_if(jxFind_ByIDName,AqClientUser_L&)
{
	return !ja_strcmp(it.m_szID , szID);
}
jLAMDA_end();

#endif // __PlugIn_ToFrontEnd_header__
