/* file : jIPerfCounter.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-02 10:03:31
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jIPerfCounter_header__
#define __jIPerfCounter_header__
#pragma once

namespace nMech
{
	namespace nLOG
	{
		struct jIPerfCounter
		{
			virtual BOOL Begin(tcstr szServiceName)=0;
			virtual BOOL End(VOID)=0;
			virtual BOOL AddCounter(LPCTSTR name,tcstr szHelp)=0;
			virtual BOOL UpdateCounter(LPCTSTR name, DWORD value)=0;
		};

	}//namespace nLOG

}//namespace nMech


#endif // __jIPerfCounter_header__
