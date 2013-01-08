// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 및 프로젝트 관련 포함 파일이 
// 들어 있는 포함 파일입니다.
//

#pragma once

#define WIN32_LEAN_AND_MEAN
#include <process.h>

#include "base/jBase.h"
#include "Interface/xml/jIXml.h"
#include <boost/bind.hpp>


#define _xmlid_LIST(X)\
X(jNet_DLL)\
X(STCB)\
X(WTCB)\
X(KTCB)\
X(TSI)\
X(USI)\
X(RUCB)\
X(PSIOCP)\
X(SIOCP)\
X(CT)\

_xmlid_LIST(jxDECL);


#include <winsock2.h>

#include "jNet.h"
#include "jNet_Header.h"
#include "jClientSession_Asio.h"



namespace nMech
{
	namespace nNET
	{

	}
}


#define var_enum(var_func)\
	var_func(jINet_OGS,OnPacketSize_UsageInfo_TIME, 20.f, 0,"time term of current packet usage info(SEC)")\
	var_func(jINet_OGS,RUDP_RetryTime,10,0,"wait time for RUDP send packet check")\
	var_func(jINet_OGS,RUDP_RetryCount,5,0,"retry count for reliable packet ")\
	var_func(jINet_OGS,RUDP_ResetTime,3000 ,0, "init time for packet serial number.")\
	var_func(jINet_OGS,UseMsgThread,true, 0,"only true. dont remind. this var will delete near future")\
	var_func(jINet_OGS,Custom_MsgLoop,false,0,"if (Custom_MsgLoop== true) then called by client game_update() for net packet pumper")\
	var_func(jINet_OGS,UseEncryt,false,0,"is encryt packet ?")\
	var_func(jINet_OGS,TcpKeepTime,30000,0,"tcp connection check time [msec]")\
	var_func(jINet_OGS,UseMsgManagerEvent,true,0,"use network thread memssage event( for CPU Time resource)")\

var_enum(jCV_DECLARE);

