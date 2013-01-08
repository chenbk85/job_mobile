// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

// 아래 지정된 플랫폼에 우선하는 플랫폼을 대상으로 하는 경우 다음 정의를 수정하십시오.
// 다른 플랫폼에 사용되는 해당 값의 최신 정보는 MSDN을 참조하십시오.
#ifndef WINVER				// Windows XP 이상에서만 기능을 사용할 수 있습니다.
#define WINVER 0x0501		// 다른 버전의 Windows에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_WINNT		// Windows XP 이상에서만 기능을 사용할 수 있습니다.                   
#define _WIN32_WINNT 0x0501	// 다른 버전의 Windows에 맞도록 적합한 값으로 변경해 주십시오.
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 이상에서만 기능을 사용할 수 있습니다.
#define _WIN32_WINDOWS 0x0410 // Windows Me 이상에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#ifndef _WIN32_IE			// IE 6.0 이상에서만 기능을 사용할 수 있습니다.
#define _WIN32_IE 0x0600	// 다른 버전의 IE에 맞도록 적합한 값으로 변경해 주십시오.
#endif

#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <ctype.h>
#include <iostream>

#include "base/jBase.h"
#include "header/uString_stl.h"
#include "Interface/xml/jIXml.h"
#include "Interface/xml/jIElement_op.h"
#include "header/jBoost.h"

using namespace nMech;
using namespace std;


inline void load_file_from_ifstream(std::tstring& s, std::tifstream& is)
{
	s.erase();
	if(is.bad()) return;
	//
	// attempt to grow string buffer to match file size,
	// this doesn't always work...
	s.reserve(is.rdbuf()->in_avail());
	TCHAR c;
	while(is.get(c))
	{
		// use logarithmic growth stategy, in case
		// in_avail (above) returned zero:
		if(s.capacity() == s.size())
			s.reserve(s.capacity() * 3);
		s.append(1, c);
	}
}

inline tcstr  read_file(tcstr  filename , std::tstring& sBuf)
{
	std::tifstream iF(filename);
	load_file_from_ifstream(sBuf, iF);
	iF.close();
	return sBuf.c_str();
}


// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

#define _xmlid_LIST(X)\
	X(Excel_Converter)\
	X(PARSE_1)\

_xmlid_LIST(jxDECL);




#define var_enum(func)\
	func(Excel_Converter,DB_VENDER,_T("MYSQL"), 0,"MSSQL , MYSQL , ORACLE")\
	func(Excel_Converter,IS_DROP_TABLE,true, 0,"is make drop table code for sql script ")\
	func(Excel_Converter,CSHAP_CSV_ENCODE,_T("EUC-KR"), 0,"[EUC-KR | utf-8] encoding type for cs code - csv file load. ")\
	func(Excel_Converter,PROTO_MEMBER_OPTION,_T("required"), 0,"optional or required")\
	func(Excel_Converter,PROTO_BUF_SERIALIZER_NAME_FOR_IPHONE,_T("BaseballClient_proto_Serializer"), 0,"proto-buf serializer name")\


	



var_enum(jCV_DECLARE);
