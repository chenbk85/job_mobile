/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_baseball_table_item.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_baseball_table_item_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	namespace nEXCEL {


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys__ItemBase
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys__ItemBase();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys__ItemBase


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys__ItemBase_id_t Sys__ItemBase::Get_sid()	{		return (Sys__ItemBase_id_t)m_sid;}
	void Sys__ItemBase::Set_sid(uint16 v)
	{
		m_sid=v;
	}

	acstr Sys__ItemBase::Get_name()	{		return (acstr)m_name;}
	void Sys__ItemBase::Set_name(acstr v)
	{
		if(!v){ throw _T("Sys__ItemBase::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EItemCategory Sys__ItemBase::Get_category()	{		return (EItemCategory)m_category;}
	void Sys__ItemBase::Set_category(EItemCategory v)
	{
		if(v<eBEGIN_EItemCategory || v>=eEND_EItemCategory)
		{
			jERROR(_T("Sys__ItemBase::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemCategory,eEND_EItemCategory,v);
		}
		m_category=v;
	}

	bool Sys__ItemBase::Get_upgrade_type()	{		return (bool)m_upgrade_type;}
	void Sys__ItemBase::Set_upgrade_type(bool v)
	{
		m_upgrade_type=v;
	}

	bool Sys__ItemBase::Get_is_visual()	{		return (bool)m_is_visual;}
	void Sys__ItemBase::Set_is_visual(bool v)
	{
		m_is_visual=v;
	}

	acstr Sys__ItemBase::Get_help()	{		return (acstr)m_help;}
	void Sys__ItemBase::Set_help(acstr v)
	{
		if(!v){ throw _T("Sys__ItemBase::Set_help( val = NULL )");}
		nExcelUtil::jSetter(m_help , v, 256);
	}

	EItemGradeType Sys__ItemBase::Get_grade()	{		return (EItemGradeType)m_grade;}
	void Sys__ItemBase::Set_grade(EItemGradeType v)
	{
		if(v<eBEGIN_EItemGradeType || v>=eEND_EItemGradeType)
		{
			jERROR(_T("Sys__ItemBase::Set_grade(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemGradeType,eEND_EItemGradeType,v);
		}
		m_grade=v;
	}

	EItemSubGradeType Sys__ItemBase::Get_subgrade()	{		return (EItemSubGradeType)m_subgrade;}
	void Sys__ItemBase::Set_subgrade(EItemSubGradeType v)
	{
		if(v<eBEGIN_EItemSubGradeType || v>=eEND_EItemSubGradeType)
		{
			jERROR(_T("Sys__ItemBase::Set_subgrade(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemSubGradeType,eEND_EItemSubGradeType,v);
		}
		m_subgrade=v;
	}

	int32 Sys__ItemBase::Get_player_level_min()	{		return (int32)m_player_level_min;}
	void Sys__ItemBase::Set_player_level_min(int32 v)
	{
		m_player_level_min=v;
	}

	int32 Sys__ItemBase::Get_player_level_max()	{		return (int32)m_player_level_max;}
	void Sys__ItemBase::Set_player_level_max(int32 v)
	{
		m_player_level_max=v;
	}

	EItemCategoryEquipment Sys_ItemEquip::Get_equip_category()	{		return (EItemCategoryEquipment)m_equip_category;}
	void Sys_ItemEquip::Set_equip_category(EItemCategoryEquipment v)
	{
		if(v<eBEGIN_EItemCategoryEquipment || v>=eEND_EItemCategoryEquipment)
		{
			jERROR(_T("Sys_ItemEquip::Set_equip_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemCategoryEquipment,eEND_EItemCategoryEquipment,v);
		}
		m_equip_category=v;
	}

	EItemSexType Sys_ItemEquip::Get_sex_type()	{		return (EItemSexType)m_sex_type;}
	void Sys_ItemEquip::Set_sex_type(EItemSexType v)
	{
		if(v<eBEGIN_EItemSexType || v>=eEND_EItemSexType)
		{
			jERROR(_T("Sys_ItemEquip::Set_sex_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemSexType,eEND_EItemSexType,v);
		}
		m_sex_type=v;
	}

	EPlayerType Sys_ItemEquip::Get_player_type()	{		return (EPlayerType)m_player_type;}
	void Sys_ItemEquip::Set_player_type(EPlayerType v)
	{
		if(v<eBEGIN_EPlayerType || v>=eEND_EPlayerType)
		{
			jERROR(_T("Sys_ItemEquip::Set_player_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerType,eEND_EPlayerType,v);
		}
		m_player_type=v;
	}

	EItemAbilityType Sys_ItemEquip::Get_item_batter_ability_type()	{		return (EItemAbilityType)m_item_batter_ability_type;}
	void Sys_ItemEquip::Set_item_batter_ability_type(EItemAbilityType v)
	{
		if(v<eBEGIN_EItemAbilityType || v>=eEND_EItemAbilityType)
		{
			jERROR(_T("Sys_ItemEquip::Set_item_batter_ability_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemAbilityType,eEND_EItemAbilityType,v);
		}
		m_item_batter_ability_type=v;
	}

	EItemAbilityType Sys_ItemEquip::Get_item_pitcher_ability_type()	{		return (EItemAbilityType)m_item_pitcher_ability_type;}
	void Sys_ItemEquip::Set_item_pitcher_ability_type(EItemAbilityType v)
	{
		if(v<eBEGIN_EItemAbilityType || v>=eEND_EItemAbilityType)
		{
			jERROR(_T("Sys_ItemEquip::Set_item_pitcher_ability_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemAbilityType,eEND_EItemAbilityType,v);
		}
		m_item_pitcher_ability_type=v;
	}

	EItemUpgradeResult Sys_ItemStuff::Get_upgradable_item_type()	{		return (EItemUpgradeResult)m_upgradable_item_type;}
	void Sys_ItemStuff::Set_upgradable_item_type(EItemUpgradeResult v)
	{
		if(v<eBEGIN_EItemUpgradeResult || v>=eEND_EItemUpgradeResult)
		{
			jERROR(_T("Sys_ItemStuff::Set_upgradable_item_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemUpgradeResult,eEND_EItemUpgradeResult,v);
		}
		m_upgradable_item_type=v;
	}

	EPlayerType Sys_ItemConsume::Get_player_type()	{		return (EPlayerType)m_player_type;}
	void Sys_ItemConsume::Set_player_type(EPlayerType v)
	{
		if(v<eBEGIN_EPlayerType || v>=eEND_EPlayerType)
		{
			jERROR(_T("Sys_ItemConsume::Set_player_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EPlayerType,eEND_EPlayerType,v);
		}
		m_player_type=v;
	}

	EConsumeItemEffect Sys_ItemConsume::Get_consume_item_effect()	{		return (EConsumeItemEffect)m_consume_item_effect;}
	void Sys_ItemConsume::Set_consume_item_effect(EConsumeItemEffect v)
	{
		if(v<eBEGIN_EConsumeItemEffect || v>=eEND_EConsumeItemEffect)
		{
			jERROR(_T("Sys_ItemConsume::Set_consume_item_effect(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EConsumeItemEffect,eEND_EConsumeItemEffect,v);
		}
		m_consume_item_effect=v;
	}

	EItemAbilityType Sys_ItemConsume::Get_Item_Ability_Type()	{		return (EItemAbilityType)m_Item_Ability_Type;}
	void Sys_ItemConsume::Set_Item_Ability_Type(EItemAbilityType v)
	{
		if(v<eBEGIN_EItemAbilityType || v>=eEND_EItemAbilityType)
		{
			jERROR(_T("Sys_ItemConsume::Set_Item_Ability_Type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemAbilityType,eEND_EItemAbilityType,v);
		}
		m_Item_Ability_Type=v;
	}

	int16 Sys_ItemConsume::Get_consume_item_effect_value()	{		return (int16)m_consume_item_effect_value;}
	void Sys_ItemConsume::Set_consume_item_effect_value(int16 v)
	{
		m_consume_item_effect_value=v;
	}

	int16 Sys_ItemConsume::Get_gameplay_effect_repeat()	{		return (int16)m_gameplay_effect_repeat;}
	void Sys_ItemConsume::Set_gameplay_effect_repeat(int16 v)
	{
		m_gameplay_effect_repeat=v;
	}

	int16 Sys_ItemConsume::Get_gameplay_effect_time()	{		return (int16)m_gameplay_effect_time;}
	void Sys_ItemConsume::Set_gameplay_effect_time(int16 v)
	{
		m_gameplay_effect_time=v;
	}

	bool Sys_ItemConsume::Get_consume_item_overlap()	{		return (bool)m_consume_item_overlap;}
	void Sys_ItemConsume::Set_consume_item_overlap(bool v)
	{
		m_consume_item_overlap=v;
	}

	int16 Sys_ItemConsume::Get_use_count()	{		return (int16)m_use_count;}
	void Sys_ItemConsume::Set_use_count(int16 v)
	{
		m_use_count=v;
	}

	bool Sys_ItemConsume::Get_is_bonus()	{		return (bool)m_is_bonus;}
	void Sys_ItemConsume::Set_is_bonus(bool v)
	{
		m_is_bonus=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_baseball_table_item_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys__ItemBase g_Sys__ItemBase;


tcstr Sys__ItemBase::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
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
	Set_category(FromString(out[index++],m_category) );
	FromString(&m_upgrade_type,out[index++]);
	FromString(&m_is_visual,out[index++]);
	Set_help(nExcelUtil_StringConverter(out[index++]).getA());
	Set_grade(FromString(out[index++],m_grade) );
	Set_subgrade(FromString(out[index++],m_subgrade) );
	Set_player_level_min(FromString(out[index++],m_player_level_min) );
	Set_player_level_max(FromString(out[index++],m_player_level_max) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_ItemEquip g_Sys_ItemEquip;


tcstr Sys_ItemEquip::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys__ItemBase::ReadCSV(iRecord ,out,index,false);
	Set_equip_category(FromString(out[index++],m_equip_category) );
	Set_sex_type(FromString(out[index++],m_sex_type) );
	Set_player_type(FromString(out[index++],m_player_type) );
	Set_item_batter_ability_type(FromString(out[index++],m_item_batter_ability_type) );
	Set_item_pitcher_ability_type(FromString(out[index++],m_item_pitcher_ability_type) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_ItemStuff g_Sys_ItemStuff;


tcstr Sys_ItemStuff::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys__ItemBase::ReadCSV(iRecord ,out,index,false);
	Set_upgradable_item_type(FromString(out[index++],m_upgradable_item_type) );
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_ItemConsume g_Sys_ItemConsume;


tcstr Sys_ItemConsume::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys__ItemBase::ReadCSV(iRecord ,out,index,false);
	Set_player_type(FromString(out[index++],m_player_type) );
	Set_consume_item_effect(FromString(out[index++],m_consume_item_effect) );
	Set_Item_Ability_Type(FromString(out[index++],m_Item_Ability_Type) );
	Set_consume_item_effect_value(FromString(out[index++],m_consume_item_effect_value) );
	Set_gameplay_effect_repeat(FromString(out[index++],m_gameplay_effect_repeat) );
	Set_gameplay_effect_time(FromString(out[index++],m_gameplay_effect_time) );
	FromString(&m_consume_item_overlap,out[index++]);
	Set_use_count(FromString(out[index++],m_use_count) );
	FromString(&m_is_bonus,out[index++]);
	return szKEY;
}

void Sys__ItemBase::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_ItemEquip::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_ItemStuff::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_ItemConsume::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys__ItemBase>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_ItemEquip>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_ItemStuff>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_ItemConsume>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_baseball_table_item)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys__ItemBase>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys__ItemBase*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys__ItemBase*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys__ItemBase*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys__ItemBase)
			for_each_nEXCEL_Sys__ItemBase_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys__ItemBase)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys__ItemBase>* p = &g_Sys__ItemBase;
				jSQ_g_var(p , g_Sys__ItemBase);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_ItemEquip>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_ItemEquip*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_ItemEquip*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_ItemEquip*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_ItemEquip)
			for_each_nEXCEL_Sys_ItemEquip_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys__ItemBase,"Sys__ItemBase*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_ItemEquip)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_ItemEquip>* p = &g_Sys_ItemEquip;
				jSQ_g_var(p , g_Sys_ItemEquip);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_ItemStuff>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_ItemStuff*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_ItemStuff*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_ItemStuff*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_ItemStuff)
			for_each_nEXCEL_Sys_ItemStuff_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys__ItemBase,"Sys__ItemBase*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_ItemStuff)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_ItemStuff>* p = &g_Sys_ItemStuff;
				jSQ_g_var(p , g_Sys_ItemStuff);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_ItemConsume>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_ItemConsume*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_ItemConsume*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_ItemConsume*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_ItemConsume)
			for_each_nEXCEL_Sys_ItemConsume_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys__ItemBase,"Sys__ItemBase*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_ItemConsume)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_ItemConsume>* p = &g_Sys_ItemConsume;
				jSQ_g_var(p , g_Sys_ItemConsume);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

