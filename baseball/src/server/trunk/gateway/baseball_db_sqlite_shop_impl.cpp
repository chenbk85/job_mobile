#include "stdafx.h" 

#include <vector> 
#include <algorithm> 
#include <boost/lexical_cast.hpp> 
#include "baseball_db.h" 
#include "baseball_db_sqlite.h" 
#include "baseball_db_sqlite_query_impl.h" 
#include "common/header/jDefine_enum.h" 

namespace baseball_db
{


Error SqliteDb::BuyGameMoneyItem(OUT BuyGameMoneyItem_result_info& result
								 ,IN Tbl_User_id_t uid
								 ,IN Sys_Shop_id_t shop_sid
								 , IN cstr etc_info)
{
	
// _SIMPLE_MODE

	Error ret = kSuccess;
/*
	// uid 로 사용자 정보 읽어오기
	std::vector<s_tbl_user> user_list;
	ret = Select_tbl_user(uid, user_list);
	jRETURN_ret(ret, kSuccess ==ret);
	jRETURN_ret(kNoData,!user_list.empty());

	s_tbl_user& user = user_list.front();

	// csv 에서 상품 정보 읽어오기
	Sys_Shop* pSys_Shop = jCSV(Sys_Shop).Index(shop_sid);
	jRETURN_ret(kShopNoProduct,pSys_Shop);

	// 게임머니로 파는 상품이 아니면
	jRETURN_ret(kShopWrongPayment,eIPT_MONEY == pSys_Shop->Get_price_type() );

	// 잔여 게임 머니 체크
	jRETURN_ret(kShopNotEnoughMoney,pSys_Shop->Get_price_money() <= user.game_money());

	Sys_ItemBase_id_t item_sid=0;
	EItemCategory eItemCategory;
	s_tbl_item item;

	switch(pSys_Shop->Get_item_type())
	{
	case eESIT_Sys_Package:
		{
			s_tbl_package package;
			Sys_Package* pSys_Package = jCSV(Sys_Package).Index(pSys_Shop->Get_item_index());
			jRETURN_ret(kUnknown,pSys_Package);
			Sys_Package_id_t package_sid = pSys_Shop->Get_item_index();
			jRETURN_ret(kShopInvalidPackage,_FillPackageInfo(uid, package_sid, etc_info, &package));
			ret = Insert_tbl_package(package);
			jRETURN_ret(ret, kSuccess == ret);
			result.package.push_back(package);
		}
		break;

	case eESIT_Sys_ItemEquip:
		{
			eItemCategory = eIC_EQUIP;
			Sys_ItemEquip* pItem = jCSV(Sys_ItemEquip).Index(pSys_Shop->Get_item_index());
			jRETURN_ret(kUnknown,pItem);
			item_sid = pSys_Shop->Get_item_index();

			jRETURN_ret(kShopInvalidItem,_FillItemInfo(uid, item_sid, eItemCategory, etc_info, &item));
			ret = Insert_tbl_item(item);
			jRETURN_ret(ret, kSuccess == ret);
			result.item.push_back(item);
		}
		break;
	case eESIT_Sys_ItemStuff:
		{
			eItemCategory = eIC_STUFF;
			Sys_ItemStuff* pItem = jCSV(Sys_ItemStuff).Index(pSys_Shop->Get_item_index());
			jRETURN_ret(kUnknown,pItem);
			item_sid = pSys_Shop->Get_item_index();

			jRETURN_ret(kShopInvalidItem,_FillItemInfo(uid, item_sid, eItemCategory, etc_info, &item));
			ret = Insert_tbl_item(item);
			jRETURN_ret(ret, kSuccess == ret);
			result.item.push_back(item);
		}
		break;
	case eESIT_Sys_ItemConsume:
		{
			eItemCategory = eIC_CONSUME;
			Sys_ItemConsume* pItem = jCSV(Sys_ItemConsume).Index(pSys_Shop->Get_item_index());
			jRETURN_ret(kUnknown,pItem);
			item_sid = pSys_Shop->Get_item_index();

			jRETURN_ret(kShopInvalidItem,_FillItemInfo(uid, item_sid, eItemCategory, etc_info, &item));
			ret = Insert_tbl_item(item);
			jRETURN_ret(ret, kSuccess == ret);
			result.item.push_back(item);
		}
		break;
	case eESIT_Sys_PlayerSkillSticker:
		{
			//jTODO
			jRETURN_ret(kUnknown,0);
		}
		break;
	default:
		{
			jRETURN_ret(kUnknown,0);
		}
	}

	// 게임 머니 차감
	user.set_game_money(user.game_money() - pSys_Shop->Get_price_money());
	jRETURN_ret(kDbFail, kSuccess == Update_tbl_user(user));
	result.game_money = user.game_money() - pSys_Shop->Get_price_money();
*/
	return ret;
}

/*
bool SqliteDb::_FillPackageInfo(Tbl_User_id_t uid, Sys_Package_id_t package_sid, 
							 	const std::string& etc_info, s_tbl_package* package) const
{
	nProtoHelper::message_init(*package);

	package->set_uid(uid);
	package->set_sid_package(package_sid);
	package->set_etc_info(etc_info);
	package->set_date_insert(time_to_string(boost::posix_time::microsec_clock::local_time()));
	package->set_date_update(time_to_string(boost::posix_time::microsec_clock::local_time()));
	package->set_state(eIS_NORMAL);
	
	return true;
}

bool SqliteDb::_FillItemInfo(Tbl_User_id_t uid, Sys__ItemBase_id_t item_id, EItemCategory category,
							 const std::string& etc_info, s_tbl_item* item) const
{
	nProtoHelper::message_init(*item);

	switch (category)
	{
	case eIC_EQUIP:
		{
			Sys_ItemEquip* item_info = jCSV(Sys_ItemEquip).Index(item_id);
			if (NULL == item_info)	return false;
			item->set_upgrade_level(to_grade_string(item_info->Get_grade()));
		}
		break;
	case eIC_STUFF:
		{
			Sys_ItemStuff* item_info = jCSV(Sys_ItemStuff).Index(item_id);
			if (NULL == item_info)	return false;
			item->set_upgrade_level(to_grade_string(item_info->Get_grade()));
		}
		break;
	case eIC_CONSUME:
		{
			Sys_ItemConsume* item_info = jCSV(Sys_ItemConsume).Index(item_id);
			if (NULL == item_info) return false;
			item->set_upgrade_level(to_grade_string(item_info->Get_grade()));
		}
		break;
	default:
		{
			return false;
		}
	}

	item->set_uid(uid);
	item->set_sid(item_id);
	item->set_category(category);
	item->set_etc_info(etc_info);
	item->set_date_insert(time_to_string(boost::posix_time::microsec_clock::local_time()));
	item->set_date_update(time_to_string(boost::posix_time::microsec_clock::local_time()));
	item->set_state(eIS_NORMAL);
	item->set_use_count(1);
	
	return true;
}
*/
}
