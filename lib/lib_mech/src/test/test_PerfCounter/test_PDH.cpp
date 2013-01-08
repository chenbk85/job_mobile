/* file : test_PDH.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-02 10:59:48
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"

std::vector<TCHAR> gszReturnPath;
COUNTERSTRUCT cs[COUNTER_MAX];
int cs_idx = 0; // COUNTERSTRUCT index
HQUERY hQuery;
PDH_BROWSE_DLG_CONFIG pdhconf;


static PDH_STATUS __stdcall pdh_callback(DWORD)
{
	if (pdhconf.CallBackStatus == PDH_MORE_DATA)
	{ 
		// 버퍼의 크기를 일정한 만큼 늘림
		gszReturnPath.resize(gszReturnPath.size() + BUFFER_INCREMENT_SIZE);
		pdhconf.szReturnPathBuffer = &gszReturnPath[0];
		pdhconf.cchReturnPathLength = gszReturnPath.size();
		return PDH_RETRY;
	}
	TCHAR *curPath;
	int len;
	PDH_COUNTER_INFO *ppci;
	DWORD pci_len;
	pci_len = 2048;
	ppci = (PDH_COUNTER_INFO*)VirtualAlloc(NULL, pci_len,
		MEM_COMMIT, PAGE_READWRITE);
	curPath = &gszReturnPath[0];
	while (1)
	{
		pci_len = 2048;
		len = lstrlen(curPath);
		if (len == 0) break;
		// 카운터 이름 출력
		_tprintf(_T("%s\n"), curPath);
		// 더 이상 카운터를 추가할 수 없으면 skip.
		if (cs_idx == COUNTER_MAX)
		{
			jt_printf(_T("No more counter available\n"));
			break;
		}
		// COUNTERSTRUCT에 카운터 이름을 저장
		lstrcpy(cs[cs_idx].pCounterName, curPath);
		// add counter
		if (PdhAddCounter(hQuery, (LPCTSTR)curPath,
			0, &(cs[cs_idx].hCounter)) != ERROR_SUCCESS)
			exit(1);
		// 카운터 정보 출력
		PdhGetCounterInfo(cs[cs_idx].hCounter, TRUE, &pci_len, ppci);
		jt_printf(_T("Explain: %s\n"), ppci->szExplainText);
		cs_idx++;
		curPath += (len + 1);
	}
	// free PDH_COUNTER_INFO buffer
	VirtualFree(ppci, 0, MEM_RELEASE);
	return ERROR_SUCCESS;
}

//#define PERF_DETAIL_NOVICE 100 // The uninformed can understand it
//#define PERF_DETAIL_ADVANCED 200 // For the advanced user
//#define PERF_DETAIL_EXPERT 300 // For the expert user
//#define PERF_DETAIL_WIZARD 400 // For the system designer
void pdh_init(HWND hwnd, TCHAR *buff, DWORD buffsize)
{
	// PDH_BROWSE_DLG_CONFIG 설정
	pdhconf.bIncludeInstanceIndex = FALSE;
	pdhconf.bSingleCounterPerAdd = TRUE;
	pdhconf.bSingleCounterPerDialog = TRUE;
	pdhconf.bLocalCountersOnly = TRUE;
	pdhconf.bWildCardInstances = FALSE;
	pdhconf.bHideDetailBox = FALSE;
	pdhconf.bInitializePath = FALSE;
	pdhconf.bReserved = NULL;
	pdhconf.hWndOwner = hwnd;
	pdhconf.szDataSource = NULL;
	pdhconf.szReturnPathBuffer = (LPTSTR)buff;
	pdhconf.cchReturnPathLength = buffsize;
	pdhconf.pCallBack = pdh_callback;
	pdhconf.dwCallBackArg = 0;
	pdhconf.dwDefaultDetailLevel = PERF_DETAIL_WIZARD;
	pdhconf.szDialogBoxCaption = (LPTSTR)_T("PDH Dialog Example");
}

int pdh_update(long *ret, int idx)
{
	PDH_FMT_COUNTERVALUE pdhFMTvalue;
	if (PdhCollectQueryData(hQuery) == ERROR_SUCCESS)
		if (PdhGetFormattedCounterValue(cs[idx].hCounter,
			PDH_FMT_LONG,
			NULL,
			&pdhFMTvalue) == ERROR_SUCCESS)
		{
			*ret = pdhFMTvalue.longValue;
			return TRUE;
		}
		return FALSE;
}

void main_PDH()
{
#if defined(UNICODE)
	std::wcout.imbue(std::locale("kor")); 
	_wsetlocale(LC_ALL, _T("korean"));

#endif

	//jMech_Init();

	int count = 0;
	LONG val;
	// Query open
	if (PdhOpenQuery(NULL, 0, &hQuery) != ERROR_SUCCESS) exit(1);
	// PDH_BROWSE_DLG_CONFIG 설정

	gszReturnPath.resize(1024);
	pdh_init(NULL, &gszReturnPath[0], gszReturnPath.size());
	// PDH Dialog Box 생성
	PdhBrowseCounters(&pdhconf);
	while (count++ < 20)
	{
		for (int i=0; i<cs_idx; i++)
		{
			// Counter 이름 출력
			jt_printf(_T("%s : "), cs[i].pCounterName);
			// Counter 값을 얻어내는데 에러가 있으면 while loop을 탈출
			if (pdh_update(&val, i) == FALSE)
			{
				count = 100;
				continue;
			}
			// 실제 Performance Counter 값 출력
			jt_printf(_T("%d\n"), val);
		}
		jt_printf(_T("\n"));
		Sleep(500);
	}
	// Query close
	PdhCloseQuery(hQuery);
	// 할당된 메모리 해제

	//jMech_Close();
}




