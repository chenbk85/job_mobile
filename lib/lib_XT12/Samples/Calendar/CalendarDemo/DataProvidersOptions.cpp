// DataProvidersOptions.cpp : implementation file
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
#include "calendardemo.h"
#include "DataProvidersOptions.h"
#include "CalendarDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const CString cstrMemExt = _T(".xtp_cal");
const CString cstrDbExt = _T(".mdb");

extern BOOL IsFileExist(LPCTSTR pcszFile);
/////////////////////////////////////////////////////////////////////////////
// CDataProvidersOptions dialog

CDataProvidersOptions::CDataProvidersOptions(CWnd* pParent /*=NULL*/)
	: CDialog(CDataProvidersOptions::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataProvidersOptions)	
	//}}AFX_DATA_INIT

	m_bWarnIfExist = FALSE;
	m_strTitle = _T("Select data provider and data file");
	
	m_bOpenMode = FALSE;	

	m_eMode = modeAll;

	m_bIsDPWasChanged = FALSE;
	m_bIsFileWasChanged = FALSE;

	m_bInitFromProfile = TRUE;
	m_bSaveToProfile = TRUE;
}

void CDataProvidersOptions::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataProvidersOptions)
		
	DDX_Control(pDX, IDC_DPFOPT_USE_MEM_DP, m_ctrlUseMemDP);
	DDX_Control(pDX, IDC_DPFOPT_USE_DB_DP, m_ctrlUseDBDP);
	DDX_Control(pDX, IDC_DPFOPT_USE_MAPI_DP, m_ctrlUseMAPIDP);
	
	DDX_Control(pDX, IDC_DPFOPT_USE_MEM_DP_HELP, m_ctrlMemFileHelp);
	DDX_Control(pDX, IDC_DPFOPT_USE_MEM_DP_FRAME, m_ctrlMemFrame);
	DDX_Control(pDX, IDC_DPFOPT_USE_MEM_DP_FILE_BROWSE, m_ctrlMemFileBrowse);
	DDX_Control(pDX, IDC_DPFOPT_USE_MEM_DP_FILE_LABEL, m_ctrlMemFileLabel);
	DDX_Control(pDX, IDC_DPFOPT_USE_MEM_DP_FILE, m_ctrlMemFile);
	DDX_Control(pDX, IDC_DPFOPT_USE_DB_DP_HELP, m_ctrlDBFileHelp);
	DDX_Control(pDX, IDC_DPFOPT_USE_DB_DP_FRAME, m_ctrlDBFrame);
	DDX_Control(pDX, IDC_DPFOPT_USE_DB_DP_FILE_LABEL, m_ctrlDBFileLabel);
	DDX_Control(pDX, IDC_DPFOPT_USE_DB_DP_FILE_BROWSE, m_ctrlDBFileBrowse);
	DDX_Control(pDX, IDC_DPFOPT_USE_DB_DP_FILE, m_ctrlDBFile);
	
	DDX_Control(pDX, IDC_DPFOPT_USE_MAPI_DP_FRAME, m_ctrlMAPIFrame);
	
	DDX_Control(pDX, IDC_DPFOPT_USE_DB_MAPI_LABEL, m_ctrlMAPILabel);
	
	DDX_Control(pDX, IDOK, m_ctrlOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataProvidersOptions, CDialog)
	//{{AFX_MSG_MAP(CDataProvidersOptions)
	ON_BN_CLICKED(IDC_DPFOPT_USE_MEM_DP_FILE_BROWSE, OnMemDPFileBrowse)
	ON_BN_CLICKED(IDC_DPFOPT_USE_DB_DP_FILE_BROWSE, OnDBDPFileBrowse)
	ON_BN_CLICKED(IDC_DPFOPT_USE_DB_DP, OnUseDBDP)
	ON_BN_CLICKED(IDC_DPFOPT_USE_MEM_DP, OnUseMemDP)
	ON_BN_CLICKED(IDC_DPFOPT_USE_MAPI_DP, OnUseMAPIDP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataProvidersOptions message handlers

BOOL CDataProvidersOptions::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(m_strTitle);
	
	if (m_bInitFromProfile)
	{	
		m_strUseDP_Prev = AfxGetApp()->GetProfileString(cstrDP_Opt_section, cstrUseDP_opt);
			
		m_strMemDPFile_Prev = AfxGetApp()->GetProfileString(cstrDP_Opt_section, cstrUseDP_Mem_File_opt);
		m_ctrlMemFile.SetWindowText(m_strMemDPFile_Prev);

		m_strDBDPFile_Prev = AfxGetApp()->GetProfileString(cstrDP_Opt_section, cstrUseDP_DB_File_opt);
		m_ctrlDBFile.SetWindowText(m_strDBDPFile_Prev);

		if(m_strUseDP_Prev.CompareNoCase(cstrUseDP_Mem_optval) == 0) {
			OnUseMemDP();
		}
		else if(m_strUseDP_Prev.CompareNoCase(cstrUseDP_DB_optval) == 0) {
			OnUseDBDP();
		}
		else if(m_strUseDP_Prev.CompareNoCase(cstrUseDP_MAPI_optval) == 0) {
			OnUseMAPIDP();
		}
		else {
			ASSERT(m_strUseDP_Prev.IsEmpty());		

			OnUseMemDP();
		}
	}
	else
	{
		int eDPType = CXTPCalendarControl::DataProviderTypeFromConStr(m_strConnectionString);
		CString strFile = CXTPCalendarControl::DataSourceFromConStr(m_strConnectionString);
		
		switch (eDPType)
		{	
		case xtpCalendarDataProviderMemory:
			m_ctrlMemFile.SetWindowText(strFile);
			OnUseMemDP();
			break;
		case xtpCalendarDataProviderDatabase:
			m_ctrlDBFile.SetWindowText(strFile);
			OnUseDBDP();
			break;
		case xtpCalendarDataProviderMAPI:
			OnUseMAPIDP();
			break;
		default:			
			OnUseMemDP();
		}
	}

	if (m_eMode == modeMemOnly) 
	{
		m_ctrlUseMemDP.EnableWindow(TRUE);
		m_ctrlUseDBDP.EnableWindow(FALSE);		
		m_ctrlUseMAPIDP.EnableWindow(FALSE);
	}
	if (m_eMode == modeDBOnly) 
	{
		m_ctrlUseMemDP.EnableWindow(FALSE);
		m_ctrlUseDBDP.EnableWindow(TRUE);		
		m_ctrlUseMAPIDP.EnableWindow(FALSE);
	}
	
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDataProvidersOptions::CheckExist(LPCTSTR pcszFile) 
{
	if(m_bWarnIfExist && IsFileExist(pcszFile)) 
	{
		int nRes = AfxMessageBox(_T("The spesified file is exist.\n Wold You like to overwrite it?"), MB_YESNO);
		return (nRes == IDYES);
	}
	return TRUE;
}

void CDataProvidersOptions::OnOK() 
{
	CString strConn_Prev = m_strConnectionString;
	
	CString strDataFile;
	if(m_ctrlUseMemDP.GetCheck())		
	{
		m_ctrlMemFile.GetWindowText(strDataFile);

		if(strDataFile.IsEmpty()) {
			AfxMessageBox(_T("Please enter Data file name."));
			m_ctrlMemFile.SetFocus();
			return;
		}
		if (strDataFile.Right(cstrMemExt.GetLength()).CompareNoCase(cstrMemExt))
		{
			CString strMsg;
			strMsg.Format(IDS_MSG_EXT, cstrMemExt);
			if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
			{
				strDataFile += cstrMemExt;
				m_ctrlMemFile.SetWindowText(strDataFile);
			}
		}
		if(!CheckExist(strDataFile)) {			
			m_ctrlMemFile.SetFocus();
			return;
		}
        		
		//*******************
		m_strConnectionString.Format(_T("Provider=XML;Data Source='%s';"), strDataFile);
        
		if (m_bSaveToProfile)
		{
			AfxGetApp()->WriteProfileString(cstrDP_Opt_section, cstrUseDP_opt, 
											cstrUseDP_Mem_optval);
			AfxGetApp()->WriteProfileString(cstrDP_Opt_section, cstrUseDP_Mem_File_opt, 
											strDataFile);
		}

		m_bIsDPWasChanged = m_strUseDP_Prev.CompareNoCase(cstrUseDP_Mem_optval);
		m_bIsFileWasChanged = m_strMemDPFile_Prev.CompareNoCase(strDataFile);
	} 
	else if(m_ctrlUseDBDP.GetCheck())
	{
		m_ctrlDBFile.GetWindowText(strDataFile);

		if(strDataFile.IsEmpty()) {
			AfxMessageBox(_T("Please enter Data file name."));
			m_ctrlDBFile.SetFocus();
			return;
		}
		if (strDataFile.Right(cstrDbExt.GetLength()).CompareNoCase(cstrDbExt))
		{
			CString strMsg;
			strMsg.Format(IDS_MSG_EXT, cstrDbExt);
			if (AfxMessageBox(strMsg, MB_YESNO) == IDYES)
			{
				strDataFile += cstrDbExt;
				m_ctrlDBFile.SetWindowText(strDataFile);
			}
		}
		if(!CheckExist(strDataFile)) {			
			m_ctrlDBFile.SetFocus();
			return;
		}

		//*******************
		m_strConnectionString.Format(_T("Provider=Microsoft.Jet.OLEDB.4.0;Data Source='%s';"), strDataFile);
        
		if (m_bSaveToProfile)
		{

			AfxGetApp()->WriteProfileString(cstrDP_Opt_section, cstrUseDP_opt, 
							cstrUseDP_DB_optval);
			AfxGetApp()->WriteProfileString(cstrDP_Opt_section, cstrUseDP_DB_File_opt, 
							strDataFile);
		}

		m_bIsDPWasChanged = m_strUseDP_Prev.CompareNoCase(cstrUseDP_DB_optval);
		m_bIsFileWasChanged = m_strDBDPFile_Prev.CompareNoCase(strDataFile);
	} 	
	else if(m_ctrlUseMAPIDP.GetCheck())
	{
		m_strConnectionString.Format(_T("Provider=MAPI;"));
        
		if (m_bSaveToProfile)
		{
			AfxGetApp()->WriteProfileString(cstrDP_Opt_section, cstrUseDP_opt, 
											cstrUseDP_MAPI_optval);
		}

		m_bIsDPWasChanged = m_strUseDP_Prev.CompareNoCase(cstrUseDP_MAPI_optval);
	}
	else {
		ASSERT(FALSE);		
		return;
	}
	
	//======================
	if (!m_bInitFromProfile)
	{
		m_bIsDPWasChanged = CXTPCalendarControl::DataProviderTypeFromConStr(strConn_Prev) != 
							CXTPCalendarControl::DataProviderTypeFromConStr(m_strConnectionString);

		m_bIsFileWasChanged =	CXTPCalendarControl::DataSourceFromConStr(strConn_Prev) != 
								CXTPCalendarControl::DataSourceFromConStr(m_strConnectionString);
	}
	
	CDialog::OnOK();
}

CString CDataProvidersOptions::FileBrowse(const CString& strFileName, 
										  const CString& strDefExt,
										  const CString& strFilter) 
{
	CFileDialog dlgFile(m_bOpenMode, strDefExt, strFileName,
						OFN_PATHMUSTEXIST | OFN_ENABLESIZING, 
						strFilter, this);

	dlgFile.m_ofn.lpstrTitle = _T("Select file");

	if(dlgFile.DoModal() == IDOK) {
		return dlgFile.GetPathName();
	}
	return _T("");
}

void CDataProvidersOptions::OnMemDPFileBrowse() 
{
	CString strFileName;
	m_ctrlMemFile.GetWindowText(strFileName);
	
	strFileName = FileBrowse(strFileName, _T("xtp_cal"),
			_T("Calendar binary files(*.xtp_cal)|*.xtp_cal|All Files (*.*)|*.*||"));
	
	if(!strFileName.IsEmpty()) {
		m_ctrlMemFile.SetWindowText(strFileName);
	}
}

void CDataProvidersOptions::OnDBDPFileBrowse() 
{
	CString strFileName;
	m_ctrlDBFile.GetWindowText(strFileName);

	strFileName = FileBrowse(strFileName, _T("mdb"), 
					_T("Calendar DB(*.mdb)|*.mdb|All Files (*.*)|*.*||"));

	if(!strFileName.IsEmpty()) {
		m_ctrlDBFile.SetWindowText(strFileName);
	}
	
}

void CDataProvidersOptions::OnUseMAPIDP() 
{
	m_ctrlUseMemDP.SetCheck(0);
	m_ctrlUseDBDP.SetCheck(0);
	m_ctrlUseMAPIDP.SetCheck(1);

	EnableMemDPcontrols(FALSE);
	EnableDBDPcontrols(FALSE);
	EnableMAPIDPcontrols(TRUE);
}

void CDataProvidersOptions::OnUseDBDP() 
{
	m_ctrlUseMemDP.SetCheck(0);
	m_ctrlUseDBDP.SetCheck(1);
	m_ctrlUseMAPIDP.SetCheck(0);

	EnableMemDPcontrols(FALSE);
	EnableDBDPcontrols(TRUE);		
	EnableMAPIDPcontrols(FALSE);
}

void CDataProvidersOptions::OnUseMemDP() 
{
	m_ctrlUseMemDP.SetCheck(1);
	m_ctrlUseDBDP.SetCheck(0);
	m_ctrlUseMAPIDP.SetCheck(0);

	EnableMemDPcontrols(TRUE);
	EnableDBDPcontrols(FALSE);	
	EnableMAPIDPcontrols(FALSE);
}

void CDataProvidersOptions::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDataProvidersOptions::EnableMAPIDPcontrols(BOOL bEnable)
{
	m_ctrlMAPIFrame.EnableWindow(bEnable);
	m_ctrlMAPILabel.EnableWindow(bEnable);
}

void CDataProvidersOptions::EnableDBDPcontrols(BOOL bEnable)
{
	m_ctrlDBFrame.EnableWindow(bEnable);
	m_ctrlDBFileLabel.EnableWindow(bEnable);
	m_ctrlDBFile.EnableWindow(bEnable);
	m_ctrlDBFileBrowse.EnableWindow(bEnable);
	m_ctrlDBFileHelp.EnableWindow(bEnable);
}

void CDataProvidersOptions::EnableMemDPcontrols(BOOL bEnable)
{	
	m_ctrlMemFrame.EnableWindow(bEnable);
	m_ctrlMemFileLabel.EnableWindow(bEnable);
	m_ctrlMemFile.EnableWindow(bEnable);
	m_ctrlMemFileBrowse.EnableWindow(bEnable);
	m_ctrlMemFileHelp.EnableWindow(bEnable);
}

BOOL CDataProvidersOptions::IsDPWasChanged() const
{
	return m_bIsDPWasChanged;
}

BOOL CDataProvidersOptions::IsFileWasChanged() const
{
	return m_bIsFileWasChanged;
}
