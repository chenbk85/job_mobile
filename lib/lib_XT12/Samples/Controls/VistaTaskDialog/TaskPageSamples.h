#pragma once


class CTaskSheetProperties;

// CTaskPageSamples dialog

class CTaskPageSamples : public CPropertyPage
{
	DECLARE_DYNAMIC(CTaskPageSamples)

public:
	CTaskPageSamples();
	virtual ~CTaskPageSamples();

	CXTPTaskDialogLinkCtrl m_wndLinkCtrl;
	CXTPTaskDialogLinkCtrl m_wndLinkPadCtrl;

// Dialog Data
	enum { IDD = IDD_TASKDIALOG_SAMPLES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

public:
	DECLARE_MESSAGE_MAP()


	afx_msg void OnBnClickedCheckSkinframework();
	afx_msg void OnLinkClicked();
	afx_msg void OnBnClickedButtonProgressdialog();
	afx_msg void OnBnClickedButtonDynamicdialog();
	afx_msg void OnBnClickedButtonTimerdialog();
	afx_msg void OnLinkTDPadClicked();
	afx_msg void OnBnClickedButtonSheet();

	afx_msg void OnBnClickedXMLDialog1();
	afx_msg void OnBnClickedXMLDialog2();
	afx_msg void OnBnClickedXMLDialog3();
	afx_msg void OnBnClickedXMLDialog4();
	afx_msg void OnBnClickedXMLDialog5();
	afx_msg void OnBnClickedXMLDialog6();
	afx_msg void OnBnClickedXMLDialog7();

	void OnShowXMLDialog(LPCTSTR lpszName);

public:
	CTaskSheetProperties* m_pDlgParent;
	BOOL m_bSkinFramework;

};
