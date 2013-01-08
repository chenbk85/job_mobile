#include "stdafx.h"
#include "resource.h"
#include "tool_Grid.h"
#include "XPThemeDemoGrid.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



/***************************************************
OnSetup
This function is called just after the grid window 
is created or attached to a dialog item.
It can be used to initially setup the grid
****************************************************/

void CXPThemeDemoGrid::OnSetup()
{


	CUGCell cell;
	//setup the fonts
	setup_Font();

	//setup the bitmaps
	//	m_noteBitmap.LoadBitmap(MAKEINTRESOURCE(IDB_NOTEBITMAP));
	//	m_folderBitmap.LoadBitmap(MAKEINTRESOURCE(IDB_FOLDERBITMAP));

	SetNumberCols( NUM_COLS );

	SetNumberRows( NUM_ROWS );

	//setup the grid widths and heights
	setup_Grid_WH();

	this->SetVScrollMode(UG_SCROLLTRACKING);

	CUGEdit* editClass = (CUGEdit*)this->GetEditClass();
	editClass->SetAutoSize(FALSE);


	//SETUP ALL OF THE CELL TYPES
	Setup_CellType();
	
#if 1

	setup_STANDARD(STANDARD_ROW);
	setup_DROPLIST(DROPLIST_ROW);
	setup_CHECKBOX(CHECKBOX_ROW);
	setup_RADIOBTN_ROW(RADIOBTN_ROW);
	setup_DATE_TIME(DATETIME_ROW);
	setup_PUSH_BUTTON(PUSHBTN_ROW);
	setup_ELLIPSIS_ROW(ELLIPSIS_ROW);
	setup_SPINBTN_ROW(SPINBTN_ROW);
	setup_SLIDERS_ROW(SLIDERS_ROW);
	setup_ARROWS_ROW(ARROWS_ROW);
	setup_SORTARROW_ROW(SORTARROW_ROW);
	setup_PROGRESS_ROW(PROGRESS_ROW);

	//MULTI-FONT ====================================================
	//	<:F,name,size,[weight]>
	//	<:C,r,g,b>
	setup_MULTIFONT_ROW(MULTIFONT_ROW);

	setup_AUTOFONT_ROW(AUTOFONT_ROW);
	setup_NOTE_ROW(NOTE_ROW);
	setup_LABELED_ROW(LABELED_ROW);
	setup_MARQUEE_ROW(MARQUEE_ROW);
	setup_PIECHART_ROW(PIECHART_ROW);

#else
	setup_STANDARD(STANDARD_ROW);
#endif

	SetMultiSelectMode(TRUE);
	EnableMenu( TRUE );

	//SetNumberRows( NUM_ROWS+300 );

}

void CXPThemeDemoGrid::Setup_CellType()
{
	CUGCell cell;

	//Radio button cell type
	m_nRadioIndex = AddCellType(&m_radio);
	//Date Time Picker cell type
	m_nDateTimeIndex = AddCellType(&m_dateTime);
	//Push Button cell type
	m_nButtonIndex = AddCellType(&m_button);
	//Ellipsis Button cell type
	m_nEllipsisIndex = AddCellType(&m_ellipsis);
	//Spin Button cell type
	m_nSpinIndex = AddCellType(&m_spin);
	//Slider cell type
	m_nSliderIndex = AddCellType(&m_slider);
	//Sort Arrow cell type
	m_nSortArrowIndex = AddCellType(&m_sortArrow);
	//Progress bar cell types
	m_nProgressIndex = AddCellType(&m_progress);
	m_nAdvProressIndex1 = AddCellType(&m_advProress1);
	m_nAdvProressIndex2 = AddCellType(&m_advProress2);
	m_nAdvProressIndex3 = AddCellType(&m_advProress3);
	//Multi-font cell type
	m_nMultiFontIndex = AddCellType(&m_multiFont);
	//Auto-font cell type
	m_nAutoFontIndex = AddCellType(&m_autoFont);
	//Note cell type
	m_nNoteIndex = AddCellType(&m_note);
	//Labeled cell type
	m_nLabeledIndex = AddCellType(&m_labeled);
	//Marquee cell type
	m_nMarqueeIndex = AddCellType(&m_marquee);
	//Pie Chart cell type
	m_nPieChartIndex = AddCellType(&m_pieChart);
}

int CXPThemeDemoGrid::setup_STANDARD( int row)
{
	CUGCell cell;
	SetupSection(row, _T("Standard"));
	SetRowHeight(row+1,10);
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,4,row);

	SetRowHeight(row+2,30);
	QuickSetText(1,row+2, _T("Text"));
	QuickSetText(2,row+2,_T("Text"));
	QuickSetTextColor(2,row+2,RGB(255,0,0));
	QuickSetText(3,row+2,_T("Left"));
	QuickSetText(4,row+2,_T("Left Bottom"));
	QuickSetAlignment(4,row+2,UG_ALIGNCENTER|UG_ALIGNBOTTOM);


	SetRowHeight(row+3,30);
	QuickSetText(1,row+3,_T("Text"));
	QuickSetFont(1,row+3,&m_medFont);
	QuickSetText(2,row+3,_T("Text"));
	QuickSetTextColor(2,row+3,RGB(0,255,0));
	QuickSetText(3,row+3,_T("Center"));
	QuickSetAlignment(3,row+3,UG_ALIGNCENTER);
	QuickSetText(4,row+3,_T("Center"));
	QuickSetAlignment(4,row+3,UG_ALIGNCENTER|UG_ALIGNVCENTER);



	SetRowHeight(row+4,30);
	QuickSetText(1,row+4,_T("Text"));
	QuickSetFont(1,row+4,&m_lrgFont);
	QuickSetText(2,row+4,_T("Text"));
	QuickSetBackColor(2,row+4,RGB(0,0,255));
	QuickSetText(3,row+4,_T("Right"));
	QuickSetAlignment(3,row+4,UG_ALIGNRIGHT);
	QuickSetText(4,row+4,_T("Right Center"));
	QuickSetAlignment(4,row+4,UG_ALIGNRIGHT|UG_ALIGNVCENTER);


	//cell.ClearAll();
	//cell.SetParam(CELLTYPE_IS_EDITABLE);
	//QuickSetRange(1,row+2,8,row+5,&cell);

	//default
	QuickSetText(1,row+5,_T("Fully Supports Cell Overlapping"));

	GetCell(1,row+6,&cell);
	cell.SetText(_T("Full bitmap support"));
	//		cell.SetBitmap(&m_folderBitmap);
	SetCell(1,row+6,&cell);
	JoinCells(1,row+6,2,row+6);
	QuickSetText(3,row+6,_T(" "));


	//multi-line
	QuickSetText(6,row,_T("Multi-line"));
	QuickSetCellTypeEx(6,row+2,UGCT_NORMALMULTILINE);
	QuickSetText(6,row+2,_T("Fully Supports\nMulti-line Text"));
	QuickSetCellTypeEx(6,row+3,UGCT_NORMALMULTILINE);
	QuickSetAlignment(6,row+3,UG_ALIGNCENTER);
	QuickSetText(6,row+3,_T("Multi\nline"));
	QuickSetCellTypeEx(6,row+4,UGCT_NORMALMULTILINE);
	QuickSetAlignment(6,row+4,UG_ALIGNRIGHT);
	QuickSetText(6,row+4,_T("Multi\nline"));

	//ellipsis
	QuickSetText(8,row,_T("Ellipsis"));
	QuickSetCellTypeEx(8,row+2,UGCT_NORMALELLIPSIS);
	QuickSetText(8,row+2,_T("Shows Ellipsis if text is too long"));
	QuickSetAlignment(8,row+2,UG_ALIGNTOP);

	QuickSetCellTypeEx(8,row+3,UGCT_NORMALELLIPSIS);
	QuickSetFont(8,row+3,&m_medFont);
	QuickSetText(8,row+3,_T("Shows Ellipsis if text is too long"));
	QuickSetAlignment(8,row+3,UG_ALIGNVCENTER);

	QuickSetCellTypeEx(8,row+4,UGCT_NORMALELLIPSIS);
	QuickSetFont(8,row+4,&m_lrgFont);
	QuickSetText(8,row+4,_T("Shows Ellipsis if text is too long"));
	QuickSetAlignment(8,row+4,UG_ALIGNBOTTOM);	return row;
}

void CXPThemeDemoGrid::setup_DROPLIST( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Droplist"));
	SetRowHeight(row+1,10);
	SetRowHeight(row+5,24);

	//default
	QuickSetText(1,row,_T("Basic"));
	cell.ClearAll();
	cell.SetCellType(UGCT_DROPLIST);
	QuickSetRange(1,row+2,1,row+5,&cell);

	QuickSetLabelText(1,row+2,_T("One\nTwo\nThree\n"));
	QuickSetText(1,row+2,_T("One"));
	QuickSetAlignment(1,row+3,UG_ALIGNCENTER|UG_ALIGNVCENTER);
	QuickSetLabelText(1,row+3,_T("One\nTwo\nThree\nFour\nFive\nSix\nSeven\nEight\nNine\nTen\nElevn\nTwelve\nThirteen\nFourteen\nFifteen\nSixteen\nSeventeen\nEighteen\nNineteen\nTwenty\n"));
	QuickSetText(1,row+3,_T("Two"));
	QuickSetFont(1,row+4,&m_medFont);
	QuickSetAlignment(1,row+4,UG_ALIGNRIGHT);
	QuickSetLabelText(1,row+4,_T("One\nTwo\nThree\nFour\nFive\n"));
	QuickSetText(1,row+4,_T("Three"));

	QuickSetLabelText(1,row+5,_T("Image\nBitmap\nGraphic\n"));
	QuickSetText(1,row+5,_T("Image"));
	//		QuickSetBitmap(1,row+5,&m_noteBitmap);

	//hide button
	QuickSetText(3,row,_T("Hide"));
	cell.ClearAll();
	cell.SetCellType(UGCT_DROPLIST);
	cell.SetCellTypeEx(UGCT_DROPLISTHIDEBUTTON);	
	QuickSetRange(3,row+2,3,row+4,&cell);

	QuickSetLabelText(3,row+2,_T("One\nTwo\nThree\n"));
	QuickSetText(3,row+2,_T("One"));
	QuickSetBackColor(3,row+3,RGB(0,255,0));
	QuickSetLabelText(3,row+3,_T("One\nTwo\nThree\nFour\nFive\nSix\nSeven\nEight\nNine\nTen\nElevn\nTwelve\nThirteen\nFourteen\nFifteen\nSixteen\nSeventeen\nEighteen\nNineteen\nTwenty\n"));
	QuickSetText(3,row+3,_T("Two"));
	QuickSetTextColor(3,row+4,RGB(255,0,0));
	QuickSetLabelText(3,row+4,_T("One\nTwo\nThree\nFour\nFive\n"));
	QuickSetText(3,row+4,_T("Three"));

	//dynamic load
	QuickSetText(5,row,_T("Dynamic"));

	GetCell(5,row+2,&cell);
	cell.SetParam(DROPLIST_DYNAMIC_LOAD);
	cell.SetCellType(UGCT_DROPLIST);
	SetCell(5,row+2,&cell);

	GetCell(5,row+3,&cell);
	cell.SetParam(DROPLIST_DYNAMIC_LOAD2);
	cell.SetCellType(UGCT_DROPLIST);
	cell.SetText(_T("Red"));
	SetCell(5,row+3,&cell);

	//change
	QuickSetText(7,row,_T("Change"));

	GetCell(7,row+2,&cell);
	cell.SetParam(DROPLIST_CHANGE_SELECTION);
	cell.SetCellType(UGCT_DROPLIST);
	cell.SetLabelText(_T("1\n2\n3\n"));
	cell.SetText(_T("One"));
	SetCell(7,row+2,&cell);

	GetCell(7,row+3,&cell);
	cell.SetParam(DROPLIST_CHANGE_SELECTION2);
	cell.SetCellType(UGCT_DROPLIST);
	cell.SetText(_T("<state>"));
	SetCell(7,row+3,&cell);

	//editable
	QuickSetText(9,row,_T("Editable"));

	GetCell(9,row+2,&cell);
	cell.SetLabelText(_T("One\nTwo\nThree\n"));
	cell.SetText(_T("One"));
	cell.SetCellType(UGCT_DROPLIST);
	cell.SetParam(CELLTYPE_IS_EDITABLE);
	SetCell(9,row+2,&cell);
}

void CXPThemeDemoGrid::setup_CHECKBOX( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Checkbox"));
	SetRowHeight(row+1,10);
	SetRowHeight(row+4,30);
	SetRowHeight(row+7,30);
	SetRowHeight(row+8,30);

	//basic styles
	QuickSetText(1,row,_T("Basic Styles"));
	JoinCells(1,row,4,row);

	row+=2;


	int checkBoxLookFlags[] = {UGCT_CHECKBOXFLAT,UGCT_CHECKBOX3DRECESS,UGCT_CHECKBOX3DRAISED};
	int checkBoxFlags[] = {0,UGCT_NORMALMULTILINE, UGCT_CHECKBOXCHECKMARK,
		UGCT_CHECKBOX3STATE,UGCT_CHECKBOXUSEALIGN,0};
	LPTSTR checkBoxTitles[] = {_T("Normal"),_T("MultiLine"),_T("Checkmark"),_T("Tri-State"),_T("Alignment"),_T("")};
	int checkBoxAlign[] = {UG_ALIGNLEFT,UG_ALIGNCENTER,UG_ALIGNRIGHT};
	int checkBoxAlign2[] = {UG_ALIGNTOP,UG_ALIGNVCENTER,UG_ALIGNBOTTOM};

	QuickSetText(2,row,_T("Flat"));
	QuickSetFont(2,row,&m_boldFont);
	QuickSetText(3,row,_T("3D Recess"));
	QuickSetFont(3,row,&m_boldFont);
	QuickSetText(4,row,_T("3D Raised"));
	QuickSetFont(4,row,&m_boldFont);

	for(int rows = 0; rows< sizeof(checkBoxFlags)/sizeof(int*); rows++){
		QuickSetText(1,row+1+ rows,checkBoxTitles[rows]);
		QuickSetFont(1,row+1+ rows,&m_boldFont);

		for(int cols = 0; cols < sizeof(checkBoxLookFlags)/sizeof(int*); cols++){			
			QuickSetLabelText(cols+2,row+1+ rows,_T("Checkbox"));
			if(rows == 1)
				QuickSetLabelText(cols+2,row+1+ rows,_T("Checkbox\nText"));
			QuickSetCellType(cols+2,row+1+rows,UGCT_CHECKBOX);			
			QuickSetCellTypeEx(cols+2,row+1+rows,
				checkBoxLookFlags[cols]|
				checkBoxFlags[rows]);
			if(rows == 4 || rows == 5){
				QuickSetLabelText(cols+2,row+1+ rows,_T("Text"));
				QuickSetAlignment(cols+2,row+1+rows,checkBoxAlign[cols]|checkBoxAlign2[cols]);
			}
		}
	}

	//More styles
	row -= 2;
	QuickSetText(6,row,_T("More Styles"));
	JoinCells(6,row,7,row);

	QuickSetCellType(6,row+2,UGCT_CHECKBOX);			
	QuickSetCellTypeEx(6,row+2,UGCT_CHECKBOXCHECKMARK|UGCT_CHECKBOX3DRAISED|UGCT_CHECKBOX3STATE);
	QuickSetBackColor(6,row+2,GetSysColor(COLOR_BTNFACE));
	QuickSetLabelText(6,row+2,_T("Checkbox"));

	QuickSetCellType(6,row+3,UGCT_CHECKBOX);			
	QuickSetCellTypeEx(6,row+3,UGCT_CHECKBOX3DRECESS);
	QuickSetFont(6,row+3,&m_medFont);
	QuickSetLabelText(6,row+3,_T("Fonts"));
	QuickSetTextColor(6,row+3,RGB(0,255,0));
	QuickSetAlignment(6,row+3,UG_ALIGNCENTER);
	GetCell(6,row+3,&cell);
	cell.SetParam(CHECKBOX_CHANGEFONT);
	SetCell(6,row+3,&cell);

	GetCell(6,row+4,&cell);
	cell.SetText(_T("1"));
	cell.SetLabelText(_T("A Long Line Of Text"));
	cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
	cell.SetCellType(UGCT_CHECKBOX);
	cell.SetAlignment(UG_ALIGNVCENTER);
	SetCell(6,row+4,&cell);

	GetCell(6,row+4,&cell);
	cell.SetText(_T("1"));
	cell.SetLabelText(_T("Image"));
	cell.SetCellType(UGCT_CHECKBOX);
	//		cell.SetBitmap(&m_folderBitmap);
	SetCell(6,row+4,&cell);
}

void CXPThemeDemoGrid::setup_RADIOBTN_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Radio Button"));
	SetRowHeight(row+1,10);
	SetRowHeight(row+2,48);
	SetRowHeight(row+3,63);

	//Default
	QuickSetText(1,row,_T("Basic"));

	GetCell(1,row+2,&cell);
	cell.SetText(_T("1"));
	cell.SetLabelText(_T("One\nTwo\nThree\n"));
	cell.SetCellType(m_nRadioIndex);
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetText(_T("1"));
	cell.SetAlignment(UG_ALIGNCENTER);
	cell.SetLabelText(_T("Mr.\nMrs.\nMs.\nDr.\n"));
	cell.SetCellType(m_nRadioIndex);
	SetCell(1,row+3,&cell);

	GetCell(2,row+2,&cell);
	cell.SetText(_T("1"));
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetLabelText(_T("Apple\nOrange\n"));
	cell.SetFont(&m_medFont);
	cell.SetCellType(m_nRadioIndex);
	SetCell(2,row+2,&cell);

	GetCell(2,row+3,&cell);
	cell.SetText(_T("1"));
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetLabelText(_T("Toronto\nNew York\nLosAngles\nSeatle\n"));
	cell.SetBackColor(RGB(222,222,222));
	cell.SetTextColor(RGB(0,0,222));
	cell.SetCellType(m_nRadioIndex);
	SetCell(2,row+3,&cell);
}

void CXPThemeDemoGrid::setup_DATE_TIME( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Date Time"));
	SetRowHeight(row+1,10);

	//basic
	QuickSetText(1,row,_T("Basic"));

	GetCell(1,row+2,&cell);
	cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
	cell.SetCellType(m_nDateTimeIndex);
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetCellType(m_nDateTimeIndex);
	SetCell(1,row+3,&cell);


	//Editable
	QuickSetText(3,row,_T("Editable"));

	GetCell(3,row+2,&cell);
	cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
	cell.SetLabelText(_T("CELLTYPE_IS_EDITABLE"));
	cell.SetCellType(m_nDateTimeIndex);
	SetCell(3,row+2,&cell);

	GetCell(3,row+3,&cell);
	cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetLabelText(_T("CELLTYPE_IS_EDITABLE"));
	cell.SetCellType(m_nDateTimeIndex);
	SetCell(3,row+3,&cell);

	//Advanced
	QuickSetText(5,row,_T("Advanced"));

	GetCell(5,row+2,&cell);
	cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
	//cell.SetParam(CELLTYPE_IS_EDITABLE);
	cell.SetCellType(m_nDateTimeIndex);
	cell.SetCellTypeEx(UGCT_DROPLISTHIDEBUTTON);
	SetCell(5,row+2,&cell);

	GetCell(5,row+3,&cell);
	cell.SetText(COleDateTime::GetCurrentTime().Format(VAR_DATEVALUEONLY));
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetCellType(m_nDateTimeIndex);
	SetCell(5,row+3,&cell);
}

int CXPThemeDemoGrid::setup_PUSH_BUTTON( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Push Button"));
	SetRowHeight(row+1,10);
	SetRowHeight(row+3,30);

	//basic
	QuickSetText(1,row,_T("Basic"));

	GetCell(1,row+2,&cell);
	cell.SetText(_T("Button"));
	cell.SetCellType(m_nButtonIndex);
	cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetText(_T("Button"));
	cell.SetCellType(m_nButtonIndex);
	cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS);
	cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
	cell.SetFont(&m_boldFont);
	cell.SetTextColor(RGB(0,0,128));
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	SetCell(1,row+3,&cell);

	GetCell(1,row+4,&cell);
	cell.SetText(_T("Button"));
	cell.SetCellType(m_nButtonIndex);
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetBackColor(RGB(100,100,220));
	SetCell(1,row+4,&cell);

	//More styles
	QuickSetText(3,row,_T("More Styles"));
	JoinCells(3,row,4,row);

	GetCell(3,row+2,&cell);
	cell.SetText(_T("Click Here For The Calculator"));
	cell.SetCellType(m_nButtonIndex);
	cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS|UGCT_NORMALELLIPSIS);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetParam(BUTTON_CLICK1);
	SetCell(3,row+2,&cell);

	GetCell(3,row+3,&cell);
	cell.SetText(_T("Multi\nLine"));
	cell.SetCellType(m_nButtonIndex);
	cell.SetCellTypeEx(UGCT_BUTTONNOFOCUS|UGCT_NORMALMULTILINE);
	cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetParam(BUTTON_CLICK2);
	SetCell(3,row+3,&cell);	return row;
}

void CXPThemeDemoGrid::setup_ELLIPSIS_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Ellipsis Button"));
	SetRowHeight(row+1,10);
	SetRowHeight(row+3,30);

	//CUGEllipsisType		m_ellipsis;
	//int					m_nEllipsisIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));

	GetCell(1,row+2,&cell);
	cell.SetText(_T("Text"));
	cell.SetCellType(m_nEllipsisIndex);
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetText(_T("Text"));
	cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
	cell.SetTextColor(RGB(220,0,0));
	cell.SetCellType(m_nEllipsisIndex);
	SetCell(1,row+3,&cell);

	GetCell(1,row+4,&cell);
	cell.SetText(_T("Text"));
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetBackColor(RGB(220,240,240));
	cell.SetFont(&m_medBoldFont);
	cell.SetCellType(m_nEllipsisIndex);
	SetCell(1,row+4,&cell);

	//More styles
	QuickSetText(3,row,_T("More Styles"));
	JoinCells(3,row,4,row);

	GetCell(3,row+2,&cell);
	cell.SetText(_T("Run The Calculator"));
	cell.SetCellType(m_nEllipsisIndex);
	cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
	cell.SetParam(ELLIPSISBUTTON_CLICK1);
	SetCell(3,row+2,&cell);

	GetCell(3,row+3,&cell);
	cell.SetText(_T("Note\nPad"));
	cell.SetCellType(m_nEllipsisIndex);
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	cell.SetParam(ELLIPSISBUTTON_CLICK2);
	SetCell(3,row+3,&cell);

	GetCell(3,row+4,&cell);
	cell.SetText(_T("Raised"));
	cell.SetCellType(m_nEllipsisIndex);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetBorder(UG_BDR_RAISED);
	SetCell(3,row+4,&cell);

	GetCell(4,row+2,&cell);
	cell.SetText(_T("Editable"));
	cell.SetCellType(m_nEllipsisIndex);
	cell.SetParam(CELLTYPE_IS_EDITABLE);
	SetCell(4,row+2,&cell);
}

void CXPThemeDemoGrid::setup_SPINBTN_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Spin Button"));
	SetRowHeight(row+1,10);

	//	CUGSpinButtonType	m_spin;
	//	int					m_nSpinIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetText(_T("1"));
	cell.SetCellType(m_nSpinIndex);
	cell.SetParam(SPIN_TYPE1);
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetText(_T("One"));
	cell.SetParam(SPIN_TYPE2);
	cell.SetAlignment(UG_ALIGNCENTER);
	cell.SetCellType(m_nSpinIndex);
	SetCell(1,row+3,&cell);

	GetCell(2,row+2,&cell);
	cell.SetText(_T("Mr"));
	cell.SetParam(SPIN_TYPE3);
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetCellType(m_nSpinIndex);
	SetCell(2,row+2,&cell);

	GetCell(2,row+3,&cell);
	cell.SetParam(SPIN_TYPE4);
	cell.SetBackColor(RGB(255,0,0));
	cell.SetCellType(m_nSpinIndex);
	SetCell(2,row+3,&cell);

	//More Styles
	QuickSetText(4,row,_T("More Styles"));
	JoinCells(4,row,5,row);

	GetCell(4,row+2,&cell);
	cell.SetText(_T("A Long Piece of Text"));
	cell.SetCellType(m_nSpinIndex);
	cell.SetParam(SPIN_TYPE5);
	cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
	SetCell(4,row+2,&cell);

	GetCell(4,row+3,&cell);
	cell.SetText(_T("Editable"));
	cell.SetParam(CELLTYPE_IS_EDITABLE);		
	cell.SetCellType(m_nSpinIndex);
	SetCell(4,row+3,&cell);
}

void CXPThemeDemoGrid::setup_SLIDERS_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Slider"));
	SetRowHeight(row+1,10);

	// CUGSliderType		m_slider;
	// int					m_nSliderIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetText(_T("1"));
	cell.SetCellType(m_nSliderIndex);
	SetCell(1,row+2,&cell);

	//advanced
	QuickSetText(3,row,_T("Advanced"));
	JoinCells(3,row,2,row);

	GetCell(3,row+2,&cell);
	cell.SetText(_T("30"));
	cell.SetCellType(m_nSliderIndex);
	cell.SetParam(SLIDER_TYPE1);
	SetCell(3,row+2,&cell);

	GetCell(4,row+2,&cell);
	cell.SetText(_T("0"));
	cell.SetCellType(m_nSliderIndex);
	cell.SetParam(SLIDER_TYPE2);
	SetCell(4,row+2,&cell);

	GetCell(5,row+2,&cell);
	cell.SetText(_T("0"));
	cell.SetCellType(m_nSliderIndex);
	cell.SetParam(SLIDER_TYPE3);
	SetCell(5,row+2,&cell);

	GetCell(6,row+2,&cell);
	cell.SetText(_T("0"));
	cell.SetCellType(m_nSliderIndex);
	cell.SetParam(SLIDER_TYPE4);
	SetCell(6,row+2,&cell);

	GetCell(5, row+3, &cell);
	cell.UseThemes(false);
	SetCell(5, row+3, &cell);

	QuickSetBackColor(5,row+3,RGB(0,0,0));
}

void CXPThemeDemoGrid::setup_ARROWS_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Arrow"));
	SetRowHeight(row+1,10);


	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,4,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(UGCT_ARROW);
	cell.SetCellTypeEx(UGCT_ARROWLEFT);
	SetCell(1,row+2,&cell);

	GetCell(2,row+2,&cell);
	cell.SetCellType(UGCT_ARROW);
	cell.SetCellTypeEx(UGCT_ARROWRIGHT);
	SetCell(2,row+2,&cell);

	GetCell(3,row+2,&cell);
	cell.SetCellType(UGCT_ARROW);
	cell.SetCellTypeEx(UGCT_ARROWDRIGHT);
	SetCell(3,row+2,&cell);

	GetCell(4,row+2,&cell);
	cell.SetCellType(UGCT_ARROW);
	cell.SetCellTypeEx(UGCT_ARROWDLEFT);
	SetCell(4,row+2,&cell);

	//More Styles
	QuickSetText(6,row,_T("More Styles"));
	JoinCells(6,row,8,row);

	GetCell(6,row+2,&cell);
	cell.SetCellType(UGCT_ARROW);
	cell.SetCellTypeEx(UGCT_ARROWLEFT);
	cell.SetBackColor(RGB(220,220,255));
	cell.SetTextColor(RGB(100,100,100));
	SetCell(6,row+2,&cell);

	GetCell(7,row+2,&cell);
	cell.SetCellType(UGCT_ARROW);
	cell.SetCellTypeEx(UGCT_ARROWRIGHT);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetBorder(UG_BDR_RAISED);
	cell.SetTextColor(RGB(255,255,255));
	SetCell(7,row+2,&cell);

	GetCell(8,row+2,&cell);
	cell.SetCellType(UGCT_ARROW);
	cell.SetCellTypeEx(UGCT_ARROWDRIGHT);
	cell.SetBackColor(RGB(220,220,110));
	cell.SetBorder(UG_BDR_RECESSED);
	SetCell(8,row+2,&cell);
}


void CXPThemeDemoGrid::setup_SORTARROW_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Sort Arrow"));
	SetRowHeight(row+1,10);

	// CUGSortArrowType	m_sortArrow;
	// int				m_nSortArrowIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nSortArrowIndex);
	cell.SetCellTypeEx(UGCT_SORTARROWUP);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetBorder(UG_BDR_RAISED);
	cell.SetText(_T("Sort Up"));
	SetCell(1,row+2,&cell);

	GetCell(2,row+2,&cell);
	cell.SetCellType(m_nSortArrowIndex);
	cell.SetCellTypeEx(UGCT_SORTARROWUP);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetBorder(UG_BDR_RAISED);
	cell.SetText(_T("Sort Down"));
	SetCell(2,row+2,&cell);

	//more styles
	QuickSetText(4,row,_T("More Styles"));
	JoinCells(4,row,6,row);

	GetCell(4,row+2,&cell);
	cell.SetCellType(m_nSortArrowIndex);
	cell.SetCellTypeEx(UGCT_SORTARROWUP);
	cell.SetBackColor(RGB(0,0,220));
	cell.SetText(_T("Text"));
	cell.SetTextColor(RGB(255,255,255));
	cell.SetAlignment(UG_ALIGNCENTER);
	SetCell(4,row+2,&cell);

	GetCell(5,row+2,&cell);
	cell.SetCellType(m_nSortArrowIndex);
	cell.SetBorder(UG_BDR_RECESSED);
	cell.SetBackColor(RGB(0,220,220));
	cell.SetText(_T("Text"));
	cell.SetAlignment(UG_ALIGNRIGHT);
	cell.SetCellTypeEx(UGCT_SORTARROWUP);
	SetCell(5,row+2,&cell);
}

void CXPThemeDemoGrid::setup_PROGRESS_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Progress Bars"));
	SetRowHeight(row+1,10);

	// CUGProgressType		m_progress;
	// int					m_nProgressIndex;
	// CUGAdvProgressType	m_advProress1;
	// int					m_nAdvProressIndex1;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nProgressIndex);
	cell.SetText(_T("30"));
	cell.SetParam(3);
	cell.UseThemes(true);
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetCellType(m_nProgressIndex);
	cell.SetHBackColor(RGB(255,0,0));
	cell.SetText(_T("40"));
	cell.SetParam(0);
	cell.UseThemes(true);
	cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
	SetCell(1,row+3,&cell);

	GetCell(1,row+4,&cell);
	cell.SetCellType(m_nProgressIndex);
	cell.SetHBackColor(RGB(0,220,0));
	cell.SetText(_T("60"));
	cell.SetLabelText(_T("Progress"));
	cell.SetParam(5);
	cell.UseThemes(true);
	cell.SetAlignment(UG_ALIGNRIGHT|UG_ALIGNVCENTER);
	cell.SetCellTypeEx(UGCT_PROGRESSUSELABEL);
	SetCell(1,row+4,&cell);

	GetCell(1,row+5,&cell);
	cell.SetCellType(m_nProgressIndex);
	cell.SetHBackColor(RGB(100,0,0));
	cell.SetBackColor(RGB(250,250,220));
	cell.SetTextColor(RGB(0,0,100));
	cell.SetHTextColor(RGB(250,220,250));
	cell.SetText(_T("70"));
	cell.SetFont(&m_medBoldFont);
	cell.SetAlignment(UG_ALIGNCENTER|UG_ALIGNVCENTER);
	cell.SetParam(5);
	cell.UseThemes(true);
	SetCell(1,row+5,&cell);
	JoinCells(1,row+5,2,row+6);

	//More Styles
	QuickSetText(4,row,_T("More Styles"));
	JoinCells(4,row,5,row);

	GetCell(4,row+2,&cell);
	cell.SetCellType(m_nAdvProressIndex1);
	cell.SetText(_T("30"));
	cell.SetParam(3);
	cell.UseThemes(true);
	SetCell(4,row+2,&cell);
	JoinCells(4,row+2,5,row+3);

	m_advProress2.SetNumberSections(100);
	for (int i=0;i<100;i++){
		m_advProress2.SetSectionPercent(i,i+1);
		m_advProress2.SetSectionColor(99-i,RGB(255-i, 200-i*2, 20+i));
	}
	GetCell(4,row+4,&cell);
	cell.SetCellType(m_nAdvProressIndex2);
	cell.SetText(_T("30"));
	cell.UseThemes(true);
	cell.SetParam(3);
	SetCell(4,row+4,&cell);
	JoinCells(4,row+4,5,row+6);

	m_advProress3.SetDirection(UGCT_PROGRESS_BOTTOM);
	GetCell(6,row+2,&cell);
	cell.SetCellType(m_nAdvProressIndex3);
	cell.UseThemes(true);
	cell.SetText(_T("30"));
	cell.SetParam(3);
	SetCell(6,row+2,&cell);
	JoinCells(6,row+2,6,row+6);
}

void CXPThemeDemoGrid::setup_MULTIFONT_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Multi-Font"));
	SetRowHeight(row+1,10);

	// CUGMultiFontType	m_multiFont;
	// int				m_nMultiFontIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);


	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nMultiFontIndex);
	cell.SetText(_T("<:F,Arial,12,300>sm <:F,Arial,16,600>Med <:F,Arial,20,900>Lrg <:F,Arial,24,1000>Huge!"));
	cell.SetAlignment(UG_ALIGNBOTTOM);
	SetCell(1,row+2,&cell);
	JoinCells(1,row+2,2,row+3);

	GetCell(1,row+4,&cell);
	cell.SetCellType(m_nMultiFontIndex);
	cell.SetText(_T("<:F,Arial,15,400>The<:F,Arial,15,800> <:C,255,0,0>Red<:C,0,0,0> <:F,Arial,15,400>Truck was <:F,Arial,24,1000>BIG"));
	SetCell(1,row+4,&cell);
	JoinCells(1,row+4,2,row+5);

	GetCell(4,row+2,&cell);
	cell.SetCellType(m_nMultiFontIndex);
	cell.SetText(_T("<:F,Arial,15,800>Value:<:C,0,0,220> <:F,Arial,15,400>643.54"));
	SetCell(4,row+2,&cell);
	JoinCells(4,row+2,5,row+2);

	GetCell(4,row+3,&cell);
	cell.SetCellType(m_nMultiFontIndex);
	cell.SetText(_T("<:F,Arial,15,800>Temp<:C,220,0,0> <:F,Arial,15,400>276K"));
	cell.SetAlignment(UG_ALIGNRIGHT);
	SetCell(4,row+3,&cell);
	JoinCells(4,row+3,5,row+3);

	GetCell(4,row+4,&cell);
	cell.SetCellType(m_nMultiFontIndex);
	cell.SetText(_T("<:C,0,100,0>8234<:F,Arial,15,800> <:C,0,0,0>Units"));
	cell.SetBorder(UG_BDR_RAISED);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetAlignment(UG_ALIGNVCENTER);
	SetCell(4,row+4,&cell);
	JoinCells(4,row+4,5,row+4);

	GetCell(4,row+5,&cell);
	cell.SetCellType(m_nMultiFontIndex);
	cell.SetText(_T("<:F,Arial,12,300>Amount<:F,Arial,19,800> <:C,220,0,0>235,456.76"));
	cell.SetBackColor(RGB(240,240,170));
	SetCell(4,row+5,&cell);
	JoinCells(4,row+5,5,row+5);
}

void CXPThemeDemoGrid::setup_AUTOFONT_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Auto Size Font"));
	SetRowHeight(row+1,10);

	// CUGAutoFontType		m_autoFont;
	//int					m_nAutoFontIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nAutoFontIndex);
	cell.SetText(_T("Automatic Font Sizing"));
	SetCell(1,row+2,&cell);
	JoinCells(1,row+2,2,row+2);

	GetCell(1,row+3,&cell);
	cell.SetCellType(m_nAutoFontIndex);
	cell.SetText(_T("Auto-Font"));
	cell.SetTextColor(RGB(0,0,255));
	cell.SetAlignment(UG_ALIGNVCENTER);
	SetCell(1,row+3,&cell);
	JoinCells(1,row+3,2,row+4);

	GetCell(3,row+2,&cell);
	cell.SetCellType(m_nAutoFontIndex);
	cell.SetText(_T("Best-Fit Text"));
	SetCell(3,row+2,&cell);

	GetCell(3,row+3,&cell);
	cell.SetCellType(m_nAutoFontIndex);
	cell.SetText(_T("Size Me!"));
	cell.SetBorder(UG_BDR_RAISED);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetAlignment(UG_ALIGNVCENTER);
	SetCell(3,row+3,&cell);
}

void CXPThemeDemoGrid::setup_NOTE_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Note"));
	SetRowHeight(row+1,10);


	// CUGNoteType			m_note;
	// int					m_nNoteIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nNoteIndex);
	cell.SetText(_T("A Note"));
	cell.SetLabelText(_T("Create a detailed note\r\nfor a cell that requires\r\nmore detailed information."));
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetCellType(m_nNoteIndex);
	cell.SetText(_T("More Info"));
	cell.SetAlignment(UG_ALIGNCENTER);
	cell.SetLabelText(_T("The size of the note window is adjusted to fit the text within it.\r\n\r\nTherefore all of the details required can be fit inside of this note!!"));
	SetCell(1,row+3,&cell);

	//more styles
	QuickSetText(3,row,_T("More Styles"));
	JoinCells(3,row,4,row);		

	GetCell(3,row+2,&cell);
	cell.SetCellType(m_nNoteIndex);
	cell.SetText(_T("Aother Note With Details"));
	cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
	cell.SetLabelText(_T("The note cell type can use all of the display styles supported by the Standard cell type."));
	cell.SetTextColor(RGB(255,0,0));
	SetCell(3,row+2,&cell);

	GetCell(3,row+3,&cell);
	cell.SetCellType(m_nNoteIndex);
	cell.SetText(_T("Aother\nNote"));
	cell.SetFont(&m_medFont);
	cell.SetCellTypeEx(UGCT_NORMALMULTILINE);
	cell.SetLabelText(_T("The note cell type can use all of the display styles supported by the Standard cell type."));
	SetCell(3,row+3,&cell);
	JoinCells(3,row+3,3,row+4);

	GetCell(4,row+2,&cell);
	cell.SetCellType(m_nNoteIndex);
	cell.SetText(_T("ABC 123"));
	cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
	cell.SetLabelText(_T("The note cell type can use all of the display styles supported by the Standard cell type."));
	cell.SetTextColor(RGB(255,255,255));
	cell.SetBorder(UG_BDR_RAISED);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetAlignment(UG_ALIGNVCENTER);
	SetCell(4,row+2,&cell);
}

void CXPThemeDemoGrid::setup_LABELED_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Labeled"));
	SetRowHeight(row+1,10);
	SetRowHeight(row+2,30);
	SetRowHeight(row+3,30);

	// CUGLabeledType		m_labeled;
	// int					m_nLabeled;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nLabeledIndex);
	cell.SetText(_T("Smith"));
	cell.SetLabelText(_T("Last"));
	cell.SetFont(&m_medBoldFont);
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetCellType(m_nLabeledIndex);
	cell.SetText(_T("John"));
	cell.SetLabelText(_T("First"));
	cell.SetFont(&m_medBoldFont);
	cell.SetTextColor(RGB(0,0,120));
	SetCell(1,row+3,&cell);

	//more styles
	QuickSetText(4,row,_T("More Styles"));
	JoinCells(4,row,5,row);

	GetCell(4,row+2,&cell);
	cell.SetCellType(m_nLabeledIndex);
	cell.SetText(_T("JohnSmith@domain.com"));
	cell.SetFont(&m_medBoldFont);
	cell.SetBackColor(RGB(240,240,180));
	cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
	cell.SetLabelText(_T("Email"));
	SetCell(4,row+2,&cell);

	GetCell(4,row+3,&cell);
	cell.SetCellType(m_nLabeledIndex);
	cell.SetText(_T("$128.95"));
	cell.SetAlignment(UG_ALIGNRIGHT|UG_ALIGNVCENTER);
	cell.SetFont(&m_medBoldFont);
	cell.SetLabelText(_T("Amount"));
	SetCell(4,row+3,&cell);

	GetCell(5,row+2,&cell);
	cell.SetCellType(m_nLabeledIndex);
	cell.SetFont(&m_medBoldFont);
	cell.SetText(_T("abcdefg"));
	cell.SetLabelText(_T("Editable"));
	cell.SetCellTypeEx(UGCT_NORMALELLIPSIS);
	cell.SetParam(CELLTYPE_IS_EDITABLE);
	SetCell(5,row+2,&cell);
}



void CXPThemeDemoGrid::setup_MARQUEE_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Marquee"));
	SetRowHeight(row+1,10);

	// CUGMarqueeType		m_marquee;
	// int					m_nMarqueeIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,2,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nMarqueeIndex);
	cell.SetText(_T("Scroll large amounts of text..."));
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetCellType(m_nMarqueeIndex);
	cell.SetTextColor(RGB(220,0,0));
	cell.SetAlignment(UG_ALIGNVCENTER);
	cell.SetFont(&m_medFont);
	cell.SetText(_T("  Great for real-time data"));
	SetCell(1,row+3,&cell);

	//basic
	QuickSetText(3,row,_T("Advanced"));

	GetCell(3,row+2,&cell);
	cell.SetCellType(m_nMarqueeIndex);
	cell.SetText(_T("This one is editable..."));
	cell.SetLabelText(_T("CELLTYPE_IS_EDITABLE"));
	SetCell(3,row+2,&cell);

	GetCell(3,row+3,&cell);
	cell.SetCellType(m_nMarqueeIndex);
	cell.SetText(_T("Uses many standard display settings"));
	cell.SetBorder(UG_BDR_RAISED);
	cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	cell.SetAlignment(UG_ALIGNVCENTER);
	SetCell(3,row+3,&cell);
}

void CXPThemeDemoGrid::setup_PIECHART_ROW( int row)
{
	CUGCell cell;

	SetupSection(row, _T("Pie Chart"));
	SetRowHeight(row+1,10);

	// CUGPieChartType		m_pieChart;
	// int					m_nPieChartIndex;

	//basic
	QuickSetText(1,row,_T("Basic"));
	JoinCells(1,row,3,row);

	GetCell(1,row+2,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA);
	cell.SetText(_T("40"));
	cell.SetHBackColor(RGB(220,0,0));
	SetCell(1,row+2,&cell);

	GetCell(1,row+3,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA);
	cell.SetText(_T("70"));
	cell.SetHBackColor(RGB(0,0,220));
	SetCell(1,row+3,&cell);

	GetCell(1,row+4,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA);
	cell.SetHBackColor(RGB(0,220,0));
	cell.SetText(_T("30"));
	SetCell(1,row+4,&cell);

	GetCell(1,row+5,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA);
	cell.SetHBackColor(RGB(0,220,220));
	cell.SetText(_T("60"));
	SetCell(1,row+5,&cell);

	GetCell(2,row+2,&cell);
	cell.SetCellType(m_nPieChartIndex);
	CString string;
	string.Format(_T("1\n%ld\n1\n%ld\n"),(long)row+2,(long)row+5);
	cell.SetText(string);
	SetCell(2,row+2,&cell);
	JoinCells(2,row+2,3,row+5);

	//advanced
	QuickSetText(5,row,_T("Editable Values"));
	JoinCells(5,row,7,row);

	GetCell(5,row+2,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
	cell.SetText(_T("200"));
	cell.SetLabelText(_T("Widgets"));	
	cell.SetHBackColor(RGB(200,200,0));
	cell.SetParam(CELLTYPE_IS_EDITABLE);
	cell.SetMask(_T("999"));
	SetCell(5,row+2,&cell);

	GetCell(5,row+3,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
	cell.SetText(_T("600"));
	cell.SetLabelText(_T("Stuff"));	
	cell.SetHBackColor(RGB(200,0,200));
	cell.SetParam(CELLTYPE_IS_EDITABLE);
	cell.SetMask(_T("999"));
	SetCell(5,row+3,&cell);

	GetCell(5,row+4,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
	cell.SetText(_T("300"));
	cell.SetLabelText(_T("Things"));	
	cell.SetHBackColor(RGB(0,50,240));
	cell.SetParam(CELLTYPE_IS_EDITABLE);
	cell.SetMask(_T("999"));
	SetCell(5,row+4,&cell);

	GetCell(5,row+5,&cell);
	cell.SetCellType(m_nPieChartIndex);
	cell.SetCellTypeEx(UGCT_PIECHARTDATA|UGCT_PIECHARTDATARIGHT|UGCT_NORMALLABELTEXT);
	cell.SetText(_T("800"));
	cell.SetLabelText(_T("Gadgets"));	
	cell.SetHBackColor(RGB(0,220,220));
	cell.SetParam(CELLTYPE_IS_EDITABLE);
	cell.SetMask(_T("999"));
	SetCell(5,row+5,&cell);

	GetCell(6,row+2,&cell);
	cell.SetCellType(m_nPieChartIndex);
	string.Format(_T("5\n%ld\n5\n%ld\n"),(long)row+2,(long)row+5);
	cell.SetText(string);
	SetCell(6,row+2,&cell);
	JoinCells(6,row+2,7,row+5);
}

