/* file : jNetClient.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-08-17 22:33:38
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jNetClient_header__
#define __jNetClient_header__
#pragma once



#include "jINetClient.h"





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





#endif // __jNetClient_header__
