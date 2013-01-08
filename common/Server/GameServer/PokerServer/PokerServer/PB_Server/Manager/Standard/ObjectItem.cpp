//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "ObjectItem.h"

#include "../../../Protocol Buffers/Poker/AdlGame_Poker.h"
#include "../../util/util.h"
#include "../ObjectMgr.h"

#include "../../include/Gstring.h"

using namespace adl;

//----------------------------------------------------------------------------------------------------
bool CObjectItem::CreateObject(void)
{
	CObjectBase::CreateObject();
	return true;
}

//----------------------------------------------------------------------------------------------------
void CObjectItem::SendItemNotify(long lUSN)
{
	RCUser* pUser=GetObjectMgr()->FindUser(lUSN);
	if(pUser==NULL) return;

	__int64 lCurrentTime=GetCurrentSystemTime();

	MsgSC_ItemNotify msg;
	msg.m_lLimitTotalCnt=pUser->m_lPTotalPlayCount;
	msg.m_lLimitTodayCnt=pUser->m_lMTodayPlayCount;
	msg.m_bInfinitySpeedItem=0;
	msg.m_llSpeedToTime=0;
	PayloadSC pld(PayloadSC::msgItemNotify_Tag, msg);
	GetObjectMgr()->SendToUser(lUSN, pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectItem::SendItemNotify(__int64 lCurrentTime)
{
	int nTotal=GetObjectMgr()->GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo& ui=GetObjectMgr()->GetUI(i);
		if(ui.m_lUSN==-1) continue;

		RCUser* pUser=GetObjectMgr()->FindUser(ui.m_lUSN);
		if(pUser==NULL) continue;

		MsgSC_ItemNotify msg;
		msg.m_lLimitTotalCnt=pUser->m_lPTotalPlayCount;
		msg.m_lLimitTodayCnt=pUser->m_lMTodayPlayCount;
		msg.m_bInfinitySpeedItem=0;
		msg.m_llSpeedToTime=0;
		PayloadSC pld(PayloadSC::msgItemNotify_Tag, msg);
		GetObjectMgr()->SendToUser(ui.m_lUSN, pld);		
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectItem::SendAssaItemNotify(long lUSN, int nIndex, string& sItem, long lRankType)
{
	MsgSC_AssaItemNotify msg;
	msg.m_lUSN=lUSN;
	msg.m_lRankType=lRankType;//m_vResultOrder[nIndex];
	msg.m_sItem=sItem;
	PayloadSC pld(PayloadSC::msgAssaItemNotify_Tag, msg);
	GetObjectMgr()->SendToUser(lUSN, pld);
}
//----------------------------------------------------------------------------------------------------
long CObjectItem::OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize)
{
	DWORD dwSize=(DWORD)lSize;
	//UserInfoInGRC ubi;
	//BDecode_UserInfoInGRC((LPCBUF)szItem, &dwSize, &ubi);

	//DB_GetUserOutData ugd;	
	//dwSize=ubi.m_sUserGameData.length();
	//DWORD dwSize1= dwSize;
	//BDecode_DB_GetUserOutData((LPCBUF)ubi.m_sUserGameData.c_str(), &dwSize1, &ugd);

	RCUser* pUser=GetObjectMgr()->FindUser(lUSN);
	if(pUser==NULL) return ERROR_CODE_CANCEL;

	// 아이템 세팅
	//pUser->SetItem(ugd.m_sReservedString4);

	SendItemNotify(lUSN);
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
void CObjectItem::Assa38GwangDdang(int nIndex)
{
	UserInfo& ui=GetObjectMgr()->GetUI(nIndex);
	if(ui.m_lUSN<0) return;
	CResultFactor cResultFactor;
	Cards & card=GetObjectMgr()->GetCards(ui.m_nIndex);
	cResultFactor.SetResultCard(card.m_vtCards);
	string sItemType=_T("G_V2_ASSA");
	if(true==cResultFactor.IsResultFactor(CResultFactor::MADETYPE_NONE, CResultFactor::RESULT_38DDANG)){
		if(GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]<CResultFactor::RESULT_38DDANG){
			GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]=CResultFactor::RESULT_38DDANG;
			string sItem=_T("G_V2_ASSA_38GWANG");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_38DDANG);
			}
		}
	}
	if(true==cResultFactor.IsResultFactor(CResultFactor::MADETYPE_NONE, CResultFactor::RESULT_18DDANG)){
		if(GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]<CResultFactor::RESULT_18DDANG){
			GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]=CResultFactor::RESULT_18DDANG;
			string sItem=_T("G_V2_ASSA_18GWANG");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_18DDANG);
			}
		}
	}
	if(true==cResultFactor.IsResultFactor(CResultFactor::MADETYPE_NONE, CResultFactor::RESULT_13DDANG)){
		if(GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]<CResultFactor::RESULT_13DDANG){
			GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]=CResultFactor::RESULT_13DDANG;
			string sItem=_T("G_V2_ASSA_13GWANG");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_13DDANG);
			}
		}
	}
	if(true==cResultFactor.IsResultFactor(CResultFactor::MADETYPE_NONE, CResultFactor::RESULT_10DDANG)){
		if(GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]<CResultFactor::RESULT_10DDANG){
			GetObjectMgr()->m_cGameInfo.m_nBestAssa[nIndex]=CResultFactor::RESULT_10DDANG;
			string sItem=_T("G_V2_ASSA_10PAIR");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_10DDANG);
			}
		}
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	TABLE : game_buyreservation
//	SQL> desc pkg_gameitem
//	PROCEDURE RESERVE_GAMEITEM
//	Argument Name                  Type                    In/Out Default?
//	------------------------------ ----------------------- ------ --------
//	P_USN							NUMBER                  IN
//	P_RESERVEDDATE					VARCHAR2                IN
//	P_RESERVEDTYPE					VARCHAR2                IN
//	P_RESERVEDCODESTR				VARCHAR2                IN
//  P_PRIORITY                      NUMBER                  IN
//	P_RESULT
//----------------------------------------------------------------------------------------------------
bool CObjectItem::DBQuery_Assa38GwangDdang(long lUSN, string sItemType, string sItem)
{
	if(sItemType!=_T("G_V2_ASSA")) return true; // 메이드 아이템은 DB에 기록을 안한다.
	//CComVariant vtOutData;
	long lResult;
	//string sQuery=::format("S|PKG_GAMEITEM.RESERVE_GAMEITEM|%ld|%s|%s|%s", lUSN, GetObjectMgr()->m_cGameInfo.m_sGameDate.c_str(), sItemType.c_str(), sItem.c_str());
//	long lTemp=m_pGRCContainer->ExecuteQueryToDB(DB_QUERY, g_lSSN, sQuery.c_str(), sQuery.size(), &vtOutData, &lResult);
//#if defined(_DEBUG) || defined(TEST_RELEASE)
//	string str=::format("DBQuery_Assa38GwangDdang 쿼리 결과 %d, %d, %s", lTemp, lResult, sQuery.c_str());
//	GetObjectMgr()->SendSystemMsg(SYSMSG_TEST, str, lUSN);
//#endif
//	if(lTemp<0)
//	{
//		GetObjectMgr()->m_cFileLog.Log("set thankyou failed %d %d %d", lTemp, lResult, lUSN);
//		return false;
//	}

	return true;
}
//----------------------------------------------------------------------------------------------------
void CObjectItem::OnRcvTestKeySetting(long lUSN, MsgCS_TestKeySetting* pMsg)
{
#ifdef _ASSA_SET
	int nIndex=GetObjectMgr()->USNToIdx(lUSN);
	if(-1==nIndex) return;
	UserInfo & ui=GetObjectMgr()->GetUI(nIndex);
	switch(pMsg->m_nChar)
	{
	case VK_F2:
		{
		}
		break;
	case VK_F3:
		{
			//string sItem=_T("G_V2_ASSA_4GO");
			//string sItemType=_T("G_V2_ASSA");
			//if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
			//	SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_10DDANG);
			//}
		}
		break;
	case VK_F4:
		{
			string sItem=_T("G_V2_ASSA_10PAIR");
			string sItemType=_T("G_V2_ASSA");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_10DDANG);
			}
		}
		break;
	case VK_F5:
		{
			string sItem=_T("G_V2_ASSA_13GWANG");
			string sItemType=_T("G_V2_ASSA");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_13DDANG);
			}
		}
		break;
	case VK_F6:
		{
			string sItem=_T("G_V2_ASSA_18GWANG");
			string sItemType=_T("G_V2_ASSA");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_18DDANG);
			}
		}
		break;
	case VK_F7 :
		{
			string sItem=_T("G_V2_ASSA_38GWANG");
			string sItemType=_T("G_V2_ASSA");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_38DDANG);
			}
		}
		break;
	case VK_F8 :
		{
			string sItem=_T("G_V2_ASSA_10PAN");
			string sItemType=_T("G_V2_ASSA");
			if(true==DBQuery_Assa38GwangDdang(ui.m_lUSN, sItemType, sItem)){
				SendAssaItemNotify(ui.m_lUSN, nIndex, sItem, RANK_ASSA_JANGDDANG);
			}
		}
		break;
	default:
		break;
	}
#endif
}