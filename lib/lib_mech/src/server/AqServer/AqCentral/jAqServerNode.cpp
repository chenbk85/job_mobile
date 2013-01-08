/* file : jAqServerNode1.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 13:57:38
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jAqServerNode.h"

jDEFINE_YVECTOR_MANAGER(AqConnectedServerNode, 32,10);


tcstr ToString(AqConnectedServerNode* v , tname1024_t buf)
{
	tfname_t buf1;
	long sec = (long)v->m_Timer.elapsed();
	jt_sprintf(buf, _T("-%s %s run=[%d.%d]%d.%d, %dmin") 
		,v->Base().GetServerTypeName()
		,ToString(&v->Base(),buf1)
		,v->Base().m_StartTime.wMonth
		,v->Base().m_StartTime.wDay
		,v->Base().m_StartTime.wHour
		,v->Base().m_StartTime.wMinute
		,sec/60
		);
	return buf;
}


