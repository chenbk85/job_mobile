/* file : PK_Plugin_Connection.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 11:04:50
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __PK_Plugin_Connection_header__
#define __PK_Plugin_Connection_header__
#pragma once

#include "PK_header.h"

#define PK_CON(pCon,Plugin) PK_Plugin_Connection*pCon=(PK_Plugin_Connection*)Plugin;

struct PK_Plugin_Connection : public Plugin_IConnection
{
public: 
	//--------------------------------------------------------------------------
	// Plugin_IConnection구현부.
	//--------------------------------------------------------------------------
	MOB_INTERFACE_Plugin_IConnection(PK_Plugin_NetIOModel);
	MOB_INTERFACE_Plugin_IConnection_HELP_CODE();

};

 
#endif // __PK_Plugin_Connection_header__
