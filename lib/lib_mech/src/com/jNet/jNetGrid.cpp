/* file : jNetGrid.cpp
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-04 10:41:56
comp.: t3.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jNetGrid.h"

namespace nMech
{
	namespace nNET
	{
		namespace Impl
		{
			jLIST_TYPEDEF_map(tstring,jNetGrid,g_mapjNetGrid);


			void jNet::for_each_jINetGrid(for_each_jINetGrid_func_t* func)
			{
				g_mapjNetGrid_it it = g_mapjNetGrid.begin(), ie = g_mapjNetGrid.end();
				for(; it!=ie ; ++it){func(it->first.c_str(),&it->second);}
			}
			jNetGrid* Get_jINetGrid(jIE* pePlugIn_Parent)
			{
				jASSERT0 ( pePlugIn_Parent->GetAttrVar(jS(TYPE))->IsContents(jS(PlugInList) ) );
				return &g_mapjNetGrid[pePlugIn_Parent->GetTagName()];
			}


			jGrid*		jNetGrid::find(tcstr szGridName){return &m_listGrid[szGridName];}
			size_t		jNetGrid::size(jGrid* pGrid){ return pGrid->m_Grid.size() ;}
			void		jNetGrid::for_each(jGrid* pGrid,for_each_grid_t& func)
			{
				jAUTO_LOCK_CS(pGrid->m_Grid_CS);
				grid_it itB;
				jFOR(pGrid->m_Grid,itB)
				{
					func(itB->second);
				}
			}

			jIGridNode* jNetGrid::find_if(jGrid* pGrid,find_if_grid_t& func)
			{
				jAUTO_LOCK_CS(pGrid->m_Grid_CS);
				grid_it itB;
				jFOR(pGrid->m_Grid,itB)
				{
					if(func(itB->second)) return itB->second;
				}
				return 0;
			}

			size_t		jNetGrid::_size(tcstr szGridName)
			{ 
				if(!szGridName) 
				{
					jWARN_T("szGridName ==NULL");
					return 0;
				}
				return m_listGrid[szGridName].m_Grid.size() ;
			}

			void jNetGrid::_for_each(tcstr szGridName,for_each_grid_t& func)
			{
				m_listGrid_it it;
				grid_it itB;
				if(szGridName)
				{
					it = m_listGrid.find(szGridName);
					if(it==m_listGrid.end()) return;
					for_each(&it->second, func);
					return;
				}

				jFOR(m_listGrid,it )
				{
					for_each(&it->second, func);
				}
			}

			jIGridNode* jNetGrid::_find_if(tcstr szGridName,find_if_grid_t& func)
			{
				m_listGrid_it it;
				grid_it itB;
				if(szGridName)
				{
					it = m_listGrid.find(szGridName);
					if(it==m_listGrid.end()) return 0;

					return find_if(&it->second,func);
				}

				jFOR(m_listGrid,it )
				{
					jIGridNode* pGN = find_if(&it->second,func);
					if(pGN) return pGN;
				}
				return 0;
			}

			bool jNetGrid::insertGrid(cstr szGridName,jPacketSocket_IOCP*pS, jIPlugIn_Net* pPlugIn)
			{
				jASSERT0(!pS->m_pGridNode);
				if(!szGridName || !jt_strlen(szGridName)) return false;

				pS->m_pGridNode = static_cast<jIGridNode*>( jRTTI::New(szGridName, jS(jINetGrid) ) );
				if(!pS->m_pGridNode)
				{
					jWARN_T("jTODO 접속종료처리해야함. GridName(%s) RTTI not found", szGridName);
					return false;
				}
				assert(!jt_strcmp(pS->m_pGridNode->GetGridName(), szGridName) );
				pS->m_pGridNode->m_pPlugIn = pPlugIn;
				pS->m_pGridNode->m_pS = pS;
				jGrid& g = m_listGrid[szGridName];
				jAUTO_LOCK_CS(g.m_Grid_CS);
				g.m_Grid[pS]=pS->m_pGridNode;
				return true;
			}
			void jNetGrid::deleteGrid(jPacketSocket_IOCP* pS)
			{
				if(!pS->m_pGridNode)return;
				tcstr szName = pS->m_pGridNode->GetGridName();
				jGrid& g = m_listGrid[szName];
				jAUTO_LOCK_CS(g.m_Grid_CS);
				g.m_Grid.erase(pS);
				jRTTI::Del(pS->m_pGridNode);
				pS->m_pGridNode=0;
			}

			// net config xml에서 GridName속성을 찾아준다.
			tcstr jNetGrid::get_GridName(IN jIE* pE,IN jIPlugIn_Net* pPlugIn,OUT fname_t szGridNameRTTI)
			{
				memset(szGridNameRTTI,0,sizeof(szGridNameRTTI));
				tcstr szGridName = pE->GetAttr(jS(GridName));
				if(!szGridName) 
				{
					pE = pE->GetParent();
					szGridName = pE->GetAttr(jS(GridName));
					if(!szGridName) 
					{
						pE = pE->GetParent();
						szGridName = pE->GetAttr(jS(GridName));
					}
				}
				if(!szGridName) return 0;
				if(!jt_strlen(szGridName) )return 0;
				if(!jt_strcmp(szGridName,jS(NULL)) ) return 0;
				return szGridName;
				//jt_sprintf(szGridNameRTTI,_T("%s%s") , szGridName, pPlugIn->m_pE->GetAttr(jS(TYPE)) );
				//return szGridNameRTTI;
			}

		}//Impl
	}//nNET
} //nMech


