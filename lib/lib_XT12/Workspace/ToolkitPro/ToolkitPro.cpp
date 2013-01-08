// ToolkitPro.cpp : Defines the initialization routines for the DLL.
//
// This file is a part of the XTREME TOOLKIT PRO MFC class library.
// (c)1998-2008 Codejock Software, All Rights Reserved.
//
// THIS SOURCE FILE IS THE PROPERTY OF CODEJOCK SOFTWARE AND IS NOT TO BE
// RE-DISTRIBUTED BY ANY MEANS WHATSOEVER WITHOUT THE EXPRESSED WRITTEN
// CONSENT OF CODEJOCK SOFTWARE.
//
// THIS SOURCE CODE CAN ONLY BE USED UNDER THE TERMS AND CONDITIONS OUTLINED
// IN THE XTREME TOOLKIT PRO LICENSE AGREEMENT. CODEJOCK SOFTWARE GRANTS TO
// YOU (ONE SOFTWARE DEVELOPER) THE LIMITED RIGHT TO USE THIS SOFTWARE ON A
// SINGLE COMPUTER.
//
// CONTACT INFORMATION:
// support@codejock.com
// http://www.codejock.com
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <afxdllx.h>

#include "Common/XTPVersion.h"
#include "Common/XTPResourceManager.h"
#include "Common/XTPWinThemeWrapper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE extensionDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID /*lpReserved*/)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Codejock ToolkitPro Initializing!\n");
		
		// Extension DLL one-time initialization
		if (!AfxInitExtensionModule(extensionDLL, hInstance))
			return 0;
		
#if !defined(XT_INIT_BY_REGULAR_DLL)
		// Create a new CDynLinkLibrary for this app.
		new CDynLinkLibrary(extensionDLL);
		XTPResourceManager()->SetResourceHandle(extensionDLL.hResource);
#endif
	}

	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Codejock ToolkitPro Terminating!\n");
		CXTPWinThemeWrapper::m_bDllDetached = TRUE;

		// Terminate the library before destructors are called
		AfxTermExtensionModule(extensionDLL);
	}
	return 1;   // ok
}

#if defined(XT_INIT_BY_REGULAR_DLL)
// Exported DLL initialization is run in context of application
// or Regular DLL.
_XTP_EXT_CLASS void AFXAPI XTFuncInitDLL()
{
	// Create a new CDynLinkLibrary for this app.
	new CDynLinkLibrary(extensionDLL);

	XTPResourceManager()->SetResourceHandle(extensionDLL.hResource);

}
#endif // defined(XT_INIT_BY_REGULAR_DLL)
