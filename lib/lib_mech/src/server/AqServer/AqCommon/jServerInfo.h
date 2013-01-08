/* file : jServerInfo.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-04 20:42:06
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __jServerInfo_header__
#define __jServerInfo_header__
#pragma once

//--------------------------------------------------------------------------
// server 객체 클래스 지원 코드
//--------------------------------------------------------------------------

//#define func(name,idStart,TAG)
#define for_each_SERVER_TYPE_F(func)\
	func(Login,1000,L)\
	func(Town,2000,T)\
	func(Dungeon,3000,D)\

//#define func(name,idStart,TAG)
#define for_each_SERVER_TYPE_B(func)\
	func(User,4000,U)\
	func(DBCache,5000,DC)\
	func(World,6000,W)\
	func(Msg,7000,M)\
	func(Trade,8000,TR)\

#define for_each_SERVER_TYPE_ADMIN(func)\
	func(Monitor,9000,TM)\

//#define func(name,idStart,TAG)
#define for_each_SERVER_TYPE(func)\
	for_each_SERVER_TYPE_F(func)\
	for_each_SERVER_TYPE_B(func)\
	for_each_SERVER_TYPE_ADMIN(func)\

//#define server_id_const(name,idStart,TAG) const serverid_t g_ID_MIN_##name = idStart; const serverid_t g_ID_MAX_##name = idStart+900;
//for_each_SERVER_TYPE(server_id_const)


#define jLAMDA_jServerUserCountInfo(X,Z) \
	X(serverid_t ,sid)\
	Z(uint16,m_iTotClient)
jLAMDA_CTOR(jServerUserCountInfo)
{

}
jLAMDA_end()

/* *_* by icandoit : 2009-08-28 20:31:42
<aqservernode >
	<Fuzhou >
		<aqservernode  m_szName='ICANDOIT'  m_szWorld='Fuzhou'  m_szServiceIP='192.168.212.111'  
					m_service_port='33002'  m_iMaxClient='50'  m_eType='WorldServer' m_szIP='192.168.212.111'  m_sid='1'  m_iTotClient='0' >
		</aqservernode>
	</Fuzhou>
	<LoginServer >
		<aqservernode  m_szName='ICANDOIT'  m_szWorld='Fuzhou'  m_szServiceIP='192.168.212.111'  
					m_service_port='33100'  m_iMaxClient='3000'  m_eType='LoginServer'  m_szIP='192.168.212.111'  m_sid='2'  m_iTotClient='0' >
		</aqservernode>
	</LoginServer>
	<UserServer>
		<aqservernode  m_szName='ICANDOIT'  m_szWorld='Fuzhou'  m_szServiceIP='192.168.212.111'  
						m_service_port='33003'  m_iMaxClient='50'  m_eType='UserServer' m_szIP='192.168.212.111'  m_sid='0'  m_iTotClient='0' >
		</aqservernode>
	<UserServer>
</aqservernode>
*/ //*_* by icandoit : 2009-08-28 20:31:44

//--------------------------------------------------------------------------
struct jServerInfoBase
//--------------------------------------------------------------------------
{
	enum EServerType
	{
		#define server_enum432(name,idStart,TAG) e##name,
		EServerType_BEGIN,
		for_each_SERVER_TYPE_F(server_enum432)// front end server
		eEND_EServerTypeFrontEnd,
		for_each_SERVER_TYPE_B(server_enum432)// back end server
		eEND_EServerTypeBackEnd,
		for_each_SERVER_TYPE_ADMIN(server_enum432)// admin connect
		EServerType_END
	};
	EServerType m_eType;
	nXML::jE m_E;
	/*
	aname32_t m_szName; // server nic name
	//DBCache의 m_szName은 서비스하는 DB명이다.
	// 그외의 모든 서버들의 m_szName은 컴퓨터명.
	aname32_t m_szWorld;// 상위 서버군 이름.
	aname32_t m_szServiceIP;// front-end server의 경우 유저 서비스를 위한 네트웍주소
	uint16 m_service_port;// front-end server의 경우 유저 서비스를 위한 네트웍포트
	uint16 m_service_udp_port;// roomserver의ㅣ 경우 udp port정보가 세팅됨.
	int16 m_iMaxClient; // 최대 접속가능한 클라이언수 . 센트랄 서버에 접속시 알려줘야함.
	*/
	tcstr Get_m_szName(){return m_E.Attr(jS(m_szName))->Get_cstr();}
	tcstr Get_m_szWorld(){return m_E.Attr(jS(m_szWorld))->Get_cstr();}
	tcstr Get_m_szServiceIP(){return m_E.Attr(jS(m_szServiceIP))->Get_cstr();}
	uint16 Get_m_service_port(){return m_E.Attr(jS(m_service_port))->Get_int();}
	uint16 Get_m_service_udp_port(){return m_E.Attr(jS(m_service_udp_port))->Get_int();}
	uint16 Get_m_iMaxClient(){return m_E.Attr(jS(m_iMaxClient))->Get_int();}
	EServerType Get_m_eType(){return m_eType;}
	static uint8 Get_buzy_level(nXML::jE e){ return (uint8)(e.AttrP(jS(m_iTotClient))->Get_int() / e.AttrP(jS(m_iMaxClient))->Get_int())*100;}

	//서버들이 자신의 정보를 만들어서 CentralServer에 통보할때 호출.
	void MakeInfo(nXML::jE e,tcstr szName,tcstr szWorld,tcstr sip , EServerType eType,uint16 port,int16 iMaxClient)
	{
		m_E = e;
		m_eType = eType;
		m_E.AttrP(jS(m_szName)).T() = szName;
		m_E.AttrP(jS(m_szWorld)).T() = szWorld;
		m_E.AttrP(jS(m_szServiceIP)).T() = sip;
		m_E.AttrP(jS(m_service_port)).T() = (int)port;
		//m_E.AttrP(jS(m_service_udp_port)).T() = (int)0;
		m_E.AttrP(jS(m_iMaxClient)).T() = (int)iMaxClient;
		m_E.AttrP(jS(m_eType)).T() = GetServerTypeName();
	}

	static bool IsFrontServer(EServerType eType){ return eType <eEND_EServerTypeFrontEnd; }
	static bool IsBackServer(EServerType eType){ return (eType >eEND_EServerTypeFrontEnd) && (eType <eEND_EServerTypeBackEnd) ;}
	bool IsFrontServer(){ return m_eType> EServerType_BEGIN && m_eType <eEND_EServerTypeFrontEnd; }
	bool IsBackServer(){ return (m_eType >eEND_EServerTypeFrontEnd) && (m_eType <eEND_EServerTypeBackEnd) ;}
	bool IsServer(EServerType eType){	return eType == m_eType;}
	EServerType GetServerType(){return m_eType;	}

	tcstr GetServerTypeName()
	{
#define get_server_typename432(name,idStart,TAG) if(IsServer(e##name))	return jS(name##Server);
		for_each_SERVER_TYPE(get_server_typename432);
		return jS(UnknownServerType);
	}
	static EServerType GetServerTypeByTypeName(tcstr szName)
	{
		#define GetServerTypeByName4332(name,idStart,TAG) if(!jt_strcmp(jS(name##Server) , szName))	return e##name;
		for_each_SERVER_TYPE(GetServerTypeByName4332);
		return EServerType_END;
	}

	static tcstr GetServerTypeName(EServerType eType)
	{
#define get_server_typename4321(name,idStart,TAG) if(eType==e##name)	return jS(name##Server);
		for_each_SERVER_TYPE(get_server_typename4321);
		return jS(UnknownServerType);
	}

	static EServerType GetServerTypeByTag(tcstr szTag)
	{
#define GetServerTypeByTag4321(name,idStart,TAG) if(tstring(szTag)==_T( #TAG ) ) return e##name;
		for_each_SERVER_TYPE(GetServerTypeByTag4321);
		return EServerType_END;
	}

};




inline tcstr ToString(jServerInfoBase::EServerType* v , tname256_t buf)
{
	jt_strcpy(buf, jServerInfoBase::GetServerTypeName(*v));
	return buf;
}
/*
inline tcstr ToString(jServerInfoBase*v , tname256_t buf)
{
	jt_sprintf(buf, _T("%s::%s max=%d sip=%s:%d")
		,jT(v->Get_m_szWorld()),jT(v->Get_m_szName()),v->Get_m_iMaxClient()
		,jT(v->Get_m_szServiceIP()),v->Get_m_service_port());
}
*/
//--------------------------------------------------------------------------
struct AQ_SERVER_LIB_API jServerInfo : public jServerInfoBase
//--------------------------------------------------------------------------
{
	jIVar* m_sid;
	jIVar* m_iTotClient;

	uint64 m_iPacketInfo;// 분당 평균 패킷전송량
	SYSTEMTIME m_StartTime;

	tcstr		Get_m_szIP(){		return m_E.Attr(jS(m_szIP))->Get_cstr(); }
	serverid_t	Get_m_sid(){		return m_sid->Get_int();}
	int16		Get_m_iTotClient(){ return m_iTotClient->Get_int();}
	void Set_ServerInfo(jIE* pE , serverid_t sid, tcstr szIP);

	bool IsFull()	{ return ( Get_m_iTotClient() > Get_m_iMaxClient()); }

	struct _jcheck_sid
	{
		serverid_t sid;
		_jcheck_sid(serverid_t id):sid(id){}
		bool operator()(jServerInfo*p){ return p->Get_m_sid()==sid;}
		bool operator()(jServerInfo& p){ return p.Get_m_sid()==sid;}
	};

};//struct jServerInfo

#if 1
//--------------------------------------------------------------------------
inline tcstr ToString(jServerInfo* v, tname256_t buf)
//--------------------------------------------------------------------------
{
	jt_sprintf(buf, _T("%s::%s cur=%d max=%d sid=%d ip=%s sip=%s:%d pk=%I64d")
		,jT(v->Get_m_szWorld()),jT(v->Get_m_szName()),v->Get_m_iTotClient(),v->Get_m_iMaxClient(),v->Get_m_sid()
		,jT(v->Get_m_szIP()),jT(v->Get_m_szServiceIP()),v->Get_m_service_port()
		,v->m_iPacketInfo
		);
	return buf;
}
#endif


jLIST_TYPEDEF_vector_typedef(jServerInfo,jServerInfoList);

struct _jxFindFreeTownServer
{
	bool operator()(jServerInfo& it)
	{
		if( it.Get_m_iTotClient()>= (it.Get_m_iMaxClient()-10) ) 
			return false;
		return true;
	}
};

struct _jxFindFreeTownServer2
{
	int start_index;
	int curr_index;
	_jxFindFreeTownServer2(int si) : start_index(si),curr_index(0){}
	bool operator()(jServerInfo& it)
	{
		//if(!it.IsTown())			return false;
		if(curr_index<start_index)
		{
			++curr_index;
			return false;
		}

		if( it.Get_m_iTotClient()>= (it.Get_m_iMaxClient()-10) )
			return false;

		return true;
	}
};

#include "interface/net/jConnectUser.h"

#include "jPlugIn_BE_Helper.h"


#endif // __jServerInfo_header__
