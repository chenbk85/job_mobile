/* file : excel_custom_code.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-03-23 17:25:17
comp.: rocworks.co.kr
title : 
desc : 

�� ����� excel csv�ڵ忡�� �ڵ����� ���� �ڵ� �����Ͽ� �����ؼ� ������ �ڵ��̴�.


*/

#include "stdafx.h"
#include "excel_custom_code.h"


//z:\src\base\Interface\net\excel_code_util.h���� struct Excel_PostLoader�� ������
namespace nMech{namespace nEXCEL{Excel_PostLoader g_Excel_PostLoader;}}




namespace nMech
{
	void FromString(SYSTEMTIME* tm,tstring& str)
	{
		vector<tstring> out;
		nString::jSplit(str, _T("_- :"), out);
		memset(tm,0,sizeof(*tm));
		if(out.size()>0) tm->wYear=jt_atoi(out[0].c_str());
		if(out.size()>1) tm->wMonth=jt_atoi(out[1].c_str());
		if(out.size()>2) tm->wDay=jt_atoi(out[2].c_str());
		if(out.size()>3) tm->wHour=jt_atoi(out[3].c_str());
		if(out.size()>4) tm->wMinute=jt_atoi(out[4].c_str());
		if(out.size()>5) tm->wSecond=jt_atoi(out[5].c_str());
	}

	namespace nEXCEL
	{
	}//namespace nEXCEL
}//nam
