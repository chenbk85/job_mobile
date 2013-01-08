/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_baseball_table_db.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_enum.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_LocalizingTable.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_ClientResult.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_ServerResult.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_force.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_test2.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_user.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_world.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_hero.txt D:\svn\lib\lib_mech\src\test\test_Excel\excel\excel_castle.txt 

-------------------------------------------------------------*/


using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;
using System.IO;


namespace nEXCEL
{
	//TYPE_INFO
	

	//TYPE_INFO_NS
	using Sys_Hero_id_t = UInt16;
	using Sys_Castle_id_t = UInt16;
	using Sys_TownPos_id_t = UInt16;
	using Sys_Force_id_t = UInt16;
	using Sys__T_Base_id_t = UInt16;
	using Sys_T_Bar_id_t = UInt16;
	using Sys_T__Bar_id_t = UInt16;
	using Sys_T_Barrack_id_t = UInt16;
	using Sys_T_Camp_id_t = UInt16;
	using Sys_T_Depot_id_t = UInt16;
	using Sys_T_Farm_id_t = UInt16;
	using Sys_T_House_id_t = UInt16;
	using Sys_T_HQ_id_t = UInt16;
	using cash_money_t = Int32;
	using Sys_Tile_id_t = UInt16;
	using Sys_World_id_t = UInt16;
	using Sys_T_Test_id_t = UInt16;
	using Sys_T_Test2_id_t = UInt16;
	using Sys_T_Test3_id_t = UInt16;
	using Sys_ItemBase_id_t = UInt16;
	using player_level_t = Int32;
	using Sys_Quest_id_t = UInt16;
	using game_money_t = Int32;
	using pp_point_t = Int32;
	using Sys_ItemEquip_id_t = UInt16;
	using Sys__ItemBase_id_t = UInt16;
	using Sys_RandomGift_id_t = UInt16;
	using g234ame_money_t = Int32;
	using Sys_BreakingBallState_id_t = UInt16;
	using Tbl__PlayerBase_id_t = Int64;
	using Sys_PlayerCard_id_t = UInt16;
	using pimang_id_t = Int32;
	using Tbl_Result_id_t = Int64;
	using Tbl_Item_id_t = Int64;
	using real_money_t = Int32;
	using Tbl_User_id_t = Int64;
	using Tbl_PlayerBetter_id_t = Int64;
	using Tbl_PlayerPitcher_id_t = Int64;
	using Tbl_RoundResult_id_t = Int64;
	using Tbl_Team_id_t = Int64;
	using Sys_Shop_id_t = UInt16;
	using Tbl_BreakingBall_id_t = Int64;
	using Tbl_Friend_id_t = Int64;
	using Sys_Daily_Quest_id_t = UInt16;
	using Sys_Error_id_t = UInt16;
	using Tbl_PitcherSkill_id_t = Int64;
	

	// -------------------------------------------------
	// enum�� �ڵ� ���ø� ����
	// -------------------------------------------------

	public enum EBuildType
	{
		eBEGIN_EBuildType=0,
		EBT_Sys_T_HQ = 1, // [����] ����
		EBT_Sys_T_Bar = 2, // [����] ����
		EBT_ACADEMY = 3, // [����] ����
		EBT_PEACE = 4, // [ġ�Ⱥ�] ġ�Ⱥ�
		EBT_SHRINE = 5, // [���] ���
		EBT_HIDEOUT = 6, // [������] ������
		EBT_TRADINGPOST = 7, // [������] ������
		EBT_Sys_T_House = 8, // [�ΰ�] �ΰ�
		EBT_Sys_T_Farm = 9, // [����] ����
		EBT_SAWMILL = 10, // [�����] �����
		EBT_QUARRY = 11, // [ä����] ä����
		EBT_MINING = 12, // [������] ������
		EBT_COCOONERY = 13, // [�����] �����
		EBT_Sys_T_Barrack = 14, // [����] ����
		EBT_SMITHY = 15, // [���尣] ���尣
		EBT_FORGE = 16, // [����] ����
		EBT_STABLE = 17, // [������] ������
		EBT_Sys_T_Camp = 18, // [�п�] �п�
		EBT_Sys_T_Depot = 19, // [â��] â��
		EBT_SECRET = 20, // [���â��] ���â��
		EBT_TOWER = 21, // [����] ����
		EBT_BARRIER = 22, // [�溮] �溮
		eEND_EBuildType,
	}
	namespace nUtil
	{
		class jString_EBuildType
		{
			public static void Parse(string sDebug,string sVal, ref EBuildType eVal) 
			{
				eVal = (EBuildType)Enum.Parse(typeof(EBuildType), sVal);
			}
		}
	}


	public enum EOutput
	{
		eBEGIN_EOutput=0,
		EOT_POPULATION = 1, // [�α�] �α�
		EOT_GOLD = 2, // [��] ��
		EOT_FOOD = 3, // [�ķ�] �ķ�
		EOT_TREE = 4, // [����] ����
		EOT_STONE = 5, // [����] ����
		EOT_IRON = 6, // [ö��] ö��
		EOT_SILK = 7, // [���] ���
		EOT_SOLDIER = 8, // [����] ����
		EOT_PIKE = 9, // [â ����] 
		EOT_HEAVY = 10, // [�߰� ����] 
		EOT_HALBERD = 11, // [����� ����] ������ (ö �Ҹ� ����)
		EOT_BOW = 12, // [�� ����] 
		EOT_CROSSBOW = 13, // [�� ����] 
		EOT_BOWGUN = 14, // [���� ����] 
		EOT_BALLISTA = 15, // [���� ����] 
		EOT_CHARIOT = 16, // [���� ����] ������ �����ؼ��� ���� (���� �þ��)
		EOT_WAGON = 17, // [����] ������ �����ؼ��� ���� (���� �þ��)
		EOT_HORSE = 18, // [����] Eunit_ClassItemA �� ���� ����
		EOT_WHEELBARROW = 19, // [����] ����, ����, ���� �뵵
		EOT_CART = 20, // [���] 
		EOT_SIEGE_LADDER = 21, // [����] B�� Ȱ�� ����
		EOT_SIEGE_RAM = 22, // [����] 
		EOT_SIEGE_TOWER = 23, // [����] 
		EOT_SIEGE_TREBUCHET = 24, // [������] 
		eEND_EOutput,
	}
	namespace nUtil
	{
		class jString_EOutput
		{
			public static void Parse(string sDebug,string sVal, ref EOutput eVal) 
			{
				eVal = (EOutput)Enum.Parse(typeof(EOutput), sVal);
			}
		}
	}

	// -------------------------------------------------
	// ����type ���̺��� base ���̺��̴�. ��� ����type ���̺��� �� ���̺��� ��ӹ޴´�
	// -------------------------------------------------

	public class Sys__T_BuildObj
	{
		public EBuildType m_base_type; 	// [�ǹ�Ÿ��] Sys_T_BaseObj����� �޴� ���̺��� �ǹ� ���� 
		public string m_name; 	// [�ǹ����ҽ���] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_EBuildType.Parse("Sys__T_BuildObj::base_type",token[idx++], ref m_base_type);
			nUtil.jString_string.Parse("Sys__T_BuildObj::name",token[idx++], ref m_name);
			nUtil.jString_UInt32.Parse("Sys__T_BuildObj::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys__T_BuildObj::population_num",token[idx++], ref m_population_num);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_base_type.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			return output;
		}
	}//class Sys__T_BuildObj

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_T_Bar
	{
		public Sys_T_Bar_id_t m_isid; 	// [����] �ǹ� ���̵� 
		public string m_client_file; 	// [�ǹ� �̹��� ����] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		public Int16 m_maxbuild; 	// [�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn; 	// [���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public Int16 m_stonereturn; 	// [�� ��ȯ���]  
		public Int16 m_ironreturn; 	// [ö ��ȯ���]  
		public Int16 m_silkreturn; 	// [��� ��ȯ���]  
		public Int16 m_populationreturn; 	// [�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public Int16 m_hideHero; 	// [��� ���] ������ ������ ������ �� 
		public UInt32 m_resettime; 	// [���½ð�] �������� �ڵ����� �������� �������� ���µǴ� �ð� (�ʷΰ��) 
		public Int16 m_itemnum; 	// [�����ۼ�] �������� ������� 1ȸ�� �������� ������ �� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Bar::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Bar::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Bar::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Bar::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Bar::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Bar::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Bar::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Bar::hideHero",token[idx++], ref m_hideHero);
			nUtil.jString_UInt32.Parse("Sys_T_Bar::resettime",token[idx++], ref m_resettime);
			nUtil.jString_Int16.Parse("Sys_T_Bar::itemnum",token[idx++], ref m_itemnum);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_hideHero.ToString() + ",";
			output += m_resettime.ToString() + ",";
			output += m_itemnum.ToString() + ",";
			return output;
		}
	}//class Sys_T_Bar

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_T_Barrack
	{
		public Sys_T_Barrack_id_t m_isid; 	// [����] �ǹ� ���̵� 
		public string m_client_file; 	// [�ǹ� �̹��� ����] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		public Int16 m_maxbuild; 	// [�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn; 	// [���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public Int16 m_stonereturn; 	// [�� ��ȯ���]  
		public Int16 m_ironreturn; 	// [ö ��ȯ���]  
		public Int16 m_silkreturn; 	// [��� ��ȯ���]  
		public Int16 m_populationreturn; 	// [�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public Int16 m_s_p_speed; 	// [����_����_�ӵ�] ���� �������� ����ӵ� ��� 
		public Int16 m_s_p_cost; 	// [����_����_���] �������� 1�� ���� ��� 
		public Int16 m_s_output; 	// [����_ ���귮] �������� �ִ� ���귮 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Barrack::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Barrack::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Barrack::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::s_p_speed",token[idx++], ref m_s_p_speed);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::s_p_cost",token[idx++], ref m_s_p_cost);
			nUtil.jString_Int16.Parse("Sys_T_Barrack::s_output",token[idx++], ref m_s_output);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_s_p_speed.ToString() + ",";
			output += m_s_p_cost.ToString() + ",";
			output += m_s_output.ToString() + ",";
			return output;
		}
	}//class Sys_T_Barrack

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_T_Camp
	{
		public Sys_T_Camp_id_t m_isid; 	// [����] �ǹ� ���̵� 
		public string m_client_file; 	// [�ǹ� �̹��� ����] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		public Int16 m_maxbuild; 	// [�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn; 	// [���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public Int16 m_stonereturn; 	// [�� ��ȯ���]  
		public Int16 m_ironreturn; 	// [ö ��ȯ���]  
		public Int16 m_silkreturn; 	// [��� ��ȯ���]  
		public Int16 m_populationreturn; 	// [�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public Int16 m_f_r_spend; 	// [����_ �ķ�_�Һ�] ���� 1���� �ð��� �Һ��ϴ� �ķ��� �� 
		public Int32 m_f_storage; 	// [����_������] �п����� ���� �ִ� ������ 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Camp::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Camp::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Camp::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Camp::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Camp::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Camp::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Camp::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Camp::f_r_spend",token[idx++], ref m_f_r_spend);
			nUtil.jString_Int32.Parse("Sys_T_Camp::f_storage",token[idx++], ref m_f_storage);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_f_r_spend.ToString() + ",";
			output += m_f_storage.ToString() + ",";
			return output;
		}
	}//class Sys_T_Camp

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_T_Depot
	{
		public Sys_T_Depot_id_t m_isid; 	// [����] �ǹ� ���̵� 
		public string m_client_file; 	// [�ǹ� �̹��� ����] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		public Int16 m_maxbuild; 	// [�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn; 	// [���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public Int16 m_stonereturn; 	// [�� ��ȯ���]  
		public Int16 m_ironreturn; 	// [ö ��ȯ���]  
		public Int16 m_silkreturn; 	// [��� ��ȯ���]  
		public Int16 m_populationreturn; 	// [�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public Int32 m_storage; 	// [�ִ뺸����] â���� �ڿ� �ִ� ������ 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Depot::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Depot::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Depot::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Depot::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Depot::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Depot::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Depot::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Depot::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int32.Parse("Sys_T_Depot::storage",token[idx++], ref m_storage);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_storage.ToString() + ",";
			return output;
		}
	}//class Sys_T_Depot

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_T_Farm
	{
		public Sys_T_Farm_id_t m_isid; 	// [����] �ǹ� ���̵� 
		public string m_client_file; 	// [�ǹ� �̹��� ����] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		public Int16 m_maxbuild; 	// [�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn; 	// [���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public Int16 m_stonereturn; 	// [�� ��ȯ���]  
		public Int16 m_ironreturn; 	// [ö ��ȯ���]  
		public Int16 m_silkreturn; 	// [��� ��ȯ���]  
		public Int16 m_populationreturn; 	// [�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public Int16 m_foodoutput; 	// [�ķ����귮] �� �������� ���� ���귮 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_Farm::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_Farm::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_Farm::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_Farm::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_Farm::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Farm::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Farm::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_Farm::foodoutput",token[idx++], ref m_foodoutput);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_foodoutput.ToString() + ",";
			return output;
		}
	}//class Sys_T_Farm

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_T_House
	{
		public Sys_T_House_id_t m_isid; 	// [����] �ǹ� ���̵� 
		public string m_client_file; 	// [�ǹ� �̹��� ����] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		public Int16 m_maxbuild; 	// [�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn; 	// [���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public Int16 m_stonereturn; 	// [�� ��ȯ���]  
		public Int16 m_ironreturn; 	// [ö ��ȯ���]  
		public Int16 m_silkreturn; 	// [��� ��ȯ���]  
		public Int16 m_populationreturn; 	// [�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public Int16 m_maxpopulation; 	// [�ΰ��ִ��α�] �ΰ� ������ ��µǴ� �ִ� �α��� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_House::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_House::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_House::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_House::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_House::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_House::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_House::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_House::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_House::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_House::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_House::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_House::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_House::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_House::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_House::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_House::maxpopulation",token[idx++], ref m_maxpopulation);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_maxpopulation.ToString() + ",";
			return output;
		}
	}//class Sys_T_House

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_T_HQ
	{
		public Sys_T_HQ_id_t m_isid; 	// [����] �ǹ� ���̵� 
		public string m_client_file; 	// [�ǹ� �̹��� ����] �ǹ� �̹���: ������ ���� �̹��� ���� -������ �ִ� ���ҽ� �̸� 
		public UInt32 m_upgradetime; 	// [���׷��̵� �ð�] ���׷��̵带 ������ �� �Һ�Ǵ� �ð� /�ʴ��� 
		public Int16 m_tree_num; 	// [���� ���] �Ǽ��� �ʿ��� ���� ��� 
		public Int16 m_stone_num; 	// [�� ���] �Ǽ��� �ʿ��� �� ��� 
		public Int16 m_iron_num; 	// [ö ���] �Ǽ��� �ʿ��� ö ��� 
		public Int16 m_silk_num; 	// [��� ���] �Ǽ��� �ʿ��� ��� ��� 
		public Int16 m_population_num; 	// [�α� ���] �Ǽ��� �ʿ��� �α� ��� 
		public Int16 m_maxbuild; 	// [�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn; 	// [���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public Int16 m_stonereturn; 	// [�� ��ȯ���]  
		public Int16 m_ironreturn; 	// [ö ��ȯ���]  
		public Int16 m_silkreturn; 	// [��� ��ȯ���]  
		public Int16 m_populationreturn; 	// [�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public Int16 m_getgold; 	// [¡��] ¡�� ��� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_T_HQ::isid",token[idx++], ref m_isid);
			nUtil.jString_string.Parse("Sys_T_HQ::client_file",token[idx++], ref m_client_file);
			nUtil.jString_UInt32.Parse("Sys_T_HQ::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys_T_HQ::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::population_num",token[idx++], ref m_population_num);
			nUtil.jString_Int16.Parse("Sys_T_HQ::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_HQ::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_HQ::treereturn",token[idx++], ref m_treereturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::stonereturn",token[idx++], ref m_stonereturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::ironreturn",token[idx++], ref m_ironreturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::silkreturn",token[idx++], ref m_silkreturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_Int16.Parse("Sys_T_HQ::getgold",token[idx++], ref m_getgold);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_isid.ToString() + ",";
			output += m_client_file.ToString() + ",";
			output += m_upgradetime.ToString() + ",";
			output += m_tree_num.ToString() + ",";
			output += m_stone_num.ToString() + ",";
			output += m_iron_num.ToString() + ",";
			output += m_silk_num.ToString() + ",";
			output += m_population_num.ToString() + ",";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_treereturn.ToString() + ",";
			output += m_stonereturn.ToString() + ",";
			output += m_ironreturn.ToString() + ",";
			output += m_silkreturn.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_getgold.ToString() + ",";
			return output;
		}
	}//class Sys_T_HQ

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_T_Bar
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Bar>		m_List = new List<Sys_T_Bar> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Bar >>>");
			foreach (Sys_T_Bar p in CSV_Sys_T_Bar.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Bar       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_T_Bar info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Bar();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Bar


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_T_Barrack
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Barrack>		m_List = new List<Sys_T_Barrack> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Barrack >>>");
			foreach (Sys_T_Barrack p in CSV_Sys_T_Barrack.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Barrack       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_T_Barrack info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Barrack();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Barrack


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_T_Camp
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Camp>		m_List = new List<Sys_T_Camp> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Camp >>>");
			foreach (Sys_T_Camp p in CSV_Sys_T_Camp.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Camp       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_T_Camp info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Camp();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Camp


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_T_Depot
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Depot>		m_List = new List<Sys_T_Depot> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Depot >>>");
			foreach (Sys_T_Depot p in CSV_Sys_T_Depot.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Depot       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_T_Depot info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Depot();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Depot


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_T_Farm
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_Farm>		m_List = new List<Sys_T_Farm> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Farm >>>");
			foreach (Sys_T_Farm p in CSV_Sys_T_Farm.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_Farm       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_T_Farm info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Farm();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_Farm


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_T_House
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_House>		m_List = new List<Sys_T_House> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_House >>>");
			foreach (Sys_T_House p in CSV_Sys_T_House.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_House       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_T_House info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_House();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_House


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_T_HQ
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_T_HQ>		m_List = new List<Sys_T_HQ> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_HQ >>>");
			foreach (Sys_T_HQ p in CSV_Sys_T_HQ.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_T_HQ       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static void _makeIndex()
		{
		}
		public static void LoadCSV(string sCsvFileName)
		{
			string sLine = "";
			string[] token;
			
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				Sys_T_HQ info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_HQ();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

	}// public class CSV_Sys_T_HQ



	


}//namespace nEXCEL
