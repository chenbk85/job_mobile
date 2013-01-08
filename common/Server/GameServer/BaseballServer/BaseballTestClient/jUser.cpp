/* file : jUser.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-20 15:34:04
comp.: www.neowiz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "jUser.h"


jUser::jUser():m_id(jS(test))
	,m_ERunnerStateRound(eBEGIN_ERunnerStateRound)
	,m_quest_sid(0)
	,m_quest_id(0)
	,m_iAutoMatchCount(0)
{
}

void jUser::calc_better_hit(const s_req_better_hit & rbh)//투수가 공던지고 타자가 공치는 상황 계산. 안타 파올등이 결정됨.
{

}


void jUser::send_req_result_better_hit(const s_ans_better_hit &abh)//투수가 공던지고 타자가 공치는 상황 계산. 안타 파올등이 결정됨.
{
	jRETURN(m_peSession);

	int32 score=0;
#if 1
	int32 base_runner_state = m_ERunnerStateRound;
#else
//	int32 base_runner_state =0	
// 	int32 iSize = m_GameRoomInfo.m_result_round().size();
// 	if(iSize)
// 	{
// 		base_runner_state = m_GameRoomInfo.m_result_round().Get(iSize-1).m_tbl_roundresult().base_runner_state();
// 	}
#endif

	EBatterHitType eType = m_EBatterHitType;
	if(eType== eBEGIN_EBatterHitType)
	{
		eType =  (EBatterHitType)nUtil::Randomi(eBEGIN_EBatterHitType+eEBIT_LEFTFIELDOUT,eEND_EBatterHitType-1);
		if(eType == eEBHT_NO_HIT)
		{
			eType =eEBHT_HOMERUN;
		}
	}
	
	/*
	// TEST
	if ( db_id() == 1001 )
	{
		eType = eEBIT_INFIELDOUT;
		jLOG(_T("req_result_better_hit : OUT");
	}
	*/

	s_result_round srr;
	make_round_result(&srr,eType,this->m_ERunnerStateRound);
	nProtoHelper::message_print(srr.m_tbl_roundresult());

	s_result_round* pRR = this->m_GameRoomInfo.add_m_result_round();
	pRR->CopyFrom(srr);

	jMAKE_MESSAGE_X2BS(this,sendMsg,sd,req_result_better_hit);
	sd->mutable_info()->CopyFrom(*pRR);
	sd->set_test(1234);
	g_pPlugIn->send_to_bs(m_peSession,sendMsg);
	jLOG(_T("req_result_better_hit를 분명히 보냄 "),1);
	//jLOG_USER(this,"req_result_better_hit를 분명히 보냄",1);
}


// jUser객체가 삭제되더라도 AutoReConnectCount 값을 유지하기 위함.
jLIST_TYPEDEF_hash_map(Tbl_User_id_t,int, g_mapAutoReConnectCount);
int jUser::Get_AutoReConnectCount()
{
	jvRETURN_ret(0,g_mapAutoReConnectCount.count(game_id) ,_T("game_id=I64d , db_id=%I64d ") ,game_id , db_id() );
	jLOG(_T("Get_AutoReConnectCount g_mapAutoReConnectCount[game_id=%I64d , db_id=%I64d] = %d"), game_id, db_id(),g_mapAutoReConnectCount[game_id]);
	return g_mapAutoReConnectCount[game_id];
}
void jUser::Init_AutoReConnectCount(int iCount)
{
	if(!g_mapAutoReConnectCount.count(game_id) )
		g_mapAutoReConnectCount[game_id] = iCount;
	jLOG(_T("Init_AutoReConnectCount g_mapAutoReConnectCount[game_id=%I64d , db_id=%I64d] = %d"), game_id, db_id(),g_mapAutoReConnectCount[game_id]);
}

void jUser::Set_AutoReConnectCount(int iCount)
{
	g_mapAutoReConnectCount[game_id] = iCount;
	jLOG(_T("Set_AutoReConnectCount g_mapAutoReConnectCount[game_id=%I64d , db_id=%I64d] = %d"), game_id, db_id(),g_mapAutoReConnectCount[game_id]);
}



namespace ug
{
	Version& Make(Version& v)
	{
		//v.set_major(major);			//optional로 바꼈고 값을 세팅하지 말것.
		//v.set_protocol(protocol);		//optional로 바꼈고 값을 세팅하지 말것.
		v.set_framework(SVNVERSION);		// t:\svn\MSG\src\svn_version.hpp의 SVNVERSION값을 세팅하시오.
		//v.set_service(BASE_BALL_GATEWAY_VERSION);			//t:/svn/baseball/MOB_lib/DBHelper.h에 정의됨
		v.set_service(pv_GatewayVersion->Get_int());			// xml에서 설정.
		return v;
	}
}