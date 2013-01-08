#ifndef __jIXmlEntity__header__
#define __jIXmlEntity__header__
#include "jIXml.h"

namespace nMech
{
	struct jIClientEntity;
	struct jINetEntity;

	namespace nXML
	{
		class jXmlEntity;

#define jINTERFACE_jIXmlEntity(x) public:	\
	virtual jXmlEntity* Base() ##x \
	virtual int GetServerIndex() ##x \
	virtual jID* GetDocImp() ##x \
	/* implement xml문서의 복사본을 리턴 */\
	virtual jIE* GetTemplateNode() ##x \
	/* jGameEntityList.xml에서의 노드 리턴 */ \
	virtual jID* GetDocTmp(cstr szNic=0) ##x \
	virtual jID* GetDocTmpFast(nMech::StringID szNic=jx(NULL)) ##x \
	/* item , player, npc등에서 template파일을 리턴한다. \
	template파일내에서 관리되는 파일의 닉네임을 인자로주면	해당 문서를 리턴*/\
	virtual jIXmlEntity* GetTarget() ##x \
	/* GetTarget()이 리턴하는 객체 : item -> 소유 플레이어 , Monster & Player -> Target */\
	virtual void SetTarget(jIXmlEntity*) ##x \
	virtual jIE* GetList(cstr szName) ##x \
	virtual jIE* GetList(nMech::StringID szName) ##x \
	/* implement xml에서 szName으로된 리스트노드를 가져온다. szName이 없으면 새로 추가후 가져옴 */ \
	virtual jIE* AddListItem(jIE* peList,void* vData,nMech::StringID  iNode=jx(NULL)) ##x\
	virtual jIE* AddListItem(jIE* peList,void* vData,cstr ) ##x\
	/* GetList()로 부터가져온 peList에 szNode라는 이름으로 vData를 추가한다. */ \
	virtual void DeleteListItem(jIE* peNode) ##x \
	/* AddListItem()로 부터 생성한 Item을 삭제한다. */ \
	virtual jIVar* Get(cstr szName,jIVar::EElementType eType) ##x \
	virtual jIVar* Get(nMech::StringID szName,jIVar::EElementType eType) ##x \
	virtual jIClientEntity* GetClientEntity() ##x \
	virtual jINetEntity* GetNetEntity() ##x \
	virtual void SetClientEntity(jIClientEntity *) ##x \
	virtual void SetNetEntity(jINetEntity*) ##x \
	virtual bool QueryInterface(nMech::StringID id,void** ppInterface) ##x \
	virtual jIE* GetClassNode() ##x \
	/* 해당 entity의 jGameEntityList.xml에 등록된 GetParent()->GetParent() 노드를 호출함. */ \

		jINTERFACE_END(jIXmlEntity);

#define jINTERFACE_jIXmlEntityManager(x) public:	\
	virtual  jID* GetDoc() 	##x\
	/*jGameEntityList.xml를 리턴*/\
	virtual jIXmlEntity* CreateEntity(int iEntitySerialNum,cstr szType,cstr szTemplate,jID* pDocImp=0) ##x \
	/* 엔티티의 고유이름으로 객체생성. szType-> jGameEntityList.xml에서 deeps=2에 해당*/\
	virtual 	jIXmlEntity* CreateEntity(int iEntitySerialNum, jIE* peTempate,jID* pDocImp=0) 	##x\
	/* jGameEntityList의 등록된 element로 객체생성*/\
	virtual jID* ReloadTemplate(jIE* peEntityNode) ##x\
	/* tool에 의해 entity xml파일명이 변경됬을때 다시 로딩 */ \
	virtual void DeleteEntity(int iEntitySerialNum) ##x\
	virtual void DeleteEntity(jIXmlEntity* pXE) ##x\
	virtual void DeleteEntity_NoSchedule(jIXmlEntity* pXE) ##x\
	virtual jIXmlEntity* FindByServerIndex(int idx) ##x\
	virtual jIE* FindTemplate(cstr sz3DFileName) ##x\
	/* gof파일명으로 해당 엔티티 template노드를 찾음 */ \

		jINTERFACE_END(jIXmlEntityManager);

		//--------------------------------------------------------------------------
		// #include "functor\\_jXE_FindByFile.h
		//--------------------------------------------------------------------------
		//g_pIXmlEntityManager->GetDoc()에서 각ENTITY TEMPLATE파일의 OBJECT3D노드가 szFile인 entity template node를 찾는 functor

	}//nXML
	
	namespace nInterface
	{
		extern JBASE_API nXML::jIXmlEntityManager* g_pjIXmlEntityManager;
	}

}


#endif //__jIXmlEntity__header__