/* file : jServerGrid.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-28 17:45:32
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef jPlugIn_Connect_Helper__AqServerUserBase_heASDFFASader__
#define jPlugIn_Connect_Helper__AqServerUserBase_heASDFFASader__
#pragma once


#include "../TCommonBase/jPlayerList.h"
#include "../TCommonClient/jGridNode_ClientBase.h"

#pragma warning(disable:4275)
#pragma warning(disable:4251)

struct jPlugIn_ConnnectBase : public jIPlugIn_Connection
{
	virtual int Get_CURR_USER()=0;

};
//--------------------------------------------------------------------------
struct T_SERVER_LIB_API jServerGrid
//--------------------------------------------------------------------------
{
public:
	jServerInfo m_MyInfo;
	jPlugIn_ConnnectBase* m_pPlugIn;

	//--------------------------------------------------------------------------
	// m_mapServerInfo
	//--------------------------------------------------------------------------
private:
	jLIST_TYPEDEF_map(serverid_t,jServerInfo,m_mapServerInfo);
	nUtil::jCriticalSection m_mapServerInfo_CS;
public:
	void			ServerInfo_erase(serverid_t sid,bool isNotFoundLog=false); 
	jServerInfo*	ServerInfo_find(serverid_t sid);
	void			ServerInfo_update_userCnt(std::vector<serverid_t> sid,std::vector<uint16> userCnt);
	void			ServerInfo_insert(jServerInfo& si);
	void			ServerInfo_insert_from_vector(std::vector<jServerInfo>&v);
	template<typename _Pred>
	jServerInfo*	ServerInfo_find_if(_Pred &p)
	{
		jAUTO_LOCK_CS(m_mapServerInfo_CS);
		m_mapServerInfo_it it = m_mapServerInfo.begin() , ie = m_mapServerInfo.end();
		for(;it!=ie; ++it) {if(p(it->second))return &it->second;}
		return 0;
	}
	template<typename _Pred>
	void			ServerInfo_for_each(_Pred &p)
	{
		jAUTO_LOCK_CS(m_mapServerInfo_CS);
		m_mapServerInfo_it it = m_mapServerInfo.begin() , ie = m_mapServerInfo.end();
		for(;it!=ie; ++it){p(&it->second);}
	}

	//--------------------------------------------------------------------------
	// m_mapU4_USER_CONNECTION_NOTIFY
	//--------------------------------------------------------------------------
private:
	jLIST_TYPEDEF_map(wstring,bool,m_mapU4_USER_CONNECTION_NOTIFY);
	nUtil::jCriticalSection m_mapU4_USER_CONNECTION_NOTIFY_CS;
	tstring m_sCurrParserType;
public:
	void Set_U4_USER_CONNECTION_NOTIFY_CS(player_id_t uid, wcstr id,bool isConnect);
	bool Make_U4_USER_CONNECTION_NOTIFY(vector<wstring>& uid_connect , vector<wstring>& uid_disconnect);

	//--------------------------------------------------------------------------
	// jIPlugIn_Connection 관련 루틴.
	//--------------------------------------------------------------------------
	jServerGrid()			{m_MyInfo.m_sid=0; m_pPlugIn=0;m_sCurrParserType=jS(PS);}
	void					SetParserType(tcstr szType){ m_sCurrParserType = szType;}
	tcstr					GetParserType(){ return m_sCurrParserType.c_str();}
	virtual bool			ParseCmd(tcstr szCommand);
	bool					ParseRemoteCmd(tcstr szCommand,tcstr szSERVER_NAME);
	jIPacketSocket_IOCP* 	Do_SERVER_ONLINE_ACTION(jServerInfo& si,tcstr szTag=0); // C_SERVER_ONLINE , C2SS_ONLINE_OK가 Central에서 왔을때 접속시도.
	void					generate_server_name(IN tcstr szName, OUT fname_t szServerName);

public:
	//--------------------------------------------------------------------------
	//  jNetGridHelper 
	//--------------------------------------------------------------------------
#define declare_jNetGridHelper_234(name,serverid_begin,TAG) jNetGridHelper<jGridNode_##name,serverid_t> m_##name;
	for_each_SERVER_TYPE(declare_jNetGridHelper_234);
	jNetGridHelper<jGridNode_ClientBase,player_id_t> m_Client;


	void Init(jPlugIn_ConnnectBase* pPlugIn)
	{
		m_pPlugIn = pPlugIn;
		#define init_jNetGridHelper_234(name,serverid_begin,TAG) m_##name.Init(static_cast<jIPlugIn_Net*>(pPlugIn),jS(jGridNode_##name));
		for_each_SERVER_TYPE(init_jNetGridHelper_234);
	}

	jIPacketSocket_IOCP* ConnectTo(cstr szServer ,serverid_t sid);
	void WritePacket(jPacket_Base& pk, jIPacketSocket_IOCP* pS_skip=0 , nNET::ESocket_Type eType=nNET::eNULL_SOCKET)
	{
		#define send_all_jNetGridHelper_234(name,serverid_begin,TAG) m_##name.WritePacket(pk,pS_skip,eType);
		for_each_SERVER_TYPE(send_all_jNetGridHelper_234);
	}

	template <class _Predicate>	void for_each(_Predicate __pred ) 
	{
		#define for_each_1356225467(name,serverid_begin,TAG) m_##name.for_each(__pred);
		for_each_SERVER_TYPE(for_each_1356225467);
	}
	template <class _Predicate>	void for_each(EServerType eType,_Predicate __pred ) 
	{
		#define for_each_13565467(name,serverid_begin,TAG) if(eType==e##name) m_##name.for_each(__pred);
		for_each_SERVER_TYPE(for_each_13565467);
	}
	template <class _Predicate>	jIGridNode* find_if(_Predicate __pred )
	{
		#define find_if_134655756(name,serverid_begin,TAG) {jGridNode_##name* pGN = m_##name.find_if(__pred); if(pGN) return pGN;}
		for_each_SERVER_TYPE(find_if_134655756);
		return 0;
	}
	template <class _Predicate>	jIGridNode* find_if(serverid_t sid,_Predicate __pred )
	{
		#define find_if_jNetGridHelper_275634(name,serverid_begin,TAG) \
		if( jServerInfo::is_same_type(e##name,sid) ){return m_##name.find_if(__pred);}
		for_each_SERVER_TYPE(find_if_jNetGridHelper_275634);
		return 0;
	}
	template <class _Predicate>	jIGridNode* find_if(EServerType eType,_Predicate __pred )
	{
		#define find_if_jNetGridHelper_34534234(name,serverid_begin,TAG) \
		if( eType == e##name){return m_##name.find_if(__pred); }
		for_each_SERVER_TYPE(find_if_jNetGridHelper_34534234);
		return 0;
	}
	jIGridNode*	find(serverid_t sid)
	{
		if(sid==0) return 0;
		#define find_jNetGridHelper_125352345(name,serverid_begin,TAG) \
		if( jServerInfo::is_same_type(e##name,sid) ){return m_##name.find(sid);}
		for_each_SERVER_TYPE(find_jNetGridHelper_125352345);
		return 0;
	}


	

};



#define jLAMDA_send_packet_sid(X,Z) X(serverid_t,sid) Z(jPacket_Base&,pk)
jLAMDA_find_if(send_packet_sid,jIGridNode*)
{
	jSI_ret(it,false);
	if(si->m_sid!=sid) return false;
	it->WritePacket(&pk);
	return true;
}
jLAMDA_end();

#define jLAMDA_send_packet(X,Z) Z(jPacket_Base&,pk)
jLAMDA_find_if(send_packet,jIGridNode*)
{
	jSI_ret(it,false);
	it->WritePacket(&pk);
	return true;
}
jLAMDA_end();



// 아래 구문은 같은 뜻이다.
//	g_SG.m_DBCache.find_if(send_packet_sid(sid_tot.back().first	, WRITE_W2DC_USER_LOGIN(buf	,pUser->m_pid , Data.id) ) );
//	g_SG.m_DBCache.SEND_PACKET_SID(sid_tot.back().first	, W2DC_USER_LOGIN ,pUser->m_pid , Data.id);

#define SEND_PACKET_SID(sid,PACKET,...) find_if(sid,send_packet_sid(sid,WRITE_##PACKET(buf,__VA_ARGS__)))
#define SEND_PACKET_TYPE(eServerType,PACKET,...) find_if(eServerType,send_packet(WRITE_##PACKET(buf,__VA_ARGS__)))
#define SEND_PACKET(PACKET,...) find_if(send_packet(WRITE_##PACKET(buf,__VA_ARGS__)))


//TCommonServer.dll이 아닌 server.dll에 위치하게 하자.
extern jServerGrid g_SG;

#endif // jPlugIn_Connect_Helper__AqServerUserBase_heASDFFASader__
