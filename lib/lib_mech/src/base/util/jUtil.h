/* file : nUtil.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-30 10:35:10
title : 
desc : 

*/

#ifndef __jUtil_header__
#define __jUtil_header__
#pragma once


#ifdef JUTIL_EXPORTS
#define JUTIL_API __declspec(dllexport)
#else
#define JUTIL_API __declspec(dllimport)
#pragma comment(lib, "jUtil.lib")
#endif

extern JUTIL_API void jUtil_Create();

#endif // __jUtil_header__

