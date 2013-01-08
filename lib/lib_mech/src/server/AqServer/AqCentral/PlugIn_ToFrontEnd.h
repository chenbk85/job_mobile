/* file : PlugIn_ToFrontEnd.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-10 13:27:09
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __PlugIn_ToFrontEnd_header__
#define __PlugIn_ToFrontEnd_header__
#pragma once

#include "../AqCommon/jServerUser.h"
#include "jAqServerNode.h"


//////////////////////////////////////////////////////////////////////////
// central
typedef jServerUsers<AqConnectedServerNode,serverid_t> AqCentral_base_t;
class PlugIn_ToFrontEnd: public jIPlugIn_Net_SQ< PlugIn_ToFrontEnd,AqCentral_base_t>
{
public:
	jPLUGIN_header_code(PlugIn_ToFrontEnd);
	virtual tcstr GetPlugInNicName()
	{ 
		return _T("PlugIn_AqCentral");
	}

	nXML::jE m_eServers;

	jLIST_TYPEDEF_map(serverid_t,uint16,m_mapC2_USER_CONNECTION_NOTIFY_Town);
	nUtil::jCriticalSection m_mapC2_USER_CONNECTION_NOTIFY_CS_Town;

	jLIST_TYPEDEF_map_typedef(serverid_t,uint16,serverid_and_cnt);
	jLIST_TYPEDEF_map(tstring,serverid_and_cnt_t,m_mapC2_USER_CONNECTION_NOTIFY_Dungeon);
	nUtil::jCriticalSection m_mapC2_USER_CONNECTION_NOTIFY_CS_Dungeon;

	void Do_Disconnect_User(userid_t uid);

	void Send_Packet_ToServers(const tstring& szClust, jPacket_Base& pk);
	void Send_Packet_InWorlds(tcstr szWorld, jPacket_Base& pk,AqConnectedServerNode* pSkip);
};
DECLARE_INSTANCE_TYPE(PlugIn_ToFrontEnd);



struct _jxGetServerList
{
	jServerInfo::EServerType eType;
	vector<jServerInfo>& pList;
	_jxGetServerList(jServerInfo::EServerType eT,vector<jServerInfo>& p): eType(eT), pList(p) {}
	void operator()(AqConnectedServerNode* pServer)
	{
		if( !pServer->Base().IsServer(eType) ) return;
		pList.push_back(pServer->Base());
	}

};


#define jLAMDA_jxSendToServers(X,Z) X(jPacket_Base&,pk)	X(jServerInfo::EServerType, eType) 	Z(AqConnectedServerNode*,pThis)
jLAMDA_for_each(jxSendToServers,AqConnectedServerNode&)
{ // 모든 서버에 보낼때는 send_all()함수를 사용하자.
	if( !it.Base().IsServer(eType)) 
		return;
	if(pThis==&it)
		return;
	it.Write_Packet(pk);
}
jLAMDA_end()

#define jLAMDA_jxFindServer(X,Z) Z(serverid_t ,sid)
jLAMDA_find_if(jxFindServer,AqConnectedServerNode&)
{
	if(it.Get_sid()==sid) return true;
	return false;
}
jLAMDA_end()

// X _DATA; 가 지정된상태
#define READ_PACKET_C_P_Data(X,_DATA)	READ_PACKET_Data(X,_DATA); jFE();
// 자동으로 X Data를 지정함.
#define READ_PACKET_C_PS_Data(X)		READ_PACKET_C_P_Data(X,Data); AqConnectedServerNode* pasdf;\
										AqConnectedServerNode *pFServer = pFE->get_user(pS);pasdf=pFServer;if(!pFServer)return;

#define READ_PACKET_C_PB_Data(X)		READ_PACKET_C_P_Data(X,Data);	nswb1024_t buf;
#define READ_PACKET_C_Data(X,_DATA)		READ_PACKET_C_P_Data(X,_DATA); nswb1024_t buf;AqConnectedServerNode* pasdf;\
										AqConnectedServerNode*pFServer = pFE->get_user(pS);pasdf=pFServer;if(!pFServer) return;

// 주의 xml은 CreateElement()된 것이므로 필요없을땐 DeleteElement()해야한다.
#define READ_PACKET_C_XML(X,xml) S_##X Data;Data.xml = GetjIXml()->CreateElement(); READ_PACKET_C_PS_Data(X);


#define READ_PACKET_C_P(X)				READ_PACKET(X); jFE();
#define READ_PACKET_C_PS(X)				READ_PACKET_C_P(X); AqConnectedServerNode* pasdf;AqConnectedServerNode *pFServer = pFE->get_user(pS);pasdf=pFServer;if(!pFServer)return;
#define READ_PACKET_C_PB(X)				READ_PACKET_C_P(X);	nswb1024_t buf;
#define READ_PACKET_C(X)				READ_PACKET_C_P(X); nswb1024_t buf;AqConnectedServerNode* pasdf;AqConnectedServerNode*pFServer = pFE->get_user(pS);pasdf=pFServer;if(!pFServer) return;


#endif // __PlugIn_ToFrontEnd_header__
