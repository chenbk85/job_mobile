//------------------------------------------------------------------------------------
// Module Name			: iRoomContext(.h)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Defines RoomContext used GLS
//------------------------------------------------------------------------------------
#pragma once
//-------------------------------------------------------------------------------------------------
// 

#include "GameMgr_Poker.h"

class CRoomContext : public CGameMgr
//-------------------------------------------------------------------------------------------------
{
public:
	//(KOR) 해당 방 번호로 GLS에서 사용할 Room Context를 생성한다.
	//CRoomContext( const interface ISGRCContainer* const pGRCContainer, char* szRoomID, long lRoomIDSize );
	CRoomContext(const char* szRoomID);
	virtual ~CRoomContext();
private:
	ISGRCContainer* m_pGRCContainer;
	string m_cRoomString;
	long m_lRoomIndex;
public:
	inline string GetRoomString(){ return m_cRoomString; }
	inline long GetRoomIndex(){ return m_lRoomIndex; }
public:
	virtual long __stdcall OnCreateRoom(const char* szRoomOption, long lSize) ;
	//virtual long __stdcall OnAddUserInRoom(long lUSN, const char* szUserData, long lSize, long* plErrorCode) ;
	virtual long __stdcall OnAddUserInRoom( adl::RCUser *user );
	virtual long __stdcall OnReserveRemoveUserInRoom(long lUSN) ;
	virtual long __stdcall OnUserDisconnectInRoomNotify(long lUSN);
	virtual long __stdcall OnRemoveUser(long lUSN);
	virtual long __stdcall OnUserMsgToRoomNotify(long lUSN, long lSize);
	virtual long __stdcall OnTimerToRoomNotify(long lTimerIndex);
	//virtual long __stdcall OnChangeUserAvatarNotify(long lUSN, long lAvatar);
	//virtual long __stdcall OnChangeUserNicknameNotify(long lUSN, const char* szNickname, long lSize);
	virtual long __stdcall OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize);
	virtual long __stdcall OnRecvMessageFromServer(long lMsgType, long lParam, const char* szContents, long lSize);
	virtual long __stdcall CanUseIBB(long lUSN);
	virtual long __stdcall OnAExcuteQueryToDBResult(long lResult, long lIndex, const char* szResult, long lSize, long lErrorCode);
	virtual long __stdcall CheckUserStateFromWeb(long lUSN);
	virtual long __stdcall GetRoomInfo(const char* szRoomInfo, long lSize);
};
