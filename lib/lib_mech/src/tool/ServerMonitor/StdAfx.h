// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__39A7805A_725B_4309_8722_3FE0C0B9F590__INCLUDED_)
#define AFX_STDAFX_H__39A7805A_725B_4309_8722_3FE0C0B9F590__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT



// VC6 STL implimentation is *atrocious*
#pragma warning (disable : 4786)

#include "header/jHeader.h"
using namespace nMech;
#define jjj_USES_CONVERSION
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#include "common/jCommon.h"
#include "interface/net/jINet.h"
#include "interface/jIConsoleDLL.h"
#include "header/jDllLoader.h"
#include "interface/jIConsoleDlg.h"
#include "interface/jIConsoleCmd.h"


using namespace nMech;
using namespace nMech::nNET;


int init_Tool();
void show_Tool(HINSTANCE hInstance);
bool close_Tool();
void show_console_window();
void hide_console_window();

#pragma warning(disable : 4819)


#define READ_PACKET_jSM(X) READ_PACKET(X);\
	nswb1024_t buf;\
	if(!g_pjServerMonitor)return;\
	jServerMonitor* pSM = g_pjServerMonitor\



#include "./net/net_common/net_Common.h"



#define DF_ENABLE_SERVER_FORM_BY_App_ServerMonitor


#endif // !defined(AFX_STDAFX_H__39A7805A_725B_4309_8722_3FE0C0B9F590__INCLUDED_)


