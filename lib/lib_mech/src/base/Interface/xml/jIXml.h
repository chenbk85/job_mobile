/* 
	filename:	jIXml.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-14 오후 2:49:29
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
		// jIXml::GetFlag()의 값 종류.
		enum EFlag_jIXml
		{
			eUSE_TINY_XML= jBIT_0,//기본적으로 MSXML을 사용.
		};


		class jXml;
		struct jIXmlCallBackManager;
		struct jIXmlUtil;

		struct jIXml_Param
		{
#define jIXml_Param_LIST(_F_)\
	_F_(bool, ms_isFirstUseJXML, false,"문서로딩시 JXML부터 검색하여로딩?")\
	_F_(bool, ms_bXML_SkipAutoSave, false,"문서의 속성중 AUTOSAVE=1이더라도 저장안함")\
	_F_(bool, ms_isGenerateJXML, false, "종료할때 로딩한 XML문서를 JXML로 저장")\
	_F_(int, ms_iSaveFileBackupCount, 5,"로딩한 XML문서를 저장할때 이전 파일 백업되는갯수")\
	_F_(bool, ms_isDocAotuLoad, false,"XML문서 로딩시 FILE링크형 ELEMENT에 대해 자동로딩적용")\

		jIXml_Param_LIST(jDECL_VAR);

		};

#define jINTERFACE_jIXml(X) public:	\
	/* 로딩된 xml 문서객체의 수*/\
	virtual size_t size()##X \
	/* Load()함수 이전에 제일먼저 호출되야함. 인자는 xml/db.xml을 넣어 주면됨.*/\
	virtual void Init()##X \
	/* jXml객체 내부 상태변수를 세팅하기위한 함수*/\
	virtual void SetInterfaceParam(jIXml_Param* param)##X \
	virtual jIXml_Param* GetInterfaceParam()##X \
	/* msxml.dll의 등록처리. 내부적으로 호출됨.*/\
	virtual void RegistXML(bool isShowLog)##X \
	/* 문서로딩. nFileSystem::jFileName fn("xml\\jGame.xml"); jID* pD = GetjIXml()->Load(fn.buffer);*/\
	virtual jIDocument* Load(tcstr sxXmlFileName , nPAK::jIPak* pPak=0)##X \
	/* xml문서로딩. 파일을 직접 fopen한후 해당 FILE*로 부터 문서를 로딩함. 특별한 경우 사용.*/\
	virtual jIDocument* Load(tcstr szFile, FILE* fp)##X \
	/* XML 문서 로딩. 메모리에 있는 스트링으로 부터 로딩.*/ \
	/*Load("a.xml", "<customer><first_name>Joe</first_name><last_name>Smith</last_name></customer>"); */ \
	virtual jIDocument* Load(tcstr szFile, tcstr pXmlBuff)##X \
	\
	/* 메모리상에서만 존재하는 문서객체를 만든다. 접근은 szNicName을 통해 가능하다.\
		jID* pDoc  = GetjIXml()->CreateMemoryDoc("test_doc"); \
		jID* pDocTest = GetjIXml()->Load("test_doc"); \
		assert(pDoc == pDocTest); */\
	virtual jID* CreateMemoryDoc(cstr szNicName) ##X \
	/* 해당 인자로 제공된 문서의 복사본 생성. */\
	virtual jIDocument* Clone(jIDocument*)##X \
	/* 해당 문서 UnLoad*/\
	virtual void UnLoad(jIDocument* pD)##X \
	/* 해당 이름으로 새로운 xml문서 생성. 기존문서가 있으면 제거됨. */\
	virtual void NewFile(cstr szXmlFileName)##X \
	/* 해당 이름으로 된 문서 객체를 넘겨줌. 로딩안됬으면 0리턴 */\
	virtual jID* GetObj(tcstr szName)##X \
	/* 몰라도됨. 걍 무시. */\
	virtual int& GetFlag()##X \
	/* 몰라도됨. 걍 무시. */\
	virtual void* GetData(nMech::StringID sz , void* vData)##X \
	/* 새로운 jIVar 객체를 넘겨줌. 반드시 DeletejVar를 호출하여 메모리 해제해야함. */\
	virtual jIVar* CreatejVar()##X \
	virtual void DeletejVar(jIVar* pV)##X \
	/* 새로운 jIE객체 생성. 다 사용후 반드시 DeleteElement()로 메모리 해제해야함. */\
	virtual jIE* CreateElement()##X \
	virtual void DeleteElement(jIE* pE)##X \
	virtual cstr GetVersion()##X \
	/* jIE객체의 GetHandle()로 알아낸 핸들값으로 jIE의 메모리 주소를 리턴. */\
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
