#ifndef _SROOMCONTEXTBASE_H_
#define _SROOMCONTEXTBASE_H_

///////////////////////////////////////////////////////////////////////////////
/// ISRoomContext
///////////////////////////////////////////////////////////////////////////////

#include "../../Protocol Buffers/Poker/AdlGameUser_Poker.h"

interface ISRoomContext
//class ISRoomContext
{
	virtual long __stdcall OnCreateRoom(const char* szRoomOption, long lSize)=0;
	//virtual long __stdcall OnAddUserInRoom(long lUSN, const char* szUserData, long lSize, long* plErrorCode)=0;
	virtual long __stdcall OnAddUserInRoom(adl::RCUser *user)=0;
	virtual long __stdcall OnReserveRemoveUserInRoom(long lUSN)=0;
//	virtual long __stdcall OnRemoveUser(long lUSN)=0;
	virtual long __stdcall OnUserDisconnectInRoomNotify(long lUSN)=0;
	virtual long __stdcall OnUserMsgToRoomNotify(long lUSN, long lSize)=0;
	virtual long __stdcall OnTimerToRoomNotify(long lTimerIndex)=0;
//	virtual long __stdcall OnTerminateRoom(long lReason)=0;

//	virtual long __stdcall OnChatChannelDisconnect(long lUSN)=0;
//	virtual long __stdcall OnChangeRoomOption(const char* szRoomOption, long lSize)=0;
//	virtual long __stdcall OnChangeUserAvatarNotify(long lUSN, long lAvatar)=0;
//	virtual long __stdcall OnChangeUserNicknameNotify(long lUSN, const char* szNickname, long lSize)=0;
	virtual long __stdcall OnChangeUserItemNotify(long lUSN, const char* szItem, long lSize)=0;
//	virtual long __stdcall OnMulticast(GBuf& gBuf)=0;

	virtual long __stdcall OnRecvMessageFromServer(long lMsgType, long lParam, const char* szContents, long lSize)=0;
	virtual long __stdcall CanUseIBB(long lUSN)=0;
//	virtual long __stdcall UserDataChange(long lUSN, const char* szUserGameData, long lSize)=0;
	virtual long __stdcall OnAExcuteQueryToDBResult(long lResult, long lIndex, const char* szResult, long lSize, long lErrorCode)=0;

	// Check whether this user can buy item or not
	virtual long __stdcall CheckUserStateFromWeb(long lUSN)=0;
//	virtual BOOL __stdcall IsBlackListUser(long lUSN)=0;

	virtual long __stdcall GetRoomInfo(const char* szRoomInfo, long lSize)=0;
};

#endif // _SROOMCONTEXTBASE_H_
