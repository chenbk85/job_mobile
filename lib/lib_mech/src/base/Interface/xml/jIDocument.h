/* 
	filename:	jIXml.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 오후 2:49:29
	title	:	
*/


#ifndef __jIDocument_h__
#define __jIDocument_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include "jIVar.h"
#include "jIElement.h"

namespace nMech
{
	namespace nXML
	{
		struct jIAttribute;
		class jxDocument;


#define jINTERFACE_jIDocument(x) public:	\
	virtual jIE* BaseI()##x \
	virtual jIElement* Find(cstr sz)##x \
	virtual jIElement* Find(nMech::StringID sz)##x \
	virtual cstr GetPath()##x \
	/* 문서의 url path를 리턴 */\
	virtual cstr GetURL(tfname_t szBuf)##x \
	/* 문서의 파일명을 포함한 url path리턴*/ \
	virtual void CopyTo(jIDocument* pD)##x \
	virtual void ReLoad()##x \
	\
	/* 파일의 저장은 기본적으로 g_ExeEnv.m_szStartDir로 이동후 저장된다. */\
	virtual void Save()##x \
	virtual void SaveJXML()##x \
	/* .jxml로 저장.*/ \
	virtual void SaveAsJXML(cstr szUrl)##x \
	virtual void SaveXML()##x \
	virtual void SaveAsXML(cstr szUrl)##x \
	\
	virtual jIElement* FindByBlood(cstr szElement , const jvector<std::tstring> &aBlood )##x \
	/*  핏줄로 부터 해당 이름을 찾는다. */ \
	virtual void DebugPrint(bool isInsert_CR)##x \
	/* XPATH API */ \
	virtual jIE* GetXPathNode(cstr szXPath , jIAttribute** pA )##x \
	/* xpath 형식 : @는 속성이다.  "attname@1.2.3"   // 첫번째자식의 2번째자식의 3번째*/ \
	virtual jIE* GetSXPathNode(cstr szXPath , jIAttribute** pA )##x \
	/*  xpath 형식 : @는 속성이다.  "attname@element.parent2.parent1.parent"   parent에 root는 포함안됨. */ \
	virtual int& GetFlag()##x \
	virtual void SetComment(jIE* pE , cstr sz)##x \
	/* 해당element의 주석스트링을 세팅. <!-- ... -->의 내용 */ \
	virtual jvector<std::tstring>* FindComment(jIE* pE)##x \
	/* 해당element의 주석스트링을 리턴. <!-- ... -->의 내용 */ \
	virtual jIElement* GetParentLink()##x \
	/* xml문서에서 다른 xml문서를 포함하는관계일때 자신을 포함하는 문서에서의 노드를 리턴 */ \
	virtual void SetParentLink(jIElement* pE)##x \
	virtual void* jGetData(cstr szDataName,void*)##x \

		jINTERFACE_END(jIDocument);

	}//nXML
}

#endif //__jIDocument_h__
