/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_baseball_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_db.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_game.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_item.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_shop.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_string_table.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_etc.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_animation.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_Eng.txt D:\svn\baseball\doc\design\excel\code\excel_baseball_table_client_locale_kor.txt 

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
	using Tbl_Package_id_t = Int64;
	using Sys_Package_id_t = UInt16;
	using Sys_Runner_State_id_t = UInt16;
	using Tbl_Quest_id_t = Int64;
	using Sys_Title_id_t = UInt16;
	using Tbl_Title_id_t = Int64;
	using Tbl_PlayerSkillSticker_id_t = Int64;
	using Sys_PlayerSkillSticker_id_t = UInt16;
	using Sys_Batter_id_t = UInt16;
	using Sys_Pitcher_id_t = UInt16;
	using Sys_Better_id_t = UInt16;
	

	// -------------------------------------------------
	// enum�� �ڵ� ���ø� ����
	// -------------------------------------------------

	public enum EBatterAnimationType : byte
	{
		eBEGIN_EBatterAnimationType=0,
		EBAT_STARTUP = 1, // [Startup] ���͹ڽ����� �Ѽ����� �������� ���ظ� ���ϰ�, �߷� ���� ���� Ÿ�� �ڼ� ���
		EBAT_MAXAFTER = 2, // [Max After] ������ ���Ľ����� ��ƮĿ�� �ƽø� ���ٰ� ��Ÿ ���̵�� ����
		EBAT_MAX = 3, // [Max] ������ ���Ľ����� ��ƮĿ�� �ƽø� ����� �� ���̵�
		EBAT_IDLE = 4, // [Idle] ������ ���Ľ����� ����̸� 1�ڷ� ����� �ణ ���� �ڼ�
		EBAT_READY = 5, // [Ready] ������ ���Ľ����� Ÿ���غ�
		EBAT_SWING_LEFT = 6, // [���� ����] ������ ���Ľ����� ���� ���� (������ �ٶ󺸴� ��������) (1_�ϴ� 2_���ϴ� 3_�ߴ� 4_�߻�� 5_���)
		EBAT_SWING_MIDDLE = 7, // [�߰� ����] ������ ���Ľ����� �߰� ���� (������ �ٶ󺸴� ��������) (1_�ϴ� 2_���ϴ� 3_�ߴ� 4_�߻�� 5_���)
		EBAT_SWING_RIGHT = 8, // [������ ����] ������ ���Ľ����� ������ ���� (������ �ٶ󺸴� ��������) (1_�ϴ� 2_���ϴ� 3_�ߴ� 4_�߻�� 5_���)
		EBAT_MAUVAIS = 9, // [�꽺��] ������ ���Ľ����� �꽺��
		EBAT_WINLOSE = 10, // [���Ӱ��â���� �̱�ų� ���� ��] ���Ӱ��â���� �̱�ų� ���� ��
		EBAT_MENUUI = 11, // [MENU UI���� ����] MENU UI���� ����
		eEND_EBatterAnimationType,
	}
	namespace nUtil
	{
		public class jString_EBatterAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref EBatterAnimationType eVal) 
			{
				eVal = (EBatterAnimationType)Enum.Parse(typeof(EBatterAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EBatterAnimationType i = EBatterAnimationType.eBEGIN_EBatterAnimationType +1;i < EBatterAnimationType.eEND_EBatterAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EBatterAnimationType> get_enums() 
			{
				List<EBatterAnimationType> list = new List<EBatterAnimationType>();
				for (EBatterAnimationType i = EBatterAnimationType.eBEGIN_EBatterAnimationType +1;i < EBatterAnimationType.eEND_EBatterAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum ECatcherAnimationType : byte
	{
		eBEGIN_ECatcherAnimationType=0,
		ECAT_STARTUP_IDLE = 1, // [Startup] ���� ������ �� ���� ���̵�
		ECAT_MITCATCH = 2, // [��Ʈ �� ĳġ] ������ ��Ʈ ��� �ش� ��ġ �̵� ���¿��� �� ĳġ ���� (1=���ϴ� 2=���ߴ� 3=�ϻ�� 4=���ϴ� 5=���ߴ� 6=�߻�� 7=���ϴ� 8=���ߴ� 9=���� 10=�ֻ��ϴ� 11=�ֻ��ߴ� 12=�ֻ���)
		ECAT_MOVE_MIDDLE = 3, // [���� �ߴ� �̵�] ���� ��ü �ߴ� �̵�
		ECAT_MOVE_LEFT = 4, // [���� ���� �̵�] ���� ��ü ���� �̵�
		ECAT_MOVE_RIGHT = 5, // [���� ������ �̵�] ���� ��ü ������ �̵�
		ECAT_BACK_MIDDLE = 6, // [���� �ߴ� �̵� �� ���ƿ���] ���� �ߴ� �̵� �� ���ƿ���
		ECAT_BACK_LEFT = 7, // [���� ���� �̵� �� ���ƿ���] ���� ���� �̵� �� ���ƿ���
		ECAT_BACK_RIGHT = 8, // [���� ������ �̵� �� ���ƿ���] ���� ������ �̵� �� ���ƿ���
		eEND_ECatcherAnimationType,
	}
	namespace nUtil
	{
		public class jString_ECatcherAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref ECatcherAnimationType eVal) 
			{
				eVal = (ECatcherAnimationType)Enum.Parse(typeof(ECatcherAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (ECatcherAnimationType i = ECatcherAnimationType.eBEGIN_ECatcherAnimationType +1;i < ECatcherAnimationType.eEND_ECatcherAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<ECatcherAnimationType> get_enums() 
			{
				List<ECatcherAnimationType> list = new List<ECatcherAnimationType>();
				for (ECatcherAnimationType i = ECatcherAnimationType.eBEGIN_ECatcherAnimationType +1;i < ECatcherAnimationType.eEND_ECatcherAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EEumpireAnimationType : byte
	{
		eBEGIN_EEumpireAnimationType=0,
		EEAT_PLAYBALL = 1, // [��� ����] ��� ����
		EEAT_IDLE = 2, // [��� ���� ���̵�] ��� ���� ���̵�
		EEAT_DECISION_PERFECT = 3, // [����Ʈ ����] ����Ʈ ����
		EEAT_DECISION_GOOD = 4, // [�� ����] �� ����
		EEAT_DECISION_NORMAL = 5, // [��� ����] ��� ����
		EEAT_DECISION_BAD = 6, // [��� ����] ��� ����
		eEND_EEumpireAnimationType,
	}
	namespace nUtil
	{
		public class jString_EEumpireAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref EEumpireAnimationType eVal) 
			{
				eVal = (EEumpireAnimationType)Enum.Parse(typeof(EEumpireAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EEumpireAnimationType i = EEumpireAnimationType.eBEGIN_EEumpireAnimationType +1;i < EEumpireAnimationType.eEND_EEumpireAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EEumpireAnimationType> get_enums() 
			{
				List<EEumpireAnimationType> list = new List<EEumpireAnimationType>();
				for (EEumpireAnimationType i = EEumpireAnimationType.eBEGIN_EEumpireAnimationType +1;i < EEumpireAnimationType.eEND_EEumpireAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}


	public enum EPitcherAnimationType : byte
	{
		eBEGIN_EPitcherAnimationType=0,
		EPAT_STARTUP_IDL = 1, // [��� ���̵� 1] ��� ������ ������ ���̵�
		EPAT_HIT_AFTER = 2, // [���� ��Ʈ �� �� ����(�� ��)] ���� ��Ʈ �� �� ����(��=1 ��=2)
		EPAT_YES = 3, // [���� ���� ����] ��� ���� ������ �� ����
		EPAT_NO = 4, // [���� ���� �ź�] ��� ���� �� �� ��������
		EPAT_STARTUP = 5, // [Startup] ������ ���� �� ����� �ڸ����
		EPAT_PITCHING = 6, // [����] �����ڵ忡�� ���� ����, ��� �ڼ�  ����
		EPAT_BACK = 7, // [���� �� �ǵ��ư���] ���� �� �ǵ��ư���
		EPAT_CEREMONY = 8, // [�����Ӵ�] Ÿ�ڰ� ��Ʈ���� ������ �� �ָ��� ������ �Ҳ� ��� �ƽ�
		EPAT_WINLOSE = 9, // [���Ӱ��â���� �̱�ų� ���� ��] ���Ӱ��â���� �̱�ų� ���� ��
		EPAT_MENUUI = 10, // [MENU UI���� ����] MENU UI���� ����
		eEND_EPitcherAnimationType,
	}
	namespace nUtil
	{
		public class jString_EPitcherAnimationType
		{
			public static void Parse(string sDebug,string sVal, ref EPitcherAnimationType eVal) 
			{
				eVal = (EPitcherAnimationType)Enum.Parse(typeof(EPitcherAnimationType), sVal);
			}
			public static List<string> get_strings() 
			{
				List<string> list = new List<string>();
				for (EPitcherAnimationType i = EPitcherAnimationType.eBEGIN_EPitcherAnimationType +1;i < EPitcherAnimationType.eEND_EPitcherAnimationType; i++){list.Add(i.ToString());}
				return list;
			}
			public static List<EPitcherAnimationType> get_enums() 
			{
				List<EPitcherAnimationType> list = new List<EPitcherAnimationType>();
				for (EPitcherAnimationType i = EPitcherAnimationType.eBEGIN_EPitcherAnimationType +1;i < EPitcherAnimationType.eEND_EPitcherAnimationType; i++){list.Add(i);}
				return list;
			}
		}
	}

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Batter_Animation
	{
		public Int16 m_index; 	// [index] �����г��� , �������̺��� ��� 
		public EPlayerBodyType m_body_type; 	// [ü��] ü�� 
		public EBatterForm m_better_form; 	// [Ÿ�� ��] Ÿ�� �� 
		public EBatterAnimationType m_batter_animation; 	// [Ÿ�ھִϸ��̼�] Ÿ�� �ִϸ��̼� ���� 
		public Int16 m_animation_number; 	// [�ش� �ִϸ��̼� �ѹ�] �ش� �ִϸ��̼��� �ѹ� 
		public string m_animation_filename; 	// [�ش� �ִϸ��̼� ���� �̸�] �ش� ���ϸ��̼� ���� �̸� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Batter_Animation::index",token[idx++], ref m_index);
				nUtil.jString_EPlayerBodyType.Parse("Sys_Batter_Animation::body_type",token[idx++], ref m_body_type);
				nUtil.jString_EBatterForm.Parse("Sys_Batter_Animation::better_form",token[idx++], ref m_better_form);
				nUtil.jString_EBatterAnimationType.Parse("Sys_Batter_Animation::batter_animation",token[idx++], ref m_batter_animation);
				nUtil.jString_Int16.Parse("Sys_Batter_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Batter_Animation::animation_filename",token[idx++], ref m_animation_filename);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output += m_index.ToString() + ",";
			output += m_body_type.ToString() + ",";
			output += m_better_form.ToString() + ",";
			output += m_batter_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Batter_Animation

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Catcher_Animation
	{
		public Int16 m_index; 	// [index] �����г��� , �������̺��� ��� 
		public ECatcherAnimationType m_catcher_animation; 	// [�����ִϸ��̼�] ���� �ִϸ��̼� ���� 
		public Int16 m_animation_number; 	// [�ش� �ִϸ��̼� �ѹ�] �ش� �ִϸ��̼��� �ѹ� 
		public string m_animation_filename; 	// [�ش� �ִϸ��̼� ���� �̸�] �ش� ���ϸ��̼� ���� �̸� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Catcher_Animation::index",token[idx++], ref m_index);
				nUtil.jString_ECatcherAnimationType.Parse("Sys_Catcher_Animation::catcher_animation",token[idx++], ref m_catcher_animation);
				nUtil.jString_Int16.Parse("Sys_Catcher_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Catcher_Animation::animation_filename",token[idx++], ref m_animation_filename);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output += m_index.ToString() + ",";
			output += m_catcher_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Catcher_Animation

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Pitcher_Animation
	{
		public Int16 m_index; 	// [index] �����г��� , �������̺��� ��� 
		public EPlayerBodyType m_body_type; 	// [ü��] ü�� 
		public EPitcherForm m_pitcher_form; 	// [������] ������ 
		public EPitcherAnimationType m_pitcher_animation; 	// [�����ִϸ��̼�] ���� �ִϸ��̼� ���� 
		public Int16 m_animation_number; 	// [�ش� �ִϸ��̼� �ѹ�] �ش� �ִϸ��̼��� �ѹ� 
		public string m_animation_filename; 	// [�ش� �ִϸ��̼� ���� �̸�] �ش� ���ϸ��̼� ���� �̸� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Pitcher_Animation::index",token[idx++], ref m_index);
				nUtil.jString_EPlayerBodyType.Parse("Sys_Pitcher_Animation::body_type",token[idx++], ref m_body_type);
				nUtil.jString_EPitcherForm.Parse("Sys_Pitcher_Animation::pitcher_form",token[idx++], ref m_pitcher_form);
				nUtil.jString_EPitcherAnimationType.Parse("Sys_Pitcher_Animation::pitcher_animation",token[idx++], ref m_pitcher_animation);
				nUtil.jString_Int16.Parse("Sys_Pitcher_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Pitcher_Animation::animation_filename",token[idx++], ref m_animation_filename);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output += m_index.ToString() + ",";
			output += m_body_type.ToString() + ",";
			output += m_pitcher_form.ToString() + ",";
			output += m_pitcher_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Pitcher_Animation

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Umpire_Animation
	{
		public Int16 m_index; 	// [index] �����г��� , �������̺��� ��� 
		public EEumpireAnimationType m_umpire_animation; 	// [���Ǿִϸ��̼�] ���� �ִϸ��̼� ���� 
		public Int16 m_animation_number; 	// [�ش� �ִϸ��̼� �ѹ�] �ش� �ִϸ��̼��� �ѹ� 
		public string m_animation_filename; 	// [�ش� �ִϸ��̼� ���� �̸�] �ش� ���ϸ��̼� ���� �̸� 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{
			try{
				int iStart=idx;
				bool isFind=false;
				nUtil.jCSV.not_thing(isFind);
				nUtil.jString_Int16.Parse("Sys_Umpire_Animation::index",token[idx++], ref m_index);
				nUtil.jString_EEumpireAnimationType.Parse("Sys_Umpire_Animation::umpire_animation",token[idx++], ref m_umpire_animation);
				nUtil.jString_Int16.Parse("Sys_Umpire_Animation::animation_number",token[idx++], ref m_animation_number);
				nUtil.jString_string.Parse("Sys_Umpire_Animation::animation_filename",token[idx++], ref m_animation_filename);
			}
catch(System.Exception e)
			{
				if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)
				{
					String strError = String.Format("{0} = id={1} {2} [ {3} ]", e.ToString(), token[0], token[idx -1],idx -1);
					nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);
				}
				else
				{
					Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
					throw e;
				}
			}
		}
		public override string ToString()
		{
			string output = "";
			output += m_index.ToString() + ",";
			output += m_umpire_animation.ToString() + ",";
			output += m_animation_number.ToString() + ",";
			output += m_animation_filename.ToString() + ",";
			return output;
		}
	}//class Sys_Umpire_Animation

	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Batter_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Batter_Animation>		m_List = new List<Sys_Batter_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Batter_Animation >>>");
			foreach (Sys_Batter_Animation p in CSV_Sys_Batter_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Batter_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				string sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					string[] token = sLine.Split(',');
					Sys_Batter_Animation info = new Sys_Batter_Animation();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

		public static void LoadCSV_FromString(string sData)
		{
			string test = "\n\r";
			string[] all_line = sData.Split(test.ToCharArray());
			int i=0;
			foreach(String sLine in all_line)
			{
				if(i==0){ ++i;continue;}
				if (sLine.Length == 0) continue;
				string[] token = sLine.Split(',');
				Sys_Batter_Animation info = new Sys_Batter_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Batter_Animation


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Catcher_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Catcher_Animation>		m_List = new List<Sys_Catcher_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Catcher_Animation >>>");
			foreach (Sys_Catcher_Animation p in CSV_Sys_Catcher_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Catcher_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				string sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					string[] token = sLine.Split(',');
					Sys_Catcher_Animation info = new Sys_Catcher_Animation();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

		public static void LoadCSV_FromString(string sData)
		{
			string test = "\n\r";
			string[] all_line = sData.Split(test.ToCharArray());
			int i=0;
			foreach(String sLine in all_line)
			{
				if(i==0){ ++i;continue;}
				if (sLine.Length == 0) continue;
				string[] token = sLine.Split(',');
				Sys_Catcher_Animation info = new Sys_Catcher_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Catcher_Animation


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Pitcher_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Pitcher_Animation>		m_List = new List<Sys_Pitcher_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Pitcher_Animation >>>");
			foreach (Sys_Pitcher_Animation p in CSV_Sys_Pitcher_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Pitcher_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				string sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					string[] token = sLine.Split(',');
					Sys_Pitcher_Animation info = new Sys_Pitcher_Animation();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

		public static void LoadCSV_FromString(string sData)
		{
			string test = "\n\r";
			string[] all_line = sData.Split(test.ToCharArray());
			int i=0;
			foreach(String sLine in all_line)
			{
				if(i==0){ ++i;continue;}
				if (sLine.Length == 0) continue;
				string[] token = sLine.Split(',');
				Sys_Pitcher_Animation info = new Sys_Pitcher_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Pitcher_Animation


	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Umpire_Animation
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Umpire_Animation>		m_List = new List<Sys_Umpire_Animation> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Umpire_Animation >>>");
			foreach (Sys_Umpire_Animation p in CSV_Sys_Umpire_Animation.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Umpire_Animation       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
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
			FileInfo _finfo = new FileInfo(sCsvFileName);
			if (!_finfo.Exists)
			{
				Console.WriteLine("file not found :: {0}", sCsvFileName);
				return;
			}
			using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding("EUC-KR")))
			{
				string sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					string[] token = sLine.Split(',');
					Sys_Umpire_Animation info = new Sys_Umpire_Animation();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
		}//void LoadCSV()

		public static void LoadCSV_FromString(string sData)
		{
			string test = "\n\r";
			string[] all_line = sData.Split(test.ToCharArray());
			int i=0;
			foreach(String sLine in all_line)
			{
				if(i==0){ ++i;continue;}
				if (sLine.Length == 0) continue;
				string[] token = sLine.Split(',');
				Sys_Umpire_Animation info = new Sys_Umpire_Animation();
				int idx=0;
				info.ReadCSV(token , ref idx,false);
				m_List.Add(info);
			}
		}//void LoadCSV_FromString()

	}// public class CSV_Sys_Umpire_Animation



	


}//namespace nEXCEL
