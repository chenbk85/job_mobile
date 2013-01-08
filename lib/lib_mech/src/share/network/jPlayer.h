/* file : jPlayer.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-03-19 16:50:43
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jPlayer_header__
#define __jPlayer_header__
#pragma once

#define for_each_EServerPlayerGPS(X)\
	X(eGPS_NOTING)\
	X(eGPS_TOWN)\
	X(eGPS_CASTLE)\
	X(eGPS_WORLD)\

#define declear_enum1234123(X) X,

enum EServerPlayerGPS
{
	for_each_EServerPlayerGPS(declear_enum1234123)
};

struct jPlayer
{
	EServerPlayerGPS m_eGPS;
	nXML::jE m_eGPS_Cashe;// 월드또는 성지역의 캐쉬 정보
	// 현제 선택된 아바타 정보
	nXML::jE m_eUser_file_db;
	townid_t m_iCurrTown;
	nXML::jE m_eCurrTown;
	nAQ::Use_User m_User;

	cstr GetGPS_String()
	{
		#define to_string_gps2434(X) if(m_eGPS==X) return jS(X);
		for_each_EServerPlayerGPS(to_string_gps2434);
		return jS(NULL);
	}

	void _Create()
	{ 
		m_eGPS = eGPS_NOTING;
		if(m_eGPS_Cashe.full()) 
			GetjIXml()->DeleteElement(m_eGPS_Cashe);
	}
	nAQ::Use_User& Get_Use_User(){ return m_User;}
	nAQ::Use_Town* Get_CapitalTown(){return Town_by_uid(m_User.Get_capital_tuid());	}
	nAQ::Use_Town* GetCurrTown(){return Town_at(m_iCurrTown);	}

#define Get_uid1234_Town Get_tuid
#define Get_uid1234_Force Get_fuid
#define Get_uid1234_Hero Get_huid


#define user_table_helpfunc659(table)\
	nAQ::Use_##table*			table##_at(uint8 aid){	if(Town().size() < aid || aid <=0) return 0;	return &table()[aid-1];}\
	int							table##_size(){ return Town().size();}\
	vector<nAQ::Use_##table>&	##table(){ return m_##table;}\
	vector<nAQ::Use_##table> m_##table;\
	nAQ::Use_##table*					table##_by_uid(db_uid_type uid)\
	{	for(int i = 0; i<table##_size();++i){if( table()[i].Get_uid1234_##table()==uid) return &table()[i];}return 0;}\


	for_each_User_table(user_table_helpfunc659);
};

inline void Test_UID(tcstr szUID,db_uid_type uid)
{
	jAssert0(jt_strlen(szUID));
	int64 uid1;
	jt_sscanf(szUID,_T("%I64d"),&uid1);
	jAssert0(uid.m_db_id==uid1);
}


enum EChatType
{
	eCT_NORMAL
	,eCT_FRIEND
	,eCT_WHISPER
	,eCT_ALL
};

#endif // __jPlayer_header__
