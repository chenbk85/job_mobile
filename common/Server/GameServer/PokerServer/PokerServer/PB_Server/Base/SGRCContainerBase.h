#ifndef _SGRCCONTAINERBASE_H_
#define _SGRCCONTAINERBASE_H_

///////////////////////////////////////////////////////////////////////////////
/// ISGRCContainer
///////////////////////////////////////////////////////////////////////////////

interface ISGRCContainer
{
	// Message
	virtual long __stdcall GetUserMsg(IN long lUSN, IN OUT char* szMsg, IN OUT long* plSize) = 0;
	virtual long __stdcall SendUserMsg(IN long lSendType, IN OPTIONAL long lUSN, IN const char* szMsg, IN long lSize) = 0;
	virtual long __stdcall DisconnectUser(IN long lUSN) = 0;
	virtual long __stdcall SendMessageToServer(IN long lMsgType, IN long lParam, IN const char* szContents, IN long lSize) = 0;

	// DB
//	virtual long __stdcall GetUserData(long lUSN, char* szUserData, long* plSize) = 0;
	virtual long __stdcall UpdateUserData(IN long lUSN, IN const char* szUserData, IN long lSize) = 0;
//	virtual long __stdcall SetGameLog(const char* szGameData, long lSize) = 0;
	virtual long __stdcall ExecuteQueryToDB(IN long lQueryType, IN long lDBType, IN const char* szQuery, IN long lQuerySize, OUT GBuf& bufResult, OUT long* plResult) = 0;
	virtual long __stdcall AExecuteQueryToDB(IN long lQueryType, IN long lDBType, IN const char* szQuery, IN long lSize, IN long lIndex) = 0;
//	virtual long __stdcall GetUpdatedUserData(long lUSN, char* szUserData, long* plSize) = 0;
//	virtual longlong __stdcall SaveExtMoney(long lUSN, long lMSN) = 0;

	// Notify
	virtual long __stdcall NotifyChangeRoomInfo(IN const char* szRoomInfo, IN long lSize) = 0;
//	virtual long __stdcall NotifyChangeRoomState(long lRoomState) = 0;
//	virtual long __stdcall NotifyUserState(long lUSN, long lUserState) = 0;
//	virtual long __stdcall NotifyChangeRoomOwner(long lUSN) = 0;
//	virtual long __stdcall NotifyUserDataChanged(long lUSN, const char* szUserData, long lSize) = 0;
	virtual long __stdcall AutoPlayNotify(IN long lType, IN long lUSN) = 0;

//	virtual long __stdcall GetRoomID(long* plCategory, long* plGCIID) = 0;
	virtual long __stdcall SetTimer(IN OUT long* plTimerIndex, IN long lDue, IN long lPeriod) = 0;
	virtual long __stdcall RemoveTimer(IN long lTimerIndex) = 0;
	// Next New Interface Must be located here.
};

//	Container Interface Common Error Code. Applied from SendMessageToServer()
#define CTERR_SUCCESS				0
#define CTERR_BASE					-65536
#define CTERR_INVALIDPARAM			(CTERR_BASE - 1)
#define CTERR_UNKNOWN				(CTERR_BASE - 2)

// ExecuteQueryToDB()'s lDBType
enum DB_TYPE
{
	DBTYPE_MIN = 0,

	DBTYPE_PHONE,
	DBTYPE_PHONELOG,

	DBTYPE_MAX
};

// ExecuteQueryToDB()'s lQueryType
enum DBQUERY_TYPE
{
	DB_QUERYTYPE_NOTDEFINED = 0,

	DB_QUERY				= 1,				// string query
	DB_QUERY_LIST								// 실행 결과를 List로 Return
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
