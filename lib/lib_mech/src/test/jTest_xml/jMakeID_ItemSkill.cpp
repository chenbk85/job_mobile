/* file : jMakeID_ItemSkill.cpp
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2006-01-11 09:46:49
title : 
desc : 

*/

#include "stdafx.h"


bool g_isSave =false;
struct _jxGenItemID
{
	jIE* m_pE;
	_jxGenItemID(jIE* pe): m_pE(pe){ 	}
	void operator () (jIE* it)
	{
		if( it->GetType() == jIVar::ETelement) return;
		if( it->GetType() != jIVar::EDcstr) return;
		jIE* peFind = m_pE->Find(it->GetTagID());
		if(peFind) return;
		int newID = m_pE->size();
		jIE* peNew = m_pE->Persist(it->GetTagID() , jIVar::EDint);
		peNew->GetVar()->intValue() = newID;
		printf("new ID : %s _ %s = %d\n", it->GetParent()->GetTagName(), it->GetTagName(), newID);
		g_isSave=true;
	}
};

int _tmain_make(int argc, _TCHAR* argv[])
{
	jID* g_pDocIDList =0;
	jIE* g_peItem=0;
	jIE* g_peSkill=0;
/* *_* by icandoit : 2006-01-11 10:04:23

	//jMech_Init("xml\\jTest_xml.xml");
	std::string sss = g_ExeEnv.m_szStartDir;
	nFileSystem::jFolder dm;
	dm.GotoStartDir();
	dm.Goto("..");
	fname_t buf1;
	GetCurrentDirectory(_countof(buf1), buf1);
	strcpy(g_ExeEnv.m_szStartDir, buf1);
*/ //*_* by icandoit : 2006-01-11 10:04:25
	std::tstring szEntityList=_T("");
	if(argc==2)
	{
		szEntityList = argv[1];
	}
	else
	{
		//szEntityList = "xml\\game\\jGameEntityList.xml";
		ja_printf("사용법 : 실행파일.exe xml\\game\\jGameEntityList.xml\n");
		_getch();
		return 0;
	}

	nFileSystem::jFileName fn(szEntityList.c_str() );
	jID* pDEList = GetjIXml()->Load(fn.buffer);
	nFileSystem::jFileName fn1(_T("xml\\game\\jGameEntityIDList.xml"));
	g_pDocIDList = GetjIXml()->Load(fn1.buffer);
	if(!g_pDocIDList)
	{
		jMB("xml\\game\\jGameEntityIDList.xml" , "파일이 없읍니다.");
	}
	g_peItem = g_pDocIDList->Find(TEXT("ItemList"));
	pDEList->Find(g_peItem->GetTagID() )->for_each(_jxGenItemID(g_peItem));

	g_peSkill = g_pDocIDList->Find(TEXT("SkillList"));
	pDEList->Find(g_peSkill->GetTagID() )->for_each(_jxGenItemID(g_peSkill));
	if(g_isSave)
		g_pDocIDList->Save();
	else
	{
		ja_printf("기존 xml\\game\\jGameEntityIDList.xml에 추가할것이 없읍니다.\n");
	}

	ja_printf("아무키나 누르셈");
	_getch();
	return 0;
}
