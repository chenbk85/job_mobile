// jSrcBackup.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CjSrcBackupApp:
// �� Ŭ������ ������ ���ؼ��� jSrcBackup.cpp�� �����Ͻʽÿ�.
//

class CjSrcBackupApp : public CWinApp
{
public:
	CjSrcBackupApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CjSrcBackupApp theApp;
extern CString g_sProjName;
extern CString g_sTargetDir;
extern CString g_sDestDir;
#include <vector>
