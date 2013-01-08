/* file : jPlayerList.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-19 20:03:21
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jUserList_header__
#define __jUserList_header__
#pragma once

#include "jPlayerBase.h"
#include "header/jBoost.h"

namespace nMech
{
	//! ������ for server ����
	namespace nServerLogic 
	{
		typedef jPlayerBase *create_jPlayerBase_ft();
		typedef void erase_jPlayerBase_ft(jPlayerBase*);

		struct T_SERVER_LIB_API jPlayerList 
		{
#pragma warning ( disable:4251)
		private:
			nUtil::jCriticalSection	m_CS;
			//jLIST_TYPEDEF_YVECTOR(jPlayerBase,m_UserZoneList);
			jLIST_TYPEDEF_map(player_name_string_t,jPlayerBase*,m_mapUser_by_name);
			jLIST_TYPEDEF_map(player_id_t,jPlayerBase*,m_mapUser_by_pid);
#pragma  warning ( default:4251 )

		public:
			jPlayerList(){}
			create_jPlayerBase_ft* mf_create_jPlayerBase;
			erase_jPlayerBase_ft* mf_erase_jPlayerBase;

			template<typename Pred> jPlayerBase* find_if(Pred& f)
			{
				jAUTO_LOCK_CS(m_CS);
				m_mapUser_by_name_it it = m_mapUser_by_name.begin(),ie=m_mapUser_by_name.end();
				for(;it!=ie;++it) if( f(it->second) ) return it->second;
			}
			template<typename Pred> void for_each(Pred& f)
			{
				jAUTO_LOCK_CS(m_CS);
				m_mapUser_by_name_it it = m_mapUser_by_name.begin(),ie=m_mapUser_by_name.end();
				for(;it!=ie;++it) f(it->second);
			}

			jPlayerBase* find(player_name_ct id);
			jPlayerBase* find(player_id_t pid);
			void	erase(player_name_ct id);
			void	erase(player_id_t pid);

			//! �鿣�弭���ʿ��� ���.
			jPlayerBase* create(player_name_ct szID,player_id_t pid);

			// TPlayer.DLL���� ���.
			jPlayerBase* create_Dummy(player_name_ct szID); // jPlayer.DLL������ jPlayerList::create()�Լ��� ������� �ʴ´�.
			void set_pid(jPlayerBase* pPlayer,player_id_t pid);


		};

#define jLAMDA_to_string_vector(X,Z) Z(vector<tstring>& ,users)
		jLAMDA_for_each(to_string_vector,jPlayerBase*)
		{
			tname1024_t buf;
			users.push_back(ToString(it,buf));
		}
		jLAMDA_end();

	}//namespace nServerLogic
}//namespace nMech
using namespace nMech::nServerLogic;


//! ���� jPlayerList_IMPLEMENT�� ���� ���� �ϰ� ������ �ش� DLL�� stdafx.h���� ��������.
#ifndef jPlayerList_IMPLEMENT
#define jPlayerList_IMPLEMENT jPlayerList
#endif

extern jPlayerList_IMPLEMENT g_PL;

#endif // __jUserList_header__
