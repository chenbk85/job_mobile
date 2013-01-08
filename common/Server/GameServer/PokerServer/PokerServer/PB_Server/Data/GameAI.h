// GameAI.h: interface for the GameAI class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEAI_H__C1FA7196_A292_433B_BE2F_13E759A015A2__INCLUDED_)
#define AFX_GAMEAI_H__C1FA7196_A292_433B_BE2F_13E759A015A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GameInfo.h"

#define ROBOT_UI	1
#define ENEMY_UI	0

typedef int	tPLATE;

struct sPossibilityVector
{
	LONG	lBotPlate;
	LONG	lBotPlatePriority;
};
typedef list<sPossibilityVector> tPOSSIBILITYLIST;


class CRoomContext;
class CHT;
class CBot
{
public:
	CBot();
	virtual ~CBot();
	virtual void Clear();

public:
	void SetRoomContext(CRoomContext* const pContext) { m_pContext = pContext; }
	CGameInfo& GetGI();
	CHT& GetHT(int idx);

protected:
	void	Initialize();
	BOOL	IsSameGroup(tPLATE A, tPLATE B);
	LONG	NoOfSameGroupOnBoard(tPLATE pl);
	LONG	NoOfSameGroupOnBot(tPLATE pl);
	void	ComputeEnemyPlateTypeCount();
	BOOL	CheckAbilityPlate(tPLATE iIndex);
	void	CaseGenerate();

public:
	void	AddGroupEaten(int iGroup) {	m_aGroupCount[iGroup]++; }
	BOOL	IsHardenedGroup(int iGroup);
	tPLATE	SelectPlate();
	tPLATE	ChoicePlate(const HTList& lstChoice);
	BOOL	ChoiceGoStop();
	BOOL	ChoiceMoveTen();

public:
	tPOSSIBILITYLIST m_lstPossibility;
	int	m_aTypeCount[HT_MAX];		// 상대방이 먹은 패들 
	int m_aGroupCount[MAX_GROUP+1];	//	

protected:
	CRoomContext* m_pContext;
public:
	SYNTHESIZE(LONG,Key)

	//#pragma comment(warning,"일단 옮김. 나중에 어떤 오브젝트로 나눌지는 생각해 봐야함.")
	int		AutoSelectHT(int iUI, BOOL bAI=TRUE);
	//------------------------------------------------------------------
};


#endif // !defined(AFX_GAMEAI_H__C1FA7196_A292_433B_BE2F_13E759A015A2__INCLUDED_)
