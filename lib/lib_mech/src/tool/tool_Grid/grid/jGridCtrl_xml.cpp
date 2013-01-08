/* file : jGridCtrl_xml.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-26 22:59:48
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "resource.h"
#include "jGridCtrl.h"
#include <ugxpthemes.h>
#include "interface/Squirrel/jISquirrel.h"
#include "header/uString_stl.h"


int getFlag_UGCT_PROGRESS(jIVar* pV)
{
#define for_each_UGCT_PROGRESS(X)\
		X(TOP)\
		X(LEFT)\
		X(RIGHT)\
		X(BOTTOM)\

#define check_UGCT_PROGRESS(X) else if(jt_strstr(pV->Get_cstr(), jS(X))) flag= UGCT_PROGRESS_##X;

	int flag=UGCT_PROGRESS_LEFT;
	if(0){}
	for_each_UGCT_PROGRESS(check_UGCT_PROGRESS);
	return flag;
}


COLORREF getSystemColor(jIVar* pV)
{
	if(pV->IsType(jIVar::EDcstr))
	{
	}
	else
	{
		COLORREF color = RGB(pV->GetInt(0),pV->GetInt(1),pV->GetInt(2) ) ;
		return color;
	}

#define for_each_SYS_COLOR(X)\
	X(SCROLLBAR)\
	X(BACKGROUND)\
	X(ACTIVECAPTION)\
	X(INACTIVECAPTION)\
	X(MENU)\
	X(WINDOW)\
	X(WINDOWFRAME)\
	X(MENUTEXT)\
	X(WINDOWTEXT)\
	X(CAPTIONTEXT)\
	X(ACTIVEBORDER)\
	X(INACTIVEBORDER)\
	X(APPWORKSPACE)\
	X(HIGHLIGHT)\
	X(HIGHLIGHTTEXT)\
	X(BTNFACE)\
	X(BTNSHADOW)\
	X(GRAYTEXT)\
	X(BTNTEXT)\
	X(INACTIVECAPTIONTEXT)\
	X(BTNHIGHLIGHT)\

#define check_sys_color432(X) if(pV->IsContents(jS(X)))return GetSysColor(COLOR_##X);
	for_each_SYS_COLOR(check_sys_color432)
		return 0;
}


int getFlag_UGCT_NORMAL(cstr sz)
{
	int flag=0;

#define for_each_UGCT_NORMAL(X)\
	X(SINGLELINE)\
	X(MULTILINE)\
	X(ELLIPSIS)\
	X(LABELTEXT)\

#define check_UG_3464(X) else if(jt_strstr(sz, jS(X)) ){ flag |= UGCT_NORMAL##X;}
	if(0){}
	for_each_UGCT_NORMAL(check_UG_3464);
	if(jt_strstr(sz , jS(NOFOCUS)))
		flag |= UGCT_BUTTONNOFOCUS;
	return flag;
}

int getFlag_UG_ALIGN(cstr sz)
{
	int flag=0;
#define for_each_UG_ALIGN(X)\
	X(LEFT)\
	X(RIGHT)\
	X(CENTER)\
	X(TOP)\
	X(BOTTOM)\
	X(VCENTER)\

#define check_UG_ALIGN(X) if(jt_strstr(sz , jS(X)) ){ flag |= UG_ALIGN##X;}
	for_each_UG_ALIGN(check_UG_ALIGN);

	return flag;
}


/////////////////////////////////////////////////////////////////////////////
//	OnSetup
//		This function is called just after the grid window 
//		is created or attached to a dialog item.
//		It can be used to initially setup the grid
#define call_func342(NAME) else if( it->IsName(jS(NAME)) ) xml_##NAME(it,__cell);

void jGridCtrl::OnSetup()
{
	CUGCell __cell;
	jIE* peCUGCellType = m_peGrid->Find( jS(CUGCellType) );
	if(!peCUGCellType)
	{
		peCUGCellType = m_peGrid->InsertChildElement(jS(CUGCellType));
	}

#define add_default_CUGCellType13(X)\
	{\
		if(!peCUGCellType->Find(jS(X)))\
		{\
			nXML::jE eType = peCUGCellType->InsertChildElement(jS(X) );\
			eType.AttrP(jS(NAME)).T() = jS(X);\
		}\
	}\

	for_each_default_CUGCellType(add_default_CUGCellType13);

	{
		jIE* peTemp = m_peGrid->Find( jS(CUGCellType) );
		assert(peTemp== peCUGCellType);


		if(peCUGCellType)
		{
			jIE* it = peCUGCellType->begin();
			jrFOR(it)
			{
				#define add_CUGCellType13(X)\
				else if(it->IsName(jS(X)))\
				{\
					if(!m_mapCUGCellType.count(jAT_s(NAME)))\
					{\
						CUGCellType* p = new X;\
						int idx = AddCellType(p);\
						typecell_t t;\
						t.cell_type_index=idx;t.pCellType=p;t.pE = it;\
						m_mapCUGCellType[jAT_s(NAME)] = t;\
					}\
				}\

				if(0){}
				for_each_default_CUGCellType(add_CUGCellType13)
				else{jERROR(  _T("unkown type= %s"),it->GetTagName());}
			}
		}
	}
	jIE* it = m_peGrid;
	jIVar* pV;

	jAT_IF(Size)
	{
		if(pV->GetInt(0)>0)
			SetNumberCols(pV->GetInt(0));

		if(pV->GetInt(1)>0)
			SetNumberRows(pV->GetInt(1));
	}

	jAT_IF(Side_Title_Size)
	{
		if(pV->GetInt(0)>0)
			SetSH_Width(pV->GetInt(0));

		if(pV->GetInt(1)>0)
			SetTH_Height(pV->GetInt(1));
	}
	jAT_IF(DoubleBuffer)
	{
		SetDoubleBufferMode(pV->Get_bool());
	}
	jAT_IF(MultiSelectMode)
	{
		SetMultiSelectMode(pV->Get_bool());
	}

	it = m_peGrid->begin();
	jrFOR(it)
	{
		jAT_IF(ENABLE)
		{
			if(pV->Get_bool()==false)
				continue;
		}
		//jLOG(jFUNC1 _T("it =%s") , it->GetTagName());

		if(0){}
		for_each_XML_FUNC(call_func342)
		else
		{
			jERROR(  _T("unknown func: %s"),it->GetTagName() );
		}

	}

	CUGEdit* editClass = (CUGEdit*)this->GetEditClass();
	editClass->SetAutoSize(FALSE);

	EnableMenu( TRUE );

}


jGridCtrl_XML_FUNC(GROUP)
{
	it = it->begin();
	jrFOR(it)
	{
		jIVar* pV;
		jAT_IF(ENABLE)
		{
			if(pV->Get_bool()==false)
				continue;
		}

		//jLOG(jFUNC1 _T("it =%s") , it->GetTagName());
		if(0){}
		for_each_XML_FUNC(call_func342)
		else
		{
			jERROR(  _T("unknown func: %s"),it->GetTagName() );
		}
	}
}

POINT jGridCtrl::_GetColRow(jIE* it,cstr sz,jIVar** ppV)
{
	if(ppV) *ppV=0;
	POINT po;
	po.x=jNULL_PO;
	po.y=jNULL_PO;
	jIVar* pV= it->GetAttrVar(sz);
	if(pV->IsType(jIVar::EDcstr))
	{
		jIE* pE = m_peGrid->Find(jS(NamedCellList));
		jRETURN_ret(po,pE);
		pV = pE->Find(pV->Get_cstr())->GetVar();
		jRETURN_ret(po,pV);
	}
	po.x = pV->GetInt(0);
	po.y = pV->GetInt(1);
	if(ppV)*ppV = pV;
	return po;
}


jGridCtrl_XML_FUNC(SetGridDefault)
{
	jIVar* pV = it->GetAttrVar(jS(ReadOnly));
	if(pV)
	{
		BOOL is = pV->Get_bool();
		__cell.SetReadOnly(is);
	}

	SetGridDefault(&__cell);
}

jGridCtrl_XML_FUNC(JoinCells)
{
	POINT po = _GetColRow(it,jS(StartColRow));
	jRETURN(po.x!=jNULL_PO);
	POINT pe = _GetColRow(it,jS(EndColRow));
	jRETURN(pe.x!=jNULL_PO);

	JoinCells(jPO, pe.x,pe.y);
}

jGridCtrl_XML_FUNC(CUGCellType)
{

}
jGridCtrl_XML_FUNC(ExpandCell)
{
	xml_Cell(it,__cell);
	jIVar* pvPOS=0;
	POINT po = _GetColRow(it,jS(ColRow), &pvPOS);
	jIVar* pV ;
	jRETURN(po.x!=jNULL_PO);

	CUGCell _cell;
	GetCell(jPO , &_cell);

	typecell_t& tc = m_mapCUGCellType[jS(CUGExpandType)];
	int idx = tc.cell_type_index;
	_cell.SetCellType(idx);

	SetCell(jPO,&_cell);

	jAT_IF(Rows)
	{
		if(pV->Get_int() > 0)
			jCELL_TYPE_p(CUGExpandType,CUGExpandType)->SetNumberOfRows(jPO, pV->Get_int());
	}
	jAT_IF(JoinCols)
	{
		int iCol = po.x;
		int iRow = po.y;
		int iCols = pV->Get_int();
		if(iCols < 0)
		{
			JoinCells(jPO , GetNumberCols() -1 ,  iRow);
		}
		else if(iCols >0)
		{
			JoinCells(jPO , iCol + iCols ,  iRow);
		}
	}
	jAT_IF(Font)
	{
		CFont* f = GetFont(pV->Get_cstr());
		if(f)
		{
			jCELL_TYPE_p(CUGExpandType,CUGExpandType)->m_pFont=f;
		}
	}

}

jGridCtrl_XML_FUNC(SetNumberOfRows)
{
	if(!m_mapCUGCellType.count(jAT_s(CellType))){jERROR(  _T("%s is not found") ,jAT_s(CellType) );return;}
	jRETURN(!m_mapCUGCellType[jAT_s(CellType)].pE->IsName(jS(CUGExpandType)) );
	int idx = m_mapCUGCellType[jAT_s(CellType)].cell_type_index;
	CUGExpandType* p = (CUGExpandType*)m_mapCUGCellType[jAT_s(CellType)].pCellType;
	int iRows =it->GetVar()->Get_int() ;
	if(iRows>0)
	{
		POINT po = _GetColRow(it,jS(ColRow));
		jRETURN(po.x!=jNULL_PO);
		p->SetNumberOfRows(jPO, iRows );
	}
}

jGridCtrl_XML_FUNC(NamedCellList)
{
	it = it->begin();
	jrFOR(it)
	{
		m_mapNamedCellList[it->GetTagName()] = jNamedCellList(it->GetVar() , it);
	}
}

jGridCtrl_XML_FUNC(SetReadOnly)
{
	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	jIVar* pV = it->PersistAttr(jS(ReadOnly),it->GetVar()->Get_bool());
	pV->Set_bool(it->GetVar()->Get_bool());

	CUGCell _cell;
	GetCell(jPO , &_cell);
	_cell.SetReadOnly(it->GetVar()->Get_bool());
	SetCell(jPO , &_cell);

}

jGridCtrl_XML_FUNC(SQScript)
{
	using namespace nSQ;
	try
	{
		SquirrelObject file = GetjISQ()->VM_CompileScript(it->Get_cstr());
		GetjISQ()->VM_RunScript(file);
	}
	jSQ_CATCH_ERROR();
}

jGridCtrl_XML_FUNC(XmlCreateFont)
{
	cstr szDefulat = it->GetAttr(jS(DEFAULT));
	it = it->begin();
	jrFOR(it)
	{
		CFont* f = new CFont;
		m_mapCFont[it->GetTagName()] = f;
		f->CreateFont(jAT_CR(HW) , 0,0,jAT_i(Weight) , jAT_i(Italic), jAT_i(Underline) , jAT_i(StrikeOut) ,0,0,0,0,0, jAT_s(FontName) );
		if(szDefulat && it->IsName(szDefulat))
		{
			SetDefFont( f);
			szDefulat=0;
		}
	}
}

jGridCtrl_XML_FUNC(SetUserSizingMode)
{
	if(it->IsContents(jS(NO)))
	{
		SetUserSizingMode(0);
	}
	else if(it->IsContents(jS(FINISHED)))
	{
		SetUserSizingMode(1);
	}
	else if(it->IsContents(jS(REALTIME)))
	{
		SetUserSizingMode(2);
	}
}

jGridCtrl_XML_FUNC(CellFont)
{
	CUGCell _cell;
	CFont* f = GetFont(it->Get_cstr());
	jRETURN(f);
	jIVar* pV = it->GetAttrVar(jS(NAME));
	if(pV->IsContents(_T("{Heading}")))
	{
		GetHeadingDefault(&_cell);
		_cell.SetFont(f);
		SetHeadingDefault(&_cell);
		return;
	}

	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);
	GetCell(jPO,&_cell);
	_cell.SetFont(f);
	SetCell(jPO,&_cell);

}

jGridCtrl_XML_FUNC(SetColWidth)
{
	int col = jAT_i(Col) ;
	if(col>=0)
		SetColWidth(col, it->GetVar()->Get_int());
	else
		SetDefColWidth(it->GetVar()->Get_int());
}

jGridCtrl_XML_FUNC(SetVScrollMode)
{
	jIVar* pV = it->GetVar();
	if(pV->IsContents(jS(NORMAL)))
		SetVScrollMode(UG_SCROLLNORMAL);
	else if(pV->IsContents(jS(TRACKING)))
		SetVScrollMode(UG_SCROLLTRACKING);
	else if(pV->IsContents(jS(JOYSTICK)))
		SetVScrollMode(UG_SCROLLJOYSTICK);
}


jGridCtrl_XML_FUNC(SetupSection)
{
	CUGCell _cell;
	int row = jAT_i(Row) ;
	jIVar* pV = jAT(BColor);
	if(pV->IsType(jIVar::EDint3) || !pV->IsContents(jS(NULL)))
		_cell.SetBackColor(getSystemColor(pV));
	pV = jAT(FColor);
	if(pV->IsType(jIVar::EDint3) || !pV->IsContents(jS(NULL)))
		_cell.SetTextColor(getSystemColor(pV));
	_cell.SetFont(GetFont(jAT_s(Font) ));
	_cell.SetAlignment(UG_ALIGNVCENTER);
	jAT_IF(StartCol)
	{
		QuickSetRange(pV->Get_int(),row,GetNumberCols() - 1,row,&_cell);
	}
	else
	{
		QuickSetRange(0,row,GetNumberCols() - 1,row,&_cell);
	}

	if(jt_strlen(it->Get_cstr()) && !it->GetVar()->IsContents(jS(NULL)))
		QuickSetText(-1,row,it->Get_cstr());
}

jGridCtrl_XML_FUNC(SetRowHeight)
{
	SetRowHeight(jAT_i(Row) , it->GetVar()->Get_int());
}


jGridCtrl_XML_FUNC(SetAlignment)
{
	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);
	QuickSetAlignment(jPO , getFlag_UG_ALIGN(it->Get_cstr() ) );
}


jGridCtrl_XML_FUNC(SetCellTypeEx)
{
	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	QuickSetCellTypeEx(jPO , getFlag_UGCT_NORMAL(it->Get_cstr()) );
}


jGridCtrl_XML_FUNC(Cell)
{
	tcstr sz;
	jIVar* pvPOS=0;
	POINT po = _GetColRow(it,jS(ColRow), &pvPOS);
	jIVar* pV ;
	jRETURN(po.x!=jNULL_PO);

	CUGCell _cell;
	GetCell(jPO , &_cell);

	jAT_IF(DropList)
	{
		_cell.ClearAll();
		_cell.SetCellType(UGCT_DROPLIST);
		tstring str = pV->Get_cstr();
		nSTL::replace(str,_T("|") , _T("\n") );
		_cell.SetLabelText(str.c_str());
	}

	jAT_IF(CheckBoxType)
	{
		//
		int flag = getFlag_UGCT_CHECKBOX(pV);
		_cell.SetCellType(UGCT_CHECKBOX);
		_cell.SetCellTypeEx(flag);
		jAT_IF(Value)
		{
			tname1024_t szBuf;
			pV->ToString(szBuf);
			_cell.SetLabelText(szBuf);
		}
	}
	else
	{
		jAT_IF(Value)
		{
			switch(pV->GetType())
			{
			case jIVar::EDint:
				{
					_cell.SetNumber(pV->Get_int());
					break;
				}
			case jIVar::EDfloat:
				{
					_cell.SetNumber(pV->Get_float());
					break;
				}
			case jIVar::EDcstr:
				{
					tstring str = pV->Get_cstr();
					nSTL::replace(str,_T("\\n") , _T("\n"));
					_cell.SetText( str.c_str() );
					break;
				}
			}
		}
	}


	jAT_IF(CellTypeEx)
	{
		_cell.SetCellTypeEx(getFlag_UGCT_NORMAL(pV->Get_cstr()) );
	}
	jAT_IF(Alignment)
	{
		_cell.SetAlignment(getFlag_UG_ALIGN(pV->Get_cstr() ) );
	}
	jAT_IF(TColor)
	{
		if(pV->IsType(jIVar::EDint3) || !pV->IsContents(jS(NULL)))
			_cell.SetTextColor(getSystemColor(pV));
	}
	jAT_IF(BColor)
	{
		if(pV->IsType(jIVar::EDint3) || !pV->IsContents(jS(NULL)))
			_cell.SetBackColor(getSystemColor(pV));
	}
	jAT_IF(Border)
	{
		int flag = getFlag_UG_BDR(pV->Get_cstr());
		_cell.SetBorder(flag);
	}
	jAT_IF(CellType)
	{
		_cell.SetCellType(GetCellTypeIndex(pV->Get_cstr()));
	}
	jAT_IF(Editable)
	{
		if(pV->Get_bool())
			_cell.SetParam(jGRIDCTRL_CELLTYPE_IS_EDITABLE);
	}
	tstring str ;
	jAT_IF(Note)
	{
		_cell.SetCellType(jCELL_TYPE_i(CUGNoteType));
		tstring str  =pV->Get_cstr();
		nSTL::replace(str, _T("\\r\\n") , _T("\r\n"));
		_cell.SetLabelText(str.c_str());
	}
	jAT_IF(Label)
	{
		if(!it->GetAttrVar(jS(Note)))
		{
			_cell.SetCellType(jCELL_TYPE_i(CUGLabeledType));
			tstring str  =pV->Get_cstr();
			nSTL::replace(str, _T("\\r\\n") , _T("\r\n"));
			_cell.SetLabelText(str.c_str());

		}
	}
	jAT_IF(ReadOnly)
	{
		_cell.SetReadOnly(pV->Get_bool());
	}
	jAT_IF(Font)
	{
		CFont* f = GetFont(pV->Get_cstr());
		if(f)
		{
			_cell.SetFont(f);
		}
	}
	jAT_IF(Name)
	{
		m_mapNamedCellList[pV->Get_cstr()] = jNamedCellList(pvPOS,it);
	}

	jIE* pE = it->Find(jS(DropList));
	if(pE)
	{
		//_cell.SetParam(pE->GetHandle());
		_cell.SetCellType(UGCT_DROPLIST);
	}
	/*
	pE = it->Find(jS(Radio));
	if(pE)
	{
		_cell.SetText(_T("1"));
		jIE* it1 = pE->begin();
		tstring str;
		jrFOR(it1)
		{
			cstr sz = it1->Get_cstr();
			jCONTINUE(sz);
			str += sz;
			str +=_T("\n");
		}
		_cell.SetLabelText(str.c_str() );
		_cell.SetCellType(jCELL_TYPE_i(CUGRadioType));
	}

	pE = it->Find(jS(MultiFont));

	if(pE)
	{
		if(pE->size())
		{
			_cell.SetCellType(jCELL_TYPE_i(CUGMultiFontType));
		}
		jIE* it= pE->begin();
		tname1024_t buf;
		tstring str;
		jrFOR(it)
		{
			jAT_IF(Font)
			{
				if(str.size() && str[str.size()-1]=='>')
				{
					str+=_T(" ");
				}
				jt_sprintf(buf,_T(" <:F,%s>"),pV->Get_cstr() );
				str +=buf;
			}
			jAT_IF(Color)
			{
				if(str.size() && str[str.size()-1]=='>')
				{
					str+=_T(" ");
				}
				jt_sprintf(buf,_T("<:C,%s>"),pV->Get_cstr() );
				str +=buf;
			}
			if(it->Get_cstr())
			{
				str +=it->Get_cstr();
			}
		}
		_cell.SetText(str.c_str());
	}


	SetCell(jPO , &_cell);

	int  pos = MAKELONG(po.x,po.y);
	short hi_x =  LOWORD(pos);
	short lw_y =  HIWORD(pos);
	assert(hi_x == po.x);
	assert(lw_y == po.y);

	m_mapXmlCellList[pos] = it;

*/
}


int getFlag_UGCT_CHECKBOX(jIVar* pV)
{
#define for_each_UGCT_CHECKBOX(X)\
	X(FLAT)\
	X(CROSS)\
	X(3DRECESS)\
	X(3DRAISED)\
	X(ROUND)\
	X(USEALIGN)\
	X(CHECKMARK)\
	X(3STATE)\
	X(DISABLED)\

	if(!pV) return 0;
	if(pV->IsType(jIVar::EDint) ) return pV->Get_int();
	int flag=0;
	#define conf_UGCT_CHECKBOX(X) if(jt_strstr(pV->Get_cstr(),jS(X) ) ) flag |= UGCT_CHECKBOX##X;
	for_each_UGCT_CHECKBOX(conf_UGCT_CHECKBOX);
	return flag;
}

jGridCtrl_XML_FUNC(CheckBox)
{
	xml_Cell(it,__cell);

	jIVar* pV;
	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	int flag =0;
	pV = jAT(Type);
	if(pV)
	{
		flag = getFlag_UGCT_CHECKBOX(pV);
	}

	bool isVertical=true;
	jAT_IF(Vertical)
	{
		isVertical = pV->Get_bool();
	}
	jIE* pE = it->begin();
	int idx=1;
	jrFOR(pE)
	{
		nXML::jE e = pE;
		jVar v = e.AttrP(jS(ColRow));
		v->SetType(jIVar::EDint2);
		if(isVertical)
		{
			v->GetInt(0)=po.x;
			v->GetInt(1)=po.y+idx;
		}
		else
		{
			v->GetInt(0)=po.x+idx;
			v->GetInt(1)=po.y;
		}

		++idx;
		e.AttrP(jS(CheckBoxType)).T()=flag;
		if(v->GetInt(0) >= GetNumberCols())
			continue;
		if(v->GetInt(1) >= GetNumberRows())
			continue;

		nXML::jIAttributeList* pList = it->GetAttributeList();
		nXML::jIAttributeList::iterator itA = pList->begin() , ieA = pList->end();
		for(; itA!=ieA ; ++itA)
		{
			if( e.Attr(itA->GetTagName()).full() ) continue;
			e.AttrP(itA->GetTagName()).T() = itA->GetVar();
		}

		xml_Cell(pE,__cell);
	}
}

jGridCtrl_XML_FUNC(Button)
{
	xml_Cell(it,__cell);
	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	CUGCell _cell;
	GetCell(jPO , &_cell);
	_cell.SetCellType(jCELL_TYPE_i(CUGButtonType));
	_cell.SetBackColor(GetSysColor(COLOR_BTNFACE));
	//_cell.SetParam(it->GetHandle());
	SetCell( jPO , &_cell);
}


jGridCtrl_XML_FUNC(EllipsisButton)
{
	xml_Cell(it,__cell);

	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	CUGCell _cell;
	GetCell(jPO , &_cell);
	_cell.SetCellType(jCELL_TYPE_i(CUGEllipsisType));
	//_cell.SetParam(it->GetHandle());

	SetCell( jPO , &_cell);
}


jGridCtrl_XML_FUNC(SpinButton)
{
	xml_Cell(it,__cell);

	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	CUGCell _cell;
	GetCell(jPO , &_cell);
	_cell.SetCellType(jCELL_TYPE_i(CUGSpinButtonType));
	//_cell.SetParam(it->GetHandle());
	_cell.SetReadOnly(FALSE);
	jIVar* pV = it->PersistAttr(jS(ReadOnly),false);
	pV->Set_bool(false);
	SetCell( jPO , &_cell);

}

jGridCtrl_XML_FUNC(Slider)
{
	xml_Cell(it,__cell);

	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	CUGCell _cell;
	GetCell(jPO , &_cell);
	_cell.SetCellType(jCELL_TYPE_i(CUGSliderType));
	SetCell( jPO , &_cell);

	jIE* pE = it->Find(jS(TextLabel));
	if(pE)
	{
		jIVar* pvValue = it->GetAttrVar(jS(Value));
		fname_t sz;
		pvValue->FromString(sz);
		pE->PersistAttr(jS(Value) , pvValue->GetType(), sz);
		xml_Cell(pE,__cell);
	}
}

jGridCtrl_XML_FUNC(ProgressBar)
{
	jIVar* pV;
	xml_Cell(it,__cell);

	POINT po = _GetColRow(it,jS(ColRow));
	jRETURN(po.x!=jNULL_PO);

	cstr szName = jAT_s(Name);

	jIE* peCUGCellType= m_peGrid->Find( jS(CUGCellType) );
	jIE* peType = peCUGCellType->Find(szName);
	typecell_t t;
	CUGAdvProgressType* p =0;
	if(!peType)
	{
		int ii = peCUGCellType->size();
		peType = peCUGCellType->InsertChildElement(jS(CUGAdvProgressType));
		assert( (ii +1) ==peCUGCellType->size());
		peType->PersistAttr(jS(NAME) , szName);
		p = new CUGAdvProgressType;
		t.cell_type_index=AddCellType(p);
		t.pCellType=p;
		t.pE = peType;
		m_mapCUGCellType[szName] = t;
	}
	else
	{
		t = m_mapCUGCellType[szName];
		if(t.pE->GetAttrVar(jS(NAME))->IsContents(jS(CUGAdvProgressType)) )
		{
			p = (CUGAdvProgressType*)t.pCellType;
		}
	}


	CUGCell _cell;
	GetCell(jPO , &_cell);
	_cell.SetCellType(t.cell_type_index);
	_cell.UseThemes(true);

	jAT_IF(LabelText)
	{
		if(jt_strlen(pV->Get_cstr()))
		{
			_cell.SetLabelText(pV->Get_cstr());
			_cell.SetCellTypeEx(UGCT_PROGRESSUSELABEL);
		}
	}
	jAT_IF(ProgressDir)
	{
		int flag = getFlag_UGCT_PROGRESS(pV);
		p->SetDirection(flag);
	}
	jAT_IF(Adjust)
	{
		p->SetCanAdjust(pV->Get_bool());
	}
	jAT_IF(NumberSections)
	{
		if(pV->Get_int()>0)
			p->SetNumberSections(pV->Get_int());
	}
	SetCell( jPO , &_cell);
}
jGridCtrl_XML_FUNC(Config)
{

}


/*
jGridCtrl_XML_FUNC(SetNumberOfRows)
{

}

*/
