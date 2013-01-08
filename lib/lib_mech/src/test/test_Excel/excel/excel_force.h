/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_force_
#define __namespace_nEXCEL___filename_excel_force_

#include "table_const_excel_force.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_force_ENUM(ENUM_TABLE)\
	ENUM_TABLE(E_ClassItemA,�������,nMech,nEXCEL)\
	ENUM_TABLE(E_ClassItemB,�������,nMech,nEXCEL)\
	ENUM_TABLE(E_W_Event,�������,nMech,nEXCEL)\
	ENUM_TABLE(EForceClass,�������,nMech,nEXCEL)\
	ENUM_TABLE(EForcePosType,�������,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nEXCEL_E_ClassItemA_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CIA_NOT			,1,���� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_PIKE			,2,â ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_HEAVY			,3,�߰� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_HALBERD			,4,����� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_BOW			,5,�� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_CROSSBOW			,6,�� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_BOWGUN			,7,���� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_BALLISTA			,8,���� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_CHARIOT			,9,���� ����,nMech,nEXCEL,E_ClassItemA)\
		ENUM_FIELD(CIA_WAGON			,10,����,nMech,nEXCEL,E_ClassItemA)\

	/* ������� */
	#define for_each_nEXCEL_E_ClassItemB_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(CIB_NOT			,1,Ż�� ����,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_HORSE			,2,����,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_WHEELBARROW			,3,����,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_CART			,4,���,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_LADDER			,5,����,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_RAM			,6,����,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_TOWER			,7,����,nMech,nEXCEL,E_ClassItemB)\
		ENUM_FIELD(CIB_SIEGE_TREBUCHET			,8,������,nMech,nEXCEL,E_ClassItemB)\

	/* ������� */
	#define for_each_nEXCEL_E_W_Event_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ENV_SUNNY			,1,����,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_RAIN			,2,�� �Ӽ�,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_MIST			,3,�Ȱ� �Ӽ�,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_TIME			,4,�㳷 �Ӽ�,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_CALAMITY			,5,õ�� ����,nMech,nEXCEL,E_W_Event)\
		ENUM_FIELD(ENV_LUCK			,6,�ູ,nMech,nEXCEL,E_W_Event)\

	/* ������� */
	#define for_each_nEXCEL_EForceClass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(FC_COMMON			,1,����,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_INFANTRY			,2,����,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_ARCHER			,3,�ú�,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_CABALRY			,4,�⺴,nMech,nEXCEL,EForceClass)\
		ENUM_FIELD(FC_SIEGE			,5,��������,nMech,nEXCEL,EForceClass)\

	/* ������� */
	#define for_each_nEXCEL_EForcePosType_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(FPT_TOWN			,1,����,nMech,nEXCEL,EForcePosType)\
		ENUM_FIELD(FPT_CASTLE			,2,��,nMech,nEXCEL,EForcePosType)\
		ENUM_FIELD(FPT_CASTLEMAP			,3,��������,nMech,nEXCEL,EForcePosType)\
		ENUM_FIELD(FPT_WORLDMAP			,4,�����,nMech,nEXCEL,EForcePosType)\


// -------------------------------------------------
// struct �ڵ� ���ø� ����
// -------------------------------------------------
#define for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(STRUCT)\
	STRUCT(Sys_Force,�������,nMech,nEXCEL)\



	// ------------------------------------------------------------
	// Sys_Force �ڽ��� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Force_STRUCT_FIELD
	#define for_each_nEXCEL_Sys_Force_STRUCT_FIELD(FIELD)\
		FIELD(fsid                   ,����_ID              ,Sys_Force_id_t               ,0 , Sys_Force_id_t , uint16 , u16)\
		FIELD(name                   ,�̸�_ID              ,tname32_t                    ,1 , tcstr , tcstr , t32)\
		FIELD(name_kor               ,�����̸�               ,tname32_t                    ,2 , tcstr , tcstr , t32)\
		FIELD(force_class            ,�����з�               ,EForceClass                  ,3 , EForceClass , EForceClass , e)\
		FIELD(forceClassItemA        ,��������_������ A         ,E_ClassItemA                 ,4 , E_ClassItemA , E_ClassItemA , e)\
		FIELD(forceClassItemB        ,��������_������ B         ,E_ClassItemB                 ,5 , E_ClassItemB , E_ClassItemB , e)\
		FIELD(att                    ,���ݷ�                ,int16                        ,6 , int16 , int16 , i16)\
		FIELD(def                    ,����                ,int16                        ,7 , int16 , int16 , i16)\
		FIELD(mspeed                 ,�̵�_�ӵ�              ,int16                        ,8 , int16 , int16 , i16)\
		FIELD(aspeed                 ,����_�ӵ�              ,int16                        ,9 , int16 , int16 , i16)\
		FIELD(srange                 ,���ðŸ�               ,int16                        ,10 , int16 , int16 , i16)\
		FIELD(suvival_ratio          ,������                ,int16                        ,11 , int16 , int16 , i16)\
		FIELD(kill_ratio             ,�����                ,int16                        ,12 , int16 , int16 , i16)\
		FIELD(client_id              ,Ŭ���̾�ƮID            ,int16                        ,13 , int16 , int16 , i16)\
		FIELD(unit_load              ,���緮                ,int16                        ,14 , int16 , int16 , i16)\

	#endif // for_each_nEXCEL_Sys_Force_STRUCT_FIELD


	// ------------------------------------------------------------
	// Sys_Force�� ����� ���̺���� �̸��� ������ ��ũ��.
	// FUNC(table)
	#ifndef for_each_nEXCEL_Sys_Force_InheritedTable
	#define for_each_nEXCEL_Sys_Force_InheritedTable(FUNC)\

	#endif // for_each_nEXCEL_Sys_Force_InheritedTable


	// ------------------------------------------------------------
	// Sys_Force�� ����� ���̺���� �ʵ常 ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited
	#define for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited(FUNC)\

	#endif // for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited


	// ------------------------------------------------------------
	// Sys_Force�� ����� ���̺���� ����ʵ�� �ڽ��� �ʵ���� ������ ��ũ��.
	// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
	#ifndef for_each_nEXCEL_Sys_Force_STRUCT_FIELD_all_member
	#define for_each_nEXCEL_Sys_Force_STRUCT_FIELD_all_member(FUNC)\
		for_each_nEXCEL_Sys_Force_STRUCT_FIELD_Inherited(FUNC)\
		for_each_nEXCEL_Sys_Force_STRUCT_FIELD(FUNC)\

	#endif // for_each_nEXCEL_Sys_Force_STRUCT_FIELD_all_member

// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum E_ClassItemA // �������
	{
		eBEGIN_E_ClassItemA = 0,
		/* ���� ���� �ڵ� �з� */
		eCIA_NOT = 1, // ���� ����
		eCIA_PIKE = 2, // â ����
		eCIA_HEAVY = 3, // �߰� ����
		/* ������ (ö �Ҹ� ����) */
		eCIA_HALBERD = 4, // ����� ����
		eCIA_BOW = 5, // �� ����
		eCIA_CROSSBOW = 6, // �� ����
		eCIA_BOWGUN = 7, // ���� ����
		eCIA_BALLISTA = 8, // ���� ����
		/* ������ �����ؼ��� ���� (���� �þ��) */
		eCIA_CHARIOT = 9, // ���� ����
		/* ������ �����ؼ��� ���� (���� �þ��) */
		eCIA_WAGON = 10, // ����
		eEND_E_ClassItemA
	}; // E_ClassItemA 



	enum E_ClassItemB // �������
	{
		eBEGIN_E_ClassItemB = 0,
		eCIB_NOT = 1, // Ż�� ����
		/* Eunit_ClassItemA �� ���� ���� */
		eCIB_HORSE = 2, // ����
		/* ����, ����, ���� �뵵 */
		eCIB_WHEELBARROW = 3, // ����
		eCIB_CART = 4, // ���
		/* B�� Ȱ�� ���� */
		eCIB_SIEGE_LADDER = 5, // ����
		eCIB_SIEGE_RAM = 6, // ����
		eCIB_SIEGE_TOWER = 7, // ����
		eCIB_SIEGE_TREBUCHET = 8, // ������
		eEND_E_ClassItemB
	}; // E_ClassItemB 



	enum E_W_Event // �������
	{
		eBEGIN_E_W_Event = 0,
		/* �Ӽ� ���� ��� */
		eENV_SUNNY = 1, // ����
		/* ȭ�� ����, ���� ���� */
		eENV_RAIN = 2, // �� �Ӽ�
		/* �þ� ����  / ��Ÿ� ��ȭ */
		eENV_MIST = 3, // �Ȱ� �Ӽ�
		/* �þ� ����  / ��Ÿ� ��ȭ */
		eENV_TIME = 4, // �㳷 �Ӽ�
		/* ����/����/����/����/ȫ��/��ǳ/����/�޶ѱⶼ/���� */
		eENV_CALAMITY = 5, // õ�� ����
		/* ǳ��/�ٻ� */
		eENV_LUCK = 6, // �ູ
		eEND_E_W_Event
	}; // E_W_Event 



	enum EForceClass // �������
	{
		eBEGIN_EForceClass = 0,
		eFC_COMMON = 1, // ����
		eFC_INFANTRY = 2, // ����
		eFC_ARCHER = 3, // �ú�
		eFC_CABALRY = 4, // �⺴
		eFC_SIEGE = 5, // ��������
		eEND_EForceClass
	}; // EForceClass 



	enum EForcePosType // �������
	{
		eBEGIN_EForcePosType = 0,
		/* ���� */
		eFPT_TOWN = 1, // ����
		/* �� */
		eFPT_CASTLE = 2, // ��
		/* �������� */
		eFPT_CASTLEMAP = 3, // ��������
		/* ����� */
		eFPT_WORLDMAP = 4, // �����
		eEND_EForcePosType
	}; // EForcePosType 





struct jEXCEL_LIB_API Sys_Force /* ������� */
{
	/*  ���� ID */
	Sys_Force_id_t m_fsid; // ����_ID min_max(,)
		typedef Sys_Force_id_t primary_key_t;
	primary_key_t GetPrimaryKey() { return m_fsid; }
	void SetPrimaryKey(primary_key_t id) { m_fsid = id; }
	/*  �̸� ID */
	tname32_t m_name; // �̸�_ID min_max(,)
	/*  ���� �̸� */
	tname32_t m_name_kor; // �����̸� min_max(,)
	/*  ���� �з� */
	EForceClass m_force_class; // �����з� min_max(,EForceClass)
	/*  ���� ���� A */
	E_ClassItemA m_forceClassItemA; // ��������_������ A min_max(,E_ClassItemA)
	/*  ���� ���� B */
	E_ClassItemB m_forceClassItemB; // ��������_������ B min_max(,E_ClassItemB)
	/*  ���ݷ� ���� */
	int16 m_att; // ���ݷ� min_max(0,100)
	/*  ���� ���� */
	int16 m_def; // ���� min_max(0,100)
	/*  �̵� �ӵ� ���� */
	int16 m_mspeed; // �̵�_�ӵ� min_max(0,1000)
	/*  ���� �ӵ� ���� / msec ���� */
	int16 m_aspeed; // ����_�ӵ� min_max(0,10000)
	/*  ���ðŸ� */
	int16 m_srange; // ���ðŸ� min_max(0,100)
	/*  ��Ƴ� Ȯ�� / % ������ (xx.x%) */
	int16 m_suvival_ratio; // ������ min_max(0,1000)
	/*  �����ų Ȯ�� / % ������ (xx.x%) */
	int16 m_kill_ratio; // ����� min_max(0,1000)
	/*  Ŭ���̾�Ʈ���� ������ ���� �̹��� id ��ȣ */
	int16 m_client_id; // Ŭ���̾�ƮID min_max(0,100)
	/*  ��ǰ ���緮 */
	int16 m_unit_load; // ���緮 min_max(0,100000)

	//�ڵ������ �ֺܼ��� IsGenerateFullCode=true�̸� #define�� ����ڵ��� ��ü�� ���� �����ϴ�.
	enum enumSys_Force
	{
		EField_BEGIN,
		#ifdef jEXCEL_STRUCT_ENUM_GEN
			for_each_nEXCEL_Sys_Force_STRUCT_FIELD(jEXCEL_STRUCT_ENUM_GEN)
		#endif //jEXCEL_STRUCT_ENUM_GEN
		EField_END
	};
	enum { eSTRUCT_COUNT =  15 };
	static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} 

	#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys_Force
		jEXCEL_TABLE_COMMON_CODE_H_Sys_Force();
	#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys_Force

	#ifdef jEXCEL_SERVER_SIDE_CODE
		#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
			for_each_nEXCEL_Sys_Force_STRUCT_FIELD(jEXCEL_STRUCT_GETTER_SETTER_GEN)
		#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN

		#ifdef jEXCEL_STRUCT_COMMON_CODE
			jEXCEL_STRUCT_COMMON_CODE(Sys_Force)
		#endif // jEXCEL_STRUCT_COMMON_CODE

	#endif //jEXCEL_SERVER_SIDE_CODE

}; // struct Sys_Force
enum { eSTRUCT_SIZE_Sys_Force = sizeof(Sys_Force) };


struct CSV_Sys_Force : public nMech::nUtil::jCSV_File<Sys_Force>
{
	virtual ~CSV_Sys_Force(){}
	virtual bool Load(tcstr _szFile)
	{
		bool isOk = nMech::nUtil::jCSV_File<Sys_Force>::Load(_szFile);
		if(!isOk) return false;
		return true;
	}
};
extern jEXCEL_LIB_API CSV_Sys_Force g_Sys_Force;


#ifdef jEXCEL_TABLE_COMMON_CODE_H_Sys
	for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_H_Sys


#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_ClassItemA[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_ClassItemB[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_E_W_Event[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EForceClass[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EForcePosType[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_force_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
			for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_struct_header_default_function);
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
	for_each_nEXCEL_excel_force_Sys_STRUCT_LIST(jEXCEL_SQ_DECLARE_INSTANCE_TYPE);

#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_force_
