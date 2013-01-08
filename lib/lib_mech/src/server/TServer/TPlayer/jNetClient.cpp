#include "StdAfx.h"
#include "TPlayer.h"
#include "jPlayerList_Dummy.h"
#include "jNetClient.h"
#include "base/jTimeHelper.h"


jNetClient *g_pNetClient=0;

void jNetClient::WritePacket(jPacket_Base* pP)
{
	jRETURN(g_pCurrUser);
	jRETURN(g_pCurrUser->m_pGrid[eChannel]);
	g_pCurrUser->m_pGrid[eChannel]->WritePacket(pP);
}

bool jNetClient::CallBack(tcstr name, jINetClient_arg)
{
	if(m_isDummyMode) return false;
	jINetClient_Receiver* pAO = (jINetClient_Receiver*)jBase::FindNamedPointer(jS(jINetClient),name);
	if(!pAO) return false;
	pAO->Call(pPlayer,pS,_pData);
	return true;
}

bool jNetClient::console_parsor(TCHAR* sz)
{
	return nCONSOLE::Get_jIConsoleCmd()->ParseCmd(sz);
}

void jNetClient::Send_X2L_USER_LOGIN(const char* world,wcstr id, vector<nMech::uint8> &pwd)
{
	nswb1024_t buf;
	jw_strcpy(g_pCurrUser->m_szID, id);
	jNET_SEND(g_pCurrUser->m_pGrid[eLogin],X2L_USER_LOGIN, world,id,pwd,"ver", "cpp_ver");
}

void jNetClient::Send_X2L_CHANNEL_SELECT(const char* channel_name)
{
	nswb1024_t buf;
	int iTot =g_pCurrUser->m_L2X_USER_LOGIN_OK.channel_name.size();
	for(int i=0; i< iTot; ++i)
	{
		if(!strncmp(g_pCurrUser->m_L2X_USER_LOGIN_OK.channel_name[i].c_str(),channel_name, strlen(channel_name)))
		{
			jNET_SEND(g_pCurrUser->m_pGrid[eLogin],X2L_CHANNEL_SELECT,g_pCurrUser->m_L2X_USER_LOGIN_OK.channel[i] );
			break;
		}
	}
}

void jNetClient::Send_X2T_TOWN_SELECT(channelid_t index)
{
//	g_pCurrUser->Change_CurrChannel(index,true);
}

void jNetClient::Send_X2T_NEW_TOWN(Sys_Castle_id_t csid,Sys_TownPos_id_t tpsid,wname32_t channel_name)
{
	//nswb1024_t buf;
	//jNET_SEND(g_pCurrUser->GetSocket_Channel(),X2T_NEW_TOWN,csid,tpsid,channel_name);
}

void jNetClient::Send_X2T_TOWN_DELETE(channelid_t index)
{
#if 0
	nswb1024_t buf;
	if(g_pCurrUser->Channel().size()<index) 
	{
		GetjILog()->Error(_T("Error channel index : %d"),index);
		return;
	}
	g_pCurrUser->Write_Packet_Channel(WRITE_X2T_TOWN_DELETE(buf,index));
#endif 
}

void jNetClient::Connect_Channel()
{
#if 0
	jPC();
	jPlayerObj *pPlayer = g_pCurrUser;
	nXML::jE e = pPlayer->Get_jE_Channel();
	if(e.empty())
	{
		jWARN1(_T("net xml : TCP_ChannelServer is not found"));
		return;
	}
	fname_t szIP;
	jt_sprintf(szIP , _T("%s:%d") ,jT(pPlayer->m_L2X_CHANNEL_SELECT_RESULT.ip), pPlayer->m_L2X_CHANNEL_SELECT_RESULT.port);
	e->Set_cstr(szIP);
	jIPacketSocket_IOCP* pSChannel = pPlayer->StartSocket_Channel(g_PL.m_pClientSession);
	if(!pSChannel)
	{
		jWARN1(_T(" to channel server connection fail : %s"),szIP);
		return;
	}
#endif 
}

jPlayerServerData* jNetClient::GetServerData()
{
	return g_pCurrUser;
}


void jNetClient::GameClient_NetworkStart()
{
	g_pCurrUser = g_PL.Start_Login(L"!@#$game_client");
	jAssert0(g_pCurrUser);
	g_pCurrUser->m_szID[0]=0;
}

const vector<jWorldServerInfo>& jNetClient::GetWorldInfo()
{ 
	return g_PL.m_world_list;
}

void jNetClient::NetworkEnd()
{
	exit (0);
#if 0
	if(g_pCurrUser->IsChannelPlayer())
	{
		g_pCurrUser->Write_Packet_Channel(
	}
	if(g_pCurrUser->IsGamePlayer())
	{

	}
#endif

}

bool jNetClient::IsOnline()
{
	if(!g_pCurrUser) return false;
	if(g_pCurrUser->m_pGrid[eLogin]) return true;
	if(g_pCurrUser->m_pGrid[eChannel]) return true;
	if(g_pCurrUser->m_pGrid[eGame]) return true;
	return false;
}



void jNetClient::SetServerTime(time_t t)
{
	m_CurrServerTime = t;
	jTimeHelper th;
	th.Get_curr_time();
	m_CurrClientTime = th.m_t;
}


time_t jNetClient::GetServerTime()
{
	jTimeHelper th;
	th.Get_curr_time();
	return m_CurrServerTime + ( th.m_t - m_CurrClientTime);
}

cstr jNetClient::GetLeftTime(IN time_t server_end_time, OUT fname_t buf)
{
#if 0
	time_t currTime = GetServerTime();
	time_t leftTime = server_end_time - currTime;
	SYSTEMTIME t = jTimeHelper::to_day(leftTime);
#endif
	jTimeHelper th;
	th.m_t = GetServerTime();
	th.Get_diff_day_string(server_end_time,buf);
	return buf;
}


nEVENT::jIMsgManager* jNetClient::Get_MM(){	return g_PL.m_pMM;}
