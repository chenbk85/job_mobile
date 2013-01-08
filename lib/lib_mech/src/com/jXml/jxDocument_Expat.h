/*
filename:	jxDocument_Expat.h
coder	:	Cho Wook Rea (4MLMman@hitel.net)(icq:74456993)
compiler:	vc++ 6.0
date	:	2001-07-05오전 7:28:50
title	:	 xml -> jxml변환용 클래스.
*/

// jxDocument_Expat.h: interface for the jxDocument_Expat class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JXDOCUMENTEX_H__5asfdsfde403wersde64CB53DB3614__INCLUDED_)
#define AFX_JXDOCUMENTEX_H__5asfdsfde403wersde64CB53DB3614__INCLUDED_

#include "jxDocument.h"
#include "util/xml/xml.h"
#pragma once

namespace nMech
{
	namespace nXML
	{
		//****************************************************************
		class jxElement_Expat : public jxElement
			//****************************************************************
		{
		public:
			void jxElement_Expat::Load(jXmlNodeRef& pElmt);
			void jxElement_Expat::LoadAtt(jXmlNodeRef&  node);
		};

		//****************************************************************
		class jxDocument_Expat   :public jxElement_Expat
			//****************************************************************
		{
		public:
			void Load(cstr szURL);
			void LoadFromBuffer(char* szBuffer);
		};

	}
}


#endif // !defined(AFX_JXDOCUMENTEX_H__5asfdsfde403wersde64CB53DB3614__INCLUDED_)
