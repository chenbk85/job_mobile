/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_world_
#define __namespace_nEXCEL___filename_excel_world_

#include "table_const_excel_world.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_world_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EIssue_Info,�������,nMech,nEXCEL)\
	ENUM_TABLE(ETile_Sort,�������,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nEXCEL_EIssue_Info_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EII_NORMAL			,1,�Ϲ�,nMech,nEXCEL,EIssue_Info)\
		ENUM_FIELD(EII_NEW			,2,�ű�,nMech,nEXCEL,EIssue_Info)\
		ENUM_FIELD(EII_RECOMMEND			,3,��õ,nMech,nEXCEL,EIssue_Info)\
		ENUM_FIELD(EII_TEST			,4,�׽�Ʈ��,nMech,nEXCEL,EIssue_Info)\

	/* ������� */
	#define for_each_nEXCEL_ETile_Sort_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ETS_ROAD			,1,����,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_MEADOW			,2,�ʿ�,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_LAND			,3,����,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_MOUNT			,4,���,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_RIVER			,5,��,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_SEA			,6,�ٴ�,nMech,nEXCEL,ETile_Sort)\
		ENUM_FIELD(ETS_SWAMP			,7,��,nMech,nEXCEL,ETile_Sort)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Tile,�������,nMech,nEXCEL)\
	STRUCT(Sys_World,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Tile �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Tile_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(FIELD)\
		FIELD(tisid                  ,����ID               ,Sys_Tile_id_t                ,0 , Sys_Tile_id_t , uint16 , u16)\
		FIELD(name                   ,�̸�ID               ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,Ÿ��_�̸�              ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(client_file            ,Ÿ�� �̹���             ,tname256_t                   ,3 , tcstr , tcstr , t256)\
		FIELD(sort                   ,�з�                 ,ETile_Sort                   ,4 , ETile_Sort , ETile_Sort , e)\
		FIELD(mspeed                 ,�̵��ӵ�����             ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(visibility             ,���ðŸ�               ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(build                  ,�Ǽ�����               ,bool                         ,7 , bool , bool , b)\
		FIELD(fskill                 ,ȭ��_��ų_����           ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(wskill                 ,����_��ų_����           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(rskill                 ,����_��ų_����           ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(hiskill                ,����_��ų_����           ,int16                        ,11 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_Tile_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Tile�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Tile_InheritedTable
	#define for_each_nEXCEL_Sys_Tile_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Tile_InheritedTable


	// ------------------------------------------------------------
	// Sys_Tile�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Tile�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Tile_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_World �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_World_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_World_STRUCT_FIELD(FIELD)\
		FIELD(wsid                   ,���� ID              ,Sys_World_id_t               ,0 , Sys_World_id_t , uint16 , u16)\
		FIELD(name                   ,�̸� ID              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,���� �̸�              ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(issue                  ,�̽� ����              ,EIssue_Info                  ,3 , EIssue_Info , EIssue_Info , e)\
		FIELD(address                ,����IP               ,tname32_t                    ,4 , tcstr , tcstr , t32)\
		FIELD(help                   ,��������               ,tname64_t                    ,5 , tcstr , tcstr , t64)\
		FIELD(goldstart              ,�� �����ڿ�             ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(ricestart              ,�ķ� �����ڿ�            ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(treestart              ,���� �����ڿ�            ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(stonestart             ,�� �����ڿ�             ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(ironstart              ,ö �����ڿ�             ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(silkstart              ,��� �����ڿ�            ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(mspeed                 ,�δ��̵��ӵ�����           ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(re_increase            ,�ڿ� ������             ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(buildtime              ,���� �ð�              ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(produtime              ,���� �ð�              ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(recrutime              ,���� �ð�              ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(researchtime           ,���� �ð�              ,int16                        ,17 , int16 , int16 , i16)\
		FIELD(goldamount             ,�� ȹ�淮              ,int16                        ,18 , int16 , int16 , i16)\
		FIELD(peo_increase           ,�α� ����              ,int16                        ,19 , int16 , int16 , i16)\
		FIELD(questbenefit           ,����Ʈ ����             ,int16                        ,20 , int16 , int16 , i16)\
		FIELD(huntbenefit            ,��� ����              ,int16                        ,21 , int16 , int16 , i16)\
		FIELD(appoint_ratio          ,��� ��� Ȯ��           ,int16                        ,22 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_World_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_World�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_World_InheritedTable
	#define for_each_nEXCEL_Sys_World_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_World_InheritedTable


	// ------------------------------------------------------------
	// Sys_World�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_World�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_World_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_World_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_World_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_World_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_World_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EIssue_Info // �������
	{
		eBEGIN_EIssue_Info = 0,
		/* �Ϲ� ���� */
		eEII_NORMAL = 1, // �Ϲ�
		/* �ű� ���� */
		eEII_NEW = 2, // �ű�
		/* ��õ ���� */
		eEII_RECOMMEND = 3, // ��õ
		/* �׽�Ʈ�� ���� */
		eEII_TEST = 4, // �׽�Ʈ��
		eEND_EIssue_Info
	}; // EIssue_Info 



	enum ETile_Sort // �������
	{
		eBEGIN_ETile_Sort = 0,
		/* ���� �� ������ �� */
		eETS_ROAD = 1, // ����
		/* �� */
		eETS_MEADOW = 2, // �ʿ�
		/* ���� */
		eETS_LAND = 3, // ����
		/* ��� */
		eETS_MOUNT = 4, // ���
		/* ���� */
		eETS_RIVER = 5, // ��
		/* �ٴ� */
		eETS_SEA = 6, // �ٴ�
		/* �� */
		eETS_SWAMP = 7, // ��
		eEND_ETile_Sort
	}; // ETile_Sort 





struct jEXCEL_LIB_API Sys_Tile /* ������� */
{
	Sys_Tile_id_t m_tisid; // ����ID min_max(,)
	tname32_t m_name; // �̸�ID min_max(,)
	tname32_t m_name_kor; // Ÿ��_�̸� min_max(,)
	tname256_t m_client_file; // Ÿ�� �̹��� min_max(,)
	/*  ���� �ؽ��� ���� */
	ETile_Sort m_sort; // �з� min_max(,ETile_Sort)
	/*  ���� �̵��ӵ� ���� (%���������� 500.0% ����) */
	int16 m_mspeed; // �̵��ӵ����� min_max(0,5000)
	/*  ������ �þ� ���� */
	int16 m_visibility; // ���ðŸ� min_max(-100,100)
	/*  �Ǽ� ������ �ȵ� ���� ���� */
	bool m_build; // �Ǽ����� min_max(0,1)
	/*  �� �Ӽ� ��ų ������ */
	int16 m_fskill; // ȭ��_��ų_���� min_max(-999,999)
	/*  �� �Ӽ� ��ų ������ */
	int16 m_wskill; // ����_��ų_���� min_max(-999,999)
	/*  �� �Ӽ� ��ų ������ */
	int16 m_rskill; // ����_��ų_���� min_max(-999,999)
	/*  ���� ��ų ������ */
	int16 m_hiskill; // ����_��ų_���� min_max(-999,999)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Tile
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  12 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Tile
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Tile();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Tile

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Tile_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Tile)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Tile
enum { eSTRUCT_SIZE_Sys_Tile = sizeof(Sys_Tile) };


struct CSV_Sys_Tile : public nMech::nUtil::jCSV_File<Sys_Tile>
{
	virtual ~CSV_Sys_Tile(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Tile>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Tile g_Sys_Tile;

struct jEXCEL_LIB_API Sys_World /* ������� */
{
	/*  ���� ���� �������� ��ȣ ���� */
	Sys_World_id_t m_wsid; // ���� ID min_max(,)
	/*  �����̸� ID */
	tname32_t m_name; // �̸� ID min_max(,)
	/*  ���� ���� ����Ʈ�� ǥ�õǴ� ���� �̸� */
	tname32_t m_name_kor; // ���� �̸� min_max(,)
	/*  �������� �˸��� ���� ��Ȳ. ������ �̹����� ǥ�� */
	EIssue_Info m_issue; // �̽� ���� min_max(,EIssue_Info)
	/*  ���� �ּ� */
	tname32_t m_address; // ����IP min_max(,)
	/*  ��Ÿ���� */
	tname64_t m_help; // �������� min_max(,)
	/*  ó�� ���۽��� ���ڿ��� */
	int16 m_goldstart; // �� �����ڿ� min_max(0,999)
	/*  ó�� ���۽��� �����ڿ��� */
	int16 m_ricestart; // �ķ� �����ڿ� min_max(0,999)
	/*  ó�� ���۽��� ���ڿ��� */
	int16 m_treestart; // ���� �����ڿ� min_max(0,999)
	/*  ó�� ���۽��� ���ڿ��� */
	int16 m_stonestart; // �� �����ڿ� min_max(0,999)
	/*  ó�� ���۽��� ���ڿ��� */
	int16 m_ironstart; // ö �����ڿ� min_max(0,999)
	/*  ó�� ���۽��� ���ڿ��� */
	int16 m_silkstart; // ��� �����ڿ� min_max(0,999)
	/*  �����ʿ����� �δ� �̵� �ӵ� (�⺻ 100���� ����) 1000�ʿ� 100Ÿ�� �̵� */
	int16 m_mspeed; // �δ��̵��ӵ����� min_max(-999,999)
	/*  �� �ڿ�ä��� �ǹ������� �ð��� �ڿ� ä�뷮 ������. (�⺻ 100���� ����) */
	int16 m_re_increase; // �ڿ� ������ min_max(-999,999)
	/*  �ǹ��� ����, ���׷��̵� �ҿ� �ð� ������. (�⺻ 100���� ����) */
	int16 m_buildtime; // ���� �ð� min_max(-999,999)
	/*  �ǹ������� ����, ��Ÿ ����ǰ���� ���� �ð� ������. (�⺻ 100���� ����) */
	int16 m_produtime; // ���� �ð� min_max(-999,999)
	/*  �ǹ������� ���� ���� �ð� ������. (�⺻ 100���� ����) */
	int16 m_recrutime; // ���� �ð� min_max(-999,999)
	/*  ���� ���� �ð� ������. (�⺻ 100���� ����) */
	int16 m_researchtime; // ���� �ð� min_max(-999,999)
	/*  �ǹ������� ���� ¡������ �� ȹ�淮 ������. (�⺻ 100���� ����) */
	int16 m_goldamount; // �� ȹ�淮 min_max(-999,999)
	/*  �ǹ������� �α� ������ ������. (�⺻ 100���� ����) */
	int16 m_peo_increase; // �α� ���� min_max(-999,999)
	/*  ����Ʈ ���� ���� ���󳻿� ������. (�⺻ 100���� ����) */
	int16 m_questbenefit; // ����Ʈ ���� min_max(-999,999)
	/*  ���(PVE)���� �¸� ���� ���󳻿� ������. (�⺻ 100���� ����) */
	int16 m_huntbenefit; // ��� ���� min_max(-999,999)
	/*  ��� ��� �õ��� ������ Ȯ�� ������. (�⺻ 100���� ����) */
	int16 m_appoint_ratio; // ��� ��� Ȯ�� min_max(-999,999)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_World
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_World_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  23 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_World
		jEXCEL_TABLE_COMMON_CODE_H_Sys_World();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_World

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_World_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_World)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_World
enum { eSTRUCT_SIZE_Sys_World = sizeof(Sys_World) };


struct CSV_Sys_World : public nMech::nUtil::jCSV_File<Sys_World>
{
	virtual ~CSV_Sys_World(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_World>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_World g_Sys_World;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EIssue_Info[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ETile_Sort[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_world_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_world_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_world_
