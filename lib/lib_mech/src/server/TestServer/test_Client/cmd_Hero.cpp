#include "stdafx.h"
#include "../AqCommon/AqCommon.h"


jCONSOLE_CMD_AUTO(jSERVER_NAME,force_lists,0,"force listing.","")
{
	check_Dummy();
	for( int i=0; i< g_pCurrUser->Force().size(); ++i)
	{
		GetjILog()->Log(_T("force[%d]"),i+1);
		nAQ::Use_Force& force = g_pCurrUser->Force()[i];
		force.jDebugPrint();
		//GetjILog()->Log(_T("tid=%d , tuid=%I64d : %s"),i+1, force.Get_tuid().m_db_id,  force.Get_name() );
	}
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,hero_lists,0,"hero listing.","")
{
	check_Dummy();
	for( int i=0; i< g_pCurrUser->Hero().size(); ++i)
	{
		GetjILog()->Log(_T("hero[%d]"),i+1);
		nAQ::Use_Hero& hero = g_pCurrUser->Hero()[i];
		hero.jDebugPrint();
		//GetjILog()->Log(_T("tid=%d , tuid=%I64d : %s"),i+1, hero.Get_tuid().m_db_id,  hero.Get_name() );
	}
	return true;
}


#if 0

jCONSOLE_CMD_AUTO(jSERVER_NAME,hero_create,0,"hero creating.","<hsid> <tpsid> <name>")
{
	check_Dummy();
#define jCONSOLE_PARAM_hero_create(X,Y) 	X(csid,int) X(tpsid,int) X(name,wcstr)
	jCONSOLE_PARAM_END(hero_create);
	g_pCurrUser->Write_Packet_Town(WRITE_X2T_NEW_TOWN(buf,csid,tpsid,name));
	return true;
}

jCONSOLE_CMD_AUTO(jSERVER_NAME,hero_del,0,"hero deleting.","<heroid>")
{
	check_Dummy();
#define jCONSOLE_PARAM_del(X,Y) X(heroid,int)
	jCONSOLE_PARAM_END(del);
	if(!g_pCurrUser->Town_at(heroid))
	{
		GetjILog()->Warning(_T("heroid not found"));
		return false;
	}
	g_pCurrUser->Write_Packet_Town(WRITE_X2T_TOWN_DELETE(buf,heroid));
	return true;
}
#endif