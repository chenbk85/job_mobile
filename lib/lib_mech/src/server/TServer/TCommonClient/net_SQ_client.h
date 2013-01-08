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
DECLARE_INSTANCE_TYPE(jError);
DECLARE_INSTANCE_TYPE(jErrorInfo);
DECLARE_INSTANCE_TYPE(jNoticeInfo);
DECLARE_INSTANCE_TYPE(player_id_t);
DECLARE_INSTANCE_TYPE(jChannelPlayerCookie);
DECLARE_INSTANCE_TYPE(jWorldServerInfo);


DECLARE_ENUM_TYPE(EUserGPS);
DECLARE_ENUM_TYPE(EUserGPS*);

#endif // __net_SQ_client_header__