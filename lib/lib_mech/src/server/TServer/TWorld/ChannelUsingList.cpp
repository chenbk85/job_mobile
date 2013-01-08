/* file : ChannelUsingList.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-11 08:58:04
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "TWorld.h"

#include "ChannelUsingList.h"
#include "../TCommonServer/jXmlSaveManager.h"

ChannelUsingList& ChannelUsingList::Get()
{
	static ChannelUsingList a;
	return a;
}
static jID* get_Sys_TownPos_Doc(Sys_Castle_id_t csid)
{
	fname_t szDoc;
	nXML::jE eDoc;
	js_sprintf(szDoc, _T("%sChannelUsing\\%s.xml"),pv_FILE_DB_PATH->Get_cstr(), jCSV(Sys_Castle).at(csid)->Get_name());
	eDoc= GetjIXml()->Load(szDoc);
	if(eDoc.empty())
	{
		nFileSystem::jFolder::CreateDirForce(szDoc);
		GetjIXml()->NewFile(szDoc);
		eDoc= GetjIXml()->Load(szDoc);
		jAssert0(eDoc.full() && __FUNCDNAME__);
		eDoc->PersistAttr(jS(csid) , (int)csid);
	}
	return eDoc->GetDoc();
}
jIE* ChannelUsingList::GetFreeChannel(Sys_Castle_id_t csid,player_name_ct szUserID,OUT Sys_TownPos_id_t &tpsid)
{
	nXML::jE eDoc =get_Sys_TownPos_Doc(csid);
	fname_t szTag;
	jIVar* pvOwner =0;
	nXML::jE eChannel;
	if(tpsid==0) // ���� ���ӿ��� ������ �ڵ� ���� ����.
	{
		for(Sys_TownPos_id_t i=1; i<= iMAX_TOWN_IN_CASTLE ; ++i)
		{
			js_sprintf(szTag,_T("T%d"),i);
			nXML::jE e = eDoc[szTag];
			pvOwner = e->PersistAttr(jS(user_id),jS(NULL));
			if(!pvOwner->IsContents(jS(NULL)))
				continue;

			pvOwner->Set_cstr(jT(szUserID));
			eChannel = e;
			tpsid = i;
			break;
		}
	}
	else
	{
		js_sprintf(szTag,_T("T%d"),tpsid);
		nXML::jE e = eDoc[szTag];
		pvOwner = e->Persist(jS(user_id), jS(NULL))->GetVar();
		if(!pvOwner->IsContents(jS(NULL)))
		{
			jWARN1(_T("�����ڰ� �ִ� ���� �����ҷ��� �Ͽ���. : %s"),jT(szUserID));
			return 0;
		}
		
		eChannel = e;
	}
	if(eChannel.empty()) return 0;

	pvOwner->SetType(jIVar::EDcstr);
	pvOwner->Set_cstr(jT(szUserID));

	g_jXmlSaveManager.SaveDoc(eDoc->GetDoc());
	return eChannel;
}


void ChannelUsingList::ChannelToFree(Sys_Castle_id_t csid, Sys_TownPos_id_t tpsid)
{
	nXML::jE eDoc =get_Sys_TownPos_Doc(csid);
	fname_t szTag;
	js_sprintf(szTag,_T("T%d"),tpsid);
	nXML::jE e = eDoc(szTag);
	if(e.empty()) return;
	e->Erase();
	g_jXmlSaveManager.SaveDoc(eDoc->GetDoc());
}
