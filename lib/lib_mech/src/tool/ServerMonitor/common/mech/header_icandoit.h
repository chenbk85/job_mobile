/* file : header_icandoit.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2010-12-23 23:45:12
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __header_icandoit_header__
#define __header_icandoit_header__
#pragma once
#include "mech/header/jDefine.h"
#include <tchar.h>

//--------------------------------------------------------------------------
// 디버깅용 feature define
//--------------------------------------------------------------------------
#define DEF_ICANDOIT_LOG_NET_PACKET// 조욱래 디버깅시만 사용하는 define
#define DEF_ICANDOIT_DISABLE_SOCKET_DISCONN // 디버깅시 서버 소켓 끊어지는거 막기.
#define DEF_ICANDOIT_NOT_USE_BOSS_WORK_nRewardMileage // 사장님작업하신 마일리지 작업 잠시 막음.
//#define DEF_ICANDOIT_DEBUG_MOVE //이동패킷관련 디버깅용.
#define DEF_ICANDOIT_MAIL_LOG // 메일관련 디버깅용.


//--------------------------------------------------------------------------
// 임시 feature define
//--------------------------------------------------------------------------
//#define DF_RANDOMBOX_ENSURE_ITEM		"2011-01-12"	// icandoit 개선사항 #3254 (공통) ItemRandomBox, ItemGambleBox에서 무조건 여러개주는 아이템필드 추가작업
#define DF_BUGFIX_GMTOOL_ITEM_NEED_RANDOM_OPTION	"2011-01-13b-버그 #3228" //ICANDOIT  (독일_CS 1차)(#버그377) GM tool을 이용해 유저들에게 아이템을 보내는 경우
//#define DF_ABUSING_MOVE_PACKET_BY_NET_DISCONN	"2011-01-17a-버그 #2867"	//ICANDOIT  (공통)(한국#578) 랜선을 뽑고 이동 시 캐릭터 순간 이동 현상
#endif // __header_icandoit_header__
#define DF_BUGFIX_MAILBOX_OUTOFDATE				"2011-01-18a-버그 #3202"	//ICANDOIT (공통)(한국#693)우편물의 보관시간이 줄어들지 않는 현상

#define ENABLE_YD_ZEROPC_4263					"2011-04-06"		//(YD_공통) Zero PC방 연동작업 
#define ENABLE_YD_ZERO_BILLING_4467						"2011-04-19"	// #4467(YD_공통) Zero Billing 연동작업

#define ENABLE_SERVER_AGENT_51						"2011-0508" // icandoit 서버 에이젼트기능.
#define	ENABLE_NEW_YD_ZERO_BILLING_4467 "2011-05-11" // 기존 ZERO PC모듈에 통합된 빌링연동처리

#if defined(DF_DEBUG_ICANDOIT) && defined(DF_VER_YD)
#define DEBUG_YD_ZEROPC_DEV_ICANDOIT // YD PC방용 개발버젼. //개발후 삭제예정.
#endif

//#define ENABLE_YD_ZEROCOUPON_4670			"2011-05-20"	// YD ZERO 쿠폰

//#define ENABLE_YD_ORDER_CODE_CONFIRM  // yd billing addon

