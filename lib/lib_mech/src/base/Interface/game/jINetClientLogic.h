#ifndef MGasdf9087INET_GAME_LOGIC_H
#define MGasdf9087INET_GAME_LOGIC_H

#include "jMessageObject.h"
#include "jLC_ServerIndex.h"
#include "interface/jINet.h"
struct jINetParty;
struct jIXmlEntity;
//------------------------------------------------------------------------------------
// Callback-Command: CallbackNetwork
//------------------------------------------------------------------------------------
struct jINetClientLogic;
struct _jINetClientCallback: public jRttiObj{	\
	virtual void Call(jINetClientLogic*,jIE*,void*)=0;\
	virtual _jINetClientCallback* GetNext_()=0;\
	virtual void SetNext_(_jINetClientCallback*)=0;\
};

#ifndef jDEFINE_RTTIOBJ_BY_SCOPE_NICK
#define jDEFINE_RTTIOBJ_BY_SCOPE_NICK(className,scope,NICK,iObj , iSlot)\
	jDEFINE_SIMPLE_MEMORY(className,iObj,iSlot);\
	jRTTI* className::getClassRep() const { return &className::ms_RTTI; }           \
	jRttiConcrete<className> className::ms_RTTI(#NICK,#scope,true);
#endif

#ifndef jNETCLIENT_CALLBACK_RECEIVER
#define jNETCLIENT_CALLBACK_RECEIVER(LOCAL_NAME,PACKET) \
struct _jJOIN_(LOCAL_NAME,PACKET) : public _jINetClientCallback \
{	jDECLARE_RTTIOBJ(_jJOIN_(LOCAL_NAME,PACKET));\
	_jINetClientCallback* m_pNext;\
	virtual void Call(jINetClientLogic*,jIE*,void* );\
	virtual _jINetClientCallback* GetNext_(){ return m_pNext;}\
	virtual void SetNext_(_jINetClientCallback* a){m_pNext=a;} }; \
	jDEFINE_RTTIOBJ_BY_SCOPE_NICK( _jJOIN_(LOCAL_NAME,PACKET) , LOCAL_NAME,PACKET,1,1 ); \
	void _jJOIN_(LOCAL_NAME,PACKET)::Call(jINetClientLogic* m_pNCB,jIE* m_peArg,void* m_pV)
#endif


struct jINetEntity : public jIMessageObject
{
	enum EType
	{
		eUSER,
		eMON,
		eITEM,
		EType_MAX
	};

	virtual jIXmlEntity* GetXmlEntity()=0	;
	virtual void SetXmlEntity(jIXmlEntity*)=0; //id종류 : jPlayer.xml의 jIMessageObject . ex) CPlayer
	/*implement의 element를 jIVar로 접근: <common> 내부에 있는 element까지 검색 */ 
	virtual cstr GetName()=0 ;
	virtual jIVar* GetVarImp(char *szTagName) =0;
	virtual void* GetUserData() =0;
	virtual void SetUserData(void*v) =0;
	virtual ServerIndex_t GetID() =0;
	virtual EType GetType() =0;

	//implement의 element를 jIVar로 접근: 내부에 있는 element까지 검색 

};
//------------------------------------------------------------------------------------
// jINetControlPlayer
//------------------------------------------------------------------------------------
#define jINTERFACE_jINetControlPlayer(x) public:	\
	virtual void CheckMove() ##x \
	virtual void Move(int flag=0) ##x \
	virtual void MoveStop() ##x \
	virtual void Jump() ##x \
	virtual void CancelCast(int skill_index) ##x \
	virtual void Revive	(int location=0) ##x \
	virtual void Attack	(jIXmlEntity* pTarget) ##x \
	virtual void CastSpell(int skill_index, jIXmlEntity* pTarget) ##x \
	virtual void PickUpItem(jIXmlEntity* pItem) ##x \
	virtual jIXmlEntity* GetXmlEntity() ##x \
	virtual void MoveTo(int dir,float _x,float _y,float _z ,int flag) ##x \

jINTERFACE_DEFINE(jINetControlPlayer);

//------------------------------------------------------------------------------------
// intefrace: NetGameLogic
//------------------------------------------------------------------------------------
struct jINetPort;
#define jINTERFACE_jINetClientLogic(x) public:	\
	virtual bool ConnectToServer		() ##x \
	virtual jINetControlPlayer*	GetControlPlayer	() ##x \
	virtual void LogIn				(cstr szUserID, cstr szPasswrod)  ##x \
	virtual bool SelectCharSlot		(int iCharSlot) ##x \
	/*iCharSlot: 가장 첫번째 캐릭터가 0부터 시작 */ \
	virtual void ReadyToEnterZone	() ##x \
	virtual void LogOut				() ##x \
	virtual bool DeleteCharSlot		(int iCharSlot) ##x \
	virtual bool CreateNewChar		(cstr szCharName, cstr iClan) ##x \
	virtual bool IsOnline		() ##x \
	virtual void Chat			(const char *szChat, xmlid_ct type) ##x \
	/* type은  LCGameServer.xml <CHAT_TYPE> */ \
	virtual void ChatTo		(const char *szChat, cstr szWho) ##x \
	virtual void OpenInven			() ##x \
	virtual void MoveItem			(jIXmlEntity* pItem ,int newPos) ##x \
	virtual jIConnection* GetSocket() ##x \
	virtual void FrameMove() ##x \
	virtual void RegistCallback(cstr szScope) ##x \
	virtual void DeleteEntity(jIXmlEntity* pXE) ##x \
	/* szScope는 항상 jNCB_로 시작해야한다. */ \

jINTERFACE_BASE1_DEFINE(jINetClientLogic,jIMessageObject);

extern JBASE_API jINetClientLogic* g_pjINetClientLogic;
//------------------------------------------------------------------------------------
#endif //MGINETWORK_H
