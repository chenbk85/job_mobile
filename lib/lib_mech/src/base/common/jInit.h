/* file : common/jInit.h
Coder : by icandoit (mech12@nate.com)
Date : 2005-06-15 14:57:51
title : 
desc : 

*/

#ifndef __jSupportXmlInit_header__
#define __jSupportXmlInit_header__
#pragma once


#include "base/jXmlDictionary.h"
namespace nMech
{

	typedef bool is_func_t();
	typedef void void_func_void_t();
	typedef void void_func_cstr_t(cstr);
	typedef void jUnLoadModelPanel_t();

	extern jCOMMON_API is_func_t* g_IsInGameMode;
	// g_IsInGameMode==NULL �̸� jGameClient.exe�� �����Ų���̰� ���� ������ ���� jGameTool.exe�� �����Ų���̴�.
	// jGameTool.exe�� ���������� g_IsInGameMode() == true�̸� ���� ���Ӹ���̸� false�� edit����̴�.

	extern jCOMMON_API void Send_jeCopyData_CHANGE_STAGE_XMLDATA(cstr szOrb ,jIE* pE, jIA* pA);
	extern jCOMMON_API void Send_jeCopyData_CHANGE_GUI_SELECT(cstr szOrb,jIE* pE);

	extern jCOMMON_API void jMech_Init(bool isMulti = false,bool debugException=true);
	extern jCOMMON_API void jMech_Close();
	extern jCOMMON_API jID* jGET_PRELOAD_DOC(cstr szDocNic,jID*doc);
}


#endif // __jSupportXmlInit_header__
