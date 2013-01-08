/* file : AqClientUser.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:41:55
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef __AqClientUser_header__
#define __AqClientUser_header__
#pragma once



#include "../AqCommon/AqClientUserBase.h"
#include "../AqCommon/jXmlSaveManager.h"
#include "network/jPlayer.h"

struct AqClientUser_T : public _AqClientUserBase 
	, public jPlayer
	, public nDataStruct::yVectorNode<AqClientUser_T>
{
	jDECLEAR_YVECTOR_MANAGER(AqClientUser_T);
	int m_iFlag;
	jSET_FLAG(_m_User,jBIT_0);// m_User가 수정되면 1이됨
	jSET_FLAG(_m_iCurrTown,jBIT_1); //m_iCurrTown가 수정되면 1이됨

	jIE* FindTownBYTUID(Use_Town_id_t tuid);
	
	vector<jHeroSkill> m_Skill;
	vector<jHeroItem> m_item;

	virtual void Create()
	{
		jPlayer::_Create();
		_AqClientUserBase::_Create();
		m_eUser_file_db.clear();

	}
	virtual void Destroy()
	{
		if(m_eUser_file_db.full())
		{
			m_eUser_file_db->GetDoc()->Save();
			//g_jXmlSaveManager.SaveDoc(,true);
			m_eUser_file_db.clear();
		}
		_AqClientUserBase::_Destroy();
	}
	virtual void CopyFrom(const AqClientUser_T& o)
	{
		jAssert0(0 && "AqClientUser_T::CopyFrom");
	}
	void Change_CurrTown(townid_t tid);
};

typedef AqClientUser_T AqClientUser;


#endif // __AqClientUser_header__
