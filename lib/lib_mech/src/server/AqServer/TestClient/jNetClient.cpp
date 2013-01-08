#include "StdAfx.h"
#include "jNetClient.h"
#include "base/jTimeHelper.h"

jNetClient g_jNetClient;
jNetClient *g_pNetClient=&g_jNetClient;

void jNetClient::SendToTown(jPacket_Base* pP)
{
	if( !g_pCurrUser->GetSocket_Town() ) return;
	g_pCurrUser->GetSocket_Town()->WritePacket(pP);
}

bool jNetClient::CallBack(tcstr name, jINetClient_arg)
{
	if(m_isDummyMode) return false;
	jINetClient_Receiver* pAO = (jINetClient_Receiver*)jBase::FindNamedPointer(jS(jINetClient),name);
	if(!pAO) return false;
	pAO->Call(pUser,pS,_pData);
	return true;
}

bool jNetClient::console_parsor(TCHAR* sz)
{
	return nCONSOLE::Get_jIConsoleCmd()->ParseCmd(sz);
}

void jNetClient::Send_X2L_USER_LOGIN(const char* world,const char* id, vector<nMech::uint8> &pwd)
{
	nswb1024_t buf;
	ja_strcpy(g_pCurrUser->m_szID, id);
	g_pCurrUser->Write_Packet_Login(WRITE_X2L_USER_LOGIN(buf, world,id,pwd,"ver", "cpp_ver"));
}

void jNetClient::Send_X2L_CHANNEL_SELECT(const char* channel_name)
{
	nswb1024_t buf;
	int iTot =g_pCurrUser->m_L2X_USER_LOGIN_OK.channel_name.size();
	for(int i=0; i< iTot; ++i)
	{
		if(!strncmp(g_pCurrUser->m_L2X_USER_LOGIN_OK.channel_name[i].c_str(),channel_name, strlen(channel_name)))
		{
			g_pCurrUser->Write_Packet_Login(WRITE_X2L_CHANNEL_SELECT(buf, g_pCurrUser->m_L2X_USER_LOGIN_OK.channel[i] ) );
			break;
		}
	}
}

void jNetClient::Send_X2T_TOWN_SELECT(townid_t index)
{
	g_pCurrUser->Change_CurrTown(index,true);
}

void jNetClient::Send_X2T_NEW_TOWN(Sys_Castle_id_t csid,Sys_TownPos_id_t tpsid,wname32_t town_name)
{
	nswb1024_t buf;
	if(g_pCurrUser->GetSocket_Town())
		g_pCurrUser->GetSocket_Town()->WritePacket(&WRITE_X2T_NEW_TOWN(buf,csid,tpsid,town_name));
}

void jNetClient::Send_X2T_TOWN_DELETE(townid_t index)
{
	nswb1024_t buf;
	if(g_pCurrUser->Town().size()<index) 
	{
		GetjILog()->Error(_T("Error town index : %d"),index);
		return;
	}
	g_pCurrUser->Write_Packet_Town(WRITE_X2T_TOWN_DELETE(buf,index));
}

void jNetClient::Connect_Town()
{
	jBE();
	jDummyPlayer *pUser = g_pCurrUser;
	nXML::jE e = pUser->Get_jE_Town();
	if(e.empty())
	{
		GetjILog()->Warning(jFUNC1 _T("net xml : TCP_TownServer is not found"));
		return;
	}
	fname_t szIP;
	jt_sprintf(szIP , _T("%s:%d") ,jT(pUser->m_L2X_CHANNEL_SELECT_RESULT.ip), pUser->m_L2X_CHANNEL_SELECT_RESULT.port);
	e->Set_cstr(szIP);
	jIPacketSocket_IOCP* pSTown = pUser->StartSocket_Town(pBE->m_pClientSession);
	if(!pSTown)
	{
		GetjILog()->Warning(jFUNC1 _T(" to town server connection fail : %s"),szIP);
		return;
	}
}

jPlayer* jNetClient::GetPlayer()
{
	return g_pCurrUser;
}


void jNetClient::NetworkStart()
{
	jBE();
	g_pCurrUser = pBE->CreateDummyUser("Player");
	jAssert0(g_pCurrUser);
	nXML::jE e_login = g_pCurrUser->Get_jE_Login();
	assert(e_login.full());
	e_login->Set_cstr(pv_DEFAULT_LOGIN_IP->Get_cstr());
	ja_strcpy(g_pCurrUser->m_szPWD , "");
	ja_strcpy(g_pCurrUser->m_szID , "");
	g_pCurrUser->StartSocket_Login(pBE->m_pClientSession);
}

const vector<jWorldServerInfo>& jNetClient::GetWorldInfo()
{ 
	return g_world_list;
}

void jNetClient::NetworkEnd()
{
	exit (0);
#if 0
	if(g_pCurrUser->IsTownPlayer())
	{
		g_pCurrUser->Write_Packet_Town(
	}
	if(g_pCurrUser->IsDungeonPlayer())
	{

	}
#endif

}

bool jNetClient::IsOnline()
{
	if(!g_pCurrUser) return false;
	if(g_pCurrUser->GetSocket_Login()) return true;
	if(g_pCurrUser->GetSocket_Town()) return true;
	if(g_pCurrUser->GetSocket_Dungeon()) return true;
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


nEVENT::jIMsgManager* jNetClient::Get_MM(){	jBE_ret(0);return pBE->m_pMM;}