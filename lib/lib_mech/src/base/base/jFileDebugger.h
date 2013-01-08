/* file : jFileDebugger.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-04-03 15:28:17
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jFileDebugger_header__
#define __jFileDebugger_header__
#pragma once

namespace nMech
{
	namespace nDebug
	{
		class  JBASE_API jFileDebugger 
		{
			fname_t m_szFile;
		public:
			jFileDebugger(){ 	}
			jFileDebugger(tcstr szFile,bool isFileTimeTagAdd=false){Init(szFile,isFileTimeTagAdd);}
			void Init(tcstr szFile,bool isFileTimeTagAdd);
			void jFileDebugger::Write(TCHAR* strList, ...);
			void jFileDebugger::WriteWithTime(TCHAR* strList, ...);
		}; 

		JBASE_API void jDebugOut(TCHAR *format, ...);
		JBASE_API bool jMyAssert(bool exp, tcstr szDesc, int line ,tcstr fileName);
		JBASE_API void  jTRACE( TCHAR* s , ...);
		JBASE_API bool MakeDumpFile(IN acstr szDumpTag, IN EXCEPTION_POINTERS*exceptionInfo);

	}//nDebug

}


#endif // __jFileDebugger_header__
