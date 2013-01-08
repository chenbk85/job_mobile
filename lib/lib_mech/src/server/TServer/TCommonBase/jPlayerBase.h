/* file : jPlayerBase.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-19 21:19:33
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jPlayerBase_header__
#define __jPlayerBase_header__
#pragma once

#include "player_id_t.h"

namespace nMech
{
	namespace nServerLogic
	{
		struct jPlayerBase :public nDataStruct::ySimpleNode<jPlayerBase>
		{
			nUtil::jCriticalSection m_CS;
			player_id_t m_pid;//memory db에서의 식별자
			db_uid_type m_uid;
			player_name_t m_szID;
			SYSTEMTIME m_StartTime;
		private:
			int m_iFlag;
			serverid_t m_ConnectedServer[eEND_EServerTypeFrontEnd];
		public:
			jSET_FLAG(_GoingTo_Logout,jBIT_0);
			jSET_FLAG(_IsDeleted,jBIT_1);
			jSET_FLAG(_IsDuplicated_so_GoingTo_Logout,jBIT_2);
			jSET_FLAG(_GoingTo_Login,jBIT_3);

			virtual void Create()
			{
				m_pid.m_id=0;
				m_uid.m_db_id=0;
				GetLocalTime(&m_StartTime);
				m_szID[0]=0;
				m_iFlag=0;
				memset(m_ConnectedServer,0,sizeof(m_ConnectedServer));
			}
			virtual void Destroy(){};
			virtual void CopyFrom(const jPlayerBase& o){jAssert0(0);}

			serverid_t Get_Server(EServerType eType)
			{
				if(eType<eEND_EServerTypeFrontEnd)
				{
					return m_ConnectedServer[eType];
				}
				else if(eType == eWorld)
					return m_pid.m_w_sid+iSTART_SERVERID_World;
				else if(eType == eDBCache)
					return m_pid.m_dc_sid;

				jAssert0(0);
				return 0;
			}
			void Set_Server(EServerType eType,serverid_t sid)
			{
				if(eType<eEND_EServerTypeFrontEnd)
					m_ConnectedServer[eType] = sid;
				else if(eType == eWorld)
					m_pid.m_w_sid=(uint8)(sid-iSTART_SERVERID_World);
				else if(eType == eDBCache)
					m_pid.m_dc_sid=sid;
				jAssert0(0);
			}
			bool IsConnectedServer()
			{
				return m_ConnectedServer[eLogin] 
				|| m_ConnectedServer[eChannel] 
				|| m_ConnectedServer[eGame];
			}

			//virtual void* Base()=0; // 최종 상속 받은 객체의 포인터.

		};

		inline tcstr ToString(jPlayerBase* pUser , tname1024_t buf)
		{
			jt_sprintf_s(buf, 1024,_T("%s=%I64d:%I64 W=%d DC=%d L=%u CH=%u G=%u (%d:%d:%d)") 
				, jT(pUser->m_szID)
				,pUser->m_pid.m_id 
				,pUser->m_uid.m_db_id
				,pUser->Get_Server(eWorld)
				,pUser->Get_Server(eDBCache)
				,pUser->Get_Server(eLogin)
				,pUser->Get_Server(eChannel)
				,pUser->Get_Server(eGame)
				,pUser->m_StartTime.wHour
				,pUser->m_StartTime.wMinute
				,pUser->m_StartTime.wSecond
				);
			return buf;
		}



	}//namespace nServerLogic
}//namespace nMech

#define jPlayerBase_DECLEAR(CLASS) jDECLEAR_SIMPLE_MEMORY(CLASS);\
									virtual void Create();\
									virtual void Destroy();\

#define jPlayerBase_CREATE(CLASS,OBJ_SIZE, SLOT_COUNT)\
		jDEFINE_SIMPLE_MEMORY(CLASS, OBJ_SIZE,SLOT_COUNT);\
		jPlayerBase *create_jPlayerBase_##CLASS(){return CLASS::_push_back();}\
		void erase_jPlayerBase_##CLASS(jPlayerBase*p){jPlayerObj::_erase((CLASS*)p);}\
		jONCE_RUN(jMEMORY_ALLOCATOR_jPlayerBase_##CLASS)\
		{\
			g_PL.mf_create_jPlayerBase = create_jPlayerBase_##CLASS;\
			g_PL.mf_erase_jPlayerBase = erase_jPlayerBase_##CLASS;\
		}\
		void CLASS::Create(){jPlayerBase::Create();\

#define jPlayerBase_DESTROY(CLASS)	} void CLASS::Destroy()


#endif // __jPlayerBase_header__
