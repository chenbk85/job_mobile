/* file : define_code_TCommonClient.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-15 04:14:01
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __define_code_TCommonClient_header__
#define __define_code_TCommonClient_header__
#pragma once


#define 	jSORT(X) std::sort(X.begin() , X.end() );


#define jLAMDA_vector_string_to_file(X,Z) Z(FILE*,fp)
jLAMDA_for_each(vector_string_to_file, tstring&)	{jt_fprintf(fp, _T("%s\n") , it.c_str());} jLAMDA_end();
jLAMDA_for_each0(vector_string_to_console, tstring&)	{jLOG1(_T("%s"), it.c_str());}jLAMDA_end();
jLAMDA_for_each0(vector_wstring_to_console, wstring&)	{jLOG1(_T("%s"), nUNI::scb256_t(it.c_str()).getT());}jLAMDA_end();

//	jLOG1(_T("%s : %s") , szName, nUNI::scb256_t(msg).getT());



#endif // __define_code_TCommonClient_header__
