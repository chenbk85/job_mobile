
#include "stdafx.h"
#include "TPlayer.h"



jCONSOLE_CMD_AUTO(jSERVER_NAME,channel_lists,0,"channel listing.","")
{
	jCHECK_CurrUser();
// 	for( int i=0; i< g_pCurrUser->Channel().size(); ++i)
// 	{
// 		nAQ::Use_Town& channel = g_pCurrUser->Channel()[i];
// 		jLOG1(_T("channelNo=%d ,tpsid=%d, tuid=%I64d : %s"),i+1, channel.Get_channelpos_sid() , channel.Get_tuid().m_db_id,  channel.Get_name() );
// 	}
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,channel_select,0,"channel selecting.","<channelid>")
{
	jCHECK_CurrUser();
// #define jCONSOLE_PARAM_channel_select(X,Y) X(channelid,int)
// 	jCONSOLE_PARAM_END(channel_select);
// 
// 	if(!g_pCurrUser->Channel_at(channelid))
// 	{
// 		jWARN1(_T("channelid not found"));
// 		return false;
// 	}
// 	g_pCurrUser->Change_CurrChannel(channelid);
	return true;
}



jCONSOLE_CMD_AUTO(jSERVER_NAME,channel_create,0,"channel creating.","<csid> <tpsid> <name>")
{
	jCHECK_CurrUser();
// #define jCONSOLE_PARAM_channel_create(X,Y) 	X(csid,int) X(tpsid,int) X(name,wcstr)
// 	jCONSOLE_PARAM_END(channel_create);
// 	g_pCurrUser->Write_Packet_Channel(WRITE_X2T_NEW_TOWN(buf,csid,tpsid,name));
 	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,channel_del,0,"channel deleting.","<channelid>")
{
	jCHECK_CurrUser();
// #define jCONSOLE_PARAM_del(X,Y) X(channelid,int)
// 	jCONSOLE_PARAM_END(del);
// 	if(!g_pCurrUser->Channel_at(channelid))
// 	{
// 		jWARN1(_T("channelid not found"));
// 		return false;
// 	}
// 	g_pCurrUser->Write_Packet_Channel(WRITE_X2T_TOWN_DELETE(buf,channelid));
 	return true;
}

