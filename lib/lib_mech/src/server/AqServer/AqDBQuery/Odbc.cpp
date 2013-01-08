#include "stdafx.h"
#include "odbc.h"
#include <stdio.h>


namespace nMech
{
	namespace nUtil
	{
		namespace nDB
		{

			COdbc::COdbc(void)
			{
				m_henv = SQL_NULL_HENV;
				m_hdbc = SQL_NULL_HDBC;
				memset(m_szConnect, 0, MAX_CONNECT);
				InitializeCriticalSection(&m_csDBHandle);
			}

			COdbc::~COdbc(void)
			{
				DeleteCriticalSection(&m_csDBHandle);
				if(IsOpen()) 
					Close();
			}

			bool COdbc::IsOpen()
			{
				return (m_hdbc != SQL_NULL_HANDLE);
			}

			bool COdbc::Open(LPCTSTR szDSN, LPCTSTR szUID, LPCTSTR szPWD)
			{
				memset(m_szConnect, 0, MAX_CONNECT);
				jt_sprintf((TCHAR*)m_szConnect, TEXT("DSN=%s;UID=%s;PWD=%s"), szDSN, szUID, szPWD);
				return Open();
			}

			bool COdbc::Open()
			{
				SQLINTEGER retcode;

				// Allocate the ODBC Environment and save handle.
				retcode = SQLAllocHandle (SQL_HANDLE_ENV, NULL, &m_henv);
				if(!SQLOK(retcode))
				{
					m_henv = SQL_NULL_HANDLE;
					return false;
				}

				// Notify ODBC that this is an ODBC 3.0 application.
				retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
				retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_HENV, 0);
				if(!SQLOK(retcode))
				{
					SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
					m_henv = SQL_NULL_HANDLE;
					return false;
				}

				// Allocate an ODBC connection handle and connect.
				retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
				if(!SQLOK(retcode))
				{
					SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
					m_hdbc = SQL_NULL_HANDLE;
					m_henv = SQL_NULL_HANDLE;
					return false;
				}

				retcode = SQLSetConnectAttr(m_hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, 0);
				if(!SQLOK(retcode))
				{
					SQLErrorMsg(SQL_HANDLE_DBC, m_hdbc);

					SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
					SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
					m_hdbc = SQL_NULL_HANDLE;
					m_henv = SQL_NULL_HANDLE;
					return false;
				}
				retcode = SQLSetConnectAttr(m_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)2000, 0);
				if(!SQLOK(retcode))
				{
					SQLErrorMsg(SQL_HANDLE_DBC, m_hdbc);

					SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
					SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
					m_hdbc = SQL_NULL_HANDLE;
					m_henv = SQL_NULL_HANDLE;
					return false;
				}

				// Call SQLDriverConnect to make a connection request. Provide SQL_DRIVER_COMPLETE_REQUIRED
				// flag sothat driver manager and driver can ask for connection information
				// If failed to connect, free the allocated hdbc in previous step.
				SQLTCHAR szConnOut[1024];
				SQLSMALLINT nNumOut;
				retcode = SQLDriverConnect (m_hdbc, NULL, m_szConnect, SQL_NTS, szConnOut, 1024, &nNumOut, SQL_DRIVER_NOPROMPT);

				if(!SQLOK(retcode))
				{
					SQLErrorMsg(SQL_HANDLE_DBC, m_hdbc);

					SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
					SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
					m_hdbc = SQL_NULL_HANDLE;
					m_henv = SQL_NULL_HANDLE;

					return false;
				}
				return true;
			}


			// Allocate statement handles and do ODBC processing.
			void COdbc::Close()
			{
				SQLDisconnect(m_hdbc);
				SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
				SQLFreeHandle(SQL_HANDLE_ENV, m_henv);

				m_hdbc = SQL_NULL_HANDLE;
				m_henv = SQL_NULL_HANDLE;
			}

			bool COdbc::ReConnect()
			{
				if(IsOpen())
					Close();
				return Open();
			}

			bool COdbc::SQLErrorMsg(SQLHSTMT hstmt, LPCSTR errfunction)
			{
				SQLTCHAR      SqlState[6], Msg[1024];
				SQLINTEGER    NativeError=0;
				SQLSMALLINT   MsgLen=0;
				SQLRETURN     rc2;

				bool bConnect = false;
				int i=1;
				memset(Msg, 0, sizeof(Msg));
				while ((rc2 = SQLGetDiagRec(SQL_HANDLE_STMT, hstmt, i, SqlState, &NativeError, Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA)
				{
					GetjILog()->Warning(_T("%s\n"), errfunction);
					GetjILog()->Warning( _T("*** %s, %d, %s, %d ***\n"), SqlState, NativeError, Msg, MsgLen);
					if(!strcmp((char *)SqlState, "08S01")) bConnect = true;
					i++;
				}

				return bConnect;
			}

			bool COdbc::SQLErrorMsg(SQLSMALLINT HandleType, SQLHANDLE Handle)
			{
				SQLTCHAR       SqlState[6], Msg[1024];
				SQLINTEGER    NativeError=0;
				SQLSMALLINT   MsgLen=0;
				SQLRETURN     rc2;

				bool bConnect = false;
				int i=1;
				memset(Msg, 0, sizeof(Msg));
				while ((rc2 = SQLGetDiagRec(HandleType, Handle, i, SqlState, &NativeError, Msg, sizeof(Msg), &MsgLen)) != SQL_NO_DATA)
				{
					jt_printf( _T("*** %s, %d, %s, %d ***\n"), SqlState, NativeError, Msg, MsgLen);
					if(!strcmp((char *)SqlState, "08S01") && HandleType == SQL_HANDLE_STMT) 
						bConnect = true;
					i++;
				}

				return bConnect;
			}

			bool COdbc::Open2(LPCTSTR odbcName, LPCTSTR loginName, LPCTSTR loginPwd)
			{
				//Test whether the input value is valid or not
				if (0 >= lstrlen(odbcName) || 0 >= lstrlen(loginName)) return false;

				//Whether the test data library have already open or not
				if (IsOpen()) return true;

				SQLRETURN nReturn = SQL_ERROR;

				__try
				{
					//Initialization DEV hand1e
					nReturn = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);

					if (!SQL_SUCCEEDED(nReturn)) __leave;

					//Set DEV ODBC 3.0
					nReturn = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3,  0);

					if (!SQL_SUCCEEDED(nReturn)) __leave;

					//Establish the pool of DEV connectivity
					nReturn = SQLSetEnvAttr(m_henv, SQL_ATTR_CONNECTION_POOLING, (SQLPOINTER)SQL_CP_ONE_PER_HENV, 0);

					if (!SQL_SUCCEEDED(nReturn)) __leave;

					//Initialization ODBC hand1e
					nReturn = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);

					if (!SQL_SUCCEEDED(nReturn)) __leave;

					//Establish the DBC is an automatic business
					nReturn = SQLSetConnectAttr(m_hdbc, SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)SQL_AUTOCOMMIT_ON, 0);

					if (!SQL_SUCCEEDED(nReturn)) __leave;

					//Establish the DBC connectivity time-out time
					nReturn = SQLSetConnectAttr(m_hdbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)2000, 0);

					if (!SQL_SUCCEEDED(nReturn)) __leave;

					//Database of connectivity
					nReturn = SQLConnect(m_hdbc, 
						(SQLTCHAR*)odbcName, SQL_NTS,
						(SQLTCHAR*)loginName, SQL_NTS, 
						(SQLTCHAR*)loginPwd, SQL_NTS); 

					if (!SQL_SUCCEEDED(nReturn)) __leave;
				}
				__finally
				{
					//       m_OpenState = nReturn;

					if (!SQL_SUCCEEDED(nReturn))
					{
						if (SQL_NULL_HDBC != m_hdbc)
						{
							SQLDisconnect(m_hdbc);
							SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
						}

						if (SQL_NULL_HENV != m_henv)	SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
					}
				}

				return SQL_SUCCEEDED(nReturn) ? true : false;
			}
		}// nDB
	}// nUTIL
}// nMech
