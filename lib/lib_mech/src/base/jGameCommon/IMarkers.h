#ifndef _IMARKERS_H_
#define _IMARKERS_H_

typedef struct ITagPoint
{
	virtual void GetPos(nMech::nMath::jVec3 &pos) = 0;
	virtual void SetPos(const nMech::nMath::jVec3 &pos) = 0;

	virtual void GetAngles(nMech::nMath::jVec3 &angles) = 0;
	virtual void SetAngles(const nMech::nMath::jVec3 &angles) = 0;

	virtual bool SetName(const char *pName) = 0;
	virtual char *GetName() = 0;

	virtual void Release()= 0;
	
} ITagPoint;


struct IXArea
{
public:
	virtual ~IXArea() {};

	virtual void	SetPoints(const nMech::nMath::jVec3* const vPoints, const int count) = 0;
	virtual void	SetID( const int id ) = 0;
	virtual int		GetID() const  = 0;
	virtual void	SetGroup( const int id) = 0;
	virtual int		GetGroup( ) const = 0;
	virtual void	AddEntity( const char* const clsName ) = 0;
	virtual void	ClearEntities( ) = 0;

	virtual void	SetCenter( const nMech::nMath::jVec3& center ) = 0;
	virtual void	SetRadius( const float rad ) = 0;

	virtual void	SetMin( const nMech::nMath::jVec3& min ) = 0;
	virtual void	SetMax( const nMech::nMath::jVec3& max ) = 0;
	virtual void	SetTM( const nMech::nMath::Matrix44& TM ) = 0;

	virtual void	SetVOrigin( float org )		= 0;
	virtual void	SetVSize( float sz=0.0f )	= 0;


//	virtual void	SetEntityName( const char* const clsName ) = 0;
//	virtual char*	GetEntityName( ) = 0;
	virtual void	SetProximity( float prx ) = 0;
	virtual float	GetProximity( ) = 0;

};

struct IXAreaMgr
{
public:
	virtual void RetriggerAreas() = 0;

	virtual IXArea *CreateArea( const nMech::nMath::jVec3d *vPoints, const int count, const std::vector<string>	&names, 
		const int type=0, const int groupId=-1, const float width=0.0f, const float height=0.0f) = 0;
	virtual IXArea *CreateArea( const nMech::nMath::jVec3d& min, const nMech::nMath::jVec3d& max, const nMech::nMath::Matrix44& TM, const std::vector<string>	&names, 
		const int type=0, const int groupId=-1, const float width=0.0f) = 0;
	virtual IXArea *CreateArea( const nMech::nMath::jVec3d& center, const float radius, const std::vector<string>	&names, 
		const int type=0, const int groupId=-1, const float width=0.0f) = 0;
	virtual IXArea*	GetArea( const nMech::nMath::jVec3& point ) = 0;

	virtual void	DeleteArea( const IXArea* aPtr ) = 0;
};

#endif// _IMARKERS_H_