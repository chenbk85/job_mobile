/* file : TProtocal_back.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-20 19:55:35
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __TProtocal_back_header__
#define __TProtocal_back_header__
#pragma once


#ifdef TPROTOCAL_BACK_EXPORTS
#define TPROTOCAL_BACK_API __declspec(dllexport)
#else
#define TPROTOCAL_BACK_API __declspec(dllimport)
#pragma comment(lib, "TProtocal_back.lib")
#endif

#include "interface/net/net_common_code.h"
//--------------------------------------------------------------------------
// 서버 클라이언트 공유 시작 해더
//--------------------------------------------------------------------------
#include "../TCommonClient/jDebugPrint_TCommonClient.h"
#include "../TCommonServer/jDebugPrint_TCommonServer.h"


#define PT_CentralServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_CentralServer jxDECL_NET
#define jxDEFINE_CentralServer jxDEFINE_NET

#define PT_UserServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_UserServer jxDECL_NET
#define jxDEFINE_UserServer jxDEFINE_NET

#define PT_MsgServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_MsgServer jxDECL_NET
#define jxDEFINE_MsgServer jxDEFINE_NET

#define PT_WorldServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_WorldServer jxDECL_NET
#define jxDEFINE_WorldServer jxDEFINE_NET

#define PT_DBCacheServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_DBCacheServer jxDECL_NET
#define jxDEFINE_DBCacheServer jxDEFINE_NET

#define PT_TestServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_TestServer jxDECL_NET
#define jxDEFINE_TestServer jxDEFINE_NET

#define PT_DBQueryServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_DBQueryServer jxDECL_NET
#define jxDEFINE_DBQueryServer jxDEFINE_NET


#define PT_AuctionServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_AuctionServer jxDECL_NET
#define jxDEFINE_AuctionServer jxDEFINE_NET


#define PT_CommandServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_CommandServer jxDECL_NET
#define jxDEFINE_CommandServer jxDEFINE_NET


#define PT_MailServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_MailServer jxDECL_NET
#define jxDEFINE_MailServer jxDEFINE_NET


#define PT_TradeServer_LIB_API TPROTOCAL_BACK_API
#define jxDECL_TradeServer jxDECL_NET
#define jxDEFINE_TradeServer jxDEFINE_NET




#ifndef jxDEFINE_NET
#define jxDEFINE_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{ \
	TPROTOCAL_BACK_API StringID x_##X= Get_jIStringTable()->RegistID(_T(#X),&x_##X);} } }
#endif

#ifndef jxDECL_NET
#define jxDECL_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{extern TPROTOCAL_BACK_API StringID x_##X;}}}
#endif


extern TPROTOCAL_BACK_API void Init_TPROTOCAL_BACK_API();
#endif // __TProtocal_back_header__

