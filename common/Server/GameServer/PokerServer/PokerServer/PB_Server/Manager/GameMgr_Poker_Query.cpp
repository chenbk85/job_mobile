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
//-- ��Ŀ�� �������޽� ���
//CREATE OR REPLACE PACKAGE "PKG_PH_IN_MONEY"
//procedure jackpot_money (
//   p_usn        IN     number,    -- ����� ��ȣ
//   p_ssn        IN     number,    -- ���� ��ȣ ������ 0
//   p_logdate    IN     varchar2,  -- �����Ͻ� (YYYYMMDDHH24MISS)
//   p_deltamoney IN     number,    -- ���޸Ӵ�
//   p_curmoney   out    number,    -- ������ �Ӵ�
//   p_result     out    number     -- 1 ���� , - 1 ����
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
	{ // ����ó��
		//DB_SETUSERDATA
		//lResult�� ���� ���� ���� ������ ã��!
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
//-- �ű��������� ���ʽ��Ӵϸ� �����ϴ� ��� �̺�Ʈ
//-- ��10�Ǹ��� Ȯ�������� �Ӵϸ� �����ϱ�� ��. 1��1���ִ�3ȸ����
//PROCEDURE reward_regist (
//p_usn        IN   number,    --- ����� ��ȣ
//p_msn        IN   number,    --- ���� ���� 1 �̸� ���� , 2 �̸� ��Ŀ
//p_ssn        IN   number,    --- ���� ��ȣ
//p_deltamoney IN   number,    --- ���� ���� �Ӵ�
//p_result     out  number     --- -1 ���� , 1 ����
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
	{ // ����ó��
		//DB_SETUSERDATA
		//lResult�� ���� ���� ���� ������ ã��!
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
//  p_usn        IN     number,    -- ����� ��ȣ
//  p_msn        IN     number,    -- ���� ��ȣ 1 ���� , 2 ��Ŀ
//  p_ssn        IN     number,    -- ���� ��ȣ ������ 0
//  p_logdate    IN     varchar2,  -- ��� �Ͻ�
//  p_deltamoney IN     number,    -- ����Ǵ� �Ӵ� �ݾ�
//  p_logtype    IN     number,    -- 4 ���θ��/�̺�Ʈ �Ӵ� ���� , 10 �̸� �ɸ��� �Ӵ� ���� , 11 �̸� ȿ�� �Ӵ� ����
//  p_service1   IN     number,    -- ���θ��/�̺�Ʈ �̸� �̺�Ʈ ��ȣ , ȿ�� �̸� ȿ�� ��ȣ , �ɸ��� �̸� �ɸ��� ��ǰ ��ȣ
//  p_curmoney   out    number,    -- �� �Ӵ�
//  p_result     out    number     -- 1 ���� , - 1 ����
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
	{ // ����ó��
		//DB_SETUSERDATA
		//lResult�� ���� ���� ���� ������ ã��!
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