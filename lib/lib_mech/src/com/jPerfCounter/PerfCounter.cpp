/* file : PerfCounter.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-06 13:16:48
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"

#define MAX_STRING_LENGTH		409600

struct PERFORMANCE_COUNTER
{
	DWORD					Index;
	TCHAR					Name[32];
	DWORD					Value;
	PERF_COUNTER_DEFINITION	Data;
} ;

static std::vector<PERFORMANCE_COUNTER> gCounterVector;
static nUtil::jCriticalSection					gSync;
#define AUTOLOCK1234() 

static PERF_OBJECT_TYPE					gHeader;

static TCHAR							gReadString[MAX_STRING_LENGTH]			= {0,}; // �ϴ� 400k���� ����ش�.
static DWORD							gReadStringLength						= sizeof(gReadString);

static TCHAR							gReadHelpString[MAX_STRING_LENGTH]		= {0,}; // �ϴ� 400k���� ����ش�.
static DWORD							gReadHelpStringLength					= sizeof(gReadHelpString);

static TCHAR							gObjectListString[MAX_STRING_LENGTH]	= {0,};

static DWORD							gLastIndex								= 0;

static BYTE								gEnd[2]									= {0, 0};

BOOL AddString(LPTSTR source, LPTSTR addItem, DWORD &length)
{
	if (!source || !addItem)
		return FALSE;

	CopyMemory(source + length / sizeof(TCHAR) - 1, addItem, _tcslen(addItem) * sizeof(TCHAR));
	length += (DWORD) _tcslen(addItem) * sizeof(TCHAR);

	CopyMemory(source + length / sizeof(TCHAR), gEnd, sizeof(gEnd));
	length += sizeof(gEnd);

	return TRUE;
}

BOOL AddDWORD(LPTSTR source, DWORD addItem, DWORD &length)
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

BOOL GetIndex(LPTSTR source, LPTSTR counterName, DWORD &index)
{
	TCHAR *PreviosString	= NULL;
	DWORD Length			= (DWORD) _tcslen(source) + 1;

	// ó���ϸ��� ����
	if (!_tcscmp(source, counterName))
		return FALSE;

	while (Length)
	{
		if (!_tcscmp(source + Length, counterName))
		{
			index = _ttoi(PreviosString);

			return TRUE;
		}

		PreviosString	= source + Length;
		Length			+= (DWORD) _tcslen(source + Length) + 1;
	}

	return FALSE;
}

BOOL GetName(LPTSTR source, DWORD index, LPTSTR counterName)
{
	TCHAR	*PreviosString	= NULL;
	DWORD	Length			= (DWORD) _tcslen(source) + 1;
	TCHAR	Index[16]		= {0,};

	_itot(index, Index, 10);

	// ó���ϸ��� ����
	if (!_tcscmp(source, Index))
		return FALSE;

	while (Length)
	{
		if (!_tcscmp(source + Length, Index))
		{
			Length		+= (DWORD) _tcslen(source + Length) + 1;

			_tcscpy(counterName, source + Length);

			return TRUE;
		}

		PreviosString	= source + Length;
		Length			+= (DWORD) _tcslen(source + Length) + 1;
	}

	return FALSE;
}

	BOOL Begin(LPTSTR dllPath)
	{
		AUTOLOCK1234();
		if (!dllPath)
		{
			return FALSE;
		}
		dllPath = g_szDLLPath;

		ZeroMemory(&gHeader, sizeof(gHeader));

		CRegistry Registry;

		Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\012"));
		Registry.GetValue(_T("Counter"), gReadString, &gReadStringLength);
		Registry.GetValue(_T("Help"), gReadHelpString, &gReadHelpStringLength);
		Registry.Close();

		Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"));
		Registry.GetValue(_T("Last Counter"), &gLastIndex);
		Registry.Close();

		if (!Registry.Open(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services\\Performance Provider\\Performance")))
		{
			Registry.CreateKey(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services\\Performance Provider\\Performance"));

			_sntprintf(gObjectListString, MAX_STRING_LENGTH, _T("%d"), gLastIndex + 2);
			Registry.SetValue(_T("Object List"), gObjectListString);

			Registry.SetValue(_T("Open"), _T("PP_Open"));
			Registry.SetValue(_T("Close"), _T("PP_Close"));
			Registry.SetValue(_T("Collect"), _T("PP_Collect"));
			Registry.SetValue(_T("Library"), dllPath);

			Registry.Close();

			// Perflib�� Last�� ������Ʈ
			Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"));
			Registry.SetValue(_T("Last Counter"), gLastIndex + 2);
			Registry.SetValue(_T("Last Help"), gLastIndex + 3);
			Registry.Close();

			// gReadString�� ������Ʈ �� �Ŀ� ������Ʈ���� �� �ش�.
			//_sntprintf(gReadString + gReadStringLength - 1, MAX_STRING_LENGTH - gReadStringLength + 1, _T("%d\0%s\0\0"), gLastIndex + 2, _T("Performance Provider"));
			//_sntprintf(gReadHelpString, MAX_STRING_LENGTH, _T("%s\n%d\n%s"), gReadHelpString, gLastIndex + 3, _T("Performance Provider Help"));
			AddDWORD(gReadString, gLastIndex + 2, gReadStringLength);
			AddString(gReadString, _T("Performance Provider"), gReadStringLength);

			AddDWORD(gReadHelpString, gLastIndex + 3, gReadHelpStringLength);
			AddString(gReadHelpString, _T("Performance Provider Help"), gReadHelpStringLength);

			Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\012"));
			Registry.SetValueForMultiSz(_T("Counter"), gReadString, gReadStringLength);
			Registry.SetValueForMultiSz(_T("Help"), gReadHelpString, gReadHelpStringLength);
			Registry.Close();

			gLastIndex	= gLastIndex + 2;
		}
		else
		{
			DWORD MaxStringLength = MAX_STRING_LENGTH;

			Registry.GetValue(_T("Object List"), gObjectListString, &MaxStringLength);

			Registry.Close();

			// ������ ī���Ϳ� ó�� ī���͸� �˾Ƽ� ������ ���鼭 �� ������ Vector�� �Է�
			//Registry.GetValue(_T("First Counter"), &gFirstIndex);
			//Registry.GetValue(_T("Last Counter"), &gLastIndex);
		}

		TCHAR	Seperator[]				= _T(" ");
		LPTSTR	Token					= NULL;

		Token = _tcstok(gObjectListString, Seperator);

		DWORD FirstIndex				= _ttoi(Token);

		gHeader.TotalByteLength			= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader) + sizeof(DWORD) * gCounterVector.size() + sizeof(DWORD);
		gHeader.DefinitionLength		= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader);
		gHeader.HeaderLength			= sizeof(gHeader);
		gHeader.ObjectNameTitleIndex	= FirstIndex;
		gHeader.ObjectNameTitle			= NULL;
		gHeader.ObjectHelpTitleIndex	= FirstIndex + 1;
		gHeader.ObjectHelpTitle			= NULL;
		gHeader.DetailLevel				= PERF_DETAIL_NOVICE;
		gHeader.NumCounters				= (DWORD) gCounterVector.size();
		gHeader.DefaultCounter			= 0;
		gHeader.NumInstances			= PERF_NO_INSTANCES;
		gHeader.CodePage				= 0;

		ZeroMemory(&gHeader.PerfTime, sizeof(gHeader.PerfTime));
		ZeroMemory(&gHeader.PerfFreq, sizeof(gHeader.PerfFreq));

		// ó���� ������ �ش�.
		Token = _tcstok(NULL, Seperator);

		while (Token)
		{
			DWORD Index = _ttoi(Token);

			PERFORMANCE_COUNTER pc;

			ZeroMemory(&pc, sizeof(pc));

			pc.Index						= Index;
			pc.Value						= 0;

			pc.Data.ByteLength				= sizeof(pc.Data);
			pc.Data.CounterNameTitleIndex	= Index;
			pc.Data.CounterNameTitle		= NULL;
			pc.Data.CounterHelpTitleIndex	= Index + 1;
			pc.Data.CounterHelpTitle		= NULL;
			pc.Data.DefaultScale			= 0;
			pc.Data.DetailLevel				= PERF_DETAIL_NOVICE;
			pc.Data.CounterType				= PERF_COUNTER_RAWCOUNT;
			pc.Data.CounterSize				= sizeof(DWORD);
			pc.Data.CounterOffset			= sizeof(DWORD);

			GetName(gReadString, Index, pc.Name);

			gCounterVector.push_back(pc);

			Token = _tcstok(NULL, Seperator);
		}

		gHeader.TotalByteLength			= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader) + sizeof(DWORD) * gCounterVector.size() + sizeof(DWORD);
		gHeader.DefinitionLength		= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader);
		gHeader.NumCounters				= (DWORD) gCounterVector.size();

		return TRUE;
	}


	BOOL AddCounter(LPTSTR name)
	{
		AUTOLOCK1234();

		if (!name)
		{
			return FALSE;
		}

		// ������ ī�����߿� ���� �̸��� �ִ��� Ȯ���Ѵ�.
		for (DWORD i=0;i<gCounterVector.size();i++)
		{
			if (!_tcscmp(gCounterVector[i].Name, name))
			{
				

				return FALSE;
			}
		}

		// Ȥ�ó� String�� �ִ��� Ȯ���� �ش�.
		//if (_tcsstr(gReadString, name))
		//{
		//	

		//	return FALSE;
		//}

		// Last Index �ѹ� Ȯ��
		CRegistry Registry;
		Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"));
		Registry.GetValue(_T("Last Counter"), &gLastIndex);
		Registry.Close();

		// 1. ��Ʈ���ʿ� �־��ְ�
		//_sntprintf(gReadString, MAX_STRING_LENGTH, _T("%s\n%d\n%s"), gReadString, gLastIndex + 2, name);
		//_sntprintf(gReadHelpString, MAX_STRING_LENGTH, _T("%s\n%d\n%s Help"), gReadHelpString, gLastIndex + 3, name);

		AddDWORD(gReadString, gLastIndex + 2, gReadStringLength);
		AddString(gReadString, name, gReadStringLength);

		AddDWORD(gReadHelpString, gLastIndex + 3, gReadHelpStringLength);
		AddString(gReadHelpString, name, gReadHelpStringLength);

		_sntprintf(gObjectListString, MAX_STRING_LENGTH, _T("%s %d"), gObjectListString, gLastIndex + 2);

		Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\012"));
		Registry.SetValueForMultiSz(_T("Counter"), gReadString, gReadStringLength);
		Registry.SetValueForMultiSz(_T("Help"), gReadHelpString, gReadHelpStringLength);
		Registry.Close();

		// 2. Perflib�� LastIndex Update
		Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"));
		Registry.SetValue(_T("Last Counter"), gLastIndex + 2);
		Registry.SetValue(_T("Last Help"), gLastIndex + 3);
		Registry.Close();

		// 3. Performance Provider�� �߰�
		Registry.Open(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services\\Performance Provider\\Performance"));
		Registry.SetValue(_T("Object List"), gObjectListString);
		Registry.Close();

		// 4. Vector �߰�
		PERFORMANCE_COUNTER pc;

		pc.Index						= gLastIndex + 2;
		pc.Value						= 0;

		pc.Data.ByteLength				= sizeof(pc.Data);
		pc.Data.CounterNameTitleIndex	= gLastIndex + 2;
		pc.Data.CounterNameTitle		= NULL;
		pc.Data.CounterHelpTitleIndex	= gLastIndex + 3;
		pc.Data.CounterHelpTitle		= NULL;
		pc.Data.DefaultScale			= 0;
		pc.Data.DetailLevel				= PERF_DETAIL_NOVICE;
		pc.Data.CounterType				= PERF_COUNTER_RAWCOUNT;
		pc.Data.CounterSize				= sizeof(DWORD);
		pc.Data.CounterOffset			= sizeof(DWORD);

		GetName(gReadString, gLastIndex + 2, pc.Name);

		gCounterVector.push_back(pc);

		// 5. Header ����
		gHeader.TotalByteLength			= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader) + sizeof(DWORD) * gCounterVector.size() + sizeof(DWORD);
		gHeader.DefinitionLength		= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader);
		gHeader.NumCounters				= (DWORD) gCounterVector.size();

		gLastIndex = gLastIndex + 2;

		

		return TRUE;
	}


	BOOL UpdateCounter(LPTSTR name, DWORD value)
	{
		AUTOLOCK1234();

		for (DWORD i=0;i<gCounterVector.size();i++)
		{
			if (!_tcscmp(gCounterVector[i].Name, name))
			{
				gCounterVector[i].Value = value;

				

				return TRUE;
			}
		}

		

		return FALSE;
	}


extern "C"
{

	DWORD __declspec(dllexport) WINAPI PP_Open(LPWSTR lpDevNames)
	{
		AUTOLOCK1234();

		ZeroMemory(&gHeader, sizeof(gHeader));

		CRegistry Registry;

		Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\012"));
		Registry.GetValue(_T("Counter"), gReadString, &gReadStringLength);
		Registry.GetValue(_T("Help"), gReadHelpString, &gReadHelpStringLength);
		Registry.Close();

		Registry.Open(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib"));
		Registry.GetValue(_T("Last Counter"), &gLastIndex);
		Registry.Close();

		if (Registry.Open(HKEY_LOCAL_MACHINE, _T("SYSTEM\\CurrentControlSet\\Services\\Performance Provider\\Performance")))
		{
			DWORD MaxStringLength = MAX_STRING_LENGTH;

			Registry.GetValue(_T("Object List"), gObjectListString, &MaxStringLength);

			Registry.Close();

			TCHAR	Seperator[]				= _T(" ");
			LPTSTR	Token					= NULL;

			Token = _tcstok(gObjectListString, Seperator);

			DWORD FirstIndex				= _ttoi(Token);

			gHeader.TotalByteLength			= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader) + sizeof(DWORD) * gCounterVector.size() + sizeof(DWORD);
			gHeader.DefinitionLength		= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader);
			gHeader.HeaderLength			= sizeof(gHeader);
			gHeader.ObjectNameTitleIndex	= FirstIndex;
			gHeader.ObjectNameTitle			= NULL;
			gHeader.ObjectHelpTitleIndex	= FirstIndex + 1;
			gHeader.ObjectHelpTitle			= NULL;
			gHeader.DetailLevel				= PERF_DETAIL_NOVICE;
			gHeader.NumCounters				= (DWORD) gCounterVector.size();
			gHeader.DefaultCounter			= 0;
			gHeader.NumInstances			= PERF_NO_INSTANCES;
			gHeader.CodePage				= 0;

			ZeroMemory(&gHeader.PerfTime, sizeof(gHeader.PerfTime));
			ZeroMemory(&gHeader.PerfFreq, sizeof(gHeader.PerfFreq));

			// ó���� ������ �ش�.
			Token = _tcstok(NULL, Seperator);

			while (Token)
			{
				DWORD Index = _ttoi(Token);

				PERFORMANCE_COUNTER pc;

				ZeroMemory(&pc, sizeof(pc));

				pc.Index						= Index;
				pc.Value						= 0;

				pc.Data.ByteLength				= sizeof(pc.Data);
				pc.Data.CounterNameTitleIndex	= Index;
				pc.Data.CounterNameTitle		= NULL;
				pc.Data.CounterHelpTitleIndex	= Index + 1;
				pc.Data.CounterHelpTitle		= NULL;
				pc.Data.DefaultScale			= 0;
				pc.Data.DetailLevel				= PERF_DETAIL_NOVICE;
				pc.Data.CounterType				= PERF_COUNTER_RAWCOUNT;
				pc.Data.CounterSize				= sizeof(DWORD);
				pc.Data.CounterOffset			= sizeof(DWORD);

				GetName(gReadString, Index, pc.Name);

				gCounterVector.push_back(pc);

				Token = _tcstok(NULL, Seperator);
			}

			gHeader.TotalByteLength			= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader) + sizeof(DWORD) * gCounterVector.size() + sizeof(DWORD);
			gHeader.DefinitionLength		= (DWORD) gCounterVector.size() * sizeof(PERF_COUNTER_DEFINITION) + sizeof(gHeader);
			gHeader.NumCounters				= (DWORD) gCounterVector.size();
		}

		

		return(ERROR_SUCCESS);
	}

	DWORD __declspec(dllexport) WINAPI PP_Close(VOID)
	{
		return(ERROR_SUCCESS);
	}

	DWORD __declspec(dllexport) WINAPI PP_Collect(LPWSTR lpValueName, 
		LPVOID* lppData, 
		LPDWORD lpcbTotalBytes, 
		LPDWORD lpNumObjectTypes)
	{
		AUTOLOCK1234();
		*lpcbTotalBytes		= gHeader.TotalByteLength;
		*lpNumObjectTypes	= (DWORD) gCounterVector.size() + 1;

		PBYTE *Data			= (PBYTE*) lppData;

		CopyMemory(*Data, &gHeader, sizeof(gHeader));
		*Data += sizeof(gHeader);

		for (DWORD i=0;i<gCounterVector.size();i++)
		{
			CopyMemory(*Data, &gCounterVector[i].Data, sizeof(gCounterVector[i].Data));
			*Data += sizeof(gCounterVector[i].Data);
		}

		DWORD ValueLength = (DWORD) (sizeof(DWORD) * gCounterVector.size());
		CopyMemory(*Data, &ValueLength, sizeof(DWORD));
		*Data += sizeof(DWORD);

		for (DWORD i=0;i<gCounterVector.size();i++)
		{
			CopyMemory(*Data, &gCounterVector[i].Value, sizeof(DWORD));
			*Data += sizeof(DWORD);
		}

		

		return(ERROR_SUCCESS);
	}
}

#pragma comment(linker, "/export:PP_Open=_PP_Open@4")
#pragma comment(linker, "/export:PP_Close=_PP_Close@0")
#pragma comment(linker, "/export:PP_Collect=_PP_Collect@16")
