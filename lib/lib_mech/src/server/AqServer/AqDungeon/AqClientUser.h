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

struct AqClientUser_D : public _AqClientUserBase , public nDataStruct::yVectorNode<AqClientUser_D>
{
	jDECLEAR_YVECTOR_MANAGER(AqClientUser_D);
	virtual void Create()
	{
		_AqClientUserBase::_Create();
	}
	virtual void Destroy()
	{
		_AqClientUserBase::_Destroy();
	}
	virtual void CopyFrom(const AqClientUser_D& o)
	{
		jAssert0(0 && "AqClientUser_D::CopyFrom");
	}

};


typedef AqClientUser_D AqClientUser;

#endif // __AqClientUser_header__
