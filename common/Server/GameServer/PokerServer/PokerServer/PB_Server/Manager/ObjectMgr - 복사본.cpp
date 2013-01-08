//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "ObjectMgr.h"


struct SPUserBaseInfo
{
	LONG	m_lUSN;
	std::string	m_sUserID;
	std::string	m_sNickName;
	LONG	m_lUSC;
	LONG	m_lJumin;
	LONG	m_lFirstUSN;
	LONG	m_lAgeIndex;
	LONG	m_lJobIndex;
	LONG	m_lRegionIndex;
	LONG	m_lGuildIndex;
	LONG	m_lMemberIndex;
	LONG	m_lClientIP;
	LONG	m_lGatewayIP;
	LONG	m_lMacAddress;
	std::string	m_sMobileInfo;
	std::string	m_sAuthKey;
};


struct SPUserGameInfo
{
	std::string	m_sUserGameData;
};

struct SPUserFullInfo : public SPUserBaseInfo
{
	std::string	m_sUserGameData;
};

struct SPUserGameInfoForChannel
{

	SPUserGameInfoForChannel()
	{
		Clear();
	}
	virtual void Clear()
	{
		m_lUSN = -1L;
		m_sUserID.erase();
		m_sNickName.erase();
		m_sUserGameData.erase();
	}
	LONG	m_lUSN;
	std::string	m_sUserID;
	std::string	m_sNickName;
	std::string	m_sUserGameData;
};

struct SPUserGameInfoForRoom : public SPUserGameInfoForChannel
{

	SPUserGameInfoForRoom()
	{
		Clear();
	}
	virtual void Clear()
	{
		SPUserGameInfoForChannel::Clear();
	}
};

typedef list<SPUserGameInfoForRoom> SPUserGameInfoForRoomList;

struct ChannelPrefix
{

	ChannelPrefix()
	{
		m_lSSN = 0;
		m_dwCategory = 0;
	}
	LONG	m_lSSN;
	DWORD	m_dwCategory;
};

struct ChannelID : public ChannelPrefix
{

	ChannelID()
	{
		m_dwGCIID = 0;
	}
	void Clear(void)
	{
		m_dwGCIID = 0;
	}
	DWORD	m_dwGCIID;
};

struct RoomID : public ChannelID
{

	RoomID()
	{
		m_dwGRIID = 0UL;
	}
	void Clear(void)
	{
		m_dwGRIID = 0UL;
	}

	DWORD	m_dwGRIID;
};

struct SPRoomBaseInfo
{

	SPRoomBaseInfo()
	{
		Clear();
	}
	virtual void Clear()
	{
		m_roomID.Clear();
		m_bUsePassword = FALSE;
		m_nMaxUserCnt = 0;
		m_sGameOption.erase();
		m_nRoomState = 0;
		m_nUserCnt = 0;
		m_sTitle.erase();
	}
	RoomID	m_roomID;
	char	m_bUsePassword;
	short	m_nMaxUserCnt;
	std::string	m_sGameOption;
	short	m_nRoomState;
	short	m_nUserCnt;
	std::string	m_sTitle;
};

struct SPRoomInfoForRoom : public SPRoomBaseInfo
{

	SPRoomInfoForRoom()
	{
		Clear();
	}
	virtual void Clear()
	{
		SPRoomBaseInfo::Clear();
		m_listUserInfo.clear();
		m_lCaptainUSN = -1L;
	}
	SPUserGameInfoForRoomList	m_listUserInfo;
	LONG	m_lCaptainUSN;
};

#if 0
template<>
class BER<SPUserBaseInfo >
{
public:
	static DWORD Size(const SPUserBaseInfo& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<LONG >::Size(_obj.m_lUSN);
		dwSize+=BER<std::string >::Size(_obj.m_sUserID);
		dwSize+=BER<std::string >::Size(_obj.m_sNickName);
		dwSize+=BER<LONG >::Size(_obj.m_lUSC);
		dwSize+=BER<LONG >::Size(_obj.m_lJumin);
		dwSize+=BER<LONG >::Size(_obj.m_lFirstUSN);
		dwSize+=BER<LONG >::Size(_obj.m_lAgeIndex);
		dwSize+=BER<LONG >::Size(_obj.m_lJobIndex);
		dwSize+=BER<LONG >::Size(_obj.m_lRegionIndex);
		dwSize+=BER<LONG >::Size(_obj.m_lGuildIndex);
		dwSize+=BER<LONG >::Size(_obj.m_lMemberIndex);
		dwSize+=BER<LONG >::Size(_obj.m_lClientIP);
		dwSize+=BER<LONG >::Size(_obj.m_lGatewayIP);
		dwSize+=BER<LONG >::Size(_obj.m_lMacAddress);
		dwSize+=BER<std::string >::Size(_obj.m_sMobileInfo);
		dwSize+=BER<std::string >::Size(_obj.m_sAuthKey);
		return dwSize;
	}

	static bool Load(SPUserBaseInfo* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lUSN), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sUserID), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sNickName), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lUSC), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lJumin), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lFirstUSN), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lAgeIndex), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lJobIndex), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lRegionIndex), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lGuildIndex), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lMemberIndex), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lClientIP), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lGatewayIP), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lMacAddress), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sMobileInfo), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sAuthKey), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const SPUserBaseInfo& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lUSN ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sUserID ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sNickName ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lUSC ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lJumin ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lFirstUSN ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lAgeIndex ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lJobIndex ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lRegionIndex ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lGuildIndex ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lMemberIndex ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lClientIP ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lGatewayIP ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lMacAddress ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sMobileInfo ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sAuthKey ))
			return false;
		return true;
	}
	static bool Copy(SPUserBaseInfo* _obj, const SPUserBaseInfo& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lUSN), src.m_lUSN))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sUserID), src.m_sUserID))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sNickName), src.m_sNickName))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lUSC), src.m_lUSC))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lJumin), src.m_lJumin))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lFirstUSN), src.m_lFirstUSN))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lAgeIndex), src.m_lAgeIndex))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lJobIndex), src.m_lJobIndex))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lRegionIndex), src.m_lRegionIndex))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lGuildIndex), src.m_lGuildIndex))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lMemberIndex), src.m_lMemberIndex))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lClientIP), src.m_lClientIP))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lGatewayIP), src.m_lGatewayIP))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lMacAddress), src.m_lMacAddress))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sMobileInfo), src.m_sMobileInfo))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sAuthKey), src.m_sAuthKey))
			return false;
		return true;
	}

};

template<>
class BER<SPUserGameInfo >
{
public:
	static DWORD Size(const SPUserGameInfo& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<std::string >::Size(_obj.m_sUserGameData);
		return dwSize;
	}

	static bool Load(SPUserGameInfo* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<std::string >::Load(&(_obj->m_sUserGameData), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const SPUserGameInfo& _obj )
	{
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sUserGameData ))
			return false;
		return true;
	}
	static bool Copy(SPUserGameInfo* _obj, const SPUserGameInfo& src)
	{
		if(!BER<std::string >::Copy(&(_obj->m_sUserGameData), src.m_sUserGameData))
			return false;
		return true;
	}

};

template<>
class BER<SPUserFullInfo >
{
public:
	static DWORD Size(const SPUserFullInfo& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<SPUserBaseInfo >::Size(_obj);
		dwSize+=BER<std::string >::Size(_obj.m_sUserGameData);
		return dwSize;
	}

	static bool Load(SPUserFullInfo* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<SPUserBaseInfo >::Load(_obj, ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sUserGameData), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const SPUserFullInfo& _obj )
	{
		if(!BER<SPUserBaseInfo >::Store(ppBuf, pdwSize,_obj))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sUserGameData ))
			return false;
		return true;
	}
	static bool Copy(SPUserFullInfo* _obj, const SPUserFullInfo& src)
	{
		if(!BER<SPUserBaseInfo >::Copy(_obj, src))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sUserGameData), src.m_sUserGameData))
			return false;
		return true;
	}

};

template<>
class BER<SPUserGameInfoForChannel >
{
public:
	static DWORD Size(const SPUserGameInfoForChannel& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<LONG >::Size(_obj.m_lUSN);
		dwSize+=BER<std::string >::Size(_obj.m_sUserID);
		dwSize+=BER<std::string >::Size(_obj.m_sNickName);
		dwSize+=BER<std::string >::Size(_obj.m_sUserGameData);
		return dwSize;
	}

	static bool Load(SPUserGameInfoForChannel* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lUSN), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sUserID), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sNickName), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sUserGameData), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const SPUserGameInfoForChannel& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lUSN ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sUserID ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sNickName ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sUserGameData ))
			return false;
		return true;
	}
	static bool Copy(SPUserGameInfoForChannel* _obj, const SPUserGameInfoForChannel& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lUSN), src.m_lUSN))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sUserID), src.m_sUserID))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sNickName), src.m_sNickName))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sUserGameData), src.m_sUserGameData))
			return false;
		return true;
	}

};


template<>
class BER<SPUserGameInfoForRoom >
{
public:
	static DWORD Size(const SPUserGameInfoForRoom& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<SPUserGameInfoForChannel >::Size(_obj);
		return dwSize;
	}

	static bool Load(SPUserGameInfoForRoom* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<SPUserGameInfoForChannel >::Load(_obj, ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const SPUserGameInfoForRoom& _obj )
	{
		if(!BER<SPUserGameInfoForChannel >::Store(ppBuf, pdwSize,_obj))
			return false;
		return true;
	}
	static bool Copy(SPUserGameInfoForRoom* _obj, const SPUserGameInfoForRoom& src)
	{
		if(!BER<SPUserGameInfoForChannel >::Copy(_obj, src))
			return false;
		return true;
	}

};

template<>
class BER<ChannelPrefix >
{
public:
	static DWORD Size(const ChannelPrefix& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<LONG >::Size(_obj.m_lSSN);
		dwSize+=BER<DWORD >::Size(_obj.m_dwCategory);
		return dwSize;
	}

	static bool Load(ChannelPrefix* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<LONG >::Load(&(_obj->m_lSSN), ppBuf, pdwSize))
			return false;
		if(!BER<DWORD >::Load(&(_obj->m_dwCategory), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const ChannelPrefix& _obj )
	{
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lSSN ))
			return false;
		if(!BER<DWORD >::Store(ppBuf, pdwSize, _obj.m_dwCategory ))
			return false;
		return true;
	}
	static bool Copy(ChannelPrefix* _obj, const ChannelPrefix& src)
	{
		if(!BER<LONG >::Copy(&(_obj->m_lSSN), src.m_lSSN))
			return false;
		if(!BER<DWORD >::Copy(&(_obj->m_dwCategory), src.m_dwCategory))
			return false;
		return true;
	}

};

template<>
class BER<ChannelID >
{
public:
	static DWORD Size(const ChannelID& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<ChannelPrefix >::Size(_obj);
		dwSize+=BER<DWORD >::Size(_obj.m_dwGCIID);
		return dwSize;
	}

	static bool Load(ChannelID* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<ChannelPrefix >::Load(_obj, ppBuf, pdwSize))
			return false;
		if(!BER<DWORD >::Load(&(_obj->m_dwGCIID), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const ChannelID& _obj )
	{
		if(!BER<ChannelPrefix >::Store(ppBuf, pdwSize,_obj))
			return false;
		if(!BER<DWORD >::Store(ppBuf, pdwSize, _obj.m_dwGCIID ))
			return false;
		return true;
	}
	static bool Copy(ChannelID* _obj, const ChannelID& src)
	{
		if(!BER<ChannelPrefix >::Copy(_obj, src))
			return false;
		if(!BER<DWORD >::Copy(&(_obj->m_dwGCIID), src.m_dwGCIID))
			return false;
		return true;
	}

};

template<>
class BER<RoomID >
{
public:
	static DWORD Size(const RoomID& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<ChannelID >::Size(_obj);
		dwSize+=BER<DWORD >::Size(_obj.m_dwGRIID);
		return dwSize;
	}

	static bool Load(RoomID* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<ChannelID >::Load(_obj, ppBuf, pdwSize))
			return false;
		if(!BER<DWORD >::Load(&(_obj->m_dwGRIID), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const RoomID& _obj )
	{
		if(!BER<ChannelID >::Store(ppBuf, pdwSize,_obj))
			return false;
		if(!BER<DWORD >::Store(ppBuf, pdwSize, _obj.m_dwGRIID ))
			return false;
		return true;
	}
	static bool Copy(RoomID* _obj, const RoomID& src)
	{
		if(!BER<ChannelID >::Copy(_obj, src))
			return false;
		if(!BER<DWORD >::Copy(&(_obj->m_dwGRIID), src.m_dwGRIID))
			return false;
		return true;
	}

};

template<>
class BER<SPRoomBaseInfo >
{
public:
	static DWORD Size(const SPRoomBaseInfo& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<RoomID >::Size(_obj.m_roomID);
		dwSize+=BER<char >::Size(_obj.m_bUsePassword);
		dwSize+=BER<short >::Size(_obj.m_nMaxUserCnt);
		dwSize+=BER<std::string >::Size(_obj.m_sGameOption);
		dwSize+=BER<short >::Size(_obj.m_nRoomState);
		dwSize+=BER<short >::Size(_obj.m_nUserCnt);
		dwSize+=BER<std::string >::Size(_obj.m_sTitle);
		return dwSize;
	}

	static bool Load(SPRoomBaseInfo* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<RoomID >::Load(&(_obj->m_roomID), ppBuf, pdwSize))
			return false;
		if(!BER<char >::Load(&(_obj->m_bUsePassword), ppBuf, pdwSize))
			return false;
		if(!BER<short >::Load(&(_obj->m_nMaxUserCnt), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sGameOption), ppBuf, pdwSize))
			return false;
		if(!BER<short >::Load(&(_obj->m_nRoomState), ppBuf, pdwSize))
			return false;
		if(!BER<short >::Load(&(_obj->m_nUserCnt), ppBuf, pdwSize))
			return false;
		if(!BER<std::string >::Load(&(_obj->m_sTitle), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const SPRoomBaseInfo& _obj )
	{
		if(!BER<RoomID >::Store(ppBuf, pdwSize, _obj.m_roomID ))
			return false;
		if(!BER<char >::Store(ppBuf, pdwSize, _obj.m_bUsePassword ))
			return false;
		if(!BER<short >::Store(ppBuf, pdwSize, _obj.m_nMaxUserCnt ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sGameOption ))
			return false;
		if(!BER<short >::Store(ppBuf, pdwSize, _obj.m_nRoomState ))
			return false;
		if(!BER<short >::Store(ppBuf, pdwSize, _obj.m_nUserCnt ))
			return false;
		if(!BER<std::string >::Store(ppBuf, pdwSize, _obj.m_sTitle ))
			return false;
		return true;
	}
	static bool Copy(SPRoomBaseInfo* _obj, const SPRoomBaseInfo& src)
	{
		if(!BER<RoomID >::Copy(&(_obj->m_roomID), src.m_roomID))
			return false;
		if(!BER<char >::Copy(&(_obj->m_bUsePassword), src.m_bUsePassword))
			return false;
		if(!BER<short >::Copy(&(_obj->m_nMaxUserCnt), src.m_nMaxUserCnt))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sGameOption), src.m_sGameOption))
			return false;
		if(!BER<short >::Copy(&(_obj->m_nRoomState), src.m_nRoomState))
			return false;
		if(!BER<short >::Copy(&(_obj->m_nUserCnt), src.m_nUserCnt))
			return false;
		if(!BER<std::string >::Copy(&(_obj->m_sTitle), src.m_sTitle))
			return false;
		return true;
	}

};


template<>
class BER<SPRoomInfoForRoom >
{
public:
	static DWORD Size(const SPRoomInfoForRoom& _obj)
	{
		DWORD dwSize = 0;
		dwSize+=BER<SPRoomBaseInfo >::Size(_obj);
		dwSize+=BER<SPUserGameInfoForRoomList >::Size(_obj.m_listUserInfo);
		dwSize+=BER<LONG >::Size(_obj.m_lCaptainUSN);
		return dwSize;
	}

	static bool Load(SPRoomInfoForRoom* _obj, LPBYTE* ppBuf, LPDWORD pdwSize)
	{
		if(!BER<SPRoomBaseInfo >::Load(_obj, ppBuf, pdwSize))
			return false;
		if(!BER<SPUserGameInfoForRoomList >::Load(&(_obj->m_listUserInfo), ppBuf, pdwSize))
			return false;
		if(!BER<LONG >::Load(&(_obj->m_lCaptainUSN), ppBuf, pdwSize))
			return false;
		return true;
	}

	static bool Store(LPBYTE* ppBuf, LPDWORD pdwSize, const SPRoomInfoForRoom& _obj )
	{
		if(!BER<SPRoomBaseInfo >::Store(ppBuf, pdwSize,_obj))
			return false;
		if(!BER<SPUserGameInfoForRoomList >::Store(ppBuf, pdwSize, _obj.m_listUserInfo ))
			return false;
		if(!BER<LONG >::Store(ppBuf, pdwSize, _obj.m_lCaptainUSN ))
			return false;
		return true;
	}
	static bool Copy(SPRoomInfoForRoom* _obj, const SPRoomInfoForRoom& src)
	{
		if(!BER<SPRoomBaseInfo >::Copy(_obj, src))
			return false;
		if(!BER<SPUserGameInfoForRoomList >::Copy(&(_obj->m_listUserInfo), src.m_listUserInfo))
			return false;
		if(!BER<LONG >::Copy(&(_obj->m_lCaptainUSN), src.m_lCaptainUSN))
			return false;
		return true;
	}

};

#endif //#if 0

//CRITICAL_SECTION CObjectMgr::g_tCritical_Section;
//bool CObjectMgr::g_bCreate_CS=false;
//----------------------------------------------------------------------------------------------------
bool CObjectMgr::CreateObject(void)
{
	CObjectData::CreateObject();
	if( !SetKey() )
	{
	}
	SetMotherID((void*)this);
	//m_cObjectWaiting.SetGRCContainer(m_pGRCContainer);
	if(false==m_cObjectWaiting.CreateObject()) return false;
	m_cObjectWaiting.SetMotherID((void*)(this));
	m_vtObjectMgr.AddMap(OB_WAITING, (CObjectBase*)&m_cObjectWaiting);

	//m_cObjectItem.SetGRCContainer(m_pGRCContainer);
	if(false==m_cObjectItem.CreateObject()) return false;
	m_cObjectItem.SetMotherID((void*)(this));
	m_vtObjectMgr.AddMap(OB_WAITING, (CObjectBase*)&m_cObjectItem);

	//m_cObjectRefill.SetGRCContainer(m_pGRCContainer);
	//20111226 임시 제거
	/*
	if(false==m_cObjectRefill.CreateObject()) return false;
	m_cObjectRefill.SetMotherID((void*)(this));
	m_vtObjectMgr.AddMap(OB_REFILL, (CObjectBase*)&m_cObjectRefill);
	*/
	//if(false==g_bCreate_CS){
	//	InitializeCriticalSection(&g_tCritical_Section);
	//	g_bCreate_CS=true;
	//}
	return true;
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::DestroyObject(void)
{
	//map<KEY_OBJPOOL, CObjectBase*>::iterator pIter;
	//int Value=0;
	//for(pIter=m_vtObjectMgr.begin(); pIter!=m_vtObjectMgr.end(); pIter++){
	//	if(NULL!=pIter->second){
	//		delete pIter->second;
	//		pIter->second=NULL;
	//	}
	//}
	m_vtObjectMgr.DeleteMap();
	m_cObjectWaiting.DestroyObject();
	m_cObjectItem.DestroyObject();

	//20111226 임시 제거
	//m_cObjectRefill.DestroyObject();
}

//----------------------------------------------------------------------------------------------------
void CObjectMgr::SetUserPos(RCUser* pUser, int nIndex, long lSoundType)
{
	if(nIndex < 0) return;
	if(GetUI(nIndex).m_lUSN!=EMPTY_USER) return;
	// User Setting
	UserInfo& ui=GetUI(nIndex);
	ui.Clear();
	ui.m_lUSN=pUser->m_lUSN;
	ui.m_nIndex=nIndex;
	ui.m_sNickName.assign(pUser->m_sNickName);
	ui.m_sID.assign(pUser->m_sUserID);
	ui.m_lCLevel=pUser->m_lCLevel;
	ui.m_lSoundType=lSoundType;
	ui.m_sAvt.assign(pUser->m_sAvt);
	ui.m_cWinLose=pUser->m_cWinLose;
	ui.m_cWinLose_Today=pUser->m_cWinLose_Today;
	ui.m_llCMoney=pUser->m_llCMoney;
	ui.m_llFMoney=pUser->m_llFMoney;
	ui.m_nItemType= __CONST_::Get_ItemType( pUser->m_ItemList );
	

	switch(m_cRCRoomData.m_lState)
	{
	case GAMESTATE_READY:
	case GAMESTATE_SAVE:
		if(m_cGameInfo.m_b49Rematch)
			ui.m_lUserState=USERSTATE_WAITING;
		else
			ui.m_lUserState=USERSTATE_READY;
		break;
	case GAMESTATE_START:
	case GAMESTATE_SELECT:
	case GAMESTATE_PLAY:
	case GAMESTATE_RESULT:
		ui.m_lUserState=USERSTATE_WAITING;
		break;
	}

	pUser->m_nIndex=nIndex;

	// Money Setting
	Money & money=GetMoney(nIndex);
	money.Clear();
	money.m_llCMoney=pUser->m_llCMoney;

	if(true==IsInRange(nIndex, 0, m_cGameInfo.m_vlTimerDie.size()-1)){
		m_cGameInfo.m_vlTimerDie[nIndex]=0;
	}
	//m_pGRCContainer->NotifyUserState(pUser->m_lUSN, 1);

	//SendFMoney();
}
//----------------------------------------------------------------------------------------------------
bool CObjectMgr::SetKey()
{
	//int nResult=NC_NRC4_set_key( KEY, KEY_SIZE, &rc4key );
	//return( nResult==NC_SUCCESS );

	return 1;
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SetTimer(long lTimerIndex, long lDue, long lPeriod)
{
	long lTimer=0;
	if(TIMER_DEALOPEN==lTimerIndex){
		if(-1!=m_ctPair_Timer.FindBeginVector(TIMER_ECHO_DEALS, lTimer)){
			//m_pGRCContainer->RemoveTimer(lTimer);
			m_ctPair_Timer.FindBeginDelVector(TIMER_ECHO_DEALS);
		}
	}
	if(TIMER_BETTING==lTimerIndex){
		if(-1!=m_ctPair_Timer.FindBeginVector(TIMER_ECHO_BET, lTimer)){
			//m_pGRCContainer->RemoveTimer(lTimer);
			m_ctPair_Timer.FindBeginDelVector(TIMER_ECHO_BET);
		}
	}
	if(TIMER_CONTINUE==lTimerIndex){
		if(-1!=m_ctPair_Timer.FindBeginVector(TIMER_ECHO_FINISH, lTimer)){
			//m_pGRCContainer->RemoveTimer(lTimer);
			m_ctPair_Timer.FindBeginDelVector(TIMER_ECHO_FINISH);
		}
	}
	if(-1!=m_ctPair_Timer.FindBeginVector(lTimerIndex, lTimer)){
		//m_pGRCContainer->RemoveTimer(lTimer);
		m_ctPair_Timer.FindBeginDelVector(lTimerIndex);
	}
	/*
	if(SGS_E_FAIL!=m_pGRCContainer->SetTimer(&lTimer, lDue, NULL)){
		m_ctPair_Timer.AddVector(lTimerIndex, lTimer);
	}
	*/
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::RemoveTimer(long lTimerIndex)
{
	long lTimer=0;
	if(TIMER_DEALOPEN==lTimerIndex){
		if(-1!=m_ctPair_Timer.FindBeginVector(TIMER_ECHO_DEALS, lTimer)){
			//m_pGRCContainer->RemoveTimer(lTimer);
			m_ctPair_Timer.FindBeginDelVector(TIMER_ECHO_DEALS);
		}
	}
	if(TIMER_BETTING==lTimerIndex){

		if(-1!=m_ctPair_Timer.FindBeginVector(TIMER_ECHO_BET, lTimer)){
			//m_pGRCContainer->RemoveTimer(lTimer);
			m_ctPair_Timer.FindBeginDelVector(TIMER_ECHO_BET);
		}
	}
	if(TIMER_CONTINUE==lTimerIndex){
		if(-1!=m_ctPair_Timer.FindBeginVector(TIMER_ECHO_FINISH, lTimer)){
			//m_pGRCContainer->RemoveTimer(lTimer);
			m_ctPair_Timer.FindBeginDelVector(TIMER_ECHO_FINISH);
		}
	}
	while(-1!=m_ctPair_Timer.FindBeginVector(lTimerIndex, lTimer)){
		//m_pGRCContainer->RemoveTimer(lTimer);
		m_ctPair_Timer.FindBeginDelVector(lTimerIndex);
		if(true==m_ctPair_Timer.IsEmpty()){
			break;
		}
	}
}
//----------------------------------------------------------------------------------------------------
bool CObjectMgr::IsTimer(long lTimerIndex)
{
#ifdef _LOCAL_TEST
	return true;
#else
	if(-1!=m_ctPair_Timer.FindBeginVector(lTimerIndex)){
		return true;
	}
	return false;
#endif
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnUserMsg(long lUSN, PayloadCS &pld)
{
	switch (pld.mTagID)
	{
	case PayloadCS::msgEntry_Tag:
		OnRcvEntry(lUSN, pld.un.m_msgEntry);
		break;
	case PayloadCS::msgObserve_Tag:
		OnRcvObserve(lUSN, pld.un.m_msgObserve);
		break;
	case PayloadCS::msgPurge_Tag:
		OnRcvPurge(lUSN, pld.un.m_msgPurge);
		break;
	case PayloadCS::msgAbuse_Tag:
		OnRcvAbuse(lUSN, pld.un.m_msgAbuse);
		break;
	case PayloadCS::msgSoundType_Tag:
		OnRcvSoundType(lUSN, pld.un.m_msgSoundType);
		break;
	case PayloadCS::msgExitQue_Tag:
		OnRcvExitQue(lUSN, pld.un.m_msgExitQue);
		break;
	case PayloadCS::msgGameMasterCall_Tag:
		OnRcvGameMasterCall(lUSN, pld.un.m_msgGameMasterCall);
		break;
	case PayloadCS::msgWaitingUserTicketReq_Tag: //철이가 대기표시스템
		m_cObjectWaiting.OnRcvWaitingUserTicketReq(lUSN, pld.un.m_msgWaitingUserTicketReq);
		break;
	case PayloadCS::msgUpdateWaitingUserInfoReq_Tag: //철이가 대기표시스템
		m_cObjectWaiting.OnRcvUpdateWaitingUserInfoReq(lUSN, pld.un.m_msgUpdateWaitingUserInfoReq);
		break;

	default:
		break;
	}
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnTimer(long lTimerIndex)
{
	int nTotal=m_ctPair_Timer.TotalVector();
	long lTimer=0;
	long lTimerValue=0;
	for(int i=0; i<nTotal; i++){
		if(false==m_ctPair_Timer.GetVector(i, lTimerValue, lTimer)) continue;
		if(lTimerIndex==lTimer){
			switch(lTimerValue)
			{
			case TIMER_PURGE:	
				{
					m_cPurge.nRoomPurgeCnt--;
					SendPurgeInfo();
					RemoveTimer(TIMER_PURGE);
					return ERROR_CODE_OK;
				}
				break;
			default: break;
			}
		}
	}
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::UIErase(long lUSN)
{
	int nIndex=USNToIdx(lUSN);
	if(nIndex < 0) return;
	if(!IsUI(lUSN))	return;

	UserInfo& ui=GetUI(nIndex);
	ui.Clear();

	Cards & Card=GetCards(nIndex);
	Card.Clear();

	Money & money=GetMoney(nIndex);
	money.Clear();

	if(true==IsInRange(nIndex, 0, m_cGameInfo.m_vlTimerDie.size()-1)){
		m_cGameInfo.m_vlTimerDie[nIndex]=0;
	}
	if(true==IsInRange(nIndex, 0, m_cGameInfo.m_nBestAssa.size()-1)){
		m_cGameInfo.m_nBestAssa[nIndex]=0;
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::AddObserve(long lUSN)
{
	if(IsObserve(lUSN)) return;

	m_vtObserveUSN.push_back(lUSN);

	//	m_pGRCContainer->NotifyUserState(lUSN, 0);

	SendEntryReject(lUSN, ENTRY_NEEDTICKET); //철이가 대기표시스템:대기표창을 무조건 보여주자
	SendObserverCnt();
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::ObserveProcesses(long lUSN, bool bEraseUser, bool bContinue)
{
	int nIndex=USNToIdx(lUSN);
	if(nIndex==-1) return;

	if(lUSN==m_cGameInfo.m_lOwnerUSN)
		NextOwner();

	bool bBossOut=false;
	if(lUSN==m_cGameInfo.m_lBossUSN)
	{
		NextBoss();
		bBossOut=true;
	}

	UIErase(lUSN);
	AddObserve(lUSN);
	SendObserveAns(lUSN, nIndex);
	if(true==bEraseUser){
		m_vtEraseUSN.push_back(lUSN);
	}

	if(GetUICount() < GetMinPlayerCount() && m_cGameInfo.m_bStart==true){
		SendNoStart();
	}
	else if(bBossOut && m_cRCRoomData.m_lState==GAMESTATE_READY){
		if(0==m_cGameInfo.m_nPlayCount){
			SendStartReq();
		}
	}
	else if(m_cRCRoomData.m_lState==GAMESTATE_SAVE){
		if(true==bContinue){
			if(0==GetSelectContinueCount()){
				SendContinue();
			}
		}
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::AllUserDisconnect()
{
	ForEachElmt(vector<RCUser>, m_RCUserData, i, j){
		long lUSN=(*i).m_lUSN;
		if( lUSN < 0 ) return;

		//m_pGRCContainer->DisconnectUser(lUSN);
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::ObserveErase(long lUSN)
{
	ForEachElmt(vector<long>, m_vtObserveUSN, ia, ja){
		if((*ia)!=lUSN) continue;

		m_vtObserveUSN.erase(ia);
		break;
	}
	m_cObjectWaiting.CancelTicket(lUSN);
	m_cObjectWaiting.CallWebClient(lUSN,false); //철이가 대기표시스템:대기자에서 빠져나가므로 웹콜유저에서 빼자
	SendObserverCnt();
}
//----------------------------------------------------------------------------------------------------
bool CObjectMgr::RoomOwner(long lUSN, bool bPuge)
{
	//if(__CONST_::TWOUSER_NUM==m_cRCRoomData.m_option.m_lMaxUserCnt)
	//{
	//	RCUser * pUser=FindUser(lUSN);
	//	if(pUser!=NULL)
	//	{
	//		if(pUser->m_llCMoney < m_cRCRoomData.m_option.m_llAnteMoney)
	//		{
	//			m_cGameInfo.m_lOwnerUSN=0;
	//			ObserveProcesses(lUSN);
	//			SendSystemMsg(SYSMSG_TWOOWNER_NOMONEY, _T(""), lUSN);
	//			return false;
	//		}
	//	}
	//}
/*
	m_cGameInfo.m_lOwnerUSN=lUSN;
	if(true==bPuge){
		SendPurgeInfo();
	}
	SPRoomInfoForRoom msg;

	msg.m_lCaptainUSN=m_cGameInfo.m_lOwnerUSN;
	msg.m_nMaxUserCnt=5;
	msg.m_nRoomState=m_cRCRoomData.m_lState;
	msg.m_bUsePassword=false;
	msg.m_sTitle=m_cRCRoomData.m_option.m_sRoomTitle;
	msg.m_nUserCnt=m_cRCRoomData.GetUserCnt();
	msg.m_roomID.m_dwGRIID=m_cRCRoomData.m_lRoomIndex;//m_lRoomIndex;
	msg.m_roomID.m_dwGCIID=m_cRCRoomData.m_option.m_lChannelID;
	msg.m_roomID.m_lSSN=120;
	msg.m_roomID.m_dwCategory=m_cRCRoomData.m_option.m_lCategory;

	CParser cParser;
	cParser.SetSting(m_cRCRoomData.m_option.m_sRoomTitle);
	cParser.SetLong(m_cGameInfo.m_lChannel_idx+1);
	cParser.SetLong(m_cRCRoomData.m_option.m_lChoiceMode);
	cParser.SetLong(m_cRCRoomData.m_option.m_llAnteMoney);
	cParser.SetLong(m_cRCRoomData.m_option.m_lBetRule);
	cParser.SetLong(m_cRCRoomData.m_option.m_lMakeUSN);
	cParser.SetLong(m_cRCRoomData.m_option.m_bEcho);
	msg.m_sGameOption=cParser.MakeTableToString("|");
	SPUserGameInfoForRoom msg_in;
	int nTotal=GetTotalUser();	
	for(int i=0; i<nTotal; i++){
		msg_in.m_lUSN=m_RCUserData[i].m_lUSN;
		msg_in.m_sUserID=m_RCUserData[i].m_sUserID;
		msg_in.m_sNickName=m_RCUserData[i].m_sNickName;
		cParser.FreeParser();
		cParser.SetHyper(m_RCUserData[i].m_llCMoney);
		cParser.SetHyper(m_RCUserData[i].m_llSafeMoney);
		cParser.SetLong(m_RCUserData[i].m_lCLevel);
		cParser.SetHyper(m_RCUserData[i].m_llPlastAllinDate);
		cParser.SetHyper(m_RCUserData[i].m_llPlastLogonDay);
		cParser.SetLong(m_RCUserData[i].m_lMTodayPlayCount);
		cParser.SetLong(m_RCUserData[i].m_lMTodayPlayTime);
		cParser.SetLong(m_RCUserData[i].m_lPTotalPlayCount);
		cParser.SetLong(m_RCUserData[i].m_cRefill.m_lPLevel);
		cParser.SetHyper(m_RCUserData[i].m_llPExtMoney);
		cParser.SetHyper(m_RCUserData[i].m_llPExtendDate);
		cParser.SetHyper(m_RCUserData[i].m_llPBonusDate);
		cParser.SetLong(m_RCUserData[i].m_lMMonthPlayCount);
		cParser.SetLong(m_RCUserData[i].m_lMMonthPlayTime);
		cParser.SetLong(m_RCUserData[i].m_cWinLose.m_lWin);
		cParser.SetLong(m_RCUserData[i].m_cWinLose.m_lLose);
		cParser.SetLong(m_RCUserData[i].m_lGDisCnt);
		cParser.SetHyper(m_RCUserData[i].m_llGlastLogonDay);
		cParser.SetHyper(m_RCUserData[i].m_llGRegDate);
		cParser.SetHyper(m_RCUserData[i].m_llGFirstPlayDate);
		cParser.SetLong(m_RCUserData[i].m_lGTodayPlayCount);
		cParser.SetLong(m_RCUserData[i].m_lGTodayPlayTime);
		cParser.SetLong(m_RCUserData[i].m_lGTotalPlayCount);
		cParser.SetLong(m_RCUserData[i].m_lGTotalPlayTime);
		cParser.SetLong(m_RCUserData[i].m_lGAllinCnt);
		cParser.SetLong(m_RCUserData[i].m_lGAllinOut);
		cParser.SetHyper(m_RCUserData[i].m_llGLastAllinDate);
		cParser.SetLong(m_RCUserData[i].m_cWinLose_Today.m_lWin);
		cParser.SetLong(m_RCUserData[i].m_cWinLose_Today.m_lLose);
		cParser.SetHyper(m_RCUserData[i].m_llGTodayMoney);
		cParser.SetLong(m_RCUserData[i].m_lFourCardCnt);
		cParser.SetLong(m_RCUserData[i].m_lStraightFlushCnt);
		cParser.SetLong(m_RCUserData[i].m_lRoyalStraightFlushCnt);
		cParser.SetInt(m_RCUserData[i].m_nReserve01);
		cParser.SetInt(m_RCUserData[i].m_nReserve02);
		msg_in.m_sUserGameData=cParser.MakeTableToString("|");
		msg.m_listUserInfo.push_back(msg_in);
	}
	DWORD dwSize=BER<SPRoomInfoForRoom >::Size(msg);

	unsigned char Data[1024]={0,};
	memset(Data, 0, 1024);
	LPBYTE pData = (LPBYTE)Data;
	DWORD dwDataSize=dwSize;
	string str;
	BStore(str, msg);
	m_pGRCContainer->NotifyChangeRoomInfo((char*)str.c_str(), (long)str.size());
	BLoad(msg, str);
	//BER<SPRoomInfoForRoom >::Store(&pData, &dwSize, msg);
	//m_pGRCContainer->NotifyChangeRoomInfo((char*)pData, (long)dwDataSize);
	//BER<SPRoomInfoForRoom >::Load(&msg, &pData, &dwDataSize);

	//unsigned char* pData=(unsigned char*)malloc(dwSize+1);
	//if(NULL==pData) return true;
	//memset(pData, 0, dwSize+1);
	//BER<SPRoomInfoForRoom >::Store(&pData, &dwSize, msg);
	//m_pGRCContainer->NotifyChangeRoomInfo((char*)pData, (long)dwSize);
	//free(pData);
	//pData=NULL;
	//if(lUSN!=0)
	//{
	//	m_pGRCContainer->NotifyRoomOwner(lUSN);
	//}
	*/
	return true;
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::NextOwner()
{
	int nIndex=USNToIdx(m_cGameInfo.m_lOwnerUSN);
	int nTotal=GetUISize();
	if(nIndex < 0)
	{
		for(int i=0; i<nTotal; i++)
		{
			UserInfo & ui=GetUI(i);
			if(ui.m_lUSN!=EMPTY_USER)
			{
				RoomOwner(ui.m_lUSN);
				nIndex=ui.m_nIndex;
				break;
			}
		}
	}

	bool bTemp=false;
	for(int i=1; i<nTotal; i++)
	{
		if(nIndex  < 0) return;

		int nTempIndex=Seat[nIndex][i];
		UserInfo & ui=GetUI(nTempIndex);
		if(ui.m_lUSN!=EMPTY_USER)
		{
			bTemp=true;
			RoomOwner(ui.m_lUSN);
			break;
		}
	}

	if(bTemp==false)
		RoomOwner(0);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::NextBoss(void)
{
	int nIndex=USNToIdx(m_cGameInfo.m_lBossUSN);
	int nTotal=GetUISize();
	if(nIndex < 0)
	{
		for(int i=0; i<nTotal; i++)
		{
			UserInfo& ui=GetUI(i);
			if(ui.m_lUSN!=EMPTY_USER)
			{
				m_cGameInfo.m_lBossUSN=ui.m_lUSN;
				SendBoss();
				break;
			}
		}
	}
	for(int i=1; i < nTotal; ++i)
	{
		if(nIndex < 0) return;

		int nTempIndex=Seat[nIndex][i];
		UserInfo& ui=GetUI(nTempIndex);
		if(ui.m_lUSN!=EMPTY_USER)
		{
			m_cGameInfo.m_lBossUSN=ui.m_lUSN;
			SendBoss();
			break;
		}
	}
	nIndex=USNToIdx(m_cGameInfo.m_lBossUSN);
	if(nIndex==-1){
		m_cGameInfo.m_lBossUSN=0;
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendToAll(const PayloadSC& pld, bool bCrypt, long lUSN, long lExcept)
{
	/*
	std::string buf;
	if( ! LStore( buf, pld ) ){ return; }
	if(bCrypt){
		unsigned int dwOutSize=buf.length() + 10;
		std::string Out;
		Out.reserve(dwOutSize);
		int nEncResult=NC_NRC4_encrypt(rc4key, (const unsigned char*)buf.data(), buf.length(), (unsigned char*)Out.data(), &dwOutSize);
		if(nEncResult==NC_SUCCESS){
			m_pGRCContainer->SendUserMsg( SENDTYPE_ALL, 1 , (const char*)Out.data(), static_cast<long>(Out.length()) );
		}
		else{
			m_pGRCContainer->SendUserMsg( SENDTYPE_ALL, 1 , (const char*)buf.data(), static_cast<long>(buf.length()) );
		}
	}
	else{
		m_pGRCContainer->SendUserMsg(SENDTYPE_ALL, 1 , (const char*)buf.data(), static_cast<long>(buf.length()) );
	}
	*/
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendToUser(long lUSN, const PayloadSC& pld, bool bCrypt)
{
	/*
	std::string buf;
	if( ! LStore( buf, pld ) ){ return; }
	if( bCrypt ){
		unsigned int dwOutSize=buf.length() + 10;
		std::string Out;
		Out.reserve(dwOutSize);
		int nEncResult=NC_NRC4_encrypt(rc4key, (const unsigned char*)buf.data(), buf.length(), (unsigned char*)Out.data(), &dwOutSize);
		if(nEncResult==NC_SUCCESS){
			m_pGRCContainer->SendUserMsg( SENDTYPE_UNICAST, lUSN , (const char*)Out.data(), static_cast<long>(Out.length()) );
		}
		else{
			m_pGRCContainer->SendUserMsg( SENDTYPE_UNICAST, lUSN , (const char*)buf.data(), static_cast<long>(buf.length()) );
		}
	}
	else{
		m_pGRCContainer->SendUserMsg( SENDTYPE_UNICAST, lUSN , (const char*)buf.data(), static_cast<long>(buf.length()) );
	}
	*/
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendToObserver(const PayloadSC& pld)
{
	/*
	std::string buf;
	if( ! LStore( buf, pld ) ){ return; }
	ForEachElmt(RCUserList, GetRCUT(), i, j) 
	{
		const RCUser& user=(*i);
		if(0>user.m_lUSN){ continue; }
		//m_pGRCContainer->SendUserMsg(user.m_lUSN, 1, (LPCSTR)buf.GetData(), buf.GetLength());
		//m_pGRCContainer->SendUserMsg( user.m_lUSN, 1, (LPCSTR)buf.data(), static_cast<DWORD>(buf.length()) );
		m_pGRCContainer->SendUserMsg( SENDTYPE_UNICAST, user.m_lUSN , (const char*)buf.data(), static_cast<long>(buf.length()) );
	}
	*/
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendSystemMsg(long lType, string str, long lUSN)
{
	MsgSC_SystemMsg msg;
	msg.m_lType=lType;
	//msg.m_sMsg=str;
	PayloadSC pld(PayloadSC::msgSystemMsg_Tag, msg);
	if(lUSN==-1)
		SendToAll(pld);
	else
		SendToUser(lUSN, pld);
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::Proc_UpdateUserData(long lUSN, bool bNotify)
{
	// DB에서 업데이트된 정보를 가져옴
	//	1. 웹에서 구매후
	//	2. GRC에서 직접 SP를 통해 업데이트 되는 정보(머니등)를 GLS와 Sync하기 위해
	//		(GRC정보가 이미 업데이트 된 경우이므로, 다시 Notify하지 않도록 처리)
	//DWORD dwSize=0;
	//m_pGRCContainer->GetUpdatedUserData(lUSN, NULL, &dwSize);

	//char* pBuf=new char[dwSize + 1];
	//if( m_pGRCContainer->GetUpdatedUserData(lUSN, pBuf, &dwSize)>0 )
	//{
	//	if(bNotify) 
	//	{ 
	//		UserDataChangeNotify(lUSN, (LPCSTR)pBuf, dwSize); 
	//	}
	//}
	//if(pBuf!=NULL){ delete[] pBuf; }
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::DB_Purge_Log(long lUSN, bool bIsUI)
{
	
}
//----------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnCreateRoom(const char* szRoomOption, long lSize)
{
	if( !SetKey() )
	{
		m_cFileLog.Log("SetKey Failed");
		SwitchState( GAMESTATE_DEAD );
	}
	CParser cParser;
	if(NULL!=szRoomOption){
		cParser.MakeStringToTable(string(szRoomOption), "|");
	}

	//NDL_RoomOption room;
	//BDecode_NDL_RoomOption((LPCBUF)szRoomOption, (LPBUFLEN)&lSize, &room);
	//m_cRCRoomData.m_option.m_sRoomTitle.assign(room.m_sRoomTitle.c_str());
	//m_cRCRoomData.m_option.m_sPassword.assign(room.m_sPassword.c_str());
	//m_cRCRoomData.m_option.m_lMaxUserCnt=room.m_lMaxUserCnt;
	//long lLevel=::atol(room.m_sType.c_str());
	//if(lLevel < 0) lLevel=0;
	//m_cGameInfo.m_lChannel_idx=lLevel;
	//m_cRCRoomData.m_option.m_lChoiceMode=GetOptionString(room.m_sGameOption, "GM", 0);
	//m_cRCRoomData.m_option.m_lLimitMoney=GetOptionString(room.m_sGameOption, "LEM", 0);
	//m_cRCRoomData.m_option.m_lAnteMoney=GetOptionString(room.m_sGameOption, "AM", 0);
	//m_cRCRoomData.m_option.m_lBetRule=GetOptionString(room.m_sGameOption, "FBR", 0);
	//m_cRCRoomData.m_option.m_lAddRule=0;//GetOptionString(room.m_sGameOption, "ABM", 0);
	//m_cRCRoomData.m_option.m_lMaxUserCnt=8;//GetOptionString(room.m_sGameOption, "GG", 0);
	//m_cRCRoomData.m_option.m_lRoomType=0;
	//m_cRCRoomData.m_option.m_lBetType=0;
	int nStart=0;
	if(7<cParser.size()){
		nStart=(int)cParser.size()-7;
	}
	m_cRCRoomData.m_option.m_sRoomTitle=cParser.GetSting(nStart+0, "-");
	if(true==m_cRCRoomData.m_option.m_sRoomTitle.empty()){
		m_cRCRoomData.m_option.m_sRoomTitle="None Title";
	}
	m_cGameInfo.m_lChannel_idx=cParser.GetLong(nStart+1, 0)-1;
	if(__CONST_::CHANNEL_99==m_cGameInfo.m_lChannel_idx){
		m_cGameInfo.m_lChannel_idx=__CONST_::CHANNEL_FREE;
	}
	if(__CONST_::CHANNEL_FREE>m_cGameInfo.m_lChannel_idx){
		m_cGameInfo.m_lChannel_idx=__CONST_::CHANNEL_FREE;
	}
	if(__CONST_::CHANNEL_4<m_cGameInfo.m_lChannel_idx){
		m_cGameInfo.m_lChannel_idx=__CONST_::CHANNEL_4;
	}
	m_cRCRoomData.m_option.m_lChoiceMode=cParser.GetLong(nStart+2, 0);
	m_cRCRoomData.m_option.m_llAnteMoney=cParser.GetHyper(nStart+3, 100000);
	m_cRCRoomData.m_option.m_llGameAnteMoney=m_cRCRoomData.m_option.m_llAnteMoney;
	m_cRCRoomData.m_option.m_lBetRule=cParser.GetLong(nStart+4, 0);
	m_cRCRoomData.m_option.m_lMakeUSN=cParser.GetLong(nStart+5, 0);
	m_cRCRoomData.m_option.m_bEcho=cParser.GetBool(nStart+6, 0);

	m_cRCRoomData.m_option.m_sPassword="";
	m_cRCRoomData.m_option.m_lMaxUserCnt=5;
	m_cRCRoomData.m_option.m_lLimitMoney=0;
	m_cRCRoomData.m_option.m_lAddRule=0;
	m_cRCRoomData.m_option.m_lRoomType=0;
	m_cRCRoomData.m_option.m_lBetType=0;

	return ERROR_CODE_OK;
}

//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnAddUserInRoom(long lUSN, const char* szUserData, long lSize, long* plErrorCode)
{
	

	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnReserveRemoveUserInRoom(long lUSN)
{

	return ERROR_CODE_CANCEL;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnUserDisconnectInRoomNotify(long lUSN)
{
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnRemoveUser(long lUSN)
{
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnUserMsgToRoomNotify(long lUSN, long lSize)
{
	return 1;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnTimerToRoomNotify(long lTimerIndex)
{
	return OnTimer(lTimerIndex);
}
////----------------------------------------------------------------------------------------------------
//long CObjectMgr::OnChangeUserAvatarNotify(long lUSN, long lAvatar)
//{
//	//DWORD dwSize2=dwSize;
//	//ChangeUserAvatar ua;
//	//BDecode_ChangeUserAvatar((LPCBUF)szAvatar, &dwSize2, &ua);
//
//	//RCUser * pUser=FindUser(lUSN);
//	//if(pUser==NULL) return -1;
//
//	//pUser->SetAvatarInfo(ua.m_sAvatar);
//
//	//int nIndex=USNToIdx(lUSN);
//	//if(nIndex < 0) return -1;
//
//	//UserInfo & ui=GetUI(nIndex);
//	//if(ui.m_lUSN < 0) return -1;
//
//	//ui.m_sAvt.assign(ua.m_sAvatar);
//	//SendChangeAvatarNotify(nIndex);
//
//	return ERROR_CODE_OK;
//}
////----------------------------------------------------------------------------------------------------
//long CObjectMgr::OnChangeUserNicknameNotify(long lUSN, const char* szNickname, long lSize)
//{
//	//DWORD dwSize=(DWORD)lSize;
//	//ChangeUserNickName NickName;
//	//BDecode_ChangeUserNickName((LPCBUF)szNickname, &dwSize, &NickName);
//
//	//RCUser* pUser=FindUser(lUSN);
//	//if(pUser==NULL) return ERROR_CODE_CANCEL;
//	//pUser->SetUserNickName(NickName.m_sNickName);
//	//int nIndex=USNToIdx(lUSN);
//	//if(nIndex < 0) return ERROR_CODE_CANCEL;
//	//UserInfo & ui=GetUI(nIndex);
//	//if(ui.m_lUSN < 0) return ERROR_CODE_CANCEL;
//	//ui.m_sNickName.assign(NickName.m_sNickName);
//
//	return ERROR_CODE_OK;
//}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize)
{
	return m_cObjectItem.OnChangeUserItemNotify(lUSN, szItem, lSize);
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnRecvMessageFromServer(long lMsgType, long lParam, const char* szContents, long lSize)
{
	//switch(lMsgType)
	//{
	//case MSGTYPE_BCS_RECV_STARTCASTING:
	//	return 0;
	//case MSGTYPE_BCS_RECV_STOPCASTING:
	//	break;
	//case MSGTYPE_GRC_JACKPOT_CANDIDATE:

	//	break;

	//case MSGTYPE_GRC_JACKPOT_TOTALMONEY:
	//	{
	//	}
	//	break;
	//	// 폴리스 방제 신고 변경안 작업
	//case MSGTYPE_LCS_TERMINATE_ROOM:
	//	{				
	//		if( TERMINATE_ROOM_GRACEFUL==lParam ){
	//			long lState=m_cRCRoomData.m_lState;
	//			// 게임중이면
	//			if( lState >= GAMESTATE_START && lState <= GAMESTATE_SAVE ){
	//				SendPoliceNotify();
	//				m_cPoliceNotify.SetPoliceNotify(true);		// 신고된 방으로 설정
	//			}
	//			else{
	//				AllUserDisconnect();
	//			}
	//		}
	//		else if( TERMINATE_ROOM_IMMEDIATE==lParam ){				// 즉시 팅겨낸다
	//			AllUserDisconnect();
	//		}
	//	}
	//	break;
	//case MSGTYPE_LCS_KICKOUT_USER:
	//	{
	//		if(KICKOUT_USER_CHEAT==lParam){
	//			if( memcmp(szContents, "0", 1) ){
	//				char	svalue[40];
	//				ZeroMemory( svalue, 40 );
	//				memcpy( svalue, szContents, lSize );
	//				SendSystemMsg(SYSMSG_LCS_KICKOUT_USER, svalue);
	//			}
	//			break;
	//		}
	//	}
	//	break;

	//default:
	//	break;
	//}
	return ERROR_CODE_OK;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::CanUseIBB(long lUSN)
{
	if(IsUI(lUSN))
		return false;

	return true;
}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::OnAExcuteQueryToDBResult(long lResult, long lIndex, const char* szResult, long lSize, long lErrorCode)
{
	return 1;
}

long CObjectMgr::CheckUserStateFromWeb(long lUSN)
{
	if( IsUI(lUSN) )
	{
		int nIndex=USNToIdx(lUSN);
		if( nIndex==-1 )return -1;
		UserInfo &ui=GetUI(nIndex);
		if(ui.m_lUSN==-1 )return -1;
		if(ui.m_lUserState==USERSTATE_PLAYING || ui.m_lUserState==USERSTATE_49WAITING || ui.m_lUserState==USERSTATE_SELECTBEGIN || ui.m_lUserState==USERSTATE_SELECTEND) //플레이중인유저
			return -1; //플레이중이면 웹구매 해서는 안된다.
	}
	else
	{
		if( m_cObjectWaiting.IsTicketUser(lUSN) ) //대기표 시스템:대기표를 받은 사람은 웹구매를 할수없다.
			return -1;
	}
	return lUSN;

}
//----------------------------------------------------------------------------------------------------
long CObjectMgr::GetRoomInfo(const char* szRoomInfo, long lSize)
{
	return 1;
}