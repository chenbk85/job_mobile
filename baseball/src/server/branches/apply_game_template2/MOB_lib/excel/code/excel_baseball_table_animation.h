/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_baseball_table_animation_
#define __namespace_nEXCEL___filename_excel_baseball_table_animation_

#include "table_const_excel_baseball_table_animation.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_baseball_table_animation_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EBatterAnimationType,�������,nMech,nEXCEL)\
	ENUM_TABLE(ECatcherAnimationType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EEumpireAnimationType,�������,nMech,nEXCEL)\
	ENUM_TABLE(EPitcherAnimationType,�������,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nEXCEL_EBatterAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBAT_STARTUP			,1,Startup,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_MAXAFTER			,2,Max After,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_MAX			,3,Max,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_IDLE			,4,Idle,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_READY			,5,Ready,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_SWING_LEFT			,6,���� ����,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_SWING_MIDDLE			,7,�߰� ����,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_SWING_RIGHT			,8,������ ����,nMech,nEXCEL,EBatterAnimationType)\
		ENUM_FIELD(EBAT_MAUVAIS			,9,�꽺��,nMech,nEXCEL,EBatterAnimationType)\

	/* ������� */
	#define for_each_nEXCEL_ECatcherAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ECAT_STARTUP_IDLE			,1,Startup,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MITCATCH			,2,��Ʈ �� ĳġ,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MOVE_MIDDLE			,3,���� �ߴ� �̵�,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MOVE_LEFT			,4,���� ���� �̵�,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_MOVE_RIGHT			,5,���� ������ �̵�,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_BACK_MIDDLE			,6,���� �ߴ� �̵� �� ���ƿ���,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_BACK_LEFT			,7,���� ���� �̵� �� ���ƿ���,nMech,nEXCEL,ECatcherAnimationType)\
		ENUM_FIELD(ECAT_BACK_RIGHT			,8,���� ������ �̵� �� ���ƿ���,nMech,nEXCEL,ECatcherAnimationType)\

	/* ������� */
	#define for_each_nEXCEL_EEumpireAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EEAT_PLAYBALL			,1,��� ����,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_IDLE			,2,��� ���� ���̵�,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_PERFECT			,3,����Ʈ ����,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_GOOD			,4,�� ����,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_NORMAL			,5,��� ����,nMech,nEXCEL,EEumpireAnimationType)\
		ENUM_FIELD(EEAT_DECISION_BAD			,6,��� ����,nMech,nEXCEL,EEumpireAnimationType)\

	/* ������� */
	#define for_each_nEXCEL_EPitcherAnimationType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EPAT_STARTUP_IDL			,1,��� ���̵� 1,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_HIT_AFTER			,2,���� ��Ʈ �� �� ����(�� ��),nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_YES			,3,���� ���� ����,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_NO			,4,���� ���� �ź�,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_STARTUP			,5,Startup,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_PITCHING			,6,����,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_BACK			,7,���� �� �ǵ��ư���,nMech,nEXCEL,EPitcherAnimationType)\
		ENUM_FIELD(EPAT_CEREMONY			,8,�����Ӵ�,nMech,nEXCEL,EPitcherAnimationType)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Batter_Animation,�������,nMech,nEXCEL)\
	STRUCT(Sys_Catcher_Animation,�������,nMech,nEXCEL)\
	STRUCT(Sys_Pitcher_Animation,�������,nMech,nEXCEL)\
	STRUCT(Sys_Umpire_Animation,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Batter_Animation �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(body_type              ,ü��                 ,EPlayerBodyType              ,1 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(better_form            ,Ÿ�� ��               ,EBatterForm                  ,2 , EBatterForm , EBatterForm , e)\
		FIELD(batter_animation       ,Ÿ�ھִϸ��̼�            ,EBatterAnimationType         ,3 , EBatterAnimationType , EBatterAnimationType , e)\
		FIELD(animation_number       ,�ش� �ִϸ��̼� �ѹ�        ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(animation_filename     ,�ش� �ִϸ��̼� ���� �̸�     ,aname32_t                    ,5 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Batter_Animation�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Batter_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Batter_Animation�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Batter_Animation�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Catcher_Animation �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(catcher_animation      ,�����ִϸ��̼�            ,ECatcherAnimationType        ,1 , ECatcherAnimationType , ECatcherAnimationType , e)\
		FIELD(animation_number       ,�ش� �ִϸ��̼� �ѹ�        ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(animation_filename     ,�ش� �ִϸ��̼� ���� �̸�     ,aname32_t                    ,3 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Catcher_Animation�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Catcher_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Catcher_Animation�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Catcher_Animation�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(body_type              ,ü��                 ,EPlayerBodyType              ,1 , EPlayerBodyType , EPlayerBodyType , e)\
		FIELD(pitcher_form           ,������                ,EPitcherForm                 ,2 , EPitcherForm , EPitcherForm , e)\
		FIELD(pitcher_animation      ,�����ִϸ��̼�            ,EPitcherAnimationType        ,3 , EPitcherAnimationType , EPitcherAnimationType , e)\
		FIELD(animation_number       ,�ش� �ִϸ��̼� �ѹ�        ,int16                        ,4 , int16 , int16 , i16)\
		FIELD(animation_filename     ,�ش� �ִϸ��̼� ���� �̸�     ,aname32_t                    ,5 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Pitcher_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Pitcher_Animation�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD_all_member


	// ------------------------------------------------------------
	// Sys_Umpire_Animation �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(FIELD)\
		FIELD(index                  ,index              ,int16                        ,0 , int16 , int16 , i16)\
		FIELD(umpire_animation       ,���Ǿִϸ��̼�            ,EEumpireAnimationType        ,1 , EEumpireAnimationType , EEumpireAnimationType , e)\
		FIELD(animation_number       ,�ش� �ִϸ��̼� �ѹ�        ,int16                        ,2 , int16 , int16 , i16)\
		FIELD(animation_filename     ,�ش� �ִϸ��̼� ���� �̸�     ,aname32_t                    ,3 , acstr , acstr , a32)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Umpire_Animation�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_InheritedTable
	#define for_each_nEXCEL_Sys_Umpire_Animation_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_InheritedTable


	// ------------------------------------------------------------
	// Sys_Umpire_Animation�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Umpire_Animation�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EBatterAnimationType // �������
	{
		eBEGIN_EBatterAnimationType = 0,
		/* ���͹ڽ����� �Ѽ����� �������� ���ظ� ���ϰ�, �߷� ���� ���� Ÿ�� �ڼ� ��� */
		eEBAT_STARTUP = 1, // Startup
		/* ������ ���Ľ����� ��ƮĿ�� �ƽø� ���ٰ� ��Ÿ ���̵�� ���� */
		eEBAT_MAXAFTER = 2, // Max After
		/* ������ ���Ľ����� ��ƮĿ�� �ƽø� ����� �� ���̵� */
		eEBAT_MAX = 3, // Max
		/* ������ ���Ľ����� ����̸� 1�ڷ� ����� �ణ ���� �ڼ� */
		eEBAT_IDLE = 4, // Idle
		/* ������ ���Ľ����� Ÿ���غ� */
		eEBAT_READY = 5, // Ready
		/* ������ ���Ľ����� ���� ���� (������ �ٶ󺸴� ��������) (1_�ϴ� 2_���ϴ� 3_�ߴ� 4_�߻�� 5_���) */
		eEBAT_SWING_LEFT = 6, // ���� ����
		/* ������ ���Ľ����� �߰� ���� (������ �ٶ󺸴� ��������) (1_�ϴ� 2_���ϴ� 3_�ߴ� 4_�߻�� 5_���) */
		eEBAT_SWING_MIDDLE = 7, // �߰� ����
		/* ������ ���Ľ����� ������ ���� (������ �ٶ󺸴� ��������) (1_�ϴ� 2_���ϴ� 3_�ߴ� 4_�߻�� 5_���) */
		eEBAT_SWING_RIGHT = 8, // ������ ����
		/* ������ ���Ľ����� �꽺�� */
		eEBAT_MAUVAIS = 9, // �꽺��
		eEND_EBatterAnimationType
	}; // EBatterAnimationType 



	enum ECatcherAnimationType // �������
	{
		eBEGIN_ECatcherAnimationType = 0,
		/* ���� ������ �� ���� ���̵� */
		eECAT_STARTUP_IDLE = 1, // Startup
		/* ������ ��Ʈ ��� �ش� ��ġ �̵� ���¿��� �� ĳġ ���� (1=���ϴ� 2=���ߴ� 3=�ϻ�� 4=���ϴ� 5=���ߴ� 6=�߻�� 7=���ϴ� 8=���ߴ� 9=���� 10=�ֻ��ϴ� 11=�ֻ��ߴ� 12=�ֻ���) */
		eECAT_MITCATCH = 2, // ��Ʈ �� ĳġ
		/* ���� ��ü �ߴ� �̵� */
		eECAT_MOVE_MIDDLE = 3, // ���� �ߴ� �̵�
		/* ���� ��ü ���� �̵� */
		eECAT_MOVE_LEFT = 4, // ���� ���� �̵�
		/* ���� ��ü ������ �̵� */
		eECAT_MOVE_RIGHT = 5, // ���� ������ �̵�
		/* ���� �ߴ� �̵� �� ���ƿ��� */
		eECAT_BACK_MIDDLE = 6, // ���� �ߴ� �̵� �� ���ƿ���
		/* ���� ���� �̵� �� ���ƿ��� */
		eECAT_BACK_LEFT = 7, // ���� ���� �̵� �� ���ƿ���
		/* ���� ������ �̵� �� ���ƿ��� */
		eECAT_BACK_RIGHT = 8, // ���� ������ �̵� �� ���ƿ���
		eEND_ECatcherAnimationType
	}; // ECatcherAnimationType 



	enum EEumpireAnimationType // �������
	{
		eBEGIN_EEumpireAnimationType = 0,
		/* ��� ���� */
		eEEAT_PLAYBALL = 1, // ��� ����
		/* ��� ���� ���̵� */
		eEEAT_IDLE = 2, // ��� ���� ���̵�
		/* ����Ʈ ���� */
		eEEAT_DECISION_PERFECT = 3, // ����Ʈ ����
		/* �� ���� */
		eEEAT_DECISION_GOOD = 4, // �� ����
		/* ��� ���� */
		eEEAT_DECISION_NORMAL = 5, // ��� ����
		/* ��� ���� */
		eEEAT_DECISION_BAD = 6, // ��� ����
		eEND_EEumpireAnimationType
	}; // EEumpireAnimationType 



	enum EPitcherAnimationType // �������
	{
		eBEGIN_EPitcherAnimationType = 0,
		/* ��� ������ ������ ���̵� */
		eEPAT_STARTUP_IDL = 1, // ��� ���̵� 1
		/* ���� ��Ʈ �� �� ����(��=1 ��=2) */
		eEPAT_HIT_AFTER = 2, // ���� ��Ʈ �� �� ����(�� ��)
		/* ��� ���� ������ �� ���� */
		eEPAT_YES = 3, // ���� ���� ����
		/* ��� ���� �� �� �������� */
		eEPAT_NO = 4, // ���� ���� �ź�
		/* ������ ���� �� ����� �ڸ���� */
		eEPAT_STARTUP = 5, // Startup
		/* �����ڵ忡�� ���� ����, ��� �ڼ�  ���� */
		eEPAT_PITCHING = 6, // ����
		/* ���� �� �ǵ��ư��� */
		eEPAT_BACK = 7, // ���� �� �ǵ��ư���
		/* Ÿ�ڰ� ��Ʈ���� ������ �� �ָ��� ������ �Ҳ� ��� �ƽ� */
		eEPAT_CEREMONY = 8, // �����Ӵ�
		eEND_EPitcherAnimationType
	}; // EPitcherAnimationType 





struct jEXCEL_LIB_API Sys_Batter_Animation /* ������� */
{
	/*  �����г��� , �������̺��� ��� */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  ü�� */
	EPlayerBodyType m_body_type; // ü�� min_max(,EPlayerBodyType)
	/*  Ÿ�� �� */
	EBatterForm m_better_form; // Ÿ�� �� min_max(,EBatterForm)
	/*  Ÿ�� �ִϸ��̼� ���� */
	EBatterAnimationType m_batter_animation; // Ÿ�ھִϸ��̼� min_max(,EBatterAnimationType)
	/*  �ش� �ִϸ��̼��� �ѹ� */
	int16 m_animation_number; // �ش� �ִϸ��̼� �ѹ� min_max(,)
	/*  �ش� ���ϸ��̼� ���� �̸� */
	aname32_t m_animation_filename; // �ش� �ִϸ��̼� ���� �̸� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Batter_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  6 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Batter_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Batter_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Batter_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Batter_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Batter_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Batter_Animation
enum { eSTRUCT_SIZE_Sys_Batter_Animation = sizeof(Sys_Batter_Animation) };


struct CSV_Sys_Batter_Animation : public nMech::nUtil::jCSV_File<Sys_Batter_Animation>
{
	virtual ~CSV_Sys_Batter_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Batter_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Batter_Animation g_Sys_Batter_Animation;

struct jEXCEL_LIB_API Sys_Catcher_Animation /* ������� */
{
	/*  �����г��� , �������̺��� ��� */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  ���� �ִϸ��̼� ���� */
	ECatcherAnimationType m_catcher_animation; // �����ִϸ��̼� min_max(,ECatcherAnimationType)
	/*  �ش� �ִϸ��̼��� �ѹ� */
	int16 m_animation_number; // �ش� �ִϸ��̼� �ѹ� min_max(,)
	/*  �ش� ���ϸ��̼� ���� �̸� */
	aname32_t m_animation_filename; // �ش� �ִϸ��̼� ���� �̸� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Catcher_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  4 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Catcher_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Catcher_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Catcher_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Catcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Catcher_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Catcher_Animation
enum { eSTRUCT_SIZE_Sys_Catcher_Animation = sizeof(Sys_Catcher_Animation) };


struct CSV_Sys_Catcher_Animation : public nMech::nUtil::jCSV_File<Sys_Catcher_Animation>
{
	virtual ~CSV_Sys_Catcher_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Catcher_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Catcher_Animation g_Sys_Catcher_Animation;

struct jEXCEL_LIB_API Sys_Pitcher_Animation /* ������� */
{
	/*  �����г��� , �������̺��� ��� */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  ü�� */
	EPlayerBodyType m_body_type; // ü�� min_max(,EPlayerBodyType)
	/*  ������ */
	EPitcherForm m_pitcher_form; // ������ min_max(,EPitcherForm)
	/*  ���� �ִϸ��̼� ���� */
	EPitcherAnimationType m_pitcher_animation; // �����ִϸ��̼� min_max(,EPitcherAnimationType)
	/*  �ش� �ִϸ��̼��� �ѹ� */
	int16 m_animation_number; // �ش� �ִϸ��̼� �ѹ� min_max(,)
	/*  �ش� ���ϸ��̼� ���� �̸� */
	aname32_t m_animation_filename; // �ش� �ִϸ��̼� ���� �̸� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Pitcher_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  6 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Pitcher_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Pitcher_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Pitcher_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Pitcher_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Pitcher_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Pitcher_Animation
enum { eSTRUCT_SIZE_Sys_Pitcher_Animation = sizeof(Sys_Pitcher_Animation) };


struct CSV_Sys_Pitcher_Animation : public nMech::nUtil::jCSV_File<Sys_Pitcher_Animation>
{
	virtual ~CSV_Sys_Pitcher_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Pitcher_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Pitcher_Animation g_Sys_Pitcher_Animation;

struct jEXCEL_LIB_API Sys_Umpire_Animation /* ������� */
{
	/*  �����г��� , �������̺��� ��� */
	int16 m_index; // index min_max(,)
		typedef int16 primary_key_t;
	primary_key_t GetPrimaryKey() { return m_index; }
	void SetPrimaryKey(primary_key_t id) { m_index = id; }
	/*  ���� �ִϸ��̼� ���� */
	EEumpireAnimationType m_umpire_animation; // ���Ǿִϸ��̼� min_max(,EEumpireAnimationType)
	/*  �ش� �ִϸ��̼��� �ѹ� */
	int16 m_animation_number; // �ش� �ִϸ��̼� �ѹ� min_max(,)
	/*  �ش� ���ϸ��̼� ���� �̸� */
	aname32_t m_animation_filename; // �ش� �ִϸ��̼� ���� �̸� min_max(,)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Umpire_Animation
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  4 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Umpire_Animation
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Umpire_Animation();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Umpire_Animation

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Umpire_Animation_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Umpire_Animation)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Umpire_Animation
enum { eSTRUCT_SIZE_Sys_Umpire_Animation = sizeof(Sys_Umpire_Animation) };


struct CSV_Sys_Umpire_Animation : public nMech::nUtil::jCSV_File<Sys_Umpire_Animation>
{
	virtual ~CSV_Sys_Umpire_Animation(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Umpire_Animation>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Umpire_Animation g_Sys_Umpire_Animation;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBatterAnimationType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_ECatcherAnimationType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EEumpireAnimationType[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EPitcherAnimationType[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_baseball_table_animation_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_baseball_table_animation_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_baseball_table_animation_
