// testtool.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CTestToolApp:
// �� Ŭ������ ������ ���ؼ��� testtool.cpp�� �����Ͻʽÿ�.
//

class CTestToolApp : public CWinApp
{
public:
	CTestToolApp();

// �������Դϴ�.
	public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	afx_msg void OnShowConsole();
};

extern CTestToolApp theApp;