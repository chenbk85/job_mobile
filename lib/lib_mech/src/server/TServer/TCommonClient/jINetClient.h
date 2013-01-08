
#ifndef __AqClient_Bridge_Interface_h__
#define __AqClient_Bridge_Interface_h__


#include "../TCommonClient/jPlayerServerData.h"


typedef void jNet_CallBack_t(void*);
#define jINTERFACE_jINetClient(X) public:	\
	virtual jPlayerServerData* GetServerData() ##X\
	\
	virtual bool console_parsor(TCHAR* sz) ##X \
	/* 로긴서버 접속*/\
	virtual void Send_X2L_USER_LOGIN(const char* world,wcstr id, vector<nMech::uint8> &pwd) ##X \
	virtual void Send_X2L_CHANNEL_SELECT(const char* channel_name) ##X \
	virtual void Send_X2T_TOWN_SELECT(channelid_t channelid) ##X \
	virtual void Send_X2T_NEW_TOWN(Sys_Castle_id_t csid,Sys_TownPos_id_t tpsid,wname32_t channel_name) ##X \
	virtual void Send_X2T_TOWN_DELETE(channelid_t index) ##X \
	virtual void WritePacket(jPacket_Base* pP) ##X \
	\
	virtual void GameClient_NetworkStart()##X\
	virtual void NetworkEnd()##X\
	virtual void Connect_Channel() ##X \
	\
	virtual const vector<jWorldServerInfo>& GetWorldInfo() ##X\
	virtual bool IsOnline() ##X \
	virtual time_t GetServerTime() ##X \
	virtual nEVENT::jIMsgManager* Get_MM() ##X \
	/*서버기준의 종료시간을 기준으로 남은 시간을 스트링으로 만들어줌*/\
	virtual cstr GetLeftTime(IN time_t server_end_time, OUT fname_t buf) ##X\

jINTERFACE_END(jINetClient);


extern jINetClient* g_pjINetClient;





#define jINetClient_arg jPlayerServerData* pPlayer,jIPacketSocket_IOCP* pS,void* _pData
struct jINetClient_Receiver{virtual void Call(jINetClient_arg) =0;};

#ifndef jINetClient_RECEIVER
#define jINetClient_RECEIVER(ACTION) \
struct _jJOIN_2(jINetClient_,ACTION) : public jINetClient_Receiver {\
	_jJOIN_2(jINetClient_,ACTION)(){nMech::jBase::RegistNamedPointer(jS(jINetClient),_T(#ACTION),this);} \
	virtual void Call(jINetClient_arg);}; \
	static _jJOIN_2(jINetClient_,ACTION) _jJOIN_2(g_jINetClient_,ACTION);\
	void _jJOIN_2(jINetClient_,ACTION)::Call(jINetClient_arg)
#endif


#define jINetClient_RECEIVER_ARG(X) S_##X& Data = *((S_##X*)_pData);nswb1024_t  buf;

#endif //asdlasdfqwerqwerqwerwqe