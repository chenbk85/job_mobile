/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_sam_npc_
#define __namespace_nTESTSERVER___filename_sam_npc_

#include "table_const_sam_npc.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nTESTSERVER_sam_npc_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EMobRank,설명없음,nMech,nTESTSERVER)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nTESTSERVER_EMobRank_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MOB_RANK_NORMAL			,0,일반형,nMech,nTESTSERVER,EMobRank)\
		ENUM_FIELD(MOB_RANK_REINFORCE			,1,강화형,nMech,nTESTSERVER,EMobRank)\
		ENUM_FIELD(MOB_RANK_SEMIBOSS			,2,준보스형,nMech,nTESTSERVER,EMobRank)\
		ENUM_FIELD(MOB_RANK_BOSS			,3,보스형,nMech,nTESTSERVER,EMobRank)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nTESTSERVER_sam_npc_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Monster,설명없음,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_Monster 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD(FIELD)\
		FIELD(msid                   ,ID                 ,Sys_Monster_id_t             ,0 , Sys_Monster_id_t , uint16 , u16)\
		FIELD(name                   ,이름                 ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(rank                   ,등급                 ,EMobRank                     ,2 , EMobRank , EMobRank , e)\
		FIELD(level                  ,레벨                 ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(rewardExp              ,보상경험치              ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(hp_max                 ,HP                 ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(hp_regen               ,HP 회복속도            ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(aggro_distance         ,어그로 범위             ,float                        ,7 , float , float , f)\
		FIELD(attack_distance        ,공격 범위              ,float                        ,8 , float , float , f)\
		FIELD(approach_distance      ,이동 범위              ,float                        ,9 , float , float , f)\
		FIELD(hit_chance             ,적중률                ,float                        ,10 , float , float , f)\
		FIELD(avoid_chance           ,회피률                ,float                        ,11 , float , float , f)\
		FIELD(move_speed             ,이동속도               ,float                        ,12 , float , float , f)\
		FIELD(aerial_type            ,Aerial 타입          ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(skill1                 ,스킬1                ,skill_sid_t                  ,14 , int32 , int32 , i32)\
		FIELD(skill2                 ,스킬2                ,skill_sid_t                  ,15 , int32 , int32 , i32)\
		FIELD(skill3                 ,스킬3                ,skill_sid_t                  ,16 , int32 , int32 , i32)\
		FIELD(skill4                 ,스킬4                ,skill_sid_t                  ,17 , int32 , int32 , i32)\
		FIELD(skill5                 ,스킬5                ,skill_sid_t                  ,18 , int32 , int32 , i32)\
		FIELD(skill6                 ,스킬6                ,float                        ,19 , float , float , f)\
		FIELD(skill7                 ,스킬7                ,float                        ,20 , float , float , f)\
		FIELD(skill8                 ,스킬8                ,float                        ,21 , float , float , f)\
		FIELD(skill9                 ,스킬9                ,float                        ,22 , float , float , f)\
		FIELD(skill10                ,스킬10               ,float                        ,23 , float , float , f)\
		FIELD(physic_atk             ,물리공격력              ,int32                        ,24 , int32 , int32 , i32)\
		FIELD(magic_atk              ,마법공격력              ,int32                        ,25 , int32 , int32 , i32)\
		FIELD(iconname               ,아이콘 이름             ,tname32_t                    ,26 , tcstr , tcstr , t32)\
		FIELD(dropname               ,드랍오브젝트 이름          ,tname32_t                    ,27 , tcstr , tcstr , t32)\
		FIELD(fsmname                ,AI Filename        ,tname256_t                   ,28 , tcstr , tcstr , t256)\
		FIELD(deathfx                ,죽는 애니메이션           ,tname256_t                   ,29 , tcstr , tcstr , t256)\
		FIELD(description            ,설명창                ,tname256_t                   ,30 , tcstr , tcstr , t256)\
		FIELD(kfmname                ,KFM Filename       ,tname256_t                   ,31 , tcstr , tcstr , t256)\

	#endif // for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Monster가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Monster_InheritedTable
	#define for_each_nTESTSERVER_Sys_Monster_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Monster_InheritedTable


	// ------------------------------------------------------------
	// Sys_Monster가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Monster가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Monster_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{

	enum EMobRank // 설명없음
	{
		eBEGIN_EMobRank = 0,
		/* 몬스터 등급에 따른 분류 */
		eMOB_RANK_NORMAL = 0, // 일반형
		eMOB_RANK_REINFORCE = 1, // 강화형
		eMOB_RANK_SEMIBOSS = 2, // 준보스형
		eMOB_RANK_BOSS = 3, // 보스형
		eEND_EMobRank
	}; // EMobRank 





struct jEXCEL_LIB_API Sys_Monster /* 설명없음 */
{
	/*  몬스터 sid */
	Sys_Monster_id_t m_msid; // ID min_max(,)
		typedef Sys_Monster_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_msid; }
	void SetPrimaryKey(primary_key_t id) { m_msid = id; }
	/*  몬스터 uid */
	tname32_t m_name; // 이름 min_max(,)
	/*  NULL */
	EMobRank m_rank; // 등급 min_max(,EMobRank)
	/*  NULL */
	int32 m_level; // 레벨 min_max(,)
	/*  NULL */
	int32 m_rewardExp; // 보상경험치 min_max(,)
	/*  NULL */
	int32 m_hp_max; // HP min_max(,)
	/*  NULL */
	int32 m_hp_regen; // HP 회복속도 min_max(,)
	/*  NULL */
	float m_aggro_distance; // 어그로 범위 min_max(,)
	/*  NULL */
	float m_attack_distance; // 공격 범위 min_max(,)
	/*  NULL */
	float m_approach_distance; // 이동 범위 min_max(,)
	/*  NULL */
	float m_hit_chance; // 적중률 min_max(,)
	/*  NULL */
	float m_avoid_chance; // 회피률 min_max(,)
	/*  NULL */
	float m_move_speed; // 이동속도 min_max(,)
	/*  NULL */
	int32 m_aerial_type; // Aerial 타입 min_max(,)
	/*  NULL */
	skill_sid_t m_skill1; // 스킬1 min_max(,)
	/*  NULL */
	skill_sid_t m_skill2; // 스킬2 min_max(,)
	/*  NULL */
	skill_sid_t m_skill3; // 스킬3 min_max(,)
	/*  NULL */
	skill_sid_t m_skill4; // 스킬4 min_max(,)
	/*  NULL */
	skill_sid_t m_skill5; // 스킬5 min_max(,)
	/*  NULL */
	float m_skill6; // 스킬6 min_max(,)
	/*  NULL */
	float m_skill7; // 스킬7 min_max(,)
	/*  NULL */
	float m_skill8; // 스킬8 min_max(,)
	/*  NULL */
	float m_skill9; // 스킬9 min_max(,)
	/*  NULL */
	float m_skill10; // 스킬10 min_max(,)
	/*  NULL */
	int32 m_physic_atk; // 물리공격력 min_max(,)
	/*  NULL */
	int32 m_magic_atk; // 마법공격력 min_max(,)
	/*  몬스터 아이콘 */
	tname32_t m_iconname; // 아이콘 이름 min_max(,)
	/*  몬스터가 죽었을때 드랍되는 Element 이름. Item_drop_patten.xml */
	tname32_t m_dropname; // 드랍오브젝트 이름 min_max(,)
	/*  AI 패턴명 */
	tname256_t m_fsmname; // AI Filename min_max(,)
	/*  NULL */
	tname256_t m_deathfx; // 죽는 애니메이션 min_max(,)
	/*  NULL */
	tname256_t m_description; // 설명창 min_max(,)
	/*  NULL */
	tname256_t m_kfmname; // KFM Filename min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
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
