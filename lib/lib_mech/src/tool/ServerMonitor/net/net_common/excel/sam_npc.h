/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_sam_npc_
#define __namespace_nTESTSERVER___filename_sam_npc_

#include "table_const_sam_npc.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nTESTSERVER_sam_npc_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EMobRank,�������,nMech,nTESTSERVER)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nTESTSERVER_EMobRank_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MOB_RANK_NORMAL			,0,�Ϲ���,nMech,nTESTSERVER,EMobRank)\
		ENUM_FIELD(MOB_RANK_REINFORCE			,1,��ȭ��,nMech,nTESTSERVER,EMobRank)\
		ENUM_FIELD(MOB_RANK_SEMIBOSS			,2,�غ�����,nMech,nTESTSERVER,EMobRank)\
		ENUM_FIELD(MOB_RANK_BOSS			,3,������,nMech,nTESTSERVER,EMobRank)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Monster,�������,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_Monster �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD(FIELD)\
		FIELD(msid                   ,ID                 ,Sys_Monster_id_t             ,0 , Sys_Monster_id_t , uint16 , u16)\
		FIELD(name                   ,�̸�                 ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(rank                   ,���                 ,EMobRank                     ,2 , EMobRank , EMobRank , e)\
		FIELD(level                  ,����                 ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(rewardExp              ,�������ġ              ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(hp_max                 ,HP                 ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(hp_regen               ,HP ȸ���ӵ�            ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(aggro_distance         ,��׷� ����             ,float                        ,7 , float , float , f)\
		FIELD(attack_distance        ,���� ����              ,float                        ,8 , float , float , f)\
		FIELD(approach_distance      ,�̵� ����              ,float                        ,9 , float , float , f)\
		FIELD(hit_chance             ,���߷�                ,float                        ,10 , float , float , f)\
		FIELD(avoid_chance           ,ȸ�Ƿ�                ,float                        ,11 , float , float , f)\
		FIELD(move_speed             ,�̵��ӵ�               ,float                        ,12 , float , float , f)\
		FIELD(aerial_type            ,Aerial Ÿ��          ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(skill1                 ,��ų1                ,skill_sid_t                  ,14 , int32 , int32 , i32)\
		FIELD(skill2                 ,��ų2                ,skill_sid_t                  ,15 , int32 , int32 , i32)\
		FIELD(skill3                 ,��ų3                ,skill_sid_t                  ,16 , int32 , int32 , i32)\
		FIELD(skill4                 ,��ų4                ,skill_sid_t                  ,17 , int32 , int32 , i32)\
		FIELD(skill5                 ,��ų5                ,skill_sid_t                  ,18 , int32 , int32 , i32)\
		FIELD(skill6                 ,��ų6                ,float                        ,19 , float , float , f)\
		FIELD(skill7                 ,��ų7                ,float                        ,20 , float , float , f)\
		FIELD(skill8                 ,��ų8                ,float                        ,21 , float , float , f)\
		FIELD(skill9                 ,��ų9                ,float                        ,22 , float , float , f)\
		FIELD(skill10                ,��ų10               ,float                        ,23 , float , float , f)\
		FIELD(physic_atk             ,�������ݷ�              ,int32                        ,24 , int32 , int32 , i32)\
		FIELD(magic_atk              ,�������ݷ�              ,int32                        ,25 , int32 , int32 , i32)\
		FIELD(iconname               ,������ �̸�             ,tname32_t                    ,26 , tcstr , tcstr , t32)\
		FIELD(dropname               ,���������Ʈ �̸�          ,tname32_t                    ,27 , tcstr , tcstr , t32)\
		FIELD(fsmname                ,AI Filename        ,tname256_t                   ,28 , tcstr , tcstr , t256)\
		FIELD(deathfx                ,�״� �ִϸ��̼�           ,tname256_t                   ,29 , tcstr , tcstr , t256)\
		FIELD(description            ,����â                ,tname256_t                   ,30 , tcstr , tcstr , t256)\
		FIELD(kfmname                ,KFM Filename       ,tname256_t                   ,31 , tcstr , tcstr , t256)\

	#endif // for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Monster�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Monster_InheritedTable
	#define for_each_nTESTSERVER_Sys_Monster_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Monster_InheritedTable


	// ------------------------------------------------------------
	// Sys_Monster�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Monster�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{

	enum EMobRank // �������
	{
		eBEGIN_EMobRank = 0,
		/* ���� ��޿� ���� �з� */
		eMOB_RANK_NORMAL = 0, // �Ϲ���
		eMOB_RANK_REINFORCE = 1, // ��ȭ��
		eMOB_RANK_SEMIBOSS = 2, // �غ�����
		eMOB_RANK_BOSS = 3, // ������
		eEND_EMobRank
	}; // EMobRank 





struct jEXCEL_LIB_API Sys_Monster /* ������� */
{
	/*  ���� sid */
	Sys_Monster_id_t m_msid; // ID min_max(,)
		typedef Sys_Monster_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_msid; }
	void SetPrimaryKey(primary_key_t id) { m_msid = id; }
	/*  ���� uid */
	tname32_t m_name; // �̸� min_max(,)
	/*  NULL */
	EMobRank m_rank; // ��� min_max(,EMobRank)
	/*  NULL */
	int32 m_level; // ���� min_max(,)
	/*  NULL */
	int32 m_rewardExp; // �������ġ min_max(,)
	/*  NULL */
	int32 m_hp_max; // HP min_max(,)
	/*  NULL */
	int32 m_hp_regen; // HP ȸ���ӵ� min_max(,)
	/*  NULL */
	float m_aggro_distance; // ��׷� ���� min_max(,)
	/*  NULL */
	float m_attack_distance; // ���� ���� min_max(,)
	/*  NULL */
	float m_approach_distance; // �̵� ���� min_max(,)
	/*  NULL */
	float m_hit_chance; // ���߷� min_max(,)
	/*  NULL */
	float m_avoid_chance; // ȸ�Ƿ� min_max(,)
	/*  NULL */
	float m_move_speed; // �̵��ӵ� min_max(,)
	/*  NULL */
	int32 m_aerial_type; // Aerial Ÿ�� min_max(,)
	/*  NULL */
	skill_sid_t m_skill1; // ��ų1 min_max(,)
	/*  NULL */
	skill_sid_t m_skill2; // ��ų2 min_max(,)
	/*  NULL */
	skill_sid_t m_skill3; // ��ų3 min_max(,)
	/*  NULL */
	skill_sid_t m_skill4; // ��ų4 min_max(,)
	/*  NULL */
	skill_sid_t m_skill5; // ��ų5 min_max(,)
	/*  NULL */
	float m_skill6; // ��ų6 min_max(,)
	/*  NULL */
	float m_skill7; // ��ų7 min_max(,)
	/*  NULL */
	float m_skill8; // ��ų8 min_max(,)
	/*  NULL */
	float m_skill9; // ��ų9 min_max(,)
	/*  NULL */
	float m_skill10; // ��ų10 min_max(,)
	/*  NULL */
	int32 m_physic_atk; // �������ݷ� min_max(,)
	/*  NULL */
	int32 m_magic_atk; // �������ݷ� min_max(,)
	/*  ���� ������ */
	tname32_t m_iconname; // ������ �̸� min_max(,)
	/*  ���Ͱ� �׾����� ����Ǵ� Element �̸�. Item_drop_patten.xml */
	tname32_t m_dropname; // ���������Ʈ �̸� min_max(,)
	/*  AI ���ϸ� */
	tname256_t m_fsmname; // AI Filename min_max(,)
	/*  NULL */
	tname256_t m_deathfx; // �״� �ִϸ��̼� min_max(,)
	/*  NULL */
	tname256_t m_description; // ����â min_max(,)
	/*  NULL */
	tname256_t m_kfmname; // KFM Filename min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Monster
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  32 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Monster
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Monster();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Monster

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Monster)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Monster
enum { eSTRUCT_SIZE_Sys_Monster = sizeof(Sys_Monster) };


struct CSV_Sys_Monster : public nMech::nUtil::jCSV_File<Sys_Monster>
{
	virtual ~CSV_Sys_Monster(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Monster>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Monster g_Sys_Monster;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EMobRank[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nTESTSERVER 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nTESTSERVER;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nTESTSERVER_sam_npc_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;
	for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nTESTSERVER___filename_sam_npc_
