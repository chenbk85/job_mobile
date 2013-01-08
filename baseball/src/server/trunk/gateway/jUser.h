/* file : jUser.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-20 15:36:37
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __jUser_header__
#define __jUser_header__
#pragma once

typedef ::google::protobuf::RepeatedPtrField< ::s_result_round > s_result_round_list_t;

// _ORACLE :  DB ���� ����ü
struct db_record
{
	int homerun;	// �� ���ӿ��� ����� Ȩ�� ��
	int strike;		// �� ���ӿ��� ����� ��Ʈ����ũ ��
};

struct jUser : public jUser_base
{
	bool is_inited;
	bool m_is_give_daily;

	time_t m_timer_game_start;
	jUser()
	{
		m_timer_game_start=0;
		is_inited=false;
		m_is_give_daily=false;
	}
	~jUser();

	void calc_game_round_result(OUT s_tbl_user* user
		,IN const s_result_round_list_t &rr_list);
	
	// _ORACLE : db�� ������ ���� ����� round result ���� �����ϴ� �Լ�
	void db_game_record( const s_result_round_list_t &rr_list, int64 db_id, db_record& record );

	nMOB::jPacketRecvTimeControl m_jPacketRecvTimeControl;

};


extern jUser g_jUser;





#define BASEBALL_CHECK_CONTINUE_STAT(better,STAT_NAME)\
if(is_##STAT_NAME)\
{\
	better->_jJOIN_3(set_,STAT_NAME,_continue)(better->STAT_NAME##_continue()+1);\
	if(better->STAT_NAME##_continue() > better->STAT_NAME##_continue_max() )\
	{\
		better->_jJOIN_3(set_,STAT_NAME,_continue_max)( better->STAT_NAME##_continue() );\
	}\
}\
else\
{\
	better->_jJOIN_3(set_,STAT_NAME,_continue)(0);\
}\

#endif // __jUser_header__
