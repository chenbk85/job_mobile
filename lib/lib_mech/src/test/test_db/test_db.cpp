
// test_db.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"


/*

Windows Registry Editor Version 5.00

[HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBC.INI\ODBC Data Sources]
"test_db"="SQL Native Client"

[HKEY_LOCAL_MACHINE\SOFTWARE\ODBC\ODBC.INI\test_db]
"Driver"="c:\\WINDOWS\\system32\\SQLNCLI.DLL"
"Server"="50.10.250.126"
"Database"="master"
"LastUser"="sa"


*/

using namespace nMech::nDB;


void test_open()
{
	jMech_Init(true);
	nDB::jIDB* pjIDB = jCREATE_INTERFACE(nMech::nDB::jIDB);
	jASSERT0(pjIDB);

	pjIDB->SetInfo(jS(test_db), jS(sa), jS(qwer));
	try
	{
		pjIDB->Open();
	}
	catch (cstr sz)
	{
		jWARN(_T("%s 디비연결안됨"), sz );
	}

	pjIDB->Release();

	jMech_Close();
}


void test_sql_param2_output1()
{
	nDB::jIDB* pjIDB = jCREATE_INTERFACE(nMech::nDB::jIDB);
	jASSERT0(pjIDB);

	pjIDB->SetInfo(jS(test_db), jS(sa), jS(qwer));
	try
	{
		pjIDB->Open();

		tcstr szSQL=
_T("IF  EXISTS (SELECT name FROM sys.databases WHERE name = N'test_db2')  DROP DATABASE [test_db2]\
CREATE DATABASE [test_db2] ON  PRIMARY ( NAME = N'test_db2', FILENAME = N'c:\\test_db2.mdf' , SIZE = 100000KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB ) LOG ON ( NAME = N'test_db2_log', FILENAME = N'c:\\test_db2_log.ldf' , SIZE = 100000KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)");

		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[test1]') \
AND type in (N'U')) DROP TABLE [dbo].[test1] \
create table test1 ( \n\
val int IDENTITY(1,1) NOT NULL\n\
, txt varchar(1024) \n\
, data INT \n\
)");
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[BIN_INSERT]') \
					AND type in (N'P', N'PC')) DROP PROCEDURE [dbo].[BIN_INSERT]" );
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("CREATE PROCEDURE [dbo].[BIN_INSERT] \n\
@txt varchar(1024) \n\
,@data INT \n\
,@ret int OUTPUT \n\
AS \n\
BEGIN \n\
INSERT INTO [test1]( txt ,data) \n\
VALUES( @txt , @data) \n\
set @ret = 1234 \n\
END");

		pjIDB->RunSQL(szSQL,0);

		struct test_struct
		{
			int i;
			float f;
			aname_t sz;
		};
		#define jLAMDA_bin_insert(X,Z) \
			X(test_struct*,p)\
			Z(int&,ret)

		jLAMDA_begin2(bin_insert,jISqlJob);
		void Bind(jISqlParameter* pSP) 
		{
			bool is = pSP->Bind(SP_IN, p->sz);
			is = pSP->Bind(SP_IN, p->i);
			is = pSP->Bind(SP_OUT, ret);
		}
		jLAMDA_end();
		
		szSQL = _T("{call bin_insert(?,?,?)}");
		int ret=111;
		test_struct t = { 1,99.9f , ("test1") };
		pjIDB->RunSQL(szSQL , &bin_insert( &t , ret ) , false );
		jASSERT0(ret==1234);
	}
	catch (cstr sz)
	{
		jWARN(_T("%s"), sz );
	}
	pjIDB->Release();
}




void test_sql_param2_fetch1()
{
	nDB::jIDB* pjIDB = jCREATE_INTERFACE(nMech::nDB::jIDB);
	jASSERT0(pjIDB);

	pjIDB->SetInfo(jS(test_db), jS(sa), jS(qwer));
	try
	{
		pjIDB->Open();

		tcstr szSQL=
			_T("IF  EXISTS (SELECT name FROM sys.databases WHERE name = N'test_db2')  DROP DATABASE [test_db2]\
			   CREATE DATABASE [test_db2] ON  PRIMARY ( NAME = N'test_db2', FILENAME = N'c:\\test_db2.mdf' , SIZE = 100000KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB ) LOG ON ( NAME = N'test_db2_log', FILENAME = N'c:\\test_db2_log.ldf' , SIZE = 100000KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)");

		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[test1]') \
				   AND type in (N'U')) DROP TABLE [dbo].[test1] \
				   create table test1 ( \n\
				   val int IDENTITY(1,1) NOT NULL\n\
				   , txt nvarchar(1024) \n\
				   , data INT \n\
				   )");
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[BIN_INSERT]') \
				   AND type in (N'P', N'PC')) DROP PROCEDURE [dbo].[BIN_INSERT]" );
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("\n\
CREATE PROCEDURE [dbo].[BIN_INSERT] \n\
@txt nvarchar(1024) \n\
,@data INT \n\
AS \n\
BEGIN \n\
SET NOCOUNT ON \n\
INSERT INTO [test1]( txt ,data) \n\
VALUES( @txt , @data) \n\
select 888 \n\
END");

		pjIDB->RunSQL(szSQL,0);

		struct test_struct
		{
			int i;
			float f;
			wname_t sz;
		};
#define jLAMDA_bin_insert1(X,Z) \
	X(test_struct*,p)\
	Z(int&,ret)

		jLAMDA_begin2(bin_insert1,jISqlJob);
		void Bind(jISqlParameter* pSP) 
		{
			bool is = pSP->Bind(SP_IN, p->sz);
			is = pSP->Bind(SP_IN, p->i);
			is = pSP->Bind(SP_OUT, ret);
		}

		void Fetch(jISqlRecord* pR)
		{
			if(pR->Next())
			{
				pR->GetData(ret);
			}
			jASSERT0(ret= 888);
		}
		jLAMDA_end();

		szSQL = _T("{call bin_insert(?,?)}");
		int ret=111;
		test_struct t = { 1,99.9f , L"test1" };
		pjIDB->RunSQL(szSQL , &bin_insert1( &t , ret ) );
	}
	catch (cstr sz)
	{
		jWARN(_T("%s"), sz );
	}
	pjIDB->Release();
}

void test_sql_param2_fetch1_DirectOpen()
{
	nDB::jIDB* pjIDB = jCREATE_INTERFACE(nMech::nDB::jIDB);
	jASSERT0(pjIDB);

	try
	{
		pjIDB->OpenDirect(_T("Driver={SQL Server};Address=127.0.0.1,1433\test_db;Server=;Uid=sa;Pwd=qwer;Trusted_Connection=Yes;Database=master;Network=dbmssocn") );
		//pjIDB->OpenDirect(_T("50.10.250.126,1433\\test_db"), _T(""), _T("sa"),_T("qwer"),_T("master"),0,nDB::protoWinSock);

		tcstr szSQL=
			_T("IF  EXISTS (SELECT name FROM sys.databases WHERE name = N'test_db2')  DROP DATABASE [test_db2]\
			   CREATE DATABASE [test_db2] ON  PRIMARY ( NAME = N'test_db2', FILENAME = N'c:\\test_db2.mdf' , SIZE = 100000KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB ) LOG ON ( NAME = N'test_db2_log', FILENAME = N'c:\\test_db2_log.ldf' , SIZE = 100000KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)");

		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[test1]') \
				   AND type in (N'U')) DROP TABLE [dbo].[test1] \
				   create table test1 ( \n\
				   val int IDENTITY(1,1) NOT NULL\n\
				   , txt nvarchar(1024) \n\
				   , data INT \n\
				   )");
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[BIN_INSERT]') \
				   AND type in (N'P', N'PC')) DROP PROCEDURE [dbo].[BIN_INSERT]" );
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("\n\
				   CREATE PROCEDURE [dbo].[BIN_INSERT] \n\
				   @txt nvarchar(1024) \n\
				   ,@data INT \n\
				   ,@outString VARCHAR(32) OUTPUT\n\
				   AS \n\
				   BEGIN \n\
				   SET NOCOUNT ON \n\
				   INSERT INTO [test1]( txt ,data) \n\
				   VALUES( @txt , @data) \n\
				   set @outString = 'asdfasdf' \n\
				   select 888 \n\
				   select 777 \n\
				   END");

		pjIDB->RunSQL(szSQL,0);

		struct test_struct
		{
			int i;
			float f;
			wname_t sz;
			aname_t outString;
		};

#define jLAMDA_bin_insert12(X,Z) X(test_struct*,p) X(int& ,ret2) Z(int&,ret)
		jLAMDA_begin2(bin_insert12,jISqlJob);
		void Bind(jISqlParameter* pSP) 
		{
			jASSERT0(pSP->Bind(SP_IN, p->sz));
			jASSERT0(pSP->Bind(SP_IN, p->i));
			jASSERT0(pSP->Bind(SP_OUT, p->outString,_countof(p->outString)));
		}

		void Fetch(jISqlRecord* pR)
		{
			if(pR->Next())
			{
				pR->GetData(ret );
			}

			if(pR->More())
			{
				if(pR->Next())
				{
					pR->GetData(ret2);
				}
			}
		}
		jLAMDA_end();

		szSQL = _T("{call bin_insert(?,?,?)}");
		int ret=111;
		int ret2=0;
		test_struct t = { 1,99.9f , L"test1" };
		pjIDB->RunSQL(szSQL , &bin_insert12( &t , ret2,ret ) );
		jASSERT0(ret==888);
		jASSERT0(ret2==777);
		jASSERT0(ja_strcmp(t.outString, "asdfasdf")==0);
	}
	catch (cstr sz)
	{
		jWARN(_T("%s"), sz );
	}
	pjIDB->Release();
}



test_struct pd;



void test_sql_param_binary()
{
	nDB::jIDB* pjIDB = jCREATE_INTERFACE(nMech::nDB::jIDB);
	jASSERT0(pjIDB);

	pjIDB->SetInfo(jS(test_db), jS(sa), jS(qwer));
	try
	{
		pjIDB->Open();

		tcstr szSQL;

		//pjIDB->RunSQL_Direct(0,0);
		//return;


		szSQL = _T("use test_db2");
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[test1]') \
				   AND type in (N'U')) DROP TABLE [dbo].[test1] \
				   create table test1 ( \n\
				   val int IDENTITY(1,1) NOT NULL\n\
				   , txt varchar(1024) \n\
				   , data INT \n\
				   , bin varbinary(1024) \n\
				   )");
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[BIN_INSERT]') \
				   AND type in (N'P', N'PC')) DROP PROCEDURE [dbo].[BIN_INSERT]" );
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("\n\
				   CREATE PROCEDURE [dbo].[BIN_INSERT] \n\
				   @txt varchar(1024) \n\
				   ,@data INT \n\
				   ,@bin varbinary(1024) \n\
				   AS \n\
				   BEGIN \n\
				   SET NOCOUNT ON \n\
				   INSERT INTO [test1]( txt ,data, bin) \n\
				   VALUES( @txt , @data, @bin) \n\
				   select * from test1 \n\
				   END");

		pjIDB->RunSQL(szSQL,0);

#define jLAMDA_bin_insert2(X,Z) \
	X(test_struct*,pasdf)\
	Z(int&,ret)

		jLAMDA_begin2(bin_insert2,jISqlJob);
		void Bind(jISqlParameter* pSP) 
		{
			bool is = pSP->Bind(SP_IN, pd.sz);
			assert(is);
			is = pSP->Bind(SP_IN, pd.i);
			assert(is);
			is = pSP->Bind(SP_IN, (void*)&pd, sizeof(test_struct),sizeof(test_struct));//sizeof(test_struct),sizeof(test_struct));
			assert(is);
		}

		void Fetch(jISqlRecord* pR)
		{
			if(pR->Next())
			{
				int id;
				aname_t txt;
				int data;
				memset(&pd,0,sizeof(test_struct));
				bool is = pR->GetData(id);
				assert(is);
				is = pR->GetData(txt,sizeof(txt));
				assert(is);
				is = pR->GetData(data);
				assert(is);
				is = pR->GetData((void*)&pd, sizeof(test_struct));// sizeof(test_struct));
				assert( is == true);
			}
			jASSERT0(ret= 888);
		}
		jLAMDA_end();

		szSQL = _T("exec bin_insert ?,?,? ");
		int ret=111;
		//test_struct t = { "test1",222,333,99.9f };
		//pd = t;
		pjIDB->RunSQL(szSQL , &bin_insert2(  &pd , ret ) );
		jASSERT0(!ja_strcmp("test1",pd.sz));
		jASSERT0(222==pd.i);

	}
	catch (cstr sz)
	{
		jWARN(_T("%s"), sz );
	}
	pjIDB->Release();
}



string GetSQLErrorStr(SQLHANDLE Handle, SQLSMALLINT iHandleType)
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

void test_sql_time()
{
	nDB::jIDB* pjIDB = jCREATE_INTERFACE(nMech::nDB::jIDB);
	jASSERT0(pjIDB);

	try
	{
		//pjIDB->OpenDirect(_T("Driver={SQL Server};Address=127.0.0.1,1433\test_db;Server=;Uid=sa;Pwd=qwer;Trusted_Connection=Yes;Database=master;Network=dbmssocn") );
		pjIDB->OpenDirect(_T("Driver={SQL Server};Server=icandoit\\sqlexpress;Uid=sa;Pwd=qwer;Trusted_Connection=Yes;Database=master;Network=dbmssocn") );

		//pjIDB->OpenDirect(_T("50.10.250.126,1433\\test_db"), _T(""), _T("sa"),_T("qwer"),_T("master"),0,nDB::protoWinSock);

		tcstr szSQL=
			_T("IF  EXISTS (SELECT name FROM sys.databases WHERE name = N'test_db2')  DROP DATABASE [test_db2]\
			   CREATE DATABASE [test_db2] ON  PRIMARY ( NAME = N'test_db2', FILENAME = N'c:\\temp\\test_db2.mdf' , SIZE = 100000KB , MAXSIZE = UNLIMITED, FILEGROWTH = 1024KB ) LOG ON ( NAME = N'test_db2_log', FILENAME = N'c:\\temp\\test_db2_log.ldf' , SIZE = 100000KB , MAXSIZE = 2048GB , FILEGROWTH = 10%)");

		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[test1]') \
				   AND type in (N'U')) DROP TABLE [dbo].[test1] \
				   create table test1 ( \n\
				   val int IDENTITY(1,1) NOT NULL\n\
				   , txt nvarchar(1024) \n\
				   , data INT \n\
				   , mydatetime datetime DEFAULT(getdate())\n\
				   , mydatetime2 datetime DEFAULT(getdate())\n\
				   )");
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[BIN_INSERT]') \
				   AND type in (N'P', N'PC')) DROP PROCEDURE [dbo].[BIN_INSERT]" );
		pjIDB->RunSQL(szSQL,0);

		szSQL = _T("\n\
				   CREATE PROCEDURE [dbo].[BIN_INSERT] \n\
				   @txt nvarchar(1024) \n\
				   ,@data INT \n\
				   ,@outString VARCHAR(32) OUTPUT\n\
				   AS \n\
				   BEGIN \n\
				   SET NOCOUNT ON \n\
				   INSERT INTO [test1]( txt ,data) \n\
				   VALUES( @txt , @data) \n\
				   set @outString = 'asdfasdf' \n\
				   select * from test1 \n\
				   select 888 \n\
				   select 777 \n\
				   END");

		pjIDB->RunSQL(szSQL,0);

		struct test_struct
		{
			int i;
			float f;
			wname_t sz;
			aname_t outString;
			SYSTEMTIME m_st;
			SysTime t;
			//TIMESTAMP_STRUCT t;
		};
		test_struct r;

#define jLAMDA_bin_insert123(X,Z) X(test_struct*,p) X(int& ,ret2) X(test_struct& ,r) Z(int&,ret)
		jLAMDA_begin2(bin_insert123,jISqlJob);
		void Bind(jISqlParameter* pSP) 
		{
			jASSERT0(pSP->Bind(SP_IN, p->sz));
			jASSERT0(pSP->Bind(SP_IN, p->i));
			jASSERT0(pSP->Bind(SP_OUT, p->outString,_countof(p->outString)));
			//jASSERT0(pSP->Bind(SP_OUT, p->t));
		}
		void Fetch(jISqlRecord* pR)
		{
			if(pR->Next())
			{
				pR->GetData(r.i);
				pR->GetData(r.sz,_countof(r.sz) );
				pR->GetData(r.i);
				pR->GetData(r.t);
			}
			if(pR->More())
			{
				if(pR->Next())
				{
					pR->GetData(ret );
				}
			}
			if(pR->More())
			{
				if(pR->Next())
				{
					pR->GetData(ret2);
				}
			}
		}
		jLAMDA_end();

		szSQL = _T("{call bin_insert(?,?,?)}");
		int ret=111;
		int ret2=0;
		test_struct t = { 1,99.9f , L"test1" };
		pjIDB->RunSQL(szSQL , &bin_insert123( &t , ret2, r ,ret ) );
		jASSERT0(ret==888);
		jASSERT0(ret2==777);
		jASSERT0(ja_strcmp(t.outString, "asdfasdf")==0);
		
		szSQL = _T("IF  EXISTS (SELECT * FROM sys.objects WHERE object_id = OBJECT_ID(N'[dbo].[datetime_insert]') \n\
					   AND type in (N'P', N'PC')) DROP PROCEDURE [dbo].[datetime_insert] \n");
		pjIDB->RunSQL(szSQL,0);

	   szSQL = _T("CREATE PROCEDURE [dbo].[datetime_insert] \n\
				   @txt nvarchar(1024) \n\
				   ,@data INT \n\
				   ,@time DATETIME \n\
				   ,@time2 DATETIME \n\
				   AS \n\
				   BEGIN \n\
				   SET NOCOUNT ON \n\
				   INSERT INTO [test1]( txt ,data,mydatetime,mydatetime2) \n\
				   VALUES( @txt , @data, @time,@time2) \n\
				   select * from test1 where val=@@identity \n\
				   END");

		pjIDB->RunSQL(szSQL,0);
	
		test_struct out;
		memset(&out,0,sizeof(out));

#define jLAMDA_datetime_insert(X,Z) X(test_struct&,in) Z(test_struct& ,out)
		jDB_BIND(datetime_insert,jISqlParameter* b)
		{
			jASSERT0(b->Bind(SP_IN, in.sz));
			jASSERT0(b->Bind(SP_IN, in.i));
			jASSERT0(b->Bind(SP_IN, in.t)); // test ok!
			jDB_SYSTEMTIME _st(in.m_st,SP_IN);
			jASSERT0(b->Bind(SP_IN, _st));
			b->ExcuteNow(this);
		}
		jDB_PATCH(jISqlRecord* p)
		{
			if(p->Next())
			{
				jASSERT0(p->GetData(out.i));
				jASSERT0(p->GetData(out.sz,_countof(out.sz) ) );
				jASSERT0(p->GetData(out.i));
				jASSERT0(p->GetData(out.t)); // test ok
				jASSERT0(p->GetData(out.m_st));
			}
		}
		jDB_END();

		GetLocalTime(&r.m_st);
		GetLocalTime(&r.t);
		pjIDB->RunSQL(_T("exec datetime_insert ?,?,?,?") , &datetime_insert(r,out));
		jASSERT0(r.i==out.i);
		jASSERT0(r.t.wSecond==out.t.wSecond);
		jASSERT0(r.m_st.wSecond==out.m_st.wSecond);

	}
	catch (cstr sz)
	{
		jWARN(_T("%s"), sz );
	}
	pjIDB->Release();
}


int _tmain(int argc, _TCHAR* argv[])
{
	void test_jCriticalSection();test_jCriticalSection();

	//int test_cls();test_cls();
	jMech_Init(true);
	//void test_jThread();test_jThread();

	void 	test_bind_static_dynamic_array();
	test_bind_static_dynamic_array();

	//test_open(); ok
	//test_sql_param2_output1(); ok
	//test_sql_param2_fetch1();// odbc:test_db미리 세팅되어있어야함 ok
	//test_sql_param2_fetch1_DirectOpen(); //ok
	test_sql_time(); // ok
	//void test_sql_binary_test_raw();void test_sql_binary_test_raw(); //error
	//int main_putimage();main_putimage(); // error
	//test_sql_param_binary_asdf(); // error



	jMech_Close();

	return 0;
}


