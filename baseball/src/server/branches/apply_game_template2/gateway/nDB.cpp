/* file : database_func.cpp
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-04-16 11:04:21
comp.: www.neowiz.com
title : 
desc : 

*/

#include <gateway/database.hpp>
#include <sqlrelay/sqlrclient.h>
#include <sstream>
#include <boost/format.hpp>
#include <stdlib.h>
#include "stdafx.h"
#include "../../MOB_lib/common/header/UFile.h"
#include "baseball_db.h" 


namespace nDB
{
	tcstr g_szPLAYER_NAME_FILE = "../etc/file_db/player_name_find.temp.txt";
	bool player_name_find(cstr szName)
	{
		//jTODO DB에서 플레이어 이름 중복체크. 
		string sBuf;
		if(!nOS::is_exist_file(g_szPLAYER_NAME_FILE)) 
			return false;
		nFileSystem::read_file(g_szPLAYER_NAME_FILE , sBuf);
		if(!sBuf.size()) return false;
		return ja_strstr(sBuf.c_str(), szName);
	}
	void player_name_add(cstr szName)
	{
		jLOG("%s : %s",__FUNCTION__,szName);
		std::tofstream of(g_szPLAYER_NAME_FILE);
		of << szName<< endl ;
		of.close();
	}

	Sys_Error_id_t team_create(jUser* pUser, const s_tbl_team& team, Tbl_Team_id_t & tid)
	{
#if 1
		tid = pUser->size_tbl_team();
		tid += (pUser->db_id()*10);
#else
		//jTODO team table insert!
		//db에서 tid를 얻어오는 작업완료필요.
#endif
		return 0;
	}


	void _pitcherskill_insert(s_tbl_pitcherskill* skill, Tbl_User_id_t uid, Tbl_PlayerPitcher_id_t pid ,EGestureType gt , EPlayerBreakingBall pbb)
	{
		//jTODO DB s_tbl_pitcherskill insert
		nProtoHelper::message_init(*skill);
		skill->set_db_id(nMOB::make_random());
		skill->set_uid(uid);
		skill->set_pid(pid);
		skill->set_gesture(gt);
		skill->set_type(pbb);
	}

#define jLAMDA_find_item_by_sid(X,Z) X(Sys__ItemBase_id_t,sid) Z(string&,sGrade)
	jLAMDA_find_if(find_item_by_sid,s_tbl_item*)
	{
		return it->sid()==sid && it->upgrade_level()==sGrade;
	}
	jLAMDA_end();

	 

	s_tbl_item* insert_item(jUser* pUser, Sys__ItemBase_id_t sid, EItemCategory category, const std::string& etc_info)
	{
		s_tbl_item item;
		nProtoHelper::message_init(item);
		string sGrade;
		switch (category)
		{

#define insert_item1234(VAR,CLASS)\
		case eIC_##VAR:\
			{\
			Sys_Item##CLASS* item_info = jCSV(Sys_Item##CLASS).Index(sid);\
				jvRETURN_ret(0,item_info,"sid = %d, category=%s", sid,ToString(category));\
				sGrade = baseball_db::to_upgrade_base_lev_string(item_info->Get_grade());\
				item.set_upgrade_level(sGrade);\
			}\
			break;\

			for_each_nEXCEL_EItemCategory123(insert_item1234);

		default:
			jWARN("category is invalid : %d", category);
			return 0;
		}

		int use_count = 1;
		if(category==eIC_CONSUME)//소모아이템의 경우만 Sys_ItemConsume에서 초기 사용갯수를 가져와 세팅해야함.
			//재료 & 장착 아이템은 무조건 1개라고 가정한다.
		{
			Sys_ItemConsume* pSysItem= jCSV(Sys_ItemConsume).Index(sid);
			use_count = pSysItem->Get_use_count();
		}

		s_tbl_item* pItem=0;
		if(nBASE_BALL::is_stackable_item_type(category))
		{
			find_item_by_sid func(sid,sGrade);
			pItem = pUser->find_if_tbl_item(func);
		}
		

		fname_t buf;

		if(pItem)
		{
			jLOG("%s set_use_count : %d -> %d" ,jFUNC, pItem->use_count(), pItem->use_count()+ use_count);
			pItem->set_use_count(pItem->use_count() + use_count);
			pItem->set_date_update(nOS::current_SYSTEMTIME(buf));
			//jTODO DB Update
		}
		else
		{
			item.set_use_count(use_count);
			item.set_db_id(nMOB::make_random());
			//jTODO		jRETURN_ERROR_ret(true,	pUser->find_tbl_item(item.db_id() ), ERR_ITEM_BUY_DATA);
			item.set_uid(pUser->db_id());
			item.set_sid(sid);
			item.set_category(category);
			item.set_etc_info(etc_info);
			item.set_date_insert(nOS::current_SYSTEMTIME(buf));

			// 유저에 아이템 지급
			pItem= pUser->add_tbl_item();
			pItem->CopyFrom(item);
			//jTODO DB Insert
		}

		nProtoHelper::message_print(*pItem,pUser->db_id());

		return pItem;
	}

	s_tbl_title* add_quest_title(Sys_Title* pTitle,Sys_Quest* pQuest,jUser* pUser,s_tbl_quest* quest
		,const s_tbl_user* user, const s_tbl_team* team,const s_tbl_playerbetter* better, const s_tbl_playerpitcher* pitcher)
	{
		if(!pTitle) return 0;//획득 타이틀 없음.

		jCHECK(IsValid(pTitle->Get_object_type()));
		s_tbl_title* title = pUser->find_tbl_title_by_group(pTitle->Get_group());
		fname_t szDate;
		if(!title)
		{
			title = pUser->add_tbl_title();
			title->set_date_insert(nOS::current_SYSTEMTIME(szDate));
			title->set_db_id(-nMOB::make_random());
			title->set_object_type(pTitle->Get_object_type());
			title->set_group(pTitle->Get_group());
			switch(pTitle->Get_object_type())
			{
#				define set_oid_GAMEOBJ(user) case eBOT_##user:title->set_oid(user->db_id());break;
				for_each_SCORE_RECORD_OBJ(set_oid_GAMEOBJ);
				case eBEGIN_EBaseballObjectType:
				case eEND_EBaseballObjectType:
					break;
			}
		}
		else
		{
			jCHECK(title->object_type()==pTitle->Get_object_type());
		}
		title->set_date_update(nOS::current_SYSTEMTIME(szDate));
		title->set_qid(quest->db_id());
		title->set_title_sid(pTitle->Get_sid());

		if(title->db_id()<0)
		{
			//jTODO DB s_tbl_title insert.
		}
		else
		{
			//jTODO DB s_tbl_title update
		}
		return title;
	}

	bool check_name(const string& str)
	{
		//jTODO Sys_InvalidWord체크 필요.
		return true;
	}


}//namespace nDB
