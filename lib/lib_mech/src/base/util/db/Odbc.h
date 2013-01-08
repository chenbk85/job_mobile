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
#define db_code_start() try {

#define db_code_end() \
} \
	catch(...) { \
	}

namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{

			const unsigned long MAX_CONNECT	= 128;

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

			class CDBHandle
			{
			private:
				SQLHSTMT			m_hstmt;
				COdbc* m_pDB;
			public:
				//CDBHandle(SQLHDBC hdbc, LPCRITICAL_SECTION pcs) 
				CDBHandle(COdbc& db)
				{
					m_pDB = &db;
					m_hstmt = NULL;
					EnterCriticalSection(&m_pDB->m_csDBHandle);
					SQLAllocHandle((SQLSMALLINT)SQL_HANDLE_STMT, m_pDB->m_hdbc, &m_hstmt);
				};
				~CDBHandle() 
				{
					SQLFreeHandle((SQLSMALLINT)SQL_HANDLE_STMT, m_hstmt);
					LeaveCriticalSection(&m_pDB->m_csDBHandle);
				};

				inline SQLHSTMT GetHandle() { return m_hstmt;};
			};

		}// nDB
	}// nUTIL
}// nMech


#endif	// _ODBC_H