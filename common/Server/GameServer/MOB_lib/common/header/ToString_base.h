/* file : ToString_base.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-23 13:51:33
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __ToString_base_header__
#define __ToString_base_header__
#pragma once

#ifdef DEF_WINDOWS
#define INT64_FMT "%I64d"
#define UINT64_FMT "%I64u"
#else
#define INT64_FMT "%lld"
#define UINT64_FMT "%llu"
#endif

namespace nMech
{
#define for_each_ToString_base_type(X)\
	X(int8,"%d")\
	X(uint8,"%u")\
	X(int16,"%d")\
	X(uint16,"%u")\
	X(int32,"%d")\
	X(uint32,"%u")\
	X(int64,INT64_FMT)\
	X(uint64,UINT64_FMT)\
	X(float,"%f")\
	X(double,"%f")\
	X(bool,"%d")\

	#define gen_ToString_base_type(TYPE,TOK) \
	inline tcstr	ToString(TYPE v,tname1024_t szBuf){ jt_sprintf(szBuf,_T(TOK),v);return szBuf;}\
	inline TYPE		FromString(TYPE* v,tcstr szBuf){jt_sscanf(szBuf,jT(TOK),v);return *v;}\
	inline TYPE		FromString(TYPE* v,std::tstring &szBuf){jt_sscanf(szBuf.c_str(),jT(TOK),v);return *v;}\

	for_each_ToString_base_type(gen_ToString_base_type);

#ifndef DEF_WINDOWS
	gen_ToString_base_type(size_t,"%u");
#endif

	
#define for_each_ToString_string_type(X)\
	X(acstr,"%s",jT(v))\
	X(std::astring,"%s",jT(v))\

//	X(wcstr,"%s",jT(v))\
//	X(std::wstring,"%s",jT(v))\

	#define gen_ToString_advance_type(TYPE,TOK,VAR) \
	inline tcstr ToString(TYPE v,tname1024_t szBuf){ jt_sprintf(szBuf,_T(TOK),VAR);return szBuf;}\

	for_each_ToString_string_type(gen_ToString_advance_type);


	void FromString(SYSTEMTIME* tm,tstring& str);
}

#endif // __ToString_base_header__
