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

class PlugIn_ToFrontEnd: public jServerUsers<AqClientUser_T,userid_t>
{
private:		nXML::jE m_eWorldInfo;
private:	jLIST_TYPEDEF_map(Sys_Castle_id_t,jIE*,m_mapCastleInfo);
public:	
	jE Get_WorldInfo(){ return m_eWorldInfo;}
	jE Get_CastleInfo(Sys_Castle_id_t csid);

	jPLUGIN_header_code(PlugIn_ToFrontEnd);

};

#endif // __PlugIn_ToFrontEnd_header__
