/* file : jGridCtrl.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-25 14:31:26
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jGridCtrl.h"


#include "resource.h"
#include "jGridCtrl.h"
#include <ugxpthemes.h>
#include "interface/Squirrel/jISquirrel.h"
#include "header/uString_stl.h"
//#include <math.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(jGridCtrl,CUGCtrl)
	//{{AFX_MSG_MAP(jGridCtrl)
	// NOTE - the ClassWizard will add and remove mapping macros here.
	//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

jGridCtrl* g_jGridCtrl=0;
/////////////////////////////////////////////////////////////////////////////
// Standard jGridCtrl construction/destruction
jGridCtrl::jGridCtrl(jIE* pE)
{
	m_isprocessed=false;
	g_jGridCtrl=this;
	void init_tool_Grid_lib();init_tool_Grid_lib();
	m_peGrid = pE;
	m_iCurrCellX=m_iCurrCellY=0;
	UGXPThemes::UseThemes(true);	
}

jGridCtrl::~jGridCtrl()
{
	UGXPThemes::CleanUp();
	m_mapCFont_it it = m_mapCFont.begin(), ie = m_mapCFont.end();
	for(;it!=ie;++it)
	{
		SAFE_DELETE(it->second);
	}
	m_mapCFont.clear();
}

void jGridCtrl::OnDrawFocusRect(CDC *dc,RECT *rect){

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


__jGRIDCRTL_EVENT_handler* jGridCtrl::get_Handler(cstr szName,int col,int row)
{
	cstr szView = m_peGrid->GetAttr(jS(RTTI_NAME)) ;
	jRETURN_ret(FALSE,szView);

	__jGRIDCRTL_EVENT_handler* pF=0;
	nMech::tfname_t szBuff; 
	if(szName)
	{
		jt_sprintf(szBuff,_T("jGRIDCRTL_EVENT_%s_%s"), szView, szName );
		pF = (__jGRIDCRTL_EVENT_handler*)jBase::FindNamedPointer(szView,szBuff);
		if(pF)
			return pF;
	}

	jt_sprintf(szBuff,_T("jGRIDCRTL_EVENT_%d%s%d"), col,szView,row);
	return (__jGRIDCRTL_EVENT_handler*)jBase::FindNamedPointer(szView,szBuff);
}


//border style defines
#define for_each_UG_BDR(X)\
	X(LTHIN)\
	X(TTHIN)\
	X(RTHIN)\
	X(BTHIN)\
	X(LMEDIUM)\
	X(TMEDIUM)\
	X(RMEDIUM)\
	X(BMEDIUM)\
	X(LTHICK)\
	X(TTHICK)\
	X(RTHICK)\
	X(BTHICK)\
	X(RECESSED)\
	X(RAISED)\

int getFlag_UG_BDR(cstr sz)
{
	int flag=0;
	#define check_UG_BDR(X) if(jt_strstr(sz,jS(X))) flag|= UG_BDR_##X;
	for_each_UG_BDR(check_UG_BDR);
	return flag;
}

void jGridCtrl::SetupSection(long row, LPCTSTR title)
{

	CUGCell cell;

	cell.SetBackColor(RGB(240,240,240));
	cell.SetTextColor(RGB(0,0,128));
	cell.SetFont(GetFont(jS(boldFont)));
	cell.SetAlignment(UG_ALIGNVCENTER);
	QuickSetRange(0,row,GetNumberCols() - 1,row,&cell);

	QuickSetText(-1,row,title);
}
int jGridCtrl::OnCellTypeNotify(jGRIDCRTL_NOTIFY_PARAM)
{
	if(ID==UGCT_DROPLIST)
	{
		m_isprocessed=false;
	}

	jIE* peCell= GetCellXml(col,row);
	if(!peCell) return FALSE;

	if(ID == UGCT_DROPLIST)
	{
		On_DropList(peCell,jGRIDCRTL_NOTIFY_CALL);
		return TRUE;
	}
	else if(ID == UGCT_CHECKBOX)
	{
		On_Checkbox(peCell,jGRIDCRTL_NOTIFY_CALL);
		return TRUE;
	}
	else if(ID==UGCT_EXPANDCONTRACT)
	{
		On_UGCT_EXPANDCONTRACT(peCell,jGRIDCRTL_NOTIFY_CALL);
	}
	#define if_call_virtualfunc432(X) else if(ID == jCELL_TYPE_i(X)){return On_##X(peCell,jGRIDCRTL_NOTIFY_CALL);}
	for_each_default_CUGCellType(if_call_virtualfunc432)
	else
	{
		printf("");
	}
	return TRUE;
}

int jGridCtrl::On_DropList(jIE* peCell,jGRIDCRTL_NOTIFY_PARAM)
{
	m_isprocessed=false;

	jIE* peDropList = peCell->Find(jS(DropList));
	if(!peDropList ) return TRUE;

	int ret=0;
	switch (msg )
	{
	case UGCT_DROPLISTSTART:
		{
			//jLOG(jFUNC1 _T("UGCT_DROPLISTSTART"));
			cstr szName = peCell->GetAttr(jS(Name));
			if(!szName)
			{
				szName = peCell->GetAttr(jS(EVENT_NAME));
				if(!szName)
				{
					szName = peDropList->GetAttr(jS(EVENT_NAME));
				}
			}
			__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
			if(pF){	ret = pF->Call(this, peDropList,jGRIDCRTL_NOTIFY_CALL);}

			CStringList* pList = (CStringList*)param;
			jIE* pE = peDropList->begin();
			jrFOR(pE)
			{
				jIVar* pV = pE->GetAttrVar(jS(ENABLE));
				if(pV && !pV->Get_bool()) continue;
				pList->AddTail(pE->Get_cstr());
			}
			return ret;
		}
	case UGCT_DROPLISTSELECTEX:
		{
			//jLOG(jFUNC1 _T("UGCT_DROPLISTSELECTEX"));
			cstr szName = peCell->GetAttr(jS(Name));
			jIE* peItem = peDropList->FindByOrder(param);
			if(!szName)
			{
				szName = peCell->GetAttr(jS(EVENT_NAME));
				if(!szName)
				{
					szName = peDropList->GetAttr(jS(EVENT_NAME));
					if(!szName)
					{
						szName = peItem->GetAttr(jS(EVENT_NAME));
					}
				}
			}
			__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
			if(pF){	return pF->Call(this, peItem,jGRIDCRTL_NOTIFY_CALL);}
			break;
		}
	}
	return TRUE;
}
int jGridCtrl::On_UGCT_EXPANDCONTRACT(jIE* peCell,jGRIDCRTL_NOTIFY_PARAM)
{

	return TRUE;
}
int jGridCtrl::On_Checkbox(jIE* peCell,jGRIDCRTL_NOTIFY_PARAM)
{
	if(!peCell->GetAttrVar(jS(CheckBoxType))) return FALSE;
	if(msg!=UGCT_CHECKBOXSET) return FALSE;
	jIE* it = peCell->GetParent();
	if(it->IsName(jS(CheckBox)))
	{
		jIVar* pV = jAT(ColRow);
		col = pV->GetInt(0);
		row = pV->GetInt(1);
	}

	cstr szName = peCell->GetAttr(jS(Name));
	if(!szName)
	{
		szName = peCell->GetAttr(jS(EVENT_NAME));
	}

	__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
	if(pF)
	{
		return pF->Call(this, peCell,jGRIDCRTL_NOTIFY_CALL);
	}
	return FALSE;
}



CFont* jGridCtrl::GetFont(cstr sz)
{ 
	m_mapCFont_it it = m_mapCFont.find(sz);
	if(it==m_mapCFont.end()) return 0;
	return it->second;
}
int jGridCtrl::GetCellTypeIndex(cstr sz)
{
	m_mapCUGCellType_it it = m_mapCUGCellType.find(sz);
	jRETURN_ret(0,it!=m_mapCUGCellType.end());
	//if(it==m_mapCUGCellType.end()) return 0;
	return it->second.cell_type_index;
}
CUGCellType* jGridCtrl::GetCellTypePtr(cstr sz)
{
	m_mapCUGCellType_it it = m_mapCUGCellType.find(sz);
	jRETURN_ret(0,it!=m_mapCUGCellType.end());
	//if(it==m_mapCUGCellType.end()) return GetCellType(0);
	return it->second.pCellType;
}

const int iMENU_OFFSET=1000;
int jGridCtrl::On_MenuCommand(int col,long row,int msg,int param)
{
	col = GetColTranslation( col );
	jIE* peCell = GetCellXml(col,row);
	if(!peCell) return FALSE;
	jIE* peMenu= peCell->Find(jS(Menu));
	if(!peMenu) return FALSE;
	jIE* peItem= peMenu->FindByOrder(param-iMENU_OFFSET);
	if(!peItem) return FALSE;

	cstr szName = 0;
	jONCE
	{
		peCell->GetAttr(jS(Name));
		if(szName) break;

		szName = peCell->GetAttr(jS(EVENT_NAME));
		if(szName) break;

		szName = peItem->GetAttr(jS(EVENT_NAME));
		if(szName) break;

		szName = peMenu->GetAttr(jS(EVENT_NAME));
	}
	jIVar* pV = peCell->GetAttrVar(jS(ColRow));
	__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,pV->GetInt(0),pV->GetInt(1));
	if(pF)
	{
		long ID =jUGCT_CONTEXT_MENU_EVENT;
		param = peItem->GetOrder();
		pF->Call(this, peItem,jGRIDCRTL_NOTIFY_CALL);
	}


	//jLOG(jFUNC1 _T(" %s"), peCell->Get_cstr() );
	return TRUE;
}
int  jGridCtrl::On_MenuStart(int col,long row,int msg)
{
	col = GetColTranslation( col );
	jIE* peCell = GetCellXml(col,row);
	if(!peCell) return FALSE;
	peCell = peCell->Find(jS(Menu));
	if(!peCell) return FALSE;
	EmptyMenu();
	peCell = peCell->begin();
	jrFOR(peCell)
	{
		long ID =1;
		int iOrder = peCell->GetOrder();
		jIVar* pV = peCell->GetAttrVar(jS(ENABLE));
		if(pV && !pV->Get_bool())
		{
			AddMenuItem(-1, peCell->Get_cstr() );
		}
		else
		{
			if(peCell->GetVar()->IsType(jIVar::ETelement))
			{
				AddMenuItem(iOrder+iMENU_OFFSET, _T("")) ;
			}
			else
				AddMenuItem(iOrder+iMENU_OFFSET, peCell->Get_cstr() );
		}

	}
	return TRUE;
}

jGRIDCTRL_NOTIFY(CUGRadioType)
{
	jIE* peRadio = peCell->Find(jS(Radio));
	if(!peRadio) return FALSE;
	jIE* peItem = peRadio->FindByOrder(param);
	if(!peItem) return FALSE;

	//jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	cstr szName = peCell->GetAttr(jS(Name));
	if(!szName)
	{
		szName = peCell->GetAttr(jS(EVENT_NAME));
		if(!szName)
		{
			szName = peRadio->GetAttr(jS(EVENT_NAME));
			if(!szName)
			{
				szName = peItem->GetAttr(jS(EVENT_NAME));
			}
		}
	}

	__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
	if(pF){	return pF->Call(this, peItem,jGRIDCRTL_NOTIFY_CALL);}
	return FALSE;
}


jGRIDCTRL_NOTIFY(CUGCTDateTimePicker)
{
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGExpandType)
{
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGButtonType)
{
	if(msg==UGCT_BUTTONCLICK)
	{
		cstr szName = peCell->GetAttr(jS(Name));
		if(!szName)
		{
			szName = peCell->GetAttr(jS(EVENT_NAME));
		}
		if(!szName)
		{
			szName = peCell->GetParent()->GetAttr(jS(EVENT_NAME));
		}
		__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
		if(pF){	return pF->Call(this, peCell,jGRIDCRTL_NOTIFY_CALL);}
	}
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGEllipsisType)
{
	if(UGCT_ELLIPSISBUTTONCLICK==msg)
	{
		cstr szName = peCell->GetAttr(jS(Name));
		if(!szName)
		{
			szName = peCell->GetAttr(jS(EVENT_NAME));
		}
		__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
		if(pF){	return pF->Call(this, peCell,jGRIDCRTL_NOTIFY_CALL);}
	}

	return FALSE;
}
jGRIDCTRL_NOTIFY(CUGSpinButtonType)
{
	jIVar* pV = peCell->GetAttrVar(jS(Value));
	bool isCall=true;
	CUGCell cell;
	if(!pV) return FALSE;

	GetCell(col,row,&cell);

	jIVar* pvMinMax= peCell->GetAttrVar(jS(MinMax));
	jIVar* pvOffSet= peCell->GetAttrVar(jS(Offset));
	if(pV->IsType(jIVar::EDint))
	{
		int iVal = pV->Get_int();
		int iOffset= 1;
		if(pvOffSet)iOffset = pvOffSet->Get_int();
		if(msg==UGCT_SPINBUTTONUP)
		{
			iVal+=iOffset;
			if(pvMinMax)if(iVal > pvMinMax->GetInt(1))iVal = pvMinMax->GetInt(1);
		}
		else if(msg == UGCT_SPINBUTTONDOWN)
		{
			iVal-=iOffset;
			if(pvMinMax)if(iVal < pvMinMax->GetInt(0))iVal = pvMinMax->GetInt(0);
		}
		if(pV->Get_int() !=iVal)
		{
			pV->Set_int(iVal);
		}
		else
			isCall=false;
	}
	else if(pV->IsType(jIVar::EDfloat))
	{
		float iVal = pV->Get_float();
		float iOffset= 1;
		if(pvOffSet)iOffset = pvOffSet->Get_float();
		if(msg==UGCT_SPINBUTTONUP)
		{
			iVal+=iOffset;
			if(pvMinMax)if(iVal > pvMinMax->GetFloat(1))iVal = pvMinMax->GetFloat(1);
		}
		else if(msg == UGCT_SPINBUTTONDOWN)
		{
			iVal-=iOffset;
			if(pvMinMax)if(iVal < pvMinMax->GetFloat(0))iVal = pvMinMax->GetFloat(0);
		}
		if(pV->Get_float() !=iVal)
		{
			pV->Set_float(iVal);
		}
		else
			isCall=false;
	}
	if(isCall)
	{
		fname_t buf;
		pV->ToString(buf);
		cell.SetText(buf);	SetCell(col,row,&cell);
		cstr szName = peCell->GetAttr(jS(Name));
		if(!szName)
		{
			szName = peCell->GetAttr(jS(EVENT_NAME));
		}
		__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
		if(pF){	return pF->Call(this, peCell,jGRIDCRTL_NOTIFY_CALL);}
	}
	return FALSE;
}
jGRIDCTRL_NOTIFY(CUGSliderType)
{
	m_isprocessed=false;
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);

	fname_t szValue;
	jIVar* pvMinMax = peCell->GetAttrVar(jS(MinMax));
	jIVar* pvValue = peCell->GetAttrVar(jS(Value));
	if(pvMinMax)
	{
		switch (pvValue->GetType())
		{
		case jIVar::EDint:
			{
				int iValue = pvMinMax->GetFloat(0) + (pvMinMax->GetFloat(1)-pvMinMax->GetFloat(0)) * param / 100;
				jt_sprintf(szValue,_T("%d"),iValue);
				break;
			}
		case jIVar::EDfloat:
			{
				float iValue = pvMinMax->GetFloat(0) + (pvMinMax->GetFloat(1)-pvMinMax->GetFloat(0)) * param / 100;
				jt_sprintf(szValue,_T("%5.3f"),iValue);
				break;
			}
		}
	}
	else
	{
		jt_sprintf(szValue,_T("%d"),param);
	}
	SetValue_ByXml(peCell,col,row,szValue,0);

	jIE* it = peCell->Find(jS(TextLabel));
	if(it)
	{
		CUGCell cell;
		GetCell(jAT_CR(ColRow),&cell);
		cell.SetText(szValue);
		SetCell(jAT_CR(ColRow),&cell);
		RedrawCell( jAT_CR(ColRow));
	}
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGSortArrowType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGProgressType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGAdvProgressType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGMultiFontType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGAutoFontType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGNoteType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGLabeledType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return FALSE;
}
jGRIDCTRL_NOTIFY(CUGMarqueeType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}
jGRIDCTRL_NOTIFY(CUGPieChartType)
{
	jLOG(jFUNC1 _T("id=%d, col=%d,row=%d,msg=%d,param=%d") ,ID,col,row,msg,param);
	return TRUE;
}


void jGridCtrl::OnLClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{ 
	jIE* it = GetCellXml(col,row);
	if(!it)return ;

	//jLOG(jFUNC1 _T("updn = %d"),updn);
	m_isprocessed = updn;

}
void jGridCtrl::OnRClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{ 
	jIE* it = GetCellXml(col,row);
	if(!it)return ;
}
void jGridCtrl::OnMouseMove(int col,long row,POINT *point,UINT nFlags,BOOL processed)
{ 
	jIE* it = GetCellXml(col,row);
	if(!it)return ;
	if(m_isprocessed)
	{
		//jLOG(jFUNC1 _T("col=%d,row=%d,nFlags=%d") ,col,row,nFlags);
	}

}

void jGridCtrl::OnDClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{
	jIE* it = GetCellXml(col,row);
	if(!it)return ;
	CUGCell cell;
	GetCell(col,row,&cell);
	int nCellTypeIndex = cell.GetCellType();
	int nParam = cell.GetParam();
	jIVar* pV;
	jAT_IF(ReadOnly)
	{
		if(!pV->Get_bool())
		{
			StartEdit();
			return ;
		}
	}

	if(nParam == jGRIDCTRL_CELLTYPE_IS_EDITABLE )
	{
		StartEdit();
		return ;
	}
}

void jGridCtrl::OnTH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnTH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnTH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnSH_LClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnSH_RClicked(int col,long row,int updn,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnSH_DClicked(int col,long row,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnCB_LClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnCB_RClicked(int updn,RECT *rect,POINT *point,BOOL processed)
{ 
}
void jGridCtrl::OnCB_DClicked(RECT *rect,POINT *point,BOOL processed)
{ 
}


void jGridCtrl::OnGetCell(int col,long row,CUGCell *cell){

}


void jGridCtrl::OnCharDown(UINT *vcKey,BOOL processed)
{
	jIE* it = GetCellXml(GetCurrentCol(),GetCurrentRow());
	if(!it)return ;

	jIVar* pV;
	jAT_IF(ReadOnly)
	{
		if(!pV->Get_bool())
		{
			StartEdit();
		}
		return ;
	}

	CUGCell cell;
	GetCell(GetCurrentCol(),GetCurrentRow(),&cell);
	if(cell.GetParam()!=jGRIDCTRL_CELLTYPE_IS_EDITABLE)
		return;
	StartEdit(*vcKey);
}

int jGridCtrl::OnEditContinue(int oldcol,long oldrow,int* newcol,long* newrow)
{
	return FALSE;
}

int	jGridCtrl::OnEditFinish(int col, long row,CWnd* edit,LPCTSTR string,BOOL cancelFlag)
{
	if(cancelFlag) 
		return TRUE;

	jIE* peCell= GetCellXml(col,row);
	if(!peCell) return TRUE;

	SetValue_ByXml(peCell,col,row,string,(CWnd*)edit);
	return TRUE;
}

cstr find_event_name(jIE* peCell)
{
	cstr szName = peCell->GetAttr(jS(Name));
	if(szName) return szName;
	szName = peCell->GetAttr(jS(EVENT_NAME));
	if(szName) return szName;
	jIVar* pV=0;
	peCell->GetAttrFromParent(jS(EVENT_NAME),&pV);
	if(!pV) return 0;
	return pV->Get_cstr();
}


bool jGridCtrl::SetValue_ByXml(jIE* peCell,int col,int row,tcstr string,CWnd * edit)
{
	jLOG(jFUNC1 _T("col=%d, row =%d  %s") ,col,row,string);
	CUGCell cell;
	GetCell(col,row,&cell);
	jIVar* pvValue = peCell->GetAttrVar(jS(Value));
	if(!pvValue)return FALSE;
	pvValue->FromString(string);

	jIVar* pvMinMax= peCell->GetAttrVar(jS(MinMax));
	if(pvMinMax)
	{
		if(pvValue->IsType(jIVar::EDint))
		{
			int iVal = pvValue->Get_int();
			if(iVal > pvMinMax->GetInt(1))
				iVal = pvMinMax->GetInt(1);
			if(iVal < pvMinMax->GetInt(0))
				iVal = pvMinMax->GetInt(0);

			if(pvValue->Get_int() ==iVal)
				return false;
			pvValue->Set_int(iVal);
		}
		else if(pvValue->IsType(jIVar::EDfloat))
		{
			float iVal = pvValue->Get_float();
			if(iVal > pvMinMax->GetFloat(1))
				iVal = pvMinMax->GetFloat(1);
			if(iVal < pvMinMax->GetFloat(0))
				iVal = pvMinMax->GetFloat(0);

			if(pvValue->Get_float() ==iVal)
				return false;
			pvValue->Set_float(iVal);
		}
	}
	fname_t szBuf;
	pvValue->ToString(szBuf);
	if(edit)
	{
		//cell.SetText(szBuf);
		//SetCell(col,row,&cell);
		edit->SetWindowText(szBuf);
	}
	cstr szName = find_event_name(peCell);
	if(!szName) 
		return TRUE;

	__jGRIDCRTL_EVENT_handler* pF = get_Handler(szName,col,row);
	long ID=0;
	if(pF){	return pF->Call(this, peCell,0,col,row,0,jGRIDCTRL_CELLTYPE_IS_EDITABLE);}

	return TRUE;
}


