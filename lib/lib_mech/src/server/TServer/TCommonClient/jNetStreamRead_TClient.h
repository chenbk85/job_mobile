/* file : Aq_Stream.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-17 08:53:13
comp.: t3.co.kr
title : 
desc : 

클라이언트와 서버간에 공유되는 사용자 패킷 패킹/언패킹 구조체들.


참고 :jNetStreamRead_TServer.h
*/

#ifndef __Aq_Stream_header__jNetStreamRead_TClient
#define __Aq_Stream_header__jNetStreamRead_TClient
#pragma once

#include "header/nNET_Stream.h"

namespace nMech
{
	namespace nNET
	{
		namespace nStream
		{
#ifdef jError_USING_DEV_MODE
			inline void Read(jNetStreamRead& st, jError& data)
			{
				Read(st,data.iClient);
				Read(st,data.iServer);
			}
			inline void Write(jNetStreamWrite& st,const jError& data)
			{
				Write(st,data.iClient);
				Write(st,data.iServer);
			}
#endif

			inline void Read(jNetStreamRead& st, jErrorInfo& data)
			{
				Read(st,data.e);
				Read(st,data.uid);
				Read(st,data.eAction);
				Read(st,data.msg);
			}
			inline void Write(jNetStreamWrite& st,const jErrorInfo& data)
			{
				Write(st,data.e);
				Write(st,data.uid);
				Write(st,data.eAction);
				Write(st,data.msg);
			}


		}//namespace nStream
	}//namespace nNET

}//namespace nMech


#endif // __Aq_Stream_header__jNetStreamRead_TClient
