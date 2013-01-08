/* file : jGridNode_Server.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUser_header__
#define __AqClientUser_header__
#pragma once



#include "../TCommonServer/jServerInfo.h"

struct jIGridNode : public _ConnectedServerNode , public nDataStruct::yVectorNode<jIGridNode>
{
	jDECLEAR_YVECTOR_MANAGER(jIGridNode);

	_AqServerNodeBase_HEADER();

};


inline cstr ToString(jIGridNode*p, fname_t buf)
{
	jt_sprintf(buf, _T("uid:%d name:%s "),p-> Get_sid(),p->Get_ServerName() );
	return buf;
}
#endif // __AqClientUser_header__
