/* file : jxVar_test.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2006-12-14 13:59:50
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jxVar.h"
#include "header\\yVector.h"
#include "header\\jMemoryChunk.h"
#include "base/jString_mem.h"
#include "base/jIndexedString.h"
#include "Interface/jILog.h"
#include "Interface/jITestUnit.h"
#include "interface/xml/jIVar_op.h"
#include "interface/xml/jIXml.h"


//--------------------------------------------------------------------------
// jxVar관련 테스트
//--------------------------------------------------------------------------
#pragma warning(disable : 4805)

namespace nMech
{

	void jTYPE_ADAPTER_TestUnit()
	{
#undef V
#define  V(x)  jAssert0(x)

#undef _jcode_ 
#define _jcode_ 1,2

		float a2[2]={1,2};
		float b2[2]={1,2};
		float* pf2 = b2;
		jFloat2 f2=a2;
		V(f2==b2);
		f2=b2;
		V(f2==pf2);

	}


	void jRECT_TestUnit()
	{
#ifdef jUSE_JRECT
#undef V
#define  V(x)  jAssert0(x && _T("jRECT_TestUnit()"))

		jRECT a,b;
		RECT c;
		a.clear();b.clear();
		memset(&c,0,sizeof(c));
		V(sizeof(a)==sizeof(int)*4);
		V(sizeof(a)==sizeof(uint)*4);
		V(sizeof(a)==sizeof(LONG)*4);
		V(!memcmp(&a,&c,sizeof(a) ) );
#undef _jcomp_
#define _jcomp_(a,op ,c)  ((a.ux op c.left) && (a.uy op c.top) && (a.uw op c.right) && (a.uh op c.bottom))
		V( _jcomp_(a,==,c) );
		a.x=a.y=a.w=a.h =-10;
		V( _jcomp_(a,!=,c) );
		memcpy(&c , &a , sizeof(a));
		V( _jcomp_(a,==,c) );
		jRECT d = c;
		V(_jcomp_(d,==,c));
		RECT e = d;
		V(_jcomp_(a,==,e));

#undef _jcomp_

#endif //jUSE_JRECT
	}

	void jxVar::TestUnit(jIE* peTestNode)
	{
		//#define jNOT_USE_TEST
#ifndef jNOT_USE_TEST
#undef V
#define  V(x)  jAssert0(x && _T("jxVar::TestUnit()"))
#define  V2(x)  jAssert0(x && ( _T("jxVar::TestUnit() ") _T(#x) ) )

		jTYPE_ADAPTER_TestUnit();
		jRECT_TestUnit();

		jxVar v_jxVar;
		jVar v_jVar = &v_jxVar;
		v_jVar.SET(&v_jxVar);
#define __type_check__jvar(type) \
	V2(v_jxVar.GetType() == jIVar::type);\
	V2(std::tstring(_T(#type)) ==  v_jxVar.GetTypeString());\
	V2(v_jVar->GetType() == jIVar::type);\
	V2(std::tstring(_T(#type)) ==  v_jVar->GetTypeString());

#define _jTEST_(var  , op , val) V2(var op val); V2(val op var);
#define __value_check_jvar(val) _jTEST_(v_jVar ,==,val);
#define __type_value_check__(val,type) \
	__type_check__jvar(ED##type); __value_check_jvar(val); { type temp = v_jVar; V2(temp==val) ;}
#define __type_value_check(val,type) \
	v_jVar->SetType(jIVar::ED##type); v_jVar=val; 	__type_value_check__(val,type);

#if 0 
		// double형은 구현안함.
		__type_value_check(1.3,float);
#endif
		__type_value_check(10 , int);
		__type_value_check(1.3f,float);
		__type_value_check(false,bool);
		__type_value_check(16u,uint);

		v_jVar->SetType(EDuint);
		v_jVar = 16u; 
		__type_value_check__(16,uint);

		v_jVar->SetType(EDStringID);
		v_jVar = jx(NULL);	
		__type_check__jvar(EDStringID); __value_check_jvar(_T("NULL")); 

		v_jVar->SetType(EDcstr);
		v_jVar = _T("test code");
		__type_check__jvar(EDcstr); __value_check_jvar(_T("test code"));

		V(v_jVar ==std::tstring(_T("test code")) );
		std::tstring s = v_jVar;
		jxVar jxV2;
		jxV2.InitValue(_T("test"),EDcstr);
		jVar vv2 = &jxV2;
		vv2 = _T("test code2");
		V(v_jVar!= vv2);
		V(v_jVar== s);
		//V(s == v_jVar);


		{// int* 와 bool* 의 호환테스트
			jxVar jxV_A ,jxV_B;
			int int_val = 0;
			jxV_A.m_int = 1;
			jxV_B.m_bool_p = reinterpret_cast<bool* > (&int_val);
			V(jxV_A.m_int != *jxV_B.m_bool_p);

			bool bool_val = true;
#if 0 
			//--------------------------------------------------------------------------
			// Run-Time Check Failure #2 - Stack around the variable 'bool_val' was corrupted.에러남
			//--------------------------------------------------------------------------
			void* pVout = &bool_val;
#else
			int int_val1 = 1;
			void* pVout = &int_val1;
#endif 
			int_val= 1;
			*(int*)pVout = int_val;

			jxV_A.m_int_p = (int*)pVout;
			V(*jxV_A.m_int_p == bool_val);
			V(*jxV_A.m_bool_p == bool_val);
			int_val1= 0;
			V(*jxV_A.m_int_p != bool_val);
			V(*jxV_A.m_bool_p != bool_val);

			jxV_A.m_int = 0;
			jxV_B.m_bool = 0;
			V(jxV_A.m_int == jxV_B.m_bool);

			jxV_A.InitValue(_T("0"),EDbool);


			jxV_B.InitValue(_T("1"),EDint);
			jVar jV_A = &jxV_A;
			jVar jV_B = &jxV_B;
			V((bool)jV_B );
			V(jV_A!=jV_B);
			jxV_A.InitValue(_T("1"),EDbool);
			V(jV_A==jV_B);
			//g_UnitTestOK_OuterMemory_For_boolData= true;

		}

		{ // std::tstring 자동 케스팅및 비교 테스트
			jxVar vStr1;
			std::tstring str = _T("asdf");
			vStr1.InitValue(str.c_str() , EDcstr);
			jVar varStr1 = &vStr1;
			V(varStr1==str);
			V(str==varStr1);
			V(!(str!=varStr1));
			V(!(varStr1!=str));
		}
		{ //비교연산
			jxVar jxV_A ;
			jxVar jxV_B;
			jVar jva= &jxV_A, jvb=&jxV_B;
			jxV_A.InitValue(23.3f);
			jxV_B.InitValue(23.33f);
			V2(jva < jvb);
			V2(jva <=jvb);
			V2(jvb > jva);
			V2(jvb >=jva);
		}
		{// EXmlID , StringID 호환테스트
			jVar v = peTestNode->Find(_T("NULL"))->GetVar();
			V2(v==jx(NULL));
			v = peTestNode->Find(_T("XKEY_LSHIFT"))->GetVar();
			V2(v==jx(XKEY_LSHIFT));
			StringID id = jx(XKEY_LSHIFT);
			StringID cid = id;
			_jTEST_(v , ==, id);
			_jTEST_(v , ==, cid);
		}

		{// AnyLInk테스트
			jxVar  xV;
			V2(xV.SizeAnyLink()==0);
			int iii = 23;
			int* int_p=&iii;
			xV.SetAnyLink(int_p);
			V2(xV.SizeAnyLink()==1);
			typedef int* int_p_t;
			int_p_t* int_pp = xV.GetAnyLink<int_p_t>();
			V2(*int_pp == int_p);
			V2(**int_pp == iii);
			POINT po;
			po.x = 12;
			po.y = 34;
			POINT *po0 = xV.GetAnyLink<POINT>();
			V2(po0 ==0);
			xV.SetAnyLink(po);
			po0 = xV.GetAnyLink<POINT>();
			V2(po0!=0);
			V2(xV.SizeAnyLink()==2);

			int * int_p_zero = 0;
			xV.SetAnyLink(int_p_zero);
			V2(xV.SizeAnyLink()==2);
			int_pp = xV.GetAnyLink<int_p_t>();
			V2(*int_pp == int_p_zero);
			//V2(**int_pp == iii);
			POINT *po1 = xV.GetAnyLink<POINT>();
			V2(po1->x==po.x && po1->y == po.y);

		}


#endif
	}
}//namespace nMech

#pragma warning(default : 4805)


