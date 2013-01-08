#include "../stdafx.h" 
#include <stdlib.h> 
#include <boost/scoped_ptr.hpp> 

#include <boost/test/unit_test.hpp> 
#include "../baseball_db.h" 
#include "../baseball_db_interface.h" 
#include "../baseball_db_sqlite.h" 

#define BUF_SIZE 4096

namespace baseball_db_crud_test
{

static const char* s_filename = "/tmp/baseball_test.db";

BOOST_AUTO_TEST_CASE(create_db_file)
{
	std::string cmd("../etc/sqlite_db/create_tables.sh ");
	cmd += s_filename;
	cmd += " ../etc/sqlite_db";
	BOOST_REQUIRE (0 == ::system (cmd.c_str()));
}


BOOST_AUTO_TEST_CASE(tbl_user)
{
// _SIMPLE_MODE
/*
	boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));

	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Initialize(), db->GetLastErrorString());

	s_tbl_user user_insert;
	user_insert.set_db_id(1000);
	user_insert.set_uname("hahah");
	user_insert.set_default_tid(50);
	user_insert.set_time_last_login("2999-11-11 11:11:11");
	user_insert.set_time_last_logout("2999-11-11 11:11:11");
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_user(user_insert), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess != db->Insert_tbl_user(user_insert), db->GetLastErrorString());

	std::vector<s_tbl_user> user_select;
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_user(1000, user_select), db->GetLastErrorString());
	BOOST_REQUIRE (1 == user_select.size());
	BOOST_REQUIRE (user_select[0].db_id() == user_insert.db_id());
	BOOST_REQUIRE (user_select[0].uname() == user_insert.uname());
	BOOST_REQUIRE (user_select[0].default_tid() == user_insert.default_tid());
	BOOST_REQUIRE (user_select[0].time_last_login() == user_insert.time_last_login());
	BOOST_REQUIRE (user_select[0].time_last_logout() == user_insert.time_last_logout());

	s_tbl_user user_update = user_select[0];
	user_update.set_db_id(1000);
	user_update.set_default_tid(100);
	user_update.set_time_last_login("2012-03-03 03:03:03");
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Update_tbl_user(user_update), db->GetLastErrorString());

	user_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_user(1000, user_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (1 == user_select.size(), user_select.size());
	char buf_select[BUF_SIZE] = { 0, };
	char buf_update[BUF_SIZE] = { 0, };
	user_select[0].SerializeToArray(buf_select, BUF_SIZE);
	user_update.SerializeToArray(buf_update, BUF_SIZE);
	BOOST_REQUIRE (0 == memcmp(buf_select, buf_update, BUF_SIZE));

	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_user(1000), db->GetLastErrorString());

	user_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kNoData == db->Select_tbl_user(1000, user_select), db->GetLastErrorString());

	db->Deinitialize();
*/
}


BOOST_AUTO_TEST_CASE(tbl_friend)
{
// _SIMPLE_MODE
/*
	boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Initialize(), db->GetLastErrorString());

	s_tbl_friend friend_insert;

	nProtoHelper::message_init(friend_insert);
	friend_insert.set_uid(1000);
	friend_insert.set_uid_fiend(1001);
	friend_insert.set_nic_fiend("1001");
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_friend(friend_insert), db->GetLastErrorString());

	nProtoHelper::message_init(friend_insert);
	friend_insert.set_uid(1000);
	friend_insert.set_uid_fiend(1002);
	friend_insert.set_nic_fiend("1002");
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_friend(friend_insert), db->GetLastErrorString());

	nProtoHelper::message_init(friend_insert);
	friend_insert.set_uid(1000);
	friend_insert.set_uid_fiend(1003);
	friend_insert.set_nic_fiend("1003");
	friend_insert.set_is_blocked(true);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_friend(friend_insert), db->GetLastErrorString());

	std::vector<s_tbl_friend> friend_select;
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_friend(1000, friend_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (3 == friend_select.size(), friend_select.size());

	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_friend(friend_select[0].db_id()), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_friend(friend_select[1].db_id()), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_friend(friend_select[2].db_id()), db->GetLastErrorString());

	friend_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kNoData == db->Select_tbl_friend(1000, friend_select), db->GetLastErrorString());

	db->Deinitialize();
*/
}


BOOST_AUTO_TEST_CASE(tbl_playerbetter)
{
// _SIMPLE_MODE
/*
	boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Initialize(), db->GetLastErrorString());

	s_tbl_playerbetter playerbetter_insert;

	nProtoHelper::message_init(playerbetter_insert);
	playerbetter_insert.set_uid(1000);
	playerbetter_insert.set_pname("aaa");
	playerbetter_insert.set_is_left(false);
	playerbetter_insert.set_elo_point(1300);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_playerbetter(playerbetter_insert), db->GetLastErrorString());

	nProtoHelper::message_init(playerbetter_insert);
	playerbetter_insert.set_uid(1000);
	playerbetter_insert.set_pname("bbb");
	playerbetter_insert.set_is_left(true);
	playerbetter_insert.set_elo_point(1300);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_playerbetter(playerbetter_insert), db->GetLastErrorString());

	std::vector<s_tbl_playerbetter> playerbetter_select;
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_playerbetter(1000, playerbetter_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (2 == playerbetter_select.size(), playerbetter_select.size());

	s_tbl_playerbetter playerbetter_update = playerbetter_select[0];
	playerbetter_update.set_elo_point(1400);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Update_tbl_playerbetter(playerbetter_update), db->GetLastErrorString());

	playerbetter_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_playerbetter(1000, playerbetter_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (playerbetter_update.elo_point() == playerbetter_select[0].elo_point(), playerbetter_select[0].elo_point());

	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_playerbetter(playerbetter_select[0].db_id()), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_playerbetter(playerbetter_select[1].db_id()), db->GetLastErrorString());

	playerbetter_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kNoData == db->Select_tbl_playerbetter(1000, playerbetter_select), db->GetLastErrorString());

	db->Deinitialize();
*/
}


BOOST_AUTO_TEST_CASE(tbl_playerpitcher)
{
// _SIMPLE_MODE
/*
	boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Initialize(), db->GetLastErrorString());

	s_tbl_playerpitcher playerpitcher_insert;

	nProtoHelper::message_init(playerpitcher_insert);
	playerpitcher_insert.set_uid(1000);
	playerpitcher_insert.set_pname("aaa");
	playerpitcher_insert.set_is_left(false);
	playerpitcher_insert.set_elo_point(1300);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_playerpitcher(playerpitcher_insert), db->GetLastErrorString());

	nProtoHelper::message_init(playerpitcher_insert);
	playerpitcher_insert.set_uid(1000);
	playerpitcher_insert.set_pname("bbb");
	playerpitcher_insert.set_is_left(true);
	playerpitcher_insert.set_elo_point(1300);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_playerpitcher(playerpitcher_insert), db->GetLastErrorString());

	std::vector<s_tbl_playerpitcher> playerpitcher_select;
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_playerpitcher(1000, playerpitcher_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (2 == playerpitcher_select.size(), playerpitcher_select.size());

	s_tbl_playerpitcher playerpitcher_update = playerpitcher_select[0];
	playerpitcher_update.set_elo_point(1400);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Update_tbl_playerpitcher(playerpitcher_update), db->GetLastErrorString());

	playerpitcher_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_playerpitcher(1000, playerpitcher_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (playerpitcher_update.elo_point() == playerpitcher_select[0].elo_point(), playerpitcher_select[0].elo_point());

	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_playerpitcher(playerpitcher_select[0].db_id()), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_playerpitcher(playerpitcher_select[1].db_id()), db->GetLastErrorString());

	playerpitcher_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kNoData == db->Select_tbl_playerpitcher(1000, playerpitcher_select), db->GetLastErrorString());

	db->Deinitialize();
*/
}


BOOST_AUTO_TEST_CASE(tbl_pitcherskill)
{
// _SIMPLE_MODE
/*
	boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Initialize(), db->GetLastErrorString());

	s_tbl_pitcherskill pitcherskill_insert;

	nProtoHelper::message_init(pitcherskill_insert);
	pitcherskill_insert.set_uid(1000);
	pitcherskill_insert.set_gesture(eEGTT_VERTICAL);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_pitcherskill(pitcherskill_insert), db->GetLastErrorString());

	std::vector<s_tbl_pitcherskill> pitcherskill_select;
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_pitcherskill(1000, pitcherskill_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (1 == pitcherskill_select.size(), pitcherskill_select.size());

	s_tbl_pitcherskill pitcherskill_update = pitcherskill_select[0];
	pitcherskill_update.set_gesture(eEGTT_S_CURVE);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Update_tbl_pitcherskill(pitcherskill_update), db->GetLastErrorString());

	pitcherskill_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_pitcherskill(1000, pitcherskill_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (pitcherskill_update.gesture() == pitcherskill_select[0].gesture(), pitcherskill_select[0].gesture());

	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_pitcherskill(pitcherskill_select[0].db_id()), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_pitcherskill(pitcherskill_select[1].db_id()), db->GetLastErrorString());

	pitcherskill_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kNoData == db->Select_tbl_pitcherskill(1000, pitcherskill_select), db->GetLastErrorString());

	db->Deinitialize();
*/
}


BOOST_AUTO_TEST_CASE(tbl_team)
{
// _SIMPLE_MODE
/*
	boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Initialize(), db->GetLastErrorString());

	s_tbl_team team_insert;

	nProtoHelper::message_init(team_insert);
	team_insert.set_uid(1000);
	team_insert.set_name("aaa");
	team_insert.set_pid_better(0);
	team_insert.set_pid_pitcher(0);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_team(team_insert), db->GetLastErrorString());

	std::vector<s_tbl_team> team_select;
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_team(1000, team_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (1 == team_select.size(), team_select.size());

	s_tbl_team team_update = team_select[0];
	team_update.set_pid_better(1);
	team_update.set_pid_pitcher(1);
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Update_tbl_team(team_update), db->GetLastErrorString());

	team_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Select_tbl_team(1000, team_select), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (team_update.pid_better() == team_select[0].pid_better(), team_select[0].pid_better());
	BOOST_REQUIRE_MESSAGE (team_update.pid_pitcher() == team_select[0].pid_pitcher(), team_select[0].pid_pitcher());

	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_team(team_select[0].db_id()), db->GetLastErrorString());
	BOOST_REQUIRE_MESSAGE (baseball_db::kSuccess == db->Delete_tbl_team(team_select[1].db_id()), db->GetLastErrorString());

	team_select.clear();
	BOOST_REQUIRE_MESSAGE (baseball_db::kNoData == db->Select_tbl_team(1000, team_select), db->GetLastErrorString());

	db->Deinitialize();
*/
}


BOOST_AUTO_TEST_CASE(delete_db_file)
{
	std::string cmd("../etc/sqlite_db/drop_tables.sh ");
	cmd += s_filename;
	BOOST_REQUIRE (0 == ::system (cmd.c_str()));
}

}
