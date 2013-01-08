/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nTESTSERVER___filename_sam_hero_
#define __namespace_nTESTSERVER___filename_sam_hero_

#include "table_const_sam_hero.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nTESTSERVER_sam_hero_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EDeckYear,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroCategory,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroEngagementtype,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroFacetype,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroPersonality,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroSex,�������,nMech,nTESTSERVER)\
	ENUM_TABLE(EHeroWorkState,�������,nMech,nTESTSERVER)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nTESTSERVER_EDeckYear_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(DY_189			,1,189�� ī�� ��,nMech,nTESTSERVER,EDeckYear)\
		ENUM_FIELD(DY_192			,2,192�� ī�� ��,nMech,nTESTSERVER,EDeckYear)\

	/* ������� */
	#define for_each_nTESTSERVER_EHeroCategory_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HC_HISTORICAL			,1,���� ���,nMech,nTESTSERVER,EHeroCategory)\
		ENUM_FIELD(HC_VIRTAUL			,2,���� ���,nMech,nTESTSERVER,EHeroCategory)\

	/* ������� */
	#define for_each_nTESTSERVER_EHeroEngagementtype_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HE_COMMON			,1,�Ϲ�,nMech,nTESTSERVER,EHeroEngagementtype)\
		ENUM_FIELD(HE_RARE			,2,���,nMech,nTESTSERVER,EHeroEngagementtype)\

	/* ������� */
	#define for_each_nTESTSERVER_EHeroFacetype_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HF_ORIGINAL			,1,���̹������,nMech,nTESTSERVER,EHeroFacetype)\
		ENUM_FIELD(HF_COMMON			,2,�����̹������,nMech,nTESTSERVER,EHeroFacetype)\
		ENUM_FIELD(HF_MONTAGE			,3,����(��Ÿ��) �̹���,nMech,nTESTSERVER,EHeroFacetype)\
		ENUM_FIELD(HF_UPLOAD			,4,���� ��� �̹���,nMech,nTESTSERVER,EHeroFacetype)\

	/* ������� */
	#define for_each_nTESTSERVER_EHeroPersonality_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HP_TOUGH			,1,����,nMech,nTESTSERVER,EHeroPersonality)\
		ENUM_FIELD(HP_BRAVE			,2,���,nMech,nTESTSERVER,EHeroPersonality)\
		ENUM_FIELD(HP_COOL			,3,����,nMech,nTESTSERVER,EHeroPersonality)\
		ENUM_FIELD(HP_WEAK			,4,�ҽ�,nMech,nTESTSERVER,EHeroPersonality)\

	/* ������� */
	#define for_each_nTESTSERVER_EHeroSex_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HS_MALE			,1,����,nMech,nTESTSERVER,EHeroSex)\
		ENUM_FIELD(HS_FEMALE			,2,����,nMech,nTESTSERVER,EHeroSex)\

	/* ������� */
	#define for_each_nTESTSERVER_EHeroWorkState_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(HWS_REST			,1,�޽�,nMech,nTESTSERVER,EHeroWorkState)\
		ENUM_FIELD(HWS_CONSTRUCTION			,2,�ǹ� �Ǽ�,nMech,nTESTSERVER,EHeroWorkState)\
		ENUM_FIELD(HWS_EXPLORATION			,3,Ž�� Ȱ��,nMech,nTESTSERVER,EHeroWorkState)\
		ENUM_FIELD(HWS_COMBAT			,4,�δ� ����,nMech,nTESTSERVER,EHeroWorkState)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Hero,��� ���̺�,nMech,nTESTSERVER)\



	// ------------------------------------------------------------
	// Sys_Hero �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD
	#define for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(FIELD)\
		FIELD(hsid                   ,sid                ,Sys_Hero_id_t                ,0 , Sys_Hero_id_t , Sys_Hero_id_t , Sys_Hero_id_t)\
		FIELD(category               ,��� �з�              ,EHeroCategory                ,1 , EHeroCategory , EHeroCategory , EHeroCategory)\
		FIELD(deck_year              ,ī�� ����              ,EDeckYear                    ,2 , EDeckYear , EDeckYear , EDeckYear)\
		FIELD(name                   ,��� ���� �̸�           ,tname32_t                    ,3 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,��� �ѱ� �̸�           ,wname32_t                    ,4 , wcstr , wcstr , w32)\
		FIELD(image_file             ,�� �̹���             ,tname256_t                   ,5 , tcstr , tcstr , t256)\
		FIELD(grade                  ,��� ���              ,int32                        ,6 , int32 , int32 , i32)\
		FIELD(age                    ,����                 ,int32                        ,7 , int32 , int32 , i32)\
		FIELD(leadership             ,���                 ,int32                        ,8 , int32 , int32 , i32)\
		FIELD(power                  ,����                 ,int32                        ,9 , int32 , int32 , i32)\
		FIELD(intelligent            ,����                 ,int32                        ,10 , int32 , int32 , i32)\
		FIELD(politic                ,��ġ                 ,int32                        ,11 , int32 , int32 , i32)\
		FIELD(charm                  ,�ŷ�                 ,int32                        ,12 , int32 , int32 , i32)\
		FIELD(is_male                ,����                 ,bool                         ,13 , bool , bool , b)\
		FIELD(personality            ,����                 ,EHeroPersonality             ,14 , EHeroPersonality , EHeroPersonality , EHeroPersonality)\

	#endif // for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Hero�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nTESTSERVER_Sys_Hero_InheritedTable
	#define for_each_nTESTSERVER_Sys_Hero_InheritedTable(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Hero_InheritedTable


	// ------------------------------------------------------------
	// Sys_Hero�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited
	#define for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Hero�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_all_member
	#define for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_all_member(FUNC)\
		for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(FUNC)\

	#endif // for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nTESTSERVER 
{

	enum EDeckYear // �������
	{
		eBEGIN_EDeckYear = 0,
		/* 189�� ī�� �� */
		eDY_189 = 1, // 189�� ī�� ��
		/* 192�� ī�� �� */
		eDY_192 = 2, // 192�� ī�� ��
		eEND_EDeckYear
	}; // EDeckYear 



	enum EHeroCategory // �������
	{
		eBEGIN_EHeroCategory = 0,
		/* ���� ��� */
		eHC_HISTORICAL = 1, // ���� ���
		/* ���� ��� */
		eHC_VIRTAUL = 2, // ���� ���
		eEND_EHeroCategory
	}; // EHeroCategory 



	enum EHeroEngagementtype // �������
	{
		eBEGIN_EHeroEngagementtype = 0,
		/* �Ϲ� */
		eHE_COMMON = 1, // �Ϲ�
		/* ��� */
		eHE_RARE = 2, // ���
		eEND_EHeroEngagementtype
	}; // EHeroEngagementtype 



	enum EHeroFacetype // �������
	{
		eBEGIN_EHeroFacetype = 0,
		/* ���� �̹���, ���� ��� */
		eHF_ORIGINAL = 1, // ���̹������
		/* �ߺ� ��밡���� �̹���, �Ϲ� ��� */
		eHF_COMMON = 2, // �����̹������
		/* �� ���ձ⸦ �̿��� ���� */
		eHF_MONTAGE = 3, // ����(��Ÿ��) �̹���
		/* ������ ���ε��� �̹��� */
		eHF_UPLOAD = 4, // ���� ��� �̹���
		eEND_EHeroFacetype
	}; // EHeroFacetype 



	enum EHeroPersonality // �������
	{
		eBEGIN_EHeroPersonality = 0,
		/* ���� */
		eHP_TOUGH = 1, // ����
		/* ��� */
		eHP_BRAVE = 2, // ���
		/* ���� */
		eHP_COOL = 3, // ����
		/* �ҽ� */
		eHP_WEAK = 4, // �ҽ�
		eEND_EHeroPersonality
	}; // EHeroPersonality 



	enum EHeroSex // �������
	{
		eBEGIN_EHeroSex = 0,
		/* ���� ��� */
		eHS_MALE = 1, // ����
		/* ���� ��� */
		eHS_FEMALE = 2, // ����
		eEND_EHeroSex
	}; // EHeroSex 



	enum EHeroWorkState // �������
	{
		eBEGIN_EHeroWorkState = 0,
		/* �ƹ� �ϵ� ���� �ʰ� ���� */
		eHWS_REST = 1, // �޽�
		/* �ǹ� �Ǽ��� ���� �� */
		eHWS_CONSTRUCTION = 2, // �ǹ� �Ǽ�
		/* Ž�� Ȱ���� ���� �� */
		eHWS_EXPLORATION = 3, // Ž�� Ȱ��
		/* �δ븦 �̲��� �ʵ忡 ���� ���� */
		eHWS_COMBAT = 4, // �δ� ����
		eEND_EHeroWorkState
	}; // EHeroWorkState 





struct jEXCEL_LIB_API Sys_Hero /* ��� ���̺� */
{
	/*  ����� �Ҽ��� ����(���� ������ �Ҽ� ���°� ����) */
	Sys_Hero_id_t m_hsid; // sid min_max(,)
	/*  ��� �з� ����, ���� ���, ���� ��� */
	EHeroCategory m_category; // ��� �з� min_max(,EHeroCategory)
	/*  ��� ������ ī�� �� �̸� */
	EDeckYear m_deck_year; // ī�� ���� min_max(,EDeckYear)
	/*  ��� ���� �̸� */
	tname32_t m_name; // ��� ���� �̸� min_max(,)
	/*  ��� �ѱ� �̸� */
	wname32_t m_name_kor; // ��� �ѱ� �̸� min_max(,)
	/*  ��� �ʻ�ȭ �̹��� */
	tname256_t m_image_file; // �� �̹��� min_max(,)
	/*  ��� ���, 1�� ~ 7������ ( ���� Sys_HeroGrade_id_t) */
	int32 m_grade; // ��� ��� min_max(,)
	int32 m_age; // ���� min_max(1,99)
	int32 m_leadership; // ��� min_max(1,200)
	int32 m_power; // ���� min_max(1,200)
	int32 m_intelligent; // ���� min_max(1,200)
	int32 m_politic; // ��ġ min_max(1,200)
	int32 m_charm; // �ŷ� min_max(1,200)
	/*  ���� */
	bool m_is_male; // ���� min_max(,)
	/*  ��� ���� */
	EHeroPersonality m_personality; // ���� min_max(,EHeroPersonality)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Hero
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  15 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Hero
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Hero();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Hero

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nTESTSERVER_Sys_Hero_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Hero)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Hero
enum { eSTRUCT_SIZE_Sys_Hero = sizeof(Sys_Hero) };


struct CSV_Sys_Hero : public nMech::nUtil::jCSV_File<Sys_Hero>
{
	virtual ~CSV_Sys_Hero(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Hero>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Hero g_Sys_Hero;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EDeckYear[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroCategory[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroEngagementtype[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroFacetype[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroPersonality[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroSex[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EHeroWorkState[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nTESTSERVER 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nTESTSERVER;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nTESTSERVER_sam_hero_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nTESTSERVER;
	for_each_nTESTSERVER_sam_hero_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nTESTSERVER___filename_sam_hero_
