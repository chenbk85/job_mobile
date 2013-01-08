/* 
filename:	jxVar.h
coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
compiler:	vc++ 6.0
date	:	2001-07-05오전 7:28:50
title	:	 xml -> jxml변환용 클래스.
*/
// jxVar.h: interface for the jxVar class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __jxvar_23l89sdflwke__
#define __jxvar_23l89sdflwke__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

#include "header\\m_Manager.h"
#include "interface/xml/jIVar.h"

#pragma warning(disable : 4251)
#pragma pack( push, mech_jxVar, 1 )

#define assert_jxVar(x) if(!(x)) throw _T("jxVar::assert");
#define assert_jxVar2(x,y) if(!(x)) throw y;

#define jASSERT_TYPE(x) assert_jxVar2(m_eType==x , _T("jxVar operator  type not match"))
#define jASSERT_TYPE2(x,y) assert_jxVar2( m_eType==x || m_eType==y , _T("jxVar operator  type not match"))
#define jASSERT_TYPE3(x,y,z) assert_jxVar2( m_eType==x || m_eType==y ||m_eType==z , _T("jxVar operator  type not match"))
#define jASSERT_TYPE_RANGE(x,y) assert_jxVar2(x < m_eType && m_eType < y ,_T("jxVar operator  array type not match"))

class CXFile;
namespace nMech
{
	namespace nUtil
	{
		struct jMemoryChunk;
	}


	struct jXmlFile
	{
		jXmlFile():xfp(0),fp(0){}
		CXFile* xfp;
		FILE* fp;
		wstring str;
	};

	//****************************************************************
	class JBASE_API jxVar : public jIVar
		//****************************************************************
	{
	public:
		union 	
		{		
			// _member_def_jxVar(bool)			->			bool m_bool; bool* m_bool_p; 로 생성
#define _member_def_jxVar(X) X m_##X; X* _jJOIN_(m_##X,_p);
			_for_each_simple_type_jvar(_member_def_jxVar)
#undef _member_def_jxVar

				TCHAR* m_cstr;
		};
		void* m_void_p; 
		enum jEnum_c8InnerOption
		{
			eIS_OUTER_MEMORY=1,
		};

#pragma warning(disable : 4201)
		union 
		{
			struct 
			{
				uchar m_eType; // 데이타 타입.
				CHAR	c8InnerOption;
				CHAR	 c8User;
				uchar	uc8User;
			};
			int  m_iType;
		};

	public:
		jxVar()		:m_iType(0) ,m_void_p(0),m_int_p(0)
		{
			m_eType=jIVar::ETelement;
		}
		jxVar(const jxVar& vv);
		void clear();
		bool empty(){ return m_eType==jIVar::ETelement;} // 초기화후 값이 세팅안된상태.

		virtual ~jxVar()	{ 		clear();	}

#define JVAR_DATA_DECL(X) 	virtual X Get_##X()const ;	virtual void Set_##X(X);	virtual X& X##Value();
		_for_each_simple_type_jvar(JVAR_DATA_DECL);
#undef JVAR_DATA_DECL

#define __setter_code_DECL(X)		jxVar& 	operator= ( X ii) ;
		_for_each_setter_type_jvar(__setter_code_DECL)
#undef __setter_code_DECL

			jxVar& 	operator= (const std::tstring& ii) ;
		jxVar&  operator= (const jxVar& vv);

		bool		operator ==(const jxVar& var) const ;
		bool		operator <(const jxVar& var) const ;

		cstr ToString(std::tstring &buf)const ;

		void writeChunk(nUtil::jMemoryChunk& mc)const ;
		void readChunk(nUtil::jMemoryChunk& mc);

		void writePacket(nUtil::jMemoryChunk& mc)const ; // network packet용.
		void readPacket(nUtil::jMemoryChunk& mc);

		void SaveXML(jXmlFile* fp)const ;


#define _InitValue_header_j(X)		jIVar* 	InitValue(X);
		_for_each_setter_type_jvar(_InitValue_header_j)
#undef _InitValue_header_j

			jINTERFACE_HEADER(jIVar);

		bool IsContents(const std::tstring& sz) const{ return IsContents(sz.c_str());}

		static EElementType  GetTypeByTagName(TCHAR* szTag); // "i_NAME" -> EDint , szTag에는 자료형이 없는 "NAME"이 복사됨
		static EElementType  GetTypeByString(cstr szName);//"EDint" -> EDint
		static cstr GetTypeStringByType(EElementType eType);// EDint ->"EDint"
		cstr GetTagNameByType(cstr szTagName, fname_t szOut);// "NAME" -> "i_NAME" , szOut를 그대로 리턴한다.

	private:
		void jxVar::delete_array_ptr();


	}; // struct jxVar

	inline jxVar* jxVar::Base(){ return (this); }
	inline CHAR &jxVar::Get_c8User(){ return c8User;}
	inline uchar &jxVar::Get_i16User(){ return uc8User;}
	inline jIVar::EElementType jxVar::GetType()const { return (jIVar::EElementType)m_eType;}
	// pV와 동일한 데이타인지. bool , int , uint , StringID일때는 형이 달라도 비교
	inline bool jxVar::IsEqual(jIVar* pV) const 	{		return (*this == *pV->Base() )	;}
	// pV보다 작은지 비교 < 연산  bool , int , uint , StringID일때는 형이 달라도 비교
	inline bool jxVar::IsLessThen(jIVar* pV) const {		return (*this <  *pV->Base() )	;}
	inline int *jxVar::GetIntP(){return m_int_p;}
	inline float *jxVar::GetFloatP(){return m_float_p;}
	inline bool jxVar::IsType(jIVar::EElementType eType){ return GetType()==eType;}

}


#pragma pack( pop, mech_jxVar)

#pragma warning(default: 4251)

#endif

