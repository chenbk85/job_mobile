/* file : j_strsafe.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-19 22:31:06
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __j_strsafe_header__
#define __j_strsafe_header__
#pragma once

#define STRSAFE_NO_DEPRECATE

#ifndef STRSAFE_NO_DEPRECATE
#pragma deprecated( "strncpy" )
#pragma deprecated( "wcsncpy" )
#pragma deprecated( "_tcsncpy" )
#pragma deprecated( "wcsncat" )
#pragma deprecated( "strncat" )
#pragma deprecated( "_tcsncat" )
#endif

#include <strsafe.h>


#endif // __j_strsafe_header__
