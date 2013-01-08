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
// ������ feature define
//--------------------------------------------------------------------------
#define DEF_ICANDOIT_LOG_NET_PACKET// ���� �����ø� ����ϴ� define
#define DEF_ICANDOIT_DISABLE_SOCKET_DISCONN // ������ ���� ���� �������°� ����.
#define DEF_ICANDOIT_NOT_USE_BOSS_WORK_nRewardMileage // ������۾��Ͻ� ���ϸ��� �۾� ��� ����.
//#define DEF_ICANDOIT_DEBUG_MOVE //�̵���Ŷ���� ������.
#define DEF_ICANDOIT_MAIL_LOG // ���ϰ��� ������.


//--------------------------------------------------------------------------
// �ӽ� feature define
//--------------------------------------------------------------------------
//#define DF_RANDOMBOX_ENSURE_ITEM		"2011-01-12"	// icandoit �������� #3254 (����) ItemRandomBox, ItemGambleBox���� ������ �������ִ� �������ʵ� �߰��۾�
#define DF_BUGFIX_GMTOOL_ITEM_NEED_RANDOM_OPTION	"2011-01-13b-���� #3228" //ICANDOIT  (����_CS 1��)(#����377) GM tool�� �̿��� �����鿡�� �������� ������ ���
//#define DF_ABUSING_MOVE_PACKET_BY_NET_DISCONN	"2011-01-17a-���� #2867"	//ICANDOIT  (����)(�ѱ�#578) ������ �̰� �̵� �� ĳ���� ���� �̵� ����
#endif // __header_icandoit_header__
#define DF_BUGFIX_MAILBOX_OUTOFDATE				"2011-01-18a-���� #3202"	//ICANDOIT (����)(�ѱ�#693)������ �����ð��� �پ���� �ʴ� ����

#define ENABLE_YD_ZEROPC_4263					"2011-04-06"		//(YD_����) Zero PC�� �����۾� 
#define ENABLE_YD_ZERO_BILLING_4467						"2011-04-19"	// #4467(YD_����) Zero Billing �����۾�

#define ENABLE_SERVER_AGENT_51						"2011-0508" // icandoit ���� ������Ʈ���.
#define	ENABLE_NEW_YD_ZERO_BILLING_4467 "2011-05-11" // ���� ZERO PC��⿡ ���յ� ��������ó��

#if defined(DF_DEBUG_ICANDOIT) && defined(DF_VER_YD)
#define DEBUG_YD_ZEROPC_DEV_ICANDOIT // YD PC��� ���߹���. //������ ��������.
#endif

//#define ENABLE_YD_ZEROCOUPON_4670			"2011-05-20"	// YD ZERO ����

//#define ENABLE_YD_ORDER_CODE_CONFIRM  // yd billing addon

