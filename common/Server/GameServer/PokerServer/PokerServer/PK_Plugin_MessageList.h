/* file : PK_Plugin_message_list.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-01-05 20:16:12
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __PK_Plugin_message_list_header__
#define __PK_Plugin_message_list_header__
#pragma once



#define for_each_PK_MessageList(X)\
	X(req_game_test_packet	," 테스트용.")\
	X(req_join_room, "방입장/만들기.")\
	X(req_send_start,"게임 시작")\
	X(req_send_select_card,"오픈카드 선택")\
	X(req_betting,"베팅 종류")\
	X(req_ping,"핑테스트")\
	X(req_entry,"엔트리 요청")\
	X(req_continue,"게임계속하기 요청")\
	X(req_ruleset,"게임룰세팅 요청")\
	X(req_jokboset,"족보세팅 요청")\
	X(req_ack,"상태별 ack")\
	X(req_choiceremovecard,"버릴카드 선택 요청")\
	X(req_purge,"강제퇴장 요청")\
	X(req_exitque,"방에서나감 요청")\
	X(req_soundtype,"사운드타입 전달")\
	X(req_abuse,"치팅유저 신고")\
	X(req_observe,"옵저버 전달")\

jDEFINE_ENUM_CODE2(PK_MessageList);



#endif // __PK_Plugin_message_list_header__
