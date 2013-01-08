/* file : TServerUserBase.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-31 15:09:09
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "TCommonServer.h"
#include "util/jRegistry.h"
#include "jServerGrid.h"

#include "../TCommonClient/protocal/PT_CentralServer_Enum.h"
using namespace nNET::nCentralServer;



void jServerGrid::ServerInfo_erase(serverid_t sid,bool isNotFoundLog)
{ 
	jAUTO_LOCK_CS(m_mapServerInfo_CS);
	m_mapServerInfo_it it = m_mapServerInfo.find(sid);
	if(it==m_mapServerInfo.end())
	{
		if(isNotFoundLog)
		{
			jWARN(" sid = %d", sid);
		}
		return;
	}
	m_mapServerInfo.erase(it);
}

void jServerGrid::ServerInfo_insert(jServerInfo& si)
{
	jAUTO_LOCK_CS(m_mapServerInfo_CS);
	m_mapServerInfo[si.m_sid] = si;
}


/*!
jServerInfo _si의 정보를이용해 자신의 PlugIn_Connect의 자식노드중 해당하는 ServerTag를 찾아
	자식노드의 SERVER_ONLINE_ACTION에 맞는 행동을 한다.
*/
jIPacketSocket_IOCP* jServerGrid::Do_SERVER_ONLINE_ACTION(jServerInfo& _si,tcstr szTag)
{
	tname1024_t buf12;
	jLOG("\004Do_SERVER_ONLINE_ACTION : %s", ToString(&_si,buf12));
	tcstr szServerType = ToString2(_si.m_eType);
	if(!m_pPlugIn)return 0;
	// jTODO m_pPlugIn에대한 락킹을 해야함.
	jIE* pePlugIn = m_pPlugIn->m_pE;
	jIE* pE = pePlugIn->Find(szServerType);
	if(!pE) return 0;

	jIVar* pV = pE->GetAttrVar(jS(SERVER_ONLINE_ACTION));
	if(!pV || pV->IsContents(jS(NULL))) return 0;
	
	cstr szCmd = pV->Get_cstr();
	if(jt_strstr(szCmd, jS(SAME_DOMAIN)))
	{
		if(jt_strcmp(_si.m_szDomain, m_MyInfo.m_szDomain ) !=0)
			return 0;
	}

	fname_t szIPS;
	js_sprintf(szIPS,_T("%s:%d"),(_si.m_szServiceIP), _si.m_service_port );


	if(jt_strstr(szCmd,jS(SINGLE)))
	{
		jIGridNode* pGN = this->find(_si.m_sid);
		jIPacketSocket_IOCP* _pS = (jIPacketSocket_IOCP*) pE->GetUserData(jS(jIPacketSocket_IOCP));
		if(_pS && _pS->IsConnected())
		{
			if(!pGN)
			{
				//jTODO : jIGridNode등록이 아직 안되서 그렇다. 로그상에서는 바로 담에 등록된다. 추후 다시 검증해보자.

				jWARN("jIGridNode* pGN = this->find(%d);못찾음 : %s",_si.m_sid, pE->GetTagName() );
				jDebugPrint(_T("jServerGrid"),this);
			}
			else
			{
				jSI_ret(pGN,0);
				*si = _si;
			}
			return 0;
		}
		jAssert0(!pGN);
		pE->Set_cstr(szIPS);
		pE->GetAttrVar(jS(ENABLE))->Set_bool(true);
		if(!m_pPlugIn) return 0;
		jIPacketSocket_IOCP* pS= m_pPlugIn->m_pClientSession->Start_ClientSocket(pE);
		if(pS)
		{
			jSI_ret(pS->GetGridNode(),0);
			*si = _si;
			jLOG("\004Do_SERVER_ONLINE_ACTION SINGLE : %s", ToString(&_si,buf12));

		}
		return pS;
	}
	if(jt_strstr(szCmd,jS(MULTI)))
	{
		fname_t szName;
		if(szTag)
			js_sprintf(szName, _T("%s_%d_%s"),szServerType,_si.m_sid,szTag);
		else
			js_sprintf(szName, _T("%s_sid_%d"),szServerType,_si.m_sid);

		jAssert0(jt_strlen(szName)<=jOBJECT_NAME);

		jIE* peNew = pePlugIn->Find(szName);
		if(!peNew)
		{
			peNew = pePlugIn->InsertChildElement(szName);
			pE->CopyTo(peNew);
			peNew->ChangeTagName(szName);
		}
		else
		{
			// 기존에 만들어 졌지만 접속이 끊긴 것이어야 한다.
			jAssert0( !peNew->GetUserData(jS(jINetSession_Service)) );
		}
		peNew->Set_cstr(szIPS);
		peNew->GetAttrVar(jS(ENABLE))->Set_bool(true);
		if(m_pPlugIn)
		{
			jIPacketSocket_IOCP* pS = m_pPlugIn->m_pClientSession->Start_ClientSocket(peNew);
			if(!pS) return 0;
			jSI_ret(pS->GetGridNode(),pS);
			*si = _si;
			jLOG("\004Do_SERVER_ONLINE_ACTION MULTI : %s", ToString(&_si,buf12));
			return pS;
		}
	}
	jLOG("\004Do_SERVER_ONLINE_ACTION 아무것도 안함");
	return 0;

}

void jServerGrid::ServerInfo_insert_from_vector(std::vector<jServerInfo>&v)
{
	jAUTO_LOCK_CS(m_mapServerInfo_CS);
	for(size_t i=0; i< v.size() ; ++i)
	{
		m_mapServerInfo[v[i].m_sid] = v[i];
	}
}


void jServerGrid::ServerInfo_update_userCnt(std::vector<serverid_t> sid,std::vector<uint16> userCnt)
{
	jAUTO_LOCK_CS(m_mapServerInfo_CS);
	for(size_t i=0; i< sid.size() ; ++i)
	{
		m_mapServerInfo[sid[i]].m_iTotClient = userCnt[i];
	}
}

jServerInfo* jServerGrid::ServerInfo_find(serverid_t sid)
{
	jAUTO_LOCK_CS(m_mapServerInfo_CS);
	m_mapServerInfo_it it = m_mapServerInfo.find(sid);
	if(it==m_mapServerInfo.end()) return 0;
	return &it->second;
}


bool jServerGrid::ParseCmd(tcstr szCommand)
{
	nswb1024_t sendBuf;
	if(m_sCurrParserType==jS(PC))
	{
		if(m_Central.size())
		{
			fname_t sendS;
			js_sprintf(sendS ,_T("%d-%s>%s") , m_MyInfo.m_sid, g_ExeEnv.m_szComputerName,szCommand);
			m_Central.WritePacket(WRITE_C_ECHO(sendBuf,sendS,0) );
			return true;
		}
	}
	return false;
}
bool jServerGrid::ParseRemoteCmd(tcstr szCommand,tcstr szSERVER_NAME)
{
	wfname_t szTag;
	jw_strcpy(szTag, szCommand+1);
	WCHAR *ch = jw_strchr(szTag, ' ');
	WCHAR * szCmd= ch+1;
	*ch =0;
	if(jw_strcmp(szTag,L"ALL") 
		&& m_MyInfo.m_eType != ToServerType_ByTag(jT(szTag))) return false;

	std::tstring strCmd = jT(szCmd);
	nSTL::replace(strCmd,_T("APP_NAME"),szSERVER_NAME);
	nCONSOLE::Get_jIConsoleCmd()->ParseCmd(jT(strCmd.c_str())); 

	return false;
}


jIPacketSocket_IOCP* jServerGrid::ConnectTo(cstr szServer ,serverid_t sid)
{

	jServerInfo *si=0;
	{
		si = ServerInfo_find(sid);
	}

	fname_t szIPS;
	jt_sprintf(szIPS,_T("%s:%d"),si->m_szServiceIP, si->m_service_port );
	if(!m_pPlugIn) return 0;

	jIE* pE = m_pPlugIn->m_pE->Find(szServer);
	if(!pE) return 0;
	jIE* peNew = GetjIXml()->CreateElement();
	peNew = pE->GetParent()->InsertChildElement(szServer);
	pE->CopyTo(peNew);
	peNew->Set_cstr(szIPS);
	peNew->GetAttrVar(jS(ENABLE))->Set_bool(true);
	fname_t sz;
	js_sprintf(sz,_T("%s_Connected"),szServer);
	peNew->ChangeTagName(szServer);
	if(!m_pPlugIn) return 0;
	return m_pPlugIn->m_pClientSession->Start_ClientSocket(peNew);
}


const int iMaxSendUser_U4_USER_CONNECTION_NOTIFY = 100;

void jServerGrid::Set_U4_USER_CONNECTION_NOTIFY_CS(player_id_t uid, wcstr id,bool isConnect)
{
	jAUTO_LOCK_CS(m_mapU4_USER_CONNECTION_NOTIFY_CS);
	m_mapU4_USER_CONNECTION_NOTIFY[id]=isConnect;
	if(m_mapU4_USER_CONNECTION_NOTIFY.size() < iMaxSendUser_U4_USER_CONNECTION_NOTIFY) return;

	nswb16000_t buf;
	vector<wstring> uid_connect,uid_disconnect;
	Make_U4_USER_CONNECTION_NOTIFY(uid_connect, uid_disconnect);
	if(!m_User.size())
	{
		jWARN1(_T("m_pToUser == NULL"));
	}
#ifdef jTSERVER_PREPARE
	else
	{
		m_User.WritePacket(&WRITE_U4_USER_CONNECTION_NOTIFY(buf, uid_connect, uid_disconnect));
	}

	if(m_MyInfo.m_eType==eChannel || m_MyInfo.m_eType==eGame)
	{
		if(uid_disconnect.size() && m_pToWorld)
			m_World.WritePacket(&nWorldServer::WRITE_W4_USER_DISCONNECT(buf, uid_disconnect));
	}
#endif
	m_mapU4_USER_CONNECTION_NOTIFY.clear();
}

bool jServerGrid::Make_U4_USER_CONNECTION_NOTIFY(vector<wstring>& uid_connect , vector<wstring>& uid_disconnect)
{
	jAUTO_LOCK_CS(m_mapU4_USER_CONNECTION_NOTIFY_CS);
	int is = m_mapU4_USER_CONNECTION_NOTIFY.size();
	if(!is) return false;

	m_mapU4_USER_CONNECTION_NOTIFY_it it = m_mapU4_USER_CONNECTION_NOTIFY.begin(), ie = m_mapU4_USER_CONNECTION_NOTIFY.end();
	int i=0, iCon=0 ,iDis=0;
	for(i=0;it!=ie;++it,++i)
	{
		if(it->second)
		{
			uid_connect.push_back(it->first);
			++iCon;
		}
		else
		{
			uid_disconnect.push_back(it->first);
			++iDis;
		}
	}

#ifdef _DEBUG
	jLOG1(_T("1Make_U4_USER_CONNECTION_NOTIFY: uid_disconnect.size()=%d uid_connect.size()=%d"), iDis, iCon);
#endif

	m_mapU4_USER_CONNECTION_NOTIFY.clear();
	return is;
}

#ifdef jTSERVER_PREPARE
void jServerGrid::test_dc_echo()
{
	m_listToDBCache_it it = m_listToDBCache.begin(), ie = m_listToDBCache.end();
	nswb256_t buf;
	for( ; it!=ie ; ++it)
	{
		it->second->WritePacket(&WRITE_DC_ECHO(buf,_T("asdf "),0));
	}
}
#endif



void jServerGrid::generate_server_name(IN tcstr szName, OUT fname_t szServerName)
{
	nMech::nUtil::CRegistry reg;
	reg.Open(_T("SOFTWAREjGamejAqServer"),HKEY_LOCAL_MACHINE);
	if(!reg[_T("name_number")].Exists()) reg[_T("name_number")] = (int)0;
	int name_number = reg[_T("name_number")];
	jt_sprintf_s(szServerName,256,_T("%s_%d"),szName,name_number);
	++name_number;
	reg[_T("name_number")]=name_number;
	reg.Close();
}

void debug_jNetGrid(tcstr s, jINetGrid* pNG)
{
	jLOG("debug_jNetGrid : %s",s);

	jLAMDA_for_each0(debug_jIGridNode,jIGridNode*)
	{
		jIE* peSocket = it->m_pS->Get_jIE();
		jIE* pePlugIn = it->m_pPlugIn->m_pE;
		jSI(it);
		tname1024_t buf;
		jLOG("%s.%s %s",pePlugIn->GetTagName(),it->GetGridName(), ToString(si,buf));
	}
	jLAMDA_end();

	pNG->_for_each(0,nNET::for_each_grid_t(debug_jIGridNode()) );
}

jCONSOLE_CMD_AUTO(TCommonServer, print_jINetGrid,0,"print jINetGrid node"," ")
{
	nInterface::g_pjINet_OGS->for_each_jINetGrid(debug_jNetGrid);
	return true;
}


