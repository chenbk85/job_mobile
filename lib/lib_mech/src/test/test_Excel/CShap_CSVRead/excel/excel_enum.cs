/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test2.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_enum.txt 

-------------------------------------------------------------*/


using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;


namespace nEXCEL
{
	//TYPE_INFO
	

	//TYPE_INFO_NS
	using Sys_Hero_id_t = UInt16;
	using Sys_Castle_id_t = UInt16;
	using Sys_TownPos_id_t = UInt16;
	using Use_User_id_t = Int64;
	using Sys_Force_id_t = UInt16;
	using Use_F_Transport_id_t = Int64;
	using Use_Force_id_t = Int64;
	using Use_Town_id_t = Int64;
	using Use_Hero_id_t = Int64;
	using Sys__T_Base_id_t = UInt16;
	using Sys_T_Bar_id_t = UInt16;
	using Sys_T__Bar_id_t = UInt16;
	using Sys_T_Barrack_id_t = UInt16;
	using Sys_T_Camp_id_t = UInt16;
	using Sys_T_Depot_id_t = UInt16;
	using Sys_T_Farm_id_t = UInt16;
	using Sys_T_House_id_t = UInt16;
	using Sys_T_HQ_id_t = UInt16;
	using Use_T_Output_id_t = Int64;
	using cash_money_t = Int32;
	using Sys_Tile_id_t = UInt16;
	using Sys_World_id_t = UInt16;
	using Sys_T_Test_id_t = UInt16;
	using Sys_T_Test2_id_t = UInt16;
	using Sys_T_Test3_id_t = UInt16;
	

	// -------------------------------------------------
	// enum�� �ڵ� ���ø� ����
	// -------------------------------------------------

	public enum EAvatarClass
	{
		eBEGIN_EAvatarClass=0,
		AC_MERCENARY = 1, // [�뺴] ���� ������
		AC_WIZARD = 2, // [������] 
		AC_FIGHTER = 3, // [������] 
		AC_ALL = 4, // [��� Ŭ����] ��� ����(����, ���� ����)
		eEND_EAvatarClass,
	}
	namespace nUtil
	{
		class FromString_EAvatarClass
		{
			public static void Parse(string sDebug,string sVal, ref EAvatarClass eVal) 
			{
				eVal = (EAvatarClass)Enum.Parse(typeof(EAvatarClass), sVal);
			}
		}
	}


	public enum EBuildType_test
	{
		eBEGIN_EBuildType_test=0,
		EBTTT_Sys_T_HQ = 1, // [����] ����
		EBTTT_Sys_T_Bar = 2, // [����] ����
		EBTTT_ACADEMY = 3, // [����] ����
		EBTTT_PEACE = 4, // [ġ�Ⱥ�] ġ�Ⱥ�
		EBTTT_SHRINE = 5, // [���] ���
		EBTTT_HIDEOUT = 6, // [������] ������
		EBTTT_TRADINGPOST = 7, // [������] ������
		EBTTT_Sys_T_House = 8, // [�ΰ�] �ΰ�
		EBTTT_Sys_T_Farm = 9, // [����] ����
		EBTTT_SAWMILL = 10, // [�����] �����
		EBTTT_QUARRY = 11, // [ä����] ä����
		EBTTT_MINING = 12, // [������] ������
		EBTTT_COCOONERY = 13, // [�����] �����
		EBTTT_Sys_T_Barrack = 14, // [����] ����
		EBTTT_SMITHY = 15, // [���尣] ���尣
		EBTTT_FORGE = 16, // [����] ����
		EBTTT_STABLE = 17, // [������] ������
		EBTTT_Sys_T_Camp = 18, // [�п�] �п�
		EBTTT_Sys_T_Depot = 19, // [â��] â��
		EBTTT_SECRET = 20, // [���â��] ���â��
		EBTTT_TOWER = 21, // [����] ����
		EBTTT_BARRIER = 22, // [�溮] �溮
		eEND_EBuildType_test,
	}
	namespace nUtil
	{
		class FromString_EBuildType_test
		{
			public static void Parse(string sDebug,string sVal, ref EBuildType_test eVal) 
			{
				eVal = (EBuildType_test)Enum.Parse(typeof(EBuildType_test), sVal);
			}
		}
	}


	public enum EBuildTypeTest
	{
		eBEGIN_EBuildTypeTest=0,
		ETT_Sys_T_HQ = 1, // [����] ����
		ETT_Sys_T_Bar = 2, // [����] ����
		ETT_ACADEMY = 3, // [����] ����
		ETT_PEACE = 4, // [ġ�Ⱥ�] ġ�Ⱥ�
		ETT_SHRINE = 5, // [���] ���
		ETT_HIDEOUT = 6, // [������] ������
		ETT_TRADINGPOST = 7, // [������] ������
		ETT_Sys_T_House = 8, // [�ΰ�] �ΰ�
		ETT_Sys_T_Farm = 9, // [����] ����
		ETT_SAWMILL = 10, // [�����] �����
		ETT_QUARRY = 11, // [ä����] ä����
		ETT_MINING = 12, // [������] ������
		ETT_COCOONERY = 13, // [�����] �����
		ETT_Sys_T_Barrack = 14, // [����] ����
		ETT_SMITHY = 15, // [���尣] ���尣
		ETT_FORGE = 16, // [����] ����
		ETT_STABLE = 17, // [������] ������
		ETT_Sys_T_Camp = 18, // [�п�] �п�
		ETT_Sys_T_Depot = 19, // [â��] â��
		ETT_SECRET = 20, // [���â��] ���â��
		ETT_TOWER = 21, // [����] ����
		ETT_BARRIER = 22, // [�溮] �溮
		eEND_EBuildTypeTest,
	}
	namespace nUtil
	{
		class FromString_EBuildTypeTest
		{
			public static void Parse(string sDebug,string sVal, ref EBuildTypeTest eVal) 
			{
				eVal = (EBuildTypeTest)Enum.Parse(typeof(EBuildTypeTest), sVal);
			}
		}
	}


	public enum EOutput_test
	{
		eBEGIN_EOutput_test=0,
		EOTTT_POPULATION = 1, // [�α�] �α�
		EOTTT_GOLD = 2, // [��] ��
		EOTTT_FOOD = 3, // [�ķ�] �ķ�
		EOTTT_TREE = 4, // [����] ����
		EOTTT_STONE = 5, // [����] ����
		EOTTT_IRON = 6, // [ö��] ö��
		EOTTT_SILK = 7, // [���] ���
		EOTTT_SOLDIER = 8, // [����] ����
		EOTTT_PIKE = 9, // [â ����] 
		EOTTT_HEAVY = 10, // [�߰� ����] 
		EOTTT_HALBERD = 11, // [����� ����] ������ (ö �Ҹ� ����)
		EOTTT_BOW = 12, // [�� ����] 
		EOTTT_CROSSBOW = 13, // [�� ����] 
		EOTTT_BOWGUN = 14, // [���� ����] 
		EOTTT_BALLISTA = 15, // [���� ����] 
		EOTTT_CHARIOT = 16, // [���� ����] ������ �����ؼ��� ���� (���� �þ��)
		EOTTT_WAGON = 17, // [����] ������ �����ؼ��� ���� (���� �þ��)
		EOTTT_HORSE = 18, // [����] Eunit_ClassItemA �� ���� ����
		EOTTT_WHEELBARROW = 19, // [����] ����, ����, ���� �뵵
		EOTTT_CART = 20, // [���] 
		EOTTT_SIEGE_LADDER = 21, // [����] B�� Ȱ�� ����
		EOTTT_SIEGE_RAM = 22, // [����] 
		EOTTT_SIEGE_TOWER = 23, // [����] 
		EOTTT_SIEGE_TREBUCHET = 24, // [������] 
		eEND_EOutput_test,
	}
	namespace nUtil
	{
		class FromString_EOutput_test
		{
			public static void Parse(string sDebug,string sVal, ref EOutput_test eVal) 
			{
				eVal = (EOutput_test)Enum.Parse(typeof(EOutput_test), sVal);
			}
		}
	}


	


}//namespace nEXCEL
