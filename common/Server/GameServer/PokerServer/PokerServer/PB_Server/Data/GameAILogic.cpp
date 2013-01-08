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

// ������ ������ �� �� Ÿ�Ժ� ���� 
void CBot::ComputeEnemyPlateTypeCount()
{	// ������ �����е� �� �� Ÿ�Ժ� ���� ��������
	const HTList& lstFive = GetGI().GetClassList(ENEMY_UI, HC_FIVE);
	// �� /////////////////////////////////////////////////
	m_aTypeCount[HT_KWANG] = static_cast<int>(GetGI().GetClassList(ENEMY_UI, HC_CAP).size());
	// ���� /////////////////////////////////////////////
	m_aTypeCount[HT_GODORI] = _CARD(_KEY)->GetTypeCount(GetGI().GetClassList(ENEMY_UI, HC_TEN), HT_GODORI);
	// ȫ�� ///////////////////////////////////////////////
	m_aTypeCount[HT_RED] = _CARD(_KEY)->GetTypeCount(lstFive, HT_RED);
	// û�� ///////////////////////////////////////////////
	m_aTypeCount[HT_BLUE] = _CARD(_KEY)->GetTypeCount(lstFive, HT_BLUE);
	// ��� ///////////////////////////////////////////////
	m_aTypeCount[HT_KUSA] = _CARD(_KEY)->GetTypeCount(lstFive, HT_KUSA);
	// ��(������ ����) /////////////////////////////////////////////////
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
	case HA_ABILITY1:	// ����� (5)
		return TRUE;
		break;
	case HA_ABILITY2:	// ���� (15)
		return TRUE;
		break;
	case HA_ABILITY3:	// �нż� (20)
		if(GetGI().GetTurnCount() >= (MAX_PLAYER*2)) { return TRUE; }
		break;
	case HA_ABILITY4:	// �� �������� (40)
		if(m_aTypeCount[HT_ONE] > 0) { return TRUE; }
		break;
	case HA_ABILITY5:	// �� �������� 
		if(GetGI().GetClassList(ENEMY_UI, HC_FIVE).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY6:	// �� �������� 
		if(GetGI().GetClassList(ENEMY_UI, HC_TEN).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY7:	// �� �������� (30)
		if(m_aTypeCount[HT_KWANG] > 0) { return TRUE; }
		break;
	case HA_ABILITY8:	// �� �����ϱ� (40)
		if(GetGI().GetClassList(ENEMY_UI, HC_FIVE).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY9:	// ���� �����ϱ�(50)
		if(GetGI().GetClassList(ENEMY_UI, HC_TEN).size() > 0) { return TRUE; }
		break;
	case HA_ABILITY10:	// �� �����ϱ� (30)
		if(m_aTypeCount[HT_KWANG] > 0) { return TRUE; }
		break;
	case HA_ABILITY11:	// +3�� 
		return TRUE;
		break;
	case HA_ABILITY12:	// ���ڴ���(2��) ���� (40)
		return TRUE;
		break;
	case HA_ABILITY13:	// ����� ��� ���� (30)
		return TRUE;
		break;
	case HA_ABILITY14:	// �ٴ��� ���� ��ġ�� (30)
		{
			const HTList& lstHold = GetGI().GetHoldList(ROBOT_UI);
			const HTList& lstOpen = GetGI().GetOpenList();
			int iGroup = 0;
			
			ForEachCElmt(HTList, lstHold, i1, j1)
			{ // ���¿� ���� �� �ִ��� �˻�!
				iGroup = GetHT(*i1).GetGroup();
				if(iGroup == GROUP_BONUS) { continue; }
				if(iGroup == GROUP_ABILITY) { continue; }
				ForEachCElmt(HTList, lstOpen, i2, j2)
				{ // ���¿� �ش��п� ���� �� �ִ��� �˻�!
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

// �� �п� ���� Priority�� ���
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
		// �������� �����к���...^^;
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
			default : lBotPlatePriority += 50; // ��ġ#2
				break;
			}
		}

		///////////////////////////////////////////////////////////////////////
		// �������� ������ ���� Priority �ű�� 
		switch(iNoSameGroupOnOpen)
		{
		case 0:
			{	
				if((iNoSameGroupOnHold == 2) && (IsHardenedGroup(iGroup)))
				{ // �������� ��쿡�� 
					if((iType == HT_NONE) || (iType == HT_ONE)) {
						lBotPlatePriority += 40; // (��ġ#1����ũ����ġ#2���ٴ��۰�)
					}else {
						lBotPlatePriority += 35; // (��ġ#1����ũ����ġ#2���ٴ��۰�)
					}
				}
				else if(iNoSameGroupOnHold == 4)
				{ // ���� (4������)
					if((iType == HT_NONE) || (iType == HT_ONE)) {
						lBotPlatePriority += 50; // ��ġ#2
					}else {
						lBotPlatePriority += 45; // (��ġ#1����ũ����ġ#2���ٴ��۰�)
					}
				}
				else
				{ // ���ٶ��� ������ �� �ֱ�(���濡�� ���� �е��� ���Ѵ�) - ���� ����(3��)
					if((iType > HT_DOUBLE) && (m_aTypeCount[iType] > 1)) { // ������ ���� ����
						lBotPlatePriority +=  5;
					}else if(iType == HT_DOUBLE) {	// ���Ǵ�
						lBotPlatePriority += 10;
					}else if(iType == HT_KWANG) {	// ����
						lBotPlatePriority += 15;
					}else if(iType == HT_GODORI) {	// ���� 
						lBotPlatePriority += 20;
					}else if(iType > HT_ONE) {		// �ܵ� 
						lBotPlatePriority += 25;
					}else {							// �׿� �������� 
						lBotPlatePriority += 30;	// ��ġ#1
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

// ��� �ִ� �е��߿� �� �� �����ϱ� 
tPLATE CBot::SelectPlate()
{
	tPLATE iIndex = -1;
	HTList lstAbility;

	// �ʱ�ȭ 
	Initialize();
	lstAbility.clear();

	// Set ȭ���� ����
	const HTList& lstRobotHold = GetGI().GetHoldList(ROBOT_UI);
	if(lstRobotHold.empty())
	{	// is game over or lack
		if(GetGI().GetHTUser(ROBOT_UI).GetJustPlayCount() > 0)
		{
			// �׳� ������ �и� ���� ��� 
			return MAX_HT;
		}
		else
		{
			// ����!
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
	// ��� ����

	// ������ ������ �� �� Ÿ�Ժ� ���� 
	ComputeEnemyPlateTypeCount();
	// ����� ó�� 
	lstAbility.sort();
	ForEachCElmt(HTList, lstAbility, i, j)
	{
		iIndex = (*i); 
		//if(GetHT(iIndex).GetAbility() == HA_NONE) { continue; }
		if(CheckAbilityPlate(iIndex)) { return iIndex; }
	}
	// Set ȭ���� ����
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

	// ��� �ִ� �д� ������ ���� �а� ���� �׳� ������ �� ������
	if((lMaxPriority <= 30) && (GetGI().GetHTUser(ROBOT_UI).GetJustPlayCount() > 0))
	{ // ��ġ#1 --------��
		return MAX_HT;
	}

	/////////////////////////////////////////////////////////////////////////////////////
	// ���� ���� 
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

// �� ���� ���� ���߿� �Ѱ� ���� 
tPLATE CBot::ChoicePlate(const HTList& lstChoice)
{	// ���� �� �ΰ��� �ϳ� ����
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

// �� �Ǵ� ���� ���� 
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

	// �� Ÿ�Ժ� üũ 
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
	{ // �ٴڿ� ���Ѱ� ���� 
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
		{ // ���� ������ ���� ���� ���Ѱ� ������ 
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

// ���� ���� �ű� ������ 
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