/* file : AqClientUser_T.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-07-14 15:42:03
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqClientUser.h"

jDEFINE_YVECTOR_MANAGER(AqClientUser_T, 256,10);


void AqClientUser_T::Change_CurrTown(townid_t tid)
{
	nswb256_t buf;
	if(tid<1 || tid > Town().size() )
	{
		tid =1;
		Write_Packet(WRITE_T2X_TOWN_SELECT_RESULT(buf, tid,jError(SR_t(Change_CurrTown),CR_t(ERROR_BAD_TOWN_ID) ) ) );
		return;
	}
	Write_Packet(WRITE_T2X_TOWN_SELECT_RESULT(buf, tid,jError() ) );

	m_iCurrTown = tid;
	m_eCurrTown = g_jAqCommon.FindTownBYTUID(m_eUser_file_db, Town_at(tid)->Get_tuid());
	assert(m_eCurrTown.full());
}