/* file : TownUsingList.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-11 08:58:04
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "TownUsingList.h"
#include "../AqCommon/jXmlSaveManager.h"


TownUsingList& TownUsingList::Get()
{
	static TownUsingList a;
	return a;
}
static jID* get_Sys_TownPos_Doc(Sys_Castle_id_t csid)
{
	fname_t szDoc;
	nXML::jE eDoc;
	jt_sprintf(szDoc, _T("%sTownUsing\\%s.xml"),pv_FILE_DB_PATH->Get_cstr(), jCSV(Sys_Castle).at(csid)->Get_name());
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
jIE* TownUsingList::GetFreeTown(Sys_Castle_id_t csid,acstr szUserID,OUT Sys_TownPos_id_t &tpsid)
{
	nXML::jE eDoc =get_Sys_TownPos_Doc(csid);
	fname_t szTag;
	jIVar* pvOwner =0;
	nXML::jE eTown;
	if(tpsid==0) // 최초 접속에서 서버가 자동 마을 선택.
	{
		for(Sys_TownPos_id_t i=1; i<= iMAX_TOWN_IN_CASTLE ; ++i)
		{
			jt_sprintf(szTag,_T("T%d"),i);
			nXML::jE e = eDoc[szTag];
			pvOwner = e->PersistAttr(jS(user_id),jS(NULL));
			if(!pvOwner->IsContents(jS(NULL)))
				continue;

			pvOwner->Set_cstr(jT(szUserID));
			eTown = e;
			tpsid = i;
			break;
		}
	}
	else
	{
		jt_sprintf(szTag,_T("T%d"),tpsid);
		nXML::jE e = eDoc[szTag];
		pvOwner = e->Persist(jS(user_id), jS(NULL))->GetVar();
		if(!pvOwner->IsContents(jS(NULL)))
		{
			GetjILog()->Warning(_T("소유자가 있는 섬을 소유할려고 하였슴. : %s"),jT(szUserID));
			return 0;
		}
		
		eTown = e;
	}
	if(eTown.empty()) return 0;

	pvOwner->SetType(jIVar::EDcstr);
	pvOwner->Set_cstr(jT(szUserID));

	g_jXmlSaveManager.SaveDoc(eDoc->GetDoc());
	return eTown;
}


void TownUsingList::TownToFree(Sys_Castle_id_t csid, Sys_TownPos_id_t tpsid)
{
	nXML::jE eDoc =get_Sys_TownPos_Doc(csid);
	fname_t szTag;
	jt_sprintf(szTag,_T("T%d"),tpsid);
	nXML::jE e = eDoc(szTag);
	if(e.empty()) return;
	e->Erase();
	g_jXmlSaveManager.SaveDoc(eDoc->GetDoc());
}
