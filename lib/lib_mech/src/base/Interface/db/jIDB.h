/* file : jIDB.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-18 18:33:56
comp.: t3.co.kr
title : 
desc : 



	모든 함수는 에러시 tstring 또는 tcstr을 throw한다.

*/

#ifndef __jIDB_header__
#define __jIDB_header__
#pragma once

#include "base/SafeDateTime.h"
#include "header/SafeStr.h"
#include "header/SafeWcs.h"

#define MAX_ODBC_SP_PARAM	64
#define MAX_ODBC_ERR		5

namespace nMech
{
	namespace nDB
	{
		typedef void*					jSQLHANDLE;

		// odbc patch param type
		enum SPTYPE
		{
			SP_IN = 1,
			SP_OUT,
			SP_INOUT,
			SP_RET,
		};

		struct jDB_SYSTEMTIME
		{
			SPTYPE eType;
			SYSTEMTIME& st;
			TIMESTAMP_STRUCT ts;
			jDB_SYSTEMTIME(SYSTEMTIME& _st,SPTYPE _type): st(_st)	,eType(_type) 
			{
				if(eType==SP_IN || eType==SP_INOUT) ts = _convert(st);
				else								memset(&ts,0,sizeof(ts));
			}
			~jDB_SYSTEMTIME(){	if(eType==SP_OUT || eType==SP_INOUT) st = _convert(ts);}
		};

		enum EProtocolsDB
		{
			protoNamedPipes,
			protoWinSock,
			protoIPX,
			protoBanyan,
			protoRPC
		};

		struct jISqlJob
		{	
			// 두함수 모두 에러시 tcstr에러 스트링을 throw하자.

			virtual void Bind(struct jISqlParameter* pSP){}// 프로시져 파라미터 세팅
			virtual void Fetch(struct jISqlRecord* pR){}//프로시져 결과레코드처리.
		};

		//--------------------------------------------------------------------------
		struct IOdbcErrorHandler
			//--------------------------------------------------------------------------
		{
		public:
			virtual void _OnError(tcstr svrName, int code, tcstr from, tcstr msg)
			{
				jERROR_T("[OdbcDB] %s:%d %s - %s", svrName, code, from, msg);
			}
		};

#define jINTERFACE_jISqlParameter_Extend jINTERFACE_jISqlParameter_Extend_org

#define jINTERFACE_jISqlParameter(XX) public:	\
	virtual class jOdbcParameter* BaseI() XX\
	virtual bool IsAlloc() XX\
	virtual void Free()  XX\
	virtual uint16& GetCurrColumn() XX\
	virtual void ExcuteNow(jISqlJob* pJob) XX\
	\
	virtual bool Bind(SPTYPE type, char& val				,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, unsigned char& val		,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, short int& val			,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, unsigned short int& val	,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, int& val					,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, unsigned int& val		,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, long& val				,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, unsigned long& val		,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, __int64& val				,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, unsigned __int64& val	,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, float& val				,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, double& val				,int not_used_arg=0)XX\
	\
	/* 주의 jDB_SYSTEMTIME를 사용할때는 jISqlParameter::ExcuteNow()로 실행해야 한다.*/\
	virtual bool Bind(SPTYPE type, jDB_SYSTEMTIME&	val		,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, TIMESTAMP_STRUCT& val	,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, SysTime&		val			,int not_used_arg=0)XX\
	\
	virtual bool Bind(SPTYPE type, aSafeName&	val			,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, aSafePath&	val			,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, aSafeMsg&	val			,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, wSafeName&	val			,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, wSafePath&	val			,int not_used_arg=0)XX\
	virtual bool Bind(SPTYPE type, wSafeMsg&	val			,int not_used_arg=0)XX\
	\
	/*주의 : INPUT전용 함수 */ \
	virtual bool Bind(SPTYPE type, const char* str)XX\
	virtual bool Bind(SPTYPE type, const wchar_t* str)XX\
	\
	virtual bool Bind(SPTYPE type, char* buf		, int sizeof_buf)XX\
	virtual bool Bind(SPTYPE type, WCHAR* buf		, int sizeof_buf)XX\
	\
	virtual bool Bind(SPTYPE type, void* bin		, int bufLen, int sizeof_buf)XX\

	jINTERFACE_END(jISqlParameter);


#define jINTERFACE_jISqlRecord(XX) public:	\
	virtual class OdbcRecord *BaseI() XX\
	virtual uint16& GetCurrColumn() XX\
	virtual bool IsAlloc() XX\
	virtual void Free() XX\
	virtual bool Next() XX\
	virtual bool More() XX\
	virtual bool GetData(int8& val				,int not_used_arg=0) XX\
	virtual bool GetData(uint8& val				,int not_used_arg=0) XX\
	virtual bool GetData(int16& val				,int not_used_arg=0) XX\
	virtual bool GetData(uint16& val			,int not_used_arg=0) XX\
	virtual bool GetData(int32&val				,int not_used_arg=0) XX\
	virtual bool GetData(uint32& val			,int not_used_arg=0) XX\
	virtual bool GetData(long& val				,int not_used_arg=0) XX\
	virtual bool GetData(unsigned long& val		,int not_used_arg=0) XX\
	virtual bool GetData(int64& val				,int not_used_arg=0) XX\
	virtual bool GetData(uint64& val			,int not_used_arg=0) XX\
	virtual bool GetData(float& val				,int not_used_arg=0) XX\
	virtual bool GetData(double& val			,int not_used_arg=0) XX\
	\
	virtual bool GetData(SYSTEMTIME& val		,int not_used_arg=0) XX\
	virtual bool GetData(SysTime& val			,int not_used_arg=0) XX\
	virtual bool GetData(TIMESTAMP_STRUCT& val	,int not_used_arg=0) XX\
	\
	virtual bool GetData(aSafeName& name		,int not_used_arg=0) XX\
	virtual bool GetData(aSafePath& path		,int not_used_arg=0) XX\
	virtual bool GetData(aSafeMsg& msg			,int not_used_arg=0) XX\
	virtual bool GetData(wSafeName& name		,int not_used_arg=0) XX\
	virtual bool GetData(wSafePath& path		,int not_used_arg=0) XX\
	virtual bool GetData(wSafeMsg& msg			,int not_used_arg=0) XX\
	\
	virtual bool GetData(char* buf				,int bufMaxLen) XX\
	virtual bool GetData(wchar_t* buf			,int bufMaxLen) XX\
	virtual bool GetData(void* buf				,int bufMaxLen) XX\

		jINTERFACE_END(jISqlRecord);


#define jINTERFACE_jIDB(XX) public:	\
	virtual class OdbcDB* BaseI() XX\
	virtual void SetInfo(tcstr svrName, tcstr usrName, tcstr pwd) XX\
	virtual void SetError(IOdbcErrorHandler* err) XX\
	virtual void Open() XX\
	/*Driver={SQL Server};Address=127.0.0.1,1433\sam_db;Server=;Uid=sa;Pwd=qwer;Trusted_Connection=Yes;Database=tgame_db;Network=dbmssocn*/\
	virtual bool OpenDirect(cstr szConnectionString) XX\
	virtual bool Transact() XX\
	virtual bool Rollback() XX\
	virtual bool Commit() XX\
	virtual void _OnError(tcstr svrName, int code, tcstr from, tcstr msg) XX\
	virtual tcstr GetSvrName() XX\
	virtual bool Ping() XX\
	virtual void Close() XX\
	\
	/* 에러시 tcstr를 throw 한다.*/\
	virtual void RunSQL(tcstr szSQL,jISqlJob* pJob,bool runFetch=true) XX\
	virtual void RunSQL_Direct(tcstr szSQL,jISqlJob* pJob=0) XX\

		jINTERFACE_END_BASE1(jIDB, nInterface::jIInterface);
	
	}//namespace nDB
}//namespace nMech


#define jDB_BIND(JOB_NAME,X)	jLAMDA_begin2(JOB_NAME,jISqlJob);void Bind(X) 
#define jDB_PATCH(X)			void Fetch(X)
#define jDB_END()				jLAMDA_end()


/*
 사용법.
	
	nDB::jIDB* pjIDB = jCREATE_INTERFACE(nMech::nDB::jIDB);

	pjIDB->Release();




	#define jLAMDA_datetime_insert(X,Z) X(test_struct*,R) Z(test_struct& ,retval)
	jDB_BIND(datetime_insert,jISqlParameter* b)
	{
		jASSERT0(pSP->Bind(SP_IN, p->sz));
	}
	jDB_PATCH(jISqlRecord* p)
	{
		jASSERT0(p->GetData(p->sz));
	}
	jDB_END();
	pjIDB->RunSQL(_T("exec datetime_insert ?,?,?") , datetime_insert(r,retval));


*/

#endif // __jIDB_header__
