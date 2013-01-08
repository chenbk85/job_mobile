

/* file : jVar.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-21 12:44:13
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jVar_header__
#define __jVar_header__
#pragma once
#include <assert.h>

#define _jV assert


#define jAutoPtr_abstruct_CTOR(MY_TYPE, MY_INTERFACE_TYPE)\
	private:	MY_INTERFACE_TYPE* m_pPtr;\
	public:\
	typedef MY_TYPE type_t;\
	typedef MY_INTERFACE_TYPE interface_t;\
	MY_TYPE& operator =(MY_INTERFACE_TYPE* pV) 	{ 		SET(pV);	return *this;}\
	MY_TYPE& operator =(const MY_TYPE& v){	SET(v.m_pPtr);	return *this;}\
	void SET(MY_INTERFACE_TYPE* pV) { m_pPtr = pV;}\
	void SET(MY_INTERFACE_TYPE* pV,bool) { m_pPtr = pV; validate();}\
	void clear(){ m_pPtr=0;}\
	bool empty(){ return m_pPtr==0;}\
	bool full(){ return m_pPtr!=0;}\
	void validate()	{jASSERT0(m_pPtr!=0);	}\
	MY_INTERFACE_TYPE* operator->() const{ return m_pPtr;}\
	MY_INTERFACE_TYPE* BaseI(){ return m_pPtr;}\
	operator MY_INTERFACE_TYPE*() const	{		return m_pPtr;	}\
	MY_TYPE(){clear();}\
	MY_TYPE(const MY_TYPE& v)	{ SET(v.m_pPtr) ; }\
	MY_TYPE(MY_INTERFACE_TYPE* pV)	{ SET(pV);	} \
	MY_TYPE(const MY_TYPE& v,bool )	{ SET(v.m_pPtr,true) ; }\
	MY_TYPE(MY_INTERFACE_TYPE* pV, bool ){ SET(pV,true); }\


namespace nMech
{
		struct jVar //: //public jAutoPtr_abstruct<jVar,  jIVar>
		{
			jAutoPtr_abstruct_CTOR(jVar, jIVar)

			// 대입문의 자료형을 jIVar자신의 자료형에 따라 자동 컨버팅하여 값을 세팅하기 위한 객체
			struct jConvertByMyType
			{
				jIVar* pV;
				//jConvertByMyType(){}는 허용안함.
				jConvertByMyType(const jVar& there):pV(there.m_pPtr){}
				jConvertByMyType(const jConvertByMyType& there):pV(there.pV){}
				jConvertByMyType(jIVar* there):pV(there){}

				jConvertByMyType& operator =(const jConvertByMyType& there)	{	return operator=(there.pV);	}
				jConvertByMyType& operator =(const jVar& there)	{	return operator=(there.m_pPtr);	}
				jConvertByMyType& operator =(jIVar* there)
				{ 
					if(!pV->IsType(there->GetType())) throw _T(__FUNCTION__);
					there->CopyTo(pV); return *this;
				}
				jConvertByMyType& operator =(tcstr there){ pV->FromString(there); return *this;}
				#define _jConvertByMyType_operator_set(TYPE) \
					jConvertByMyType& operator =(TYPE data){ if(!pV->IsType(jIVar::ED##TYPE)) throw _T(__FUNCTION__);if(pV)pV->Set_##TYPE(data);return *this;}
				_for_each_simple_type_jvar(_jConvertByMyType_operator_set);
				
				jConvertByMyType& operator =(std::tstring data)
				{ if(!pV->IsType(jIVar::EDcstr)) throw _T(__FUNCTION__);if(pV)pV->Set_cstr(data.c_str());return *this;}
			};

			// 대입문(=)의 자료형에 따라 jIVar의 자료형을 변경하고 값을 세팅하기위한 유틸 객체
			// type convert by data
			struct jConvertByThereType 
			{
				jIVar* pV;
				//jConvertByThereType(){}는 허용안함.
				jConvertByThereType(const jVar& there):pV(there.m_pPtr){}
				jConvertByThereType(const jConvertByThereType& there):pV(there.pV){}
				jConvertByThereType(jIVar* there):pV(there){}

				jConvertByThereType& operator =(const jConvertByThereType& there)	{	return operator=(there.pV);	}
				jConvertByThereType& operator =(const jVar& there)	{	return operator=(there.m_pPtr);	}
				jConvertByThereType& operator =(jIVar* there)
				{ 
					there->CopyTo(pV);
					return *this;
				}

				#define _jConvertByThereType_operator_set(TYPE) \
					jConvertByThereType& operator =(TYPE there)	{ pV->SetType(jIVar::ED##TYPE); pV->Set_##TYPE(there); return *this;}
				_for_each_setter_type_jvar(_jConvertByThereType_operator_set);
				
				jConvertByThereType& operator =(std::tstring there)	{ pV->SetType(jIVar::EDcstr); pV->Set_cstr(there.c_str()); return *this;}
			};

#if 0
			struct jPredicater
			{
				jIVar* pV;
				jPredicater(const jVar& there):pV(there.m_pPtr){}
				jPredicater(const jPredicater& there):pV(there.pV){}
				jPredicater(jIVar* there):pV(there){}
			};
#endif


			jConvertByMyType M(){ return jConvertByMyType(m_pPtr);}
			jConvertByThereType T() { return jConvertByThereType(m_pPtr);}


				//~jVar() { m_pPtr =0;}
			jVar& SetType(jIVar::EElementType e){ m_pPtr->SetType(e); return *this;}

			operator int()
			{ 
				if(!m_pPtr) return false;

				_jV(m_pPtr->IsIntSizeValue()); 
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				return m_pPtr->Get_int();
			}
			operator bool()
			{ 
				if(!m_pPtr) return false;

				_jV(m_pPtr->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				return m_pPtr->Get_bool();
			}
			operator uint()
			{ 
				if(!m_pPtr) return false;

				_jV(m_pPtr->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				return m_pPtr->Get_uint();
			}

			operator float()
			{
				_jV(m_pPtr->GetType()==jIVar::EDfloat) ;
				return  m_pPtr->Get_float();
			}
			operator double()
			{ 
				_jV(m_pPtr->GetType()==jIVar::EDfloat) ;
				return (double)m_pPtr->Get_float();
			}
			operator nMech::StringID() { _jV(m_pPtr->GetType()==jIVar::EDStringID ); return m_pPtr->Get_StringID();}

			operator int*(){_jV(m_pPtr->IsIntArray() ); return m_pPtr->GetIntP();}
			operator float*(){ _jV(m_pPtr->IsFloatArray()); return m_pPtr->GetFloatP();}
			operator cstr (){ _jV(m_pPtr->IsStringValue());return m_pPtr->Get_cstr();}
			operator POINT() { _jV(m_pPtr->IsIntArray()); return *m_pPtr->GetPOINT();}
			operator RECT() { _jV(m_pPtr->IsIntArray()); return  m_pPtr->GetRect();}
			bool StringEquals(cstr sz){	_jV(m_pPtr->IsStringValue()); return jt_strcmp(sz, m_pPtr->Get_cstr() )==0;	}
			operator std::tstring(){ fname_t buf; m_pPtr->ToString(buf); return std::tstring(buf);}

			jVar& operator =( bool i)
			{
				_jV(m_pPtr->IsIntSizeValue()); 
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				m_pPtr->Set_bool(i); 
				return *this;
			}
			jVar& operator =( int i)
			{ 
				_jV(m_pPtr->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat);
				m_pPtr->Set_int(i); 
				return *this;
			}
			jVar& operator =( uint i)
			{ 
				_jV(m_pPtr->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				m_pPtr->Set_uint(i); 
				return *this;
			}

			jVar& operator =( float  i)
			{ 
				_jV(m_pPtr->IsIntSizeValue());
				_jV(m_pPtr->GetType()==jIVar::EDfloat);
				m_pPtr->Set_float(i); 
				return *this;
			}
			jVar& operator =( double i)
			{ 
				_jV(m_pPtr->IsIntSizeValue());
				_jV(m_pPtr->GetType()==jIVar::EDfloat);
				m_pPtr->Set_float((float)i); 
				return *this;
			}

			jVar& operator =(const cstr i){ _jV(m_pPtr->IsStringValue());m_pPtr->Set_cstr(i); return *this;}
			jVar& operator =(const std::tstring & i){_jV(m_pPtr->IsStringValue()); m_pPtr->Set_cstr(i.c_str()) ;return *this;}
			jVar& operator =(nMech::StringID i){ _jV(m_pPtr->IsIntSizeValue());m_pPtr->Set_StringID(i);return *this;}
			jVar& operator =(const POINT& i)
			{
				_jV(m_pPtr->IsIntValue()&& m_pPtr->IsArrayValue()); 
				m_pPtr->GetInt(0) = i.x , m_pPtr->GetInt(1)=i.y;
				return *this;
			}
			jVar& operator =(const RECT& i)
			{ 
				_jV(m_pPtr->IsIntValue()&& m_pPtr->IsArrayValue());
				m_pPtr->GetInt(0) = i.left;  m_pPtr->GetInt(1) = i.top; 
				m_pPtr->GetInt(2) = i.right; m_pPtr->GetInt(3) = i.bottom; 
				return *this;
			}

		};

#define __FOR_EACH_OP(_N_ , type) _N_(== , type ) _N_(< , type ) _N_(>, type) _N_(!=, type ) _N_(<=, type ) _N_(>=, type) 
#define	__genarate_code(op,type) inline bool operator op(jVar &v ,  type i)  { return (v.BaseI()->Get_##type() op i) ; }\
	inline bool operator op(  type i, jVar &v )  { return (v.BaseI()->Get_##type() op i) ; }
#define __genarate_code_for_Type(type) __FOR_EACH_OP( __genarate_code , type);
		// jVar에 대해 _for_each_simple_type_jvar에 언급된 자료형과 __FOR_EACH_OP에 
		// 언급된 오퍼레이팅이 호환되게정의
		// jxVar _v = "asdf" ;		jVar v = _v;  assert(v=="asdf");
		_for_each_simple_type_jvar(__genarate_code_for_Type);

#define jGENERATE_OPERATOR(typeL, typeR, equal_code , lessthen_code) \
	inline bool operator ==(typeL &valL , typeR &valR)	{		return equal_code;	}\
	inline bool operator < (typeL &valL , typeR &valR)	{		return lessthen_code;	}\
	inline bool operator !=(typeL &valL,typeR &valR)	{		return !(valL == valR) ;}\
	inline bool operator > (typeL &valL,typeR &valR)	{		return !( (valL==valR) && (valL  < valR) );}\
	inline bool operator <=(typeL &valL,typeR &valR)	{		return ( (valL ==valR ) || (valL < valR) );}\
	inline bool operator >= (typeL &valL,typeR &valR){		return !(valL < valR);}


		jGENERATE_OPERATOR(jVar, jVar, valL.BaseI()->IsEqual(valR.BaseI()) , valL.BaseI()->IsLessThen(valR.BaseI()) );
		//jGENERATE_OPERATOR(jVar, double, ( valL.m_pPtr->Get_float()==(float)valR) ,(valL.m_pPtr->Get_float() < (float)valR) );
		//jGENERATE_OPERATOR_RL(jVar, double, ( valL.m_pPtr->Get_float()==(float)valR) ,(valL.m_pPtr->Get_float() < (float)valR) );

#define __OP_EQUAL_STR(typeL, typeR , func , arg )\
	inline bool operator ==(typeL &v , typeR varR){ return v.BaseI()->func(arg) ;}\
	inline bool operator !=(typeL &v , typeR varR){ return !(v == arg );}\
	inline bool operator ==(typeR varR , typeL &v){ return v == arg ;}\
	inline bool operator !=(typeR varR , typeL &v){ return !(v == arg );}

		__OP_EQUAL_STR(jVar, cstr , IsContents , varR );
		__OP_EQUAL_STR(jVar, std::tstring , IsContents , varR.c_str() );

#define vNULL ((jIVar*)0)

#undef _jV


}
#endif // __jVar_header__
