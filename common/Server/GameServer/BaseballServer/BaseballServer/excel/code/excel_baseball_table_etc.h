/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_etc_
#define __namespace_nEXCEL___filename_excel_baseball_table_etc_

#include "table_const_excel_baseball_table_etc.h"
// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_BreakingBallUpgrade,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(FIELD)\
		FIELD(id                     ,id                 ,Sys_BreakingBallState_id_t   ,0 , Sys_BreakingBallState_id_t , uint16 , u16)\
		FIELD(name                   ,name               ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(type                   ,��ȭ��Ÿ��              ,EPlayerBreakingBall          ,2 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(need_basicskill1       ,���׷��̵� �ʿ� ������1      ,EPitcherForm                 ,3 , EPitcherForm , EPitcherForm , e)\
		FIELD(need_basicskill2       ,���׷��̵� �ʿ� ������2      ,EPitcherForm                 ,4 , EPitcherForm , EPitcherForm , e)\
		FIELD(need_upgrade1          ,���׷��̵� �ʿ� ��ȭ��1      ,EPlayerBreakingBall          ,5 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(need_upgrade2          ,���׷��̵� �ʿ� ��ȭ��2      ,EPlayerBreakingBall          ,6 , EPlayerBreakingBall , EPlayerBreakingBall , e)\
		FIELD(need_player_level      ,���׷��̵� ���� �÷��̾� ����   ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(equip_player_level     ,���� ���� �÷��̾� ����      ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(upgrade_need_time1     ,��ȭ��1�� ���׷��̵�ð�1     ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(upgrade_need_time2     ,��ȭ��2�� ���׷��̵�ð�2     ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(need_money             ,���׷��̵���            ,game_money_t                 ,11 , int32 , int32 , i32)\
		FIELD(breaking_pitch         ,��ȭ�� ����             ,EBreakingBallPitch           ,12 , EBreakingBallPitch , EBreakingBallPitch , e)\
		FIELD(ball_rotation          ,�� ȸ�� ����            ,EBreakingBallRotation        ,13 , EBreakingBallRotation , EBreakingBallRotation , e)\
		FIELD(open_date              ,���� �Ͻ�              ,SYSTEMTIME                   ,14 , SYSTEMTIME , SYSTEMTIME , tm)\
		FIELD(first_open_breakingball,���� ���� ���� ��ȭ��       ,bool                         ,15 , bool , bool , b)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_InheritedTable
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_InheritedTable


	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_BreakingBallUpgrade�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{



struct jEXCEL_LIB_API Sys_BreakingBallUpgrade /* ������� */
{
	/*  id */
	Sys_BreakingBallState_id_t m_id; // id min_max(,)
	/*  name */
	tname32_t m_name; // name min_max(,)
	/*  ��ȭ�� �̸� */
	EPlayerBreakingBall m_type; // ��ȭ��Ÿ�� min_max(,EPlayerBreakingBall)
	/*  ���׷��̵忡 �ʿ��� ������(null�� ��� ��� �������� �͵� ��� ����) */
	EPitcherForm m_need_basicskill1; // ���׷��̵� �ʿ� ������1 min_max(,EPitcherForm)
	/*  ���׷��̵忡 �ʿ��� ������(null�� ��� ��� �������� �͵� ��� ����) */
	EPitcherForm m_need_basicskill2; // ���׷��̵� �ʿ� ������2 min_max(,EPitcherForm)
	/*  ���׷��̵忡 �ʿ��� ��ȭ�� (���� �� 1�� ���׷��̵� �Ұ� null�� ��� �⺻ ��ȭ��) */
	EPlayerBreakingBall m_need_upgrade1; // ���׷��̵� �ʿ� ��ȭ��1 min_max(,EPlayerBreakingBall)
	/*  ���׷��̵忡 �ʿ��� ��ȭ�� (���� �� 1�� ���׷��̵� �Ұ�) */
	EPlayerBreakingBall m_need_upgrade2; // ���׷��̵� �ʿ� ��ȭ��2 min_max(,EPlayerBreakingBall)
	/*  ���׷��̵� �ʿ� �÷��̾� ���� */
	int16 m_need_player_level; // ���׷��̵� ���� �÷��̾� ���� min_max(1,100)
	/*  ���׷��̵� �ʿ� �÷��̾� ���� */
	int16 m_equip_player_level; // ���� ���� �÷��̾� ���� min_max(1,100)
	/*  ���׷��̵� �ʿ� �ð� */
	int16 m_upgrade_need_time1; // ��ȭ��1�� ���׷��̵�ð�1 min_max(0,100)
	/*  ���׷��̵忡 ��ȭ���� 2�� �̻� �ʿ� ��쿡�� ��ȭ���� 2�� ��� Ʈ���̴� �Ϸ� �ؾ� ������ �ʿ� */
	int16 m_upgrade_need_time2; // ��ȭ��2�� ���׷��̵�ð�2 min_max(0,100)
	/*  ���׷��̵� �ʿ� ���ӸӴ� */
	game_money_t m_need_money; // ���׷��̵��� min_max(,)
	/*  ��ȭ���� ��Ⱦ��ȭ ���� */
	EBreakingBallPitch m_breaking_pitch; // ��ȭ�� ���� min_max(,EBreakingBallPitch)
	/*  ��ȭ�� ���� ȸ�� ���� ���� */
	EBreakingBallRotation m_ball_rotation; // �� ȸ�� ���� min_max(,EBreakingBallRotation)
	/*  ��ȭ�� ���� ���� */
	SYSTEMTIME m_open_date; // ���� �Ͻ� min_max(,)
	/*  ĳ���� ���� �� ���� �Ҽ� �ִ� ��ȭ�� ���� �ƴ��� ���� (0=�Ұ��� 1=����) */
	bool m_first_open_breakingball; // ���� ���� ���� ��ȭ�� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_BreakingBallUpgrade
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  16 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_BreakingBallUpgrade
		jEXCEL_TABLE_COMMON_CODE_H_Sys_BreakingBallUpgrade();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_BreakingBallUpgrade

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_BreakingBallUpgrade_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_BreakingBallUpgrade)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_BreakingBallUpgrade
enum { eSTRUCT_SIZE_Sys_BreakingBallUpgrade = sizeof(Sys_BreakingBallUpgrade) };


struct CSV_Sys_BreakingBallUpgrade : public nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade>
{
	virtual ~CSV_Sys_BreakingBallUpgrade(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_BreakingBallUpgrade>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_BreakingBallUpgrade g_Sys_BreakingBallUpgrade;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_etc_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_etc_
