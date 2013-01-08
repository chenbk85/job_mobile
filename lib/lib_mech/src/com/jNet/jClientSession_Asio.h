/* file : jAsio_ClientSession.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-03-19 19:09:55
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jAsio_ClientSession_header__
#define __jAsio_ClientSession_header__
#pragma once


#include "interface/net/jINet_asio.h"

namespace nMech
{
	namespace nNET
	{
		jIPlugin_jIClientSession_Asio* Create_Plugin_jClientSession_Asio(cstr szPlugIn,jIE* pE);
		void Stop_jClientSession_Asio(jIE* pE);
		void Run_jClientSession_Asio(jIE* pE);




	}//namespace nNET

}//namespace nMech

#endif // __jAsio_ClientSession_header__
