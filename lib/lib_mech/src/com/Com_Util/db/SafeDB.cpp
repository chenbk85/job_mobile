//////////////////////////////////////////////////////////////////////////
// Safe DB/ODBC class
// Author: Chunmin Ahn (emocreator@gmail.com)
// Version: 1.06
// History: 
//  2007-03: Initial work
//  2007-10: Make abstract class, int type Data()/Bind()
//  2008-07: Support wide char type
//  2008-08: Fixed handle leak
//  2008-11: Support binary data type
//	2009-12: Add server name parameter on _OnError(), Add query dump features
//	2010-04: Execute/Prepare() with wide char type
//

#include "stdafx.h"
#include "SafeDB.h"
#include "interface/xml/jIVar.h"
#pragma comment(lib, "odbc32.lib")


// string lengths
#define MAX_FIELD_NAME_LEN			40
#define MAX_ERROR_MSG_LEN			1024
#define MAX_SQL_STATE_LEN			6
#define MAX_SQL_STATEMENT_LEN		4096

namespace nMech
{

	namespace nDB
	{
		jIVar* pv_LogSqlQuery = jCV(jIDB,LogSqlQuery,false,0,"Saving jIDB sql query log");
		static tstring errorStr;

		//////////////////////////////////////////////////////////////////////////

		jCTOR_INTERFACE(nMech::nDB::jIDB,OdbcDB)
		{
			return new OdbcDB;
		}
		jDTOR_INTERFACE(nMech::nDB::jIDB,OdbcDB)
		{
			delete this;
		}


		OdbcDB::OdbcDB() : m_hEnv(SQL_NULL_HENV), m_hDBC(SQL_NULL_HANDLE)
		{
			static IOdbcErrorHandler	_pErrHandler;
			_err= &_pErrHandler;
			_lastPingTime = 0;
		}

		OdbcDB::~OdbcDB()
		{
			Close();
		}

		tcstr OdbcDB::GetSvrName() { return _svrName; }
		void OdbcDB::SetInfo(tcstr svrName, tcstr usrName, tcstr pwd)
		{
			jt_strcpy(_svrName ,svrName);
			jt_strcpy(_usrName , usrName);
			jt_strcpy(_pwd , pwd);
		}

		OdbcDB* OdbcDB::BaseI() { return this;}

		void OdbcDB::SetError(IOdbcErrorHandler* err)
		{
			_err = err;
		}

		void PrintError(SQLSMALLINT handletype, SQLHANDLE handle)
		{
			SQLCHAR state[MAX_SQL_STATE_LEN];
			SQLINTEGER errorcode;
			SQLCHAR msg[MAX_ERROR_MSG_LEN];
			SQLSMALLINT msglen;

			SQLRETURN result;
			unsigned short ii = 1;
			while ((result = SQLGetDiagRecA(handletype, handle, ii, state, &errorcode, msg, sizeof(msg), &msglen)) != SQL_NO_DATA)
			{
				jERROR(_T("SQL ERROR: state(%s)  error(%d)  %s"), jT((char*)state), errorcode, jT((char*)msg) );
				ii++;
			}
		}

		bool OdbcDB::OpenDirect(cstr szConnectionString)
		{
			int result;
// 			SetInfo(szIP,szID,szPWD);
// 			TCHAR szDriverString[1024]=_T("");
// 			// SQL szServer가 아닌 SQL Native Client 사용으로 변경 하였습니다.
// 			if(!szIP || tstring(szIP)==jS(NULL)) szIP=_T("");
// 			if(!szServer || tstring(szServer)==jS(NULL)) szServer=_T("");

// 			_stprintf_s(szDriverString
// 				, _T("Driver={SQL Server};Address=%s;Server=%s;Uid=%s;Pwd=%s;Trusted_Connection=%s;Database=%s;Network="),
// 				SAFE_STR(szIP), SAFE_STR(szServer), SAFE_STR(szID)
// 				, SAFE_STR(szPWD), (isTrust ? _T("Yes") : _T("No"))
// 				, SAFE_STR(Database));
				//_stprintf_s(szDriverString, sizeof(szDriverString), _T("Driver={SQL Native Client};szIP=%s;szServer=%s;Uid=%s;Pwd=%s;Database=%s;Trusted_Connection=%s;"),
				//	SAFE_STR(szIP), SAFE_STR(szServer), SAFE_STR(szID), SAFE_STR(szPWD), SAFE_STR(Database), (isTrust ? _T("Yes") : _T("No")));

			// SQL Native Client에서는 Network 설정을 지원하지 않는다.
// 			switch(eProtocal)
// 						{
// 						case protoNamedPipes:_tcscat_s(szDriverString, _T("dbnmpntw"));break;
// 						case protoWinSock:_tcscat_s(szDriverString, _T("dbmssocn"));break;
// 						case protoIPX:_tcscat_s(szDriverString, _T("dbmsspxn"));break;
// 						case protoBanyan:_tcscat_s(szDriverString, _T("dbmsvinn"));break;
// 						case protoRPC:_tcscat_s(szDriverString, _T("dbmsrpcn"));break;
// 						default:_tcscat_s(szDriverString, _T("dbmssocn"));break;
// 						}
// 			
// 						_tcscat_s(szDriverString,_T(";"));

			jONCE
			{
				result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
				if (SQL_ERR(result))
				{
					jERROR(_T("result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);"));
					return false;
				}
				result = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (void *)SQL_OV_ODBC3, 0);
				if (SQL_ERR(result))
				{
					PrintError(SQL_HANDLE_ENV, m_hEnv);
					break;
				}
				result = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDBC);
				if (SQL_ERR(result))
				{
					PrintError(SQL_HANDLE_ENV, m_hEnv);
					break;
				}
				SQLSetConnectOption(m_hDBC,	SQL_LOGIN_TIMEOUT, 5);
				short shortResult = 0;
				SQLTCHAR szOutConnectString[1024];
				result = SQLDriverConnect(m_hDBC, NULL, (SQLTCHAR *)szConnectionString, (SQLSMALLINT)_tcslen(szConnectionString)
					, szOutConnectString, (SQLSMALLINT)sizeof(szOutConnectString), &shortResult, SQL_DRIVER_NOPROMPT);
				if (SQL_ERR(result))
				{
					PrintError(SQL_HANDLE_DBC, m_hDBC);
					break;
				}
				_lastPingTime = GetTickCount();
				return true;
			}

			if (m_hDBC) SQLDisconnect(m_hDBC);
			if (m_hDBC)
			{
				SQLFreeHandle(SQL_HANDLE_DBC, m_hDBC);
				m_hDBC = NULL;
			}
			if	(m_hEnv)
			{
				SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
				m_hEnv = NULL;
			}
			return false;
		}

		void OdbcDB::Open()
		{
			SQLRETURN  rc;

			jAUTO_LOCK_CS1(_door);

			rc = ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
			if (SQL_ERR(rc))
			{
				throw tstring(jFUNC1  jS(SQLAllocHandle(SQL_HANDLE_ENV) _T(" : ") ) ) + _svrName ;
			}

			rc = ::SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (LPVOID)SQL_OV_ODBC3, 0);
			if (SQL_ERR(rc))
			{
				_ErrorEnv(_T("Open() SQLSetEnvAttr"));
				Close();
				errorStr = tstring(jFUNC1 jS(SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (LPVOID)SQL_OV_ODBC3, 0)) _T(" : ") ) + _svrName ;
				throw errorStr.c_str();
			}

			rc = ::SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDBC);
			if (SQL_ERR(rc))
			{
				_ErrorEnv(_T("Open() SQLAllocHandle"));
				Close();
				errorStr = tstring(jFUNC1 jS(SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDBC)) _T(" : ") ) + _svrName ;
				throw errorStr.c_str();
			}

			rc = ::SQLConnect(m_hDBC, (SQLTCHAR*)_svrName, SQL_NTS, (SQLTCHAR*)_usrName, SQL_NTS, (SQLTCHAR*)_pwd, SQL_NTS);
			if (SQL_ERR(rc))
			{
				_ErrorEnv(_T("Open() SQLConnect"));
				Close();
				errorStr =  tstring(jFUNC1 jS(SQLConnect(m_hDBC, (SQLTCHAR*)_svrName ) ) ) + _svrName ;
				throw errorStr.c_str();
			}

			_lastPingTime = GetTickCount();
		}

		void OdbcDB::Close()
		{
			if (m_hDBC != SQL_NULL_HANDLE)
			{
				::SQLDisconnect(m_hDBC);
				::SQLFreeHandle(SQL_NULL_HANDLE, m_hDBC);

				m_hDBC = SQL_NULL_HANDLE;
			}

			if (m_hEnv != SQL_NULL_HENV)
			{
				::SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
				m_hEnv = SQL_NULL_HENV;
			}
		}

		bool OdbcDB::_IsLive()
		{
			bool ret = m_hDBC != SQL_NULL_HANDLE;
			return ret;
		}

		//--------------------------------------------------------------------------
		bool OdbcDB::Execute(tcstr sql, OdbcRecord* record)
			//--------------------------------------------------------------------------
		{
			jAUTO_LOCK_CS1(_door);

			if (!_IsLive())
			{
				return false;
			}

			if (pv_LogSqlQuery->Get_bool())
			{
				_OnError(_svrName, 0, _T("__DUMP__"), sql);
			}

			SQLRETURN rc;
			SQLHANDLE stmt = SQL_NULL_HANDLE;
			bool ret = false;

			rc = ::SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &stmt);
			if (SQL_ERR(rc))
			{
				_ErrorOdbc(_T("Execute()"));
				return false;
			}

			rc = ::SQLExecDirect(stmt, (SQLTCHAR*)sql, SQL_NTS);
			if (SQL_OK(rc))
			{
				if(record)
				{
					ret = true;

					record->Free();
					record->_db = this;
					record->_rec = stmt;
					stmt = SQL_NULL_HANDLE;
				}
			}
			else
			{
				_ErrorStmt(stmt, sql);
			}

			if (stmt != SQL_NULL_HANDLE)
				::SQLFreeHandle(SQL_HANDLE_STMT, stmt);

			return ret;
		}

		//--------------------------------------------------------------------------
		bool OdbcDB::Prepare(tcstr storedProc, jOdbcParameter* sp)
			//--------------------------------------------------------------------------
		{
			jAUTO_LOCK_CS1(_door);

			if (!_IsLive())
			{
				return false;
			}

			SQLRETURN rc;
			SQLHANDLE stmt;
			bool ret = false;

			rc = ::SQLAllocHandle(SQL_HANDLE_STMT, m_hDBC, &stmt);
			if (SQL_ERR(rc))
			{
				_ErrorOdbc(_T("Prepare() SQLAllocHandle"));
				return false;
			}

			rc = ::SQLPrepare(stmt, (SQLTCHAR*)storedProc, SQL_NTS);
			if (SQL_OK(rc))
			{
				ret = true;

				sp->Free();
				sp->_db = this;
				sp->_sp = stmt;
				jt_strcpy(sp->_spName , storedProc);
				stmt = SQL_NULL_HANDLE;
			}
			else
			{
				_ErrorStmt(stmt, _T("Prepare() SQLPrepareA") );
			}

			if (stmt != SQL_NULL_HANDLE)
				::SQLFreeHandle(SQL_HANDLE_STMT, stmt);

			return ret;
		}


		bool OdbcDB::Transact()
		{
			return false;
		}

		bool OdbcDB::Rollback()
		{
			jAUTO_LOCK_CS1(_door);
			bool ret = SQL_SUCCESS == ::SQLEndTran(SQL_HANDLE_DBC, m_hDBC, SQL_ROLLBACK);

			if (ret == false)
				_ErrorOdbc(_T("Rollback() SQLEndTran"));

			return ret;
		}

		bool OdbcDB::Commit()
		{
			bool ret = SQL_SUCCESS == ::SQLEndTran(SQL_HANDLE_DBC, m_hDBC, SQL_COMMIT);
			if (ret == false)
				_ErrorOdbc(_T("Commit() SQLEndTran"));

			return ret;
		}

		void OdbcDB::_OnError(tcstr svrName, int code, tcstr from, tcstr msg)
		{
			if (_err)
			{
				_err->_OnError(svrName, code, from, msg);
			}
			else
			{
#ifdef _DEBUG
				tSafeMsg dmsg;
				dmsg.Format(_T("ODBC Error: Code(%d), From(%s), Msg(%s)\n"), code, from, msg);
				OutputDebugString(dmsg._s);
#endif
			}
		}

		bool OdbcDB::Ping()
		{
			if( _lastPingTime + 300000 < GetTickCount() )
			{
				_lastPingTime = GetTickCount();
				return Execute(_T("select 1"));
			}

			return true;
		}

		void OdbcDB::_Error(short handleType, void* handle, tcstr from)
		{
			SQLTCHAR     errMsg[MAX_ODBC_ERR][SQL_MAX_MESSAGE_LENGTH + 1] ;
			SQLTCHAR     state[MAX_ODBC_ERR][SQL_SQLSTATE_SIZE + 1] ;
			SQLINTEGER	errCode[MAX_ODBC_ERR];
			SQLSMALLINT errMsgLen, count = 0;

			while (SQL_SUCCESS == ::SQLGetDiagRec(handleType, handle,
				count+1,
				state[count], &errCode[count],
				errMsg[count], SQL_MAX_MESSAGE_LENGTH+1,
				&errMsgLen))
			{
				if (count >= (MAX_ODBC_ERR-1))
					break;
				count++;
			}

			tSafeMsg paramInfo(from);
			if (paramInfo.Find('?') >= 0)
				_GetParamInfo(handle, paramInfo);

			for (SQLSMALLINT i = 0; i < count; i++)
			{
				_OnError(_svrName, errCode[i], (paramInfo._s), (tcstr)errMsg[i]);
			}
		}

		void OdbcDB::_ErrorEnv(tcstr from)
		{
			_Error(SQL_HANDLE_ENV, m_hEnv, from);
		}

		void OdbcDB::_ErrorOdbc(tcstr from)
		{
			_Error(SQL_HANDLE_DBC, m_hDBC, from);
		}

		void OdbcDB::_ErrorStmt(void* handle, tcstr from)
		{
			_Error(SQL_HANDLE_STMT, handle, from);
		}

		void OdbcDB::_GetParamInfo(void* handle, tSafeMsg& msg)
		{
			// http://msdn.microsoft.com/en-us/library/ms712631(VS.85).aspx
			// http://msdn.microsoft.com/en-us/library/ms713560(VS.85).aspx
			SQLSMALLINT paramCount;
			SQLRETURN rc = ::SQLNumParams(handle, &paramCount);
			if (!SQL_OK(rc))
				return;

			SQLHDESC descAPD, descIPD;
			SQLINTEGER cbDesc;
			rc = ::SQLGetStmtAttr(handle, SQL_ATTR_APP_PARAM_DESC, (SQLPOINTER)&descAPD, SQL_IS_POINTER, &cbDesc);
			if (!SQL_OK(rc))
				return;

			rc = ::SQLGetStmtAttr(handle, SQL_ATTR_IMP_PARAM_DESC, (SQLPOINTER)&descIPD, SQL_IS_POINTER, &cbDesc);
			if (!SQL_OK(rc))
			{
				::SQLFreeHandle(SQL_HANDLE_DESC, descAPD);
				return;
			}

			for (SQLSMALLINT i=1; i <= paramCount; i++)
			{
				SQLSMALLINT dataType;
				SQLSMALLINT digit, nullable;
				SQLULEN paramSize;

				//rc = ::SQLGetDescField(descIPD, i, SQL_DESC_TYPE, &dataType, SQL_IS_SMALLINT, NULL);
				rc = ::SQLDescribeParam(handle, i, &dataType, &paramSize, &digit, &nullable);
				if (SQL_OK(rc))
				{
					SafeStr<8000> valStr;
					tSafeStr<8000> numStr;
					SQLPOINTER val = (SQLPOINTER)&valStr._s;

					if (paramSize > (SQLUINTEGER)valStr.MaxLen())
					{
						msg.ReplaceOnce(_T("?"), _T("[over]") );
						continue;
					}

					SQLSMALLINT dataUnsigned;
					rc = ::SQLGetDescField(descIPD, i, SQL_DESC_UNSIGNED, &dataUnsigned, SQL_IS_SMALLINT, NULL);
					if (!SQL_OK(rc))
					{
						msg.ReplaceOnce(_T("?"), _T("[err]") );
						continue;
					}

					SQLSMALLINT ptype;
					rc = ::SQLGetDescField(descIPD, i, SQL_DESC_PARAMETER_TYPE, &ptype, SQL_IS_SMALLINT, NULL);
					if (SQL_OK(rc))
					{
						switch (ptype)
						{
						case SQL_PARAM_INPUT:				break;
						case SQL_PARAM_OUTPUT:				msg.ReplaceOnce(_T("?"), _T("[out]") ); continue;
						case SQL_PARAM_INPUT_OUTPUT:		break;
						case SQL_RETURN_VALUE:				msg.ReplaceOnce(_T("?"), _T("[ret]") ); continue;
						}
					}

					DATE_STRUCT* date;
					TIME_STRUCT* time;
					TIMESTAMP_STRUCT* stamp;
					SQL_INTERVAL_STRUCT* inter;

					SQLINTEGER strLen;
					rc = ::SQLGetDescField(descAPD, i, SQL_DESC_DATA_PTR, &val, valStr.MaxLen(), &strLen);
					if (SQL_OK(rc))
					{
						switch (dataType)
						{
						case SQL_CHAR:
						case SQL_VARCHAR:
						case SQL_LONGVARCHAR:
							numStr.Format(_T("'%s'"), jT( (CHAR*)val ) );
							break;
						case SQL_WCHAR:
						case SQL_WVARCHAR:
						case SQL_WLONGVARCHAR:
							numStr.Format(_T("'%s'"), jT((WCHAR*)val) );
							break;
						case SQL_DECIMAL:
						case SQL_NUMERIC:
							break;
						case SQL_SMALLINT:
							numStr.Format(_T("%d"), (dataUnsigned == SQL_TRUE ? *((USHORT*)val): *((SHORT*)val)) );
							break;
						case SQL_INTEGER:
							if (dataUnsigned)
								numStr.Format(_T("%u"), *((ULONG*)val));
							else
								numStr.Format(_T("%d"), *((LONG*)val));
							break;
						case SQL_REAL:
							numStr.Format(_T("%g"), *((float*)val));
							break;
						case SQL_FLOAT:
						case SQL_DOUBLE:
							numStr.Format(_T("%g"), *((double*)val));
							break;
						case SQL_BIT:
						case SQL_TINYINT:
							numStr.Format(_T("%d"), (dataUnsigned == SQL_TRUE ? *((BYTE*)val): *((CHAR*)val)) );
							break;
						case SQL_BIGINT:
							if (dataUnsigned)
								numStr.Format(_T("%I64u"), *((UINT64*)val));
							else
								numStr.Format(_T("%I64d"), *((INT64*)val));
							break;
						case SQL_BINARY:
						case SQL_VARBINARY:
						case SQL_LONGVARBINARY:
							break;
						case SQL_TYPE_DATE:
							date = (DATE_STRUCT*)val;
							numStr.Format(_T("%04d-%02d-%02d"), date->year, date->month, date->day);
							break;
						case SQL_TYPE_TIME:
							time = (TIME_STRUCT*)val;
							numStr.Format(_T("%02d:%02d:%02d"), time->hour, time->minute, time->second);
							break;
						case SQL_TYPE_TIMESTAMP:
							stamp = (TIMESTAMP_STRUCT*)val;
							numStr.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%d"), stamp->year, stamp->month, stamp->day,
								stamp->hour, stamp->minute, stamp->second, (int)(stamp->fraction / 1000000));
							break;
							//case SQL_TYPE_UTCDATETIME:
							//case SQL_TYPE_UTCTIME:
						case SQL_INTERVAL_MONTH:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.year_month.month);
							break;
						case SQL_INTERVAL_YEAR:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.year_month.year);
							break;
						case SQL_INTERVAL_YEAR_TO_MONTH:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.year_month.month);
							break;
						case SQL_INTERVAL_DAY:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.day);
							break;
						case SQL_INTERVAL_HOUR:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.hour);
							break;
						case SQL_INTERVAL_MINUTE:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.minute);
							break;
						case SQL_INTERVAL_SECOND:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.second);
							break;
						case SQL_INTERVAL_DAY_TO_HOUR:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.hour);
							break;
						case SQL_INTERVAL_DAY_TO_MINUTE:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.minute);
							break;
						case SQL_INTERVAL_DAY_TO_SECOND:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.second);
							break;
						case SQL_INTERVAL_HOUR_TO_MINUTE:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.minute);
							break;
						case SQL_INTERVAL_HOUR_TO_SECOND:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.second);
							break;
						case SQL_INTERVAL_MINUTE_TO_SECOND:
							inter = (SQL_INTERVAL_STRUCT*)val;
							numStr.Format(_T("%d"), inter->intval.day_second.second);
							break;
							//case SQL_GUID: SQLGUID type
						}

						if (numStr.IsNull())
							numStr = _T("[unknown]");

						msg.ReplaceOnce(_T("?"), numStr._s);
					}
					else
					{
						msg.ReplaceOnce(_T("?"), _T("[err]"));
					}
				}
				else
				{
					msg.ReplaceOnce(_T("?"), _T("[err]"));
				}
			}
			msg.Replace(_T("?"), _T("[none]"));

			::SQLFreeHandle(SQL_HANDLE_DESC, descIPD);
			::SQLFreeHandle(SQL_HANDLE_DESC, descAPD);
		}

		void OdbcDB::RunSQL_Direct(tcstr szSQL,jISqlJob* pJob)
		{
#if 1
			void test1234();
			test1234();
#else
			this->Execute(szSQL);
			if(pJob)
			{
				// jTODO  fetch코드 
			}
#endif

		}
		void OdbcDB::RunSQL(tcstr szSQL,jISqlJob* pJob,bool runFetch)
		{
			if(!pJob)
			{
				this->Execute(szSQL);
				return;
			}
			jOdbcParameter sp;
			if (this->Prepare(szSQL, &sp))
			{
				sp.m_iCol=1;
				pJob->Bind(&sp);

				if(sp.m_isExcuted) return;
				if(runFetch)
				{
					OdbcRecord rec;
					if (sp.Execute(&rec))
					{
						rec.m_iCol=1;
						pJob->Fetch(&rec);
					}
				}
				else
				{
					sp.Execute();
				}
			}
		}

	}//namespace nDB


}//namespace nMech