/* file : Excel_code_util.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-28 11:17:50
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __Excel_code_util_header__
#define __Excel_code_util_header__
#pragma once
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include "header/ToString_base.h"
#include "header/uString_stl.h"
#include "db_uid_type.h"
#include "header/jCSV_File.h"

#ifndef EXCEL_CSV_STRING_VECTOR
#define EXCEL_CSV_STRING_VECTOR std::vector<std::tstring>
#define excel_wcstr	tcstr
#define EXCEL_WSTRING_SPLIT_CODE vector<tstring> out;nString::jSplit(sz,_T(";"),out);
#define nExcelUtil nMech
#define jAPP_NAME test_Excel

#endif


#define DECLARE_ENUM_TYPE_csv(TYPE)
#define PROTOS_ENUM_TYPE_csv(TYPE)


/*
DECLARE_INSTANCE_TYPE_COMPLAX_csv 와 PROTOS_ENUM_TYPE_COMPLAX_csv는 쌍으로 사용.
CSV 관련 EXCEL 필드에서 복합형( vector<?> ) 에 사용.
*/
#define DECLARE_INSTANCE_TYPE_COMPLAX_csv(TYPE)
#define PROTOS_ENUM_TYPE_COMPLAX_csv(TYPE)

#define jEXCEL_STRUCT_ENUM_GEN(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
	eF_##eng_name=field_order,

#define jEXCEL_STRUCT_GETTER_SETTER_GEN(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
	getter_type Get_##eng_name(); void Set_##eng_name(setter_type data);

#define jEXCEL_ENUM_STRING_CPP_CODE(enum_eng_name,enum_value,enum_help,root_namespace, namespace12,enumTag)\
	{ e##enum_eng_name , jS(enum_eng_name) , jS(enum_help) }, 


#define jEXCEL_STRUCT_COMMON_CODE(STRUCT_NAME)\
	/*STRUCT_NAME(){ CLASS_CLS();}*/\
	tcstr ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t &index,IN bool isCheck=true);\
	void DebugPrint();\



#define ENUM_FROMSTRING12(ENUM_NAME,VAL,HELP,root_ns,ns,ENUM_TABLE)	if(jt_strcmp(jS(ENUM_NAME),sz)==0) return root_ns::ns::e##ENUM_NAME;
#define ENUM_TOSTRING12(ENUM_NAME,VAL,HELP,root_ns,ns,ENUM_TABLE)	if(eType==root_ns::ns::e##ENUM_NAME) return jS(ENUM_NAME);
#define jEXCEL_ENUM_StringToVal(enum_tbl,help,root_ns,ns)\
	inline enum_tbl FromString(enum_tbl *eVal,excel_wcstr  sz)\
	{_jJOIN_5(for_each_,ns,_,enum_tbl,_ENUM_FIELD)(ENUM_FROMSTRING12);return eBEGIN_##enum_tbl;}\
	inline enum_tbl FromString(enum_tbl *eVal,std::tstring& sz){return FromString(eVal,sz.c_str());}\
	inline tcstr ToString(root_ns::ns::enum_tbl eType,tname1024_t szBuf=0)\
	{_jJOIN_5(for_each_,ns,_,enum_tbl,_ENUM_FIELD)(ENUM_TOSTRING12);	return jS(NULL);	}\
	inline void jDebugPrint(tcstr szName,root_ns::ns::enum_tbl val){jLOG(_T("\t%s : %s[=%d]"), szName, ToString(val), val);}\



#if 1
#define jEXCEL_struct_header_default_function(table_name,help,root_ns,ns)\
	inline void jDebugPrint(tcstr szName,root_ns::ns::table_name& val)\
	{\
		jLOG(_T("\t%s : %s"), szName, jS(table_name));\
	}\
	inline void jDebugPrint(tcstr szName,std::vector<root_ns::ns::table_name>& val)\
	{\
	jLOG(_T("\t%s : %s.size()=%d"), szName, jS(table_name),val.size());\
	}\

#endif

#define jEXCEL_STRUCT_FIELD_DebugPrint(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\
 	ToString(Get_##eng_name(),szBuf); jLOG(_T("\t") jS(eng_name) _T(" = %s"), szBuf);

#define print_ENUM23984(ns,enum_tbl)	inline void print_##enum_tbl(){jEnumString::DebugPrint(ns::g_ES_##enum_tbl);}


//ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define jEXCEL_SQ_DECLARE_ENUM_TYPE(enum_tbl,help,root_ns,ns)
#define jEXCEL_SQ_DECLARE_ENUM_TYPE_PROTO(enum_tbl,help,root_ns,ns)
#define jEXCEL_SQ_DECLARE_INSTANCE_TYPE(struct_name,help,domain,ns)
#define jEXCEL_SQ_TABLE_FILED_BIND(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
#define jEXCEL_SQ_TABLE_FUNC_BIND(table)
#define jEXCEL_SQ_bind_EnumField_BEGIN(enum_tbl,help,root_ns,ns)
#define jEXCEL_SQ_bind_EnumField(enum_eng_name,enum_value,enum_help,root_namespace, namespace12,enum_tbl)



#if 0
// .h생성시 엑셀 데이타의 네임스페이스 내부에서 구조체 리스토로 생성할 코드
#define jEXCEL_STRUCT_LIST_COMMON_CODE_ns(STRUCT_LIST,DLL_API,root_ns,ns)\


// .h생성시 엑셀 데이타의 root namespace (=TR_excel_data) 안에서 구조체리스트로 생성할 코드
#define jEXCEL_STRUCT_LIST_COMMON_CODE_root_ns(STRUCT_LIST,DLL_API,root_ns,ns)\


// .h생성시 엑셀 데이타의 root namespace 밖에서 구조체리스트로 생성할 코드
#define jEXCEL_STRUCT_LIST_COMMON_CODE(STRUCT_LIST,DLL_API,root_ns,ns)\

#endif


//--------------------------------------------------------------------------
// excel sql bind code
//--------------------------------------------------------------------------

#define jEXCEL_SQL_TYPE_int64 SQL_C_SBIGINT
#define jEXCEL_SQL_TYPE_uint64 SQL_C_UBIGINT

#define jEXCEL_SQL_TYPE_int32 SQL_C_SLONG
#define jEXCEL_SQL_TYPE_uint32 SQL_C_ULONG

#define jEXCEL_SQL_TYPE_int16 SQL_C_SSHORT
#define jEXCEL_SQL_TYPE_uint16 SQL_C_USHORT

#define jEXCEL_SQL_TYPE_int8 SQL_C_STINYINT
#define jEXCEL_SQL_TYPE_uint8 SQL_C_UTINYINT

//#define jEXCEL_SQL_TYPE_undefined_t SQL_INTEGER
#define jEXCEL_SQL_TYPE_SYSTEMTIME SQL_C_TYPE_TIMESTAMP
#define jEXCEL_SQL_TYPE_bool SQL_BIT 
//SQL_BINARY

#define jEXCEL_SQL_TYPE_aname32_t SQL_C_CHAR
#define jEXCEL_SQL_TYPE_aname64_t SQL_C_CHAR
#define jEXCEL_SQL_TYPE_aname128_t SQL_C_CHAR
#define jEXCEL_SQL_TYPE_aname256_t SQL_C_CHAR
#define jEXCEL_SQL_TYPE_aname1024_t SQL_C_CHAR
#define jEXCEL_SQL_TYPE_aname2048_t SQL_C_CHAR

#define jEXCEL_SQL_TYPE_wname32_t SQL_C_WCHAR
#define jEXCEL_SQL_TYPE_wname64_t SQL_C_WCHAR
#define jEXCEL_SQL_TYPE_wname128_t SQL_C_WCHAR
#define jEXCEL_SQL_TYPE_wname256_t SQL_C_WCHAR
#define jEXCEL_SQL_TYPE_wname1024_t SQL_C_WCHAR
#define jEXCEL_SQL_TYPE_wname2048_t SQL_C_WCHAR


#define jEXCEL_SQLHSTMT void* 

#if 0
#define jEXCEL_SQL_BIND_FIELD(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\
	SQLBindCol(hS, field_order+1,jEXCEL_SQL_TYPE_##data_type,&p->_jJOIN_4(m_,eng_name,_,data_type_simple)\
					,sizeof(p->_jJOIN_4(m_,eng_name,_,data_type_simple)),	&data_len[field_order]);

#define jEXCEL_SQL_BIND_FUNC_DECL(STRUCT_NAME,help,ns1,ns2)	void jBindColData(jEXCEL_SQLHSTMT hS, STRUCT_NAME* p);

#define jEXCEL_SQL_BIND_FUNC_DEFINE(STRUCT_NAME,help,ns1,ns2) void jBindColData(jEXCEL_SQLHSTMT hS, STRUCT_NAME* p)\
	{static SQLLEN data_len[STRUCT_NAME::eSTRUCT_COUNT]; _jJOIN_5(for_each_,ns2,_,STRUCT_NAME,_STRUCT_FIELD_all_member)(jEXCEL_SQL_BIND_FIELD);}

#else
#define jEXCEL_SQL_BIND_FIELD(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)
#define jEXCEL_SQL_BIND_FUNC_DECL(STRUCT_NAME,help,ns1,ns2)	
#define jEXCEL_SQL_BIND_FUNC_DEFINE(STRUCT_NAME,help,ns1,ns2) 
#endif

namespace nMech
{
	//inline void jSetter(std::wstring dest, wcstr src){ dest = src;};
	inline void jSetter(std::string dest, acstr src){ dest = src;};

	inline void jSetter(CHAR* dest, acstr src,int itot){ja_strncpy(dest, src,itot-1);dest[itot-1]=0;}
	//inline void jSetter(WCHAR* dest, wcstr src,int itot){jw_strncpy(dest, src,itot-1);dest[itot-1]=0;}

	inline acstr jGetter(std::string& v){ return v.c_str();}
	//inline wcstr jGetter(std::wstring& v){ return v.c_str();}

	//#define nExcelUtil_StringConverter nUNI::scb1024_t
	struct nUNI_scb1024_t
	{
		tstring &sz;
		nUNI_scb1024_t(tstring& s):sz(s){}
		tcstr getT(){ return sz.c_str();}
		tcstr getA(){ return sz.c_str();}
	};
	#define nExcelUtil_StringConverter nUNI_scb1024_t


	inline void jSetter(aname32_t dest, acstr src){ja_strncpy(dest, src,31);dest[31-1]=0;}
	//inline void jSetter(wname32_t dest, wcstr src){jw_strncpy(dest, src,31);dest[31-1]=0;}
}


#define jCSV(Table) g_##Table

#define jEXCEL_DECL_csv_namespace(Table,Name,ns1,ns2) using namespace ns1::ns2;



namespace nMech
{
	namespace nEXCEL
	{
		typedef boost::function<void (excel_wcstr szData)> Regist_PostLoad_ft;
		struct Excel_PostLoader
		{
			struct PostLoadObj
			{
				PostLoadObj(Regist_PostLoad_ft f,tstring d, tstring h): func(f),data(d),help(h){}
				PostLoadObj(){}
				Regist_PostLoad_ft func;
				tstring data;
				tstring help;
			};

			jLIST_TYPEDEF_list(PostLoadObj,m_Regist_PostLoad);

			void Run()
			{
				m_Regist_PostLoad_it it = m_Regist_PostLoad.begin(), ie = m_Regist_PostLoad.end();
				try
				{
					for(;it!=ie; ++it)
					{
						it->func(it->data.c_str());
					}
				}
				catch (tstring e)
				{
					jERROR("load fail(%s) : %s",jT(it->help) ,e.c_str() );
				}
				catch (...)
				{
					jERROR("load fail unkown (%s) , data=%s",it->help.c_str() ,jT(it->data));
				}
			}
			void insert(Regist_PostLoad_ft func,tcstr szData,tcstr szHelp,void* v=0)
			{
				m_Regist_PostLoad.push_back(PostLoadObj(func,szData,szHelp));
			}
		};
		extern Excel_PostLoader g_Excel_PostLoader; 
		// g_Excel_PostLoader는 csv loader쪽 모듈에서 반드시 정의 해주어야 한다.
		// namespace nMech{namespace nEXCEL{Excel_PostLoader g_Excel_PostLoader;}}

	}//namespace nEXCEL
}//namespace nMech

// Sys_ 테이블에 대한 header용 공통코드
#define jEXCEL_TABLE_COMMON_CODE_H_Sys(sys_table,help,ns1,ns2)\
	typedef sys_table* sys_table##_ptr;\
	typedef std::vector<sys_table##_ptr> sys_table##_ptr_vec;\
	typedef sys_table##_ptr_vec& sys_table##_ptr_vec_ref;\
	void GetTable_FromeString(OUT sys_table##_ptr* v,IN excel_wcstr sz);\
	void GetTable_FromeString(OUT sys_table##_ptr_vec* v,IN excel_wcstr sz, IN int iArrayMax);\

#if 0
template<typename sys_table>
void _GetTable_FromeString(OUT sys_table** v,IN excel_wcstr sz, nUtil::jCSV_File<sys_table>& table,tcstr szTable)
{
	(*v)=0;
	if(!jt_strcmp(sz,_T("NULL") )  || !jt_strcmp(sz, _T("0") ) )	{			(*v)=0; 		return; 	}
	if(!table.size()) 	{		throw tstring(szTable) +_T(" > table.size() ==0 ");	}
	
	if(sz[0]>='0' && sz[0]<='9'){ (*v) = table.Index(jt_atoi(sz)); }
	else						{	(*v) = table.find(jT(sz));	}
	if(!(*v)){fname_t szBuf;	jt_sprintf(szBuf, _T("%s>  %s data= %s , not found !!! "),jFUNC,szTable, jT(sz) );		throw tstring(szBuf);	}
}
template<typename sys_table>
void _Excel_PostLoader_registe(sys_table** v,excel_wcstr sz,tcstr szHelp)
{
	(*v)=0;
	void GetTable_FromeString(OUT sys_table** v,IN excel_wcstr sz);
	boost::function<void (excel_wcstr szData)> func = boost::bind(GetTable_FromeString, v , _1);
	nMech::nEXCEL::g_Excel_PostLoader.insert(func,sz,szHelp,v);
}

template<typename sys_table>
void _GetTable_FromeString(OUT std::vector<sys_table*>* v,IN excel_wcstr sz, IN int iArrayMax, tcstr szTable)
{
	EXCEL_CSV_STRING_VECTOR out;
	nString::jSplit(sz, _T(";"),out);
	if(iArrayMax && (out.size() > (size_t)iArrayMax))
	{
		fname_t szBuf;
		jt_sprintf(szBuf,_T("%s> %s : data= %s , size(%u) > iArrayMax(%d)!!! )"),jFUNC1 ,szTable,jT(sz), out.size() ,iArrayMax);
		throw tstring(szBuf);
	}
	size_t size = v->size();
	v->resize(out.size());
	try
	{
		for(size_t i = 0; i < out.size() ; ++i)
		{ 
			GetTable_FromeString(&(*v)[i], out[i].c_str());
		}
	}
	catch (tstring str)
	{
		throw tstring(_T("GetTable_FromeString(")) + szTable + _T("_ptr_vec) > ") + str;
	}
}
template<typename sys_table>
void _Excel_PostLoader_registe(std::vector<sys_table*>* v,excel_wcstr sz,int iArrayMax,tcstr szHelp)
{
	v->clear();
	void GetTable_FromeString(OUT std::vector<sys_table*>* v,IN excel_wcstr sz, IN int iArrayMax);
	boost::function<void (excel_wcstr szData)> func = boost::bind(GetTable_FromeString, v , _1,iArrayMax);
	//func(sz);
	nMech::nEXCEL::g_Excel_PostLoader.insert(func,sz,szHelp,v);
}



// Sys_ 테이블에 대한 cpp용 공통코드
#define jEXCEL_TABLE_COMMON_CODE_CPP_Sys(sys_table,help,ns1,ns2)\
	void GetTable_FromeString(OUT sys_table** v,IN excel_wcstr sz)	{_GetTable_FromeString(v,sz,jCSV(sys_table),jS(sys_table) );}\
	void Excel_PostLoader_registe(sys_table** v,excel_wcstr sz,tcstr szHelp){	_Excel_PostLoader_registe(v,sz,szHelp);}\
	\
	void GetTable_FromeString(OUT std::vector<sys_table*>* v,IN excel_wcstr sz, IN int iArrayMax) {_GetTable_FromeString(v, sz, iArrayMax, jS(sys_table));}\
	void Excel_PostLoader_registe(std::vector<sys_table*>* v,excel_wcstr sz,int iArrayMax,tcstr szHelp){_Excel_PostLoader_registe(v,sz,iArrayMax,szHelp);}\

#else

// Sys_ 테이블에 대한 cpp용 공통코드
#define jEXCEL_TABLE_COMMON_CODE_CPP_Sys(sys_table,help,ns1,ns2)\
	void GetTable_FromeString(OUT sys_table##_ptr* v,IN excel_wcstr sz)\
	{\
	(*v)=0;\
	if(!jt_strcmp(sz,"NULL" )  || !jt_strcmp(sz, "0" ) ){	(*v)=0; return; }\
	if(!jCSV(sys_table).size()) {throw tstring("sys_table") +" > jCSV(sys_table).size() ==0 ";}\
	if(sz[0]>='0' && sz[0]<='9'){ (*v) = jCSV(sys_table).Index(jt_atoi(sz)); }\
		else						{(*v) = jCSV(sys_table).find(jT(sz));}\
		if(!(*v))\
		{\
		fname_t szBuf;\
		jt_sprintf(szBuf,"%s > " jS(sys_table) _T(" data= %s , not found !!! )"),jFUNC,jT(sz) );\
		throw tstring(szBuf);\
}\
}\
	void GetTable_FromeString(OUT sys_table##_ptr_vec* v,IN excel_wcstr sz, IN int iArrayMax)\
	{\
	std::vector<std::tstring> out;\
	nString::jSplit(sz, ";",out);\
	if(iArrayMax && (out.size() > (size_t)iArrayMax))\
		{\
		fname_t szBuf;\
		jt_sprintf(szBuf,"%s> " jS(sys_table)  _T(" data= %s , size(%d) > iArrayMax(%d)!!! )"),jFUNC,jT(sz), out.size() ,iArrayMax);\
		throw tstring(szBuf);\
}\
	(*v).resize(out.size());\
	try\
		{\
		for(size_t i = 0; i < out.size() ; ++i)\
			{ \
			GetTable_FromeString(&(*v)[i], out[i].c_str());\
}\
}\
	catch (tstring str){throw tstring(_T("GetTable_FromeString(")) + jS(sys_table) + _T("_ptr_vec) > ") + str;}\
}\
	void Excel_PostLoader_registe(sys_table##_ptr* v,excel_wcstr sz,tcstr szHelp)\
	{\
	(*v)=0;\
	void GetTable_FromeString(OUT sys_table##_ptr* v,IN excel_wcstr sz);\
	g_Excel_PostLoader.insert(boost::bind(GetTable_FromeString, v , _1 ),sz,szHelp);\
}\
	void Excel_PostLoader_registe(sys_table##_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp)\
	{\
	(*v).clear();\
	void GetTable_FromeString(OUT sys_table##_ptr_vec* v,IN excel_wcstr sz, IN int iArrayMax);\
	g_Excel_PostLoader.insert(boost::bind(GetTable_FromeString, v , _1 ,iArrayMax),sz,szHelp);\
}\

#endif

// Sys_ 테이블에 대한 cpp용 sq 공통코드
#define jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys(sys_table,help,ns1,ns2)\
	DECLARE_INSTANCE_TYPE_COMPLAX_csv(vector<sys_table*>);





#endif // __Excel_code_util_header__
