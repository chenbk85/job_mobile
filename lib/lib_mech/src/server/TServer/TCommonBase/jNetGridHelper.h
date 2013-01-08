/* file : jINetGrid_Util.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-04 21:09:25
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jINetGrid_Util_header__
#define __jINetGrid_Util_header__
#pragma once

#include "Interface/net/jINetGrid.h"


//#define __check_null70029387 while(!m_pNetGrid){jWARN("!m_pNetGrid");}while(!m_pGrid){jWARN("!m_pGrid");}jAssert0(m_pNetGrid);jAssert0(m_pGrid);
//#define __check_null70029387 while(!m_pNetGrid);while(!m_pGrid);jAssert0(m_pNetGrid);jAssert0(m_pGrid);
#define __check_null70029387 int _i;for(_i=0;_i<100 ;++_i){if(m_pNetGrid) break;}

namespace nMech
{
	namespace nNET
	{
		template <typename RTTI_t,typename RTTI_key_t>
		struct jNetGridHelper 
		{
			jGrid* m_pGrid;
			jINetGrid* m_pNetGrid;
		public:
			void Init(jIPlugIn_Net* pPlugIn,tcstr szGridName)
			{
				m_pNetGrid = pPlugIn->m_pjINetGrid;jAssert0(m_pNetGrid );
				m_pGrid = m_pNetGrid->find(szGridName); jAssert0(m_pGrid);
			}
			size_t size() 
			{
				__check_null70029387;
				return m_pNetGrid ? m_pNetGrid->size(m_pGrid) : 0;
			};

			template <class _Predicate>	void for_each(_Predicate __pred ) 
			{
				__check_null70029387;
				if(m_pNetGrid) m_pNetGrid->for_each(m_pGrid,for_each_grid_t(__pred));
			}
			template <class _Predicate>	RTTI_t* find_if(_Predicate __pred )
			{
				__check_null70029387;
				if(!m_pNetGrid) return 0;
				return (RTTI_t*)m_pNetGrid->find_if(m_pGrid, find_if_grid_t(__pred));
			}

			//ESocket_Type eType= eACCEPTED_SOCKET ,eCONNECTING_SOCKET,eNULL_SOCKET이렇게 올수 있다.
			void WritePacket(jPacket_Base& pk,jIPacketSocket_IOCP* pS_skip=0,ESocket_Type eType=eNULL_SOCKET)
			{
				__check_null70029387;
				#define jLAMDA__send_all(X,Z) X(jIPacketSocket_IOCP* ,pS_skip) X(ESocket_Type ,eType) Z(jPacket_Base& ,pk)
				jLAMDA_for_each(_send_all,jIGridNode*)
				{
					if(it->m_pS==pS_skip)  return;

					if(eType == eNULL_SOCKET) 
					{
						it->m_pS->WritePacket(&pk); 
					}
					else
					{
						if(it->m_pS->GetType()==eType)
							it->m_pS->WritePacket(&pk);
					}
				}
				jLAMDA_end();

				if(!m_pNetGrid) return;
				m_pNetGrid->for_each(m_pGrid,for_each_grid_t(_send_all(pS_skip,eType,pk)));
			}

			RTTI_t* find(RTTI_key_t uid)
			{
				__check_null70029387;
				struct _find
				{
					RTTI_key_t id;
					_find(RTTI_key_t _uid):id(_uid){}bool operator ()(jIGridNode* _it)
					{
						RTTI_t* it = (RTTI_t*)_it;
						return it->GetID()==id;
					}
				};
				if(!m_pNetGrid) return 0;
				return (RTTI_t*) m_pNetGrid->find_if( m_pGrid, find_if_grid_t(_find(uid)) );
			}
			//	jIPlugIn_Server_IOCP helper function
			void DoDisconnect(RTTI_t* pC)			{if(pC && pC->m_pPlugIn) pC->m_pPlugIn->DoDisconnect(pC->m_pS);}
			void DoDisconnect(jIPacketSocket_IOCP* pS){ if(pS)pS->GetGridNode()->m_pPlugIn->DoDisconnect(pS);}
			void DoDisconnect(RTTI_key_t id)
			{
				RTTI_t* pConnection = find(id);
				if(!pConnection) 
				{
					fname_t szBuf;
					jWARN("id not found %s", ToString(id, szBuf));
					return;
				}
				pConnection->m_pPlugIn->DoDisconnect(pConnection->m_pS);
			}
		};//struct jNetGridHelper 


	}//namespace nNET
}//namespace nMech


#endif // __jINetGrid_Util_header__
