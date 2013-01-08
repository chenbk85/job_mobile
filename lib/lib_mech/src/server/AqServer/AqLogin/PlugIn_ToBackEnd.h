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
};

DECLARE_INSTANCE_TYPE(PlugIn_ToBackEnd);

#define jLAMDA_jxGet_channel_list(X,Z) \
	X(vector<serverid_t>&,channel)\
	X(vector<astring>&,channel_name)\
	Z(vector<uint8>&,buzy_level)
jLAMDA_for_each(jxGet_channel_list, jIE*)
{
	nXML::jE e = it;
	if(!e.Attr(jS(m_eType))->IsContents(jS(TownServer))) return;
	channel.push_back((serverid_t)e.Attr(jS(m_sid))->Get_int());
	channel_name.push_back( jA(e->GetAttr(jS(m_szName))) );
	buzy_level.push_back(jServerInfoBase::Get_buzy_level(e));
}
jLAMDA_end();



#endif // __PlugIn_ToBackEnd_header__
