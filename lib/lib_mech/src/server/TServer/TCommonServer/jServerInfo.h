/* file : jServerInfo.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-04 20:42:06
comp.: wiki.aqrius.com
title : 
desc : 


<예약된 server id > 
	Central server id = 0;
	
	//Command server id = 1;
	//User    server id = 2;


*/

#ifndef __jServerInfo_header__
#define __jServerInfo_header__
#pragma once

//--------------------------------------------------------------------------
// server 객체 클래스 지원 코드
//--------------------------------------------------------------------------

//#define func(name,serverid_begin,TAG)
#define for_each_SERVER_TYPE_FRONT(func)\
	func(Login,10,L)\
	func(Channel,1000,T)\
	func(Game,2000,D)\

//#define func(name,serverid_begin,TAG)
#define for_each_SERVER_TYPE_WORLD(func)\
	func(World,3200,W)\
	func(DBCache,4000,DC)\
	func(Trade,5000,T)\
	func(Mail,6000,M)\
	func(Auction,7000,A)\

//#define func(name,serverid_begin,TAG)
#define for_each_SERVER_TYPE_BACK(func)\
	func(Central,1,C)\
	func(Command,8000,CD)\
	func(User,8100,U)\
	func(Msg,8200,MG)\
	func(Dummy,8300,DT)\

// serverid_t는 MAX_SERVER_ID 보다 작아야 한다.
const serverid_t MAX_SERVER_ID = 1<<14;


//#define func(name,serverid_begin,TAG)
#define for_each_SERVER_TYPE(func)\
	for_each_SERVER_TYPE_FRONT(func)\
	for_each_SERVER_TYPE_WORLD(func)\
	for_each_SERVER_TYPE_BACK(func)\

enum EServerType
{
#define server_enum432(name,idStart,TAG) e##name,
	for_each_SERVER_TYPE_FRONT(server_enum432)// front end server
	eEND_EServerTypeFrontEnd,
	for_each_SERVER_TYPE_WORLD(server_enum432)// back end server
	eEND_EServerTypeWORLD,
	for_each_SERVER_TYPE_BACK(server_enum432)// back end server
	eEND_EServerTypeBackEnd,
	EServerType_END
};

#define server_id_START_432(name,idStart,TAG) const int iSTART_SERVERID_##name = idStart;
for_each_SERVER_TYPE(server_id_START_432);

inline tcstr ToString(EServerType eType)
{
#define get_server_typename4321(name,idStart,TAG) if(eType==e##name)	return jS(name##Server);
	for_each_SERVER_TYPE(get_server_typename4321);
	return jS(UnknownServerType);
}
inline tcstr ToString2(EServerType eType)
{
#define ToString2_typename4321(name,idStart,TAG) if(eType==e##name)	return jS(name);
	for_each_SERVER_TYPE(ToString2_typename4321);
	return jS(UnknownServer);
}

inline EServerType ToServerType(tcstr szName)
{
#define GetServerTypeByName4332(name,idStart,TAG) if(!jt_strcmp(jS(name##Server) , szName))	return e##name;
	for_each_SERVER_TYPE(GetServerTypeByName4332);
	return EServerType_END;
}
inline EServerType ToServerType_ByTag(tcstr szTag)
{
#define GetServerTypeByTag4321(name,idStart,TAG) if(tstring(szTag)==_T( #TAG ) ) return e##name;
	for_each_SERVER_TYPE(GetServerTypeByTag4321);
	return EServerType_END;
}
inline bool IsFrontServer(EServerType eType){ return eType <eEND_EServerTypeFrontEnd; }
inline bool IsBackServer(EServerType eType)	{ return (eType >eEND_EServerTypeFrontEnd) && (eType <eEND_EServerTypeBackEnd) ;}
inline tcstr ToString(EServerType* v, tname256_t buf){jt_strcpy_s(buf,256, ToString(*v));return buf;}


//--------------------------------------------------------------------------
struct T_SERVER_LIB_API jServerInfo
//--------------------------------------------------------------------------
{
	uint64 m_PacketAmount;
	EServerType m_eType;
	tname32_t m_szName; // server nic name
	SYSTEMTIME m_StartTime;//GetLocalTime() central 기준시간.

	//DBCache의 m_szName은 서비스하는 DB명이다.
	// 그외의 모든 서버들의 m_szName은 컴퓨터명.
	tname32_t m_szDomain;// 상위 서버군 이름.
	tname32_t m_szIP; // 접속한 ip
	tname32_t m_szServiceIP;// front-end server의 경우 유저 서비스를 위한 네트웍주소
	serverid_t m_sid;
	uint16 m_service_port;// front-end server의 경우 유저 서비스를 위한 네트웍포트
	uint16 m_service_udp_port;// GameServer의ㅣ 경우 udp port정보가 세팅됨.
	int16 m_iMaxClient; // 최대 접속가능한 클라이언수 . 센트랄 서버에 접속시 알려줘야함.
	int16 m_iTotClient; // 현제 접속자.

	uint8		Get_buzy_level(){ return (m_iTotClient / m_iMaxClient)*100;}
	bool		IsFull()		{ return m_iTotClient >=m_iMaxClient;}
	serverid_t	GetID()			{ return m_sid;}

	bool		IsFrontServer()					{ return ::IsFrontServer(m_eType); }
	bool		IsBackServer()					{ return ::IsBackServer(m_eType);}
	bool		IsServer(EServerType eType)		{ return eType == m_eType;}

	jServerInfo()
	{
		memset(this, 0, sizeof(*this));
	}
	//서버들이 자신의 정보를 만들어서 CentralServer에 통보할때 호출.SS2C_ONLINE
	void jServerInfo::MakeInfo(tcstr szName,tcstr serviceIP ,uint16 servicePort,int16 iMaxClient)
	{
		// m_eType , m_szDomain은 PlugIn_Connect::Start()시 세팅됨.
		jt_strcpy_s(m_szName, (szName));
		jt_strcpy_s(m_szServiceIP ,(serviceIP));
		m_service_port = servicePort;
		m_iMaxClient = iMaxClient;
	}
	static serverid_t get_max_sid(EServerType eType);
	static serverid_t get_min_sid(EServerType eType);
	//! sid가 해당 서버타입인지
	static bool is_same_type(EServerType eType, serverid_t sid){return (get_min_sid(eType)<=sid && sid <= get_max_sid(eType));}

};//struct jServerInfo



inline  tcstr ToString(jServerInfo* v, tname1024_t buf)
{
	jt_sprintf_s(buf,1024 ,_T("%s.%s cur=%d max=%d sid=%d ip=%s sip=%s:%d pk=%I64d")
		,(v->m_szDomain),(v->m_szName),v->m_iTotClient,v->m_iMaxClient,v->m_sid
		,(v->m_szIP),(v->m_szServiceIP),v->m_service_port
		,v->m_PacketAmount
		);
	return buf;
}



jLIST_TYPEDEF_vector_typedef(jServerInfo,jServerInfoList);


#endif // __jServerInfo_header__
