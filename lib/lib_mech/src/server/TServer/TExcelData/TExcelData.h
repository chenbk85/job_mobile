/* file : TExcelData.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-10-20 19:56:31
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __TExcelData_header__
#define __TExcelData_header__
#pragma once



#ifdef TEXCELDATA_EXPORTS
#define TEXCELDATA_API __declspec(dllexport)
#else
#define TEXCELDATA_API __declspec(dllimport)
#pragma comment(lib, "TExcelData.lib")
#endif


#include "interface/net/jDebugPrint.h"
#include "header/ToString_base.h"
#include "interface/db/db_uid_type.h"


#include "interface/net/excel_code_util.h"
#include "Interface/net/net_common_code.h"

#include "interface/db/db_uid_type.h"
#include "header/jCSV_File.h"

//! excel code���� ����ϴ� ���ӽ����̽��� nMech�� ��ü.
#define nExcelUtil nMech

//! excel code ���� server side������ ����ϴ� �ڵ带 ������� ����.
#define TR_SERVER_SIDE_CODE

//! excel �ڵ�� DLL export����
#define jEXCEL_LIB_API TEXCELDATA_API 


//--------------------------------------------------------------------------
// ���� csv�ε�
//--------------------------------------------------------------------------
#include "db_type.h"
namespace nTR_excel{}
using namespace nTR_excel;

#include "../TCommonClient/excel/table_type.h"




#include "../TCommonClient/excel/LocalizingTable.h"
//#include "../TCommonClient/excel/ClientResult.h"
//#include "../TCommonClient/excel/ServerResult.h"

#pragma warning ( disable:4181)
#pragma warning ( disable:4251)

#include "../TCommonClient/excel/sam_world.h"
#include "../TCommonClient/excel/sam_user.h"
#include "../TCommonClient/excel/sam_hero.h"
#include "../TCommonClient/excel/Sam_Castle.h"
#include "../TCommonClient/excel/sam_force.h"

#pragma  warning ( default:4251 )
#pragma  warning ( default:4181)


extern TEXCELDATA_API void Init_TEXCELDATA_API ();

#endif // __TExcelData_header__


