/* file : SAMPLE_Plugin_Connection.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 11:04:50
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __SAMPLE_Plugin_Connection_header__
#define __SAMPLE_Plugin_Connection_header__
#pragma once

#include "SAMPLE_header.h"

#define SAMPLE_CON(pCon,Plugin) SAMPLE_Plugin_Connection*pCon=(SAMPLE_Plugin_Connection*)Plugin;

struct SAMPLE_Plugin_Connection : public Plugin_IConnection
{
public: 
	//--------------------------------------------------------------------------
	// Plugin_IConnection구현부.
	//--------------------------------------------------------------------------
	MOB_INTERFACE_Plugin_IConnection(SAMPLE_Plugin_NetIOModel);
	MOB_INTERFACE_Plugin_IConnection_HELP_CODE();


};

 
#endif // __SAMPLE_Plugin_Connection_header__
