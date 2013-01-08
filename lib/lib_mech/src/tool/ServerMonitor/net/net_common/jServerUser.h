/* file : jServerUser.h
Coder : by icandoit ( mech12@nate.com)
Date : 2009-02-23 09:58:26
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jServerUser_header__
#define __jServerUser_header__
#pragma once



template <typename USER_CLASS,typename USER_CLASS_id_t>
struct jServerUsers : public jIPlugIn_Server_IOCP
{
	typedef USER_CLASS usertype_t;
	typedef nMech::nDataStruct::yVector<USER_CLASS> 	m_ConnectUsers_t; 
private:
	m_ConnectUsers_t m_ConnectUsers;
	nUtil::jCriticalSection m_ConnectUsers_CS;
public:
	size_t size(){return m_ConnectUsers.size(); };
	void start(){m_ConnectUsers.clear();}

	template <class _Predicate>
	void for_each(_Predicate __pred ) {nUtil::jCriticalSection::Auto a(&m_ConnectUsers_CS);m_ConnectUsers.for_each(__pred);}
	template <class _Predicate>
	USER_CLASS *find_if(_Predicate __pred )
	{
		nUtil::jCriticalSection::Auto a(&m_ConnectUsers_CS);
		m_ConnectUsers_t::iterator it = m_ConnectUsers.find_if(__pred);
		return it==m_ConnectUsers.end() ? 0 : it;
	}

	void send_all(jPacket_Base& pk,jIPacketSocket_IOCP* pSockOwner)
	{
		nUtil::jCriticalSection::Auto a(&m_ConnectUsers_CS);
		m_ConnectUsers_t::iterator it = m_ConnectUsers.begin(),ie= m_ConnectUsers.end();
		for( ; it!=ie ;++it )
		{
			if(it->m_pS==pSockOwner) continue;
			it->Write_Packet(pk);
		}
	}
	USER_CLASS* push_back(jIPacketSocket_IOCP* pS)
	{
		nUtil::jCriticalSection::Auto a(&m_ConnectUsers_CS);
		m_ConnectUsers_t::iterator it = m_ConnectUsers.push_back();
		it->m_pS=pS;
		pS->SetUserData(&(*it));
		return it;
	}
	void erase(USER_CLASS* it)
	{
		nUtil::jCriticalSection::Auto a(&m_ConnectUsers_CS);
		if(it->m_pS)it->m_pS->SetUserData(0);
		m_ConnectUsers.erase(it);
	}
	USER_CLASS* get_user(jIPacketSocket_IOCP* pS)
	{
		return (USER_CLASS*)pS->GetUserData();
	}
	struct _jxFindUser_by_uid
	{
		USER_CLASS_id_t uid;
		_jxFindUser_by_uid(USER_CLASS_id_t _uid):uid(_uid){}
		bool operator ()(USER_CLASS& it){return it.GetUID()==uid;}
	};

	USER_CLASS* find_user(USER_CLASS_id_t uid)
	{
		nUtil::jCriticalSection::Auto a(&m_ConnectUsers_CS);
		m_ConnectUsers_t::iterator it = m_ConnectUsers.find_if(_jxFindUser_by_uid(uid));
		return it==m_ConnectUsers.end() ? 0 : it;
	}
	USER_CLASS* find_by_handle(uint iHandle){return m_ConnectUsers.GetNode(iHandle);}
	USER_CLASS* push_back_if_not_found(jIPacketSocket_IOCP* pS)
	{
		nUtil::jCriticalSection::Auto a(&m_ConnectUsers_CS);
		USER_CLASS * pUser = get_user(pS);
		if( pUser )  
		{
			jWARN(_T("push_back_if_not_found : !!!"));
			return pUser;
		}
		m_ConnectUsers_t::iterator it = m_ConnectUsers.push_back();
		it->m_pS=pS;

		pS->SetUserData(&(*it));
		return it;
	}

	//	jIPlugIn_Server_IOCP helper function
	void DisconnectTcpClient(USER_CLASS* pUser){m_pServer->DisconnectTcpClient(pUser->m_pS);}
	void DisconnectTcpClient(USER_CLASS_id_t id)
	{
		USER_CLASS* pUser = find_user(id);
		if(!pUser) 
		{
			fname_t szBuf;
			jWARN(_T("uid not found %s"), ToString(id, szBuf));
			return;
		}
		DisconnectTcpClient(pUser);
	}


};


#endif // __jServerUser_header__
