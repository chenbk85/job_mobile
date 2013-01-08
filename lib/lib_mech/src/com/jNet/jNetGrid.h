/* file : jNetGrid.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-04 10:41:53
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jNetGrid_header__
#define __jNetGrid_header__
#pragma once
#include "Interface/net/jINetGrid.h"
#include "jPacketSocket_IOCP.h"

namespace nMech
{
	namespace nNET
	{
		jLIST_TYPEDEF_map_typedef(jIPacketSocket_IOCP*,jIGridNode*,grid);
		struct jGrid
		{
			grid_t m_Grid;
			nUtil::jCriticalSection m_Grid_CS;
		};

		namespace Impl
		{

		class jNetGrid : public jINetGrid
		{
		public:
			jINTERFACE_HEADER(jINetGrid);

			jLIST_TYPEDEF_map(tstring,jGrid,m_listGrid);
			bool insertGrid(cstr szGridName,jPacketSocket_IOCP* pS, jIPlugIn_Net* pPlugIn);
			void deleteGrid(jPacketSocket_IOCP* pS);
			tcstr get_GridName(IN jIE* pE,IN jIPlugIn_Net* pPlugIn,OUT fname_t szGridNameRTTI);
		};


		jNetGrid* Get_jINetGrid(jIE* pePlugIn_Parent);

		}//Impl
	}//nNET
} //nMech


#endif // __jNetGrid_header__
