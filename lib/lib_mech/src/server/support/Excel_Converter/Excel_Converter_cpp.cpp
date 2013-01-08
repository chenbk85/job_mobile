/* file : Excel_Converter_cpp.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-28 15:43:23
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "Excel_Converter.h"

jLIST_TYPEDEF_vector(jIE* , g_new_registed_type);

#undef TAB_TIC
#define TAB_TIC _T("\t\t\t")
void pvRef_print_readcsv_help_code(tofstream &of, tcstr szKey, tcstr szMax)
{
}

#undef TAB_TIC
#define TAB_TIC _T("\t\t")

void pvNotRef_print_readcsv_help_code(tofstream &of,tcstr szKey, tcstr szMax)
{
	if(jt_strncmp(szKey,jS(Sys_),4) ==0) 
		return;
	of<<_jNF("%1%& FromeString(OUT %1%* v, IN excel_wcstr sz)\n") % szKey;
	of<<_jNF("{\n");
	of<<_jNF("\treturn v;\n");
	of<<_jNF("}\n");
}

#undef TAB_TIC
#define TAB_TIC _T("\t")
void pvRef_print_tostring_help_code(tofstream &of, tcstr szKey, tcstr szMax)
{

	of<<_jNF("static tcstr ToString(IN %1%_ptr v      , tname1024_t szBuf)\n") % szKey;
	of<<_jNF("{\n");
		of<<_jNF("\tif(v) jt_strcpy(szBuf,v->Get_name());\n");
		of<<_jNF("\telse jt_strcpy(szBuf,jS(NULL) );\n");
	of<<_jNF("\treturn szBuf;\n");
	of<<_jNF("}\n");

	of<<_jNF("namespace %2%{void Excel_PostLoader_registe(%1%_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp);}\n") % szKey % g_Excel_Converter->m_Namespace;
	of<<_jNF("static tcstr ToString(IN %1%_ptr_vec& v , tname1024_t szBuf)\n") % szKey;
	of<<_jNF("{\n");
		of<<_jNF("\ttstring str;\n");
		of<<_jNF("\tfor(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T(\"NULL;\"); continue;};str += v[i]->Get_name();str += _T(\";\");}\n");
		of<<_jNF("\tjt_strncpy(szBuf,str.c_str(),1024-4);\n");
		of<<_jNF("\tszBuf[1024-4]=0;\n");
		of<<_jNF("\treturn szBuf;\n");
	of<<_jNF("}\n");
}
void pvNotRef_print_tostring_help_code(tofstream &of,tcstr szKey, tcstr szMax)
{
	of<<_jNF("static tcstr ToString(IN %1%_vec& v,OUT tname1024_t szBuf)\n") % szKey;
	of<<_jNF("{\n");
		of<<_jNF("\ttstring str;\n");
		of<<_jNF("\tfor(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T(\"0;\");continue;} str += ToString(v[i],szBuf);str += _T(\";\");}\n");
		of<<_jNF("\tjt_strncpy(szBuf,str.c_str(),1024-4);\n");
		of<<_jNF("\tszBuf[1024-4]=0;\n");
		of<<_jNF("\treturn szBuf;\n");
	of<<_jNF("}\n");
}



#undef TAB_TIC
#define TAB_TIC _T("\t")

void pvRef_declear_tostring(tofstream& of, tcstr szKey, tcstr szMax)
{
	of<<_jNF("tcstr ToString(IN %1%_ptr v      , tname1024_t szBuf);\n") % szKey;
	of<<_jNF("tcstr ToString(IN %1%_ptr_vec& v , tname1024_t szBuf);\n") % szKey;
}
void pvNotRef_declear_tostring(tofstream& of, tcstr szKey, tcstr szMax)
{
	of<<_jNF("tcstr ToString(IN %1%_vec& v,OUT tname1024_t szBuf);\n") % szKey;
}



#undef TAB_TIC
#define TAB_TIC _T("\t\t")
void pvRef_declear_readcsv(tofstream &of,tcstr szKey, tcstr szMax)
{
}
void pvNotRef_declear_readcsv(tofstream &of,tcstr szKey, tcstr szMax)
{
	if(jt_strncmp(szKey,jS(Sys_),4) ==0) 
		return;


	of<<_jNF("static void Convert_FromeString(OUT %1%_vec* v, IN excel_wcstr sz,IN int iArrayMax)\n") % szKey;
	of<<_jNF("{\n");
	of<<_jNF("\tEXCEL_WSTRING_SPLIT_CODE;\n");
	of<<_jNF("\tif(iArrayMax && (out.size() >(size_t)iArrayMax) ) \n");
	of<<_jNF("\t{\n");
	of<<_jNF("\t\ttstring szBuf = jFUNC1;\n");
	of<<_jNF("\t\tszBuf+=_T(\"data=\");szBuf+=jT(sz);\n");
	of<<_jNF("\t\tszBuf+=_T(\", array size(\");\n");
	of<<_jNF("\t\ttname1024_t buf2;\n");
	of<<_jNF("\t\tszBuf+=ToString(out.size(),buf2);\n");
	of<<_jNF("\t\tszBuf+=_T(\"iArrayMax(\");	szBuf+=ToString(iArrayMax,buf2);	szBuf+=_T(\");\");\n");
	of<<_jNF("\t\tthrow tstring(szBuf);\n");
	of<<_jNF("\t}\n");
	of<<_jNF("\t(*v).resize(out.size());\n");
	of<<_jNF("\ttry{for(size_t i=0;i<out.size(); ++i){FromString(&((*v)[i]),out[i].c_str());}}\n");
	of<<_jNF("\tcatch (tstring e)\n");
	of<<_jNF("\t\t{tstring szBuf = jFUNC1; szBuf+= _T(\"catched error > \");szBuf+=e.c_str(); szBuf+=_T(\")\");throw tstring(szBuf);};\n");
	of<<_jNF("}\n");

	of<<_jNF("static void Excel_PostLoader_registe_%1%_vec(OUT %1%_vec* v, IN excel_wcstr sz, IN int iArrayMax , tcstr szHelp)\n")% szKey;
	of<<_jNF("{\n");
	of<<_jNF("\tg_Excel_PostLoader.insert(boost::bind(Convert_FromeString, v , _1,iArrayMax),sz,szHelp);\n");
	of<<_jNF("}\n");
}


#undef TAB_TIC
#define TAB_TIC _T("\t")
void pvRef_declear_sq_type(tofstream &of,tcstr szKey, tcstr szMax)
{
	of<<_jNF("PROTOS_ENUM_TYPE_csv(%1%);\n") % szKey;
	of<<_jNF("PROTOS_ENUM_TYPE_COMPLAX_csv(vector<%1%*>);\n") % szKey;
}
void pvNotRef_declear_sq_type(tofstream &of,tcstr szKey, tcstr szMax)
{
	of<<_jNF("PROTOS_ENUM_TYPE_COMPLAX_csv(vector<%1%>);\n") % szKey;
}


#undef TAB_TIC
#define TAB_TIC _T("\t")
void pvRef_print_sq_def_help_code(tofstream &of,tcstr szKey, tcstr szMax)
{
	//of<<_jNF("DECLARE_INSTANCE_TYPE_COMPLAX_csv(vector<%1%*>);") % szKey;
}
void pvNotRef_print_sq_def_help_code(tofstream &of,tcstr szKey, tcstr szMax)
{
	if(jt_strncmp(szKey,jS(Sys_),4) ==0) 
		return;

	of<<_jNF("DECLARE_INSTANCE_TYPE_COMPLAX_csv(vector<%1%>);") % szKey;
}


void Excel_Converter::make_file_cpp()
{
	filesystem::tpath  saveFile(m_save_file_path);
	saveFile /= (m_FileName + jS(.cpp) );
	tofstream of(jA(saveFile.string()));

	of << _T("/*------------------------------------------------------------\n") ;
	//of << _jF("Create By %3%  \nVersion = %1% \nDate =  %2%\n") % jCURR_VERSION % _T(__TIMESTAMP__) % g_ExeEnv.m_szExeName;
	//of << _jF("\ncommand line : \n%1%\n\n") %GetCommandLine();
	of << _T("-------------------------------------------------------------*/\n");
	of << endl;

	of << _T("#include \"stdafx.h\"\n");
	tname1024_t szHeader;
	jt_sprintf(szHeader,_T("#include <%s>"),pv_header_file->Get_cstr());
	of << szHeader <<endl <<endl;

	of << _jF("#include \"%1%.h\"\n") % m_FileName;
	of << endl;

	//--------------------------------------------------------------------------
	// GetTable_FromeString와 ToString핼프 함수 출력
	//--------------------------------------------------------------------------
	{// ref , arrary형 필드 전방 선언
		of<<endl << endl;
		of<<_jF("//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.\n") ;
		of<<_jF("#if 0\n\n") ;

		begin_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE),true);
		{
			_print_help_tostring(of, 0/*pvRef_print_sq_def_help_code */, pvNotRef_print_sq_def_help_code);
		}
		end_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE));


		of<<endl;
#ifdef jUSE_EXTERNAL_TO_STRING // ToString함수를 외부에서 정의해서 사용할때 .
		of<< _jF("namespace nMech\n");
		of<< _jF("{\n");
			_print_help_tostring(of, pvRef_print_tostring_help_code , pvNotRef_print_tostring_help_code);
		of<< _jF("}//namespace nMech\n");
		of<<endl << endl;
#endif

		of<< _jF("namespace nMech\n");
		of<< _jF("{\n");
		{
			AutoTab a(this);
			of<< _jF("namespace %1%\n") % g_Excel_Converter->m_Namespace;
			of<< _jF("{\n");
			_print_help_tostring(of, 0/*pvRef_print_readcsv_help_code */, pvNotRef_print_readcsv_help_code);
			of<< _jF("}//namespace %1%\n") % g_Excel_Converter->m_Namespace;
		}
		of<< _jF("}//namespace nMech\n");

		of<<_jF("#endif //구현되어야 하는 코드 끝.\n") ;
		of<<endl ;

	}


	begin_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE),true);
	{
		tcstr szStruct = jS(Sys);
		of << _jFF("#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_%3%) && defined(for_each_%1%_%2%_%3%_STRUCT_LIST)") % m_Namespace % m_FileName % szStruct ;
		of << _jFF("\tfor_each_%1%_%2%_%3%_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_%3%);") % m_Namespace % m_FileName % szStruct ;
		of << _jFF("#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_%1%\n\n") % szStruct;

		szStruct = jS(Tbl);
		of << _jFF("#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_%1%") % szStruct;
		of << _jFF("\tfor_each_%1%_%2%_%3%_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_%3%);") % m_Namespace % m_FileName % szStruct;
		of << _jFF("#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_%1%\n\n") % szStruct;

		_print_help_tostring(of, pvRef_declear_sq_type,pvNotRef_declear_sq_type);
	}
	end_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE));

	if(m_eEnum.size())
	{
		for_each_ENUM_LIST(of, jS(jEXCEL_SQ_DECLARE_ENUM_TYPE) );
		of<<endl;
	}

	//sql bind코드를 위한부분
	if(m_eUse.size())
	{
		begin_ServerSideCode(of);
		for_each_STRUCT_LIST(of, jS(jEXCEL_SQL_BIND_FUNC_DEFINE) ,jS(Tbl));
		of <<endl;
		end_ServerSideCode(of);
	}


	of << _jF("namespace %1% {") % pv_domain_name->Get_cstr();
	//--------------------------------------------------------------------------
	// ToString 전방선언 
	//--------------------------------------------------------------------------
	{
		AutoTab a(this);
		of<<endl ;
#ifdef jUSE_EXTERNAL_TO_STRING
		_print_help_tostring(of,pvRef_declear_tostring,pvNotRef_declear_tostring);
#else
		_print_help_tostring(of, pvRef_print_tostring_help_code , pvNotRef_print_tostring_help_code);
#endif

	}

	of << _jF("\tnamespace %1% {\n\n") % m_Namespace;


	//--------------------------------------------------------------------------
	// ref , arrary형 필드 전방 선언
	//--------------------------------------------------------------------------
	{
		AutoTab a(this);
	_print_help_tostring(of,0/*pvRef_declear_readcsv*/,pvNotRef_declear_readcsv);
	}

	make_file_cpp_SUB_gen_enum(of);

	make_file_cpp_SUB_gen_struct_set_get(of,m_eSys);
	make_file_cpp_SUB_gen_struct_ReadCSV(of,m_eSys);
	make_file_cpp_SUB_gen_struct_jDebugPrint(of,m_eSys);


	make_file_cpp_SUB_gen_struct_set_get(of,m_eUse);
	make_file_cpp_SUB_gen_struct_jDebugPrint(of,m_eUse);

	make_file_cpp_SUB_gen_struct_set_get(of,m_eApp);
	make_file_cpp_SUB_gen_struct_jDebugPrint(of,m_eApp);


	of << _jF("\n} //namespace %1% \n") % m_Namespace;
	of << _jF("\n}// namespace %1% \n") % pv_domain_name->Get_cstr() ;


	if(pv_IsUse_SQ_BindCode->Get_bool())
		make_file_cpp_SUB_gen_Squirrel_Bind_code(of);

	make_file_cpp_SUB_gen_struct_nDebug_jDebugPrint(of);

	of.close();
}

void Excel_Converter::make_file_cpp_SUB_gen_enum(tofstream & of)
{
	if(m_eEnum.empty()) return;
	jIE* it = m_eEnum->begin();

	jrFOR(it)
	{
		of << _jF("%1% %2%::jEnumString g_ES_%3%[] = \n") % pv_EXCEL_LIB_API->Get_cstr() % pv_net_core_ns->Get_cstr() % it->GetTagName();
		of << Tab() << _T("{\n");
		AddTab();
		of << _jF("{ %1% , 0, 0},\n") % it->size();

		if(pv_IsGenerateFullCode->Get_bool())
		{
			jIE* peField = it->begin();
			jrFOR(peField)
			{
				of << _jF("{ e%1%, \"%1%\" , _T(\"%2%\") },\n") % peField->GetTagName() % jC5(peField,help);
			}
		}
		else
		{
			of << Tab() << _T("#ifdef jEXCEL_ENUM_STRING_CPP_CODE\n");
			of << _jF("\tfor_each_%1%_%2%_ENUM_FIELD(jEXCEL_ENUM_STRING_CPP_CODE)\n") % m_Namespace % it->GetTagName();
			of << Tab() << _T("#endif // jEXCEL_ENUM_STRING_CPP_CODE\n");
		}
		
		DecTab();
		of << Tab() << _T("};\n");
	}
}
bool IsGettterOrg(cstr data_type,jVar getter)
{
	if( getter->IsContents(data_type) ) return true;
	if( jt_strstr(data_type,_T("aname")) ) return true;
	if( jt_strstr(data_type,_T("wname")) ) return true;
	if( jt_strstr(data_type,_T("tname")) ) return true;

	return false;
}


bool _regist_info_xml(tcstr data_type,jE e)
{
	g_isSave_AppDoc=true;
	g_isGen_table_type=true;

	bool isS = !jt_strncmp(data_type,jS(Sys_),jt_strlen(jS(Sys_)));
	bool isU = !jt_strncmp(data_type,jS(Tbl_),jt_strlen(jS(Tbl_)));
	bool isE = data_type[0]=='E';

	jWARN(_T("%s 자료형이 <TYPE_INFO>에 등록안되어 있음. 자동 등록함."),data_type);
	if(!( isS || isU || isE ) )
	{
		e = g_eTYPE_INFO_NS[jS(min_max_type)][data_type];
		e.AttrP(jS(Org)).T() = jS(int32);
		e.AttrP(jS(Setter)).T() = jS(int32);
		e.AttrP(jS(Getter)).T() = jS(int32);
		e.AttrP(jS(Tag)).T() = jS(i32);
		e.AttrP(jS(org_set_get)).SetType(jIVar::EDint2);
		e.AttrP(jS(org_set_get))->GetInt(0)=1;
		e.AttrP(jS(org_set_get))->GetInt(1)=1;
		e.AttrP(jS(db_type)).T() = jS(INT);
		g_new_registed_type.push_back(e.BaseI());
		return true;
	}
	e = g_eTYPE_INFO_NS[jS(min_max_type)][data_type];
	if(isU)
	{
		e.AttrP(jS(Org)).T() = jS(db_uid_type);
		e.AttrP(jS(Setter)).T() = jS(db_uid_type_ref);
		e.AttrP(jS(Getter)).T() = jS(db_uid_type_ref);
		e.AttrP(jS(Tag)).T() = jS(i64);
		e.AttrP(jS(org_set_get)).SetType(jIVar::EDint2);
		e.AttrP(jS(org_set_get))->GetInt(0)=1;
		e.AttrP(jS(org_set_get))->GetInt(1)=1;
		e.AttrP(jS(db_type)).T() = jS(BIGINT);
	}
	else if(isS)
	{
		e.AttrP(jS(Setter)).T() = jS(uint16);
		e.AttrP(jS(Getter)).T() = data_type;
		e.AttrP(jS(Tag)).T() = jS(u16);
		e.AttrP(jS(org_set_get)).SetType(jIVar::EDint2);
		e.AttrP(jS(org_set_get))->GetInt(0)=1;
		e.AttrP(jS(org_set_get))->GetInt(1)=1;
		e.AttrP(jS(db_type)).T() = jS(SMALLINT);
	}
	else if(isE)
	{
		e.AttrP(jS(Setter)).T() = data_type;
		e.AttrP(jS(Getter)).T() = data_type;
		e.AttrP(jS(Tag)).T() = jS(e);
		e.AttrP(jS(org_set_get)).SetType(jIVar::EDint2);
		e.AttrP(jS(org_set_get))->GetInt(0)=1;
		e.AttrP(jS(org_set_get))->GetInt(1)=1;
		e.AttrP(jS(db_type)).T() = jS(TINYINT);
	}
	return true;

}


void Excel_Converter::make_file_cpp_SUB_gen_struct_set_get(tofstream & of, jE table)
{
	if(table.empty()) return;
	jIE* peTable = table->begin();
	tcstr szStruct = table->GetTagName();

	of << _jFF("#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_%1%") % peTable->GetTagName();
	of << _jFF("\tjEXCEL_TABLE_COMMON_CODE_CPP_%1%();") % peTable->GetTagName();
	of << _jFF("#endif //jEXCEL_TABLE_COMMON_CODE_CPP_%1%\n\n") % peTable->GetTagName();

	of<<_T("\n#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN\n");
	begin_ServerSideCode(of);

	jrFOR(peTable)
	{
		jIE* peField = peTable->begin();
		jrFOR(peField)
		{
			if(nInherit::find_Field_Inherit_Table(peField)) 
				continue;

			cstr data_type = jC5(peField,data_type);
			cstr eng_name = peField->GetTagName();

			jIVar* pvArray = peField->GetAttrVar(jS(array_field));
			jIVar* pvRef = peField->GetAttrVar(jS(ref_field));

			fname_t varName;
			_GetMemeberName(eng_name,data_type, varName, pvArray,pvRef);

			jE e = Get_TYPE_INFO(data_type);

			if(pvArray || pvRef)
			{
				//--------------------------------------------------------------------------
				// ref, array 형 필드에 대한 set , get 함수 생성.
				//--------------------------------------------------------------------------
				if(pvArray)
				{
					_print_set_get_ref_array_Field(of,data_type, peTable->GetTagName() , eng_name,varName,_T("_ref"));
				}
				else
				{
					_print_set_get_ref_array_Field(of,data_type, peTable->GetTagName() , eng_name,varName);
				}

				continue;
			}
			else if(e.empty())
			{
				if(!_regist_info_xml(data_type,e))
					continue;
				e = Get_TYPE_INFO(data_type);
			}

			//--------------------------------------------------------------------------
			// 일반 자료형 필드에 대한 set , get 함수 생성.
			//--------------------------------------------------------------------------

			bool is_org_get= e.Attr(jS(org_set_get))->GetInt(1);
			bool is_org_set = e.Attr(jS(org_set_get))->GetInt(0);
			jVar vST = e.Attr(jS(Setter));
			jVar vGT = e.Attr(jS(Getter));

			jE max = peField->Find(jS(max),1);
			jE enumValue = _IsEnumValue(max);

			tcstr szGetType = vGT->Get_cstr();
			tcstr szSetType = vST->Get_cstr();
			if(enumValue.full())
			{
				szSetType = szGetType = enumValue->GetTagName();
			}
			else
			{
				if(max->Get_cstr()[0] == 'E')
				{
					jWARN(_T("액셀에서 enum_%s가 정의 안되어있는것 같음. enum정의를 못참음"),max->Get_cstr());
				}
			}

			of<<_jF("%1% %3%::Get_%2%()") % szGetType % eng_name %peTable->GetTagName();
			of<<Tab()<<_T("{");
			if(is_org_get)
			{
				of<<_jF("\treturn (%2%)%1%;") % varName %szGetType;
			}
			else
				of<<_jF("return %2%::jGetter(%1%);") % varName % pv_net_core_ns->Get_cstr();
			of<<_T("}\n");


			of<<_jF("void %3%::Set_%1%(%2% v)\n") % eng_name % szSetType %peTable->GetTagName();
			of<<Tab()<<_T("{\n");
			AddTab();


			if( e(-1)->IsName(jS(fname)) )
			{
				of<<_jF("if(!v){ throw _T(\"%1%::Set_%2%( val = NULL )\");}") % peTable->GetTagName() % eng_name;
				of<<endl;
			}
			else if(e(-1)->IsName(jS(min_max_type)))
			{
				if(enumValue.full())
				{
					tstring smin = tstring(jS(eBEGIN_)) + enumValue->GetTagName();
					tstring smax = tstring(jS(eEND_)) + enumValue->GetTagName();

					of<<_jF("if(v<%1% || v>=%2%)\n") %smin %smax;
					of<<Tab() << _T("{\n");
					of<<_jF("\tjERROR(_T(\"%1%::Set_%2%(enum minmax(%3%,%3%)error, val=%3%\")\n\t\t\t\t,%4%,%5%,v);\n")
						% peTable->GetTagName() % peField->GetTagName() % _T("%d") % smin % smax;
					of<<Tab() << _T("}\n");
				}
				else
				{
					if(max.Var()->IsType(jIVar::EDcstr) && jt_strlen(max.Var()->Get_cstr())  && !jt_strchr(max->Get_cstr(),'=') )
					{
#if 0
						of<<_jF("if(v>%1%){ jERROR_T(\"%2%::Set_%3%(max error, val=%4%, max=%1% )\"),v);}\n")
							% max->Get_cstr() % peTable->GetTagName() % peField->GetTagName() % _T("%d");
#else
						if(tstring(jS(Eservice))==max->Get_cstr())
						{
							int i=0;
							++i;
						}
						of<<_jF("if(v>%1%) v = (%2%)%1%;\n") % max->Get_cstr() % data_type;
#endif
					}

					jE min = peField->Find(jS(min));
					if(min.Var()->IsType(jIVar::EDcstr) && jt_strlen(min->Get_cstr()) )
					{
#if 0
						of<<_jF("if(v<%1%){ jERROR_T(\"%2%::Set_%3%(min error, val=%4%, min=%1% )\"),v);}\n")
							% min->Get_cstr() % peTable->GetTagName() % peField->GetTagName() % _T("%d");
#else
						of<<_jF("if(v<%1%) v = %1%;\n") % min->Get_cstr();
#endif
					}
				}
			}

			if(is_org_set)
			{
				of<<_jF("%1%=v;\n") % varName;
			}
			else if(e(-1)->IsName(jS(fname)))
			{
				cstr szLen = e.Attr(jS(Tag))->Get_cstr()+1;
				of<<_jF("%3%::jSetter(%1% , v, %2%);\n") % varName % szLen % pv_net_core_ns->Get_cstr();
			}
			else
			{
				of<<_jF("%2%::jSetter(%1% , v);\n") % varName% pv_net_core_ns->Get_cstr();
			}

			DecTab();
			of<<Tab()<<_T("}\n");
			of<<endl;

		}//구조체의 필드
	}// 구조체

	end_ServerSideCode(of);
	of<<_T("#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN\n");


	of << _jFF("#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_%1%") % szStruct;
	of << _jFF("\tfor_each_%1%_%2%_%3%_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_%3%);") % m_Namespace % m_FileName % szStruct;
	of << _jFF("#endif //jEXCEL_TABLE_COMMON_CODE_CPP_%1%\n\n") % szStruct;


}

void Excel_Converter::make_file_cpp_SUB_gen_struct_jDebugPrint(tofstream & of,jE eStruct)
{
	if(eStruct.empty()) return;
	jIE* peTable = eStruct->begin();
	jrFOR(peTable)
	{
		of<<_jF("void %1%::DebugPrint()\n") % peTable->GetTagName();
		of<<_jT("{") ;
		AddTab();
		of<<_jF("tname1024_t szBuf;\n");

		for_each_STRUCT_FILELD_all_member(of, peTable->GetTagName(),jS(jEXCEL_STRUCT_FIELD_DebugPrint));
		DecTab();
		of<<_jT("\n}\n\n");
	}
}

void Excel_Converter::make_file_cpp_SUB_gen_struct_ReadCSV(tofstream & of, jE table)
{
	if(table.empty()) return;
	jIE* peTable = table->begin();
	jrFOR(peTable)
	{
		of <<_jF("%2% CSV_%1% g_%1%;\n\n") % peTable->GetTagName() % pv_EXCEL_LIB_API->Get_cstr();

		of<<endl;
		
		of<<_jF("tcstr %1%::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)\n") % peTable->GetTagName();
		of<<_jT("{\n");
		AddTab();
		of<<_jT("tcstr szKEY=0;\n");
		of<<_jT("tfname_t szHelp;\n");
		of<<_jT("szHelp[0]=0;\n");
		of<<_jT("if(isCheck && (out.size() != Get_STRUCT_COUNT()) )\n");
		of<<_jT("{\n");
		of<<_jF("\tjERROR(_T(\"parse size error(%1%!=Get_STRUCT_COUNT(%1%) lineNum=%2%\"),out.size(),Get_STRUCT_COUNT(),index );\n") 
			%_T("%d") % _T("%s");
		of<<_jT("}\n");

		jIE* peField = peTable->begin();
		jrFOR(peField)
		{
			jIE* peInherit = nInherit::find_Field_Inherit_Table(peField);
			if(peInherit)
			{
				of <<_jF("szKEY = %1%::ReadCSV(iRecord ,out,index,false);\n") % peInherit->GetTagName();
				continue;
			}
			tcstr data_type = jC5(peField,data_type);
			jE eCfgType = Get_TYPE_INFO(data_type);
			tstring buf_data_type;
			jIVar* pvArray = peField->GetAttrVar(jS(array_field));
			jIVar* pvRef = peField->GetAttrVar(jS(ref_field));
			fname_t varName;
			_GetMemeberName(peField->GetTagName(),data_type, varName, pvArray,pvRef);
			if(pvArray || pvRef)
			{
				of<<_jF("jt_sprintf(szHelp, _T(\"loading(iRecord=%3%) file(%4%)%1%::%2%\"),(int32)iRecord);\n") 
					% peTable->GetTagName() % peField->GetTagName() 
					% _T("%d") 
					% m_FileName;
				if(pvRef)
				{
					if(pvArray)
					{
						of<<_jF("Excel_PostLoader_registe(&%1% , out[index++].c_str() ,%2% , szHelp ) ;\n") 
							% varName % pvArray->Get_int();

					}
					else
					{
						of<<_jF("Excel_PostLoader_registe(&%1%, out[index++].c_str()  , szHelp );\n") 
							% varName ;
					}
				}
				else
				{
					of<<_jF("Excel_PostLoader_registe_%3%(&%1%, out[index++].c_str(), %2% , szHelp );\n")
						% varName % pvArray->Get_int() % data_type;
				}
			}
			else if( eCfgType(-1)->IsName(jS(simple_type)) )
			{
				buf_data_type = data_type;
				of<<_jF("FromString(&%1%,out[index++]);\n") % varName;
			}
			else if( eCfgType(-1)->IsName(jS(min_max_type)) )
			{
				jE max = peField->Find(jS(max));
				jE enumT = _IsEnumValue(max);
				if(enumT.full())
				{
					//buf_data_type = m_Namespace + _T("::eBEGIN_") + enumT->GetTagName();
					of<<_jF("Set_%2%(FromString(out[index++],%1%) );\n") % varName % peField->GetTagName();
				}
				else
				{
					of<<_jF("Set_%2%(FromString(out[index++],%1%) );\n") % varName % peField->GetTagName();
				}
			}
			else if (eCfgType(-1)->IsName(jS(string))  || eCfgType(-1)->IsName(jS(fname)) )
			{
				fname_t uni_ansi;
				if(!jt_strncmp(data_type,_T("net_string"), jt_strlen(_T("net_string")) ) )
				{
					jt_strcpy(uni_ansi ,jS(T) );
				}
				else
				{
					uni_ansi[0] = toupper(data_type[0]);
					uni_ansi[1] =0;
				}
				of<<_jF("Set_%1%(nExcelUtil_StringConverter(out[index++]).get%3%());\n") % peField->GetTagName() % peField->GetOrder() % uni_ansi;
			}
			else
			{
				peField->DebugPrint(nInterface::g_pjILog);
				jWARN(_T("처리 할 수 없는 데이타 타입 : %s"), data_type);

			}
			if(peField->IsName(jS(name)))
			{
				of<<_jF("szKEY = Get_name();\n");
			}
		}//jrFOR(peField)

		of<<_jF("return szKEY;\n");
		DecTab();
		of<<_jT("}\n");
		of<<endl;

	}

}


void Excel_Converter::make_file_h_SUB_gen_Squirrel_Bind_code(tofstream & of)
{
	begin_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE),true);
	of << _jFF("using namespace %1%::%2%;")% pv_domain_name->Get_cstr()% m_Namespace;
#if 0
	if(m_eEnum.size())
	{
		for_each_ENUM_LIST(of, jS(jEXCEL_SQ_DECLARE_ENUM_TYPE) );
		of<<endl;
	}
#endif
	if(m_eSys.size())
	{
		for_each_STRUCT_LIST(of, jS(jEXCEL_SQ_DECLARE_INSTANCE_TYPE) ,jS(Sys));
		of <<endl;
	}
	if(m_eUse.size())
	{
		for_each_STRUCT_LIST(of, jS(jEXCEL_SQ_DECLARE_INSTANCE_TYPE) ,jS(Tbl));
		of <<endl;
	}
	if(m_eApp.size())
	{
		for_each_STRUCT_LIST(of, jS(jEXCEL_SQ_DECLARE_INSTANCE_TYPE) ,jS(App));
		of <<endl;
	}

	of << endl;
	end_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE));
}


void Excel_Converter::make_file_cpp_SUB_gen_Squirrel_Bind_code(tofstream & of)
{
	begin_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE),true);
	of << _jFF("using namespace %1%::%2%;")% pv_domain_name->Get_cstr()% m_Namespace;

	of << endl;

	make_file_cpp_SUB_gen_sq_bind_Table_declear_jCSV_File(of, m_eUse);
	make_file_cpp_SUB_gen_sq_bind_Table_declear_jCSV_File(of, m_eSys);

	of << _jFF("namespace %1% { namespace %2%") % pv_domain_name->Get_cstr() % m_Namespace;
	of << _jTT("{");
	{
		AutoTab b(this);

		of << _jFF("jSQ_REGIST_BIND(%2%_%1%_%3%)") % m_Namespace % pv_domain_name->Get_cstr() % m_FileName;
		of << _jTT("{");
		{
			AutoTab a(this);

			make_file_cpp_SUB_gen_sq_bind_EnumField(of);

			make_file_cpp_SUB_gen_sq_bind_Table(of, m_eSys);
			make_file_cpp_SUB_gen_sq_bind_Table(of, m_eUse);
			make_file_cpp_SUB_gen_sq_bind_Table(of, m_eApp);
		}
		of << _jTT("}");

	}
	of << _jFF("} /*namespace %1% */ }// namespace %2% \n") % m_Namespace % pv_domain_name->Get_cstr() ;

	end_DEFINE(of,jS(jNOT_USE_SQ_BIND_CODE));
}

void Excel_Converter::make_file_cpp_SUB_gen_sq_bind_EnumField(tofstream & of)
{
	if(m_eEnum.empty()) return;
	of<< _jTT("{");
	AddTab();

	of<< _jTT("SquirrelObject enumRoot= nSQ::jSQ_GetEnumTable();");
	for_each_ENUM_LIST(of, jS(jEXCEL_SQ_bind_EnumField_BEGIN) );
	nXML::jE it = m_eEnum.begin();
	eFOR(it)
	{
		for_each_ENUM_FILELD(of, it->GetTagName(), jS(jEXCEL_SQ_bind_EnumField));
	}

	DecTab();
	of<< _jTT("}");

}


void Excel_Converter::make_file_cpp_SUB_gen_sq_bind_Table_declear_jCSV_File(tofstream & of, nXML::jE eTable)
{
	if(eTable.empty()) return;
	jIE* it = eTable->begin();
	jrFOR(it)
	{
		//of << _jFF("typedef CSV_%1% %1%_csv_file_t;") % it->GetTagName() ;

		// 주의 아래코드는 excel_code_util.h의  jEXCEL_SQ_DECLARE_INSTANCE_TYPE()에 의해 만들어짐.
		//of << _jFF("DECLARE_INSTANCE_TYPE(%2%::%3%::%1%);") % it->GetTagName()% pv_domain_name->Get_cstr() % m_Namespace;
		if(eTable->IsName(jS(Sys)))
		{
			of << _jFF("DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<%1%>);") % it->GetTagName();
		}
		
// 		of << _jFF("int CSV_%1%_size(){ return %2%::%3%::g_%1%.size();}") % it->GetTagName() % pv_domain_name->Get_cstr() % m_Namespace;
// 		of << _jFF("Sys_Error* CSV_%1%_at(int array_index){ return %2%::%3%::g_%1%.at(array_index);}")% it->GetTagName() % pv_domain_name->Get_cstr() % m_Namespace;
// 		of << _jFF("Sys_Error* CSV_%1%_Index(Sys_Error_id_t sid){ return %2%::%3%::g_%1%.Index(sid);}")% it->GetTagName() % pv_domain_name->Get_cstr() % m_Namespace;
// 		of << _jFF("Sys_Error* CSV_%1%_find(tcstr key){ return %2%::%3%::g_%1%.find(key);}")% it->GetTagName() % pv_domain_name->Get_cstr() % m_Namespace;

		of<<endl;
	}

}

void Excel_Converter::make_file_cpp_SUB_gen_sq_bind_Table(tofstream & of, nXML::jE eTables)
{
	if(eTables.empty()) return;
	jIE* peTable = eTables->begin();
	jrFOR(peTable)
	{
		if(eTables->IsName(jS(Sys)) )
		{
			of<< _jFF("jSQ_Interface(nMech::nUtil::jCSV_File<%1%>)") % peTable->GetTagName();
			of<< _jFF("\tjSQ_fn(size,\"int(void)\",\"total size\")");
			of<< _jFF("\tjSQ_fn(at,\"%1%*(int index)\",\"array operator. index is start 0\")") % peTable->GetTagName();
			of<< _jFF("\tjSQ_fn(Index,\"%1%*(int index)\",\"array operator. index is start 1\")") % peTable->GetTagName();
			of<< _jFF("\tjSQ_fn(find,\"%1%*(tcstr key)\",\"map operator\")") % peTable->GetTagName();
			of<< _jTT("jSQ_end();\n");
		}

		of<< _jFF("jSQ_Interface(%1%)") % peTable->GetTagName();

		for_each_STRUCT_FILELD(of, peTable->GetTagName(), jS(jEXCEL_SQ_TABLE_FILED_BIND));
		std::vector<nXML::jE> vec;
		nInherit::get_Inherit_Info(vec,peTable);
		for(size_t i=0; i< vec.size() ; ++i)
		{
			of<< _jFF("\tjSQ_fn(GetBase_%1%,\"%1%*()\",\"Get base Table\")") % vec[i]->GetTagName();
		}

		of<< _jFF("jEXCEL_SQ_TABLE_FUNC_BIND(%1%)") % peTable->GetTagName();
		of<< _jTT("jSQ_end();");

		if(eTables->IsName(jS(Sys)) )
		{
			of << _jFF("");
			of << _jFF("{");
			of << _jFF("	nMech::nUtil::jCSV_File<%1%>* p = &g_%1%;") %peTable->GetTagName();
			of << _jFF("	jSQ_g_var(p , g_%1%);") % peTable->GetTagName();
			of << _jFF("}");
		}

		of<<endl;
	}

}

void Excel_Converter::make_file_cpp_SUB_gen_struct_nDebug_jDebugPrint(tofstream & of)
{
	
}
