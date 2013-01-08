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

	public enum E_ClassItemA
	{
		eBEGIN_E_ClassItemA=0,
		CIA_NOT = 1, // [���� ����] ���� ���� �ڵ� �з�
		CIA_PIKE = 2, // [â ����] 
		CIA_HEAVY = 3, // [�߰� ����] 
		CIA_HALBERD = 4, // [����� ����] ������ (ö �Ҹ� ����)
		CIA_BOW = 5, // [�� ����] 
		CIA_CROSSBOW = 6, // [�� ����] 
		CIA_BOWGUN = 7, // [���� ����] 
		CIA_BALLISTA = 8, // [���� ����] 
		CIA_CHARIOT = 9, // [���� ����] ������ �����ؼ��� ���� (���� �þ��)
		CIA_WAGON = 10, // [����] ������ �����ؼ��� ���� (���� �þ��)
		eEND_E_ClassItemA,
	}
	namespace nUtil
	{
		class jString_E_ClassItemA
		{
			public static void Parse(string sDebug,string sVal, ref E_ClassItemA eVal) 
			{
				eVal = (E_ClassItemA)Enum.Parse(typeof(E_ClassItemA), sVal);
			}
		}
	}


	public enum E_ClassItemB
	{
		eBEGIN_E_ClassItemB=0,
		CIB_NOT = 1, // [Ż�� ����] 
		CIB_HORSE = 2, // [����] Eunit_ClassItemA �� ���� ����
		CIB_WHEELBARROW = 3, // [����] ����, ����, ���� �뵵
		CIB_CART = 4, // [���] 
		CIB_SIEGE_LADDER = 5, // [����] B�� Ȱ�� ����
		CIB_SIEGE_RAM = 6, // [����] 
		CIB_SIEGE_TOWER = 7, // [����] 
		CIB_SIEGE_TREBUCHET = 8, // [������] 
		eEND_E_ClassItemB,
	}
	namespace nUtil
	{
		class jString_E_ClassItemB
		{
			public static void Parse(string sDebug,string sVal, ref E_ClassItemB eVal) 
			{
				eVal = (E_ClassItemB)Enum.Parse(typeof(E_ClassItemB), sVal);
			}
		}
	}


	public enum E_W_Event
	{
		eBEGIN_E_W_Event=0,
		ENV_SUNNY = 1, // [����] �Ӽ� ���� ���
		ENV_RAIN = 2, // [�� �Ӽ�] ȭ�� ����, ���� ����
		ENV_MIST = 3, // [�Ȱ� �Ӽ�] �þ� ����  / ��Ÿ� ��ȭ
		ENV_TIME = 4, // [�㳷 �Ӽ�] �þ� ����  / ��Ÿ� ��ȭ
		ENV_CALAMITY = 5, // [õ�� ����] ����/����/����/����/ȫ��/��ǳ/����/�޶ѱⶼ/����
		ENV_LUCK = 6, // [�ູ] ǳ��/�ٻ�
		eEND_E_W_Event,
	}
	namespace nUtil
	{
		class jString_E_W_Event
		{
			public static void Parse(string sDebug,string sVal, ref E_W_Event eVal) 
			{
				eVal = (E_W_Event)Enum.Parse(typeof(E_W_Event), sVal);
			}
		}
	}


	public enum EForceClass
	{
		eBEGIN_EForceClass=0,
		FC_COMMON = 1, // [����] 
		FC_INFANTRY = 2, // [����] 
		FC_ARCHER = 3, // [�ú�] 
		FC_CABALRY = 4, // [�⺴] 
		FC_SIEGE = 5, // [��������] 
		eEND_EForceClass,
	}
	namespace nUtil
	{
		class jString_EForceClass
		{
			public static void Parse(string sDebug,string sVal, ref EForceClass eVal) 
			{
				eVal = (EForceClass)Enum.Parse(typeof(EForceClass), sVal);
			}
		}
	}


	public enum EForcePosType
	{
		eBEGIN_EForcePosType=0,
		FPT_TOWN = 1, // [����] ����
		FPT_CASTLE = 2, // [��] ��
		FPT_CASTLEMAP = 3, // [��������] ��������
		FPT_WORLDMAP = 4, // [�����] �����
		eEND_EForcePosType,
	}
	namespace nUtil
	{
		class jString_EForcePosType
		{
			public static void Parse(string sDebug,string sVal, ref EForcePosType eVal) 
			{
				eVal = (EForcePosType)Enum.Parse(typeof(EForcePosType), sVal);
			}
		}
	}

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class Sys_Force
	{
		public Sys_Force_id_t m_fsid; 	// [����_ID] ���� ID 
		public string m_name; 	// [�̸�_ID] �̸� ID 
		public string m_name_kor; 	// [�����̸�] ���� �̸� 
		public EForceClass m_force_class; 	// [�����з�] ���� �з� 
		public E_ClassItemA m_forceClassItemA; 	// [��������_������ A] ���� ���� A 
		public E_ClassItemB m_forceClassItemB; 	// [��������_������ B] ���� ���� B 
		public Int16 m_att; 	// [���ݷ�] ���ݷ� ���� 
		public Int16 m_def; 	// [����] ���� ���� 
		public Int16 m_mspeed; 	// [�̵�_�ӵ�] �̵� �ӵ� ���� 
		public Int16 m_aspeed; 	// [����_�ӵ�] ���� �ӵ� ���� / msec ���� 
		public Int16 m_srange; 	// [���ðŸ�] ���ðŸ� 
		public Int16 m_suvival_ratio; 	// [������] ��Ƴ� Ȯ�� / % ������ (xx.x%) 
		public Int16 m_kill_ratio; 	// [�����] �����ų Ȯ�� / % ������ (xx.x%) 
		public Int16 m_client_id; 	// [Ŭ���̾�ƮID] Ŭ���̾�Ʈ���� ������ ���� �̹��� id ��ȣ 
		public Int16 m_unit_load; 	// [���緮] ��ǰ ���緮 
		
		public  void Print(){Console.WriteLine(ToString());}
		public  void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			nUtil.jString_UInt16.Parse("Sys_Force::fsid",token[idx++], ref m_fsid);
			nUtil.jString_string.Parse("Sys_Force::name",token[idx++], ref m_name);
			nUtil.jString_string.Parse("Sys_Force::name_kor",token[idx++], ref m_name_kor);
			nUtil.jString_EForceClass.Parse("Sys_Force::force_class",token[idx++], ref m_force_class);
			nUtil.jString_E_ClassItemA.Parse("Sys_Force::forceClassItemA",token[idx++], ref m_forceClassItemA);
			nUtil.jString_E_ClassItemB.Parse("Sys_Force::forceClassItemB",token[idx++], ref m_forceClassItemB);
			nUtil.jString_Int16.Parse("Sys_Force::att",token[idx++], ref m_att);
			nUtil.jString_Int16.Parse("Sys_Force::def",token[idx++], ref m_def);
			nUtil.jString_Int16.Parse("Sys_Force::mspeed",token[idx++], ref m_mspeed);
			nUtil.jString_Int16.Parse("Sys_Force::aspeed",token[idx++], ref m_aspeed);
			nUtil.jString_Int16.Parse("Sys_Force::srange",token[idx++], ref m_srange);
			nUtil.jString_Int16.Parse("Sys_Force::suvival_ratio",token[idx++], ref m_suvival_ratio);
			nUtil.jString_Int16.Parse("Sys_Force::kill_ratio",token[idx++], ref m_kill_ratio);
			nUtil.jString_Int16.Parse("Sys_Force::client_id",token[idx++], ref m_client_id);
			nUtil.jString_Int16.Parse("Sys_Force::unit_load",token[idx++], ref m_unit_load);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_fsid.ToString() + ",";
			output += m_name.ToString() + ",";
			output += m_name_kor.ToString() + ",";
			output += m_force_class.ToString() + ",";
			output += m_forceClassItemA.ToString() + ",";
			output += m_forceClassItemB.ToString() + ",";
			output += m_att.ToString() + ",";
			output += m_def.ToString() + ",";
			output += m_mspeed.ToString() + ",";
			output += m_aspeed.ToString() + ",";
			output += m_srange.ToString() + ",";
			output += m_suvival_ratio.ToString() + ",";
			output += m_kill_ratio.ToString() + ",";
			output += m_client_id.ToString() + ",";
			output += m_unit_load.ToString() + ",";
			return output;
		}
	}//class Sys_Force

	namespace nUtil
	{
		class jString_Sys_Force
		{
			public static string ToString(Sys_Force o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_Force> sysList)
			{
				string output = "";
				foreach (Sys_Force o in sysList)
				{
					if( o==null )
						output += "NULL;";
					else
						output += (o.m_name + ";");
				}
				return output;
			}
			public static void PostParse(nEXCEL.nUtil.jCSV.PostParseData ppd)
			{
				Sys_Force o = (Sys_Force)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_Force o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_Force.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_Force.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_Force> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_Force> sysList = (List<Sys_Force>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_Force o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_Force.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_Force.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_Force
	}//namespace nUtil
	

	// -------------------------------------------------
	// �������
	// -------------------------------------------------

	public class CSV_Sys_Force
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		public		static List<Sys_Force>		m_List = new List<Sys_Force> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_Force >>>");
			foreach (Sys_Force p in CSV_Sys_Force.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count; }
		public      static Sys_Force       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count)
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_Force FindBy_name(string key){return (Sys_Force)m_Hashtable_name[key];}

		private static void _makeIndex()
		{
			foreach(Sys_Force p in m_List){m_Hashtable_name[p.m_name] = p;}
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
				Sys_Force info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_Force();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_Force



	


}//namespace nEXCEL
