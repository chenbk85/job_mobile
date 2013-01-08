// tool_FileParser.h : main header file for the tool_FileParser application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Ctool_FileParserApp:
// See tool_FileParser.cpp for the implementation of this class
//

class Ctool_FileParserApp : public CWinApp
{
public:
	Ctool_FileParserApp();

protected:
	CMultiDocTemplate* m_pDocTemplate;
public:

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	afx_msg void OnFileNewFrame();
	afx_msg void OnFileNew();
	DECLARE_MESSAGE_MAP()
};

extern Ctool_FileParserApp theApp;