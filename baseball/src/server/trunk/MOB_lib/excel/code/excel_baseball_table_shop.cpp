/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_shop.h"



//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.
#if 0

#ifndef jNOT_USE_SQ_BIND_CODE
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nEXCEL
	{
	}//namespace nEXCEL
}//namespace nMech
#endif //구현되어야 하는 코드 끝.

#ifndef jNOT_USE_SQ_BIND_CODE

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_shop_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

	PROTOS_ENUM_TYPE_csv(Sys_ItemEquip);
	PROTOS_ENUM_TYPE_COMPLAX_csv(vector<Sys_ItemEquip*>);

	PROTOS_ENUM_TYPE_csv(Sys_ItemConsume);
	PROTOS_ENUM_TYPE_COMPLAX_csv(vector<Sys_ItemConsume*>);

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	static tcstr ToString(IN Sys_ItemEquip_ptr v      , tname1024_t szBuf)
	{
		if(v) jt_strcpy(szBuf,v->Get_name());
		else jt_strcpy(szBuf,jS(NULL) );
		return szBuf;
	}
	namespace nEXCEL{void Excel_PostLoader_registe(Sys_ItemEquip_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp);}
	static tcstr ToString(IN Sys_ItemEquip_ptr_vec& v , tname1024_t szBuf)
	{
		tstring str;
		for(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T("NULL;"); continue;};str += v[i]->Get_name();str += _T(";");}
		jt_strncpy(szBuf,str.c_str(),1024-4);
		szBuf[1024-4]=0;
		return szBuf;
	}

	static tcstr ToString(IN Sys_ItemConsume_ptr v      , tname1024_t szBuf)
	{
		if(v) jt_strcpy(szBuf,v->Get_name());
		else jt_strcpy(szBuf,jS(NULL) );
		return szBuf;
	}
	namespace nEXCEL{void Excel_PostLoader_registe(Sys_ItemConsume_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp);}
	static tcstr ToString(IN Sys_ItemConsume_ptr_vec& v , tname1024_t szBuf)
	{
		tstring str;
		for(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T("NULL;"); continue;};str += v[i]->Get_name();str += _T(";");}
		jt_strncpy(szBuf,str.c_str(),1024-4);
		szBuf[1024-4]=0;
		return szBuf;
	}

	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_MainItemAbility
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_MainItemAbility();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_MainItemAbility


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int16 Sys_MainItemAbility::Get_sid()	{		return (int16)m_sid;}
	void Sys_MainItemAbility::Set_sid(int16 v)
	{
		m_sid=v;
	}

	EItemCategoryEquipment Sys_MainItemAbility::Get_equip_category()	{		return (EItemCategoryEquipment)m_equip_category;}
	void Sys_MainItemAbility::Set_equip_category(EItemCategoryEquipment v)
	{
		if(v<eBEGIN_EItemCategoryEquipment || v>=eEND_EItemCategoryEquipment)
		{
			jERROR(_T("Sys_MainItemAbility::Set_equip_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemCategoryEquipment,eEND_EItemCategoryEquipment,v);
		}
		m_equip_category=v;
	}

	EItemGradeType Sys_MainItemAbility::Get_grade()	{		return (EItemGradeType)m_grade;}
	void Sys_MainItemAbility::Set_grade(EItemGradeType v)
	{
		if(v<eBEGIN_EItemGradeType || v>=eEND_EItemGradeType)
		{
			jERROR(_T("Sys_MainItemAbility::Set_grade(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemGradeType,eEND_EItemGradeType,v);
		}
		m_grade=v;
	}

	EItemSubGradeType Sys_MainItemAbility::Get_subgrade()	{		return (EItemSubGradeType)m_subgrade;}
	void Sys_MainItemAbility::Set_subgrade(EItemSubGradeType v)
	{
		if(v<eBEGIN_EItemSubGradeType || v>=eEND_EItemSubGradeType)
		{
			jERROR(_T("Sys_MainItemAbility::Set_subgrade(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemSubGradeType,eEND_EItemSubGradeType,v);
		}
		m_subgrade=v;
	}

	float Sys_MainItemAbility::Get_mainitem_first_equip_level()	{		return (float)m_mainitem_first_equip_level;}
	void Sys_MainItemAbility::Set_mainitem_first_equip_level(float v)
	{
		m_mainitem_first_equip_level=v;
	}

	float Sys_MainItemAbility::Get_mainitem_possible_upgrade_level()	{		return (float)m_mainitem_possible_upgrade_level;}
	void Sys_MainItemAbility::Set_mainitem_possible_upgrade_level(float v)
	{
		m_mainitem_possible_upgrade_level=v;
	}

	float Sys_MainItemAbility::Get_mainitem_need_time()	{		return (float)m_mainitem_need_time;}
	void Sys_MainItemAbility::Set_mainitem_need_time(float v)
	{
		m_mainitem_need_time=v;
	}

	float Sys_MainItemAbility::Get_mainitem_basic_value()	{		return (float)m_mainitem_basic_value;}
	void Sys_MainItemAbility::Set_mainitem_basic_value(float v)
	{
		m_mainitem_basic_value=v;
	}

	float Sys_MainItemAbility::Get_mainitem_equip_level()	{		return (float)m_mainitem_equip_level;}
	void Sys_MainItemAbility::Set_mainitem_equip_level(float v)
	{
		m_mainitem_equip_level=v;
	}

	float Sys_MainItemAbility::Get_value_min()	{		return (float)m_value_min;}
	void Sys_MainItemAbility::Set_value_min(float v)
	{
		m_value_min=v;
	}

	float Sys_MainItemAbility::Get_value_max()	{		return (float)m_value_max;}
	void Sys_MainItemAbility::Set_value_max(float v)
	{
		m_value_max=v;
	}

	EPlayerType Sys_MainItemAbility::Get_player_type()	{		return (EPlayerType)m_player_type;}
	void Sys_MainItemAbility::Set_player_type(EPlayerType v)
	{
		if(v<eBEGIN_EPlayerType || v>=eEND_EPlayerType)
		{
			jERROR(_T("Sys_MainItemAbility::Set_player_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerType,eEND_EPlayerType,v);
		}
		m_player_type=v;
	}

	int64 Sys_MainItemAbility::Get_mainitem_upgrade_need_money()	{		return (int64)m_mainitem_upgrade_need_money;}
	void Sys_MainItemAbility::Set_mainitem_upgrade_need_money(int64 v)
	{
		m_mainitem_upgrade_need_money=v;
	}

	Sys_Package_id_t Sys_Package::Get_sid()	{		return (Sys_Package_id_t)m_sid;}
	void Sys_Package::Set_sid(uint16 v)
	{
		m_sid=v;
	}

	acstr Sys_Package::Get_name()	{		return (acstr)m_name;}
	void Sys_Package::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_Package::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EItemPriceType Sys_Package::Get_price_type()	{		return (EItemPriceType)m_price_type;}
	void Sys_Package::Set_price_type(EItemPriceType v)
	{
		if(v<eBEGIN_EItemPriceType || v>=eEND_EItemPriceType)
		{
			jERROR(_T("Sys_Package::Set_price_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemPriceType,eEND_EItemPriceType,v);
		}
		m_price_type=v;
	}

	int32 Sys_Package::Get_price_money()	{		return (int32)m_price_money;}
	void Sys_Package::Set_price_money(int32 v)
	{
		m_price_money=v;
	}

	int32 Sys_Package::Get_price_cash()	{		return (int32)m_price_cash;}
	void Sys_Package::Set_price_cash(int32 v)
	{
		m_price_cash=v;
	}

	Sys_ItemEquip_ptr_vec_ref Sys_Package::Get_equip_items1()	{			return m_equip_items1_ptr_vec;}
	void Sys_Package::Set_equip_items1(Sys_ItemEquip_ptr_vec_ref v)
	{
		m_equip_items1_ptr_vec = v;
	}

	Sys_ItemConsume_ptr_vec_ref Sys_Package::Get_consum_items1()	{			return m_consum_items1_ptr_vec;}
	void Sys_Package::Set_consum_items1(Sys_ItemConsume_ptr_vec_ref v)
	{
		m_consum_items1_ptr_vec = v;
	}

	Sys_ItemEquip_ptr_vec_ref Sys_Package::Get_equip_items2()	{			return m_equip_items2_ptr_vec;}
	void Sys_Package::Set_equip_items2(Sys_ItemEquip_ptr_vec_ref v)
	{
		m_equip_items2_ptr_vec = v;
	}

	Sys_ItemConsume_ptr_vec_ref Sys_Package::Get_consum_items2()	{			return m_consum_items2_ptr_vec;}
	void Sys_Package::Set_consum_items2(Sys_ItemConsume_ptr_vec_ref v)
	{
		m_consum_items2_ptr_vec = v;
	}

	Sys_ItemEquip_ptr_vec_ref Sys_Package::Get_equip_items3()	{			return m_equip_items3_ptr_vec;}
	void Sys_Package::Set_equip_items3(Sys_ItemEquip_ptr_vec_ref v)
	{
		m_equip_items3_ptr_vec = v;
	}

	Sys_ItemConsume_ptr_vec_ref Sys_Package::Get_consum_items3()	{			return m_consum_items3_ptr_vec;}
	void Sys_Package::Set_consum_items3(Sys_ItemConsume_ptr_vec_ref v)
	{
		m_consum_items3_ptr_vec = v;
	}

	Sys_ItemEquip_ptr_vec_ref Sys_Package::Get_equip_items4()	{			return m_equip_items4_ptr_vec;}
	void Sys_Package::Set_equip_items4(Sys_ItemEquip_ptr_vec_ref v)
	{
		m_equip_items4_ptr_vec = v;
	}

	Sys_ItemConsume_ptr_vec_ref Sys_Package::Get_consum_items4()	{			return m_consum_items4_ptr_vec;}
	void Sys_Package::Set_consum_items4(Sys_ItemConsume_ptr_vec_ref v)
	{
		m_consum_items4_ptr_vec = v;
	}

	EGiftType Sys_Package::Get_gift_type1()	{		return (EGiftType)m_gift_type1;}
	void Sys_Package::Set_gift_type1(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type1(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type1=v;
	}

	int64 Sys_Package::Get_gift_type1_value()	{		return (int64)m_gift_type1_value;}
	void Sys_Package::Set_gift_type1_value(int64 v)
	{
		m_gift_type1_value=v;
	}

	EGiftType Sys_Package::Get_gift_type2()	{		return (EGiftType)m_gift_type2;}
	void Sys_Package::Set_gift_type2(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type2(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type2=v;
	}

	int64 Sys_Package::Get_gift_type2_value()	{		return (int64)m_gift_type2_value;}
	void Sys_Package::Set_gift_type2_value(int64 v)
	{
		m_gift_type2_value=v;
	}

	EGiftType Sys_Package::Get_gift_type3()	{		return (EGiftType)m_gift_type3;}
	void Sys_Package::Set_gift_type3(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type3(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type3=v;
	}

	int64 Sys_Package::Get_gift_type3_value()	{		return (int64)m_gift_type3_value;}
	void Sys_Package::Set_gift_type3_value(int64 v)
	{
		m_gift_type3_value=v;
	}

	EGiftType Sys_Package::Get_gift_type4()	{		return (EGiftType)m_gift_type4;}
	void Sys_Package::Set_gift_type4(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type4(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type4=v;
	}

	int64 Sys_Package::Get_gift_type4_value()	{		return (int64)m_gift_type4_value;}
	void Sys_Package::Set_gift_type4_value(int64 v)
	{
		m_gift_type4_value=v;
	}

	EGiftType Sys_Package::Get_gift_type5()	{		return (EGiftType)m_gift_type5;}
	void Sys_Package::Set_gift_type5(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type5(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type5=v;
	}

	int64 Sys_Package::Get_gift_type5_value()	{		return (int64)m_gift_type5_value;}
	void Sys_Package::Set_gift_type5_value(int64 v)
	{
		m_gift_type5_value=v;
	}

	EGiftType Sys_Package::Get_gift_type6()	{		return (EGiftType)m_gift_type6;}
	void Sys_Package::Set_gift_type6(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type6(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type6=v;
	}

	int64 Sys_Package::Get_gift_type6_value()	{		return (int64)m_gift_type6_value;}
	void Sys_Package::Set_gift_type6_value(int64 v)
	{
		m_gift_type6_value=v;
	}

	EGiftType Sys_Package::Get_gift_type7()	{		return (EGiftType)m_gift_type7;}
	void Sys_Package::Set_gift_type7(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type7(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type7=v;
	}

	int64 Sys_Package::Get_gift_type7_value()	{		return (int64)m_gift_type7_value;}
	void Sys_Package::Set_gift_type7_value(int64 v)
	{
		m_gift_type7_value=v;
	}

	EGiftType Sys_Package::Get_gift_type8()	{		return (EGiftType)m_gift_type8;}
	void Sys_Package::Set_gift_type8(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type8(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type8=v;
	}

	int64 Sys_Package::Get_gift_type8_value()	{		return (int64)m_gift_type8_value;}
	void Sys_Package::Set_gift_type8_value(int64 v)
	{
		m_gift_type8_value=v;
	}

	EGiftType Sys_Package::Get_gift_type9()	{		return (EGiftType)m_gift_type9;}
	void Sys_Package::Set_gift_type9(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type9(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type9=v;
	}

	int64 Sys_Package::Get_gift_type9_value()	{		return (int64)m_gift_type9_value;}
	void Sys_Package::Set_gift_type9_value(int64 v)
	{
		m_gift_type9_value=v;
	}

	EGiftType Sys_Package::Get_gift_type10()	{		return (EGiftType)m_gift_type10;}
	void Sys_Package::Set_gift_type10(EGiftType v)
	{
		if(v<eBEGIN_EGiftType || v>=eEND_EGiftType)
		{
			jERROR(_T("Sys_Package::Set_gift_type10(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EGiftType,eEND_EGiftType,v);
		}
		m_gift_type10=v;
	}

	int64 Sys_Package::Get_gift_type10_value()	{		return (int64)m_gift_type10_value;}
	void Sys_Package::Set_gift_type10_value(int64 v)
	{
		m_gift_type10_value=v;
	}

	Sys_Shop_id_t Sys_Shop::Get_shop_id()	{		return (Sys_Shop_id_t)m_shop_id;}
	void Sys_Shop::Set_shop_id(uint16 v)
	{
		m_shop_id=v;
	}

	acstr Sys_Shop::Get_name()	{		return (acstr)m_name;}
	void Sys_Shop::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys_Shop::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EShopItemType Sys_Shop::Get_item_type()	{		return (EShopItemType)m_item_type;}
	void Sys_Shop::Set_item_type(EShopItemType v)
	{
		if(v<eBEGIN_EShopItemType || v>=eEND_EShopItemType)
		{
			jERROR(_T("Sys_Shop::Set_item_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EShopItemType,eEND_EShopItemType,v);
		}
		m_item_type=v;
	}

	int32 Sys_Shop::Get_item_index()	{		return (int32)m_item_index;}
	void Sys_Shop::Set_item_index(int32 v)
	{
		m_item_index=v;
	}

	bool Sys_Shop::Get_is_new()	{		return (bool)m_is_new;}
	void Sys_Shop::Set_is_new(bool v)
	{
		m_is_new=v;
	}

	bool Sys_Shop::Get_is_best()	{		return (bool)m_is_best;}
	void Sys_Shop::Set_is_best(bool v)
	{
		m_is_best=v;
	}

	bool Sys_Shop::Get_is_hot()	{		return (bool)m_is_hot;}
	void Sys_Shop::Set_is_hot(bool v)
	{
		m_is_hot=v;
	}

	EShopBatterSection Sys_Shop::Get_shop_batter_section()	{		return (EShopBatterSection)m_shop_batter_section;}
	void Sys_Shop::Set_shop_batter_section(EShopBatterSection v)
	{
		if(v<eBEGIN_EShopBatterSection || v>=eEND_EShopBatterSection)
		{
			jERROR(_T("Sys_Shop::Set_shop_batter_section(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EShopBatterSection,eEND_EShopBatterSection,v);
		}
		m_shop_batter_section=v;
	}

	EShopPitcherSection Sys_Shop::Get_shop_pitcher_section()	{		return (EShopPitcherSection)m_shop_pitcher_section;}
	void Sys_Shop::Set_shop_pitcher_section(EShopPitcherSection v)
	{
		if(v<eBEGIN_EShopPitcherSection || v>=eEND_EShopPitcherSection)
		{
			jERROR(_T("Sys_Shop::Set_shop_pitcher_section(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EShopPitcherSection,eEND_EShopPitcherSection,v);
		}
		m_shop_pitcher_section=v;
	}

	EShopConsumeSection Sys_Shop::Get_shop_consume_section()	{		return (EShopConsumeSection)m_shop_consume_section;}
	void Sys_Shop::Set_shop_consume_section(EShopConsumeSection v)
	{
		if(v<eBEGIN_EShopConsumeSection || v>=eEND_EShopConsumeSection)
		{
			jERROR(_T("Sys_Shop::Set_shop_consume_section(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EShopConsumeSection,eEND_EShopConsumeSection,v);
		}
		m_shop_consume_section=v;
	}

	SYSTEMTIME Sys_Shop::Get_sell_start_date()	{		return (SYSTEMTIME)m_sell_start_date;}
	void Sys_Shop::Set_sell_start_date(SYSTEMTIME v)
	{
		m_sell_start_date=v;
	}

	SYSTEMTIME Sys_Shop::Get_sell_end_date()	{		return (SYSTEMTIME)m_sell_end_date;}
	void Sys_Shop::Set_sell_end_date(SYSTEMTIME v)
	{
		m_sell_end_date=v;
	}

	int32 Sys_Shop::Get_price_money()	{		return (int32)m_price_money;}
	void Sys_Shop::Set_price_money(int32 v)
	{
		m_price_money=v;
	}

	int32 Sys_Shop::Get_price_cash()	{		return (int32)m_price_cash;}
	void Sys_Shop::Set_price_cash(int32 v)
	{
		m_price_cash=v;
	}

	EItemPriceType Sys_Shop::Get_price_type()	{		return (EItemPriceType)m_price_type;}
	void Sys_Shop::Set_price_type(EItemPriceType v)
	{
		if(v<eBEGIN_EItemPriceType || v>=eEND_EItemPriceType)
		{
			jERROR(_T("Sys_Shop::Set_price_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemPriceType,eEND_EItemPriceType,v);
		}
		m_price_type=v;
	}

	EItemSellStatus Sys_Shop::Get_sell_status()	{		return (EItemSellStatus)m_sell_status;}
	void Sys_Shop::Set_sell_status(EItemSellStatus v)
	{
		if(v<eBEGIN_EItemSellStatus || v>=eEND_EItemSellStatus)
		{
			jERROR(_T("Sys_Shop::Set_sell_status(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemSellStatus,eEND_EItemSellStatus,v);
		}
		m_sell_status=v;
	}

	int16 Sys_SubItemAbility::Get_sid()	{		return (int16)m_sid;}
	void Sys_SubItemAbility::Set_sid(int16 v)
	{
		m_sid=v;
	}

	EItemCategoryEquipment Sys_SubItemAbility::Get_equip_category()	{		return (EItemCategoryEquipment)m_equip_category;}
	void Sys_SubItemAbility::Set_equip_category(EItemCategoryEquipment v)
	{
		if(v<eBEGIN_EItemCategoryEquipment || v>=eEND_EItemCategoryEquipment)
		{
			jERROR(_T("Sys_SubItemAbility::Set_equip_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemCategoryEquipment,eEND_EItemCategoryEquipment,v);
		}
		m_equip_category=v;
	}

	EItemGradeType Sys_SubItemAbility::Get_grade()	{		return (EItemGradeType)m_grade;}
	void Sys_SubItemAbility::Set_grade(EItemGradeType v)
	{
		if(v<eBEGIN_EItemGradeType || v>=eEND_EItemGradeType)
		{
			jERROR(_T("Sys_SubItemAbility::Set_grade(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemGradeType,eEND_EItemGradeType,v);
		}
		m_grade=v;
	}

	int8 Sys_SubItemAbility::Get_subitem_first_equip_level()	{		return (int8)m_subitem_first_equip_level;}
	void Sys_SubItemAbility::Set_subitem_first_equip_level(int8 v)
	{
		m_subitem_first_equip_level=v;
	}

	int8 Sys_SubItemAbility::Get_subitem_better_ability()	{		return (int8)m_subitem_better_ability;}
	void Sys_SubItemAbility::Set_subitem_better_ability(int8 v)
	{
		m_subitem_better_ability=v;
	}

	float Sys_SubItemAbility::Get_subitem_pitcher_ability()	{		return (float)m_subitem_pitcher_ability;}
	void Sys_SubItemAbility::Set_subitem_pitcher_ability(float v)
	{
		m_subitem_pitcher_ability=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_shop_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_MainItemAbility g_Sys_MainItemAbility;


tcstr Sys_MainItemAbility::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_equip_category(FromString(out[index++],m_equip_category) );
	Set_grade(FromString(out[index++],m_grade) );
	Set_subgrade(FromString(out[index++],m_subgrade) );
	Set_mainitem_first_equip_level(FromString(out[index++],m_mainitem_first_equip_level) );
	Set_mainitem_possible_upgrade_level(FromString(out[index++],m_mainitem_possible_upgrade_level) );
	Set_mainitem_need_time(FromString(out[index++],m_mainitem_need_time) );
	Set_mainitem_basic_value(FromString(out[index++],m_mainitem_basic_value) );
	Set_mainitem_equip_level(FromString(out[index++],m_mainitem_equip_level) );
	Set_value_min(FromString(out[index++],m_value_min) );
	Set_value_max(FromString(out[index++],m_value_max) );
	Set_player_type(FromString(out[index++],m_player_type) );
	Set_mainitem_upgrade_need_money(FromString(out[index++],m_mainitem_upgrade_need_money) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Package g_Sys_Package;


tcstr Sys_Package::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_price_type(FromString(out[index++],m_price_type) );
	Set_price_money(FromString(out[index++],m_price_money) );
	Set_price_cash(FromString(out[index++],m_price_cash) );
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::equip_items1"),(int32)iRecord);
	Excel_PostLoader_registe(&m_equip_items1_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::consum_items1"),(int32)iRecord);
	Excel_PostLoader_registe(&m_consum_items1_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::equip_items2"),(int32)iRecord);
	Excel_PostLoader_registe(&m_equip_items2_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::consum_items2"),(int32)iRecord);
	Excel_PostLoader_registe(&m_consum_items2_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::equip_items3"),(int32)iRecord);
	Excel_PostLoader_registe(&m_equip_items3_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::consum_items3"),(int32)iRecord);
	Excel_PostLoader_registe(&m_consum_items3_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::equip_items4"),(int32)iRecord);
	Excel_PostLoader_registe(&m_equip_items4_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_baseball_table_shop)Sys_Package::consum_items4"),(int32)iRecord);
	Excel_PostLoader_registe(&m_consum_items4_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	Set_gift_type1(FromString(out[index++],m_gift_type1) );
	Set_gift_type1_value(FromString(out[index++],m_gift_type1_value) );
	Set_gift_type2(FromString(out[index++],m_gift_type2) );
	Set_gift_type2_value(FromString(out[index++],m_gift_type2_value) );
	Set_gift_type3(FromString(out[index++],m_gift_type3) );
	Set_gift_type3_value(FromString(out[index++],m_gift_type3_value) );
	Set_gift_type4(FromString(out[index++],m_gift_type4) );
	Set_gift_type4_value(FromString(out[index++],m_gift_type4_value) );
	Set_gift_type5(FromString(out[index++],m_gift_type5) );
	Set_gift_type5_value(FromString(out[index++],m_gift_type5_value) );
	Set_gift_type6(FromString(out[index++],m_gift_type6) );
	Set_gift_type6_value(FromString(out[index++],m_gift_type6_value) );
	Set_gift_type7(FromString(out[index++],m_gift_type7) );
	Set_gift_type7_value(FromString(out[index++],m_gift_type7_value) );
	Set_gift_type8(FromString(out[index++],m_gift_type8) );
	Set_gift_type8_value(FromString(out[index++],m_gift_type8_value) );
	Set_gift_type9(FromString(out[index++],m_gift_type9) );
	Set_gift_type9_value(FromString(out[index++],m_gift_type9_value) );
	Set_gift_type10(FromString(out[index++],m_gift_type10) );
	Set_gift_type10_value(FromString(out[index++],m_gift_type10_value) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Shop g_Sys_Shop;


tcstr Sys_Shop::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_shop_id(FromString(out[index++],m_shop_id) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getA());
	szKEY = Get_name();
	Set_item_type(FromString(out[index++],m_item_type) );
	Set_item_index(FromString(out[index++],m_item_index) );
	FromString(&m_is_new,out[index++]);
	FromString(&m_is_best,out[index++]);
	FromString(&m_is_hot,out[index++]);
	Set_shop_batter_section(FromString(out[index++],m_shop_batter_section) );
	Set_shop_pitcher_section(FromString(out[index++],m_shop_pitcher_section) );
	Set_shop_consume_section(FromString(out[index++],m_shop_consume_section) );
	FromString(&m_sell_start_date,out[index++]);
	FromString(&m_sell_end_date,out[index++]);
	Set_price_money(FromString(out[index++],m_price_money) );
	Set_price_cash(FromString(out[index++],m_price_cash) );
	Set_price_type(FromString(out[index++],m_price_type) );
	Set_sell_status(FromString(out[index++],m_sell_status) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_SubItemAbility g_Sys_SubItemAbility;


tcstr Sys_SubItemAbility::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_sid(FromString(out[index++],m_sid) );
	Set_equip_category(FromString(out[index++],m_equip_category) );
	Set_grade(FromString(out[index++],m_grade) );
	Set_subitem_first_equip_level(FromString(out[index++],m_subitem_first_equip_level) );
	Set_subitem_better_ability(FromString(out[index++],m_subitem_better_ability) );
	Set_subitem_pitcher_ability(FromString(out[index++],m_subitem_pitcher_ability) );
	return szKEY;
}

void Sys_MainItemAbility::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Package::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Package_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Shop::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_Shop_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_SubItemAbility::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_MainItemAbility>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Package>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Shop>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_SubItemAbility>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_shop)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_MainItemAbility>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_MainItemAbility*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_MainItemAbility*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_MainItemAbility*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_MainItemAbility)
			for_each_nEXCEL_Sys_MainItemAbility_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_MainItemAbility)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_MainItemAbility>* p = &g_Sys_MainItemAbility;
				jSQ_g_var(p , g_Sys_MainItemAbility);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Package>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Package*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Package*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Package*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Package)
			for_each_nEXCEL_Sys_Package_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Package)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Package>* p = &g_Sys_Package;
				jSQ_g_var(p , g_Sys_Package);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Shop>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Shop*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Shop*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Shop*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Shop)
			for_each_nEXCEL_Sys_Shop_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Shop)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Shop>* p = &g_Sys_Shop;
				jSQ_g_var(p , g_Sys_Shop);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_SubItemAbility>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_SubItemAbility*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_SubItemAbility*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_SubItemAbility*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_SubItemAbility)
			for_each_nEXCEL_Sys_SubItemAbility_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_SubItemAbility)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_SubItemAbility>* p = &g_Sys_SubItemAbility;
				jSQ_g_var(p , g_Sys_SubItemAbility);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

