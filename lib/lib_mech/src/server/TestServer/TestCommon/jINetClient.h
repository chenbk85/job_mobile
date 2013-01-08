
#ifndef __AqClient_Bridge_Interface_h__
#define __AqClient_Bridge_Interface_h__


//#include "..\TCommonClient/jPlayer.h"


struct jPlayer;

typedef void jNet_CallBack_t(void*);
#define jINTERFACE_jINetClient(X) public:	\
	virtual jPlayer* GetPlayer() ##X\
	\
	virtual bool console_parsor(TCHAR* sz) ##X \
	/* 로긴서버 접속*/\
	virtual void Send_X2L_USER_LOGIN(const char* world,const char* id, vector<nMech::uint8> &pwd) ##X \
	virtual void SendToTown(jPacket_Base* pP) ##X \
	\
	virtual void NetworkStart()##X\
	virtual void NetworkEnd()##X\
	\
	virtual time_t GetServerTime() ##X \
	virtual nEVENT::jIMsgManager* Get_MM() ##X \
	/*서버기준의 종료시간을 기준으로 남은 시간을 스트링으로 만들어줌*/\
	virtual cstr GetLeftTime(IN time_t server_end_time, OUT fname_t buf) ##X\

jINTERFACE_END(jINetClient);


extern jINetClient* g_pjINetClient;





#define jINetClient_arg jPlayer* pUser,jIPacketSocket_IOCP* pS,void* _pData
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

