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

		// iLen���� ū �޸𸮸� Ȱ���Ͽ� ���� 
		//  ����Ȱ��� �޸𸮻����� realLen�� ������ ���� �Ͽ� �˼� �ִ�.
		//  TCHAR* p = char_p_new(... );
		// int * pLen = (int*)p;
		//  int realLen = *(--pLen);
		extern JBASE_API TCHAR* char_p_new(size_t iLen ); 
		extern JBASE_API void char_p_delete(TCHAR* p );
		extern JBASE_API TCHAR* char_p_resize(TCHAR**ppch , size_t iResize);// iResize�� ������ ����. ���� ����Ÿ�� �������.
		extern JBASE_API size_t char_p_size(TCHAR* p) ;

	}//nString


}



#endif // __jString_mem_header__
