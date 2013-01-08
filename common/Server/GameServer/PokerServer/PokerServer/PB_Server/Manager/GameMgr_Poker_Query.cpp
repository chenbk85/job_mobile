//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"


#include "GameMgr_Poker.h"

#include "../util/util.h"

using namespace util;

#if defined(_Poker)
//-- 포커군 잭팟지급시 사용
//CREATE OR REPLACE PACKAGE "PKG_PH_IN_MONEY"
//procedure jackpot_money (
//   p_usn        IN     number,    -- 사용자 번호
//   p_ssn        IN     number,    -- 게임 번호 없으면 0
//   p_logdate    IN     varchar2,  -- 지급일시 (YYYYMMDDHH24MISS)
//   p_deltamoney IN     number,    -- 지급머니
//   p_curmoney   out    number,    -- 지급후 머니
//   p_result     out    number     -- 1 성공 , - 1 실패
//);
//----------------------------------------------------------------------------------------------------
bool CGameMgr::DB_Query_Jackpot(long lUSN, long long &llJackpotMoney)
{
	/*
	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return false;

	int nIdx=USNToIdx(lUSN);
	if(nIdx==-1) return false;
	UserInfo & ui=GetUI(nIdx);
	if(0!=ui.m_lJackpot) return false;
	Money & money=GetMoney(nIdx);
	long lSSN=120;
	string sLogdate=::GetCurrentSystemTime_s();
	GBuf bufOut;
	long lResult=0;
	long lReturn=0;

	if((money.m_llCMoney+llJackpotMoney)>9999999999999999){
		llJackpotMoney=9999999999999999-money.m_llCMoney;
	}
	money.m_llJackpotMoney=llJackpotMoney;
	string sQuery=::format("S|pkg_ph_in_money.jackpot_money|%ld|%ld|%s|%I64i", lUSN, lSSN, sLogdate.c_str(), llJackpotMoney);
	bufOut.Clear();
	if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
	{ // 에러처리
		//DB_SETUSERDATA
		//lResult의 값을 보고 실패 원인을 찾음!
		return false;
	}
	ui.m_lJackpot=1;
	CParser cCParserReceive;
	int nGBufLength=bufOut->GetLength();
	long long llPrevMoney=0;
	llJackpotMoney=0;
	if((0!=nGBufLength)&&(0<=lResult)){
		string strRecv;
		strRecv.assign((char*)bufOut->GetData(), nGBufLength);
		cCParserReceive.MakeStringToTable(strRecv, "|");
		llPrevMoney = pUser->m_llCMoney;
		pUser->m_llCMoney = cCParserReceive.GetHyper(0, 0);
		money.m_llCMoney = pUser->m_llCMoney;
		pUser->m_llGTodayMoney+=pUser->m_llCMoney-llPrevMoney;
		llJackpotMoney=pUser->m_llCMoney-llPrevMoney;
		//SendJackpotMoney(lUSN, pUser->m_llCMoney-llPrevMoney);
		return true;
	}
	FileDebug("pkg_ph_in_money jackpot_money failed %d", lUSN);
	*/
	return false;
}
//CREATE OR REPLACE PACKAGE                 "PKG_PH_EVENT_MONEY"
//AS
//-- 신규유저에게 보너스머니를 지급하는 상시 이벤트
//-- 매10판마다 확률적으로 머니를 지급하기로 함. 1인1일최대3회제한
//PROCEDURE reward_regist (
//p_usn        IN   number,    --- 사용자 번호
//p_msn        IN   number,    --- 군별 정보 1 이면 고스톱 , 2 이면 포커
//p_ssn        IN   number,    --- 게임 번호
//p_deltamoney IN   number,    --- 변경 보상 머니
//p_result     out  number     --- -1 실패 , 1 성공
//);
//end;
///
bool CGameMgr::DB_Query_Event(long lUSN, long long &llEventMoney)
{
	/*
	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return false;

	int nIdx=USNToIdx(lUSN);
	if(nIdx==-1) return false;
	UserInfo & ui=GetUI(nIdx);
	//if(0!=ui.m_lJackpot) return false;
	Money & money=GetMoney(nIdx);
	long lSSN=120;
	long lMSN=2;
	string sLogdate=::GetCurrentSystemTime_s();
	GBuf bufOut;
	long lResult=0;
	long lReturn=0;

	
	string sQuery=::format("S|pkg_ph_event_money.reward_regist|%ld|%ld|%ld|%I64i", lUSN, lMSN, lSSN, llEventMoney);
	bufOut.Clear();
	if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
	{ // 에러처리
		//DB_SETUSERDATA
		//lResult의 값을 보고 실패 원인을 찾음!
		llEventMoney=0;
		return false;
	}
	if(0<=lResult){
		return true;
	}
	llEventMoney=0;
	FileDebug("pkg_ph_event_money event_money failed %d", lUSN);
	*/
	return false;
	
}

//CREATE OR REPLACE PACKAGE BODY                 "PKG_PH_IN_MONEY"
//procedure update_money (
//  p_usn        IN     number,    -- 사용자 번호
//  p_msn        IN     number,    -- 군별 번호 1 고스톱 , 2 포커
//  p_ssn        IN     number,    -- 게임 번호 없으면 0
//  p_logdate    IN     varchar2,  -- 사용 일시
//  p_deltamoney IN     number,    -- 변경되는 머니 금액
//  p_logtype    IN     number,    -- 4 프로모션/이벤트 머니 지급 , 10 이면 케릭터 머니 지급 , 11 이면 효력 머니 지급
//  p_service1   IN     number,    -- 프로모션/이벤트 이면 이벤트 번호 , 효력 이면 효력 번호 , 케릭터 이면 케릭터 상품 번호
//  p_curmoney   out    number,    -- 현 머니
//  p_result     out    number     -- 1 성공 , - 1 실패
// );

bool CGameMgr::DB_Query_UpdateMoney(long lUSN, long long &llEventMoney)
{
	/*
	RCUser* pUser=FindUser(lUSN);
	if(pUser==NULL) return false;

	int nIdx=USNToIdx(lUSN);
	if(nIdx==-1) return false;
	UserInfo & ui=GetUI(nIdx);
	//if(0!=ui.m_lJackpot) return false;
	Money & money=GetMoney(nIdx);
	long lSSN=120;
	long lMSN=2;
	string sLogdate=::GetCurrentSystemTime_s();
	GBuf bufOut;
	long lResult=0;
	long lReturn=0;


	string sQuery=::format("S|pkg_ph_in_money.update_money|%ld|%ld|%ld|%s|%I64i|%ld|%ld", lUSN, lMSN, lSSN, sLogdate.c_str(), llEventMoney, 4, 2);
	bufOut.Clear();
	if( (lReturn=m_pGRCContainer->ExecuteQueryToDB(1, DBTYPE_PHONE, sQuery.c_str(), sQuery.size(), bufOut, &lResult))<0 )
	{ // 에러처리
		//DB_SETUSERDATA
		//lResult의 값을 보고 실패 원인을 찾음!
		llEventMoney=0;
		return false;
	}
	CParser cCParserReceive;
	int nGBufLength=bufOut->GetLength();
	long long llPrevMoney=0;
	if((0!=nGBufLength)&&(0<=lResult)){
		string strRecv;
		strRecv.assign((char*)bufOut->GetData(), nGBufLength);
		cCParserReceive.MakeStringToTable(strRecv, "|");
		llPrevMoney = pUser->m_llCMoney;
		pUser->m_llCMoney = cCParserReceive.GetHyper(0, 0);
		money.m_llCMoney = pUser->m_llCMoney;
		pUser->m_llGTodayMoney+=pUser->m_llCMoney-llPrevMoney;
		llEventMoney=pUser->m_llCMoney-llPrevMoney;
		//SendJackpotMoney(lUSN, pUser->m_llCMoney-llPrevMoney);
		return true;
	}
	FileDebug("pkg_ph_in_money update_money failed %d", lUSN);
	*/
	return false;
}

//CREATE TABLE "SAYPHONE"."PH_GT_USER" 
//(    "USN" NUMBER(10,0), 
// "REG_DATE" VARCHAR2(14) DEFAULT to_char(sysdate,'yyyymmddhh24miss'), 
// "RESTRICT_CNT" NUMBER(5,0) DEFAULT 0, 
// "RESTRICT_REGDATE" VARCHAR2(14) DEFAULT '00000000000000', 
// "UPD_DATE" VARCHAR2(14) DEFAULT '00000000000000'
// ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
// STORAGE(INITIAL 1048576 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
// PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT)
// TABLESPACE "ORYX_D01_PHONE" 
//
// CREATE TABLE "SAYPHONE"."PH_LT_EXTMONEY" 
// (    "USN" NUMBER(10,0), 
// "MSN" NUMBER(3,0), 
// "LOG_DATE" VARCHAR2(14) DEFAULT to_char(sysdate,'yyyymmddhh24miss'), 
// "LOG_TYPE" NUMBER(2,0), 
// "DELTA_EXTMONEY" NUMBER(20,0), 
// "CUR_EXTMONEY" NUMBER(20,0), 
// "EXT_ENDDATE" VARCHAR2(14)
// ) PCTFREE 10 PCTUSED 40 INITRANS 1 MAXTRANS 255 NOCOMPRESS LOGGING
// STORAGE(INITIAL 1048576 NEXT 1048576 MINEXTENTS 1 MAXEXTENTS 2147483645
// PCTINCREASE 0 FREELISTS 1 FREELIST GROUPS 1 BUFFER_POOL DEFAULT)
// TABLESPACE "ORYX_D01_PHONE" 

#endif