/* file : TestSession.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-20 15:34:01
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef ____TestUserGate_header__123498TestUserGate_header__
#define ____TestUserGate_header__123498TestUserGate_header__
#pragma once

struct TestSession 
{
	TestSession();

	jIE* m_peSession;// 소켓 session 연결 객체
	tstring m_id;
	Tbl_User_id_t game_id;
	Tbl_User_id_t db_id(){ return game_id;}

};



#endif // ____TestUserGate_header__123498TestUserGate_header__
