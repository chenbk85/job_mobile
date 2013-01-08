// GameInfo.h: interface for the CGameInfo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GameData_H__
#define __GameData_H__
#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

//#include "../GameCommon.h"

#include  "GameInfo.h"
#include "../util/FileLog.h"
#include "../util/GRCUtil.h"

#include "../../Protocol Buffers/Poker/AdlGameRoom.h"
#include "../../Protocol Buffers/Poker/AdlGame_Poker.h"
#include "../../Protocol Buffers/Poker/AdlGameCommon.h"
#include "../include/xdef.h"

using namespace std;
using namespace adl;

//=ä�� �뷱�� 20100323
namespace	__CONST_
{
	enum{
		TWOUSER_NUM=2,
		LEVEL_MAX=10,
		ANTEMONEY_MAX=5,
	};

	enum CHANNEL_TYPE_NEWSUDDA {
		CHANNEL_FREE=0,
		CHANNEL_1=1,
		CHANNEL_2=2,
		CHANNEL_3=3,
		CHANNEL_4=4,
		CHANNEL_99=99,
		CHANNEL_NUMBER_MAX=5,
	};

	const __int64 UsedMoney[CHANNEL_NUMBER_MAX][2]={	// ���� ���� �����Ӵ�
		{500*MAN,		MMAX},
		{500*MAN,		MMAX},
		{50*UK,			MMAX},
		{500*UK,		MMAX},
		{1000*UK,		MMAX},
	};

	const __int64 PurgeMoney[CHANNEL_NUMBER_MAX]={	//���� �Ӵϱ�
		1*MAN,
		1*MAN,
		1*MAN,
		2*MAN,
		20*MAN,
	};

	const __int64 g_llAnteMoneyTable[CHANNEL_NUMBER_MAX][ANTEMONEY_MAX]={ //�氪
		{10,		10,			10,			10,			10},
		{10,		10,			10,			10,			10},
		{1000,		1000,		1000,		1000,		1000},
		{5*MAN,		5*MAN,		5*MAN,		5*MAN,		5*MAN},
		{50*MAN,	50*MAN,		50*MAN,		50*MAN,		50*MAN},
	};
	const string channelNameString[CHANNEL_NUMBER_MAX]={"����ä��", "10ä��", "1õä��", "10��ä��", "500��ä��"};

	const string cnt_sLevel[LEVEL_MAX]={"���̽�","�����","�����","Ʈ����","��Ʈ����Ʈ","�÷���","Ǯ�Ͽ콺","��ĿƮ","��Ƽ��","��Ƽ��"};
								          //0	  1	      2	       3	     4	         5		  6		    7	     8         9
	inline bool	Is_UsableChannelidx( long channel_idx ){
		if( CHANNEL_1>channel_idx ) return false;
		if( CHANNEL_NUMBER_MAX <= channel_idx ) return false;
		return true;
	}
	inline string	Get_LevelName( int clevel ){ 
		Range_Check<int>( clevel, 0, LEVEL_MAX-1 );
		return cnt_sLevel[ clevel ]; 
	}
	inline bool	Verify_Entry_UserGrade( long cLevel , long channel_idx ){
		if((CHANNEL_FREE==channel_idx)||(CHANNEL_99==channel_idx)){
			return true;
		}
		if(CHANNEL_1==channel_idx){
			return (2>=cLevel); //���̽�
		}
		if(CHANNEL_2==channel_idx){
			return ((1<=cLevel)&&(3>=cLevel)); //�����~Ʈ����
		}
		if(CHANNEL_3==channel_idx){
			return ((3<=cLevel)&&(5>=cLevel)); //Ʈ����~�÷���
		}
		if(CHANNEL_4==channel_idx){
			return ((4<=cLevel)&&(9>=cLevel)); //��Ʈ����Ʈ~��ĿƮ
		}
		return false;
	}
	inline __int64	Get_BasicAnte(long channel_idx,  long option, long lMaxUserCnt=0){
		if(TWOUSER_NUM==lMaxUserCnt) return 1*UK;
		if( false==Is_UsableChannelidx( channel_idx ) )
			channel_idx=CHANNEL_FREE;
		Range_Check<long>( option, 0, ANTEMONEY_MAX-1 );
		if( 0==g_llAnteMoneyTable[channel_idx][option] ){
			return g_llAnteMoneyTable[channel_idx][0];
		}
		return g_llAnteMoneyTable[channel_idx][option];
	}
	inline long	Get_AnteToOption(long channel_idx, __int64 llAnteMoney){
		int nAnteMoney=0;
		for(int i=0; i<ANTEMONEY_MAX; i++){
			if( g_llAnteMoneyTable[channel_idx][i]==llAnteMoney ){
				nAnteMoney=i;
			}
		}
		return nAnteMoney;
	}
	// �氪�� �ο����� ���	
	inline long long Get_Ante_Multi(long channel_idx, long long llAnt, long nPlayerCnt, long lMaxPlayer=6 ){
		switch(channel_idx){
		case CHANNEL_1:
			{
				switch(nPlayerCnt){
				case 2: return 1*MAN;
				case 3: return 1000;
				case 4: return 100;
				case 5: return llAnt;
				}
			}
			break;
		case CHANNEL_2:
			{
				switch(nPlayerCnt){
				case 2: return 100*MAN;
				case 3: return 10*MAN;
				case 4: return 1*MAN;
				case 5: return llAnt;
				}
			}
			break;
		case CHANNEL_3:
			{
				switch(nPlayerCnt){
				case 2: return 5000*MAN;
				case 3: return 500*MAN;
				case 4: return 50*MAN;
				case 5: return llAnt;
				}
			}
			break;
		case CHANNEL_4:
			{
				switch(nPlayerCnt){
				case 2: return 5*UK;
				case 3: return 5000*MAN;
				case 4: return 500*MAN;
				case 5: return llAnt;
				}
			}
			break;
		case CHANNEL_FREE:
		case CHANNEL_99:
		default:
			{
				return llAnt;
			}
			break;
		}
		return llAnt;
	}
	inline __int64	Get_EXT_Money( ItemList &UserItemList ){
#ifndef _IPHONE
		return 9999999999999999;
#else
		return 9999999999999999ll;
#endif
	}
	inline __int64	Get_UsedMoney(long channel_idx,  long MinMaxUsedMoney_idx){
		Range_Check<long>( channel_idx, CHANNEL_FREE, CHANNEL_NUMBER_MAX-1 );
		Range_Check<long>( MinMaxUsedMoney_idx, 0, 1 );
		return UsedMoney[channel_idx][MinMaxUsedMoney_idx];
	}
	inline bool	Do_U_Have_CashBox( ItemList &UserItemList ){
		return UserItemList.IsItem( ITEM_FIRSTGOLD ) || UserItemList.IsItem( ITEM_FIRSTCLUB ) || UserItemList.IsItem( ITEM_MINICASHBOX ) || UserItemList.IsItem( ITEM_MINICASHBOX_PRACTICE ) || UserItemList.IsItem( ITEM_MINICASHBOX_DISCOUNT );
	}
	// ������ 3%
	inline long Get_Dealer_Tax_Percentage( ItemList &UserItemList, long channel_idx, int nRealBet=0){
		// NORMAL USER  3.0%
		// FC USER		2.5%
		// FG USER		2.0%
		// CHANNEL_REALBET		1.0%
		if( UserItemList.IsItem( ITEM_FIRSTGOLD ) ) return 20;
		else if( UserItemList.IsItem( ITEM_FIRSTCLUB ) ) return 25;
		return 30;
	}

	inline int	Get_ItemType( ItemList & UserItemList)
	{
		if( UserItemList.IsItem( ITEM_FIRSTGOLD ) ) return 4;
		else if( UserItemList.IsItem( ITEM_FIRSTCLUB ) ) return 3;
		else if( UserItemList.IsItem( ITEM_FIRSTDREAM ) ) return 2;		
		else if( UserItemList.IsItem( ITEM_FIRSTLOVE ) ) return 1;
		return 0;
	}
};


class CGameData
{
public:
	CPurge m_cPurge;
	vector<CPurgeMoney> m_vtCPurgeMoney;
	CPoliceNotify m_cPoliceNotify;
	VecUSN	m_vtObserveUSN;
	VecUSN	m_vtEraseUSN;
	CGameInfo m_cGameInfo;
	CFileLog m_cFileLog;
	CGRCUtil m_CGRCUtil;
	CBetLog m_cBetLog;
	RCRoomData m_cRCRoomData;
	RCUserData m_RCUserData;
public:
	CGameData(void){ InitGameData(); }
	virtual ~CGameData(void){ FreeGameData(); }
	void InitGameData(void){ m_vtObserveUSN.clear(); m_vtEraseUSN.clear(); m_cFileLog.Set("Poker"); }
	void FreeGameData(void){ }
public:
	RCRoomData& GetData(void){ return m_cRCRoomData; }
	RCUserData& GetRCUT(void){ return m_RCUserData; }
	void SwitchState(long lState){
		if(m_cRCRoomData.m_lState==lState) return;
		m_cRCRoomData.m_lState=lState;
	}
public:
	// USERINFO
	UITable& GetUITable(){ return m_cRCRoomData.m_tblUI; }
	int GetUISize(){ return m_cRCRoomData.GetUISize(); }
	UserInfo& GetUI(int nIndex){ ASSERT(_inrange(0, nIndex, m_cRCRoomData.GetUISize())); return m_cRCRoomData.GetUI(nIndex); }
	//	const UserInfo& GetUI(int nIndex) const { ASSERT(_inrange(0, nIndex, m_cRCRoomData.GetUISize())); return m_cRCRoomData.GetUI(nIndex); }

	// CARDINFO
	CardTable& GetCardTable(){ return m_cRCRoomData.m_tblCard; }
	int GetCardSize(){ return m_cRCRoomData.GetCardsSize(); }
	Cards & GetCards(int idx){ return m_cRCRoomData.GetCards(idx); }
	const Cards & GetCards(int idx) const { return m_cRCRoomData.GetCards(idx); }

	// MONEYINFO
	MoneyTable & GetMoneyTable(){ return m_cRCRoomData.m_tblMoney; }
	int GetMoneySize(){ return m_cRCRoomData.GetMoneySize(); }
	Money & GetMoney(int idx){ return m_cRCRoomData.GetMoney(idx); }
	const Money & GetMoney(int idx) const { return m_cRCRoomData.GetMoney(idx); }
	int GetUserCnt(void){ return m_cRCRoomData.GetUserCnt(); }
	__int64 GetAvgMoney(void){ return m_cRCRoomData.GetAvgMoney(); }


	BettingMsg & GetBettingMsg(int idx){ return m_cRCRoomData.GetBettingMsg(idx); }
	int GetBettingMsgSize(void){ return m_cRCRoomData.GetBettingMsgSize(); }
	const BettingMsg & GetBettingMsg(int idx) const {return m_cRCRoomData.GetBettingMsg(idx);}
public:
	void AddUser(RCUser& ud){ m_RCUserData.AddUser(ud); }
	void RemoveUser(long lUSN){ m_RCUserData.RemoveUser(lUSN); }
	RCUser* FindUser(long lUSN){ return m_RCUserData.FindUser(lUSN); }
	int	GetIndex(long lUSN){ return m_RCUserData.GetIndex(lUSN); }
	int	GetTotalUser(){ return m_RCUserData.GetTotalUser(); }
	bool ExistUser(){ return m_RCUserData.ExistUser(); }
};


#endif // !defined(AFX_GAMEINFO_H__69913046_B5B6_4052_B350_7C961115A68C__INCLUDED_)
