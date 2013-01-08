#include "stdafx.h"
#include "Excel_Converter.h"



namespace excel_util
{

	// Sys, Tbl등에서 db_type에 "INDEX"가 있으면 그 필드명들을 추출한다.
	void get_INDEX_field(IN jIE* peTable, OUT vector<jIE*>& out)
	{
		jIE* it = peTable->begin();
		jrFOR(it)
		{
			if(jt_strstr(jC5(it,db_type) , jS(INDEX) ) )
				out.push_back(it);
		}

		vector<jE> listInherit;
		get_Inherit_Info(listInherit, peTable);
		for(size_t i= 0; i<listInherit.size() ; ++i)
		{
			jE e = listInherit[i];
			get_INDEX_field(e, out);
		}
	}


	void get_NAME_field(IN jIE* peTable, OUT vector<jIE*>& out)
	{
		jIE* it = peTable->begin();
		jrFOR(it)
		{
			bool isName = it->IsName(jS(name));
			if(isName)
				out.push_back(it);
		}

		vector<jE> listInherit;
		get_Inherit_Info(listInherit, peTable);
		for(size_t i= 0; i<listInherit.size() ; ++i)
		{
			jE e = listInherit[i];
			get_NAME_field(e, out);
		}
	}
	cstr get_cshap_type(cstr szType)
	{
		static jIE* peDEFAULT_CSHAP_TYPE_LIST = nGLOBAL::g_pDocApp->Find(jS(DEFAULT_CSHAP_TYPE_LIST));
		jASSERT0(peDEFAULT_CSHAP_TYPE_LIST);
		jIE * pE = peDEFAULT_CSHAP_TYPE_LIST->Find(szType);
		static std::map<tstring ,tstring> s_get_cshap_type_Cache;
		if(!pE) 
		{
			fname_t szN ;
			jt_strcpy(szN,szType);
			size_t iLen = jt_strlen(szN);
			if(	szType[iLen-4]=='_' 
				&& szType[iLen-3]=='p' 
				&& szType[iLen-2]=='t' 
				&& szType[iLen-1]=='r' 
				)
			{
				szN[iLen-4]=0;
				tstring sNewType = get_cshap_type(szN);
				pE = peDEFAULT_CSHAP_TYPE_LIST->Persist(szType,sNewType.c_str());
				return pE->Get_cstr();
			}
			TCHAR* sz = jt_strstr(szN,jS(_ptr_vec));
			if(sz)
			{
				*sz=0;
				fname_t buf;
				tstring sNewType = get_cshap_type(szN);
				jt_sprintf(buf,_T("List<%s>"),sNewType.c_str());
				s_get_cshap_type_Cache[szType] = buf;
				return s_get_cshap_type_Cache[szType].c_str();
			}

			if(	szType[iLen-4]=='_' 
				&& szType[iLen-3]=='v' 
				&& szType[iLen-2]=='e' 
				&& szType[iLen-1]=='c' 
				)
			{
				szN[iLen-4]=0;
				fname_t buf;
				tstring sNewType = get_cshap_type(szN);
				jt_sprintf(buf,_T("List<%s>"),sNewType.c_str());
				s_get_cshap_type_Cache[szType] = buf;
				return s_get_cshap_type_Cache[szType].c_str();
			}
			return szType;
		}
		return pE->Get_cstr();
	}


}//namespace excel_util
using namespace excel_util;

jLIST_TYPEDEF_map(tstring,tstring,g_mapSys_id_t);
void Excel_Converter::make_file_cshap_using(tofstream &of,jE e)
{
	jIE* it = e->begin();
	jrFOR(it)
	{
		cstr szTag = it->GetTagName();
		size_t iLen= jt_strlen(szTag);
		if(szTag[iLen-2] != '_' || szTag[iLen-1] != 't') continue;

		cstr szCType = it->GetAttr(jS(Setter));

		cstr szType = get_cshap_type(szCType);
		of << _jFF("using %1% = %2%;") % szTag % szType;
		g_mapSys_id_t[szTag]=szType;
	}
}


//enum출력.
void Excel_Converter::make_file_cshap_enum(tofstream &of)
{
	jE eEnum = m_eDoc(jS(enum));
	if(eEnum.empty()) return;
	jIE* it = eEnum->begin();

	Print_Title(of, _T("enum형 코드 템플릿 정의"));
	jrFOR(it)
	{
		cstr szT = it->GetTagName();
		of << _jFF("public enum %1% : byte") % it->GetTagName();
		of << _jTT("{");
		{
			AutoTab a(this);
			of << _jFF("eBEGIN_%1%=0,") % it->GetTagName();
			jIE* itE = it->begin();
			int iMaxEnumVal=0;
			jrFOR(itE)
			{
				of << _jFF("%1% = %2%, // [%3%] %4%") % itE->GetTagName() % itE->Find(jS(value))->Get_cstr() 
					% itE->Find(jS(name))->Get_cstr() %itE->Find(jS(help))->Get_cstr();

				int iEnumVal = jt_atoi(itE->Find(jS(value))->Get_cstr());
				if(iMaxEnumVal<iEnumVal)
					iMaxEnumVal = iEnumVal;

			}
			of << _jFF("eEND_%1%,") % it->GetTagName();
			jvCHECK(iMaxEnumVal<255, _T(" enum %s 's value is so big then 254"),it->GetTagName());
		}
		of << _jTT("}");

		of << _jFF("namespace nUtil");
		of << _jFF("{");
		of << _jFF("	public class jString_%1%") % szT;
		of << _jFF("	{");
		of << _jFF("		public static void Parse(string sDebug,string sVal, ref %1% eVal) ") % szT;
		of << _jFF("		{");
		of << _jFF("			eVal = (%1%)Enum.Parse(typeof(%1%), sVal);") % szT;
		of << _jFF("		}");
		of << _jFF("		public static List<string> get_strings() ");
		of << _jFF("		{");
		of << _jFF("			List<string> list = new List<string>();");
		of << _jFF("			for (%1% i = %1%.eBEGIN_%1% +1;i < %1%.eEND_%1%; i++){list.Add(i.ToString());}") % szT;
		of << _jFF("			return list;");
		of << _jFF("		}");
		of << _jFF("		public static List<%1%> get_enums() ") % szT;
		of << _jFF("		{");
		of << _jFF("			List<%1%> list = new List<%1%>();") % szT;
		of << _jFF("			for (%1% i = %1%.eBEGIN_%1% +1;i < %1%.eEND_%1%; i++){list.Add(i);}") % szT;
		of << _jFF("			return list;");
		of << _jFF("		}");
		of << _jFF("	}");
		of << _jFF("}\n\n");

	}
}

tstring get_nUtil_jString_type(jIE* it)
{
	cstr szType = get_cshap_type(jC5(it,data_type)) ;
	tstring sNewType = szType;
	if(g_mapSys_id_t.count(szType))
	{
		sNewType = g_mapSys_id_t[szType].c_str();
	}
	else
	{
		if( jt_strstr(szType,_T("List<")) )
		{
			fname_t buf;
			jt_strcpy(buf,szType+5);
			buf[jt_strlen(buf)-1]=0;
			sNewType = buf;
		}
	}
	return sNewType;
}

//구조체 출력.
void Excel_Converter::make_file_cshap_struct(tofstream &of,cstr szStruct)
{
	jE eSys = m_eDoc(szStruct);
	if(eSys.empty()) return;
	jIE* peTable  = eSys->begin();
	jrFOR(peTable)
	{
		cstr szT = peTable->GetTagName();
		Print_Title(of, peTable->GetAttr(jS(HELP)) );

		of << _jFF("public class %1%") % szT ;

		vector<jIE*> inheritList;
		get_inherit_list(inheritList, peTable);
		bool isInH = inheritList.size();
		cstr szNew=_T("");

		if(isInH)
		{
			of << _jFF("");
			szNew=_T("new");
			of << _jT("\t:");
			for(size_t i=0; i<inheritList.size(); ++i)
			{
				of << boost::tformat(_T(" %1%")) % inheritList[i]->GetTagName();
				if(i<inheritList.size()-1)
				{
					of << _jT(",");
				}
			}
		}
		of << _jTT("{");
		{
			AutoTab a(this);
			jIE* it = peTable->begin();
			jrFOR(it)
			{
				if(is_inherit_node(it))
					continue;


				cstr name = jC5(it,name);
				cstr help = jC5(it,help);
				cstr szType = get_cshap_type(jC5(it,data_type)) ;
				if(jt_strstr(szType,_T("List<")))
				{
					//of << _jFF("%1% m_%2%= new %1%{}; \t// [%3%] %4% ") 
					of << _jFF("public %1% m_%2% = new %1%{}; \t// [%3%] %4% ") 
						% szType % it->GetTagName() % name % help;
				}
				else
				{
					of << _jFF("public %1% m_%2%; \t// [%3%] %4% ") % szType
						% it->GetTagName() % name % help;
				}
			}
			of << _jTT("");
			of << _jFF("public %1% void Print(){Console.WriteLine(ToString());}") % szNew;

			bool isSys= !jt_strncmp(szStruct,_T("Sys"),3);
			if(isSys)
			{
				of << _jFF("public %1% void ReadCSV(string[] token,ref int idx,bool isPostParse)") % szNew;
				of << _jFF("{");
				{
					AutoTab a(this);
					of << _jFF("try{");
					{
						AutoTab b(this);
						it = peTable->begin();
						of << _jFF("int iStart=idx;");
						of << _jFF("bool isFind=false;");
						of << _jFF("nUtil.jCSV.not_thing(isFind);");
						if(isInH)
						{
							of << _jFF("base.ReadCSV(token,ref idx,isPostParse);");
						}

						jrFOR(it)
						{
							if(is_inherit_node(it))
								continue;

							tstring sNewType = get_nUtil_jString_type(it);
							cstr szType =jC5(it,data_type);
							bool isSys = jt_strstr(szType,_T("Sys_")) &&  jt_strcmp(szType+jt_strlen(szType)-5 , _T("_id_t"));
							if(isSys)
							{// 다른 Sys테이블에 대한 래퍼런스객체이면 null채크하여 못찾았을때 PostParse에 등록.
								of << _jFF("try{");
								of << _jFF("	isFind = nUtil.jString_%2%.Parse(\"%3%::%1%\",token[idx++], ref m_%1%);") % it->GetTagName() % sNewType % szT;
								of << _jFF("}");
								of << _jFF("catch(System.Exception e)");
								of << _jFF("{");
								of << _jFF("	if(isPostParse){ throw e;}");
								of << _jFF("}");
								of << _jFF("if(!isFind)");
								of << _jFF("{");
								of << _jFF("	if(!isPostParse)");
								of << _jFF("	{");
								of << _jFF("		if(!nUtil.jCSV.m_PostParseList.ContainsKey(this))");
								of << _jFF("		{");
								of << _jFF("		");
								of << _jFF("			nUtil.jCSV.PostParseData ppd = new nUtil.jCSV.PostParseData();");
								of << _jFF("			ppd.func = new nUtil.jCSV.PostParseFunc(nUtil.jString_%1%.PostParse);")%szT;
								of << _jFF("			ppd.token = token;");
								of << _jFF("			ppd.idx = iStart;");
								of << _jFF("			ppd.o = this;");
								of << _jFF("			ppd.sDebug = \" -> %1% : \" ;") % szT;
								of << _jFF("			nUtil.jCSV.m_PostParseList[this]=ppd;");
								of << _jFF("		}");
								of << _jFF("	}");
								of << _jFF("	else");
								of << _jFF("	{");
								of << _jFF("		Console.WriteLine(\"[WARN] %1% : %2% : \" + token[idx-1] + \"index=\" + (idx - 1).ToString() ) ;") 
									% szT % it->GetTagName();
								of << _jFF("	}");
								of << _jFF("}");
							}
							else
							{
								of << _jFF("nUtil.jString_%2%.Parse(\"%3%::%1%\",token[idx++], ref m_%1%);") % it->GetTagName() % sNewType % szT;
							}
						}
					}
					of << _jFF("}\ncatch(System.Exception e)");
					of << _jFF("{");
					{
						AutoTab c(this);
						of << _jFF("if (nEXCEL.nUtil.jCSV.m_ErrorLogFunc != null)");
						of << _jFF("{");
						of << _jFF("	String strError = String.Format(\"{0} = id={1} {2} [ {3} ]\", e.ToString(), token[0], token[idx -1],idx -1);");
						of << _jFF("	nEXCEL.nUtil.jCSV.m_ErrorLogFunc(strError,e);");
						of << _jFF("}");
						of << _jFF("else");
						of << _jFF("{");
						of << _jFF("	Console.WriteLine(\"{0} = id={1} {2} [ {3} ]\",e.ToString() , token[0] , token[idx-1], idx-1 );");
						of << _jFF("	throw e;");
						of << _jFF("}");
					}
					of << _jFF("}");
				}


				of << _jFF("}");
			}

			of << _jFF("public override string ToString()");
			of << _jFF("{");
			{
				AutoTab b(this);

				of << _jFF("string output = \"\";");
				if(isInH)
				{
					of << _jFF("output = base.ToString();");
					of << _jFF("output += \"\t\";");
				}

				it = peTable->begin();
				jrFOR(it)
				{
					if(is_inherit_node(it))
						continue;

					cstr szType =jC5(it,data_type);


					jIVar* pV = it->GetAttrVar(jS(array_field));
					jIVar* pV2 = it->GetAttrVar(jS(ref_field));
					bool isVec = pV && pV->Get_bool(); 
					//bool isSys = jt_strstr(szType,_T("Sys_")) &&  jt_strcmp(szType+jt_strlen(szType)-5 , _T("_id_t"));
					bool isSys = pV2 && pV2->Get_bool();
					tstring sNewType = get_nUtil_jString_type(it);
					
					cstr szTypeCShap = get_cshap_type(jC5(it,data_type)) ;
					bool isCustom = jt_strstr(szTypeCShap,_T("List<"));

					if(isVec || isSys || isCustom) 
					{
						//jMB(it->GetTagName(), jC5(it,data_type));
						of << _jFF("output += (nUtil.jString_%2%.ToString(m_%1%)+ \",\");") % it->GetTagName() % sNewType;
					}
					else
						of << _jFF("output += m_%1%.ToString() + \",\";") % it->GetTagName();
				}
				of << _jFF("return output;");
			}
			of << _jFF("}");

		}
		of << _jFF("}//class %1%\n") % szT;

		jIE* peName = get_name_field_from_inherit_class(peTable);

		if(!jt_strstr(szT,_T("Tbl_")) && !jt_strstr(szT,_T("Sys__")) && peName)
		{
			of << _jFF("namespace nUtil");
			of << _jFF("{");
			of << _jFF("	class jString_%1%") % szT;
			of << _jFF("	{");
			of << _jFF("		public static string ToString(%1% o)") % szT;
			of << _jFF("		{");
			of << _jFF("			if (o ==null)");
			of << _jFF("			{");
			of << _jFF("				return \"NULL\";");
			of << _jFF("			}");
			of << _jFF("			return o.m_name;");
			of << _jFF("		}");
			of << _jFF("		public static string ToString(List<%1%> sysList)") % szT;
			of << _jFF("		{");
			of << _jFF("			string output = \"\";");
			of << _jFF("			foreach (%1% o in sysList)") % szT;
			of << _jFF("			{");
			of << _jFF("				if( o==null )");
			of << _jFF("					output += \"NULL;\";");
			of << _jFF("				else");
			of << _jFF("					output += (o.m_name + \";\");");
			of << _jFF("			}");
			of << _jFF("			return output;");
			of << _jFF("		}");


			of << _jFF("		public static void PostParse(nEXCEL.nUtil.jCSV.PostParseData ppd)");
			of << _jFF("		{");
			of << _jFF("			%1% o = (%1%)ppd.o;") % szT;
			of << _jFF("			o.ReadCSV(ppd.token,ref ppd.idx,true);");
			of << _jFF("		}");

			of << _jFF("		public static bool Parse(string sDebug,string sVal, ref %1% o)") % szT;
			of << _jFF("		{");
			of << _jFF("			if(sVal==\"\" || sVal==\"0\" || sVal==\"NULL\" || sVal==\"null\") return true;");
			of << _jFF("			if (Char.IsNumber(sVal[0]))");
			of << _jFF("			{");
			of << _jFF("				o = CSV_%1%.Find(int.Parse(sVal));") % szT;
			of << _jFF("				//nEXCEL.nUtil.jCSV.jCHECK_null(o, \"PostParse Error \",sDebug);");
			of << _jFF("			}");
			of << _jFF("			else");
			of << _jFF("			{");
			of << _jFF("				o = CSV_%1%.FindBy_name(sVal);") % szT;
			of << _jFF("				//nEXCEL.nUtil.jCSV.jCHECK_null(o, \"PostParse Error \",sDebug);");
			of << _jFF("			}");
			of << _jFF("			return o!=null;");
			of << _jFF("		}");
			of << _jFF("		public static bool Parse(string sDebug,string sVal, ref List<%1%> oList)") % szT;
			of << _jFF("		{") ;
			of << _jFF("			oList.Clear();");
			of << _jFF("			if(sVal==\"\" || sVal==\"0\" || sVal==\"NULL\" || sVal==\"null\") return true;");
			of << _jFF("			bool isFind=false;");
			of << _jFF("			List<%1%> sysList = (List<%1%>)oList;") % szT;
			of << _jFF("			foreach ( string s in sVal.Split(';') )") ;
			of << _jFF("			{") ;
			of << _jFF("				%1% o=null;") % szT;
			of << _jFF("				if (Char.IsNumber(s[0]))") ;
			of << _jFF("				{") ;
			of << _jFF("					o = CSV_%1%.Find(int.Parse(s));") % szT;
			of << _jFF("					//nEXCEL.nUtil.jCSV.jCHECK_null(o, \"PostParse_List Error \" + sDebug,s);");
			of << _jFF("					sysList.Add(o);");
			of << _jFF("				}") ;
			of << _jFF("				else") ;
			of << _jFF("				{") ;
			of << _jFF("					o = CSV_%1%.FindBy_name(s);") % szT;
			of << _jFF("					//nEXCEL.nUtil.jCSV.jCHECK_null(o, \"PostParse_List Error \" + sDebug,s);");
			of << _jFF("					sysList.Add( o );");
			of << _jFF("				}") ;
			of << _jFF("				if(o!=null)");
			of << _jFF("					isFind=true;");
			of << _jFF("				else");
			of << _jFF("					throw new System.Exception(sVal + \" -> ((\" + s + \")) IS NOT FOUND !! : \" + sDebug);");
			of << _jFF("			}") ;
			of << _jFF("			return isFind;") ;
			of << _jFF("		}") ;

			of << _jFF("	}//class jString_%1%") % szT;
			of << _jFF("}//namespace nUtil");
		}
		of << _jFF("\n\n");

	}//jrFOR(peTable)

}

//CSV로딩 클래스출력.
void Excel_Converter::make_file_cshap_CSV_class(tofstream &of)
{
	jE eSys = m_eDoc(jS(Sys));
	if(eSys.empty()) return;
	jIE* peTable  = eSys->begin();
	jrFOR(peTable)
	{
		cstr szT = peTable->GetTagName();
		if(jt_strstr(szT,_T("Sys__"))) continue;
		if(!jt_strncmp(szT,_T("Tbl_"),4)) continue;
		Print_Title(of, peTable->GetAttr(jS(HELP)) );


// 		vector<jIE*> inheritList;
// 		get_inherit_list(inheritList, peTable);
		of << _jFF("public class CSV_%1%") % szT;
		of << _jFF("{");
		{
			AutoTab a(this);
			of << _jFF("public  class CSV_Sys_Test_Exception : System.Exception");
			of << _jFF("{");
			of << _jFF("\tpublic CSV_Sys_Test_Exception(string s) : base(s)");
			of << _jFF("\t{");
			of << _jFF("\t\tConsole.WriteLine(\"[CSV_Sys_Test_Exception] Logging '{0}'\", this.Message);");
			of << _jFF("\t}");
			of << _jFF("}");
			of << _jFF("public		static List<%1%>		m_List = new List<%1%> { };") % szT;
			of << _jFF("public      static void             Print()");
			of << _jFF("{");
			of << _jFF("\tConsole.WriteLine(\"\\n\\n<<< %1% >>>\");") % szT;
			of << _jFF("\tforeach (%1% p in CSV_%1%.m_List){p.Print();}") % szT;
			of << _jFF("");
			of << _jFF("}");

			of << _jFF("public      static int              Count() { return m_List.Count; }") ;
			of << _jFF("public      static %1%       Find(int idx)// idx is must be over 0. 0 is mean NULL!!!") % szT;
			of << _jFF("{") ;
			{
				AutoTab b(this);
				of << _jFF("if (idx <= 0 || idx >= m_List.Count)") ;
				of << _jFF("{") ;
				of << _jFF("\t return null;");
				of << _jFF("\t//throw new CSV_Sys_Test_Exception(\"범위를 벋어난값 : \" + idx.ToString());") ;
				of << _jFF("}") ;
				of << _jFF("return m_List[idx-1];") ;
			}
			of << _jFF("}") ;

			//#--------------------------------------------------------------------------
			// PK , INDEX  코드 생성.
			//#--------------------------------------------------------------------------
			vector<jIE*> out_NAME;
			get_NAME_field(peTable,out_NAME);
			if(out_NAME.size())
			{
				for(size_t i = 0 ; i < out_NAME.size() ; ++i)
				{
					cstr szName = out_NAME[i]->GetTagName();
					of << _jFF("private static Hashtable m_Hashtable_%1% = new Hashtable();") % szName;
					cstr szType = jC5(out_NAME[i] , data_type);
					szType = get_cshap_type(szType);
					of << _jFF("public static %1% FindBy_%2%(%3% key){return (%1%)m_Hashtable_%2%[key];}\n") % szT % szName % szType;
				}

			}

			vector<jIE*> out_INDEX;
			get_INDEX_field(peTable,out_INDEX);
			if(out_INDEX.size())
			{
				for(size_t i = 0 ; i < out_INDEX.size() ; ++i)
				{
					cstr szName = out_INDEX[i]->GetTagName();
					cstr szType = jC5(out_INDEX[i] , data_type);
					szType = get_cshap_type(szType);

					of << _jFF("private static Dictionary<%3%,List<%1%>> m_Dictionary_%2% = new Dictionary<%3%,List<%1%>>{};") % szT % szName % szType;
					of << _jFF("public static List<%1%> FindBy_%2%(%3% key){return m_Dictionary_%2%[key];}\n") % szT % szName % szType;
				}
			}

			of << _jFF("private static void _makeIndex()");
			of << _jFF("{");
			{
				AutoTab b(this);
				for(size_t i = 0 ; i < out_NAME.size() ; ++i)
				{
					cstr szName = out_NAME[i]->GetTagName();
					of << _jFF("foreach(%1% p in m_List){m_Hashtable_%2%[p.m_%2%] = p;}") % szT % szName;
				}

				for(size_t i = 0 ; i < out_INDEX.size() ; ++i)
				{
					cstr szType = jC5(out_INDEX[i] , data_type);
					szType = get_cshap_type(szType);
					cstr szINDEX = out_INDEX[i]->GetTagName();
					of << _jFF("foreach(%1% p in m_List)") % szT;
					of << _jFF("{");
					{
						AutoTab a(this);

						of << _jFF("if (!m_Dictionary_%2%.ContainsKey(p.m_%2%))")% szT % szINDEX;
						of << _jFF("{");
						of << _jFF("\tm_Dictionary_%2%[p.m_%2%] = new List<%1%> { };")% szT % szINDEX;
						of << _jFF("}");

						of << _jFF("m_Dictionary_%2%[p.m_%2%].Add(p);") % szT % szINDEX;
					}
					of << _jFF("}");
				}

			}
			of << _jFF("}");


			//#--------------------------------------------------------------------------
			// 로딩 코드.
			//#--------------------------------------------------------------------------
			of << _jFF("public static void LoadCSV(string sCsvFileName)") ;
			of << _jFF("{") ;
			{
				AutoTab c(this);
				of << _jFF("FileInfo _finfo = new FileInfo(sCsvFileName);") ;
				of << _jFF("if (!_finfo.Exists)") ;
				of << _jFF("{") ;
				of << _jFF("	Console.WriteLine(\"file not found :: {0}\", sCsvFileName);");
				of << _jFF("	return;") ;
				of << _jFF("}") ;

				of << _jFF("using (StreamReader sr = new StreamReader(sCsvFileName, Encoding.GetEncoding(\"%1%\")))") 
					% pv_CSHAP_CSV_ENCODE->Get_cstr();
				of << _jFF("{") ;
				{
					AutoTab d(this);
					of << _jFF("string sLine = sr.ReadLine();");
					of << _jFF("while ((sLine = sr.ReadLine()) != null)") ;
					of << _jFF("{") ;
					{
						AutoTab e(this);
						of << _jFF("string[] token = sLine.Split(',');") ;
						of << _jFF("%1% info = new %1%();") % szT;
						of << _jFF("int idx=0;");
						of << _jFF("info.ReadCSV(token , ref idx,false);") ;
						of << _jFF("m_List.Add(info);") ;
					}
					of << _jFF("}") ;
				}
				of << _jFF("}") ;

				if(out_NAME.size() )
				{
					of << _jFF("_makeIndex();");
				}
			}
			of << _jTT("}//void LoadCSV()\n");


			//#--------------------------------------------------------------------------
			// 로딩 코드.
			//#--------------------------------------------------------------------------
			of << _jFF("public static void LoadCSV_FromString(string sData)") ;
			of << _jFF("{") ;
			{
				AutoTab c(this);
				of << _jFF("string test = \"\\n\\r\";");
				of << _jFF("string[] all_line = sData.Split(test.ToCharArray());");
				of << _jFF("int i=0;");
				of << _jFF("foreach(String sLine in all_line)") ;
				of << _jFF("{") ;
				{
					AutoTab e(this);
					of << _jFF("if(i==0){ ++i;continue;}");
					of << _jFF("if (sLine.Length == 0) continue;");
					of << _jFF("string[] token = sLine.Split(',');") ;
					of << _jFF("%1% info = new %1%();") % szT;
					of << _jFF("int idx=0;");
					of << _jFF("info.ReadCSV(token , ref idx,false);") ;
					of << _jFF("m_List.Add(info);") ;
				}
				of << _jFF("}") ;

				if(out_NAME.size() )
				{
					of << _jFF("_makeIndex();");
				}
			}
			of << _jTT("}//void LoadCSV_FromString()\n");
		}
		of << _jFF("}// public class CSV_%1%\n\n\n") % szT;
	}//jrFOR(peTable)

}

void Excel_Converter::make_file_cshap()
{
	filesystem::tpath  saveFile(m_save_file_path);
	saveFile /= (m_FileName + jS(.csv.cs) );
	tofstream of(jA(saveFile.string()));

	of << _T("/*------------------------------------------------------------\n") ;
	//of << _jFF("Create By %3%  \nVersion = %1% \nDate =  %2%\n") % jCURR_VERSION % _T(__TIMESTAMP__) % g_ExeEnv.m_szExeName;
	of << _jFF("\ncommand line : \n%1%\n\n") %GetCommandLine();
	of << _T("-------------------------------------------------------------*/\n");
	of << endl;

	static jIE* peUSING_HEADER = nGLOBAL::g_pDocApp->Find(jS(USING_HEADER));
	jIE* it = peUSING_HEADER->begin();
	jrFOR(it)
	{
		of << _jFF("%1%;") % it->Get_cstr();
	}
	of << _jTT("\n");

	of << _jFF("namespace %1%") % m_Namespace;
	of << _jTT("{");
	{
		AutoTab a(this);
		of << _jTT("//TYPE_INFO");
		nXML::jE e = g_eTYPE_INFO(jS(min_max_type));
		make_file_cshap_using(of, e);
		of << _jTT("\n");
		of << _jTT("//TYPE_INFO_NS");
		e = g_eTYPE_INFO_NS(jS(min_max_type));
		if(e.empty())
		{
			jWARN(_T("g_eTYPE_INFO_NS(%s) is not found <min_max_type>"), g_eTYPE_INFO_NS->GetTagName());
		}
		else
		{
			make_file_cshap_using(of, e);
		}
		of << _jTT("\n\n");

		//enum출력.
		make_file_cshap_enum(of);

		//구조체 출력.
		make_file_cshap_struct(of, jS(Sys));
		make_file_cshap_struct(of, jS(Tbl));
		make_file_cshap_struct(of, jS(App));

		//CSV로딩 클래스출력.
		make_file_cshap_CSV_class(of);
		of << _jTT("\n\n");
	}
	of << _jFF("}//namespace %1%\n") % m_Namespace ;


	of.close();
}
