#ifndef as9df08asf09qweiuqfoipweupoi123u94817320
#define as9df08asf09qweiuqfoipweupoi123u94817320

#include "network/jINetClient.h"





struct jNetClient : public jINetClient
{
	jINTERFACE_HEADER(jINetClient);

	// local func
	bool CallBack(tcstr name, jINetClient_arg);
private:
	time_t m_CurrServerTime;
	time_t m_CurrClientTime;//서버시각에서의 클라 시간
public:
	void SetServerTime(time_t t);
	bool m_isDummyMode;


	jNetClient():m_isDummyMode(true){}

};

extern jNetClient *g_pNetClient;

#define jNetClient_Call_ret(X,Data) if(g_pNetClient->CallBack(jS(X),g_pCurrUser,pS,&Data))return;




#endif //as9df08asf09qweiuqfoipweupoi123u94817320