/* file : jPlayerBase.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-09-04 14:43:48
comp.: wiki.aqrius.com
title : 
desc : 

*/

#ifndef ___UserZoneInfo_header__
#define ___UserZoneInfo_header__
#pragma once

#include "header/jBoost.h"

struct AQ_SERVER_LIB_API jPlayerBase :public nDataStruct::yVectorNode<jPlayerBase>
{
	userid_t m_uid;//user db에서의 식별자
	aname32_t m_ip;
	username_t m_szID;
	serverid_t m_sid_world;
	int m_iFlag;
private:
	serverid_t m_ConnectedServer[jServerInfo::eEND_EServerTypeFrontEnd];
public:
	SYSTEMTIME m_LoginTime;
	userid_t Get_uid(){ return m_uid;}

	jSET_FLAG(_GoingTo_Logout,jBIT_0);
	jSET_FLAG(_IsDeleted,jBIT_1);
	jSET_FLAG(_IsDuplicated_so_GoingTo_Logout,jBIT_2);
	jSET_FLAG(_GoingTo_Login,jBIT_3);
	

	//--------------------------------------------------------------------------
	// jVectorNode virtual func
	//--------------------------------------------------------------------------
	jDECLEAR_YVECTOR_MANAGER(jPlayerBase);

	jPlayerBase():m_iFlag(0){}
	virtual void Create()
	{
		memset(m_ConnectedServer, 0, sizeof(m_ConnectedServer));
		m_uid.m_id = 0;
		m_iFlag=0;
		m_szID[0]=0;
	}

	virtual void Destroy()
	{
		m_iFlag=0;
		SetFlag_IsDeleted(true);
	}

	virtual void CopyFrom(const jPlayerBase& o)
	{
		jAssert0(0 && "AqConnectedServerNode::CopyFrom");
	}

	serverid_t &Get_ConnectedServer(jServerInfo::EServerType eType)
	{
		if(eType>jServerInfo::eEND_EServerTypeFrontEnd)
		{
			static serverid_t sid=0;
			sid =0;
			return sid;
		}

		return m_ConnectedServer[eType];
	}

	void Set_ConnectedServer(jServerInfo::EServerType eType,serverid_t sid)
	{
		if(eType>jServerInfo::eEND_EServerTypeFrontEnd)
			return;

		m_ConnectedServer[eType] = sid;
	}

	bool IsConnectedServer()
	{
		return m_ConnectedServer[jServerInfo::eLogin] 
		|| m_ConnectedServer[jServerInfo::eTown] 
		|| m_ConnectedServer[jServerInfo::eDungeon];
	}

};//struct jPlayerBase :public nDataStruct::yVectorNode<jPlayerBase>

extern AQ_SERVER_LIB_API tcstr ToString(jPlayerBase* pUser , tname1024_t bufOut);

struct AQ_SERVER_LIB_API jUserZoneInfoList
{

private:
#pragma warning ( disable:4251)
	jLIST_TYPEDEF_YVECTOR(jPlayerBase,m_UserZoneList);
	jLIST_TYPEDEF_map(astring,jPlayerBase*,m_mapUser_by_idname);
	jLIST_TYPEDEF_map(userid_t,jPlayerBase*,m_mapUser_by_uid);

#pragma  warning ( default:4251 )
	// _로 시작하는 것은 락을 안건다.
	jPlayerBase* _push_back(IN username_t id);
	jPlayerBase* _find_by_username(acstr id);
	jPlayerBase* _find_by_uid(userid_t uid);
	jPlayerBase* _find_in_yvector(username_t id);
	jPlayerBase* _find_in_yvector(userid_t uid);

public:
	void Clear()
	{
		m_UserZoneList.clear();
		m_mapUser_by_uid.clear();
		m_mapUser_by_idname.clear();
	}
	//nUtil::jCriticalSection m_UserZoneList_CS;
//#define __ASDF9823IOACKDFIE jAUTO_LOCK_CS(m_UserZoneList_CS)
#define __ASDF9823IOACKDFIE 
	void	erase_by_name(acstr id);
	void	erase_by_uid(userid_t uid);
	jPlayerBase* find_by_username(acstr id){__ASDF9823IOACKDFIE; return _find_by_username(id);}
	jPlayerBase* find_by_uid(userid_t uid){__ASDF9823IOACKDFIE; return _find_by_uid(uid);}
	jPlayerBase* find_in_yvector(username_t id){__ASDF9823IOACKDFIE; return _find_in_yvector(id);}
	jPlayerBase* find_in_yvector(userid_t uid){__ASDF9823IOACKDFIE; return _find_in_yvector(uid);}
	void	Regist_by_uid(jPlayerBase* pUser,userid_t uid);
	
	jPlayerBase* push_back_with_world_sid(username_t szID,serverid_t world_sid);
	void for_each(function<void(jPlayerBase&)> f){m_UserZoneList.for_each(f);}
	void erase(jPlayerBase* pUser){erase_by_name(pUser->m_szID);}


#define jLAMDA_to_string(X,Z) \
	Z(vector<tstring>& ,users)
	jLAMDA_for_each(to_string,jPlayerBase&)
	{
		fname_t buf;
		users.push_back(ToString(&it,buf));
	}
	jLAMDA_end()

};



#endif // ___UserZoneInfo_header__
