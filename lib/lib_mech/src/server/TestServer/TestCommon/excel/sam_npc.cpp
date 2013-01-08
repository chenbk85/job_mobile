/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "sam_npc.h"



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

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST)
		for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nTESTSERVER_sam_npc_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

#endif //jNOT_USE_SQ_BIND_CODE


for_each_nTESTSERVER_sam_npc_ENUM(jEXCEL_SQ_DECLARE_ENUM_TYPE);
namespace nMech {
	namespace nTESTSERVER {

jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EMobRank[] = 
{
	{ 4 , 0, 0},
	#ifdef jEXCEL_ENUM_STRING_CPP_CODE
		for_each_nTESTSERVER_EMobRank_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)
	#endif // jEXCEL_ENUM_STRING_CPP_CODE
};

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Monster
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Monster();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_Monster


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	Sys_Monster_id_t Sys_Monster::Get_msid()	{		return (Sys_Monster_id_t)m_msid;}
	void Sys_Monster::Set_msid(uint16 v)
	{
		m_msid=v;
	}

	tcstr Sys_Monster::Get_name()	{		return (tcstr)m_name;}
	void Sys_Monster::Set_name(tcstr v)
	{
		if(!v){ throw _T("Sys_Monster::Set_name( val = NULL )");}
		nExcelUtil::jSetter(m_name , v, 32);
	}

	EMobRank Sys_Monster::Get_rank()	{		return (EMobRank)m_rank;}
	void Sys_Monster::Set_rank(EMobRank v)
	{
		if(v<eBEGIN_EMobRank || v>=eEND_EMobRank)
		{
			jERROR(_T("Sys_Monster::Set_rank(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EMobRank,eEND_EMobRank,v);
		}
		m_rank=v;
	}

	int32 Sys_Monster::Get_level()	{		return (int32)m_level;}
	void Sys_Monster::Set_level(int32 v)
	{
		m_level=v;
	}

	int32 Sys_Monster::Get_rewardExp()	{		return (int32)m_rewardExp;}
	void Sys_Monster::Set_rewardExp(int32 v)
	{
		m_rewardExp=v;
	}

	int32 Sys_Monster::Get_hp_max()	{		return (int32)m_hp_max;}
	void Sys_Monster::Set_hp_max(int32 v)
	{
		m_hp_max=v;
	}

	int32 Sys_Monster::Get_hp_regen()	{		return (int32)m_hp_regen;}
	void Sys_Monster::Set_hp_regen(int32 v)
	{
		m_hp_regen=v;
	}

	float Sys_Monster::Get_aggro_distance()	{		return (float)m_aggro_distance;}
	void Sys_Monster::Set_aggro_distance(float v)
	{
		m_aggro_distance=v;
	}

	float Sys_Monster::Get_attack_distance()	{		return (float)m_attack_distance;}
	void Sys_Monster::Set_attack_distance(float v)
	{
		m_attack_distance=v;
	}

	float Sys_Monster::Get_approach_distance()	{		return (float)m_approach_distance;}
	void Sys_Monster::Set_approach_distance(float v)
	{
		m_approach_distance=v;
	}

	float Sys_Monster::Get_hit_chance()	{		return (float)m_hit_chance;}
	void Sys_Monster::Set_hit_chance(float v)
	{
		m_hit_chance=v;
	}

	float Sys_Monster::Get_avoid_chance()	{		return (float)m_avoid_chance;}
	void Sys_Monster::Set_avoid_chance(float v)
	{
		m_avoid_chance=v;
	}

	float Sys_Monster::Get_move_speed()	{		return (float)m_move_speed;}
	void Sys_Monster::Set_move_speed(float v)
	{
		m_move_speed=v;
	}

	int32 Sys_Monster::Get_aerial_type()	{		return (int32)m_aerial_type;}
	void Sys_Monster::Set_aerial_type(int32 v)
	{
		m_aerial_type=v;
	}

	int32 Sys_Monster::Get_skill1()	{		return (int32)m_skill1;}
	void Sys_Monster::Set_skill1(int32 v)
	{
		m_skill1=v;
	}

	int32 Sys_Monster::Get_skill2()	{		return (int32)m_skill2;}
	void Sys_Monster::Set_skill2(int32 v)
	{
		m_skill2=v;
	}

	int32 Sys_Monster::Get_skill3()	{		return (int32)m_skill3;}
	void Sys_Monster::Set_skill3(int32 v)
	{
		m_skill3=v;
	}

	int32 Sys_Monster::Get_skill4()	{		return (int32)m_skill4;}
	void Sys_Monster::Set_skill4(int32 v)
	{
		m_skill4=v;
	}

	int32 Sys_Monster::Get_skill5()	{		return (int32)m_skill5;}
	void Sys_Monster::Set_skill5(int32 v)
	{
		m_skill5=v;
	}

	float Sys_Monster::Get_skill6()	{		return (float)m_skill6;}
	void Sys_Monster::Set_skill6(float v)
	{
		m_skill6=v;
	}

	float Sys_Monster::Get_skill7()	{		return (float)m_skill7;}
	void Sys_Monster::Set_skill7(float v)
	{
		m_skill7=v;
	}

	float Sys_Monster::Get_skill8()	{		return (float)m_skill8;}
	void Sys_Monster::Set_skill8(float v)
	{
		m_skill8=v;
	}

	float Sys_Monster::Get_skill9()	{		return (float)m_skill9;}
	void Sys_Monster::Set_skill9(float v)
	{
		m_skill9=v;
	}

	float Sys_Monster::Get_skill10()	{		return (float)m_skill10;}
	void Sys_Monster::Set_skill10(float v)
	{
		m_skill10=v;
	}

	int32 Sys_Monster::Get_physic_atk()	{		return (int32)m_physic_atk;}
	void Sys_Monster::Set_physic_atk(int32 v)
	{
		m_physic_atk=v;
	}

	int32 Sys_Monster::Get_magic_atk()	{		return (int32)m_magic_atk;}
	void Sys_Monster::Set_magic_atk(int32 v)
	{
		m_magic_atk=v;
	}

	tcstr Sys_Monster::Get_iconname()	{		return (tcstr)m_iconname;}
	void Sys_Monster::Set_iconname(tcstr v)
	{
		if(!v){ throw _T("Sys_Monster::Set_iconname( val = NULL )");}
		nExcelUtil::jSetter(m_iconname , v, 32);
	}

	tcstr Sys_Monster::Get_dropname()	{		return (tcstr)m_dropname;}
	void Sys_Monster::Set_dropname(tcstr v)
	{
		if(!v){ throw _T("Sys_Monster::Set_dropname( val = NULL )");}
		nExcelUtil::jSetter(m_dropname , v, 32);
	}

	tcstr Sys_Monster::Get_fsmname()	{		return (tcstr)m_fsmname;}
	void Sys_Monster::Set_fsmname(tcstr v)
	{
		if(!v){ throw _T("Sys_Monster::Set_fsmname( val = NULL )");}
		nExcelUtil::jSetter(m_fsmname , v, 256);
	}

	tcstr Sys_Monster::Get_deathfx()	{		return (tcstr)m_deathfx;}
	void Sys_Monster::Set_deathfx(tcstr v)
	{
		if(!v){ throw _T("Sys_Monster::Set_deathfx( val = NULL )");}
		nExcelUtil::jSetter(m_deathfx , v, 256);
	}

	tcstr Sys_Monster::Get_description()	{		return (tcstr)m_description;}
	void Sys_Monster::Set_description(tcstr v)
	{
		if(!v){ throw _T("Sys_Monster::Set_description( val = NULL )");}
		nExcelUtil::jSetter(m_description , v, 256);
	}

	tcstr Sys_Monster::Get_kfmname()	{		return (tcstr)m_kfmname;}
	void Sys_Monster::Set_kfmname(tcstr v)
	{
		if(!v){ throw _T("Sys_Monster::Set_kfmname( val = NULL )");}
		nExcelUtil::jSetter(m_kfmname , v, 256);
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_Monster g_Sys_Monster;


tcstr Sys_Monster::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	Set_msid(FromString(out[index++],m_msid) );
	Set_name(nExcelUtil_StringConverter(out[index++]).getT());
	szKEY = Get_name();
	Set_rank(FromString(out[index++],m_rank) );
	Set_level(FromString(out[index++],m_level) );
	Set_rewardExp(FromString(out[index++],m_rewardExp) );
	Set_hp_max(FromString(out[index++],m_hp_max) );
	Set_hp_regen(FromString(out[index++],m_hp_regen) );
	Set_aggro_distance(FromString(out[index++],m_aggro_distance) );
	Set_attack_distance(FromString(out[index++],m_attack_distance) );
	Set_approach_distance(FromString(out[index++],m_approach_distance) );
	Set_hit_chance(FromString(out[index++],m_hit_chance) );
	Set_avoid_chance(FromString(out[index++],m_avoid_chance) );
	Set_move_speed(FromString(out[index++],m_move_speed) );
	Set_aerial_type(FromString(out[index++],m_aerial_type) );
	Set_skill1(FromString(out[index++],m_skill1) );
	Set_skill2(FromString(out[index++],m_skill2) );
	Set_skill3(FromString(out[index++],m_skill3) );
	Set_skill4(FromString(out[index++],m_skill4) );
	Set_skill5(FromString(out[index++],m_skill5) );
	Set_skill6(FromString(out[index++],m_skill6) );
	Set_skill7(FromString(out[index++],m_skill7) );
	Set_skill8(FromString(out[index++],m_skill8) );
	Set_skill9(FromString(out[index++],m_skill9) );
	Set_skill10(FromString(out[index++],m_skill10) );
	Set_physic_atk(FromString(out[index++],m_physic_atk) );
	Set_magic_atk(FromString(out[index++],m_magic_atk) );
	Set_iconname(nExcelUtil_StringConverter(out[index++]).getT());
	Set_dropname(nExcelUtil_StringConverter(out[index++]).getT());
	Set_fsmname(nExcelUtil_StringConverter(out[index++]).getT());
	Set_deathfx(nExcelUtil_StringConverter(out[index++]).getT());
	Set_description(nExcelUtil_StringConverter(out[index++]).getT());
	Set_kfmname(nExcelUtil_StringConverter(out[index++]).getT());
	return szKEY;
}

void Sys_Monster::DebugPrint()
{	tname1024_t szBuf;

	for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nTESTSERVER 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_Monster>);

	namespace nMech { namespace nTESTSERVER
	{
		jSQ_REGIST_BIND(nMech_nTESTSERVER_sam_npc)
		{
			{
				SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();
				for_each_nTESTSERVER_sam_npc_ENUM(jEXCEL_SQ_bind_EnumField_BEGIN);
				for_each_nTESTSERVER_EMobRank_ENUM_FIELD(jEXCEL_SQ_bind_EnumField);
			}
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_Monster>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_Monster*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_Monster*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_Monster*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_Monster)
			for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_Monster)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_Monster>* p = &g_Sys_Monster;
				jSQ_g_var(p , g_Sys_Monster);
			}

		}
	} /*namespace nTESTSERVER */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

