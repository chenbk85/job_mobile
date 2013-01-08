/* file : jMemoryDLL.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-04-11 12:56:16
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jMemoryDLL_header__
#define __jMemoryDLL_header__
#pragma once

namespace nMech
{
	class jMemoryDLL : public jIMemoryDLL
	{
		struct _DllEntry
		{
			CHAR*szDLL;
			int iSize;
			void* pMemDLL;
			HMEMORYMODULE hDLL;
		};
		jLIST_TYPEDEF_map(acstr, _DllEntry , m_DllEntryList);
		static void _DllEntryClear(m_DllEntryList_vt it);

		CHAR* m_pMemBuffer;
		int m_iSizeMemBuffer;
		tcstr GetDBName();
	public:
		~jMemoryDLL(){Close();}
		void ReadDB(tcstr szPath); //db file load & init
		void Close(); // 해제및 종료.
		void WriteDB(tcstr szPath); // db file write to GetDBName();
		HMEMORYMODULE _LoadLibrary(acstr szDLL);
		FARPROC GetProcAddress(HMEMORYMODULE hDLL,acstr szFunc);
	};

}


#endif // __jMemoryDLL_header__
