/*------------------------------------------------------------


command line : 
Excel_Converter.exe D:\svn\baseball\doc\design\excel\code\excel_test2.txt D:\svn\baseball\doc\design\excel\code\excel_enum.txt D:\svn\baseball\doc\design\excel\code\excel_test.txt 

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
	using Sys_ItemBase_id_t = UInt16;
	using player_level_t = Int32;
	using Sys_Quest_id_t = UInt16;
	using game_money_t = Int32;
	using pp_point_t = Int32;
	using Sys_ItemEquip_id_t = UInt16;
	using Sys__ItemBase_id_t = UInt16;
	using Sys_RandomGift_id_t = UInt16;
	using g234ame_money_t = Int32;
	

	// -------------------------------------------------
	// ����type ���̺��� base ���̺��̴�. ��� ����type ���̺��� �� ���̺��� ��ӹ޴´�
	// -------------------------------------------------

	public class Sys__T_Base
	{
		public Sys__T_Base_id_t m_level; 	// [����] �ǹ� ���� ( �ش� ������ �ǹ� sid �ĺ��ڷε� ���δ�) 
		public EBuildType_test m_base_type; 	// [�ǹ�Ÿ��] Sys_T_BaseObj����� �޴� ���̺��� �ǹ� ���� 
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
			nUtil.jString_UInt16.Parse("Sys__T_Base::level",token[idx++], ref m_level);
			nUtil.jString_EBuildType_test.Parse("Sys__T_Base::base_type",token[idx++], ref m_base_type);
			nUtil.jString_string.Parse("Sys__T_Base::name",token[idx++], ref m_name);
			nUtil.jString_UInt32.Parse("Sys__T_Base::upgradetime",token[idx++], ref m_upgradetime);
			nUtil.jString_Int16.Parse("Sys__T_Base::tree_num",token[idx++], ref m_tree_num);
			nUtil.jString_Int16.Parse("Sys__T_Base::stone_num",token[idx++], ref m_stone_num);
			nUtil.jString_Int16.Parse("Sys__T_Base::iron_num",token[idx++], ref m_iron_num);
			nUtil.jString_Int16.Parse("Sys__T_Base::silk_num",token[idx++], ref m_silk_num);
			nUtil.jString_Int16.Parse("Sys__T_Base::population_num",token[idx++], ref m_population_num);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output += m_level.ToString() + ",";
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
	}//class Sys__T_Base

	

	// -------------------------------------------------
	// �׽�Ʈ��
	// -------------------------------------------------

	public class Sys_T_Test
			: Sys__T_Base
	{
		public Int16 m_maxbuild; 	// [111�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel; 	// [111�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_populationreturn; 	// [111�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public EBuildType_test m_test; 	// [111test]  
		public Int16 m_getgold; 	// [111¡��] ¡�� ��� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_Int16.Parse("Sys_T_Test::maxbuild",token[idx++], ref m_maxbuild);
			nUtil.jString_Int16.Parse("Sys_T_Test::downlevel",token[idx++], ref m_downlevel);
			nUtil.jString_Int16.Parse("Sys_T_Test::populationreturn",token[idx++], ref m_populationreturn);
			nUtil.jString_EBuildType_test.Parse("Sys_T_Test::test",token[idx++], ref m_test);
			nUtil.jString_Int16.Parse("Sys_T_Test::getgold",token[idx++], ref m_getgold);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_maxbuild.ToString() + ",";
			output += m_downlevel.ToString() + ",";
			output += m_populationreturn.ToString() + ",";
			output += m_test.ToString() + ",";
			output += m_getgold.ToString() + ",";
			return output;
		}
	}//class Sys_T_Test

	namespace nUtil
	{
		class jString_Sys_T_Test
		{
			public static string ToString(Sys_T_Test o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_T_Test> sysList)
			{
				string output = "";
				foreach (Sys_T_Test o in sysList)
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
				Sys_T_Test o = (Sys_T_Test)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_T_Test o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_T_Test.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_T_Test.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_T_Test> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_T_Test> sysList = (List<Sys_T_Test>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_T_Test o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_T_Test.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_T_Test.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_T_Test
	}//namespace nUtil
	

	// -------------------------------------------------
	// �׽�Ʈ��2
	// -------------------------------------------------

	public class Sys_T_Test2
			: Sys_T_Test
	{
		public Int16 m_maxbuild2; 	// [222�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public Int16 m_downlevel2; 	// [2�ٿ�׷��̵巹��] �ٿ�ɶ� ����. ������ 0�� �Ǹ� �ǹ��� ������ 
		public Int16 m_treereturn2; 	// [222���� ��ȯ���] �ǹ��� �ٿ��ų �� �ڿ��� 50%�� ��ȯ��. (â���� �����縸ŭ ��ȯ��) 
		public EOutput_test m_stonereturn2; 	// [222�� ��ȯ���]  
		public Int16 m_populationreturn2; 	// [222�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public EBuildType_test m_test2; 	// [222test]  
		public Int16 m_getgold2; 	// [222¡��] ¡�� ��� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_Int16.Parse("Sys_T_Test2::maxbuild2",token[idx++], ref m_maxbuild2);
			nUtil.jString_Int16.Parse("Sys_T_Test2::downlevel2",token[idx++], ref m_downlevel2);
			nUtil.jString_Int16.Parse("Sys_T_Test2::treereturn2",token[idx++], ref m_treereturn2);
			nUtil.jString_EOutput_test.Parse("Sys_T_Test2::stonereturn2",token[idx++], ref m_stonereturn2);
			nUtil.jString_Int16.Parse("Sys_T_Test2::populationreturn2",token[idx++], ref m_populationreturn2);
			nUtil.jString_EBuildType_test.Parse("Sys_T_Test2::test2",token[idx++], ref m_test2);
			nUtil.jString_Int16.Parse("Sys_T_Test2::getgold2",token[idx++], ref m_getgold2);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_maxbuild2.ToString() + ",";
			output += m_downlevel2.ToString() + ",";
			output += m_treereturn2.ToString() + ",";
			output += m_stonereturn2.ToString() + ",";
			output += m_populationreturn2.ToString() + ",";
			output += m_test2.ToString() + ",";
			output += m_getgold2.ToString() + ",";
			return output;
		}
	}//class Sys_T_Test2

	namespace nUtil
	{
		class jString_Sys_T_Test2
		{
			public static string ToString(Sys_T_Test2 o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_T_Test2> sysList)
			{
				string output = "";
				foreach (Sys_T_Test2 o in sysList)
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
				Sys_T_Test2 o = (Sys_T_Test2)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_T_Test2 o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_T_Test2.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_T_Test2.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_T_Test2> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_T_Test2> sysList = (List<Sys_T_Test2>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_T_Test2 o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_T_Test2.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_T_Test2.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_T_Test2
	}//namespace nUtil
	

	// -------------------------------------------------
	// �׽�Ʈ��2
	// -------------------------------------------------

	public class Sys_T_Test3
			: Sys__T_Base
	{
		public Int16 m_maxbuild2; 	// [333�ִ� ������] �� ������ �ִ� ���� ������ �ǹ� �� 
		public EOutput_test m_stonereturn2; 	// [333�� ��ȯ���]  
		public Int16 m_populationreturn2; 	// [333�α� ��ȯ���] �ǹ��� �ٿ��ų �� �α��� ��ȯ��. �α� 100% ��ȯ�Ǹ� �ΰ� �ִ� �α��� ��ŭ�� ��ȯ��. 
		public EBuildType_test m_test2; 	// [333test]  
		public Int16 m_getgold2; 	// [333¡��] ¡�� ��� 
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_Int16.Parse("Sys_T_Test3::maxbuild2",token[idx++], ref m_maxbuild2);
			nUtil.jString_EOutput_test.Parse("Sys_T_Test3::stonereturn2",token[idx++], ref m_stonereturn2);
			nUtil.jString_Int16.Parse("Sys_T_Test3::populationreturn2",token[idx++], ref m_populationreturn2);
			nUtil.jString_EBuildType_test.Parse("Sys_T_Test3::test2",token[idx++], ref m_test2);
			nUtil.jString_Int16.Parse("Sys_T_Test3::getgold2",token[idx++], ref m_getgold2);
		}catch(System.Exception e)
		{
			Console.WriteLine("{0} = id={1} {2} [ {3} ]",e.ToString() , token[0] , token[idx-1], idx-1 );
			throw e;
		}
		}
		public override string ToString()
		{
			string output = "";
			output = base.ToString();
			output += "	";
			output += m_maxbuild2.ToString() + ",";
			output += m_stonereturn2.ToString() + ",";
			output += m_populationreturn2.ToString() + ",";
			output += m_test2.ToString() + ",";
			output += m_getgold2.ToString() + ",";
			return output;
		}
	}//class Sys_T_Test3

	namespace nUtil
	{
		class jString_Sys_T_Test3
		{
			public static string ToString(Sys_T_Test3 o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_T_Test3> sysList)
			{
				string output = "";
				foreach (Sys_T_Test3 o in sysList)
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
				Sys_T_Test3 o = (Sys_T_Test3)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_T_Test3 o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_T_Test3.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_T_Test3.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_T_Test3> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_T_Test3> sysList = (List<Sys_T_Test3>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_T_Test3 o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_T_Test3.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_T_Test3.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_T_Test3
	}//namespace nUtil
	

	// -------------------------------------------------
	// �׽�Ʈ��
	// -------------------------------------------------

	public class CSV_Sys_T_Test
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		private		static List<Sys_T_Test>		m_List = new List<Sys_T_Test> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Test >>>");
			foreach (Sys_T_Test p in CSV_Sys_T_Test.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_T_Test       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_T_Test FindBy_name(string key){return (Sys_T_Test)m_Hashtable_name[key];}

		private static Dictionary<EBuildType_test,List<Sys_T_Test>> m_Dictionary_base_type = new Dictionary<EBuildType_test,List<Sys_T_Test>>{};
		public static List<Sys_T_Test> FindBy_base_type(EBuildType_test key){return m_Dictionary_base_type[key];}

		private static void _makeIndex()
		{
			foreach(Sys_T_Test p in m_List){m_Hashtable_name[p.m_name] = p;}
			foreach(Sys_T_Test p in m_List)
			{
				if (!m_Dictionary_base_type.ContainsKey(p.m_base_type))
				{
					m_Dictionary_base_type[p.m_base_type] = new List<Sys_T_Test> { };
				}
				m_Dictionary_base_type[p.m_base_type].Add(p);
			}
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
				Sys_T_Test info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Test();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_T_Test


	// -------------------------------------------------
	// �׽�Ʈ��2
	// -------------------------------------------------

	public class CSV_Sys_T_Test2
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		private		static List<Sys_T_Test2>		m_List = new List<Sys_T_Test2> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Test2 >>>");
			foreach (Sys_T_Test2 p in CSV_Sys_T_Test2.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_T_Test2       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_T_Test2 FindBy_name(string key){return (Sys_T_Test2)m_Hashtable_name[key];}

		private static Dictionary<EBuildType_test,List<Sys_T_Test2>> m_Dictionary_base_type = new Dictionary<EBuildType_test,List<Sys_T_Test2>>{};
		public static List<Sys_T_Test2> FindBy_base_type(EBuildType_test key){return m_Dictionary_base_type[key];}

		private static void _makeIndex()
		{
			foreach(Sys_T_Test2 p in m_List){m_Hashtable_name[p.m_name] = p;}
			foreach(Sys_T_Test2 p in m_List)
			{
				if (!m_Dictionary_base_type.ContainsKey(p.m_base_type))
				{
					m_Dictionary_base_type[p.m_base_type] = new List<Sys_T_Test2> { };
				}
				m_Dictionary_base_type[p.m_base_type].Add(p);
			}
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
				Sys_T_Test2 info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Test2();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_T_Test2


	// -------------------------------------------------
	// �׽�Ʈ��2
	// -------------------------------------------------

	public class CSV_Sys_T_Test3
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		private		static List<Sys_T_Test3>		m_List = new List<Sys_T_Test3> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Test3 >>>");
			foreach (Sys_T_Test3 p in CSV_Sys_T_Test3.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_T_Test3       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("������ ����� : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_T_Test3 FindBy_name(string key){return (Sys_T_Test3)m_Hashtable_name[key];}

		private static Dictionary<EBuildType_test,List<Sys_T_Test3>> m_Dictionary_base_type = new Dictionary<EBuildType_test,List<Sys_T_Test3>>{};
		public static List<Sys_T_Test3> FindBy_base_type(EBuildType_test key){return m_Dictionary_base_type[key];}

		private static void _makeIndex()
		{
			foreach(Sys_T_Test3 p in m_List){m_Hashtable_name[p.m_name] = p;}
			foreach(Sys_T_Test3 p in m_List)
			{
				if (!m_Dictionary_base_type.ContainsKey(p.m_base_type))
				{
					m_Dictionary_base_type[p.m_base_type] = new List<Sys_T_Test3> { };
				}
				m_Dictionary_base_type[p.m_base_type].Add(p);
			}
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
				Sys_T_Test3 info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Test3();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_T_Test3



	


}//namespace nEXCEL
