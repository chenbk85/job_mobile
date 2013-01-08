/* file : PlugIn_Server.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-08 14:05:42
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TUser.h"
#include "PlugIn_Server.h"


void Job_U2W_USER_DISCONNECT(nEVENT::jIMessage*)
{// �α伭���� ���� ���� ������ �������� U2W_USER_DISCONNECT�� ������.

#ifdef TSERVER_PREPARE
	jPS();
	if(!pPS->m_DisconnectedUsers.size()) return;
	nswb8000_t buf;
	jAUTO_LOCK_CS1(pPS->m_DisconnectedUsers_CS);
	PlugIn_Server::m_DisconnectedUsers_it it = pPS->m_DisconnectedUsers.begin(), ie = pPS->m_DisconnectedUsers.end();
	for( ; it!= ie ; ++it)
	{
		jIGridNode* pW = pPS->find_user(it->first);
		if(!pW) 
		{
			jWARN1(_T("world server not found : %d"), it->first);
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
	pPS->m_DisconnectedUsers.clear();
#endif //TSERVER_PREPARE
}

jPLUGIN_CPP_CODE_START_Server(PlugIn_Server)
{
	m_pMM->Regist_TimeBase(0 , Job_U2W_USER_DISCONNECT, 0,pv_U2W_USER_DISCONNECT->Get_float())->DoWakeUp();

}
jPLUGIN_CPP_CODE_STOP(PlugIn_Server)
{

}
jPLUGIN_CPP_CODE_END_Server(PlugIn_Server);

PlugIn_Server::PlugIn_Server()
{

}

bool PlugIn_Server::ParseCmd(tcstr szCommand)
{
	jPS_COMMON_ParseCmd(U);
}


// CIocp�� �����Լ���
VOID PlugIn_Server::OnIoConnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoConnected_fromServer(U_HELLO);// jIGridNode* pGN, szIP,nswb256_t buf
}

VOID PlugIn_Server::OnIoDisconnected(jIPacketSocket_IOCP *pS)
{
	jFE_OnIoDisconnected_fromServer(); //jIGridNode* pGN ,jServerInfo* si ,jServerInfo* si
	nswb1024_t buf;

#ifdef TSERVER_PREPARE
	if(pServer->IsFrontServer())
	{
		vector<jPlayerBase*> del_users;
		
		jAUTO_LOCK_CS1(m_DisconnectedUsers_CS);
		//--------------------------------------------------------------------------
		/// �ش� ������ ������ ���� ��������ó��
		//--------------------------------------------------------------------------
		#define jLAMDA_make_user_offline(X,Z) X(vector<jPlayerBase*>&, del_users) Z(jIGridNode* ,pServer)
		jLAMDA_for_each(make_user_offline,jPlayerBase*)
		{
			serverid_t _sid = it->Get_Server(pServer->GetServerType() );
			if(_sid == si->m_sid)
			{
				it->Set_Server(pServer->GetServerType(), 0 );
			}
			if( !it->IsConnectedServer() )
			{
				if(pServer->m_eType==eLogin)
				{// �� �α伭���� ��� ������������ó���� Game&Channel������ ���ӵ��� ���������̸�
					// ���忡 �뺸�ؼ� DBCache������ ������ �Ѵ�.
					jPS();
					pPS->m_DisconnectedUsers[it->m_sid_world].push_back(it->m_szID);
				}
				del_users.push_back(&it);
			}
		}
		jLAMDA_end();

		{
			jAUTO_LOCK_CS1(g_Users.m_CS);
			g_Users.for_each(make_user_offline(del_users,pServer));
		}
		jFOR_EACH(del_users , bind(&jUserZoneInfoList::erase,&g_Users,_1) );
	}
	else if(pServer->IsBackServer())
	{

	}
	else
	{
		//jTODO error ó��
	}

#endif //TSERVER_PREPARE

}
