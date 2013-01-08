/* file : jINetGrid.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-01 14:39:22
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jINetGrid_header__
#define __jINetGrid_header__
#pragma once


namespace nMech
{
	namespace nNET
	{
		const int IMAX_GRID_NAME_RTTI = 64;// GridRTTI용 이름길이
		struct jGrid;
		struct jIPacketSocket_IOCP;
		void grid_for_each_func_t(jIPacketSocket_IOCP* ,void*);

		struct jIGridNode : public jRttiObj
		{
			jIPlugIn_Net* m_pPlugIn;
			jIPacketSocket_IOCP* m_pS;
			tcstr GetGridName(){ return getClassRep()->getClassName();}
			virtual void WritePacket(jPacket_Base& pk){if(m_pS)m_pS->WritePacket(&pk);}
			virtual void WritePacket(jPacket_Base* pk){if(m_pS)m_pS->WritePacket(pk);}

		};
		inline cstr GridName(jIGridNode*pGN){ return pGN ? pGN->GetGridName() : jS(NULL) ;}

		typedef boost::function<void (jIGridNode*)> for_each_grid_t;
		typedef boost::function<bool (jIGridNode*)> find_if_grid_t;

#define jINTERFACE_jINetGrid(x) public:	\
	virtual jGrid*		find(tcstr szGridName) ##x \
	\
	virtual void		_for_each	(tcstr szGridName	,for_each_grid_t& func )##x \
	virtual jIGridNode* _find_if		(tcstr szGridName	,find_if_grid_t& func )##x \
	virtual size_t		_size		(tcstr szGridName) ##x \
	\
	virtual void		for_each	(jGrid* pGrid		,for_each_grid_t& func )##x \
	virtual jIGridNode* find_if		(jGrid* pGrid		,find_if_grid_t& func )##x \
	virtual size_t		size		(jGrid* pGrid) ##x \

		jINTERFACE_END(jINetGrid);
	}
}


#endif // __jINetGrid_header__
