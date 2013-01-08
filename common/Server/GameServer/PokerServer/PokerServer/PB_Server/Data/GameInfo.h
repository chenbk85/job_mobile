// GameInfo.h: interface for the CGameInfo class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __GameInfo_H__
#define __GameInfo_H__
#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

//#include "../../Protocol Buffers/Poker/Game_Poker.pb.h"
#include "../../protobuf/gameLogic.pb.h"
#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

#include <vector>

#include "PK_header.h"

#include "../include/xtmpl.h"
#include "../util/CTPairVector.h"
#include "../util/PublicFunc.h"

//#include "../GameCommon.h"



using namespace std;
//using namespace Game_Poker;
using namespace adl;

enum UserState
{
	USER_PLAY,
	USER_DIE,
	USER_EXIT,
};

class CHabMoney
{
public:
	CHabMoney(){ Clear(); }
	~CHabMoney(){}
public:
	void Clear(){
		vtUSN.clear();
		llHabMoney=0;
	}
public:
	vector<long> vtUSN;
	__int64 llHabMoney;
};

class CDivisionMoney
{
public:
	CDivisionMoney(){}
	~CDivisionMoney(){}
public:
	void ADDMoney(long lUSN, __int64 llCallHabMoney, long lState, string sNickName){
		bool bTemp=false;
		//vector<UserMoney> tmpvt;
		//ForEachElmt(tmpvt, m_vtUser, ia, ib){
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_lusn()==lUSN){
				bTemp=true;
				(*ia).set_m_llcallhabmoney(llCallHabMoney);
				(*ia).set_m_llmoney(llCallHabMoney);
				(*ia).set_m_lstate(lState);
				(*ia).set_m_snickname(sNickName);
			}
		}
		if(bTemp==false){
			UserMoney user;
			user.Clear();
			user.set_m_lusn(lUSN);
			user.set_m_llcallhabmoney(llCallHabMoney);
			user.set_m_llmoney(llCallHabMoney);
			user.set_m_lstate(lState);
			user.set_m_snickname(sNickName);
			m_vtUser.push_back(user);
		}
	}
	void DecreaseMoney(long lUSN, __int64 llDecreaseMoney, long lState){
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_lusn()==lUSN){
				if((*ia).m_llcallhabmoney()<llDecreaseMoney){
					(*ia).set_m_llcallhabmoney(0);
					(*ia).set_m_llmoney(0);
				}
				else{
					(*ia).set_m_llcallhabmoney((*ia).m_llcallhabmoney()-llDecreaseMoney);
					(*ia).set_m_llmoney((*ia).m_llmoney()-llDecreaseMoney);
				}
				(*ia).set_m_lstate(lState);
			}
		}
	}
	bool IsDieExit(vector<long> vtUSN){
		int nCnt=0;
		int nSize=vtUSN.size();
		for(int i=0; i<nSize; i++){
			ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
				if((*ia).m_lusn()==vtUSN[i]){
					if((*ia).m_lstate()==USER_DIE || (*ia).m_lstate()==USER_EXIT)
						nCnt++;
				}
			}
		}
		if(nCnt==nSize)
			return true;
		return false;
	}
	int GetStatePlayCnt(vector<long> vtUSN){
		int nCnt=0;
		int nSize=vtUSN.size();
		for(int i=0; i<nSize; i++){
			ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
				if((*ia).m_lusn()==vtUSN[i]){
					if((*ia).m_lstate()==USER_PLAY)
						nCnt++;
				}
			}
		}
		return nCnt;
	}
	bool IsStatePlay(long lUSN){
		bool bTemp=false;
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_lusn()==lUSN){
				if((*ia).m_lstate()==USER_PLAY)
					bTemp=true;
			}
		}
		return bTemp;
	}
	__int64 GetSmallMoney(){
		__int64 lTemp=0;
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_llmoney()!=0){
				if(lTemp==0 || (*ia).m_llmoney()<lTemp){
					lTemp=(*ia).m_llmoney();
				}
			}
		}
		return lTemp;
	}
	void Init(int nUserSize=MAX_PLAYER_COUNT){
		m_cvHabMoney.clear();
		for(int i=0; i<nUserSize; ++i){
			CHabMoney cHab;
			cHab.Clear();
			m_cvHabMoney.push_back(cHab);
		}
	}
	void SetRePlay(){
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			(*ia).set_m_llmoney((*ia).m_llcallhabmoney());
		}
		m_llHabRematchMoney=0;
	}
	void Clear(){
		m_vtUser.clear();
		m_llHabRematchMoney=0;
		for(int i=0; i<(int)m_cvHabMoney.size(); i++){
			m_cvHabMoney[i].Clear();
		}
	}
	__int64 GetTakeMoney(long lUSN){
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_lusn()==lUSN){
				return (*ia).m_lltakemoney();
			}
		}
		return 0;
	}
	__int64 GetCallHabMoney(long lUSN){
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_lusn()==lUSN){
				return (*ia).m_llcallhabmoney();
			}
		}
		return 0;
	}
	string GetDealerTax(long lUSN){
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_lusn()==lUSN){
				return (*ia).m_sdealertax();
			}
		}

		return "";
	}
	__int64 GetDealMoney(long lUSN){
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			if((*ia).m_lusn()==lUSN){
				return (*ia).m_lldealmoney();
			}
		}
		return 0;
	}
	__int64 GetDealMoneyHab(){
		__int64 lHab=0;
		ForEachElmt(vector<UserMoney>, m_vtUser, ia, ib){
			lHab+=(*ia).m_lldealmoney();
		}
		return lHab;
	}
public:
	vector<UserMoney> m_vtUser;
	vector<CHabMoney> m_cvHabMoney;
	__int64 m_llHabRematchMoney;
};

class CPurgeMoney
{
public:
	CPurgeMoney(){ Clear(); }
	virtual ~CPurgeMoney(){}
public:
	void Clear(){
		lUSN=-1;
		llPurgeMoney=0;
	}
public:
	long lUSN;
	__int64 llPurgeMoney;
};

class CIp
{
public:
	CIp(){ Clear(); }
	virtual ~CIp(){};
public:
	void Clear(){
		lClientIp=0;
		lGateWayIp=0;
		sClientMacAddr="";
	}
public:
	long lClientIp;
	long lGateWayIp;
	string sClientMacAddr;
};

class CPurge
{
public:
	CPurge(){ Clear(); }
	virtual ~CPurge(){};
public:
	bool IsEmpty(){ return vtPurgeList.empty(); }
	void Clear(){
		nRoomPurgeCnt=0;
		vtPurgeList.clear();
	}
	bool IsPurge(long lPurgeUSN){
		int nTotal=(int)vtPurgeList.size();
		for(int i=0; i<nTotal; i++){
			if(vtPurgeList[i]==lPurgeUSN){
				return true;
			}
		}
		return false;
		//ForEachElmt(VecUSN, vtPurgeList, i, j){
		//	if((*i)==lPurgeUSN) return true;
		//}
		//return false;
	}
	void PurgeErase(long lPurgeUSN){
		VecUSN::iterator i,j;
		ForEachElmt(VecUSN, vtPurgeList, i, j){
			if((*i)==lPurgeUSN) break;
		}
		if(i==vtPurgeList.end()) return ;
		vtPurgeList.erase(i);
	}
	bool AddPurge(long lPurgeUSN){
		if(!IsPurge(lPurgeUSN)){
			vtPurgeList.push_back(lPurgeUSN);
			return true;
		}
		return false;
	}
public:
	int nRoomPurgeCnt;
	VecUSN vtPurgeList;
};


///////////////////////////////////////////////////////////////////////////////////
// 폴리스 방제 신고 변경
class CPoliceNotify
{
public:
	CPoliceNotify(){ Clear(); }
	virtual ~CPoliceNotify(){};
public:
	void Clear(){ m_bPoliceNotify=false; }
	void SetPoliceNotify(bool bPolice){ m_bPoliceNotify=bPolice; }
	bool GetPoliceNotify(){ return m_bPoliceNotify; }
private:
	bool m_bPoliceNotify;
};


class CGameInfo
{
public:
	CGameInfo(void){ m_lChannel_idx=0; InitGameInfo(); }
	virtual ~CGameInfo(void){ FreeGameInfo(); }
	void ClearGameInfo(void);
	void InitGameInfo(void);
	void Init(int nUserSize=MAX_PLAYER_COUNT, int nCardSize=MAX_PLAYER_COUNT);
	//void AddUser();
	//void AddRemoveUser(int nSize);
	//void RemoveUser(int idx);
	void ClearResultOrder(void);
	void ClearStartMoney(void);
	void ClearGiveMoney(int nPlayerCnt);
	void FreeGameInfo(void){ }
public:
	void SetPreBetType(long lBetType);
	void AddPoolMoney(__int64 PoolMoney){ m_llPoolMoney+=PoolMoney; }
	__int64 GetGiveMoneyHab();
	__int64 GetDealMoney(long lUSN);
	void Clear49Replay(void);
	void SetGameEnd(void){ m_nPlayCount++; m_bStartPrev=false; }
	bool IsStartPrev(void){
#ifdef _DEBUG
		return true;
#endif
		return (0<m_nPlayCount) && ( 0==m_nPlayCount%3 );
	}
public:
	string m_sGameMasterTime;// 운영자 호출 시간
	string m_sMakeRoomTime;
	long m_lCreateRoomOwner;
	long m_lChannel_idx;
	long m_lPreBetType;
	long m_lWantBetType;
	long m_lBetBtnType;
	int m_nBetAddTime;
	long m_lBetTurn;
	long m_lOwnerUSN;
	long m_lBossUSN;
	long m_lBetUSN;
	long m_lRoomId;
	DWORD m_dwStartTimer;
	__int64 m_llGameData;
	__int64 m_llPoolMoney;
	__int64 m_llPrevBetMoney;
	__int64 m_llMaxBetMoney;
	__int64 m_llJackpotMoney;
	__int64 m_llRematchAddMoney;
	long m_lDealtCardCount;
	long m_lCardsDealt;
	long m_lBetCount;
	long m_lCutCount;

	bool m_bGiveUp;
	bool m_bStart;
	bool m_b49Rematch;
	bool m_bJoinRematch;
	bool m_bBetUserMoney;
	int m_nRuleIdx;
	int m_nOldRuleIdx;
	int m_nPlayCount;
	bool m_bStartReq;
	bool m_bStartPrev;
	string m_sGameDate;
	vector<long> m_vlTimerDie;
	CDivisionMoney m_CDivisionMoney;
	vector<int> m_vtWin;
	vector<__int64> m_vllGiveMoney;
	vector<long> m_vResultOrder;
	vector<int>	m_nBestAssa;
	vector<__int64> m_vllStartMoney;
	vector<int> m_vJokbo;
	vector<int> m_vtWinIndex;
	CTPairVector<long, tHyperInt> m_cvtHyperInt_Level;
	CTPairVector<long, int> m_cvtJoin;
public:
	void SortHyperInt(bool bAseOrDes=true);
	static unsigned __int64 GetHyperInt(CTPairVector<long, tHyperInt>* pVoid, int nArray);
	static void SwapHyperInt(CTPairVector<long, tHyperInt>* pVoid, int nSwap1, int nSwap2);
public:
	int m_nRealDealer;
	bool m_bEnableChannelDeal;
};


#endif 
