#include "../stdafx.h" 
#include <stdlib.h> 
#include <boost/scoped_ptr.hpp> 

#include <boost/test/unit_test.hpp> 
#include "../baseball_db.h" 
#include "../baseball_db_interface.h" 
#include "../baseball_db_sqlite.h" 

namespace baseball_db_shop_test
{

static const char* s_filename = "/tmp/baseball_test.db";

BOOST_AUTO_TEST_CASE(create_db_file)
{
	std::string cmd("../etc/sqlite_db/create_tables.sh ");
	cmd += s_filename;
	cmd += " ../etc/sqlite_db";
	BOOST_REQUIRE (0 == ::system (cmd.c_str()));
}


BOOST_AUTO_TEST_CASE(bug_game_money_single_item)
{
// _SIMPLE_MODE
/*
	const int default_game_money = 1000000;
	const int shop_id = 10;
	const int package_shop_id = 260;

	Sys_Shop* shop = jCSV(Sys_Shop).Index(shop_id);
	BOOST_CHECK_MESSAGE (NULL != shop, "can't find shop item. id : " << shop_id);
	Sys_Shop* package_shop = jCSV(Sys_Shop).Index(package_shop_id);
	BOOST_CHECK_MESSAGE (NULL != package_shop, "can't find shop item. id : " << package_shop_id);
	boost::scoped_ptr<baseball_db::DbInterface> db(new baseball_db::SqliteDb(s_filename));

	BOOST_CHECK_MESSAGE (baseball_db::kSuccess == db->Initialize(), "db initialize fail, " << db->GetLastErrorString());

	s_tbl_user user_insert;
	user_insert.set_db_id(1000);
	user_insert.set_uname("hahah");
	user_insert.set_default_tid(50);
	user_insert.set_game_money(default_game_money);
	user_insert.set_time_last_login("2999-11-11 11:11:11");
	user_insert.set_time_last_logout("2999-11-11 11:11:11");
	BOOST_CHECK_MESSAGE (baseball_db::kSuccess == db->Insert_tbl_user(user_insert), "Inser user fail : " << db->GetLastErrorString());

	baseball_db::BuyGameMoneyItem_result_info result;
	BOOST_CHECK_MESSAGE (baseball_db::kSuccess == db->BuyGameMoneyItem(result, 1000, shop_id, ""), "Buy Item fail : " << db->GetLastErrorString());
	BOOST_CHECK (result.item.size() == 1);

	std::vector<s_tbl_user> user_select;
	BOOST_CHECK_MESSAGE (baseball_db::kSuccess == db->Select_tbl_user(1000, user_select), "Select user fail " << db->GetLastErrorString());
	BOOST_CHECK (1 == user_select.size());
	BOOST_CHECK_MESSAGE (user_select[0].game_money() == default_game_money - shop->Get_price_money(), 
			"Game money not match, before:" << default_game_money << ", use:" << shop->Get_price_money() << ", after:" << user_select[0].game_money());
	BOOST_TEST_MESSAGE ("Game money, before:" << default_game_money << ", use:" << shop->Get_price_money() << ", after:" << user_select[0].game_money());

	baseball_db::BuyGameMoneyItem_result_info package_result;
	BOOST_CHECK_MESSAGE (baseball_db::kShopWrongPayment == db->BuyGameMoneyItem(package_result, 1000, package_shop_id, ""), "Buy Package Item fail : " << db->GetLastErrorString());

	std::vector<s_tbl_item> item_select;
	BOOST_CHECK_MESSAGE (baseball_db::kSuccess == db->Select_tbl_item(1000, item_select), "Select item fail " << db->GetLastErrorString());
	BOOST_CHECK (1 == item_select.size());
	BOOST_CHECK_MESSAGE (item_select[0].sid() == shop->Get_item_index(), "Item id is not match");

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
