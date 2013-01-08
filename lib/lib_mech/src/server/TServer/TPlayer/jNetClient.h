#ifndef as9df08asf09qweiuqfoipweupoi123u94817320
#define as9df08asf09qweiuqfoipweupoi123u94817320

#include "../TCommonClient/jINetClient.h"


/*! game_client.exe에서 사용하는 객체. test_dummy로 돌릴때는 사용안함.
	jNetClient 는 내부적으로 g_pCurrUser를 유저객체로 간주하고 처리한다.
*/
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