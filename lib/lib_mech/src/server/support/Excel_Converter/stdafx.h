// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

// �Ʒ� ������ �÷����� �켱�ϴ� �÷����� ������� �ϴ� ��� ���� ���Ǹ� �����Ͻʽÿ�.
// �ٸ� �÷����� ���Ǵ� �ش� ���� �ֽ� ������ MSDN�� �����Ͻʽÿ�.
#ifndef WINVER				// Windows XP �̻󿡼��� ����� ����� �� �ֽ��ϴ�.
#define WINVER 0x0501		// �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_WINNT		// Windows XP �̻󿡼��� ����� ����� �� �ֽ��ϴ�.                   
#define _WIN32_WINNT 0x0501	// �ٸ� ������ Windows�� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif						

#ifndef _WIN32_WINDOWS		// Windows 98 �̻󿡼��� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_WINDOWS 0x0410 // Windows Me �̻� �µ��� ������ ������ ������ �ֽʽÿ�.
#endif

#ifndef _WIN32_IE			// IE 6.0 �̻󿡼��� ����� ����� �� �ֽ��ϴ�.
#define _WIN32_IE 0x0600	// �ٸ� ������ IE�� �µ��� ������ ������ ������ �ֽʽÿ�.
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


// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.

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
