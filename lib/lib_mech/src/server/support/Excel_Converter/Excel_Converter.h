/* file : Excel_Converter.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-24 17:33:54
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __Excel_Converter_header__
#define __Excel_Converter_header__
#pragma once

#include "base/jxVar.h"

using namespace nMech::nXML;

#define jSEP _T(",@#,") 
const int jCURR_VERSION = 1013;
#define TABLE_NAME_IDX 1
#define TABLE_HELP_IDX 2


#define _jFF(X) endl << Tab()<< boost::tformat(_T(X))
#define _jTT(X) endl << Tab()<< _T(X)

#define _jF(X) Tab()<< boost::tformat(_T(X))
#define _jT(X) Tab()<< _T(X)

#define _jNF(X) TAB_TIC << boost::tformat(_T(X))

#define jC5(var,name) var->Find(jS(name))->Get_cstr()
#define jA5(var,name) var->GetAttr(jS(name))

//�׸��� �þ�� �Ʒ��� X(???)�� �߰��ϰ� void _parse_???(nXML::jE e, vector<std::tstring>& o)�� �߰��Ͻÿ�
#define for_each_parse(X) X(enum) X(Sys) X(Tbl) X(App)



#define jCV_DEF(VAR,VAL,HELP) jIVar *pv_##VAR = jCV(Excel_Converter, VAR , VAL , 0,HELP);
#define jCV_DECL(VAR,VAL,HELP) extern jIVar * pv_##VAR;

#define for_each_jCV_my(F)\
	F(header_file,_T("db_type.h"),"h, cpp ���ϻ����� �⺻������ ��Ŭ����� �ش����ϸ�")\
	F(domain_name,_T("nMech"),"������ C++�ڵ�鿡 ���� �⺻ ���ӽ����̽�")\
	F(net_core_ns,_T("nExcelUtil"),"������ ��Ʈ�� ���̺귯�� ���ӽ����̽�")\
	F(SERVER_SIDE_CODE,_T("jEXCEL_SERVER_SIDE_CODE"), "Ŭ���̾�Ʈ�ʿ����� �� ���ڵ忡 ���� define��")\
	F(EXCEL_LIB_API,_T("jEXCEL_LIB_API"), "���Ӽ��� ���� DLL�� ���� �±�")\
	F(IsAddSimpleTypeTag,1,"����ü�� �ɹ����� ������ data type�� simpleǥ�⸦ �ڿ� ������ ����")\
	F(IsGenerateFullCode,false,"interface/net/Excel_code_util.h�� ��ũ�λ����ϰ� �ڵ带 ���� ����")\
	F(IsUse_SQ_BindCode,true,"squirrel bind code�� �������� ������")\
	F(SysData_Sample_Count,30,"sys table ���ð��� ������, [Sys_Name]_sample.txt�� ��µ�")\
	F(excel_enum_file_name,_T("excel_enum"),"enum table xml name WITHOUT ext")\

for_each_jCV_my(jCV_DECL);

extern nXML::jE g_Cfg;
extern jE g_eTYPE_INFO;
extern jE g_eTYPE_INFO_NS;
jE Get_TYPE_INFO(tcstr szType);
jLIST_TYPEDEF_vector_header(jIE* , g_new_registed_type);
extern bool g_isSave_AppDoc;
extern bool g_isGen_table_type;


inline void Debug_Print(std::vector<std::tstring> & out)
{
	for(size_t i=0 ; i< out.size() ; ++i)
		jt_printf(_T("%s\n"), out[i].c_str());

}
struct jCodeGenerator
{
	tstring m_sTabBuf;
	void ClearTab(){m_sTabBuf.clear();}
	void AddTab(){m_sTabBuf+=_T("\t");}
	void DecTab(){m_sTabBuf.erase(m_sTabBuf.begin());}
	tstring& Tab(){ return m_sTabBuf; }
	struct AutoTab
	{
		jCodeGenerator* pThis;
		AutoTab(jCodeGenerator* p): pThis(p)		{			pThis->AddTab();		}
		~AutoTab()		{			pThis->DecTab();		}
	};

	void begin_DEFINE(tofstream& of,cstr sz,bool is_NOTDEF=false)	
	{		
		if(is_NOTDEF)		{of<<_jF("#ifndef %1%\n") % sz;	AddTab();	}
		else						{of<<_jF("#ifdef %1%\n") % sz;	AddTab();	}
	}
	void end_DEFINE(tofstream& of,cstr sz)	
	{		
		DecTab();of<<_jF("#endif //%1%\n\n") % sz;	
	}
	void Print_Title(tofstream& of,  tcstr sz)
	{
		of<< Tab() << _T("// -------------------------------------------------\n");
		of<< Tab() << _T("// ") << sz << endl;
		of<< Tab() << _T("// -------------------------------------------------\n");
	}


};

class Excel_Converter : public jCodeGenerator
{
public:
	//--------------------------------------------------------------------------
	// �ɹ����� ����
	//--------------------------------------------------------------------------
	tstring m_Namespace
		,m_save_file_path
		,m_FileName
		;

	jLIST_TYPEDEF_vector(std::tstring, m_lineList);
	m_lineList_it m_it;
	nXML::jE m_eDoc;//�Ľ��� ����Ÿ �����.
	jIE* m_peDocEbum;
	jE m_eSys;
	jE m_eUse;
	jE m_eApp;
	jE m_eEnum;

	jLIST_TYPEDEF_set(jIE*,m_Array_Ref);

private:

	//--------------------------------------------------------------------------
	// �ɹ��Լ� ����
	//--------------------------------------------------------------------------
public:

	~Excel_Converter();

	Excel_Converter(std::tstring & buf);
	void _init(std::tstring &n, std::tstring &s,std::tstring &f);
	void ParseAll()
	{
		make_to_xml();

		m_eSys = m_eDoc(jS(Sys));
		m_eUse = m_eDoc(jS(Tbl));
		m_eApp = m_eDoc(jS(App));
		m_eEnum = m_eDoc(jS(enum));

		ClearTab();
		make_file_h();

		ClearTab();
		make_file_cpp();

		make_file_cshap();
		make_file_proto();
		make_file_proto_cshap_contract_code();
		make_file_proto_cshap_contract_code_help_cs();


		make_file_sys_table_sample();

		make_file_sql_insert();
		make_file_sql_sample_data();
		make_file_sql_select();
		make_file_sql_create();
		make_file_sql_update();
		WinExec("__merge_create_sql.bat",SW_HIDE);
	}

private:
	//--------------------------------------------------------------------------
	// �Ľ� ��ƿ
	//--------------------------------------------------------------------------

	void make_to_xml();
	void make_to_xml_SUB_add_table_to_xml(nXML::jE e, vector<std::tstring>& o);

	void make_file_h();

	void make_file_h_SUB_enum_gen_define(tofstream &of);
	void make_file_h_SUB_struct_gen_define(tofstream &of,tcstr szStruct);

	void make_file_h_SUB_gen_enum(tofstream &of);
	void make_file_h_SUB_struct(tofstream& of, tcstr szStrcut);
	void make_file_h_SUB_gen_jEXCEL_ENUM_LIST_COMMON_CODE(tofstream &of);
	void make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_ns(tofstream& of);
	void make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_root_ns(tofstream& of);
	void make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE(tofstream& of);
	void make_file_h_SUB_gen_jEXCEL_STRUCT_LIST_COMMON_CODE_struct(tofstream& of, jE table);
	void make_file_cpp();
	void make_file_cpp_SUB_gen_enum(tofstream & of);
	void make_file_cpp_SUB_gen_struct_set_get(tofstream & of, jE table);
	void make_file_cpp_SUB_gen_struct_jDebugPrint(tofstream& of,jE eStruct);
	void make_file_cpp_SUB_gen_struct_ReadCSV(tofstream & of, jE table);
	void make_file_cpp_SUB_gen_struct_nDebug_jDebugPrint(tofstream & of);

	void make_file_proto();

	void make_file_proto_cshap_contract_code( );
	void make_file_proto_cshap_contract_code_help_cs( );

	void make_file_proto_struct(tofstream &of,cstr szStruct);
	jLIST_TYPEDEF_set_typedef(tstring , cshap_contract_type_list);
	void _make_file_proto_cshap_contract_code_STRUCT( tofstream & of, cstr szStruct,cshap_contract_type_list_t& type_list);
	void _make_file_proto_cshap_contract_code_help( tofstream & of, cstr szStruct);
	void _make_file_proto_cshap_contract_code_FIELD( IN OUT  int &idx ,jIE* peTable, tofstream & of );

	void _make_file_proto_struct_field( IN OUT int& idx,jIE* peTable, tofstream & of );
	void make_file_cshap();
	void make_file_cshap_using(tofstream &of,jE e);
	void make_file_cshap_enum(tofstream &of);
	void make_file_cshap_struct(tofstream &of,cstr szSys);

	void make_file_cshap_CSV_class(tofstream &of);

	void make_file_sys_table_sample();
	void make_file_sys_table_sample_SUB_gen_line(int i, nXML::jE e , TCHAR outBuffer[2048]);
	void make_file_sql_create();

	void _make_file_sql_create_for_BaseTable( jIE* peField, tofstream &of );
	void make_file_sql_insert();
	void make_file_sql_sample_data();
	void make_file_sql_select();
	void make_file_sql_update();



	//--------------------------------------------------------------------------
	//sq bind ����
	//--------------------------------------------------------------------------
	void make_file_h_SUB_gen_Squirrel_Bind_code(tofstream & of);
	void make_file_cpp_SUB_gen_Squirrel_Bind_code(tofstream & of);
	void make_file_cpp_SUB_gen_sq_bind_Table_declear_jCSV_File(tofstream & of, nXML::jE eTable);
	void make_file_cpp_SUB_gen_sq_bind_Table(tofstream & of, nXML::jE eTable);
	void make_file_cpp_SUB_gen_sq_bind_EnumField(tofstream & of);



	//--------------------------------------------------------------------------
	// ��ƿ �ڵ�
	//--------------------------------------------------------------------------
	void for_each_ENUM_LIST(tofstream& of, tcstr szDEFINE)
	{
		of<<_jFF("for_each_%1%_%2%_ENUM(%3%);") % m_Namespace % m_FileName %szDEFINE;
	}
	void for_each_STRUCT_LIST(tofstream& of, tcstr szDEFINE,cstr szTag)
	{
		of<< _jFF("for_each_%1%_%2%_%4%_STRUCT_LIST(%3%);") % m_Namespace % m_FileName % szDEFINE% szTag ;
	}
	void for_each_ENUM_FILELD(tofstream& of, tcstr szEnumName, tcstr szDEFINE)
	{
		of<<_jFF("for_each_%1%_%2%_ENUM_FIELD(%3%);") % m_Namespace % szEnumName %szDEFINE;

	}
	void for_each_STRUCT_FILELD_all_member(tofstream& of, tcstr szTableName, tcstr szDEFINE)
	{
		of<< _jFF("for_each_%1%_%2%_STRUCT_FIELD_all_member(%3%);") % m_Namespace % szTableName % szDEFINE;
	}

	void for_each_STRUCT_FILELD(tofstream& of, tcstr szTableName, tcstr szDEFINE)
	{
		of<< _jFF("for_each_%1%_%2%_STRUCT_FIELD(%3%);") % m_Namespace % szTableName % szDEFINE;
	}

	void begin_ServerSideCode(tofstream& of){begin_DEFINE(of,pv_SERVER_SIDE_CODE->Get_cstr());}
	void end_ServerSideCode(tofstream& of){end_DEFINE(of,pv_SERVER_SIDE_CODE->Get_cstr());}

	cstr _jGetterType(cstr sz);
	cstr _jSetterType(cstr sz);
	cstr _jSimpleType(cstr sz);
	jE _IsEnumValue(jE max);

	//--------------------------------------------------------------------------
	//��ƿ �Լ���
	//--------------------------------------------------------------------------

	// �ش� �ʵ��̸����� �ɹ� �������� ����.
	cstr _GetMemeberName(tcstr eng_name,tcstr data_type, fname_t buf,bool isArray, bool isRef);
	// 
	void _print_set_get_ref_array_Field(tofstream &of,tstring data_type, tstring table_name , tstring eng_name,tstring varName,tstring sRef=_T(""));

	typedef void print_help_tstring_ft(std::tofstream &of, tcstr szKey, tcstr szMax);
	void _print_help_tostring(tofstream &of,print_help_tstring_ft *pRefFunc,print_help_tstring_ft *pNotRefFunc);

public:
};
extern Excel_Converter* g_Excel_Converter;

namespace nInherit
{
	jLIST_TYPEDEF_map_header(tstring,jID*,g_LoadedXml);

	jIE* find_Field_Inherit_Table(jIE* peField);

	// �ش� ���̺��� ��ӹ޴� �ʵ������� ���� ��� ���̺� �����͸� ã�� ����.
	bool get_Inherit_Info(vector<nXML::jE> &listInherit, jIE* peTable);
	bool is_inherit_node(jIE* it);
	void get_inherit_list(std::vector<jIE*>& out, jIE* pE);
	jIE* get_name_field_from_inherit_class( jIE* peTable );// ���̺��� name�̶�� �ʵ尡 ������ �ش� �����͸� ����. ������̺��θ� �����ؼ� ã�´�.

}
using namespace nInherit;

namespace excel_util
{
	cstr get_cshap_type(cstr szType);
	cstr get_proto_type(cstr szType);

	void get_NAME_field(IN jIE* peTable, OUT vector<jIE*>& out);// "name" �ʵ� ã��.
	void get_INDEX_field(IN jIE* peTable, OUT vector<jIE*>& out);// Sys, Tbl��� db_type�� "INDEX"�� ������ �� �ʵ����� �����Ѵ�.
}
using namespace excel_util;


#endif // __Excel_Converter_header__
