/* file : BB_Plugin_Connection.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 11:04:50
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __BB_Plugin_Connection_header__
#define __BB_Plugin_Connection_header__
#pragma once

#include "BB_header.h"

#define BB_CON(pCon,Plugin) BB_Plugin_Connection*pCon=(BB_Plugin_Connection*)Plugin;

struct BB_Plugin_Connection : public Plugin_IConnection
{
public: 
	//--------------------------------------------------------------------------
	// Plugin_IConnection구현부.
	//--------------------------------------------------------------------------
	MOB_INTERFACE_Plugin_IConnection(BB_Plugin_NetIOModel);
	MOB_INTERFACE_Plugin_IConnection_HELP_CODE();

};

 
#endif // __BB_Plugin_Connection_header__
