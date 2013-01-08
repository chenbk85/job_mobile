/* file : jDefine_log.h
Coder : by icandoit ( mech12@nate.com)
Date : 2011-07-25 14:12:19
comp.: neobian.co.kr
title : 
desc : 

*/

#ifndef __jDefine_log_header__
#define __jDefine_log_header__
#pragma once


//--------------------------------------------------------------------------
// 로그 매크로.
//--------------------------------------------------------------------------
#ifdef DEF_WINDOWS
#include <tchar.h>
#else
#define _T(X) X
#endif

#define _STRINGIFY(x) _T(#x)
#define _TOSTRING(x) _STRINGIFY(x)
#define jDEBUG_LINE_INFO _T(":") _T(__FILE__) _T(":") _TOSTRING(__LINE__) _T(" ")

#define jLOG_T(fmt,...) do{GetjILog()->Log(GetCurrentThreadId(),_T(fmt),__VA_ARGS__);}while(0);
#define jWARN_T(fmt,...) do{GetjILog()->Warning(GetCurrentThreadId(),_T(fmt) jFUNC1 jDEBUG_LINE_INFO ,__VA_ARGS__);}while(0);
#define jERROR_T(fmt,...) do{GetjILog()->Error(GetCurrentThreadId(),_T(fmt) jFUNC1 jDEBUG_LINE_INFO ,__VA_ARGS__);}while(0);

#define jLOG(...) do { GetjILog()->Log(GetCurrentThreadId(),__VA_ARGS__); }while(0);
#define jWARN(...) do{GetjILog()->Warning(GetCurrentThreadId(),jFUNC1 jDEBUG_LINE_INFO __VA_ARGS__);}while(0);
#define jERROR(...) do{GetjILog()->Error(GetCurrentThreadId(),jFUNC1 jDEBUG_LINE_INFO __VA_ARGS__);}while(0);


#define jASSERT_TAG					UIDEN(__ASSERT_)

#define jASSERT(exp,...) do{if(!(exp)) {jERROR(_T("jASSERT: ") _T(#exp) _T(")")  __VA_ARGS__);}}while(0);
#define jASSERT0(exp) do{if(!(exp)){jERROR(_T(#exp) _T("jASSERT0:")  );}}while(0);

#define jIF_NOT(exp)  bool jASSERT_TAG=(exp);if(!jASSERT_TAG){jWARN(_T(#exp) _T(" jIF_NOT:") ); };if(!jASSERT_TAG)
#define jvIF_NOT(exp,...) bool jASSERT_TAG=(exp);if(!jASSERT_TAG){jWARN(_T(#exp) _T(" jIF_NOT:")  __VA_ARGS__); };if(!jASSERT_TAG)

#define jIF(exp) bool jASSERT_TAG=(exp);if(jASSERT_TAG){jWARN(_T(#exp) _T(" jIF:") ); };if(jASSERT_TAG)
#define jvIF(exp,...) bool jASSERT_TAG=(exp);if(jASSERT_TAG){jWARN(_T(#exp) _T(" jvIF:")  __VA_ARGS__); };if(jASSERT_TAG)

//--------------------------------------------------------------------------
// [WARN] 출력용 로그.
//--------------------------------------------------------------------------
#define jCHECK(exp) do{if(!(exp)){jWARN(_T("jCHECK(") _T(#exp) _T(")")  );}}while(0);
#define jCONTINUE(exp) do{if(!(exp)){jWARN(_T("jCONTINUE(") _T(#exp) _T(")")  );continue;}}while(0);
#define jBREAK(exp) do{if(!(exp)){jWARN(_T("jBREAK(") _T(#exp) _T(")") );break;}}while(0);
#define jTHROW(exp) do{if(!(exp)){jWARN(_T("jTHROW(") _T(#exp) _T(")") );throw _T("jTHROW : ") _T(#exp)  ;}}while(0);
#define jRETURN(exp) do{if(!(exp)){jWARN( _T("jRETURN(") _T(#exp) _T(")")  );  return;}}while(0);
#define jRETURN_ret(ret,exp) do{if(!(exp)){jWARN(_T("jRETURN_VAL : ") _T(#exp) _T(")")  );  return ret;}}while(0);
#define jRAISE(exp) do{if(!(exp)){jERROR( _T("jRAISE(") _T(#exp) _T(")")  );RaiseException( __LINE__,EXCEPTION_ACCESS_VIOLATION, 0, NULL );}}while(0);

#define jvCHECK(exp,...) do{if(!(exp)){jWARN(_T("jvCHECK(") _T(#exp) _T(")") __VA_ARGS__);}}while(0);
#define jvCONTINUE(exp,...) do{if(!(exp)){jWARN(_T("jvCONTINUE :") _T(#exp) __VA_ARGS__);continue;}}while(0);
#define jvBREAK(exp,...) do{if(!(exp)){jWARN(_T("jvBREAK(") _T(#exp) _T(")")  __VA_ARGS__);break;}}while(0);
#define jvTHROW(exp,...) do{if(!(exp)){jWARN(_T("jvTHROW(") _T(#exp) _T(")")  __VA_ARGS__);throw _T("jvTHROW : ") _T(#exp)  ;}}while(0);
#define jvRETURN(exp,...) do{if(!(exp)){jWARN( _T("jvRETURN(") _T(#exp) _T(")")   __VA_ARGS__);  return;}}while(0);
#define jvRETURN_ret(ret,exp, ...) do{if(!(exp)){jWARN(_T("jvRETURN_ret(") _T(#exp)  _T(")")  __VA_ARGS__);  return ret;}}while(0);
#define jvRAISE(exp,...) do{if(!(exp)){jERROR( _T("jvRAISE(") _T(#exp) _T(")")   __VA_ARGS__);  \
	RaiseException( __LINE__, EXCEPTION_ACCESS_VIOLATION, 0, NULL );}}while(0);


//--------------------------------------------------------------------------
// count만큼만 로그찍음.
//--------------------------------------------------------------------------

#define jLOG_T_C(count,fmt,...) do{static int jASSERT_TAG=0;if(jASSERT_TAG++<count){GetjILog()->Log(GetCurrentThreadId(),_T(fmt),__VA_ARGS__);}}while(0);
#define jWARN_T_C(count,fmt,...) do{static int jASSERT_TAG=0;if(jASSERT_TAG++<count){GetjILog()->Warning(GetCurrentThreadId(),jFUNC1 _T(fmt),__VA_ARGS__);}}while(0);
#define jERROR_T_C(count,fmt,...) do{static int jASSERT_TAG=0;if(jASSERT_TAG++<count){GetjILog()->Error(GetCurrentThreadId(),jFUNC1 _T(fmt),__VA_ARGS__);}}while(0);

#define jLOG_C(count,...) do{static int jASSERT_TAG=0;if(jASSERT_TAG++<count){GetjILog()->Log(GetCurrentThreadId(),__VA_ARGS__);}}while(0);
#define jWARN_C(count,...) do{static int jASSERT_TAG=0;if(jASSERT_TAG++<count){GetjILog()->Warning(GetCurrentThreadId(),jFUNC1 __VA_ARGS__);}}while(0);
#define jERROR_C(count,...)do{ static int jASSERT_TAG=0;if(jASSERT_TAG++<count){GetjILog()->Error(GetCurrentThreadId(),jFUNC1 __VA_ARGS__);}}while(0);

#define jCHECK_C(count,exp) do{if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jCHECK(") _T(#exp)  _T(")") ) ;}}}while(0);
#define jCONTINUE_C(count,exp)do{ if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jCONTINUE(") _T(#exp) _T(")") );}continue;}}while(0);
#define jBREAK_C(count,exp) do{if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jBREAK(") _T(#exp)  _T(")");}break;}}while(0);
#define jTHROW_C(count,exp) do{if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jTHROW(") _T(#exp)  _T(")") );}throw _T("jTHROW : ") _T(#exp)  ;}}while(0);
#define jRETURN_C(count,exp) do{if(!(exp)){static int __count__=0;if(__count__++<count){jWARN( _T("jRETURN : ") _T(#exp)   _T(")") );}  return;}}while(0);
#define jRETURN_C_ret(count,ret,exp) do{if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jRETURN_VAL : ") _T(#exp)  _T(")") );}  return ret;}}while(0);
#define jRAISE_C(count,exp) do{if(!(exp)){static int __count__=0;if(__count__++<count){jERROR( _T("jRETURN : ") _T(#exp)  _T(")") );}  \
							RaiseException( __LINE__,EXCEPTION_ACCESS_VIOLATION, 0, NULL ); }}while(0);

#define jvCHECK_C(count,exp,...) do{if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jvCHECK_C:") _T(#exp)  _T(")") __VA_ARGS__);} }}while(0);
#define jvCONTINUE_C(count,exp,...) do{if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jvCONTINUE_C:") _T(#exp)  _T(")") __VA_ARGS__);} continue;}}while(0);
#define jvBREAK_C(count,exp,...) do{if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jvBREAK_C:") _T(#exp)  _T(")") __VA_ARGS__);} break;}}while(0);
#define jvTHROW_C(count,exp,...) do{if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jvTHROW_C:") _T(#exp)  _T(")") __VA_ARGS__);throw _T("jvTHROW_C:") _T(#exp) _T(" ") jDEBUG_LINE_INFO;}}while(0);
#define jvRETURN_C(count,exp,...) do{if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN( _T("jvRETURN_C: ") _T(#exp)   __VA_ARGS__);}  return;}}while(0);
#define jvRETURN_C_ret(count,ret,exp, ...) do{if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jRETURN_VAL : ") _T(#exp)   __VA_ARGS__);} return ret;}}while(0);
#define jvRAISE_C(exp,...) do{if(!(exp)){static int __count__=0;if(__count__++<count){ jERROR( _T("jvRAISE_C:") _T(#exp)   __VA_ARGS__);}  \
							RaiseException( __LINE__, EXCEPTION_ACCESS_VIOLATION, 0, NULL );}}while(0);


//--------------------------------------------------------------------------
// per 마다 로그찍음.
//--------------------------------------------------------------------------

#define jLOG_T_P(per,fmt,...) do{static int jASSERT_TAG=0;if(!(jASSERT_TAG++ % per)){GetjILog()->Log(GetCurrentThreadId(),_T(fmt),__VA_ARGS__);}}while(0);
#define jWARN_T_P(per,fmt,...) do{static int jASSERT_TAG=0;if(!(jASSERT_TAG++ % per)){GetjILog()->Warning(GetCurrentThreadId(),jFUNC1 _T(fmt),__VA_ARGS__);}}while(0);
#define jERROR_T_P(per,fmt,...) do{static int jASSERT_TAG=0;if(!(jASSERT_TAG++ % per)){GetjILog()->Error(GetCurrentThreadId(),jFUNC1 _T(fmt),__VA_ARGS__);}}while(0);

#define jLOG_P(per,...) do{static int jASSERT_TAG=0;if(!(jASSERT_TAG++%per)){GetjILog()->Log(GetCurrentThreadId(),__VA_ARGS__);}}while(0);
#define jWARN_P(per,...) do{static int jASSERT_TAG=0;if(!(jASSERT_TAG++%per)){GetjILog()->Warning(GetCurrentThreadId(),jFUNC1 __VA_ARGS__);}}while(0);
#define jERROR_P(per,...) do{static int jASSERT_TAG=0;if(!(jASSERT_TAG++%per)){GetjILog()->Error(GetCurrentThreadId(),jFUNC1 __VA_ARGS__);}}while(0);

#define jCHECK_P(per,exp) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jCHECK_P(") _T(#exp)  _T(")") );}}}while(0);
#define jCONTINUE_P(per,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jCONTINUE_P(") _T(#exp)   _T(")") );}continue;}}while(0);
#define jBREAK_P(per,exp) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jBREAK_P(") _T(#exp)  _T(")") );}break;}}while(0);
#define jTHROW_P(per,exp) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jTHROW_P(") _T(#exp)  _T(")") );}throw _T("jTHROW : ") _T(#exp)  _T(" ")  jDEBUG_LINE_INFO;}}while(0);
#define jRETURN_P(per,exp) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN( _T("jRETURN_P(") _T(#exp)  _T(")") );}  return;}}while(0);
#define jRETURN_P_ret(per,ret,exp) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jRETURN_P_ret(") _T(#exp)  _T(")") );}  return ret;}}while(0);
#define jRAISE_P(per,exp) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){jERROR( _T("jRAISE_P(") _T(#exp)  _T(")"));}  \
	RaiseException( __LINE__,EXCEPTION_ACCESS_VIOLATION, 0, NULL ); }}while(0);

#define jvCHECK_P(per,exp,...) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvCHECK_P(") _T(#exp)  _T(")") __VA_ARGS__);} }}while(0);
#define jvCONTINUE_P(per,exp,...) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvCONTINUE_P(") _T(#exp)  _T(")") __VA_ARGS__);} continue;}}while(0);
#define jvBREAK_P(per,exp,...) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvBREAK_P(") _T(#exp)  _T(")") __VA_ARGS__);} break;}}while(0);
#define jvTHROW_P(per,exp,...) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvTHROW_P(") _T(#exp)  _T(")") __VA_ARGS__);} throw _T("jTHROW : ") _T(#exp) _T(" ")  jDEBUG_LINE_INFO;}}while(0);
#define jvRETURN_P(per,exp,...) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN( _T("jvRETURN_P(") _T(#exp)  _T(")") __VA_ARGS__);}  return;}}while(0);
#define jvRETURN_P_ret(per,ret,exp, ...) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvRETURN_P_ret(") _T(#exp)  _T(")") __VA_ARGS__);} return ret;}}while(0);
#define jvRAISE_P(exp,...) do{if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jERROR( _T("jvRAISE_P(") _T(#exp)  _T(")") __VA_ARGS__);}  \
	RaiseException( __LINE__, EXCEPTION_ACCESS_VIOLATION, 0, NULL );}}while(0);



//--------------------------------------------------------------------------
// [ERROR] 에러출력용 로그.
//--------------------------------------------------------------------------
#define jCHECK_E(exp) do{if(!(exp)){jERROR(_T("jCHECK_E") _T(#exp) );}}while(0);
#define jCONTINUE_E(exp) do{if(!(exp)){jERROR(_T("jCONTINUE_E") _T(#exp) );continue;}}while(0);
#define jBREAK_E(exp) do{if(!(exp)){jERROR(_T("jBREAK_E") _T(#exp) );break;}}while(0);
#define jTHROW_E(exp) do{if(!(exp)){jERROR(_T("jTHROW_E") _T(#exp) );throw _T("jTHROW_E(") _T(#exp)  _T(")") jDEBUG_LINE_INFO;}}while(0);
#define jRETURN_E(exp) do{if(!(exp)){jERROR( _T("jRETURN_E(") _T(#exp)   _T(")"));  return;}}while(0);
#define jRETURN_ret_E(ret,exp) do{if(!(exp)){jERROR(_T("jRETURN_ret_E(") _T(#exp)  _T(")") );  return ret;}}while(0);

#define jvCHECK_E(exp,...) do{if(!(exp)){jERROR(_T("jvCHECK_E(") _T(#exp)  _T(")") __VA_ARGS__);}}while(0);
#define jvCONTINUE_E(exp,...) do{if(!(exp)){jERROR(_T("jvCONTINUE_E(") _T(#exp)  _T(")") __VA_ARGS__);continue;}}while(0);
#define jvBREAK_E(exp,...) do{if(!(exp)){jERROR(_T("jvBREAK_E(") _T(#exp)  _T(")") __VA_ARGS__);break;}}while(0);
#define jvTHROW_E(exp,...) do{if(!(exp)){jERROR(_T("jvTHROW_E(") _T(#exp)  _T(")") __VA_ARGS__);throw _T("jvTHROW_E : ") _T(#exp)  jDEBUG_LINE_INFO;}}while(0);
#define jvRETURN_E(exp,...) do{if(!(exp)){jERROR( _T("jvRETURN_E(") _T(#exp)  _T(")")  __VA_ARGS__);  return;}}while(0);
#define jvRETURN_ret_E(ret,exp, ...) do{if(!(exp)){jERROR(_T("jvRETURN_ret_E(") _T(#exp)  _T(")")  __VA_ARGS__);  return ret;}}while(0);

#define apiCHECK(exp) do{if(!(exp)){jWARN(_T("apiCHECK(") _T(#exp) _T(") GetLastError(%d)"),GetLastError());}}while(0);
#define apiCONTINUE(exp)do{ if(!(exp)){jWARN(_T("apiCONTINUE(") _T(#exp) _T("GetLastError(%d)"),GetLastError());continue;}}while(0);
#define apiBREAK(exp)do{ if(!(exp)){jWARN(_T("apiBREAK(") _T(#exp) _T(") GetLastError(%d)"),GetLastError());break;}}while(0);
#define apiTHROW(exp) do{if(!(exp)){jWARN(_T("apiTHROW(") _T(#exp) _T(") GetLastError(%d)"),GetLastError());throw _T("jTHROW : ") _T(#exp)  jDEBUG_LINE_INFO;}}while(0);
#define apiRETURN(exp) do{if(!(exp)){jWARN( _T("apiRETURN(") _T(#exp)  _T(") ") _T("GetLastError(%d) :"),GetLastError() );  return;}}while(0);
#define apiRETURN_ret(ret,exp) do{if(!(exp)){jWARN(_T("apiRETURN_ret(") _T(#exp)  _T(") ") _T("GetLastError(%d) : "),GetLastError() );  return ret;}}while(0);




#define _BF(X) endl<< boost::tformat(_T(X))
#define __BF(X) boost::tformat(_T(X))


#endif // __jDefine_log_header__
