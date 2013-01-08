/* file : jMSSql_Connection.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-24 19:32:34
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jMSSql_Connection_header__
#define __jMSSql_Connection_header__
#pragma once


#include <windows.h>
#include <sqlext.h>



// string lengths
#define MAX_FIELD_NAME_LEN			40
#define MAX_ERROR_MSG_LEN			1024
#define MAX_SQL_STATE_LEN			6
#define MAX_SQL_STATEMENT_LEN		4096



class ODBC_CONNECTION
{
private:
	HENV            m_hEnv; 
	HDBC			m_hDBC;

public:
	HDBC GetHDBC(void) { return m_hDBC; }

	bool Connect(LPCTSTR source);
	bool IsConnected(void);
	void Disconnect(void) { if (m_hDBC) SQLDisconnect(m_hDBC); }

	bool Init(void) { m_hDBC = NULL; m_hEnv = NULL; return TRUE; }
	void Free(void);

	void PrintError(SQLSMALLINT handletype, SQLHANDLE handle);
};


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class MSSQL_CONNECTION : public ODBC_CONNECTION
{
public:
	enum enumProtocols
	{
		protoNamedPipes,
		protoWinSock,
		protoIPX,
		protoBanyan,
		protoRPC
	};

public:
	bool Connect(
		LPCTSTR Address = _T(""),
		LPCTSTR Server = _T("(local)"),
		LPCTSTR User = _T(""),
		LPCTSTR Pass = _T(""),
		LPCTSTR Database = _T(""),
		bool Trusted = 1, 
		enumProtocols Proto = protoNamedPipes);
};




// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class ODBC_STATEMENT
{
private:
	HSTMT m_hStmt;

public:
	operator HSTMT(void) { return m_hStmt; }

	ODBC_STATEMENT(HDBC hDBC);
	virtual ~ODBC_STATEMENT(void);

	bool IsValid(void) { return m_hStmt != INVALID_HANDLE_VALUE; }
	void PrintError(void);

	bool BindInputParameter(
		SQLUSMALLINT parameter,
		SQLSMALLINT value_type,
		SQLSMALLINT param_type,
		SQLPOINTER ptr,
		SQLINTEGER buflen,
		SQLLEN * strlen_ptr,
		SQLUINTEGER column_size,
		SQLSMALLINT decimal_digits);

	USHORT GetColumnCount(void);
	SQLLEN GetChangedRowCount(void);

	bool Query(LPCTSTR strSQL)
	{ return SQL_OK(SQLExecDirect(m_hStmt, (SQLTCHAR *)strSQL, SQL_NTS)); }

	bool Fetch(void)
	{ return SQL_OK(SQLFetch(m_hStmt)); }
	bool FecthRow(USHORT row)
	{ return SQL_OK(SQLSetPos(m_hStmt, row, SQL_POSITION, SQL_LOCK_NO_CHANGE)); }
	bool FetchRow(ULONG row, bool absolute = TRUE)
	{ return SQL_OK(SQLFetchScroll(m_hStmt, (absolute ? SQL_FETCH_ABSOLUTE : SQL_FETCH_RELATIVE), row)); }
	bool FetchPrevious(void)
	{ return SQL_OK(SQLFetchScroll(m_hStmt, SQL_FETCH_PRIOR, 0)); }
	bool FetchNext(void)
	{ return SQL_OK(SQLFetchScroll(m_hStmt, SQL_FETCH_NEXT, 0)); }
	bool FetchFirst(void)
	{ return SQL_OK(SQLFetchScroll(m_hStmt, SQL_FETCH_FIRST, 0)); }
	bool FetchLast(void)
	{ return SQL_OK(SQLFetchScroll(m_hStmt, SQL_FETCH_LAST, 0)); }

	bool Cancel(void)
	{ return SQL_OK(SQLCancel(m_hStmt)); }
};


// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
class ODBC_RECORD
{
private:
	HSTMT m_hStmt;

public:
	ODBC_RECORD(HSTMT hStmt) { m_hStmt = hStmt; };
	~ODBC_RECORD(void) { }

	USHORT GetColumnCount(void);
	bool BindColumn(
		USHORT column,
		LPVOID buffer,
		ULONG buflen,
		SQLLEN * ret_buflen = NULL,
		USHORT type = SQL_C_TCHAR);

	USHORT GetColumnByName(LPCTSTR column);
	bool GetData(
		USHORT column, 
		LPVOID buffer, 
		ULONG buflen, 
		SQLLEN * datalen = NULL, 
		SQLSMALLINT type = SQL_C_DEFAULT);

	int GetColumnType(USHORT column);
	UINT GetColumnSize(USHORT column);
	USHORT GetColumnScale(USHORT column);
	bool GetColumnName(
		USHORT column,
		LPTSTR name,
		SHORT bufsize);
	bool IsColumnNullable(USHORT column);
};




#endif // __jMSSql_Connection_header__
