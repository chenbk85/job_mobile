/* file : PlugIn_ToFrontEnd.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "PlugIn_ToFrontEnd.h"
#include <boost/bind.hpp>

jUserZoneList_U g_Users;

void Job_U2W_USER_DISCONNECT(nEVENT::jIMessage*)
{// �α伭���� ���� ���� ������ �������� U2W_USER_DISCONNECT�� ������.
	jFE();
	if(!pFE->m_DisconnectedUsers.size()) return;
	nswb8000_t buf;
	jAUTO_LOCK_CS1(pFE->m_DisconnectedUsers_CS);
	PlugIn_ToFrontEnd::m_DisconnectedUsers_it it = pFE->m_DisconnectedUsers.begin(), ie = pFE->m_DisconnectedUsers.end();
	for( ; it!= ie ; ++it)
	{
		AqConnectedServerNode* pW = pFE->find_user(it->first);
		if(!pW) 
		{
			GetjILog()->Warning(jFUNC1 _T("world server not found : %d"), it->first);
			continue;
		}

		vector<astring> uids;
		for(int i=0; i< it->second.size(); ++i)
		{
			uids.push_back(it->second[i]);
			if(((i+1)%100)==0)
			{
				pW->Write_Packet(WRITE_U2W_USER_DISCONNECT(buf, uids));
				uids.clear();
			}
		}
		if(uids.size())	{	pW->Write_Packet(WRITE_U2W_USER_DISCONNECT(buf, uids)); }
	}
	pFE->m_DisconnectedUsers.clear();
}

jPLUGIN_FRONT_END_cpp_code_Start(PlugIn_ToFrontEnd,AqConnectedServerNode)
{
	jAUTO_LOCK_CS1(g_Users.m_CS);
	g_Users.Clear();
	m_pMM->Regist_TimeBase(0 , Job_U2W_USER_DISCONNECT, 0,pv_U2W_USER_DISCONNECT->Get_float())->DoWakeUp();

}
jPLUGIN_cpp_code_Stop(PlugIn_ToFrontEnd)
{
	jAUTO_LOCK_CS1(g_Users.m_CS);
	g_Users.Clear();

}
jPLUGIN_FRONT_END_cpp_code_End(PlugIn_ToFrontEnd,AqConnectedServerNode);

PlugIn_ToFrontEnd::PlugIn_ToFrontEnd()
{
}

bool PlugIn_ToFrontEnd::ParseCmd(tcstr szCommand)
{
	//nswb1024_t buf;
	std::tstring str = _T("FromAqCentral:");
	str += szCommand;
	net_string256 sendStr = str.c_str();
	//jPacket_Base pk = nTestCentralServer::WRITE_TS_ECHO(buf, sendStr );
	//jIPacketSocket_IOCP* p =0;
	//send_all(&pk, p );	
	return false;
}

void jSocketDebugger(jIPacketSocket_IOCP* pS)
{

}

// CIocp�� �����Լ���
//serverid_t jSERVER_sid(){ jBE_ret(0);assert(pBE->m_sid);return pBE->m_sid;}
serverid_t jSERVER_sid(){ return 0;}
VOID PlugIn_ToFrontEnd::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(U_HELLO);//AqConnectedServerNode* pServer;nswb256_t buf; fname_t szIP
}

VOID PlugIn_ToFrontEnd::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //AqConnectedServerNode* pServer
	nswb1024_t buf;

	if(pServer->IsFrontServer())
	{
		vector<jUserZoneInfo*> del_users;
		
		jAUTO_LOCK_CS1(m_DisconnectedUsers_CS);
		//--------------------------------------------------------------------------
		/// �ش� ������ ������ ���� ��������ó��
		//--------------------------------------------------------------------------
		#define jLAMDA_make_user_offline(X,Z) X(vector<jUserZoneInfo*>&, del_users) Z(AqConnectedServerNode* ,pServer)
		jLAMDA_for_each(make_user_offline,jUserZoneInfo&)
		{
			serverid_t _sid = it.Get_ConnectedServer(pServer->GetServerType() );
			if(_sid == pServer->Get_sid())
			{
				it.Set_ConnectedServer(pServer->GetServerType(), 0 );
			}
			if( !it.IsConnectedServer() )
			{
				if(pServer->m_eType==jServerInfo::eLogin)
				{// �� �α伭���� ��� ������������ó���� Dungeon&Town������ ���ӵ��� ���������̸�
					// ���忡 �뺸�ؼ� DBCache������ ������ �Ѵ�.
					jFE();
					pFE->m_DisconnectedUsers[it.m_sid_world].push_back(it.m_szID);
				}
				del_users.push_back(&it);
			}
		}
		jLAMDA_end();

		{
			jAUTO_LOCK_CS1(g_Users.m_CS);
			g_Users.for_each(make_user_offline(del_users,pServer));
		}
		using namespace boost;
		jFOR_EACH(del_users , bind(&jUserZoneInfoList::erase,&g_Users,_1) );
	}
	else if(pServer->IsBackServer())
	{

	}
	else
	{
		//jTODO error ó��
	}


	erase(pServer);
}
