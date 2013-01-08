//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "ObjectMgr.h"
#include "../sgrc/SGSErrorCode.h"
//#include "../data/GameUser.h"
#include "PK_Room.h"
#include "PK_header.h"

using namespace adl;



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
		/*
	case PayloadCS::msgEntry_Tag:
		//OnRcvEntry(lUSN, pld.un.m_msgEntry);
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
	*/
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

	/*
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

	RCRoomData pRoomData =  GetData();
	nMOB::ug_room_id_t rid = pRoomData.m_lRoomIndex;
	PK_ROOM_RID(pRoom, rid);

	jRETURN(pRoom);

	#define jLAMDA_send_msg_ansgameprotocol(X,Z) Z(CObjectMgr* , pCObjectMgr)
	jLAMDA_for_each(send_msg_ansgameprotocol,PK_Plugin_Connection*)
	{
		pCObjectMgr;
		pp_game_id_t gid = it->m_gid;

		GAnsProtocol sendMsg;

		sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
		GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
		packet->set_type(::GLAnsGameProtocol_Type_ans_deal_cards);

		it->send_me(sendMsg);					
	}
	jLAMDA_end();

	boost::function<void (PK_Plugin_Connection*)> func = send_msg_ansgameprotocol(this);
	pRoom->for_each(func);
}

void CObjectMgr::SendToAll(GLAnsGameProtocol_Type type, void* msg)
{

	RCRoomData pRoomData =  GetData();
	nMOB::ug_room_id_t rid = pRoomData.m_lRoomIndex;
	PK_ROOM_RID(pRoom, rid);

	jRETURN(pRoom);

	switch(type)
	{
	case GLAnsGameProtocol_Type_ans_deal_card: 
		{
			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,ans_deal_card);

			s_ans_deal_card& p = *(s_ans_deal_card*)msg;

			pSendData->CopyFrom(p);

			pRoom->send_to_all(sendMsg, nMOB::eSAT_SendAll,0);
			/*
			#define jLAMDA_send_msg(X,Z) X(void* ,msg) Z(CObjectMgr* , pCObjectMgr)
			jLAMDA_for_each(send_msg,PK_Plugin_Connection*)
			{
				pCObjectMgr;
				pp_game_id_t gid = it->m_gid;

				GAnsProtocol sendMsg;

				MsgSC_DealCard* pMsgSC_DealCards = (MsgSC_DealCard*)msg;

				sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
				GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
				packet->set_type(GLAnsGameProtocol_Type_ans_deal_card);

				s_ans_deal_card* ps_ans_deal_card =  packet->mutable_m_ans_deal_card();

				ps_ans_deal_card->set_m_lbossusn(pMsgSC_DealCards->m_lBossUSN);
				ps_ans_deal_card->set_m_lcardsdealt(pMsgSC_DealCards->m_lCardsDealt);
				ps_ans_deal_card->set_m_ntype(pMsgSC_DealCards->m_nType);

				for(vector<OneCard>::iterator it = pMsgSC_DealCards->m_vtOneCard.begin() ; it != pMsgSC_DealCards->m_vtOneCard.end() ; ++it)
				{
					PKOneCard* pOneCard = pOneCard = ps_ans_deal_card->add_m_vtonecard();

					pOneCard->set_m_lcardindex(it->m_lCardIndex);
					pOneCard->set_m_nindex(it->m_nIndex);
				}

				it->send_me(sendMsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_msg(msg, this);
			pRoom->for_each(func);
			*/
		}
		break;

	case GLAnsGameProtocol_Type_ans_send_ante:
		{

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,ans_send_ante);

			s_ans_send_ante& p = *(s_ans_send_ante*)msg;

			pSendData->CopyFrom(p);

			pRoom->send_to_all(sendMsg, nMOB::eSAT_SendAll,0);

			/*
			#define jLAMDA_send_msg_ans_send_ante(X,Z) X(void* ,msg) Z(CObjectMgr* , pCObjectMgr)
			jLAMDA_for_each(send_msg_ans_send_ante,PK_Plugin_Connection*)
			{
				GAnsProtocol sendMsg;

				MsgSC_AnteMoney* pMsgSC_AnteMoney = (MsgSC_AnteMoney*)msg;

				sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
				GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
				packet->set_type(GLAnsGameProtocol_Type_ans_send_ante);

				s_ans_send_ante* pAnte = packet->mutable_m_ans_send_ante();
				pAnte->set_m_llantemoney(pMsgSC_AnteMoney->m_llAnteMoney);

				it->send_me(sendMsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_msg_ans_send_ante(msg,this);
			pRoom->for_each(func);
			*/
		}
		break;

	case GLAnsGameProtocol_Type_ans_boss:
		{
			GAnsProtocol sendMsg;
			MsgSC_Boss *pMsgSC_Boss = (MsgSC_Boss*)msg;

			sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
			GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
			packet->set_type(GLAnsGameProtocol_Type_ans_boss);

			s_ans_boss* pBoss = packet->mutable_m_ans_boss();

			pBoss->set_m_lbossusn(pMsgSC_Boss->m_lBossUSN);
			pBoss->set_m_nbossrank(pMsgSC_Boss->m_nBossRank);


			#define jLAMDA_send_ans_boss(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_ans_boss,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_ans_boss(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_ans_betting:
		{
			GAnsProtocol sendMsg;
			MsgSC_Betting *pMsgSC_Betting = (MsgSC_Betting*)msg;

			sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);

			GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
			packet->set_type(GLAnsGameProtocol_Type_ans_betting);

			s_ans_betting* pBetting = packet->mutable_m_ans_betting();

			pBetting->set_m_lusn(pMsgSC_Betting->m_lBetUSN);
			pBetting->set_m_bettype(pMsgSC_Betting->m_lBetBtnType);

			#define jLAMDA_send_ans_betting(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_ans_betting,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_ans_betting(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_betting_msg:
		{
			GAnsProtocol sendMsg;
			MsgSC_BettingAnsMsg *pMsgSC_BettingAnsMsg = (MsgSC_BettingAnsMsg*)msg;

			sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);

			GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
			packet->set_type(GLAnsGameProtocol_Type_betting_msg);

			s_betting_msg* pBetting = packet->mutable_m_betting_msg();

			pBetting->set_m_bbettingmoney(pMsgSC_BettingAnsMsg->m_bBettingMoney);
			pBetting->set_m_bcallmoneyzero(pMsgSC_BettingAnsMsg->m_bCallMoneyZero);
			pBetting->set_m_bettype(pMsgSC_BettingAnsMsg->m_BetType);
			pBetting->set_m_bmoneylack(pMsgSC_BettingAnsMsg->m_bMoneyLack);
			pBetting->set_m_llcallmoney(pMsgSC_BettingAnsMsg->m_llCallMoney);
			pBetting->set_m_llraisemoney(pMsgSC_BettingAnsMsg->m_llRaiseMoney);
			pBetting->set_m_lusn(pMsgSC_BettingAnsMsg->m_lUSN);
			pBetting->set_m_nindex(pMsgSC_BettingAnsMsg->m_nIndex);
			pBetting->set_m_llpoolmoney(pMsgSC_BettingAnsMsg->m_llPoolMoney);
			pBetting->set_m_llsidemoney(pMsgSC_BettingAnsMsg->m_llSideMoney);
			pBetting->set_m_lbetturn(pMsgSC_BettingAnsMsg->m_lBetTurn);

			PKMoney* pMoney = pBetting->mutable_m_money();
			pMoney->set_m_lbetcount(pMsgSC_BettingAnsMsg->m_money.m_lBetCount);
			pMoney->set_m_lbetreceive(pMsgSC_BettingAnsMsg->m_money.m_lBetReceive);
			pMoney->set_m_lbetstate(pMsgSC_BettingAnsMsg->m_money.m_lBetState);
			pMoney->set_m_llcallhabmoney(pMsgSC_BettingAnsMsg->m_money.m_llCallHabMoney);
			pMoney->set_m_llcallmoney(pMsgSC_BettingAnsMsg->m_money.m_llCallMoney);
			pMoney->set_m_llcmoney(pMsgSC_BettingAnsMsg->m_money.m_llCMoney);
			pMoney->set_m_lljackpotmoney(pMsgSC_BettingAnsMsg->m_money.m_llJackpotMoney);
			pMoney->set_m_llsidemoney(pMsgSC_BettingAnsMsg->m_money.m_llSideMoney);
			pMoney->set_m_lltakemoney(pMsgSC_BettingAnsMsg->m_money.m_llTakeMoney);
			pMoney->set_m_lresultidx(pMsgSC_BettingAnsMsg->m_money.m_lResultIdx);
			pMoney->set_m_smoneymsg(pMsgSC_BettingAnsMsg->m_money.m_sMoneyMsg);

			for(VecMoney::iterator it = pMsgSC_BettingAnsMsg->m_vtCallMoney.begin() ; it < pMsgSC_BettingAnsMsg->m_vtCallMoney.end() ; ++it)
			{
				pBetting->add_m_vtcallmoney(*it);
			}
			
			#define jLAMDA_send_ans_betting(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_ans_betting,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_ans_betting(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_ans_entry:
		{
			#define jLAMDA_send_ans_entry(X, Z) X(void*, msg) Z(CObjectMgr* , pCObjectMgr)
			jLAMDA_for_each(send_ans_entry,PK_Plugin_Connection*)
			{
				GAnsProtocol sendMsg;
				MsgSC_EntryAns *pMsgSC_EntryAns = (MsgSC_EntryAns*)msg;

				sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);

				GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
				packet->set_type(GLAnsGameProtocol_Type_ans_entry);

				s_ans_entry* pEntry = packet->mutable_m_ans_entry();

				pEntry->set_m_lusn(it->m_gid);
				pEntry->set_m_lownerusn(pMsgSC_EntryAns->m_lOwnerUSN);
				pEntry->set_m_bwelcomesound(pMsgSC_EntryAns->m_bWelcomeSound);
				pEntry->set_m_lobservecnt(pMsgSC_EntryAns->m_lObserveCnt);
				pEntry->set_m_nindex(pMsgSC_EntryAns->m_nIndex);

				int i = 0;
				for(vector<Money>::iterator it_begin = pMsgSC_EntryAns->m_tblMoney.begin() ; it_begin != pMsgSC_EntryAns->m_tblMoney.end() ; ++it_begin)
				{
					PKMoney* pMoney = pEntry->add_m_tblmoney();

					pMoney->set_m_lbetcount(it_begin->m_lBetCount);
					pMoney->set_m_lbetreceive(it_begin->m_lBetReceive);
					pMoney->set_m_lbetstate(it_begin->m_lBetState);
					pMoney->set_m_llcallhabmoney(it_begin->m_llCallHabMoney);
					pMoney->set_m_llcallmoney(it_begin->m_llCallMoney);
					pMoney->set_m_llcmoney(it_begin->m_llCMoney);
					pMoney->set_m_lljackpotmoney(it_begin->m_llJackpotMoney);
					pMoney->set_m_llsidemoney(it_begin->m_llSideMoney);
					pMoney->set_m_lltakemoney(it_begin->m_llTakeMoney);
					pMoney->set_m_lresultidx(it_begin->m_lResultIdx);
					pMoney->set_m_smoneymsg(_T(it_begin->m_sMoneyMsg));
				}

				i = 0;
				for(vector<UserInfo>::iterator it_begin = pMsgSC_EntryAns->m_tblUI.begin() ; it_begin != pMsgSC_EntryAns->m_tblUI.end() ; ++it_begin)
				{
					PKUserInfo* pUserInfo = pEntry->add_m_tblui();

					pUserInfo->set_m_llcmoney(it_begin->m_llCMoney);
					pUserInfo->set_m_lack(it_begin->m_lAck);
					pUserInfo->set_m_lclevel(it_begin->m_lCLevel);
					pUserInfo->set_m_ldiecardsdealt(it_begin->m_lDieCardsDealt);
					pUserInfo->set_m_lexit(it_begin->m_lExit);
					pUserInfo->set_m_ljackpot(it_begin->m_lJackpot);
					pUserInfo->set_m_llcmoney(it_begin->m_llCMoney);
					pUserInfo->set_m_llfmoney(it_begin->m_llFMoney);
					pUserInfo->set_m_lsoundtype(it_begin->m_lSoundType);
					pUserInfo->set_m_luserstate(it_begin->m_lUserState);
					pUserInfo->set_m_lusn(it_begin->m_lUSN);
					pUserInfo->set_m_nindex(it_begin->m_nIndex);
					pUserInfo->set_m_nitemtype(it_begin->m_nItemType);
					pUserInfo->set_m_savt(it_begin->m_sAvt == "" ? _T("test") : it_begin->m_sAvt);
					pUserInfo->set_m_sid(it_begin->m_sID);
					pUserInfo->set_m_snickname(it_begin->m_sNickName == "" ? _T("test") :it_begin->m_sNickName) ;

					pUserInfo->mutable_m_cwinlose()->set_m_lwin(it_begin->m_cWinLose.m_lWin);
					pUserInfo->mutable_m_cwinlose()->set_m_llose(it_begin->m_cWinLose.m_lLose);
					pUserInfo->mutable_m_cwinlose()->set_m_lcontinue(it_begin->m_cWinLose.m_lContinue);
					pUserInfo->mutable_m_cwinlose_room()->set_m_lwin(it_begin->m_cWinLose_Room.m_lWin);
					pUserInfo->mutable_m_cwinlose_room()->set_m_llose(it_begin->m_cWinLose_Room.m_lLose);
					pUserInfo->mutable_m_cwinlose_room()->set_m_lcontinue(it_begin->m_cWinLose_Room.m_lContinue);
					pUserInfo->mutable_m_cwinlose_today()->set_m_lwin(it_begin->m_cWinLose_Today.m_lWin);
					pUserInfo->mutable_m_cwinlose_today()->set_m_llose(it_begin->m_cWinLose_Today.m_lLose);
					pUserInfo->mutable_m_cwinlose_today()->set_m_lcontinue(it_begin->m_cWinLose_Today.m_lContinue);
						
				}

				it->send_me(sendMsg);
			}


			/*
			#define jLAMDA_send_ans_entry(X, Z) X(s_ans_entry*, entry) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_ans_entry,PK_Plugin_Connection*)
			{
				entry->set_m_lusn(it->m_gid);
				it->send_me(sendmsg);
			}
			*/

			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_ans_entry(msg, this);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_ans_continue:
		{
			MsgSC_ContinueAns* pMsgSC_ContinueAns = (MsgSC_ContinueAns*)msg;

			jLOG(jFUNC1 _T("gameid : %d"), pMsgSC_ContinueAns->m_lUSN);

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,ans_continue);

			pSendData->set_m_lusn(pMsgSC_ContinueAns->m_lUSN);

			#define jLAMDA_send_ans_continue(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_ans_continue,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_ans_continue(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_ans_start:
		{
			MsgSC_StartAns* pMsgSC_StartAns = (MsgSC_StartAns*)msg;
			
			jLOG(jFUNC1 _T("systemtime : %d\n state : %d\n "),
				pMsgSC_StartAns->m_llSystemTime , 
				pMsgSC_StartAns->m_lState);

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,ans_start);

			pSendData->set_m_llsystemtime(pMsgSC_StartAns->m_llSystemTime);
			pSendData->set_m_lstate(pMsgSC_StartAns->m_lState);

			for(vector<LONG>::iterator it = pMsgSC_StartAns->m_vtState.begin() ; it < pMsgSC_StartAns->m_vtState.end() ; ++it)
			{
				pSendData->add_m_vtstate(*it);
			}

			#define jLAMDA_send_ans_start(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_ans_start,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_ans_start(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_nostart:
		{
			MsgSC_NoStart* pMsgSC_NoStart = (MsgSC_NoStart*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,nostart);

			#define jLAMDA_send_nostart(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_nostart,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_nostart(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_finished:
		{
			MsgSC_Finished* pMsgSC_Finished = (MsgSC_Finished*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,finished);

			pSendData->set_m_bgiveup(pMsgSC_Finished->m_bGiveUp);
			pSendData->set_m_lbossusn(pMsgSC_Finished->m_lBossUSN);
			pSendData->set_m_lljackpot(pMsgSC_Finished->m_llJackpot);
			pSendData->set_m_llgivemoney(pMsgSC_Finished->m_llGiveMoney);
			pSendData->set_m_llpoolmoney(pMsgSC_Finished->m_llPoolMoney);
			pSendData->set_m_lrank(pMsgSC_Finished->m_lRank);
			pSendData->set_m_lresultidx(pMsgSC_Finished->m_lResultIdx);
			pSendData->set_m_lstate(pMsgSC_Finished->m_lState);

			for(vector<Cards>::iterator it = pMsgSC_Finished->m_tblCard.begin() ; it < pMsgSC_Finished->m_tblCard.end() ; ++it)
			{
				PKCards* pCard = pSendData->add_m_tblcard();

				pCard->set_m_lresultidx(it->m_lResultIdx);

				for(int i = 0 ; i < it->m_vtCards.size() ; ++i)
				{
					pCard->add_m_vtcards(it->m_vtCards[i]);
				}

				for(int i=0; i <it->m_vUserUSN.size(); i++)
				{
					pCard->add_m_vuserusn()->set_usn(it->m_vUserUSN[i]);
				}
			}

			for(vector<Money>::iterator it = pMsgSC_Finished->m_tblMoney.begin() ; it < pMsgSC_Finished->m_tblMoney.end() ; ++it)
			{
				PKMoney* pMoney = pSendData->add_m_tblmoney();

				pMoney->set_m_lbetcount(it->m_lBetCount);
				pMoney->set_m_lbetreceive(it->m_lBetReceive);
				pMoney->set_m_lbetstate(it->m_lBetState);
				pMoney->set_m_llcallhabmoney(it->m_llCallHabMoney);
				pMoney->set_m_llcallmoney(it->m_llCallMoney);
				pMoney->set_m_llcmoney(it->m_llCMoney);
				pMoney->set_m_lljackpotmoney(it->m_llJackpotMoney);
				pMoney->set_m_llsidemoney(it->m_llSideMoney);
				pMoney->set_m_lltakemoney(it->m_llTakeMoney);
				pMoney->set_m_lresultidx(it->m_lResultIdx);
				pMoney->set_m_smoneymsg(it->m_sMoneyMsg);
			}

			for(vector<UserMoney>::iterator it = pMsgSC_Finished->m_vtUserMoney.begin() ; it < pMsgSC_Finished->m_vtUserMoney.end() ; ++it)
			{
				UserMoney* pUserMoney = pSendData->add_m_vtusermoney();

				pUserMoney->set_m_llcallhabmoney(it->m_llcallhabmoney());
				pUserMoney->set_m_lldealmoney(it->m_lldealmoney());
				pUserMoney->set_m_llmoney(it->m_llmoney());
				pUserMoney->set_m_lltakemoney(it->m_lltakemoney());
				pUserMoney->set_m_lstate(it->m_lstate());
				pUserMoney->set_m_lusn(it->m_lusn());
				pUserMoney->set_m_sdealertax(it->m_sdealertax());
				pUserMoney->set_m_snickname(it->m_snickname());
			}

			for(vector<int>::iterator it = pMsgSC_Finished->m_vtWin.begin() ; it < pMsgSC_Finished->m_vtWin.end() ; ++it)
			{
				pSendData->add_m_vtwin(*it);	
			}

			for(vector<LONGLONG>::iterator it = pMsgSC_Finished->m_vtGiveMoney.begin() ; it < pMsgSC_Finished->m_vtGiveMoney.end() ; ++it)
			{
				pSendData->add_m_vtgivemoney(*it);	
			}

			for(vector<int>::iterator it = pMsgSC_Finished->m_vtResult.begin() ; it < pMsgSC_Finished->m_vtResult.end() ; ++it)
			{
				pSendData->add_m_vtresult(*it);
			}

			#define jLAMDA_send_finished(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_finished,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_finished(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_newgame:
		{
			MsgSC_NewGame* pMsgSC_NewGame = (MsgSC_NewGame*)msg;
			
			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,newgame);

			for(VectorWinLoseInfo::iterator it =  pMsgSC_NewGame->m_vtWinLoseInfo.begin() ; it < pMsgSC_NewGame->m_vtWinLoseInfo.end() ; ++it)
			{
				PKWinLoseInfo* pWinLoseInfo = pSendData->add_m_vtwinloseinfo();				

				pWinLoseInfo->set_m_llcmoney(it->m_llCMoney);
				pWinLoseInfo->set_m_lwin(it->m_lWin);
				pWinLoseInfo->set_m_lreserved(it->m_lReserved);
				pWinLoseInfo->set_m_llose(it->m_lLose);
			}
			
			#define jLAMDA_send_newgame(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_newgame,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_newgame(sendMsg);
			pRoom->for_each(func);

		}
		break;

	case GLAnsGameProtocol_Type_systemmsg:
		{
			MsgSC_SystemMsg* pMsgSC_SystemMsg = (MsgSC_SystemMsg*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,systemmsg);

			pSendData->set_m_ltype(pMsgSC_SystemMsg->m_lType);

			#define jLAMDA_send_systemmsg(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_systemmsg,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_systemmsg(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_exitntf:
		{
			MsgSC_ExitNtf* pMsgSC_ExitNtf = (MsgSC_ExitNtf*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,exitntf);

			pSendData->set_m_bexit(pMsgSC_ExitNtf->m_bExit);
			pSendData->set_m_lexit(pMsgSC_ExitNtf->m_lExit);
			pSendData->set_m_lusn(pMsgSC_ExitNtf->m_lUSN);
			pSendData->set_m_nindex(pMsgSC_ExitNtf->m_nIndex);

			#define jLAMDA_send_exitntf(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_exitntf,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_exitntf(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_soundtypeans:
		{
			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,soundtypeans);

			s_soundtypeans& p = *(s_soundtypeans*)msg;

			pSendData->CopyFrom(p);

			pRoom->send_to_all(sendMsg, nMOB::eSAT_SendAll,0);
		}
		break;

	case GLAnsGameProtocol_Type_purgeinfo:
		{
			MsgSC_PurgeInfo* pMsgSC_PurgeInfo = (MsgSC_PurgeInfo*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,purgeinfo);

			pSendData->set_m_ncount(pMsgSC_PurgeInfo->m_nCount);

			for(VecUSN::iterator it = pMsgSC_PurgeInfo->m_vtPurgeUSN.begin() ; it < pMsgSC_PurgeInfo->m_vtPurgeUSN.end() ; ++it)
			{
				pSendData->add_m_vtpurgeusn()->set_usn(*it);
			}

			#define jLAMDA_send_purgeinfo(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_purgeinfo,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_purgeinfo(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_refillmoneyntf:
		{
			MsgSC_RefillMoneyNtf* pMsgSC_RefillMoneyNtf = (MsgSC_RefillMoneyNtf*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg,pSendData,refillmoneyntf);

			pSendData->set_m_lusn(pMsgSC_RefillMoneyNtf->m_lUSN);
			pSendData->set_m_llrefillmoney(pMsgSC_RefillMoneyNtf->m_llRefillMoney);
			pSendData->set_m_nrefillcnt(pMsgSC_RefillMoneyNtf->m_nRefillCnt);

			#define jLAMDA_send_refillmoneyntf(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_refillmoneyntf,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_refillmoneyntf(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_userdisconnect:
		{
			MsgSC_UserDisconnect* pMsgSC_UserDisconnect = (MsgSC_UserDisconnect*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg, pSendData, userdisconnect);

			pSendData->set_m_lusn(pMsgSC_UserDisconnect->m_lUSN);
			pSendData->set_m_lstate(pMsgSC_UserDisconnect->m_lState);
			pSendData->set_m_lownerusn(pMsgSC_UserDisconnect->m_lOwnerUSN);

			PKUserInfo* pPKUserInfo = pSendData->mutable_m_uinfo();
			UserInfo* pUserInfo = &pMsgSC_UserDisconnect->m_uinfo;

			pPKUserInfo->set_m_lack(pUserInfo->m_lAck);
			pPKUserInfo->set_m_lclevel(pUserInfo->m_lCLevel);
			pPKUserInfo->set_m_ldiecardsdealt(pUserInfo->m_lDieCardsDealt);
			pPKUserInfo->set_m_lexit(pUserInfo->m_lExit);
			pPKUserInfo->set_m_ljackpot(pUserInfo->m_lJackpot);
			pPKUserInfo->set_m_llcmoney(pUserInfo->m_llCMoney);
			pPKUserInfo->set_m_llfmoney(pUserInfo->m_llFMoney);
			pPKUserInfo->set_m_lsoundtype(pUserInfo->m_lSoundType);
			pPKUserInfo->set_m_luserstate(pUserInfo->m_lUserState);
			pPKUserInfo->set_m_lusn(pUserInfo->m_lUSN);
			pPKUserInfo->set_m_nindex(pUserInfo->m_nIndex);
			pPKUserInfo->set_m_nitemtype(pUserInfo->m_nItemType);
			pPKUserInfo->set_m_savt(pUserInfo->m_sAvt);
			pPKUserInfo->set_m_sid(pUserInfo->m_sID);
			pPKUserInfo->set_m_snickname(pUserInfo->m_sNickName);

			#define jLAMDA_send_userdisconnect(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_userdisconnect,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_userdisconnect(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_continue_msg:
		{
			MsgSC_Continue* pMsgSC_Continue = (MsgSC_Continue*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg, pSendData, continue_msg);

			for(VectorWinLoseInfo::iterator it =  pMsgSC_Continue->m_vtWinLoseInfo.begin() ; it < pMsgSC_Continue->m_vtWinLoseInfo.end() ; ++it)
			{
				PKWinLoseInfo* pWinLoseInfo = pSendData->add_m_vtwinloseinfo();				

				pWinLoseInfo->set_m_llcmoney(it->m_llCMoney);
				pWinLoseInfo->set_m_lwin(it->m_lWin);
				pWinLoseInfo->set_m_lreserved(it->m_lReserved);
				pWinLoseInfo->set_m_llose(it->m_lLose);
			}

			#define jLAMDA_send_continue_msg(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_continue_msg,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_continue_msg(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_ans_ruleset:
		{
			MsgSC_RuleNotify* pMsgSC_RuleNotify = (MsgSC_RuleNotify*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg, pSendData, ans_ruleset);

			pSendData->set_m_nruleidx(pMsgSC_RuleNotify->m_nRuleIdx);

			#define jLAMDA_send_ruleset(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_ruleset,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_ruleset(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_observercnt:
		{
			MsgSC_ObserverCnt* pMsgSC_ObserverCnt = (MsgSC_ObserverCnt*)msg;

			MOB_MAKE_SEND_PACKET(sendMsg, pSendData, observercnt);

			pSendData->set_m_nobservercnt(pMsgSC_ObserverCnt->m_nObserverCnt);
			
			#define jLAMDA_send_observercnt(X,Z) Z(GAnsProtocol, sendmsg)
			jLAMDA_for_each(send_observercnt,PK_Plugin_Connection*)
			{
				it->send_me(sendmsg);					
			}
			jLAMDA_end();

			boost::function<void (PK_Plugin_Connection*)> func = send_observercnt(sendMsg);
			pRoom->for_each(func);
		}
		break;

	case GLAnsGameProtocol_Type_NONE:
		{

		}
		break;
	}
	

}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::SendToUser(long lUSN, const PayloadSC& pld, bool bCrypt)
{
	RCRoomData pRoomData =  GetData();
	nMOB::ug_room_id_t rid = pRoomData.m_lRoomIndex;
	PK_ROOM_RID(pRoom, rid);

	jRETURN(pRoom);

	RCUser* pRCUser = pRoom->m_CGameMgr.FindUser(lUSN);

	GAnsProtocol sendMsg;

	sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
	GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
	packet->set_type(::GLAnsGameProtocol_Type_ans_deal_card);

	pRCUser->m_pCon->send_me(sendMsg);
}

void CObjectMgr::SendToUser(long lUSN, GLAnsGameProtocol_Type type, void* msg)
{
	jLOG(jFUNC1 _T("message type : %d"),type);

	RCRoomData pRoomData =  GetData();
	nMOB::ug_room_id_t rid = pRoomData.m_lRoomIndex;
	PK_ROOM_RID(pRoom, rid);

	jRETURN(pRoom);

	RCUser* pRCUser = pRoom->m_CGameMgr.FindUser(lUSN);

	GAnsProtocol sendMsg;

	sendMsg.set_type(::GAnsProtocol_Type_GLANSGAMEPROTOCOL);
	GLAnsGameProtocol* packet = sendMsg.mutable_ansgameprotocol();
	packet->set_type(type);

	switch(type)
	{
	case GLAnsGameProtocol_Type_ans_deal_cards:
		{
			/*
		MsgSC_DealCards* pMsgSC_DealCards = (MsgSC_DealCards*)msg;

		s_ans_deal_cards* ps_ans_deal_card =  packet->mutable_m_ans_deal_cards();

		ps_ans_deal_card->set_m_lbossusn(pMsgSC_DealCards->m_lBossUSN);
		ps_ans_deal_card->set_m_llpoolmoney(pMsgSC_DealCards->m_llPoolMoney);
		ps_ans_deal_card->set_m_lstate(pMsgSC_DealCards->m_lState);
		ps_ans_deal_card->set_m_ntype(pMsgSC_DealCards->m_nType);
		
		for(vector<Cards>::iterator it = pMsgSC_DealCards->m_tblCard.begin() ; it != pMsgSC_DealCards->m_tblCard.end() ; ++it)
		{
			PKCards* pCard = NULL;
			if(it->m_vtCards.size())
			{
				pCard =ps_ans_deal_card->add_m_tblcard();
			}
			else
			{
				continue;
			}

			pCard->set_m_lresultidx(it->m_lResultIdx);
			for(int i=0; i <it->m_vtCards.size(); i++)
			{
				pCard->add_m_vtcards(it->m_vtCards[i]);
				//pCard->add_m_lresultidx(it->m_lResultIdx);
			}

			for(int i=0; i <it->m_vUserUSN.size(); i++)
			{
				pCard->add_m_vuserusn()->set_usn(it->m_vUserUSN[i]);
			}
		}

		for(vector<Money>::iterator it = pMsgSC_DealCards->m_tblMoney.begin() ; it != pMsgSC_DealCards->m_tblMoney.end() ; ++it)
		{
			PKMoney *pPKMoney = NULL;
			pPKMoney = ps_ans_deal_card->add_m_tblmoney();

			pPKMoney->set_m_lbetcount(it->m_lBetCount);
			pPKMoney->set_m_lbetreceive(it->m_lBetReceive);
			pPKMoney->set_m_lbetstate(it->m_lBetState);
			pPKMoney->set_m_llcallhabmoney(it->m_llCallHabMoney);
			pPKMoney->set_m_llcallmoney(it->m_llCallMoney);
			pPKMoney->set_m_llcmoney(it->m_llCMoney);
			pPKMoney->set_m_lljackpotmoney(it->m_llJackpotMoney);
			pPKMoney->set_m_llsidemoney(it->m_llSideMoney);
			pPKMoney->set_m_lltakemoney(it->m_llTakeMoney);
			pPKMoney->set_m_lresultidx(it->m_lResultIdx);
			pPKMoney->set_m_smoneymsg(it->m_sMoneyMsg);
		}
		*/
		}
		break;

	case GLAnsGameProtocol_Type_ans_select_card://선택한 카드 모든 유저에게 전달
		{
			/*
			MsgSC_SelectedCardAns* pMsgSC_SelectedCardAns = (MsgSC_SelectedCardAns*)msg;
			s_ans_select_card* pSelectCard = packet->mutable_m_ans_select_card();
			
			pSelectCard->set_m_lcardindex(pMsgSC_SelectedCardAns->m_lCardIndex);
			pSelectCard->set_m_lchoicetype(pMsgSC_SelectedCardAns->m_lChoiceType);
			pSelectCard->set_m_lusn(pMsgSC_SelectedCardAns->m_lUSN);
			pSelectCard->set_m_nselect(pMsgSC_SelectedCardAns->m_nSelect);
			*/
		}
		break;

	case GLAnsGameProtocol_Type_ans_opencard:
		{
			/*
			MsgSC_DealOpenCard* pMsgSC_DealOpenCard = (MsgSC_DealOpenCard*)msg;
			s_ans_opencard* pOpenCard = packet->mutable_m_ans_opencard();

			pOpenCard->set_m_lstate(pMsgSC_DealOpenCard->m_lState);
			
			for(vector<Cards>::iterator it = pMsgSC_DealOpenCard->m_tblCard.begin() ; it != pMsgSC_DealOpenCard->m_tblCard.end() ; ++it)
			{
				PKCards* pCard = pOpenCard->add_m_tblcard();

				pCard->set_m_lresultidx(it->m_lResultIdx);

				for(int i = 0 ; i < it->m_vtCards.size() ; ++i)
				{
					pCard->add_m_vtcards(it->m_vtCards[i]);
				}

				for(int i=0; i <it->m_vUserUSN.size(); i++)
				{
					pCard->add_m_vuserusn()->set_usn(it->m_vUserUSN[i]);
				}
			}
			
			for(int i = 0 ; i < pMsgSC_DealOpenCard->m_vtState.size() ; ++i)
			{
				pOpenCard->add_m_vtstate(pMsgSC_DealOpenCard->m_vtState[i]);
			}
			*/
		}

		break;

	case GLAnsGameProtocol_Type_ans_deal_hiddencard:
		{
			MsgSC_DealHiddenCard *pMsgSC_DealHiddenCard = (MsgSC_DealHiddenCard*)msg;
			s_ans_deal_hiddencard* pDealHiddenCard = packet->mutable_m_ans_deal_hiddencard();

			pDealHiddenCard->set_m_lbossusn(pMsgSC_DealHiddenCard->m_lBossUSN);
			pDealHiddenCard->set_m_lcardsdealt(pMsgSC_DealHiddenCard->m_lCardsDealt);

			int i = 0; 
			for(vector<OneCard>::iterator it = pMsgSC_DealHiddenCard->m_vtOneCard.begin() ; it != pMsgSC_DealHiddenCard->m_vtOneCard.end() ; ++it)
			{
				PKOneCard* pOneCard = pDealHiddenCard->add_m_vtonecard();

				pOneCard->set_m_lcardindex(it->m_lCardIndex);
				pOneCard->set_m_nindex(it->m_nIndex);
			}
		}
		break;

	case GLAnsGameProtocol_Type_carddata:
		{
			MsgSC_CardData* pMsgSC_CardData = (MsgSC_CardData*)msg;

			s_carddata* pCardData = packet->mutable_m_carddata();

			pCardData->set_m_llpoolmoney(pMsgSC_CardData->m_llPoolMoney);
			pCardData->set_m_lcardsdealt(pMsgSC_CardData->m_lCardsDealt);
			pCardData->set_m_ndealcnt(pMsgSC_CardData->m_nDealCnt);

			for(vector<Cards>::iterator it = pMsgSC_CardData->m_tblCard.begin() ; it != pMsgSC_CardData->m_tblCard.end() ; ++it)
			{
				PKCards* pCard = pCardData->add_m_tblcard();

				pCard->set_m_lresultidx(it->m_lResultIdx);	

				for(int i = 0 ; i < it->m_vtCards.size() ; ++i)
				{
					pCard->add_m_vtcards(it->m_vtCards[i]);
				}

				for(int i=0; i <it->m_vUserUSN.size(); i++)
				{
					pCard->add_m_vuserusn()->set_usn(it->m_vUserUSN[i]);
				}
			}
			
		}
	case GLAnsGameProtocol_Type_entryreject:
		{
			MsgSC_EntryReject* pMsgSC_EntryReject = (MsgSC_EntryReject*)msg;

			s_entryreject* pEntryReject = packet->mutable_m_entryreject();

			pEntryReject->set_m_llcmoney(pMsgSC_EntryReject->m_llCMoney);
			pEntryReject->set_m_ltype(pMsgSC_EntryReject->m_lType);
		}
		break;

	case GLAnsGameProtocol_Type_ans_purge:
		{
			MsgSC_PurgeAns* pMsgSC_PurgeAns = (MsgSC_PurgeAns*)msg;

			s_ans_purge* pPurge = packet->mutable_m_ans_purge();
		}
		break;

	case GLAnsGameProtocol_Type_bonus:
		{
			MsgSC_Bonus* pMsgSC_Bonus = (MsgSC_Bonus*)msg;

			s_bonus* pBonus = packet->mutable_m_bonus();

			pBonus->set_m_llbonus(pMsgSC_Bonus->m_llBonus);
		}
		break;

	case GLAnsGameProtocol_Type_userjoinerr:
		{
			MsgSC_UserJoinErr* pMsgSC_UserJoinErr = (MsgSC_UserJoinErr*)msg;

			s_userjoinerr* pJoinErr = packet->mutable_m_userjoinerr();

			pJoinErr->set_m_lusn(pMsgSC_UserJoinErr->m_lUSN);
			pJoinErr->set_m_lerrorcode(pMsgSC_UserJoinErr->m_lErrorCode);
		}
		break;

	case GLAnsGameProtocol_Type_userjoinans:
		{
			MsgSC_UserJoinAns* pMsgSC_UserJoinAns = (MsgSC_UserJoinAns*)msg;

			s_userjoinans* pUserJoinAns = packet->mutable_m_userjoinans();

			pUserJoinAns->set_m_lbossusn(pMsgSC_UserJoinAns->m_lBossUSN);
			pUserJoinAns->set_m_lchannel_idx(pMsgSC_UserJoinAns->m_lChannel_idx);
			pUserJoinAns->set_m_lownerusn(pMsgSC_UserJoinAns->m_lOwnerUSN);
			pUserJoinAns->set_m_lstate(pMsgSC_UserJoinAns->m_lState);
			pUserJoinAns->set_m_nenter(pMsgSC_UserJoinAns->m_nEnter);
			pUserJoinAns->set_m_nroompurgecnt(pMsgSC_UserJoinAns->m_nRoomPurgeCnt);
			pUserJoinAns->set_m_nset(pMsgSC_UserJoinAns->m_nSet);

			PKOption* pPKOption = pUserJoinAns->mutable_m_option();
			Option* pOption = &pMsgSC_UserJoinAns->m_option;

			pPKOption->set_m_becho(pOption->m_bEcho);
			pPKOption->set_m_laddrule(pOption->m_lAddRule);
			pPKOption->set_m_lbetrule(pOption->m_lBetRule);
			pPKOption->set_m_lbettype(pOption->m_lBetType);
			pPKOption->set_m_lcategory(pOption->m_lCategory);
			pPKOption->set_m_lchannelid(pOption->m_lChannelID);
			pPKOption->set_m_lchoicemode(pOption->m_lChoiceMode);
			pPKOption->set_m_llantemoney(pOption->m_llAnteMoney);
			pPKOption->set_m_llgameantemoney(pOption->m_llGameAnteMoney);
			pPKOption->set_m_llimitmoney(pOption->m_lLimitMoney);
			pPKOption->set_m_lmakeusn(pOption->m_lMakeUSN);
			pPKOption->set_m_lmaxplayercardcnt(pOption->m_lMaxPlayerCardCnt);
			pPKOption->set_m_lmaxplayerusercnt(pOption->m_lMaxPlayerUserCnt);
			pPKOption->set_m_lmaxusercnt(pOption->m_lMaxUserCnt);
			pPKOption->set_m_lrematchjoin(pOption->m_lRematchJoin);
			pPKOption->set_m_lroomtype(pOption->m_lRoomType);
			pPKOption->set_m_spassword(pOption->m_sPassword);
			pPKOption->set_m_sroomtitle(pOption->m_sRoomTitle);
		}
		break;

	case GLAnsGameProtocol_Type_startreq:
		{
			MsgSC_StartReq* pMsgSC_StartReq = (MsgSC_StartReq*)msg;

			s_startreq* pStartReq = packet->mutable_m_startreq();
		}
		break;

	case GLAnsGameProtocol_Type_systemmsg:
		{
			MsgSC_SystemMsg* pMsgSC_SystemMsg = (MsgSC_SystemMsg*)msg;

			s_systemmsg* pSystemMsg = packet->mutable_m_systemmsg();

			pSystemMsg->set_m_ltype(pMsgSC_SystemMsg->m_lType);
		}
		break;

	case GLAnsGameProtocol_Type_ans_abuse:
		{
			packet->mutable_m_ans_abuse()->CopyFrom(*(s_ans_abuse*)msg);
		}
		break;
	}

	pRCUser->m_pCon->send_me(sendMsg);
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
		//SendToAll(pld);
		SendToAll(GLAnsGameProtocol_Type_systemmsg, &msg);
	else
		SendToUser(lUSN, GLAnsGameProtocol_Type_systemmsg, &msg);
		//SendToUser(lUSN, pld);
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
//long CObjectMgr::OnAddUserInRoom(long lUSN, const char* szUserData, long lSize, long* plErrorCode)
long CObjectMgr::OnAddUserInRoom(RCUser *user)
{
#if 1
	string strLog;
	if(false==m_RCUserData.ExistUser()){
		//if(lUSN!=m_cRCRoomData.m_option.m_lMakeUSN){
		if(user->m_lUSN!=m_cRCRoomData.m_option.m_lMakeUSN){
			strLog="";//::format("USN : %d : %d", user->m_lUSN, m_cRCRoomData.m_option.m_lMakeUSN);
			m_cFileLog.DebugLog(strLog.c_str());
		}
	}
	strLog="";//::format("USN : %d : %d : Num = %d", user->m_lUSN, m_cRCRoomData.m_option.m_lMakeUSN, m_RCUserData.size());
	m_cFileLog.DebugLog(strLog.c_str());
	SPUserFullInfo pLser;

	//string str(szUserData, lSize);

	//LPBYTE pData = (LPBYTE)str.data();

	//BLoad(&pLser, &pData, (LPDWORD)&lSize);
	//BER<SPUserFullInfo >::Load(&pLser, &pData, (LPDWORD)&lSize);

	RCUser * pUser=FindUser(user->m_lUSN);
	if(pUser!=NULL){
		//(*plErrorCode)=SGRC_E_DUPLICATED;
		return SGRC_E_DUPLICATED;
	}

	long lErrorCode=0;	
	if(IsUserJoinErr(user->m_lUSN, lErrorCode))
	{
		SendUserJoinErr(user->m_lUSN, lErrorCode);
		//(*plErrorCode)=SGRC_E_BLACKLIST;
		return SGRC_E_BLACKLIST;
	}
	if(m_cRCRoomData.m_option.m_lMaxUserCnt<=GetUICount()){
		//(*plErrorCode)=SGRC_E_ROOM_FULL;
		return SGRC_E_ROOM_FULL;
	}

	CParser cParser;
	if(false==pLser.m_sUserGameData.empty()){
		cParser.MakeStringToTable(string(pLser.m_sUserGameData), "|");
	}

	/*
	int nStart=0;
	RCUser User;
	User.Clear();

	User.m_lUSN=lUSN;
	User.m_lJumin=pLser.m_lJumin;
	User.m_lFirstUSN=pLser.m_lFirstUSN;
	User.m_lAgeIndex=pLser.m_lAgeIndex;
	User.m_lJobIndex=pLser.m_lJobIndex;
	User.m_lRegionIndex=pLser.m_lRegionIndex;
	User.m_lGuildIndex=pLser.m_lGuildIndex;
	User.m_lMemberIndex=pLser.m_lMemberIndex;
	User.m_lClientIP=pLser.m_lClientIP;
	User.m_lGatewayIP=pLser.m_lGatewayIP;
	User.m_lMacAddress=pLser.m_lMacAddress;
	User.m_sMobileInfo=pLser.m_sMobileInfo;
	User.m_sAuthKey=pLser.m_sAuthKey;
	User.m_nIndex=-1;
	User.m_sNickName=pLser.m_sNickName;
	User.m_sUserID=pLser.m_sUserID;
	User.m_lSex=0;
	User.m_llCMoney=cParser.GetHyper(nStart, 100000000000);
	User.m_llFMoney=User.m_llCMoney;
	User.m_llSafeMoney=cParser.GetHyper(nStart+1, 0);
	User.m_lCLevel=cParser.GetLong(nStart+2, 0);
	User.m_llPlastAllinDate=cParser.GetHyper(nStart+3, 0);
	User.m_llPlastLogonDay=cParser.GetHyper(nStart+4, 0);
	User.m_lMTodayPlayCount=cParser.GetLong(nStart+5, 0);
	User.m_lMTodayPlayTime=cParser.GetLong(nStart+6, 0);
	User.m_lPTotalPlayCount=cParser.GetLong(nStart+7, 0);
	User.m_cRefill.m_lPLevel=cParser.GetLong(nStart+8, 0);
	User.m_llPExtMoney=cParser.GetHyper(nStart+9, 0);
	User.m_llPExtendDate=cParser.GetHyper(nStart+10, 0);
	User.m_llPBonusDate=cParser.GetHyper(nStart+11, 0);
	User.m_lMMonthPlayCount=cParser.GetLong(nStart+12, 0);
	User.m_lMMonthPlayTime=cParser.GetLong(nStart+13, 0);
	User.m_cWinLose.m_lWin=cParser.GetLong(nStart+14, 0);
	User.m_cWinLose.m_lLose=cParser.GetLong(nStart+15, 0);
	User.m_lGDisCnt=cParser.GetLong(nStart+16, 0);
	User.m_llGlastLogonDay=cParser.GetHyper(nStart+17, 0);
	User.m_llGRegDate=cParser.GetHyper(nStart+18, 0);
	User.m_llGFirstPlayDate=cParser.GetHyper(nStart+19, 0);
	User.m_lGTodayPlayCount=cParser.GetLong(nStart+20, 0);
	User.m_lGTodayPlayTime=cParser.GetLong(nStart+21, 0);
	User.m_lGTotalPlayCount=cParser.GetLong(nStart+22, 0);
	User.m_lGTotalPlayTime=cParser.GetLong(nStart+23, 0);
	User.m_lGAllinCnt=cParser.GetLong(nStart+24, 0);
	User.m_lGAllinOut=cParser.GetLong(nStart+25, 0);
	User.m_llGLastAllinDate=cParser.GetHyper(nStart+26, 0);
	User.m_cWinLose_Today.m_lWin=cParser.GetLong(nStart+27, 0);
	User.m_cWinLose_Today.m_lLose=cParser.GetLong(nStart+28, 0);
	User.m_llGTodayMoney=cParser.GetHyper(nStart+29, 0);
	User.m_lFourCardCnt=cParser.GetLong(nStart+30, 0);
	User.m_lStraightFlushCnt=cParser.GetLong(nStart+31, 0);
	User.m_lRoyalStraightFlushCnt=cParser.GetLong(nStart+32, 0);
	User.m_nReserve01=cParser.GetInt(nStart+33, 0);
	User.m_nReserve02=cParser.GetInt(nStart+34, 0);
	User.m_ItemList.Clear();
	User.m_llJoinDate=GetCurrentSystemTime();
	User.m_llPlayDate=User.m_llGlastLogonDay;
	
	AddUser(User);
	*/

	AddUser(*user);
	UserJoin(user->m_lUSN);
#endif

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
	RemoveUser(lUSN);
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