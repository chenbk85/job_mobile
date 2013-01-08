/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "aq_table.h"



//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.
#if 0

#ifndef jNOT_USE_SQ_BIND_CODE
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nTESTSERVER
	{
	}//namespace nTESTSERVER
}//namespace nMech
#endif //구현되어야 하는 코드 끝.

#ifndef jNOT_USE_SQ_BIND_CODE

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST)
		for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nTESTSERVER_aq_table_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nTESTSERVER_aq_table_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nTESTSERVER {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAttackType[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EAttackType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAvatarParts[] = 
{
	{ 24 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EAvatarParts_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAvatarSubclass[] = 
{
	{ 10 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EAvatarSubclass_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EDamageType[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EDamageType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemBind[] = 
{
	{ 3 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EItemBind_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemClass[] = 
{
	{ 8 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EItemClass_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemGrade[] = 
{
	{ 7 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EItemGrade_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemQuality[] = 
{
	{ 6 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EItemQuality_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSubclass[] = 
{
	{ 33 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EItemSubclass_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EMechanic[] = 
{
	{ 8 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EMechanic_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EModifier[] = 
{
	{ 29 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EModifier_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EModValueType[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EModValueType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ESkillCastType[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_ESkillCastType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ESkillType[] = 
{
	{ 2 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_ESkillType_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};
jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETarget[] = 
{
	{ 5 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_ETarget_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Avatar
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Avatar();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Avatar


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_Avatar_id_t Sys_Avatar::Get_asid()	{		return (Sys_Avatar_id_t)m_asid;}
	void Sys_Avatar::Set_asid(uint16 v)
	{
		m_asid=v;
	}

	tcstr Sys_Avatar::Get_name()	{		return (tcstr)m_name;}
	void Sys_Avatar::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Avatar::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EAvatarClass Sys_Avatar::Get_baseclass()	{		return (EAvatarClass)m_baseclass;}
	void Sys_Avatar::Set_baseclass(EAvatarClass v)
	{
		if(v<eBEGIN_EAvatarClass || v>=eEND_EAvatarClass)
		{
			jERROR(_T("Sys_Avatar::Set_baseclass(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EAvatarClass,eEND_EAvatarClass,v);
		}
		m_baseclass=v;
	}

	EAvatarSubclass Sys_Avatar::Get_subclass()	{		return (EAvatarSubclass)m_subclass;}
	void Sys_Avatar::Set_subclass(EAvatarSubclass v)
	{
		if(v<eBEGIN_EAvatarSubclass || v>=eEND_EAvatarSubclass)
		{
			jERROR(_T("Sys_Avatar::Set_subclass(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EAvatarSubclass,eEND_EAvatarSubclass,v);
		}
		m_subclass=v;
	}

	int32 Sys_Avatar::Get_hp_max()	{		return (int32)m_hp_max;}
	void Sys_Avatar::Set_hp_max(int32 v)
	{
		if(v<0) v = 0;
		m_hp_max=v;
	}

	int32 Sys_Avatar::Get_mp_max()	{		return (int32)m_mp_max;}
	void Sys_Avatar::Set_mp_max(int32 v)
	{
		if(v<0) v = 0;
		m_mp_max=v;
	}

	int32 Sys_Avatar::Get_hp_regen()	{		return (int32)m_hp_regen;}
	void Sys_Avatar::Set_hp_regen(int32 v)
	{
		m_hp_regen=v;
	}

	int32 Sys_Avatar::Get_mp_regen()	{		return (int32)m_mp_regen;}
	void Sys_Avatar::Set_mp_regen(int32 v)
	{
		m_mp_regen=v;
	}

	int32 Sys_Avatar::Get_st_str()	{		return (int32)m_st_str;}
	void Sys_Avatar::Set_st_str(int32 v)
	{
		if(v<0) v = 0;
		m_st_str=v;
	}

	int32 Sys_Avatar::Get_st_sta()	{		return (int32)m_st_sta;}
	void Sys_Avatar::Set_st_sta(int32 v)
	{
		if(v<0) v = 0;
		m_st_sta=v;
	}

	int32 Sys_Avatar::Get_st_agi()	{		return (int32)m_st_agi;}
	void Sys_Avatar::Set_st_agi(int32 v)
	{
		if(v<0) v = 0;
		m_st_agi=v;
	}

	int32 Sys_Avatar::Get_st_int()	{		return (int32)m_st_int;}
	void Sys_Avatar::Set_st_int(int32 v)
	{
		if(v<0) v = 0;
		m_st_int=v;
	}

	int32 Sys_Avatar::Get_st_men()	{		return (int32)m_st_men;}
	void Sys_Avatar::Set_st_men(int32 v)
	{
		if(v<0) v = 0;
		m_st_men=v;
	}

	int32 Sys_Avatar::Get_reation_aerial_type()	{		return (int32)m_reation_aerial_type;}
	void Sys_Avatar::Set_reation_aerial_type(int32 v)
	{
		m_reation_aerial_type=v;
	}

	int32 Sys_Avatar::Get_reation_blow_type()	{		return (int32)m_reation_blow_type;}
	void Sys_Avatar::Set_reation_blow_type(int32 v)
	{
		m_reation_blow_type=v;
	}

	int32 Sys_Avatar::Get_reation_push_type()	{		return (int32)m_reation_push_type;}
	void Sys_Avatar::Set_reation_push_type(int32 v)
	{
		m_reation_push_type=v;
	}

	int32 Sys_Avatar::Get_physic_atk()	{		return (int32)m_physic_atk;}
	void Sys_Avatar::Set_physic_atk(int32 v)
	{
		m_physic_atk=v;
	}

	int32 Sys_Avatar::Get_physic_def()	{		return (int32)m_physic_def;}
	void Sys_Avatar::Set_physic_def(int32 v)
	{
		m_physic_def=v;
	}

	float Sys_Avatar::Get_physic_crit()	{		return (float)m_physic_crit;}
	void Sys_Avatar::Set_physic_crit(float v)
	{
		m_physic_crit=v;
	}

	int32 Sys_Avatar::Get_magic_atk()	{		return (int32)m_magic_atk;}
	void Sys_Avatar::Set_magic_atk(int32 v)
	{
		m_magic_atk=v;
	}

	int32 Sys_Avatar::Get_magic_def()	{		return (int32)m_magic_def;}
	void Sys_Avatar::Set_magic_def(int32 v)
	{
		m_magic_def=v;
	}

	float Sys_Avatar::Get_magic_crit()	{		return (float)m_magic_crit;}
	void Sys_Avatar::Set_magic_crit(float v)
	{
		m_magic_crit=v;
	}

	float Sys_Avatar::Get_attack_speed()	{		return (float)m_attack_speed;}
	void Sys_Avatar::Set_attack_speed(float v)
	{
		m_attack_speed=v;
	}

	float Sys_Avatar::Get_casting_speed()	{		return (float)m_casting_speed;}
	void Sys_Avatar::Set_casting_speed(float v)
	{
		m_casting_speed=v;
	}

	float Sys_Avatar::Get_move_speed()	{		return (float)m_move_speed;}
	void Sys_Avatar::Set_move_speed(float v)
	{
		m_move_speed=v;
	}

	float Sys_Avatar::Get_dash_speed()	{		return (float)m_dash_speed;}
	void Sys_Avatar::Set_dash_speed(float v)
	{
		m_dash_speed=v;
	}

	float Sys_Avatar::Get_hit_chance()	{		return (float)m_hit_chance;}
	void Sys_Avatar::Set_hit_chance(float v)
	{
		m_hit_chance=v;
	}

	float Sys_Avatar::Get_avoid_chance()	{		return (float)m_avoid_chance;}
	void Sys_Avatar::Set_avoid_chance(float v)
	{
		m_avoid_chance=v;
	}

	float Sys_Avatar::Get_jumpFactor()	{		return (float)m_jumpFactor;}
	void Sys_Avatar::Set_jumpFactor(float v)
	{
		m_jumpFactor=v;
	}

	int32 Sys_Avatar::Get_resist_fire()	{		return (int32)m_resist_fire;}
	void Sys_Avatar::Set_resist_fire(int32 v)
	{
		m_resist_fire=v;
	}

	int32 Sys_Avatar::Get_resist_water()	{		return (int32)m_resist_water;}
	void Sys_Avatar::Set_resist_water(int32 v)
	{
		m_resist_water=v;
	}

	int32 Sys_Avatar::Get_resist_light()	{		return (int32)m_resist_light;}
	void Sys_Avatar::Set_resist_light(int32 v)
	{
		m_resist_light=v;
	}

	int32 Sys_Avatar::Get_resist_dark()	{		return (int32)m_resist_dark;}
	void Sys_Avatar::Set_resist_dark(int32 v)
	{
		m_resist_dark=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo1()	{		return (Sys_Skill_id_t)m_combo1;}
	void Sys_Avatar::Set_combo1(uint16 v)
	{
		m_combo1=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo2()	{		return (Sys_Skill_id_t)m_combo2;}
	void Sys_Avatar::Set_combo2(uint16 v)
	{
		m_combo2=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo3()	{		return (Sys_Skill_id_t)m_combo3;}
	void Sys_Avatar::Set_combo3(uint16 v)
	{
		m_combo3=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo4()	{		return (Sys_Skill_id_t)m_combo4;}
	void Sys_Avatar::Set_combo4(uint16 v)
	{
		m_combo4=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo5()	{		return (Sys_Skill_id_t)m_combo5;}
	void Sys_Avatar::Set_combo5(uint16 v)
	{
		m_combo5=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_jump_atk()	{		return (Sys_Skill_id_t)m_jump_atk;}
	void Sys_Avatar::Set_jump_atk(uint16 v)
	{
		m_jump_atk=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_dash_atk()	{		return (Sys_Skill_id_t)m_dash_atk;}
	void Sys_Avatar::Set_dash_atk(uint16 v)
	{
		m_dash_atk=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo1_2h()	{		return (Sys_Skill_id_t)m_combo1_2h;}
	void Sys_Avatar::Set_combo1_2h(uint16 v)
	{
		m_combo1_2h=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo2_2h()	{		return (Sys_Skill_id_t)m_combo2_2h;}
	void Sys_Avatar::Set_combo2_2h(uint16 v)
	{
		m_combo2_2h=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo3_3h()	{		return (Sys_Skill_id_t)m_combo3_3h;}
	void Sys_Avatar::Set_combo3_3h(uint16 v)
	{
		m_combo3_3h=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo4_2h()	{		return (Sys_Skill_id_t)m_combo4_2h;}
	void Sys_Avatar::Set_combo4_2h(uint16 v)
	{
		m_combo4_2h=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_combo5_2h()	{		return (Sys_Skill_id_t)m_combo5_2h;}
	void Sys_Avatar::Set_combo5_2h(uint16 v)
	{
		m_combo5_2h=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_jump_atk_2h()	{		return (Sys_Skill_id_t)m_jump_atk_2h;}
	void Sys_Avatar::Set_jump_atk_2h(uint16 v)
	{
		m_jump_atk_2h=v;
	}

	Sys_Skill_id_t Sys_Avatar::Get_dash_atk_2h()	{		return (Sys_Skill_id_t)m_dash_atk_2h;}
	void Sys_Avatar::Set_dash_atk_2h(uint16 v)
	{
		m_dash_atk_2h=v;
	}

	tcstr Sys_Avatar::Get_xmlname()	{		return (tcstr)m_xmlname;}
	void Sys_Avatar::Set_xmlname(tcstr v)
	{
		if(!v){ throw _T("Sys_Avatar::Set_xmlname( val = NULL )");}
		nExcelUtil::jSetter(m_xmlname , v, 32);
	}

	tcstr Sys_Avatar::Get_fkmname()	{		return (tcstr)m_fkmname;}
	void Sys_Avatar::Set_fkmname(tcstr v)
	{
		if(!v){ throw _T("Sys_Avatar::Set_fkmname( val = NULL )");}
		nExcelUtil::jSetter(m_fkmname , v, 256);
	}

	Sys_Item_id_t Sys_Item::Get_isid()	{		return (Sys_Item_id_t)m_isid;}
	void Sys_Item::Set_isid(uint16 v)
	{
		m_isid=v;
	}

	tcstr Sys_Item::Get_name()	{		return (tcstr)m_name;}
	void Sys_Item::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Item::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EItemClass Sys_Item::Get_category()	{		return (EItemClass)m_category;}
	void Sys_Item::Set_category(EItemClass v)
	{
		if(v<eBEGIN_EItemClass || v>=eEND_EItemClass)
		{
			jERROR(_T("Sys_Item::Set_category(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemClass,eEND_EItemClass,v);
		}
		m_category=v;
	}

	EItemSubclass Sys_Item::Get_subcategory()	{		return (EItemSubclass)m_subcategory;}
	void Sys_Item::Set_subcategory(EItemSubclass v)
	{
		if(v<eBEGIN_EItemSubclass || v>=eEND_EItemSubclass)
		{
			jERROR(_T("Sys_Item::Set_subcategory(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemSubclass,eEND_EItemSubclass,v);
		}
		m_subcategory=v;
	}

	EItemGrade Sys_Item::Get_grade()	{		return (EItemGrade)m_grade;}
	void Sys_Item::Set_grade(EItemGrade v)
	{
		if(v<eBEGIN_EItemGrade || v>=eEND_EItemGrade)
		{
			jERROR(_T("Sys_Item::Set_grade(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemGrade,eEND_EItemGrade,v);
		}
		m_grade=v;
	}

	EItemQuality Sys_Item::Get_quality()	{		return (EItemQuality)m_quality;}
	void Sys_Item::Set_quality(EItemQuality v)
	{
		if(v<eBEGIN_EItemQuality || v>=eEND_EItemQuality)
		{
			jERROR(_T("Sys_Item::Set_quality(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemQuality,eEND_EItemQuality,v);
		}
		m_quality=v;
	}

	EItemBind Sys_Item::Get_bind_type()	{		return (EItemBind)m_bind_type;}
	void Sys_Item::Set_bind_type(EItemBind v)
	{
		if(v<eBEGIN_EItemBind || v>=eEND_EItemBind)
		{
			jERROR(_T("Sys_Item::Set_bind_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EItemBind,eEND_EItemBind,v);
		}
		m_bind_type=v;
	}

	EAvatarParts Sys_Item::Get_part()	{		return (EAvatarParts)m_part;}
	void Sys_Item::Set_part(EAvatarParts v)
	{
		if(v<eBEGIN_EAvatarParts || v>=eEND_EAvatarParts)
		{
			jERROR(_T("Sys_Item::Set_part(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EAvatarParts,eEND_EAvatarParts,v);
		}
		m_part=v;
	}

	EAvatarClass Sys_Item::Get_reqClass()	{		return (EAvatarClass)m_reqClass;}
	void Sys_Item::Set_reqClass(EAvatarClass v)
	{
		if(v<eBEGIN_EAvatarClass || v>=eEND_EAvatarClass)
		{
			jERROR(_T("Sys_Item::Set_reqClass(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EAvatarClass,eEND_EAvatarClass,v);
		}
		m_reqClass=v;
	}

	EAvatarSubclass Sys_Item::Get_reqSubclass()	{		return (EAvatarSubclass)m_reqSubclass;}
	void Sys_Item::Set_reqSubclass(EAvatarSubclass v)
	{
		if(v<eBEGIN_EAvatarSubclass || v>=eEND_EAvatarSubclass)
		{
			jERROR(_T("Sys_Item::Set_reqSubclass(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EAvatarSubclass,eEND_EAvatarSubclass,v);
		}
		m_reqSubclass=v;
	}

	int32 Sys_Item::Get_maxCount()	{		return (int32)m_maxCount;}
	void Sys_Item::Set_maxCount(int32 v)
	{
		m_maxCount=v;
	}

	int32 Sys_Item::Get_stackCount()	{		return (int32)m_stackCount;}
	void Sys_Item::Set_stackCount(int32 v)
	{
		if(v>99) v = (int32)99;
		if(v<1) v = 1;
		m_stackCount=v;
	}

	int32 Sys_Item::Get_buyPrice()	{		return (int32)m_buyPrice;}
	void Sys_Item::Set_buyPrice(int32 v)
	{
		m_buyPrice=v;
	}

	int32 Sys_Item::Get_sellPrice()	{		return (int32)m_sellPrice;}
	void Sys_Item::Set_sellPrice(int32 v)
	{
		m_sellPrice=v;
	}

	int32 Sys_Item::Get_repairPrice()	{		return (int32)m_repairPrice;}
	void Sys_Item::Set_repairPrice(int32 v)
	{
		m_repairPrice=v;
	}

	int32 Sys_Item::Get_reqCash()	{		return (int32)m_reqCash;}
	void Sys_Item::Set_reqCash(int32 v)
	{
		m_reqCash=v;
	}

	int32 Sys_Item::Get_reqLevel()	{		return (int32)m_reqLevel;}
	void Sys_Item::Set_reqLevel(int32 v)
	{
		if(v>60) v = (int32)60;
		if(v<1) v = 1;
		m_reqLevel=v;
	}

	int32 Sys_Item::Get_durability()	{		return (int32)m_durability;}
	void Sys_Item::Set_durability(int32 v)
	{
		m_durability=v;
	}

	int32 Sys_Item::Get_activeTime()	{		return (int32)m_activeTime;}
	void Sys_Item::Set_activeTime(int32 v)
	{
		m_activeTime=v;
	}

	int32 Sys_Item::Get_trigger_skill()	{		return (int32)m_trigger_skill;}
	void Sys_Item::Set_trigger_skill(int32 v)
	{
		m_trigger_skill=v;
	}

	tcstr Sys_Item::Get_iconname()	{		return (tcstr)m_iconname;}
	void Sys_Item::Set_iconname(tcstr v)
	{
		if(!v){ throw _T("Sys_Item::Set_iconname( val = NULL )");}
		nExcelUtil::jSetter(m_iconname , v, 256);
	}

	tcstr Sys_Item::Get_delegate()	{		return (tcstr)m_delegate;}
	void Sys_Item::Set_delegate(tcstr v)
	{
		if(!v){ throw _T("Sys_Item::Set_delegate( val = NULL )");}
		nExcelUtil::jSetter(m_delegate , v, 128);
	}

	tcstr Sys_Item::Get_filename()	{		return (tcstr)m_filename;}
	void Sys_Item::Set_filename(tcstr v)
	{
		if(!v){ throw _T("Sys_Item::Set_filename( val = NULL )");}
		nExcelUtil::jSetter(m_filename , v, 256);
	}

	tcstr Sys_Item::Get_xmlname()	{		return (tcstr)m_xmlname;}
	void Sys_Item::Set_xmlname(tcstr v)
	{
		if(!v){ throw _T("Sys_Item::Set_xmlname( val = NULL )");}
		nExcelUtil::jSetter(m_xmlname , v, 32);
	}

	tcstr Sys_Item::Get_description()	{		return (tcstr)m_description;}
	void Sys_Item::Set_description(tcstr v)
	{
		if(!v){ throw _T("Sys_Item::Set_description( val = NULL )");}
		nExcelUtil::jSetter(m_description , v, 32);
	}

	Sys_Skill_id_t Sys_Skill::Get_ssid()	{		return (Sys_Skill_id_t)m_ssid;}
	void Sys_Skill::Set_ssid(uint16 v)
	{
		m_ssid=v;
	}

	tcstr Sys_Skill::Get_name()	{		return (tcstr)m_name;}
	void Sys_Skill::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	int32 Sys_Skill::Get_level()	{		return (int32)m_level;}
	void Sys_Skill::Set_level(int32 v)
	{
		m_level=v;
	}

	int32 Sys_Skill::Get_maxLevel()	{		return (int32)m_maxLevel;}
	void Sys_Skill::Set_maxLevel(int32 v)
	{
		m_maxLevel=v;
	}

	int32 Sys_Skill::Get_reqLevel()	{		return (int32)m_reqLevel;}
	void Sys_Skill::Set_reqLevel(int32 v)
	{
		m_reqLevel=v;
	}

	int32 Sys_Skill::Get_reqGold()	{		return (int32)m_reqGold;}
	void Sys_Skill::Set_reqGold(int32 v)
	{
		m_reqGold=v;
	}

	int32 Sys_Skill::Get_reqSP()	{		return (int32)m_reqSP;}
	void Sys_Skill::Set_reqSP(int32 v)
	{
		m_reqSP=v;
	}

	Sys_Item_id_t Sys_Skill::Get_reqItem()	{		return (Sys_Item_id_t)m_reqItem;}
	void Sys_Skill::Set_reqItem(uint16 v)
	{
		m_reqItem=v;
	}

	int32 Sys_Skill::Get_costHP()	{		return (int32)m_costHP;}
	void Sys_Skill::Set_costHP(int32 v)
	{
		m_costHP=v;
	}

	int32 Sys_Skill::Get_costMP()	{		return (int32)m_costMP;}
	void Sys_Skill::Set_costMP(int32 v)
	{
		m_costMP=v;
	}

	Sys_Item_id_t Sys_Skill::Get_costItem()	{		return (Sys_Item_id_t)m_costItem;}
	void Sys_Skill::Set_costItem(uint16 v)
	{
		m_costItem=v;
	}

	ESkillType Sys_Skill::Get_type()	{		return (ESkillType)m_type;}
	void Sys_Skill::Set_type(ESkillType v)
	{
		if(v<eBEGIN_ESkillType || v>=eEND_ESkillType)
		{
			jERROR(_T("Sys_Skill::Set_type(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ESkillType,eEND_ESkillType,v);
		}
		m_type=v;
	}

	ESkillCastType Sys_Skill::Get_castingType()	{		return (ESkillCastType)m_castingType;}
	void Sys_Skill::Set_castingType(ESkillCastType v)
	{
		if(v<eBEGIN_ESkillCastType || v>=eEND_ESkillCastType)
		{
			jERROR(_T("Sys_Skill::Set_castingType(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ESkillCastType,eEND_ESkillCastType,v);
		}
		m_castingType=v;
	}

	int32 Sys_Skill::Get_castingAnim()	{		return (int32)m_castingAnim;}
	void Sys_Skill::Set_castingAnim(int32 v)
	{
		m_castingAnim=v;
	}

	float Sys_Skill::Get_castingTime()	{		return (float)m_castingTime;}
	void Sys_Skill::Set_castingTime(float v)
	{
		m_castingTime=v;
	}

	float Sys_Skill::Get_chargingTime()	{		return (float)m_chargingTime;}
	void Sys_Skill::Set_chargingTime(float v)
	{
		m_chargingTime=v;
	}

	float Sys_Skill::Get_chargingMutiplier()	{		return (float)m_chargingMutiplier;}
	void Sys_Skill::Set_chargingMutiplier(float v)
	{
		m_chargingMutiplier=v;
	}

	float Sys_Skill::Get_coolTime()	{		return (float)m_coolTime;}
	void Sys_Skill::Set_coolTime(float v)
	{
		m_coolTime=v;
	}

	int32 Sys_Skill::Get_skillAnim()	{		return (int32)m_skillAnim;}
	void Sys_Skill::Set_skillAnim(int32 v)
	{
		m_skillAnim=v;
	}

	ETarget Sys_Skill::Get_target()	{		return (ETarget)m_target;}
	void Sys_Skill::Set_target(ETarget v)
	{
		if(v<eBEGIN_ETarget || v>=eEND_ETarget)
		{
			jERROR(_T("Sys_Skill::Set_target(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_ETarget,eEND_ETarget,v);
		}
		m_target=v;
	}

	EAttackType Sys_Skill::Get_attackType()	{		return (EAttackType)m_attackType;}
	void Sys_Skill::Set_attackType(EAttackType v)
	{
		if(v<eBEGIN_EAttackType || v>=eEND_EAttackType)
		{
			jERROR(_T("Sys_Skill::Set_attackType(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EAttackType,eEND_EAttackType,v);
		}
		m_attackType=v;
	}

	float Sys_Skill::Get_attackRate()	{		return (float)m_attackRate;}
	void Sys_Skill::Set_attackRate(float v)
	{
		m_attackRate=v;
	}

	float Sys_Skill::Get_hit_chance()	{		return (float)m_hit_chance;}
	void Sys_Skill::Set_hit_chance(float v)
	{
		m_hit_chance=v;
	}

	float Sys_Skill::Get_critical_chance()	{		return (float)m_critical_chance;}
	void Sys_Skill::Set_critical_chance(float v)
	{
		m_critical_chance=v;
	}

	float Sys_Skill::Get_effectRange()	{		return (float)m_effectRange;}
	void Sys_Skill::Set_effectRange(float v)
	{
		m_effectRange=v;
	}

	float Sys_Skill::Get_effectDuration()	{		return (float)m_effectDuration;}
	void Sys_Skill::Set_effectDuration(float v)
	{
		m_effectDuration=v;
	}

	tcstr Sys_Skill::Get_effect()	{		return (tcstr)m_effect;}
	void Sys_Skill::Set_effect(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_effect( val = NULL )");}
		nExcelUtil::jSetter(m_effect , v, 32);
	}

	tcstr Sys_Skill::Get_castingFX()	{		return (tcstr)m_castingFX;}
	void Sys_Skill::Set_castingFX(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_castingFX( val = NULL )");}
		nExcelUtil::jSetter(m_castingFX , v, 32);
	}

	tcstr Sys_Skill::Get_skillFX()	{		return (tcstr)m_skillFX;}
	void Sys_Skill::Set_skillFX(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_skillFX( val = NULL )");}
		nExcelUtil::jSetter(m_skillFX , v, 32);
	}

	tcstr Sys_Skill::Get_chargingFX()	{		return (tcstr)m_chargingFX;}
	void Sys_Skill::Set_chargingFX(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_chargingFX( val = NULL )");}
		nExcelUtil::jSetter(m_chargingFX , v, 32);
	}

	tcstr Sys_Skill::Get_collisionFX()	{		return (tcstr)m_collisionFX;}
	void Sys_Skill::Set_collisionFX(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_collisionFX( val = NULL )");}
		nExcelUtil::jSetter(m_collisionFX , v, 32);
	}

	tcstr Sys_Skill::Get_targetFX()	{		return (tcstr)m_targetFX;}
	void Sys_Skill::Set_targetFX(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_targetFX( val = NULL )");}
		nExcelUtil::jSetter(m_targetFX , v, 32);
	}

	tcstr Sys_Skill::Get_description()	{		return (tcstr)m_description;}
	void Sys_Skill::Set_description(tcstr v)
	{
		if(!v){ throw _T("Sys_Skill::Set_description( val = NULL )");}
		nExcelUtil::jSetter(m_description , v, 256);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Avatar g_Sys_Avatar;


tcstr Sys_Avatar::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_asid(FromString(out[index++],m_asid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_baseclass(FromString(out[index++],m_baseclass) );
	Set_subclass(FromString(out[index++],m_subclass) );
	Set_hp_max(FromString(out[index++],m_hp_max) );
	Set_mp_max(FromString(out[index++],m_mp_max) );
	Set_hp_regen(FromString(out[index++],m_hp_regen) );
	Set_mp_regen(FromString(out[index++],m_mp_regen) );
	Set_st_str(FromString(out[index++],m_st_str) );
	Set_st_sta(FromString(out[index++],m_st_sta) );
	Set_st_agi(FromString(out[index++],m_st_agi) );
	Set_st_int(FromString(out[index++],m_st_int) );
	Set_st_men(FromString(out[index++],m_st_men) );
	Set_reation_aerial_type(FromString(out[index++],m_reation_aerial_type) );
	Set_reation_blow_type(FromString(out[index++],m_reation_blow_type) );
	Set_reation_push_type(FromString(out[index++],m_reation_push_type) );
	Set_physic_atk(FromString(out[index++],m_physic_atk) );
	Set_physic_def(FromString(out[index++],m_physic_def) );
	Set_physic_crit(FromString(out[index++],m_physic_crit) );
	Set_magic_atk(FromString(out[index++],m_magic_atk) );
	Set_magic_def(FromString(out[index++],m_magic_def) );
	Set_magic_crit(FromString(out[index++],m_magic_crit) );
	Set_attack_speed(FromString(out[index++],m_attack_speed) );
	Set_casting_speed(FromString(out[index++],m_casting_speed) );
	Set_move_speed(FromString(out[index++],m_move_speed) );
	Set_dash_speed(FromString(out[index++],m_dash_speed) );
	Set_hit_chance(FromString(out[index++],m_hit_chance) );
	Set_avoid_chance(FromString(out[index++],m_avoid_chance) );
	Set_jumpFactor(FromString(out[index++],m_jumpFactor) );
	Set_resist_fire(FromString(out[index++],m_resist_fire) );
	Set_resist_water(FromString(out[index++],m_resist_water) );
	Set_resist_light(FromString(out[index++],m_resist_light) );
	Set_resist_dark(FromString(out[index++],m_resist_dark) );
	Set_combo1(FromString(out[index++],m_combo1) );
	Set_combo2(FromString(out[index++],m_combo2) );
	Set_combo3(FromString(out[index++],m_combo3) );
	Set_combo4(FromString(out[index++],m_combo4) );
	Set_combo5(FromString(out[index++],m_combo5) );
	Set_jump_atk(FromString(out[index++],m_jump_atk) );
	Set_dash_atk(FromString(out[index++],m_dash_atk) );
	Set_combo1_2h(FromString(out[index++],m_combo1_2h) );
	Set_combo2_2h(FromString(out[index++],m_combo2_2h) );
	Set_combo3_3h(FromString(out[index++],m_combo3_3h) );
	Set_combo4_2h(FromString(out[index++],m_combo4_2h) );
	Set_combo5_2h(FromString(out[index++],m_combo5_2h) );
	Set_jump_atk_2h(FromString(out[index++],m_jump_atk_2h) );
	Set_dash_atk_2h(FromString(out[index++],m_dash_atk_2h) );
	Set_xmlname(nExcelUtil_StringConverter(out[index++]).getT());
	Set_fkmname(nExcelUtil_StringConverter(out[index++]).getT());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Item g_Sys_Item;


tcstr Sys_Item::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_isid(FromString(out[index++],m_isid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_category(FromString(out[index++],m_category) );
	Set_subcategory(FromString(out[index++],m_subcategory) );
	Set_grade(FromString(out[index++],m_grade) );
	Set_quality(FromString(out[index++],m_quality) );
	Set_bind_type(FromString(out[index++],m_bind_type) );
	Set_part(FromString(out[index++],m_part) );
	Set_reqClass(FromString(out[index++],m_reqClass) );
	Set_reqSubclass(FromString(out[index++],m_reqSubclass) );
	Set_maxCount(FromString(out[index++],m_maxCount) );
	Set_stackCount(FromString(out[index++],m_stackCount) );
	Set_buyPrice(FromString(out[index++],m_buyPrice) );
	Set_sellPrice(FromString(out[index++],m_sellPrice) );
	Set_repairPrice(FromString(out[index++],m_repairPrice) );
	Set_reqCash(FromString(out[index++],m_reqCash) );
	Set_reqLevel(FromString(out[index++],m_reqLevel) );
	Set_durability(FromString(out[index++],m_durability) );
	Set_activeTime(FromString(out[index++],m_activeTime) );
	Set_trigger_skill(FromString(out[index++],m_trigger_skill) );
	Set_iconname(nExcelUtil_StringConverter(out[index++]).getT());
	Set_delegate(nExcelUtil_StringConverter(out[index++]).getT());
	Set_filename(nExcelUtil_StringConverter(out[index++]).getT());
	Set_xmlname(nExcelUtil_StringConverter(out[index++]).getT());
	Set_description(nExcelUtil_StringConverter(out[index++]).getT());
	return szKEY;
}

jEXCEL_LIB_API CSV_Sys_Skill g_Sys_Skill;


tcstr Sys_Skill::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_ssid(FromString(out[index++],m_ssid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_level(FromString(out[index++],m_level) );
	Set_maxLevel(FromString(out[index++],m_maxLevel) );
	Set_reqLevel(FromString(out[index++],m_reqLevel) );
	Set_reqGold(FromString(out[index++],m_reqGold) );
	Set_reqSP(FromString(out[index++],m_reqSP) );
	Set_reqItem(FromString(out[index++],m_reqItem) );
	Set_costHP(FromString(out[index++],m_costHP) );
	Set_costMP(FromString(out[index++],m_costMP) );
	Set_costItem(FromString(out[index++],m_costItem) );
	Set_type(FromString(out[index++],m_type) );
	Set_castingType(FromString(out[index++],m_castingType) );
	Set_castingAnim(FromString(out[index++],m_castingAnim) );
	Set_castingTime(FromString(out[index++],m_castingTime) );
	Set_chargingTime(FromString(out[index++],m_chargingTime) );
	Set_chargingMutiplier(FromString(out[index++],m_chargingMutiplier) );
	Set_coolTime(FromString(out[index++],m_coolTime) );
	Set_skillAnim(FromString(out[index++],m_skillAnim) );
	Set_target(FromString(out[index++],m_target) );
	Set_attackType(FromString(out[index++],m_attackType) );
	Set_attackRate(FromString(out[index++],m_attackRate) );
	Set_hit_chance(FromString(out[index++],m_hit_chance) );
	Set_critical_chance(FromString(out[index++],m_critical_chance) );
	Set_effectRange(FromString(out[index++],m_effectRange) );
	Set_effectDuration(FromString(out[index++],m_effectDuration) );
	Set_effect(nExcelUtil_StringConverter(out[index++]).getT());
	Set_castingFX(nExcelUtil_StringConverter(out[index++]).getT());
	Set_skillFX(nExcelUtil_StringConverter(out[index++]).getT());
	Set_chargingFX(nExcelUtil_StringConverter(out[index++]).getT());
	Set_collisionFX(nExcelUtil_StringConverter(out[index++]).getT());
	Set_targetFX(nExcelUtil_StringConverter(out[index++]).getT());
	Set_description(nExcelUtil_StringConverter(out[index++]).getT());
	return szKEY;
}

void Sys_Avatar::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Item::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}

void Sys_Skill::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nTESTSERVER 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Avatar>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Item>);

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Skill>);

	namespace nMech { namespace nTESTSERVER
	{
		jSQ_REGIST_BIND(nMech_nTESTSERVER_aq_table)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nTESTSERVER_aq_table_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nTESTSERVER_EAttackType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EAvatarParts_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EAvatarSubclass_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EDamageType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EItemBind_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EItemClass_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EItemGrade_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EItemQuality_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EItemSubclass_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EMechanic_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EModifier_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_EModValueType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_ESkillCastType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_ESkillType_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
				for_each_nTESTSERVER_ETarget_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Avatar>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Avatar*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Avatar*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Avatar*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Avatar)
			for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Avatar)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Avatar>* p = &g_Sys_Avatar;
				jSQ_g_var(p , g_Sys_Avatar);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Item>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Item*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Item*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Item*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Item)
			for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Item)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Item>* p = &g_Sys_Item;
				jSQ_g_var(p , g_Sys_Item);
			}

			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Skill>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Skill*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Skill*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Skill*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Skill)
			for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Skill)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Skill>* p = &g_Sys_Skill;
				jSQ_g_var(p , g_Sys_Skill);
			}

		}
	} /*namespace nTESTSERVER */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

