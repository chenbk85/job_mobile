/* file : DBUserManager.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2009-08-21 17:25:24
comp.: wiki.aqrius.com
title : 
desc : 

*/

#include "stdafx.h"
#include "AqDBCacheUser.h"



cstr ToString(AqDBCacheUser* pUser,fname_t buf)
{
	jt_sprintf(buf, _T("%s(%I64d:%d) T:%d D:%d")
		,jT(pUser->m_pjDBUserInfo->m_szID)
		,pUser->m_pjDBUserInfo->m_uid.m_id
		,pUser->m_pjDBUserInfo->m_uid.m_dc_sid
		,pUser->m_pToTown ? 1 :0
		,pUser->m_pToDungeon ? 1 :0
		);
	return buf;
}



#if 0

jHeroItem* AqDBCacheUser::Item_push_back(Sys_Item* pN,int amount , int limite_time_end, Use_Town_id_t auid)
{
	if(Item_size()>=iMAX_TOWN_ITEM) return 0;
	jHeroItem* pItem=0;
	for(int i=0; i< iMAX_TOWN_ITEM; ++i)
	{
		if(GetDB()->m_Item[i].m_iid!=0) continue;
		pItem = GetDB()->m_Item + i;
		pItem->m_iid = i+1; 
		break;
	}
	if(!pItem) return 0;
	pItem->m_eType = pN->Get_category();
	Use_Item_id_t iuid;
	iuid.m_db_id = 0;

	#define  the_item3243(enum_name,a1,b1,c1,d1,e1)\
	if(pItem->m_eType == e##enum_name)\
	{\
		pItem->m_##enum_name.Set_iuid(iuid);\
		pItem->m_##enum_name.Set_auid(auid);\
		pItem->m_##enum_name.Set_isid(pN->Get_isid());\
		pItem->m_##enum_name.Set_amount(amount);\
		pItem->m_##enum_name.Set_limite_time_end(g_jAqCommon.Calcul_limite_Day(limite_time_end));\
		pItem->m_##enum_name.Set_is_possession(false);\
		pItem->m_##enum_name.Set_endurance(pN->Get_durability());\
		pItem->m_##enum_name.jDebugPrint();\
	}\

	for_each_nAQ_EItemClass_ENUM_FIELD(the_item3243);
	//++this->m_pjDBUserInfo->m_iTotItem;
	/*
	if(pItem->m_eType==¹«±â)
	{

	}
	*/
	++this->Item_size();
	return pItem;
}
#endif

void AqDBCacheUser::Town_erase(townid_t aid)
{
	
	/* *_* by icandoit : 2009-09-25 01:40:08

	#include <memory.h>
	#include <string.h>
	#include <stdio.h>

	char str1[32] = "aabbcc";

	void del_vec(char* str1 , int del,int tot)
	{
	memmove( str1 + del, str1+del+1, tot-del );
	memset(str1 + tot-1 , 0 , 1 );
	}

	int main( void )
	{
	printf( "The string: %s\n", str1 );
	memcpy( str1 + 2, str1, 4 );
	printf( "New string: %s\n", str1 );

	strcpy_s( str1, sizeof(str1), "0123456789" );   // reset string
	printf( "The string: %s\n", str1 );
	del_vec(str1,0,10);
	printf( "New string: %s\n", str1 );
	}

	*/ //*_* by icandoit : 2009-09-25 01:40:11

	int tot = Town_size();
	int del = aid-1;
	int size = sizeof(GetDB()->m_Town[0]);
	nAQ::Use_Town* str1 = GetDB()->m_Town;
	memmove( str1 + del , str1+del+1 , (tot-del)*size );
	memset(str1 + tot-1 , 0 , size );
	--Town_size();
}
