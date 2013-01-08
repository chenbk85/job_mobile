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
	/* implement xml������ ���纻�� ���� */\
	virtual jIE* GetTemplateNode() ##x \
	/* jGameEntityList.xml������ ��� ���� */ \
	virtual jID* GetDocTmp(cstr szNic=0) ##x \
	virtual jID* GetDocTmpFast(nMech::StringID szNic=jx(NULL)) ##x \
	/* item , player, npc��� template������ �����Ѵ�. \
	template���ϳ����� �����Ǵ� ������ �г����� ���ڷ��ָ�	�ش� ������ ����*/\
	virtual jIXmlEntity* GetTarget() ##x \
	/* GetTarget()�� �����ϴ� ��ü : item -> ���� �÷��̾� , Monster & Player -> Target */\
	virtual void SetTarget(jIXmlEntity*) ##x \
	virtual jIE* GetList(cstr szName) ##x \
	virtual jIE* GetList(nMech::StringID szName) ##x \
	/* implement xml���� szName���ε� ����Ʈ��带 �����´�. szName�� ������ ���� �߰��� ������ */ \
	virtual jIE* AddListItem(jIE* peList,void* vData,nMech::StringID  iNode=jx(NULL)) ##x\
	virtual jIE* AddListItem(jIE* peList,void* vData,cstr ) ##x\
	/* GetList()�� ���Ͱ����� peList�� szNode��� �̸����� vData�� �߰��Ѵ�. */ \
	virtual void DeleteListItem(jIE* peNode) ##x \
	/* AddListItem()�� ���� ������ Item�� �����Ѵ�. */ \
	virtual jIVar* Get(cstr szName,jIVar::EElementType eType) ##x \
	virtual jIVar* Get(nMech::StringID szName,jIVar::EElementType eType) ##x \
	virtual jIClientEntity* GetClientEntity() ##x \
	virtual jINetEntity* GetNetEntity() ##x \
	virtual void SetClientEntity(jIClientEntity *) ##x \
	virtual void SetNetEntity(jINetEntity*) ##x \
	virtual bool QueryInterface(nMech::StringID id,void** ppInterface) ##x \
	virtual jIE* GetClassNode() ##x \
	/* �ش� entity�� jGameEntityList.xml�� ��ϵ� GetParent()->GetParent() ��带 ȣ����. */ \

		jINTERFACE_END(jIXmlEntity);

#define jINTERFACE_jIXmlEntityManager(x) public:	\
	virtual  jID* GetDoc() 	##x\
	/*jGameEntityList.xml�� ����*/\
	virtual jIXmlEntity* CreateEntity(int iEntitySerialNum,cstr szType,cstr szTemplate,jID* pDocImp=0) ##x \
	/* ��ƼƼ�� �����̸����� ��ü����. szType-> jGameEntityList.xml���� deeps=2�� �ش�*/\
	virtual 	jIXmlEntity* CreateEntity(int iEntitySerialNum, jIE* peTempate,jID* pDocImp=0) 	##x\
	/* jGameEntityList�� ��ϵ� element�� ��ü����*/\
	virtual jID* ReloadTemplate(jIE* peEntityNode) ##x\
	/* tool�� ���� entity xml���ϸ��� ��������� �ٽ� �ε� */ \
	virtual void DeleteEntity(int iEntitySerialNum) ##x\
	virtual void DeleteEntity(jIXmlEntity* pXE) ##x\
	virtual void DeleteEntity_NoSchedule(jIXmlEntity* pXE) ##x\
	virtual jIXmlEntity* FindByServerIndex(int idx) ##x\
	virtual jIE* FindTemplate(cstr sz3DFileName) ##x\
	/* gof���ϸ����� �ش� ��ƼƼ template��带 ã�� */ \

		jINTERFACE_END(jIXmlEntityManager);

		//--------------------------------------------------------------------------
		// #include "functor\\_jXE_FindByFile.h
		//--------------------------------------------------------------------------
		//g_pIXmlEntityManager->GetDoc()���� ��ENTITY TEMPLATE������ OBJECT3D��尡 szFile�� entity template node�� ã�� functor

	}//nXML
	
	namespace nInterface
	{
		extern JBASE_API nXML::jIXmlEntityManager* g_pjIXmlEntityManager;
	}

}


#endif //__jIXmlEntity__header__