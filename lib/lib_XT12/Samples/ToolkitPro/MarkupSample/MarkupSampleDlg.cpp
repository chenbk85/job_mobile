// MarkupSampleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MarkupSample.h"
#include "MarkupSampleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CMarkupSampleDlg dialog

CMarkupSampleDlg::CMarkupSampleDlg(CWnd* pParent /*=NULL*/)
	: CXTResizeDialog(CMarkupSampleDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMarkupSampleDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMarkupSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CXTResizeDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMarkupSampleDlg)
	DDX_Control(pDX, IDC_TREE_MARKUP, m_wndTree);
	DDX_Control(pDX, IDC_BUTTON_MORE, m_btnMore);
	DDX_Control(pDX, IDC_CHECK_MARKUP, m_wndCheckBox);
	DDX_Control(pDX, IDC_BUTTON_MARKUP, m_wndButton);
	DDX_Control(pDX, IDC_RADIO_MARKUP, m_wndRadio);
	DDX_Control(pDX, IDC_STATIC_MARKUP, m_wndStatic);
	DDX_Control(pDX, IDC_LIST_MARKUP, m_wndList);
	DDX_Control(pDX, IDC_TABCONTROL, m_wndTabControl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMarkupSampleDlg, CXTResizeDialog)
	//{{AFX_MSG_MAP(CMarkupSampleDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MORE_POPUPCONTROL, OnMorePopupcontrol)
	ON_COMMAND(ID_MORE_UNICODESUPPORT, OnMoreUnicodesupport)
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_MORE_TASKDIALOG, OnMoreTaskdialog)
	//}}AFX_MSG_MAP
	ON_CBN_DROPDOWN(IDC_BUTTON_MORE, OnMoreDropDown)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TABCONTROL, OnTabControlSelChanged)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMarkupSampleDlg message handlers

BOOL CMarkupSampleDlg::OnInitDialog()
{
	CXTResizeDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	UINT nIDFavorite = 10;
	XTPImageManager()->SetIcons(_T("FAVORITES.PNG"), &nIDFavorite, 1, 0); 

	UINT nIDHelp = 12;
	XTPImageManager()->SetIcons(_T("HELP.BMP"), &nIDHelp, 1, 0); 

	m_wndStatic.SetMarkupText(
		"<Border Padding='4' BorderThickness='1' BorderBrush='#767676' Background='#e4ecf7'>"
		"<StackPanel TextBlock.FontFamily='Tahoma'>"
		"   <TextBlock Padding='1, 3, 1, 3' FontWeight='Bold'>Change Case</TextBlock>"
		"   <TextBlock Padding='9, 6, 30, 7' TextWrapping='Wrap'>Change all the selected text to UPPERCASE, lowercase, or <Hyperlink ToolTip='Some other capitalization'>other</Hyperlink> common capitalizations.</TextBlock>"
		"   <Border Height='1' Background='#9ebbdd' />"
		"   <Border Height='1' Background='White' />"
		"   <StackPanel Margin='1, 7, 0, 3' Orientation='Horizontal'>"
		"        <Image Source='12'/><TextBlock Margin='7, 0, 0, 0' VerticalAlignment='Center' FontWeight='Bold'>Press F1 for more help.</TextBlock>"
		"   </StackPanel>"
		"</StackPanel>"
		"</Border>");
	m_wndStatic.AddHandler(CXTPMarkupHyperlink::m_pClickEvent, CreateMarkupClassDelegate(this, &CMarkupSampleDlg::OnHyperlinkClick));

	UINT nIDLove = 13;
	XTPImageManager()->SetIcons(_T("LOVE.PNG"), &nIDLove, 1, 0); 

	m_wndRadio.EnableMarkup();
	m_wndCheckBox.EnableMarkup();
	m_wndButton.EnableMarkup();


	HTREEITEM hItemRoot = m_wndTree.AddItem(_T("Personal Folders"), -1, -1, TVI_ROOT);

	m_wndTree.AddItem(_T("Deleted Items"), -1, -1, hItemRoot);
	m_wndTree.AddItem(_T("Drafts"), -1, -1, hItemRoot);
	m_wndTree.AddItem(_T("<TextBlock><Bold>Inbox</Bold> <Run Foreground='Blue' Text='(1)'/></TextBlock>"), -1, -1, hItemRoot);
	m_wndTree.AddItem(_T("<TextBlock><Bold>Junk E-mail</Bold> <Run Foreground='Green' Text='[3]'/></TextBlock>"), -1, -1, hItemRoot);
	m_wndTree.AddItem(_T("Outbox"), -1, -1, hItemRoot);

	m_wndTree.Expand(hItemRoot, TVE_EXPAND);

	//m_wndTabControl.SetAppearance(xtpTabAppearanceStateButtons);
	m_wndTabControl.SetAppearance(xtpTabAppearanceVisualStudio);
	m_wndTabControl.GetPaintManager()->m_clientFrame = xtpTabFrameSingleLine;
	m_wndTabControl.EnableMarkup();
	m_wndTabControl.InsertItem(0, _T("<TextBlock>ListBox <Run Foreground='Green'>(3 Items)</Run></TextBlock>"));
	m_wndTabControl.InsertItem(1, _T("<TextBlock>ListBox <Run Foreground='Red'>(9 Items)</Run></TextBlock>"));


	m_btnMore.SetPushButtonStyle(xtpButtonDropDown);


	SetResize(IDC_LIST_MARKUP, SZ_TOP_LEFT, SZ_BOTTOM_RIGHT);
	SetResize(IDC_TABCONTROL, SZ_TOP_LEFT, SZ_TOP_RIGHT);

	SetResize(IDC_LABEL_TREEVIEW, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_TREE_MARKUP, SZ_BOTTOM_LEFT, SZ_BOTTOM_CENTER);

	SetResize(IDC_LABEL_STATIC, SZ_BOTTOM_CENTER, SZ_BOTTOM_RIGHT);
	SetResize(IDC_STATIC_MARKUP, SZ_BOTTOM_CENTER, SZ_BOTTOM_RIGHT);

	SetResize(IDC_LABEL_BUTTONS, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_RADIO_MARKUP, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_CHECK_MARKUP, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);
	SetResize(IDC_BUTTON_MARKUP, SZ_BOTTOM_LEFT, SZ_BOTTOM_LEFT);

	SetResize(IDC_BUTTON_MORE, SZ_BOTTOM_CENTER, SZ_BOTTOM_CENTER);
	SetResize(IDOK, SZ_BOTTOM_CENTER, SZ_BOTTOM_CENTER);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMarkupSampleDlg::AddListItem(LPCTSTR lpszMarkup)
{
	MARKUP_LISTITEM* pItem = new MARKUP_LISTITEM(&m_wndList);
	pItem->Resolve(lpszMarkup);
	m_wndList.AddString((LPCTSTR)pItem);

}

void CMarkupSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CXTResizeDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMarkupSampleDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CXTResizeDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMarkupSampleDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMarkupSampleDlg::OnHyperlinkClick(CXTPMarkupObject* pSender, CXTPMarkupRoutedEventArgs* pArgs)
{
	if (pSender->IsKindOf(MARKUP_TYPE(CXTPMarkupHyperlink)))
	{
		AfxMessageBox(_T("Hyperlink Clicked"));

		pArgs->SetHandled();
	}
}

void CMarkupSampleDlg::OnMoreDropDown()
{
	CMenu menu;
	VERIFY(menu.LoadMenu(IDR_MENU_MORE));

	CXTPWindowRect rc(GetDlgItem(IDC_BUTTON_MORE));

	TrackPopupMenu(menu.GetSubMenu(0)->GetSafeHmenu(), 0, rc.left, rc.bottom, 0, m_hWnd, 0);
}

void CMarkupSampleDlg::OnMorePopupcontrol() 
{
CXTPPopupControl* pPopup = new CXTPPopupControl();
	pPopup->SetTransparency(200);
	pPopup->SetTheme(xtpPopupThemeOffice2003);
	pPopup->AllowMove(TRUE);
	pPopup->SetAnimateDelay(500);
	pPopup->SetPopupAnimation();
	pPopup->SetShowDelay(5000);
	pPopup->SetAutoDelete(TRUE);
	
	CXTPPopupItem* pItemText = (CXTPPopupItem*)pPopup->AddItem(new CXTPPopupItem(CRect(8, 12, 500, 130)));

	LPCTSTR lpszMarkup = 
	_T("<Grid VerticalAlignment='Center' HorizontalAlignment='Center'>")
    _T("    <Grid.ColumnDefinitions>")
    _T("        <ColumnDefinition/>")
    _T("        <ColumnDefinition/>")
    _T("        <ColumnDefinition/>")
    _T("        <ColumnDefinition/>")
    _T("    </Grid.ColumnDefinitions>")
    _T("    <Grid.RowDefinitions>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("        <RowDefinition/>")
    _T("     </Grid.RowDefinitions>")
    _T("    <Border Grid.Column='0' Grid.Row='0'><TextBlock><Hyperlink>FTSE 100</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='1'><TextBlock><Hyperlink>FTSE TechMark</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='2'><TextBlock><Hyperlink>Dow Jones</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='3'><TextBlock><Hyperlink>S&amp;P 500</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='4'><TextBlock><Hyperlink>Dollar</Hyperlink></TextBlock></Border>")
    _T("    <Border Grid.Column='0' Grid.Row='5'><TextBlock><Hyperlink>Euro</Hyperlink></TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='0'><TextBlock TextAlignment='Right'>5,990.12</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='1'><TextBlock TextAlignment='Right'>804.10</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='2'><TextBlock TextAlignment='Right'>8,322.12</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='3'><TextBlock TextAlignment='Right'>860</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='4'><TextBlock TextAlignment='Right'>1.56</TextBlock></Border>")
    _T("    <Border Margin='5, 0, 5, 0' Grid.Column='1' Grid.Row='5'><TextBlock TextAlignment='Right'>1.59</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='0'><TextBlock TextAlignment='Right' Foreground='Green'>+50.1</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='1'><TextBlock TextAlignment='Right' Foreground='Red'>-0.4</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='2'><TextBlock TextAlignment='Right' Foreground='Green'>+78</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='3'><TextBlock TextAlignment='Right' Foreground='Green'>+15.43</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='4'><TextBlock TextAlignment='Right' Foreground='Green'>+0.06</TextBlock></Border>")
    _T("    <Border Grid.Column='2' Grid.Row='5'><TextBlock TextAlignment='Right' Foreground='Red'>-0.11</TextBlock></Border>")
    _T("</Grid>");
	
	
	
	pItemText->SetMarkupText(lpszMarkup);
	pItemText->FitToContent();
	CSize sz(pItemText->GetRect().Size());

	// close icon.
	CXTPPopupItem* pItemIcon = (CXTPPopupItem*)pPopup->AddItem(
		new CXTPPopupItem(CRect(sz.cx + 10, 10, sz.cx + 10 + 16, 10 + 16)));
	
	pPopup->GetImageManager()->SetIcon(IDI_POPUP_CLOSE, IDI_POPUP_CLOSE);
	pItemIcon->SetIconIndex(IDI_POPUP_CLOSE);

	pItemIcon->SetButton(TRUE);
	pItemIcon->SetID(XTP_ID_POPUP_CLOSE);

	pPopup->SetPopupSize(CSize(sz.cx + 30, sz.cy + 20));
	pPopup->Show(this);

}

void CMarkupSampleDlg::OnMoreUnicodesupport() 
{
	m_wndStatic.SetMarkupText(
		"<?xml encoding='utf-8'?>"
		"<Border Background='#eeffee' BorderBrush='#999999' BorderThickness='1'>"
		"<ScrollViewer>"
		"<StackPanel TextElement.FontFamily='Tahoma' Margin='4'>"
		"<TextBlock TextWrapping='Wrap'><Bold>Markup supports Unicode text in ANSI applications.<LineBreak/>Use UTF-8 encode to enter it:</Bold></TextBlock>"
		"<TextBlock TextWrapping='Wrap'><Italic>Languages:</Italic> 碼?晩邈磨?馬 (ar) ??Az?rbaycan (az) ????剋均逵??克龜 (bg) ??Catal횪 (ca) ??훻esky (cs) ??Deutsch (de) ???貫貫管館菅觀郭 (el) ??English (en) ??Esperanto (eo) ??Espa챰ol (es) ???碼邈卍? (fa) ??Suomi (fi) ??Fran챌ais (fr) ???ζ쑍沃?(ja) ???쒓뎅??(ko) ??Lietuvi킬 (lt) ??石?눠石?늅石녀큲 (ml) ???逵克筠畇棘戟?克龜 (mk) ??西ⓣ쪍西むㅎ西?西?ㅎ西룅ㅎ (new) ??黍むŉ黍쒉㉭黍о? (pa) ??Polski (pl) ??Portugu챗s (pt) ??Rom창n훱 (ro) ??????克龜橘 (ru) ??Svenska (sv) ??昔ㅰ?昔욈?晳?(ta) ??仙꾝툠錫?(th) ??T체rk챌e (tr) ??叫克?逵?戟??克逵 (uk) ??Ti梳퓆g Vi沼뇍 (vi) ??訝?뻼 (zh)</TextBlock>"
		"</StackPanel>"
		"</ScrollViewer>"
		"</Border>");
}

void CMarkupSampleDlg::OnTabControlSelChanged(NMHDR* pHeader, LRESULT* pResult)
{
	m_wndList.ResetContent();

	if (m_wndTabControl.GetCurSel() == 0)
	{
		AddListItem(_T("<Border BorderThickness='2' BorderBrush='DodgerBlue' Margin='2' Padding='3'><StackPanel Orientation='Horizontal'>")
			_T("<Border Width='32' Height='32'/>")
			_T("<Grid><Grid.ColumnDefinitions><ColumnDefinition Width='Auto'/><ColumnDefinition Width='*'/></Grid.ColumnDefinitions>")
			_T("<Grid.RowDefinitions><RowDefinition/><RowDefinition/></Grid.RowDefinitions>")
			_T("<TextBlock TextAlignment='Right' FontWeight='Bold' Foreground='Navy' Text='Description:'/>")
			_T("<TextBlock TextAlignment='Right' Grid.Row='1' FontWeight='Bold' Foreground='Navy' Text='Current Price:'/>")
			_T("<TextBlock Margin='6, 0, 0, 0' Grid.Column='1' Text='Digital camera'/>")
			_T("<TextBlock Margin='6, 0, 0, 0'  Grid.Column='1' Grid.Row='1'  Text='$321'/>")
			_T("</Grid></StackPanel></Border>"));
		
		
		AddListItem(_T("<Border BorderThickness='2' BorderBrush='Orange' Margin='2' Padding='3'><StackPanel Orientation='Horizontal'>")
			_T("<Image Source='10'/>")
			_T("<Grid><Grid.ColumnDefinitions><ColumnDefinition Width='Auto'/><ColumnDefinition Width='*'/></Grid.ColumnDefinitions>")
			_T("<Grid.RowDefinitions><RowDefinition/><RowDefinition/></Grid.RowDefinitions>")
			_T("<TextBlock TextAlignment='Right' FontWeight='Bold' Foreground='Navy' Text='Description:'/>")
			_T("<TextBlock TextAlignment='Right' Grid.Row='1' FontWeight='Bold' Foreground='Navy' Text='Current Price:'/>")
			_T("<TextBlock Margin='6, 0, 0, 0' Grid.Column='1' Text='Snowboard and bindings'/>")
			_T("<TextBlock Margin='6, 0, 0, 0'  Grid.Column='1' Grid.Row='1'  Text='$150'/>")
			_T("</Grid></StackPanel></Border>"));
		
		AddListItem(_T("<Border BorderThickness='2' BorderBrush='Orange' Margin='2' Padding='3'><StackPanel Orientation='Horizontal'>")
			_T("<Image Source='10'/>")
			_T("<Grid><Grid.ColumnDefinitions><ColumnDefinition Width='Auto'/><ColumnDefinition Width='*'/></Grid.ColumnDefinitions>")
			_T("<Grid.RowDefinitions><RowDefinition/><RowDefinition/></Grid.RowDefinitions>")
			_T("<TextBlock TextAlignment='Right' FontWeight='Bold' Foreground='Navy' Text='Description:'/>")
			_T("<TextBlock TextAlignment='Right' Grid.Row='1' FontWeight='Bold' Foreground='Navy' Text='Current Price:'/>")
			_T("<TextBlock Margin='6, 0, 0, 0' Grid.Column='1' Text='Inside C#, first edition'/>")
			_T("<TextBlock Margin='6, 0, 0, 0'  Grid.Column='1' Grid.Row='1'  Text='$15'/>")
			_T("</Grid></StackPanel></Border>"));

	}
	if (m_wndTabControl.GetCurSel() == 1)
	{
		AddListItem(_T("<TextBlock Padding='2, 0, 2, 0'>Inbox</TextBlock>"));
		AddListItem(_T("<TextBlock Padding='2, 0, 2, 0'><Bold>Unread Mail</Bold> <Run Foreground='Blue'>(4730)</Run></TextBlock>"));
		AddListItem(_T("<TextBlock Padding='2, 0, 2, 0'><Bold>For Follow Up</Bold> <Run Foreground='Green'>[21]</Run></TextBlock>"));
		AddListItem(_T("<TextBlock Padding='2, 0, 2, 0'>Sent Items</TextBlock>"));
		AddListItem(_T("<TextBlock Padding='2, 0, 2, 0' TextWrapping='Wrap'><Bold FontSize='15'>W</Bold>e have been using the Xtreme Toolkit for a very short while in our company and already now the investment has paid for itself in terms of productivity gain. We have been down the road of using various non-commercial packages but time is quickly wasted on patching up these 'semi-products' for stability...Thank you for a great product!</TextBlock>"));
		AddListItem(_T("<Border Padding='2, 0, 2, 0' Background='Gold'><TextBlock TextAlignment='Center'>Centered Text</TextBlock></Border>"));
		AddListItem(_T("<TextBlock Padding='2, 0, 2, 0' TextWrapping='Wrap'><Underline>Some Text <Image Source='pen'/> Some another text</Underline></TextBlock>"));
		AddListItem(_T("<StackPanel Orientation='Horizontal' Margin='2'><StackPanel><Border Width='6' Height='6' Background='Red'/><Border Width='6' Height='6' Background='Green'/><Border Width='6' Height='6' Background='Blue'/></StackPanel><TextBlock Margin='2' VerticalAlignment='Center'>Stack Panel</TextBlock></StackPanel>"));
		AddListItem(_T("<Grid><Grid.ColumnDefinitions><ColumnDefinition MinWidth='30'/><ColumnDefinition MinWidth='100'/></Grid.ColumnDefinitions><Grid.RowDefinitions><RowDefinition Height='Auto'/><RowDefinition Height='Auto'/></Grid.RowDefinitions><Border Margin='1' BorderThickness='1' BorderBrush='Red'><TextBlock Foreground='Red'>Grid Text Column 1, Row 1</TextBlock></Border>")
			_T("<Border Margin='1' BorderThickness='1' Grid.Row='1' BorderBrush='Green'><TextBlock Foreground='Green'>Grid Text Column 1, Row 2</TextBlock></Border><Border Margin='1' BorderThickness='1' Grid.Column='1' Grid.Row='0' BorderBrush='Blue'><TextBlock Foreground='Blue'>Grid Text Column 2, Row 1</TextBlock></Border><Border Margin='1' BorderThickness='1' BorderBrush='Gold' Grid.Column='1' Grid.Row='1'><TextBlock Foreground='Gold'>Grid Text Column 2, Row 2</TextBlock></Border></Grid>"));
	}
};

BOOL CMarkupSampleDlg::OnEraseBkgnd(CDC* pDC) 
{
	BOOL bResult = CXTResizeDialog::OnEraseBkgnd(pDC);

#if 0
	CXTPMarkupContext* pContext = XTPMarkupCreateContext();
	CXTPMarkupUIElement* pElement = XTPMarkupParseText(pContext, _T("<TextBlock VerticalAlignment='Bottom'><Bold><Run Foreground='Blue'>Codejock</Run>Software</Bold></TextBlock>"));
	
	XTPMarkupRenderElement(pElement, pDC->GetSafeHdc(), CXTPClientRect(this));
	
	XTPMarkupReleaseElement(pElement);
	XTPMarkupReleaseContext(pContext);
#endif
	return bResult;
}

void CMarkupSampleDlg::OnMoreTaskdialog() 
{
	CXTPTaskDialog td;

	td.SetMainInstruction(_T("<TextBlock>Main <Italic ToolTip='Instruction'>Instruction</Italic></TextBlock>"));
	td.SetContent(_T("<TextBlock><Run>Content</Run> <Bold>Contet</Bold> <Run Foreground='Red'>Content</Run> <Hyperlink Tag='DoNothing' ToolTip='This is Link'>Link</Hyperlink></TextBlock>"));	
	td.EnableMarkup();

	td.DoModal();
}
