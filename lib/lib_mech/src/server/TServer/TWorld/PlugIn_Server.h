/* file : PlugIn_Server.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:37
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_Server_header__
#define __PlugIn_Server_header__
#pragma once


class PlugIn_Server: public jIPlugIn_Server_IOCP  
{
public:
	jPLUGIN_HEADER_CODE(PlugIn_Server);

	void Send_W2DC_USER_DISCONNECT(wstrings_t& uid);

};

#endif // __PlugIn_Server_header__
