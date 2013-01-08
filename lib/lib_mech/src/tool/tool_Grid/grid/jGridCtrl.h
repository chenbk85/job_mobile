/* file : jGridCtrl.h
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-25 14:31:24
comp.: rocworks.co.kr
title : 
desc : 

*/

#ifndef __jGridCtrl_header__
#define __jGridCtrl_header__
#pragma once

#pragma warning(disable : 4819)
#include "ugctrl.h"
//celltypes
#include <ugctexpand.h>
#include "ugctprog.h"
#include "ugctspin.h"
#include "ugctbutn.h"
#include "ugctsarw.h"
#include "ugctelps.h"
#include "ugctrado.h"
#include "ugctmfnt.h"
#include "ugctpie.h"
#include "ugctafnt.h"
#include "ugctpro1.h"
#include "ugctsldr.h"
#include "ugctdtp.h"
#include "ugctmarquee.h"
#include "UGCTNote.h"
#include "UGCTLabeled.h"
#pragma warning(default : 4819)

#define jGRIDCTRL_CELLTYPE_IS_EDITABLE		999
#define jWM_USER_UPDATE_CELL  WM_USER + 1
#define jUGCT_CONTEXT_MENU_EVENT 5000 // context menu 이벤트 발생시 ID값에 넘어감.

//jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
#define jGRIDCRTL_NOTIFY_PARAM long ID,int col,long row,long msg,LONG_PTR param
#define jGRIDCRTL_NOTIFY_CALL  ID,col,row,msg,param

#define jGRIDCRTL_NOTIFY_PARAM2 class jGridCtrl* pGrid,jIE* pE,jGRIDCRTL_NOTIFY_PARAM
#define jGRIDCRTL_NOTIFY_CALL2  pGrid,pE,jGRIDCRTL_NOTIFY_CALL

struct __jGRIDCRTL_EVENT_handler {	virtual int Call(jGRIDCRTL_NOTIFY_PARAM2) const =0;};



#define jGRIDCRTL_EVENT(View,Name) \
struct _jJOIN_4(jGRIDCRTL_EVENT_,View,_,Name) : public __jGRIDCRTL_EVENT_handler {_jJOIN_4(jGRIDCRTL_EVENT_,View,_,Name)(){\
	nMech::tfname_t szName; jt_sprintf(szName,_T("jGRIDCRTL_EVENT_%s_%s"), jS(View),jS(Name) ); \
	nMech::jBase::RegistNamedPointer(jS(View) , szName , (__jGRIDCRTL_EVENT_handler*)this);} int Call(jGRIDCRTL_NOTIFY_PARAM2) const;}; \
	static _jJOIN_4(jGRIDCRTL_EVENT_,View,_,Name) _jJOIN_4(g_jGRIDCRTL_EVENT_,View,_,Name);\
	int _jJOIN_4(jGRIDCRTL_EVENT_,View,_,Name)::Call(jGRIDCRTL_NOTIFY_PARAM2) const

#define jGRIDCRTL_EVENT_ColRow(View,Col,Row) \
struct _jJOIN_4(jGRIDCRTL_EVENT_,Col,View,Row) : public __jGRIDCRTL_EVENT_handler {_jJOIN_4(jGRIDCRTL_EVENT_,Col,View,Row)(){\
	nMech::tfname_t szName; jt_sprintf(szName,_T("jGRIDCRTL_EVENT_%d%s%d"), Col,jS(View),Row); \
	nMech::jBase::RegistNamedPointer(jS(View) , szName , (__jGRIDCRTL_EVENT_handler*)this);} int Call(jGRIDCRTL_NOTIFY_PARAM2) const;}; \
	static _jJOIN_4(jGRIDCRTL_EVENT_,Col,View,Row) _jJOIN_4(g_jGRIDCRTL_EVENT_,Col,View,Row);\
	int _jJOIN_4(jGRIDCRTL_EVENT_,Col,View,Row)::Call(jGRIDCRTL_NOTIFY_PARAM2) const


#define jAT(NAME) it->GetAttrVar(jS(NAME))
#define jAT_i(NAME) it->GetAttrVar(jS(NAME))->Get_int()
//#define jAT_i33(pV) pV->GetInt(0),pV->GetInt(1),pV->GetInt(2)
#define jAT_ia(NAME,i) it->GetAttrVar(jS(NAME))->GetInt(i)
#define jAT_s(NAME) it->GetAttrVar(jS(NAME))->Get_cstr()
#define jAT_CR(ColRow) jAT(ColRow)->GetInt(0),jAT(ColRow)->GetInt(1)
#define jPO po.x , po. y
#define jCELL_TYPE_i(X) GetCellTypeIndex(jS(X))
#define jCELL_TYPE_p(T,X) ((T*)GetCellTypePtr(jS(X)))
#define jAT_IF(X) pV = jAT(X);if(pV)


const int jNULL_PO = -9999;


#define jINTERFACE_jIGridCtrl(X) public:\
	virtual void SetNumber(int c,int r,int Value) ##X\
	virtual void SetText(int c,int r,cstr Value) ##X\
	virtual void SetReadOnly(int c,int r,bool b) ##X\
	virtual void SetNumberPos(cstr szPOS,int Value) ##X\
	virtual void SetTextPos(cstr szPOS,cstr Value) ##X\
	virtual void SetReadOnlyPos(cstr szPOS,bool b) ##X\
	virtual int GetColNum() ##X\
	virtual int GetRowNum() ##X\
	virtual void setColWidth(int col,int w) ##X\
	virtual void setRowHeight(int row,int h) ##X\
	virtual void resetCell(int startRow, int endRow, int startCol, int endCol) ##X\
	virtual void joinCells(int startCol,long startRow,int endCol,long endRow) ##X\


jINTERFACE_END(jIGridCtrl);

#define for_each_ECheckBoxState(X)\
	X(eEMPTY	,0	,"CHECKBOX NULL")\
	X(ePUSH		,1	,"CHECKBOX PUSH")\
	X(ePUSH2	,2	,"CHECKBOX PUSH2")\

jDEFINE_ENUM_CODE(ECheckBoxState);

#define for_each_XML_FUNC(X)\
	X(XmlCreateFont)\
	X(SetGridDefault)\
	X(JoinCells)\
	X(GROUP)\
	X(CUGCellType)\
	X(ExpandCell)\
	X(SetNumberOfRows)\
	X(NamedCellList)\
	X(SetReadOnly)\
	X(SQScript)\
	X(SetUserSizingMode)\
	X(CellFont)\
	X(SetColWidth)\
	X(SetVScrollMode)\
	X(SetupSection)\
	X(SetRowHeight)\
	X(SetAlignment)\
	X(SetCellTypeEx)\
	X(Cell)\
	X(CheckBox)\
	X(Button)\
	X(EllipsisButton)\
	X(SpinButton)\
	X(Slider)\
	X(ProgressBar)\
	X(Config)\


#define for_each_default_CUGCellType(X)\
	X(CUGRadioType)\
	X(CUGCTDateTimePicker)\
	X(CUGExpandType)\
	X(CUGButtonType)\
	X(CUGEllipsisType)\
	X(CUGSpinButtonType)\
	X(CUGSliderType)\
	X(CUGSortArrowType)\
	X(CUGProgressType)\
	X(CUGMultiFontType)\
	X(CUGAutoFontType)\
	X(CUGNoteType)\
	X(CUGLabeledType)\
	X(CUGMarqueeType)\
	X(CUGPieChartType)\
	X(CUGAdvProgressType)\

class jGridCtrl:public CUGCtrl, public jIGridCtrl
{
public:
	typedef jGridCtrl parent_t;
	jINTERFACE_HEADER(jIGridCtrl);

	jIE* m_peGrid;

	jGridCtrl(jIE* pE);
	~jGridCtrl();


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL


	//{{AFX_MSG(jGridCtrl)
	// NOTE - the ClassWizard will add and remove member functions here.
	//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	virtual void OnDrawFocusRect(CDC *dc,RECT *rect);
	virtual int OnCellTypeNotify(jGRIDCRTL_NOTIFY_PARAM);

	virtual int On_DropList(jIE* peCell,jGRIDCRTL_NOTIFY_PARAM);
	virtual int On_Checkbox(jIE* peCell,jGRIDCRTL_NOTIFY_PARAM);
	virtual int On_UGCT_EXPANDCONTRACT(jIE* peCell,jGRIDCRTL_NOTIFY_PARAM);
	

	int On_MenuCommand(int col,long row,int section,int item);
	int On_MenuStart(int col,long row,int section);

	virtual void OnMenuCommand(int col,long row,int section,int item){this->On_MenuCommand(col,row,section,item);}
	virtual int OnMenuStart(int col,long row,int section){return this->On_MenuStart(col,row,section);}


	#define jGRIDCTRL_NOTIFY(X) int jGridCtrl::On_##X(jIE* peCell, jGRIDCRTL_NOTIFY_PARAM)
	#define jGRIDCTRL_NOTIFY_decl(X) virtual int On_##X(jIE* peCell,jGRIDCRTL_NOTIFY_PARAM);
	for_each_default_CUGCellType(jGRIDCTRL_NOTIFY_decl);

	virtual void OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed);
	virtual void OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed);
	virtual void OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed=0);
	virtual void OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed=0);
	virtual void OnCB_DClicked(RECT *rect,POINT *point,BOOL processed=0);

	virtual void OnGetCell(int col,long row,CUGCell *cell);

	virtual void OnCharDown(UINT *vcKey,BOOL processed);
	virtual int OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow);
	virtual int OnEditFinish(int col, long row,CWnd* edit,LPCTSTR string,BOOL cancelFlag);
	
	
	bool SetValue_ByXml(jIE* peCell,int col,int row,tcstr string,CWnd* edit);


public:
	//***** Over-ridable Notify Functions *****
	virtual void OnSetup();

protected:
	#define decl_func342(NAME) void xml_##NAME(jIE* it,CUGCell& cell);
	for_each_XML_FUNC(decl_func342);
	POINT jGridCtrl::_GetColRow(jIE* it,cstr sz,jIVar** ppV=0);

public:
	struct typecell_t
	{
		int cell_type_index;
		CUGCellType* pCellType;
		jIE* pE;
	};
	jLIST_TYPEDEF_map(tstring,typecell_t,m_mapCUGCellType );
	struct jNamedCellList
	{
		jNamedCellList(){m_po=0;m_pE=0;}
		jNamedCellList(jIVar* p,jIE* e){m_pE=e;m_po=p;}
		POINT GetPos()
		{ 
			POINT po;
			po.x=m_po->GetInt(0);
			po.y=m_po->GetInt(1);
		}
		jIVar* m_po;
		jIE* m_pE;
	};
	jLIST_TYPEDEF_map(tstring,jNamedCellList,m_mapNamedCellList);
	jIVar* GetNameCellPos(cstr sz)
	{
		m_mapNamedCellList_it it = m_mapNamedCellList.find(sz);
		if(it==m_mapNamedCellList.end())
			return 0;
		return it->second.m_po;
	}
	POINT jGridCtrl::GetNamedCellPOINT(cstr sz)
	{
		POINT po;
		po.x=jNULL_PO;
		po.y=jNULL_PO;
		jIVar* pV = GetNameCellPos(sz);
		jRETURN_ret(po,pV);
		po.x= pV->GetInt(0);
		po.y= pV->GetInt(1);
		return po;
	}
	jLIST_TYPEDEF_map(tstring,CFont*,m_mapCFont);
	CFont* GetFont(cstr sz);
	int jGridCtrl::GetCellTypeIndex(cstr sz);
	CUGCellType* GetCellTypePtr(cstr sz);
	void SetupSection(long row, LPCTSTR title);

	jLIST_TYPEDEF_map(LONG , jIE* , m_mapXmlCellList);
	jIE* GetCellXml(int col,int row)
	{
		m_mapXmlCellList_it it = m_mapXmlCellList.find(MAKELONG(col,row));
		if(it==m_mapXmlCellList.end()) return 0;
		return it->second;
	}
	__jGRIDCRTL_EVENT_handler* jGridCtrl::get_Handler(cstr szName,int col,int row);

	bool m_isprocessed;
	int m_iCurrCellX,m_iCurrCellY;

};

#define jGridCtrl_XML_FUNC(NAME) void jGridCtrl::xml_##NAME(jIE* it,CUGCell& __cell)

extern jGridCtrl* g_jGridCtrl;
int getFlag_UG_ALIGN(cstr sz);
int getFlag_UGCT_NORMAL(cstr sz);
int getFlag_UGCT_CHECKBOX(jIVar* pV);
int getFlag_UG_BDR(cstr sz);
COLORREF getSystemColor(jIVar* pV);
#endif // __jGridCtrl_header__
