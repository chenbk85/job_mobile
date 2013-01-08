// GameAILogic.cpp: implementation of the GameAI class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "GameAI.h"
#include "iRoomContext.h"
#include "HT.h"
#include "ObjectHeader.h"

/////////////////////////////////////////////////////////////////////////////
// GameAILogic.cpp															//
//																			//
// AI related				 												//
//																			//
//////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
//

#define _KEY m_Key
CGameInfo& CBot::GetGI() 
{ 
	return _GAMEINFO(_KEY)->GetGI();
}
CHT& CBot::GetHT(int idx) { 
	return _CARD(_KEY)->GetHT(idx);
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBot::CBot()
{
	Clear();
}
CBot::~CBot()
{
}

void CBot::Clear()
{
	for(int i=0; i<MAX_GROUP+1; ++i)
	{
		m_aGroupCount[i] = 0;
	}	

	Initialize();
}

void CBot::Initialize()
{
	for(int i=0; i<HT_MAX; ++i)
	{
		m_aTypeCount[i] = 0;
	}

	m_lstPossibility.clear();
}

///////////////////////////////////////////////////////////////////////////////
//

BOOL CBot::IsHardenedGroup(int iGroup) 
{
	if(m_aGroupCount[iGroup] == 2) 
	{
		return TRUE;
	}
	return FALSE;
}

BOOL CBot::IsSameGroup(tPLATE A, tPLATE B)
{
	if(GetHT(A).GetGroup() == GetHT(B).GetGroup()) 
	{
		return TRUE;
	}
	return FALSE;
}

LONG CBot::NoOfSameGroupOnBoard(tPLATE pl)
{
	LONG lCount = 0L;
	const HTList& lstOpen = GetGI().GetOpenList();

	ForEachCElmt(HTList, lstOpen, i, j)
	{
		if(IsSameGroup(*i, pl)) { ++lCount; }
	}

	return lCount;
}

LONG CBot::NoOfSameGroupOnBot(tPLATE pl)
{
	LONG lCount = 0L;
	const HTList& lstHold = GetGI().GetHoldList(ROBOT_UI);

	ForEachCElmt(HTList, lstHold, i, j)
	{
		if(IsSameGroup(*i, pl)) { ++lCount; }
	}
	return lCount;
}

///////////////////////////////////////////////////////////////////////////////
//

// 상대방이 먹은패 중 각 타입별 갯수 
void CBot::ComputeEnemyPlateTypeCount()
{	// 상대방이 먹은패들 중 각 타입별 갯수 저장했음
	const HTList& lstFive = GetGI().GetClassList(ENEMY_UI, HC_FIVE);
	// 광 /////////////////////////////////////////////////
	m_aTypeCount[HT_KWANG] = static_cast<int>(GetGI().GetClassList(ENEMY_UI, HC_CAP).size());
	// 고도리 /////////////////////////////////////////////
	m_aTypeCount[HT_GODORI] = _CARD(_KEY)->GetTypeCount(GetGI().GetClassList(ENEMY_UI, HC_TEN), HT_GODORI);
	// 홍단 ///////////////////////////////////////////////
	m_aTypeCount[HT_RED] = _CARD(_KEY)->GetTypeCount(lstFive, HT_RED);
	// 청단 ///////////////////////////////////////////////
	m_aTypeCount[HT_BLUE] = _CARD(_KEY)->GetTypeCount(lstFive, HT_BLUE);
	// 쿠사 ///////////////////////////////////////////////
	m_aTypeCount[HT_KUSA] = _CARD(_KEY)->GetTypeCount(lstFive, HT_KUSA);
	// 피(더블피 포함) /////////////////////////////////////////////////
	m_aTypeCount[HT_ONE] = _CARD(_KEY)->GetOneClassPeeNum(GetGI().GetClassList(ENEMY_UI, HC_ONE));
}

int CBot::AutoSelectHT(int iUI, BOOL bAI)
{
	int iIndex = -1;

	if( !_ROOM(_KEY)->IsHoguChannel() && (_ROOM(_KEY)->IsRobot(iUI) && bAI) )
	{
		iIndex = SelectPlate();
	}
	else
	{
		const HTList& lstHold = GetGI().GetHoldList(iUI);

		if(lstHold.size() == 0)
		{
			if(GetGI().GetHTUser(iUI).GetJustPlayCount() > 0)
			{
				iIndex = MAX_HT; 
			}
			else
			{
				_SENDER(_KEY)->SendGameOverInit(FALSE, FALSE); 
			}
		}
		else
		{
			iIndex = lstHold.front();
		}
	}

	return iIndex;
}
BOOL CBot::CheckAbilityPlate(tPLATE iIndex)
{
	int iAbility = GetHT(iIndex).GetAbility();
	switch(iAbility) 
	{
	case HA_ABILITY1:	// 골든패 (5)
		return TRUE;
		break;
	case HA_ABILITY2:	// 흑기사 (15)
		return TRUE;
		break;
	case HA_ABILITY3:	// 분신술 (20)
		if(GetGI().GetTurnCount() >= (MAX_PLAYER*2)) { return TRUE; }
		break;
	case HA_ABILITY4:	// 피 가져오기 (40)
		if(m_aTypeCount[HT_ONE] > 0) { return TRUE; }
		break;
	case HA_ABILITY5:	// 띠 가져오기 
		if(GetGI().GetClassList(ENEMY_UI, HC_FIVE).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY6:	// 십 가져오기 
		if(GetGI().GetClassList(ENEMY_UI, HC_TEN).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY7:	// 광 가져오기 (30)
		if(m_aTypeCount[HT_KWANG] > 0) { return TRUE; }
		break;
	case HA_ABILITY8:	// 띠 복사하기 (40)
		if(GetGI().GetClassList(ENEMY_UI, HC_FIVE).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY9:	// 열끗 복사하기(50)
		if(GetGI().GetClassList(ENEMY_UI, HC_TEN).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY10:	// 광 복사하기 (30)
		if(m_aTypeCount[HT_KWANG] > 0) { return TRUE; }
		break;
	case HA_ABILITY11:	// +3점 
		return TRUE;
		break;
	case HA_ABILITY12:	// 잠자는패(2개) 보기 (40)
		return TRUE;
		break;
	case HA_ABILITY13:	// 상대패 잠깐 보기 (30)
		return TRUE;
		break;
	case HA_ABILITY14:	// 바닥패 새로 고치기 (30)
		{
			const HTList& lstHold = GetGI().GetHoldList(ROBOT_UI);
			const HTList& lstOpen = GetGI().GetOpenList();
			int iGroup = 0;
			
			ForEachCElmt(HTList, lstHold, i1, j1)
			{ // 오픈에 먹을 것 있는지 검사!
				iGroup = GetHT(*i1).GetGroup();
				if(iGroup == GROUP_BONUS) { continue; }
				if(iGroup == GROUP_ABILITY) { continue; }
				ForEachCElmt(HTList, lstOpen, i2, j2)
				{ // 오픈에 해당패와 같은 것 있는지 검사!
					if(GetHT(*i2).GetGroup() == iGroup) {
						return FALSE;
					}
				}
			}
			return TRUE;
		}
		break;
	case HA_ABILITY15:  
		return TRUE;
		break;
	default: break;
	}

	return FALSE;
}

// 각 패에 대한 Priority를 계산
void CBot::CaseGenerate()
{
	m_lstPossibility.clear();

	int iType, iGroup;
	int iNoSameGroupOnOpen, iNoSameGroupOnHold;
	LONG lBotPlatePriority = 0L;
	tPLATE P;
	
	const HTList& lstHold = GetGI().GetHoldList(ROBOT_UI);

	ForEachCElmt(HTList, lstHold, i, j)
	{
		P = (*i);
		iNoSameGroupOnOpen = NoOfSameGroupOnBoard(P);
		iNoSameGroupOnHold = NoOfSameGroupOnBot(P);
		iGroup = GetHT(P).GetGroup();
		iType = GetHT(P).GetType();
		
		lBotPlatePriority  = 0L;

		///////////////////////////////////////////////////////////////////////
		// 먹을때는 좋은패부터...^^;
		if(iNoSameGroupOnOpen > 0)
		{
			switch(iType)
			{
			case HT_ONE: lBotPlatePriority += 55;
				break;
			case HT_DOUBLE: lBotPlatePriority += 75;
				break;
			case HT_RED: lBotPlatePriority +=60;
				break;		
			case HT_BLUE: lBotPlatePriority += 60;
				break;
			case HT_KUSA: lBotPlatePriority += 60;
				break;
			case HT_GODORI: lBotPlatePriority += 65;
				break;
			case HT_KWANG: lBotPlatePriority += 70;
				break;
			default : lBotPlatePriority += 50; // 일치#2
				break;
			}
		}

		///////////////////////////////////////////////////////////////////////
		// 먹을패의 갯수에 따른 Priority 매기기 
		switch(iNoSameGroupOnOpen)
		{
		case 0:
			{	
				if((iNoSameGroupOnHold == 2) && (IsHardenedGroup(iGroup)))
				{ // 굳은자일 경우에는 
					if((iType == HT_NONE) || (iType == HT_ONE)) {
						lBotPlatePriority += 40; // (일치#1보다크고일치#2보다는작게)
					}else {
						lBotPlatePriority += 35; // (일치#1보다크고일치#2보다는작게)
					}
				}
				else if(iNoSameGroupOnHold == 4)
				{ // 흔들기 (4장으로)
					if((iType == HT_NONE) || (iType == HT_ONE)) {
						lBotPlatePriority += 50; // 일치#2
					}else {
						lBotPlatePriority += 45; // (일치#1보다크고일치#2보다는작게)
					}
				}
				else
				{ // 내줄때는 안좋은 것 주기(상대방에게 좋은 패들은 피한다) - 흔들기 포함(3장)
					if((iType > HT_DOUBLE) && (m_aTypeCount[iType] > 1)) { // 상대방이 약할 것은
						lBotPlatePriority +=  5;
					}else if(iType == HT_DOUBLE) {	// 쌍피는
						lBotPlatePriority += 10;
					}else if(iType == HT_KWANG) {	// 광은
						lBotPlatePriority += 15;
					}else if(iType == HT_GODORI) {	// 고도리 
						lBotPlatePriority += 20;
					}else if(iType > HT_ONE) {		// 단들 
						lBotPlatePriority += 25;
					}else {							// 그외 떨거지들 
						lBotPlatePriority += 30;	// 일치#1
					}
				}
			}
			break;
		case 1:
			{
				if(iNoSameGroupOnHold == 3)
				{
					if(m_aTypeCount[HT_ONE] > 1) {
						lBotPlatePriority += 35;
					}else if(GetGI().GetTurnCount() > (MAX_PLAYER*3)) {
						lBotPlatePriority += 30;
					}else {
						lBotPlatePriority += 10;
					}
				}
				else 
				{
					lBotPlatePriority += 15;
				}
			}
			break;
		case 2:
			{
				lBotPlatePriority += 15; 
			}
			break;
		case 3:
			{
				if(GetGI().IsYourBBuck(ROBOT_UI, GetHT(P).GetGroup())) 
				{
					if(m_aTypeCount[HT_ONE] > 1) {
						lBotPlatePriority += 70;
					}else if(GetGI().GetTurnCount() > (MAX_PLAYER*3)) {
						lBotPlatePriority += 60;
					}else {
						lBotPlatePriority += 10;
					}
				}
				else 
				{
					if(m_aTypeCount[HT_ONE] > 0) {
						lBotPlatePriority += 65; 
					}else if(GetGI().GetTurnCount() > (MAX_PLAYER*3)) {
						lBotPlatePriority += 55;
					}else {
						lBotPlatePriority += 10;
					}
				}
			}
			break;
		default: 
			break;
		}
		///////////////////////////////////////////////////////////////////////
		// 
		sPossibilityVector v;
		v.lBotPlate	= P;
		v.lBotPlatePriority = lBotPlatePriority;
		m_lstPossibility.push_back(v);
	}

}

// 들고 있는 패들중에 낼 패 선택하기 
tPLATE CBot::SelectPlate()
{
	tPLATE iIndex = -1;
	HTList lstAbility;

	// 초기화 
	Initialize();
	lstAbility.clear();

	// Set 화투패 상태
	const HTList& lstRobotHold = GetGI().GetHoldList(ROBOT_UI);
	if(lstRobotHold.empty())
	{	// is game over or lack
		if(GetGI().GetHTUser(ROBOT_UI).GetJustPlayCount() > 0)
		{
			// 그냥 뒤집을 패만 남은 경우 
			return MAX_HT;
		}
		else
		{
			// 에러!
		}
		return MAX_HT;
	}
	else if(GetGI().GetTurnCount() == (MAX_PLAYER*2))
	{
		ForEachCElmt(HTList, lstRobotHold, i, j)
		{
			iIndex = (*i); 
			if(GetHT(iIndex).GetGroup() == GROUP_BONUS)
			{
				return iIndex;
			}
			else if(GetHT(iIndex).GetGroup() == GROUP_ABILITY)
			{
				lstAbility.push_back(iIndex);
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////
	// 멤버 세팅

	// 상대방이 먹은패 중 각 타입별 갯수 
	ComputeEnemyPlateTypeCount();
	// 기능패 처리 
	lstAbility.sort();
	ForEachCElmt(HTList, lstAbility, i, j)
	{
		iIndex = (*i); 
		//if(GetHT(iIndex).GetAbility() == HA_NONE) { continue; }
		if(CheckAbilityPlate(iIndex)) { return iIndex; }
	}
	// Set 화투패 상태
	CaseGenerate();

	/////////////////////////////////////////////////////////////////////////////////////
	//
	tPLATE pl = -1L;
	LONG lMaxPriority = 0L;

	ForEachElmt(tPOSSIBILITYLIST, m_lstPossibility, it1, it2)
	{
		sPossibilityVector& pv = (*it1);
		if(pv.lBotPlatePriority > lMaxPriority)
		{
			lMaxPriority = pv.lBotPlatePriority;
			pl = pv.lBotPlate;
		}

	}

	// 들고 있는 패는 있으나 먹을 패가 없고 그냥 뒤집을 수 있을때
	if((lMaxPriority <= 30) && (GetGI().GetHTUser(ROBOT_UI).GetJustPlayCount() > 0))
	{ // 일치#1 --------ㅗ
		return MAX_HT;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// 에러 사항 
	if(pl == -1)
	{
		if(GetGI().GetHTUser(ROBOT_UI).GetJustPlayCount() > 0)
		{
			pl = MAX_HT;
		}
		else
		{
			pl = AutoSelectHT(ROBOT_UI, FALSE);
		}
	}

	return pl;
}

// 두 개의 먹을 패중에 한개 선택 
tPLATE CBot::ChoicePlate(const HTList& lstChoice)
{	// 먹을 패 두개중 하나 선택
	int iHT1 = lstChoice.front();
	int iHT2 = lstChoice.back();

	if(GetHT(iHT1).GetClass() != GetHT(iHT2).GetClass()) 
	{
		int iType1 = GetHT(iHT1).GetType();
		int iType2 = GetHT(iHT2).GetType();

		if(iType1 == HT_DOUBLE) { return iHT1; }
		if(iType2 == HT_DOUBLE) { return iHT2; }

		if(iType1 == HT_KWANG) { return iHT1; }

		if((iType1 != HT_NONE) && (iType1 != HT_ONE)) { return iHT1; }
		if((iType2 != HT_NONE) && (iType2 != HT_ONE)) { return iHT2; }

		if((iType1 == HT_NONE) && (iType2 != HT_NONE)) { return iHT2; }
	}
	return iHT1;
}

// 고 또는 스톱 결정 
BOOL CBot::ChoiceGoStop()
{
	int iPeeCount = _CARD(_KEY)->GetOneClassPeeNum(GetGI().GetClassList(ENEMY_UI, HC_ONE));
	int iJumsu = _PROC(_KEY)->Proc_CheckUserPoint(GetGI().GetHTUser(ENEMY_UI), iPeeCount, FALSE);
	int iCount = 0;

	if(iJumsu < 1) return TRUE;

	if( GetGI().Get9TenCanMove() && _CARD(_KEY)->FindIndex(GetGI().GetClassList(ENEMY_UI, HC_TEN), INDEX_9TEN) )
	{
		iPeeCount += 2;
	}

	// 각 타입별 체크 
	for(int i=HT_RED; i<HT_MAX; ++i)
	{
		iCount = 0;

		if(i == HT_KWANG)
		{
			if(m_aTypeCount[i] == 2) 
			{
				iCount = m_aTypeCount[i];
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetHoldList(ROBOT_UI), HT_KWANG);
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetClassList(ROBOT_UI, HC_CAP), HT_KWANG);
				if((iCount != 5) && (iJumsu > 2) && (iPeeCount > 9)) return FALSE;
			}
		}
		else if(m_aTypeCount[i] == 2) 
		{
			switch(i) 
			{
			case HT_RED :
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetHoldList(ROBOT_UI), HT_RED);
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetClassList(ROBOT_UI, HC_FIVE), HT_RED);
				if((iCount == 0) && (iJumsu > 2)) return FALSE;
				break;
			case HT_BLUE :
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetHoldList(ROBOT_UI), HT_BLUE);
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetClassList(ROBOT_UI, HC_FIVE), HT_BLUE);
				if((iCount == 0) && (iJumsu > 2)) return FALSE;
				break;
			case HT_KUSA :
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetHoldList(ROBOT_UI), HT_KUSA);
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetClassList(ROBOT_UI, HC_FIVE), HT_KUSA);
				if((iCount == 0) && (iJumsu > 2)) return FALSE;
				break;
			case HT_GODORI :
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetHoldList(ROBOT_UI), HT_GODORI);
				iCount += _CARD(_KEY)->GetTypeCount(GetGI().GetClassList(ROBOT_UI, HC_TEN), HT_GODORI);
				if((iCount == 0) && (iJumsu > 1)) return FALSE;
				break;
			default : break;
			}
		}
	}
	
	const HTList& lstBBuckGroup = GetGI().GetBBuckGroupList();

	if(!lstBBuckGroup.empty())
	{ // 바닥에 뻑한게 있음 
		const HTList& lstHold = GetGI().GetHoldList(ROBOT_UI);
		BOOL bRet = TRUE;
		ForEachCElmt(HTList, lstBBuckGroup, it1, it2)
		{
			if( _CARD(_KEY)->GetGroupCount(lstHold, (*it1)) == 0 ) {
				bRet = FALSE; 
				break;
			}
		}
		if(!bRet)
		{ // 내가 가지고 있지 않은 뻑한게 있을때 
			if(iPeeCount > 9)
			{
				if(iJumsu > 1) return FALSE;
				if(iPeeCount > 10) return FALSE;
			}
			else
			{
				if(iJumsu < 4 && iPeeCount < 7) return TRUE;
				if(iJumsu > 2) return FALSE;		
			}
		}
	}

	if(iPeeCount > 9)
	{
		if(iJumsu > 2) return FALSE;
		if(iPeeCount > 11) return FALSE;
	}
	else
	{
		if(iJumsu < 5 && iPeeCount < 7) return TRUE;
		if(iJumsu > 3) return FALSE;
	}

	return TRUE;
}

// 국진 열끗 옮길 것인지 
BOOL CBot::ChoiceMoveTen()
{
	DWORD iTenCnt = static_cast<DWORD>(GetGI().GetClassList(ROBOT_UI, HC_TEN).size());

	if(iTenCnt == 7) 
	{
		return FALSE;
	}

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////////////////
// End of File
/////////////////////////////////////////////////////////////////////////////////////////

#undef _KEY