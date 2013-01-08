/* file : jServerInfo.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-04 21:08:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jServerInfo.h"

void jServerInfo::Set_ServerInfo(jIE* pE , serverid_t sid, tcstr szIP)
{ 
	m_E = pE;
	m_E.AttrP(jS(m_szIP)).T() = szIP;
	jVar v = m_E.AttrP(jS(m_sid));
	v.T() = (int)sid;
	m_sid = v;
	v = m_E.AttrP(jS(m_iTotClient));
	v.T() = 0;
	m_iTotClient = m_E.AttrP(jS(m_iTotClient));

}
