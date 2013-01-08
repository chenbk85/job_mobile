// XPThemeDemoGrid.cpp: implementation of the CXPThemeDemoGrid class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "tool_Grid.h"
#include "XPThemeDemoGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CXPThemeDemoGrid,CUGCtrl)
	//{{AFX_MSG_MAP(CXPThemeDemoGrid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXPThemeDemoGrid::CXPThemeDemoGrid()
{

}

CXPThemeDemoGrid::~CXPThemeDemoGrid()
{

}



/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnDrawFocusRect(CDC *dc,RECT *rect){

	CUGCtrl::OnDrawFocusRect(dc,rect);
	return;

	CPen pen;
	rect->right -=2;
	rect->bottom -=2;
	pen.CreatePen(PS_DOT,1,RGB(10,10,10));
	CPen* oldPen = dc->SelectObject(&pen);
	dc->MoveTo(rect->left,rect->top);
	dc->LineTo(rect->right,rect->top);
	dc->LineTo(rect->right,rect->bottom);
	dc->LineTo(rect->left,rect->bottom);
	dc->LineTo(rect->left,rect->top);
	dc->SelectObject(oldPen);
	//this->DrawExcelFocusRect(dc,rect);
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnCellTypeNotify(long ID,int col,long row,long msg,long param){

	if(ID == UGCT_DROPLIST){
		return OnDropList(ID, col, row, msg, param);
	}
	if(ID == UGCT_CHECKBOX){
		return OnCheckbox(ID, col, row, msg, param);
	}
	if(ID == m_nRadioIndex){
	}
	if(ID == m_nDateTimeIndex){
		return OnDateTime(ID, col, row, msg, param);		
	}
	if(ID == m_nButtonIndex){
		return OnPushButton( ID, col, row, msg, param);
	}
	if(ID == m_nEllipsisIndex){
		return OnEllipsisButton( ID, col, row, msg, param);
	}
	if(ID == m_nSpinIndex){
		return OnSpinButton( ID, col, row, msg, param);
	}
	if(ID == m_nSliderIndex){
		return OnSlider( ID, col, row, msg, param);
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnDropList(long ID,int col,long row,long msg,LONG_PTR param){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == DROPLIST_DYNAMIC_LOAD){
		if(msg == UGCT_DROPLISTSTART){		
			CStringList* pList = (CStringList*)param;
			CString string;
			pList->AddTail(_T("Rnd # of Items"));
			srand(GetTickCount());
			int len = rand()%20 + 1;
			for(int loop = 0 ;loop < len;loop++){
				string.Format(_T("Dyn Item %d"),loop);
				pList->AddTail(string);
			}
		}
	}
	if(nParam == DROPLIST_DYNAMIC_LOAD2){
		if(msg == UGCT_DROPLISTSTART){
			CStringList* pList = (CStringList*)param;
			CString string = cell.GetText();
			if(string != _T("Red"))
				pList->AddTail(_T("Red"));
			if(string != _T("Green"))
				pList->AddTail(_T("Green"));
			if(string != _T("Blue"))
				pList->AddTail(_T("Blue"));
		}
	}
	if(nParam == DROPLIST_CHANGE_SELECTION){
		if(msg == UGCT_DROPLISTSELECT){
			CString * pString = (CString*) param;
			if(*pString ==_T("1"))
				*pString = _T("One");
			if(*pString ==_T("2"))
				*pString = _T("Two");
			if(*pString ==_T("3"))
				*pString = _T("Three");
		}
	}
	if(nParam == DROPLIST_CHANGE_SELECTION2){
	
		LPCTSTR pszLongStateNames[] = {_T("ALABAMA"),_T("ALASKA"),_T("ARIZONA"),_T("ARKANSAS"),_T("CALIFORNIA"),
			_T("COLORADO"),_T("CONNECTICUT"),_T("DELAWARE"),_T("DISTRICT OF COLUMBIA"),_T("FLORIDA"),
			_T("GEORGIA"),_T("GUAM"),_T("HAWAII"),_T("IDAHO"),_T("ILLINOIS"),_T("INDIANA"),_T("IOWA"),_T("KANSAS"),
			_T("KENTUCKY"),_T("LOUISIANA"),_T("MAINE"),_T("MARSHALL ISLANDS"),_T("MARYLAND"),_T("MASSACHUSETTS"),
			_T("MICHIGAN"),_T("MINNESOTA"),_T("MISSISSIPPI"),_T("MISSOURI"),_T("MONTANA"),_T("NEBRASKA"),
			_T("NEVADA"),_T("NEW HAMPSHIRE"),_T("NEW JERSEY"),_T("NEW MEXICO"),_T("NEW YORK"),_T("NORTH CAROLINA"),
			_T("NORTH DAKOTA"),_T("NORTHERN MARIANA ISLANDS"),_T("OHIO"),_T("OKLAHOMA"),_T("OREGON"),
			_T("PALAU"),_T("PENNSYLVANIA"),_T("PUERTO RICO"),_T("RHODE ISLAND"),_T("SOUTH CAROLINA"),
			_T("SOUTH DAKOTA"),_T("TENNESSEE"),_T("TEXAS"),_T("UTAH"),_T("VERMONT"),_T("VIRGIN ISLANDS"),
			_T("VIRGINIA"),_T("WASHINGTON"),_T("WEST VIRGINIA"),_T("WISCONSIN"),_T("WYOMING")};
		LPCTSTR pszShortStateNames[] = {_T("AL"),_T("AK"),_T("AZ"),_T("AR"),_T("CA"),_T("CO"),_T("CT"),_T("DE"),_T("DC"),_T("FL"),
			_T("GA"),_T("GU"),_T("HI"),_T("ID"),_T("IL"),_T("IN"),_T("IA"),_T("KS"),_T("KY"),_T("LA"),_T("ME"),_T("MH"),_T("MD"),_T("MA"),_T("MI"),
			_T("MN"),_T("MS"),_T("MO"),_T("MT"),_T("NE"),_T("NV"),_T("NH"),_T("NJ"),_T("NM"),_T("NY"),_T("NC"),_T("ND"),_T("MP"),_T("OH"),_T("OK"),
			_T("OR"),_T("PW"),_T("PA"),_T("PR"),_T("RI"),_T("SC"),_T("SD"),_T("TN"),_T("TX"),_T("UT"),_T("VT"),_T("VI"),_T("VA"),_T("WA"),_T("WV"),
			_T("WI"),_T("WY")};

		if(msg == UGCT_DROPLISTSTART){		
			CStringList* pList = (CStringList*)param;
			int len = sizeof(pszLongStateNames) / sizeof(LPCTSTR);
			for(int loop = 0 ;loop < len;loop++){
				pList->AddTail(pszLongStateNames[loop]);
			}
		}
		if(msg == UGCT_DROPLISTSELECT){
			CString * pString = (CString*) param;
			int len = sizeof(pszLongStateNames) / sizeof(LPCTSTR);
			for(int loop = 0 ;loop < len;loop++){
				if(*pString == pszLongStateNames[loop]){
					*pString = pszShortStateNames[loop];
				}
			}
		}
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnCheckbox(long ID,int col,long row,long msg,long param){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == CHECKBOX_CHANGEFONT){
		if(cell.GetFont() == &m_medFont){
			cell.SetFont(&m_defFont);
			cell.SetTextColor(RGB(255,0,0));
		}
		else{
			cell.SetFont(&m_medFont);
			cell.SetTextColor(RGB(0,255,0));
		}
		SetCell(col,row,&cell);
		RedrawCell(col,row);
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnDateTime(long ID,int col,long row,long msg,LONG_PTR param){

	if(col == 5 && row == DATETIME_ROW+3){
		if(msg == UGCT_DISPLAYMONTHCAL){
			UGCTMONTHCALSETTINGS* pmcs = (UGCTMONTHCALSETTINGS*)param;

			pmcs->szDimension.cx = 2;
			pmcs->szDimension.cy = 2;
		}
		if(msg == UGCT_CONVERTDATE){
			UGCTCONVERTDATE* cd = (UGCTCONVERTDATE*)param;
			cd->string = cd->date.Format(_T("%b %d, %y"));
		}
	}
	if(col == 5 && row == DATETIME_ROW+2){
		if(msg == UGCT_DISPLAYMONTHCAL){
			UGCTMONTHCALSETTINGS* pmcs = (UGCTMONTHCALSETTINGS*)param;

			pmcs->clrMonthBk = RGB(250,250,200);
			pmcs->clrTitleBk = RGB(220,220,180);
		}
	}
	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnPushButton(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(msg == UGCT_BUTTONCLICK){
		if(nParam == BUTTON_CLICK1){
			WinExec("calc.exe",SW_SHOW);
		}
		else if(nParam == BUTTON_CLICK2){
			WinExec("notepad.exe",SW_SHOW);
		}

		else{
			MessageBox(_T("The button was clicked"),_T("Cell Type Notification"));
		}
	}
	if(msg == UGCT_BUTTONDOWN){
		if(nParam == BUTTON_CLICK3){
			MessageBox(_T("The button pressed"),_T("Cell Type Notification"));
		}
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnEllipsisButton(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(msg == UGCT_ELLIPSISBUTTONCLICK){
		if(nParam == ELLIPSISBUTTON_CLICK1){
			WinExec("calc.exe",SW_SHOW);
		}
		else if(nParam == ELLIPSISBUTTON_CLICK2){
			WinExec("notepad.exe",SW_SHOW);
		}

		else{
			MessageBox(_T("The button was clicked"),_T("Cell Type Notification"));
		}
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnSpinButton(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == SPIN_TYPE1){
		long num;
		cell.GetNumber(&num);

		if(msg == UGCT_SPINBUTTONUP){
			num++;
			if(num > 10)
				num = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			num--;
			if(num < 0)
				num = 10;
		}
		CString str;
		str.Format(_T("%ld"),num);
		cell.SetText(str);
		SetCell(col,row,&cell);
	}
	else if(nParam == SPIN_TYPE2 || nParam == CELLTYPE_IS_EDITABLE){
		LPCTSTR szVals[] = {_T("One"),_T("Two"),_T("Three"),_T("Four"),_T("Five"),_T("Six"),_T("Seven"),_T("Eight"),_T("Nine"),_T("Ten")};

		CString str = cell.GetText();
		int len = (sizeof(szVals) / sizeof(LPCTSTR));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(str == szVals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetText(szVals[index]);
		SetCell(col,row,&cell);
	}

	else if(nParam == SPIN_TYPE3){

		LPCTSTR szVals[] = {_T("Mr"),_T("Mrs"),_T("Ms"),_T("Miss"),_T("Dr")};

		CString str = cell.GetText();
		int len = (sizeof(szVals) / sizeof(LPCTSTR));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(str == szVals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetText(szVals[index]);
		SetCell(col,row,&cell);
	}
	else if(nParam == SPIN_TYPE4){

		COLORREF vals[] = {(RGB(255,0,0)),(RGB(255,255,0)),(RGB(0,255,0)),
			(RGB(0,255,255)),(RGB(0,0,255))	};

		COLORREF color = cell.GetBackColor();

		int len = (sizeof(vals) / sizeof(COLORREF));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(color == vals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetBackColor(vals[index]);
		SetCell(col,row,&cell);
	}
	else if(nParam == SPIN_TYPE5){

		LPCTSTR szVals[] = {_T("A Long Piece of Text"),
			_T("Another Piece of Text"),
			_T("Even More Text"),
			_T("This is the End")};

		CString str = cell.GetText();
		int len = (sizeof(szVals) / sizeof(LPCTSTR));
		int index = 0;

		for(int loop = 0; loop < len ; loop++){
			if(str == szVals[loop]){
				index = loop;
				break;
			}
		}

		if(msg == UGCT_SPINBUTTONUP){
			index++;
			if(index >= len)
				index = 0;
		}
		if(msg == UGCT_SPINBUTTONDOWN){
			index--;
			if(index < 0)
				index = len - 1;
		}
		cell.SetText(szVals[index]);
		SetCell(col,row,&cell);

	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnSlider(long ID,int col,long row,long msg,long param){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();

	if(nParam == SLIDER_TYPE1){
		QuickSetText(col,row+1,cell.GetText());
		RedrawCell(col,row+1);
	}
	else if(nParam == SLIDER_TYPE2){
		float fVal = 255 - (float)param * (float)2.55;
		cell.SetBackColor(RGB(255,fVal,fVal));
		SetCell(col,row,&cell);

		fVal = 255 - fVal;

		GetCell(col+1,row+1,&cell);
		COLORREF color = cell.GetBackColor();
		cell.SetBackColor(RGB(fVal,GetGValue(color),GetBValue(color)));
		SetCell(col+1,row+1,&cell);
		RedrawCell(col+1,row+1);
	}
	else if(nParam == SLIDER_TYPE3){
		float fVal = 255 - (float)param * (float)2.55;
		cell.SetBackColor(RGB(fVal,255,fVal));
		SetCell(col,row,&cell);

		fVal = 255 - fVal;

		GetCell(col,row+1,&cell);
		COLORREF color = cell.GetBackColor();
		cell.SetBackColor(RGB(GetRValue(color),fVal,GetBValue(color)));
		SetCell(col,row+1,&cell);
		RedrawCell(col,row+1);
	}
	else if(nParam == SLIDER_TYPE4){
		float fVal = 255 - (float)param * (float)2.55;
		cell.SetBackColor(RGB(fVal,fVal,255));
		SetCell(col,row,&cell);

		fVal = 255 - fVal;

		GetCell(col-1,row+1,&cell);
		COLORREF color = cell.GetBackColor();
		cell.SetBackColor(RGB(GetRValue(color),GetGValue(color),fVal));
		SetCell(col-1,row+1,&cell);
		RedrawCell(col-1,row+1);
	}

	return TRUE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow){
	return FALSE;
}

/***************************************************
****************************************************/
int CXPThemeDemoGrid::OnEditFinish(int col, long row,CWnd* edit,LPCTSTR string,BOOL cancelFlag){

	CUGCell cell;
	GetCell(GetCurrentCol(),GetCurrentRow(),&cell);
	int nCellTypeIndex = cell.GetCellType();

	if(nCellTypeIndex == m_nDateTimeIndex){
		if(cancelFlag)
			return TRUE;
		COleDateTime date;
		return date.ParseDateTime(string,VAR_DATEVALUEONLY);
	}

	if(nCellTypeIndex == m_nPieChartIndex){
		InvalidateRect(NULL,FALSE);
	}

	return TRUE;
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCharDown(UINT *vcKey,BOOL processed){

	CUGCell cell;
	GetCell(GetCurrentCol(),GetCurrentRow(),&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();

	if(nParam == CELLTYPE_IS_EDITABLE || string == _T("CELLTYPE_IS_EDITABLE")){
		StartEdit(*vcKey);
	}

}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnGetCell(int col,long row,CUGCell *cell){

}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();

	if(nCellTypeIndex == m_nProgressIndex || nCellTypeIndex == m_nAdvProressIndex1 
		|| nCellTypeIndex == m_nAdvProressIndex2 || nCellTypeIndex == m_nAdvProressIndex3){
		long val;
		cell.GetNumber(&val);
		val +=cell.GetParam();
		if(val > 100)
			val = 0;
		cell.SetNumber(val);
		SetCell(col,row,&cell);
		RedrawCell(col,row);
	}
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();

	if(nCellTypeIndex == m_nProgressIndex || nCellTypeIndex == m_nAdvProressIndex1 
		|| nCellTypeIndex == m_nAdvProressIndex2 || nCellTypeIndex == m_nAdvProressIndex3){
		long val;
		cell.GetNumber(&val);
		val -=cell.GetParam();;
		if(val < 0)
			val = 100;
		cell.SetNumber(val);
		SetCell(col,row,&cell);
		RedrawCell(col,row);
	}
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
	
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	CString string;
	if(cell.GetLabelText() != NULL)
		string = cell.GetLabelText();

	if(processed){
		if(cell.GetCellType() == m_nSpinIndex)
			return ;
	}

	if(nParam == CELLTYPE_IS_EDITABLE || string == _T("CELLTYPE_IS_EDITABLE")){
		StartEdit();
	}
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
	
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){

}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed){
}

/***************************************************
****************************************************/
void CXPThemeDemoGrid::SetupSection(long row, LPCTSTR title){

	CUGCell cell;

	cell.SetBackColor(RGB(240,240,240));
	cell.SetTextColor(RGB(0,0,128));
	cell.SetFont(&m_boldFont);
	cell.SetAlignment(UG_ALIGNVCENTER);
	QuickSetRange(0,row,GetNumberCols() - 1,row,&cell);

	QuickSetText(-1,row,title);
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuCommand
//		This notification is called when the user has selected a menu item
//		in the pop-up menu.
//	Params:
//		col, row - the cell coordinates of where the menu originated from
//		setcion - identify for which portion of the gird the menu is for.
//				  possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//		item - ID of the menu item selected
//	Return:
//		<none>
void CXPThemeDemoGrid::OnMenuCommand(int col,long row,int section,int item)
{
//	CUGExcel::OnMenuCommand( col, row, section, item );
	// Translate column location
	col = GetColTranslation( col );

	CUGCell cell;
	GetCell(col, row, &cell);

	int type = cell.GetCellType();

    CUGCellType * cellType = GetCellType(type);
	switch(item)
	{
	case MSG_USE_THEMES:
		cellType->ResetThemes();
		cell.UseThemes(true);
		break;
	case MSG_USE_THEMES_ALL:
		cellType->UseThemes(true);
		break;
	case MSG_DONT_USE_THEMES:
		cellType->ResetThemes();
		cell.UseThemes(false);
		break;
	case MSG_DONT_USE_THEMES_ALL:
		cellType->UseThemes(false);
		break;
	}

	SetCell(col, row, &cell);

	Invalidate();
}

/////////////////////////////////////////////////////////////////////////////
//	OnMenuStart
//		Is called when the pop up menu is about to be shown
//	Params:
//		col, row	- the cell coordinates of where the menu originated from
//		setcion		- identify for which portion of the gird the menu is for.
//					possible sections:
//						UG_TOPHEADING, UG_SIDEHEADING,UG_GRID
//						UG_HSCROLL  UG_VSCROLL  UG_CORNERBUTTON
//	Return:
//		TRUE - to allow menu to show
//		FALSE - to prevent the menu from poping up
int CXPThemeDemoGrid::OnMenuStart(int col,long row,int section)
{
	// TODO: add your notification handling here
	UNREFERENCED_PARAMETER(row);

	int retVal = 1;
	// Translate column location
	col = GetColTranslation( col );

	CUGCell cell;
	GetCell(col, row, &cell);

	int type = cell.GetCellType();

	if (type == m_nProgressIndex || type == m_nAdvProressIndex1 || type == m_nAdvProressIndex2 || type == m_nAdvProressIndex3)
	{
		retVal = 0;
	}
	else
	{
		col = GetColTranslation( col );

		EmptyMenu();

		AddMenuItem( MSG_USE_THEMES, _T("Use themes for this cell") );
		AddMenuItem( MSG_DONT_USE_THEMES, _T("Don't use themes for this cell") );
		AddMenuItem( MSG_USE_THEMES_ALL, _T("Use themes for this cell type") );
		AddMenuItem( MSG_DONT_USE_THEMES_ALL, _T("Don't use themes for this cell type") );
	}

	return retVal;
}

void CXPThemeDemoGrid::setup_Font()
{
	m_defFont.CreateFont( 14, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );
	m_boldFont.CreateFont( 14, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_smFont.CreateFont( 10, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Arial" ) );	
	m_medFont.CreateFont( 16, 0, 0, 0, 500, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_medBoldFont.CreateFont( 16, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, _T( "MS Sans Serif" ) );
	m_lrgFont.CreateFont( 20, 0, 0, 0, 600, 0, 0, 0, 0, 0, 0, 0, 0, _T( "Times New Roman" ) );	
	SetDefFont( &m_defFont );
}

void CXPThemeDemoGrid::setup_Grid_WH()
{
	CUGCell cell;
	SetSH_Width( 105 );

	SetDoubleBufferMode(TRUE);
	this->SetUserSizingMode(2);

	GetHeadingDefault(&cell);
	cell.SetFont(&m_medBoldFont);
	SetHeadingDefault(&cell);

	SetColWidth(0,30);
}