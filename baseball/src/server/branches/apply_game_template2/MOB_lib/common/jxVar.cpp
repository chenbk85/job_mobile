     /* 
	filename:	jxDocumentEx.h
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05오전 7:28:50
	title	:	 xml -> jxml변환용 클래스.

	xml file load 규칙.
	: 
*/
// jxDocument.cpp: implementation of the jxDocument class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jxVar.h"
//#include "base/jXmlDictionary.h"
//#include "Interface/jILog.h"
//#include "base/jTestUnit.h"
//#include "interface/xml/jIVar_op.h"
#include "header/uStringParsor.h"
#include <assert.h>
#include <string.h> 

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

#define RGB(r,g,b)          ((unsigned long)(((char)(r)|((unsigned short)((char)(g))<<8))|(((unsigned long)(char)(b))<<16)))

#define MAKEWORD(a, b)      ((WORD)(((BYTE)(((unsigned long)(a)) & 0xff)) | ((WORD)((BYTE)(((unsigned long)(b)) & 0xff))) << 8))
#define MAKELONG(a, b)      ((LONG)(((WORD)(((unsigned long)(a)) & 0xffff)) | ((DWORD)((WORD)(((unsigned long)(b)) & 0xffff))) << 16))
#define LOWORD(l)           ((WORD)(((unsigned long)(l)) & 0xffff))
#define HIWORD(l)           ((WORD)((((unsigned long)(l)) >> 16) & 0xffff))
#define LOBYTE(w)           ((int8)(((unsigned long)(w)) & 0xff))
#define HIBYTE(w)           ((BYTE)((((unsigned long)(w)) >> 8) & 0xff))

#define GetRValue(rgb)      (LOBYTE(rgb))
#define GetGValue(rgb)      (LOBYTE(((unsigned short)(rgb)) >> 8))
#define GetBValue(rgb)      (LOBYTE((rgb)>>16))


#define jFLOAT_FMT _T("%5.3f")
namespace nMech
{
	//--------------------------------------------------------------------------
	// 가령 EDfloat라는 값으로 "EDfloat"라는 스트링을 얻기 위한 정보를 세팅하기 위함
	//--------------------------------------------------------------------------
	namespace 
	{

		//typedef std::vector<std::tstring ,jxVar::EElementType_MAX+1> s_EDataTypeMap_t; 
		typedef std::vector<std::tstring> s_EDataTypeMap_t; 
		s_EDataTypeMap_t s_EDataTypeMap;
		//static std::tstring s_EDataTypeMap[jxVar::EElementType_MAX+1];
		//static bool g_UnitTestOK_OuterMemory_For_boolData=false;

		jONCE_RUN(__jxVar_cpp__)
		{
			s_EDataTypeMap.resize(jxVar::EElementType_MAX+1);
#undef __JVAR_ENUM_STR
#define __JVAR_ENUM_STR(x) s_EDataTypeMap[jxVar::x]=_T(#x);
			_for_each_ENUM_type_jvar(__JVAR_ENUM_STR)
		}
	}


	cstr jxVar::GetTagNameByType(cstr szTagName, fname_t szOut)
	{
#define __JVAR_NAME_BY_TYPE(TAG_STRING , ENUM_VAR) \
			case ENUM_VAR:			jt_sprintf(szOut, _T(#TAG_STRING) _T("%s"), szTagName);				break;

		switch(m_eType)
		{
			_for_each_data_type_jvar(__JVAR_NAME_BY_TYPE)
		default:	        jt_strcpy(szOut, szTagName);						break;
		}
		return szOut;
	}

	//****************************************************************
	jxVar::EElementType  jxVar::GetTypeByTagName(TCHAR* szTag)
		//****************************************************************
	{
		fname_t szType;
		fname_t szName;
		jxVar::EElementType m_eType;

		jt_strcpy(szName , szTag);
		jt_strcpy(szType , szTag);
#define __JVAR_TYPE_FINDER_BY_TAGNAME(TAG_STRING,ENUM_VAR) \
	else if( _T(#TAG_STRING)[0]!=_T('0') && !jt_strncmp(szType ,  _T(#TAG_STRING) ,jt_strlen(_T(#TAG_STRING)) ) )\
		{	m_eType = ENUM_VAR ; 	jt_strcpy( szTag , szName+jt_strlen(_T(#TAG_STRING) )); 	}	

		if(0)	{	}
		_for_each_data_type_jvar(__JVAR_TYPE_FINDER_BY_TAGNAME)
		else
		{ // 기본적으로 무조건 jstring으로 저장.
			m_eType = jxVar::EDcstr;
		}
		return m_eType;
	}

	//--------------------------------------------------------------------------
#undef _JMB
#define _JMB(x) m_##x
#define JVAR_DATA_DEFINE(X) 	\
	X& jxVar::X##Value(){		return IsOuterMemorySource() ? *_JMB(X##_p) : m_##X;}\
	X jxVar::Get_##X()const {	return IsOuterMemorySource() ? *_JMB(X##_p):m_##X; }\
	void jxVar::Set_##X(X val){		if(IsOuterMemorySource())		*_JMB(X##_p) = val; 	else 	m_##X= val; }

	_for_each_simple_type_jvar(JVAR_DATA_DEFINE);


	jxVar::EElementType  jxVar::GetTypeByString(cstr szName)//"EDint" -> EDint
	{
#undef __JVAR_ENUM_STR
#define __JVAR_ENUM_STR(x) if(!jt_strncmp(_T(#x), szName, jt_strlen(_T(#x)) )) return x;
		_for_each_ENUM_type_jvar(__JVAR_ENUM_STR);
		return EDataType_SIMPLE_BEGIN;
	}
	cstr jxVar::GetTypeStringByType(jIVar::EElementType eType)
	{
		jASSERT0(jxVar::EElementType_MAX >= eType);
		return s_EDataTypeMap[eType].c_str();
	}

	cstr jxVar::GetTypeString()  const 
	{
		jASSERT0(jxVar::EElementType_MAX >= m_eType);
		return s_EDataTypeMap[m_eType].c_str();
	}

	//---------------------------------------------------------------
	jxVar::jxVar(const jxVar& otherV)
		:m_iType(0),m_void_p(0),m_int_p(0)
		//----------------------------------------------------------------
	{
		*this = otherV;
	}

	//---------------------------------------------------------------
	void jxVar::clear()
		//----------------------------------------------------------------
	{
		if(!IsOuterMemorySource())
		{
			delete_array_ptr();
		}
		m_eType = ETelement;
		m_void_p=0;
	}

	//---------------------------------------------------------------
	//// 자료형도 강제 변환됨
	jxVar&  jxVar::operator= (const jxVar& otherV)
		//----------------------------------------------------------------
	{
		if(IsOuterMemorySource())
		{
			jASSERT0(GetType() == otherV.GetType());
		}
		SetType(otherV.GetType());
		if(IsIntSizeValue())
		{
			if(IsOuterMemorySource())
			{
				if(otherV.IsOuterMemorySource())
					*(int*)m_int_p = *(int*)otherV.m_int_p;
				else
					*(int*)m_int_p = otherV.m_int;
			}
			else
			{
				if(otherV.IsOuterMemorySource())
					m_int = *(int*)otherV.m_int_p;
				else
					m_int = otherV.m_int;
			}
		}
		else if(m_eType ==EDcstr)
		{
			Set_cstr(otherV.m_cstr.c_str());
		}
		else if( IsArrayValue())
		{
			uint itot=otherV.GetArraySize();
			memcpy(m_int_p , otherV.m_int_p , sizeof(int)*itot);
		}
		return *this;
	}


#define _InitValue_define(X)		jIVar* 	jxVar::InitValue(X x){ SetType(ED##X); Set_##X(x); return this;}
	_for_each_setter_type_jvar(_InitValue_define);

	//---------------------------------------------------------------
	jIVar* 	jxVar::InitValue(cstr sData , EElementType type) 
		//----------------------------------------------------------------
	{
		SetType(type);
		FromString(sData);
		return this;
	} // jxVar& 	Set(cstr sData , cstr sType) 


	cstr jxVar::ToString(TCHAR szBufferTemp[256]) const 
	{
		const int iMAX_LEN = 255;//sizeof(szBufferTemp);
		szBufferTemp[0]=0;
		switch(m_eType)
		{
		case EDint:		jt_sprintf(szBufferTemp,_T("%d"),Get_int());	break;
		case EDbool:	
			{
				jt_sprintf(szBufferTemp,_T("%s"),Get_bool()?jS(true):jS(false));
				break;
			}
		case EDhex:	jt_sprintf(szBufferTemp,_T("%x"),Get_int());	break;
		case EDfloat:	jt_sprintf(szBufferTemp,jFLOAT_FMT , Get_float() );break;
		case EDuint:	jt_sprintf(szBufferTemp,_T("%u") , Get_uint());	break;
		case EDStringID:
		case EDcstr:			
			{
				cstr sz = Get_cstr();
				jt_strncpy(szBufferTemp, sz, iMAX_LEN );
				return sz;
			}
		case EDargb :
			{
				jt_sprintf(szBufferTemp,_T("%d;%d;%d;%d") , Get_A() , Get_R() , Get_G() , Get_B() );
				break;
			}
		case EDrgb:
			{
				jt_sprintf(szBufferTemp,_T("%d;%d;%d") ,  GetRValue(m_uint) , GetGValue(m_uint) , GetBValue(m_uint) );
				break;
			}
		case EDint2: 
			jt_sprintf(szBufferTemp,_T("%d;%d") , m_int_p[0], m_int_p[1] );
			break;
		case EDint3 :  
			jt_sprintf(szBufferTemp,_T("%d;%d;%d") , m_int_p[0], m_int_p[1] ,m_int_p[2] );
			break;
		case EDint4 :// v에는 int v[4]
			jt_sprintf(szBufferTemp,_T("%d;%d;%d;%d") , m_int_p[0], m_int_p[1] ,m_int_p[2] , m_int_p[3] );
			break;

		case EDvector2: 
		case EDvector3: 
		case EDvector4 :// v에는 float v[4]
		case EDmatrix44 :// v에는 float v[4*4]
		case EDmatrix33 :// v에는 float v[3*3]
			{
				int itot=GetArraySize();
				jt_sprintf(szBufferTemp,jFLOAT_FMT , m_float_p[0]);
				fname_t sz1;
				jt_strcpy(sz1 , szBufferTemp);
				for(int idx = 1 ; idx< itot;++idx)
				{
					jt_sprintf(szBufferTemp,_T(";%5.3f") ,m_float_p[idx]);
					jt_strcat(sz1, szBufferTemp);
				}
				jt_strcpy(szBufferTemp, sz1);
				jASSERT0(jt_strlen(szBufferTemp)<=iMAX_LEN);
				break;
			}
		}
		return szBufferTemp;
	}


	//---------------------------------------
	void jxVar::FromString(cstr buf)
	{
		switch(m_eType)
		{
		case EDbool:	
			{
				bool is;
				if(!jt_stricmp(buf,jS(true)))
				{
					is=true;
				}
				else if(!jt_stricmp(buf,jS(false)))
				{
					is=false;
				}
				else
				{
					is =(bool)jt_atoi(buf);
				}
				Set_bool(is); 
				break;	
			}
		case EDint:		{Set_int((int)jt_atoi(buf)); break;	}	
		case EDuint:	{Set_uint((uint)jt_atol(buf)); break;	}
		case EDfloat:	{Set_float((float)jt_atof(buf)); break;	}
		case EDhex:			
			{
				int i_hex;;
				jt_sscanf(buf, _T("%x"),&i_hex);	
				Set_int(i_hex);
				break;
			}
		case EDStringID: 
		case EDcstr:			
			Set_cstr(buf);
			break;
		case EDargb :
			{
				jvector<std::tstring> out;
				nString::jSplit( buf, _T("; \t\n") , out);
				assert( (out.size() == 4) && _T("jxVar 데이타형이 잘못됐음 , int array갯수 가 안맞음 , 예) argb_NAME -> 23;23;2;2") );
				int aa, rr, gg, bb;
				aa = jt_atoi(out[0].c_str() );
				rr = jt_atoi(out[1].c_str() );
				gg = jt_atoi(out[2].c_str() );
				bb = jt_atoi(out[3].c_str() );
				m_int = jD3DCOLOR_ARGB(aa,rr,gg,bb);
			}
			break;
		case EDrgb:
			{
				jvector<std::tstring> out;
				nString::jSplit( buf, _T("; \t\n") , out);
				assert(out.size() == 3 && _T("jxVar 데이타형이 잘못됐음 , int array갯수 가 안맞음 , 예) argb_NAME -> 23;23;2;2"));
				int rr, gg, bb;
				rr = jt_atoi(out[0].c_str() );
				gg = jt_atoi(out[1].c_str() );
				bb = jt_atoi(out[2].c_str() );
				m_int = RGB(rr,gg,bb);
				break;
			}
		case EDint2: 
		case EDint3:
		case EDint4 :// v에는 int v[4]
			{
				uint itot=GetArraySize();
				jvector<std::tstring> out;
				nString::jSplit( buf , _T("; \t\n") , out);
				assert(out.size() == itot && _T("jxVar:: 데이타형이 잘못됐음 , int array갯수 가 안맞음 , 예) i2_NAME -> 23;23"));

				jASSERT0(m_int_p);
				//v = m_float_p = new int[itot];

				for(uint idx = 0 ; idx< itot;++idx)
				{
					//uCalculator cal(out[idx].c_str());
					m_int_p[idx] = jt_atoi(out[idx].c_str());//cal.calc();	
					//m_int_p[idx] = jt_atoi(out[idx].c_str() );
				}
				break;
			}

		case EDvector2: 
		case EDvector3: 
		case EDvector4 :// v에는 float v[4]
		case EDmatrix44 :// v에는 float v[4*4]
		case EDmatrix33 :// v에는 float v[3*3]
			{
				uint itot=GetArraySize();
				jASSERT0(m_float_p);
				jvector<std::tstring> out;
				nString::jSplit( buf , _T("; \n\t") , out);
				assert(out.size() == itot && _T("jxVar 데이타형이 잘못됐음 , float array갯수 가 안맞음 , 예) i2_NAME -> 23;23"));

				for(uint idx = 0 ; idx< itot;++idx)
				{
					m_float_p[idx] = jt_atof(out[idx].c_str() );
				}
				break;
			}
		default:
			throw _T("error xml var");
		}

	}


	//---------------------------------------------------------------
	void jxVar::DebugPrint(bool isInsert_CR) const 
		//----------------------------------------------------------------
	{
		if(GetType() == ETelement) return;
		fname_t buf;
		cstr  sz = ToString(buf);
		GetjILog()->LogPlus(_T("%s"),sz);				
	}

	//--------------------------------------------------------------------------
	void jxVar::Set_cstr(cstr sz)
		//--------------------------------------------------------------------------
	{
		bool isOk = m_eType==jIVar::ETelement || m_eType == jxVar::EDcstr || m_eType == jxVar::EDStringID;
#ifdef _DEBUG
		if(!isOk)
		{
			printf("");
		}
#endif
		jRETURN(isOk);
		//jRAISE(isOk);
		//jASSERT0(isOk);
		bool isEle = (m_eType==jIVar::ETelement);
		if(m_eType == jxVar::EDcstr || isEle)	
		{
			if(isEle)
				m_eType = jIVar::EDcstr;

			m_cstr = sz;
		}
		//else m_StringID = nString::Get_jIStringTable()->GetIndex(sz);
	}
	bool jxVar::IsContents(cstr sz) const
	{
		return !jt_strcmp(sz, Get_cstr());
	}
	//--------------------------------------------------------------------------
	cstr jxVar::Get_cstr() const 
		//--------------------------------------------------------------------------
	{
		bool isOk = m_eType==jIVar::ETelement || m_eType == jxVar::EDcstr || m_eType == jxVar::EDStringID;
#ifdef _DEBUG
		if(!isOk)
		{
			printf("");
		}
#endif
		jRETURN_ret("",isOk);
		//jRAISE
		//jASSERT0(isOk);

		if(m_eType == jxVar::EDStringID)	
		{
			//return nString::Get_jIStringTable()->GetName(m_StringID);
		}
		return m_cstr.c_str();
	}
	bool		jxVar::operator <(const  jxVar& var) const 
	{
		jRETURN_ret(0,!IsOuterMemorySource());
		//jASSERT0(!IsOuterMemorySource());

		if(m_eType!= var.m_eType) return false;
		else if(m_eType==EDfloat )
			return Get_float() < var.Get_float();
		else if(m_eType  < EDataType_SIMPLE_INT_END)
			return (Get_int() < var.Get_int());
		else if( EDcstr)
			return ( 0  > jt_strcmp( Get_cstr() , var.Get_cstr() ) );
		else
			throw _T("jxVar operator == error");
		return false;
	}

	//--------------------------------------------------------------------------
	bool		jxVar::operator ==(const  jxVar& var) const
		//--------------------------------------------------------------------------
	{
		bool isRet = false;

		jRETURN_ret(0,!IsOuterMemorySource());
		//jASSERT0(!IsOuterMemorySource());
		if(GetType()==EDbool || var.GetType()==EDbool)
		{
			isRet = ( Get_bool() && var.Get_bool());
		}
		else if(IsIntSizeValue() && var.IsIntSizeValue())
		{
			isRet =  (Get_int()==var.Get_int());
		}
		else if( IsStringValue() && var.IsStringValue())
		{
			isRet = ( !jt_strcmp( Get_cstr() , var.Get_cstr() ) );
		}
		else if(IsArrayValue())
		{
			isRet = !memcmp(m_int_p ,var.m_int_p , sizeof(int) * GetArraySize() );
		}
		else
		{
			throw _T("jxVar operator == error");
		}
		return isRet;
	}

	//--------------------------------------------------------------------------
	int jxVar::GetArraySize() const 
		//--------------------------------------------------------------------------
	{
		int itot=0;
		if(IsIntArray() )
		{
			if(m_eType==EDint2) itot = 2;
			else if(m_eType==EDint3 ) itot = 3;
			else if(m_eType==EDint4 ) itot = 4;
		}
		else if( IsFloatArray() )
		{
			if(m_eType==EDvector2) itot = 2;
			else if(m_eType==EDvector3) itot = 3;
			else if(m_eType==EDvector4) itot = 4;
			else if(m_eType==EDmatrix44) itot = 4*4;
			else if(m_eType==EDmatrix33) itot = 3*3;
		}
		else
		{
			throw _T("EDataType_ARRAY error");
		}
		return itot;
	}

	void jxVar::CopyTo(jIVar* pvDest)const  // 자료형관계없이 무조건복사.
	{
		*((jxVar*)pvDest) = *this;
	}

	void  jxVar::SetType(EElementType eT)
	{ 
		if(m_eType==eT) return ;
		delete_array_ptr();

		m_eType = eT;
		if( IsArrayValue())
		{
			uint itot=GetArraySize();
			jNEWi(m_int_p , int , itot );
			memset(m_int_p , 0 , sizeof(int)*itot);
		}
		else if(m_eType==EDcstr)
		{
			m_cstr=_T("");
		}
		return ;
	}

#define __setter_code(X)		jxVar& jxVar::	operator= ( X ii) \
	{ \
	SetType(ED##X);\
	Set_##X(ii);\
	return *this;\
	}

	_for_each_setter_type_jvar(__setter_code)


		jxVar& jxVar::	operator= (const std::tstring& ii) { 	*this = ii.c_str();	return *this; }

		float& jxVar::GetFloat(int i)
		{ 
			jCHECK(IsFloatArray());
			//jASSERT0(IsFloatArray() ); 
			return m_float_p[i];
		}
		int& jxVar::GetInt(int i)
		{ 
			jCHECK(IsIntArray());
			//jASSERT0( IsIntArray() ); 
			return m_int_p[i];
		}
		uchar jxVar::Get_A()const 
		{ 
			//jASSERT0(m_eType==EDargb); 
			return  ((uchar)((m_int)>>24));
		}
		uchar jxVar::Get_R()const 
		{ 
			//jASSERT0(m_eType==EDargb); 
			return  GetBValue(m_int);
		}
		uchar jxVar::Get_G()const 
		{ 
			//jASSERT0(m_eType==EDargb); 
			return  GetGValue(m_int);
		}

		uchar jxVar::Get_B()const 
		{ 
			//jASSERT0(m_eType==EDargb); 
			return  GetRValue(m_int);
		}


		uint			jxVar::Get_ARGB()const 
		{ 
			jASSERT0(m_eType == EDargb); 
			return m_uint;	
		}
		uint			jxVar::Get_RGB()const 
		{ 
			jASSERT0(m_eType == EDrgb); 
			return m_uint;	
		}
		POINT* jxVar::GetPOINT()
		{
			jASSERT0(m_eType==EDint2);
			return (POINT*)GetIntP();
		}

		RECT* jxVar::GetRECT()
		{ 
			jASSERT0(m_eType == EDint4);
			return (RECT*)GetIntP();
		}

		RECT jxVar::GetRect()const 
		{
			jASSERT0(m_eType == EDint4);
			return *(RECT*)m_int_p;
		}

		bool jxVar::IsUserDataOK()const { 	return true;}
		void jxVar::SetUserData(void* pV)	
		{		
			jASSERT0( IsUserDataOK() ); 
			m_void_p = pV;	
		}
		void* jxVar::GetUserData()			const 
		{	
			jASSERT0( IsUserDataOK() );
			return m_void_p;	
		}
		bool jxVar::IsNULL() const
		{ 
			if(m_eType==EDcstr)
			{
				return m_cstr.size();
			}
			return false;
		}


		void jxVar::delete_array_ptr()
		{
			if(IsOuterMemorySource())
				return;

			if(!m_int_p) return;

			if( IsArrayValue())
			{
				delete [] m_int_p;
				m_int_p=0;
			}
			else if(m_eType==EDcstr)
			{
				m_cstr.clear();
			}
		}



		int  jxVar::IsFloatArray()const 
		{
			if(m_eType > EDataType_FLOAT_ARRAY_BEGIN && m_eType <EDataType_FLOAT_ARRAY_END)
				return m_eType;
			return 0;
		}
		int jxVar::IsIntArray()const 
		{
			if (m_eType > EDataType_INT_ARRAY_BEGIN && m_eType <EDataType_INT_ARRAY_END)
				return m_eType;
			return 0;
		}
		bool jxVar::IsNotArrayValue()const  // IsIntSizeValue() 이거나 EDcstr형이면 true리턴
		{
			return m_eType  < EDataType_SIMPLE_END;
		}
		int jxVar::IsArrayValue() const // Array value이면 해당 type을 아니면 0을 리턴.
		{
			if ( m_eType >= jxVar::EDataType_ARRAY_BEGIN  && m_eType <= jxVar::EDataType_ARRAY_END )
				return m_eType;
			return 0;
		}
		int jxVar::IsIntValue()const  // IsIntArray()이거나 EDint형이면 해당 type리턴
		{
			if(m_eType == jxVar::EDint || 		 IsIntArray() )
				return m_eType;
			return 0;
		}

		bool jxVar::IsOuterMemorySource() const
		{
			return c8InnerOption & eIS_OUTER_MEMORY;
		}


		bool jxVar::IsIntSizeValue()const  // sizeof(int)인 값이면 true 이다.  int , uint , float , jStringID 등등
		{
			if( m_eType <=EDataType_SIMPLE_INT_END)
				return true;
			return false;
		}
		bool jxVar::IsStringValue() const 
		{
			return (m_eType == EDcstr|| m_eType==EDStringID || m_eType == ETelement);
		}

		void jxVar::Lerp(jIVar* pIV1, jIVar* pIV2 , float fLerpRatio)
		{
			if(!pIV1 || !pIV2 ) return;
			jxVar* pV1 = pIV1->Base();
			jxVar* pV2 = pIV2->Base();
			if(pV1->m_eType!=pV2->m_eType) return;
			if(m_eType!=pV2->m_eType) return;

			switch(m_eType)
			{
			case EDbool:
				{
					Set_bool(  (fLerpRatio<0.5) ? pV1->Get_bool() : pV2->Get_bool() );
					break;
				}
			case EDint:
			case EDhex:
				{
					float fV2 = (float)pV1->Get_int() + fLerpRatio * (float)(pV2->Get_int() - pV1->Get_int());
					Set_int( (int)fV2 );
					break;
				}
			case EDuint:
				{
					float fV2 = (float)pV1->Get_int() + fLerpRatio * (float)(pV2->Get_int() - pV1->Get_int());
					Set_uint( (uint)fV2);
					break;
				}
			case EDfloat:
				{
					Set_float( pV1->Get_float() + fLerpRatio * (pV2->Get_float() - pV1->Get_float()) );
					break;
				}
			case EDargb:
				{
					float r = pV1->Get_R() + fLerpRatio * (pV2->Get_R() - pV1->Get_R());
					float g = pV1->Get_G() + fLerpRatio * (pV2->Get_G() - pV1->Get_G());
					float b = pV1->Get_B() + fLerpRatio * (pV2->Get_B() - pV1->Get_B());
					float a = pV1->Get_A() + fLerpRatio * (pV2->Get_A() - pV1->Get_A());
					m_int = jD3DCOLOR_ARGB((int)a,(int)r,(int)g,(int)b);
					break;
				}
			case EDrgb:
				{
					float r = pV1->Get_R() + fLerpRatio * (pV2->Get_R() - pV1->Get_R());
					float g = pV1->Get_G() + fLerpRatio * (pV2->Get_G() - pV1->Get_G());
					float b = pV1->Get_B() + fLerpRatio * (pV2->Get_B() - pV1->Get_B());
					m_int = RGB((int)r,(int)g,(int)b);
					break;
				}
			case EDStringID:
				{
					Set_StringID(  (fLerpRatio<0.5) ? pV1->Get_StringID() : pV2->Get_StringID() );
					break;
				}
			case EDcstr:
				{
					Set_cstr(  (fLerpRatio<0.5) ? pV1->Get_cstr() : pV2->Get_cstr() );
					break;
				}
			case EDint2:
				{
					m_int_p[0] = (int)( pV1->m_int_p[0] + fLerpRatio * (pV2->m_int_p[0] - pV1->m_int_p[0]  )  );
					m_int_p[1] = (int)( pV1->m_int_p[1] + fLerpRatio * (pV2->m_int_p[1] - pV1->m_int_p[1]  )  );
					break;
				}
			case EDint3:
				{
					m_int_p[0] = (int)( pV1->m_int_p[0] + fLerpRatio * (pV2->m_int_p[0] - pV1->m_int_p[0]  )  );
					m_int_p[1] = (int)( pV1->m_int_p[1] + fLerpRatio * (pV2->m_int_p[1] - pV1->m_int_p[1]  )  );
					m_int_p[2] = (int)( pV1->m_int_p[2] + fLerpRatio * (pV2->m_int_p[2] - pV1->m_int_p[2]  )  );
					break;
				}

			case EDint4:
				{
					m_int_p[0] = (int)( pV1->m_int_p[0] + fLerpRatio * (pV2->m_int_p[0] - pV1->m_int_p[0]  )  );
					m_int_p[1] = (int)( pV1->m_int_p[1] + fLerpRatio * (pV2->m_int_p[1] - pV1->m_int_p[1]  )  );
					m_int_p[2] = (int)( pV1->m_int_p[2] + fLerpRatio * (pV2->m_int_p[2] - pV1->m_int_p[2]  )  );
					m_int_p[3] = (int)( pV1->m_int_p[3] + fLerpRatio * (pV2->m_int_p[3] - pV1->m_int_p[3]  )  );
					break;
				}
			case EDvector2:
				{
					m_float_p[0] = ( pV1->m_float_p[0] + fLerpRatio * (pV2->m_float_p[0] - pV1->m_float_p[0]  )  );
					m_float_p[1] = ( pV1->m_float_p[1] + fLerpRatio * (pV2->m_float_p[1] - pV1->m_float_p[1]  )  );
					break;
				}
			case EDvector3:
				{
					m_float_p[0] = ( pV1->m_float_p[0] + fLerpRatio * (pV2->m_float_p[0] - pV1->m_float_p[0]  )  );
					m_float_p[1] = ( pV1->m_float_p[1] + fLerpRatio * (pV2->m_float_p[1] - pV1->m_float_p[1]  )  );
					m_float_p[2] = ( pV1->m_float_p[2] + fLerpRatio * (pV2->m_float_p[2] - pV1->m_float_p[2]  )  );
					break;
				}
			case EDvector4:
				{
					m_float_p[0] = ( pV1->m_float_p[0] + fLerpRatio * (pV2->m_float_p[0] - pV1->m_float_p[0]  )  );
					m_float_p[1] = ( pV1->m_float_p[1] + fLerpRatio * (pV2->m_float_p[1] - pV1->m_float_p[1]  )  );
					m_float_p[2] = ( pV1->m_float_p[2] + fLerpRatio * (pV2->m_float_p[2] - pV1->m_float_p[2]  )  );
					m_float_p[3] = ( pV1->m_float_p[3] + fLerpRatio * (pV2->m_float_p[3] - pV1->m_float_p[3]  )  );
					break;
				}
			}
		}//void jxVar::Lerp(jIVar* pIV1, jIVar* pIV2 , float fLerpRatio)

}//namespace nMech
