/* file : jUser.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-20 15:34:01
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jUser_header__
#define __jUser_header__
#pragma once

/*
#define for_each_EUserGPS(X)\
X(eGPS_LOGOUT			," ��Ʈ����������")\
X(eGPS_LOGIN			,"UserGate����������")\
X(eGPS_SHOP				,"��������")\
X(eGPS_UserGateServer	,"��������� ��������Ʈ���������� ����")\
\
X(eGPS_GAMEROOM			,"BaseballServer������ �������")\
X(eGPS_GAME_START		,"���ӽ���")\
X(eGPS_GAME_ROUND_START	,"���ӽ���")\
X(eGPS_PITCHER_THROW	,"������ ���� ������")\
X(eGPS_BETTER_HIT		,"Ÿ�ڰ� ���� �ƴ�")\
X(eGPS_GAMEROOM_PRE_LEAVE,"�κ�� ������ ������� ����")\
X(eGPS_BaseballServer	,"��������� ���Ӽ������ӻ���")\

jDEFINE_ENUM_CODE2(EUserGPS);
*/


struct jUser : public jUser_base
{
	jUser();

	jIE* m_peSession;// ���� session ���� ��ü
	tstring m_id;
	Tbl_User_id_t game_id;
	Tbl_User_id_t db_id(){ return game_id;}


	s_ans_pitcher_throw		m_ans_pitcher_throw;
	s_ans_better_hit		m_ans_better_hit;

#	define UAnsProtocol_member(ENUM,STRUCT,VAR) STRUCT m_##STRUCT;
	for_each_UAnsProtocol(UAnsProtocol_member);


	void do_play_client_production(){}
	void calc_better_hit(const s_req_better_hit & rbh);
	void send_req_result_better_hit(const s_ans_better_hit& abh);

	bool is_allow_rematch;
	bool is_allow_rematch_other;
	int32 m_single_play_id;//�̱۸�ġ �����Ҷ� �������� ���и� ��������Ͽ� �����ϱ����� ����id
	void reset_user_info()
	{
		jUser_base::reset_user_info();
		is_allow_rematch=false;
		is_allow_rematch_other=false;
		m_single_play_id=0;
	}

	ERunnerStateRound m_ERunnerStateRound;
	EBatterHitType m_EBatterHitType;

	//#--------------------------------------------------------------------------
	//  ����Ʈ ����.
	//#--------------------------------------------------------------------------
	Sys_Quest_id_t m_quest_sid;
	int64			m_quest_id;

	//#--------------------------------------------------------------------------
	//������.
	//#--------------------------------------------------------------------------
	jLIST_TYPEDEF_map(astring,int,m_recv_table_count);
	jLIST_TYPEDEF_map(astring,int,m_ServerInfoRecvState);

	//#--------------------------------------------------------------------------
	//[AutoPlay]
	//#--------------------------------------------------------------------------
	int m_iAutoMatchCount; // pv_IsAutoPlay�� true�϶� AnsDB���� pv_AutoMatchCount���� ���õȴ�. ���� ���������� �߻��ϸ� -1�� ���õ�.
	bool IsAutoPlay(){ return m_iAutoMatchCount>0;}
	bool IsAutoPlayError(){ return m_iAutoMatchCount<0;}

	int m_iAutoReJoinCount; // pv_IsAutoPlay�� true�϶� AnsDB���� pv_AutoReJoinCount���� ���õȴ�.
	void Init_AutoReConnectCount(int iCount);
	int Get_AutoReConnectCount();
	void Set_AutoReConnectCount(int iCount);

};



#endif // __jUser_header__
