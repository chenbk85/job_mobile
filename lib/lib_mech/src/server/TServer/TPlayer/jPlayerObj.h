/* file : TClientUser.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUser_header__
#define __AqClientUser_header__
#pragma once


#include "../TCommonBase/jPlayerBase.h"
#include "../TCommonClient/jPlayerServerData.h"

//FUNC(NAME,HELP)
#define for_each_EGamePlayerState(FUNC)\
	FUNC(eGPS_NOT_LOGIN,"")\
	FUNC(eGPS_LOGINSERVER_CONNECTED,"�α伭�� tcp ���ӿϷ�")\
	FUNC(eGPS_LOGIN_OK,"")\
	\
	\
	FUNC(eGPS_TOWN_SERVER_BEGIN, " ������� �κ񼭹��̴�.")\
	\
	FUNC(eGPS_T_HELLO,"TOWN ���� ���� �Ϸ�.")\
	FUNC(eGPS_T_USER_INFO_RECV,"�������� �κ� ���ӿϷ�. �������� �ٹ���")\
	FUNC(eGPS_T_TOWN_SELECTED,"ĳ���ͼ��ÿϷ�.")\
	\
	FUNC(eGPS_TOWN_SERVER_END, " ������� �κ񼭹��̴�.")\
	\
	\
	FUNC(eGPS_DUNGEON_SERVER_BEGIN,"")\
	\
	FUNC(eGPS_DUNGEON_GAMEDUNGEON_CREATING,"���ӹ� �������")\
	FUNC(eGPS_DUNGEON_GAMEDUNGEON_JOINING,"���ӹ� ������")\
	FUNC(eGPS_DUNGEON_SERVER_GAMEDUNGEON_CREATED,"R2X_GAMEDUNGEON_CREATE_OK_PART_TWO���� ��������")\
	FUNC(eGPS_DUNGEON_TO_TOWN,"���ӹ濡�� �κ�� ������")\
	\
	FUNC(eGPS_DUNGEON_SERVER_END,"")\



enum EGamePlayerState
{
	EGamePlayerState_BEGIN,
#define _enum_EGamePlayerState(NAME,HELP) NAME,
	for_each_EGamePlayerState(_enum_EGamePlayerState)
	EGamePlayerState_END,
};


struct jPlayerObj : public jPlayerServerData ,public jPlayerBase
{
public:
	jPlayerBase_DECLEAR(jPlayerObj);
	void CopyFrom(const jPlayerObj& o){jAssert0(0 && "jPlayerObj::CopyFrom");}
	jPlayerObj(){ m_EGamePlayerState=EGamePlayerState_BEGIN;}


	// ���� ����
	EGamePlayerState m_EGamePlayerState;
	void SetState(EGamePlayerState e)
	{
		m_EGamePlayerState = e;
		jLOG1(_T("dummy(%s) = %s"),jT(m_szID), GetString_EGamePlayerState());
	}
	tcstr GetString_EGamePlayerState()
	{
#define __GetString_EGamePlayerState(NAME,HELP) if(m_EGamePlayerState==NAME) return _T(#NAME);
		for_each_EGamePlayerState(__GetString_EGamePlayerState);
		return _T("NULL");
	}

	aname32_t m_szPWD;
	player_id_t Get_uid(){ return m_L2X_USER_LOGIN_OK.pid;}

	jIP_Address m_Udp_ServerIP;
	jIP_Address m_Udp_RealAddr, m_Udp_VirtualAddr ;
	jIPacketSocket_IOCP* m_pUdpSocket;

	jIGridNode* m_pGrid[eEND_EServerTypeFrontEnd];

#define jPACKET_MEMEBER(ns,X) n##ns::S_##X m_##X;
	jPACKET_MEMEBER(LoginServer,L_HELLO);
	jPACKET_MEMEBER(LoginServer,L2X_USER_LOGIN_OK);
	jPACKET_MEMEBER(LoginServer,L2X_CHANNEL_SELECT_RESULT);

	bool IsChannelPlayer(){return m_EGamePlayerState >= eGPS_TOWN_SERVER_BEGIN && m_EGamePlayerState <= eGPS_TOWN_SERVER_END;}
	bool IsGamePlayer(){return m_EGamePlayerState >= eGPS_DUNGEON_SERVER_BEGIN && m_EGamePlayerState <= eGPS_DUNGEON_SERVER_END;	}
	void StopSocket_ALL(bool isRelease);
	void InitUdp(tcstr szIP,jIPacketSocket_IOCP* pS);
	void Send_ECHO(wcstr szMsg,DWORD delay);
	void Change_CurrChannel(channelid_t channelNo,bool isSendToServer=true);
};



tcstr ToString(jPlayerObj* v, tname1024_t buf);
extern jPlayerObj *g_pCurrUser;

#define jCHECK_CurrUser() if(!g_pCurrUser){jWARN("g_pCurrUser==NULL"); return true;} nswb1024_t buf;


#endif // __AqClientUser_header__
