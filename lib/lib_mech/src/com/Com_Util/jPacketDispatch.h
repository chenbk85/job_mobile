/* file : jPacketDispather.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-06-08 15:25:09
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jPacketDispather_header__
#define __jPacketDispather_header__
#pragma once

#include "interface/net/jIPacketDispatch.h"

namespace nMech
{
	namespace nNET
	{
		class jPacketDispatchTable :public jIPacketDispatchTable
		{
		public:
			virtual const _jNamed_Event_Handler* find(int id) const 
			{
				std::map<int,_jNamed_Event_Handler*>::const_iterator it = m_mapNEH.find(id);
				//m_mapNEH_it it= m_mapNEH.find(id);
				if(it==m_mapNEH.end()) return 0;
				return it->second;
			}
			virtual void insert(int id, _jNamed_Event_Handler* pNEH)
			{
				m_mapNEH[id]=pNEH;
			}
		private:
			jLIST_TYPEDEF_map(int, _jNamed_Event_Handler*,m_mapNEH);
		};


		class jPacketDispatch : public jIPacketDispatch
		{
		public:
			jINTERFACE_HEADER(jIInterface);
			jINTERFACE_HEADER(jIPacketDispatch);

			jPacketDispatch();
			~jPacketDispatch();

			jLIST_TYPEDEF_map(std::tstring, jPacketDispatchTable,m_jNetEventHandler);
			jIPacketDispatchTable* find(tcstr szTable)
			{
				m_jNetEventHandler_it it = m_jNetEventHandler.find(szTable);
				if(it==m_jNetEventHandler.end()) return 0;
				return &it->second;
			}
			jIPacketDispatchTable* push_back(tcstr szTable)
			{
				jIPacketDispatchTable* pDT = &m_jNetEventHandler[szTable];
				return pDT;
			}

		};//struct jPacketDispatch


	} //nNET
}//nMech


#endif // __jPacketDispather_header__
