// jRegexTool.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error PCH���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����Ͻʽÿ�.
#endif

#include "resource.h"		// �� ��ȣ


// CjRegexToolApp:
// �� Ŭ������ ������ ���ؼ��� jRegexTool.cpp�� �����Ͻʽÿ�.
//

class CjRegexToolApp : public CWinApp
{
public:
	CjRegexToolApp();

// ������
	public:
	virtual BOOL InitInstance();

// ����

	DECLARE_MESSAGE_MAP()
};

extern CjRegexToolApp theApp;
