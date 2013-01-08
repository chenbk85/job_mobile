/* file : jString_mem.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-27 10:12:30
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jString_mem_header__
#define __jString_mem_header__
#pragma once


namespace nMech
{
	namespace nString
	{
		const size_t  iOFFSET = 1+sizeof(size_t);

		// iLen보다 큰 메모리를 활당하여 리턴 
		//  실제활당된 메모리사이즈 realLen은 다음과 같이 하여 알수 있다.
		//  TCHAR* p = char_p_new(... );
		// int * pLen = (int*)p;
		//  int realLen = *(--pLen);
		extern JBASE_API TCHAR* char_p_new(size_t iLen ); 
		extern JBASE_API void char_p_delete(TCHAR* p );
		extern JBASE_API TCHAR* char_p_resize(TCHAR**ppch , size_t iResize);// iResize로 사이즈 조정. 기존 데이타는 복사안함.
		extern JBASE_API size_t char_p_size(TCHAR* p) ;

	}//nString


}



#endif // __jString_mem_header__
