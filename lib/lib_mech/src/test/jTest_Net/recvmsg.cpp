#include "stdafx.h"
#include "struct.h"

static char txt[1024];

jNET_PACKET_RECEIVER(jGameServer, ChatMsg)
{
	jNET_PARSE_ARG();
	if(m_pCon->GetNetPort()->IsServerMode() )  // client mode
	{
		jIConnection* pCon  = g_pGameServer->GotoBegin();
		for( ; pCon ;pCon = g_pGameServer->Next())
		{
			if(pCon == m_pCon) continue;
			pCon->Send(m_pMC->GetBuffer(), m_pMC->GetTotalSize());
		}
	}
	wsprintf(txt,"%d-ChatMsg:(%s)",m_pCon->GetSocket() , m_peArg->Find(TEXT("TEXT"))->Get_cstr());
	g_pjINet->Log(txt,true);
}


void ServerReceivedMsg(jIConnection* pCon,char* pMsg,DWORD dwLen)
{
	PTCL wID = (PTCL)(*(WORD*)pMsg);

	
	switch(wID)
	{
	case PTCL_CHAT_BROADCAST:
		{
			CHAT_PACKET	*chat = (CHAT_PACKET*)pMsg ;
			wsprintf(txt,"%d: [chatmsg]%s",pCon->GetSocket() , chat->szMsg );
			g_pjINet->Log(txt,true);
			jIConnection* pCon1 = g_pGameServer->GotoBegin();
			for( ; pCon1 ; pCon1 = g_pGameServer->Next())
			{
				if(pCon == pCon1) 
					continue;
				pCon1->Send((char*)chat,chat->GetPacketSize());
			}
		}
		break;
	}
	
}

void ClientReceivedMsg(jIConnection* pCon,char* pMsg,DWORD dwLen)
{
	PTCL wID = (PTCL)(*(WORD*)pMsg);
	switch(wID)
	{
	case PTCL_CHAT_BROADCAST:
		{
			CHAT_PACKET*	chat = (CHAT_PACKET*)pMsg;
			wsprintf(txt,"%d: [chat msg] %s ",pCon->GetSocket(), chat->szMsg);
			g_pjINet->Log(txt,true);
		}
		break;
	}

}

jNET_PACKET_RECEIVER(jHostServer, ChatMsg)
{
	jNET_PARSE_ARG();
	if(m_pCon->GetNetPort()->IsServerMode() )  // client mode
	{
		jIConnection* pCon  = g_pGameServer->GotoBegin();
		for( ; pCon ;pCon = g_pGameServer->Next())
		{
			if(pCon == m_pCon) continue;
			pCon->Send(m_pMC->GetBuffer(), m_pMC->GetTotalSize());
		}
	}
	wsprintf(txt,"%d-HostServer ChatMsg:(%s)",m_pCon->GetSocket() , m_peArg->Find(TEXT("TEXT"))->Get_cstr());
	g_pjINet->Log(txt,true);
}


void ServerReceivedMsgHost(jIConnection* pCon,char* pMsg,DWORD dwLen)
{
	PTCL wID = (PTCL)(*(WORD*)pMsg);


	switch(wID)
	{
	case PTCL_CHAT_BROADCAST:
		{
			CHAT_PACKET	*chat = (CHAT_PACKET*)pMsg ;
			wsprintf(txt,"%d: [HostServerr chatmsg]%s",pCon->GetSocket() , chat->szMsg );
			g_pjINet->Log(txt,true);
			jIConnection* pCon1 = pCon->GetNetPort()->GotoBegin();
			for( ; pCon1 ; pCon1 = pCon->GetNetPort()->Next())
			{
				if(pCon == pCon1) 
					continue;
				pCon1->Send((char*)chat,chat->GetPacketSize());
			}
		}
		break;
	}

}

void ClientReceivedMsgHost(jIConnection* pCon,char* pMsg,DWORD dwLen)
{
	PTCL wID = (PTCL)(*(WORD*)pMsg);
	switch(wID)
	{
	case PTCL_CHAT_BROADCAST:
		{
			CHAT_PACKET*	chat = (CHAT_PACKET*)pMsg;
			wsprintf(txt,"%d: [Host chat msg] %s ",pCon->GetSocket(), chat->szMsg);
			g_pjINet->Log(txt,true);
		}
		break;
	}

}

void OnDisconnect(jIConnection* pCon)
{

}
void OnConnect(jIConnection* pCon)
{
	// 접속되었을때 자동 호출되는 함수
	wsprintf(txt,"On Connect %d",pCon->GetSocket() );
	g_pjINet->Log(txt,true);
}
void OnConnectHost(jIConnection* pCon)
{
	// 접속되었을때 자동 호출되는 함수
	wsprintf(txt,"Host On Connect %d",pCon->GetSocket() );
	g_pjINet->Log(txt,true);
}

jNetPortCallback g_ServerCB ,g_ClientCB;

jNetPortCallback g_HostServerCB, g_HostClientCB;


struct __a__{ __a__()
{
	g_ServerCB.m_pConnector = OnConnect;
	g_ServerCB.m_pReceiver =ServerReceivedMsg ;
	g_ServerCB.m_pDisConnector = OnDisconnect;

	g_ClientCB.m_pConnector = OnConnect;
	g_ClientCB.m_pReceiver =ClientReceivedMsg ;
	g_ClientCB.m_pDisConnector = OnDisconnect;

	g_HostServerCB.m_pConnector = OnConnectHost;
	g_HostServerCB.m_pReceiver =ServerReceivedMsgHost ;
	g_HostServerCB.m_pDisConnector = OnDisconnect;

	g_HostClientCB.m_pConnector = OnConnectHost;
	g_HostClientCB.m_pReceiver =ClientReceivedMsgHost ;
	g_HostClientCB.m_pDisConnector = OnDisconnect;

}};static __a__ __a__1 ;
