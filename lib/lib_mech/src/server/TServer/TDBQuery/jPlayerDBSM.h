/* file : jPlayerDBSM.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 17:32:59
comp.: wiki.aqrius.com
title : 
desc : 


플레이어정보를 위한 DBCache와 DBQuery간의 공유 메모리용 구조체 .

*/

#ifndef __jDBUserInfo_header__23429324323j324P5l3a3425ye4r5D54BSM
#define __jDBUserInfo_header__23429324323j324P5l3a3425ye4r5D54BSM
#pragma once


struct jPlayerDBSM
{
public:
	enum EUserNodeUsingState
	{
		eNOT_INIT,// YVECTOR와 SHARED MEMORY ARRAY와 BINDING이 안된 최초상태. 
		eNOT_USE, // YVECTOR와 SHARED MEMORY 와 BINDING은 되었으나 사용안하는상태
		eGOING_TO_LOGIN,
		eLOGIN_OK,
		eNOW_DELETING,//유저접속이 끊겨서 DB에 데이타 삭제예정중.
	};
	SYSTEMTIME m_StartTime;
	EUserNodeUsingState m_eUsingState;
	player_id_t m_pid;
	nAQ::Use_User m_User;
	Use_User_id_t Get_uid(){ return m_User.Get_uid();}
};

#endif // __jDBUserInfo_header__23429324323j324P5l3a3425ye4r5D54BSM
