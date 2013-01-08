/* file : PerfReg.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-03 20:55:20
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "PerfReg.h"


namespace nPerfReg
{
	enum 
	{
		eKOR,//012
		eENG,//009
		eMAX_CODE,
	};
	tcstr s_szCode[eMAX_CODE] = {jS(012),jS(009)};


	static BYTE							gEnd[2]									= {0, 0};
	static TCHAR							g_szReadDataString[MAX_STRING_LENGTH]			= {0,}; // 일단 400k정도 잡아준다.
	static TCHAR							g_szReadHelpString[MAX_STRING_LENGTH]		= {0,}; // 일단 400k정도 잡아준다.
	static DWORD							g_szReadDataString_length						= sizeof(g_szReadDataString);
	static DWORD							g_szReadHelpString_length					= sizeof(g_szReadHelpString);

	static BOOL _addString(LPTSTR source, LPCTSTR addItem, DWORD &length)
	{
		if (!source || !addItem)
			return FALSE;

		CopyMemory(source + length / sizeof(TCHAR) - 1, addItem, _tcslen(addItem) * sizeof(TCHAR));
		length += (DWORD) _tcslen(addItem) * sizeof(TCHAR);

		CopyMemory(source + length / sizeof(TCHAR), gEnd, sizeof(gEnd));
		length += sizeof(gEnd);

		return TRUE;
	}

	static BOOL _addDWORD(LPTSTR source, DWORD addItem, DWORD &length)
	{
		if (!source)
			return FALSE;

		TCHAR AddItem[16] = {0,};
		_sntprintf(AddItem, 16, _T("%d"), addItem);

		CopyMemory(source + length / sizeof(TCHAR) - 1, AddItem, _tcslen(AddItem) * sizeof(TCHAR));
		length += (DWORD) _tcslen(AddItem) * sizeof(TCHAR);

		CopyMemory(source + length / sizeof(TCHAR), gEnd, sizeof(gEnd));
		length += sizeof(gEnd);

		return TRUE;
	}

	static DWORD _getIndex(LPTSTR source,IN LPCTSTR counterName,DWORD max_len)
	{
		DWORD iLastCounter = load_LastCounter();
		tcstr PreviosString	= NULL;
		DWORD iLen12			= (DWORD) _tcslen(source) + 1;
		if (!_tcscmp(source, counterName))return 0;// 처음일리가 없다

		int i=0;
		while (iLen12)
		{
			++i;
			tcstr ch = source + iLen12;
			if (!_tcscmp(ch, counterName))
			{
				return _ttoi(PreviosString);
			}
			PreviosString	= ch;
			iLen12			+= (DWORD) _tcslen(ch) + 1;
			if(iLen12 >=max_len)
			{
				break;
			}
		}
		return 0;
	}

	static BOOL _getName(LPTSTR source, DWORD index, OUT tname32_t counterName)
	{
		tcstr PreviosString	= NULL;
		DWORD	iLen12			= (DWORD) _tcslen(source) + 1;
		TCHAR	szIndex[16]		= {0,};

		_itot(index, szIndex, 10);

		// 처음일리가 없다
		if (!_tcscmp(source, szIndex))
			return FALSE;

		while (iLen12)
		{
			tcstr ch = source + iLen12;
			if (!_tcscmp(ch, szIndex))
			{
				iLen12		+= (DWORD) _tcslen(ch) + 1;
				ch = source + iLen12;
				jt_strcpy_s(counterName,32, ch);

				return TRUE;
			}

			PreviosString	= ch;
			iLen12			+= (DWORD) _tcslen(ch) + 1;
		}

		return FALSE;
	}

	BOOL AddString_Help(LPCTSTR data)					{return  _addString(g_szReadHelpString, data, g_szReadHelpString_length);	}
	BOOL AddDWORD_Help(DWORD addItem)	{return  _addDWORD(g_szReadHelpString, addItem, g_szReadHelpString_length);	}
	DWORD GetIndex_Help(LPCTSTR counterName){return _getIndex(g_szReadHelpString,counterName,g_szReadHelpString_length);}
	BOOL GetName_Help(DWORD index, OUT tname32_t counterName){return _getName(g_szReadHelpString, index,counterName);}

	BOOL AddString_Data(LPCTSTR data)					{return  _addString(g_szReadDataString, data, g_szReadDataString_length);	}
	BOOL AddDWORD_Data(DWORD addItem)	{return  _addDWORD(g_szReadDataString, addItem, g_szReadDataString_length);	}
	DWORD GetIndex_Data(LPCTSTR counterName){return _getIndex(g_szReadDataString,counterName,g_szReadDataString_length);}
	BOOL GetName_Data(DWORD index, OUT tname32_t counterName){return _getName(g_szReadDataString, index,counterName);}


	tcstr get_MyServiceURL(fname_t buf)
	{
		fname_t szURL;
		jt_sprintf(buf, szMY_SERVICE_URL_FMT , get_my_service_url(szURL));
		return buf;
	}

	DWORD load_LastCounter()
	{
		DWORD i=0;
		CRegistry Registry;
		Registry.Open(HKEY_LOCAL_MACHINE, szPERF_LIB );
		Registry.GetValue(_T("Last Counter"), &i);
		Registry.Close();
		return i;
	}

	void save_LastCounter(DWORD iLast)
	{
		CRegistry Registry;
		Registry.Open(HKEY_LOCAL_MACHINE, szPERF_LIB);
		Registry.SetValue(_T("Last Counter"), iLast);
		Registry.SetValue(_T("Last Help"), iLast + 1);
		Registry.Close();
	}

	void save_Counter_Contents()
	{
		CRegistry Registry;
		Registry.Open(HKEY_LOCAL_MACHINE, szPERF_LIB_KOR );
		Registry.SetValueForMultiSz(_T("Counter"), g_szReadDataString, g_szReadDataString_length);
		Registry.SetValueForMultiSz(_T("Help"), g_szReadHelpString, g_szReadHelpString_length);
		Registry.Close();
	}

	void load_Counter_Contents()
	{
		CRegistry Registry;
		Registry.Open(HKEY_LOCAL_MACHINE, szPERF_LIB_KOR );
		Registry.GetValue(_T("Counter"), g_szReadDataString, &g_szReadDataString_length);
		Registry.GetValue(_T("Help"), g_szReadHelpString, &g_szReadHelpString_length);
		Registry.Close();
	}

	bool load_My_ObjectList()
	{
		memset(g_szMyObjectList, 0 , sizeof(g_szMyObjectList));
		fname_t szMyServiceURL;
		CRegistry Registry;
		if (!Registry.Open(HKEY_LOCAL_MACHINE,get_MyServiceURL(szMyServiceURL) ))
			return false;

		DWORD MaxStringLength = MAX_STRING_LENGTH;
		Registry.GetValue(_T("Object List"), g_szMyObjectList, &MaxStringLength);
		Registry.Close();
		return true;
	}

	void save_My_ObjectList()
	{
		CRegistry Registry;
		// 3. Performance Provider쪽 추가
		fname_t szMyServiceURL;
		Registry.Open(HKEY_LOCAL_MACHINE, nPerfReg::get_MyServiceURL(szMyServiceURL) );
		Registry.SetValue(_T("Object List"), g_szMyObjectList);
		Registry.Close();
	}

}//nPerfReg
