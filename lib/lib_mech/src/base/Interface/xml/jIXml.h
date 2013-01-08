/* 
	filename:	jIXml.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 ���� 2:49:29
	title	:	
*/

/* file : jIXml.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-08 00:59:46
title : 
desc : 

*/

#ifndef __jIXml_header__
#define __jIXml_header__
#pragma once
#include "header\\jDefine.h"
#include "interface/xml/jIVar.h"
#include "interface/xml/jIElement.h"
#include "interface/xml/jIDocument.h"
namespace nMech
{
	namespace nPAK{struct jIPak;}
	namespace nXML
	{
		// jIXml::GetFlag()�� �� ����.
		enum EFlag_jIXml
		{
			eUSE_TINY_XML= jBIT_0,//�⺻������ MSXML�� ���.
		};


		class jXml;
		struct jIXmlCallBackManager;
		struct jIXmlUtil;

		struct jIXml_Param
		{
#define jIXml_Param_LIST(_F_)\
	_F_(bool, ms_isFirstUseJXML, false,"�����ε��� JXML���� �˻��Ͽ��ε�?")\
	_F_(bool, ms_bXML_SkipAutoSave, false,"������ �Ӽ��� AUTOSAVE=1�̴��� �������")\
	_F_(bool, ms_isGenerateJXML, false, "�����Ҷ� �ε��� XML������ JXML�� ����")\
	_F_(int, ms_iSaveFileBackupCount, 5,"�ε��� XML������ �����Ҷ� ���� ���� ����Ǵ°���")\
	_F_(bool, ms_isDocAotuLoad, false,"XML���� �ε��� FILE��ũ�� ELEMENT�� ���� �ڵ��ε�����")\

		jIXml_Param_LIST(jDECL_VAR);

		};

#define jINTERFACE_jIXml(X) public:	\
	/* �ε��� xml ������ü�� ��*/\
	virtual size_t size()##X \
	/* Load()�Լ� ������ ���ϸ��� ȣ��Ǿ���. ���ڴ� xml/db.xml�� �־� �ָ��.*/\
	virtual void Init()##X \
	/* jXml��ü ���� ���º����� �����ϱ����� �Լ�*/\
	virtual void SetInterfaceParam(jIXml_Param* param)##X \
	virtual jIXml_Param* GetInterfaceParam()##X \
	/* msxml.dll�� ���ó��. ���������� ȣ���.*/\
	virtual void RegistXML(bool isShowLog)##X \
	/* �����ε�. nFileSystem::jFileName fn("xml\\jGame.xml"); jID* pD = GetjIXml()->Load(fn.buffer);*/\
	virtual jIDocument* Load(tcstr sxXmlFileName , nPAK::jIPak* pPak=0)##X \
	/* xml�����ε�. ������ ���� fopen���� �ش� FILE*�� ���� ������ �ε���. Ư���� ��� ���.*/\
	virtual jIDocument* Load(tcstr szFile, FILE* fp)##X \
	/* XML ���� �ε�. �޸𸮿� �ִ� ��Ʈ������ ���� �ε�.*/ \
	/*Load("a.xml", "<customer><first_name>Joe</first_name><last_name>Smith</last_name></customer>"); */ \
	virtual jIDocument* Load(tcstr szFile, tcstr pXmlBuff)##X \
	\
	/* �޸𸮻󿡼��� �����ϴ� ������ü�� �����. ������ szNicName�� ���� �����ϴ�.\
		jID* pDoc  = GetjIXml()->CreateMemoryDoc("test_doc"); \
		jID* pDocTest = GetjIXml()->Load("test_doc"); \
		assert(pDoc == pDocTest); */\
	virtual jID* CreateMemoryDoc(cstr szNicName) ##X \
	/* �ش� ���ڷ� ������ ������ ���纻 ����. */\
	virtual jIDocument* Clone(jIDocument*)##X \
	/* �ش� ���� UnLoad*/\
	virtual void UnLoad(jIDocument* pD)##X \
	/* �ش� �̸����� ���ο� xml���� ����. ���������� ������ ���ŵ�. */\
	virtual void NewFile(cstr szXmlFileName)##X \
	/* �ش� �̸����� �� ���� ��ü�� �Ѱ���. �ε��ȉ����� 0���� */\
	virtual jID* GetObj(tcstr szName)##X \
	/* ���󵵵�. �� ����. */\
	virtual int& GetFlag()##X \
	/* ���󵵵�. �� ����. */\
	virtual void* GetData(nMech::StringID sz , void* vData)##X \
	/* ���ο� jIVar ��ü�� �Ѱ���. �ݵ�� DeletejVar�� ȣ���Ͽ� �޸� �����ؾ���. */\
	virtual jIVar* CreatejVar()##X \
	virtual void DeletejVar(jIVar* pV)##X \
	/* ���ο� jIE��ü ����. �� ����� �ݵ�� DeleteElement()�� �޸� �����ؾ���. */\
	virtual jIE* CreateElement()##X \
	virtual void DeleteElement(jIE* pE)##X \
	virtual cstr GetVersion()##X \
	/* jIE��ü�� GetHandle()�� �˾Ƴ� �ڵ鰪���� jIE�� �޸� �ּҸ� ����. */\
	virtual jIElement* FindElementByHandle(uint iHandle)##X \
	virtual jIXmlCallBackManager* GetCallBackManager() ##X \
	virtual jIXmlUtil* GetXmlUtil() ##X \
	virtual jIVar::EElementType  GetTypeByString(tcstr szName)##X\
	/*"EDint" -> EDint */ \
	virtual cstr GetTypeStringByType(jIVar::EElementType eType) ##X \
	/* EDint ->"EDint" */ \


		jINTERFACE_END(jIXml);

	}//nXML
	extern JBASE_API nXML::jIXml* GetjIXml();
	extern JBASE_API void GetjIXml_close();

#define Get_jIXmlUtil() GetjIXml()->GetXmlUtil()
}


#include "Interface/xml/jIVar_op.h"

#include "interface/xml/jIElement_op.h"


#endif // __jIXml_header__
