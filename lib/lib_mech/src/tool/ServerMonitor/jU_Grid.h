/* file : jU_Grid.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-14 13:40:41
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jU_Grid_header__
#define __jU_Grid_header__
#pragma once

#define STANDARD_ROW	1
#define DROPLIST_ROW	STANDARD_ROW + 8
#define CHECKBOX_ROW	DROPLIST_ROW + 7
#define RADIOBTN_ROW	CHECKBOX_ROW + 10
#define DATETIME_ROW	RADIOBTN_ROW + 5
#define PUSHBTN_ROW		DATETIME_ROW + 5
#define ELLIPSIS_ROW	PUSHBTN_ROW + 6
#define SPINBTN_ROW		ELLIPSIS_ROW + 7
#define SLIDERS_ROW		SPINBTN_ROW + 5
#define ARROWS_ROW		SLIDERS_ROW + 5
#define SORTARROW_ROW	ARROWS_ROW + 4
#define PROGRESS_ROW	SORTARROW_ROW + 4
#define MULTIFONT_ROW	PROGRESS_ROW + 8
#define AUTOFONT_ROW	MULTIFONT_ROW + 7
#define NOTE_ROW		AUTOFONT_ROW + 6
#define LABELED_ROW		NOTE_ROW + 6
#define MARQUEE_ROW		LABELED_ROW + 5
#define PIECHART_ROW	MARQUEE_ROW + 5
#define NUM_ROWS		PIECHART_ROW + 7


//cell 'param' values, used as a style field
#define DROPLIST_DYNAMIC_LOAD		110
#define DROPLIST_DYNAMIC_LOAD2		111
#define DROPLIST_DYNAMIC_LOAD3		112
#define DROPLIST_CHANGE_SELECTION	113
#define DROPLIST_CHANGE_SELECTION2	114

#define CELLTYPE_IS_EDITABLE		120

#define CHECKBOX_CHANGEFONT			130

#define BUTTON_CLICK1				140
#define BUTTON_CLICK2				141
#define BUTTON_CLICK3				142

#define ELLIPSISBUTTON_CLICK1		150
#define ELLIPSISBUTTON_CLICK2		151

#define SPIN_TYPE1					160
#define SPIN_TYPE2					161
#define SPIN_TYPE3					162
#define SPIN_TYPE4					163
#define SPIN_TYPE5					164

#define SLIDER_TYPE1				170
#define SLIDER_TYPE2				171
#define SLIDER_TYPE3				172
#define SLIDER_TYPE4				173

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "jGridCtrl.h"


class jU_Grid : public jGridCtrl
{
	//Arrow cell type built-in
	//UGCT_ARROW

	//bitmaps
	//	CBitmap				m_noteBitmap;
	//	CBitmap				m_folderBitmap;

	//menu notifications
	virtual void OnMenuCommand(int col,long row,int section,int item);
	virtual int  OnMenuStart(int col,long row,int section);

	//celltype notification handlers
	int OnDropList(long ID,int col,long row,long msg,LONG_PTR param);
	int OnCheckbox(long ID,int col,long row,long msg,LONG_PTR param);
	int OnDateTime(long ID,int col,long row,long msg,LONG_PTR param);
	int OnPushButton(long ID,int col,long row,long msg,long param);
	int OnEllipsisButton(long ID,int col,long row,long msg,long param);
	int OnSpinButton(long ID,int col,long row,long msg,long param);
	int OnSlider(long ID,int col,long row,long msg,long param);

public:
	jU_Grid(jIE* pE);
	virtual ~jU_Grid();

	DECLARE_MESSAGE_MAP()


	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();

	void setup_PIECHART_ROW( int row);
	void setup_MARQUEE_ROW( int row);
	void setup_LABELED_ROW( int row);
	void setup_NOTE_ROW( int row);
	void setup_AUTOFONT_ROW( int row);
	void setup_MULTIFONT_ROW( int row);
	void setup_PROGRESS_ROW( int row);
	void setup_SORTARROW_ROW( int row);
	void setup_ARROWS_ROW( int row);
	void setup_SLIDERS_ROW( int row);
	void setup_SPINBTN_ROW( int row);
	void setup_ELLIPSIS_ROW( int row);
	int setup_PUSH_BUTTON( int row);
	void setup_DATE_TIME( int row);
	void setup_RADIOBTN_ROW( int row);
	void setup_CHECKBOX( int row);
	void setup_DROPLIST( int row);
	int setup_STANDARD( int row);

	virtual int OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow);
	virtual int OnEditFinish(int col, long row,CWnd* edit,LPCTSTR string,BOOL cancelFlag);

	//cell type notifications
	virtual int OnCellTypeNotify(long ID,int col,long row,long msg,LONG_PTR param);

	//mouse and key strokes
	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);

	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
};


#define MSG_USE_THEMES				15101
#define MSG_DONT_USE_THEMES			15102
#define MSG_USE_THEMES_ALL			15103
#define MSG_DONT_USE_THEMES_ALL		15104

#endif // __jU_Grid_header__
