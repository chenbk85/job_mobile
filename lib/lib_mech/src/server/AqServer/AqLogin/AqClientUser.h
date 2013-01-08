/* file : AqClientUser.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUser_header__
#define __AqClientUser_header__
#pragma once

#include "../AqCommon/AqClientUserBase.h"

struct AqClientUser_L : public _AqClientUserBase , public nDataStruct::yVectorNode<AqClientUser_L>
{
	jDECLEAR_YVECTOR_MANAGER(AqClientUser_L);

	virtual void Create()
	{
		_AqClientUserBase::_Create();
	}
	virtual void Destroy()
	{
		_AqClientUserBase::_Destroy();
	}
	virtual void CopyFrom(const AqClientUser_L& o)
	{
		jAssert0(0 && "AqClientUser_L::CopyFrom");
	}
};

typedef AqClientUser_L AqClientUser;

#endif // __AqClientUser_header__
