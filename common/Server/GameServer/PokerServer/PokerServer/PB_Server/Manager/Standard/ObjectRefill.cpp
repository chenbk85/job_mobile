//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"
#include "ObjectRefill.h"

#include "../../../Protocol Buffers/Poker/AdlGameUser_Poker.h"
#include "../../util/util.h"

using namespace adl;

//----------------------------------------------------------------------------------------------------
bool CObjectRefill::CreateObject(void)
{
	CObjectBase::CreateObject();
	return true;
}
//----------------------------------------------------------------------------------------------------
bool CObjectRefill::IsNewRU(long lUSN)
{
	RCUser * pUser=GetObjectMgr()->FindUser(lUSN);
	if(pUser==NULL) return false;

	if(pUser->m_lPTotalPlayCount<500)
		return true;

	return false;
}
//----------------------------------------------------------------------------------------------------
bool CObjectRefill::IsPCBang(long lUSN)
{
	RCUser * pUser=GetObjectMgr()->FindUser(lUSN);
	if(pUser==NULL) return false;
	return false;
}
//----------------------------------------------------------------------------------------------------
int CObjectRefill::NowMaxRefillCnt(long lUSN)
{
	if(IsNewRU(lUSN))
		return 8;
	else 
		return 8;
}
//----------------------------------------------------------------------------------------------------
__int64 CObjectRefill::NowMaxRefillMoney(long lUSN)
{
	if(IsNewRU(lUSN))
		return 3*UK;
	else 
		return 3*UK;
}
//----------------------------------------------------------------------------------------------------
long CObjectRefill::GetRefillType(long lUSN)
{
	if(IsNewRU(lUSN))               // 신규
		return 1;//61
	else
		return 1;						 // 일반
}
//----------------------------------------------------------------------------------------------------
bool CObjectRefill::IsRefillResetDay(long lUSN)
{
	RCUser * pUser=GetObjectMgr()->FindUser(lUSN);
	if(pUser==NULL) return false;

	__int64 lTime=GetCurrentSystemTime();
	if(pUser->m_cRefill.GetTime()==0)
		return true;
	else
	{
		__int64 lTemp1=(pUser->m_cRefill.GetTime()-120000)/1000000;    //최근 refill time
		__int64 lTemp2=(lTime-120000)/1000000;                         //현재 play time
		if(lTemp1 - lTemp2<0)
			return true;
		else
			return false;
	}
	return false;
}
//----------------------------------------------------------------------------------------------------
void CObjectRefill::RefillCheck()
{
	long lChannel=GetObjectMgr()->m_cGameInfo.m_lChannel_idx;
	if(lChannel>__CONST_::CHANNEL_1){
		return;
	}
	//if((GetObjectMgr()->m_cGameInfo.m_lChannel_idx!=__CONST_::CHANNEL_1) && (GetObjectMgr()->m_cGameInfo.m_lChannel_idx!=__CONST_::CHANNEL_2)){
	//	return ;
	//}
	int nTotal=GetObjectMgr()->GetUISize();
	for(int i=0; i<nTotal; i++)
	{
		UserInfo & ui=GetObjectMgr()->GetUI(i);
		if(ui.m_lUSN==-1) continue;
		//if(ui.m_lCLevel>2) continue; //하수 이하
		//20110905 원페어 이하 리필 안됨
		if(ui.m_lCLevel>0) continue; //하수 이하
		Money & money=GetObjectMgr()->GetMoney(ui.m_nIndex);
		if(money.m_llCMoney >= 500*MAN) continue;
		if(GetObjectMgr()->IsMiniCashBox(ui.m_lUSN)) continue;

		RCUser * pUser=GetObjectMgr()->FindUser(ui.m_lUSN);
		if(pUser==NULL) return ;
		DBQGetRefillCnt(ui.m_lUSN);
		if(IsRefillResetDay(ui.m_lUSN)) // 다른 날짜일때
		{
			pUser->m_cRefill.m_nCnt=0; // 임시 0으로 세팅한다.
		}
		if(NowMaxRefillCnt(ui.m_lUSN)>pUser->m_cRefill.GetCnt()){
			DBQSetRefillCnt(ui.m_lUSN);
		}
	}
}
//----------------------------------------------------------------------------------------------------
//CREATE TABLE "SAYPHONE_TEST"."PH_GT_REFILL" 
//("USN" NUMBER(10,0) NOT NULL ENABLE, 
// "MSN" NUMBER(3,0) NOT NULL ENABLE, 
// "REFILL_TYPE" NUMBER(2,0) NOT NULL ENABLE, 
// "REG_DAY" VARCHAR2(8) DEFAULT to_char(sysdate,'yyyymmdd') NOT NULL ENABLE, 
// "REFILL_CNT" NUMBER(2,0) NOT NULL ENABLE, 
// "LASTREFILLDATE" VARCHAR2(14) NOT NULL ENABLE
// ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
// STORAGE(INITIAL 1048576 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
// PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT)
// TABLESPACE "ORYX_D01_PHONE" 
/**/
bool CObjectRefill::DBQGetRefillCnt(long lUSN)
{
	/*
	RCUser * pUser=GetObjectMgr()->FindUser(lUSN);
	if(pUser==NULL) return false;

	long lMSN=2; // 고스톱류(1), 포커류(2), 훌라류(3), 캐쥬얼류(4), 섯다류(5)  머니고유넘버
	long lRefill_type=1;
	GBuf bufOut;
	long lResult=0;
	long lReturn=0;

	string sQuery=::format("Q|select refill_cnt , lastrefilldate from ph_gt_refill where usn=%ld and msn=%ld and refill_type=%ld", lUSN, lMSN, lRefill_type);
	bufOut.Clear();
	if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
	{ // 에러처리
		return false;
	}
	CParser cCParserReceive;
	int nGBufLength=bufOut->GetLength();
	if((0!=nGBufLength)&&(0<=lResult)){
		string strRecv;
		strRecv.assign((char*)bufOut->GetData(), nGBufLength);
		cCParserReceive.MakeStringToTable(strRecv, "|");
		pUser->m_cRefill.m_nCnt=cCParserReceive.GetLong(0, 0);
		pUser->m_cRefill.m_llTime=cCParserReceive.GetHyper(1, GetCurrentSystemTime());
		return true;
	}
	*/
	return false;
}
//CREATE OR REPLACE PACKAGE "PKG_PH_IN_MONEY" 
//procedure refill_money     (
//	p_usn        IN    number,   -- 사용자 번호 
//	p_msn        IN    number,   -- 군별 정보 
//	p_refilltype IN    number,   -- 리필 타입 
//	p_deltamoney IN    number,   -- 변경 머니 
//	p_curmoney   out   number,   -- 변경 이후 현 머니 
//	p_result     out   number    -- 결과  -1 실패 , 1 성공 
//	);

//----------------------------------------------------------------------------------------------------
void CObjectRefill::DBQSetRefillCnt(long lUSN)
{
	/*
	RCUser * pUser=GetObjectMgr()->FindUser(lUSN);
	if(pUser==NULL) return ;

	int nIdx=GetObjectMgr()->USNToIdx(lUSN);
	if(nIdx==-1) return ;

	Money & money=GetObjectMgr()->GetMoney(nIdx);

	long lRefillType=GetRefillType(lUSN); // 
	long lMSN=2; // 고스톱류(1), 포커류(2), 
	__int64 llRefillMoney=NowMaxRefillMoney(lUSN);
	GBuf bufOut;
	long lResult=0;
	long lReturn=0;

	string sQuery=::format("S|pkg_ph_in_money.refill_money|%ld|%ld|%ld|%I64i", lUSN, lMSN, lRefillType, llRefillMoney);
	bufOut.Clear();
	if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
	{ // 에러처리
		//DB_SETUSERDATA
		//lResult의 값을 보고 실패 원인을 찾음!
		return;
	}
	//string sQuery=::format("S|PKG_MONEY_SERVICE.REFILL_MONEY|%ld|%ld|%ld|%I64i", 62, lUSN, lMSN, llRefillMoney);
	//if( m_pGRCContainer->ExecuteQueryToDB(DB_QUERY, g_lSSN, sQuery.c_str(), sQuery.size(), &vtOutData, &lResult)<0 )
	//{ 
	//	FileDebug("DBQSetRefillCnt ExecuteQueryToDB faild ");
	//	return ;
	//}
	CParser cCParserReceive;
	int nGBufLength=bufOut->GetLength();
	long long llPrevMoney=0;
	if((0!=nGBufLength)&&(0<=lResult)){
		string strRecv;
		strRecv.assign((char*)bufOut->GetData(), nGBufLength);
		cCParserReceive.MakeStringToTable(strRecv, "|");
		pUser->m_cRefill.m_nCnt++;
		llPrevMoney = pUser->m_llCMoney;
		pUser->m_cRefill.m_llTime=GetCurrentSystemTime();
		pUser->m_llCMoney = cCParserReceive.GetHyper(0, 0);
		money.m_llCMoney = pUser->m_llCMoney;
		int nRefillCnt=NowMaxRefillCnt(lUSN)-pUser->m_cRefill.GetCnt();
		GetObjectMgr()->SendRefillMoneyNtf(lUSN, nRefillCnt, pUser->m_llCMoney-llPrevMoney);
	}
	else{
		FileDebug("pkg_ph_in_money refill failed %d", lUSN);
	}
	*/
}
//----------------------------------------------------------------------------------------------------