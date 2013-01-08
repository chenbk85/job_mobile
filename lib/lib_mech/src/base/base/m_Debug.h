/* 
	filename:	m_Debug.h
	coder	:	Cho Wook Rea (mech12@hanmail.net)
	compiler:	vc++ 6.0
	date	:	1999 / 
	title	:	������ ������ �޼������� �ӽ����Ϸ� �����Ҷ� ���.

	ex)
		CDebug debug("�ӽ�����.txt");
		...
		...
		...
		debug.SaveValue(" �޼��� ���� : %s",msg);

*/

#if !defined(AFX_M_DEBUG_H__5E5E436C_DE33_11D2_8FBA_00A02486A654__INCLUDED_)
	#define AFX_M_DEBUG_H__5E5E436C_DE33_11D2_8FBA_00A02486A654__INCLUDED_

#if _MSC_VER > 1000
	#pragma once
#endif // _MSC_VER > 1000


///////////////////////////////////////////////
#define M_DEBUG_VAL // ���� �������� ������Ͽ� file�� ����Ҷ�.
#define M_USING_DEBUGFILE 
#define MECH_DEBUG
#define WECANDOIT_DEBUG
#define M_DEBUG
#define M_STAGE_RESULT_DEBUG

#include "base/jFolder.h"

namespace nMech
{
	namespace nDEBUG
	{
		void  JBASE_API jTRACE( TCHAR* s , ...);
		typedef void jConsolePrint_t(tcstr sz,int iDebugLevel);
		extern JBASE_API jConsolePrint_t* g_pConsolePrint;


		const int MAX_TEMP_STRLEN = 1024;
		extern JBASE_API TCHAR g_szDebug[MAX_TEMP_STRLEN];

		//#ifdef _DEBUG
#define READ_DEBUG_STATE(x)  	{_stprintf(g_szDebug , TEXT("%s : [%d]\n%s"), __FILE__,__LINE__,x);}

		inline void MY_THROW(tcstr x)
		{ 
#ifndef _WIN64
			__asm int 3; 	
#else
			__debugbreak();
#endif
			throw x;

		}


#ifdef _DEBUG
		JBASE_API void jAssertArg( bool is,TCHAR* s , ...);
#else
		inline JBASE_API void jAssertArg( bool is,TCHAR* s , ...){}
#endif


		//#ifdef _DEBUG
#ifndef jASSERT
#define jASSERT(x) if(!(x)) nDEBUG::MY_THROW(#x);
#endif



		//#define M_DEBUG // TECHMO ����� ���� ����Ҷ� ���.
		/////////////////////////////////////////////////
		class  JBASE_API CDebug {
			nFileSystem::jFolder m_DM;
			TCHAR m_pFile[256];
		public:
			CDebug(){ 	}
			CDebug(TCHAR*f)
			{
				Init(f);
			}
			void Init(TCHAR* f);
			//	~CDebug(){delete [] m_pFile;}
#ifdef M_USING_DEBUGFILE
			void CDebug::SaveValue(TCHAR* strList, ...);
			void CDebug::SaveValue1(TCHAR* strList, ...);

#else
			void CDebug::SaveValue(TCHAR* strList, ...){}
			void CDebug::SaveValue1(TCHAR* strList, ...){}
#endif
		}; 
		extern  JBASE_API CDebug g_DebugFunc;
		void  JBASE_API jDebugFunc(tcstr s);
		extern  JBASE_API bool g_isDebugFunc;
		extern JBASE_API tfname_t g_DebugStringBuf ; // ���� �Լ����� debug�� jstring�� ��ȯ�ϴ� �Լ�.

		JBASE_API bool jMyAssert(bool exp, tcstr szDesc, int line ,tcstr fileName);

	}//nDEBUG

}

#endif // !defined(AFX_M_DEBUG_H__5E5E436C_DE33_11D2_8FBA_00A02486A654__INCLUDED_)
