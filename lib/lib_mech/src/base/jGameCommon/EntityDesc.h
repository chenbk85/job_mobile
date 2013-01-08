//////////////////////////////////////////////////////////////////////
//
//  Game Source Code
//
//  File: EntityDesc.h
//  Description: Entity description utility class used for the creation of the entities.
//
//  History:
//  - 08/16/2001: Alberto Demichelis created
//  - 12/04/2003: MM optimized, cleaned up
//
//////////////////////////////////////////////////////////////////////

#ifndef GAME_ENTITYDESC_H
#define GAME_ENTITYDESC_H

#include "Stream.h"
#include "IEntityRenderState.h"
#include <string>


struct IEntityContainer;

template<int _max_size> class SafeString
{
public:
	SafeString(){
		memset(m_s,0,_max_size);
	}
	SafeString &operator =(const string &s)
	{
		assert( s.length() < _max_size );
		strcpy(m_s,s.c_str());
		return *this;
	}
	SafeString &operator =(const char *s) 
	{
		assert( s );
		assert( strlen(s) < _max_size );
		strcpy(m_s,s);
		return *this;
	}
	operator const char*() const
	{
		return m_s;
	}
	operator const char*()
	{
		return m_s;
	}
	const char *c_str() const {return m_s;}
	const char *c_str() {return m_s;}
	int length(){return strlen(m_s);}
private:
	char m_s[_max_size];
};


/*!
	CEntityDecs class is an entity description.
  This class describes what kind of entity needs to be spawned, and is passed to entity system when an entity is spawned. This
	class is kept in the entity and can be later retrieved in order to (for example) clone an entity.
	@see IEntitySystem::SpawnEntity(CEntityDesc &)
	@see IEntity::GetEntityDesc()
 */
typedef SafeString<256> CEntityDesc_string_t123;;
#if 1
	typedef SafeString<256> CEntityDesc_string_t;
#else
	typedef char CEntityDesc_string_t[256];
	//typedef std::string CEntityDesc_string_t;
#endif


#define CEntityDesc_FLAG \
	int m_iFlag;\
	jSET_FLAG(_HasOwner, jBIT_0);\

class CEntityDesc
{
public:  
	int m_iCEntityDesc_FLAG_Data;
	CEntityDesc_FLAG;

	//! the net unique identifier (EntityId)
	nMech::int32										id;						
	//! the name of the player... does not need to be unique
	CEntityDesc_string_t				name;	
	//! player, weapon, or something else - the class id of this entity
	EntityClassId						ClassId;
  //! specify a model for the player container
	CEntityDesc_string_t					sModel;

	nMech::nMath::jVec3										vColor;			//!< used for team coloring (0xffffff=default, coloring not used)

	//! this is filled out by container, defaults to ANY
	bool										netPresence;	
	//! the name of the lua table corresponding to this entity
	CEntityDesc_string_t					className;								
	nMech::nMath::jVec3										pos;
	nMech::nMath::jVec3										angles;
	float										scale;
	void *									pUserData;			//! used during loading from XML

	nMech::nLUA1::IScriptObject *pProperties;
	nMech::nLUA1::IScriptObject *pPropertiesInstance;
	~CEntityDesc(){};
	CEntityDesc()
	{
		className = "";
		id = 0;
		netPresence = true;
		ClassId = 0;
		sModel= "";
		pUserData =0;
		pProperties=NULL;
		pPropertiesInstance=NULL;
		angles(0,0,0);
		pos(0,0,0);
		scale = 1;
		vColor=nMech::nMath::jVec3(1,1,1);	// default, colour not used

		m_iCEntityDesc_FLAG_Data=0;
		m_iFlag=0;

	}
	CEntityDesc( int _id, const EntityClassId _ClassId )
	{
		className = "";
		id = _id;
		netPresence = true;
		ClassId = _ClassId;	
		sModel= "";
		pUserData =0;
		pProperties=NULL;
		pPropertiesInstance=NULL;
		angles(0,0,0);
		pos(0,0,0);
		scale = 1;
		vColor=nMech::nMath::jVec3(1,1,1);	// default, colour not used

		m_iCEntityDesc_FLAG_Data=0;
		m_iFlag=0;

	}
	CEntityDesc( const CEntityDesc &d ) { *this = d; };
	CEntityDesc& operator=( const CEntityDesc &d )
	{
		className = d.className;
		id = d.id;
		netPresence = d.netPresence;
		ClassId= d.ClassId;
		sModel= d.sModel;
		pos = d.pos;
		angles = d.angles;
		pProperties=d.pProperties;
		pPropertiesInstance=d.pPropertiesInstance;
		vColor=d.vColor;
		scale = d.scale;
		m_iCEntityDesc_FLAG_Data=d.m_iCEntityDesc_FLAG_Data;
		m_iFlag=d.m_iFlag;

		return *this;
	}
	bool Write( nMech::nJC_stream::IBitStream *pIBitStream, nMech::nJC_stream::CStream &stm);
	bool Read( nMech::nJC_stream::IBitStream *pIBitStream, nMech::nJC_stream::CStream &stm);
	bool IsDirty(){		return true;	}
};

///////////////////////////////////////////////



///////////////////////////////////////////////
inline bool CEntityDesc::Write( nMech::nJC_stream::IBitStream *pIBitStream, nMech::nJC_stream::CStream &stm )
{
	WRITE_COOKIE(stm);

	if(!pIBitStream->WriteBitStream(stm,id,nMech::nJC_stream::eEntityId))
		return false;

	if(name.length())
	{
		stm.Write(true);
		stm.Write(name.c_str());
	}
	else
		stm.Write(false);

	if(!pIBitStream->WriteBitStream(stm,ClassId,nMech::nJC_stream::eEntityClassId))
		return false;

	if(sModel.length())
	{
		stm.Write(true);
		stm.Write(sModel);
	}
	else
	{
		stm.Write(false);
	}
	if((*((unsigned int *)(&pos.x))==0)
		&& (*((unsigned int *)(&pos.y))==0)
		&& (*((unsigned int *)(&pos.z))==0))
	{
		stm.Write(false);
	}
	else
	{
		stm.Write(true);
		stm.Write(pos);
	}
		
	if(vColor!=nMech::nMath::jVec3(1,1,1))
	{
		stm.Write(true);
		stm.Write((unsigned char)(vColor.x*255.0f));
		stm.Write((unsigned char)(vColor.y*255.0f));
		stm.Write((unsigned char)(vColor.z*255.0f));
	}
	else
		stm.Write(false);

	stm.Write(m_iFlag);
	if(m_iFlag)
	{
		stm.Write(m_iCEntityDesc_FLAG_Data);
	}

	WRITE_COOKIE(stm);
	return true;
}

///////////////////////////////////////////////
inline bool CEntityDesc::Read( nMech::nJC_stream::IBitStream *pIBitStream, nMech::nJC_stream::CStream &stm )
{
	bool bModel,bName,bPos,bTeamColor;
	static char sTemp[250];
	VERIFY_COOKIE(stm);

	if(!pIBitStream->ReadBitStream(stm,id,nMech::nJC_stream::eEntityId))
		return false;

	stm.Read(bName);
	if(bName)
	{
		stm.Read(sTemp,250);
		name=sTemp;
	}
	
	if(!pIBitStream->ReadBitStream(stm,ClassId,nMech::nJC_stream::eEntityClassId))
		return false;

	stm.Read(bModel);
	if(bModel)
	{
		stm.Read(sTemp,250);
		sModel=sTemp;
	}

	stm.Read(bPos);
	if(bPos)
		stm.Read(pos);
	 else
		pos=nMech::nMath::jVec3(0,0,0);

	stm.Read(bTeamColor);
	if(bTeamColor)
	{
		unsigned char x,y,z;
		stm.Read(x);stm.Read(y);stm.Read(z);

		vColor=nMech::nMath::jVec3(x/255.0f,y/255.0f,z/255.0f);
	}
	else
		vColor=nMech::nMath::jVec3(1,1,1);

	stm.Read(m_iFlag);
	if(m_iFlag)
	{
		stm.Read(m_iCEntityDesc_FLAG_Data);
	}


	VERIFY_COOKIE(stm);
	return true;
}

#endif // GAME_ENTITYDESC_H
