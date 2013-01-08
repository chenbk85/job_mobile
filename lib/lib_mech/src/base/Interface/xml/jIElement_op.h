/* file : jE.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-21 12:44:13
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jE_header__
#define __jE_header__
#pragma once

#include "Interface/xml/jIVar_op.h"
#include <Windows.h>

namespace nMech
{
	namespace nXML
	{
		struct jIDocument;
	}
	typedef nXML::jIDocument jID;
	namespace nXML
	{
		struct jIDocument;
#define _jV assert

		//--------------------------------------------------------------------------
		struct jE //: public jAutoPtr_abstruct<jE,  jIE>
			//--------------------------------------------------------------------------
		{
			jAutoPtr_abstruct_CTOR(jE, jIE);

			jE& SetType(jIVar::EElementType e){ m_pPtr->GetVar()->SetType(e); return *this;}
			jE begin(){ return m_pPtr ? m_pPtr->begin() : jE();}
			jE end() { return jE();}
			jE GetNext(){ return m_pPtr ? m_pPtr->GetRight() : jE();}
			jE GetPrev(){ return m_pPtr ? m_pPtr->GetLeft() : jE();}
			size_t size() { return m_pPtr ? m_pPtr->size() : 0;}

			// jID*관련 유틸함수
			jE(jID* pD)	{ if(!pD)m_pPtr=0;else SET(pD->BaseI());	}
			jE(jID* pD,bool isCheck)	{ SET(pD ? pD->BaseI() : 0 , isCheck);	}
			jE& operator =(jID* pD) 	{ 		SET(pD ? pD->BaseI():0);		return *this;	}
			operator jID*() const	{		return m_pPtr? m_pPtr->GetDoc():0;}

			operator int()
			{ 
				if(!m_pPtr) return false;
				_jV(m_pPtr->GetVar()->IsIntSizeValue()); 
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				return m_pPtr->GetVar()->Get_int();
			}
			operator bool()
			{ 
				if(!m_pPtr) return false;
				_jV(m_pPtr->GetVar()->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				return m_pPtr->GetVar()->Get_bool();
			}
			operator uint()
			{ 
				if(!m_pPtr) return false;
				_jV(m_pPtr->GetVar()->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				return m_pPtr->GetVar()->Get_uint();
			}
			operator float()
			{
				_jV(m_pPtr->GetType()==jIVar::EDfloat) ;
				return  m_pPtr->GetVar()->Get_float();
			}
			operator double()
			{ 
				_jV(m_pPtr->GetType()==jIVar::EDfloat) ;
				return (double)m_pPtr->GetVar()->Get_float();
			}
			jVar Var(){ if(m_pPtr) return m_pPtr->GetVar(); return jVar(); }
			operator jVar(){ if(m_pPtr) return m_pPtr->GetVar(); return jVar(); }
			operator jIVar*() { if(m_pPtr) return m_pPtr->GetVar(); return 0; }
			operator tcstr (){ if(!m_pPtr) return 0;  _jV(m_pPtr->GetVar()->IsStringValue());return m_pPtr->GetVar()->Get_cstr();}

			operator nMech::StringID() { _jV(m_pPtr->GetType()==jIVar::EDStringID ); return m_pPtr->GetVar()->Get_StringID();}
			operator POINT() { _jV(m_pPtr->GetVar()->IsIntArray()); return *m_pPtr->GetVar()->GetPOINT();}
			operator RECT() { _jV(m_pPtr->GetVar()->IsIntArray()); return  m_pPtr->GetVar()->GetRect();}

			jE& operator =( bool i)
			{
				_jV(m_pPtr->GetVar()->IsIntSizeValue()); 
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				m_pPtr->GetVar()->Set_bool(i); 
				return *this;
			}
			jE& operator =( int i)
			{ 
				_jV(m_pPtr->GetVar()->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat);
				m_pPtr->GetVar()->Set_int(i); 
				return *this;
			}
			jE& operator =( uint i)
			{ 
				_jV(m_pPtr->GetVar()->IsIntSizeValue());
				_jV(m_pPtr->GetType()!=jIVar::EDfloat) ;
				m_pPtr->GetVar()->Set_uint(i); 
				return *this;
			}

			jE& operator =( float  i)
			{ 
				_jV(m_pPtr->GetVar()->IsIntSizeValue());
				_jV(m_pPtr->GetType()==jIVar::EDfloat);
				m_pPtr->GetVar()->Set_float(i); 
				return *this;
			}
			jE& operator =( double i)
			{ 
				_jV(m_pPtr->GetVar()->IsIntSizeValue());
				_jV(m_pPtr->GetType()==jIVar::EDfloat);
				m_pPtr->GetVar()->Set_float((float)i); 
				return *this;
			}

			jE& operator =(const tcstr i){ _jV(m_pPtr->GetVar()->IsStringValue());m_pPtr->GetVar()->Set_cstr(i); return *this;}
			jE& operator =(const std::tstring & i){_jV(m_pPtr->GetVar()->IsStringValue()); m_pPtr->GetVar()->Set_cstr(i.c_str()) ;return *this;}
			jE& operator =(nMech::StringID i){ _jV(m_pPtr->GetVar()->IsIntSizeValue());m_pPtr->GetVar()->Set_StringID(i);return *this;}
			jE& operator =(const POINT& i)
			{
				_jV(m_pPtr->GetVar()->IsIntValue()&& m_pPtr->GetVar()->IsArrayValue()); 
				m_pPtr->GetVar()->GetInt(0) = i.x , m_pPtr->GetVar()->GetInt(1)=i.y;
				return *this;
			}
			jE& operator =(const RECT& i)
			{ 
				_jV(m_pPtr->GetVar()->IsIntValue()&& m_pPtr->GetVar()->IsArrayValue());
				m_pPtr->GetVar()->GetInt(0) = i.left;  m_pPtr->GetVar()->GetInt(1) = i.top; 
				m_pPtr->GetVar()->GetInt(2) = i.right; m_pPtr->GetVar()->GetInt(3) = i.bottom; 
				return *this;
			}

			//  eName["TYPE"]  -> eName엘리먼트 바로 밑 자식에 "TYPE"있으면 그것을 리턴하고 없으면 만들어서 리턴.
			jE operator[](const std::tstring& sz){ return operator[](sz.c_str());	}
			jE operator[](tcstr sz){	return m_pPtr->Persist(sz,jIVar::ETelement);	}
			jE operator[](StringID sz){	return m_pPtr->Persist(sz,jIVar::ETelement);	}

			// eName("TYPE")   -> eName엘리먼트 자식중에 "TYPE"있으면 그걸 리턴. 없으면 null객체를 리턴.
			jE operator()(const std::tstring &s){ if(!m_pPtr) return jE(); return m_pPtr->Find(s.c_str()) ; }
			jE operator()(tcstr sz)	{	if(m_pPtr) {  jIE* pE = m_pPtr->Find(sz); if(pE) return pE; } return jE();}
			jE operator()(nMech::StringID sz)	{	if(m_pPtr) {  jIE* pE = m_pPtr->Find(sz); 	if(pE) return pE; } return jE();}
			jE operator()(int idx)
			{
				if(!m_pPtr)  return jE();
				else if(idx < 0)
				{
					jIE* pE=m_pPtr;
					idx = -idx;
					for(int i=0; i < idx; ++i)
					{
						if(pE->isRoot()) return jE();
						pE = pE->GetParent();
					}
					return pE;
				}

#pragma warning(disable:4018)
				else if(m_pPtr->size() > idx) 
#pragma warning(default:4018)
				{
					jIE* pE = m_pPtr->FindByOrder(idx);
					if( pE) return pE;
				}
				return jE();
			}
			
			//  eName.AttrP["TYPE"]  -> eName엘리먼트 속성중에 "TYPE"있으면 그것을 리턴하고 없으면 만들어서 리턴.
			jVar AttrP(const std::tstring &s){ return AttrP(s.c_str());}
			jVar AttrP(tcstr sz){ return m_pPtr->PersistAttr(sz,jIVar::ETelement) ;}
			jVar AttrP(StringID sz){ return m_pPtr->PersistAttr(sz,jIVar::ETelement); }

			// eName.Attr(TEXT("TYPE"))   -> eName엘리먼트 속성중에 "TYPE"있으면 그걸 리턴. 없으면 null객체를 리턴.
			jVar Attr(const std::tstring &s){ jIVar* pV = m_pPtr->GetAttrVar(s.c_str() ); if(pV) return pV; return jVar();}
			jVar Attr(tcstr sz){ jIVar* pV = m_pPtr->GetAttrVar(sz); if(pV) return pV; return jVar();}
			jVar Attr(StringID sz){ jIVar* pV = m_pPtr->GetAttrVar(sz); if(pV) return pV; return jVar();}

			jVar::jConvertByMyType M(){ return Var().M();}
			jVar::jConvertByThereType T() { return Var().T();}


		};

#undef __genarate_code
#define	__genarate_code(op,type) inline bool operator op(jE &e ,  type i)  { return (e.BaseI()->GetVar()->Get_##type() op i) ; }\
	inline bool operator op(  type i, jE &e )  { return (e.BaseI()->GetVar()->Get_##type() op i) ; }

		_for_each_simple_type_jvar(__genarate_code_for_Type);

		jGENERATE_OPERATOR(jE, jE, valL.BaseI()->GetVar()->IsEqual(valR.BaseI()->GetVar()) , valL.BaseI()->GetVar()->IsLessThen(valR.BaseI()->GetVar()) );

		__OP_EQUAL_STR(jE, tcstr , GetVar()->IsContents , varR )
			__OP_EQUAL_STR(jE, std::tstring , GetVar()->IsContents , varR.c_str() )


#define eNULL ((jIE*)0)

#undef _jV

	}//nXML

}
#endif // __jE_header__
