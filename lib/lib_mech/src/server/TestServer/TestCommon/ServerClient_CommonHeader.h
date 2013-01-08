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

#define nGame nMech




#define PT_TestServer_LIB_API AQ_SERVER_LIB_API
#define jxDECL_TestServer jxDECL_NET
#define jxDEFINE_TestServer jxDEFINE_NET

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

typedef nMech::uint16 dummyclient_id_t; // did, test client  �ĺ�  id
typedef nMech::uint32 dummy_id_t; // �׽�Ʈ ������ �������̵�.
typedef nMech::aname32_t username_t;//���� ID�̸�.


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



#endif // __common_AQ_header_header__
