/* file : Excel_Converter_h.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-28 15:44:17
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "Excel_Converter.h"


void Excel_Converter::make_file_h()
{
	filesystem::tpath  saveFile(m_save_file_path);
	saveFile /= (m_FileName + jS(.h) );
	tofstream of(jA(saveFile.string()));

	of << _T("/*------------------------------------------------------------\n") ;
	//of << _jF("Create By %3%  \nVersion = %1% \nDate =  %2%\n") % jCURR_VERSION % _T(__TIMESTAMP__) % g_ExeEnv.m_szExeName;
	//of << _jF("\ncommand line : \n%1%\n\n") %GetCommandLine();
	of << _T("-------------------------------------------------------------*/\n");
	of << endl;


	of << _jF("#ifndef __namespace_%1%___filename_%2%_\n") % m_Namespace % m_FileName ;
	of << _jF("#define __namespace_%1%___filename_%2%_\n") % m_Namespace % m_FileName ;
	of << endl;
	of << _jF("#include \"table_const_%1%.h\"\n") % m_FileName;

	make_file_h_SUB_enum_gen_define(of);

	make_file_h_SUB_struct_gen_define(of, jS(Sys));
	make_file_h_SUB_struct_gen_define(of, jS(Tbl));
	make_file_h_SUB_struct_gen_define(of, jS(App));


	Print_Title(of , _T("코드 시작"));

	of << _jF("namespace %1% { namespace %2% \n{\n\n") % pv_domain_name->Get_cstr() % m_Namespace;

	{

		make_file_h_SUB_gen_enum(of);

		{// ref , arrary형 필드 전방 선언
			AutoTab a(this);
			m_Array_Ref_it it = m_Array_Ref.begin(), ie = m_Array_Ref.end();

			std::set<tstring> listType;
			for(;it!=ie;++it)
			{
				jIE* peField= *it;
				jE eField = peField;
				jIVar* data_type = peField->Find(jS(data_type) )->GetVar();
				eField.AttrP(jS(org_data_type_for_arr_ref)).T() = data_type->Get_cstr();

				bool isPrinted=false;
				if(listType.count(data_type->Get_cstr()))
				{
					isPrinted=true;
				}
				else
				{
					listType.insert(data_type->Get_cstr());
				}

				jIVar* pvRef = peField->GetAttrVar(jS(ref_field));
				bool isRef=false;
				tstring sOriginalProto_data_type = data_type->Get_cstr();

				if(pvRef && pvRef->Get_bool())
				{
					if(!isPrinted)
					{
						of<<_jF("struct %1%;\n") % data_type->Get_cstr() ;
						of<<_jF("typedef %1%* %1%_ptr;\n") % data_type->Get_cstr() ;
						of<<_jF("typedef std::vector<%1%_ptr> %1%_ptr_vec;\n") % data_type->Get_cstr();
						of<<_jF("typedef %1%_ptr_vec& %1%_ptr_vec_ref;\n") % data_type->Get_cstr();
						of<<endl;

					}
					tname256_t szBuf;
					jt_sprintf(szBuf,_T("%s_ptr"), data_type->Get_cstr() );
					data_type->Set_cstr(szBuf);
					isRef=true;

					jIVar* pvArray = peField->GetAttrVar(jS(array_field));
					if(pvArray)
					{
						tname256_t szBuf;
						jt_sprintf(szBuf,_T("%s_vec"), data_type->Get_cstr() );
						data_type->Set_cstr(szBuf);
					}
				
					continue;
				}

				jIVar* pvArray = peField->GetAttrVar(jS(array_field));
				if(pvArray)
				{
					if(!isPrinted)
					{
						of<<_jF("typedef std::vector<%1%> %1%_vec;\n") % data_type->Get_cstr();
						of<<_jF("typedef %1%_vec& %1%_vec_ref;\n") % data_type->Get_cstr();
						of<<endl;
					}
					tname256_t szBuf;
					jt_sprintf(szBuf,_T("%s_vec"), data_type->Get_cstr() );
					data_type->Set_cstr(szBuf);
				}
			}
			of<<endl << endl;
		}

		//--------------------------------------------------------------------------
		// 구조체 생성
		//--------------------------------------------------------------------------
		make_file_h_SUB_struct(of,jS(Sys));
		make_file_h_SUB_struct(of,jS(Tbl));
		make_file_h_SUB_struct(of,jS(App));


	}

	make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_ns(of);
	of << _jF("\n} //namespace %1% \n") % m_Namespace;
	make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_root_ns(of);
	of << _jF("\n}// namespace %1% \n") % pv_domain_name->Get_cstr() ;
	make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE(of);

	of << endl;
	of << _jF("#endif //__namespace_%1%___filename_%2%_\n") % m_Namespace % m_FileName ;

	of.close();
}

void Excel_Converter::make_file_h_SUB_enum_gen_define(tofstream &of)
{
	jE eEnum = m_eDoc(jS(enum));
	if(eEnum.empty()) return;
	jIE* it = eEnum->begin();

	Print_Title(of, _T("enum형 코드 템플릿 정의"));
	of<<_T("// ENUM_TABLE(enum_tbl,help,root_ns,ns)\n");
	of<<_jF("#define for_each_%1%_%2%_ENUM(ENUM_TABLE)\\\n") % m_Namespace % m_FileName;
	jrFOR(it)
	{
		tstring help = it->GetAttr(jS(HELP));
		nSTL::replace(help , _T(",") , _T(".."));
		of<<_jF("\tENUM_TABLE(%1%,%2%,%3%,%4%)\\\n") % it->GetTagName() % help % pv_domain_name->Get_cstr() % m_Namespace;
	}
	of<<endl ;

	AddTab();

	of<< Tab() << _T("// -------------------------------------------------\n");
	of<< Tab() << _T("// FUNC(enum_eng_name,enum_value,enum_help,root_namespace, namespace,enumTag)\n");
	of<< Tab() << _T("// 주의 enum변수는 앞에 e가 자동으로 붙어서 선언됨 \n");
	of<< Tab() << _T("// -------------------------------------------------\n\n");

	it = eEnum->begin();
	jrFOR(it)
	{
		of << _jF("/* %1% */\n") % jA5(it,HELP);
		of<< _jF("#define for_each_%1%_%2%_ENUM_FIELD(ENUM_FIELD)\\\n") % m_Namespace % it->GetTagName();
		jIE* peField = it->begin();
		jrFOR(peField)
		{
			jE e = peField;
			of<<_jF("\tENUM_FIELD(%1%\t\t\t,%2%,%3%,%4%,%5%,%6%)\\\n") % peField->GetTagName() % jC5(e,value) % jC5(e,name)
				% pv_domain_name->Get_cstr() % m_Namespace % it->GetTagName();
		}
		of<<endl;
	}
	of << endl;
	DecTab();

}



void Excel_Converter::make_file_h_SUB_struct_gen_define(tofstream &of,tcstr szStruct)
{
	jE eSys = m_eDoc(szStruct);
	if(eSys.empty()) return;
	jIE* peTable  = eSys->begin();
	Print_Title(of, _T("struct 코드 템플릿 정의"));
	of<<_jF("#define for_each_%1%_%2%_%3%_STRUCT_LIST(STRUCT)\\\n") % m_Namespace % m_FileName % szStruct;
	jrFOR(peTable)
	{
		tstring help = peTable->GetAttr(jS(HELP));
		nSTL::replace(help , _T(",") , _T(".."));
		of<<_jF("\tSTRUCT(%1%,%2%,%3%,%4%)\\\n") % peTable->GetTagName() % help % pv_domain_name->Get_cstr() % m_Namespace;
	}
	of<<endl << endl;


	peTable = eSys->begin();
	AddTab();
	jrFOR(peTable)
	{
		//--------------------------------------------------------------------------
		// 코드 생성기 출력
		//--------------------------------------------------------------------------
		of<< endl;
		of<< _jF("// ------------------------------------------------------------\n");
		of<< _jF("// %1% 자신의 필드만 나열한 매크로.\n") % peTable->GetTagName();
		of<< _jF("// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\n");

		fname_t sz_for_each_field;
		jt_sprintf(sz_for_each_field,_T("for_each_%s_%s_STRUCT_FIELD"),  m_Namespace.c_str() , peTable->GetTagName());
		of<< _jF("#ifndef %1%\n") % sz_for_each_field;
		of<< _jF("#define %1%(FIELD)\\\n") % sz_for_each_field;
		jIE* peField = peTable->begin();
		vector<jE> listInherit;
		jrFOR(peField)
		{
			jIVar* pvArray = peField->GetAttrVar(jS(array_field));
			jIVar* pvRef = peField->GetAttrVar(jS(ref_field));

			bool isInherit=false;
			jIE* peInherit = peField->Find(jS(inherit));
			if(peInherit)
			{
				isInherit = peInherit->GetVar()->Get_bool();
			}

			if(isInherit)
			{
				listInherit.push_back(peField);
				continue;
			}
			tcstr data_type = jC5(peField,data_type);
			if(data_type[jt_strlen(data_type)-1] == '*')
				continue;
			tstring name = jC5(peField,name);
			nSTL::replace(name,_T(","),_T("_ "));

			jE eMax = peField->Find(jS(max),1);
			jE eEnumType = _IsEnumValue(eMax);

			if(pvArray || pvRef)
			{
				if(pvRef)
				{
					if(pvArray)
					{
						of<< _jF("\tFIELD(%1%%|30t|,%2% %|50t|,%3%_ptr_vec %|80t|, %4% ,%3%_ptr_vec_ref , %3%_ptr_vec_ref , ptr_vec)\\\n")
							% peField->GetTagName() % name % data_type % peField->GetOrder();

					}
					else
					{
						of<< _jF("\tFIELD(%1%%|30t|,%2% %|50t|,%3%_ptr %|80t|, %4% ,%3%_ptr , %3%_ptr , ptr)\\\n")
							% peField->GetTagName() % name % data_type % peField->GetOrder();

					}
				}
				else
				{	// 일반 자료형 array
					of<< _jF("\tFIELD(%1%%|30t|,%2% %|50t|,%3%_vec %|80t|, %4% ,%3%_vec_ref , %3%_vec_ref , vec)\\\n")
						% peField->GetTagName() % name % data_type % peField->GetOrder();
				}
			}
			else if(eEnumType.full())
			{
				of<< _jF("\tFIELD(%1%%|30t|,%2% %|50t|,%3% %|80t|,%4% , %5% , %6% , %7%)\\\n")
					% peField->GetTagName() % name % data_type % peField->GetOrder() % eEnumType->GetTagName()
					% eEnumType->GetTagName() % _jSimpleType(data_type) ;
			}
			else
			{
				of<< _jF("\tFIELD(%1%%|30t|,%2% %|50t|,%3% %|80t|,%4% , %5% , %6% , %7%)\\\n")
					% peField->GetTagName() % name % data_type % peField->GetOrder() % _jGetterType(data_type)
					% _jSetterType(data_type) % _jSimpleType(data_type) ;
			}
		}
		of<<endl;
		of<< _jF("#endif // %1%\n\n") % sz_for_each_field;

		{
			of<< endl;
			of<< _jF("// ------------------------------------------------------------\n");
			of<< _jF("// %1%가 상속한 테이블들의 이름을 나열한 매크로.\n") % peTable->GetTagName();
			of<< _jF("// FUNC(table)\n");
			jt_sprintf(sz_for_each_field,_T("for_each_%s_%s_InheritedTable"),  m_Namespace.c_str() , peTable->GetTagName());
			of<< _jF("#ifndef %1%\n") % sz_for_each_field;
			of<< _jF("#define %1%(FUNC)\\\n") % sz_for_each_field;
			for( size_t i=0; i<listInherit.size(); ++i)
			{
				of << _jF("\tfor_each_%1%_%2%_InheritedTable(FUNC)\\\n") % m_Namespace.c_str() % listInherit[i]->GetTagName();
				of << _jF("\tFUNC(%1%)\\\n") % listInherit[i]->GetTagName();
			}
			of<<endl;
			of<< _jF("#endif // %1%\n\n") % sz_for_each_field;
		}

		{
			of<< endl;
			of<< _jF("// ------------------------------------------------------------\n");
			of<< _jF("// %1%가 상속한 테이블들의 필드만 나열한 매크로.\n") % peTable->GetTagName();
			of<< _jF("// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\n");
			jt_sprintf(sz_for_each_field,_T("for_each_%s_%s_STRUCT_FIELD_Inherited"),  m_Namespace.c_str() , peTable->GetTagName());
			of<< _jF("#ifndef %1%\n") % sz_for_each_field;
			of<< _jF("#define %1%(FUNC)\\\n") % sz_for_each_field;
			for( size_t i=0; i<listInherit.size(); ++i)
			{
				of << _jF("\tfor_each_%1%_%2%_STRUCT_FIELD_all_member(FUNC)\\\n") %  m_Namespace.c_str() % listInherit[i]->GetTagName();
			}
			of<<endl;
			of<< _jF("#endif // %1%\n\n") % sz_for_each_field;
		}
		{
			of<< endl;
			of<< _jF("// ------------------------------------------------------------\n");
			of<< _jF("// %1%가 상속한 테이블들의 모든필드와 자신의 필드들을 포함한 매크로.\n") % peTable->GetTagName();
			of<< _jF("// FUNC(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\n");
			jt_sprintf(sz_for_each_field,_T("for_each_%s_%s_STRUCT_FIELD_all_member"),  m_Namespace.c_str() , peTable->GetTagName());
			of<< _jF("#ifndef %1%\n") % sz_for_each_field;
			of<< _jF("#define %1%(FUNC)\\\n") % sz_for_each_field;
			of << _jF("\tfor_each_%1%_%2%_STRUCT_FIELD_Inherited(FUNC)\\\n") %  m_Namespace.c_str() % peTable->GetTagName();
			of << _jF("\tfor_each_%1%_%2%_STRUCT_FIELD(FUNC)\\\n") %  m_Namespace.c_str() % peTable->GetTagName();
			of<<endl;
			of<< _jF("#endif // %1%\n\n") % sz_for_each_field;
		}


	}
	DecTab();

}

void Excel_Converter::make_file_h_SUB_gen_enum(tofstream &of)
{
	AutoTab a(this);


	jE eEnum = m_eDoc(jS(enum));
	if(eEnum.empty()) return;
	jIE* it = eEnum->begin();
	jrFOR(it)
	{
		of<< _jF("enum %1% // %2%\n") % it->GetTagName() % jA5(it,HELP);
		of<< Tab() <<_T("{\n");
		{
			AutoTab a(this);

			of<< _jF("eBEGIN_%1% = 0,\n") % it->GetTagName();

			jIE* peField = it->begin();
			jrFOR(peField)
			{
				jE e = peField;
				tstring help = jC5(e,help);
				nSTL::trim(help);
				if(help.size())
					of<<_jF("/* %1% */\n") % help ;

				of<<_jF("e%1% = %2%, // %3%\n") % peField->GetTagName() % jC5(e,value) % jC5(e,name);
			}
			of<< _jF("eEND_%1%\n") % it->GetTagName();

		}
		of<< _jF("}; // %1% \n\n\n\n") % it->GetTagName();
	}
}

bool is_baseclass(tcstr szTable)
{
	return !jt_strncmp(szTable,jS(Tbl__),5) || !jt_strncmp(szTable,jS(Sys__),5) ;
}


void Excel_Converter::make_file_h_SUB_struct(tofstream& of, tcstr szStruct)
{
	jE eSys = m_eDoc(szStruct);
	if(eSys.empty()) return;

	jIE* peTable  = eSys->begin();
	vector<jIE*> listVec;
	jrFOR(peTable)
	{
		if(!jt_strstr(peTable->GetTagName() , _T("Sys__")) ) continue;
		listVec.push_back(peTable);
	}
	for(size_t i= 0 ; i < listVec.size() ;  ++i)
	{
		listVec[i]->MovePosition(0);
	}

	peTable  = eSys->begin();
	jrFOR(peTable)
	{
		cstr szTag = peTable->GetTagName();
		wcout << szTag << endl;
		vector<jE> listInherit;
		get_Inherit_Info(listInherit, peTable);
		if(listInherit.size())
		{
			of<<_jF("struct %1% %2% /* %3% */\n") % pv_EXCEL_LIB_API->Get_cstr() % peTable->GetTagName() % jA5(peTable,HELP);
			for(size_t i=0; i<listInherit.size(); ++i)
			{
				if(i==0)
					of<<_jF("\t:%1%\n") % listInherit[i]->GetTagName();
				else
					of<<_jF("\t,%1%\n") % listInherit[i]->GetTagName();
			}
		}
		else
		{
			cstr szHELP = jA5(peTable,HELP);
			if(!szHELP)
				szHELP=jS(NULL);
			of<<_jF("struct %1% %2% /* %3% */\n") % pv_EXCEL_LIB_API->Get_cstr() % peTable->GetTagName() % szHELP;
		}

		of<<_T("{\n");

		bool isPK=false;
		AddTab();
		{
			jIE* peField = peTable->begin();
			jrFOR(peField)
			{
				jIVar* pvArray = peField->GetAttrVar(jS(array_field));
				jIVar* pvRef = peField->GetAttrVar(jS(ref_field));

				jIE* itInherit = find_Field_Inherit_Table(peField);
				if(itInherit)
				{
					of<<_jF("%1%* GetBase_%1%(){ return static_cast<%1%*>(this);}\n") % itInherit->GetTagName();
					continue;
				}

				jE e = peField;
				cstr name_eng = jC5(e,name_eng);
				cstr data_type = jC5(e,data_type);
				tstring help = jC5(e,help);
				nSTL::trim(help);
				if(help.size())
					of<<_jF("/*  %1% */\n") %help;

				fname_t varName;
				_GetMemeberName(name_eng,data_type, varName,pvArray,pvRef);

				of<<_jF("%1% %2%; // %5% min_max(%3%,%4%)\n") % data_type % varName % jC5(e,min) % jC5(e,max) % jC5(e,name) ;

				// primary key 코드 생성
				jVar db_type = e(jS(db_type));
				tcstr szPk = jt_strstr(db_type->Get_cstr() , jS(PK) );
				if(db_type.full() && szPk )
				{
					szPk+=3;
					fname_t buf;
					jt_strcpy(buf, szPk);
					TCHAR* szPkEnd = jt_strchr(buf,')');

					tstring pk_type = data_type;
					if(szPkEnd)
					{
						*szPkEnd=0;
						pk_type = buf;
					}
					isPK=true;
					of << Tab() << _jF("typedef %1% primary_key_t;\n") % pk_type;
					of << _jF("primary_key_t GetPrimaryKey() { return %1%; }\n") % varName;
					of << _jF("void SetPrimaryKey(primary_key_t id) { %1% = id; }\n") % varName;
				}
			}//jrFOR(peField)
			of<< endl;


			fname_t sz_for_each_field;
			jt_sprintf(sz_for_each_field,_T("for_each_%s_%s_STRUCT_FIELD"),  m_Namespace.c_str() , peTable->GetTagName());

			//--------------------------------------------------------------------------
			// struct 필드용 enum정의
			//--------------------------------------------------------------------------
			if(!pv_IsGenerateFullCode->Get_bool())
				of<< Tab() << _T("//코드생성시 콘솔변수 IsGenerateFullCode=true이면 #define된 축약코드의 전체를 볼수 있읍니다.\n") ;

			of << _jF("enum enum%1%\n") % peTable->GetTagName();
			of << Tab() << _T("{\n");
			AddTab();
			{
				of << Tab() << _T("EField_BEGIN,\n");
				if(pv_IsGenerateFullCode->Get_bool())
				{
					peField = peTable->begin();
					jrFOR(peField)
					{
						of << _jF("eF_%1%=%2%,\n") % peField->GetTagName() % peField->GetOrder();
					}
				}
				else
				{
					of<<Tab() << _T("#ifdef jEXCEL_STRUCT_ENUM_GEN\n");
					of<< _jF("\t%1%(jEXCEL_STRUCT_ENUM_GEN)\n") % sz_for_each_field;
					of<<Tab() << _T("#endif //jEXCEL_STRUCT_ENUM_GEN\n");
				}
				of << Tab() << _T("EField_END\n");
			}
			DecTab();
			of << Tab() << _T("};\n");
			of << _jF("enum { eSTRUCT_COUNT =  %1% };\n") % (peTable->size()-listInherit.size()) ;
			if(listInherit.size())
			{
				of << _jF("static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT\n");
				for(size_t i=0; i< listInherit.size(); ++i)
				{
					of << _jF("\t + %1%::Get_STRUCT_COUNT()\n") % listInherit[i]->GetTagName();
				}
				of << _jF("; };\n\n") ;
			}
			else
			{
				of << _jF("static size_t Get_STRUCT_COUNT(){ return eSTRUCT_COUNT;} \n");
			}

			of << _jFF("#ifdef jEXCEL_TABLE_COMMON_CODE_H_%1%") % peTable->GetTagName();
			of << _jFF("\tjEXCEL_TABLE_COMMON_CODE_H_%1%();") % peTable->GetTagName();
			of << _jFF("#endif //jEXCEL_TABLE_COMMON_CODE_H_%1%\n\n") % peTable->GetTagName();

			begin_ServerSideCode(of);
			{
				of << Tab() << _T("#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN\n");
				//--------------------------------------------------------------------------
				// getter setter 출력정의
				if(pv_IsGenerateFullCode->Get_bool())
				{
					peField = peTable->begin();
					jrFOR(peField)
					{
						if(nInherit::find_Field_Inherit_Table(peField))
						{
							continue;
						}
						of << _jF("%1% Get_%2%();\n") % _jGetterType(jC5(peField,data_type)) % peField->GetTagName();
						of << _jF("void Set_%2%(%1%);\n") % _jSetterType(jC5(peField,data_type)) % peField->GetTagName();
					}
				}
				else
				{
					of<< _jF("\t%1%(jEXCEL_STRUCT_GETTER_SETTER_GEN)\n") % sz_for_each_field;
				}

				of << Tab() << _T("#endif //jEXCEL_STRUCT_GETTER_SETTER_GEN\n");
				of << endl;

				if(pv_IsGenerateFullCode->Get_bool())
				{
					of<<Tab() << _T("void ReadCSV(IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t &index,IN bool isCheck=true);\n") ;
					of<<Tab() << _T("void DebugPrint();\n");
				}
				else
				{
					of<<Tab() << _T("#ifdef jEXCEL_STRUCT_COMMON_CODE\n");
					of<<_jF("\tjEXCEL_STRUCT_COMMON_CODE(%1%)\n") % peTable->GetTagName();
					of<<Tab() << _T("#endif // jEXCEL_STRUCT_COMMON_CODE\n");
				}
				of << endl;
			}
			end_ServerSideCode(of);
		}
		DecTab();
		of<<_jF("}; // struct %1%\n") % peTable->GetTagName();
		of << _jF("enum { eSTRUCT_SIZE_%1% = sizeof(%1%) };\n") % peTable->GetTagName();
		of << endl;

		if(peTable->GetParent()->IsName(jS(Sys)))
		{
			of << _jFF("struct CSV_%1% : public nMech::nUtil::jCSV_File<%1%>") % peTable->GetTagName();
			of << _jFF("{");
			of << _jFF("	virtual ~CSV_%1%(){}") % peTable->GetTagName();
			vector<jIE*> out_INDEX;
			excel_util::get_INDEX_field(peTable,out_INDEX);
			size_t i=0;
			for(i=0; i< out_INDEX.size(); ++i)
			{
				jIE* peINDEX = out_INDEX[i];
				of << _jFF("	jLIST_TYPEDEF_vector_typedef(%1%*,vector_%2%);")% peTable->GetTagName() % peINDEX->GetTagName();
				of << _jFF("	jLIST_TYPEDEF_map(%1%, vector_%2%_t, m_INDEX_%2%);") %jC5(peINDEX,data_type) % peINDEX->GetTagName();
				of << _jFF("	void init_INDEX_%1%()") % peINDEX->GetTagName();
				of << _jFF("	{");
				of << _jFF("		for(size_t i=0; i<size() ; ++i)");
				of << _jFF("		{");
				of << _jFF("			%1%* p = at(i);") % peTable->GetTagName();
				of << _jFF("			m_INDEX_%1%[p->Get_%1%()].push_back(p);") % peINDEX->GetTagName();
				of << _jFF("		}");
				of << _jFF("	}");
			}
			{
				AutoTab a(this);
				of << _jFF("virtual bool Load(tcstr _szFile)");
				of << _jFF("{");
				of << _jFF("	bool isOk = nMech::nUtil::jCSV_File<%1%>::Load(_szFile);") % peTable->GetTagName();
				of << _jFF("	if(!isOk) return false;");
				for(i=0; i< out_INDEX.size(); ++i)
				{
					jIE* peINDEX = out_INDEX[i];
					of << _jFF("	init_INDEX_%1%();") % peINDEX->GetTagName();
				}
				of << _jFF("	return true;");
				of << _jFF("}");

			}


			of << _jFF("};");
			of <<_jFF("extern %2% CSV_%1% g_%1%;\n\n") % peTable->GetTagName() % pv_EXCEL_LIB_API->Get_cstr();
		}


		bool isBase = is_baseclass(peTable->GetTagName()) ;
		if(!isPK && !jt_strcmp(szStruct,jS(Tbl)) && !listInherit.size() && !isBase )
		{
			jWARN(_T("%s 테이블에서 PrimaryKey(PK)가 지정안되어 있음"),peTable->GetTagName());
		}


	}//jrFOR(peTable)
	of << _jFF("#ifdef jEXCEL_TABLE_COMMON_CODE_H_%1%") % szStruct;
	of << _jFF("\tfor_each_%1%_%2%_%3%_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_H_%3%);") % m_Namespace % m_FileName % szStruct;
	of << _jFF("#endif //jEXCEL_TABLE_COMMON_CODE_H_%1%\n\n") % szStruct;


}

void Excel_Converter::make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_ns(tofstream& of)
{

	jE eEnum = m_eDoc(jS(enum));
	if(eEnum.empty()) return;
	jIE* it = eEnum->begin();
	of<<endl;

	begin_ServerSideCode(of);

	//sql bind코드를 위한부분
	if(m_eUse.size())
	{
		for_each_STRUCT_LIST(of, jS(jEXCEL_SQL_BIND_FUNC_DECL) ,jS(Tbl));
		of <<endl;
	}

	jrFOR(it)
	{
		of<<_jF("extern %1% %2%::jEnumString g_ES_%3%[];\n") 
			% pv_EXCEL_LIB_API->Get_cstr() % pv_net_core_ns->Get_cstr() % it->GetTagName();

		//of<<_jF()

	}
	end_ServerSideCode(of);

}

void Excel_Converter::make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_root_ns(tofstream& of)
{

}

void Excel_Converter::make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_struct(tofstream& of, jE table)
{
	if(table.empty()) return;
#if 1
	of<<_jF("for_each_%1%_%2%_%3%_STRUCT_LIST(jEXCEL_struct_header_default_function);\n") % m_Namespace % m_FileName % table->GetTagName();
#else
	jIE* it = table->begin();
	jrFOR(it)
	{
		of<<_jF("extern %1% void DebugPrint(acstr szName,%2%::%3%::%4% &val);\n")
			% pv_EXCEL_LIB_API->Get_cstr() % pv_domain_name->Get_cstr() % m_Namespace % it->GetTagName();
	}
#endif
}

void Excel_Converter::make_file_h_SUB_gen_jEXCEL_ENUM_LIST_COMMON_CODE(tofstream& of)
{
	if(m_eEnum.empty()) return;
	jIE* it = m_eEnum->begin();
	of<<endl;
	if(pv_IsGenerateFullCode->Get_bool())
	{
		jrFOR(it)
		{
			tstring ns = tstring(pv_domain_name->Get_cstr()) + jS(::) +  m_Namespace ;
			of<< _jF("%2% FromString(tcstr val,%2%)\n")
				% ns % it->GetTagName();
			of<< _jT("{\n");
			AddTab();
			of<< _jF("jEnumString* pES = jEnumString::Get(g_ES_%2%,jw_atoi(val.c_str()));\n") % ns % it->GetTagName();
			of<< _jF("return pES ? (%2%)pES->m_id : eBEGIN_%2%; \n") % ns % it->GetTagName();
			DecTab();
			of<<_jT("}\n");
		}
	}
	else
	{
		begin_DEFINE(of, jS(jEXCEL_ENUM_StringToVal));
		of<<_jF("for_each_%1%_%2%_ENUM(jEXCEL_ENUM_StringToVal);\n") % m_Namespace % m_FileName;
		end_DEFINE(of, jS(jEXCEL_ENUM_StringToVal));
	}
	of<<endl;

}

void Excel_Converter::make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE(tofstream& of)
{
	of<<endl;
	begin_ServerSideCode(of);

	of<<_jF("namespace %1%{\n") % pv_net_core_ns->Get_cstr();
	AddTab();

	tstring ns = tstring(pv_domain_name->Get_cstr()) + jS(::) +  m_Namespace ;
	of<<_jF("using namespace %1%;") % ns;

	make_file_h_SUB_gen_jEXCEL_ENUM_LIST_COMMON_CODE(of);

	of<< endl;

	begin_DEFINE(of, jS(jEXCEL_struct_header_default_function));
	make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_struct(of, m_eSys);
	make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_struct(of, m_eUse);
	make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_struct(of, m_eApp);
	end_DEFINE(of, jS(jEXCEL_struct_header_default_function));

	DecTab();
	of<<_jF("} // %1%\n") % pv_net_core_ns->Get_cstr();

	end_ServerSideCode(of);

	make_file_h_SUB_gen_Squirrel_Bind_code(of);

	of<<endl;

}


