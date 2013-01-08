/* file : jPlayerDBSM.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 17:32:59
comp.: wiki.aqrius.com
title : 
desc : 


�÷��̾������� ���� DBCache�� DBQuery���� ���� �޸𸮿� ����ü .

*/

#ifndef __jDBUserInfo_header__23429324323j324P5l3a3425ye4r5D54BSM
#define __jDBUserInfo_header__23429324323j324P5l3a3425ye4r5D54BSM
#pragma once


struct jPlayerDBSM
{
public:
	enum EUserNodeUsingState
	{
		eNOT_INIT,// YVECTOR�� SHARED MEMORY ARRAY�� BINDING�� �ȵ� ���ʻ���. 
		eNOT_USE, // YVECTOR�� SHARED MEMORY �� BINDING�� �Ǿ����� �����ϴ»���
		eGOING_TO_LOGIN,
		eLOGIN_OK,
		eNOW_DELETING,//���������� ���ܼ� DB�� ����Ÿ ����������.
	};
	SYSTEMTIME m_StartTime;
	EUserNodeUsingState m_eUsingState;
	player_id_t m_pid;
	nAQ::Use_User m_User;
	Use_User_id_t Get_uid(){ return m_User.Get_uid();}
};

#endif // __jDBUserInfo_header__23429324323j324P5l3a3425ye4r5D54BSM
