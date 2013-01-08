/* file : common_AQ_header.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-08-13 16:06:06
comp.: actoz.com
title : 
desc : 

*/

#ifndef __common_AQ_header_header__
#define __common_AQ_header_header__
#pragma once

#ifndef jNET_COMMON_LIB_API
#define jNET_COMMON_LIB_API T_SERVER_LIB_API
#endif


// excel StringID header��
#define jSTRING_ID_LIB_API T_SERVER_LIB_API 

#pragma warning( error : 4715 )


#define jOBJECT_NAME 31 // ��� ���� ������Ʈ�� �̸��� 32-1�̴�.

//! --------------------------------------------------------------------------
//!  �⺻ ��� ����. 
//! --------------------------------------------------------------------------
#include "../TCommonClient/excel/table_const.h"

const int jMAX_TOWN_SLOT = 14;//aq_table.xls �� EItemInventoryType����
const int iMAX_TOWN_ITEM = 200; //���� ������ �ִ밹��



//! --------------------------------------------------------------------------
//! �⺻ �ڷ��� ����.
//! --------------------------------------------------------------------------

typedef nMech::uint32 dummy_id_t; // �׽�Ʈ ������ �������̵�.
typedef nMech::wname64_t player_name_t;//���� ID�̸�.
typedef nMech::wcstr	 player_name_ct;	
typedef std::wstring	 player_name_string_t;
const size_t			player_name_SIZE = 64;


typedef nMech::uint8 channelid_t; // �޸�DB������ index , ������ ���� ���� ����Ʈ������ �ε���.
typedef nMech::uint16 itemid_t;// �޸�DB������ index , ������ ���� ���� ����Ʈ������ �ε���. �ε����� 1���ͽ���. 0�� ������� �ʴ´�.
typedef nMech::uint16 inven_slot_t;//�κ��丮�� 0~1000 , â��� 1000����...
typedef nMech::uint8 skillid_t; // skid �迭�� ���� 1���ͽ���

typedef nMech::uint16 serverid_t;//central server���� �ο�.

jLIST_TYPEDEF_vector_typedef(astring,astrings);
jLIST_TYPEDEF_vector_typedef(wstring,wstrings);
#ifdef UNICODE
jLIST_TYPEDEF_vector_typedef(tstring,wstrings);
#else
jLIST_TYPEDEF_vector_typedef(tstring,astrings);
#endif

#include "interface/db/db_uid_type.h"
#include "../TCommonClient/excel/table_type.h"
#include "../TCommonBase/player_id_t.h"

//! --------------------------------------------------------------------------
//!  �⺻ ����ü ����
//! --------------------------------------------------------------------------

//! W_ERROR, DC_ERROR, L_ERROR, T_ERROR, D_ERROR , U_ERROR , C_ERROR���� ���.
enum EErrorActionType
{
	eEAT_SKIP // �ش� �α׸� ����� �ƹ� �׼��� ������ ����.
	,eEAT_NOTIFY_TO_CLIENT // �������� �����޽����� �����Ѵ�.
	,eEAT_NOTIFY_ALL_CLIENT // �������� ��� �����޽����� �����Ѵ�.
	,eEAT_NOTIFY_AND_DISCON_USER // �����޼��� ������ �ش� Ŭ���̾�Ʈ ������ ���´�.
	,eEAT_DISCON_USER // �� �޼����� ������ ������ �ش� Ŭ���̾�Ʈ ������ ��� ���´�.
};
struct jErrorInfo // ��Ʈ����Ű��� ���� ��������.
{

	jError		e; //���� �߻��Ѱ����� ������ ���� ����.
	player_id_t	pid;
	uint8		eAction; // EErrorActionType , �����޽����� �ް� ���� socket�� ���� ó��(disconnect or skip or log)
	void SetAction(EErrorActionType e){ eAction=(EErrorActionType)e;}
	EErrorActionType GetAction() { return (EErrorActionType)eAction;}
	bool IsAction(EErrorActionType e){ return eAction==e;}
	astring		sFunction;

	jErrorInfo(){}
	jErrorInfo(jError _e,EErrorActionType _eAction,acstr _sFunction,player_id_t _pid):sFunction(_sFunction),e(_e),pid(_pid){SetAction(_eAction);}
	jErrorInfo(jError_Creator_arg_t s, jError_Creator_arg_t c,EErrorActionType _eAction,acstr _sFunction,player_id_t _pid)
		:sFunction(_sFunction),e(s,c),pid(_pid){SetAction(_eAction);}
};

struct jServerUserID // �������� ���� ��û�� ó���Ҷ� �ش������� ���ӵǾ� �ִ� ���������� ������ user id
{
	player_id_t uid;
	serverid_t sid;
	jServerUserID(player_id_t u,serverid_t s): sid(s){uid = u;}
	jServerUserID() : sid(0){uid.m_id = 0;}
};

struct jNoticeInfo
{
	nMech::uint8 type; //���� Ÿ��
	nMech::uint8 color;//���ϴ� ��� ���� ��
	nMech::uint16 reserve_min; //�ش� ���� ���� �� ������ Ŭ���̾�Ʈ�� ���.
	nMech::uint16 repeat_count; //�ش� ������ ��� �ݺ��ؼ� ���
};


// 
#define for_each_USER_GPS(X)\
	X(NULL , "�ʱ�ȭ����")\
	X(L_CONNECTED,"�α伭�����ӿϷ�.�������ȵǾ���.")\
	X(L_CERTIFICATION,"�α伭�� ���� �Ϸ�.")\
	X(T_USER_CONNECT,"Ÿ��� ���� �Ϸ�.")\
	X(T_PERSONALROOM,"�ۼ��� �뿡 ����.")\
	X(T_TOWN,"������ ����.")\

enum EUserGPS
{
	#define enum_USER_GPS23(name,help) eGPS_##name,
	for_each_USER_GPS(enum_USER_GPS23)
	EUserGPS_END,
};

inline nMech::tcstr ToString(EUserGPS e)
{
	#define ToString_USER_GPS23(name,help) if(e==eGPS_##name) return _T(#name);
	for_each_USER_GPS(ToString_USER_GPS23);
	return jS(EUserGPS_Unkown);
}



struct jChannelPlayerCookie
{
	player_id_t uid;
	nMech::wname32_t channel_id;
};

enum EChannelPlayerMovement
{
	eTPM_STOP,
	eTPM_WALK,
	eTPM_RUN
};


struct jWorldServerInfo
{
	aname32_t szName;
	uint8			iBusy;
};

inline cstr ToString(jWorldServerInfo* p, fname_t buf)
{
	jt_sprintf_s(buf, 256,_T("name:%s busy:%s"), p->szName, p->iBusy);
	return buf;
}


#endif // __common_AQ_header_header__
