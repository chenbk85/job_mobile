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
#define jNET_COMMON_LIB_API AQ_SERVER_LIB_API
#endif
#define TR_SERVER_SIDE_CODE
#define nTR_net nMech
#define nGame nMech




#define PT_TownServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_TownServer jxDECL_NET
#define jxDEFINE_TownServer jxDEFINE_NET

#define PT_DungeonServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_DungeonServer jxDECL_NET
#define jxDEFINE_DungeonServer jxDEFINE_NET

// excel �ڵ��
#define TR_SERVER_LIB_API AQ_SERVER_LIB_API 

// excel StringID header��
#define jSTRING_ID_LIB_API AQ_SERVER_LIB_API 

#pragma warning( error : 4715 )


typedef nMech::uint16 serverid_t;//central server���� �ο�.
jLIST_TYPEDEF_vector_typedef(astring,id_list);

//--------------------------------------------------------------------------
// aq const 
//--------------------------------------------------------------------------
const int jMAX_TOWN_SLOT = 14;//aq_table.xls �� EItemInventoryType����
const int iMAX_TOWN_ITEM = 200; //���� ������ �ִ밹��

#include "network/userid_t.h"
#include "network/db_uid_type.h"
#include "network/excel/table_const.h"
#include "network/excel/table_type.h"

typedef nMech::uint16 dummyclient_id_t; // did, test client  �ĺ�  id
typedef nMech::uint32 dummy_id_t; // �׽�Ʈ ������ �������̵�.
typedef nMech::aname32_t username_t;//���� ID�̸�.

typedef nMech::uint8 townid_t; // �޸�DB������ index , ������ ���� ���� ����Ʈ������ �ε���.
typedef nMech::uint16 itemid_t;// �޸�DB������ index , ������ ���� ���� ����Ʈ������ �ε���. �ε����� 1���ͽ���. 0�� ������� �ʴ´�.
typedef nMech::uint16 inven_slot_t;//�κ��丮�� 0~1000 , â��� 1000����...
typedef nMech::uint8 skillid_t; // skid �迭�� ���� 1���ͽ���

struct jServerUserID // �������� ���� ��û�� ó���Ҷ� �ش������� ���ӵǾ� �ִ� ���������� ������ user id
{
	userid_t uid;
	serverid_t sid;
	jServerUserID(userid_t u,serverid_t s): sid(s){uid = u;}
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



struct jTownPlayerCookie
{
	userid_t uid;
	nMech::wname32_t town_id;
};

enum ETownPlayerMovement
{
	eTPM_STOP,
	eTPM_WALK,
	eTPM_RUN
};


//W_ERROR, DC_ERROR, L_ERROR, T_ERROR, D_ERROR , U_ERROR , C_ERROR���� ���.
enum EServer_Common_Error
{
	eSEND_Disconn_User // ��� ������ Ŭ���̾�Ʈ ���������´�.
	,eSEND_jError_ToClient // �������� �����޽����� �����Ѵ�.
	,eSEND_jError_and_User_Do_Disconn // �����޼��� ������ Ŭ���̾�Ʈ�� ������ ���´�.
};


struct jWorldServerInfo
{
	aname32_t szName;
	uint8			iBusy;
};

inline cstr ToString(jWorldServerInfo* p, fname_t buf)
{
	jt_sprintf(buf, _T("name:%s busy:%s"), p->szName, p->iBusy);
	return buf;
}


#endif // __common_AQ_header_header__
