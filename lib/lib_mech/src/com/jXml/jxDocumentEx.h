/*
	filename:	jxDocumentEx.h
	coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993)
	compiler:	vc++ 6.0
	date	:	2001-07-05오전 7:28:50
	title	:	 xml -> jxml변환용 클래스.
*/

// jxDocumentEx.h: interface for the jxDocumentEx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JXDOCUMENTEX_H__5FE83878_A087_4037_B779_64CB53DB3614__INCLUDED_)
#define AFX_JXDOCUMENTEX_H__5FE83878_A087_4037_B779_64CB53DB3614__INCLUDED_

#include "jxDocument.h"
//#pragma warning(disable : 4251)


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#	ifdef jMSXML_USE

using namespace std;
#	import "msxml4.dll"

// 2004-05-27 june@digicell.co.kr
// using namespace MSXML2;

namespace nMech
{
	namespace nXML
	{

		//****************************************************************
		class jxElementEx : public jxElement
			//****************************************************************
		{
		public:
			void jxElementEx::Load(MSXML2::IXMLDOMElementPtr& pElmt);
			void jxElementEx::LoadAtt(MSXML2::IXMLDOMNamedNodeMapPtr& attMap);
		};

		//****************************************************************
		class jxDocumentEx   :public jxElementEx
			//****************************************************************
		{
		public:
			jxDocumentEx();
			~jxDocumentEx();

			void Load(cstr szURL);
			void jxDocumentEx::LoadFromBuffer(tcstr szBuffer);
		};

	}
}
#	pragma warning(default: 4251)

#endif //#ifdef jMSXML_USE


#endif // !defined(AFX_JXDOCUMENTEX_H__5FE83878_A087_4037_B779_64CB53DB3614__INCLUDED_)
