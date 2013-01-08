//------------------------------------------------------------------------------------
// Module Name			: iRoomContext(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Defines RoomContext used GLS
//------------------------------------------------------------------------------------
#include "StdAfx.h"
#include "iRoomContext.h"

//#include "../../Protocol Buffers/Poker/AdlGameUser_Poker.h"

//------------------------------------------------------------------------------------
//CRoomContext::CRoomContext(const interface ISGRCContainer* const pGRCContainer, 
//						   char* szRoomID, long lRoomIDSize) : CGameMgr()

CRoomContext::CRoomContext(const char* szRoomID) : CGameMgr()							
//------------------------------------------------------------------------------------
{
	//m_pGRCContainer=(ISGRCContainer*)pGRCContainer;
	CParser cParser;
	if(NULL!=szRoomID){
		m_cRoomString=string(szRoomID);
		cParser.MakeStringToTable(string(szRoomID), "|");
	}
	m_cRCRoomData.m_option.m_lCategory=cParser.GetLong(1, 1);
	m_cRCRoomData.m_option.m_lChannelID=cParser.GetLong(2, 1);
	m_cRCRoomData.m_lRoomIndex=m_lRoomIndex=cParser.GetLong(3, 1);
	//SetGRCContainer((ISGRCContainer*)pGRCContainer);
	//_SET(m_lRoomIndex)->SetGRCContainer( m_pGRCContainer );
	//_ROOM(m_lRoomIndex)->GetData().m_lRoomIndex=lRoomIndex;
	//_ROBOT(m_lRoomIndex)->GetAI().SetRoomContext(this);
}
//------------------------------------------------------------------------------------
CRoomContext::~CRoomContext()
//------------------------------------------------------------------------------------
{

}
//------------------------------------------------------------------------------------
// Interface to communicate with GLS
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Create Room Request
long __stdcall CRoomContext::OnCreateRoom(const char* szRoomOption, long lSize)
//------------------------------------------------------------------------------------
{
	//return _SET(m_lRoomIndex)->OnCreateRoom(szRoomOption, lSize);
	return CGameMgr::OnCreateRoom(szRoomOption, lSize);
}
//------------------------------------------------------------------------------------
//long __stdcall CRoomContext::OnAddUserInRoom( long lUSN, const char* szUserData, long lSize, long* plErrorCode )
long __stdcall CRoomContext::OnAddUserInRoom( adl::RCUser *user )
//------------------------------------------------------------------------------------
{
	//return _SET(m_lRoomIndex)->OnAddUserInRoom(lUSN, szUserData, lSize, plErrorCode);
	//return CGameMgr::OnAddUserInRoom(lUSN, szUserData, lSize, plErrorCode);

	return CGameMgr::OnAddUserInRoom(user);
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnReserveRemoveUserInRoom( long lUSN )
//------------------------------------------------------------------------------------
{
	//_SET(m_lRoomIndex)->OnReserveRemoveUserInRoom(lUSN);
	//return -1L;
	//return _SET(m_lRoomIndex)->OnReserveRemoveUserInRoom(lUSN);
	return CGameMgr::OnReserveRemoveUserInRoom(lUSN);
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnUserDisconnectInRoomNotify( long lUSN )
//------------------------------------------------------------------------------------
{
	//return _SET(m_lRoomIndex)->OnUserDisconnectInRoomNotify(lUSN);
	return CGameMgr::OnUserDisconnectInRoomNotify(lUSN);
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnRemoveUser( long lUSN )
//------------------------------------------------------------------------------------
{
	//return _SET(m_lRoomIndex)->OnRemoveUser(lUSN);
	return CGameMgr::OnRemoveUser(lUSN);
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnUserMsgToRoomNotify( long lUSN, long lSize )
//------------------------------------------------------------------------------------
{
	//return _USERMSG(m_lRoomIndex)->OnUserMsgToRoomNotify( lUSN, lSize );
	return CGameMgr::OnUserMsgToRoomNotify( lUSN, lSize );
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnTimerToRoomNotify( long lTimerIndex )
//------------------------------------------------------------------------------------
{
	//return _TIMER(m_lRoomIndex)->OnTimerToRoomNotify( lTimerIndex );
	return CGameMgr::OnTimerToRoomNotify( lTimerIndex );
}
////------------------------------------------------------------------------------------
//long __stdcall CRoomContext::OnChangeUserAvatarNotify(long lUSN, long lAvatar)
////------------------------------------------------------------------------------------
//{
//	//return _SET(m_lRoomIndex)->OnChangeUserAvatarNotify( lUSN, lAvatar );
//	return CGameMgr::OnChangeUserAvatarNotify( lUSN, lAvatar );
//}
////------------------------------------------------------------------------------------
//long __stdcall CRoomContext::OnChangeUserNicknameNotify( long lUSN, const char* szNickname, long lSize )
////------------------------------------------------------------------------------------
//{
//	//return _SET(m_lRoomIndex)->OnChangeUserNicknameNotify( lUSN, szNickname, lSize );
//	return CGameMgr::OnChangeUserNicknameNotify( lUSN, szNickname, lSize );
//}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnChangeUserItemNotify( long lUSN, const char* szItem, long lSize )
//------------------------------------------------------------------------------------
{
	//return _SET(m_lRoomIndex)->OnChangeUserItemNotify( lUSN, szItem, lSize );
	return CGameMgr::OnChangeUserItemNotify( lUSN, szItem, lSize );
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnRecvMessageFromServer( long lMsgType, long lParam, const char* szContents, long lSize )
//------------------------------------------------------------------------------------
{
	//return _SET(m_lRoomIndex)->OnRecvMessageFromServer(lMsgType, lParam, szContents, lSize);
	return CGameMgr::OnRecvMessageFromServer(lMsgType, lParam, szContents, lSize);
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::CanUseIBB( long lUSN )
//------------------------------------------------------------------------------------
{
	//return _ROOM(m_lRoomIndex)->CanUseIBB(lUSN);
	return CGameMgr::CanUseIBB(lUSN);
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::OnAExcuteQueryToDBResult(long lResult, long lIndex, const char* szResult, long lSize, long lErrorCode)
//------------------------------------------------------------------------------------
{
	//return _SET(m_lRoomIndex)->OnAExcuteQueryToDBResult(lRevVal, lIndex, pvtOutData, lErrorCode);
	return CGameMgr::OnAExcuteQueryToDBResult(lResult, lIndex, szResult, lSize, lErrorCode);
}
//------------------------------------------------------------------------------------
long __stdcall CRoomContext::CheckUserStateFromWeb( long lUSN )
//------------------------------------------------------------------------------------
{
	//return _ROOM(m_lRoomIndex)->CheckUserStateFromWeb(lUSN);
	return CGameMgr::CheckUserStateFromWeb(lUSN);
}

//------------------------------------------------------------------------------------
long __stdcall CRoomContext::GetRoomInfo(const char* szRoomInfo, long lSize)
{
	//return _ROOM(m_lRoomIndex)->GetRoomInfo(szRoomInfo, lSize);
	return CGameMgr::GetRoomInfo(szRoomInfo, lSize);
}



						



