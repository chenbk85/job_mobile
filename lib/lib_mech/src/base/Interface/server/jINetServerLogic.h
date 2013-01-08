#ifndef MasdfsfdGINEefsT_2332G2AM2E36_6LOGIC_H
#define MasdfsfdGINEefsT_2332G2AM2E36_6LOGIC_H

#include "jMessageObject.h"
#include "base/nFileSystem::UFileName.h"

struct jIXmlEntity;
class jNetGameUser;
#define jINTERFACE_jIXmlDBClient(x) public:	\
	virtual void ConnectToServer(jINetPort* pGamerServer,cstr szPath) ##x \
	virtual void Refresh() ##x \
	virtual void Save() ##x \
	virtual void Disconnect() ##x \
	virtual void FrameMove() ##x \
	virtual jID* ConnectDoc(cstr szName) ##x \
	virtual void UnLoadAllDoc() ##x \
	virtual void DisconnectUserDoc(cstr szUser,cstr szNicName,jID* pDocAssert=0) ##x \
	virtual jID* ConnectUserDoc(cstr szUser,cstr szNicName) ##x \
	virtual jIE* FindUserCharByCharName(cstr szChar) ##x \
	virtual int GetUserIndex(jIE* peUserInfoNode) ##x \
	virtual int GetUserCharIndex(jIE* peCharNode) ##x \
	virtual void UnRegistDoc(cstr szName) ##x \
	virtual jID* RegistDoc(cstr szName, nFileSystem::UFileName&) ##x \
	virtual void RegistDoc(cstr szName, jID*) ##x \

	/* user_list.xml에서 해당이름의 캐릭터 노드를 리턴 */

jINTERFACE_BASE1_DEFINE(jIXmlDBClient,jIMessageObject);

struct jINetEntity : public jIMessageObject
{
	virtual jIXmlEntity* GetXmlEntity() =0;
	virtual void SetXmlEntity(jIXmlEntity*) =0; //id종류 : jPlayer.xml의 jIMessageObject . ex) CPlayer
	/*implement의 element를 jIVar로 접근: <common> 내부에 있는 element까지 검색 */ 
	virtual cstr GetName() =0;
	virtual jIVar* GetVarImp(char *szTagName) =0;
	virtual jIVar* GetVarImp(xmlid_ct szTagName) =0;
	//implement의 element를 jIVar로 접근: 내부에 있는 element까지 검색 
};

//------------------------------------------------------------------------------------
// intefrace: NetGameLogic
//------------------------------------------------------------------------------------
#define jINTERFACE_jINetServerLogic(x) public:	\
	virtual void StartService() ##x \
	virtual void LogOut				()  ##x \
	virtual jINetPort* GetNetPort_GameServer() ##x \
	virtual void FrameMove() ##x \
	virtual void ParseCmd(cstr cmd) ##x \
	virtual jIXmlDBClient* GetXmlDB() ##x \

jINTERFACE_BASE1_DEFINE(jINetServerLogic,jIMessageObject);

extern JBASE_API jINetServerLogic* g_pjINetServerLogic;
#define MAX_INV_SLOT 120
//------------------------------------------------------------------------------------
#endif //MGINETWORK_H
