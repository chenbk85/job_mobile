/* file : jPerfCounter.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-02 10:09:40
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jPerfCounter_header__
#define __jPerfCounter_header__
#pragma once


#ifdef JPERFCOUNTER_EXPORTS
#define JPERFCOUNTER_API __declspec(dllexport)
#else
#define JPERFCOUNTER_API __declspec(dllimport)
#endif




#define		MAX_STRING_LENGTH		409600
#define		szPERF_LIB			_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib")
#define		szPERF_LIB_KOR		_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\012")
#define		szPERF_LIB_ENG		_T("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\Perflib\\009")
#define		szTOKEN				_T(" ")
#define		szMY_SERVICE_URL_FMT _T("SYSTEM\\CurrentControlSet\\Services\\%s\\Performance") 



typedef struct _PERFORMANCE_COUNTER
{
	DWORD					szIndex;
	TCHAR					Name[32];
	DWORD					Value;
	PERF_COUNTER_DEFINITION	Data;
} jPerfCounterNode;

struct jPerfCounter :public nLOG::jIPerfCounter
{
	virtual BOOL Begin(tcstr szServiceName);
	virtual BOOL End(VOID);
	virtual BOOL AddCounter(LPCTSTR name,tcstr szHelp);
	virtual BOOL UpdateCounter(LPCTSTR name, DWORD value);

	void create_MyServiceURL( LPCTSTR dllPath );
	void update_MyServiceURL( tcstr szDLLPath);
	void update_header_PERF_OBJECT_TYPE();

	jPerfCounterNode* find_MyCounter(tcstr szName);
	jPerfCounterNode* find_MyCounter(DWORD idx);
	bool check_Exist_in_MyCounter(tcstr szName);

	jPerfCounterNode* find_MyCounter_FromSM(DWORD index);
	jPerfCounterNode* get_FreeCounterNode();

	void Init_PerfCounterNode(DWORD idx);

	jPerfCounter();

};

extern jPerfCounter g_pjPerfCounter;
extern nMech::nUtil::jMemoryMap<jPerfCounterNode> m_smMyCounterObject;
extern std::vector<jPerfCounterNode*>	m_vecMyCountObject;

extern PERF_OBJECT_TYPE					g_header_PERF_OBJECT_TYPE;
extern jMutex							g_jMutex;
extern nFileSystem::jFileName					g_DLLPath;

extern TCHAR g_szMyObjectList[MAX_STRING_LENGTH];

#endif // __jPerfCounter_header__
