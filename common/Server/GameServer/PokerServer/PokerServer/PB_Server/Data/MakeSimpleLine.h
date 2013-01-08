//------------------------------------------------------------------------------------
// Module Name			: MakeSimpleLine(.h)
// First Modified Date	: 2010/07/02
// Author				: Neowiz SmartP Team
//						  Byoung-Tae,Ahn(anbyt@neowiz.com)
// Description			: Make easy define
//------------------------------------------------------------------------------------


#pragma once

// Easy refer Project Objects
#define _ROOM(key) (dynamic_cast<CProjectRoom*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::ROOM)))
#define _USER(key) (dynamic_cast<CProjectUser*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::USER)))
#define _GAMEINFO(key) (dynamic_cast<CProjectGameInfo*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::GAMEINFO)))
#define _ROBOT(key) (dynamic_cast<CProjectRobot*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::ROBOT)))
#define _CARD(key) (dynamic_cast<CProjectCard*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::CARD)))
#define _SENDER(key) (dynamic_cast<CProjectSender*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::SENDER)))
#define _RECVER(key) (dynamic_cast<CProjectRecver*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::RECVER)))
#define _ITEM(key) (dynamic_cast<CProjectItem*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::ITEM)))
#define _DB(key) (dynamic_cast<CProjectDB*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::DB)))
#define _RANKING(key) (dynamic_cast<CProjectRanking*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::RANKING)))
#define _CNS(key) (dynamic_cast<CProjectCns*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::CNS)))
#define _TIMER(key) (dynamic_cast<CProjectTimer*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::TIMER)))
#define _PROC(key) (dynamic_cast<CProjectProc*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::PROC)))
#define _USERMSG(key) (dynamic_cast<CProjectUserMsg*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::USERMSG)))
#define _LOGIC(key) (dynamic_cast<CProjectLogic*>(GObjectPool().FindObjectPool(key)->FindObject(CProjectObjectSet::LOGIC)))

// Easy refer Project ObjectSet
#define _SET(key) GObjectPool().FindObjectPool(key)


// Easy make Getter/Setter
#define SYNTHESIZE(Type,Name) \
	Type m_##Name;\
	void Set##Name( Type Name ) { m_##Name = Name; }\
	Type Get##Name() { return m_##Name; }

// Easy make objectset room context call
#define PREFIX_OBJECTSET_CONTEXT_CALL_LONG \
	ClearErrorInformation();\
	MAP_OBJ::iterator it = m_Map.begin();\
	for ( ; it != m_Map.end(); ++it )\
	{\
		VALUE_OBJ* pValue = it->second;\
		if ( pValue != NULL )\
		{

#define POSTFIX_OBJECTSET_CONTEXT_CALL_LONG \
			if ( m_lErrorCode != ERROR_CODE_OK )\
			{\
				m_strErrorOccuredObject = pValue->GetName();\
				return m_lErrorCode;\
			}\
		}\
	}\
	return m_lErrorCode;
#define PREFIX_OBJECTSET_CONTEXT_CALL_BOOL \
	BOOL bRet = TRUE;\
	ClearErrorInformation();\
	MAP_OBJ::iterator it = m_Map.begin();\
	for ( ; it != m_Map.end(); ++it )\
	{\
		VALUE_OBJ* pValue = it->second;\
		if ( pValue != NULL )\
		{

#define POSTFIX_OBJECTSET_CONTEXT_CALL_BOOL \
			if ( ! bRet )\
			{\
				m_strErrorOccuredObject = pValue->GetName();\
				return FALSE;\
			}\
		}\
	}\
	return TRUE;