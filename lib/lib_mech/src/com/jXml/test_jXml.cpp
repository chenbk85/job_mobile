/* file : test_jXml.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2008-01-30 15:31:24
comp.: www.actoz.com
title : 
desc : 

*/

#include "stdafx.h"
#include "base/jTestUnit.h"
#include "Interface/xml/jIXml.h"
#include "interface/jIPak.h"

using namespace nMech;
using namespace nMech::nXML;
namespace 
{
	jTEST_SUITE_BEGIN(jXml_Load);

	jTEST(CreateMemoryDoc)
	{
		cstr szDoc =_T("CreateMemoryDoc_______21388sdflk");
		jE doc = GetjIXml()->CreateMemoryDoc(szDoc);
		jCHECK(doc.full());

		jE doc1 = GetjIXml()->Load(szDoc);
		jEQUAL(doc.BaseI() , doc1.BaseI() );

		jVar v = doc[_T("DEFAULT") ][_T("TEST") ].AttrP(_T("test") );
		jCHECK(v.full());

		jIVar *v1 = doc->Find(_T("DEFAULT") )->Find(_T("TEST") )->GetAttrVar(_T("test") );
		jEQUAL(v1 ,v.BaseI()); //주소값이 동일해야함.

		GetjIXml()->UnLoad(doc);

		doc1 = GetjIXml()->Load(szDoc);
		jCHECK(doc1.empty() );

		{
			jFlagHelper useTiny(GetjIXml()->GetFlag(),nXML::eUSE_TINY_XML, true);
			nPAK::jIPak* asdf = nInterface::g_pjIPak;
			nInterface::g_pjIPak=0;
			jID* pD = GetjIXml()->Load(_T("xml\\App_Default.xml") );
			nInterface::g_pjIPak = asdf;
			jCHECK(pD);
		}


	}

	jTEST_SUITE_END(jXml_Load)
}

