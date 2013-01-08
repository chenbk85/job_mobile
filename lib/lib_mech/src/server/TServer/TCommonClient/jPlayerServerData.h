/* file : jPlayerServerData.h
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

struct jPlayerServerData
{
	EServerPlayerGPS m_eGPS;
	// 현제 선택된 아바타 정보
	nXML::jE m_eUser_file_db;
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
#if 0
		if(m_eGPS_Cashe.full()) 
			GetjIXml()->DeleteElement(m_eGPS_Cashe);
#endif
	}
	nAQ::Use_User& Get_Use_User(){ return m_User;}


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
