/* file : jPlugInHelpTable.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-04-21 15:39:28
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jPlugInHelpTable_header__
#define __jPlugInHelpTable_header__
#pragma once

namespace nMech
{
	namespace nNET
	{
		struct jNamedEventTable_impl: public jNamedEventTable
		{
			jLIST_TYPEDEF_vector(jNamedEventNode,m_list);
			virtual jNamedEventNode* GetByNum(int idx)
			{
				m_list_it it = m_list.begin(), ie = m_list.end();
				for( ; it!=ie ; ++it)if(it->m_id == idx) return &(*it);
				return 0;
			}
			virtual jNamedEventNode* GetByID(StringID& id)
			{
				m_list_it it = m_list.begin(), ie = m_list.end();
				for( ; it!=ie ; ++it)if(it->m_jStringID == id) return &(*it);
				return 0;
			}
			virtual jNamedEventNode* GetByName(tcstr sz)
			{
				m_list_it it = m_list.begin(), ie = m_list.end();
				for( ; it!=ie ; ++it)if(!jt_strcmp(sz,it->m_szName)) return &(*it);
				return 0;
			}
			virtual jNamedEventNode* Insert(int idx,tcstr name,tcstr thread_name)
			{
				if(GetByNum(idx))
				{
					jERROR(_T("jNamedEventNode* Insert(%d, %s) 중복데이타"),idx,name);
				}
				jNamedEventNode node;
				node.m_id=idx;
				node.m_jStringID = nString::Get_jIStringTable()->GetIndex(name);
				node.m_szName = nString::Get_jIStringTable()->GetName(node.m_jStringID);
				node.thread_name = thread_name;
				m_list.push_back(node);
				return GetByNum(idx);
			}
			virtual void for_each(for_each_func_t* f,jIE* pE,jIPacketDispatchTable* pTable)
			{
				m_list_it it = m_list.begin(), ie = m_list.end();
				for(; it!=ie; ++it) f(&(*it),pE,pTable);
			}
		};

		typedef jNamedEventTable_impl jPlugInHelpTableList_impl ;

	}//namespace nNET
}//namespace nMech

#endif // __jPlugInHelpTable_header__
