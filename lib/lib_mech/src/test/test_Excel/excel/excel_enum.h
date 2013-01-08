/*------------------------------------------------------------
-------------------------------------------------------------*/

#ifndef __namespace_nEXCEL___filename_excel_enum_
#define __namespace_nEXCEL___filename_excel_enum_

#include "table_const_excel_enum.h"
// -------------------------------------------------
// enum�� �ڵ� ���ø� ����
// -------------------------------------------------
// ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define for_each_nEXCEL_excel_enum_ENUM(ENUM_TABLE)\
	ENUM_TABLE(EAvatarClass,�������,nMech,nEXCEL)\
	ENUM_TABLE(EBuildType_test,�������,nMech,nEXCEL)\
	ENUM_TABLE(EBuildTypeTest,�������,nMech,nEXCEL)\
	ENUM_TABLE(EOutput_test,�������,nMech,nEXCEL)\

	// -------------------------------------------------
	// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)
	// ���� enum������ �տ� e�� �ڵ����� �پ ����� 
	// -------------------------------------------------

	/* ������� */
	#define for_each_nEXCEL_EAvatarClass_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(AC_MERCENARY			,1,�뺴,nMech,nEXCEL,EAvatarClass)\
		ENUM_FIELD(AC_WIZARD			,2,������,nMech,nEXCEL,EAvatarClass)\
		ENUM_FIELD(AC_FIGHTER			,3,������,nMech,nEXCEL,EAvatarClass)\
		ENUM_FIELD(AC_ALL			,4,��� Ŭ����,nMech,nEXCEL,EAvatarClass)\

	/* ������� */
	#define for_each_nEXCEL_EBuildType_test_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EBTTT_Sys_T_HQ			,1,����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Bar			,2,����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_ACADEMY			,3,����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_PEACE			,4,ġ�Ⱥ�,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SHRINE			,5,���,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_HIDEOUT			,6,������,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_TRADINGPOST			,7,������,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_House			,8,�ΰ�,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Farm			,9,����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SAWMILL			,10,�����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_QUARRY			,11,ä����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_MINING			,12,������,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_COCOONERY			,13,�����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Barrack			,14,����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SMITHY			,15,���尣,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_FORGE			,16,����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_STABLE			,17,������,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Camp			,18,�п�,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_Sys_T_Depot			,19,â��,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_SECRET			,20,���â��,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_TOWER			,21,����,nMech,nEXCEL,EBuildType_test)\
		ENUM_FIELD(EBTTT_BARRIER			,22,�溮,nMech,nEXCEL,EBuildType_test)\

	/* ������� */
	#define for_each_nEXCEL_EBuildTypeTest_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(ETT_Sys_T_HQ			,1,����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Bar			,2,����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_ACADEMY			,3,����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_PEACE			,4,ġ�Ⱥ�,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SHRINE			,5,���,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_HIDEOUT			,6,������,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_TRADINGPOST			,7,������,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_House			,8,�ΰ�,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Farm			,9,����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SAWMILL			,10,�����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_QUARRY			,11,ä����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_MINING			,12,������,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_COCOONERY			,13,�����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Barrack			,14,����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SMITHY			,15,���尣,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_FORGE			,16,����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_STABLE			,17,������,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Camp			,18,�п�,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_Sys_T_Depot			,19,â��,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_SECRET			,20,���â��,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_TOWER			,21,����,nMech,nEXCEL,EBuildTypeTest)\
		ENUM_FIELD(ETT_BARRIER			,22,�溮,nMech,nEXCEL,EBuildTypeTest)\

	/* ������� */
	#define for_each_nEXCEL_EOutput_test_ENUM_FIELD(ENUM_FIELD)\
		ENUM_FIELD(EOTTT_POPULATION			,1,�α�,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_GOLD			,2,��,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_FOOD			,3,�ķ�,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_TREE			,4,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_STONE			,5,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_IRON			,6,ö��,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SILK			,7,���,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SOLDIER			,8,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_PIKE			,9,â ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_HEAVY			,10,�߰� ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_HALBERD			,11,����� ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_BOW			,12,�� ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_CROSSBOW			,13,�� ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_BOWGUN			,14,���� ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_BALLISTA			,15,���� ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_CHARIOT			,16,���� ����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_WAGON			,17,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_HORSE			,18,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_WHEELBARROW			,19,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_CART			,20,���,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_LADDER			,21,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_RAM			,22,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_TOWER			,23,����,nMech,nEXCEL,EOutput_test)\
		ENUM_FIELD(EOTTT_SIEGE_TREBUCHET			,24,������,nMech,nEXCEL,EOutput_test)\


// -------------------------------------------------
// �ڵ� ����
// -------------------------------------------------
namespace nMech { namespace nEXCEL 
{

	enum EAvatarClass // �������
	{
		eBEGIN_EAvatarClass = 0,
		/* ���� ������ */
		eAC_MERCENARY = 1, // �뺴
		eAC_WIZARD = 2, // ������
		eAC_FIGHTER = 3, // ������
		/* ��� ����(����, ���� ����) */
		eAC_ALL = 4, // ��� Ŭ����
		eEND_EAvatarClass
	}; // EAvatarClass 



	enum EBuildType_test // �������
	{
		eBEGIN_EBuildType_test = 0,
		/* ���� */
		eEBTTT_Sys_T_HQ = 1, // ����
		/* ���� */
		eEBTTT_Sys_T_Bar = 2, // ����
		/* ���� */
		eEBTTT_ACADEMY = 3, // ����
		/* ġ�Ⱥ� */
		eEBTTT_PEACE = 4, // ġ�Ⱥ�
		/* ��� */
		eEBTTT_SHRINE = 5, // ���
		/* ������ */
		eEBTTT_HIDEOUT = 6, // ������
		/* ������ */
		eEBTTT_TRADINGPOST = 7, // ������
		/* �ΰ� */
		eEBTTT_Sys_T_House = 8, // �ΰ�
		/* ���� */
		eEBTTT_Sys_T_Farm = 9, // ����
		/* ����� */
		eEBTTT_SAWMILL = 10, // �����
		/* ä���� */
		eEBTTT_QUARRY = 11, // ä����
		/* ������ */
		eEBTTT_MINING = 12, // ������
		/* ����� */
		eEBTTT_COCOONERY = 13, // �����
		/* ���� */
		eEBTTT_Sys_T_Barrack = 14, // ����
		/* ���尣 */
		eEBTTT_SMITHY = 15, // ���尣
		/* ���� */
		eEBTTT_FORGE = 16, // ����
		/* ������ */
		eEBTTT_STABLE = 17, // ������
		/* �п� */
		eEBTTT_Sys_T_Camp = 18, // �п�
		/* â�� */
		eEBTTT_Sys_T_Depot = 19, // â��
		/* ���â�� */
		eEBTTT_SECRET = 20, // ���â��
		/* ���� */
		eEBTTT_TOWER = 21, // ����
		/* �溮 */
		eEBTTT_BARRIER = 22, // �溮
		eEND_EBuildType_test
	}; // EBuildType_test 



	enum EBuildTypeTest // �������
	{
		eBEGIN_EBuildTypeTest = 0,
		/* ���� */
		eETT_Sys_T_HQ = 1, // ����
		/* ���� */
		eETT_Sys_T_Bar = 2, // ����
		/* ���� */
		eETT_ACADEMY = 3, // ����
		/* ġ�Ⱥ� */
		eETT_PEACE = 4, // ġ�Ⱥ�
		/* ��� */
		eETT_SHRINE = 5, // ���
		/* ������ */
		eETT_HIDEOUT = 6, // ������
		/* ������ */
		eETT_TRADINGPOST = 7, // ������
		/* �ΰ� */
		eETT_Sys_T_House = 8, // �ΰ�
		/* ���� */
		eETT_Sys_T_Farm = 9, // ����
		/* ����� */
		eETT_SAWMILL = 10, // �����
		/* ä���� */
		eETT_QUARRY = 11, // ä����
		/* ������ */
		eETT_MINING = 12, // ������
		/* ����� */
		eETT_COCOONERY = 13, // �����
		/* ���� */
		eETT_Sys_T_Barrack = 14, // ����
		/* ���尣 */
		eETT_SMITHY = 15, // ���尣
		/* ���� */
		eETT_FORGE = 16, // ����
		/* ������ */
		eETT_STABLE = 17, // ������
		/* �п� */
		eETT_Sys_T_Camp = 18, // �п�
		/* â�� */
		eETT_Sys_T_Depot = 19, // â��
		/* ���â�� */
		eETT_SECRET = 20, // ���â��
		/* ���� */
		eETT_TOWER = 21, // ����
		/* �溮 */
		eETT_BARRIER = 22, // �溮
		eEND_EBuildTypeTest
	}; // EBuildTypeTest 



	enum EOutput_test // �������
	{
		eBEGIN_EOutput_test = 0,
		/* �α� */
		eEOTTT_POPULATION = 1, // �α�
		/* �� */
		eEOTTT_GOLD = 2, // ��
		/* �ķ� */
		eEOTTT_FOOD = 3, // �ķ�
		/* ���� */
		eEOTTT_TREE = 4, // ����
		/* ���� */
		eEOTTT_STONE = 5, // ����
		/* ö�� */
		eEOTTT_IRON = 6, // ö��
		/* ��� */
		eEOTTT_SILK = 7, // ���
		/* ���� */
		eEOTTT_SOLDIER = 8, // ����
		eEOTTT_PIKE = 9, // â ����
		eEOTTT_HEAVY = 10, // �߰� ����
		/* ������ (ö �Ҹ� ����) */
		eEOTTT_HALBERD = 11, // ����� ����
		eEOTTT_BOW = 12, // �� ����
		eEOTTT_CROSSBOW = 13, // �� ����
		eEOTTT_BOWGUN = 14, // ���� ����
		eEOTTT_BALLISTA = 15, // ���� ����
		/* ������ �����ؼ��� ���� (���� �þ��) */
		eEOTTT_CHARIOT = 16, // ���� ����
		/* ������ �����ؼ��� ���� (���� �þ��) */
		eEOTTT_WAGON = 17, // ����
		/* Eunit_ClassItemA �� ���� ���� */
		eEOTTT_HORSE = 18, // ����
		/* ����, ����, ���� �뵵 */
		eEOTTT_WHEELBARROW = 19, // ����
		eEOTTT_CART = 20, // ���
		/* B�� Ȱ�� ���� */
		eEOTTT_SIEGE_LADDER = 21, // ����
		eEOTTT_SIEGE_RAM = 22, // ����
		eEOTTT_SIEGE_TOWER = 23, // ����
		eEOTTT_SIEGE_TREBUCHET = 24, // ������
		eEND_EOutput_test
	}; // EOutput_test 






#ifdef jEXCEL_SERVER_SIDE_CODE
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EAvatarClass[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildType_test[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EBuildTypeTest[];
	extern jEXCEL_LIB_API nExcelUtil::jEnumString g_ES_EOutput_test[];
#endif //jEXCEL_SERVER_SIDE_CODE


} //namespace nEXCEL 

}// namespace nMech 

#ifdef jEXCEL_SERVER_SIDE_CODE
	namespace nExcelUtil{
		using namespace nMech::nEXCEL;
		#ifdef jEXCEL_ENUM_StringToVal
			for_each_nEXCEL_excel_enum_ENUM(jEXCEL_ENUM_StringToVal);
		#endif //jEXCEL_ENUM_StringToVal



		#ifdef jEXCEL_struct_header_default_function
		#endif //jEXCEL_struct_header_default_function

	} // nExcelUtil
#endif //jEXCEL_SERVER_SIDE_CODE

#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;
#endif //jNOT_USE_SQ_BIND_CODE



#endif //__namespace_nEXCEL___filename_excel_enum_
