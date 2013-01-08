/* file : jIZipUtil.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-07-23 17:45:17
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jIZipUtil_header__
#define __jIZipUtil_header__
#pragma once

namespace nMech
{
	namespace nUtil
	{
		struct jIZipBuffer : public nInterface::jIInterface
		{
			virtual CHAR* GetZipBuff()=0;
			virtual void Init(CHAR* srcBuf, size_t srcSize)=0;
			virtual int GetZipSize()=0;
		};

		struct jIUnZipBuffer: public nInterface::jIInterface
		{
			virtual CHAR* GetUnZipBuff()=0;
			virtual void Init(CHAR* srcBuf, size_t srcSize)=0;
			virtual int GetUnZipSize()=0;
		};
	}
}


#endif // __jIZipUtil_header__
