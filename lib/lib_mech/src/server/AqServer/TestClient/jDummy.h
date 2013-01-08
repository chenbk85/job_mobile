/* file : jDummy.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-27 13:41:38
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __jDummy_header__
#define __jDummy_header__
#pragma once

#include "network/jinetclient.h"
#include "network/jPlayer.h"

//FUNC(NAME,HELP)
#define for_each_EGamePlayerState(FUNC)\
	FUNC(eGPS_NOT_LOGIN,"")\
	FUNC(eGPS_LOGINSERVER_CONNECTED,"로긴서버 tcp 접속완료")\
	FUNC(eGPS_LOGIN_OK,"")\
	\
	\
	FUNC(eGPS_TOWN_SERVER_BEGIN, " 여기부터 로비서버이다.")\
	\
	FUNC(eGPS_T_HELLO,"TOWN 소켓 접속 완료.")\
	FUNC(eGPS_T_USER_INFO_RECV,"정상적인 로비 접속완료. 유저정보 다받음")\
	FUNC(eGPS_T_TOWN_SELECTED,"캐릭터선택완료.")\
	\
	FUNC(eGPS_TOWN_SERVER_END, " 여기까지 로비서버이다.")\
	\
	\
	FUNC(eGPS_DUNGEON_SERVER_BEGIN,"")\
	\
	FUNC(eGPS_DUNGEON_GAMEDUNGEON_CREATING,"게임방 만들기중")\
	FUNC(eGPS_DUNGEON_GAMEDUNGEON_JOINING,"게임방 접속중")\
	FUNC(eGPS_DUNGEON_SERVER_GAMEDUNGEON_CREATED,"R2X_GAMEDUNGEON_CREATE_OK_PART_TWO까지 받은상태")\
	FUNC(eGPS_DUNGEON_TO_TOWN,"게임방에서 로비로 접속중")\
	\
	FUNC(eGPS_DUNGEON_SERVER_END,"")\



enum EGamePlayerState
{
#define _enum_EGamePlayerState(NAME,HELP) NAME,
	for_each_EGamePlayerState(_enum_EGamePlayerState)
	EGamePlayerState_END,
};



struct jDummyPlayer : public jPlayer ,public nDataStruct::yVectorNode<jDummyPlayer> 
{
	jDECLEAR_YVECTOR_MANAGER(jDummyPlayer);


	void Create()
	{
		jPlayer::_Create();
		jCLEAR(m_szID);
		m_pUdpSocket=0;
		m_iCurrTown=0;
		m_eUser_file_db.clear();
		memset(m_pSocket, 0, sizeof(m_pSocket) );
	}
	void Destroy()
	{
		if(m_eUser_file_db.full())
		{
			GetjIXml()->DeleteElement(m_eUser_file_db);
			m_eUser_file_db.clear();
		}
	}
	void CopyFrom(const jDummyPlayer& o){jAssert0(0 && "jDummyPlayer::CopyFrom");}

	// 더미 정보
	EGamePlayerState m_EGamePlayerState;
	void SetState(EGamePlayerState e)
	{
		m_EGamePlayerState = e;
		GetjILog()->Log(_T("dummy(%s) = %s"),jT(m_szID), GetString_EGamePlayerState());
	}
	tcstr GetString_EGamePlayerState()
	{
	#define __GetString_EGamePlayerState(NAME,HELP) if(m_EGamePlayerState==NAME) return _T(#NAME);
		for_each_EGamePlayerState(__GetString_EGamePlayerState);
		return _T("NULL");
	}

	username_t m_szID;
	aname32_t m_szPWD;
	userid_t Get_uid(){ return m_L2X_USER_LOGIN_OK.uid;}

	jIP_Address m_Udp_ServerIP;
	jIP_Address m_Udp_RealAddr, m_Udp_VirtualAddr ;
	jIPacketSocket_IOCP* m_pUdpSocket;

private:
	jIPacketSocket_IOCP* m_pSocket[jServerInfo::eEND_EServerTypeFrontEnd+1];//로비서버간 이동용 예비소켓
	nXML::jE m_eSocket[jServerInfo::eEND_EServerTypeFrontEnd+1];//로비서버간 이동용 예비소켓
	


public:
#define SetGetServer_socket(name,idStart,TAG) \
	void						SetSocket_##name(jIPacketSocket_IOCP* pS){ m_pSocket[jServerInfo::e##name]=pS;}\
	jIPacketSocket_IOCP* GetSocket_##name(){ return m_pSocket[jServerInfo::e##name];}\
	\
	void						StopSocket_##name	(jINetSession_Service* pSS,bool isRelease=true);\
	jIPacketSocket_IOCP* StartSocket_##name(jINetSession_Service* pSS);\
	\
	void						Set_jE_##name(jE e){ m_eSocket[jServerInfo::e##name]=e;}\
	jE							Get_jE_##name(){ return m_eSocket[jServerInfo::e##name];}\
	void Write_Packet_##name(jPacket_Base& pk)\
	{\
		if(!GetSocket_##name()) { GetjILog()->Warning(_T(#name) _T(" socket is NULL")); return ;}\
		GetSocket_##name()->WritePacket(&pk);\
	}\

	for_each_SERVER_TYPE_F(SetGetServer_socket);


#define jPACKET_MEMEBER(ns,X) n##ns::S_##X m_##X;
	jPACKET_MEMEBER(LoginServer,L_HELLO);
	jPACKET_MEMEBER(LoginServer,L2X_USER_LOGIN_OK);
	jPACKET_MEMEBER(LoginServer,L2X_CHANNEL_SELECT_RESULT);
	
	nAQ::Use_Town* Get_Use_Town(Use_Town_id_t tuid);



	bool IsTownPlayer(){return m_EGamePlayerState >= eGPS_TOWN_SERVER_BEGIN && m_EGamePlayerState <= eGPS_TOWN_SERVER_END;}
	bool IsDungeonPlayer(){return m_EGamePlayerState >= eGPS_DUNGEON_SERVER_BEGIN && m_EGamePlayerState <= eGPS_DUNGEON_SERVER_END;	}
	void Init();
	jDummyPlayer(){ Init();}
	void StopSocket_ALL(bool isRelease);
	void InitUdp(tcstr szIP,jIPacketSocket_IOCP* pS);
	void Send_ChatMsg(wcstr szMsg,DWORD delay);
	void Change_CurrTown(townid_t tid,bool isSendToServer=true);
	vector<userid_t> c_uid; 
};

tcstr ToString(jDummyPlayer* v, tname1024_t buf);
extern jDummyPlayer *g_pCurrUser;
extern vector<jWorldServerInfo> g_world_list;


#define check_Dummy() if(!g_pCurrUser){GetjILog()->Warning(_T("g_pCurrUser==NULL")); return true;} nswb1024_t buf;

#endif // __jDummy_header__
