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
	// 테스트용4
	// -------------------------------------------------

	public class Sys_T_Test4
			: Sys__T_Base
	{
		public Int16 m_maxbuild2; 	// [333최대 생성수] 한 마을에 최대 생성 가능한 건물 수 
		public Sys_T_Test4 m_sys_test3_ref; 	// [자신테이블참조] 다운될때 레벨. 레벨이 0이 되면 건물은 없어짐 
		public List<Sys_T_Test2> m_sys_test2_arrary = new List<Sys_T_Test2>{}; 	// [자신테이블참조배열] 건물을 다운시킬 때 자원의 50%가 반환됨. (창고의 남은양만큼 반환됨) 
		public EBuildTypeTest m_enum_val; 	// [enum_val]  
		public Int16 m_populationreturn4; 	// [populationreturn4] 건물을 다운시킬 때 인구가 반환됨. 인구 100% 반환되며 민가 최대 인구수 만큼만 반환됨. 
		public EBuildTypeTest m_test4; 	// [test4]  
		public Int16 m_getgold4; 	// [getgold4] 징수 명령 
		public List<Sys_T_Test2> m_test3_array_id = new List<Sys_T_Test2>{}; 	// [자신테이블참조고정배열3]  
		public List<Int32> m_field_array = new List<Int32>{}; 	// [int어레이3]  
		public List<Int32> m_field_vector = new List<Int32>{}; 	// [int어레이]  
		public jItemObj1 m_itemObj1; 	// [사용자자료형]  
		public Int32 m_val_int; 	// [int변수]  
		
		public new void Print(){Console.WriteLine(ToString());}
		public new void ReadCSV(string[] token,ref int idx,bool isPostParse)
		{try{
			int iStart=idx;
			bool isFind=false;
			nUtil.jCSV.not_thing(isFind);
			base.ReadCSV(token,ref idx,isPostParse);
			nUtil.jString_Int16.Parse("Sys_T_Test4::maxbuild2",token[idx++], ref m_maxbuild2);
			isFind = nUtil.jString_Sys_T_Test4.Parse("Sys_T_Test4::sys_test3_ref",token[idx++], ref m_sys_test3_ref);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_T_Test4.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_T_Test4 : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_T_Test4 : sys_test3_ref : " + token[idx-1]) ;
				}
			}
			isFind = nUtil.jString_Sys_T_Test2.Parse("Sys_T_Test4::sys_test2_arrary",token[idx++], ref m_sys_test2_arrary);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_T_Test4.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_T_Test4 : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_T_Test4 : sys_test2_arrary : " + token[idx-1]) ;
				}
			}
			nUtil.jString_EBuildTypeTest.Parse("Sys_T_Test4::enum_val",token[idx++], ref m_enum_val);
			nUtil.jString_Int16.Parse("Sys_T_Test4::populationreturn4",token[idx++], ref m_populationreturn4);
			nUtil.jString_EBuildTypeTest.Parse("Sys_T_Test4::test4",token[idx++], ref m_test4);
			nUtil.jString_Int16.Parse("Sys_T_Test4::getgold4",token[idx++], ref m_getgold4);
			isFind = nUtil.jString_Sys_T_Test2.Parse("Sys_T_Test4::test3_array_id",token[idx++], ref m_test3_array_id);
			if(!isFind)
			{
				if(!isPostParse)
				{
					if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))
					{
					
						nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();
						ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_Sys_T_Test4.PostParse);
						ppd.token = token;
						ppd.idx = iStart;
						ppd.o = this;
						ppd.sDebug = " -> Sys_T_Test4 : " ;
						nUtil.jCSV.m_PostParseList[this]=ppd;
					}
				}
				else
				{
					Console.WriteLine("[WARN]" + " -> Sys_T_Test4 : test3_array_id : " + token[idx-1]) ;
				}
			}
			nUtil.jString_Int32.Parse("Sys_T_Test4::field_array",token[idx++], ref m_field_array);
			nUtil.jString_Int32.Parse("Sys_T_Test4::field_vector",token[idx++], ref m_field_vector);
			nUtil.jString_jItemObj1.Parse("Sys_T_Test4::itemObj1",token[idx++], ref m_itemObj1);
			nUtil.jString_Int32.Parse("Sys_T_Test4::val_int",token[idx++], ref m_val_int);
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
			output += (nUtil.jString_Sys_T_Test4.ToString(m_sys_test3_ref)+ ",");
			output += (nUtil.jString_Sys_T_Test2.ToString(m_sys_test2_arrary)+ ",");
			output += m_enum_val.ToString() + ",";
			output += m_populationreturn4.ToString() + ",";
			output += m_test4.ToString() + ",";
			output += m_getgold4.ToString() + ",";
			output += (nUtil.jString_Sys_T_Test2.ToString(m_test3_array_id)+ ",");
			output += (nUtil.jString_Int32.ToString(m_field_array)+ ",");
			output += (nUtil.jString_Int32.ToString(m_field_vector)+ ",");
			output += m_itemObj1.ToString() + ",";
			output += m_val_int.ToString() + ",";
			return output;
		}
	}//class Sys_T_Test4

	namespace nUtil
	{
		class jString_Sys_T_Test4
		{
			public static string ToString(Sys_T_Test4 o)
			{
				if (o ==null)
				{
					return "NULL";
				}
				return o.m_name;
			}
			public static string ToString(List<Sys_T_Test4> sysList)
			{
				string output = "";
				foreach (Sys_T_Test4 o in sysList)
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
				Sys_T_Test4 o = (Sys_T_Test4)ppd.o;
				o.ReadCSV(ppd.token,ref ppd.idx,true);
			}
			public static bool Parse(string sDebug,string sVal, ref Sys_T_Test4 o)
			{
				if (Char.IsNumber(sVal[0]))
				{
					o = CSV_Sys_T_Test4.Find(int.Parse(sVal));
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				else
				{
					o = CSV_Sys_T_Test4.FindBy_name(sVal);
					//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse Error ",sDebug);
				}
				return o!=null;
			}
			public static bool Parse(string sDebug,string sVal, ref List<Sys_T_Test4> oList)
			{
				oList.Clear();
				bool isFind=false;
				List<Sys_T_Test4> sysList = (List<Sys_T_Test4>)oList;
				foreach ( string s in sVal.Split(';') )
				{
					Sys_T_Test4 o=null;
					if (Char.IsNumber(s[0]))
					{
						o = CSV_Sys_T_Test4.Find(int.Parse(s));
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add(o);
					}
					else
					{
						o = CSV_Sys_T_Test4.FindBy_name(s);
						//nEXCEL.nUtil.jCSV.jCHECK_null(o, "PostParse_List Error " + sDebug,s);
						sysList.Add( o );
					}
					if(o!=null) isFind=true;
				}
				return isFind;
			}
		}//class jString_Sys_T_Test4
	}//namespace nUtil
	

	// -------------------------------------------------
	// 테스트용4
	// -------------------------------------------------

	public class CSV_Sys_T_Test4
	{
		public  class CSV_Sys_Test_Exception : System.Exception
		{
			public CSV_Sys_Test_Exception(string s) : base(s)
			{
				Console.WriteLine("[CSV_Sys_Test_Exception] Logging '{0}'", this.Message);
			}
		}
		private		static List<Sys_T_Test4>		m_List = new List<Sys_T_Test4> { };
		public      static void             Print()
		{
			Console.WriteLine("\n\n<<< Sys_T_Test4 >>>");
			foreach (Sys_T_Test4 p in CSV_Sys_T_Test4.m_List){p.Print();}
		
		}
		public      static int              Count() { return m_List.Count(); }
		public      static Sys_T_Test4       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!
		{
			if (idx <= 0 || idx >= m_List.Count())
			{
				 return null;
				//throw new CSV_Sys_Test_Exception("범위를 벋어난값 : " + idx.ToString());
			}
			return m_List[idx-1];
		}
		private static Hashtable m_Hashtable_name = new Hashtable();
		public static Sys_T_Test4 FindBy_name(string key){return (Sys_T_Test4)m_Hashtable_name[key];}

		private static Dictionary<EBuildType_test,List<Sys_T_Test4>> m_Dictionary_base_type = new Dictionary<EBuildType_test,List<Sys_T_Test4>>{};
		public static List<Sys_T_Test4> FindBy_base_type(EBuildType_test key){return m_Dictionary_base_type[key];}

		private static void _makeIndex()
		{
			foreach(Sys_T_Test4 p in m_List){m_Hashtable_name[p.m_name] = p;}
			foreach(Sys_T_Test4 p in m_List)
			{
				if (!m_Dictionary_base_type.ContainsKey(p.m_base_type))
				{
					m_Dictionary_base_type[p.m_base_type] = new List<Sys_T_Test4> { };
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
				Sys_T_Test4 info;
				sLine = sr.ReadLine();
				while ((sLine = sr.ReadLine()) != null)
				{
					token = sLine.Split(',');
					info = new Sys_T_Test4();
					int idx=0;
					info.ReadCSV(token , ref idx,false);
					m_List.Add(info);
				}
			}
			_makeIndex();
		}//void LoadCSV()

	}// public class CSV_Sys_T_Test4



	


}//namespace nEXCEL
