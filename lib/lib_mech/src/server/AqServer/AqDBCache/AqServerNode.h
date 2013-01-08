/* file : AqServerNode.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUser_header__
#define __AqClientUser_header__
#pragma once



#include "../AqCommon/jServerInfo.h"

struct AqConnectedServerNode : public _ConnectedServerNode , public nDataStruct::yVectorNode<AqConnectedServerNode>
{
	jDECLEAR_YVECTOR_MANAGER(AqConnectedServerNode);

	_AqServerNodeBase_HEADER();

};


inline cstr ToString(AqConnectedServerNode*p, fname_t buf)
{
	jt_sprintf(buf, _T("uid:%d name:%s "),p-> Get_sid(),p->Get_ServerName() );
	return buf;
}
#endif // __AqClientUser_header__
