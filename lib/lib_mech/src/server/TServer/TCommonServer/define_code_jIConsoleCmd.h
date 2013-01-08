/* file : define_code_jIConsoleCmd.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-15 04:11:59
comp.: t3.co.kr
title : 
desc : 


// console cmd .cpp에만 추가하자.


*/

#ifndef __define_code_jIConsoleCmd_header__
#define __define_code_jIConsoleCmd_header__
#pragma once


// jTODO : 테스트 되고 나서 jIConsoleCmd.h로 옮길것.
#define _jCONSOLE_VAL_tstring(VAL,TYPE,DEFAULT) tstring VAL= arg.size()<=e_##VAL ? (DEFAULT==0?_T(""):_T(DEFAULT)) : arg[e_##VAL];
#define _jCONSOLE_VAL_astring(VAL,TYPE,DEFAULT) astring VAL= arg.size()<=e_##VAL ? (DEFAULT==0? "":jA(DEFAULT) : jA(arg[e_##VAL]);
#define _jCONSOLE_VAL_wstring(VAL,TYPE,DEFAULT) tstring VAL= arg.size()<=e_##VAL ? (DEFAULT==0? L"":jW(DEFAULT) : jW(arg[e_##VAL]);



#endif // __define_code_jIConsoleCmd_header__
