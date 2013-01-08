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


const long g_lSSN = 25;  //����
const int g_nVersion = 1234;//1256;

const int MAX_CARD_ARRAY = 8; // ��ü ������ ��Ʋ�� �ִ� ������ �Ǵ� ī�� �� ��
const int MAX_CARD_COUNT = 5;
const int TOTAL_CARDS = 40;
const int NUM_MADE = 22;
const int MAX_CARDCHECK_COUNT = 5;
const int MAX_CHANNEL = 10;
//const int Seat[5][5] = {{0, 1, 2, 3, 4}, {1, 2, 3, 4, 0}, {2, 3, 4, 0, 1}, {3, 4, 0, 1, 2}, {4, 0, 1, 2, 3}};
// CHANNEL_BEGIN�� �ش��ϴ� ���� �׻� ��� �迭�� ���� �־�� �Ѵ�.

//ö�̰� ���� ī��Ʈ
//const int MAX_ALLIN = 3;//��ȣõ��
//const int PURGE_INCRAESE[LIMIT_PURGECNT] = {1, 2, 5, 10, 20}; 
//ö�̰� ���� ī��Ʈ

//��ȣõ��
const int cnt_MAX_ALLIN = 4;	// 4ȸ�� ���� : ���� ��ȣ��

enum _NEWSUDDA_GAMERULE{
	GAMERULE_SUDDA_2 = 0,
	GAMERULE_SUDDA_3 = 1,
	GAMERULE_DORIG_9 = 2,
};


//=ä�� �뷱�� 20100323
namespace	__CONST_
{
	enum{
		TWOUSER_NUM = 2,
		LEVEL_MAX = 9,
		ANTEMONEY_MAX = 5,
	};

	enum CHANNEL_TYPE_NEWSUDDA {
		CHANNEL_FREE = 0,			// ����  = ����
		CHANNEL_BEGIN = 1,		    // �Թ�  = 1õ/3õ
		CHANNEL_HASOO = 2,			// �ϼ�  = 1��/3��
		CHANNEL_MIDDLE = 3,			// �߼�  = 10��/30��
		CHANNEL_PRO = 4,			// ����(���) = 1�鸸
		CHANNEL_MASTERS = 5,		// ��������(Ÿ¥) = 3�鸸/1��
		CHANNEL_REALBET = 6,		// ���� = �嶯
		CHANNEL_NUMBER_MAX = 7,
	};

	const int RaiseCount[CHANNEL_NUMBER_MAX][5] = { // ���� Ƚ��
		{2,2,2,2,2}, // ����(����)
		{2,2,2,2,2}, // �Թ�  = 1õ/3õ
		{2,2,2,2,2}, // �ϼ�  = 1��/3��
		{2,2,2,2,2}, // �߼�  = 10��/30��
		{2,2,2,2,2}, // ����(���) = 1�鸸
		{2,2,2,2,2}, // ��������(Ÿ¥) = 3�鸸/1��
		{1,3,3,3,3}, // ���� = �嶯
	};

	const __int64 UsedMoney[CHANNEL_NUMBER_MAX][2] = {	// ���� ���� �����Ӵ�
		{1000,			MMAX},			// ����(����)
		{1000,			330*MAN},		// �Թ�  = 1õ/3õ
		{80*MAN,		3300*MAN},		// �ϼ�  = 1��/3��
		{800*MAN,		3*UK+3000*MAN},	// �߼�  = 10��/30��
		{2500*MAN,		10*UK},			// ����(���) = 1�鸸
		{8000*MAN,		MMAX},			// ��������(Ÿ¥) = 3�鸸/1��
		{3*UK,			MMAX},			// ���� = �嶯
	};

	const __int64 MinMoney[CHANNEL_NUMBER_MAX] = {	// ä�� �ּ� ���� �ݾ�
		1,			// ����(����)
		1,		    // �Թ�  = 1õ/3õ
		80*MAN,		// �ϼ�  = 1��/3��
		800*MAN,	// �߼�  = 10��/30��
		2500*MAN,	// ����(���) = 1�鸸
		8000*MAN,	// ��������(Ÿ¥) = 3�鸸/1��
		3*UK,		// ���� = �嶯
	};

	const __int64 EntryMoney[CHANNEL_NUMBER_MAX][ANTEMONEY_MAX] = {	// ��ä�κ� ���� ���� �ݾ�
		{1000,			1000,			1000,			1000,			1000},		// ����(����)
		{1000,			3000,			3000,			3000,			3000},		// �Թ�  = 1õ/3õ
		{1*MAN,			1*MAN,			1*MAN,			1*MAN,			1*MAN},		// �ϼ�  = 1��/3��
		{10*MAN,		10*MAN,			10*MAN,			10*MAN,			10*MAN},	// �߼�  = 10��/30��
		{100*MAN,		100*MAN,		100*MAN,		100*MAN,		100*MAN},	// ����(���) = 1�鸸
		{300*MAN,		10*UK,			20*UK,			50*UK,			100*UK},	// ��������(Ÿ¥) = 3�鸸/1��
		{500*MAN,		20*UK,			50*UK,			100*UK,			300*UK},	// ���� = �嶯
	};
	const __int64 PurgeMoney[CHANNEL_NUMBER_MAX] = {	//���� �Ӵϱ�
		1*MAN,		// ����
		1*MAN,		// �Թ�  = 1õ/3õ
		1*MAN,		// �ϼ�  = 1��/3��
		2*MAN,		// �߼�  = 10��/30��
		20*MAN,		// ���� = 1�鸸
		50*MAN,		// �������� = 3�鸸/1��
		50*MAN,		// ���� = �嶯
	};
	const __int64 LevelMoney[LEVEL_MAX][2] = {
		{0,				30*MAN},	// �Թ�
		{30*MAN,		100*MAN},	// �ʺ�
		{100*MAN,		300*MAN},	// �ϼ�
		{300*MAN,		1000*MAN},	// �߼�
		{1000*MAN,		3000*MAN},	// ���
		{3000*MAN,		1*UK},		// ����
		{1*UK,			3*UK},		// Ÿ¥
		{3*UK,			10*UK},		// ����
		{10*UK,			MMAX},		// ����
	};

	const __int64 g_llAnteMoneyTable[CHANNEL_NUMBER_MAX][ANTEMONEY_MAX] = { //�氪
		{1000,		1000,		1000,		1000,		1000},			// ����
		{1000,		3000,		3000,		3000,		3000},			// �Թ�  = 1õ/3õ
		{1*MAN,		3*MAN,		3*MAN,		3*MAN,		3*MAN},			// �ϼ�  = 1��/3��
		{10*MAN,	30*MAN,		30*MAN,		30*MAN,		30*MAN},		// �߼�  = 10��/30��
		{100*MAN,	100*MAN,	100*MAN,	100*MAN,	100*MAN},		// ����(���) = 1�鸸
		{300*MAN,	1000*MAN,	3000*MAN,	1*UK,		1*UK},	        // ��������(Ÿ¥) = 3�鸸/1��
		{500*MAN,	1000*MAN,	3000*MAN,	5000*MAN,	5000*MAN},	    // ���� = �嶯
	};
	const string channelNameString[CHANNEL_NUMBER_MAX] = {"����ä��", "1õ,3õ ä��", "1��,3�� ä��", "10��,30�� ä��", "1�� �� ä��", "3�鸸~1�� ä��", "�嶯ä��"};

	const string cnt_sLevel[LEVEL_MAX] = {"�Թ�","�ʺ�","�ϼ�","�߼�","���","����","Ÿ¥","����","����"};
								          //0	  1	     2	    3	   4	  5		 6		7	   8
	const string MadeNum[NUM_MADE] ={"118", "127", "136", "145", "019",
									 "226", "235", "028", "334", "037",
									 "389", "244", "046", "479", "055",
									 "569", "578", "668", "677", "488",
									 "299", "000"};

	const string MadeName[NUM_MADE] ={"������", "�߸�ĥ", "������", "������", "�汸��",
									  "�ϴ���", "�̻��", "������", "�ɽɻ�", "��ĥ��",
									  "�����", "�����", "�����", "��ĥ��", "������",
									  "������", "������", "������", "öö��", "���Ž�",
									  "������", "������"};

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
	inline bool	Verify_Entry_UserGrade( long cLevel , long channel_idx ){ //�̿���
		if(CHANNEL_FREE==channel_idx){
			return true;
		}
		if(CHANNEL_BEGIN==channel_idx){
			return (2>=cLevel); //"�ʺ�"~"�ϼ�"
		}
		if(CHANNEL_HASOO==channel_idx){
			return ((4>=cLevel)&&(2<=cLevel)); //"�ϼ�"~"���"
		}
		if(CHANNEL_MIDDLE==channel_idx){
			return ((6>=cLevel)&&(4<=cLevel)); //"���"~"Ÿ¥"
		}
		if(CHANNEL_PRO==channel_idx){
			return ((7>=cLevel)&&(5<=cLevel)); //"����"~"����"
		}
		if(CHANNEL_MASTERS==channel_idx){
			return (6<=cLevel);  //"Ÿ¥"~"����"
		}
		if(CHANNEL_REALBET==channel_idx){
			return (7<=cLevel);  //"����"~"����"
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
	// �氪�� �ο����� ���	
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
	// ������ 3%
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
		sTitle = "[�Ŀ�ä��] ��������Դϴ�.";
		sMsg = "���� �۽�ƮŬ��, ���� �۽�Ʈ���, ���� �Ŀ�ä�� �����\n�̿� �ÿ� ���������� �����մϴ�.";	
	}
	inline void	MakeString_Reject_GRADE(string &sTitle, string &sMsg, long lSSN, int now_chidx, int lclevel ){
		for( int i=1;i<CHANNEL_NUMBER_MAX;i++){
			if( Verify_Entry_UserGrade( lclevel, i ) ){				
				break;
			}
		}
		int canplay_chi = Verify_Entry_UserChannel(lclevel);
		sTitle = ::format( "[%sä��] ��������Դϴ�.", Get_ChannelName( now_chidx ).c_str() );
		sMsg = ::format("%sä�η� �̵��ϸ� ���������� �����մϴ�.", Get_ChannelName( canplay_chi ).c_str() );
	}
	inline void	MakeString_Eject_Money( string &sTitle, string &sMsg, long lSSN, __int64 money_low, __int64 lCMoney ){
		string	smm_low = LongToStr( money_low, 2);
		sTitle = ::format("[%s�̻� ��]�Դϴ�.", smm_low.c_str() );
		/*
		else
		sTitle = ::format("[%s~%s ��] ��������Դϴ�.", LongToStr( money_low, 2).c_str(), LongToStr( money_high, 2).c_str() );
		*/
		sMsg = ::format("�����Ͻ� ���ӹ��� �����Ӵϰ� %s�̻��̾��\n��������/������ �����մϴ�.", smm_low.c_str());
		sMsg += "\n���ӿ� �����Ͻ÷��� �ݰ�����, ����, ���Ӹ��� �̿��ϼ���.";
	}
	inline void	MakeString_Reject_Money( string &sTitle, string &sMsg, long lSSN, __int64 money_low, __int64 money_high, __int64 llCMoney ){
		string	smm_low = LongToStr( money_low, 2);
		string	smm_high = LongToStr( money_high, 2);
		if(MMAX == money_high){
			sTitle = ::format("[%s�̻� ��] ��������Դϴ�.", smm_low.c_str() );
			sMsg = ::format("�����Ͻ� ���ӹ��� �����Ӵϰ� %s�̻��� �е鸸 \n���ӿ� ���� �� �� �ֽ��ϴ�.", smm_low.c_str() );
			sMsg += "\n���ӿ� �����Ͻ÷��� �ݰ�����, ����, ���Ӹ��� �̿��ϼ���.";
		}
		else{
			sTitle = ::format("[%s�̻� �� %s�̸� ��] ��������Դϴ�.", smm_low.c_str(), smm_high.c_str() );		
			sMsg = ::format("�����Ͻ� ���ӹ��� �����Ӵϰ� %s�̻�, %s �̸��� �е鸸 \n���ӿ� ���� �� �� �ֽ��ϴ�.", smm_low.c_str(), smm_high.c_str() );
			sMsg += "\n���ӿ� �����Ͻ÷��� �ݰ�����, ����, ���Ӹ��� �̿��ϼ���.";
		}
	}
	inline void	MakeString_Reject_Money_2( string &sTitle, string &sMsg, long lSSN, __int64 money_low, __int64 money_high, __int64 llCMoney ){
		string	smm_low = LongToStr( money_low, 2);
		string	smm_high = LongToStr( money_high, 2);
		if(MMAX == money_high){
			sTitle = ::format("[%s�̻� ��] ��������Դϴ�.", smm_low.c_str() );
			sMsg = ::format("�����Ͻ� ���ӹ��� �����Ӵϰ� %s�̻��� �е鸸 \n���ӿ� ���� �� �� �ֽ��ϴ�.", smm_low.c_str() );
		}
		else{
			sTitle = ::format("[%s�̻� �� %s�̸� ��] ��������Դϴ�.", smm_low.c_str(), smm_high.c_str() );		
			sMsg = ::format("�����Ͻ� ���ӹ��� �����Ӵϰ� %s�̻�, %s �̸��� �е鸸 \n���ӿ� ���� �� �� �ֽ��ϴ�.", smm_low.c_str(), smm_high.c_str() );
		}
		if(llCMoney <= UsedMoney[CHANNEL_BEGIN][1])
			sMsg += "\n���ӿ� ���� �ϽǷ��� �Թ�ä�ο� ������.";
		else if(llCMoney <= UsedMoney[CHANNEL_HASOO][1])
			sMsg += "\n���ӿ� ���� �ϽǷ��� �ϼ�ä�ο� ������.";
		else if(llCMoney <= UsedMoney[CHANNEL_MIDDLE][1])
			sMsg += "\n���ӿ� ���� �ϽǷ��� �߼�ä�ο� ������.";
		else if(llCMoney <= UsedMoney[CHANNEL_PRO][1])
			sMsg += "\n���ӿ� ���� �ϽǷ��� ���ä�ο� ������.";
		else
			sMsg += "\n���ӿ� ���� �ϽǷ��� Ÿ¥ä�ο� ������.";
	}
	inline __int64	Get_AngelMoney( long lssn,	long	channel_idx , int Angel_Cnt, long lCLevel )
	{	
		// ���μ�ȣõ�� �ݾ� ����
		if(channel_idx != CHANNEL_BEGIN) return 0;

		switch( lssn )
		{
		case 25: //����
			if((0==lCLevel)||(1==lCLevel)) //"�ʺ�"~"�Թ�"
//			if( (lCLevel == 0 && channel_idx == CHANNEL_BEGIN) ||
//				(lCLevel == 1 && (channel_idx == CHANNEL_BEGIN || channel_idx == CHANNEL_HASOO))	)
				return (20*MAN);

		default:
			break;
		}
		return 0;
	}
};


// ����(1000, 1000, 1000, 1000, 1000)
// �Թ�( 500, 1000, 1000, 1000, 1000)
// �ϼ�(2000, 3000, 3000, 3000, 3000)
// �߼�(6000, 10000, 10000, 10000, 10000)
// ���(30000, 100000, 300000, 300000, 300000)
// Ÿ¥(1000000, 3000000, 10000000, 30000000, 100000000)
//////////////////////////////////////////////////////////////////////////////////////////////////////
//
//   ������ ���θ��
//
const float cnt_WorldCupMulti[7][8]= {
	{	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f    },	// ����
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.2f, 2.5f, 3.0f    },	// �Թ�
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.2f, 2.5f, 3.0f    },	// �ϼ�
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 3.0f, 4.0f    },	// �߼�
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 4.0f, 5.0f    },	// ���(3����,10����)
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 5.0f, 6.0f    },	// ���/Ÿ¥(30����,1�鸸��)
	{	1.0f, 1.1f, 1.2f, 1.5f, 2.0f, 2.5f, 5.0f, 6.0f    },	// Ÿ¥(3�鸸��, õ����, 3õ����, 1���)

};

// ��� �����ֱ�
inline float Get_WorldCupPromotion_Multi(int chIdx, int nAnteIdx, int perIdx)
{		
	// ����ä�� ���� : ����ڵ�
	if( chIdx == __CONST_::CHANNEL_FREE ) return false;
	if( perIdx < 0 || perIdx > 7 ) perIdx = 0;	// ���� �ϳ� �߸��� �� �������� �ʱ�ȭ

	int nMultiIdx = 0;

	// �氪���� �ٸ���(���, ������� �ٸ���)
	if( chIdx == __CONST_::CHANNEL_PRO )
	{
		if( nAnteIdx == 0 || nAnteIdx == 1 )	nMultiIdx = 4;	// 3����, 10����
		else if( nAnteIdx == 2 )				nMultiIdx = 5;	// 30����
	}
	else if( chIdx == __CONST_::CHANNEL_MASTERS )
	{
		if( nAnteIdx == 0 )						nMultiIdx = 5;	// 100����
		else									nMultiIdx = 6;	// Ÿ¥ ������ �氪(3��-1��)
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
// ������ ���� �Ű� ����
enum TERMINATE_ROOM
{
	TERMINATE_ROOM_GRACEFUL = 1,                // �������� ���� ���� �� �� ����
	TERMINATE_ROOM_IMMEDIATE = 2,               // ��� �� ����(���� ���� ���� ���̳� ���� �ʿ��� ��츦 ����)
	KICKOUT_USER_CHEAT = 1,
};


#endif
