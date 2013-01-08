
#include "stdafx.h"
#include "../AqCommon/AqCommon.h"



jCONSOLE_CMD_AUTO(jSERVER_NAME,town_lists,0,"town listing.","")
{
	check_Dummy();
	for( int i=0; i< g_pCurrUser->Town().size(); ++i)
	{
		nAQ::Use_Town& town = g_pCurrUser->Town()[i];
		GetjILog()->Log(_T("tid=%d ,tpsid=%d, tuid=%I64d : %s"),i+1, town.Get_townpos_sid() , town.Get_tuid().m_db_id,  town.Get_name() );
	}
	return true;
}


jCONSOLE_CMD_AUTO(jSERVER_NAME,town_select,0,"town selecting.","<townid>")
{
	check_Dummy();
#define jCONSOLE_PARAM_town_select(X,Y) X(townid,int)
	jCONSOLE_PARAM_END(town_select);

	if(!g_pCurrUser->Town_at(townid))
	{
		GetjILog()->Warning(_T("townid not found"));
		return false;
	}
	g_pCurrUser->Change_CurrTown(townid);
	return true;
}



jCONSOLE_CMD_AUTO(jSERVER_NAME,town_create,0,"town creating.","<csid> <tpsid> <name>")
{
	check_Dummy();
#define jCONSOLE_PARAM_town_create(X,Y) 	X(csid,int) X(tpsid,int) X(name,wcstr)
	jCONSOLE_PARAM_END(town_create);
	g_pCurrUser->Write_Packet_Town(WRITE_X2T_NEW_TOWN(buf,csid,tpsid,name));
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,town_del,0,"town deleting.","<townid>")
{
	check_Dummy();
#define jCONSOLE_PARAM_del(X,Y) X(townid,int)
	jCONSOLE_PARAM_END(del);
	if(!g_pCurrUser->Town_at(townid))
	{
		GetjILog()->Warning(_T("townid not found"));
		return false;
	}
	g_pCurrUser->Write_Packet_Town(WRITE_X2T_TOWN_DELETE(buf,townid));
	return true;
}

