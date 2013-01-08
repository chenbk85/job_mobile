#ifndef _IAISYSTEM_H_
#define _IAISYSTEM_H_


#include <jc_Math.h>
//#include <..\jcAISystem\jcAISystem.h>


class IPhysicalEntity;
class IPhysicalWorld;
class	nMech::jcISizer;
struct IClient;
struct IAgentProxy;
struct IAgent;
struct IAIObject;
struct IGoalPipe;
struct IGraph;
struct ObstacleData;

enum EnumAreaType
{
		AREATYPE_PATH,
		AREATYPE_FORBIDDEN,
		AREATYPE_NAVIGATIONMODIFIER,
		AREATYPE_OCCLUSION_PLANE,
};


#define	AIFAF_VISIBLE_FROM_REQUESTER  1 	//! Requires whoever is requesting the anchor to also have a line of sight to it
#define AIFAF_VISIBLE_TARGET		  2 	//! Requires that there is a line of sight between target and anchor

typedef struct AIBalanceStats
{
	int nAllowedDeaths;
	int nTotalPlayerDeaths;
	int nEnemiesKilled;
	int nShotsFires;
	int nShotsHit;
	int nCheckpointsHit;
	int nVehiclesDestroyed;
	int nTotalEnemiesInLevel;
	int nSilentKills;
	
	float fAVGEnemyLifetime;
	float fAVGPlayerLifetime;
	float fTotalTimeSeconds;

	bool bFinal;

	AIBalanceStats(){	memset(this , 0, sizeof(*this));	}

} AIBalanceStats;

typedef struct IAutoBalance
{
	virtual void RegisterPlayerDeath()=0;
	virtual void RegisterPlayerFire(int nShots)=0;
	virtual void RegisterPlayerHit()=0;
	virtual void RegisterEnemyLifetime(float fLifeInSeconds)=0;
	virtual void RegisterVehicleDestroyed(void)=0;
	virtual void SetAllowedDeathCount(int nDeaths)=0;
	virtual void Checkpoint()=0;

	virtual void GetAutobalanceStats(AIBalanceStats & stats)=0;

	virtual void SetMultipliers(float fAccuracy, float fAggression, float fHealth)=0;
	virtual void GetMultipliers(float & fAccuracy, float & fAggression, float & fHealth)=0;

} IAutoBalance;

/*! Interface to AI system. Defines functions to control the ai system.
*/
typedef struct IAISystem
{
	//! Initialize the ai system 
	virtual bool Init(ISystem* pSys, const char *szLevel, const char *szMissionName) = 0;
	//! Release the system
	virtual void ShutDown() = 0;
	//! Update system. This function is called every frame
	virtual void Update() = 0;

	virtual void FlushSystem(void) = 0;

	virtual const ObstacleData GetObstacle(int nIndex) = 0;

	//! Create an ai representation for an object
	virtual IAIObject *CreateAIObject(unsigned short type, void *pAssociation) = 0;

	virtual IGoalPipe *CreateGoalPipe(const char *pName) = 0;
	virtual IGoalPipe *OpenGoalPipe(const char *pName) = 0;

	virtual IAIObject *GetAIObjectByName(unsigned short type, const char *pName) = 0;

	virtual IAIObject *GetNearestObjectOfType(const nMech::nMath::jVec3 &pos, unsigned int type, float fRadius, IAIObject* pSkip=NULL ) = 0;

	virtual IAIObject *GetNearestObjectOfType(IAIObject *pObject , unsigned int type, float fRadius, int nOption = 0) = 0;

	virtual IAIObject *GetNearestToObject( IAIObject *pRef , unsigned short nType, float fRadius) = 0;

	virtual void Release() = 0;

	virtual void Reset() = 0;

	virtual void RemoveObject(IAIObject *pObject) = 0;

	virtual void SoundEvent( int soundid, const nMech::nMath::jVec3 &pos, float fRadius, float fThreat, float fInterest, IAIObject *pObject) = 0;
		

	virtual bool CreatePath(const char *szPathName, EnumAreaType aAreaType = AREATYPE_PATH, float fHeight = 0) = 0;

	virtual void AddPointToPath(const nMech::nMath::jVec3 &pos, const char *szPathName, EnumAreaType aAreaType = AREATYPE_PATH) = 0;

	virtual void DeletePath(const char *szPathName) = 0;

	virtual void SendSignal(unsigned char cFilter, int nSignalId,const char *szText,  IAIObject *pSenderObject) = 0;

	virtual void SendAnonimousSignal(int nSignalId,const char *szText, const nMech::nMath::jVec3 &pos, float fRadius, IAIObject *pSenderObject) = 0;

	virtual void LoadTriangulation( const char *, const char *) = 0;

	virtual int GetGroupCount(int groupID) = 0;

	virtual void SetAssesmentMultiplier(unsigned short type, float fMultiplier) = 0;

	virtual void SetSpeciesThreatMultiplier(int nSpeciesID, float fMultiplier) = 0;

	virtual IGraph *GetNodeGraph() = 0;

	virtual IGraph *GetHideGraph() = 0;

	virtual bool CheckInside(const nMech::nMath::jVec3 &pos, int &nBuildingID, IVisArea *&pArea, bool bIgnoreSpecialAreas = false) = 0;

	virtual IAutoBalance * GetAutoBalanceInterface(void) = 0;

	virtual	void DumpStateOf(IAIObject * pObject) = 0;

	// debug members ============= DO NOT USE
	virtual void DebugDraw(IRenderer *pRenderer) = 0;
	
	virtual float GetPerceptionValue( IAIObject *pObject) = 0;

	virtual int GetAITickCount() = 0;

	virtual	void GetMemoryStatistics(nMech::jcISizer *pSizer) = 0;

	virtual void SetTheSkip(IPhysicalEntity* pSkip) = 0;

	virtual bool IntersectsForbidden(const nMech::nMath::jVec3 & vStart, const nMech::nMath::jVec3 & vEnd, nMech::nMath::jVec3 & vClosestPoint) = 0;
} IAISystem;

#endif //_IAISYSTEM_H_

