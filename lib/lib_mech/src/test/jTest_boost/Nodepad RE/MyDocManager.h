#ifndef MYDOCMANAGER_H
#define MYDOCMANAGER_H

#include "notepadreFile.h"

class CMyDocManager : public CDocManager
{
public:
	CMyDocManager ();
	virtual ~CMyDocManager ();

	virtual BOOL DoPromptFileName(CString& fileName, UINT nIDSTitle,
			DWORD lFlags, BOOL bOpenFileDialog, CDocTemplate* pTemplate);

private:
	static CNotepadreFile::e_FileType m_eFileType;
	static CNotepadreFile::e_FileFormat m_eFileFormat;
	bool m_bReadOnly;

	static UINT CALLBACK OFNSaveHookProc (HWND hdlg, UINT uiMsg,
		WPARAM wParam, LPARAM lParam);
};

#endif
