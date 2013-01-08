/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_user_
#define __namespace_nEXCEL___filename_excel_user_

#include "table_const_excel_user.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_user_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EBuildType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EOutput,�������,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nEXCEL_EBuildType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBT_Sys_T_HQ			,1,����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Bar			,2,����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_ACADEMY			,3,����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_PEACE			,4,ġ�Ⱥ�,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SHRINE			,5,���,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_HIDEOUT			,6,������,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_TRADINGPOST			,7,������,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_House			,8,�ΰ�,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Farm			,9,����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SAWMILL			,10,�����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_QUARRY			,11,ä����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_MINING			,12,������,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_COCOONERY			,13,�����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Barrack			,14,����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SMITHY			,15,���尣,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_FORGE			,16,����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_STABLE			,17,������,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Camp			,18,�п�,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_Sys_T_Depot			,19,â��,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_SECRET			,20,���â��,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_TOWER			,21,����,nMech,nEXCEL,EBuildType)\
		ENUM_FIELD(EBT_BARRIER			,22,�溮,nMech,nEXCEL,EBuildType)\

	/* ������� */
	#define for_each_nEXCEL_EOutput_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EOT_POPULATION			,1,�α�,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_GOLD			,2,��,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_FOOD			,3,�ķ�,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_TREE			,4,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_STONE			,5,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_IRON			,6,ö��,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SILK			,7,���,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SOLDIER			,8,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_PIKE			,9,â ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_HEAVY			,10,�߰� ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_HALBERD			,11,����� ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_BOW			,12,�� ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_CROSSBOW			,13,�� ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_BOWGUN			,14,���� ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_BALLISTA			,15,���� ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_CHARIOT			,16,���� ����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_WAGON			,17,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_HORSE			,18,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_WHEELBARROW			,19,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_CART			,20,���,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_LADDER			,21,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_RAM			,22,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_TOWER			,23,����,nMech,nEXCEL,EOutput)\
		ENUM_FIELD(EOT_SIEGE_TREBUCHET			,24,������,nMech,nEXCEL,EOutput)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys__T_BuildObj,����type ���̺��� base ���̺��̴�. ��� ����type ���̺��� �� ���̺��� ��ӹ޴´�,nMech,nEXCEL)\
	STRUCT(Sys_T_Bar,�������,nMech,nEXCEL)\
	STRUCT(Sys_T_Barrack,�������,nMech,nEXCEL)\
	STRUCT(Sys_T_Camp,�������,nMech,nEXCEL)\
	STRUCT(Sys_T_Depot,�������,nMech,nEXCEL)\
	STRUCT(Sys_T_Farm,�������,nMech,nEXCEL)\
	STRUCT(Sys_T_House,�������,nMech,nEXCEL)\
	STRUCT(Sys_T_HQ,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys__T_BuildObj �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD
	#define for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(FIELD)\
		FIELD(base_type              ,�ǹ�Ÿ��               ,EBuildType                   ,0 , EBuildType , EBuildType , e)\
		FIELD(name                   ,�ǹ����ҽ���             ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys__T_BuildObj�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_InheritedTable
	#define for_each_nEXCEL_Sys__T_BuildObj_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_InheritedTable


	// ------------------------------------------------------------
	// Sys__T_BuildObj�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys__T_BuildObj�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Bar �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,����                 ,Sys_T_Bar_id_t               ,0 , Sys_T_Bar_id_t , uint16 , u16)\
		FIELD(client_file            ,�ǹ� �̹��� ����          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,�ִ� ������             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,�ٿ�׷��̵巹��           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,���� ��ȯ���            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,�� ��ȯ���             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,ö ��ȯ���             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,��� ��ȯ���            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,�α� ��ȯ���            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(hideHero               ,��� ���              ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(resettime              ,���½ð�               ,uint32                       ,16 , uint32 , uint32 , i32)\
		FIELD(itemnum                ,�����ۼ�               ,int16                        ,17 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Bar�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Bar_InheritedTable
	#define for_each_nEXCEL_Sys_T_Bar_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Bar_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Bar�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Bar�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Barrack �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,����                 ,Sys_T_Barrack_id_t           ,0 , Sys_T_Barrack_id_t , uint16 , u16)\
		FIELD(client_file            ,�ǹ� �̹��� ����          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,�ִ� ������             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,�ٿ�׷��̵巹��           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,���� ��ȯ���            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,�� ��ȯ���             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,ö ��ȯ���             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,��� ��ȯ���            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,�α� ��ȯ���            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(s_p_speed              ,����_����_�ӵ�           ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(s_p_cost               ,����_����_���           ,int16                        ,16 , int16 , int16 , i16)\
		FIELD(s_output               ,����_ ���귮            ,int16                        ,17 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Barrack�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_InheritedTable
	#define for_each_nEXCEL_Sys_T_Barrack_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Barrack�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Barrack�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Camp �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,����                 ,Sys_T_Camp_id_t              ,0 , Sys_T_Camp_id_t , uint16 , u16)\
		FIELD(client_file            ,�ǹ� �̹��� ����          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,�ִ� ������             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,�ٿ�׷��̵巹��           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,���� ��ȯ���            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,�� ��ȯ���             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,ö ��ȯ���             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,��� ��ȯ���            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,�α� ��ȯ���            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(f_r_spend              ,����_ �ķ�_�Һ�         ,int16                        ,15 , int16 , int16 , i16)\
		FIELD(f_storage              ,����_������             ,int32                        ,16 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Camp�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Camp_InheritedTable
	#define for_each_nEXCEL_Sys_T_Camp_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Camp_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Camp�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Camp�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Depot �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,����                 ,Sys_T_Depot_id_t             ,0 , Sys_T_Depot_id_t , uint16 , u16)\
		FIELD(client_file            ,�ǹ� �̹��� ����          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,�ִ� ������             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,�ٿ�׷��̵巹��           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,���� ��ȯ���            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,�� ��ȯ���             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,ö ��ȯ���             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,��� ��ȯ���            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,�α� ��ȯ���            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(storage                ,�ִ뺸����              ,int32                        ,15 , int32 , int32 , i32)\

	#endif // for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Depot�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Depot_InheritedTable
	#define for_each_nEXCEL_Sys_T_Depot_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Depot_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Depot�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Depot�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_Farm �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,����                 ,Sys_T_Farm_id_t              ,0 , Sys_T_Farm_id_t , uint16 , u16)\
		FIELD(client_file            ,�ǹ� �̹��� ����          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,�ִ� ������             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,�ٿ�׷��̵巹��           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,���� ��ȯ���            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,�� ��ȯ���             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,ö ��ȯ���             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,��� ��ȯ���            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,�α� ��ȯ���            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(foodoutput             ,�ķ����귮              ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_Farm�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_Farm_InheritedTable
	#define for_each_nEXCEL_Sys_T_Farm_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Farm_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_Farm�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_Farm�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_House �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_House_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,����                 ,Sys_T_House_id_t             ,0 , Sys_T_House_id_t , uint16 , u16)\
		FIELD(client_file            ,�ǹ� �̹��� ����          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,�ִ� ������             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,�ٿ�׷��̵巹��           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,���� ��ȯ���            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,�� ��ȯ���             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,ö ��ȯ���             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,��� ��ȯ���            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,�α� ��ȯ���            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(maxpopulation          ,�ΰ��ִ��α�             ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_House_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_House�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_House_InheritedTable
	#define for_each_nEXCEL_Sys_T_House_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_House_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_House�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_House�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_House_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_T_HQ �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(FIELD)\
		FIELD(isid                   ,����                 ,Sys_T_HQ_id_t                ,0 , Sys_T_HQ_id_t , uint16 , u16)\
		FIELD(client_file            ,�ǹ� �̹��� ����          ,tname256_t                   ,1 , tcstr , tcstr , t256)\
		FIELD(upgradetime            ,���׷��̵� �ð�           ,uint32                       ,2 , uint32 , uint32 , i32)\
		FIELD(tree_num               ,���� ���              ,int16                        ,3 , int16 , int16 , i16)\
		FIELD(stone_num              ,�� ���               ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(iron_num               ,ö ���               ,int16                        ,5 , int16 , int16 , i16)\
		FIELD(silk_num               ,��� ���              ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(population_num         ,�α� ���              ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(maxbuild               ,�ִ� ������             ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(downlevel              ,�ٿ�׷��̵巹��           ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(treereturn             ,���� ��ȯ���            ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(stonereturn            ,�� ��ȯ���             ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(ironreturn             ,ö ��ȯ���             ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(silkreturn             ,��� ��ȯ���            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(populationreturn       ,�α� ��ȯ���            ,int16                        ,14 , int16 , int16 , i16)\
		FIELD(getgold                ,¡��                 ,int16                        ,15 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_T_HQ�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_T_HQ_InheritedTable
	#define for_each_nEXCEL_Sys_T_HQ_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_HQ_InheritedTable


	// ------------------------------------------------------------
	// Sys_T_HQ�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_T_HQ�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EBuildType // �������
	{
		eBEGIN_EBuildType = 0,
		/* ���� */
		eEBT_Sys_T_HQ = 1, // ����
		/* ���� */
		eEBT_Sys_T_Bar = 2, // ����
		/* ���� */
		eEBT_ACADEMY = 3, // ����
		/* ġ�Ⱥ� */
		eEBT_PEACE = 4, // ġ�Ⱥ�
		/* ��� */
		eEBT_SHRINE = 5, // ���
		/* ������ */
		eEBT_HIDEOUT = 6, // ������
		/* ������ */
		eEBT_TRADINGPOST = 7, // ������
		/* �ΰ� */
		eEBT_Sys_T_House = 8, // �ΰ�
		/* ���� */
		eEBT_Sys_T_Farm = 9, // ����
		/* ����� */
		eEBT_SAWMILL = 10, // �����
		/* ä���� */
		eEBT_QUARRY = 11, // ä����
		/* ������ */
		eEBT_MINING = 12, // ������
		/* ����� */
		eEBT_COCOONERY = 13, // �����
		/* ���� */
		eEBT_Sys_T_Barrack = 14, // ����
		/* ���尣 */
		eEBT_SMITHY = 15, // ���尣
		/* ���� */
		eEBT_FORGE = 16, // ����
		/* ������ */
		eEBT_STABLE = 17, // ������
		/* �п� */
		eEBT_Sys_T_Camp = 18, // �п�
		/* â�� */
		eEBT_Sys_T_Depot = 19, // â��
		/* ���â�� */
		eEBT_SECRET = 20, // ���â��
		/* ���� */
		eEBT_TOWER = 21, // ����
		/* �溮 */
		eEBT_BARRIER = 22, // �溮
		eEND_EBuildType
	}; // EBuildType 



	enum EOutput // �������
	{
		eBEGIN_EOutput = 0,
		/* �α� */
		eEOT_POPULATION = 1, // �α�
		/* �� */
		eEOT_GOLD = 2, // ��
		/* �ķ� */
		eEOT_FOOD = 3, // �ķ�
		/* ���� */
		eEOT_TREE = 4, // ����
		/* ���� */
		eEOT_STONE = 5, // ����
		/* ö�� */
		eEOT_IRON = 6, // ö��
		/* ��� */
		eEOT_SILK = 7, // ���
		/* ���� */
		eEOT_SOLDIER = 8, // ����
		eEOT_PIKE = 9, // â ����
		eEOT_HEAVY = 10, // �߰� ����
		/* ������ (ö �Ҹ� ����) */
		eEOT_HALBERD = 11, // ����� ����
		eEOT_BOW = 12, // �� ����
		eEOT_CROSSBOW = 13, // �� ����
		eEOT_BOWGUN = 14, // ���� ����
		eEOT_BALLISTA = 15, // ���� ����
		/* ������ �����ؼ��� ���� (���� �þ��) */
		eEOT_CHARIOT = 16, // ���� ����
		/* ������ �����ؼ��� ���� (���� �þ��) */
		eEOT_WAGON = 17, // ����
		/* Eunit_ClassItemA �� ���� ���� */
		eEOT_HORSE = 18, // ����
		/* ����, ����, ���� �뵵 */
		eEOT_WHEELBARROW = 19, // ����
		eEOT_CART = 20, // ���
		/* B�� Ȱ�� ���� */
		eEOT_SIEGE_LADDER = 21, // ����
		eEOT_SIEGE_RAM = 22, // ����
		eEOT_SIEGE_TOWER = 23, // ����
		eEOT_SIEGE_TREBUCHET = 24, // ������
		eEND_EOutput
	}; // EOutput 





struct jEXCEL_LIB_API Sys__T_BuildObj /* ����type ���̺��� base ���̺��̴�. ��� ����type ���̺��� �� ���̺��� ��ӹ޴´� */
{
	/*  Sys_T_BaseObj����� �޴� ���̺��� �ǹ� ���� */
	EBuildType m_base_type; // �ǹ�Ÿ�� min_max(,EBuildType)
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname32_t m_name; // �ǹ����ҽ��� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys__T_BuildObj
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  8 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys__T_BuildObj
		jEXCEL_TABLE_COMMON_CODE_H_Sys__T_BuildObj();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys__T_BuildObj

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys__T_BuildObj_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys__T_BuildObj)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys__T_BuildObj
enum { eSTRUCT_SIZE_Sys__T_BuildObj = sizeof(Sys__T_BuildObj) };


struct CSV_Sys__T_BuildObj : public nMech::nUtil::jCSV_File<Sys__T_BuildObj>
{
	virtual ~CSV_Sys__T_BuildObj(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys__T_BuildObj>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys__T_BuildObj g_Sys__T_BuildObj;

struct jEXCEL_LIB_API Sys_T_Bar /* ������� */
{
	/*  �ǹ� ���̵� */
	Sys_T_Bar_id_t m_isid; // ���� min_max(,)
		typedef Sys_T_Bar_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname256_t m_client_file; // �ǹ� �̹��� ���� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // �ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // �ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn; // ���� ��ȯ��� min_max(,)
	int16 m_stonereturn; // �� ��ȯ��� min_max(,)
	int16 m_ironreturn; // ö ��ȯ��� min_max(,)
	int16 m_silkreturn; // ��� ��ȯ��� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // �α� ��ȯ��� min_max(,)
	/*  ������ ������ ������ �� */
	int16 m_hideHero; // ��� ��� min_max(,)
	/*  �������� �ڵ����� �������� �������� ���µǴ� �ð� (�ʷΰ��) */
	uint32 m_resettime; // ���½ð� min_max(,)
	/*  �������� ������� 1ȸ�� �������� ������ �� */
	int16 m_itemnum; // �����ۼ� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Bar
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  18 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Bar
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Bar();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Bar

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Bar_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Bar)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Bar
enum { eSTRUCT_SIZE_Sys_T_Bar = sizeof(Sys_T_Bar) };


struct CSV_Sys_T_Bar : public nMech::nUtil::jCSV_File<Sys_T_Bar>
{
	virtual ~CSV_Sys_T_Bar(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Bar>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Bar g_Sys_T_Bar;

struct jEXCEL_LIB_API Sys_T_Barrack /* ������� */
{
	/*  �ǹ� ���̵� */
	Sys_T_Barrack_id_t m_isid; // ���� min_max(,)
		typedef Sys_T_Barrack_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname256_t m_client_file; // �ǹ� �̹��� ���� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // �ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // �ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn; // ���� ��ȯ��� min_max(,)
	int16 m_stonereturn; // �� ��ȯ��� min_max(,)
	int16 m_ironreturn; // ö ��ȯ��� min_max(,)
	int16 m_silkreturn; // ��� ��ȯ��� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // �α� ��ȯ��� min_max(,)
	/*  ���� �������� ����ӵ� ��� */
	int16 m_s_p_speed; // ����_����_�ӵ� min_max(,)
	/*  �������� 1�� ���� ��� */
	int16 m_s_p_cost; // ����_����_��� min_max(,)
	/*  �������� �ִ� ���귮 */
	int16 m_s_output; // ����_ ���귮 min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Barrack
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  18 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Barrack
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Barrack();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Barrack

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Barrack_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Barrack)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Barrack
enum { eSTRUCT_SIZE_Sys_T_Barrack = sizeof(Sys_T_Barrack) };


struct CSV_Sys_T_Barrack : public nMech::nUtil::jCSV_File<Sys_T_Barrack>
{
	virtual ~CSV_Sys_T_Barrack(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Barrack>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Barrack g_Sys_T_Barrack;

struct jEXCEL_LIB_API Sys_T_Camp /* ������� */
{
	/*  �ǹ� ���̵� */
	Sys_T_Camp_id_t m_isid; // ���� min_max(,)
		typedef Sys_T_Camp_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname256_t m_client_file; // �ǹ� �̹��� ���� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // �ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // �ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn; // ���� ��ȯ��� min_max(,)
	int16 m_stonereturn; // �� ��ȯ��� min_max(,)
	int16 m_ironreturn; // ö ��ȯ��� min_max(,)
	int16 m_silkreturn; // ��� ��ȯ��� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // �α� ��ȯ��� min_max(,)
	/*  ���� 1���� �ð��� �Һ��ϴ� �ķ��� �� */
	int16 m_f_r_spend; // ����_ �ķ�_�Һ� min_max(,)
	/*  �п����� ���� �ִ� ������ */
	int32 m_f_storage; // ����_������ min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Camp
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  17 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Camp
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Camp();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Camp

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Camp_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Camp)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Camp
enum { eSTRUCT_SIZE_Sys_T_Camp = sizeof(Sys_T_Camp) };


struct CSV_Sys_T_Camp : public nMech::nUtil::jCSV_File<Sys_T_Camp>
{
	virtual ~CSV_Sys_T_Camp(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Camp>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Camp g_Sys_T_Camp;

struct jEXCEL_LIB_API Sys_T_Depot /* ������� */
{
	/*  �ǹ� ���̵� */
	Sys_T_Depot_id_t m_isid; // ���� min_max(,)
		typedef Sys_T_Depot_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname256_t m_client_file; // �ǹ� �̹��� ���� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // �ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // �ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn; // ���� ��ȯ��� min_max(,)
	int16 m_stonereturn; // �� ��ȯ��� min_max(,)
	int16 m_ironreturn; // ö ��ȯ��� min_max(,)
	int16 m_silkreturn; // ��� ��ȯ��� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // �α� ��ȯ��� min_max(,)
	/*  â���� �ڿ� �ִ� ������ */
	int32 m_storage; // �ִ뺸���� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Depot
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Depot
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Depot();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Depot

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Depot_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Depot)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Depot
enum { eSTRUCT_SIZE_Sys_T_Depot = sizeof(Sys_T_Depot) };


struct CSV_Sys_T_Depot : public nMech::nUtil::jCSV_File<Sys_T_Depot>
{
	virtual ~CSV_Sys_T_Depot(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Depot>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Depot g_Sys_T_Depot;

struct jEXCEL_LIB_API Sys_T_Farm /* ������� */
{
	/*  �ǹ� ���̵� */
	Sys_T_Farm_id_t m_isid; // ���� min_max(,)
		typedef Sys_T_Farm_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname256_t m_client_file; // �ǹ� �̹��� ���� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // �ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // �ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn; // ���� ��ȯ��� min_max(,)
	int16 m_stonereturn; // �� ��ȯ��� min_max(,)
	int16 m_ironreturn; // ö ��ȯ��� min_max(,)
	int16 m_silkreturn; // ��� ��ȯ��� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // �α� ��ȯ��� min_max(,)
	/*  �� �������� ���� ���귮 */
	int16 m_foodoutput; // �ķ����귮 min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_Farm
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Farm
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Farm();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_Farm

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_Farm_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_Farm)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_Farm
enum { eSTRUCT_SIZE_Sys_T_Farm = sizeof(Sys_T_Farm) };


struct CSV_Sys_T_Farm : public nMech::nUtil::jCSV_File<Sys_T_Farm>
{
	virtual ~CSV_Sys_T_Farm(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_Farm>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_Farm g_Sys_T_Farm;

struct jEXCEL_LIB_API Sys_T_House /* ������� */
{
	/*  �ǹ� ���̵� */
	Sys_T_House_id_t m_isid; // ���� min_max(,)
		typedef Sys_T_House_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname256_t m_client_file; // �ǹ� �̹��� ���� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // �ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // �ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn; // ���� ��ȯ��� min_max(,)
	int16 m_stonereturn; // �� ��ȯ��� min_max(,)
	int16 m_ironreturn; // ö ��ȯ��� min_max(,)
	int16 m_silkreturn; // ��� ��ȯ��� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // �α� ��ȯ��� min_max(,)
	/*  �ΰ� ������ ��µǴ� �ִ� �α��� */
	int16 m_maxpopulation; // �ΰ��ִ��α� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_House
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_House
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_House();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_House

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_House_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_House)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_House
enum { eSTRUCT_SIZE_Sys_T_House = sizeof(Sys_T_House) };


struct CSV_Sys_T_House : public nMech::nUtil::jCSV_File<Sys_T_House>
{
	virtual ~CSV_Sys_T_House(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_House>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_House g_Sys_T_House;

struct jEXCEL_LIB_API Sys_T_HQ /* ������� */
{
	/*  �ǹ� ���̵� */
	Sys_T_HQ_id_t m_isid; // ���� min_max(,)
		typedef Sys_T_HQ_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_isid; }
	void SetPrimaryKey(primary_key_t id) { m_isid = id; }
	/*  �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� */
	tname256_t m_client_file; // �ǹ� �̹��� ���� min_max(,)
	/*  ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� */
	uint32 m_upgradetime; // ���׷��̵� �ð� min_max(,)
	/*  �Ǽ��� �ʿ��� ���� ��� */
	int16 m_tree_num; // ���� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �� ��� */
	int16 m_stone_num; // �� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ö ��� */
	int16 m_iron_num; // ö ��� min_max(,)
	/*  �Ǽ��� �ʿ��� ��� ��� */
	int16 m_silk_num; // ��� ��� min_max(,)
	/*  �Ǽ��� �ʿ��� �α� ��� */
	int16 m_population_num; // �α� ��� min_max(,)
	/*  �� ������ �ִ� ���� ������ �ǹ� �� */
	int16 m_maxbuild; // �ִ� ������ min_max(,)
	/*  �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ */
	int16 m_downlevel; // �ٿ�׷��̵巹�� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) */
	int16 m_treereturn; // ���� ��ȯ��� min_max(,)
	int16 m_stonereturn; // �� ��ȯ��� min_max(,)
	int16 m_ironreturn; // ö ��ȯ��� min_max(,)
	int16 m_silkreturn; // ��� ��ȯ��� min_max(,)
	/*  �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. */
	int16 m_populationreturn; // �α� ��ȯ��� min_max(,)
	/*  ¡�� ��� */
	int16 m_getgold; // ¡�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_T_HQ
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_T_HQ
		jEXCEL_TABLE_COMMON_CODE_H_Sys_T_HQ();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_T_HQ

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_T_HQ_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_T_HQ)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_T_HQ
enum { eSTRUCT_SIZE_Sys_T_HQ = sizeof(Sys_T_HQ) };


struct CSV_Sys_T_HQ : public nMech::nUtil::jCSV_File<Sys_T_HQ>
{
	virtual ~CSV_Sys_T_HQ(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_T_HQ>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_T_HQ g_Sys_T_HQ;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EOutput[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_user_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_user_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_user_
