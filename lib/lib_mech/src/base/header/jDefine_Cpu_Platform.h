/* file : jCpu_Platform.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-29 13:51:59
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jCpu_Platform_header__
#define __jCpu_Platform_header__
	
#pragma once


	#if defined(WIN32) && !defined(WIN64)
		#define _CPU_X86
		// Insert your headers here
		#include <windows.h>
		#define RC_EXECUTABLE "rc.exe"
	#endif

	#if defined(WIN64)
		#define _CPU_AMD64
		// Insert your headers here
		#include <windows.h>
		#define RC_EXECUTABLE "rc64.exe"
	#endif


#endif // __jCpu_Platform_header__
