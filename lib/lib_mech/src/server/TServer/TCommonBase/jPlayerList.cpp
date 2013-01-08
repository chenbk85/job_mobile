/* file : jPlayerList.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-19 20:03:25
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jPlayerList.h"



namespace nMech
{
	namespace nServerLogic
	{


		//--------------------------------------------------------------------------
		jPlayerBase* jPlayerList::find(player_name_ct _id)
		//--------------------------------------------------------------------------
		{
			jAUTO_LOCK_CS(m_CS);
			player_name_t id;
#pragma warning(disable : 4996)
			jw_strcpy_s(id,player_name_SIZE,_id);
#pragma warning(default : 4996)


			jw_strlwr(id);
			m_mapUser_by_name_it it = m_mapUser_by_name.find(id);
			if(it==m_mapUser_by_name.end())
				return 0;
			return it->second;
		}

		//--------------------------------------------------------------------------
		jPlayerBase* jPlayerList::find(player_id_t pid)
		//--------------------------------------------------------------------------
		{
			jAUTO_LOCK_CS(m_CS);
			m_mapUser_by_pid_it it = m_mapUser_by_pid.find(pid);
			if(it==m_mapUser_by_pid.end())
				return 0;
			return it->second;
		}

		void jPlayerList::erase(player_name_ct id)
		{
			jAssert0(mf_erase_jPlayerBase);

			jAUTO_LOCK_CS(m_CS);
			jPlayerBase* pPlayer = find(id);
			if(!pPlayer)
			{
				jWARN("%s not found",jT(id));
				return;
			}

#pragma warning(disable : 4996)
			m_mapUser_by_name.erase(jw_strlwr(pPlayer->m_szID));
#pragma warning(default : 4996)
			m_mapUser_by_pid.erase(pPlayer->m_pid);
			if(mf_erase_jPlayerBase)
				mf_erase_jPlayerBase(pPlayer);
		}

		void jPlayerList::erase(player_id_t pid)
		{
			jAssert0(mf_erase_jPlayerBase);
			jAUTO_LOCK_CS(m_CS);
			jPlayerBase* pPlayer = find(pid);
			if(!pPlayer)
			{
				tname1024_t buf;
				jWARN("%s not found",ToString(pid,buf));
				return;
			}
#pragma warning(disable : 4996)
			m_mapUser_by_name.erase(jw_strlwr(pPlayer->m_szID));
#pragma warning(default : 4996)

			m_mapUser_by_pid.erase(pPlayer->m_pid);
			if(mf_erase_jPlayerBase)
				mf_erase_jPlayerBase(pPlayer);
		}
		
		//! 백엔드서버쪽에서 사용.
		jPlayerBase* jPlayerList::create(player_name_ct _szID,player_id_t pid)
		{
			jAssert0(mf_create_jPlayerBase);

			player_name_t szID;
			jw_strcpy_s(szID,_szID);

#pragma warning(disable : 4996)
			jw_strlwr(szID);
#pragma warning(default : 4996)
			jAssert0(find(szID)==0);
			jAssert0(find(pid)==0);

			jAUTO_LOCK_CS(m_CS);
			jPlayerBase* pPlayer = mf_create_jPlayerBase();
			pPlayer->m_pid = pid;
			jw_strcpy(pPlayer->m_szID, szID);
			m_mapUser_by_pid[pid] = pPlayer;
			m_mapUser_by_name[szID] = pPlayer;
			return pPlayer;
		}


		jPlayerBase* jPlayerList::create_Dummy(player_name_ct _szID)
		{
			jAssert0(mf_create_jPlayerBase);

			player_name_t szID;
			jw_strcpy_s(szID,_szID);
#pragma warning(disable : 4996)
			jw_strlwr(szID);
#pragma warning(default : 4996)
			jvRETURN_ret(0,!find(szID) ,_T("중복생성 : %s"),szID);
			jPlayerBase* pPlayer = (jPlayerBase*)mf_create_jPlayerBase();
			jw_strcpy_s(pPlayer->m_szID, szID);
			m_mapUser_by_name[szID] = pPlayer;
			return pPlayer;
		}

		void jPlayerList::set_pid(jPlayerBase* pPlayer,player_id_t pid)
		{
			jAUTO_LOCK_CS(m_CS);
			jAssert0(find(pid)==0);
			pPlayer->m_pid = pid;
			m_mapUser_by_pid[pid] = pPlayer;
		}


	}//namespace nServerLogic
}//namespace nMech
