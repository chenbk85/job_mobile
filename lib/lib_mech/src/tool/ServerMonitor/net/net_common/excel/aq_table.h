/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_aq_table_
#define __namespace_nTESTSERVER___filename_aq_table_

#include "table_const_aq_table.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nTESTSERVER_aq_table_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EAttackType,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EAvatarParts,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EAvatarSubclass,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EDamageType,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemBind,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemClass,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemGrade,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemQuality,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EItemSubclass,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EMechanic,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EModifier,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EModValueType,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(ESkillCastType,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(ESkillType,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(ETarget,�������,nMech,nTESTSERVER)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nTESTSERVER_EAttackType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ATK_NONE			,1,NONE,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_NORMAL			,2,�Ϲ�,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_PUSH			,3,�б�,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_PULL			,4,����,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_AERIAL			,5,����,nMech,nTESTSERVER,EAttackType)\
		ENUM_FIELD(ATK_BLOW			,6,������,nMech,nTESTSERVER,EAttackType)\

	/* ������� */
	#define for_each_nTESTSERVER_EAvatarParts_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(PART_VISUAL_HEAD			,1,�ƹ�Ÿ �Ӹ�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_FACE			,2,�ƹ�Ÿ ��,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_SHOULDER			,3,�ƹ�Ÿ ���,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_BODY			,4,�ƹ�Ÿ �ٵ�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_HAND			,5,�ƹ�Ÿ ��,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_WAIST			,6,�ƹ�Ÿ �㸮,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_LEGS			,7,�ƹ�Ÿ �ٸ�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_FEET			,8,�ƹ�Ÿ ��,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_BACK			,9,�ƹ�Ÿ ��,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_WEAPON_RH			,10,�ƹ�Ÿ ���� ������,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_WEAPON_LH			,11,�ƹ�Ÿ ���� �޼�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_WEAPON_2H			,12,�ƹ�Ÿ ���� ���,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_VISUAL_COUNT			,13,�ƹ�Ÿ ��� ����,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_SKINCOLOR			,14,�ƹ�Ÿ �Ǻλ�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_HEAD			,15,��� �Ӹ�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_SHOULDER			,16,��� ���,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_BODY			,17,��� �ٵ�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_WAIST			,18,��� �㸮,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_LEGS			,19,��� �ٸ�,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_FEET			,20,��� ��,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_NECK			,21,��� ��,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_FINGER1			,22,��� �հ���1,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_EQUIP_FINGER2			,23,��� �հ���2,nMech,nTESTSERVER,EAvatarParts)\
		ENUM_FIELD(PART_NONE			,24,��� ����,nMech,nTESTSERVER,EAvatarParts)\

	/* ������� */
	#define for_each_nTESTSERVER_EAvatarSubclass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ASC_NONE			,1,������,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_BERSERK			,2,������,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_MAGIC_NIGHT			,3,���˻�,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_PALADIN			,4,��ȣ���,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_ELEMENTAL_MASTER			,5,�븶����,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_EXORCIST			,6,��ȯ����,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_SUMMONER			,7,��ȯ��,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_MONK			,8,��ũ,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_STREET_FIGHTER			,9,��Ʈ��Ʈ������,nMech,nTESTSERVER,EAvatarSubclass)\
		ENUM_FIELD(ASC_AURA_MASTER			,10,���� ������,nMech,nTESTSERVER,EAvatarSubclass)\

	/* ������� */
	#define for_each_nTESTSERVER_EDamageType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(DMG_PHYSIC			,1,��������,nMech,nTESTSERVER,EDamageType)\
		ENUM_FIELD(DMG_MAGIC			,2,��������,nMech,nTESTSERVER,EDamageType)\

	/* ������� */
	#define for_each_nTESTSERVER_EItemBind_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ITEM_BIND_NONE			,1,�ͼ� ����,nMech,nTESTSERVER,EItemBind)\
		ENUM_FIELD(ITEM_BIND_WHEN_EQUIPED			,2,���� �� �ͼ�,nMech,nTESTSERVER,EItemBind)\
		ENUM_FIELD(ITEM_BIND_WHEN_ACQUIRED			,3,ȹ�� �� �ͼ�,nMech,nTESTSERVER,EItemBind)\

	/* ������� */
	#define for_each_nTESTSERVER_EItemClass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(IC_CONSUMABLE			,1,�Ҹ�ǰ,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_WEAPON			,2,����,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_AMOR			,3,��,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_ACCESSORY			,4,�׼�����,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_COSTUME			,5,�ǻ�,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_RESOURCE			,6,�ڿ�,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_QUEST			,7,����Ʈ,nMech,nTESTSERVER,EItemClass)\
		ENUM_FIELD(IC_MISC			,8,��Ÿ,nMech,nTESTSERVER,EItemClass)\

	/* ������� */
	#define for_each_nTESTSERVER_EItemGrade_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ITEM_GRADE_POOR			,1,�㸧��,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_NORMAL			,2,�Ϲ�,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_MAGIC			,3,����,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_SET			,4,��Ʈ,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_RARE			,5,����,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_UNIQUE			,6,����ũ,nMech,nTESTSERVER,EItemGrade)\
		ENUM_FIELD(ITEM_GRADE_ARTIFACT			,7,�ΰ���,nMech,nTESTSERVER,EItemGrade)\

	/* ������� */
	#define for_each_nTESTSERVER_EItemQuality_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ITEM_QUALITY_NONE			,1,NONE,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_LOWEST			,2,���ϱ�,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_LOW			,3,�ϱ�,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_INTERMEDIATE			,4,�߱�,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_HIGHER			,5,���,nMech,nTESTSERVER,EItemQuality)\
		ENUM_FIELD(ITEM_QUALITY_HIGHEST			,6,�ֻ��,nMech,nTESTSERVER,EItemQuality)\

	/* ������� */
	#define for_each_nTESTSERVER_EItemSubclass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ISC_WEAPON_BIGSWORD			,1,���,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_MAGICSWORD			,2,������,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_MACE			,3,�б�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_SHIELD			,4,����,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_STAFF			,5,������,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_ROBE			,6,�κ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_CHARM			,7,����,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_KNUCKLE			,8,��Ŭ,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_GAUNTLET			,9,��Ʋ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_MAGICBRACELET			,10,���� ����,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_WEAPON_END			,11,���� ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_HEAD			,12,��� �Ӹ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_SHOULDER			,13,��� ���,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_BODY			,14,��� �ٵ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_WAIST			,15,��� �㸮,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_LEGS			,16,��� �ٸ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_FEET			,17,��� ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_NECK			,18,�׼����� ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_FINGER1			,19,�׼����� �հ���1,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_FINGER2			,20,�׼����� �հ���2,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_EQ_END			,21,�׼����� ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_HEAD			,22,�ƹ�Ÿ �Ӹ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_FACE			,23,�ƹ�Ÿ ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_SHOULDER			,24,�ƹ�Ÿ ���,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_BODY			,25,�ƹ�Ÿ �ٵ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_HANDS			,26,�ƹ�Ÿ ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_WAIST			,27,�ƹ�Ÿ �㸮,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_LEGS			,28,�ƹ�Ÿ �ٸ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_FEET			,29,�ƹ�Ÿ ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_BACK			,30,�ƹ�Ÿ ��,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_EFFECT			,31,�ƹ�Ÿ ����Ʈ,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_SKINCOLOR			,32,�ƹ�Ÿ �Ǻλ�,nMech,nTESTSERVER,EItemSubclass)\
		ENUM_FIELD(ISC_AV_END			,33,�ƹ�Ÿ ��,nMech,nTESTSERVER,EItemSubclass)\

	/* ������� */
	#define for_each_nTESTSERVER_EMechanic_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MECHANIC_NONE			,1,�̻� ����,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_FREEZE			,2,���� ����,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_BLAZE			,3,ȭ�� ����,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_SLOW			,4,���ο� ����,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_BLIND			,5,�Ǹ� ����,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_SLIDE			,6,�̲����� ����,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_STONE			,7,��ȭ ����,nMech,nTESTSERVER,EMechanic)\
		ENUM_FIELD(MECHANIC_POISON			,8,�� ����,nMech,nTESTSERVER,EMechanic)\

	/* ������� */
	#define for_each_nTESTSERVER_EModifier_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MOD_NONE			,1,NONE,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_HP			,2,HP,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_HP_MAX			,3,HP MAX,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_HP_REGEN			,4,HP REGEN,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MP			,5,MP ȸ��,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MP_MAX			,6,MP MAX,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MP_REGEN			,7,MP_REGEN,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_ALL			,8,��� ����,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_STR			,9,��,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_STA			,10,ü��,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_AGI			,11,��ø,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_INT			,12,����,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_STAT_MEN			,13,����,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_ALL			,14,��� ���׷�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_WATER			,15,���Ӽ����׷�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_FIRE			,16,ȭ�Ӽ����׷�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_LIGHT			,17,��Ӽ����׷�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_RESIST_DARK			,18,�ϼӼ����׷�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_PHYSIC_ATK			,19,�������ݷ�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_PHYSIC_DEF			,20,��������,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_PHYSIC_CRIT_CHANCE			,21,����ũ��Ƽ��Ȯ��,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAGIC_ATK			,22,�������ݷ�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAGIC_DEF			,23,��������,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAGIC_CRIT_CHANCE			,24,����ũ��Ƽ��Ȯ��,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_ATTACK_SPEED			,25,���ݼӵ�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_CAST_SPEED			,26,ĳ���üӵ�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MOVE_SPEED			,27,�̵��ӵ�,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_JUMP_FACTOR			,28,������,nMech,nTESTSERVER,EModifier)\
		ENUM_FIELD(MOD_MAX			,29,�ִ�MOD,nMech,nTESTSERVER,EModifier)\

	/* ������� */
	#define for_each_nTESTSERVER_EModValueType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(MODVALUE_BASE			,1,�⺻��,nMech,nTESTSERVER,EModValueType)\
		ENUM_FIELD(MODVALUE_ADD			,2,ADD,nMech,nTESTSERVER,EModValueType)\
		ENUM_FIELD(MODVALUE_PCT			,3,PERCENTAGE,nMech,nTESTSERVER,EModValueType)\
		ENUM_FIELD(MODVALUE_MAX			,4,HP REGEN,nMech,nTESTSERVER,EModValueType)\

	/* ������� */
	#define for_each_nTESTSERVER_ESkillCastType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CAST_INSTANT			,1,���,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_CASTING			,2,ĳ����,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_CHARGING			,3,��¡,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_LOCATING			,4,��ġ����,nMech,nTESTSERVER,ESkillCastType)\
		ENUM_FIELD(CAST_TARGETING			,5,�������,nMech,nTESTSERVER,ESkillCastType)\

	/* ������� */
	#define for_each_nTESTSERVER_ESkillType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(SKILL_ACTIVE			,1,ACTIVE,nMech,nTESTSERVER,ESkillType)\
		ENUM_FIELD(SKILL_PASSIVE			,2,PASSIVE,nMech,nTESTSERVER,ESkillType)\

	/* ������� */
	#define for_each_nTESTSERVER_ETarget_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(TARGET_NONE			,1,NONE,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_SELF			,2,����,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_MEMBER			,3,��Ƽ ����,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_GROUP			,4,��Ƽ �׷�,nMech,nTESTSERVER,ETarget)\
		ENUM_FIELD(TARGET_ENEMY			,5,��,nMech,nTESTSERVER,ETarget)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nTESTSERVER_aq_table_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Avatar,�������,nMech,nTESTSERVER)\
	STRUCT(Sys_Item,�������,nMech,nTESTSERVER)\
	STRUCT(Sys_Skill,�������,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_Avatar �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD(FIELD)\
		FIELD(asid                   ,�ƹ�Ÿ ID             ,Sys_Avatar_id_t              ,0 , Sys_Avatar_id_t , uint16 , u16)\
		FIELD(name                   ,�ƹ�Ÿ �̸�             ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(baseclass              ,�ƹ�Ÿ ��������           ,EAvatarClass                 ,2 , EAvatarClass , EAvatarClass , e)\
		FIELD(subclass               ,�ƹ�Ÿ ��������           ,EAvatarSubclass              ,3 , EAvatarSubclass , EAvatarSubclass , e)\
		FIELD(hp_max                 ,HP                 ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(mp_max                 ,MP                 ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(hp_regen               ,HPȸ�� �ӵ�            ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(mp_regen               ,MPȸ�� �ӵ�            ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(st_str                 ,��                  ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(st_sta                 ,��ø                 ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(st_agi                 ,ü��                 ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(st_int                 ,����                 ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(st_men                 ,���ŷ�                ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(reation_aerial_type    ,�������Ÿ��             ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(reation_blow_type      ,��������Ÿ��             ,int32                        ,14 , int32 , int32 , i32)\
		FIELD(reation_push_type      ,�з�����Ÿ��             ,int32                        ,15 , int32 , int32 , i32)\
		FIELD(physic_atk             ,���� ���ݷ�             ,int32                        ,16 , int32 , int32 , i32)\
		FIELD(physic_def             ,���� ����             ,int32                        ,17 , int32 , int32 , i32)\
		FIELD(physic_crit            ,���� ũ��Ƽ�� Ȯ��         ,float                        ,18 , float , float , f)\
		FIELD(magic_atk              ,���� ���ݷ�             ,int32                        ,19 , int32 , int32 , i32)\
		FIELD(magic_def              ,���� ����             ,int32                        ,20 , int32 , int32 , i32)\
		FIELD(magic_crit             ,���� ũ��Ƽ�� Ȯ��         ,float                        ,21 , float , float , f)\
		FIELD(attack_speed           ,���� �ӵ�              ,float                        ,22 , float , float , f)\
		FIELD(casting_speed          ,ĳ���� �ӵ�             ,float                        ,23 , float , float , f)\
		FIELD(move_speed             ,�̵��ӵ�               ,float                        ,24 , float , float , f)\
		FIELD(dash_speed             ,�뽬�ӵ�               ,float                        ,25 , float , float , f)\
		FIELD(hit_chance             ,����                 ,float                        ,26 , float , float , f)\
		FIELD(avoid_chance           ,ȸ��                 ,float                        ,27 , float , float , f)\
		FIELD(jumpFactor             ,������                ,float                        ,28 , float , float , f)\
		FIELD(resist_fire            ,ȭ�Ӽ� ���׷�            ,int32                        ,29 , int32 , int32 , i32)\
		FIELD(resist_water           ,���Ӽ� ���׷�            ,int32                        ,30 , int32 , int32 , i32)\
		FIELD(resist_light           ,��Ӽ� ���׷�            ,int32                        ,31 , int32 , int32 , i32)\
		FIELD(resist_dark            ,�ϼӼ� ���׷�            ,int32                        ,32 , int32 , int32 , i32)\
		FIELD(combo1                 ,�޺�����1              ,Sys_Skill_id_t               ,33 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo2                 ,�޺�����2              ,Sys_Skill_id_t               ,34 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo3                 ,�޺�����3              ,Sys_Skill_id_t               ,35 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo4                 ,�޺�����4              ,Sys_Skill_id_t               ,36 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo5                 ,�޺�����5              ,Sys_Skill_id_t               ,37 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(jump_atk               ,��������               ,Sys_Skill_id_t               ,38 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(dash_atk               ,�뽬����               ,Sys_Skill_id_t               ,39 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo1_2h              ,����޺�����1            ,Sys_Skill_id_t               ,40 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo2_2h              ,����޺�����2            ,Sys_Skill_id_t               ,41 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo3_3h              ,����޺�����3            ,Sys_Skill_id_t               ,42 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo4_2h              ,����޺�����4            ,Sys_Skill_id_t               ,43 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(combo5_2h              ,����޺�����5            ,Sys_Skill_id_t               ,44 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(jump_atk_2h            ,�����������             ,Sys_Skill_id_t               ,45 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(dash_atk_2h            ,��մ뽬����             ,Sys_Skill_id_t               ,46 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(xmlname                ,�ƹ�Ÿ xml ���� �̸�      ,tname32_t                    ,47 , tcstr , tcstr , t32)\
		FIELD(fkmname                ,���� �̸� �� ���         ,tname256_t                   ,48 , tcstr , tcstr , t256)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Avatar�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_InheritedTable
	#define for_each_nTESTSERVER_Sys_Avatar_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_InheritedTable


	// ------------------------------------------------------------
	// Sys_Avatar�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Avatar�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Avatar_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Item �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,������ ID             ,Sys_Item_id_t                ,0 , Sys_Item_id_t , uint16 , u16)\
		FIELD(name                   ,������ �̸�             ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(category               ,������ ��з�            ,EItemClass                   ,2 , EItemClass , EItemClass , e)\
		FIELD(subcategory            ,������ �Һз�            ,EItemSubclass                ,3 , EItemSubclass , EItemSubclass , e)\
		FIELD(grade                  ,������ ���             ,EItemGrade                   ,4 , EItemGrade , EItemGrade , e)\
		FIELD(quality                ,������ ǰ��             ,EItemQuality                 ,5 , EItemQuality , EItemQuality , e)\
		FIELD(bind_type              ,������ �ͼ� ����          ,EItemBind                    ,6 , EItemBind , EItemBind , e)\
		FIELD(part                   ,������ ���� ����          ,EAvatarParts                 ,7 , EAvatarParts , EAvatarParts , e)\
		FIELD(reqClass               ,������ ��� ��������        ,EAvatarClass                 ,8 , EAvatarClass , EAvatarClass , e)\
		FIELD(reqSubclass            ,������ ��� ��������        ,EAvatarSubclass              ,9 , EAvatarSubclass , EAvatarSubclass , e)\
		FIELD(maxCount               ,������ �ִ� ���� ����       ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(stackCount             ,������ �ִ� ���� ����       ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(buyPrice               ,������ ���� ����          ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(sellPrice              ,������ �Ǹ� ����          ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(repairPrice            ,������ ���� ����          ,int32                        ,14 , int32 , int32 , i32)\
		FIELD(reqCash                ,������ ĳ�� ����          ,int32                        ,15 , int32 , int32 , i32)\
		FIELD(reqLevel               ,������ ��� ����          ,int32                        ,16 , int32 , int32 , i32)\
		FIELD(durability             ,������ ������            ,int32                        ,17 , int32 , int32 , i32)\
		FIELD(activeTime             ,������ Ȱ�� ���� �ð�(��밡�ɱⰣ) ,int32                      ,18 , int32 , int32 , i32)\
		FIELD(trigger_skill          ,������ ���� ���� ��ų      ,int32                        ,19 , int32 , int32 , i32)\
		FIELD(iconname               ,������ ������            ,tname256_t                   ,20 , tcstr , tcstr , t256)\
		FIELD(delegate               ,������ ��� ������Ʈ        ,tname128_t                   ,21 , tcstr , tcstr , t128)\
		FIELD(filename               ,������ ���ҽ� ����(����� ������Ʈ) ,tname256_t                 ,22 , tcstr , tcstr , t256)\
		FIELD(xmlname                ,������ �ɼ� xml ���� �̸�   ,tname32_t                    ,23 , tcstr , tcstr , t32)\
		FIELD(description            ,������ �˾� ����â         ,tname32_t                    ,24 , tcstr , tcstr , t32)\

	#endif // for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Item�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Item_InheritedTable
	#define for_each_nTESTSERVER_Sys_Item_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Item_InheritedTable


	// ------------------------------------------------------------
	// Sys_Item�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Item�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Item_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Skill �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD(FIELD)\
		FIELD(ssid                   ,��ų ID              ,Sys_Skill_id_t               ,0 , Sys_Skill_id_t , uint16 , u16)\
		FIELD(name                   ,��ų �̸�              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(level                  ,��ų ����              ,skill_level_t                ,2 , int32 , int32 , i32)\
		FIELD(maxLevel               ,��ų �ִ� ����           ,int32                        ,3 , int32 , int32 , i32)\
		FIELD(reqLevel               ,��ų ���� �ִ� �ƹ�Ÿ����    ,int32                        ,4 , int32 , int32 , i32)\
		FIELD(reqGold                ,��ų ȹ�� �� �ʿ� GOLD    ,int32                        ,5 , int32 , int32 , i32)\
		FIELD(reqSP                  ,��ų �������� �ʿ� SP      ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(reqItem                ,��ų ���� �ʿ� ������      ,Sys_Item_id_t                ,7 , Sys_Item_id_t , uint16 , u16)\
		FIELD(costHP                 ,��ų ���� �Ҹ�Ǵ� hp     ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(costMP                 ,��ų ���� �Ҹ�Ǵ� mp     ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(costItem               ,��ų ���� �Ҹ�Ǵ� ������    ,Sys_Item_id_t                ,10 , Sys_Item_id_t , uint16 , u16)\
		FIELD(type                   ,��ų Ÿ��              ,ESkillType                   ,11 , ESkillType , ESkillType , e)\
		FIELD(castingType            ,��ų ĳ���� Ÿ��          ,ESkillCastType               ,12 , ESkillCastType , ESkillCastType , e)\
		FIELD(castingAnim            ,��ų ĳ���þִϸ��̼�        ,int32                        ,13 , int32 , int32 , i32)\
		FIELD(castingTime            ,��ų ���� �ð�           ,float                        ,14 , float , float , f)\
		FIELD(chargingTime           ,��¡ �ִ� �ð�           ,float                        ,15 , float , float , f)\
		FIELD(chargingMutiplier      ,��¡ ������������          ,float                        ,16 , float , float , f)\
		FIELD(coolTime               ,��ų ���� �ð�          ,float                        ,17 , float , float , f)\
		FIELD(skillAnim              ,��ų �ִϸ��̼�           ,int32                        ,18 , int32 , int32 , i32)\
		FIELD(target                 ,��ų ������            ,ETarget                      ,19 , ETarget , ETarget , e)\
		FIELD(attackType             ,��ų ���� ���׼� Ÿ��       ,EAttackType                  ,20 , EAttackType , EAttackType , e)\
		FIELD(attackRate             ,���� ���׼� ����          ,float                        ,21 , float , float , f)\
		FIELD(hit_chance             ,��ų ���߷�             ,float                        ,22 , float , float , f)\
		FIELD(critical_chance        ,��ų ũ��Ƽ�� Ȯ��         ,float                        ,23 , float , float , f)\
		FIELD(effectRange            ,��ų ȿ�� ����           ,float                        ,24 , float , float , f)\
		FIELD(effectDuration         ,ȿ�� ���� �ð�           ,float                        ,25 , float , float , f)\
		FIELD(effect                 ,ȿ��                 ,tname32_t                    ,26 , tcstr , tcstr , t32)\
		FIELD(castingFX              ,��ų ĳ����FX           ,tname32_t                    ,27 , tcstr , tcstr , t32)\
		FIELD(skillFX                ,��ų �⺻ FX           ,tname32_t                    ,28 , tcstr , tcstr , t32)\
		FIELD(chargingFX             ,��ƿ ��¡ FX           ,tname32_t                    ,29 , tcstr , tcstr , t32)\
		FIELD(collisionFX            ,��ų �浹 FX           ,tname32_t                    ,30 , tcstr , tcstr , t32)\
		FIELD(targetFX               ,��ų Ÿ�� FX           ,tname32_t                    ,31 , tcstr , tcstr , t32)\
		FIELD(description            ,����â                ,tname256_t                   ,32 , tcstr , tcstr , t256)\

	#endif // for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Skill�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Skill_InheritedTable
	#define for_each_nTESTSERVER_Sys_Skill_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Skill_InheritedTable


	// ------------------------------------------------------------
	// Sys_Skill�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Skill�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Skill_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{

	enum EAttackType // �������
	{
		eBEGIN_EAttackType = 0,
		/* ȿ�� ���� */
		eATK_NONE = 1, // NONE
		/* �Ϲ� ���� */
		eATK_NORMAL = 2, // �Ϲ�
		/* ���� �ڷ� �и��� �Ѵ�. */
		eATK_PUSH = 3, // �б�
		/* ���� ���� ����. */
		eATK_PULL = 4, // ����
		/* ���� �ٿ�� */
		eATK_AERIAL = 5, // ����
		/* ���� ������ */
		eATK_BLOW = 6, // ������
		eEND_EAttackType
	}; // EAttackType 



	enum EAvatarParts // �������
	{
		eBEGIN_EAvatarParts = 0,
		/* �ƹ�Ÿ ��� */
		ePART_VISUAL_HEAD = 1, // �ƹ�Ÿ �Ӹ�
		ePART_VISUAL_FACE = 2, // �ƹ�Ÿ ��
		ePART_VISUAL_SHOULDER = 3, // �ƹ�Ÿ ���
		ePART_VISUAL_BODY = 4, // �ƹ�Ÿ �ٵ�
		ePART_VISUAL_HAND = 5, // �ƹ�Ÿ ��
		ePART_VISUAL_WAIST = 6, // �ƹ�Ÿ �㸮
		ePART_VISUAL_LEGS = 7, // �ƹ�Ÿ �ٸ�
		ePART_VISUAL_FEET = 8, // �ƹ�Ÿ ��
		ePART_VISUAL_BACK = 9, // �ƹ�Ÿ ��
		/* ���� ��� */
		ePART_WEAPON_RH = 10, // �ƹ�Ÿ ���� ������
		ePART_WEAPON_LH = 11, // �ƹ�Ÿ ���� �޼�
		ePART_WEAPON_2H = 12, // �ƹ�Ÿ ���� ���
		/* >> �ƹ�Ÿ ��� ���� */
		ePART_VISUAL_COUNT = 13, // �ƹ�Ÿ ��� ����
		/* �Ǻλ� */
		ePART_SKINCOLOR = 14, // �ƹ�Ÿ �Ǻλ�
		/* �⺻ ��� */
		ePART_EQUIP_HEAD = 15, // ��� �Ӹ�
		ePART_EQUIP_SHOULDER = 16, // ��� ���
		ePART_EQUIP_BODY = 17, // ��� �ٵ�
		ePART_EQUIP_WAIST = 18, // ��� �㸮
		ePART_EQUIP_LEGS = 19, // ��� �ٸ�
		ePART_EQUIP_FEET = 20, // ��� ��
		/* �׼����� */
		ePART_EQUIP_NECK = 21, // ��� ��
		ePART_EQUIP_FINGER1 = 22, // ��� �հ���1
		ePART_EQUIP_FINGER2 = 23, // ��� �հ���2
		ePART_NONE = 24, // ��� ����
		eEND_EAvatarParts
	}; // EAvatarParts 



	enum EAvatarSubclass // �������
	{
		eBEGIN_EAvatarSubclass = 0,
		/* �뺴 ���� ������ */
		eASC_NONE = 1, // ������
		eASC_BERSERK = 2, // ������
		eASC_MAGIC_NIGHT = 3, // ���˻�
		eASC_PALADIN = 4, // ��ȣ���
		/* ������ ���� ������ */
		eASC_ELEMENTAL_MASTER = 5, // �븶����
		eASC_EXORCIST = 6, // ��ȯ����
		eASC_SUMMONER = 7, // ��ȯ��
		/* ������ ���� ������ */
		eASC_MONK = 8, // ��ũ
		eASC_STREET_FIGHTER = 9, // ��Ʈ��Ʈ������
		eASC_AURA_MASTER = 10, // ���� ������
		eEND_EAvatarSubclass
	}; // EAvatarSubclass 



	enum EDamageType // �������
	{
		eBEGIN_EDamageType = 0,
		/* ���������� */
		eDMG_PHYSIC = 1, // ��������
		/* ���������� */
		eDMG_MAGIC = 2, // ��������
		eEND_EDamageType
	}; // EDamageType 



	enum EItemBind // �������
	{
		eBEGIN_EItemBind = 0,
		/* �ͼ� ���ο� ���� �з� */
		eITEM_BIND_NONE = 1, // �ͼ� ����
		eITEM_BIND_WHEN_EQUIPED = 2, // ���� �� �ͼ�
		eITEM_BIND_WHEN_ACQUIRED = 3, // ȹ�� �� �ͼ�
		eEND_EItemBind
	}; // EItemBind 



	enum EItemClass // �������
	{
		eBEGIN_EItemClass = 0,
		/* ������ �� �з� */
		eIC_CONSUMABLE = 1, // �Ҹ�ǰ
		eIC_WEAPON = 2, // ����
		eIC_AMOR = 3, // ��
		eIC_ACCESSORY = 4, // �׼�����
		eIC_COSTUME = 5, // �ǻ�
		eIC_RESOURCE = 6, // �ڿ�
		eIC_QUEST = 7, // ����Ʈ
		eIC_MISC = 8, // ��Ÿ
		eEND_EItemClass
	}; // EItemClass 



	enum EItemGrade // �������
	{
		eBEGIN_EItemGrade = 0,
		/* GRAY */
		eITEM_GRADE_POOR = 1, // �㸧��
		/* WHITE */
		eITEM_GRADE_NORMAL = 2, // �Ϲ�
		/* BLUE */
		eITEM_GRADE_MAGIC = 3, // ����
		/* GREEN */
		eITEM_GRADE_SET = 4, // ��Ʈ
		/* PURPLE */
		eITEM_GRADE_RARE = 5, // ����
		/* GOLD */
		eITEM_GRADE_UNIQUE = 6, // ����ũ
		/* LIGHT_YELLOW */
		eITEM_GRADE_ARTIFACT = 7, // �ΰ���
		eEND_EItemGrade
	}; // EItemGrade 



	enum EItemQuality // �������
	{
		eBEGIN_EItemQuality = 0,
		/* ������ ǰ���� ���� �з� */
		eITEM_QUALITY_NONE = 1, // NONE
		eITEM_QUALITY_LOWEST = 2, // ���ϱ�
		/* ���ϱ�->�ֻ�޼����� ǰ�� */
		eITEM_QUALITY_LOW = 3, // �ϱ�
		eITEM_QUALITY_INTERMEDIATE = 4, // �߱�
		eITEM_QUALITY_HIGHER = 5, // ���
		eITEM_QUALITY_HIGHEST = 6, // �ֻ��
		eEND_EItemQuality
	}; // EItemQuality 



	enum EItemSubclass // �������
	{
		eBEGIN_EItemSubclass = 0,
		/* ���� ������ �� �з� */
		eISC_WEAPON_BIGSWORD = 1, // ���
		eISC_WEAPON_MAGICSWORD = 2, // ������
		eISC_WEAPON_MACE = 3, // �б�
		eISC_WEAPON_SHIELD = 4, // ����
		eISC_WEAPON_STAFF = 5, // ������
		eISC_WEAPON_ROBE = 6, // �κ�
		eISC_WEAPON_CHARM = 7, // ����
		eISC_WEAPON_KNUCKLE = 8, // ��Ŭ
		eISC_WEAPON_GAUNTLET = 9, // ��Ʋ��
		eISC_WEAPON_MAGICBRACELET = 10, // ���� ����
		eISC_WEAPON_END = 11, // ���� ��
		/* ��� ������ �� �з� */
		eISC_EQ_HEAD = 12, // ��� �Ӹ�
		eISC_EQ_SHOULDER = 13, // ��� ���
		eISC_EQ_BODY = 14, // ��� �ٵ�
		eISC_EQ_WAIST = 15, // ��� �㸮
		eISC_EQ_LEGS = 16, // ��� �ٸ�
		eISC_EQ_FEET = 17, // ��� ��
		/* �׼����� ������ �� �з� */
		eISC_EQ_NECK = 18, // �׼����� ��
		eISC_EQ_FINGER1 = 19, // �׼����� �հ���1
		eISC_EQ_FINGER2 = 20, // �׼����� �հ���2
		eISC_EQ_END = 21, // �׼����� ��
		/* ���� ������ �� �з� */
		eISC_AV_HEAD = 22, // �ƹ�Ÿ �Ӹ�
		eISC_AV_FACE = 23, // �ƹ�Ÿ ��
		eISC_AV_SHOULDER = 24, // �ƹ�Ÿ ���
		eISC_AV_BODY = 25, // �ƹ�Ÿ �ٵ�
		eISC_AV_HANDS = 26, // �ƹ�Ÿ ��
		eISC_AV_WAIST = 27, // �ƹ�Ÿ �㸮
		eISC_AV_LEGS = 28, // �ƹ�Ÿ �ٸ�
		eISC_AV_FEET = 29, // �ƹ�Ÿ ��
		eISC_AV_BACK = 30, // �ƹ�Ÿ ��
		eISC_AV_EFFECT = 31, // �ƹ�Ÿ ����Ʈ
		eISC_AV_SKINCOLOR = 32, // �ƹ�Ÿ �Ǻλ�
		eISC_AV_END = 33, // �ƹ�Ÿ ��
		eEND_EItemSubclass
	}; // EItemSubclass 



	enum EMechanic // �������
	{
		eBEGIN_EMechanic = 0,
		/* ���� ��ȭ�� ���� �з� */
		eMECHANIC_NONE = 1, // �̻� ����
		/* ������½� �ൿ�� �Ұ����ϸ� ���� ���ݿ� �������� �Դ´�. */
		eMECHANIC_FREEZE = 2, // ���� ����
		/* ȭ�� ���½� ���� �ð����� �������� ���������� �Դ´�. */
		eMECHANIC_BLAZE = 3, // ȭ�� ����
		/* ���ο� ���½� �ൿ�ӵ��� ����Ȯ���� �������� �ȴ�. */
		eMECHANIC_SLOW = 4, // ���ο� ����
		/* �Ǹ� ���½� ���� �κ��� �����ϰ� ȭ���� ������ �ʴ´�. */
		eMECHANIC_BLIND = 5, // �Ǹ� ����
		/* �̲����� ���½� �̵�Ű�Է°� �ݴ� �������� �̵��ϰ� �ȴ�. */
		eMECHANIC_SLIDE = 6, // �̲����� ����
		/* ��ȭ ���½� �ൿ�� �Ұ����ϸ� ���� ���ݿ� �������� �Դ´�. */
		eMECHANIC_STONE = 7, // ��ȭ ����
		/* �� ���½� ���� �ð����� �������� ���������� �Դ´�. */
		eMECHANIC_POISON = 8, // �� ����
		eEND_EMechanic
	}; // EMechanic 



	enum EModifier // �������
	{
		eBEGIN_EModifier = 0,
		/* �ƹ�Ÿ�� �ɷ�ġ�� ������ ����Ʈ�̴�. */
		eMOD_NONE = 1, // NONE
		/* add, pct */
		eMOD_HP = 2, // HP
		/* add, pct */
		eMOD_HP_MAX = 3, // HP MAX
		/* add, pct */
		eMOD_HP_REGEN = 4, // HP REGEN
		/* add, pct */
		eMOD_MP = 5, // MP ȸ��
		/* add, pct */
		eMOD_MP_MAX = 6, // MP MAX
		/* add, pct */
		eMOD_MP_REGEN = 7, // MP_REGEN
		/* add, pct */
		eMOD_STAT_ALL = 8, // ��� ����
		/* add, pct */
		eMOD_STAT_STR = 9, // ��
		/* add, pct */
		eMOD_STAT_STA = 10, // ü��
		/* add, pct */
		eMOD_STAT_AGI = 11, // ��ø
		/* add, pct */
		eMOD_STAT_INT = 12, // ����
		/* add, pct */
		eMOD_STAT_MEN = 13, // ����
		/* pct */
		eMOD_RESIST_ALL = 14, // ��� ���׷�
		/* pct */
		eMOD_RESIST_WATER = 15, // ���Ӽ����׷�
		/* pct */
		eMOD_RESIST_FIRE = 16, // ȭ�Ӽ����׷�
		/* pct */
		eMOD_RESIST_LIGHT = 17, // ��Ӽ����׷�
		/* pct */
		eMOD_RESIST_DARK = 18, // �ϼӼ����׷�
		/* pct */
		eMOD_PHYSIC_ATK = 19, // �������ݷ�
		/* pct */
		eMOD_PHYSIC_DEF = 20, // ��������
		/* pct */
		eMOD_PHYSIC_CRIT_CHANCE = 21, // ����ũ��Ƽ��Ȯ��
		/* pct */
		eMOD_MAGIC_ATK = 22, // �������ݷ�
		/* pct */
		eMOD_MAGIC_DEF = 23, // ��������
		/* pct */
		eMOD_MAGIC_CRIT_CHANCE = 24, // ����ũ��Ƽ��Ȯ��
		/* pct */
		eMOD_ATTACK_SPEED = 25, // ���ݼӵ�
		/* pct */
		eMOD_CAST_SPEED = 26, // ĳ���üӵ�
		/* pct */
		eMOD_MOVE_SPEED = 27, // �̵��ӵ�
		/* pct */
		eMOD_JUMP_FACTOR = 28, // ������
		eMOD_MAX = 29, // �ִ�MOD
		eEND_EModifier
	}; // EModifier 



	enum EModValueType // �������
	{
		eBEGIN_EModValueType = 0,
		eMODVALUE_BASE = 1, // �⺻��
		eMODVALUE_ADD = 2, // ADD
		eMODVALUE_PCT = 3, // PERCENTAGE
		eMODVALUE_MAX = 4, // HP REGEN
		eEND_EModValueType
	}; // EModValueType 



	enum ESkillCastType // �������
	{
		eBEGIN_ESkillCastType = 0,
		/* ��� ��� �����Ѵ�. */
		eCAST_INSTANT = 1, // ���
		/* ���������� �����Ѵ�. */
		eCAST_CASTING = 2, // ĳ����
		/* �⸦ ������ ����ȴ�. */
		eCAST_CHARGING = 3, // ��¡
		/* ��ġ�� �������� �����Ѵ�. */
		eCAST_LOCATING = 4, // ��ġ����
		/* ����� �����ϰ� �����Ѵ�. */
		eCAST_TARGETING = 5, // �������
		eEND_ESkillCastType
	}; // ESkillCastType 



	enum ESkillType // �������
	{
		eBEGIN_ESkillType = 0,
		/* ��Ƽ�꽺ų */
		eSKILL_ACTIVE = 1, // ACTIVE
		/* �нú꽺ų */
		eSKILL_PASSIVE = 2, // PASSIVE
		eEND_ESkillType
	}; // ESkillType 



	enum ETarget // �������
	{
		eBEGIN_ETarget = 0,
		eTARGET_NONE = 1, // NONE
		/* ���ο��� �����Ѵ�. */
		eTARGET_SELF = 2, // ����
		/* ��Ƽ �׷��� ���ο��� �����Ѵ� */
		eTARGET_MEMBER = 3, // ��Ƽ ����
		/* ��Ƽ �׷쿡�� �����Ѵ� */
		eTARGET_GROUP = 4, // ��Ƽ �׷�
		/* ��/������Ʈ/Ʈ���� �����Ѵ�. PVP�� �ٸ����� MOB ���� �з��Ѵ�. */
		eTARGET_ENEMY = 5, // ��
		eEND_ETarget
	}; // ETarget 





struct jEXCEL_LIB_API Sys_Avatar /* ������� */
{
	/*  �ƹ�Ÿ sid */
	Sys_Avatar_id_t m_asid; // �ƹ�Ÿ ID min_max(,)
		typedef Sys_Avatar_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_asid; }
	void SetPrimaryKey(primary_key_t id) { m_asid = id; }
	/*  �ƹ�Ÿ �̸� */
	tname32_t m_name; // �ƹ�Ÿ �̸� min_max(,)
	/*  NULL */
	EAvatarClass m_baseclass; // �ƹ�Ÿ �������� min_max(,EAvatarClass)
	/*  NULL */
	EAvatarSubclass m_subclass; // �ƹ�Ÿ �������� min_max(,EAvatarSubclass)
	/*  default value */
	int32 m_hp_max; // HP min_max(0,)
	/*  default value */
	int32 m_mp_max; // MP min_max(0,)
	/*  1�д� ȸ���Ǵ� hp */
	int32 m_hp_regen; // HPȸ�� �ӵ� min_max(,)
	/*  1�д� ȸ���Ǵ� mp */
	int32 m_mp_regen; // MPȸ�� �ӵ� min_max(,)
	/*  default value */
	int32 m_st_str; // �� min_max(0,)
	/*  default value */
	int32 m_st_sta; // ��ø min_max(0,)
	/*  default value */
	int32 m_st_agi; // ü�� min_max(0,)
	/*  default value */
	int32 m_st_int; // ���� min_max(0,)
	/*  default value */
	int32 m_st_men; // ���ŷ� min_max(0,)
	int32 m_reation_aerial_type; // �������Ÿ�� min_max(,)
	int32 m_reation_blow_type; // ��������Ÿ�� min_max(,)
	int32 m_reation_push_type; // �з�����Ÿ�� min_max(,)
	/*  default value */
	int32 m_physic_atk; // ���� ���ݷ� min_max(,)
	/*  default value */
	int32 m_physic_def; // ���� ���� min_max(,)
	/*  default value */
	float m_physic_crit; // ���� ũ��Ƽ�� Ȯ�� min_max(,)
	/*  default value */
	int32 m_magic_atk; // ���� ���ݷ� min_max(,)
	/*  default value */
	int32 m_magic_def; // ���� ���� min_max(,)
	/*  default value */
	float m_magic_crit; // ���� ũ��Ƽ�� Ȯ�� min_max(,)
	/*  default value */
	float m_attack_speed; // ���� �ӵ� min_max(,)
	/*  default value */
	float m_casting_speed; // ĳ���� �ӵ� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	float m_move_speed; // �̵��ӵ� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	float m_dash_speed; // �뽬�ӵ� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	float m_hit_chance; // ���� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	float m_avoid_chance; // ȸ�� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	float m_jumpFactor; // ������ min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	int32 m_resist_fire; // ȭ�Ӽ� ���׷� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	int32 m_resist_water; // ���Ӽ� ���׷� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	int32 m_resist_light; // ��Ӽ� ���׷� min_max(,)
	/*  �Ǽ��� %�� ǥ�� */
	int32 m_resist_dark; // �ϼӼ� ���׷� min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo1; // �޺�����1 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo2; // �޺�����2 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo3; // �޺�����3 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo4; // �޺�����4 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo5; // �޺�����5 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_jump_atk; // �������� min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_dash_atk; // �뽬���� min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo1_2h; // ����޺�����1 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo2_2h; // ����޺�����2 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo3_3h; // ����޺�����3 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo4_2h; // ����޺�����4 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_combo5_2h; // ����޺�����5 min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_jump_atk_2h; // ����������� min_max(,)
	/*  skill id */
	Sys_Skill_id_t m_dash_atk_2h; // ��մ뽬���� min_max(,)
	/*  xml���� �ҷ� ���� �ƹ�Ÿ �ɼ� �̸� */
	tname32_t m_xmlname; // �ƹ�Ÿ xml ���� �̸� min_max(,)
	/*  ������ �̸� �� ���(kfm) */
	tname256_t m_fkmname; // ���� �̸� �� ��� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
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

struct jEXCEL_LIB_API Sys_Item /* ������� */
{
	/*  �������� sid */
	Sys_Item_id_t m_isid; // ������ ID min_max(,)
		typedef Sys_Item_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �������� name */
	tname32_t m_name; // ������ �̸� min_max(,)
	/*  NULL */
	EItemClass m_category; // ������ ��з� min_max(,EItemClass)
	/*  NULL */
	EItemSubclass m_subcategory; // ������ �Һз� min_max(,EItemSubclass)
	/*  �Ϲ�_ ����_ ��Ʈ_ ����_ ����ũ_ ���� */
	EItemGrade m_grade; // ������ ��� min_max(,EItemGrade)
	/*  ���ϱ�_ �ϱ�_ �߱�_ ���_ �ֻ�� */
	EItemQuality m_quality; // ������ ǰ�� min_max(,EItemQuality)
	/*  �ͼ� ����_ ȹ�� �� �ͼ�_ ���� �� �ͼ� */
	EItemBind m_bind_type; // ������ �ͼ� ���� min_max(,EItemBind)
	/*  NULL */
	EAvatarParts m_part; // ������ ���� ���� min_max(,EAvatarParts)
	/*  ���� ����_��� ���� ������� �з� */
	EAvatarClass m_reqClass; // ������ ��� �������� min_max(,EAvatarClass)
	/*  ���� ������ �з� */
	EAvatarSubclass m_reqSubclass; // ������ ��� �������� min_max(,EAvatarSubclass)
	/*  �������� �����Ҽ� �ִ� �ִ� ���� */
	int32 m_maxCount; // ������ �ִ� ���� ���� min_max(,)
	/*  �κ��丮 ��ĭ�� �ִ� ����_ �ִ� 99�� */
	int32 m_stackCount; // ������ �ִ� ���� ���� min_max(1,99)
	/*  ���� ���� ���� */
	int32 m_buyPrice; // ������ ���� ���� min_max(,)
	/*  ���� �Ǹ� ���� */
	int32 m_sellPrice; // ������ �Ǹ� ���� min_max(,)
	/*  ������ x ���� ���� */
	int32 m_repairPrice; // ������ ���� ���� min_max(,)
	/*  ĳ�� ���� ���� */
	int32 m_reqCash; // ������ ĳ�� ���� min_max(,)
	/*  ������ ��� ���� ���� */
	int32 m_reqLevel; // ������ ��� ���� min_max(1,60)
	/*  �ְ� ������ ǥ�� */
	int32 m_durability; // ������ ������ min_max(,)
	/*  �Ⱓ�� �������� ��� �Ⱓ_ ��(Min)���� */
	int32 m_activeTime; // ������ Ȱ�� ���� �ð�(��밡�ɱⰣ) min_max(,)
	/*  ������ ���� ����� ��ų */
	int32 m_trigger_skill; // ������ ���� ���� ��ų min_max(,)
	/*  ������ ����(dds) */
	tname256_t m_iconname; // ������ ������ min_max(,)
	/*  ������ ����� �������� ������Ʈ */
	tname128_t m_delegate; // ������ ��� ������Ʈ min_max(,)
	/*  ������ �̸��� ���(nif) */
	tname256_t m_filename; // ������ ���ҽ� ����(����� ������Ʈ) min_max(,)
	/*  xml���� �ҷ����� ������ �ɼ� �̸� */
	tname32_t m_xmlname; // ������ �ɼ� xml ���� �̸� min_max(,)
	/*  Sys_LocaleText.csv ���� ȭ�鿡 ��µǴ� ������ ���� */
	tname32_t m_description; // ������ �˾� ����â min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
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

struct jEXCEL_LIB_API Sys_Skill /* ������� */
{
	/*  ��ų�� sid */
	Sys_Skill_id_t m_ssid; // ��ų ID min_max(,)
		typedef Sys_Skill_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_ssid; }
	void SetPrimaryKey(primary_key_t id) { m_ssid = id; }
	/*  ��ų�� name */
	tname32_t m_name; // ��ų �̸� min_max(,)
	/*  ��ų ���� */
	skill_level_t m_level; // ��ų ���� min_max(,)
	/*  ��ų�� ���� �ִ� �ִ� ���� */
	int32 m_maxLevel; // ��ų �ִ� ���� min_max(,)
	/*  NULL */
	int32 m_reqLevel; // ��ų ���� �ִ� �ƹ�Ÿ���� min_max(,)
	/*  NULL */
	int32 m_reqGold; // ��ų ȹ�� �� �ʿ� GOLD min_max(,)
	/*  NULL */
	int32 m_reqSP; // ��ų �������� �ʿ� SP min_max(,)
	/*  NULL */
	Sys_Item_id_t m_reqItem; // ��ų ���� �ʿ� ������ min_max(,)
	/*  NULL */
	int32 m_costHP; // ��ų ���� �Ҹ�Ǵ� hp min_max(,)
	/*  NULL */
	int32 m_costMP; // ��ų ���� �Ҹ�Ǵ� mp min_max(,)
	/*  NULL */
	Sys_Item_id_t m_costItem; // ��ų ���� �Ҹ�Ǵ� ������ min_max(,)
	/*  ���/�ֱ���/������ */
	ESkillType m_type; // ��ų Ÿ�� min_max(,ESkillType)
	/*  ���/����/ĳ���� */
	ESkillCastType m_castingType; // ��ų ĳ���� Ÿ�� min_max(,ESkillCastType)
	/*  NULL */
	int32 m_castingAnim; // ��ų ĳ���þִϸ��̼� min_max(,)
	/*  ���� : �� */
	float m_castingTime; // ��ų ���� �ð� min_max(,)
	float m_chargingTime; // ��¡ �ִ� �ð� min_max(,)
	/*  ��¡ �����ϸ� ���� �� �⺻ �������� �����ش�. */
	float m_chargingMutiplier; // ��¡ ������������ min_max(,)
	/*  ���� : �� */
	float m_coolTime; // ��ų ���� �ð� min_max(,)
	/*  NULL */
	int32 m_skillAnim; // ��ų �ִϸ��̼� min_max(,)
	/*  ����/�׷�/�� */
	ETarget m_target; // ��ų ������ min_max(,ETarget)
	/*  ��ų ���� Ÿ�� */
	EAttackType m_attackType; // ��ų ���� ���׼� Ÿ�� min_max(,EAttackType)
	/*  ��ų ���� Ÿ�� ��ġ */
	float m_attackRate; // ���� ���׼� ���� min_max(,)
	/*  �ƹ�Ÿ ��ġ�� + �Ͽ� ��� */
	float m_hit_chance; // ��ų ���߷� min_max(,)
	/*  �ƹ�Ÿ ��ġ�� + �Ͽ� ��� */
	float m_critical_chance; // ��ų ũ��Ƽ�� Ȯ�� min_max(,)
	/*  ��ų ȿ�� ���� ����(����m) */
	float m_effectRange; // ��ų ȿ�� ���� min_max(,)
	float m_effectDuration; // ȿ�� ���� �ð� min_max(,)
	tname32_t m_effect; // ȿ�� min_max(,)
	/*  NULL */
	tname32_t m_castingFX; // ��ų ĳ����FX min_max(,)
	/*  NULL */
	tname32_t m_skillFX; // ��ų �⺻ FX min_max(,)
	tname32_t m_chargingFX; // ��ƿ ��¡ FX min_max(,)
	/*  NULL */
	tname32_t m_collisionFX; // ��ų �浹 FX min_max(,)
	/*  NULL */
	tname32_t m_targetFX; // ��ų Ÿ�� FX min_max(,)
	/*  Sys_LocaleText.csv ���� ȭ�鿡 ��µǴ� ��ų ���� */
	tname256_t m_description; // ����â min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
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
