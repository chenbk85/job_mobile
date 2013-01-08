/* file : db_uid_type.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-08 20:55:44
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __db_uid_type_header__
#define __db_uid_type_header__
#pragma once

//#include "header/jHeader.h"
using namespace nMech;
#ifdef USE_db_uid_type
struct db_uid_type
{
	union
	{
		nMech::int64		m_db_id;
		time_t				m_t;
		SYSTEMTIME			m_st;

	};
	bool operator ==(const db_uid_type& uid)const {return m_db_id==uid.m_db_id;}
	bool operator <(const db_uid_type& uid)const {return m_db_id<uid.m_db_id;}
	struct less	{bool operator()( const db_uid_type& uid1, const db_uid_type& uid2) const{ return (uid1.m_db_id<uid2.m_db_id);}	};
	operator nMech::int64(){return m_db_id;}
};
#endif
typedef int64 db_uid_type;
typedef db_uid_type db_uid_type_ref;
typedef db_uid_type j_time_t; // squrrel에서 int64를 지원안하기때문에....

inline int64& FromeString(OUT int64 &id,IN fname_t sz)
{
#ifdef DEF_WINDOWS
	jt_sscanf(sz , _T("%I64d"),&id);
#else
	jt_sscanf(sz , _T("%lld"),&id);
#endif
	return id;
}
#ifdef USE_db_uid_type
inline cstr ToString(IN db_uid_type dbid,OUT afname_t sz)
{
#ifdef DEF_WINDOWS
	jt_sprintf(sz,"%I64d",dbid.m_db_id);
#else
	jt_sprintf(sz,"%lld",dbid.m_db_id);
#endif
	return sz;
}

inline db_uid_type &FromeString(OUT db_uid_type &dbid,IN fname_t sz)
{
	FromeString(dbid.m_db_id,sz);return dbid;
}
#endif

inline cstr ToString(SYSTEMTIME t,fname_t sz)
{
	jt_sprintf(sz, _T(jPRINTF_SYSTEMTIME),jSPREED_SYSTEMTIME(t));
	return sz;
}
inline SYSTEMTIME& FromString(OUT SYSTEMTIME& t,IN fname_t sz)
{
	jt_sscanf(sz,_T(jPRINTF_SYSTEMTIME),jSPREED_SYSTEMTIME_PTR(t));
	return t;
}

#endif // __db_uid_type_header__
