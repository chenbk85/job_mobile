#ifndef __CTVVector_H__
#define __CTVVector_H__

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#include "define.h"

#pragma warning(disable : 4786)


#include <list>
#include <vector>
#include <map>
using namespace std;

typedef struct tagLineCol{
public:
	tagLineCol(void){ m_nLineCol=0; }
	tagLineCol(int nLineCol){ m_nLineCol=nLineCol; }
	tagLineCol(short sLine, short sCol){ m_tLineCol.sLine=sLine; m_tLineCol.sCol=sCol; }
	tagLineCol(char cLine1, char cCol1, char cLine2, char cCol2){ m_tLineCol12.cLine1=cLine1; m_tLineCol12.cCol1=cCol1; m_tLineCol12.cLine2=cLine2; m_tLineCol12.cCol2=cCol2; }
public:
	void SetLineCol(int nLineCol){ m_nLineCol=nLineCol; }
	void SetLineCol(short sLine, short sCol){ m_tLineCol.sLine=sLine; m_tLineCol.sCol=sCol; }
	void SetLineCol(char cLine1, char cCol1, char cLine2, char cCol2){ m_tLineCol12.cLine1=cLine1; m_tLineCol12.cCol1=cCol1; m_tLineCol12.cLine2=cLine2; m_tLineCol12.cCol2=cCol2; }
	void SwapLineColShort(void){
		short sTemp=m_tLineCol.sLine;
		m_tLineCol.sLine=m_tLineCol.sCol; m_tLineCol.sCol=sTemp;
	}
	void SwapLineColChar(void){ 
		char sTempL=m_tLineCol12.cLine1; char sTempC=m_tLineCol12.cCol1; 
		m_tLineCol12.cLine1=m_tLineCol12.cLine2; m_tLineCol12.cLine2=sTempL;
		m_tLineCol12.cCol1=m_tLineCol12.cCol2; m_tLineCol12.cCol2=sTempC;
	}
public:
	union{
		int m_nLineCol;
		struct{
			short int sLine;
			short int sCol;
		}m_tLineCol;
		struct{
			char cLine1;
			char cCol1;
			char cLine2;
			char cCol2;
		}m_tLineCol12;
	};
}tLineCol;

template <typename TYPE>
class CTVVector : public vector<vector<TYPE> >
{
public:
public:
	CTVVector(void){ InitTVVector(); }
	virtual ~CTVVector(void){ FreeTVVector(); }
	void InitTVVector(void){}
	void FreeTVVector(void){ DelVector(); }
	int OverArray(int nLine){ return max(0, nLine-((int)size()-1)); }
	int OverArray(int nLine, int nCol){
		if((0<=nLine)&&(((int)(*this).size()-1)>=nLine)){
			return max(0, nCol-((int)(*this)[nLine].size()-1));
		}
		return 0;
	}
	bool IsUsableArray(int nLine){ return ((0<=nLine)&&((int)size()>nLine)); }
	bool IsUsableArray(int nLine, int nCol){
		if((0<=nLine)&&(((int)size()-1)>=nLine)){
			return ((0<=nCol)&&(((int)(*this)[nLine].size()-1)>=nCol));
		}
		return false;
	}
	bool IsEmpty(void){ return (bool)empty(); }
	bool IsEmpty(int nLine){
		if((0<=nLine)&&(((int)size()-1)>=nLine)){
			return (*this)[nLine].empty();
		}
		return true;
	}
public:
	bool CreateVector(int nLine);
	bool CreateVector(int nLine, int nCol);
	bool CreateVector(int nLine, int nCol, TYPE Type);
	int AddVector(int nLine, TYPE Type);
	int AddVector(int nLine, TYPE** ppType);
	int AddVector(int nLine, TYPE Type, TYPE** ppType);
	bool InsertVector(int nLine, int nCol, TYPE Type);
	bool ChangeVector(int nLine, int nCol, TYPE Type);
	bool SwapVector(int nLine1, int nCol1, int nLine2, int nCol2);
	bool MoveVector(int nLine1, int nCol1, int nLine2, int nCol2);
	tLineCol FindBeginVector(TYPE Type);
	tLineCol FindBeginVector(TYPE Type, TYPE** ppType);
	tLineCol FindEndVector(TYPE Type);
	tLineCol FindEndVector(TYPE Type, TYPE** ppType);
	int FindBeginVector(int nLine, TYPE Type);
	int FindBeginVector(int nLine, TYPE Type, TYPE** ppType);
	int FindEndVector(int nLine, TYPE Type);
	int FindEndVector(int nLine, TYPE Type, TYPE** ppType);
	tLineCol FindBeginDelVector(TYPE Type);
	tLineCol FindEndDelVector(TYPE Type);
	int FindBeginDelVector(int nLine, TYPE Type);
	int FindEndDelVector(int nLine, TYPE Type);
	tLineCol FindBeginClearVector(TYPE Type, TYPE TypeClear);
	tLineCol FindEndClearVector(TYPE Type, TYPE TypeClear);
	int FindBeginClearVector(int nLine, TYPE Type, TYPE TypeClear);
	int FindEndClearVector(int nLine, TYPE Type, TYPE TypeClear);
	bool DelVector(int nLine, int nCol);
	bool DelVector(int nLine);
	void DelVector(void);
	int TotalVector(void);
	bool TotalVector(int nLine, int &Total);
public:
	bool GetVector(int nLine, int nCol, TYPE &Type);
	bool GetVectorPtr(int nLine, int nCol, TYPE** ppType);
	bool GetVectorPtr(int nLine, vector<TYPE>** ppvType);
	bool GetVectorLine(int nLine, vector<TYPE>* pvType);
	bool GetVectorCol(int nCol, vector<TYPE>* pvType);
public:
	void SetVector(TYPE Type);
public:
	void NonZeroLineColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type);
	void SumLineColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol);
	int SumLineVector(int nCol, int nStartLine, int nEndLine);
	int SumColVector(int nLine, int nStartCol, int nEndCol);
	int SumLineColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol);
	void SumLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet);
	void SumColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet);
	void SumLineColVectorBegin(void);
	void SumLineColVectorEnd(void);
	void SumLineVectorBegin(void);
	void SumColVectorBegin(void);
	void SumLineVectorEnd(void);
	void SumColVectorEnd(void);
	tLineCol ContinueLineVectorBegin(TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueColVectorBegin(TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueLineVectorEnd(TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueColVectorEnd(TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueLineColsVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueColLinesVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueFillLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueFillColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueFillLineColsVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	tLineCol ContinueFillColLinesVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame=true, vector<tLineCol>* pvtLineCol=NULL);
	int ContinueLineToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, int nCol, TYPE Type, bool bTypeSame=true, bool bLooping=true, tLineCol* ptLineCol=NULL, vector<tLineCol>* pvtLineCol=NULL);
	int ContinueColToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, int nCol, TYPE Type, bool bTypeSame=true, bool bLooping=true, tLineCol* ptLineCol=NULL, vector<tLineCol>* pvtLineCol=NULL);
	void ContinueLinesToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nCol, TYPE Type, bool bTypeSame=true, bool bLooping=true, vector<tLineCol>* pvtLineCol=NULL);
	void ContinueColsToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, TYPE Type, bool bTypeSame=true, bool bLooping=true, vector<tLineCol>* pvtLineCol=NULL);
	void ContinueFillLinesToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nCol, TYPE Type, bool bTypeSame=true, bool bLooping=true, vector<tLineCol>* pvtLineCol=NULL);
	void ContinueFillColsToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, TYPE Type, bool bTypeSame=true, bool bLooping=true, vector<tLineCol>* pvtLineCol=NULL);
	void ContinueDiffLinesToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nCol, int nDiffCnt, TYPE Type, bool bTypeSame=true, bool bLooping=true, vector<tLineCol>* pvtLineCol=NULL);
	void ContinueDiffColsToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, int nDiffCnt, TYPE Type, bool bTypeSame=true, bool bLooping=true, vector<tLineCol>* pvtLineCol=NULL);
};
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::CreateVector(int nLine)
{
	if(0>=nLine) return false;
	DelVector();
	vector<TYPE> vVector;
	for(int i=0; i<nLine; i++){
		push_back(vVector);
	}
	return (nLine==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::CreateVector(int nLine, int nCol)
{
	if(0>=nLine) return false;
	if(0>=nCol) return false;
	DelVector();
	TYPE Type;
	vector<TYPE> vVector;
	for(int i=0; i<nLine; i++){
		push_back(vVector);
		for(int j=0; j<nCol; j++){
			(*this)[i].push_back(Type);
		}
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::CreateVector(int nLine, int nCol, TYPE Type)
{
	if(0>=nLine) return false;
	if(0>=nCol) return false;
	DelVector();
	vector<TYPE> vVector;
	for(int i=0; i<nLine; i++){
		push_back(vVector);
		for(int j=0; j<nCol; j++){
			(*this)[i].push_back(Type);
		}
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::AddVector(int nLine, TYPE Type)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	int nCol=(int)(*this)[nLine].size();
	(*this)[nLine].push_back(Type);
	return nCol;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::AddVector(int nLine, TYPE** ppType)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	int nCol=(int)(*this)[nLine].size();
	TYPE Type;
	(*this)[nLine].push_back(Type);
	if(NULL!=ppType) (*ppType)=&(*this)[nLine][nCol];
	return nCol;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::AddVector(int nLine, TYPE Type, TYPE** ppType)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	int nCol=(int)(*this)[nLine].size();
	(*this)[nLine].push_back(Type);
	if(NULL!=ppType) (*ppType)=&(*this)[nLine][nCol];
	return nCol;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::InsertVector(int nLine, int nCol, TYPE Type)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	if((0>nCol)||((int)(*this)[nLine].size()<=nCol)) return false;
	(*this)[nLine].insert((*this)[nLine].begin()+nCol, Type);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::ChangeVector(int nLine, int nCol, TYPE Type)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	if((0>nCol)||((int)(*this)[nLine].size()<=nCol)) return false;
	(*this)[nLine][nCol]=Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::SwapVector(int nLine1, int nCol1, int nLine2, int nCol2)
{
	if((0>nLine1)||((int)size()<=nLine1)) return false;
	if((0>nCol1)||((int)(*this)[nLine1].size()<=nCol1)) return false;
	if((0>nLine2)||((int)size()<=nLine2)) return false;
	if((0>nCol2)||((int)(*this)[nLine2].size()<=nCol2)) return false;
	TYPE Type=(*this)[nLine1][nCol1];
	(*this)[nLine1][nCol1]=(*this)[nLine2][nCol2];
	(*this)[nLine2][nCol2]=Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::MoveVector(int nLine1, int nCol1, int nLine2, int nCol2)
{
	if((0>nLine1)||((int)size()<=nLine1)) return false;
	if((0>nCol1)||((int)(*this)[nLine1].size()<=nCol1)) return false;
	if((0>nLine2)||((int)size()<=nLine2)) return false;
	if((0>nCol2)||((int)(*this)[nLine2].size()<=nCol2)) return false;
	TYPE Type=(*this)[nLine2][nCol2];
	if(nLine1==nLine2){
		if(nCol2>nCol1){
			erase((*this)[nLine2].begin()+nCol2);
			insert((*this)[nLine1].begin()+nCol1, Type);
		}
		else{
			insert((*this)[nLine1].begin()+nCol1, Type);
			erase((*this)[nLine2].begin()+nCol2);
		}
	}
	else{
		insert((*this)[nLine1].begin()+nCol1, Type);
		erase((*this)[nLine2].begin()+nCol2);
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindBeginVector(TYPE Type)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::iterator vtIteraterLine;
	vector<TYPE>::iterator vtIteraterCol;
	for(vtIteraterLine=(*this).begin(); vtIteraterLine!=(*this).end(); vtIteraterLine++){
		for(vtIteraterCol=vtIteraterLine->begin(); vtIteraterCol!=vtIteraterLine->end(); vtIteraterCol++){
			if(Type==(*vtIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)(vtIteraterLine-(*this).begin());
				tlc.m_tLineCol.sCol=(short int)(vtIteraterCol-vtIteraterLine->begin());
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindBeginVector(TYPE Type, TYPE** ppType)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::iterator vtIteraterLine;
	vector<TYPE>::iterator vtIteraterCol;
	for(vtIteraterLine=(*this).begin(); vtIteraterLine!=(*this).end(); vtIteraterLine++){
		for(vtIteraterCol=vtIteraterLine->begin(); vtIteraterCol!=vtIteraterLine->end(); vtIteraterCol++){
			if(Type==(*vtIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)(vtIteraterLine-(*this).begin());
				tlc.m_tLineCol.sCol=(short int)(vtIteraterCol-vtIteraterLine->begin());
				if(NULL!=ppType) (*ppType)=vtIteraterCol._Myptr;
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindEndVector(TYPE Type)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::reverse_iterator vtRIteraterLine;
	vector<TYPE>::reverse_iterator vtRIteraterCol;
	for(vtRIteraterLine=(*this).rbegin(); vtRIteraterLine!=(*this).rend(); vtRIteraterLine++){
		for(vtRIteraterCol=vtRIteraterLine.rbegin(); vtRIteraterCol!=vtRIteraterLine.rend(); vtRIteraterCol++){
			if(Type==(*vtRIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)((*this).rend()-vtRIteraterLine);
				tlc.m_tLineCol.sCol=(short int)(vtRIteraterLine.rend()-vtRIteraterCol);
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindEndVector(TYPE Type, TYPE** ppType)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::reverse_iterator vtRIteraterLine;
	vector<TYPE>::reverse_iterator vtRIteraterCol;
	vector<TYPE>::iterator vtIterater;
	for(vtRIteraterLine=(*this).rbegin(); vtRIteraterLine!=(*this).rend(); vtRIteraterLine++){
		for(vtRIteraterCol=vtRIteraterLine.rbegin(); vtRIteraterCol!=vtRIteraterLine.rend(); vtRIteraterCol++){
			if(Type==(*vtRIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)((*this).rend()-vtRIteraterLine);
				tlc.m_tLineCol.sCol=(short int)(vtRIteraterLine.rend()-vtRIteraterCol);
				vtIterater=vtRIteraterCol.base();
				if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindBeginVector(int nLine, TYPE Type)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=(*this)[nLine].begin(); vtIterater!=(*this)[nLine].end(); vtIterater++){
		if(Type==(*vtIterater)){
			return (int)(vtIterater-(*this)[nLine].begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindBeginVector(int nLine, TYPE Type, TYPE** ppType)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=(*this)[nLine].begin(); vtIterater!=(*this)[nLine].end(); vtIterater++){
		if(Type==(*vtIterater)){
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(vtIterater-(*this)[nLine].begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindEndVector(int nLine, TYPE Type)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=(*this)[nLine].rbegin(); vtRIterater!=(*this)[nLine].rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			return (int)((*this)[nLine].rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindEndVector(int nLine, TYPE Type, TYPE** ppType)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=(*this)[nLine].rbegin(); vtRIterater!=(*this)[nLine].rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)((*this)[nLine].rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindBeginDelVector(TYPE Type)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::iterator vtIteraterLine;
	vector<TYPE>::iterator vtIteraterCol;
	for(vtIteraterLine=(*this).begin(); vtIteraterLine!=(*this).end(); vtIteraterLine++){
		for(vtIteraterCol=vtIteraterLine->begin(); vtIteraterCol!=vtIteraterLine->end(); vtIteraterCol++){
			if(Type==(*vtIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)(vtIteraterLine-(*this).begin());
				tlc.m_tLineCol.sCol=(short int)(vtIteraterCol-vtIteraterLine->begin());
				vtIteraterCol=vtIteraterLine->erase(vtIteraterCol);
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindEndDelVector(TYPE Type)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::reverse_iterator vtRIteraterLine;
	vector<TYPE>::reverse_iterator vtRIteraterCol;
	vector<TYPE>::iterator vtIterater;
	for(vtRIteraterLine=(*this).rbegin(); vtRIteraterLine!=(*this).rend(); vtRIteraterLine++){
		for(vtRIteraterCol=vtRIteraterLine.rbegin(); vtRIteraterCol!=vtRIteraterLine.rend(); vtRIteraterCol++){
			if(Type==(*vtRIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)((*this).rend()-vtRIteraterLine);
				tlc.m_tLineCol.sCol=(short int)(vtRIteraterLine.rend()-vtRIteraterCol);
				vtIterater=vtRIteraterLine.erase(vtRIteraterCol);
				vtRIteraterCol=vector<TYPE>::reverse_iterator(vtIterater);
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindBeginDelVector(int nLine, TYPE Type)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	int nFind=0;
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=(*this)[nLine].begin(); vtIterater!=(*this)[nLine].end(); vtIterater++){
		if(Type==(*vtIterater)){
			nFind=(int)(vtIterater-(*this)[nLine].begin());
			vtIterater=(*this)[nLine].erase(vtIterater);
			return nFind;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindEndDelVector(int nLine, TYPE Type)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	int nFind=0;
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=(*this)[nLine].rbegin(); vtRIterater!=(*this)[nLine].rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			nFind=(int)((*this)[nLine].rend()-vtRIterater);
			vtIterater=vtRIterater.base();
			vtIterater=(*this)[nLine].erase(vtIterater);
			vtRIterater=vector<TYPE>::reverse_iterator(vtIterater);
			return nFind;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindBeginClearVector(TYPE Type, TYPE TypeClear)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::iterator vtIteraterLine;
	vector<TYPE>::iterator vtIteraterCol;
	for(vtIteraterLine=(*this).begin(); vtIteraterLine!=(*this).end(); vtIteraterLine++){
		for(vtIteraterCol=vtIteraterLine->begin(); vtIteraterCol!=vtIteraterLine->end(); vtIteraterCol++){
			if(Type==(*vtIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)(vtIteraterLine-(*this).begin());
				tlc.m_tLineCol.sCol=(short int)(vtIteraterCol-vtIteraterLine->begin());
				(*vtIteraterCol)=TypeClear;
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::FindEndClearVector(TYPE Type, TYPE TypeClear)
{
	tLineCol tlc(-1, -1);
	vector<vector<TYPE> >::reverse_iterator vtRIteraterLine;
	vector<TYPE>::reverse_iterator vtRIteraterCol;
	for(vtRIteraterLine=(*this).rbegin(); vtRIteraterLine!=(*this).rend(); vtRIteraterLine++){
		for(vtRIteraterCol=vtRIteraterLine.rbegin(); vtRIteraterCol!=vtRIteraterLine.rend(); vtRIteraterCol++){
			if(Type==(*vtRIteraterCol)){
				tlc.m_tLineCol.sLine=(short int)((*this).rend()-vtRIteraterLine);
				tlc.m_tLineCol.sCol=(short int)(vtRIteraterLine.rend()-vtRIteraterCol);
				(*vtRIteraterCol)=TypeClear;
				return tlc;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindBeginClearVector(int nLine, TYPE Type, TYPE TypeClear)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	int nFind=0;
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=(*this)[nLine].begin(); vtIterater!=(*this)[nLine].end(); vtIterater++){
		if(Type==(*vtIterater)){
			nFind=(int)(vtIterater-(*this)[nLine].begin());
			(*vtIterater)=TypeClear;
			return nFind;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::FindEndClearVector(int nLine, TYPE Type, TYPE TypeClear)
{
	if((0>nLine)||((int)size()<=nLine)) return -1;
	int nFind=0;
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=(*this)[nLine].rbegin(); vtRIterater!=(*this)[nLine].rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			nFind=(int)((*this)[nLine].rend()-vtRIterater);
			(*vtRIterater)=TypeClear;
			return nFind;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::DelVector(int nLine, int nCol)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	if((0>nCol)||((int)(*this)[nLine].size()<=nCol)) return false;
	(*this)[nLine].erase((*this)[nLine].begin()+nCol);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::DelVector(int nLine)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	(*this)[nLine].clear();
	(*this).erase(begin()+nLine);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::DelVector(void)
{
	for(int i=0; i<(int)(*this).size(); i++){
		(*this)[i].clear();
	}
	(*this).clear();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::TotalVector(void)
{
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::TotalVector(int nLine, int &Total)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	Total=(int)(*this)[nLine].size();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::GetVector(int nLine, int nCol, TYPE &Type)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	if((0>nCol)||((int)(*this)[nLine].size()<=nCol)) return false;
	Type=(*this)[nLine][nCol];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::GetVectorPtr(int nLine, int nCol, TYPE** ppType)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	if((0>nCol)||((int)(*this)[nLine].size()<=nCol)) return false;
	(*ppType)=&(*this)[nLine][nCol];
	return (NULL!=(*ppType));
}//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::GetVectorLine(int nLine, vector<TYPE>* pvType)
{
	if(NULL==pvType) return false;
	if((0>nLine)||((int)size()<=nLine)) return false;
	pvType->assign((*this)[nLine].begin(), (*this)[nLine].end());
	return true;   	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::GetVectorCol(int nCol, vector<TYPE>* pvType)
{
	if(NULL==pvType) return false;
	if(0==size()) return false;
	if((0>nCol)||((int)(*this)[0].size()<=nCol)) return false;
	int nTotal=(int)size();
	vector<TYPE>::iterator vtIteraterCol;
	int nLineTotal=(int)size();
	for(int i=0; i<nLineTotal; i++){
		if(false==IsUsableArray(i, nCol)) continue;
		pvType->push_back((*this)[i][nCol]);
	}
	return true;   
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVVector<TYPE>::GetVectorPtr(int nLine, vector<TYPE>** ppvType)
{
	if((0>nLine)||((int)size()<=nLine)) return false;
	(*ppvType)=&(*this)[nLine];
	return (NULL!=(*ppvType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SetVector(TYPE Type)
{
	vector<vector<TYPE> >::iterator vtIteraterLine;
	vector<TYPE>::iterator vtIteraterCol;
	for(vtIteraterLine=(*this).begin(); vtIteraterLine!=(*this).end(); vtIteraterLine++){
		for(vtIteraterCol=vtIteraterLine->begin(); vtIteraterCol!=vtIteraterLine->end(); vtIteraterCol++){
			(*vtIteraterCol)=Type;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::NonZeroLineColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSetLine=InRangeValue(0, nLineTotal-1, nSetLine);
	for(i=nStartLine; i<=nEndLine; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nLine=0;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		for(j=nStartCol; j<=nEndCol; j++){
			if(0!=(*this)[i][j]){
				(*this)[i][nSetCol]=Type;
				break;
			}
		}
	}
	if(true==TotalVector(0, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nCol=0;
			for(i=nStartLine; i<=nEndLine; i++){
				if(true==IsUsableArray(i, j)){
					if(0!=(*this)[i][j]){
						(*this)[nSetLine][j]=Type;
						break;
					}
				}
			}
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumLineColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSetLine=InRangeValue(0, nLineTotal-1, nSetLine);
	for(i=nStartLine; i<=nEndLine; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nLine=0;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nLine+=(*this)[i][j];
		}
		(*this)[i][nSetCol]=nLine;
	}
	if(true==TotalVector(0, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nCol=0;
			for(i=nStartLine; i<=nEndLine; i++){
				if(true==IsUsableArray(i, j)){
					nCol+=(*this)[i][j];
				}
			}
			(*this)[nSetLine][j]=nCol;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::SumLineVector(int nCol, int nStartLine, int nEndLine)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(false==TotalVector(nCol, nColTotal)) return nLine;
	for(i=nStartLine; i<=nEndLine; i++){
		nLine+=(*this)[i][nCol];
	}
	return nLine;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::SumColVector(int nLine, int nStartCol, int nEndCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	if(false==TotalVector(nLine, nColTotal)) return nCol;
	nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
	nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
	for(j=nStartCol; j<=nEndCol; j++){
		nCol+=(*this)[nLine][j];
	}
	return nCol;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::SumLineColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLineCol=0;
	int i=0, j=0;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	for(i=nStartLine; i<=nEndLine; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nLineCol+=(*this)[i][j];
		}
	}
	return nLineCol;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSet=InRangeValue(0, nLineTotal-1, nSet);
	if(true==TotalVector(0, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nLine=0;
			for(i=nStartLine; i<=nEndLine; i++){
				if(true==IsUsableArray(i, j)){
					nLine+=(*this)[i][j];
				}
			}
			(*this)[nSet][j]=nLine;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	for(i=nStartLine; i<=nEndLine; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSet=InRangeValue(0, nColTotal-1, nSet);
		nCol=0;
		for(j=nStartCol; j<=nEndCol; j++){
			nCol+=(*this)[i][j];
		}
		(*this)[i][nSet]=nCol;
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumLineColVectorBegin(void)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	if(true==TotalVector(0, nColTotal)){
		for(j=1; j<nColTotal; j++){
			nLine=0;
			for(i=1; i<nLineTotal; i++){
				if(true==IsUsableArray(i, j)){
					nLine+=(*this)[i][j];
				}
			}
			(*this)[0][j]=nLine;
		}
	}
	for(i=1; i<nLineTotal; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nCol=0;
		for(j=1; j<nColTotal; j++){
			nCol+=(*this)[i][j];
		}
		(*this)[i][0]=nCol;
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumLineColVectorEnd(void)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	if(true==TotalVector(0, nColTotal)){
		for(j=0; j<nColTotal-1; j++){
			nLine=0;
			for(i=0; i<nLineTotal-1; i++){
				if(true==IsUsableArray(i, j)){
					nLine+=(*this)[i][j];
				}
			}
			(*this)[nLineTotal-1][j]=nLine;
		}
	}
	for(i=0; i<nLineTotal-1; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nCol=0;
		for(j=0; j<nColTotal-1; j++){
			nCol+=(*this)[i][j];
		}
		(*this)[i][nColTotal-1]=nCol;
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumLineVectorBegin(void)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	if(true==TotalVector(0, nColTotal)){
		for(j=0; j<nColTotal; j++){
			nLine=0;
			for(i=1; i<nLineTotal; i++){
				if(true==IsUsableArray(i, j)){
					nLine+=(*this)[i][j];
				}
			}
			(*this)[0][j]=nLine;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumColVectorBegin(void)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	for(i=0; i<nLineTotal; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nCol=0;
		for(j=1; j<nColTotal; j++){
			nCol+=(*this)[i][j];
		}
		(*this)[i][0]=nCol;
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumLineVectorEnd(void)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	if(true==TotalVector(0, nColTotal)){
		for(j=0; j<nColTotal; j++){
			nLine=0;
			for(i=0; i<nLineTotal-1; i++){
				if(true==IsUsableArray(i, j)){
					nLine+=(*this)[i][j];
				}
			}
			(*this)[nLineTotal-1][j]=nLine;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::SumColVectorEnd(void)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	for(i=0; i<nLineTotal; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nCol=0;
		for(j=0; j<nColTotal-1; j++){
			nCol+=(*this)[i][j];
		}
		(*this)[i][nColTotal-1]=nCol;
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueLineVectorBegin(TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(0, nColTotal)){
		for(j=0; j<nColTotal; j++){
			nLine=0;
			for(i=1; i<nLineTotal; i++){
				if(true==IsUsableArray(i, j)){
					if(true==bTypeSame){
						if(Type==(*this)[i][j]){
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=i;
								tlcPrev.m_tLineCol12.cCol1=j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=i;
								tlcPrev.m_tLineCol12.cCol2=j;
							}
							nLine++;
						}
						else{
							if(nLine>=(*this)[0][j]){
								(*this)[0][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							nLine=0;
						}
					}
					else{
						if(Type!=(*this)[i][j]){
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=i;
								tlcPrev.m_tLineCol12.cCol1=j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=i;
								tlcPrev.m_tLineCol12.cCol2=j;
							}
							nLine++;
						}
						else{
							if(nLine>=(*this)[0][j]){
								(*this)[0][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							nLine=0;
						}
					}
				}
			}
			if(nLine>=(*this)[0][j]){
				(*this)[0][j]=nLine;
			}
			if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
				if(nLine>=nMax){
					tlc=tlcPrev;
					nMax=nLine;
				}
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlcPrev);
				}
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueColVectorBegin(TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	for(i=0; i<nLineTotal; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nCol=0;
		for(j=1; j<nColTotal; j++){
			if(true==bTypeSame){
				if(Type==(*this)[i][j]){
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=i;
						tlcPrev.m_tLineCol12.cCol1=j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=i;
						tlcPrev.m_tLineCol12.cCol2=j;
					}
					nCol++;
				}
				else{
					if(nCol>=(*this)[i][0]){
						(*this)[i][0]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					nCol=0;
				}
			}
			else{
				if(Type!=(*this)[i][j]){
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=i;
						tlcPrev.m_tLineCol12.cCol1=j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=i;
						tlcPrev.m_tLineCol12.cCol2=j;
					}
					nCol++;
				}
				else{
					if(nCol>=(*this)[i][0]){
						(*this)[i][0]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					nCol=0;
				}
			}
		}
		if(nCol>=(*this)[i][0]){
			(*this)[i][0]=nCol;
		}
		if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
			if(nCol>=nMax){
				tlc=tlcPrev;
				nMax=nCol;
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlcPrev);
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueLineVectorEnd(TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(0, nColTotal)){
		for(j=0; j<nColTotal; j++){
			nLine=0;
			for(i=0; i<nLineTotal-1; i++){
				if(true==IsUsableArray(i, j)){
					if(true==bTypeSame){
						if(Type==(*this)[i][j]){
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=i;
								tlcPrev.m_tLineCol12.cCol1=j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=i;
								tlcPrev.m_tLineCol12.cCol2=j;
							}
							nLine++;
						}
						else{
							if(nLine>=(*this)[nLineTotal-1][j]){
								(*this)[nLineTotal-1][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							nLine=0;
						}
					}
					else{
						if(Type!=(*this)[i][j]){
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=i;
								tlcPrev.m_tLineCol12.cCol1=j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=i;
								tlcPrev.m_tLineCol12.cCol2=j;
							}
							nLine++;
						}
						else{
							if(nLine>=(*this)[nLineTotal-1][j]){
								(*this)[nLineTotal-1][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							nLine=0;
						}
					}
				}
			}
			if(nLine>=(*this)[nLineTotal-1][j]){
				(*this)[nLineTotal-1][j]=nLine;
			}
			if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
				if(nLine>=nMax){
					tlc=tlcPrev;
					nMax=nLine;
				}
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlcPrev);
				}
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueColVectorEnd(TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	for(i=0; i<nLineTotal; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nCol=0;
		for(j=0; j<nColTotal-1; j++){
			if(true==bTypeSame){
				if(Type==(*this)[i][j]){
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=i;
						tlcPrev.m_tLineCol12.cCol1=j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=i;
						tlcPrev.m_tLineCol12.cCol2=j;
					}
					nCol++;
				}
				else{
					if(nCol>=(*this)[i][nColTotal-1]){
						(*this)[i][nColTotal-1]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					nCol=0;
				}
			}
			else{
				if(Type!=(*this)[i][j]){
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=i;
						tlcPrev.m_tLineCol12.cCol1=j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=i;
						tlcPrev.m_tLineCol12.cCol2=j;
					}
					nCol++;
				}
				else{
					if(nCol>=(*this)[i][nColTotal-1]){
						(*this)[i][nColTotal-1]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					nCol=0;
				}
			}
		}
		if(nCol>=(*this)[i][nColTotal-1]){
			(*this)[i][nColTotal-1]=nCol;
		}
		if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
			if(nCol>=nMax){
				tlc=tlcPrev;
				nMax=nCol;
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlcPrev);
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSet=InRangeValue(0, nLineTotal-1, nSet);
	if(true==TotalVector(0, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nLine=0;
			for(i=nStartLine; i<=nEndLine; i++){
				if(true==IsUsableArray(i, j)){
					if(true==bTypeSame){
						if(Type==(*this)[i][j]){
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=(char)i;
								tlcPrev.m_tLineCol12.cCol1=(char)j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=(char)i;
								tlcPrev.m_tLineCol12.cCol2=(char)j;
							}
							nLine++;
						}
						else{
							if(nLine>=(*this)[nSet][j]){
								(*this)[nSet][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							nLine=0;
						}
					}
					else{
						if(Type!=(*this)[i][j]){
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=(char)i;
								tlcPrev.m_tLineCol12.cCol1=(char)j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=(char)i;
								tlcPrev.m_tLineCol12.cCol2=(char)j;
							}
							nLine++;
						}
						else{
							if(nLine>=(*this)[nSet][j]){
								(*this)[nSet][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							nLine=0;
						}
					}
				}
			}
			if(nLine>=(*this)[nSet][j]){
				(*this)[nSet][j]=nLine;
			}
			if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
				if(nLine>=nMax){
					tlc=tlcPrev;
					nMax=nLine;
				}
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlcPrev);
				}
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	for(i=nStartLine; i<=nEndLine; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSet=InRangeValue(0, nColTotal-1, nSet);
		nCol=0;
		for(j=nStartCol; j<=nEndCol; j++){
			if(true==bTypeSame){
				if(Type==(*this)[i][j]){
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=(char)i;
						tlcPrev.m_tLineCol12.cCol1=(char)j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=(char)i;
						tlcPrev.m_tLineCol12.cCol2=(char)j;
					}
					nCol++;
				}
				else{
					if(nCol>=(*this)[i][nSet]){
						(*this)[i][nSet]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					nCol=0;
				}
			}
			else{
				if(Type!=(*this)[i][j]){
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=(char)i;
						tlcPrev.m_tLineCol12.cCol1=(char)j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=(char)i;
						tlcPrev.m_tLineCol12.cCol2=(char)j;
					}
					nCol++;
				}
				else{
					if(nCol>=(*this)[i][nSet]){
						(*this)[i][nSet]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					nCol=0;
				}
			}
		}
		if(nCol>=(*this)[i][nSet]){
			(*this)[i][nSet]=nCol;
		}
		if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
			if(nCol>=nMax){
				tlc=tlcPrev;
				nMax=nCol;
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlcPrev);
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueLineColsVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1), tlcPrev(-1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSetLine=InRangeValue(0, nLineTotal-1, nSetLine);
	for(i=nStartLine; i<=nEndLine; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		nCol=0;
		for(j=nStartCol; j<=nEndCol; j++){
			if(true==bTypeSame){
				if(Type==(*this)[i][j]){
					nCol++;
					break;
				}
			}
			else{
				if(Type!=(*this)[i][j]){
					nCol++;
					break;
				}
			}
		}
		if(0!=nCol){
			if(0==nLine){
				tlcPrev.m_tLineCol.sLine=(short)i;
			}
			else{
				tlcPrev.m_tLineCol.sCol=(short)i;
			}
			nLine++;
		}
		else{
			if(nLine>=(*this)[nSetLine][nSetCol]){
				(*this)[nSetLine][nSetCol]=nLine;
			}
			if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
				if(nLine>=nMax){
					tlc=tlcPrev;
					nMax=nLine;
				}
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlcPrev);
				}
			}
			nLine=0;
		}
	}
	if(true==TotalVector(nSetLine, nColTotal)){
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		if(nLine>=(*this)[nSetLine][nSetCol]){
			(*this)[nSetLine][nSetCol]=nLine;
		}
	}
	if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
		if(nLine>=nMax){
			tlc=tlcPrev;
			nMax=nLine;
		}
		if(NULL!=pvtLineCol){
			pvtLineCol->push_back(tlcPrev);
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueColLinesVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	int nMax=0;
	tLineCol tlc(-1, -1), tlcPrev(-1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSetLine=InRangeValue(0, nLineTotal-1, nSetLine);
	if(true==TotalVector(nSetLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nLine=0;
			for(i=nStartLine; i<=nEndLine; i++){
				if(true==IsUsableArray(i, j)){
					if(true==bTypeSame){
						if(Type==(*this)[i][j]){
							nLine++;
							break;
						}
					}
					else{
						if(Type!=(*this)[i][j]){
							nLine++;
							break;
						}
					}
				}
			}
			if(0!=nLine){
				if(0==nCol){
					tlcPrev.m_tLineCol.sLine=(short)j;
				}
				else{
					tlcPrev.m_tLineCol.sCol=(short)j;
				}
				nCol++;
			}
			else{
				if(nCol>=(*this)[nSetLine][nSetCol]){
					(*this)[nSetLine][nSetCol]=nCol;
				}
				if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
					if(nCol>=nMax){
						tlc=tlcPrev;
						nMax=nCol;
					}
					if(NULL!=pvtLineCol){
						pvtLineCol->push_back(tlcPrev);
					}
				}
				nCol=0;
			}
		}
	}
	if(true==TotalVector(nSetLine, nColTotal)){
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		if(nCol>=(*this)[nSetLine][nSetCol]){
			(*this)[nSetLine][nSetCol]=nCol;
		}
	}
	if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
		if(nCol>=nMax){
			tlc=tlcPrev;
			nMax=nCol;
		}
		if(NULL!=pvtLineCol){
			pvtLineCol->push_back(tlcPrev);
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueFillLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0;
	int i=0, j=0;
	int nMax=0;
	int nPrevi=-1;
	int nFill=1;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSet=InRangeValue(0, nLineTotal-1, nSet);
	if(true==TotalVector(0, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		for(j=nStartCol; j<=nEndCol; j++){
			nPrevi=-1;
			tlcPrev.SetLineCol(-1, -1, -1, -1);
			nFill=1;
			nLine=0;
			for(i=nStartLine; i<=nEndLine; i++){
Restart:
				if(true==IsUsableArray(i, j)){
					if(true==bTypeSame){
						if(Type==(*this)[i][j]){
							if(0==nLine){
								if(-1==tlcPrev.m_tLineCol12.cLine1){
									tlcPrev.m_tLineCol12.cLine1=(char)i;
								}
								if(-1==tlcPrev.m_tLineCol12.cCol1){
									tlcPrev.m_tLineCol12.cCol1=(char)j;
								}
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=(char)i;
								tlcPrev.m_tLineCol12.cCol2=(char)j;
							}
							if((0==nFill)&&(-1==nPrevi)){
								nPrevi=i;
							}
							nLine++;
						}
						else if(0<nFill){
							if((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cCol1)){
								if(-1==nPrevi){
									nPrevi=i;
								}
							}
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=(char)i;
								tlcPrev.m_tLineCol12.cCol1=(char)j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=(char)i;
								tlcPrev.m_tLineCol12.cCol2=(char)j;
							}
							nFill--;
						}
						else{
							if(nLine>=(*this)[nSet][j]){
								(*this)[nSet][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							if(-1!=nPrevi){
								i=nPrevi-1;
								nPrevi=-1;
							}
							else if(((-1==tlcPrev.m_tLineCol12.cLine2)&&(-1==tlcPrev.m_tLineCol12.cCol2))&&(0==nFill)){
								i=i-1;
							}
							tlcPrev.SetLineCol(-1, -1, -1, -1);
							nFill=1;
							nLine=0;
						}
					}
					else{
						if(Type!=(*this)[i][j]){
							if(0==nLine){
								if(-1==tlcPrev.m_tLineCol12.cLine1){
									tlcPrev.m_tLineCol12.cLine1=(char)i;
								}
								if(-1==tlcPrev.m_tLineCol12.cCol1){
									tlcPrev.m_tLineCol12.cCol1=(char)j;
								}
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=(char)i;
								tlcPrev.m_tLineCol12.cCol2=(char)j;
							}
							if((0==nFill)&&(-1==nPrevi)){
								nPrevi=i;
							}
							nLine++;
						}
						else if(0<nFill){
							if((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cCol1)){
								if(-1==nPrevi){
									nPrevi=i;
								}
							}
							if(0==nLine){
								tlcPrev.m_tLineCol12.cLine1=(char)i;
								tlcPrev.m_tLineCol12.cCol1=(char)j;
							}
							else{
								tlcPrev.m_tLineCol12.cLine2=(char)i;
								tlcPrev.m_tLineCol12.cCol2=(char)j;
							}
							nFill--;
						}
						else{
							if(nLine>=(*this)[nSet][j]){
								(*this)[nSet][j]=nLine;
							}
							if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
								if(nLine>=nMax){
									tlc=tlcPrev;
									nMax=nLine;
								}
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlcPrev);
								}
							}
							if(-1!=nPrevi){
								i=nPrevi-1;
								nPrevi=-1;
							}
							else if(((-1==tlcPrev.m_tLineCol12.cLine2)&&(-1==tlcPrev.m_tLineCol12.cCol2))&&(0==nFill)){
								i=i-1;
							}
							tlcPrev.SetLineCol(-1, -1, -1, -1);
							nFill=1;
							nLine=0;
						}
					}
				}
			}
			if(nLine>=(*this)[nSet][j]){
				(*this)[nSet][j]=nLine;
			}
			if(((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cLine2))&&(1<nLine)){
				if(nLine>=nMax){
					tlc=tlcPrev;
					nMax=nLine;
				}
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlcPrev);
				}
			}
			if(-1!=nPrevi){
				i=nPrevi;
				nPrevi=-1;
				tlcPrev.SetLineCol(-1, -1, -1, -1);
				nFill=1;
				nLine=0;
				goto Restart;
			}
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueFillColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSet, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nCol=0;
	int i=0, j=0;
	int nMax=0;
	int nPrevj=0;
	int nFill=1;
	tLineCol tlc(-1, -1, -1, -1), tlcPrev(-1, -1, -1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	for(i=nStartLine; i<=nEndLine; i++){
		if(false==TotalVector(i, nColTotal)) continue;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSet=InRangeValue(0, nColTotal-1, nSet);
		nPrevj=-1;
		tlcPrev.SetLineCol(-1, -1, -1, -1);
		nFill=1;
		nCol=0;
		for(j=nStartCol; j<=nEndCol; j++){
Restart:
			if(true==bTypeSame){
				if(Type==(*this)[i][j]){
					if(0==nCol){
						if(-1==tlcPrev.m_tLineCol12.cLine1){
							tlcPrev.m_tLineCol12.cLine1=(char)i;
						}
						if(-1==tlcPrev.m_tLineCol12.cCol1){
							tlcPrev.m_tLineCol12.cCol1=(char)j;
						}
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=(char)i;
						tlcPrev.m_tLineCol12.cCol2=(char)j;
					}
					if((0==nFill)&&(-1==nPrevj)){
						nPrevj=j;
					}
					nCol++;
				}
				else if(0<nFill){
					if((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cCol1)){
						if(-1==nPrevj){
							nPrevj=j;
						}
					}
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=(char)i;
						tlcPrev.m_tLineCol12.cCol1=(char)j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=(char)i;
						tlcPrev.m_tLineCol12.cCol2=(char)j;
					}
					nFill--;
				}
				else{
					if(nCol>=(*this)[i][nSet]){
						(*this)[i][nSet]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					if(-1!=nPrevj){
						j=nPrevj-1;
						nPrevj=-1;
					}
					else if(((-1==tlcPrev.m_tLineCol12.cLine2)&&(-1==tlcPrev.m_tLineCol12.cCol2))&&(0==nFill)){
						j=j-1;
					}
					tlcPrev.SetLineCol(-1, -1, -1, -1);
					nFill=1;
					nCol=0;
				}
			}
			else{
				if(Type!=(*this)[i][j]){
					if(0==nCol){
						if(-1==tlcPrev.m_tLineCol12.cLine1){
							tlcPrev.m_tLineCol12.cLine1=(char)i;
						}
						if(-1==tlcPrev.m_tLineCol12.cCol1){
							tlcPrev.m_tLineCol12.cCol1=(char)j;
						}
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=(char)i;
						tlcPrev.m_tLineCol12.cCol2=(char)j;
					}
					if((0==nFill)&&(-1==nPrevj)){
						nPrevj=j;
					}
					nCol++;
				}
				else if(0<nFill){
					if((-1!=tlcPrev.m_tLineCol12.cLine1)&&(-1!=tlcPrev.m_tLineCol12.cCol1)){
						if(-1==nPrevj){
							nPrevj=j;
						}
					}
					if(0==nCol){
						tlcPrev.m_tLineCol12.cLine1=(char)i;
						tlcPrev.m_tLineCol12.cCol1=(char)j;
					}
					else{
						tlcPrev.m_tLineCol12.cLine2=(char)i;
						tlcPrev.m_tLineCol12.cCol2=(char)j;
					}
					nFill--;
				}
				else{
					if(nCol>=(*this)[i][nSet]){
						(*this)[i][nSet]=nCol;
					}
					if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
						if(nCol>=nMax){
							tlc=tlcPrev;
							nMax=nCol;
						}
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlcPrev);
						}
					}
					if(-1!=nPrevj){
						j=nPrevj-1;
						nPrevj=-1;
					}
					else if(((-1==tlcPrev.m_tLineCol12.cLine2)&&(-1==tlcPrev.m_tLineCol12.cCol2))&&(0==nFill)){
						j=j-1;
					}
					tlcPrev.SetLineCol(-1, -1, -1, -1);
					nFill=1;
					nCol=0;
				}
			}
		}
		if(nCol>=(*this)[i][nSet]){
			(*this)[i][nSet]=nCol;
		}
		if(((-1!=tlcPrev.m_tLineCol12.cCol1)&&(-1!=tlcPrev.m_tLineCol12.cCol2))&&(1<nCol)){
			if(nCol>=nMax){
				tlc=tlcPrev;
				nMax=nCol;
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlcPrev);
			}
		}
		if(-1!=nPrevj){
			j=nPrevj;
			nPrevj=-1;
			tlcPrev.SetLineCol(-1, -1, -1, -1);
			nFill=1;
			nCol=0;
			goto Restart;
		}
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueFillLineColsVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	int nMax=0;
	int nPrevi=-1;
	int nFill=1;
	tLineCol tlc(-1, -1), tlcPrev(-1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSetLine=InRangeValue(0, nLineTotal-1, nSetLine);
	for(i=nStartLine; i<=nEndLine; i++){
Restart:
		if(false==TotalVector(i, nColTotal)) continue;
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		nCol=0;
		for(j=nStartCol; j<=nEndCol; j++){
			if(true==bTypeSame){
				if(Type==(*this)[i][j]){
					nCol++;
					break;
				}
			}
			else{
				if(Type!=(*this)[i][j]){
					nCol++;
					break;
				}
			}
		}
		if(0!=nCol){
			if(0==nLine){
				if(-1==tlcPrev.m_tLineCol.sLine){
					tlcPrev.m_tLineCol.sLine=(short)i;
				}
			}
			else{
				tlcPrev.m_tLineCol.sCol=(short)i;
			}
			if((0==nFill)&&(-1==nPrevi)){
				nPrevi=i;
			}
			nLine++;
		}
		else if(0<nFill){
			if(-1!=tlcPrev.m_tLineCol.sLine){
				if(-1==nPrevi){
					nPrevi=i;
				}
			}
			if(0==nLine){
				tlcPrev.m_tLineCol.sLine=(short)i;
			}
			else{
				tlcPrev.m_tLineCol.sCol=(short)i;
			}
			nFill--;
		}
		else{
			if(nLine>=(*this)[nSetLine][nSetCol]){
				(*this)[nSetLine][nSetCol]=nLine;
			}
			if((-1!=tlcPrev.m_tLineCol.sLine)&&(-1!=tlcPrev.m_tLineCol.sCol)){
				if(nLine>=nMax){
					tlc=tlcPrev;
					nMax=nLine;
				}
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlcPrev);
				}
			}
			if(-1!=nPrevi){
				i=nPrevi-1;
				nPrevi=-1;
			}
			else if((-1==tlcPrev.m_tLineCol.sCol)&&(0==nFill)){
				i=i-1;
			}
			tlcPrev.SetLineCol(-1, -1, -1, -1);
			nFill=1;
			nLine=0;
		}
	}
	if(true==TotalVector(nSetLine, nColTotal)){
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		if(nLine>=(*this)[nSetLine][nSetCol]){
			(*this)[nSetLine][nSetCol]=nLine;
		}
	}
	if((-1!=tlcPrev.m_tLineCol.sLine)&&(-1!=tlcPrev.m_tLineCol.sCol)){
		if(nLine>=nMax){
			tlc=tlcPrev;
			nMax=nLine;
		}
		if(NULL!=pvtLineCol){
			pvtLineCol->push_back(tlcPrev);
		}
	}
	if(-1!=nPrevi){
		i=nPrevi;
		nPrevi=-1;
		tlcPrev.SetLineCol(-1, -1, -1, -1);
		nFill=1;
		nLine=0;
		goto Restart;
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
tLineCol CTVVector<TYPE>::ContinueFillColLinesVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nSetLine, int nSetCol, TYPE Type, bool bTypeSame, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int nLine=0, nCol=0;
	int i=0, j=0;
	int nMax=0;
	int nPrevj=-1;
	int nFill=1;
	tLineCol tlc(-1, -1), tlcPrev(-1, -1);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	nSetLine=InRangeValue(0, nLineTotal-1, nSetLine);
	if(true==TotalVector(nSetLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		for(j=nStartCol; j<=nEndCol; j++){
Restart:
			nLine=0;
			for(i=nStartLine; i<=nEndLine; i++){
				if(true==IsUsableArray(i, j)){
					if(true==bTypeSame){
						if(Type==(*this)[i][j]){
							nLine++;
							break;
						}
					}
					else{
						if(Type!=(*this)[i][j]){
							nLine++;
							break;
						}
					}
				}
			}
			if(0!=nLine){
				if(0==nCol){
					if(-1==tlcPrev.m_tLineCol.sLine){
						tlcPrev.m_tLineCol.sLine=(short)j;
					}
				}
				else{
					tlcPrev.m_tLineCol.sCol=(short)j;
				}
				if((0==nFill)&&(-1==nPrevj)){
					nPrevj=j;
				}
				nCol++;
			}
			else if(0<nFill){
				if(-1!=tlcPrev.m_tLineCol.sLine){
					if(-1==nPrevj){
						nPrevj=j;
					}
				}
				if(0==nCol){
					tlcPrev.m_tLineCol.sLine=(short)j;
				}
				else{
					tlcPrev.m_tLineCol.sCol=(short)j;
				}
				nFill--;
			}
			else{
				if(nCol>=(*this)[nSetLine][nSetCol]){
					(*this)[nSetLine][nSetCol]=nCol;
				}
				if((-1!=tlcPrev.m_tLineCol.sLine)&&(-1!=tlcPrev.m_tLineCol.sCol)){
					if(nCol>=nMax){
						tlc=tlcPrev;
						nMax=nCol;
					}
					if(NULL!=pvtLineCol){
						pvtLineCol->push_back(tlcPrev);
					}
				}
				if(-1!=nPrevj){
					j=nPrevj-1;
					nPrevj=-1;
				}
				else if((-1==tlcPrev.m_tLineCol.sCol)&&(0==nFill)){
					j=j-1;
				}
				tlcPrev.SetLineCol(-1, -1, -1, -1);
				nFill=1;
				nCol=0;
			}
		}
	}
	if(false==TotalVector(nSetLine, nColTotal)){
		nSetCol=InRangeValue(0, nColTotal-1, nSetCol);
		if(nCol>=(*this)[nSetLine][nSetCol]){
			(*this)[nSetLine][nSetCol]=nCol;
		}
	}
	if((-1!=tlcPrev.m_tLineCol.sLine)&&(-1!=tlcPrev.m_tLineCol.sCol)){
		if(nCol>=nMax){
			tlc=tlcPrev;
			nMax=nCol;
		}
		if(NULL!=pvtLineCol){
			pvtLineCol->push_back(tlcPrev);
		}
	}
	if(-1!=nPrevj){
		j=nPrevj;
		nPrevj=-1;
		tlcPrev.SetLineCol(-1, -1, -1, -1);
		nFill=1;
		nCol=0;
		goto Restart;
	}
	return tlc;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::ContinueLineToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, int nCol, TYPE Type, bool bTypeSame, bool bLooping, tLineCol* ptLineCol, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	int nCnt=0;
	tLineCol tlc(-1, -1, -1, -1);
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return nCnt;
		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=nLine;
		nCnt++;
		for(i=nLine-1; i>=nStartLine; i--){
			if(true==IsUsableArray(i, nCol)){
				if(true==bTypeSame){
					if(Type==(*this)[i][nCol]){
						nCnt++;
						tlc.m_tLineCol12.cLine1=(char)i;
					}
					else{
						break;
					}
				}
				else{
					if(Type!=(*this)[i][nCol]){
						nCnt++;
						tlc.m_tLineCol12.cLine1=(char)i;
					}
					else{
						break;
					}
				}
			}
		}
		for(i=nLine+1; i<=nEndLine; i++){
			if(true==IsUsableArray(i, nCol)){
				if(true==bTypeSame){
					if(Type==(*this)[i][nCol]){
						nCnt++;
						tlc.m_tLineCol12.cCol1=(char)i;
					}
					else{
						break;
					}
				}
				else{
					if(Type!=(*this)[i][nCol]){
						nCnt++;
						tlc.m_tLineCol12.cCol1=(char)i;
					}
					else{
						break;
					}
				}
			}
		}
		if(true==bLooping){
			if((nEndLine==tlc.m_tLineCol12.cCol1)&&(nStartLine!=tlc.m_tLineCol12.cLine1)){
				tlc.m_tLineCol12.cLine2=nStartLine;
				for(i=nStartLine; i<nLine; i++){
					if(true==IsUsableArray(i, nCol)){
						if(true==bTypeSame){
							if(Type==(*this)[i][nCol]){
								nCnt++;
								tlc.m_tLineCol12.cCol2=(char)i;
							}
							else{
								break;
							}
						}
						else{
							if(Type!=(*this)[i][nCol]){
								nCnt++;
								tlc.m_tLineCol12.cCol2=(char)i;
							}
							else{
								break;
							}
						}
					}
				}
				if(-1==tlc.m_tLineCol12.cCol2){
					tlc.m_tLineCol12.cLine2=-1;
				}
			}
			if((nStartLine==tlc.m_tLineCol12.cLine1)&&(nEndLine!=tlc.m_tLineCol12.cCol1)){
				tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
				tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
				tlc.m_tLineCol12.cCol1=nEndLine;
				for(i=nEndLine; i>nLine; i--){
					if(true==IsUsableArray(i, nCol)){
						if(true==bTypeSame){
							if(Type==(*this)[i][nCol]){
								nCnt++;
								tlc.m_tLineCol12.cLine1=(char)i;
							}
							else{
								break;
							}
						}
						else{
							if(Type!=(*this)[i][nCol]){
								nCnt++;
								tlc.m_tLineCol12.cLine1=(char)i;
							}
							else{
								break;
							}
						}
					}
				}
				if(-1==tlc.m_tLineCol12.cLine1){
					tlc.m_tLineCol12.cCol1=-1;
					tlc.SwapLineColChar();
				}
			}
		}
	}
	if(NULL!=ptLineCol){
		(*ptLineCol)=tlc;
	}
	if(NULL!=pvtLineCol){
		if((-1!=tlc.m_tLineCol12.cLine2)&&(-1!=tlc.m_tLineCol12.cCol2)){
			for(i=tlc.m_tLineCol12.cLine1; i<=tlc.m_tLineCol12.cCol1; i++){
				pvtLineCol->push_back(tLineCol(i, nCol));
			}
			for(i=tlc.m_tLineCol12.cLine2; i<=tlc.m_tLineCol12.cCol2; i++){
				pvtLineCol->push_back(tLineCol(i, nCol));
			}
		}
		else{
			for(i=tlc.m_tLineCol12.cLine1; i<=tlc.m_tLineCol12.cCol1; i++){
				pvtLineCol->push_back(tLineCol(i, nCol));
			}
		}
	}
	return nCnt; 
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVVector<TYPE>::ContinueColToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, int nCol, TYPE Type, bool bTypeSame, bool bLooping, tLineCol* ptLineCol, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	int nCnt=0;
	tLineCol tlc(-1, -1, -1, -1);
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return nCnt;
		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=nCol;
		nCnt++;
		for(j=nCol-1; j>=nStartCol; j--){
			if(true==IsUsableArray(nLine, j)){
				if(true==bTypeSame){
					if(Type==(*this)[nLine][j]){
						nCnt++;
						tlc.m_tLineCol12.cLine1=(char)j;
					}
					else{
						break;
					}
				}
				else{
					if(Type!=(*this)[nLine][j]){
						nCnt++;
						tlc.m_tLineCol12.cLine1=(char)j;
					}
					else{
						break;
					}
				}
			}
		}
		for(j=nCol+1; j<=nEndCol; j++){
			if(true==IsUsableArray(nLine, j)){
				if(true==bTypeSame){
					if(Type==(*this)[nLine][j]){
						nCnt++;
						tlc.m_tLineCol12.cCol1=(char)j;
					}
					else{
						break;
					}
				}
				else{
					if(Type!=(*this)[nLine][j]){
						nCnt++;
						tlc.m_tLineCol12.cCol1=(char)j;
					}
					else{
						break;
					}
				}
			}
		}
		if(true==bLooping){
			if((nEndCol==tlc.m_tLineCol12.cCol1)&&(nStartCol!=tlc.m_tLineCol12.cLine1)){
				tlc.m_tLineCol12.cLine2=nStartLine;
				for(j=nStartCol; j<nCol; j++){
					if(true==IsUsableArray(nLine, j)){
						if(true==bTypeSame){
							if(Type==(*this)[nLine][j]){
								nCnt++;
								tlc.m_tLineCol12.cCol2=(char)j;
							}
							else{
								break;
							}
						}
						else{
							if(Type!=(*this)[nLine][j]){
								nCnt++;
								tlc.m_tLineCol12.cCol2=(char)j;
							}
							else{
								break;
							}
						}
					}
				}
				if(-1==tlc.m_tLineCol12.cCol2){
					tlc.m_tLineCol12.cLine2=-1;
				}
			}
			if((nStartCol==tlc.m_tLineCol12.cLine1)&&(nEndCol!=tlc.m_tLineCol12.cCol1)){
				tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
				tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
				tlc.m_tLineCol12.cCol1=nEndLine;
				for(j=nEndCol; j>nCol; j--){
					if(true==IsUsableArray(nLine, j)){
						if(true==bTypeSame){
							if(Type==(*this)[nLine][j]){
								nCnt++;
								tlc.m_tLineCol12.cLine1=(char)j;
							}
							else{
								break;
							}
						}
						else{
							if(Type!=(*this)[nLine][j]){
								nCnt++;
								tlc.m_tLineCol12.cLine1=(char)j;
							}
							else{
								break;
							}
						}
					}
				}
				if(-1==tlc.m_tLineCol12.cLine1){
					tlc.m_tLineCol12.cCol1=-1;
					tlc.SwapLineColChar();
				}
			}
		}
	}
	if(NULL!=ptLineCol){
		(*ptLineCol)=tlc;
	}
	if(NULL!=pvtLineCol){
		if((-1!=tlc.m_tLineCol12.cLine2)&&(-1!=tlc.m_tLineCol12.cCol2)){
			for(j=tlc.m_tLineCol12.cLine1; j<=tlc.m_tLineCol12.cCol1; j++){
				pvtLineCol->push_back(tLineCol(nLine, j));
			}
			for(j=tlc.m_tLineCol12.cLine2; j<=tlc.m_tLineCol12.cCol2; j++){
				pvtLineCol->push_back(tLineCol(nLine, j));
			}
		}
		else{
			for(j=tlc.m_tLineCol12.cLine2; j<=tlc.m_tLineCol12.cCol2; j++){
				pvtLineCol->push_back(tLineCol(nLine, j));
			}
		}
	}
	return nCnt; 
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::ContinueLinesToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nCol, TYPE Type, bool bTypeSame, bool bLooping, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	tLineCol tlc(-1, -1, -1, -1);
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nStartLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return;
		for(i=nStartLine; i<=nEndLine; i++){
			if(true==IsUsableArray(i, nCol)){
				if(true==bTypeSame){
					if(Type==(*this)[i][nCol]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=(char)i;
						}
						else{
							tlc.m_tLineCol12.cCol1=(char)i;
						}
					}
					else{
						//if(true==bLooping){
						//	if((nStartLine==tlc.m_tLineCol12.cLine1)&&(nEndLine!=tlc.m_tLineCol12.cCol1)){
						//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
						//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
						//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
						//		for(j=nEndLine; j>i; j--){
						//			if(true==IsUsableArray(j, nCol)){
						//				if(Type==(*this)[j][nCol]){
						//					if(-1==tlc.m_tLineCol12.cCol1){
						//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=j;
						//					}
						//					else{
						//						tlc.m_tLineCol12.cLine1=j;
						//					}
						//				}
						//				else{
						//					break;
						//				}
						//			}
						//		}
						//		if(-1==tlc.m_tLineCol12.cLine1){
						//			tlc.m_tLineCol12.cCol1=-1;
						//			tlc.SwapLineColChar();
						//		}
						//		else{
						//			nEndLine=tlc.m_tLineCol12.cLine1-1;
						//		}
						//	}
						//}
						if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
							if(NULL!=pvtLineCol){
								pvtLineCol->push_back(tlc);
							}
						}
						tlc.SetLineCol(-1, -1, -1 ,-1);
					}
				}
				else{
					if(Type!=(*this)[i][nCol]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=(char)i;
						}
						else{
							tlc.m_tLineCol12.cCol1=(char)i;
						}
					}
					else{
						//if(true==bLooping){
						//	if((nStartLine==tlc.m_tLineCol12.cLine1)&&(nEndLine!=tlc.m_tLineCol12.cCol1)){
						//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
						//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
						//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
						//		for(j=nEndLine; j>i; j--){
						//			if(true==IsUsableArray(j, nCol)){
						//				if(Type!=(*this)[j][nCol]){
						//					if(-1==tlc.m_tLineCol12.cCol1){
						//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=j;
						//					}
						//					else{
						//						tlc.m_tLineCol12.cLine1=j;
						//					}
						//				}
						//				else{
						//					break;
						//				}
						//			}
						//		}
						//		if(-1==tlc.m_tLineCol12.cLine1){
						//			tlc.m_tLineCol12.cCol1=-1;
						//			tlc.SwapLineColChar();
						//		}
						//		else{
						//			nEndLine=tlc.m_tLineCol12.cLine1-1;
						//		}
						//	}
						//}
						if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
							if(NULL!=pvtLineCol){
								pvtLineCol->push_back(tlc);
							}
						}
						tlc.SetLineCol(-1, -1, -1 ,-1);
					}
				}
			}
		}
		if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
			if(true==bLooping){
				if((nEndLine==tlc.m_tLineCol12.cCol1)&&(nStartLine!=tlc.m_tLineCol12.cLine1)){
					for(j=nStartLine; j<nEndLine; j++){
						if(true==IsUsableArray(j, nCol)){
							if(true==bTypeSame){
								if(Type==(*this)[j][nCol]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)j;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)j;
									}
								}
								else{
									break;
								}
							}
							else{
								if(Type!=(*this)[j][nCol]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)j;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)j;
									}
								}
								else{
									break;
								}
							}
						}
					}
					if(-1==tlc.m_tLineCol12.cCol2){
						tlc.m_tLineCol12.cLine2=-1;
					}
				}
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlc);
			}
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::ContinueColsToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, TYPE Type, bool bTypeSame, bool bLooping, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	int nCnt=0;
	tLineCol tlc(-1, -1, -1, -1);
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return nCnt;
		nCnt++;
		for(j=nStartCol; j<=nEndCol; j++){
			if(true==IsUsableArray(nLine, j)){
				if(true==bTypeSame){
					if(Type==(*this)[nLine][j]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=(char)j;
						}
						else{
							tlc.m_tLineCol12.cCol1=(char)j;
						}
					}
					else{
						//if(true==bLooping){
						//	if((nStartCol==tlc.m_tLineCol12.cLine1)&&(nEndCol!=tlc.m_tLineCol12.cCol1)){
						//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
						//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
						//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
						//		for(i=nEndCol; i>j; i--){
						//			if(true==IsUsableArray(nLine, i)){
						//				if(Type==(*this)[nLine][i]){
						//					if(-1==tlc.m_tLineCol12.cCol1){
						//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=j;
						//					}
						//					else{
						//						tlc.m_tLineCol12.cLine1=j;
						//					}
						//				}
						//				else{
						//					break;
						//				}
						//			}
						//		}
						//		if(-1==tlc.m_tLineCol12.cLine1){
						//			tlc.m_tLineCol12.cCol1=-1;
						//			tlc.SwapLineColChar();
						//		}
						//		else{
						//			nEndCol=tlc.m_tLineCol12.cLine1-1;
						//		}
						//	}
						//}
						if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
							if(NULL!=pvtLineCol){
								pvtLineCol->push_back(tlc);
							}
						}
						tlc.SetLineCol(-1, -1, -1 ,-1);
					}
				}
				else{
					if(Type!=(*this)[nLine][j]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=(char)j;
						}
						else{
							tlc.m_tLineCol12.cCol1=(char)j;
						}
					}
					else{
						//if(true==bLooping){
						//	if((nStartCol==tlc.m_tLineCol12.cLine1)&&(nEndCol!=tlc.m_tLineCol12.cCol1)){
						//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
						//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
						//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
						//		for(i=nEndCol; i>j; i--){
						//			if(true==IsUsableArray(nLine, i)){
						//				if(Type!=(*this)[nLine][i]){
						//					if(-1==tlc.m_tLineCol12.cCol1){
						//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=j;
						//					}
						//					else{
						//						tlc.m_tLineCol12.cLine1=j;
						//					}
						//				}
						//				else{
						//					break;
						//				}
						//			}
						//		}
						//		if(-1==tlc.m_tLineCol12.cLine1){
						//			tlc.m_tLineCol12.cCol1=-1;
						//			tlc.SwapLineColChar();
						//		}
						//		else{
						//			nEndCol=tlc.m_tLineCol12.cLine1-1;
						//		}
						//	}
						//}
						if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
							if(NULL!=pvtLineCol){
								pvtLineCol->push_back(tlc);
							}
						}
						tlc.SetLineCol(-1, -1, -1 ,-1);
					}
				}
			}
		}
		if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
			if(true==bLooping){
				if((nEndCol==tlc.m_tLineCol12.cCol1)&&(nStartCol!=tlc.m_tLineCol12.cLine1)){
					for(i=nStartCol; i<nEndCol; i++){
						if(true==IsUsableArray(nLine, i)){
							if(true==bTypeSame){
								if(Type==(*this)[nLine][i]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)i;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)i;
									}
								}
								else{
									break;
								}
							}
							else{
								if(Type!=(*this)[nLine][i]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)i;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)i;
									}
								}
								else{
									break;
								}
							}
						}
					}
					if(-1==tlc.m_tLineCol12.cCol2){
						tlc.m_tLineCol12.cLine2=-1;
					}
				}
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlc);
			}
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::ContinueFillLinesToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nCol, TYPE Type, bool bTypeSame, bool bLooping, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	tLineCol tlc(-1, -1, -1, -1);
	int nFill=1;
	int nPrev=-1;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nStartLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return;
		for(i=nStartLine; i<=nEndLine; i++){
Restart:
			if(true==IsUsableArray(i, nCol)){
				if(true==bTypeSame){
					if(Type==(*this)[i][nCol]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=i;
						}
						else{
							tlc.m_tLineCol12.cCol1=i;
						}
						if((0==nFill)&&(-1==nPrev)){
							nPrev=i;
						}
					}
					else{
						if(0<nFill){
							if(-1==tlc.m_tLineCol12.cLine1){
								tlc.m_tLineCol12.cLine1=(char)i;
							}
							else{
								if(-1==nPrev){
									nPrev=i;
								}
								tlc.m_tLineCol12.cCol1=(char)i;
							}
							nFill--;
						}
						else{
							//if(true==bLooping){
							//	if((nStartLine==tlc.m_tLineCol12.cLine1)&&(nEndLine!=tlc.m_tLineCol12.cCol1)){
							//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
							//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
							//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
							//		for(j=nEndLine; j>i; j--){
							//			if(true==IsUsableArray(j, nCol)){
							//				if(Type==(*this)[j][nCol]){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=j;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=j;
							//					}
							//				}
							//				else if(0<nFill){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cCol1=i;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=i;
							//					}
							//					nFill--;
							//				}
							//				else{
							//					break;
							//				}
							//			}
							//		}
							//		if(-1==tlc.m_tLineCol12.cLine1){
							//			tlc.m_tLineCol12.cCol1=-1;
							//			tlc.SwapLineColChar();
							//		}
							//	}
							//}
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								i=nPrev-1;
								nPrev=-1;
							}
							else if((-1==tlc.m_tLineCol12.cCol1)&&(0==nFill)){
								i=i-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nFill=1;
						}
					}
				}
				else{
					if(Type!=(*this)[i][nCol]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=i;
						}
						else{
							tlc.m_tLineCol12.cCol1=i;
						}
						if((0==nFill)&&(-1==nPrev)){
							nPrev=i;
						}
					}
					else{
						if(0<nFill){
							if(-1==tlc.m_tLineCol12.cLine1){
								tlc.m_tLineCol12.cLine1=(char)i;
							}
							else{
								if(-1==nPrev){
									nPrev=i;
								}
								tlc.m_tLineCol12.cCol1=(char)i;
							}
							nFill--;
						}
						else{
							//if(true==bLooping){
							//	if((nStartLine==tlc.m_tLineCol12.cLine1)&&(nEndLine!=tlc.m_tLineCol12.cCol1)){
							//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
							//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
							//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
							//		for(j=nEndLine; j>i; j--){
							//			if(true==IsUsableArray(j, nCol)){
							//				if(Type!=(*this)[j][nCol]){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=j;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=j;
							//					}
							//				}
							//				else if(0<nFill){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cCol1=i;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=i;
							//					}
							//					nFill--;
							//				}
							//				else{
							//					break;
							//				}
							//			}
							//		}
							//		if(-1==tlc.m_tLineCol12.cLine1){
							//			tlc.m_tLineCol12.cCol1=-1;
							//			tlc.SwapLineColChar();
							//		}
							//	}
							//}
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								i=nPrev-1;
								nPrev=-1;
							}
							else if((-1==tlc.m_tLineCol12.cCol1)&&(0==nFill)){
								i=i-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nFill=1;
						}
					}
				}
			}
		}
		if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
			if(true==bLooping){
				if((nEndLine==tlc.m_tLineCol12.cCol1)&&(nStartLine!=tlc.m_tLineCol12.cLine1)){
					for(j=nStartLine; j<nEndLine; j++){
						if(true==IsUsableArray(j, nCol)){
							if(true==bTypeSame){
								if(Type==(*this)[j][nCol]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)j;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)j;
									}
								}
								else if(0<nFill){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cLine2=(char)j;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)j;
									}
									nFill--;
								}
								else{
									break;
								}
							}
							else{
								if(Type!=(*this)[j][nCol]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)j;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)j;
									}
								}
								else if(0<nFill){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cLine2=(char)j;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)j;
									}
									nFill--;
								}
								else{
									break;
								}
							}
						}
					}
					if(-1==tlc.m_tLineCol12.cCol2){
						tlc.m_tLineCol12.cLine2=-1;
					}
				}
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlc);
			}
		}
		if(-1!=nPrev){
			i=nPrev;
			nPrev=-1;
			tlc.SetLineCol(-1, -1, -1, -1);
			nFill=1;
			goto Restart;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::ContinueFillColsToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, TYPE Type, bool bTypeSame, bool bLooping, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	int nCnt=0;
	tLineCol tlc(-1, -1, -1, -1);
	int nFill=1;
	int nPrev=-1;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return nCnt;
		nCnt++;
		for(j=nStartCol; j<=nEndCol; j++){
			if(true==IsUsableArray(nLine, j)){
				if(true==bTypeSame){
					if(Type==(*this)[nLine][j]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=(char)j;
						}
						else{
							tlc.m_tLineCol12.cCol1=(char)j;
						}
						if((0==nFill)&&(-1==nPrev)){
							nPrev=j;
						}
					}
					else{
						if(0<nFill){
							if(-1==tlc.m_tLineCol12.cLine1){
								tlc.m_tLineCol12.cLine1=(char)j;
							}
							else{
								if(-1==nPrev){
									nPrev=j;
								}
								tlc.m_tLineCol12.cCol1=(char)j;
							}
							nFill--;
						}
						else{
							//if(true==bLooping){
							//	if((nStartCol==tlc.m_tLineCol12.cLine1)&&(nEndCol!=tlc.m_tLineCol12.cCol1)){
							//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
							//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
							//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
							//		for(i=nEndCol; i>j; i--){
							//			if(true==IsUsableArray(nLine, i)){
							//				if(Type==(*this)[nLine][i]){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=i;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=i;
							//					}
							//				}
							//				else if(0<nFill){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cCol1=i;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=i;
							//					}
							//					nFill--;
							//				}
							//				else{
							//					break;
							//				}
							//			}
							//		}
							//		if(-1==tlc.m_tLineCol12.cLine1){
							//			tlc.m_tLineCol12.cCol1=-1;
							//			tlc.SwapLineColChar();
							//		}
							//		else{
							//			nEndCol=tlc.m_tLineCol12.cLine1;
							//		}
							//	}
							//}
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								j=nPrev-1;
								nPrev=-1;
							}
							else if((-1==tlc.m_tLineCol12.cCol1)&&(0==nFill)){
								j=j-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nFill=1;
						}
					}
				}
				else{
					if(Type!=(*this)[nLine][j]){
						if(-1==tlc.m_tLineCol12.cLine1){
							tlc.m_tLineCol12.cCol1=tlc.m_tLineCol12.cLine1=j;
						}
						else{
							tlc.m_tLineCol12.cCol1=j;
						}
						if((0==nFill)&&(-1==nPrev)){
							nPrev=j;
						}
					}
					else{
						if(0<nFill){
							if(-1==tlc.m_tLineCol12.cLine1){
								tlc.m_tLineCol12.cLine1=(char)j;
							}
							else{
								if(-1==nPrev){
									nPrev=j;
								}
								tlc.m_tLineCol12.cCol1=(char)j;
							}
							nFill--;
						}
						else{
							//if(true==bLooping){
							//	if((nStartCol==tlc.m_tLineCol12.cLine1)&&(nEndCol!=tlc.m_tLineCol12.cCol1)){
							//		tlc.m_tLineCol12.cLine2=tlc.m_tLineCol12.cLine1;
							//		tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cCol1;
							//		tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=-1;
							//		for(i=nEndCol; i>j; i--){
							//			if(true==IsUsableArray(nLine, i)){
							//				if(Type!=(*this)[nLine][i]){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cLine1=tlc.m_tLineCol12.cCol1=i;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=i;
							//					}
							//				}
							//				else if(0<nFill){
							//					if(-1==tlc.m_tLineCol12.cCol1){
							//						tlc.m_tLineCol12.cCol1=i;
							//					}
							//					else{
							//						tlc.m_tLineCol12.cLine1=i;
							//					}
							//					nFill--;
							//				}
							//				else{
							//					break;
							//				}
							//			}
							//		}
							//		if(-1==tlc.m_tLineCol12.cLine1){
							//			tlc.m_tLineCol12.cCol1=-1;
							//			tlc.SwapLineColChar();
							//		}
							//		else{
							//			nEndCol=tlc.m_tLineCol12.cLine1;
							//		}
							//	}
							//}
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								j=nPrev-1;
								nPrev=-1;
							}
							else if((-1==tlc.m_tLineCol12.cCol1)&&(0==nFill)){
								j=j-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nFill=1;
						}
					}
				}
			}
		}
		if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
			if(true==bLooping){
				if((nEndCol==tlc.m_tLineCol12.cCol1)&&(nStartCol!=tlc.m_tLineCol12.cLine1)){
					for(i=nStartCol; i<nEndCol; i++){
						if(true==IsUsableArray(nLine, i)){
							if(true==bTypeSame){
								if(Type==(*this)[nLine][i]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)i;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)i;
									}
								}
								else if(0<nFill){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cLine2=(char)i;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)i;
									}
									nFill--;
								}
								else{
									break;
								}
							}
							else{
								if(Type!=(*this)[nLine][i]){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cCol2=tlc.m_tLineCol12.cLine2=(char)i;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)i;
									}
								}
								else if(0<nFill){
									if(-1==tlc.m_tLineCol12.cLine2){
										tlc.m_tLineCol12.cLine2=(char)i;
									}
									else{
										tlc.m_tLineCol12.cCol2=(char)i;
									}
									nFill--;
								}
								else{
									break;
								}
							}
						}
					}
					if(-1==tlc.m_tLineCol12.cCol2){
						tlc.m_tLineCol12.cLine2=-1;
					}
				}
			}
			if(NULL!=pvtLineCol){
				pvtLineCol->push_back(tlc);
			}
		}
		if(-1!=nPrev){
			j=nPrev;
			nPrev=-1;
			tlc.SetLineCol(-1, -1, -1, -1);
			nFill=1;
			goto Restart;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::ContinueDiffLinesToColVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nCol, int nDiffCnt, TYPE Type, bool bTypeSame, bool bLooping, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	tLineCol tlc(-1, -1, -1, -1);
	int nDiff=nDiffCnt;
	int nPrev=-1;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nStartLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return;
		for(i=nStartLine; i<=nEndLine; i++){
Restart:
			if(true==IsUsableArray(i, nCol)){
				if(true==bTypeSame){
					if(Type==(*this)[i][nCol]){
						if((-1==tlc.m_tLineCol12.cLine1)&&(nDiffCnt==nDiff)){
							tlc.m_tLineCol12.cLine1=(char)i;
						}
						else if(0==nDiff){
							tlc.m_tLineCol12.cCol1=(char)i;
						}
						if(nDiffCnt>nDiff){
							if(-1==nPrev){
								nPrev=i;
							}
						}
					}
					else{
						if((-1!=tlc.m_tLineCol12.cLine1)&&(0<nDiff)){
							nDiff--;
						}
						else{
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								i=nPrev-1;
								nPrev=-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nDiff=nDiffCnt;
						}
					}
				}
				else{
					if(Type!=(*this)[i][nCol]){
						if((-1==tlc.m_tLineCol12.cLine1)&&(nDiffCnt==nDiff)){
							tlc.m_tLineCol12.cLine1=(char)i;
						}
						else if(0==nDiff){
							tlc.m_tLineCol12.cCol1=(char)i;
						}
						if(nDiffCnt>nDiff){
							if(-1==nPrev){
								nPrev=i;
							}
						}
					}
					else{
						if((-1!=tlc.m_tLineCol12.cLine1)&&(0<nDiff)){
							nDiff--;
						}
						else{
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								i=nPrev-1;
								nPrev=-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nDiff=nDiffCnt;
						}
					}
				}
			}
		}
		if(-1!=tlc.m_tLineCol12.cLine1){
			if(-1==tlc.m_tLineCol12.cCol1){
				if(true==bLooping){
					tlc.m_tLineCol12.cCol1=nEndLine;
					tlc.m_tLineCol12.cLine2=nStartLine;
					for(j=nStartLine; j<nEndLine; j++){
						if(true==IsUsableArray(j, nCol)){
							if(true==bTypeSame){
								if(Type==(*this)[j][nCol]){
									if(0==nDiff){
										tlc.m_tLineCol12.cCol2=(char)j;
									}
								}
								else{
									if(0<nDiff){
										nDiff--;
									}
									else{
										break;
									}
								}
							}
							else{
								if(Type!=(*this)[j][nCol]){
									if(0==nDiff){
										tlc.m_tLineCol12.cCol2=(char)j;
									}
								}
								else{
									if(0<nDiff){
										nDiff--;
									}
									else{
										break;
									}
								}
							}
						}
					}
					if(-1==tlc.m_tLineCol12.cCol2){
						tlc.m_tLineCol12.cLine2=-1;
						tlc.m_tLineCol12.cCol1=-1;
					}
					if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlc);
						}
					}
				}
			}
			else{
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlc);
				}
			}
		}
		if(-1!=nPrev){
			i=nPrev;
			nPrev=-1;
			tlc.SetLineCol(-1, -1, -1, -1);
			nDiff=nDiffCnt;
			goto Restart;
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVVector<TYPE>::ContinueDiffColsToLineVector(int nStartLine, int nEndLine, int nStartCol, int nEndCol, int nLine, int nDiffCnt, TYPE Type, bool bTypeSame, bool bLooping, vector<tLineCol>* pvtLineCol)
{
	int nLineTotal=(int)size();
	int nColTotal=0;
	int i=0, j=0;
	int nCnt=0;
	tLineCol tlc(-1, -1, -1, -1);
	int nDiff=nDiffCnt;
	int nPrev=-1;
	nStartLine=InRangeValue(0, nLineTotal-1, nStartLine);
	nEndLine=InRangeValue(0, nLineTotal-1, nEndLine);
	if(NULL!=pvtLineCol){
		pvtLineCol->clear();
	}
	if(true==TotalVector(nLine, nColTotal)){
		nStartCol=InRangeValue(0, nColTotal-1, nStartCol);
		nEndCol=InRangeValue(0, nColTotal-1, nEndCol);
		if(false==IsInRange(nCol, nStartCol, nEndCol)) return nCnt;
		nCnt++;
		for(j=nStartCol; j<=nEndCol; j++){
			if(true==IsUsableArray(nLine, j)){
				if(true==bTypeSame){
					if(Type!=(*this)[nLine][j]){
						if((-1==tlc.m_tLineCol12.cLine1)&&(nDiffCnt==nDiff)){
							tlc.m_tLineCol12.cLine1=(char)j;
						}
						else if(0==nDiff){
							tlc.m_tLineCol12.cCol1=(char)j;
						}
						if(nDiffCnt>nDiff){
							if(-1==nPrev){
								nPrev=j;
							}
						}
					}
					else{
						if((-1!=tlc.m_tLineCol12.cLine1)&&(0<nDiff)){
							nDiff--;
						}
						else{
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								j=nPrev-1;
								nPrev=-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nDiff=nDiffCnt;
						}
					}
				}
				else{
					if(Type!=(*this)[nLine][j]){
						if((-1==tlc.m_tLineCol12.cLine1)&&(nDiffCnt==nDiff)){
							tlc.m_tLineCol12.cLine1=(char)j;
						}
						else if(0==nDiff){
							tlc.m_tLineCol12.cCol1=(char)j;
						}
						if(nDiffCnt>nDiff){
							if(-1==nPrev){
								nPrev=j;
							}
						}
					}
					else{
						if((-1!=tlc.m_tLineCol12.cLine1)&&(0<nDiff)){
							nDiff--;
						}
						else{
							if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
								if(NULL!=pvtLineCol){
									pvtLineCol->push_back(tlc);
								}
							}
							if(-1!=nPrev){
								j=nPrev-1;
								nPrev=-1;
							}
							tlc.SetLineCol(-1, -1, -1 ,-1);
							nDiff=nDiffCnt;
						}
					}
				}
			}
		}
		if(-1!=tlc.m_tLineCol12.cLine1){
			if(-1==tlc.m_tLineCol12.cCol1){
				if(true==bLooping){
					tlc.m_tLineCol12.cCol1=nEndCol;
					tlc.m_tLineCol12.cLine2=nStartCol;
					for(i=nStartCol; i<nEndCol; i++){
						if(true==IsUsableArray(nLine, i)){
							if(true==bTypeSame){
								if(Type==(*this)[nLine][i]){
									if(0==nDiff){
										tlc.m_tLineCol12.cCol2=(char)i;
									}
								}
								else{
									if(0<nDiff){
										nDiff--;
									}
									else{
										break;
									}
								}
							}
							else{
								if(Type!=(*this)[nLine][i]){
									if(0==nDiff){
										tlc.m_tLineCol12.cCol2=(char)i;
									}
								}
								else{
									if(0<nDiff){
										nDiff--;
									}
									else{
										break;
									}
								}
							}
						}
					}
					if(-1==tlc.m_tLineCol12.cCol2){
						tlc.m_tLineCol12.cLine2=-1;
						tlc.m_tLineCol12.cCol1=-1;
					}
					if((-1!=tlc.m_tLineCol12.cLine1)&&(-1!=tlc.m_tLineCol12.cCol1)){
						if(NULL!=pvtLineCol){
							pvtLineCol->push_back(tlc);
						}
					}
				}
			}
			else{
				if(NULL!=pvtLineCol){
					pvtLineCol->push_back(tlc);
				}
			}
		}
		if(-1!=nPrev){
			j=nPrev;
			nPrev=-1;
			tlc.SetLineCol(-1, -1, -1, -1);
			nDiff=nDiffCnt;
			goto Restart;
		}
	}
}


#pragma warning(default : 4786)
#endif
