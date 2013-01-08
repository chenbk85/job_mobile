/* file : Aq_Stream.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2009-12-17 08:53:13
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __Aq_Stream_header__
#define __Aq_Stream_header__
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
			inline void Write(jNetStreamWrite& st,const jError data)
			{
				Write(st,data.iClient);
				Write(st,data.iServer);
			}
#endif

		}//namespace nStream
	}//namespace nNET

}//namespace nMech


#endif // __Aq_Stream_header__
