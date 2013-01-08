/* file : SafeDB_OdbcSP.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-19 17:50:33
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "SafeDB.h"
#include "interface/xml/jIVar.h"


namespace nMech
{
	namespace nDB
	{
		//////////////////////////////////////////////////////////////////////////

		OdbcRecord::OdbcRecord()
		{
			_rec = (void*)SQL_NULL_HANDLE;
		}

		OdbcRecord::~OdbcRecord()
		{
			Free();
		}

		OdbcRecord *OdbcRecord::BaseI()
		{
			return this;
		}

		bool OdbcRecord::IsAlloc()
		{
			return ((SQLHANDLE)_rec != SQL_NULL_HANDLE);
		}

		void OdbcRecord::Free()
		{
			if (IsAlloc())
			{
				jAUTO_LOCK_CS1(_db->BaseI()->_door);
				::SQLFreeHandle(SQL_HANDLE_STMT, (SQLHANDLE)_rec);
				_rec = (void*)SQL_NULL_HANDLE;
			}
		}

		bool OdbcRecord::Next()
		{
			m_iCol=1;
			SQLRETURN rc = ::SQLFetch((SQLHANDLE)_rec);
			return (rc == SQL_SUCCESS);
		}

		bool OdbcRecord::More()
		{
			SQLRETURN rc = ::SQLMoreResults((SQLHANDLE)_rec);
			return (rc == SQL_SUCCESS);
		}

		bool OdbcRecord::GetData(char& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_STINYINT, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(unsigned char& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_UTINYINT, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(short int& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_SSHORT, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(unsigned short int& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_USHORT, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(int &val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_SLONG, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(unsigned int& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_ULONG, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(long& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_SLONG, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(unsigned long& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_ULONG, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(INT64& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_SBIGINT, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(UINT64& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_UBIGINT, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(float& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_FLOAT, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(double& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_DOUBLE, &val, 0, &cbVal);
		}

		bool OdbcRecord::GetData(char* buf, int bufMaxLen)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_CHAR, buf, bufMaxLen, &cbVal);
		}

		bool OdbcRecord::GetData(wchar_t* buf, int bufMaxLen)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_WCHAR, buf, 2 * bufMaxLen, &cbVal);
		}

		bool OdbcRecord::GetData(void* buf, int bufMaxLen)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_BINARY, buf, bufMaxLen, &cbVal);
		}

		bool OdbcRecord::GetData(SYSTEMTIME& sysTime,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			TIMESTAMP_STRUCT timeStamp;
			ZeroMemory(&timeStamp, sizeof(timeStamp));

			SQLRETURN rc = ::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_TYPE_TIMESTAMP, &timeStamp, 0, &cbVal);

			if (rc == SQL_SUCCESS)
			{
				sysTime = _convert(timeStamp);
				return true;
			}
			ZeroMemory(&sysTime, sizeof(sysTime));
			return false;
		}
		bool OdbcRecord::GetData(SysTime& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			TIMESTAMP_STRUCT &timeStamp = val.BaseTS();
			SQLRETURN rc = ::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_TYPE_TIMESTAMP, &timeStamp, 0, &cbVal);

			if (rc == SQL_SUCCESS)
			{
				val.To_ST();
				return true;
			}
			ZeroMemory(&val, sizeof(val));
			return false;
		}
		bool OdbcRecord::GetData(TIMESTAMP_STRUCT& val,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			ZeroMemory(&val, sizeof(val));

			SQLRETURN rc = ::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_TYPE_TIMESTAMP, &val, 0, &cbVal);

			if (rc == SQL_SUCCESS)
			{
				return true;
			}
			ZeroMemory(&val, sizeof(val));
			return false;
		}

		bool OdbcRecord::GetData(aSafeName& name,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_CHAR, name._s, name.MaxLen(), &cbVal);
		}

		bool OdbcRecord::GetData(aSafePath& path,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_CHAR, path._s, path.MaxLen(), &cbVal);
		}

		bool OdbcRecord::GetData(aSafeMsg& msg,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_CHAR, msg._s, msg.MaxLen(), &cbVal);
		}

		bool OdbcRecord::GetData(wSafeName& name,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_WCHAR, name._s, 2 * name.MaxLen(), &cbVal);
		}

		bool OdbcRecord::GetData(wSafePath& path,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_WCHAR, path._s, 2 * path.MaxLen(), &cbVal);
		}

		bool OdbcRecord::GetData(wSafeMsg& msg,int /*not_used_arg=0*/)
		{
			SQLLEN cbVal = 0;
			return SQL_SUCCESS ==
				::SQLGetData((SQLHANDLE)_rec, m_iCol++, SQL_C_WCHAR, msg._s, 2 * msg.MaxLen(), &cbVal);
		}




		//--------------------------------------------------------------------------
		//		jOdbcParameter
		//--------------------------------------------------------------------------



		inline SQLSMALLINT _InOutType(SPTYPE type)
		{
			switch (type)
			{
			case SP_IN:    return SQL_PARAM_INPUT;
			case SP_OUT:   return SQL_PARAM_OUTPUT;
			case SP_INOUT: return SQL_PARAM_INPUT_OUTPUT;
			case SP_RET:   return SQL_RETURN_VALUE;
			default:       return 0;
			}
		}

		bool jOdbcParameter::IsAlloc()
		{
			return ((SQLHANDLE)_sp != SQL_NULL_HANDLE);
		}

		void jOdbcParameter::Free()
		{
			if (IsAlloc())
			{
				jAUTO_LOCK_CS1(_db->_door);

				::SQLFreeHandle(SQL_HANDLE_STMT, (SQLHANDLE)_sp);
				_sp = (void*)SQL_NULL_HANDLE;
				StrLenCount = 0;
			}
		}

		bool jOdbcParameter::Bind(SPTYPE type, char& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_STINYINT, SQL_TINYINT, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, unsigned char& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_UTINYINT, SQL_TINYINT, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, short int& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_SSHORT, SQL_SMALLINT, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, unsigned short int& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_USHORT, SQL_SMALLINT, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, int& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_SLONG, SQL_INTEGER, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, unsigned int& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_ULONG, SQL_INTEGER, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, long& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_SLONG, SQL_INTEGER, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, unsigned long& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_ULONG, SQL_INTEGER, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, INT64& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_SBIGINT, SQL_BIGINT, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, UINT64& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_UBIGINT, SQL_BIGINT, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, float& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_FLOAT, SQL_REAL, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, double& val,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_DOUBLE, SQL_DOUBLE, 0, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, const char* str)
		{
			//SQLLEN cbVal = SQL_LEN_DATA_AT_EXEC;  -- only for BINARY, LONG VARCHAR, long data
			//SQLLEN cbVal = SQL_DATA_AT_EXEC;      -- only for ODBCV 1.0 application

			SQLLEN* cbVal = GetLenPtr(0);
			SQLINTEGER len = (str == NULL ? 0: (SQLINTEGER)strlen(str));
			if (type == SP_IN)
				cbVal = NULL;
			else
				return false;

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_CHAR, SQL_VARCHAR, len, 0, (void*)str, len, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, const wchar_t* str)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			SQLINTEGER len = (str == NULL ? 0: (SQLINTEGER)wcslen(str));
			if (type == SP_IN)
				cbVal = NULL;
			else
				return false;

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_WCHAR, SQL_WVARCHAR, len, 0, (void*)str, len * 2, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, char* buf, int sizeof_buf)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = sizeof_buf;

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_CHAR, SQL_VARCHAR, sizeof_buf, 0, buf, sizeof_buf, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, WCHAR* buf, int sizeof_buf)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = sizeof_buf/2;

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_WCHAR, SQL_WVARCHAR, sizeof_buf/2, 0, buf, sizeof_buf, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, void* buf, int bufLen, int bufMaxLen)
		{
			SQLLEN* cbVal = GetLenPtr(0);

			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = bufLen;

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_BINARY,SQL_LONGVARBINARY , bufMaxLen, 0, buf, bufMaxLen, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, jDB_SYSTEMTIME&	val			,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 19, 0, &val.ts, 0, cbVal);
		}
		bool jOdbcParameter::Bind(SPTYPE type, SysTime&	val				,int /*not_used_arg=0*/)
		{
			if(type == SP_IN || type==SP_INOUT)
			{
				val.To_TS();
			}
			else
			{
				ZeroMemory(&val,sizeof(val));
			}

			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 19, 0, &val.BaseTS(), 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, TIMESTAMP_STRUCT &val	,int /*not_used_arg=0*/)
		{
			jRAISE(type == SP_IN); // TIMESTAMP_STRUCT는 SP_IN만 지원.
			//TIMESTAMP_STRUCT ts=_convert(val);

			SQLLEN* cbVal = GetLenPtr(0);
			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_TYPE_TIMESTAMP, SQL_TYPE_TIMESTAMP, 19, 0, &val, 0, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, aSafeName& name,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = name.Len();

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_CHAR, SQL_VARCHAR, name.MaxLen(), 0, name._s, name.MaxLen(), cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, aSafePath& path,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = path.Len();

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_CHAR, SQL_VARCHAR, path.MaxLen(), 0, path._s, path.MaxLen(), cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, aSafeMsg& msg,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = msg.Len();

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_CHAR, SQL_VARCHAR, msg.MaxLen(), 0, msg._s, msg.MaxLen(), cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, wSafeName& name,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = name.Len();

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_WCHAR, SQL_WVARCHAR, name.MaxLen(), 0, name._s, name.MaxLen() * 2, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, wSafePath& path,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = path.Len();

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_WCHAR, SQL_WVARCHAR, path.MaxLen(), 0, path._s, path.MaxLen() * 2, cbVal);
		}

		bool jOdbcParameter::Bind(SPTYPE type, wSafeMsg& msg,int /*not_used_arg=0*/)
		{
			SQLLEN* cbVal = GetLenPtr(0);
			if (type == SP_IN)
				cbVal = NULL;
			else if (type == SP_INOUT)
				*cbVal = msg.Len();

			return SQL_SUCCESS ==
				::SQLBindParameter(_sp, m_iCol++, _InOutType(type), SQL_C_WCHAR, SQL_WVARCHAR, msg.MaxLen(), 0, msg._s, msg.MaxLen() * 2, cbVal);
		}

		bool jOdbcParameter::Execute(OdbcRecord* record)
		{
			jAUTO_LOCK_CS1(_db->_door);

			if (pv_LogSqlQuery->Get_bool())
			{
				tSafeMsg paramInfo(_spName);
				if (paramInfo.Find('?') >= 0)
					((OdbcDB*)_db)->_GetParamInfo(_sp, paramInfo);
				_db->_OnError(_db->GetSvrName(), 0, _T("__DUMP__"), paramInfo._s);
			}

			SQLRETURN rc = ::SQLExecute(_sp);

			bool ret = SQL_OK(rc);
			if (ret)
			{
				if (record)
				{
					record->Free();
					record->_db = _db;
					record->_rec = _sp;
					_sp = SQL_NULL_HANDLE;
				}
				else
				{
					while (::SQLMoreResults(_sp) != SQL_NO_DATA)
					{
					}
				}
			}
			else
			{
				if (rc == SQL_NEED_DATA)
				{
					_db->_OnError(_db->GetSvrName(), rc, _spName, _T("Need more parameter data."));
					::SQLCancel(_sp);
				}
				else
				{
					((OdbcDB*)_db)->_ErrorStmt(_sp, _spName);
				}
			}

			return ret;
		}
		jOdbcParameter* jOdbcParameter::BaseI() { return this;}

		void jOdbcParameter::ExcuteNow(jISqlJob* pJob)
		{
			m_isExcuted = true;
			OdbcRecord rec;
			if (this->Execute(&rec))
			{
				rec.m_iCol=1;
				pJob->Fetch(&rec);
			}
		}

	}//namespace nDB


}// nMech


