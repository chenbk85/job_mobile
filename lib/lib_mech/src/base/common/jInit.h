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
	// g_IsInGameMode==NULL 이면 jGameClient.exe로 실행시킨것이고 값이 있으면 현제 jGameTool.exe로 실행시킨것이다.
	// jGameTool.exe로 실행됬을대 g_IsInGameMode() == true이면 현제 게임모드이며 false면 edit모드이다.

	extern jCOMMON_API void Send_jeCopyData_CHANGE_STAGE_XMLDATA(cstr szOrb ,jIE* pE, jIA* pA);
	extern jCOMMON_API void Send_jeCopyData_CHANGE_GUI_SELECT(cstr szOrb,jIE* pE);

	extern jCOMMON_API void jMech_Init(bool isMulti = false,bool debugException=true);
	extern jCOMMON_API void jMech_Close();
	extern jCOMMON_API jID* jGET_PRELOAD_DOC(cstr szDocNic,jID*doc);
}


#endif // __jSupportXmlInit_header__
