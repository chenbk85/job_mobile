/* file : jXmlSaveManager.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-16 13:46:59
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jXmlSaveManager.h"

jLIST_TYPEDEF_map(jID*,bool,m_SavingFlag);
AQ_SERVER_LIB_API jXmlSaveManager g_jXmlSaveManager;

static void _JOB_Save(nEVENT::jIMessage* pM)
{
	jID* pD = (jID*)pM->GetArg(0)->GetUserData();
	//jXmlSaveManager* pXSM = (jXmlSaveManager*)pM->GetArg(1)->GetUserData();
	pD->Save();
	pM->Erase();
	m_SavingFlag_it it = m_SavingFlag.find(pD);
	if(it!=m_SavingFlag.end())
	{
		if(it->second)
		{
			GetjIXml()->UnLoad(pD);
		}
		m_SavingFlag.erase(it);
	}
}

void jXmlSaveManager::SaveDoc(jID* pD,bool isUnload,float fTimeSec)
{
	m_SavingFlag_it it = m_SavingFlag.find(pD);
	if(it!=m_SavingFlag.end()) 
	{
		if(isUnload)
		{
			it->second=true;
		}
		return;
	}
	else
	{
		m_SavingFlag[pD] = isUnload;
	}

	if(fTimeSec==0)
	{
		fTimeSec = pv_XmlSaveScheduleTime->Get_float();
	}
	static nEVENT::jIMsgManager* pMM = nEVENT::jIMsgManager::Get(jS(jXmlSaveManager), true);
	nEVENT::jIMessage* pM = pMM->Regist_TimeBaseAndCount(0,_JOB_Save,2,fTimeSec,1);
	pM->GetArg(0)->SetUserData(pD);
	//pM->GetArg(1)->SetUserData(this);
	pM->DoWakeUp();
}

void jXmlSaveManager::Destory()
{
	static nUtil::jCriticalSection cs;
	jAUTO_LOCK_CS(cs);
	m_SavingFlag_it it = m_SavingFlag.begin(), ie = m_SavingFlag.end();
	for(;it!=ie;++it)
	{
		jID* pD = it->first;
		if(pD)
			pD->Save();
	}
	m_SavingFlag.clear();
}
