/* file : jGridCtrl_SQ.cpp
Coder : by icandoit ( chowookrea@hotmail.com)
Date : 2011-04-25 22:16:15
comp.: rocworks.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "jGridCtrl.h"
#include "interface/Squirrel/jISquirrel.h"
#include "base/jSQ_bind.h"

void jGridCtrl::resetCell(int startRow, int endRow, int startCol, int endCol)
{
	this->ResetCells(startRow, endRow, startCol, endCol);
}

void jGridCtrl::setColWidth(int col,int w)
{
	SetColWidth(col , w);
	RedrawAll();
}
void jGridCtrl::setRowHeight(int row, int h)
{
	SetRowHeight(row , h);
	RedrawAll();
}


int jGridCtrl::GetColNum()
{
	
	return CUGCtrl::GetNumberCols();
}
int jGridCtrl::GetRowNum()
{
	return CUGCtrl::GetNumberRows();
}


void jGridCtrl::SetNumber(int c,int r,int Value)
{
	QuickSetNumber(c,r, Value);
}

void jGridCtrl::SetText(int c,int r,cstr Value)
{
	QuickSetText(c,r, Value);
}

void jGridCtrl::SetReadOnly(int c,int r,bool b)
{
	CUGCell cell;
	GetCell(c,r,&cell);
	cell.SetReadOnly(b);
	jIE* pE = GetCellXml(c,r);
	if(pE)
	{
		jIVar* pV = pE->PersistAttr(jS(ReadOnly),b);
		pV->Set_bool(b);
	}
	SetCell(c,r,&cell);
}
void jGridCtrl::SetNumberPos(cstr szPos,int Value)
{
	POINT po = GetNamedCellPOINT(szPos);
	QuickSetNumber(jPO, Value);
}

void jGridCtrl::SetTextPos(cstr szPos,cstr Value)
{
	POINT po = GetNamedCellPOINT(szPos);
	QuickSetText(jPO, Value);
}

void jGridCtrl::SetReadOnlyPos(cstr szPos,bool b)
{
	POINT po = GetNamedCellPOINT(szPos);
	CUGCell cell;
	GetCell(jPO,&cell);
	cell.SetReadOnly(b);
	SetCell(jPO,&cell);
	cell.SetParam(jGRIDCTRL_CELLTYPE_IS_EDITABLE);

}

void jGridCtrl::joinCells(int startCol,long startRow,int endCol,long endRow)
{
	parent_t::JoinCells(startCol,startRow,endCol,endRow);
}
DECLARE_INSTANCE_TYPE(jIGridCtrl);


//jSQ_REGIST_BIND(tool_Grid_lib)
void init_tool_Grid_lib()
{
	static bool is=false;
	if(is)return;
	is=true;

	jSQ_Interface(jIGridCtrl)
		jSQ_fn(SetNumber,"int Col,int Row,int Value","");
		jSQ_fn(SetText,"int Col,int Row,cstr Value","");
		jSQ_fn(SetReadOnly,"int Col,int Row,bool Value","");
		jSQ_fn(SetNumberPos,"cstr NamedCellList,int Value","");
		jSQ_fn(SetTextPos,"cstr NamedCellList,cstr Value","");
		jSQ_fn(SetReadOnlyPos,"cstr NamedCellList,bool Value","");
		jSQ_fn(GetColNum,"int ()","");
		jSQ_fn(GetRowNum,"int ()","");
		jSQ_fn(setColWidth,"(int col,int width)","");
		jSQ_fn(setRowHeight,"void (int row, int h)","");
		jSQ_fn(resetCell,"(int row, int h)","");
		jSQ_fn(joinCells,"(int startCol,long startRow,int endCol,long endRow)","");
		
		

	jSQ_end();

	jSQ_g_var((jIGridCtrl*)g_jGridCtrl,g_UGrid);
}

