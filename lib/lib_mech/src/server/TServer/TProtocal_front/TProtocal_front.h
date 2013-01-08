/* file : TProtocal_front.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-20 19:55:01
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __TProtocal_front_header__
#define __TProtocal_front_header__
#pragma once

#ifdef TPROTOCAL_FRONT_EXPORTS
#define TPROTOCAL_FRONT_API __declspec(dllexport)
#else
#define TPROTOCAL_FRONT_API __declspec(dllimport)
#pragma comment(lib, "TProtocal_front.lib")
#endif


#include "interface/net/net_common_code.h"
//--------------------------------------------------------------------------
// 서버 클라이언트 공유 시작 해더
//--------------------------------------------------------------------------
#include "../TCommonClient/jDebugPrint_TCommonClient.h"
#include "../TCommonServer/jDebugPrint_TCommonServer.h"

#define PT_DummyServer_LIB_API TPROTOCAL_FRONT_API
#define jxDECL_DummyServer jxDECL_NET
#define jxDEFINE_DummyServer jxDEFINE_NET

#define PT_LoginServer_LIB_API TPROTOCAL_FRONT_API
#define jxDECL_LoginServer jxDECL_NET
#define jxDEFINE_LoginServer jxDEFINE_NET

#define PT_ChannelServer_LIB_API TPROTOCAL_FRONT_API
#define jxDECL_ChannelServer jxDECL_NET
#define jxDEFINE_ChannelServer jxDEFINE_NET

#define PT_GameServer_LIB_API TPROTOCAL_FRONT_API
#define jxDECL_GameServer jxDECL_NET
#define jxDEFINE_GameServer jxDEFINE_NET




#ifndef jxDEFINE_NET
#define jxDEFINE_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{ \
	TPROTOCAL_FRONT_API StringID x_##X= Get_jIStringTable()->RegistID(_T(#X),&x_##X);} } }
#endif

#ifndef jxDECL_NET
#define jxDECL_NET(X) namespace nMech{ namespace nString{ namespace nINDEX{extern TPROTOCAL_FRONT_API StringID x_##X;}}}
#endif

extern TPROTOCAL_FRONT_API void Init_TPROTOCAL_FRONT_API();

#endif // __TProtocal_front_header__

