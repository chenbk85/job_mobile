/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_aq_table_
#define __namespace_nTESTSERVER___filename_aq_table_

#include "table_const_aq_table.h"
// -------------------------------------------------
// enum형 코드 템플릿 정의
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nTESTSERVER_aq_table_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EAttackType,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EAvatarParts,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EAvatarSubclass,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EDamageType,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemBind,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemClass,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemGrade,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemQuality,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemSubclass,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EMechanic,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EModifier,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(EModValueType,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(ESkillCastType,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(ESkillType,설명없음,nMech,nTESTSERVER)\
	ENUM_TABLE(ETarget,설명없음,nMech,nTESTSERVER)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 
	// -------------------------------------------------

	/* 설명없음 */
	#define for_each_nTESTSERVER_EAttackType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ATK_NONE			,1,NONE,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_NORMAL			,2,일반,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_PUSH			,3,밀기,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_PULL			,4,당기기,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_AERIAL			,5,띄우기,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_BLOW			,6,날리기,nMech,nTESTSERVER,EAttackType)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EAvatarParts_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PART_VISUAL_HEAD			,1,아바타 머리,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_FACE			,2,아바타 얼굴,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_SHOULDER			,3,아바타 어깨,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_BODY			,4,아바타 바디,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_HAND			,5,아바타 손,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_WAIST			,6,아바타 허리,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_LEGS			,7,아바타 다리,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_FEET			,8,아바타 발,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_BACK			,9,아바타 등,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_WEAPON_RH			,10,아바타 무기 오른손,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_WEAPON_LH			,11,아바타 무기 왼손,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_WEAPON_2H			,12,아바타 무기 양손,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_COUNT			,13,아바타 장비 개수,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_SKINCOLOR			,14,아바타 피부색,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_HEAD			,15,장비 머리,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_SHOULDER			,16,장비 어깨,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_BODY			,17,장비 바디,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_WAIST			,18,장비 허리,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_LEGS			,19,장비 다리,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_FEET			,20,장비 발,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_NECK			,21,장비 목,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_FINGER1			,22,장비 손가락1,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_FINGER2			,23,장비 손가라2,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_NONE			,24,사용 안함,nMech,nTESTSERVER,EAvatarParts)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EAvatarSubclass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ASC_NONE			,1,사용안함,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_BERSERK			,2,광전사,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_MAGIC_NIGHT			,3,마검사,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_PALADIN			,4,수호기사,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_ELEMENTAL_MASTER			,5,대마법사,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_EXORCIST			,6,영환도사,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_SUMMONER			,7,소환사,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_MONK			,8,몽크,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_STREET_FIGHTER			,9,스트리트파이터,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_AURA_MASTER			,10,오러 마스터,nMech,nTESTSERVER,EAvatarSubclass)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EDamageType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(DMG_PHYSIC			,1,물리뎀쥐,nMech,nTESTSERVER,EDamageType)\
		ENUM_FIELD(DMG_MAGIC			,2,마법뎀쥐,nMech,nTESTSERVER,EDamageType)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EItemBind_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ITEM_BIND_NONE			,1,귀속 없음,nMech,nTESTSERVER,EItemBind)\
		ENUM_FIELD(ITEM_BIND_WHEN_EQUIPED			,2,착용 시 귀속,nMech,nTESTSERVER,EItemBind)\
		ENUM_FIELD(ITEM_BIND_WHEN_ACQUIRED			,3,획득 시 귀속,nMech,nTESTSERVER,EItemBind)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EItemClass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IC_CONSUMABLE			,1,소모품,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_WEAPON			,2,무기,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_AMOR			,3,방어구,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_ACCESSORY			,4,액세서리,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_COSTUME			,5,의상,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_RESOURCE			,6,자원,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_QUEST			,7,퀘스트,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_MISC			,8,기타,nMech,nTESTSERVER,EItemClass)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EItemGrade_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ITEM_GRADE_POOR			,1,허름한,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_NORMAL			,2,일반,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_MAGIC			,3,매직,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_SET			,4,세트,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_RARE			,5,레어,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_UNIQUE			,6,유니크,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_ARTIFACT			,7,인공물,nMech,nTESTSERVER,EItemGrade)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EItemQuality_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ITEM_QUALITY_NONE			,1,NONE,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_LOWEST			,2,최하급,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_LOW			,3,하급,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_INTERMEDIATE			,4,중급,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_HIGHER			,5,상급,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_HIGHEST			,6,최상급,nMech,nTESTSERVER,EItemQuality)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EItemSubclass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ISC_WEAPON_BIGSWORD			,1,대겁,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_MAGICSWORD			,2,마법검,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_MACE			,3,둔기,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_SHIELD			,4,방패,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_STAFF			,5,스태프,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_ROBE			,6,로브,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_CHARM			,7,부적,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_KNUCKLE			,8,너클,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_GAUNTLET			,9,건틀릿,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_MAGICBRACELET			,10,마법 팔찌,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_END			,11,무기 끝,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_HEAD			,12,장비 머리,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_SHOULDER			,13,장비 어깨,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_BODY			,14,장비 바디,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_WAIST			,15,장비 허리,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_LEGS			,16,장비 다리,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_FEET			,17,장비 발,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_NECK			,18,액세서리 목,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_FINGER1			,19,액세서리 손가락1,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_FINGER2			,20,액세서리 손가라2,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_END			,21,액세서리 끝,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_HEAD			,22,아바타 머리,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_FACE			,23,아바타 얼굴,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_SHOULDER			,24,아바타 어깨,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_BODY			,25,아바타 바디,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_HANDS			,26,아바타 손,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_WAIST			,27,아바타 허리,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_LEGS			,28,아바타 다리,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_FEET			,29,아바타 발,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_BACK			,30,아바타 등,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_EFFECT			,31,아바타 이펙트,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_SKINCOLOR			,32,아바타 피부색,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_END			,33,아바타 끝,nMech,nTESTSERVER,EItemSubclass)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EMechanic_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MECHANIC_NONE			,1,이상 없음,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_FREEZE			,2,빙결 상태,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_BLAZE			,3,화염 상태,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_SLOW			,4,슬로우 상태,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_BLIND			,5,실명 상태,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_SLIDE			,6,미끄러짐 상태,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_STONE			,7,석화 상태,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_POISON			,8,독 상태,nMech,nTESTSERVER,EMechanic)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EModifier_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MOD_NONE			,1,NONE,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_HP			,2,HP,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_HP_MAX			,3,HP MAX,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_HP_REGEN			,4,HP REGEN,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MP			,5,MP 회복,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MP_MAX			,6,MP MAX,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MP_REGEN			,7,MP_REGEN,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_ALL			,8,모든 상태,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_STR			,9,힘,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_STA			,10,체력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_AGI			,11,민첩,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_INT			,12,지능,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_MEN			,13,정신,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_ALL			,14,모든 저항력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_WATER			,15,수속성저항력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_FIRE			,16,화속성저항력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_LIGHT			,17,명속성저항력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_DARK			,18,암속성저항력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_PHYSIC_ATK			,19,물리공격력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_PHYSIC_DEF			,20,물리방어력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_PHYSIC_CRIT_CHANCE			,21,물리크리티컬확률,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAGIC_ATK			,22,마법공격력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAGIC_DEF			,23,마법방어력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAGIC_CRIT_CHANCE			,24,마법크리티컬확률,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_ATTACK_SPEED			,25,공격속도,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_CAST_SPEED			,26,캐스팅속도,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MOVE_SPEED			,27,이동속도,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_JUMP_FACTOR			,28,점프력,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAX			,29,최대MOD,nMech,nTESTSERVER,EModifier)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_EModValueType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MODVALUE_BASE			,1,기본값,nMech,nTESTSERVER,EModValueType)\
		ENUM_FIELD(MODVALUE_ADD			,2,ADD,nMech,nTESTSERVER,EModValueType)\
		ENUM_FIELD(MODVALUE_PCT			,3,PERCENTAGE,nMech,nTESTSERVER,EModValueType)\
		ENUM_FIELD(MODVALUE_MAX			,4,HP REGEN,nMech,nTESTSERVER,EModValueType)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_ESkillCastType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CAST_INSTANT			,1,즉시,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_CASTING			,2,캐스팅,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_CHARGING			,3,차징,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_LOCATING			,4,위치지정,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_TARGETING			,5,대상지정,nMech,nTESTSERVER,ESkillCastType)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_ESkillType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(SKILL_ACTIVE			,1,ACTIVE,nMech,nTESTSERVER,ESkillType)\
		ENUM_FIELD(SKILL_PASSIVE			,2,PASSIVE,nMech,nTESTSERVER,ESkillType)\

	/* 설명없음 */
	#define for_each_nTESTSERVER_ETarget_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(TARGET_NONE			,1,NONE,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_SELF			,2,본인,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_MEMBER			,3,파티 개인,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_GROUP			,4,파티 그룹,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_ENEMY			,5,적,nMech,nTESTSERVER,ETarget)\


// -------------------------------------------------
// struct 코드 템플릿 정의
// -------------------------------------------------
#define for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Avatar,설명없음,nMech,nTESTSERVER)\
	STRUCT(Sys_Item,설명없음,nMech,nTESTSERVER)\
	STRUCT(Sys_Skill,설명없음,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_Avatar 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD(FIELD)\
		FIELD(asid                   ,아바타 ID             ,Sys_Avatar_id_t              ,0 , Sys_Avatar_id_t , uint16 , u16)\
		FIELD(name                   ,아바타 이름             ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(baseclass              ,아바타 상위직업           ,EAvatarClass                 ,2 , EAvatarClass , EAvatarClass , e)\
		FIELD(subclass               ,아바타 하위직업           ,EAvatarSubclass              ,3 , EAvatarSubclass , EAvatarSubclass , e)\
		FIELD(hp_max                 ,HP                 ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(mp_max                 ,MP                 ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(hp_regen               ,HP회복 속도            ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(mp_regen               ,MP회복 속도            ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(st_str                 ,힘                  ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(st_sta                 ,민첩                 ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(st_agi                 ,체력                 ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(st_int                 ,지능                 ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(st_men                 ,정신력                ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(reation_aerial_type    ,띄워지는타입             ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(reation_blow_type      ,날려지는타입             ,int32                        ,14 , int32 , int32 , i32)\
		FIELD(reation_push_type      ,밀려지는타입             ,int32                        ,15 , int32 , int32 , i32)\
		FIELD(physic_atk             ,물리 공격력             ,int32                        ,16 , int32 , int32 , i32)\
		FIELD(physic_def             ,물리 방어력             ,int32                        ,17 , int32 , int32 , i32)\
		FIELD(physic_crit            ,물리 크리티컬 확률         ,float                        ,18 , float , float , f)\
		FIELD(magic_atk              ,마법 공격력             ,int32                        ,19 , int32 , int32 , i32)\
		FIELD(magic_def              ,마법 방어력             ,int32                        ,20 , int32 , int32 , i32)\
		FIELD(magic_crit             ,마법 크리티컬 확률         ,float                        ,21 , float , float , f)\
		FIELD(attack_speed           ,공격 속도              ,float                        ,22 , float , float , f)\
		FIELD(casting_speed          ,캐스팅 속도             ,float                        ,23 , float , float , f)\
		FIELD(move_speed             ,이동속도               ,float                        ,24 , float , float , f)\
		FIELD(dash_speed             ,대쉬속도               ,float                        ,25 , float , float , f)\
		FIELD(hit_chance             ,적중                 ,float                        ,26 , float , float , f)\
		FIELD(avoid_chance           ,회피                 ,float                        ,27 , float , float , f)\
		FIELD(jumpFactor             ,점프력                ,float                        ,28 , float , float , f)\
		FIELD(resist_fire            ,화속성 저항력            ,int32                        ,29 , int32 , int32 , i32)\
		FIELD(resist_water           ,수속성 저항력            ,int32                        ,30 , int32 , int32 , i32)\
		FIELD(resist_light           ,명속성 저항력            ,int32                        ,31 , int32 , int32 , i32)\
		FIELD(resist_dark            ,암속성 저항력            ,int32                        ,32 , int32 , int32 , i32)\
		FIELD(combo1                 ,콤보공격1              ,Sys_Skill_id_t               ,33 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo2                 ,콤보공격2              ,Sys_Skill_id_t               ,34 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo3                 ,콤보공격3              ,Sys_Skill_id_t               ,35 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo4                 ,콤보공격4              ,Sys_Skill_id_t               ,36 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo5                 ,콤보공격5              ,Sys_Skill_id_t               ,37 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(jump_atk               ,점프공격               ,Sys_Skill_id_t               ,38 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(dash_atk               ,대쉬공격               ,Sys_Skill_id_t               ,39 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo1_2h              ,양손콤보공격1            ,Sys_Skill_id_t               ,40 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo2_2h              ,양손콤보공격2            ,Sys_Skill_id_t               ,41 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo3_3h              ,양손콤보공격3            ,Sys_Skill_id_t               ,42 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo4_2h              ,양손콤보공격4            ,Sys_Skill_id_t               ,43 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo5_2h              ,양손콤보공격5            ,Sys_Skill_id_t               ,44 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(jump_atk_2h            ,양손점프공격             ,Sys_Skill_id_t               ,45 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(dash_atk_2h            ,양손대쉬공격             ,Sys_Skill_id_t               ,46 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(xmlname                ,아바타 xml 파일 이름      ,tname32_t                    ,47 , tcstr , tcstr , t32)\
		FIELD(fkmname                ,파일 이름 및 경로         ,tname256_t                   ,48 , tcstr , tcstr , t256)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Avatar가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_InheritedTable
	#define for_each_nTESTSERVER_Sys_Avatar_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_InheritedTable


	// ------------------------------------------------------------
	// Sys_Avatar가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Avatar가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Item 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,아이템 ID             ,Sys_Item_id_t                ,0 , Sys_Item_id_t , uint16 , u16)\
		FIELD(name                   ,아이템 이름             ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(category               ,아이템 대분류            ,EItemClass                   ,2 , EItemClass , EItemClass , e)\
		FIELD(subcategory            ,아이템 소분류            ,EItemSubclass                ,3 , EItemSubclass , EItemSubclass , e)\
		FIELD(grade                  ,아이템 등급             ,EItemGrade                   ,4 , EItemGrade , EItemGrade , e)\
		FIELD(quality                ,아이템 품질             ,EItemQuality                 ,5 , EItemQuality , EItemQuality , e)\
		FIELD(bind_type              ,아이템 귀속 여부          ,EItemBind                    ,6 , EItemBind , EItemBind , e)\
		FIELD(part                   ,아이템 착용 부위          ,EAvatarParts                 ,7 , EAvatarParts , EAvatarParts , e)\
		FIELD(reqClass               ,아이팀 사용 상위직업        ,EAvatarClass                 ,8 , EAvatarClass , EAvatarClass , e)\
		FIELD(reqSubclass            ,아이템 사용 하위직업        ,EAvatarSubclass              ,9 , EAvatarSubclass , EAvatarSubclass , e)\
		FIELD(maxCount               ,아이템 최대 소지 개수       ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(stackCount             ,아이템 최대 스택 수량       ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(buyPrice               ,아이템 구입 가격          ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(sellPrice              ,아이템 판매 가격          ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(repairPrice            ,아이템 수리 가격          ,int32                        ,14 , int32 , int32 , i32)\
		FIELD(reqCash                ,아이템 캐쉬 가격          ,int32                        ,15 , int32 , int32 , i32)\
		FIELD(reqLevel               ,아이템 사용 레벨          ,int32                        ,16 , int32 , int32 , i32)\
		FIELD(durability             ,아이템 내구도            ,int32                        ,17 , int32 , int32 , i32)\
		FIELD(activeTime             ,아이템 활성 제한 시간(사용가능기간) ,int32                      ,18 , int32 , int32 , i32)\
		FIELD(trigger_skill          ,아이템 사용시 적용 스킬      ,int32                        ,19 , int32 , int32 , i32)\
		FIELD(iconname               ,아이템 아이콘            ,tname256_t                   ,20 , tcstr , tcstr , t256)\
		FIELD(delegate               ,아이템 드랍 오브젝트        ,tname128_t                   ,21 , tcstr , tcstr , t128)\
		FIELD(filename               ,아이템 리소스 파일(착용시 오브젝트) ,tname256_t                 ,22 , tcstr , tcstr , t256)\
		FIELD(xmlname                ,아이템 옵션 xml 파일 이름   ,tname32_t                    ,23 , tcstr , tcstr , t32)\
		FIELD(description            ,아이템 팝업 설명창         ,tname32_t                    ,24 , tcstr , tcstr , t32)\

	#endif // for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Item가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Item_InheritedTable
	#define for_each_nTESTSERVER_Sys_Item_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Item_InheritedTable


	// ------------------------------------------------------------
	// Sys_Item가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Item가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Skill 자신의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD(FIELD)\
		FIELD(ssid                   ,스킬 ID              ,Sys_Skill_id_t               ,0 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(name                   ,스킬 이름              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(level                  ,스킬 레벨              ,skill_level_t                ,2 , int32 , int32 , i32)\
		FIELD(maxLevel               ,스킬 최대 레벨           ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(reqLevel               ,스킬 배울수 있는 아바타레벨    ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(reqGold                ,스킬 획득 시 필요 GOLD    ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(reqSP                  ,스킬 레벨업시 필요 SP      ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(reqItem                ,스킬 사용시 필요 아이템      ,Sys_Item_id_t                ,7 , Sys_Item_id_t , uint16 , u16)\
		FIELD(costHP                 ,스킬 사용시 소모되는 hp     ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(costMP                 ,스킬 사용시 소모되는 mp     ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(costItem               ,스킬 사용시 소모되는 아이템    ,Sys_Item_id_t                ,10 , Sys_Item_id_t , uint16 , u16)\
		FIELD(type                   ,스킬 타입              ,ESkillType                   ,11 , ESkillType , ESkillType , e)\
		FIELD(castingType            ,스킬 캐스팅 타입          ,ESkillCastType               ,12 , ESkillCastType , ESkillCastType , e)\
		FIELD(castingAnim            ,스킬 캐스팅애니메이션        ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(castingTime            ,스킬 시전 시간           ,float                        ,14 , float , float , f)\
		FIELD(chargingTime           ,차징 최대 시간           ,float                        ,15 , float , float , f)\
		FIELD(chargingMutiplier      ,차징 데미지증가력          ,float                        ,16 , float , float , f)\
		FIELD(coolTime               ,스킬 재사용 시간          ,float                        ,17 , float , float , f)\
		FIELD(skillAnim              ,스킬 애니메이션           ,int32                        ,18 , int32 , int32 , i32)\
		FIELD(target                 ,스킬 적용대상            ,ETarget                      ,19 , ETarget , ETarget , e)\
		FIELD(attackType             ,스킬 공격 리액션 타입       ,EAttackType                  ,20 , EAttackType , EAttackType , e)\
		FIELD(attackRate             ,공격 리액션 비율          ,float                        ,21 , float , float , f)\
		FIELD(hit_chance             ,스킬 명중률             ,float                        ,22 , float , float , f)\
		FIELD(critical_chance        ,스킬 크리티컬 확률         ,float                        ,23 , float , float , f)\
		FIELD(effectRange            ,스킬 효과 범위           ,float                        ,24 , float , float , f)\
		FIELD(effectDuration         ,효과 적용 시간           ,float                        ,25 , float , float , f)\
		FIELD(effect                 ,효과                 ,tname32_t                    ,26 , tcstr , tcstr , t32)\
		FIELD(castingFX              ,스킬 캐스팅FX           ,tname32_t                    ,27 , tcstr , tcstr , t32)\
		FIELD(skillFX                ,스킬 기본 FX           ,tname32_t                    ,28 , tcstr , tcstr , t32)\
		FIELD(chargingFX             ,스틸 차징 FX           ,tname32_t                    ,29 , tcstr , tcstr , t32)\
		FIELD(collisionFX            ,스킬 충돌 FX           ,tname32_t                    ,30 , tcstr , tcstr , t32)\
		FIELD(targetFX               ,스킬 타겟 FX           ,tname32_t                    ,31 , tcstr , tcstr , t32)\
		FIELD(description            ,설명창                ,tname256_t                   ,32 , tcstr , tcstr , t256)\

	#endif // for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Skill가 상속한 테이블들의 이름을 나열한 매크로.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Skill_InheritedTable
	#define for_each_nTESTSERVER_Sys_Skill_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Skill_InheritedTable


	// ------------------------------------------------------------
	// Sys_Skill가 상속한 테이블들의 필드만 나열한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Skill가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_all_member

// -------------------------------------------------
// 코드 시작
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{

	enum EAttackType // 설명없음
	{
		eBEGIN_EAttackType = 0,
		/* 효과 없음 */
		eATK_NONE = 1, // NONE
		/* 일반 공격 */
		eATK_NORMAL = 2, // 일반
		/* 적을 뒤로 밀리게 한다. */
		eATK_PUSH = 3, // 밀기
		/* 적을 끌어 당긴다. */
		eATK_PULL = 4, // 당기기
		/* 적을 뛰운다 */
		eATK_AERIAL = 5, // 띄우기
		/* 적을 날린다 */
		eATK_BLOW = 6, // 날리기
		eEND_EAttackType
	}; // EAttackType 



	enum EAvatarParts // 설명없음
	{
		eBEGIN_EAvatarParts = 0,
		/* 아바타 장비 */
		ePART_VISUAL_HEAD = 1, // 아바타 머리
		ePART_VISUAL_FACE = 2, // 아바타 얼굴
		ePART_VISUAL_SHOULDER = 3, // 아바타 어깨
		ePART_VISUAL_BODY = 4, // 아바타 바디
		ePART_VISUAL_HAND = 5, // 아바타 손
		ePART_VISUAL_WAIST = 6, // 아바타 허리
		ePART_VISUAL_LEGS = 7, // 아바타 다리
		ePART_VISUAL_FEET = 8, // 아바타 발
		ePART_VISUAL_BACK = 9, // 아바타 등
		/* 무기 장비 */
		ePART_WEAPON_RH = 10, // 아바타 무기 오른손
		ePART_WEAPON_LH = 11, // 아바타 무기 왼손
		ePART_WEAPON_2H = 12, // 아바타 무기 양손
		/* >> 아바타 장비 개수 */
		ePART_VISUAL_COUNT = 13, // 아바타 장비 개수
		/* 피부색 */
		ePART_SKINCOLOR = 14, // 아바타 피부색
		/* 기본 장비 */
		ePART_EQUIP_HEAD = 15, // 장비 머리
		ePART_EQUIP_SHOULDER = 16, // 장비 어깨
		ePART_EQUIP_BODY = 17, // 장비 바디
		ePART_EQUIP_WAIST = 18, // 장비 허리
		ePART_EQUIP_LEGS = 19, // 장비 다리
		ePART_EQUIP_FEET = 20, // 장비 발
		/* 액세서리 */
		ePART_EQUIP_NECK = 21, // 장비 목
		ePART_EQUIP_FINGER1 = 22, // 장비 손가락1
		ePART_EQUIP_FINGER2 = 23, // 장비 손가라2
		ePART_NONE = 24, // 사용 안함
		eEND_EAvatarParts
	}; // EAvatarParts 



	enum EAvatarSubclass // 설명없음
	{
		eBEGIN_EAvatarSubclass = 0,
		/* 용병 하위 직업군 */
		eASC_NONE = 1, // 사용안함
		eASC_BERSERK = 2, // 광전사
		eASC_MAGIC_NIGHT = 3, // 마검사
		eASC_PALADIN = 4, // 수호기사
		/* 마법사 하위 직업군 */
		eASC_ELEMENTAL_MASTER = 5, // 대마법사
		eASC_EXORCIST = 6, // 영환도사
		eASC_SUMMONER = 7, // 소환사
		/* 격투가 하위 직업군 */
		eASC_MONK = 8, // 몽크
		eASC_STREET_FIGHTER = 9, // 스트리트파이터
		eASC_AURA_MASTER = 10, // 오러 마스터
		eEND_EAvatarSubclass
	}; // EAvatarSubclass 



	enum EDamageType // 설명없음
	{
		eBEGIN_EDamageType = 0,
		/* 물리데미지 */
		eDMG_PHYSIC = 1, // 물리뎀쥐
		/* 매직데미지 */
		eDMG_MAGIC = 2, // 마법뎀쥐
		eEND_EDamageType
	}; // EDamageType 



	enum EItemBind // 설명없음
	{
		eBEGIN_EItemBind = 0,
		/* 귀속 여부에 따른 분류 */
		eITEM_BIND_NONE = 1, // 귀속 없음
		eITEM_BIND_WHEN_EQUIPED = 2, // 착용 시 귀속
		eITEM_BIND_WHEN_ACQUIRED = 3, // 획득 시 귀속
		eEND_EItemBind
	}; // EItemBind 



	enum EItemClass // 설명없음
	{
		eBEGIN_EItemClass = 0,
		/* 아이템 대 분류 */
		eIC_CONSUMABLE = 1, // 소모품
		eIC_WEAPON = 2, // 무기
		eIC_AMOR = 3, // 방어구
		eIC_ACCESSORY = 4, // 액세서리
		eIC_COSTUME = 5, // 의상
		eIC_RESOURCE = 6, // 자원
		eIC_QUEST = 7, // 퀘스트
		eIC_MISC = 8, // 기타
		eEND_EItemClass
	}; // EItemClass 



	enum EItemGrade // 설명없음
	{
		eBEGIN_EItemGrade = 0,
		/* GRAY */
		eITEM_GRADE_POOR = 1, // 허름한
		/* WHITE */
		eITEM_GRADE_NORMAL = 2, // 일반
		/* BLUE */
		eITEM_GRADE_MAGIC = 3, // 매직
		/* GREEN */
		eITEM_GRADE_SET = 4, // 세트
		/* PURPLE */
		eITEM_GRADE_RARE = 5, // 레어
		/* GOLD */
		eITEM_GRADE_UNIQUE = 6, // 유니크
		/* LIGHT_YELLOW */
		eITEM_GRADE_ARTIFACT = 7, // 인공물
		eEND_EItemGrade
	}; // EItemGrade 



	enum EItemQuality // 설명없음
	{
		eBEGIN_EItemQuality = 0,
		/* 아이템 품질에 따른 분류 */
		eITEM_QUALITY_NONE = 1, // NONE
		eITEM_QUALITY_LOWEST = 2, // 최하급
		/* 최하급->최상급순서의 품질 */
		eITEM_QUALITY_LOW = 3, // 하급
		eITEM_QUALITY_INTERMEDIATE = 4, // 중급
		eITEM_QUALITY_HIGHER = 5, // 상급
		eITEM_QUALITY_HIGHEST = 6, // 최상급
		eEND_EItemQuality
	}; // EItemQuality 



	enum EItemSubclass // 설명없음
	{
		eBEGIN_EItemSubclass = 0,
		/* 무기 아이템 소 분류 */
		eISC_WEAPON_BIGSWORD = 1, // 대겁
		eISC_WEAPON_MAGICSWORD = 2, // 마법검
		eISC_WEAPON_MACE = 3, // 둔기
		eISC_WEAPON_SHIELD = 4, // 방패
		eISC_WEAPON_STAFF = 5, // 스태프
		eISC_WEAPON_ROBE = 6, // 로브
		eISC_WEAPON_CHARM = 7, // 부적
		eISC_WEAPON_KNUCKLE = 8, // 너클
		eISC_WEAPON_GAUNTLET = 9, // 건틀릿
		eISC_WEAPON_MAGICBRACELET = 10, // 마법 팔찌
		eISC_WEAPON_END = 11, // 무기 끝
		/* 장비 아이템 소 분류 */
		eISC_EQ_HEAD = 12, // 장비 머리
		eISC_EQ_SHOULDER = 13, // 장비 어깨
		eISC_EQ_BODY = 14, // 장비 바디
		eISC_EQ_WAIST = 15, // 장비 허리
		eISC_EQ_LEGS = 16, // 장비 다리
		eISC_EQ_FEET = 17, // 장비 발
		/* 액세서리 아이템 소 분류 */
		eISC_EQ_NECK = 18, // 액세서리 목
		eISC_EQ_FINGER1 = 19, // 액세서리 손가락1
		eISC_EQ_FINGER2 = 20, // 액세서리 손가라2
		eISC_EQ_END = 21, // 액세서리 끝
		/* 파츠 아이템 소 분류 */
		eISC_AV_HEAD = 22, // 아바타 머리
		eISC_AV_FACE = 23, // 아바타 얼굴
		eISC_AV_SHOULDER = 24, // 아바타 어깨
		eISC_AV_BODY = 25, // 아바타 바디
		eISC_AV_HANDS = 26, // 아바타 손
		eISC_AV_WAIST = 27, // 아바타 허리
		eISC_AV_LEGS = 28, // 아바타 다리
		eISC_AV_FEET = 29, // 아바타 발
		eISC_AV_BACK = 30, // 아바타 등
		eISC_AV_EFFECT = 31, // 아바타 이펙트
		eISC_AV_SKINCOLOR = 32, // 아바타 피부색
		eISC_AV_END = 33, // 아바타 끝
		eEND_EItemSubclass
	}; // EItemSubclass 



	enum EMechanic // 설명없음
	{
		eBEGIN_EMechanic = 0,
		/* 상태 변화에 따른 분류 */
		eMECHANIC_NONE = 1, // 이상 없음
		/* 빙결상태시 행동이 불가능하며 적의 공격에 데미지를 입는다. */
		eMECHANIC_FREEZE = 2, // 빙결 상태
		/* 화염 상태시 지속 시간동안 데미지를 지속적으로 입는다. */
		eMECHANIC_BLAZE = 3, // 화염 상태
		/* 슬로우 상태시 행동속도가 일정확률로 떨어지게 된다. */
		eMECHANIC_SLOW = 4, // 슬로우 상태
		/* 실명 상태시 일정 부분을 제외하고 화면이 보이지 않는다. */
		eMECHANIC_BLIND = 5, // 실명 상태
		/* 미끄러짐 상태시 이동키입력과 반대 방향으로 이동하게 된다. */
		eMECHANIC_SLIDE = 6, // 미끄러짐 상태
		/* 석화 상태시 행동이 불가능하며 적의 공격에 데미지를 입는다. */
		eMECHANIC_STONE = 7, // 석화 상태
		/* 독 상태시 지속 시간동안 데미지를 지속적으로 입는다. */
		eMECHANIC_POISON = 8, // 독 상태
		eEND_EMechanic
	}; // EMechanic 



	enum EModifier // 설명없음
	{
		eBEGIN_EModifier = 0,
		/* 아바타에 능력치의 수정자 리스트이다. */
		eMOD_NONE = 1, // NONE
		/* add, pct */
		eMOD_HP = 2, // HP
		/* add, pct */
		eMOD_HP_MAX = 3, // HP MAX
		/* add, pct */
		eMOD_HP_REGEN = 4, // HP REGEN
		/* add, pct */
		eMOD_MP = 5, // MP 회복
		/* add, pct */
		eMOD_MP_MAX = 6, // MP MAX
		/* add, pct */
		eMOD_MP_REGEN = 7, // MP_REGEN
		/* add, pct */
		eMOD_STAT_ALL = 8, // 모든 상태
		/* add, pct */
		eMOD_STAT_STR = 9, // 힘
		/* add, pct */
		eMOD_STAT_STA = 10, // 체력
		/* add, pct */
		eMOD_STAT_AGI = 11, // 민첩
		/* add, pct */
		eMOD_STAT_INT = 12, // 지능
		/* add, pct */
		eMOD_STAT_MEN = 13, // 정신
		/* pct */
		eMOD_RESIST_ALL = 14, // 모든 저항력
		/* pct */
		eMOD_RESIST_WATER = 15, // 수속성저항력
		/* pct */
		eMOD_RESIST_FIRE = 16, // 화속성저항력
		/* pct */
		eMOD_RESIST_LIGHT = 17, // 명속성저항력
		/* pct */
		eMOD_RESIST_DARK = 18, // 암속성저항력
		/* pct */
		eMOD_PHYSIC_ATK = 19, // 물리공격력
		/* pct */
		eMOD_PHYSIC_DEF = 20, // 물리방어력
		/* pct */
		eMOD_PHYSIC_CRIT_CHANCE = 21, // 물리크리티컬확률
		/* pct */
		eMOD_MAGIC_ATK = 22, // 마법공격력
		/* pct */
		eMOD_MAGIC_DEF = 23, // 마법방어력
		/* pct */
		eMOD_MAGIC_CRIT_CHANCE = 24, // 마법크리티컬확률
		/* pct */
		eMOD_ATTACK_SPEED = 25, // 공격속도
		/* pct */
		eMOD_CAST_SPEED = 26, // 캐스팅속도
		/* pct */
		eMOD_MOVE_SPEED = 27, // 이동속도
		/* pct */
		eMOD_JUMP_FACTOR = 28, // 점프력
		eMOD_MAX = 29, // 최대MOD
		eEND_EModifier
	}; // EModifier 



	enum EModValueType // 설명없음
	{
		eBEGIN_EModValueType = 0,
		eMODVALUE_BASE = 1, // 기본값
		eMODVALUE_ADD = 2, // ADD
		eMODVALUE_PCT = 3, // PERCENTAGE
		eMODVALUE_MAX = 4, // HP REGEN
		eEND_EModValueType
	}; // EModValueType 



	enum ESkillCastType // 설명없음
	{
		eBEGIN_ESkillCastType = 0,
		/* 사용 즉시 적용한다. */
		eCAST_INSTANT = 1, // 즉시
		/* 시전동작후 적용한다. */
		eCAST_CASTING = 2, // 캐스팅
		/* 기를 모은후 적용된다. */
		eCAST_CHARGING = 3, // 차징
		/* 위치를 지정한후 적용한다. */
		eCAST_LOCATING = 4, // 위치지정
		/* 대상을 지정하고 적용한다. */
		eCAST_TARGETING = 5, // 대상지정
		eEND_ESkillCastType
	}; // ESkillCastType 



	enum ESkillType // 설명없음
	{
		eBEGIN_ESkillType = 0,
		/* 액티브스킬 */
		eSKILL_ACTIVE = 1, // ACTIVE
		/* 패시브스킬 */
		eSKILL_PASSIVE = 2, // PASSIVE
		eEND_ESkillType
	}; // ESkillType 



	enum ETarget // 설명없음
	{
		eBEGIN_ETarget = 0,
		eTARGET_NONE = 1, // NONE
		/* 본인에게 적용한다. */
		eTARGET_SELF = 2, // 본인
		/* 파티 그룹중 개인에게 적용한다 */
		eTARGET_MEMBER = 3, // 파티 개인
		/* 파티 그룹에게 적용한다 */
		eTARGET_GROUP = 4, // 파티 그룹
		/* 몹/오브젝트/트랩에 적용한다. PVP시 다른팀은 MOB 으로 분류한다. */
		eTARGET_ENEMY = 5, // 적
		eEND_ETarget
	}; // ETarget 





struct jEXCEL_LIB_API Sys_Avatar /* 설명없음 */
{
	/*  아바타 sid */
	Sys_Avatar_id_t m_asid; // 아바타 ID min_max(,)
		typedef Sys_Avatar_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_asid; }
	void SetPrimaryKey(primary_key_t id) { m_asid = id; }
	/*  아바타 이름 */
	tname32_t m_name; // 아바타 이름 min_max(,)
	/*  NULL */
	EAvatarClass m_baseclass; // 아바타 상위직업 min_max(,EAvatarClass)
	/*  NULL */
	EAvatarSubclass m_subclass; // 아바타 하위직업 min_max(,EAvatarSubclass)
	/*  default value */
	int32 m_hp_max; // HP min_max(0,)
	/*  default value */
	int32 m_mp_max; // MP min_max(0,)
	/*  1분당 회복되는 hp */
	int32 m_hp_regen; // HP회복 속도 min_max(,)
	/*  1분당 회복되는 mp */
	int32 m_mp_regen; // MP회복 속도 min_max(,)
	/*  default value */
	int32 m_st_str; // 힘 min_max(0,)
	/*  default value */
	int32 m_st_sta; // 민첩 min_max(0,)
	/*  default value */
	int32 m_st_agi; // 체력 min_max(0,)
	/*  default value */
	int32 m_st_int; // 지능 min_max(0,)
	/*  default value */
	int32 m_st_men; // 정신력 min_max(0,)
	int32 m_reation_aerial_type; // 띄워지는타입 min_max(,)
	int32 m_reation_blow_type; // 날려지는타입 min_max(,)
	int32 m_reation_push_type; // 밀려지는타입 min_max(,)
	/*  default value */
	int32 m_physic_atk; // 물리 공격력 min_max(,)
	/*  default value */
	int32 m_physic_def; // 물리 방어력 min_max(,)
	/*  default value */
	float m_physic_crit; // 물리 크리티컬 확률 min_max(,)
	/*  default value */
	int32 m_magic_atk; // 마법 공격력 min_max(,)
	/*  default value */
	int32 m_magic_def; // 마법 방어력 min_max(,)
	/*  default value */
	float m_magic_crit; // 마법 크리티컬 확률 min_max(,)
	/*  default value */
	float m_attack_speed; // 공격 속도 min_max(,)
	/*  default value */
	float m_casting_speed; // 캐스팅 속도 min_max(,)
	/*  실수와 %로 표시 */
	float m_move_speed; // 이동속도 min_max(,)
	/*  실수와 %로 표시 */
	float m_dash_speed; // 대쉬속도 min_max(,)
	/*  실수와 %로 표시 */
	float m_hit_chance; // 적중 min_max(,)
	/*  실수와 %로 표시 */
	float m_avoid_chance; // 회피 min_max(,)
	/*  실수와 %로 표시 */
	float m_jumpFactor; // 점프력 min_max(,)
	/*  실수와 %로 표시 */
	int32 m_resist_fire; // 화속성 저항력 min_max(,)
	/*  실수와 %로 표시 */
	int32 m_resist_water; // 수속성 저항력 min_max(,)
	/*  실수와 %로 표시 */
	int32 m_resist_light; // 명속성 저항력 min_max(,)
	/*  실수와 %로 표시 */
	int32 m_resist_dark; // 암속성 저항력 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo1; // 콤보공격1 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo2; // 콤보공격2 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo3; // 콤보공격3 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo4; // 콤보공격4 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo5; // 콤보공격5 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_jump_atk; // 점프공격 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_dash_atk; // 대쉬공격 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo1_2h; // 양손콤보공격1 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo2_2h; // 양손콤보공격2 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo3_3h; // 양손콤보공격3 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo4_2h; // 양손콤보공격4 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo5_2h; // 양손콤보공격5 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_jump_atk_2h; // 양손점프공격 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_dash_atk_2h; // 양손대쉬공격 min_max(,)
	/*  xml에서 불러 오는 아바타 옵션 이름 */
	tname32_t m_xmlname; // 아바타 xml 파일 이름 min_max(,)
	/*  파일의 이름 및 경로(kfm) */
	tname256_t m_fkmname; // 파일 이름 및 경로 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Avatar
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  49 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Avatar
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Avatar();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Avatar

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Avatar)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Avatar
enum { eSTRUCT_SIZE_Sys_Avatar = sizeof(Sys_Avatar) };


struct CSV_Sys_Avatar : public nMech::nUtil::jCSV_File<Sys_Avatar>
{
	virtual ~CSV_Sys_Avatar(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Avatar>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Avatar g_Sys_Avatar;

struct jEXCEL_LIB_API Sys_Item /* 설명없음 */
{
	/*  아이템의 sid */
	Sys_Item_id_t m_isid; // 아이템 ID min_max(,)
		typedef Sys_Item_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  아이템의 name */
	tname32_t m_name; // 아이템 이름 min_max(,)
	/*  NULL */
	EItemClass m_category; // 아이템 대분류 min_max(,EItemClass)
	/*  NULL */
	EItemSubclass m_subcategory; // 아이템 소분류 min_max(,EItemSubclass)
	/*  일반_ 매직_ 세트_ 레어_ 유니크_ 에픽 */
	EItemGrade m_grade; // 아이템 등급 min_max(,EItemGrade)
	/*  최하급_ 하급_ 중급_ 상급_ 최상급 */
	EItemQuality m_quality; // 아이템 품질 min_max(,EItemQuality)
	/*  귀속 없음_ 획득 시 귀속_ 착용 시 귀속 */
	EItemBind m_bind_type; // 아이템 귀속 여부 min_max(,EItemBind)
	/*  NULL */
	EAvatarParts m_part; // 아이템 착용 부위 min_max(,EAvatarParts)
	/*  상위 직업_모든 직업 사용으로 분류 */
	EAvatarClass m_reqClass; // 아이팀 사용 상위직업 min_max(,EAvatarClass)
	/*  하위 직업별 분류 */
	EAvatarSubclass m_reqSubclass; // 아이템 사용 하위직업 min_max(,EAvatarSubclass)
	/*  아이템을 소지할수 있는 최대 개수 */
	int32 m_maxCount; // 아이템 최대 소지 개수 min_max(,)
	/*  인벤토리 한칸에 최대 수량_ 최대 99개 */
	int32 m_stackCount; // 아이템 최대 스택 수량 min_max(1,99)
	/*  상점 구입 가격 */
	int32 m_buyPrice; // 아이템 구입 가격 min_max(,)
	/*  상점 판매 가격 */
	int32 m_sellPrice; // 아이템 판매 가격 min_max(,)
	/*  내구도 x 수리 가격 */
	int32 m_repairPrice; // 아이템 수리 가격 min_max(,)
	/*  캐쉬 구입 가격 */
	int32 m_reqCash; // 아이템 캐쉬 가격 min_max(,)
	/*  아이템 사용 가능 레벨 */
	int32 m_reqLevel; // 아이템 사용 레벨 min_max(1,60)
	/*  최고 내구도 표시 */
	int32 m_durability; // 아이템 내구도 min_max(,)
	/*  기간제 아이템의 사용 기간_ 분(Min)단위 */
	int32 m_activeTime; // 아이템 활성 제한 시간(사용가능기간) min_max(,)
	/*  아이템 사용시 적용될 스킬 */
	int32 m_trigger_skill; // 아이템 사용시 적용 스킬 min_max(,)
	/*  아이콘 파일(dds) */
	tname256_t m_iconname; // 아이템 아이콘 min_max(,)
	/*  아이템 드랍시 떨어지는 오브젝트 */
	tname128_t m_delegate; // 아이템 드랍 오브젝트 min_max(,)
	/*  파일의 이름및 경로(nif) */
	tname256_t m_filename; // 아이템 리소스 파일(착용시 오브젝트) min_max(,)
	/*  xml에서 불러오는 아이템 옵션 이름 */
	tname32_t m_xmlname; // 아이템 옵션 xml 파일 이름 min_max(,)
	/*  Sys_LocaleText.csv 게임 화면에 출력되는 아이템 설명 */
	tname32_t m_description; // 아이템 팝업 설명창 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Item
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  25 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Item
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Item();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Item

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Item)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Item
enum { eSTRUCT_SIZE_Sys_Item = sizeof(Sys_Item) };


struct CSV_Sys_Item : public nMech::nUtil::jCSV_File<Sys_Item>
{
	virtual ~CSV_Sys_Item(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Item>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Item g_Sys_Item;

struct jEXCEL_LIB_API Sys_Skill /* 설명없음 */
{
	/*  스킬의 sid */
	Sys_Skill_id_t m_ssid; // 스킬 ID min_max(,)
		typedef Sys_Skill_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_ssid; }
	void SetPrimaryKey(primary_key_t id) { m_ssid = id; }
	/*  스킬의 name */
	tname32_t m_name; // 스킬 이름 min_max(,)
	/*  스킬 레벨 */
	skill_level_t m_level; // 스킬 레벨 min_max(,)
	/*  스킬을 배울수 있는 최대 레벨 */
	int32 m_maxLevel; // 스킬 최대 레벨 min_max(,)
	/*  NULL */
	int32 m_reqLevel; // 스킬 배울수 있는 아바타레벨 min_max(,)
	/*  NULL */
	int32 m_reqGold; // 스킬 획득 시 필요 GOLD min_max(,)
	/*  NULL */
	int32 m_reqSP; // 스킬 레벨업시 필요 SP min_max(,)
	/*  NULL */
	Sys_Item_id_t m_reqItem; // 스킬 사용시 필요 아이템 min_max(,)
	/*  NULL */
	int32 m_costHP; // 스킬 사용시 소모되는 hp min_max(,)
	/*  NULL */
	int32 m_costMP; // 스킬 사용시 소모되는 mp min_max(,)
	/*  NULL */
	Sys_Item_id_t m_costItem; // 스킬 사용시 소모되는 아이템 min_max(,)
	/*  즉시/주기적/지속적 */
	ESkillType m_type; // 스킬 타입 min_max(,ESkillType)
	/*  즉시/지정/캐스팅 */
	ESkillCastType m_castingType; // 스킬 캐스팅 타입 min_max(,ESkillCastType)
	/*  NULL */
	int32 m_castingAnim; // 스킬 캐스팅애니메이션 min_max(,)
	/*  단위 : 초 */
	float m_castingTime; // 스킬 시전 시간 min_max(,)
	float m_chargingTime; // 차징 최대 시간 min_max(,)
	/*  차징 성공하면 물리 및 기본 데미지에 곱해준다. */
	float m_chargingMutiplier; // 차징 데미지증가력 min_max(,)
	/*  단위 : 초 */
	float m_coolTime; // 스킬 재사용 시간 min_max(,)
	/*  NULL */
	int32 m_skillAnim; // 스킬 애니메이션 min_max(,)
	/*  본인/그룹/적 */
	ETarget m_target; // 스킬 적용대상 min_max(,ETarget)
	/*  스킬 공격 타입 */
	EAttackType m_attackType; // 스킬 공격 리액션 타입 min_max(,EAttackType)
	/*  스킬 공격 타입 수치 */
	float m_attackRate; // 공격 리액션 비율 min_max(,)
	/*  아바타 수치와 + 하여 계산 */
	float m_hit_chance; // 스킬 명중률 min_max(,)
	/*  아바타 수치와 + 하여 계산 */
	float m_critical_chance; // 스킬 크리티컬 확률 min_max(,)
	/*  스킬 효과 적용 범위(단위m) */
	float m_effectRange; // 스킬 효과 범위 min_max(,)
	float m_effectDuration; // 효과 적용 시간 min_max(,)
	tname32_t m_effect; // 효과 min_max(,)
	/*  NULL */
	tname32_t m_castingFX; // 스킬 캐스팅FX min_max(,)
	/*  NULL */
	tname32_t m_skillFX; // 스킬 기본 FX min_max(,)
	tname32_t m_chargingFX; // 스틸 차징 FX min_max(,)
	/*  NULL */
	tname32_t m_collisionFX; // 스킬 충돌 FX min_max(,)
	/*  NULL */
	tname32_t m_targetFX; // 스킬 타겟 FX min_max(,)
	/*  Sys_LocaleText.csv 게임 화면에 출력되는 스킬 설명 */
	tname256_t m_description; // 설명창 min_max(,)

	//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.
	enum enumSys_Skill
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  33 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Skill
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Skill();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Skill

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Skill)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Skill
enum { eSTRUCT_SIZE_Sys_Skill = sizeof(Sys_Skill) };


struct CSV_Sys_Skill : public nMech::nUtil::jCSV_File<Sys_Skill>
{
	virtual ~CSV_Sys_Skill(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Skill>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Skill g_Sys_Skill;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAttackType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAvatarParts[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAvatarSubclass[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EDamageType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemBind[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemClass[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemGrade[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemQuality[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EItemSubclass[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EMechanic[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EModifier[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EModValueType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ESkillCastType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ESkillType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETarget[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nTESTSERVER 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nTESTSERVER;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nTESTSERVER_aq_table_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;
	for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nTESTSERVER___filename_aq_table_
