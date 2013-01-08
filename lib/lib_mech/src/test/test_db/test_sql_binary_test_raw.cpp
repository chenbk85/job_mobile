#include "stdafx.h"
#include "Interface/db/jIDB.h"
#include <windows.h>
#include <sqlext.h>
#include <sstream>

using namespace nMech::nDB;



void test_sql_binary_test_raw()
{
	SQLRETURN  rc;
	jSQLHANDLE			_env;
	jSQLHANDLE			_odbc;

	int ret=111;

	SQLHANDLE stmt;
	try
	{
		/*

		USE [test_db2]
		GO
		SET ANSI_NULLS ON
		GO
		SET QUOTED_IDENTIFIER ON
		GO
		SET ANSI_PADDING ON
		GO
		CREATE TABLE [dbo].[test1](
		[val] [int] IDENTITY(1,1) NOT NULL,
		[txt] [varchar](1024) NULL,
		[data] [int] NULL,
		[bin] [varbinary](max) NULL
		) ON [PRIMARY]

		GO

		SET ANSI_PADDING ON
		USE [test_db2]
		GO
		SET ANSI_NULLS OFF
		GO
		SET QUOTED_IDENTIFIER ON
		GO
		ALTER PROCEDURE [dbo].[BIN_INSERT] 
		@txt varchar(1024) 
		,@data INT 
		,@bin varbinary(1024) 
		AS 
		BEGIN 
		SET NOCOUNT ON 
		set ANSI_PADDING on
		INSERT INTO [test1]( txt ,data, bin) 
		VALUES( @txt , @data, @bin) 
		select bin from test1 where @@identity =val
		END

		*/

		rc = ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &_env);
		if (SQL_ERR(rc))
		{
			throw jS(asdf1);
		}

		rc = ::SQLSetEnvAttr(_env, SQL_ATTR_ODBC_VERSION, (LPVOID)SQL_OV_ODBC3, 0);
		if (SQL_ERR(rc))
		{
			throw jS(asdf2);
		}

		rc = ::SQLAllocHandle(SQL_HANDLE_DBC, _env, &_odbc);
		if (SQL_ERR(rc))
		{
			throw jS(asdf3);
		}

		rc = ::SQLConnect(_odbc, (SQLTCHAR*)jS(test_db), SQL_NTS, (SQLTCHAR*)jS(sa), SQL_NTS, (SQLTCHAR*)jS(qwer), SQL_NTS);
		if (SQL_ERR(rc))
		{
			throw jS(asdf4);
		}

		rc = ::SQLAllocHandle(SQL_HANDLE_STMT, _odbc, &stmt);

		if (SQL_ERR(rc))
		{
			throw jS(asdf11);
		}
		//SQLSetStmtAttr(stmt,SQL_SOPT_SS_TEXTPTR_LOGGING,			SQL_TL_OFF);


		rc = ::SQLPrepareA(stmt, (SQLCHAR*)("{call bin_insert(?,?,?)}"), SQL_NTS);
		if (!SQL_OK(rc))
		{
			throw jS(asdf12);
		}
		INT col=0;
		test_struct t = { "1234567890\0\01234567890",222,333,99.9f ,"asdf"};
		memset(pd.all, 99,sizeof(pd.all));
		//pd = t;
		//memcpy(pd.buf,t.buf,sizeof(t.buf));
		pd.f = t.f;
		pd.i = t.i;
		pd.j = t.j;
		memcpy(pd.sz,t.sz, sizeof(t.sz));


		static SQLLEN cbVal;
		SQLULEN len = ja_strlen(pd.sz);
		assert(SQL_SUCCESS ==::SQLBindParameter(stmt, ++col, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR, len, 0, pd.sz , len, 0));
		assert(SQL_SUCCESS ==::SQLBindParameter(stmt, ++col, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &pd.i, 0, 0));
		assert(SQL_SUCCESS ==::SQLBindParameter(stmt, ++col,SQL_PARAM_INPUT, SQL_C_BINARY,SQL_LONGVARBINARY , sizeof(pd), 0, &pd, sizeof(pd), 0));


		rc = ::SQLExecute(stmt);

		ret = SQL_OK(rc);
		if (!ret) 
			throw jS(asdf13);


		rc = ::SQLFetch((SQLHANDLE)stmt);
		if(rc != SQL_SUCCESS)
			throw jS(asdf14);


		test_struct pd1;
		memset(&pd1,0,sizeof(test_struct));
		cbVal = 0;
		col=0;
		//assert(SQL_SUCCESS ==::SQLGetData((SQLHANDLE)stmt, ++col, SQL_C_SLONG, &id, 0, &cbVal) );
		//assert(SQL_SUCCESS ==::SQLGetData((SQLHANDLE)stmt, ++col, SQL_C_SLONG, &data, 0, &cbVal) );
		//assert(SQL_SUCCESS ==::SQLGetData((SQLHANDLE)stmt, ++col, SQL_C_CHAR, txt, sizeof(txt), &cbVal));
		cbVal = sizeof(pd1);
		assert(SQL_SUCCESS ==::SQLGetData((SQLHANDLE)stmt, ++col, SQL_C_BINARY, &pd1, sizeof(pd1), &cbVal));

		jASSERT0(!ja_strcmp("test1",pd1.sz));
		jASSERT0(0==pd1.i);

	}
	catch (cstr sz)
	{
		jWARN(_T("%s : %s"), sz, jT(GetSQLErrorStr(stmt).c_str() ) );
	}
}
