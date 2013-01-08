#ifndef __Common_H__
#define __Common_H__
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _NO_XLIB
#define _XADL

using namespace std;

#include "xUtil.h"
#include "xADLBER.h"

#include "AdlGameCommon.h"
#include "AdlGameCommon_b.h"
#include "AdlGameUserBase.h"
#include "AdlGameUserBase_b.h"
#if defined(_Sudda)
#include "AdlGameUser_Sudda.h"
#include "AdlGameUser_Sudda_b.h"
#include "AdlGameRoom.h"
#include "AdlGameRoom_b.h"
#include "AdlGame_Sudda.h"
#include "AdlGame_Sudda_b.h"
#elif defined(_Poker)
#include "AdlGameUser_Poker.h"
#include "AdlGameUser_Poker_b.h"
#include "AdlGameRoom.h"
#include "AdlGameRoom_b.h"
#include "AdlGame_Poker.h"
#include "AdlGame_Poker_b.h"
#else
#include "AdlGameUser.h"
#include "AdlGameUser_b.h"
#include "AdlGameRoom.h"
#include "AdlGameRoom_b.h"
#include "AdlGame.h"
#include "AdlGame_b.h"
#endif



//#include "AdlSGSCli.h"
//#include "AdlSGSCli_b.h"
//#include "AdlSGSCommon.h"
//#include "AdlSGSCommon_b.h"


const long g_lSSN = 25;  //섯다
const int g_nVersion = 1234;//1256;

const int MAX_CARD_ARRAY = 8; // 전체 게임을 통틀어 최대 가지게 되는 카드 장 수
const int MAX_CARD_COUNT = 5;
const int TOTAL_CARDS = 40;
const int NUM_MADE = 22;
const int MAX_CARDCHECK_COUNT = 5;
const int MAX_CHANNEL = 10;
//const int Seat[5][5] = {{0, 1, 2, 3, 4}, {1, 2, 3, 4, 0}, {2, 3, 4, 0, 1}, {3, 4, 0, 1, 2}, {4, 0, 1, 2, 3}};
// CHANNEL_BEGIN에 해당하는 값이 항상 모든 배열의 끝에 있어야 한다.

//철이가 강퇴 카운트
//const int MAX_ALLIN = 3;//수호천사
//const int PURGE_INCRAESE[LIMIT_PURGECNT] = {1, 2, 5, 10, 20}; 
//철이가 강퇴 카운트

//수호천사
const int cnt_MAX_ALLIN = 4;	// 4회로 변경 : 섯다 수호군

enum _NEWSUDDA_GAMERULE{
	GAMERULE_SUDDA_2 = 0,
	GAMERULE_SUDDA_3 = 1,
	GAMERULE_DORIG_9 = 2,
};


//=채널 밸런싱 20100323
namespace	__CONST_
{
	enum{
		TWOUSER_NUM = 2,
		LEVEL_MAX = 9,
		ANTEMONEY_MAX = 5,
	};

	enum CHANNEL_TYPE_NEWSUDDA {
		CHANNEL_FREE = 0,			// 자유  = 자유
		CHANNEL_BEGIN = 1,		    // 입문  = 1천/3천
		CHANNEL_HASOO = 2,			// 하수  = 1만/3만
		CHANNEL_MIDDLE = 3,			// 중수  = 10만/30만
		CHANNEL_PRO = 4,			// 프로(고수) = 1백만
		CHANNEL_MASTERS = 5,		// 마스터즈(타짜) = 3백만/1억
		CHANNEL_REALBET = 6,		// 리얼 = 장땡
		CHANNEL_NUMBER_MAX = 7,
	};

	const int RaiseCount[CHANNEL_NUMBER_MAX][5] = { // 베팅 횟수
		{2,2,2,2,2}, // 자유(자유)
		{2,2,2,2,2}, // 입문  = 1천/3천
		{2,2,2,2,2}, // 하수  = 1만/3만
		{2,2,2,2,2}, // 중수  = 10만/30만
		{2,2,2,2,2}, // 프로(고수) = 1백만
		{2,2,2,2,2}, // 마스터즈(타짜) = 3백만/1억
		{1,3,3,3,3}, // 리얼 = 장땡
	};

	const __int64 UsedMoney[CHANNEL_NUMBER_MAX][2] = {	// 입장 가능 소지머니
		{1000,			MMAX},			// 자유(자유)
		{1000,			330*MAN},		// 입문  = 1천/3천
		{80*MAN,		3300*MAN},		// 하수  = 1만/3만
		{800*MAN,		3*UK+3000*MAN},	// 중수  = 10만/30만
		{2500*MAN,		10*UK},			// 프로(고수) = 1백만
		{8000*MAN,		MMAX},			// 마스터즈(타짜) = 3백만/1억
		{3*UK,			MMAX},			// 리얼 = 장땡
	};

	const __int64 MinMoney[CHANNEL_NUMBER_MAX] = {	// 채널 최소 유지 금액
		1,			// 자유(자유)
		1,		    // 입문  = 1천/3천
		80*MAN,		// 하수  = 1만/3만
		800*MAN,	// 중수  = 10만/30만
		2500*MAN,	// 프로(고수) = 1백만
		8000*MAN,	// 마스터즈(타짜) = 3백만/1억
		3*UK,		// 리얼 = 장땡
	};

	const __int64 EntryMoney[CHANNEL_NUMBER_MAX][ANTEMONEY_MAX] = {	// 각채널별 입장 제한 금액
		{1000,			1000,			1000,			1000,			1000},		// 자유(자유)
		{1000,			3000,			3000,			3000,			3000},		// 입문  = 1천/3천
		{1*MAN,			1*MAN,			1*MAN,			1*MAN,			1*MAN},		// 하수  = 1만/3만
		{10*MAN,		10*MAN,			10*MAN,			10*MAN,			10*MAN},	// 중수  = 10만/30만
		{100*MAN,		100*MAN,		100*MAN,		100*MAN,		100*MAN},	// 프로(고수) = 1백만
		{300*MAN,		10*UK,			20*UK,			50*UK,			100*UK},	// 마스터즈(타짜) = 3백만/1억
		{500*MAN,		20*UK,			50*UK,			100*UK,			300*UK},	// 리얼 = 장땡
	};
	const __int64 PurgeMoney[CHANNEL_NUMBER_MAX] = {	//강퇴 머니군
		1*MAN,		// 자유
		1*MAN,		// 입문  = 1천/3천
		1*MAN,		// 하수  = 1만/3만
		2*MAN,		// 중수  = 10만/30만
		20*MAN,		// 프로 = 1백만
		50*MAN,		// 마스터즈 = 3백만/1억
		50*MAN,		// 리얼 = 장땡
	};
	const __int64 LevelMoney[LEVEL_MAX][2] = {
		{0,				30*MAN},	// 입문
		{30*MAN,		100*MAN},	// 초보
		{100*MAN,		300*MAN},	// 하수
		{300*MAN,		1000*MAN},	// 중수
		{1000*MAN,		3000*MAN},	// 고수
		{3000*MAN,		1*UK},		// 선수
		{1*UK,			3*UK},		// 타짜
		{3*UK,			10*UK},		// 영웅
		{10*UK,			MMAX},		// 제왕
	};

	const __int64 g_llAnteMoneyTable[CHANNEL_NUMBER_MAX][ANTEMONEY_MAX] = { //삥값
		{1000,		1000,		1000,		1000,		1000},			// 자유
		{1000,		3000,		3000,		3000,		3000},			// 입문  = 1천/3천
		{1*MAN,		3*MAN,		3*MAN,		3*MAN,		3*MAN},			// 하수  = 1만/3만
		{10*MAN,	30*MAN,		30*MAN,		30*MAN,		30*MAN},		// 중수  = 10만/30만
		{100*MAN,	100*MAN,	100*MAN,	100*MAN,	100*MAN},		// 프로(고수) = 1백만
		{300*MAN,	1000*MAN,	3000*MAN,	1*UK,		1*UK},	        // 마스터즈(타짜) = 3백만/1억
		{500*MAN,	1000*MAN,	3000*MAN,	5000*MAN,	5000*MAN},	    // 리얼 = 장땡
	};
	const string channelNameString[CHANNEL_NUMBER_MAX] = {"자유채널", "1천,3천 채널", "1만,3만 채널", "10만,30만 채널", "1백 만 채널", "3백만~1억 채널", "장땡채널"};

	const string cnt_sLevel[LEVEL_MAX] = {"입문","초보","하수","중수","고수","선수","타짜","영웅","제왕"};
								          //0	  1	     2	    3	   4	  5		 6		7	   8
	const string MadeNum[NUM_MADE] ={"118", "127", "136", "145", "019",
									 "226", "235", "028", "334", "037",
									 "389", "244", "046", "479", "055",
									 "569", "578", "668", "677", "488",
									 "299", "000"};

	const string MadeName[NUM_MADE] ={"콩콩팔", "삐리칠", "물삼육", "빽새오", "삥구장",
									  "니니육", "이삼오", "이판장", "심심새", "삼칠장",
									  "삼빡구", "살살이", "사륙장", "사칠구", "꼬꼬장",
									  "오륙구", "오리발", "쭉쭉팔", "철철육", "팍팍싸",
									  "구구리", "장장장"};

	inline bool	Is_UsableChannelidx( long channel_idx ){
		if( CHANNEL_FREE > channel_idx ) return false;
		if( CHANNEL_NUMBER_MAX <= channel_idx ) return false;
		return true;
	}

	inline long	GetChannelIndex( long channel_idx ){
		switch( channel_idx ){
		case CHANNEL_BEGIN:
		case CHANNEL_HASOO:
		case CHANNEL_MIDDLE:	
		case CHANNEL_PRO:
		case CHANNEL_MASTERS:
		case CHANNEL_FREE:	
		case CHANNEL_REALBET:	
			return channel_idx;
		}
		return CHANNEL_FREE;
	}
	inline char* Get_ProjectName( long lSSN ){
		switch(lSSN){
		case 26:	return "G9ddang";
		case 25:	return "Sudda";
		default:
			break;
		}
		return NULL;
	}
	inline string	Get_LevelName( int clevel ){ 
		Range_Check<int>( clevel, 0, LEVEL_MAX-1 );
		return cnt_sLevel[ clevel ]; 
	}
	inline int		GetRaiseCount( int channel_idx, int nDealCount ){
		if( false == Is_UsableChannelidx( channel_idx ) )
			channel_idx = CHANNEL_FREE;
		return RaiseCount[channel_idx][nDealCount];
	}
	inline __int64	Get_LevelMoney( int cLevel, int MinLevelMoney_idx){
		Range_Check<int>( cLevel, 0, LEVEL_MAX-1 );
		Range_Check<int>( MinLevelMoney_idx, 0, 1 );
		return LevelMoney[cLevel][MinLevelMoney_idx];
	}
	inline string	Get_ChannelName( int	channel_idx ){
		return channelNameString[channel_idx];
	}
	inline bool	Verify_Entry_UserGrade( long cLevel , long channel_idx ){ //이용등급
		if(CHANNEL_FREE==channel_idx){
			return true;
		}
		if(CHANNEL_BEGIN==channel_idx){
			return (2>=cLevel); //"초보"~"하수"
		}
		if(CHANNEL_HASOO==channel_idx){
			return ((4>=cLevel)&&(2<=cLevel)); //"하수"~"고수"
		}
		if(CHANNEL_MIDDLE==channel_idx){
			return ((6>=cLevel)&&(4<=cLevel)); //"고수"~"타짜"
		}
		if(CHANNEL_PRO==channel_idx){
			return ((7>=cLevel)&&(5<=cLevel)); //"선수"~"영웅"
		}
		if(CHANNEL_MASTERS==channel_idx){
			return (6<=cLevel);  //"타짜"~"제왕"
		}
		if(CHANNEL_REALBET==channel_idx){
			return (7<=cLevel);  //"영웅"~"제왕"
		}		
		return false;
	}

	inline int	Verify_Entry_UserChannel( long cLevel ){
		switch(cLevel){
		case 0: return CHANNEL_BEGIN;
		case 1: return CHANNEL_BEGIN;
		case 2: return CHANNEL_HASOO;
		case 3: return CHANNEL_HASOO;
		case 4: return CHANNEL_MIDDLE;
		case 5: return CHANNEL_PRO;
		case 6: return CHANNEL_MASTERS;
		case 7: return CHANNEL_REALBET;
		case 8: return CHANNEL_REALBET;
		}
		return CHANNEL_FREE;
	}
	inline __int64	Get_BasicAnte(long channel_idx,  long option, long lMaxUserCnt=0){
		if(TWOUSER_NUM == lMaxUserCnt) return 1*UK;
		if( false == Is_UsableChannelidx( channel_idx ) )
			channel_idx = CHANNEL_FREE;
		Range_Check<long>( option, 0, ANTEMONEY_MAX-1 );
		if( 0 == g_llAnteMoneyTable[channel_idx][option] ){
			return g_llAnteMoneyTable[channel_idx][0];
		}
		return g_llAnteMoneyTable[channel_idx][option];
	}
	inline long	Get_AnteToOption(long channel_idx, __int64 llAnteMoney){
		int nAnteMoney = 0;
		for(int i=0; i<ANTEMONEY_MAX; i++){
			if( g_llAnteMoneyTable[channel_idx][i] == llAnteMoney ){
				nAnteMoney = i;
			}
		}
		return nAnteMoney;
	}
	// 삥값의 인원수별 배수	
	inline long	Get_Ante_Multi( long channel_idx, long nPlayerCnt, long lMaxPlayer=6 ){
		return 1;
	}
	inline __int64	Get_EXT_Money( ItemList &UserItemList ){
		if( UserItemList.IsItem( ITEM_FIRSTGOLD ) ) return 1*CHO;
		else if( UserItemList.IsItem( ITEM_FIRSTCLUB ) ) return 3000*UK;
		else return 1000*UK;
	}

	inline __int64	Get_MinMoney(long channel_idx){
		Range_Check<long>( channel_idx, CHANNEL_FREE, CHANNEL_NUMBER_MAX-1 );
		return MinMoney[channel_idx];
	}

	inline __int64	Get_UsedMoney(long channel_idx,  long MinMaxUsedMoney_idx){
		Range_Check<long>( channel_idx, CHANNEL_FREE, CHANNEL_NUMBER_MAX-1 );
		Range_Check<long>( MinMaxUsedMoney_idx, 0, 1 );
		return UsedMoney[channel_idx][MinMaxUsedMoney_idx];
	}

	inline __int64	Get_EntryMoney(long channel_idx,  long MinEntryMoney_idx){
		Range_Check<long>( channel_idx, CHANNEL_FREE, CHANNEL_NUMBER_MAX-1 );
		Range_Check<long>( MinEntryMoney_idx, 0, ANTEMONEY_MAX-1 );
		return EntryMoney[channel_idx][MinEntryMoney_idx];
	}
	inline bool	Do_U_Have_CashBox( ItemList &UserItemList ){
		return UserItemList.IsItem( ITEM_FIRSTGOLD ) || UserItemList.IsItem( ITEM_FIRSTCLUB ) || UserItemList.IsItem( ITEM_MINICASHBOX ) || UserItemList.IsItem( ITEM_MINICASHBOX_PRACTICE ) || UserItemList.IsItem( ITEM_MINICASHBOX_DISCOUNT );
	}
	// 딜러비 3%
	inline long Get_Dealer_Tax_Percentage( ItemList &UserItemList, long channel_idx, int nRealBet = 0){
		// NORMAL USER  3.0%
		// FC USER		2.5%
		// FG USER		2.0%
		// CHANNEL_REALBET		1.0%
		SYSTEMTIME st; 
		GetLocalTime(&st);
		if((st.wYear*10000)+(st.wMonth*100)+(st.wDay) < 20101026 ){
			if((((st.wHour*100)+(st.wMinute)>=2000) && ((st.wHour*100)+(st.wMinute)<=2400))
				||(((st.wHour*100)+(st.wMinute)>=0) && ((st.wHour*100)+(st.wMinute)<=259))){
				Range_Check<long>( channel_idx, CHANNEL_FREE, CHANNEL_NUMBER_MAX-1 );
				if(CHANNEL_REALBET == channel_idx) return 10;
			}
#if defined(_DEBUG) || defined(TEST_RELEASE)
			if(0!=nRealBet){
				if(((st.wHour*100)+(st.wMinute)>=nRealBet) && ((st.wHour*100)+(st.wMinute)<=(nRealBet+59))){
					if(CHANNEL_REALBET == channel_idx) return 10;
				}
			}
#endif
		}
		if( UserItemList.IsItem( ITEM_FIRSTGOLD ) ) return 20;
		else if( UserItemList.IsItem( ITEM_FIRSTCLUB ) ) return 25;
		return 30;
	}
	inline bool	Is_FirstRefillUser( ItemList &UserItemList ){
		SYSTEMTIME st; 
		GetLocalTime(&st);
		__int64 lCurrentTime = (st.wYear*10000000000) + (st.wMonth*100000000) + (st.wDay*1000000) + (st.wHour*10000) + (st.wMinute*100) + st.wSecond;
		ForEachElmt(list<Item>, UserItemList.m_lstItem, i, j){
			switch( i->GetFucnsrl() ){
			case ITEM_FIRSTGOLD:
			case ITEM_FIRSTCLUB:
			case ITEM_FIRSTDREAM:
			case ITEM_FIRSTLOVE:
			case ITEM_FIRSTMINI:
				if(i->GetEndTime() >= lCurrentTime)	return true;
				break;
			}
		}					
		return false;
	}

	inline int	Get_ItemType( ItemList & UserItemList)
	{
		if( UserItemList.IsItem( ITEM_FIRSTGOLD ) ) return 4;
		else if( UserItemList.IsItem( ITEM_FIRSTCLUB ) ) return 3;
		else if( UserItemList.IsItem( ITEM_FIRSTDREAM ) ) return 2;		
		else if( UserItemList.IsItem( ITEM_FIRSTLOVE ) ) return 1;
		return 0;
	}

	inline void	MakeString_Reject_PowerChannel( string &sTitle, string &sMsg ){
		sTitle = "[파워채널] 관전모드입니다.";
		sMsg = "고스톱 퍼스트클럽, 고스톱 퍼스트골드, 고스톱 파워채널 입장권\n이용 시에 게임참여가 가능합니다.";	
	}
	inline void	MakeString_Reject_GRADE(string &sTitle, string &sMsg, long lSSN, int now_chidx, int lclevel ){
		for( int i=1;i<CHANNEL_NUMBER_MAX;i++){
			if( Verify_Entry_UserGrade( lclevel, i ) ){				
				break;
			}
		}
		int canplay_chi = Verify_Entry_UserChannel(lclevel);
		sTitle = ::format( "[%s채널] 관전모드입니다.", Get_ChannelName( now_chidx ).c_str() );
		sMsg = ::format("%s채널로 이동하면 게임참여가 가능합니다.", Get_ChannelName( canplay_chi ).c_str() );
	}
	inline void	MakeString_Eject_Money( string &sTitle, string &sMsg, long lSSN, __int64 money_low, __int64 lCMoney ){
		string	smm_low = LongToStr( money_low, 2);
		sTitle = ::format("[%s이상 방]입니다.", smm_low.c_str() );
		/*
		else
		sTitle = ::format("[%s~%s 방] 관전모드입니다.", LongToStr( money_low, 2).c_str(), LongToStr( money_high, 2).c_str() );
		*/
		sMsg = ::format("선택하신 게임방은 소지머니가 %s이상이어야\n게임참여/관전이 가능합니다.", smm_low.c_str());
		sMsg += "\n게임에 참여하시려면 금고인출, 리필, 게임몰을 이용하세요.";
	}
	inline void	MakeString_Reject_Money( string &sTitle, string &sMsg, long lSSN, __int64 money_low, __int64 money_high, __int64 llCMoney ){
		string	smm_low = LongToStr( money_low, 2);
		string	smm_high = LongToStr( money_high, 2);
		if(MMAX == money_high){
			sTitle = ::format("[%s이상 방] 관전모드입니다.", smm_low.c_str() );
			sMsg = ::format("선택하신 게임방은 소지머니가 %s이상인 분들만 \n게임에 참여 할 수 있습니다.", smm_low.c_str() );
			sMsg += "\n게임에 참여하시려면 금고인출, 리필, 게임몰을 이용하세요.";
		}
		else{
			sTitle = ::format("[%s이상 방 %s미만 방] 관전모드입니다.", smm_low.c_str(), smm_high.c_str() );		
			sMsg = ::format("선택하신 게임방은 소지머니가 %s이상, %s 미만인 분들만 \n게임에 참여 할 수 있습니다.", smm_low.c_str(), smm_high.c_str() );
			sMsg += "\n게임에 참여하시려면 금고인출, 리필, 게임몰을 이용하세요.";
		}
	}
	inline void	MakeString_Reject_Money_2( string &sTitle, string &sMsg, long lSSN, __int64 money_low, __int64 money_high, __int64 llCMoney ){
		string	smm_low = LongToStr( money_low, 2);
		string	smm_high = LongToStr( money_high, 2);
		if(MMAX == money_high){
			sTitle = ::format("[%s이상 방] 관전모드입니다.", smm_low.c_str() );
			sMsg = ::format("선택하신 게임방은 소지머니가 %s이상인 분들만 \n게임에 참여 할 수 있습니다.", smm_low.c_str() );
		}
		else{
			sTitle = ::format("[%s이상 방 %s미만 방] 관전모드입니다.", smm_low.c_str(), smm_high.c_str() );		
			sMsg = ::format("선택하신 게임방은 소지머니가 %s이상, %s 미만인 분들만 \n게임에 참여 할 수 있습니다.", smm_low.c_str(), smm_high.c_str() );
		}
		if(llCMoney <= UsedMoney[CHANNEL_BEGIN][1])
			sMsg += "\n게임에 참여 하실려면 입문채널에 들어가세요.";
		else if(llCMoney <= UsedMoney[CHANNEL_HASOO][1])
			sMsg += "\n게임에 참여 하실려면 하수채널에 들어가세요.";
		else if(llCMoney <= UsedMoney[CHANNEL_MIDDLE][1])
			sMsg += "\n게임에 참여 하실려면 중수채널에 들어가세요.";
		else if(llCMoney <= UsedMoney[CHANNEL_PRO][1])
			sMsg += "\n게임에 참여 하실려면 고수채널에 들어가세요.";
		else
			sMsg += "\n게임에 참여 하실려면 타짜채널에 들어가세요.";
	}
	inline __int64	Get_AngelMoney( long lssn,	long	channel_idx , int Angel_Cnt, long lCLevel )
	{	
		// 올인수호천사 금액 변경
		if(channel_idx != CHANNEL_BEGIN) return 0;

		switch( lssn )
		{
		case 25: //섯다
			if((0==lCLevel)||(1==lCLevel)) //"초보"~"입문"
//			if( (lCLevel == 0 && channel_idx == CHANNEL_BEGIN) ||
//				(lCLevel == 1 && (channel_idx == CHANNEL_BEGIN || channel_idx == CHANNEL_HASOO))	)
				return (20*MAN);

		default:
			break;
		}
		return 0;
	}
};


// 자유(1000, 1000, 1000, 1000, 1000)
// 입문( 500, 1000, 1000, 1000, 1000)
// 하수(2000, 3000, 3000, 3000, 3000)
// 중수(6000, 10000, 10000, 10000, 10000)
// 고수(30000, 100000, 300000, 300000, 300000)
// 타짜(1000000, 3000000, 10000000, 30000000, 100000000)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   월드컵 프로모션
//
const float cnt_WorldCupMulti[7][8]= {
	{	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f    },	// 자유
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.2f, 2.5f, 3.0f    },	// 입문
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.2f, 2.5f, 3.0f    },	// 하수
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 3.0f, 4.0f    },	// 중수
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 4.0f, 5.0f    },	// 고수(3만원,10만원)
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 5.0f, 6.0f    },	// 고수/타짜(30만원,1백만원)
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 5.0f, 6.0f    },	// 타짜(3백만원, 천만원, 3천만원, 1억원)

};

// 배수 돌려주기
inline float Get_WorldCupPromotion_Multi(int chIdx, int nAnteIdx, int perIdx)
{		
	// 자유채널 제외 : 방어코드
	if( chIdx == __CONST_::CHANNEL_FREE ) return false;
	if( perIdx < 0 || perIdx > 7 ) perIdx = 0;	// 만에 하나 잘못된 값 들어왔을때 초기화

	int nMultiIdx = 0;

	// 삥값별로 다르다(고수, 마스터즈만 다르다)
	if( chIdx == __CONST_::CHANNEL_PRO )
	{
		if( nAnteIdx == 0 || nAnteIdx == 1 )	nMultiIdx = 4;	// 3만원, 10만원
		else if( nAnteIdx == 2 )				nMultiIdx = 5;	// 30만원
	}
	else if( chIdx == __CONST_::CHANNEL_MASTERS )
	{
		if( nAnteIdx == 0 )						nMultiIdx = 5;	// 100만원
		else									nMultiIdx = 6;	// 타짜 나머지 삥값(3백-1억)
	}
	else
		nMultiIdx = chIdx;


	return cnt_WorldCupMulti[nMultiIdx][perIdx];
}

enum StraightPrecedence {
	STRAIGHT_NONE = -1,
	STRAIGHT_TOP,
	STRAIGHT_BACK,
	STRAIGHT_MOUNTAIN
};

///////////////////////////////////////////////////////////////////////////////////
// 폴리스 방제 신고 변경
enum TERMINATE_ROOM
{
	TERMINATE_ROOM_GRACEFUL = 1,                // 진행중인 방이 끝난 뒤 방 삭제
	TERMINATE_ROOM_IMMEDIATE = 2,               // 즉시 방 삭제(현재 쓰지 않을 것이나 추후 필요할 경우를 위해)
	KICKOUT_USER_CHEAT = 1,
};


#endif
