/* file : jMSSql_Connection.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-24 19:32:37
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jMSSql_Connection.h"
#include <sstream>

bool ODBC_CONNECTION::Connect(LPCTSTR source)
{
	int result;

	jONCE
	{
		result = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
		if (SQL_ERR(result))
		{
			break;
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
		result = SQLDriverConnect(m_hDBC, NULL, (SQLTCHAR *)source, (SQLSMALLINT)_tcslen(source), szOutConnectString, (SQLSMALLINT)sizeof(szOutConnectString), &shortResult, SQL_DRIVER_NOPROMPT);
		if (SQL_ERR(result))
		{
			PrintError(SQL_HANDLE_DBC, m_hDBC);
			break;
		}
		return TRUE;
	}

	Free();
	return FALSE;
}


bool ODBC_CONNECTION::IsConnected(void)
{
	if(m_hDBC)
	{
		SQLINTEGER connectionDead = SQL_CD_TRUE;
		SQLINTEGER nLen = 0;
		SQLRETURN hret = SQLGetConnectAttr(
			m_hDBC,
			SQL_ATTR_CONNECTION_DEAD,
			&connectionDead,
			0,
			&nLen);
		return SQL_OK(hret) && (connectionDead == SQL_CD_FALSE);
	}
	return FALSE;
}


void ODBC_CONNECTION::Free(void)
{
	Disconnect();
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
}


void ODBC_CONNECTION::PrintError(
								 SQLSMALLINT handletype, 
								 SQLHANDLE handle)
{
	SQLCHAR state[MAX_SQL_STATE_LEN];
	SQLINTEGER errorcode;
	SQLCHAR msg[MAX_ERROR_MSG_LEN];
	SQLSMALLINT msglen;

	SQLRETURN result;
	unsigned short ii = 1;
	while ((result = SQLGetDiagRecA(handletype, handle, ii, state, &errorcode, msg, sizeof(msg), &msglen)) != SQL_NO_DATA)
	{
		printf("SQL ERROR: state(%s)  error(%d)  %s", (char*)state, errorcode, (char*)msg);
		ii++;
	}
}


// ---------------------------------------------------------------------------
// class MSSQL_CONNECTION
// ---------------------------------------------------------------------------

bool MSSQL_CONNECTION::Connect(
							   LPCTSTR Address, 
							   LPCTSTR Server, 
							   LPCTSTR User, LPCTSTR Pass, 
							   LPCTSTR Database, 
							   bool Trusted, 
							   enumProtocols Proto)
{
	TCHAR str[1024]=_T("");

	UNREFERENCED_PARAMETER(Address);
	UNREFERENCED_PARAMETER(Server);
	UNREFERENCED_PARAMETER(Address);
	UNREFERENCED_PARAMETER(Proto);
	UNREFERENCED_PARAMETER(Trusted);


	// SQL Server가 아닌 SQL Native Client 사용으로 변경 하였습니다.
	_stprintf_s(str, _T("Driver={SQL Server};Address=%s;Server=%s;Uid=%s;Pwd=%s;Trusted_Connection=%s;Database=%s;Network="),
		SAFE_STR(Address), SAFE_STR(Server), SAFE_STR(User), SAFE_STR(Pass), (Trusted ? _T("Yes") : _T("No")), SAFE_STR(Database));
	//_stprintf_s(str, sizeof(str), _T("Driver={SQL Native Client};Address=%s;Server=%s;Uid=%s;Pwd=%s;Database=%s;Trusted_Connection=%s;"),
	//	SAFE_STR(Address), SAFE_STR(Server), SAFE_STR(User), SAFE_STR(Pass), SAFE_STR(Database), (Trusted ? _T("Yes") : _T("No")));

	// SQL Native Client에서는 Network 설정을 지원하지 않는다.
	switch(Proto)
	{
	case protoNamedPipes:
		_tcscat_s(str, _T("dbnmpntw"));
		break;
	case protoWinSock:
		_tcscat_s(str, _T("dbmssocn"));
		break;
	case protoIPX:
		_tcscat_s(str, _T("dbmsspxn"));
		break;
	case protoBanyan:
		_tcscat_s(str, _T("dbmsvinn"));
		break;
	case protoRPC:
		_tcscat_s(str, _T("dbmsrpcn"));
		break;
	default:
		_tcscat_s(str, _T("dbmssocn"));
		break;
	}
	_tcscat_s(str,_T(";"));

	return ODBC_CONNECTION::Connect(str);
}





// ---------------------------------------------------------------------------
// class ODBC_STATEMENT
// ---------------------------------------------------------------------------

ODBC_STATEMENT::ODBC_STATEMENT(HDBC hDBC)
{
	assert(hDBC);
	if (hDBC == NULL)
	{
		m_hStmt = INVALID_HANDLE_VALUE;
		return;
	}

	SQLRETURN result;
	result = SQLAllocHandle(SQL_HANDLE_STMT, hDBC, &m_hStmt);
	if (SQL_ERR(result))
	{
		m_hStmt = INVALID_HANDLE_VALUE;
		return;
	}
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_CONCURRENCY, (SQLPOINTER)SQL_CONCUR_ROWVER, 0);
	SQLSetStmtAttr(m_hStmt, SQL_ATTR_CURSOR_TYPE, (SQLPOINTER)SQL_CURSOR_KEYSET_DRIVEN, 0);
}


/*virtual*/ ODBC_STATEMENT::~ODBC_STATEMENT(void)
{
	if	(m_hStmt != INVALID_HANDLE_VALUE)
	{
		SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
	}
}


void ODBC_STATEMENT::PrintError(void)
{
	SQLCHAR state[MAX_SQL_STATE_LEN];
	SQLINTEGER errorcode;
	SQLCHAR msg[MAX_ERROR_MSG_LEN];
	SQLSMALLINT msglen;

	SQLRETURN result;
	unsigned short ii = 1;
	while ((result = SQLGetDiagRecA(SQL_HANDLE_STMT, m_hStmt, ii, state, &errorcode, msg, sizeof(msg), &msglen)) != SQL_NO_DATA)
	{
		printf("SQL ERROR: state(%s)  error(%d)  %s", (char*)state, errorcode, (char*)msg);
		ii++;
	}
}


bool ODBC_STATEMENT::BindInputParameter(
										SQLUSMALLINT parameter,
										SQLSMALLINT value_type,
										SQLSMALLINT param_type,
										SQLPOINTER ptr,
										SQLINTEGER buflen,
										SQLLEN * strlen_ptr,
										SQLUINTEGER column_size,
										SQLSMALLINT decimal_digits)
{
	SQLRETURN result = SQLBindParameter(m_hStmt, parameter, SQL_PARAM_INPUT, value_type, param_type, column_size, 
		decimal_digits, ptr, buflen, strlen_ptr);
	if (SQL_ERR(result))
	{
		PrintError();
		return FALSE;
	}
	return TRUE;
}


USHORT ODBC_STATEMENT::GetColumnCount(void)
{
	short columns = 0;
	if (SQL_ERR(SQLNumResultCols(m_hStmt, &columns)))
	{
		return 0;
	}
	return columns;
}


SQLLEN ODBC_STATEMENT::GetChangedRowCount(void)
{
	SQLLEN rows = 0;
	if (SQL_ERR(SQLRowCount(m_hStmt, &rows)))
	{
		return 0;
	}
	return rows;
}


// ---------------------------------------------------------------------------
// class ODBC_RECORD
// ---------------------------------------------------------------------------

USHORT ODBC_RECORD::GetColumnCount(void)
{
	short columns = 0;
	SQLRETURN result = SQLNumResultCols(m_hStmt , &columns);
	if (SQL_ERR(result))
	{
		return 0;
	}
	return columns;	
}


bool ODBC_RECORD::BindColumn(
							 USHORT column,
							 LPVOID buffer,
							 ULONG buflen,
							 SQLLEN * ret_buflen,
							 USHORT type)
{
	SQLLEN ret_len = 0;
	SQLRETURN result = SQLBindCol(m_hStmt, column, type, buffer, buflen, &ret_len);
	if (ret_buflen)
	{
		*ret_buflen = ret_len;
	}
	return SQL_OK(result);
}


USHORT ODBC_RECORD::GetColumnByName(LPCTSTR column)
{
	USHORT columns = GetColumnCount();
	if (columns == 0)
	{
		return 0;
	}
	for (USHORT ii = 0; ii < columns; ++ii)
	{
		TCHAR name[MAX_FIELD_NAME_LEN] = _T("");
		GetColumnName(ii + 1, name, sizeof(name));
		if (_tcsicmp(name, column) == 0)
		{
			return ii + 1;
		}
	}
	return 0;
}


bool ODBC_RECORD::GetData(
						  USHORT column, 
						  LPVOID buffer, 
						  ULONG buflen, 
						  SQLLEN * datalen, 
						  SQLSMALLINT type)
{
	SQLLEN temp = 0;
	SQLRETURN result = SQLGetData(m_hStmt, column, type, buffer, buflen, &temp);
	if	(datalen)
	{
		*datalen = temp;
	}
	return SQL_OK(result);
}


int ODBC_RECORD::GetColumnType(USHORT column)
{
	SQLTCHAR colname[256]=_T("");
	SQLSMALLINT retNameLen = 0, retDataType = 0, retScale = 0, retNull = 0;
	SQLULEN retColSize;
	SQLDescribeCol(m_hStmt, column, colname, sizeof(colname), &retNameLen, &retDataType, &retColSize, &retScale, &retNull);
	return (int)retDataType;
}


UINT ODBC_RECORD::GetColumnSize(USHORT column)
{
	SQLTCHAR colname[256]=_T("");
	SQLSMALLINT retNameLen = 0, retDataType = 0, retScale = 0, retNull = 0;
	SQLULEN retColSize;
	SQLDescribeCol(m_hStmt, column, colname, sizeof(colname), &retNameLen, &retDataType, &retColSize, &retScale, &retNull);
	return (UINT)retColSize;
}


USHORT ODBC_RECORD::GetColumnScale(USHORT column)
{
	SQLTCHAR colname[256]=_T("");
	SQLSMALLINT retNameLen = 0, retDataType = 0, retScale = 0, retNull = 0;
	SQLULEN retColSize;
	SQLDescribeCol(m_hStmt, column, colname, (SQLSMALLINT)sizeof(colname), &retNameLen, &retDataType, &retColSize, &retScale, &retNull);
	return retScale;
}


bool ODBC_RECORD::GetColumnName(
								USHORT column,
								LPTSTR name,
								SHORT bufsize)
{
	SQLSMALLINT retNameLen = 0, retDataType = 0, retScale = 0, retNull = 0;
	SQLULEN retColSize;
	SQLRETURN result = SQLDescribeCol(m_hStmt, column, (SQLTCHAR *)name, bufsize, &retNameLen, &retDataType, &retColSize, &retScale, &retNull);
	return SQL_OK(result);
}


bool ODBC_RECORD::IsColumnNullable(USHORT column)
{
	SQLTCHAR colname[256]=_T("");
	SQLSMALLINT retNameLen = 0, retDataType = 0, retScale = 0, retNull = 0;
	SQLULEN retColSize;
	SQLDescribeCol(m_hStmt, column, colname, sizeof(colname), &retNameLen, &retDataType, &retColSize, &retScale, &retNull);
	return (retNull == SQL_NULLABLE);
}



// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
void DatabasePrintResult(
						 ODBC_STATEMENT & statement)
{
	while (statement.Fetch())
	{
		ODBC_RECORD record(statement);
		USHORT colCount = statement.GetColumnCount();
		assert(colCount < USHRT_MAX - 1);
		for (USHORT ii = 0; ii < colCount; ++ii)
		{
			TCHAR data[512] = _T("");
			SQLLEN datalen = 0;
			record.GetData(ii + 1, data, sizeof(data), &datalen);
			TCHAR name[MAX_FIELD_NAME_LEN]=_T("");
			record.GetColumnName(ii + 1, name, sizeof(name));
			printf("%15s>  %25s\n", name, data);
		}
	}
}

SQLHSTMT DatabaseManagerGetStatement(
									 SQLHDBC dbHandle,
									 const char * statementText )
{
	jRETURN_ret(0,dbHandle);
	jRETURN_ret(0,statementText && statementText[0]);

	SQLHSTMT toRet = NULL;
	SQLRETURN res = SQL_ERROR;

	res = SQLAllocHandle(SQL_HANDLE_STMT, dbHandle, &toRet);
	jRETURN_ret(0, res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO);

	res = SQLPrepareA(toRet, (SQLCHAR*)statementText, SQL_NTS);
	jIF_NOT(res == SQL_SUCCESS || res == SQL_SUCCESS_WITH_INFO)
	{
		SQLFreeHandle(SQL_HANDLE_STMT,toRet);
		return NULL;
	}

	return toRet;
}
void DatabaseManagerReleaseStatement(
									 SQLHSTMT & stmtHdl )
{
	if(!stmtHdl)
		return;

	SQLCloseCursor(stmtHdl);
	SQLFreeHandle(SQL_HANDLE_STMT,stmtHdl);
	stmtHdl = NULL;
}


class CScopedSQLStmt
{
public:
	CScopedSQLStmt(SQLHDBC hDBC, const char* szStatement) : hStmt(DatabaseManagerGetStatement(hDBC, szStatement)) { }
	~CScopedSQLStmt(void) { DatabaseManagerReleaseStatement(hStmt); }
	operator SQLHSTMT(void) { return hStmt; }

protected:
	SQLHSTMT hStmt;
};

string GetSQLErrorStr(SQLHANDLE Handle, SQLSMALLINT iHandleType=SQL_HANDLE_STMT)
{
	std::ostringstream ss;
	SQLCHAR szState[7], szMessage[1024];
	SQLINTEGER NativeError;
	SQLSMALLINT Length;
	SQLRETURN Return = SQL_SUCCESS;
	for (SQLSMALLINT iRecNumber = 1; Return == SQL_SUCCESS; ++iRecNumber) {
		Return = SQLGetDiagRecA
			(iHandleType, Handle, iRecNumber, szState, &NativeError, szMessage, sizeof(szMessage), &Length);
		if (SQL_SUCCEEDED(Return)) 
			ss << "State: " << szState << ", NativeError: " << NativeError << ", Message: " << szMessage << "\n";
	}
	return ss.str();
}
	using namespace nMech;
struct asdf
{
	int i;
	float f;
	aname32_t ip;
	char c;
};
void test1234()
{

	MSSQL_CONNECTION con;
	con.Init();

	char szIP[] = "50.10.250.36";
	int iRet = 0;
	SQLINTEGER cbVal=0,ilen=(int)strlen(szIP);



	try
	{
		jASSERT0(con.Connect(_T("50.10.250.113,1433\\test_db"), _T(""), _T("sa"),_T("qwer"),_T("test_db2"),0,MSSQL_CONNECTION::protoWinSock) );
		asdf a={111,222.f,"asdf",33};
		asdf b;
		BYTE buf[1024];
		BYTE buf2[1024];
		memset(buf,99,sizeof(buf));
		memset(buf2,96,sizeof(buf2));
		
		//memcpy(buf,&a,sizeof(a));
		//memset(&b,0, sizeof(b));
		aname32_t temp;
		CScopedSQLStmt hStmt(con.GetHDBC(), "{ call sp_bin_insert(?,?)}");

		assert(hStmt!=0);
		SQLLEN c1=0,c2=0;
		SQLINTEGER param=0;
		SQLINTEGER len2= sizeof(b);

		try
		{
			jTHROW(SQL_SUCCEEDED(SQLBindParameter(hStmt, ++param, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, ilen, 0, szIP, ilen, 0)));
			jTHROW(SQL_SUCCEEDED(SQLBindParameter(hStmt, ++param, SQL_PARAM_INPUT, SQL_C_BINARY, SQL_LONGVARBINARY, sizeof(buf), 0, buf, sizeof(buf), &c2)));

			param=0;
			jTHROW(SQL_SUCCEEDED(SQLBindCol(hStmt, ++param, SQL_C_BINARY, buf2, 1024, &c1)));
			jTHROW(SQL_SUCCEEDED(SQLExecute(hStmt)));
			jTHROW(SQL_SUCCEEDED(SQLFetch(hStmt)));
		}
		catch (...)
		{
			jERROR_T("error : %s",jT(GetSQLErrorStr(hStmt).c_str()) );
		}
	}
	catch (...)
	{
		jERROR_T("asdf");
	}

	con.Disconnect();
	con.Free();

}