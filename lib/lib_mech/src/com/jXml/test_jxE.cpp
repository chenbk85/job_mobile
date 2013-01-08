/* file : test_jxE.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-28 11:22:45
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "jxElement.h"
#include "interface/jIZipUtil.h"
using namespace nMech;
using namespace nMech::nXML;


void print_1(jIE* it)
{
	printf("\n");
	fname_t buf;
	for(int i=0; i< it->GetDepth(); ++i)
	{
		printf("\t");
	}
	jt_printf(_T("%s = %s"), it->GetTagName() , it->GetVar()->ToString(buf));
}
namespace 
{
	jTEST_SUITE_BEGIN(jXml_test)
	jTEST(jxElement_test)
	{
		//peTestNode 는 xml/system/jTestUnit.xml에서의 <jxElement>노드임.
		//#define jNOT_USE_TEST
#ifndef jNOT_USE_TEST
#undef V
#define  V(x)  jCHECK(x)
#define  V2(x)  jCHECK(x)

#define NEQ(X, Y) V2((X)!=(Y)); V2((Y)!=(X));
#define NEQT(T, X, Y) NEQ(X,Y); NEQ(Y,X);{ T TX = X, TY=Y; NEQ(TX,Y); NEQ(X,TY);}

#define EQ(X, Y) V2((X)==(Y)); V2((Y)==(X));
#define EQT(T, X, Y) EQ(X,Y); EQ(Y,X);{ T TX = X, TY=Y; EQ(TX,Y); EQ(X,TY);}

#define LE(X, Y) V2((X)<=(Y)); V2((Y)>=(X));

#define jLESS(X, Y) V2((X)<(Y)); V2((Y)>(X));

		{
			size_t i1= jxElement::ms_TreeNodeMemoryManager.size();
			jIE* pe = GetjIXml()->CreateElement();
			size_t  i2 = jxElement::ms_TreeNodeMemoryManager.size();
			V2((i1+1)==i2);
			GetjIXml()->DeleteElement(pe);
			i1 = jxElement::ms_TreeNodeMemoryManager.size();
			V2( (i1+1)==i2);
		}

		jID* pDocTest = GetjIXml()->Load(_T("xml\\test\\jTestUnit.xml")) ;
#ifndef DEBUG
		if(!pDocTest) return ;
#endif
		jCHECK(pDocTest);

		jE peTestNode = pDocTest->BaseI();

		jE eTest = peTestNode(_T("jxElement"));
		// int 테스트
		jIE* pE = peTestNode->Find(_T("INT1"));
		jIE* pE1 = pE->GetRight();
		V(pE&&pE1);
		jE e = pE;
		jE e1 = pE1;
		EQT(int, e, pE->GetVar()->Get_int());
		EQT(int, e, pE1->GetVar()->Get_int());
		EQT(int, e, e1);

		//float 테스트
		e = pE = peTestNode->Find(_T("FLOAT"));
		e1 = peTestNode->Find(_T("FLOAT2"));
		EQT(float, e, pE->GetVar()->Get_float());
		V2(e1>e);
		V2(e<e1);
		V2(e1>=e);
		V2(e<=e1);

		//LE(e, e1);

		// bool 테스트
		e= peTestNode->Find(_T("BOOL" ) );
		e1= peTestNode->Find(_T("BOOL2" ) );
		EQ(e,e1);
		// EQT(bool, e,e1);// 테스트 통과 안됨 나중에 버그 잡을것.
#pragma warning(disable : 4805)
		EQT(bool, e,e.BaseI()->GetVar()->Get_bool());
		EQT(bool, e,e.BaseI()->GetVar()->Get_int());
		EQT(bool, e,e1.BaseI()->GetVar()->Get_bool());
		EQT(bool, e,e1.BaseI()->GetVar()->Get_int());
#pragma warning(default : 4805)

		e = eTest(_T("INT1" ) );
		e1 = eTest(_T("test" ) )(_T("INT1" ) );
		V2(e==e1);
		V2(e.BaseI()==e1.BaseI());

		e = eTest(_T("test" ) )(1);
		V2(e==e1);
		V2(e.BaseI()!=e1.BaseI());
		//e = eTest(jx(POINT)));
		e = eTest(_T("POINT" ) );
		POINT po = e;
		V2(po.x==32 && po.y==23);
		e = eTest(23432)(2344)(-23)(_T("not_found_ok?" ) )(23);
		V2(!e.BaseI());
		int i = e;
		uint ui = e;
		V2(i==ui);

		//eTest->for_each_depth(print_1);	printf("\n");

		e1 = eTest(_T("VECTOR" ) );
		jCHECK(e1.full());
		e = eTest(e1->GetOrder());
		V2(e==e1);
		V2(e.BaseI()==e1.BaseI());

		e = eTest(-1)(_T("한글호키" ) );
		V2(e.BaseI());
		tstring str = e;
		V2(str == e);
		V2(e ==str);

		jVar eVar = e;
		jVar eVar2;
		eVar2= eTest(-1)(_T("한글호키" ) ).Var();
		V2(eVar==eVar2);
		V2(eVar == str);

		tstring str12 = _T("asdf");
		tstring str13 = _T("asdf");
		//jEQUAL(str12,str13);
		jCHECK(str12==str13);

		{
			// insert delete테스트
			jxE org(_T("org" ) );
			org.InsertChildElement(_T("a1" ) );
			org.DebugPrint(nInterface::g_pjILog);
			org.InsertChildElement(_T("a3" ) );
			org.DebugPrint(nInterface::g_pjILog);
			org.InsertChildElement(_T("a2"),1);
			org.DebugPrint(nInterface::g_pjILog);
			org.InsertChildElement(_T("a0"),0);
			org.DebugPrint(nInterface::g_pjILog);
			jE a5 = org.InsertChildElement(_T("a5" ) );
			org.InsertChildElement(_T("a4"),a5->GetOrder());
			org.DebugPrint(nInterface::g_pjILog);

			// 복사 , attach테스트
			jxE dest(_T("dest" ) );
			org.CopyTo_Child(&dest);
			dest.DebugPrint(nInterface::g_pjILog);
			org.attach(&dest);
			org.DebugPrint(nInterface::g_pjILog);

			jxE dest1(&dest);
			V2(dest1.GetRoot() != dest.GetRoot() );// parent정보는 복사안됨
			dest1.ChangeTagName(_T("dest1" ) );
			dest1.DebugPrint(nInterface::g_pjILog);
			org.attach(&dest1, &dest);
			V2(dest1.GetRoot() == dest.GetRoot() );// parent가 같다.

			org.DebugPrint(nInterface::g_pjILog);

			// detach() redetach()테스트
			dest1.detach();
			org.DebugPrint(nInterface::g_pjILog); // org에는 dest1이 없다.
			dest1.redetach();
			org.DebugPrint(nInterface::g_pjILog); // org에 다시 편입됨


		}


#endif
	}// jxElement_test

	jTEST(doc_load_save)
	{
#if 0
		HMODULE hM =0;
		jCREATE_INTERFACE_AUTO(pUnZip, nMech::nUtil::jIZipBuffer);
		bool is_skip_jxml_save=false;
		if(pUnZip.empty())
		{
			hM = ::LoadLibraryA( "com_util.dll" );
			if(hM)
			{
				jCreateInterface_t* pFunc = (jCreateInterface_t*)::GetProcAddress(hM, "jCreateInterface");
				jCHECK(pFunc);
				if(pFunc)pFunc(0);
			}
			else
			{
				is_skip_jxml_save= false;
			}
		}

		{
			tcstr TEST_DOC= _T("<?xml version='1.0' encoding=\"euc-kr\"?>\
				<jTestUnit>\
				<i_int>23</i_int>\
				<string>asdf</string>\
				</jTestUnit>");

			tcstr sztempjXml = _T("test\\asdf1234asdf.jxml");
			jID* pD = GetjIXml()->Load(_T("asdf1234asdf.xml"), TEST_DOC);
			jCHECK(pD);
			if(1)
			{
				pD->SaveAsJXML(sztempjXml);
				
				if(!nTest::Get_jITestUnit()->IsTested_VUTPP())
					jCHECK(nFileSystem::jFolder::Is_Exist(sztempjXml));

				jID* pDJXml = GetjIXml()->Load(sztempjXml);
				if(!nTest::Get_jITestUnit()->IsTested_VUTPP())
					jCHECK(pDJXml);
				GetjIXml()->UnLoad(pD);
				GetjIXml()->UnLoad(pDJXml);
				jCHECK(!GetjIXml()->GetObj(_T("asdf1234asdf.xml")) );
				jCHECK(!GetjIXml()->GetObj(sztempjXml) );
				DeleteFile(sztempjXml);
			}
		}



		jID* pD = GetjIXml()->Load(_T("xml\\test\\jTestUnit.xml") );
		tcstr testjxml = _T("test\\test_jxml.jxml");
		if(nFileSystem::jFolder::Is_Exist(testjxml))
		{
			DeleteFile(testjxml);
		}
		jCHECK(!nFileSystem::jFolder::Is_Exist(testjxml));
		pD->SaveAsJXML(testjxml);
		jCHECK(nFileSystem::jFolder::Is_Exist(testjxml));

		pD = GetjIXml()->Load(_T("test\\test_asdf29384798jxml.jxml"));
		jCHECK(!pD);

		pD = GetjIXml()->Load(testjxml);
		jCHECK(pD&&_T("test\\test_jxml.jxml"));
		if(pD)pD->SaveXML();
		DeleteFile(testjxml);
		//if(hM)			FreeLibrary(hM);
#endif
	}//jTEST(doc_load_save)

	jTEST(element_insert)
	{
		jE pD = GetjIXml()->CreateMemoryDoc(_T("asdfasdfkljwieofj8932sdlkfjioewj") );
		pD[_T("FILES")];

		pD->Find(_T("FILES") )->InsertChildElement(_T("asdf") );
		pD->Find(_T("FILES") )->InsertChildElement(_T("asdf") );
		pD->Find(_T("FILES") )->InsertChildElement(_T("asdf") );
		pD->Find(_T("FILES") )->InsertChildElement(_T("asdf") );
		pD->Find(_T("FILES") )->InsertChildElement(_T("aaa3" ) ,3);
		pD->Find(_T("FILES") )->InsertChildElement(_T("aaa2" ) ,2);
		pD->Find(_T("FILES") )->InsertChildElement(_T("aaa1" ) ,1);
		pD->DebugPrint(nInterface::g_pjILog);
		GetjIXml()->UnLoad(pD);
	}
	jTEST(attribute_copy_test)
	{
		jE pD = GetjIXml()->CreateMemoryDoc(_T("asdfasdfkljwieofj8932sdlkfjioewj") );
		jE e = pD[_T("E")];
		e.AttrP(jS(test) ).T() = 1234;
		e.AttrP( jS(test2) ).T() = jS(test2);
		jE ne = pD[jS(E1)];

		e->CopyTo(ne);
		jCHECK(e->GetAttributeList()->size()==2);
		jCHECK(ne->GetAttributeList()->size()==2);
		jCHECK(ne.Attr(jS(test))->Get_int() == (int)1234);
		jCHECK(ne.Attr(jS(test2))->IsContents(jS(test2)) );

		GetjIXml()->UnLoad(pD);
	}


	jTEST_SUITE_END(jXml_test)
}
