/* file : jxVar_test.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2006-12-14 13:59:50
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jxVar.h"
#include "interface/xml/jIVar_op.h"
#include "base/jString_mem.h"
#include "base/jTestUnit.h"


struct test_anilink_obj
{
	int i;
	float f;
	std::tstring s;
	POINT Po;
};
struct test_anilink_obj2 : public test_anilink_obj
{
	RECT r;
};


//--------------------------------------------------------------------------
// jxVar관련 테스트
//--------------------------------------------------------------------------
#pragma warning(disable : 4805)
namespace nMech
{
	jTEST_SUITE_BEGIN( TYPE_TEST)
		jTEST( ARRAY_TYPE_ADAPTER)
		{
#undef _jcode_ 
#define _jcode_ 1,2

			float a2[2]={1,2};
			float b2[2]={1,2};
			float* pf2 = b2;
			jFloat2 f2=a2;
			assert(f2==b2);
			f2=b2;
			assert(f2==pf2);
		}

		jTEST(jRECT_TEST)
		{
#ifdef jUSE_JRECT
			jRECT a,b;
			RECT c;
			a.clear();b.clear();
			memset(&c,0,sizeof(c));
			jEQUAL(sizeof(a),sizeof(int)*4);
			jEQUAL(sizeof(a),sizeof(uint)*4);
			jEQUAL(sizeof(a),sizeof(LONG)*4);
			jTEST_CHECK(!memcmp(&a,&c,sizeof(a) ) );
#define _jcomp_(a,op ,c)  ((a.ux op c.left) && (a.uy op c.top) && (a.uw op c.right) && (a.uh op c.bottom))
			jTEST_CHECK( _jcomp_(a,==,c) );
			a.x=a.y=a.w=a.h =-10;
			jTEST_CHECK( _jcomp_(a,!=,c) );
			memcpy(&c , &a , sizeof(a));
			jTEST_CHECK( _jcomp_(a,==,c) );
			jRECT d = c;
			jTEST_CHECK(_jcomp_(d,==,c));
			RECT e = d;
			jTEST_CHECK(_jcomp_(a,==,e));
#endif //jUSE_JRECT
		}

		jTEST(jxVar_TEST)
		{
			jxVar v_jxVar;
			jVar v_jVar = &v_jxVar;
			v_jVar.SET(&v_jxVar);
#define __type_check__jvar(type) \
	jEQUAL(v_jxVar.GetType() , jIVar::ED##type);\
	jEQUAL(std::tstring(_T(#type)) ,  v_jxVar.GetTypeString());\
	jEQUAL(v_jVar->GetType() , jIVar::ED##type);\
	jEQUAL(std::tstring(_T(#type)) ,  v_jVar->GetTypeString());

#define __JPREDICATE_TEST(var  , op , val) jTEST_CHECK( (var op val) ); jTEST_CHECK( (val op var) );
#define __value_check_jvar(val) __JPREDICATE_TEST(v_jVar ,==,val);
#define __type_value_check__(val,type) \
	__type_check__jvar(type); __value_check_jvar(val); { type temp = v_jVar; jEQUAL(temp,val) ;}
#define __type_value_check(val,type) v_jVar=val; __type_value_check__(val,type);

			// double형은 구현안함.
			//__type_value_check(1.3,float);

#if 0
			v_jVar->SetType(jIVar::EDint);
			__type_value_check(10 , int);

			v_jVar->SetType(jIVar::EDfloat);
			__type_value_check(1.3f,float);

			v_jVar->SetType(jIVar::EDbool);
			__type_value_check(false,bool);

			v_jVar->SetType(jIVar::EDuint);
			__type_value_check(16u,uint);

			v_jVar->SetType(jIVar::EDuint);
			v_jVar = 16u; 
			__type_value_check__(16,uint);

			v_jVar->SetType(jIVar::EDStringID);
			v_jVar = jx(NULL);	
			__type_check__jvar(StringID); __value_check_jvar(_T("NULL")); 

			v_jVar->SetType(jIVar::EDcstr);
			v_jVar = _T("test code");
			__type_check__jvar(cstr); __value_check_jvar(_T("test code"));

			jTEST_CHECK(v_jVar ==tstring(_T("test code")) );
			tstring s = v_jVar;
			jxVar jxV2;
			jxV2.InitValue(_T("test"),jIVar::EDcstr);
			jVar vv2 = &jxV2;
			vv2 = _T("test code2");
			jTEST_CHECK(v_jVar!= vv2);
			jTEST_CHECK(v_jVar== s);
			//V(s == v_jVar);
#endif

			{// int* 와 bool* 의 호환테스트
				jxVar jxV_A ,jxV_B;
				jxVar jv_A1 ;

				int int_val = 0;
				jxV_A.m_int = 1;
				jxV_B.m_bool_p = reinterpret_cast<bool* > (&int_val);
				jTEST_CHECK(jxV_A.m_int != *jxV_B.m_bool_p);

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

				jv_A1.m_int_p = (int*)pVout;
				jTEST_CHECK(*jv_A1.m_int_p == bool_val);
				jTEST_CHECK(*jv_A1.m_bool_p == bool_val);
				int_val1= 0;
				jTEST_CHECK(*jv_A1.m_int_p != bool_val);
				jTEST_CHECK(*jv_A1.m_bool_p != bool_val);

				jv_A1.m_int = 0;
				jxV_B.m_bool = 0;
				jTEST_CHECK(jv_A1.m_int == jxV_B.m_bool);

				jv_A1.InitValue(_T("0"),jIVar::EDbool);


				jxV_B.InitValue(_T("1"),jIVar::EDint);
				jVar jv_A = &jv_A1;
				jVar jv_B = &jxV_B;
				jTEST_CHECK((bool)jv_B );
				jTEST_CHECK(jv_A!=jv_B);
				jv_A1.InitValue(_T("1"),jIVar::EDbool);
				jTEST_CHECK(jv_A==jv_B);
				//g_UnitTestOK_OuterMemory_For_boolData= true;

			}

			{ // tstring 자동 케스팅및 비교 테스트
				jxVar vStr1;
				tstring str = _T("asdf");
				vStr1.InitValue(str.c_str() , jIVar::EDcstr);
				jVar varStr1 = &vStr1;
				jTEST_CHECK(varStr1==str);
				jTEST_CHECK(str==varStr1);
				jTEST_CHECK(!(str!=varStr1));
				jTEST_CHECK(!(varStr1!=str));
			}
			{ //비교연산
				jxVar jv_A1 ;
				jxVar jxV_B;
				jVar jva= &jv_A1, jvb=&jxV_B;
				jv_A1.InitValue(23.3f);
				jxV_B.InitValue(23.33f);
				jTEST_CHECK(jva < jvb);
				jTEST_CHECK(jva <=jvb);
				jTEST_CHECK(jvb > jva);
				jTEST_CHECK(jvb >=jva);
			}
#if 0
			{// EXmlID , jStringID 호환테스트
				jVar v = peTestNode->Find(_T("NULL"))->GetCHECKar();
				jTEST_CHECK(v==jx(NULL));
				v = peTestNode->Find(_T("XKEY_LSHIFT"))->GetCHECKar();
				jTEST_CHECK(v==jx(XKEY_LSHIFT));
				jStringID id = jx(XKEY_LSHIFT);
				nMech::nString::jStringID cid = id;
				__JPREDICATE_TEST(v , ==, id);
				__JPREDICATE_TEST(v , ==, cid);
			}
#endif

		}//TEST(jxVar)

		
		jTEST(xjVar_AnyLink)
		{
			jxVar  vVar;
			jTEST_CHECK(vVar.SizeAnyLink()==0);
			int iii = 23;
			int* int_p=&iii;
			vVar.SetAnyLink(int_p);
			jTEST_CHECK(vVar.SizeAnyLink()==1);
			typedef int* int_p_t;
			int_p_t* int_pp = vVar.GetAnyLink<int_p_t>();
			jTEST_CHECK(*int_pp == int_p);
			jTEST_CHECK(**int_pp == iii);
			POINT po;
			po.x = 12;
			po.y = 34;
			POINT *po0 = vVar.GetAnyLink<POINT>();
			jTEST_CHECK(po0 ==0);
			vVar.SetAnyLink(po);
			po0 = vVar.GetAnyLink<POINT>();
			jTEST_CHECK(po0!=0);
			jTEST_CHECK(vVar.SizeAnyLink()==2);

			int * int_p_zero = 0;
			vVar.SetAnyLink(int_p_zero);
			jTEST_CHECK(vVar.SizeAnyLink()==2);
			int_pp = vVar.GetAnyLink<int_p_t>();
			jTEST_CHECK(*int_pp == int_p_zero);
			//jTEST_CHECK(**int_pp == iii);
			POINT *po1 = vVar.GetAnyLink<POINT>();
			jTEST_CHECK(po1->x==po.x && po1->y == po.y);
#if 1
			test_anilink_obj obj;
			obj.s = _T("test1");
			vVar.SetAnyLink(&obj);
			jEQUAL(vVar.SizeAnyLink() , 3);

			test_anilink_obj2 obj2;
			vVar.SetAnyLink(&obj2);
			obj2.s = _T("test2");
			jEQUAL(vVar.SizeAnyLink() , 4);

			test_anilink_obj** pObj = vVar.GetAnyLink<test_anilink_obj*>();
			jEQUAL(*pObj, &obj);
			
			test_anilink_obj2** pObj2 = vVar.GetAnyLink<test_anilink_obj2*>();
			jEQUAL(*pObj2, &obj2);
#endif

		}//TEST(xjVar_AnyLink)

		jTEST(jVar_jConvertByMyType)
		{
			jxVar testVar;
			testVar.SetType(jIVar::EDint);
			jVar v = &testVar;
			v.M() = 234;
			jTEST_CHECK(v==234);
			jTEST_CHECK(234==v);
			jTEST_CHECK(235!=v);
			jTEST_CHECK(v!=235);

			v.M() = _T("1234");
			jTEST_CHECK(v==1234);
			jTEST_CHECK(1234==v);
			jTEST_CHECK(1235!=v);
			jTEST_CHECK(v!=1235);

			try
			{
				v.M() = 23.3f;
				jTEST_CHECK(0);
			}
			catch (tcstr)
			{
				jTEST_CHECK(1);
			}

			v.T() = 23.3f;
			jTEST_CHECK( v->IsType(jIVar::EDfloat) );
			jTEST_CHECK(v==23.3f);
			jTEST_CHECK(23.3f==v);
			jTEST_CHECK(123.5f!=v);
			jTEST_CHECK(v!=12.35f);

			v.T() = _T("1234");
			jTEST_CHECK( v->IsType(jIVar::EDcstr) );
#if 1
			jTEST_CHECK(_T("1234")	==	v);
			jTEST_CHECK(_T("12345")	!=	v);
			jTEST_CHECK(v	!=	_T("12354"));
#else 
			// 이렇게 사용하면 안됨
			jEQUAL(v	,	_T("1234"));
			jEQUAL(_T("1234")	,	v);
#endif

			v.T() = true;
			jTEST_CHECK( v->IsType(jIVar::EDbool) );
			jTEST_CHECK(v==true);
			jTEST_CHECK(true==v);
			jTEST_CHECK(false!=v);
			jTEST_CHECK(v!=false);

			tstring testS = _T("asdfoi23jkd");
			v.T() = testS;
			jTEST_CHECK( v->IsType(jIVar::EDcstr) );
			jTEST_CHECK(v==testS);
			jTEST_CHECK(testS==v);
			jTEST_CHECK(std::tstring(_T("123.5f"))!=v);
			jTEST_CHECK(v!=12.35f);

		}//jTEST(jVar_jConvertByMyType)
	jTEST_SUITE_END( TYPE_TEST)

}//namespace nMech

#pragma warning(default : 4805)
