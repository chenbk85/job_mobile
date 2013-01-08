/* file : net_SQ.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-10-08 18:58:16
comp.: actoz.com
title : 
desc : 

*/

#ifndef __net_SQ_client_header__
#define __net_SQ_client_header__
#pragma once


//--------------------------------------------------------------------------
// client 와 서버가 공통사용하는 SQ 관련 선언부
//--------------------------------------------------------------------------
#define jNOT_USE_SQ_CLIENT_DECLARE_INSTANCE_TYPE
#ifndef jNOT_USE_SQ_CLIENT_DECLARE_INSTANCE_TYPE

DECLARE_INSTANCE_TYPE(jError);
DECLARE_INSTANCE_TYPE(jNoticeInfo);
DECLARE_INSTANCE_TYPE(wstring);
DECLARE_INSTANCE_TYPE(astring);
DECLARE_INSTANCE_TYPE(userid_t);
DECLARE_INSTANCE_TYPE(jTownPlayerCookie);
DECLARE_INSTANCE_TYPE(db_uid_type);
DECLARE_INSTANCE_TYPE(jWorldServerInfo);


DECLARE_ENUM_TYPE(EUserGPS);
DECLARE_ENUM_TYPE(EUserGPS*);


#endif //#ifndef jNOT_USE_SQ_CLIENT_DECLARE_INSTANCE_TYPE
#endif // __net_SQ_client_header__