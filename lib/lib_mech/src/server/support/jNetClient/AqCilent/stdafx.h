// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <vector>

using namespace std;
#include "windows.h"
#include "tchar.h"

#define TownServer_jNOTUSE_PACKET_JXDEFINE
#define LoginServer_jNOTUSE_PACKET_JXDEFINE
#define DungeonServer_jNOTUSE_PACKET_JXDEFINE
#define TownServer_jNOT_USE_PACKET_PLUGIN_HELP
#define LoginServer_jNOT_USE_PACKET_PLUGIN_HELP
#define DungeonServer_jNOT_USE_PACKET_PLUGIN_HELP
#define TownServer_jNOTUSE_PACKET_HPP_INCLUDE
#define LoginServer_jNOTUSE_PACKET_HPP_INCLUDE
#define DungeonServer_jNOTUSE_PACKET_HPP_INCLUDE
#define AQ_SERVER_LIB_API
#define jEXCEL_SQL_BIND_FUNC_DECL(Use_Avatar,asdf,nTR_excel,nAQ)

namespace nMech
{
	namespace nUtil
	{
		template<typename T>
		struct jCSV_File
		{

		};

	}
}
#define jPARAM(X) Data_##X& Data = *(Data_##X*)_pData;
#define jCALLBACK(X) void CALLBACK_##X(void* _pData){
#define jCALLBACK_PARAM(X) void CALLBACK_##X(void* _pData){ jPARAM(X)
#define jCALLBACK_end(X) }
#define jSET_CALLBACK(X) void CALLBACK_##X(void* _pData);g_Net->Set_CallBack( #X , CALLBACK_##X);


#include "jTypedef_type.h"
#include "jDefine.h"
#include "m_stltag.h"
#include "Z:/source/share/network/AqServerClient_CommonHeader.h"

namespace nMech
{
#undef TR_SERVER_SIDE_CODE
#define jNOT_USE_SQ_BIND_CODE
	#include "z:/source/share/network/excel/aq_table.h"
}
using namespace nMech::nTR_excel;
using namespace nMech::nTR_excel::nAQ;

#include "Z:/source/share/network/AqServerClient_CommonHeader_End.h"

// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "jINetClient.h"
