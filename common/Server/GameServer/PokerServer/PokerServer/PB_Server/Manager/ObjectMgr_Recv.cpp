//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"

#include "ObjectMgr.h"

#include "../util/util.h"

#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

using namespace util;

//----------------------------------------------------------------------------------------------------
void CObjectMgr::OnRcvPurge(long lUSN, s_req_purge * pMsg)
{
	// 방장만이 할수 있다. 그리고 강퇴 대상이 방장이면 안된다.
	if( lUSN!=m_cGameInfo.m_lOwnerUSN || pMsg->m_lpurgeusn()==m_cGameInfo.m_lOwnerUSN )  return ;

	RCUser* pUser=FindUser(pMsg->m_lpurgeusn());
	if(pUser==NULL) return ;

	//if(pUser->m_nPurge_BadmanCnt >= 1 && pMsg->m_lType==true )	// 강제적으로 나가라고 했는데 클라이언트 조작으로 안 나가는 나쁜넘이 있다
	//{
	//	m_pGRCContainer->DisconnectUser(pMsg->m_lpurgeusn());		return ;
	//}

	string sTempName;
	if(pMsg->m_ltype())                            // 0: 강퇴취소, 1:강퇴
	{
		//// 강퇴를 두번 시키는 경우를 예방하고자 함
		//if(find(m_cPurge.vtPurgeList.begin(),m_cPurge.vtPurgeList.end(), pMsg->m_lpurgeusn())!=m_cPurge.vtPurgeList.end()) return;

		//pUser->m_nPurge_BadmanCnt++;
		if(false==m_cPurge.AddPurge(pMsg->m_lpurgeusn())) return;
		if(IsUI(pMsg->m_lpurgeusn()))
		{
			int nIndex=USNToIdx(pMsg->m_lpurgeusn());
			if(nIndex<0) return ;

			UserInfo & ui=GetUI(nIndex);
			sTempName=ui.m_sNickName;

			// 게임중이 아니면 바로 강퇴
			if( ui.m_lUserState==USERSTATE_WAITING || ui.m_lUserState==USERSTATE_READY )
			{
				ObserveProcesses(pMsg->m_lpurgeusn());

				//SendSystemMsg(SYSMSG_PURGE, sTempName, pMsg->m_lpurgeusn());
				SendSystemMsg(SYSMSG_PURGE, sTempName);	// 강퇴 당한사람 외에도 전체로 보냄

				SendPurgeAns(pMsg->m_lpurgeusn());
			}
			else
			{
				SendSystemMsg(SYSMSG_PURGE_RESERVED, sTempName, lUSN);
				//MsgSC_SystemMsg msg;
				//msg.m_lType=SYSMSG_PURGE_RESERVED;
				//msg.m_sMsg=sTempName;
				//PayloadSC pld(PayloadSC::msgSystemMsg_Tag, msg);
				//SendToUser(lUSN, pld);

			}
		}
		else
		{
			sTempName=pUser->m_sNickName;
			SendSystemMsg(SYSMSG_PURGE, sTempName, pMsg->m_lpurgeusn());
			SendPurgeAns(pMsg->m_lpurgeusn());
		}
	}
	else
	{
		m_cPurge.PurgeErase(pMsg->m_lpurgeusn());

		if(IsUI(pMsg->m_lpurgeusn()))
		{
			int nIndex=USNToIdx(pMsg->m_lpurgeusn());
			if(nIndex<0) return ;

			UserInfo & ui=GetUI(nIndex);
			sTempName=ui.m_sNickName;
		}
		else
		{
			RCUser * pUser=FindUser(pMsg->m_lpurgeusn());
			if(pUser==NULL) return;

			sTempName=pUser->m_sNickName;
		}
		
		//// BanMan 체크
		//pUser->m_nPurge_BadmanCnt--;
		//// BanMan 체크

		SendSystemMsg(SYSMSG_PURGE_CANCEL, sTempName, lUSN);
	}
	SendPurgeInfo();
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::OnRcvAbuse(long lUSN, s_req_abuse * pMsg)
{
	RCUser * pUser=FindUser(lUSN);
	if(pUser==NULL)
		return ;

	if(pMsg->m_sday()=="")
		return ;

	if(pMsg->m_ltype()!=3)
	{
		string str="";//::format("OnRcvAbuse : lType=%d,  StartTime=%s", pMsg->m_lType, pMsg->m_sDay.c_str());
		m_cFileLog.DebugLog(str.c_str());

		UserDisconnect(lUSN, false);

		s_ans_abuse msg;
		SendToUser(lUSN, GLAnsGameProtocol_Type_ans_abuse, &msg);
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::OnRcvSoundType(long lUSN, s_req_soundtype * pMsg)
{
	int nIndex=USNToIdx(lUSN);
	if(nIndex==-1) return;

	UserInfo & ui=GetUI(nIndex);
	ui.m_lSoundType=pMsg->m_lsoundtype();

	s_soundtypeans msg;
	msg.set_m_lusn(lUSN);
	msg.set_m_nindex(nIndex);
	msg.set_m_lsoundtype(pMsg->m_lsoundtype());
	//PayloadSC pld(PayloadSC::msgSoundTypeAns_Tag, msg);
	//SendToAll(pld);
	SendToAll(GLAnsGameProtocol_Type_soundtypeans, &msg);


}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::OnRcvExitQue(long lUSN, s_req_exitque * pMsg)
{
	int nIndex=USNToIdx(lUSN);
	if(nIndex==-1) return;

	switch(m_cRCRoomData.m_lState)
	{
	case GAMESTATE_READY:
		{
			if(false==m_cGameInfo.m_b49Rematch)
			{
				SendExitNtf(nIndex, pMsg->m_lexit(), true);
			}
			else
			{
				UserInfo & ui=GetUI(nIndex);
				//if( ( ui.m_lUserState!=USERSTATE_WAITING ) && ( ui.m_lUserState!=USERSTATE_49WAITING ) )
				if( ui.m_lUserState!=USERSTATE_WAITING )
				{
					if(ui.m_lExit==pMsg->m_lexit())
					{
						pMsg->set_m_lexit(0);
					}
					SendExitNtf(nIndex, pMsg->m_lexit(), false);
				}
				else
				{
					SendExitNtf(nIndex, pMsg->m_lexit(), true);
				}
			}
		}
		break;
	case GAMESTATE_SAVE:
		{
			//SendExitNtf(nIndex, pMsg->m_lexit(), true);
			UserInfo & ui=GetUI(nIndex);
			//if( ( ui.m_lUserState!=USERSTATE_WAITING ) && ( ui.m_lUserState!=USERSTATE_49WAITING ) )
			if( pMsg->m_baction() && ui.m_lUserState!=USERSTATE_WAITING )
			{
				if(ui.m_lExit==pMsg->m_lexit())
				{
					pMsg->set_m_lexit(0);
				}
				SendExitNtf(nIndex, pMsg->m_lexit(), false);
			}
			else
			{
				SendExitNtf(nIndex, pMsg->m_lexit(), true);
			}
		}
		break;
	case GAMESTATE_START:
	case GAMESTATE_SELECT:
	case GAMESTATE_PLAY:  
	case GAMESTATE_RESULT: // 게임이 끝나고 나가
		{
			UserInfo & ui=GetUI(nIndex);
			long lstate=ui.m_lUserState;
			if(lstate==USERSTATE_49WAITING || lstate==USERSTATE_SELECTBEGIN || lstate==USERSTATE_SELECTEND || lstate==USERSTATE_PLAYING || lstate==USERSTATE_DIE)
			//if( lstate==USERSTATE_SELECTBEGIN || lstate==USERSTATE_SELECTEND || lstate==USERSTATE_PLAYING || lstate==USERSTATE_DIE )
			{
				if(ui.m_lExit==pMsg->m_lexit())
				{
					pMsg->set_m_lexit(0);
				}
				SendExitNtf(nIndex, pMsg->m_lexit(), false);
			}
			else
			{
				SendExitNtf(nIndex, pMsg->m_lexit(), true);
			}
		}
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------------------------------------------
void CObjectMgr::OnRcvGameMasterCall(long lUSN, MsgCS_GameMasterCall * pMsg)
{
	if(m_cRCRoomData.m_lGameMaster!=-1) return;

	m_cRCRoomData.m_lGameMaster=lUSN;
	m_cGameInfo.m_sGameMasterTime=GetCurrentSystemTime_s();

	MsgSC_GameMasterCallNtf msg;
	msg.m_lGMCall_USN=lUSN;
	PayloadSC pld(PayloadSC::msgGameMasterCallNtf_Tag, msg);
	SendToAll(pld);	
}
//----------------------------------------------------------------------------------------------------
