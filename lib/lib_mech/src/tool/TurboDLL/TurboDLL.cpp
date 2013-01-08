// TurboDLL.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <afxdllx.h>
#include "TurboDLL.h"
#include "TreeListResource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static AFX_EXTENSION_MODULE TurboDLL = { NULL, NULL };

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	// ���ʹ�� lpReserved ������ɾ������
	UNREFERENCED_PARAMETER(lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		TRACE0("Turbo Soft Control Gallery DLL Initializing!\n");
		
		// MFC ��չ DLL ��ʼ��
		if (!AfxInitExtensionModule(TurboDLL, hInstance))
			return 0;

		// Insert this DLL into the resource chain
		// NOTE: If this Extension DLL is being implicitly linked to by
		//  an MFC Regular DLL (such as an ActiveX Control)
		//  instead of an MFC application, then you will want to
		//  remove this line from DllMain and put it in a separate
		//  function exported from this Extension DLL.  The Regular DLL
		//  that uses this Extension DLL should then explicitly call that
		//  function to initialize this Extension DLL.  Otherwise,
		//  the CDynLinkLibrary object will not be attached to the
		//  Regular DLL's resource chain, and serious problems will
		//  result.

		new CDynLinkLibrary(TurboDLL);
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		TRACE0("Turbo Soft Control Gallery DLL Terminating!\n");

		// MFC ��չ DLL ��ֹ
		AfxTermExtensionModule(TurboDLL);
	}

	return TRUE;   // ok
}

CTreeListResource::CTreeListResource()
{
	m_hOldInst = AfxGetResourceHandle ();
	ASSERT (m_hOldInst != NULL);

	AfxSetResourceHandle( TurboDLL.hResource );
}

CTreeListResource::~CTreeListResource()
{
	AfxSetResourceHandle( m_hOldInst );
}
