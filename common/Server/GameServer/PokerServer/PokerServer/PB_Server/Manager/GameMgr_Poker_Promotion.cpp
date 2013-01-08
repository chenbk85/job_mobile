//------------------------------------------------------------------------------------
// Module Name			: Object(.cpp)
// First Modified Date	: 2010/07/01
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Interface description of CObject
//------------------------------------------------------------------------------------
#include "stdafx.h"


#include "GameMgr_Poker.h"



#if defined(_Poker)

void CGameMgr::PromotionCheck()
{
	Promotion_Bonus500();
}

void CGameMgr::Promotion_Bonus500()
{
	if(m_cGameInfo.m_lChannel_idx==__CONST_::CHANNEL_FREE) return;
	int nTotal=GetUISize();
	int nRandom=0;
	bool bBonus=true;
	long long llBunumMoney=0;
	if(3>GetPlayingCount()) return;
	for(int i=0; i<nTotal; i++){
		UserInfo & ui=GetUI(i);
		if(ui.m_lUSN==-1) continue;
		if(ui.m_lUserState==USERSTATE_WAITING) continue;
		if(ui.m_lCLevel>5) continue;
		Money & money=GetMoney(ui.m_nIndex);
		RCUser* pUser=FindUser(ui.m_lUSN);
		if(NULL==pUser) continue;
		if(money.m_llCallHabMoney <= m_cRCRoomData.m_option.m_llGameAnteMoney) continue;
		bBonus=true;
		switch(money.m_lBetState){
		case RANK_FOUROFAKIND: bBonus=false; break;
		case RANK_STRAIGHTFLUSH: bBonus=false; break;
		case RANK_ROYALSTRAIGHTFLUSH: bBonus=false; break;
		}
		if(false==bBonus) continue;
		llBunumMoney=0;
		if((10==pUser->m_nReserve01)||(20==pUser->m_nReserve01)||(30==pUser->m_nReserve01)||(40==pUser->m_nReserve01)||(50==pUser->m_nReserve01)){
			nRandom=PersentSumMakeRandomValue(6000, 2500, 1000, 500, -1);
			switch(ui.m_lCLevel){
			case 0:
				{
					switch(nRandom){
					case 0: llBunumMoney=5*UK; break;
					case 1: llBunumMoney=10*UK; break;
					case 2: llBunumMoney=20*UK; break;
					case 3: llBunumMoney=40*UK; break;
					}
				}
				break;
			case 1:
				{
					switch(nRandom){
					case 0: llBunumMoney=10*UK; break;
					case 1: llBunumMoney=20*UK; break;
					case 2: llBunumMoney=40*UK; break;
					case 3: llBunumMoney=80*UK; break;
					}
				}
				break;
			case 2:
				{
					switch(nRandom){
					case 0: llBunumMoney=20*UK; break;
					case 1: llBunumMoney=40*UK; break;
					case 2: llBunumMoney=80*UK; break;
					case 3: llBunumMoney=160*UK; break;
					}
				}
				break;
			case 3:
				{
					switch(nRandom){
					case 0: llBunumMoney=40*UK; break;
					case 1: llBunumMoney=80*UK; break;
					case 2: llBunumMoney=160*UK; break;
					case 3: llBunumMoney=320*UK; break;
					}
				}
				break;
			//case 4:
			//	{
			//		switch(nRandom){
			//		case 0: llBunumMoney=250*UK; break;
			//		case 1: llBunumMoney=750*UK; break;
			//		case 2: llBunumMoney=1500*UK; break;
			//		case 3: llBunumMoney=3000*UK; break;
			//		}
			//	}
			//	break;
			//case 5:
			//	{
			//		switch(nRandom){
			//		case 0: llBunumMoney=600*UK; break;
			//		case 1: llBunumMoney=1200*UK; break;
			//		case 2: llBunumMoney=2400*UK; break;
			//		case 3: llBunumMoney=4800*UK; break;
			//		}
			//	}
			//	break;
			}
		}
		if(0<llBunumMoney){
			if(true==DB_Query_UpdateMoney(ui.m_lUSN, llBunumMoney)){
				//long long llCMoney=money.m_llCMoney;
				//pUser->m_llCMoney=money.m_llCMoney=llCMoney+llBunumMoney;
				MsgSC_Bonus msg;
				msg.m_llBonus=llBunumMoney;
				//PayloadSC pld(PayloadSC::msgBonus_Tag, msg);
				//SendToUser(ui.m_lUSN, pld);
				SendToUser(ui.m_lUSN, GLAnsGameProtocol_Type_bonus, &msg);
			}
		}
	}

}

#endif
