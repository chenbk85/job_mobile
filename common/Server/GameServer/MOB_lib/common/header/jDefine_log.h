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

#ifndef DEF_WINDOWS
#define GetCurrentThreadId() 0
#endif

//--------------------------------------------------------------------------
// 로그 매크로.
//--------------------------------------------------------------------------
#define _STRINGIFY(x) _T(#x)
#define _TOSTRING(x) _STRINGIFY(x)
#define jDEBUG_LINE_INFO _T(":") _T(__FILE__) _T(":") _TOSTRING(__LINE__) _T(" ")

#define jLOG(...) GetjILog()->Log(GetCurrentThreadId(),__VA_ARGS__);
#ifdef DEF_WINDOWS
#define jWARN(...) GetjILog()->Warning(GetCurrentThreadId(),jFUNC1 jDEBUG_LINE_INFO __VA_ARGS__);
#define jERROR(...) GetjILog()->Error(GetCurrentThreadId(),jFUNC1 jDEBUG_LINE_INFO __VA_ARGS__);
#else
#define jWARN(...) GetjILog()->Warning(0,jDEBUG_LINE_INFO "%s>",jFUNC);GetjILog()->Warning(0, __VA_ARGS__);
#define jERROR(...) GetjILog()->Warning(0,jDEBUG_LINE_INFO  "%S>",jFUNC); GetjILog()->Error(0,__VA_ARGS__);
#endif





#define jASSERT_TAG					UIDEN(__ASSERT_)

#define jASSERT(exp,...) if(!(exp)) {jERROR(_T("jASSERT: ") _T(#exp) _T(")")  __VA_ARGS__);}
#define jASSERT0(exp) if(!(exp)){jERROR(_T(#exp) _T("jASSERT0:")  );}

#define jIF_NOT(exp) bool jASSERT_TAG=(exp);if(!jASSERT_TAG){jWARN(_T(#exp) _T(" jIF_NOT:") ); };if(!jASSERT_TAG)
#define jvIF_NOT(exp,...) bool jASSERT_TAG=(exp);if(!jASSERT_TAG){jWARN(_T(#exp) _T(" jIF_NOT:")  __VA_ARGS__); };if(!jASSERT_TAG)

#define jIF(exp) bool jASSERT_TAG=(exp);if(jASSERT_TAG){jWARN(_T(#exp) _T(" jIF_NOT:") ); };if(jASSERT_TAG)
#define jvIF(exp,...) bool jASSERT_TAG=(exp);if(jASSERT_TAG){jWARN(_T(#exp) _T(" jIF_NOT:")  __VA_ARGS__); };if(jASSERT_TAG)

//--------------------------------------------------------------------------
// [WARN] 출력용 로그.
//--------------------------------------------------------------------------
#define jCHECK(exp) if(!(exp)){jWARN(_T("jCHECK(") _T(#exp) _T(")")  );}
#define jCONTINUE(exp) if(!(exp)){jWARN(_T("jCONTINUE(") _T(#exp) _T(")")  );continue;}
#define jBREAK(exp) if(!(exp)){jWARN(_T("jBREAK(") _T(#exp) _T(")") );break;}
#define jTHROW(exp) if(!(exp)){jWARN(_T("jTHROW(") _T(#exp) _T(")") );throw _T("jTHROW : ") _T(#exp)  ;}
#define jRETURN(exp) if(!(exp)){jWARN( _T("jRETURN(") _T(#exp) _T(")")  );  return;}
#define jRETURN_ret(ret,exp) if(!(exp)){jWARN(_T("jRETURN_VAL : ") _T(#exp) _T(")")  );  return ret;}
#define jRAISE(exp) if(!(exp)){jERROR( _T("jRAISE(") _T(#exp) _T(")")  );  \
	RaiseException( __LINE__,EXCEPTION_ACCESS_VIOLATION, 0, NULL );}

#define jvCHECK(exp,...) if(!(exp)){jWARN(_T("jvCHECK(") _T(#exp) _T(")") __VA_ARGS__);}
#define jvCONTINUE(exp,...) if(!(exp)){jWARN(_T("jvCONTINUE :") _T(#exp) __VA_ARGS__);continue;}
#define jvBREAK(exp,...) if(!(exp)){jWARN(_T("jvBREAK(") _T(#exp) _T(")")  __VA_ARGS__);break;}
#define jvTHROW(exp,...) if(!(exp)){jWARN(_T("jvTHROW(") _T(#exp) _T(")")  __VA_ARGS__);throw _T("jvTHROW : ") _T(#exp)  ;}
#define jvRETURN(exp,...) if(!(exp)){jWARN( _T("jvRETURN(") _T(#exp) _T(")")   __VA_ARGS__);  return;}
#define jvRETURN_ret(ret,exp, ...) if(!(exp)){jWARN(_T("jvRETURN_ret(") _T(#exp)  _T(")")  __VA_ARGS__);  return ret;}
#define jvRAISE(exp,...) if(!(exp)){jERROR( _T("jvRAISE(") _T(#exp) _T(")")   __VA_ARGS__);  \
	RaiseException( __LINE__, EXCEPTION_ACCESS_VIOLATION, 0, NULL );}


//--------------------------------------------------------------------------
// count만큼만 로그찍음.
//--------------------------------------------------------------------------

#define jLOG_T_C(count,fmt,...) static int jASSERT_TAG=0;if(jASSERT_TAG++<count){jLOG(_T(fmt),__VA_ARGS__);}
#define jWARN_T_C(count,fmt,...) static int jASSERT_TAG=0;if(jASSERT_TAG++<count){jWARN(_T(fmt),__VA_ARGS__);}
#define jERROR_T_C(count,fmt,...) static int jASSERT_TAG=0;if(jASSERT_TAG++<count){jERROR(_T(fmt),__VA_ARGS__);}

#define jLOG_C(count,...) static int jASSERT_TAG=0;if(jASSERT_TAG++<count){jLOG(__VA_ARGS__);}
#define jWARN_C(count,...) static int jASSERT_TAG=0;if(jASSERT_TAG++<count){jWARN(__VA_ARGS__);}
#define jERROR_C(count,...) static int jASSERT_TAG=0;if(jASSERT_TAG++<count){jERROR(__VA_ARGS__);}

#define jCHECK_C(count,exp) if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jCHECK(") _T(#exp)  _T(")") ) ;}}
#define jCONTINUE_C(count,exp) if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jCONTINUE(") _T(#exp) _T(")") );}continue;}
#define jBREAK_C(count,exp) if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jBREAK(") _T(#exp)  _T(")");}break;}
#define jTHROW_C(count,exp) if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jTHROW(") _T(#exp)  _T(")") );}throw _T("jTHROW : ") _T(#exp)  ;}
#define jRETURN_C(count,exp) if(!(exp)){static int __count__=0;if(__count__++<count){jWARN( _T("jRETURN : ") _T(#exp)   _T(")") );}  return;}
#define jRETURN_C_ret(count,ret,exp) if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jRETURN_VAL : ") _T(#exp)  _T(")") );}  return ret;}
#define jRAISE_C(count,exp) if(!(exp)){static int __count__=0;if(__count__++<count){jERROR( _T("jRETURN : ") _T(#exp)  _T(")") );}  \
							RaiseException( __LINE__,EXCEPTION_ACCESS_VIOLATION, 0, NULL ); }

#define jvCHECK_C(count,exp,...) if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jvCHECK_C:") _T(#exp)  _T(")") __VA_ARGS__);} }
#define jvCONTINUE_C(count,exp,...) if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jvCONTINUE_C:") _T(#exp)  _T(")") __VA_ARGS__);} continue;}
#define jvBREAK_C(count,exp,...) if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jvBREAK_C:") _T(#exp)  _T(")") __VA_ARGS__);} break;}
#define jvTHROW_C(count,exp,...) if(!(exp)){static int __count__=0;if(__count__++<count){jWARN(_T("jvTHROW_C:") _T(#exp)  _T(")") __VA_ARGS__);throw _T("jvTHROW_C:") _T(#exp) _T(" ") jDEBUG_LINE_INFO;}
#define jvRETURN_C(count,exp,...) if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN( _T("jvRETURN_C: ") _T(#exp)   __VA_ARGS__);}  return;}
#define jvRETURN_C_ret(count,ret,exp, ...) if(!(exp)){static int __count__=0;if(__count__++<count){ jWARN(_T("jRETURN_VAL : ") _T(#exp)   __VA_ARGS__);} return ret;}
#define jvRAISE_C(exp,...) if(!(exp)){static int __count__=0;if(__count__++<count){ jERROR( _T("jvRAISE_C:") _T(#exp)   __VA_ARGS__);}  \
							RaiseException( __LINE__, EXCEPTION_ACCESS_VIOLATION, 0, NULL );}


//--------------------------------------------------------------------------
// per 마다 로그찍음.
//--------------------------------------------------------------------------

#define jLOG_T_P(per,fmt,...) static int jASSERT_TAG=0;if(!(jASSERT_TAG++ % per)){jLOG(_T(fmt),__VA_ARGS__);}
#define jWARN_T_P(per,fmt,...) static int jASSERT_TAG=0;if(!(jASSERT_TAG++ % per)){jWARN(_T(fmt),__VA_ARGS__);}
#define jERROR_T_P(per,fmt,...) static int jASSERT_TAG=0;if(!(jASSERT_TAG++ % per)){jERROR(_T(fmt),__VA_ARGS__);}

#define jLOG_P(per,...) static int jASSERT_TAG=0;if(!(jASSERT_TAG++%per)){jLOG(__VA_ARGS__);}
#define jWARN_P(per,...) static int jASSERT_TAG=0;if(!(jASSERT_TAG++%per)){jWARN(__VA_ARGS__);}
#define jERROR_P(per,...) static int jASSERT_TAG=0;if(!(jASSERT_TAG++%per)){jERROR(__VA_ARGS__);}

#define jCHECK_P(per,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jCHECK_P(") _T(#exp)  _T(")") );}}
#define jCONTINUE_P(per,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jCONTINUE_P(") _T(#exp)   _T(")") );}continue;}
#define jBREAK_P(per,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jBREAK_P(") _T(#exp)  _T(")") );}break;}
#define jTHROW_P(per,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jTHROW_P(") _T(#exp)  _T(")") );}throw _T("jTHROW : ") _T(#exp)  _T(" ")  jDEBUG_LINE_INFO;}
#define jRETURN_P(per,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN( _T("jRETURN_P(") _T(#exp)  _T(")") );}  return;}
#define jRETURN_P_ret(per,ret,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){jWARN(_T("jRETURN_P_ret(") _T(#exp)  _T(")") );}  return ret;}
#define jRAISE_P(per,exp) if(!(exp)){static int __count__=0;if(!(__count__++%per)){jERROR( _T("jRAISE_P(") _T(#exp)  _T(")"));}  \
	RaiseException( __LINE__,EXCEPTION_ACCESS_VIOLATION, 0, NULL ); }

#define jvCHECK_P(per,exp,...) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvCHECK_P(") _T(#exp)  _T(")") __VA_ARGS__);} }
#define jvCONTINUE_P(per,exp,...) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvCONTINUE_P(") _T(#exp)  _T(")") __VA_ARGS__);} continue;}
#define jvBREAK_P(per,exp,...) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvBREAK_P(") _T(#exp)  _T(")") __VA_ARGS__);} break;}
#define jvTHROW_P(per,exp,...) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvTHROW_P(") _T(#exp)  _T(")") __VA_ARGS__);} throw _T("jTHROW : ") _T(#exp) _T(" ")  jDEBUG_LINE_INFO;}
#define jvRETURN_P(per,exp,...) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN( _T("jvRETURN_P(") _T(#exp)  _T(")") __VA_ARGS__);}  return;}
#define jvRETURN_P_ret(per,ret,exp, ...) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jWARN(_T("jvRETURN_P_ret(") _T(#exp)  _T(")") __VA_ARGS__);} return ret;}
#define jvRAISE_P(exp,...) if(!(exp)){static int __count__=0;if(!(__count__++%per)){ jERROR( _T("jvRAISE_P(") _T(#exp)  _T(")") __VA_ARGS__);}  \
	RaiseException( __LINE__, EXCEPTION_ACCESS_VIOLATION, 0, NULL );}



//--------------------------------------------------------------------------
// [ERROR] 에러출력용 로그.
//--------------------------------------------------------------------------
#define jCHECK_E(exp) if(!(exp)){jERROR(_T("jCHECK_E") _T(#exp) );}
#define jCONTINUE_E(exp) if(!(exp)){jERROR(_T("jCONTINUE_E") _T(#exp) );continue;}
#define jBREAK_E(exp) if(!(exp)){jERROR(_T("jBREAK_E") _T(#exp) );break;}
#define jTHROW_E(exp) if(!(exp)){jERROR(_T("jTHROW_E") _T(#exp) );throw _T("jTHROW_E(") _T(#exp)  _T(")") jDEBUG_LINE_INFO;}
#define jRETURN_E(exp) if(!(exp)){jERROR( _T("jRETURN_E(") _T(#exp)   _T(")"));  return;}
#define jRETURN_ret_E(ret,exp) if(!(exp)){jERROR(_T("jRETURN_ret_E(") _T(#exp)  _T(")") );  return ret;}

#define jvCHECK_E(exp,...) if(!(exp)){jERROR(_T("jvCHECK_E(") _T(#exp)  _T(")") __VA_ARGS__);}
#define jvCONTINUE_E(exp,...) if(!(exp)){jERROR(_T("jvCONTINUE_E(") _T(#exp)  _T(")") __VA_ARGS__);continue;}
#define jvBREAK_E(exp,...) if(!(exp)){jERROR(_T("jvBREAK_E(") _T(#exp)  _T(")") __VA_ARGS__);break;}
#define jvTHROW_E(exp,...) if(!(exp)){jERROR(_T("jvTHROW_E(") _T(#exp)  _T(")") __VA_ARGS__);throw _T("jvTHROW_E : ") _T(#exp)  jDEBUG_LINE_INFO;}
#define jvRETURN_E(exp,...) if(!(exp)){jERROR( _T("jvRETURN_E(") _T(#exp)  _T(")")  __VA_ARGS__);  return;}
#define jvRETURN_ret_E(ret,exp, ...) if(!(exp)){jERROR(_T("jvRETURN_ret_E(") _T(#exp)  _T(")")  __VA_ARGS__);  return ret;}

#define apiCHECK(exp) if(!(exp)){jWARN(_T("apiCHECK(") _T(#exp) _T(") GetLastError(%d)"),GetLastError());}
#define apiCONTINUE(exp) if(!(exp)){jWARN(_T("apiCONTINUE(") _T(#exp) _T("GetLastError(%d)"),GetLastError());continue;}
#define apiBREAK(exp) if(!(exp)){jWARN(_T("apiBREAK(") _T(#exp) _T(") GetLastError(%d)"),GetLastError());break;}
#define apiTHROW(exp) if(!(exp)){jWARN(_T("apiTHROW(") _T(#exp) _T(") GetLastError(%d)"),GetLastError());throw _T("jTHROW : ") _T(#exp)  jDEBUG_LINE_INFO;}
#define apiRETURN(exp) if(!(exp)){jWARN( _T("apiRETURN(") _T(#exp)  _T(") ") _T("GetLastError(%d) :"),GetLastError() );  return;}
#define apiRETURN_ret(ret,exp) if(!(exp)){jWARN(_T("apiRETURN_ret(") _T(#exp)  _T(") ") _T("GetLastError(%d) : "),GetLastError() );  return ret;}





#endif // __jDefine_log_header__
