#ifndef _ODBC_H
#define _ODBC_H
#pragma once

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <string.h>
#include <odbcss.h>
#include <tchar.h>
#pragma comment(lib, "odbc32.lib")

#define SQLOK(nResult)	(nResult == SQL_SUCCESS || nResult == SQL_SUCCESS_WITH_INFO)

namespace nMech
{
	namespace nNET
	{
		namespace nDB
		{
			const unsigned long MAX_CONNECT	= 128;

			class CDBHandle
			{
			public:
				CDBHandle(SQLHDBC hdbc, LPCRITICAL_SECTION pcs) 
				{
					m_hstmt = NULL;
					EnterCriticalSection(pcs);
					m_pCS = pcs;
					SQLAllocHandle((SQLSMALLINT)SQL_HANDLE_STMT, hdbc, &m_hstmt);
				};
				~CDBHandle() 
				{
					SQLFreeHandle((SQLSMALLINT)SQL_HANDLE_STMT, m_hstmt);
					LeaveCriticalSection(m_pCS);
				};

				inline SQLHSTMT GetHandle() { return m_hstmt;};
			private:
				SQLHSTMT			m_hstmt;
				LPCRITICAL_SECTION	m_pCS;
			};

			class JUTIL_API COdbc
			{
			public:
				COdbc(void);
				virtual ~COdbc(void);

			public:
				SQLHDBC	m_hdbc;
				CRITICAL_SECTION m_csDBHandle;

				inline bool IsOpen ();
				bool Open(LPCTSTR szDSN, LPCTSTR szUID, LPCTSTR szPWD);
				bool Open2(LPCTSTR odbcName, LPCTSTR loginName, LPCTSTR loginPwd);
				void Close();
				bool ReConnect();
				bool SQLErrorMsg(SQLHSTMT hstmt, LPCSTR errfunction);
				bool SQLErrorMsg(SQLSMALLINT HandleType, SQLHANDLE Handle);

			private:
				SQLHENV m_henv;
				SQLTCHAR m_szConnect[MAX_CONNECT];

				bool Open(); 
			};
		}// nDB
	}// nUTIL
}// nMech


#endif	// _ODBC_H