#ifndef _SGRCCONTAINERBASE_H_
#define _SGRCCONTAINERBASE_H_

//#include "../include/GBuf.h"

///////////////////////////////////////////////////////////////////////////////
/// ISGRCContainer
///////////////////////////////////////////////////////////////////////////////

interface ISGRCContainer
{
	// Message
	virtual long __stdcall GetUserMsg(long lUSN, char* szMsg, long* plSize)=0;
	virtual long __stdcall SendUserMsg(long lSendType, long lUSN, const char* szMsg, long lSize)=0;
	virtual long __stdcall DisconnectUser(long lUSN)=0;
	virtual long __stdcall SendMessageToServer(long lMsgType, long lParam, const char* szContents, long lSize)=0;

	// DB
//	virtual long __stdcall GetUserData(long lUSN, char* szUserData, long* plSize)=0;
	virtual long __stdcall UpdateUserData(long lUSN, const char* szUserData, long lSize)=0;
//	virtual long __stdcall SetGameLog(const char* szGameData, long lSize)=0;
//	virtual long __stdcall ExecuteQueryToDB(long lQueryType, long lDBType, const char* szQuery, long lQuerySize, GBuf& bufResult, long* plResult)=0;
	virtual long __stdcall AExecuteQueryToDB(long lQueryType, long lDBType, const char* szQuery, long lSize, long lIndex)=0;
//	virtual long __stdcall GetUpdatedUserData(long lUSN, char* szUserData, long* plSize)=0;
//	virtual longlong __stdcall SaveExtMoney(long lUSN, long lMSN)=0;

	// Notify
	virtual long __stdcall NotifyChangeRoomInfo(const char* szRoomInfo, long lSize)=0;
//	virtual long __stdcall NotifyChangeRoomState(long lRoomState)=0;
//	virtual long __stdcall NotifyUserState(long lUSN, long lUserState)=0;
//	virtual long __stdcall NotifyChangeRoomOwner(long lUSN)=0;
//	virtual long __stdcall NotifyUserDataChanged(long lUSN, const char* szUserData, long lSize)=0;
	virtual long __stdcall AutoPlayNotify(long lType, long lUSN)=0;

//	virtual long __stdcall GetRoomID(long* plCategory, long* plGCIID)=0;
	virtual long __stdcall SetTimer(long lTimerIndex, long lDue, long lPeriod)=0;
	virtual long __stdcall RemoveTimer(long lIndex)=0;
	// Next New Interface Must be located here.
};

//	Container Interface Common Error Code. Applied from SendMessageToServer()
#define CTERR_BASE					-65536
#define CTERR_INVALIDPARAM			(CTERR_BASE - 1)

// ExecuteQueryToDB()'s lDBType
enum DB_TYPE
{
	DBTYPE_MIN=0,

	DBTYPE_PHONE,
	DBTYPE_PHONELOG,

	DBTYPE_MAX
};

// SendUserMsg Type
enum SEND_TYPE
{
	SENDTYPE_UNICAST,
	SENDTYPE_EXCEPT,
	SENDTYPE_ALL
};

// AutoPlaying State
#define AUTOPLAY_SET	1
#define AUTOPLAY_RESET	2

// ODBGW
#define MSGTYPE_ODBGW_UPDATE_RECOMMEND_ROOM		0x00010001

#endif // _SGRCCONTAINERBASE_H_
