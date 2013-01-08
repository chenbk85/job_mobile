// jPerfCounter.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#include "jPerfCounter.h"
#include "PerfReg.h"


/*
#undef STATIC_USING
#define STATIC_USING 
*/

#if 0

#pragma data_seg("SHARED")

static BYTE testVal;

#pragma data_seg()
#pragma comment(linker, "/SECTION:SHARED,RWS")

#endif

TCHAR g_szMyObjectList[MAX_STRING_LENGTH];

nMech::nUtil::jMemoryMap<jPerfCounterNode> m_smMyCounterObject;
jLIST_TYPEDEF_vector(jPerfCounterNode*, m_vecMyCountObject);

jMutex								g_jMutex;
PERF_OBJECT_TYPE					g_header_PERF_OBJECT_TYPE;
jPerfCounter g_pjPerfCounter;


jPerfCounter::jPerfCounter()
{
	bool isCreate = m_smMyCounterObject.Init(_T("asdfasdf"), 100);
	if(!isCreate)
	{
		for(size_t i=0 ; i < m_smMyCounterObject.size() ; ++i)
		{
			if(m_smMyCounterObject.at(i)->szIndex!=0)
				m_vecMyCountObject.push_back(m_smMyCounterObject.at(i));
		}
	}
}

void jPerfCounter::update_header_PERF_OBJECT_TYPE()
{
	int currCountNum=m_vecMyCountObject.size();
	PERF_OBJECT_TYPE& h = g_header_PERF_OBJECT_TYPE;
	h.DefinitionLength		= (DWORD) currCountNum * sizeof(PERF_COUNTER_DEFINITION) 
							+ sizeof(PERF_OBJECT_TYPE);

	h.TotalByteLength	= h.DefinitionLength
						+ sizeof(DWORD) * currCountNum 
						+ sizeof(DWORD);

	h.NumCounters		= (DWORD) currCountNum;
}


jPerfCounterNode* jPerfCounter::get_FreeCounterNode()
{
	for( size_t i = 0; i < m_smMyCounterObject.size() ;++i)
	{
		if(m_smMyCounterObject.at(i)->szIndex==0)
			return m_smMyCounterObject.at(i);
	}
	return 0;
}

jPerfCounterNode* jPerfCounter::find_MyCounter_FromSM(DWORD index)
{
	// 기존의 카운터중에 같은 이름이 있는지 확인한다.
	for (size_t i=0;i<m_smMyCounterObject.size();i++)
	{
		if (m_smMyCounterObject.at(i)->szIndex== index)
		{
			return m_smMyCounterObject.at(i);
		}
	}
	return 0;
}

jPerfCounterNode* jPerfCounter::find_MyCounter(DWORD idx)
{
	// 기존의 카운터중에 같은 이름이 있는지 확인한다.
	for (DWORD i=0;i<m_vecMyCountObject.size();i++)
	{
		if (m_vecMyCountObject[i]->szIndex==idx)
		{
			return m_vecMyCountObject[i];
		}
	}
	return 0;
}

jPerfCounterNode* jPerfCounter::find_MyCounter(tcstr szName)
{
	// 기존의 카운터중에 같은 이름이 있는지 확인한다.
	for (DWORD i=0;i<m_vecMyCountObject.size();i++)
	{
		if (!_tcscmp(m_vecMyCountObject[i]->Name, szName))
		{
			return m_vecMyCountObject[i];
		}
	}
	return 0;
}

bool jPerfCounter::check_Exist_in_MyCounter(tcstr szName)
{
	if(find_MyCounter(szName)) return true;

	nPerfReg::load_Counter_Contents();
	DWORD index = nPerfReg::GetIndex_Data(szName);
	if(index)
	{
		return true;
	}
	return false;
}

void jPerfCounter::update_MyServiceURL( tcstr szDLLPath)
{
	CRegistry Registry;
	fname_t szMyServiceURL;
	Registry.Open(HKEY_LOCAL_MACHINE, nPerfReg::get_MyServiceURL(szMyServiceURL));
	Registry.SetValue(_T("Library"), szDLLPath);
	Registry.Close();
}
void jPerfCounter::create_MyServiceURL( tcstr szServiceName)
{
	CRegistry Registry;

	fname_t szMyServiceURL;
	nPerfReg::get_MyServiceURL(szMyServiceURL);

	Registry.CreateKey(HKEY_LOCAL_MACHINE, szMyServiceURL);
	
	DWORD iLastIndex = nPerfReg::load_LastCounter();
	iLastIndex+=2;
	
	fname_t buf;
	jt_sprintf(buf, _T("%d"), iLastIndex);
	Registry.SetValue(_T("Object List"), buf);

	Registry.SetValue(_T("Open"), _T("jPerf_Open"));
	Registry.SetValue(_T("Close"), _T("jPerf_Close"));
	Registry.SetValue(_T("Collect"), _T("jPerf_Collect"));
	Registry.SetValue(_T("Library"), g_DLLPath.buffer);

	Registry.Close();

	fname_t szURL;
	nPerfReg::AddDWORD_Data( iLastIndex );
	nPerfReg::AddString_Data( get_my_service_url(szURL));

	fname_t szHelp;
	jt_sprintf(szHelp, _T("%s Help"),szURL);
	nPerfReg::AddDWORD_Help( iLastIndex + 1);
	nPerfReg::AddString_Help( szHelp);

	// Perflib의 Last값 업데이트
	nPerfReg::save_LastCounter(iLastIndex);
	nPerfReg::save_Counter_Contents();
}

void jPerfCounter::Init_PerfCounterNode(DWORD idx)
{
	jPerfCounterNode* pCN = find_MyCounter_FromSM(idx);
	if(pCN)
	{
		if(!find_MyCounter(idx))
		{
			m_vecMyCountObject.push_back(pCN);
		}
	}
	else
	{
		jPerfCounterNode *pc= get_FreeCounterNode();
		if(!pc)
		{
			//jTODO eventlog로 남길것.
			return;
		}

		pc->szIndex						= idx;
		pc->Value						= 0;

		pc->Data.ByteLength				= sizeof(pc->Data);
		pc->Data.CounterNameTitleIndex	= idx;
		pc->Data.CounterNameTitle		= NULL;
		pc->Data.CounterHelpTitleIndex	= idx + 1;
		pc->Data.CounterHelpTitle		= NULL;
		pc->Data.DefaultScale			= 0;
		pc->Data.DetailLevel				= PERF_DETAIL_NOVICE;
		pc->Data.CounterType				= PERF_COUNTER_RAWCOUNT;
		pc->Data.CounterSize				= sizeof(DWORD);
		pc->Data.CounterOffset			= sizeof(DWORD);

		nPerfReg::GetName_Data(idx, pc->Name);

		m_vecMyCountObject.push_back(pc);
	}
}


BOOL jPerfCounter::Begin(tcstr szServiceName)
{
	jAUTO_LOCK_MU(g_jMutex);

	PERF_OBJECT_TYPE &h = g_header_PERF_OBJECT_TYPE;
	ZeroMemory(&h, sizeof(PERF_OBJECT_TYPE));


	nPerfReg::load_Counter_Contents();

	if(!nPerfReg::load_My_ObjectList())
	{
		create_MyServiceURL(szServiceName);
		assert(nPerfReg::load_My_ObjectList());
	}
	else
	{
		update_MyServiceURL(g_DLLPath.buffer);
	}

	LPTSTR Token = _tcstok(g_szMyObjectList, szTOKEN);

	DWORD FirstIndex				= _ttoi(Token);


	update_header_PERF_OBJECT_TYPE();

	h.HeaderLength			= sizeof(PERF_OBJECT_TYPE);
	h.ObjectNameTitleIndex	= FirstIndex;
	h.ObjectNameTitle			= NULL;
	h.ObjectHelpTitleIndex	= FirstIndex + 1;
	h.ObjectHelpTitle			= NULL;
	h.DetailLevel				= PERF_DETAIL_NOVICE;
	h.DefaultCounter			= 0;
	h.NumInstances			= PERF_NO_INSTANCES;
	h.CodePage				= 0;

	// 처음은 무시해 준다.
	Token = _tcstok(NULL, szTOKEN);

	while (Token)
	{
		DWORD idx = _ttoi(Token);
		Token = _tcstok(NULL, szTOKEN);
		Init_PerfCounterNode(idx);
	}

	update_header_PERF_OBJECT_TYPE();

	return TRUE;
}

BOOL jPerfCounter::End(VOID)
{
	return TRUE;
}


BOOL jPerfCounter::AddCounter(LPCTSTR name,tcstr szHelp)
{

	if (!name)
	{
		return FALSE;
	}
	jAUTO_LOCK_MU(g_jMutex);

	if(check_Exist_in_MyCounter(name)) 
		return FALSE;

	jPerfCounterNode *pc = get_FreeCounterNode();
	if(!pc)
		return FALSE;

	// Last szIndex 한번 확인
	DWORD iLastIndex = nPerfReg::load_LastCounter();
	iLastIndex +=2;

	nPerfReg::AddDWORD_Data( iLastIndex);
	nPerfReg::AddString_Data( name);

	nPerfReg::AddDWORD_Help( iLastIndex + 1);
	nPerfReg::AddString_Help( szHelp);

	nPerfReg::load_My_ObjectList();
	_sntprintf(g_szMyObjectList, MAX_STRING_LENGTH, _T("%s %d"), g_szMyObjectList, iLastIndex );

	nPerfReg::save_Counter_Contents();

	// 2. Perflib쪽 LastIndex Update
	nPerfReg::save_LastCounter(iLastIndex );

	nPerfReg::save_My_ObjectList();

	// 4. Vector 추가
	pc->szIndex						= iLastIndex;
	pc->Value						= 0;

	pc->Data.ByteLength				= sizeof(pc->Data);
	pc->Data.CounterNameTitleIndex	= iLastIndex;
	pc->Data.CounterNameTitle		= NULL;
	pc->Data.CounterHelpTitleIndex	= iLastIndex + 1;
	pc->Data.CounterHelpTitle		= NULL;
	pc->Data.DefaultScale			= 0;
	pc->Data.DetailLevel				= PERF_DETAIL_NOVICE;
	pc->Data.CounterType				= PERF_COUNTER_RAWCOUNT;
	pc->Data.CounterSize				= sizeof(DWORD);
	pc->Data.CounterOffset			= sizeof(DWORD);

	nPerfReg::GetName_Data(iLastIndex, pc->Name);
	assert(jt_strcmp(pc->Name,name) ==0);
	m_vecMyCountObject.push_back(pc);

	// 5. Header 변경
	update_header_PERF_OBJECT_TYPE();

	return TRUE;
}

BOOL jPerfCounter::UpdateCounter(LPCTSTR name, DWORD value)
{
	jAUTO_LOCK_MU(g_jMutex);

	jPerfCounterNode* pCN = find_MyCounter(name);
	if(!pCN) return false;
	pCN->Value = value;
	return FALSE;
}
