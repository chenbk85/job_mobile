/* file : config_all_server.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2011-12-14 16:37:10
comp.: neowiz.co.kr
title : 
desc : 

*/

#ifndef __config_all_server_header__
#define __config_all_server_header__
#pragma once


#include <cstdlib>
#include <iostream>

//stl
#include <vector>
#include <list>
#include <queue>
#include <algorithm>
#include <functional>
#include <deque>

//boost
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>


#pragma warning(disable : 4819)
#pragma warning(disable : 949)

#include "header/jDefine.h"
#include "header/jTypedef_type.h"
#include "header/m_stltag.h"

using namespace nMech;

//로그 보기

#if 0
#undef jLOG
#undef jWARN
#undef jERROR

#ifdef DEF_WINDOWS
#		define jLOG(...) jt_printf(_T("\n") __VA_ARGS__) ;
#		define jWARN(...) jt_printf(jFUNC1 jDEBUG_LINE_INFO _T("\n[WARN]") __VA_ARGS__) ;
#		define jERROR(...) jt_printf(jFUNC1 jDEBUG_LINE_INFO  _T("\n[ERROR]") __VA_ARGS__) ;
#else
#		define jLOG(...) printf(_T("\n") __VA_ARGS__) ;
#		define jWARN(...) printf(_T("\n[WARN]") __VA_ARGS__) ;
#		define jERROR(...) printf(_T("\n[ERROR]") __VA_ARGS__) ;
#endif
#endif


#ifdef DEF_WINDOWS
#	include <tchar.h>
#else
#	define _T(X) X
#endif



#ifdef DEF_LINUX
//typedef nMech::int64				ptrdiff_t;
typedef nMech::tcstr				LPCTSTR;
typedef nMech::acstr				LPCSTR;

#endif




#endif // __config_all_server_header__
