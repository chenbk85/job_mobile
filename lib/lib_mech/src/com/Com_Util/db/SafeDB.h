//////////////////////////////////////////////////////////////////////////
// Safe DB/ODBC class
// Author: Chunmin Ahn (emocreator@gmail.com)
// Version: 1.07
// History: 
//  2007-03: Initial work
//  2007-10: Make abstract class, int type Data()/Bind()
//  2008-07: Support wide char type
//  2008-08: Fixed handle leak
//  2008-11: Support binary data type
//	2009-12: Add server name parameter on _OnError(), Add query dump features
//	2010-04: Execute/Prepare() with wide char type
//

#pragma once

#include <windows.h>
#include <sqlext.h>

#include "header/SafeStr.h"
#include "header/SafeWcs.h"

#include "interface/db/jIDB.h"

#pragma comment(lib, "odbc32.lib")

namespace nMech
{

//////////////////////////////////////////////////////////////////////////

	namespace nDB
	{

		//--------------------------------------------------------------------------
		class OdbcDB : public jIDB
			//--------------------------------------------------------------------------
		{
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIDB);

			bool Prepare(tcstr storedProc, jOdbcParameter* sp);
			bool Execute(tcstr sql, OdbcRecord* record=0);

		public:

			OdbcDB();
			virtual ~OdbcDB();
			void _Error(short handleType, void* handle, tcstr at);
			void _ErrorEnv(tcstr from);
			void _ErrorOdbc(tcstr from);
			void _ErrorStmt(void* handle, tcstr from);
			void _GetParamInfo(void* handle, tSafeMsg& msg);
			bool _IsLive();

			// jIDB에서 가져온것
			nUtil::jCriticalSection		_door;
		protected:
			fname_t		_svrName;
			fname_t		_usrName;
			fname_t		_pwd;

		protected:
			jSQLHANDLE			m_hEnv;
			jSQLHANDLE			m_hDBC;
			IOdbcErrorHandler*	_err;

		private:
			DWORD		_lastPingTime;
		};


		//--------------------------------------------------------------------------
		class OdbcRecord : public jISqlRecord
			//--------------------------------------------------------------------------
		{
			jINTERFACE_HEADER(jISqlRecord);
			uint16 m_iCol;

		public:
			struct jIDB*		_db;
			void*		_rec;

		public:
			OdbcRecord();
			virtual ~OdbcRecord();
		};
		inline uint16& OdbcRecord::GetCurrColumn() { return m_iCol;}


		//--------------------------------------------------------------------------
		class jOdbcParameter : public jISqlParameter
			//--------------------------------------------------------------------------
		{
			jINTERFACE_HEADER(jISqlParameter);

			bool Execute(OdbcRecord* record=0);
			uint16 m_iCol;


		public:
			jOdbcParameter::jOdbcParameter() : StrLenCount(0),_sp(SQL_NULL_HANDLE),_db(0),m_iCol(0)	,m_isExcuted(false){	}
			jOdbcParameter::~jOdbcParameter()	{Free();	}


			SQLLEN* GetLenPtr(long val)
			{
				SQLLEN* ptr = &StrLen[StrLenCount++];
				*ptr = val;
				return ptr;
			}
			bool m_isExcuted;
			SQLLEN StrLen[MAX_ODBC_SP_PARAM];
			long StrLenCount;
			OdbcDB*		_db;
			void*		_sp;
			tname1024_t _spName;

		};
		inline uint16& jOdbcParameter::GetCurrColumn(){ return m_iCol;}

		extern jIVar* pv_LogSqlQuery;

	}//namespace nDB


}//namespace nMech