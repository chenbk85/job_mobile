/* file : TownUsingList.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-11 08:58:01
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __TownUsingList_header__
#define __TownUsingList_header__
#pragma once


class TownUsingList
{
public:
	static TownUsingList& Get();
	jIE* GetFreeTown(Sys_Castle_id_t csid,acstr szUserID,OUT Sys_TownPos_id_t &tpsid);
	void TownToFree(Sys_Castle_id_t csid, Sys_TownPos_id_t tpsid);
	nUtil::jCriticalSection m_CS;

};



#endif // __TownUsingList_header__
