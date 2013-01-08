/* file : nDB.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-16 11:05:25
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __nDB_header__
#define __nDB_header__
#pragma once


struct jUser;
namespace nDB
{

	bool player_name_find(cstr szName);//true이면 이름중복.
	void player_name_add(cstr szName);
	void player_name_erase(cstr szName);
	Sys_Error_id_t team_create(jUser* pUser, const s_tbl_team& team, Tbl_Team_id_t & tid);

#	define pitcherskill_insert(skill, uid ,pid ,gt ,pbb) _pitcherskill_insert(skill,uid, pid,(EGestureType)gt,(EPlayerBreakingBall)pbb)
	void _pitcherskill_insert(s_tbl_pitcherskill* skill, Tbl_User_id_t uid, Tbl_PlayerPitcher_id_t pid ,EGestureType gt , EPlayerBreakingBall pbb);


  /// @brief DB에 아이템 추가
  /// @param etc_info[in] etc_info
  /// @param item[out] 추가된 아이템 정보가 저장될 포인터
	/// return값은 클라이언트로 전송하고자 할때 사용.

  s_tbl_item* insert_item(jUser* user, Sys__ItemBase_id_t sid, EItemCategory category, const std::string& etc_info);


  s_tbl_title* add_quest_title(Sys_Title* pTitle,Sys_Quest* pQuest,jUser* pUser,s_tbl_quest* quest
	  ,const s_tbl_user* user, const s_tbl_team* team,const s_tbl_playerbetter* better, const s_tbl_playerpitcher* pitcher);

  bool check_name(const string& str);

}//namespace nDB



#endif // __nDB_header__
