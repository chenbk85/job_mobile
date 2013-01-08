/* file : jProcess.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-11-18 17:38:02
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jProcess_header__
#define __jProcess_header__
#pragma once

namespace nMech
{
	namespace nUtil
	{
		class JUTIL_API jProcess
		{
		public:
			static bool kill_Process_byName(tcstr strProcessName,DWORD skip_id,DWORD waitTime=INFINITE);
			static bool kill_Process_byID(DWORD kill_id,DWORD waitTime=INFINITE);
			static DWORD is_Exist(DWORD processID);
			static DWORD is_Exist(cstr  strProcessName);
		};
	}//namespace nUtil
}



#endif // __jProcess_header__
