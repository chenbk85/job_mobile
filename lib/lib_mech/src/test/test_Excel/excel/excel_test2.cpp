/*------------------------------------------------------------
-------------------------------------------------------------*/

#include "stdafx.h"
#include <db_type.h>

#include "excel_test2.h"



//현제 모듈의 Sys테이블에 대해 배열형 필드를 사용할때는 아래 코드를 구현해야 한다.
#if 0

#ifndef jNOT_USE_SQ_BIND_CODE
	DECLARE_INSTANCE_TYPE_COMPLAX_csv(vector<int32>);
#endif //jNOT_USE_SQ_BIND_CODE


namespace nMech
{
	namespace nEXCEL
	{
		int32& FromeString(OUT int32* v, IN excel_wcstr sz)
		{
			return v;
		}

	}//namespace nEXCEL
}//namespace nMech
#endif //구현되어야 하는 코드 끝.

#ifndef jNOT_USE_SQ_BIND_CODE

	#if defined(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys) && defined(for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST)
		for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Sys


	#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl
		for_each_nEXCEL_excel_test2_Tbl_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl);
	#endif //jEXCEL_TABLE_COMMON_CODE_CPP_SQ_GLOBAL_Tbl

	PROTOS_ENUM_TYPE_csv(Sys_T_Test4);
	PROTOS_ENUM_TYPE_COMPLAX_csv(vector<Sys_T_Test4*>);

	PROTOS_ENUM_TYPE_csv(Sys_T_Test2);
	PROTOS_ENUM_TYPE_COMPLAX_csv(vector<Sys_T_Test2*>);

	PROTOS_ENUM_TYPE_COMPLAX_csv(vector<int32>);

#endif //jNOT_USE_SQ_BIND_CODE

namespace nMech {
	static tcstr ToString(IN Sys_T_Test4_ptr v      , tname1024_t szBuf)
	{
		if(v) jt_strcpy(szBuf,v->Get_name());
		else jt_strcpy(szBuf,jS(NULL) );
		return szBuf;
	}
	namespace nEXCEL{void Excel_PostLoader_registe(Sys_T_Test4_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp);}
	static tcstr ToString(IN Sys_T_Test4_ptr_vec& v , tname1024_t szBuf)
	{
		tstring str;
		for(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T("NULL;"); continue;};str += v[i]->Get_name();str += _T(";");}
		jt_strncpy(szBuf,str.c_str(),1024-4);
		szBuf[1024-4]=0;
		return szBuf;
	}

	static tcstr ToString(IN Sys_T_Test2_ptr v      , tname1024_t szBuf)
	{
		if(v) jt_strcpy(szBuf,v->Get_name());
		else jt_strcpy(szBuf,jS(NULL) );
		return szBuf;
	}
	namespace nEXCEL{void Excel_PostLoader_registe(Sys_T_Test2_ptr_vec* v,excel_wcstr sz,int iArrayMax,tcstr szHelp);}
	static tcstr ToString(IN Sys_T_Test2_ptr_vec& v , tname1024_t szBuf)
	{
		tstring str;
		for(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T("NULL;"); continue;};str += v[i]->Get_name();str += _T(";");}
		jt_strncpy(szBuf,str.c_str(),1024-4);
		szBuf[1024-4]=0;
		return szBuf;
	}

	static tcstr ToString(IN int32_vec& v,OUT tname1024_t szBuf)
	{
		tstring str;
		for(size_t i=0; i< v.size() ; ++i){if(!v[i]){str+=_T("0;");continue;} str += ToString(v[i],szBuf);str += _T(";");}
		jt_strncpy(szBuf,str.c_str(),1024-4);
		szBuf[1024-4]=0;
		return szBuf;
	}

	namespace nEXCEL {

		static void Convert_FromeString(OUT int32_vec* v, IN excel_wcstr sz,IN int iArrayMax)
		{
			EXCEL_WSTRING_SPLIT_CODE;
			if(iArrayMax && (out.size() >(size_t)iArrayMax) ) 
			{
				tstring szBuf = jFUNC1;
				szBuf+=_T("data=");szBuf+=jT(sz);
				szBuf+=_T(", array size(");
				tname1024_t buf2;
				szBuf+=ToString(out.size(),buf2);
				szBuf+=_T("iArrayMax(");	szBuf+=ToString(iArrayMax,buf2);	szBuf+=_T(");");
				throw tstring(szBuf);
			}
			(*v).resize(out.size());
			try{for(size_t i=0;i<out.size(); ++i){FromString(&((*v)[i]),out[i].c_str());}}
			catch (tstring e)
				{tstring szBuf = jFUNC1; szBuf+= _T("catched error > ");szBuf+=e.c_str(); szBuf+=_T(")");throw tstring(szBuf);};
		}
		static void Excel_PostLoader_registe_int32_vec(OUT int32_vec* v, IN excel_wcstr sz, IN int iArrayMax , tcstr szHelp)
		{
			g_Excel_PostLoader.insert(boost::bind(Convert_FromeString, v , _1,iArrayMax),sz,szHelp);
		}


#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys_T_Test4
	jEXCEL_TABLE_COMMON_CODE_CPP_Sys_T_Test4();
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys_T_Test4


#ifdef jEXCEL_STRUCT_GETTER_SETTER_GEN
#ifdef jEXCEL_SERVER_SIDE_CODE
	int16 Sys_T_Test4::Get_maxbuild2()	{		return (int16)m_maxbuild2;}
	void Sys_T_Test4::Set_maxbuild2(int16 v)
	{
		m_maxbuild2=v;
	}

	Sys_T_Test4_ptr Sys_T_Test4::Get_sys_test3_ref()	{			return m_sys_test3_ref_ptr;}
	void Sys_T_Test4::Set_sys_test3_ref(Sys_T_Test4_ptr v)
	{
		m_sys_test3_ref_ptr = v;
	}

	Sys_T_Test2_ptr_vec_ref Sys_T_Test4::Get_sys_test2_arrary()	{			return m_sys_test2_arrary_ptr_vec;}
	void Sys_T_Test4::Set_sys_test2_arrary(Sys_T_Test2_ptr_vec_ref v)
	{
		m_sys_test2_arrary_ptr_vec = v;
	}

	EBuildTypeTest Sys_T_Test4::Get_enum_val()	{		return (EBuildTypeTest)m_enum_val;}
	void Sys_T_Test4::Set_enum_val(EBuildTypeTest v)
	{
		if(v<eBEGIN_EBuildTypeTest || v>=eEND_EBuildTypeTest)
		{
			jERROR(_T("Sys_T_Test4::Set_enum_val(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBuildTypeTest,eEND_EBuildTypeTest,v);
		}
		m_enum_val=v;
	}

	int16 Sys_T_Test4::Get_populationreturn4()	{		return (int16)m_populationreturn4;}
	void Sys_T_Test4::Set_populationreturn4(int16 v)
	{
		m_populationreturn4=v;
	}

	EBuildTypeTest Sys_T_Test4::Get_test4()	{		return (EBuildTypeTest)m_test4;}
	void Sys_T_Test4::Set_test4(EBuildTypeTest v)
	{
		if(v<eBEGIN_EBuildTypeTest || v>=eEND_EBuildTypeTest)
		{
			jERROR(_T("Sys_T_Test4::Set_test4(enum minmax(%d,%d)error, val=%d")
				,eBEGIN_EBuildTypeTest,eEND_EBuildTypeTest,v);
		}
		m_test4=v;
	}

	int16 Sys_T_Test4::Get_getgold4()	{		return (int16)m_getgold4;}
	void Sys_T_Test4::Set_getgold4(int16 v)
	{
		m_getgold4=v;
	}

	Sys_T_Test2_ptr_vec_ref Sys_T_Test4::Get_test3_array_id()	{			return m_test3_array_id_ptr_vec;}
	void Sys_T_Test4::Set_test3_array_id(Sys_T_Test2_ptr_vec_ref v)
	{
		m_test3_array_id_ptr_vec = v;
	}

	int32_vec_ref Sys_T_Test4::Get_field_array()	{			return m_field_array_vec;}
	void Sys_T_Test4::Set_field_array(int32_vec_ref v)
	{
		m_field_array_vec = v;
	}

	int32_vec_ref Sys_T_Test4::Get_field_vector()	{			return m_field_vector_vec;}
	void Sys_T_Test4::Set_field_vector(int32_vec_ref v)
	{
		m_field_vector_vec = v;
	}

	jItemObj1_ref Sys_T_Test4::Get_itemObj1()	{		return (jItemObj1_ref)m_itemObj1;}
	void Sys_T_Test4::Set_itemObj1(jItemObj1_ref v)
	{
		m_itemObj1=v;
	}

	int32 Sys_T_Test4::Get_val_int()	{		return (int32)m_val_int;}
	void Sys_T_Test4::Set_val_int(int32 v)
	{
		if(v>60000) v = (int32)60000;
		if(v<0) v = 0;
		m_val_int=v;
	}

#endif //jEXCEL_SERVER_SIDE_CODE

#endif // jEXCEL_STRUCT_GETTER_SETTER_GEN

#ifdef jEXCEL_TABLE_COMMON_CODE_CPP_Sys
	for_each_nEXCEL_excel_test2_Sys_STRUCT_LIST(jEXCEL_TABLE_COMMON_CODE_CPP_Sys);
#endif //jEXCEL_TABLE_COMMON_CODE_CPP_Sys

jEXCEL_LIB_API CSV_Sys_T_Test4 g_Sys_T_Test4;


tcstr Sys_T_Test4::ReadCSV(IN size_t iRecord,IN EXCEL_CSV_STRING_VECTOR &out,IN OUT size_t& index,IN bool isCheck)
{
	tcstr szKEY=0;
	tfname_t szHelp;
	szHelp[0]=0;
	if(isCheck && (out.size() != Get_STRUCT_COUNT()) )
	{
		jERROR(_T("parse size error(%d!=Get_STRUCT_COUNT(%d) lineNum=%s"),out.size(),Get_STRUCT_COUNT(),index );
	}
	szKEY = Sys__T_Base::ReadCSV(iRecord ,out,index,false);
	Set_maxbuild2(FromString(out[index++],m_maxbuild2) );
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_test2)Sys_T_Test4::sys_test3_ref"),(int32)iRecord);
	Excel_PostLoader_registe(&m_sys_test3_ref_ptr, out[index++].c_str()  , szHelp );
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_test2)Sys_T_Test4::sys_test2_arrary"),(int32)iRecord);
	Excel_PostLoader_registe(&m_sys_test2_arrary_ptr_vec , out[index++].c_str() ,0 , szHelp ) ;
	Set_enum_val(FromString(out[index++],m_enum_val) );
	Set_populationreturn4(FromString(out[index++],m_populationreturn4) );
	Set_test4(FromString(out[index++],m_test4) );
	Set_getgold4(FromString(out[index++],m_getgold4) );
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_test2)Sys_T_Test4::test3_array_id"),(int32)iRecord);
	Excel_PostLoader_registe(&m_test3_array_id_ptr_vec , out[index++].c_str() ,3 , szHelp ) ;
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_test2)Sys_T_Test4::field_array"),(int32)iRecord);
	Excel_PostLoader_registe_int32_vec(&m_field_array_vec, out[index++].c_str(), 3 , szHelp );
	jt_sprintf(szHelp, _T("loading(iRecord=%d) file(excel_test2)Sys_T_Test4::field_vector"),(int32)iRecord);
	Excel_PostLoader_registe_int32_vec(&m_field_vector_vec, out[index++].c_str(), 0 , szHelp );
	Set_itemObj1(FromString(out[index++],m_itemObj1) );
	Set_val_int(FromString(out[index++],m_val_int) );
	return szKEY;
}

void Sys_T_Test4::DebugPrint()
{	tname1024_t szBuf;

	for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD_all_member(jEXCEL_STRUCT_FIELD_DebugPrint);
}


} //namespace nEXCEL 

}// namespace nMech 
#ifndef jNOT_USE_SQ_BIND_CODE

	using namespace nMech::nEXCEL;

	DECLARE_INSTANCE_TYPE(nMech::nUtil::jCSV_File<Sys_T_Test4>);

	namespace nMech { namespace nEXCEL
	{
		jSQ_REGIST_BIND(nMech_nEXCEL_excel_test2)
		{
			jSQ_Interface(nMech::nUtil::jCSV_File<Sys_T_Test4>)
				jSQ_fn(size,"int(void)","total size")
				jSQ_fn(at,"Sys_T_Test4*(int index)","array operator. index is start 0")
				jSQ_fn(Index,"Sys_T_Test4*(int index)","array operator. index is start 1")
				jSQ_fn(find,"Sys_T_Test4*(tcstr key)","map operator")
			jSQ_end();

			jSQ_Interface(Sys_T_Test4)
			for_each_nEXCEL_Sys_T_Test4_STRUCT_FIELD(jEXCEL_SQ_TABLE_FILED_BIND);
				jSQ_fn(GetBase_Sys__T_Base,"Sys__T_Base*()","Get base Table")
			jEXCEL_SQ_TABLE_FUNC_BIND(Sys_T_Test4)
			jSQ_end();
			
			{
				nMech::nUtil::jCSV_File<Sys_T_Test4>* p = &g_Sys_T_Test4;
				jSQ_g_var(p , g_Sys_T_Test4);
			}

		}
	} /*namespace nEXCEL */ }// namespace nMech 
#endif //jNOT_USE_SQ_BIND_CODE

