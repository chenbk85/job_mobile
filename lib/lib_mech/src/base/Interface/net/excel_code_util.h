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

#include "header/ToString_base.h"
#include "header/uString_stl.h"
#include "interface/db/db_uid_type.h"


// To register simple types (like enums) so they can be used as arguments
#define DECLARE_ENUM_TYPE_csv(TYPE) namespace nMech{ namespace nSQ { \
	bool Match(TypeWrapper<TYPE>,HSQUIRRELVM v,int idx) { return Match(TypeWrapper<int>(),v,idx); } \
	TYPE Get(TypeWrapper<TYPE>,HSQUIRRELVM v,int idx) { return (TYPE)Get(TypeWrapper<int>(),v,idx); } \
	void Push(HSQUIRRELVM v,TYPE value) { Push(v,(int)value); } \
	template<> struct TypeInfo<TYPE> : public TypeInfo<int> { }; \
} } // nameSpace jSqPlus


//DECLARE_ENUM_TYPE_csv()으로 정의 된 자료형에 대한 선언용
#define PROTOS_ENUM_TYPE_csv(TYPE) namespace nMech{ namespace nSQ { \
	bool Match(TypeWrapper<TYPE>,HSQUIRRELVM v,int idx); \
	TYPE Get(TypeWrapper<TYPE>,HSQUIRRELVM v,int idx); \
	void Push(HSQUIRRELVM v,TYPE value); \
	template<> struct TypeInfo<TYPE>;\
} } // nameSpace jSqPlus



/*
DECLARE_INSTANCE_TYPE_COMPLAX_csv 와 PROTOS_ENUM_TYPE_COMPLAX_csv는 쌍으로 사용.
CSV 관련 EXCEL 필드에서 복합형( vector<?> ) 에 사용.
*/
#define DECLARE_INSTANCE_TYPE_COMPLAX_csv(TYPE) namespace nMech{ namespace nSQ { \
	const SQChar * GetTypeName(const TYPE & n)            { return _T(#TYPE); } \
	void Push(HSQUIRRELVM v,TYPE * value)                 \
{ \
	if (!GetjISQ()->BindUtil_CreateNativeClassInstance(v,GetTypeName(*value),value,0)) \
	throw SquirrelError(_T("Push(): could not create INSTANCE (check registration name)")); } \
	\
	void Push(HSQUIRRELVM v,TYPE & value)                 \
{ if (!CreateCopyInstance(v,GetTypeName(value),value)) \
	throw SquirrelError(_T("Push(): could not create INSTANCE copy (check registration name)")); } \
	\
	bool	Match(TypeWrapper<TYPE &>,HSQUIRRELVM v,int idx) { return  GetInstance<TYPE,false>(v,idx) != NULL; } \
	bool	Match(TypeWrapper<TYPE *>,HSQUIRRELVM v,int idx) { return  GetInstance<TYPE,false>(v,idx) != NULL; } \
	TYPE & Get(TypeWrapper<TYPE &>,HSQUIRRELVM v,int idx) { return *GetInstance<TYPE,true>(v,idx); } \
	TYPE * Get(TypeWrapper<TYPE *>,HSQUIRRELVM v,int idx) { return  GetInstance<TYPE,true>(v,idx); } \
} } // nameSpace jSqPlus

// DECLARE_INSTANCE_TYPE_COMPLAX_csv(vector<Sys_T_Test2*>); 와 같이 미리 선언된 복합자료형에 대한 선언용.
#define PROTOS_ENUM_TYPE_COMPLAX_csv(TYPE) namespace nMech{ namespace nSQ { \
	const SQChar * GetTypeName(const TYPE & n);\
	void Push(HSQUIRRELVM v,TYPE * value);\
	void Push(HSQUIRRELVM v,TYPE & value);\
	bool	Match(TypeWrapper<TYPE &>,HSQUIRRELVM v,int idx);\
	bool	Match(TypeWrapper<TYPE *>,HSQUIRRELVM v,int idx);\
	TYPE & Get(TypeWrapper<TYPE &>,HSQUIRRELVM v,int idx);\
	TYPE * Get(TypeWrapper<TYPE *>,HSQUIRRELVM v,int idx);\
	template<> struct TypeInfo<TYPE> { \
	const SQChar * typeName; \
	TypeInfo() : typeName(_T(#TYPE)) {} \
	enum {TypeID=VAR_TYPE_INSTANCE,Size=sizeof(TYPE),TypeMask='x'}; \
	operator ScriptVarType() { return ScriptVarType(TypeID); } \
	};\
} } // nameSpace jSqPlus



#define jEXCEL_STRUCT_ENUM_GEN(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
	eF_##eng_name=field_order,

#define jEXCEL_STRUCT_GETTER_SETTER_GEN(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple) \
	getter_type Get_##eng_name(); void Set_##eng_name(setter_type data);

#define jEXCEL_ENUM_STRING_CPP_CODE(enum_eng_name,enum_value,enum_help,root_namespace, namespace12,enumTag)\
	{ e##enum_eng_name , jS(enum_eng_name) , jS(enum_help) }, 


#define jEXCEL_STRUCT_COMMON_CODE(STRUCT_NAME)\
	/*STRUCT_NAME(){ CLASS_CLS();}*/\
	tcstr ReadCSV(IN size_t iRecord,IN std::vector<std::wstring> &out,IN OUT size_t &index,IN bool isCheck=true);\
	void DebugPrint();\

/*
#if 0

#define jEXCEL_ENUM_StringToVal(enum_tbl,help,root_ns,ns)\
	inline enum_tbl FromString(enum_tbl* eVal,wcstr sz)\
	{\
		tstring val(jT(sz));\
		nSTL::trim(val);\
		tcstr v = val.c_str();\
		jEnumString* pES = jEnumString::Get(g_ES_##enum_tbl,v );\
		if(pES){(*eVal)=(enum_tbl)pES->m_id ; return *eVal;}\
		jWARN(jS(ns) jS(::) jS( enum_tbl) jS(=)_T("못찾음 : %s") , v );\
		return eBEGIN_##enum_tbl;\
	}\
	inline enum_tbl FromString(enum_tbl* eVal,std::wstring& sz){return FromString(eVal,sz.c_str());}\
	inline tcstr ToString(root_ns::ns::enum_tbl eType,tname1024_t szBuf=0)\
	{\
		jEnumString* pES = jEnumString::Get(g_ES_##enum_tbl,eType);\
		if(szBuf){jt_strcpy(szBuf, pES ? pES->m_szName : _T("enumNULL"));}\
		return pES ? pES->m_szName : _T("enumNULL");\
	}\
	inline void jDebugPrint(tcstr szName,root_ns::ns::enum_tbl val)\
	{\
		jLOG(_T("\t%s : %s[=%d]"), szName, ToString(val), val);\
	}\

#else

*/
#define ENUM_FROMSTRING12(ENUM_NAME,VAL,HELP,root_ns,ns,ENUM_TABLE)	\
	if(jt_strcmp(jS(ENUM_NAME),sz)==0 || jt_strcmp(jS(e##ENUM_NAME),sz)==0) \
		return root_ns::ns::e##ENUM_NAME;

#define ENUM_TOSTRING12(ENUM_NAME,VAL,HELP,root_ns,ns,ENUM_TABLE)	\
	if(eType==root_ns::ns::e##ENUM_NAME) \
		return jS(ENUM_NAME);

#define jEXCEL_ENUM_StringToVal(enum_tbl,help,root_ns,ns)\
	inline enum_tbl FromString(excel_wcstr  sz,enum_tbl)\
	{\
		_jJOIN_5(for_each_,ns,_,enum_tbl,_ENUM_FIELD)(ENUM_FROMSTRING12);\
		return eBEGIN_##enum_tbl;\
	}\
	inline enum_tbl FromString(std::tstring& sz,enum_tbl eVal)\
	{\
		return FromString(sz.c_str(),eVal);\
	}\
	inline tcstr ToString(root_ns::ns::enum_tbl eType,tname1024_t szBuf=0)\
	{\
		_jJOIN_5(for_each_,ns,_,enum_tbl,_ENUM_FIELD)(ENUM_TOSTRING12);	\
		return jS(NULL);	\
	}\
	inline void jDebugPrint(tcstr szName,root_ns::ns::enum_tbl val)\
	{\
		jLOG(_T("\t%s : %s[=%d]"), szName, ToString(val), val);\
	}\

/*

#endif
*/


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

// #define jEXCEL_STRUCT_FIELD_DebugPrint(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\
//  	ToString(Get_##eng_name(),szBuf); GetjILog()->LogPlus(_T("%s "),szBuf);

#define print_ENUM23984(ns,enum_tbl)	inline void print_##enum_tbl(){jEnumString::DebugPrint(ns::g_ES_##enum_tbl);}


//ENUM_TABLE(enum_tbl,help,root_ns,ns)
#define jEXCEL_SQ_DECLARE_ENUM_TYPE(enum_tbl,help,root_ns,ns) DECLARE_ENUM_TYPE_csv(enum_tbl);print_ENUM23984(ns,enum_tbl);
		



#define jEXCEL_SQ_DECLARE_ENUM_TYPE_PROTO(enum_tbl,help,root_ns,ns) PROTOS_ENUM_TYPE_csv(enum_tbl);


#define jEXCEL_SQ_DECLARE_INSTANCE_TYPE(struct_name,help,domain,ns) DECLARE_INSTANCE_TYPE(struct_name);

#define jEXCEL_SQ_TABLE_FILED_BIND(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\
	jSQ_fn(Get_##eng_name,#getter_type,"")	jSQ_fn(Set_##eng_name,"",#setter_type)

#define jEXCEL_SQ_TABLE_FUNC_BIND(table) jSQ_fn(DebugPrint,"void(void)","debug print")

//void Excel_Converter::make_file_cpp_SUB_gen_sq_bind_EnumField(of)에서 사용.
#define jEXCEL_SQ_bind_EnumField_BEGIN(enum_tbl,help,root_ns,ns)\
		nSQ::SquirrelObject sq##enum_tbl=  GetjISQ()->VM_CreateTable();\
		enumRoot.SetValue(jS(enum_tbl), sq##enum_tbl );\
		nMech::Get_jIScriptHelper()->RegistEnumTable_ToEnumRoot(jS(enum_tbl),jS(help));\
		RegisterGlobal(print_##enum_tbl,jS(print_##enum_tbl));



#define jEXCEL_SQ_bind_EnumField(enum_eng_name,enum_value,enum_help,root_namespace, namespace12,enum_tbl)\
	nSQ::BindConstant(sq##enum_tbl , e##enum_eng_name,jS(e##enum_eng_name) );\
	nMech::Get_jIScriptHelper()->RegistEnumField_ToEnumRoot(jS(enum_tbl),jS(e##enum_eng_name),e##enum_eng_name,jS(enum_help));\



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


#define jEXCEL_SQL_BIND_FIELD(eng_name,name,data_type,field_order,getter_type,setter_type,data_type_simple)\
	SQLBindCol(hS, field_order+1,jEXCEL_SQL_TYPE_##data_type,&p->_jJOIN_4(m_,eng_name,_,data_type_simple)\
					,sizeof(p->_jJOIN_4(m_,eng_name,_,data_type_simple)),	&data_len[field_order]);

#define jEXCEL_SQL_BIND_FUNC_DECL(STRUCT_NAME,help,ns1,ns2)	void jBindColData(jEXCEL_SQLHSTMT hS, STRUCT_NAME* p);

#define jEXCEL_SQL_BIND_FUNC_DEFINE(STRUCT_NAME,help,ns1,ns2) void jBindColData(jEXCEL_SQLHSTMT hS, STRUCT_NAME* p)\
	{static SQLLEN data_len[STRUCT_NAME::eSTRUCT_COUNT]; _jJOIN_5(for_each_,ns2,_,STRUCT_NAME,_STRUCT_FIELD_all_member)(jEXCEL_SQL_BIND_FIELD);}

namespace nMech
{
	inline void jSetter(std::wstring dest, wcstr src){ dest = src;};
	inline void jSetter(std::string dest, acstr src){ dest = src;};

	inline void jSetter(CHAR* dest, acstr src,int itot){ja_strncpy(dest, src,itot-1);dest[itot-1]=0;}
	inline void jSetter(WCHAR* dest, wcstr src,int itot){jw_strncpy(dest, src,itot-1);dest[itot-1]=0;}

	inline acstr jGetter(std::string& v){ return v.c_str();}
	inline wcstr jGetter(std::wstring& v){ return v.c_str();}

	#define nExcelUtil_StringConverter nUNI::scb1024_t

	inline void jSetter(aname32_t dest, acstr src){ja_strncpy(dest, src,31);dest[31-1]=0;}
	inline void jSetter(wname32_t dest, wcstr src){jw_strncpy(dest, src,31);dest[31-1]=0;}
}


#define jCSV(Table) g_##Table

#define jEXCEL_DECL_csv_namespace(Table,Name,ns1,ns2) using namespace ns1::ns2;

// Sys_ 테이블에 대한 header용 공통코드
#define jEXCEL_TABLE_COMMON_CODE_H_Sys(sys_table,help,ns1,ns2)\
	typedef sys_table* sys_table##_ptr;\
	typedef std::vector<sys_table##_ptr> sys_table##_ptr_vec;\
	typedef sys_table##_ptr_vec& sys_table##_ptr_vec_ref;\
	void GetTable_FromeString(OUT sys_table##_ptr* v,IN wcstr sz);\
	void GetTable_FromeString(OUT sys_table##_ptr_vec* v,IN wcstr sz, IN int iArrayMax);\

// Sys_ 테이블에 대한 cpp용 공통코드
#define jEXCEL_TABLE_COMMON_CODE_CPP_Sys(sys_table,help,ns1,ns2)\
	void GetTable_FromeString(OUT sys_table##_ptr* v,IN wcstr sz1)\
	{\
		nUNI::scb1024_t sz_1(sz1);\
		tcstr sz = sz_1.getT();\
		(*v)=0;\
		if(!jt_strcmp(sz,_T("NULL") )  || !jt_strcmp(sz, _T("0") ) ){	(*v)=0; return; }\
		if(!jCSV(sys_table).size()) {throw tstring(jS(sys_table)) +_T(" > jCSV(sys_table).size() ==0 ");}\
		if(sz[0]>='0' && sz[0]<='9'){ (*v) = jCSV(sys_table).Index(jt_atoi(sz)); }\
		else						{(*v) = jCSV(sys_table).find(sz);}\
		if(!(*v))\
		{\
			fname_t szBuf;\
			jt_sprintf(szBuf,jFUNC1 jS(sys_table) _T(" data= %s , not found !!! )"),sz);\
			throw tstring(szBuf);\
		}\
	}\
	void GetTable_FromeString(OUT sys_table##_ptr_vec* v,IN wcstr sz, IN int iArrayMax)\
	{\
		std::vector<std::wstring> out;\
		nString::jSplitW(sz, L";",out);\
		if(iArrayMax && (out.size() > (size_t)iArrayMax))\
		{\
			fname_t szBuf;\
			jt_sprintf(szBuf,jFUNC1 jS(sys_table)  _T(" data= %s , size(%d) > iArrayMax(%d)!!! )"),jT(sz), out.size() ,iArrayMax);\
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
	void Excel_PostLoader_registe(sys_table##_ptr* v,wcstr sz,tcstr szHelp)\
	{\
		(*v)=0;\
		void GetTable_FromeString(OUT sys_table##_ptr* v,IN wcstr sz);\
		g_Excel_PostLoader.insert(boost::bind(GetTable_FromeString, v , jBOOST__PLACEHODER_1 ),sz,szHelp);\
	}\
	void Excel_PostLoader_registe(sys_table##_ptr_vec* v,wcstr sz,int iArrayMax,tcstr szHelp)\
	{\
		(*v).clear();\
		void GetTable_FromeString(OUT sys_table##_ptr_vec* v,IN wcstr sz, IN int iArrayMax);\
		g_Excel_PostLoader.insert(boost::bind(GetTable_FromeString, v , jBOOST__PLACEHODER_1 ,iArrayMax),sz,szHelp);\
	}\


// Sys_ 테이블에 대한 cpp용 sq 공통코드
#define jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys(sys_table,help,ns1,ns2)\
	DECLARE_INSTANCE_TYPE_COMPLAX_csv(vector<sys_table*>);





namespace nMech
{
	namespace nEXCEL
	{
		typedef boost::function<void (wcstr szData)> Regist_PostLoad_ft;
		struct Excel_PostLoader
		{
			struct PostLoadObj
			{
				PostLoadObj(Regist_PostLoad_ft f,wstring d, tstring h): func(f),data(d),help(h){}
				PostLoadObj(){}
				Regist_PostLoad_ft func;
				wstring data;
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
					jERROR_T("load fail(%s) : %s",jT(it->help) ,e.c_str() );
				}
				catch (...)
				{
					jERROR_T("load fail unkown (%s) , data=%s",it->help.c_str() ,jT(it->data));
				}
			}
			void insert(Regist_PostLoad_ft func,wcstr szData,tcstr szHelp)
			{
				m_Regist_PostLoad.push_back(PostLoadObj(func,szData,szHelp));
			}
		};
		extern Excel_PostLoader g_Excel_PostLoader; 
		// g_Excel_PostLoader는 csv loader쪽 모듈에서 반드시 정의 해주어야 한다.
		// namespace nMech{namespace nEXCEL{Excel_PostLoader g_Excel_PostLoader;}}

	}//namespace nEXCEL
}//namespace nMech

#endif // __Excel_code_util_header__
