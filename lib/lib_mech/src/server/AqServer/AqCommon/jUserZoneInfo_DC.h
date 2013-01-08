/* file : jUserZoneInfo_DC.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 17:32:59
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __jDBUserInfo_header__
#define __jDBUserInfo_header__
#pragma once


struct jUserZoneInfo_DC
{
public:
	enum EUserNodeUsingState
	{
		eNOT_USE,
		eGOING_TO_LOGIN,
		eLOGIN_OK,
		eNOW_DELETING,//유저접속이 끊겨서 DB에 데이타 삭제예정중.
	};
	EUserNodeUsingState m_eUsingState;
	userid_t m_uid;
	username_t m_szID;	
	nAQ::Use_User m_User;
	Use_User_id_t Get_db_uid(){ return m_User.Get_uid();}

#define User_table_decl34(table) nAQ::Use_##table m_##table[ iMAX_USER_##table ]; uint8 m_iTot##table;
	for_each_User_table(User_table_decl34)

	// TOWN HELPER
	nAQ::Use_Town*	Town_at(townid_t i){if(i>m_iTotTown) return 0; return m_Town+i-1;}
	uint8&				Town_size(){ return m_iTotTown;}

};

#endif // __jDBUserInfo_header__
