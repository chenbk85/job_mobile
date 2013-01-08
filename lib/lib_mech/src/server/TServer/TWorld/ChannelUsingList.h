/* file : ChannelUsingList.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-11 08:58:01
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __ChannelUsingList_header__
#define __ChannelUsingList_header__
#pragma once


class ChannelUsingList
{
public:
	static ChannelUsingList& Get();
	jIE* GetFreeChannel(Sys_Castle_id_t csid,player_name_ct szUserID,OUT Sys_TownPos_id_t &tpsid);
	void ChannelToFree(Sys_Castle_id_t csid, Sys_TownPos_id_t tpsid);
	nUtil::jCriticalSection m_CS;

};



#endif // __ChannelUsingList_header__
