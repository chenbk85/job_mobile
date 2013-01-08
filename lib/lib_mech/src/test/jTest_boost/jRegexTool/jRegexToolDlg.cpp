// jRegexToolDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "jRegexTool.h"
#include "jRegexToolDlg.h"
#include ".\jregextooldlg.h"

#include <iostream>
#include <string>
#include <boost/regex.hpp>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


#define  ASDF() \
	asdk(match_default )\
	asdk(match_not_bol )\
	asdk(match_not_eol )\
	asdk(match_not_bob )\
	asdk(match_not_eob )\
	asdk(match_not_bow )\
	asdk(match_not_eow )\
	asdk(match_not_dot_newline )\
	asdk(match_not_dot_null )\
	asdk(match_prev_avail )\
	asdk(match_any )\
	asdk(match_not_null )\
	asdk(match_continuous )\
	asdk(match_partial )\
	asdk(match_all )\
	asdk(match_perl )\
	asdk(match_posix )\
	asdk(match_nosubs )\
	asdk(match_extra )\
	asdk(match_single_line )\
	asdk(format_perl )\
	asdk(format_default )\
	asdk(format_sed )\
	asdk(format_all )\
	asdk(format_no_copy )\
	asdk(format_first_only )\


#define  ASDF_match() \
	asdk(match_default )\
	asdk(match_not_bol )\
	asdk(match_not_eol )\
	asdk(match_not_bob )\
	asdk(match_not_eob )\
	asdk(match_not_bow )\
	asdk(match_not_eow )\
	asdk(match_not_dot_newline )\
	asdk(match_not_dot_null )\
	asdk(match_prev_avail )\
	asdk(match_any )\
	asdk(match_not_null )\
	asdk(match_continuous )\
	asdk(match_partial )\
	asdk(match_all )\
	asdk(match_perl )\
	asdk(match_posix )\
	asdk(match_nosubs )\
	asdk(match_extra )\
	asdk(match_single_line )\


#define  ASDF_format() \
	asdk(format_perl )\
	asdk(format_default )\
	asdk(format_sed )\
	asdk(format_all )\
	asdk(format_no_copy )\
	asdk(format_first_only )\


std::vector<std::string> g_FlagListMatch;
std::vector<std::string> g_FlagListFormat;

boost::match_flag_type jGetFlagMatch(const std::string str)
{
	if(str=="NULL") return boost::match_default;
#define asdk(x) if( str == #x ) return boost::x;
	ASDF()
#undef asdk
		return boost::match_default;
}



// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// ��ȭ ���� ������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ����

	// ����
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}
void CjRegexToolDlg::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	OnCancel();
}

void CjRegexToolDlg::OnBnClickedHelp()
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CjRegexToolDlg ��ȭ ����



CjRegexToolDlg::CjRegexToolDlg(CWnd* pParent /*=NULL*/)
: CDialog(CjRegexToolDlg::IDD, pParent)
, m_editOrg(_T(""))
, m_editMatch(_T(""))
, m_editResult(_T(""))
, m_editReplace(_T(""))
, m_logFile(_T(".\match.txt"))
, m_caseOk(FALSE)
, m_bAutoSave(FALSE)
, m_editDesc(_T(""))
{
#define asdk(x) g_FlagListMatch.push_back(#x);
	ASDF_match()
#undef asdk

#define asdk(x) g_FlagListFormat.push_back(#x);
		ASDF_format()
#undef asdk

		m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CjRegexToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ORG, m_editOrg);
	DDX_Text(pDX, IDC_EDIT_MATCH, m_editMatch);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_editResult);
	DDX_Text(pDX, IDC_EDIT_REPLACE, m_editReplace);
	DDX_Control(pDX, IDC_COMBO1, m_Flag1);
	DDX_Control(pDX, IDC_COMBO2, m_Flag2);
	DDX_Text(pDX, IDC_EDIT_MATCH2, m_logFile);
	DDX_Check(pDX, IDC_CHK_CASE, m_caseOk);
	DDX_Check(pDX, IDC_CHK_AUTOSAVE, m_bAutoSave);
	DDX_Text(pDX, IDC_EDIT_DESC, m_editDesc);
}

BEGIN_MESSAGE_MAP(CjRegexToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BT_SEARCH, OnBnClickedBtSearch)
	ON_BN_CLICKED(IDC_BT_SEARCH2, OnBnClickedBtReplace)
	ON_BN_CLICKED(IDC_BT_MATCH, OnBnClickedBtMatch)
	ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
	ON_BN_CLICKED(IDC_HELP, OnBnClickedHelp)
	ON_BN_CLICKED(ID_OPENLOG, OnBnClickedOpenlog)
	ON_BN_CLICKED(IDC_BT_SAVE, OnBnClickedBtSave)
END_MESSAGE_MAP()


// CjRegexToolDlg �޽��� ó����

BOOL CjRegexToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	// �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	int is=0;
	int i =0;
	for( ; i < g_FlagListMatch.size() ; ++i)
	{
		CString str = g_FlagListMatch[i].c_str();
		m_Flag1.InsertString(i,str);
		if(str=="match_default")
			m_Flag1.SetCurSel(i);
	}
	m_Flag1.InsertString(i,"NULL");

	i=0;
	for( ; i < g_FlagListFormat.size() ; ++i)
	{
		CString str = g_FlagListFormat[i].c_str();
		m_Flag2.InsertString(i,str);
		if(str=="format_all")
			m_Flag2.SetCurSel(i);
	}

	m_bAutoSave= false;

	m_Flag2.InsertString(i,"NULL");
	m_caseOk = true;
	boost::filesystem::path foo( boost::filesystem::initial_path() / "../match.txt" );
	foo = foo.normalize();
	m_logFile = foo.native_directory_string().c_str();
	m_Flag1.UpdateData(0);
	UpdateData(0);

	return TRUE;  // ��Ʈ�ѿ� ���� ��Ŀ���� �������� ���� ��� TRUE�� ��ȯ�մϴ�.
}

void CjRegexToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸����� 
// �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
// �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CjRegexToolDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�. 
HCURSOR CjRegexToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

std::string g_szAction="NULL";
void CjRegexToolDlg::SaveFile1(const char*  strAction,bool iscustomSave)
{
	if(!iscustomSave)
	{
		g_szAction = strAction;
		if(!m_bAutoSave)
		{
			return;
		}
	}
	else
	{
		UpdateData();
	}
	FILE* fp = fopen(m_logFile,"a+");
	if(!fp) return;

	int isel = m_Flag1.GetCurSel();
	CString s1;
	m_Flag1.GetLBText(isel , s1);
	CString s2;
	isel = m_Flag2.GetCurSel();
	m_Flag2.GetLBText(isel , s2);

	fprintf(fp , "%s[%s]\n(%s|%s) \n����: %s\n", strAction
		,m_caseOk ? "case ok" : "no case"
		,s1,s2
		, m_editOrg);
	fprintf(fp , "����: %s\n", m_editMatch);
	if(!strcmp("regex_replace" , strAction))
		fprintf(fp , "�ٲٱ�: %s\n", m_editReplace);
	CString str23 ;
	{
		str23 = m_editResult;
		str23.Replace("\r\n", "\n");
		fprintf(fp , "���: %s\n", str23);
	}
	str23 = m_editDesc;
	str23.Replace("\r\n", "\n");
	if(iscustomSave)
	{
		fprintf(fp , "����: %s\n", str23);
	}
	fprintf(fp , "=================================\n");
	fclose(fp);

}


void CjRegexToolDlg::OnBnClickedOpenlog()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	CString exe1;
	exe1.Format("notepad %s" , m_logFile);
	WinExec(exe1,SW_SHOWNORMAL);
}

void CjRegexToolDlg::OnBnClickedBtSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SaveFile1( g_szAction.c_str() , true);
}

unsigned long  CjRegexToolDlg::GetFlagMatch()
{
	int isel = m_Flag1.GetCurSel();
	CString s1;
	m_Flag1.GetLBText(isel , s1);
	boost::match_flag_type  iFlag1 =jGetFlagMatch((const char*)s1);
	return iFlag1;

}
unsigned long  CjRegexToolDlg::GetFlagMatch2()
{
	int isel = m_Flag2.GetCurSel();
	CString s1;
	m_Flag2.GetLBText(isel , s1);
	boost::match_flag_type  iFlag1 =jGetFlagMatch((const char*)s1);
	return iFlag1;

}

void CjRegexToolDlg::OnBnClickedBtSearch()
{
	/*
	// <�׸��� ���۵Ǿ�>�׸��� ������ ���ڿ��� ��ġ�ϴ� ���� ǥ������ �˻�
	boost::regex  r( "<[^>]+>" );
	boost::smatch m;
	string str1 = "The HTML tag <title > means that ...";

	if( boost::regex_search(str1, m, r) )
	{
	cout << "found (pos=" << m.position() << ")" << endl;
	cout << " ==> " << m.str() << endl;
	}
	*/


	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	try
	{

		boost::regex  r;
		if(!m_caseOk)
			r.assign( (const char*)m_editMatch , boost::regbase::icase);
		else
			r.assign((const char*)m_editMatch );

		//boost::smatch m;
		string str1 = (const char*)m_editOrg;

		boost::match_flag_type flag = boost::match_default;

		boost::match_flag_type iFlag1 = (boost::match_flag_type )GetFlagMatch();
		if(iFlag1!=boost::match_default)
			flag = iFlag1;

		boost::match_flag_type flag2 = boost::format_all;
		boost::match_flag_type iFlag2 = (boost::match_flag_type )GetFlagMatch2();
		if(iFlag2!=boost::format_all)
			flag2 = iFlag2;

		boost::match_results<std::string::const_iterator> m;
		std::string::const_iterator start = str1.begin();
		std::string::const_iterator end = str1.end();

		m_editResult.Format("Ok");
		int ii=0;
		while (boost::regex_search(start, end, m, r,flag | flag2))
		{
			// m[0]�� ��ġ�ϴ� �κ� ���ڿ��� ��Ÿ����,
			// m[0].first�� ��ġ�ϴ� �κ��� ���� ��ġ,
			// m[0].second�� ��ġ�ϴ� �κ��� ���� ��Ÿ����.
			// m[n]�� ���� ǥ����(��ȣ�� �ѷ����� ǥ����)�� ��Ÿ���µ�, 
			// ���� ���� ǥ���Ŀ� ���� ǥ������ �������� �ʱ� ������, 
			// ���⼭�� [0] �ۿ��� �� ���� ����.
			CString sRet;
			std::string s12 = m[0];
			if(s12.size()==0) break;
			sRet.Format("\r\n(%d)%s = %d~%d" 
				,ii,s12.c_str()  , m[0].first - str1.begin() , m[0].second - str1.begin());
			start = m[0].second;
			m_editResult += sRet;
			++ii;


		}
		if( ii!=0)
		{
			UpdateData(0);
			SaveFile1("regex_search");

			return ;
		}
	}

	catch (std::exception& e)
	{
		cerr << e.what() << endl;
	}


	/*

	if( boost::regex_search(str1, m, r,flag) )
	{
	int ii =m.position();
	std::string str = m.str() ;
	m_editResult.Format("Ok\r\n found ( pos=%d ) \r\n\r\n---------------------\r\n\r\n",ii);
	m_editResult += (str.c_str());
	UpdateData(0);
	return;
	}
	*/
	m_editResult.Format("Fail");
	UpdateData(0);

	SaveFile1("regex_search");

	return;
}

void CjRegexToolDlg::OnBnClickedBtReplace()
{
	UpdateData();
	try
	{
		/*
		// ��ġ�� �κ���, ���Ŀ�#(��)�� ���� ���ڿ��� ġȯ�Ѵ�
		boost::regex r2( "A([1-9]*|[a-z]*)A" );
		string str2 = "A123A AaaaA A3b3A A9A";
		cout <<	boost::regex_replace(  str2, r2, "#$0#", boost::format_all )<< endl;
		*/
		boost::match_flag_type flag = boost::match_default;
		if(m_caseOk)
		{
			//flag = flag | boost::regbase::icase;
		}

		boost::match_flag_type iFlag1 = (boost::match_flag_type )GetFlagMatch();
		if(iFlag1!=boost::match_default)
			flag = iFlag1;

		boost::match_flag_type flag2 = boost::format_all;
		boost::match_flag_type iFlag2 = (boost::match_flag_type )GetFlagMatch();
		if(iFlag2!=boost::format_all)
			flag2 = iFlag2;


		boost::regex r2;//( (const  char*)m_editMatch );
		if(!m_caseOk)
			r2.assign( (const char*)m_editMatch , boost::regbase::icase);
		else
			r2.assign((const char*)m_editMatch );


		string str2 = (const char*)m_editOrg;
		string replaceStr = (const char*)m_editReplace;
		std::string ret = boost::regex_replace(	str2, r2, replaceStr, flag | flag2 );
		m_editResult = ret.c_str();
	}
	catch (std::exception& e)
	{
		std::string s = e.what();
		::AfxMessageBox( s.c_str() , MB_OK);
		//cerr << "Exception: " << e.what() << endl;
	}
	SaveFile1("regex_replace");

	UpdateData(0);
}

void CjRegexToolDlg::OnBnClickedBtMatch()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData();
	try
	{

		/*
		static const boost::regex e("(\\d{4}[- ]){3}\\d{4}");
		\d���ڰ� ��Ȯ�� 4�� ���� "-" or " "�� �� �׸���
		�׸��� ����1�� �ٽ� ��Ȯ�� 3������ �������� \d(����)�� �ٽ� 4����
		// s = 1234-1234 6344 5654
		return regex_match(s, e);
		*/
		boost::match_flag_type flag = boost::match_default;
		if(m_caseOk)
		{
			//flag = flag | boost::regbase::icase;
		}
		boost::match_flag_type iFlag1 = (boost::match_flag_type )GetFlagMatch();
		if(iFlag1!=boost::match_default)
			flag = iFlag1;

		boost::match_flag_type flag2 = boost::format_all;
		boost::match_flag_type iFlag2 = (boost::match_flag_type )GetFlagMatch();
		if(iFlag2!=boost::format_all)
			flag2 = iFlag2;

		std::string str = (const char*)m_editOrg;
		boost::regex re;//((const char*)m_editMatch);
		if(!m_caseOk)
			re.assign( (const char*)m_editMatch , boost::regbase::icase);
		else
			re.assign((const char*)m_editMatch );

		boost::cmatch matches;
		if (boost::regex_match(str.c_str(), matches,re))
		{
			std::string mat1 = matches[0];
			m_editResult = "True";
			m_editResult.Format("True : [%s]",mat1.c_str() );
			// matches[0] contains the original string.  matches[n]
			// contains a sub_match object for each matching
			// subexpression
			for (int i = 1; i < matches.size(); i++)
			{
				// sub_match::first and sub_match::second are iterators that
				// refer to the first and one past the last chars of the
				// matching subexpression
				string match(matches[i].first, matches[i].second);
				CString strRet;

				strRet.Format("\r\n[%d]%s====%d~%d", i, match.c_str() ,match.begin()-str.begin()
					, match.end()-str.begin());
				m_editResult +=strRet;
			}
		}
		else
		{
			m_editResult = "False";
		}
	}
	catch (std::exception& e)
	{
		m_editResult = "False";
		std::string s = e.what();
		::AfxMessageBox( s.c_str() , MB_OK);
		//cerr << "Exception: " << e.what() << endl;
	}

	SaveFile1("regex_match");
	UpdateData(0);
}


