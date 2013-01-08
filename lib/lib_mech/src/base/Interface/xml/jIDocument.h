/* 
	filename:	jIXml.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 ���� 2:49:29
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
	/* ������ url path�� ���� */\
	virtual cstr GetURL(tfname_t szBuf)##x \
	/* ������ ���ϸ��� ������ url path����*/ \
	virtual void CopyTo(jIDocument* pD)##x \
	virtual void ReLoad()##x \
	\
	/* ������ ������ �⺻������ g_ExeEnv.m_szStartDir�� �̵��� ����ȴ�. */\
	virtual void Save()##x \
	virtual void SaveJXML()##x \
	/* .jxml�� ����.*/ \
	virtual void SaveAsJXML(cstr szUrl)##x \
	virtual void SaveXML()##x \
	virtual void SaveAsXML(cstr szUrl)##x \
	\
	virtual jIElement* FindByBlood(cstr szElement , const jvector<std::tstring> &aBlood )##x \
	/*  ���ٷ� ���� �ش� �̸��� ã�´�. */ \
	virtual void DebugPrint(bool isInsert_CR)##x \
	/* XPATH API */ \
	virtual jIE* GetXPathNode(cstr szXPath , jIAttribute** pA )##x \
	/* xpath ���� : @�� �Ӽ��̴�.  "attname@1.2.3"   // ù��°�ڽ��� 2��°�ڽ��� 3��°*/ \
	virtual jIE* GetSXPathNode(cstr szXPath , jIAttribute** pA )##x \
	/*  xpath ���� : @�� �Ӽ��̴�.  "attname@element.parent2.parent1.parent"   parent�� root�� ���Ծȵ�. */ \
	virtual int& GetFlag()##x \
	virtual void SetComment(jIE* pE , cstr sz)##x \
	/* �ش�element�� �ּ���Ʈ���� ����. <!-- ... -->�� ���� */ \
	virtual jvector<std::tstring>* FindComment(jIE* pE)##x \
	/* �ش�element�� �ּ���Ʈ���� ����. <!-- ... -->�� ���� */ \
	virtual jIElement* GetParentLink()##x \
	/* xml�������� �ٸ� xml������ �����ϴ°����϶� �ڽ��� �����ϴ� ���������� ��带 ���� */ \
	virtual void SetParentLink(jIElement* pE)##x \
	virtual void* jGetData(cstr szDataName,void*)##x \

		jINTERFACE_END(jIDocument);

	}//nXML
}

#endif //__jIDocument_h__
