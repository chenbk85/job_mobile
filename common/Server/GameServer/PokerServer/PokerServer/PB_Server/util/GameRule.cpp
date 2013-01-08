#include "stdafx.h"
#include "PublicFunc.h"
#include "StaticFunc.h"

#include "../include/xtmpl.h"

#include "../../Protocol Buffers/Poker/AdlGameCommon.h"

using namespace adl;

//------------------------------------------------------------------//
// ¿À¸£±â
//------------------------------------------------------------------//
void Sort_Ascend(int Start, int End, void* pVoid, int (*Function)(void* pVoid, int nArrayNum), void (*Swap)(void* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	int Value=0;
	int pivot=Function(pVoid, Start);
	while(i<j){
		while((Value=Function(pVoid, i))>=pivot){
			i++;
			if(i>End){
				i=End;
				break;
			}
		}
		while((Value=Function(pVoid, j))<=pivot){
			j--;
			if(j<Start){
				j=Start;
				break;
			}
		}
		if(i<j){
			Swap(pVoid, i, j);
		}
	}
	if(pivot<Function(pVoid, j)){
		Swap(pVoid, Start, j);
	}
	Sort_Ascend(Start, j-1, pVoid, Function, Swap);
	Sort_Ascend(j+1, End, pVoid, Function, Swap);
}
//------------------------------------------------------------------//
//³»¸®±â
//------------------------------------------------------------------//
void Sort_Descend(int Start, int End, void* pVoid, int (*Function)(void* pVoid, int nArrayNum), void (*Swap)(void* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	int Value=0;
	int pivot=Function(pVoid, Start);
	while(i<j){
		while((Value=Function(pVoid, i))<=pivot){
			i++;
			if(i>End){
				i=End;
				break;
			}
		}
		while((Value=Function(pVoid, j))>=pivot){
			j--;
			if(j<Start){
				j=Start;
				break;
			}
		}
		if(i<j){
			Swap(pVoid, i, j);
		}
	}
	if(pivot>Function(pVoid, j)){
		Swap(pVoid, Start, j);
	}
	Sort_Descend(Start, j-1, pVoid, Function, Swap);
	Sort_Descend(j+1, End, pVoid, Function, Swap);
}

//------------------------------------------------------------------//
// ¿À¸£±â
//------------------------------------------------------------------//
void Sort_Ascend(int Start, int End, int nReserve, void* pVoid, int (*Function)(void* pVoid, int nArrayNum, int nReserve), void (*Swap)(void* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	int Value=0;
	int pivot=Function(pVoid, Start, nReserve);
	while(i<j){
		while((Value=Function(pVoid, i, nReserve))>=pivot){
			i++;
			if(i>End){
				i=End;
				break;
			}
		}
		while((Value=Function(pVoid, j, nReserve))<=pivot){
			j--;
			if(j<Start){
				j=Start;
				break;
			}
		}
		if(i<j){
			Swap(pVoid, i, j);
		}
	}
	if(pivot<Function(pVoid, j, nReserve)){
		Swap(pVoid, Start, j);
	}
	Sort_Ascend(Start, j-1, nReserve, pVoid, Function, Swap);
	Sort_Ascend(j+1, End, nReserve, pVoid, Function, Swap);
}
//------------------------------------------------------------------//
//³»¸®±â
//------------------------------------------------------------------//
void Sort_Descend(int Start, int End, int nReserve, void* pVoid, int (*Function)(void* pVoid, int nArrayNum, int nReserve), void (*Swap)(void* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	int Value=0;
	int pivot=Function(pVoid, Start, nReserve);
	while(i<j){
		while((Value=Function(pVoid, i, nReserve))<=pivot){
			i++;
			if(i>End){
				i=End;
				break;
			}
		}
		while((Value=Function(pVoid, j, nReserve))>=pivot){
			j--;
			if(j<Start){
				j=Start;
				break;
			}
		}
		if(i<j){
			Swap(pVoid, i, j);
		}
	}
	if(pivot>Function(pVoid, j, nReserve)){
		Swap(pVoid, Start, j);
	}
	Sort_Descend(Start, j-1, nReserve, pVoid, Function, Swap);
	Sort_Descend(j+1, End, nReserve, pVoid, Function, Swap);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void Sort_Ascend(vector<int>* pvVector)
{
	if(NULL==pvVector) return;
	Sort_Ascend(0, ((int)pvVector->size()-1), pvVector, GetVector, SwapVector);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void Sort_Descend(vector<int>* pvVector)
{
	if(NULL==pvVector) return;
	Sort_Descend(0, ((int)pvVector->size()-1), pvVector, GetVector, SwapVector);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void Sort_Ascend3(vector<tInt3>* pvVector, int nSortInt)
{
	if(NULL==pvVector) return;
	Sort_Ascend(0, ((int)pvVector->size()-1), nSortInt, pvVector, GetVector3, SwapVector3);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void Sort_Descend3(vector<tInt3>* pvVector, int nSortInt)
{
	if(NULL==pvVector) return;
	Sort_Descend(0, ((int)pvVector->size()-1), nSortInt, pvVector, GetVector3, SwapVector3);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int GetVector(void* pvVoid, int nArray)
{
	vector<int>* pvVector=(vector<int>*)(pvVoid);
	if(NULL==pvVector) return 0;
	if((0>nArray)||((int)pvVector->size()<=nArray)) return 0;
	return (*pvVector)[nArray];
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void SwapVector(void* pvVoid, int nSwap1, int nSwap2)
{
	vector<int>* pvVector=(vector<int>*)(pvVoid);
	if(NULL==pvVector) return;
	if((0>nSwap1)||((int)pvVector->size()<=nSwap1)) return;
	if((0>nSwap2)||((int)pvVector->size()<=nSwap2)) return;
	int nVector=(*pvVector)[nSwap1];
	(*pvVector)[nSwap1]=(*pvVector)[nSwap2];
	(*pvVector)[nSwap2]=nVector;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int GetVector3(void* pvVoid, int nArray, int nReserve)
{
	vector<tInt3>* pvVector=(vector<tInt3>*)(pvVoid);
	if(NULL==pvVector) return 0;
	if((0>nArray)||((int)pvVector->size()<=nArray)) return 0;
	if(2==nReserve){
		return (*pvVector)[nArray].nInt3;
	}
	else if(1==nReserve){
		return (*pvVector)[nArray].nInt2;
	}
	return (*pvVector)[nArray].nInt1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void SwapVector3(void* pvVoid, int nSwap1, int nSwap2)
{
	vector<tInt3>* pvVector=(vector<tInt3>*)(pvVoid);
	if(NULL==pvVector) return;
	if((0>nSwap1)||((int)pvVector->size()<=nSwap1)) return;
	if((0>nSwap2)||((int)pvVector->size()<=nSwap2)) return;
	tInt3 tInt3Value=(*pvVector)[nSwap1];
	(*pvVector)[nSwap1]=(*pvVector)[nSwap2];
	(*pvVector)[nSwap2]=tInt3Value;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void SameVector_int(vector<int>* pvVector, vector<int>* pvSame, vector<int>* pvRest)
{
	if(NULL==pvVector) return;
	if(NULL==pvSame) return;
	int nSame=0;
	bool bSame=FALSE;
	int nTotal=(int)pvVector->size();
	for(int i=0; i<nTotal-1; i++){
		for(int j=i+1; j<nTotal; j++){
			if((*pvVector)[i]==(*pvVector)[j]){
				nSame=(int)pvSame->size();
				bSame=FALSE;
				for(int k=0; k<nSame; k++){
					if((*pvVector)[i]==(*pvSame)[k]){
						bSame=TRUE;
						break;
					}
				}
				if(FALSE==bSame){
					pvSame->push_back((*pvVector)[i]);
				}
			}
		}
	}
	if(NULL!=pvRest){
		for(int i=0; i<nTotal; i++){
			nSame=(int)pvSame->size();
			bSame=FALSE;
			for(int k=0; k<nSame; k++){
				if((*pvVector)[i]==(*pvSame)[k]){
					bSame=TRUE;
					break;
				}
			}
			if(FALSE==bSame){
				pvRest->push_back((*pvVector)[i]);
			}
		}
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void SameVector_long(vector<long>* pvVector, vector<long>* pvSame, vector<long>* pvRest)
{
	if(NULL==pvVector) return;
	if(NULL==pvSame) return;
	int nSame=0;
	bool bSame=FALSE;
	int nTotal=(int)pvVector->size();
	for(int i=0; i<nTotal-1; i++){
		for(int j=i+1; j<nTotal; j++){
			if((*pvVector)[i]==(*pvVector)[j]){
				nSame=(int)pvSame->size();
				bSame=FALSE;
				for(int k=0; k<nSame; k++){
					if((*pvVector)[i]==(*pvSame)[k]){
						bSame=TRUE;
						break;
					}
				}
				if(FALSE==bSame){
					pvSame->push_back((*pvVector)[i]);
				}
			}
		}
	}
	if(NULL!=pvRest){
		for(int i=0; i<nTotal; i++){
			nSame=(int)pvSame->size();
			bSame=FALSE;
			for(int k=0; k<nSame; k++){
				if((*pvVector)[i]==(*pvSame)[k]){
					bSame=TRUE;
					break;
				}
			}
			if(FALSE==bSame){
				pvRest->push_back((*pvVector)[i]);
			}
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void RectClear(RECT &rRect)
{
	rRect.left=rRect.right=rRect.top=rRect.bottom=0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
void PointClear(POINT &pPoint)
{
	pPoint.x=pPoint.y=0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int RectToWidth(RECT rRect)
{
	return rRect.right-rRect.left;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int RectToHeight(RECT rRect)
{
	return rRect.bottom-rRect.top;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT RectToTL(RECT rRect)
{
	POINT pt={0, 0};
	pt.x=rRect.left;
	pt.y=rRect.top;
	return pt;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT RectToBR(RECT rRect)
{
	POINT pt={0, 0};
	pt.x=rRect.right;
	pt.y=rRect.bottom;
	return pt;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT RectToTR(RECT rRect)
{
	POINT pt={0, 0};
	pt.x=rRect.right;
	pt.y=rRect.top;
	return pt;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT RectToBL(RECT rRect)
{
	POINT pt={0, 0};
	pt.x=rRect.left;
	pt.y=rRect.bottom;
	return pt;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT PointXY(int x, int y)
{
	POINT pPos = { x, y };
	return pPos;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
RECT RectWH(int x, int y, int cx, int cy)
{
	RECT rRect = { x, y, x + cx, y + cy };
	return rRect;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
RECT RectLTRB(int left, int top, int right, int bottom)
{
	RECT rRect = { left, top, right, bottom };
	return rRect;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
RECT RectToCenter(RECT rRect, int nWidth, int nHeight)
{
	RECT rCenter={0, 0, 0, 0};
	int nX=((rRect.right-rRect.left)-nWidth)/2;
	int nY=((rRect.bottom-rRect.top)-nHeight)/2;
	rCenter.left=rRect.left+nX;
	rCenter.top=rRect.top+nY;
	rCenter.right=rRect.right-nX;
	rCenter.bottom=rRect.bottom-nY;
	return rCenter;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
RECT RectToCenter(RECT rRect, float fPerWidth, float fPerHeight)
{
	RECT rCenter={0, 0, 0, 0};
	int nWidth=FLOATtoINT((float)(rRect.right-rRect.left)*fPerWidth);
	int nHeight=FLOATtoINT((float)(rRect.bottom-rRect.top)*fPerHeight);
	int nX=((rRect.right-rRect.left)-nWidth)/2;
	int nY=((rRect.bottom-rRect.top)-nHeight)/2;
	rCenter.left=rRect.left+nX;
	rCenter.top=rRect.top+nY;
	rCenter.right=rRect.right-nX;
	rCenter.bottom=rRect.bottom-nY;
	return rCenter;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
RECT CutRectTL(RECT rRect, SIZE sSize)
{
	rRect.left+=sSize.cx;
	rRect.right-=sSize.cx;
	return rRect;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
RECT CutRectBR(RECT rRect, SIZE sSize)
{
	rRect.top+=sSize.cy;
	rRect.bottom-=sSize.cy;
	return rRect;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
RECT CutRect(RECT rRect, SIZE sSize)
{
	rRect.left+=sSize.cx;
	rRect.right-=sSize.cx;
	rRect.top+=sSize.cy;
	rRect.bottom-=sSize.cy;
	return rRect;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT Circle(int nRadius)
{
	POINT pt={0,};
	if(0==nRadius) return pt;
	int nRadius1=IRandom(nRadius);
	float fAngle=(float)IRandom(360);
	float fRadian=(float)D3DToRadian(fAngle);
	pt.x=(int)(nRadius1*cosf(fRadian))+nRadius;
	pt.y=(int)(nRadius1*sinf(fRadian))+nRadius;
	return pt;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT Circle(POINT pPos, int nRadius)
{
	POINT pt={0,};
	if(0==nRadius) return pt;
	int nRadius1=IRandom(nRadius);
	float fAngle=(float)IRandom(360);
	float fRadian=(float)D3DToRadian(fAngle);
	pt.x=(int)(nRadius1*cosf(fRadian))+pPos.x+nRadius;
	pt.y=(int)(nRadius1*sinf(fRadian))+pPos.y+nRadius;
	return pt;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool InCircle(POINT pCheckPos, POINT pPos, int nRadius)
{
	POINT pCenterPos={0,};
	pCenterPos.x=pPos.x+nRadius;
	pCenterPos.y=pPos.y+nRadius;
	return ((nRadius>=Pythagoras2(pCheckPos.x, pCheckPos.y, pCenterPos.x, pCenterPos.y))?(TRUE):(FALSE));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool IsSamePoint(POINT pPoint1, POINT pPoint2)
{
	if(pPoint1.x!=pPoint2.x) return FALSE;
	if(pPoint1.y!=pPoint2.y) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool IsSameRect(RECT rRect1, RECT rRect2)
{
	if(rRect1.left!=rRect2.left) return FALSE;
	if(rRect1.top!=rRect2.top) return FALSE;
	if(rRect1.right!=rRect2.right) return FALSE;
	if(rRect1.bottom!=rRect2.bottom) return FALSE;
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------//
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CIDVector::AddVector(unsigned int nIdenty, int nValue)
{
	int nArray=(int)size();
	push_back(PairVector(nIdenty, nValue));
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CIDVector::FindAddVector(unsigned int nIdenty, int nValue)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(nIdenty==vtIterater->first){
			vtIterater->second=nValue;
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(nIdenty, nValue);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CIDVector::FindVector(unsigned int nIdenty)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(nIdenty==vtIterater->first){
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CIDVector::FindDelVector(unsigned int nIdenty)
{
	int nFind=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(nIdenty==vtIterater->first){
			nFind=(int)(vtIterater-begin());
			vtIterater=erase(vtIterater);
			return nFind;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CIDVector::DelVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return FALSE;

	//iterator »ç¿ëÇÔ
	CIDVector::iterator it = this->begin();
	erase(it + nArray);
	//erase(&(*this)[nArray]);
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CIDVector::GetVector(int nArray, int &nValue)
{
	if((0>nArray)||((int)size()<=nArray)) return FALSE;

	nValue=(*this)[nArray].second;
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CIDVector::GetVector(int nArray, unsigned int &nIdenty, int &nValue)
{
	if((0>nArray)||((int)size()<=nArray)) return FALSE;
	nIdenty=(*this)[nArray].first;
	nValue=(*this)[nArray].second;
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CIDVector::VectorBegin(unsigned int &nIdenty, int &nValue)
{
	if(TRUE==empty()) return FALSE;
	m_vtIterater=begin();
	nIdenty=m_vtIterater->first;
	nValue=m_vtIterater->second;
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CIDVector::VectorNext(unsigned int &nIdenty, int &nValue)
{
	m_vtIterater++;
	if(m_vtIterater==end()) return FALSE;
	nIdenty=m_vtIterater->first;
	nValue=m_vtIterater->second;
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------//
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
CIDVector CActPos_Vector::m_cUpdate;
//------------------------------------------------------------------//
int CActPos_Vector::GetActPos_Time(void)
{
	int nTotal=(int)size();
	if(0==nTotal) return 0;
	int nTime=0;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		if(FALSE==pcActPos_Clock->IsClock()) continue;
		if(nTime<pcActPos_Clock->EndClock()){
			nTime=pcActPos_Clock->EndClock();
		}
	}	
	return nTime;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_AreaToPos(POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(TRUE==(bool)empty()) return FALSE;
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	int nTotal=(int)size();
	if(0==nTotal) return FALSE;
	POINT pPos;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock->SetActPos_Clock(tAct::ACT_NOIDENTY, tAct::ACT_NOSET, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_AreaToPos(RECT rArea, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	POINT pBase=::RectToTL(rArea);
	int nWidth=::RectToWidth(rArea);
	int nHeight=::RectToHeight(rArea);
	return ActPos_Vector_AreaToPos(pBase, nWidth, nHeight, nPosTotal, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_AreaToDel(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(TRUE==(bool)empty()) return FALSE;
	if(FALSE==DelActPos_Vector(nArray)) return FALSE;
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	int nTotal=(int)size();
	if(0==nTotal) return FALSE;
	POINT pPos;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock->SetActPos_Clock(tAct::ACT_NOIDENTY, tAct::ACT_NOSET, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_AreaToDel(int nArray, RECT rArea, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	POINT pBase=::RectToTL(rArea);
	int nWidth=::RectToWidth(rArea);
	int nHeight=::RectToHeight(rArea);
	return ActPos_Vector_AreaToDel(nArray, pBase, nWidth, nHeight, nPosTotal, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffFront(POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(0, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pEnd;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		pPos.x+=pDiff.x;
		pPos.y+=pDiff.y;
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffBack(POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nTotal-1, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pEnd;
	for(int i=nTotal-1; i>=0; i--){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		pPos.x-=pDiff.x;
		pPos.y-=pDiff.y;
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffFront(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	POINT pEnd=GetActPos_Pos_Front(0, pBase, nWidth, nHeight, nPosTotal);
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		pEnd.x+=pDiff.x;
		pEnd.y+=pDiff.y;
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffBack(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	POINT pEnd=GetActPos_Pos_Front(nPosTotal-1, pBase, nWidth, nHeight, nPosTotal);
	for(int i=nTotal-1; i>=0; i--){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		pEnd.x-=pDiff.x;
		pEnd.y-=pDiff.y;
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPos(POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(0==nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) return FALSE;
		POINT pEnd=pcActPos_Clock->pEnd;
		pEnd.x+=pDiff.x;
		pEnd.y+=pDiff.y;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPos(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(0==nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) return FALSE;
		POINT pEnd=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		pEnd.x+=pDiff.x;
		pEnd.y+=pDiff.y;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPosReturn(POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(0==nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) return FALSE;
		POINT pMiddle=pcActPos_Clock->pEnd;
		pMiddle.x+=pDiff.x;
		pMiddle.y+=pDiff.y;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pMiddle, pcActPos_Clock->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPosReturn(POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(0==nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) return FALSE;
		POINT pEnd=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		POINT pMiddle=pEnd;
		pMiddle.x+=pDiff.x;
		pMiddle.y+=pDiff.y;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pMiddle, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPos(int nArray, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	POINT pEnd=pcActPos_Clock->pEnd;
	pEnd.x+=pDiff.x;
	pEnd.y+=pDiff.y;
	pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPos(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	POINT pEnd=GetActPos_Pos_Front(nArray, pBase, nWidth, nHeight, nPosTotal);
	pEnd.x+=pDiff.x;
	pEnd.y+=pDiff.y;
	pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPosReturn(int nArray, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	POINT pMiddle=pcActPos_Clock->pEnd;
	pMiddle.x+=pDiff.x;
	pMiddle.y+=pDiff.y;
	pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pMiddle, pcActPos_Clock->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_DiffPosReturn(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, POINT pDiff, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	POINT pEnd=GetActPos_Pos_Front(nArray, pBase, nWidth, nHeight, nPosTotal);
	POINT pMiddle=pEnd;
	pMiddle.x+=pDiff.x;
	pMiddle.y+=pDiff.y;
	pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pMiddle, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_StepFront(int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(0, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pCur;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, pcActPos_Clock->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_StepBack(int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nTotal-1, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pCur;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, pcActPos_Clock->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_StepArray(int nArray, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pCur;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, pcActPos_Clock->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_StepFront(POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(0, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pCur;
	POINT pEnd;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pEnd=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_StepBack(POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nTotal-1, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pCur;
	POINT pEnd;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pEnd=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_StepArray(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	if(1>=nTotal) return FALSE;
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	POINT pPos=pcActPos_Clock->pCur;
	POINT pEnd;
	for(int i=0; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pEnd=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_ChangePos(int nArray, int nIdenty, int nType, int nMessage, POINT pPos, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pcActPos_Clock->pCur, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_ChangePosComeAndGo(int nArray, int nIdenty, int nType, int nMessage, POINT pPos, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pcActPos_Clock->pCur, pPos, pcActPos_Clock->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_MovePos(int nArray, POINT pPos, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_MovePos(int nArray, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	int nTotal=(int)size();
	if(0==nTotal) return FALSE;
	POINT pPos=GetActPos_Pos_Front(nArray, pBase, nWidth, nHeight, nPosTotal);
	pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_MovePosComeAndGo(int nArray, POINT pPos, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pPos, pcActPos_Clock->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_MoveArray(int nArray1, int nArray2, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(nArray1==nArray2) return FALSE;
	CActPos_Clock* pcActPos_Clock1=NULL;
	CActPos_Clock* pcActPos_Clock2=NULL;
	if(FALSE==GetActPos_Vector(nArray1, &pcActPos_Clock1)) return FALSE;
	if(FALSE==GetActPos_Vector(nArray2, &pcActPos_Clock2)) return FALSE;
	pcActPos_Clock1->SetActPos_Clock(pcActPos_Clock1->pCur, pcActPos_Clock2->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock1->PlayActPos_Clock();
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_MoveArrayComeAndGo(int nArray1, int nArray2, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(nArray1==nArray2) return FALSE;
	CActPos_Clock* pcActPos_Clock1=NULL;
	CActPos_Clock* pcActPos_Clock2=NULL;
	if(FALSE==GetActPos_Vector(nArray1, &pcActPos_Clock1)) return FALSE;
	if(FALSE==GetActPos_Vector(nArray2, &pcActPos_Clock2)) return FALSE;
	pcActPos_Clock1->SetActPos_Clock(pcActPos_Clock1->pCur, pcActPos_Clock2->pEnd, pcActPos_Clock1->pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	pcActPos_Clock1->PlayActPos_Clock();
	return TRUE;	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_MoveArray(vector<int> ctvArray, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nArrayTotal=(int)ctvArray.size();
	if(0==nArrayTotal) return FALSE;
	int nArray=0;
	for(int i=0; i<nArrayTotal; i++){
		nArray=ctvArray[i];
		ActPos_Vector_Swap(i, nArray, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
	}
	return TRUE;	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_Swap(int nArray1, int nArray2, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(nArray1==nArray2) return FALSE;
	if(FALSE==SwapActPos_Vector(nArray1, nArray2)) return FALSE;
	CActPos_Clock* pcActPos_Clock1=NULL;
	CActPos_Clock* pcActPos_Clock2=NULL;
	int nMin=Min2(nArray1, nArray2);
	int nMax=Max2(nArray1, nArray2);
	if(FALSE==GetActPos_Vector(nMin, &pcActPos_Clock1)) return FALSE;
	if(FALSE==GetActPos_Vector(nMax, &pcActPos_Clock2)) return FALSE;
	POINT pEnd1=pcActPos_Clock1->pEnd;
	POINT pEnd2=pcActPos_Clock2->pEnd;
	if((0==m_pSelect.x)&&(0==m_pSelect.y)){
		pcActPos_Clock1->SetActPos_Clock(pcActPos_Clock1->pCur, pEnd2, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock1->PlayActPos_Clock();
		pcActPos_Clock2->SetActPos_Clock(pcActPos_Clock2->pCur, pEnd1, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock2->PlayActPos_Clock();
	}
	else{
		POINT pMiddle1;
		POINT pMiddle2;
		pMiddle1.x=(pcActPos_Clock1->pCur.x+(pEnd2.x-pcActPos_Clock1->pCur.x)/2)+m_pSelect.x;
		pMiddle1.y=(pcActPos_Clock1->pCur.y+(pEnd2.y-pcActPos_Clock1->pCur.y)/2)+m_pSelect.y;
		pMiddle2.x=(pcActPos_Clock2->pCur.x+(pEnd1.x-pcActPos_Clock2->pCur.x)/2)-m_pSelect.x;
		pMiddle2.y=(pcActPos_Clock2->pCur.y+(pEnd1.y-pcActPos_Clock2->pCur.y)/2)-m_pSelect.y;
		pcActPos_Clock1->SetActPos_Clock(pcActPos_Clock1->pCur, pMiddle1, pEnd2, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock1->PlayActPos_Clock();
		pcActPos_Clock2->SetActPos_Clock(pcActPos_Clock2->pCur, pMiddle2, pEnd1, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock2->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_SwapDistance(int nArray1, int nArray2, int nDistance, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(nArray1==nArray2) return FALSE;
	if(FALSE==SwapActPos_Vector(nArray1, nArray2)) return FALSE;
	CActPos_Clock* pcActPos_Clock1=NULL;
	CActPos_Clock* pcActPos_Clock2=NULL;
	int nMin=Min2(nArray1, nArray2);
	int nMax=Max2(nArray1, nArray2);
	if(FALSE==GetActPos_Vector(nMin, &pcActPos_Clock1)) return FALSE;
	if(FALSE==GetActPos_Vector(nMax, &pcActPos_Clock2)) return FALSE;
	POINT pEnd1=pcActPos_Clock1->pEnd;
	POINT pEnd2=pcActPos_Clock2->pEnd;
	if((0==m_pSelect.x)&&(0==m_pSelect.y)){
		pcActPos_Clock1->SetActPos_Clock_Distance(pcActPos_Clock1->pCur, pEnd2, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock1->PlayActPos_Clock();
		pcActPos_Clock2->SetActPos_Clock_Distance(pcActPos_Clock2->pCur, pEnd1, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock2->PlayActPos_Clock();
	}
	else{
		POINT pMiddle1;
		POINT pMiddle2;
		pMiddle1.x=(pcActPos_Clock1->pCur.x+(pEnd2.x-pcActPos_Clock1->pCur.x)/2)+m_pSelect.x;
		pMiddle1.y=(pcActPos_Clock1->pCur.y+(pEnd2.y-pcActPos_Clock1->pCur.y)/2)+m_pSelect.y;
		pMiddle2.x=(pcActPos_Clock2->pCur.x+(pEnd1.x-pcActPos_Clock2->pCur.x)/2)-m_pSelect.x;
		pMiddle2.y=(pcActPos_Clock2->pCur.y+(pEnd1.y-pcActPos_Clock2->pCur.y)/2)-m_pSelect.y;
		pcActPos_Clock1->SetActPos_Clock_Distance(pcActPos_Clock1->pCur, pMiddle1, pEnd2, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock1->PlayActPos_Clock();
		pcActPos_Clock2->SetActPos_Clock_Distance(pcActPos_Clock2->pCur, pMiddle2, pEnd1, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock2->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_SwapAndAreaToPos(int nArray1, int nArray2, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	POINT pPos;
	int nMin=0;
	int nMax=0;
	POINT pEnd1;
	POINT pEnd2;
	int nTotal=(int)size();
	if(nArray1!=nArray2){
		if(FALSE==SwapActPos_Vector(nArray1, nArray2)) return FALSE;
		CActPos_Clock* pcActPos_Clock1=NULL;
		CActPos_Clock* pcActPos_Clock2=NULL;
		nMin=Min2(nArray1, nArray2);
		nMax=Max2(nArray1, nArray2);
		if(FALSE==GetActPos_Vector(nMin, &pcActPos_Clock1)) return FALSE;
		if(FALSE==GetActPos_Vector(nMax, &pcActPos_Clock2)) return FALSE;
		pEnd1=pcActPos_Clock1->pEnd;
		pEnd2=pcActPos_Clock2->pEnd;
		pPos=GetActPos_Pos_Front(nMin, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock1->SetActPos_Clock(pcActPos_Clock1->pCur, pEnd2, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock1->PlayActPos_Clock();
		pPos=GetActPos_Pos_Front(nMax, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock2->SetActPos_Clock(pcActPos_Clock2->pCur, pEnd1, pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock2->PlayActPos_Clock();
		CActPos_Clock* pcActPos_Clock=NULL;
		for(int i=0; i<nTotal; i++){
			if(i==nArray1) continue;
			if(i==nArray2) continue;
			if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
			pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
			pcActPos_Clock->SetActPos_Clock(pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
			pcActPos_Clock->PlayActPos_Clock();
		}
	}
	else{
		CActPos_Clock* pcActPos_Clock=NULL;
		for(int i=0; i<nTotal; i++){
			if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
			pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
			pcActPos_Clock->SetActPos_Clock(pPos, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
			pcActPos_Clock->PlayActPos_Clock();
		}
	}	
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_SwapDistanceAndAreaToPos(int nArray1, int nArray2, POINT pBase, int nWidth, int nHeight, int nPosTotal, int nDistance, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	POINT pPos;
	int nMin=0;
	int nMax=0;
	POINT pEnd1;
	POINT pEnd2;
	int nTotal=(int)size();
	if(nArray1!=nArray2){
		if(FALSE==SwapActPos_Vector(nArray1, nArray2)) return FALSE;
		CActPos_Clock* pcActPos_Clock1=NULL;
		CActPos_Clock* pcActPos_Clock2=NULL;
		nMin=Min2(nArray1, nArray2);
		nMax=Max2(nArray1, nArray2);
		if(FALSE==GetActPos_Vector(nMin, &pcActPos_Clock1)) return FALSE;
		if(FALSE==GetActPos_Vector(nMax, &pcActPos_Clock2)) return FALSE;
		pEnd1=pcActPos_Clock1->pEnd;
		pEnd2=pcActPos_Clock2->pEnd;
		pPos=GetActPos_Pos_Front(nMin, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock1->SetActPos_Clock_Distance(pcActPos_Clock1->pCur, pEnd2, pPos, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock1->PlayActPos_Clock();
		pPos=GetActPos_Pos_Front(nMax, pBase, nWidth, nHeight, nPosTotal);
		pcActPos_Clock2->SetActPos_Clock_Distance(pcActPos_Clock2->pCur, pEnd1, pPos, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock2->PlayActPos_Clock();
		CActPos_Clock* pcActPos_Clock=NULL;
		for(int i=0; i<nTotal; i++){
			if(i==nArray1) continue;
			if(i==nArray2) continue;
			if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
			pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
			pcActPos_Clock->SetActPos_Clock_Distance(pPos, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
			pcActPos_Clock->PlayActPos_Clock();
		}
	}
	else{
		CActPos_Clock* pcActPos_Clock=NULL;
		for(int i=0; i<nTotal; i++){
			if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
			pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
			pcActPos_Clock->SetActPos_Clock_Distance(pPos, nDistance, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
			pcActPos_Clock->PlayActPos_Clock();
		}
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_Del(int nArray, int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock)
{
	int nTotal=(int)size();
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	POINT pPrevPos=pcActPos_Clock->pEnd;
	POINT pEnd=pcActPos_Clock->pEnd;
	for(int i=nArray+1; i<nTotal; i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pPrevPos=pcActPos_Clock->pEnd;
		pcActPos_Clock->SetActPos_Clock(pcActPos_Clock->pCur, pEnd, nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
		pEnd=pPrevPos;
	}
	return DelActPos_Vector(nArray);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::ActPos_Vector_Select(int nArray, bool bOnly)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(TRUE==bOnly){
		ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
			if(TRUE==Start->IsActAndType(tAct::ACT_SELECT)){
				Start->RemoveActType(tAct::ACT_SELECT);
			}
		}
	}
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	pcActPos_Clock->InsertActType(tAct::ACT_SELECT);
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_Pos(POINT pBase, int nWidth, int nHeight, int nPosTotal)
{
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	int nTotal=(int)size();
	POINT pPos;
	CActPos_Clock* pcActPos_Clock=NULL;
	for(int i=0; i<nTotal; i++){
		pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->ChangeActPos_Clock_EndPos(pPos);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::IsAllActPos_Move(void)
{
	if(TRUE==(bool)empty()) return FALSE;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(FALSE==Start->IsClock()){
			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_Identy(vector<long> vtIdenty, int nType, int nMessage)
{
	int nTotal=min((int)size(), (int)vtIdenty.size());
	CActPos_Clock* pcActPos_Clock=NULL;
	int nIdenty=0;
	for(int i=0; i<nTotal; i++){
		nIdenty=vtIdenty[i];
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActIdenty(nIdenty);
		pcActPos_Clock->SetActType(nType);
		pcActPos_Clock->SetActMessage(nMessage);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_Identy(vector<long> vtIdenty, int nType, int nMessage, POINT pBase, int nWidth, int nHeight, int nPosTotal)
{
	if(0==nPosTotal){ nPosTotal=(int)size(); }
	int nIdentyTotal=(int)vtIdenty.size();
	POINT pPos;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nIdenty=0;
	for(int i=0; i<nIdentyTotal; i++){
		nIdenty=vtIdenty[i];
		pPos=GetActPos_Pos_Front(i, pBase, nWidth, nHeight, nPosTotal);
		if(TRUE==GetActPos_Vector(i, &pcActPos_Clock)){
			pcActPos_Clock->SetActPos_Clock(nIdenty, nType, nMessage, pPos);
		}
		else{
			AddActPos_Vector(nIdenty, nType, nMessage, pPos);
		}
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::IsAllActPos_Type(int nType)
{
	if(TRUE==(bool)empty()) return tClock::CLOCKTYPE_NONE;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(FALSE==Start->IsActType(nType)){
			return FALSE;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::IsAllActPos_AndType(int nType)
{
	if(TRUE==(bool)empty()) return tClock::CLOCKTYPE_NONE;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(FALSE==Start->IsActAndType(nType)){
			return FALSE;
		}
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::IsActPos_Type(int nArray, int nType)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	return pcActPos_Clock->IsActType(nType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::IsActPos_AndType(int nArray, int nType)
{
	CActPos_Clock* pcActPos_Clock=NULL;
	if(FALSE==GetActPos_Vector(nArray, &pcActPos_Clock)) return FALSE;
	return pcActPos_Clock->IsActAndType(nType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_Clock(int nTotalClock, int nBaseClock, int nWaitClock, int nDelayClock, int nHalfClock, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActPos_Clock(nTotalClock, nBaseClock, nWaitClock, nDelayClock, nHalfClock);
		pcActPos_Clock->PlayActPos_Clock();
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_Identy(int nIdenty, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActIdenty(nIdenty);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_Type(int nType, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActType(nType);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_InsertType(int nType, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->InsertActType(nType);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_RemoveType(int nType, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->RemoveActType(nType);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_ChangeType(int nType, int nChangeType, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(nType)){
			pcActPos_Clock->RemoveActType(nType);
			pcActPos_Clock->InsertActType(nChangeType);
		}
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_Message(int nMessage, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->SetActMessage(nMessage);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_InsertMessage(int nMessage, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->InsertActMessage(nMessage);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_RemoveMessage(int nMessage, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->RemoveActMessage(nMessage);
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
bool CActPos_Vector::SetAllActPos_ChangeMessage(int nMessage, int nChangeMessage, int nArray1, int nArray2)
{
	if(TRUE==(bool)empty()) return TRUE;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	if(-1==nArray1){ nArray1=0; }
	if(-1==nArray2){ nArray2=nTotal-1; }
	for(int i=nArray1; i<=min(nArray2, nTotal-1); i++){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		if(TRUE==pcActPos_Clock->IsActAndMessage(nMessage)){
			pcActPos_Clock->RemoveActMessage(nMessage);
			pcActPos_Clock->InsertActMessage(nChangeMessage);
		}
	}
	return TRUE;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::FindActPos_Vector_FromIdenty(int nIdenty)
{
	if(TRUE==(bool)empty()) return -1;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(TRUE==Start->IsActIdenty(nIdenty)){
			return Start-begin();
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::FindActPos_Array_FromAndType(int nType, vector<int>* pvArray, vector<int>* pvNonArray)
{
	if(NULL!=pvArray) pvArray->clear();
	if(NULL!=pvNonArray) pvNonArray->clear();
	if(TRUE==(bool)empty()) return 0;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(TRUE==Start->IsActAndType(nType)){
			if(NULL!=pvArray){
				pvArray->push_back(Start-begin());
			}
		}
		else{
			if(NULL!=pvNonArray){
				pvNonArray->push_back(Start-begin());
			}
		}
	}
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::FindActPos_Identy_FromAndType(int nType, vector<long>* pvIdenty, vector<long>* pvNonIdenty)
{
	if(NULL!=pvIdenty) pvIdenty->clear();
	if(NULL!=pvNonIdenty) pvNonIdenty->clear();
	if(TRUE==(bool)empty()) return 0;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(TRUE==Start->IsActAndType(nType)){
			if(NULL!=pvIdenty){
				pvIdenty->push_back(Start->nIdenty);
			}
		}
		else{
			if(NULL!=pvNonIdenty){
				pvNonIdenty->push_back(Start->nIdenty);
			}
		}
	}
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::FindActPos_FromAndType(int nType, vector<int>* pctvIA, vector<int>* pctvNonIA)
{
	if(NULL!=pctvIA) pctvIA->clear();
	if(NULL!=pctvNonIA) pctvNonIA->clear();
	if(TRUE==(bool)empty()) return 0;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(TRUE==Start->IsActAndType(nType)){
			if(NULL!=pctvIA){
				pctvIA->push_back(SHORT_INT(Start-begin(), Start->nIdenty));
			}
		}
		else{
			if(NULL!=pctvNonIA){
				pctvNonIA->push_back(SHORT_INT(Start-begin(), Start->nIdenty));
			}
		}
	}
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::FindActPos_FromAndType(int nType, vector<long>* pvIdenty, vector<long>* pvNonIdenty, vector<int>* pvArray, vector<int>* pvNonArray)
{
	if(NULL!=pvArray) pvArray->clear();
	if(NULL!=pvNonArray) pvNonArray->clear();
	if(NULL!=pvIdenty) pvIdenty->clear();
	if(NULL!=pvNonIdenty) pvNonIdenty->clear();
	if(TRUE==(bool)empty()) return 0;
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		if(TRUE==Start->IsActAndType(nType)){
			if(NULL!=pvIdenty){
				pvIdenty->push_back(Start->nIdenty);
			}
			if(NULL!=pvArray){
				pvArray->push_back(Start-begin());
			}
		}
		else{
			if(NULL!=pvNonIdenty){
				pvNonIdenty->push_back(Start->nIdenty);
			}
			if(NULL!=pvNonArray){
				pvNonArray->push_back(Start-begin());
			}
		}
	}
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::PtInPosDown(POINT pPos, int nWidth, int nHeight, bool bClick, bool bSwitch)
{
	if(TRUE==m_bMove) return -1;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	int nArray=-1;
	for(int i=nTotal-1; i>=0; i--){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOVE)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOUSENONE)) continue;
		if((TRUE==pcActPos_Clock->PtInPos(pPos, nWidth, nHeight))&&(-1==nArray)){
			if(TRUE==bClick){
				if(TRUE==bSwitch){
					if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_CLICK)){
						pcActPos_Clock->RemoveActType(tAct::ACT_CLICK);
					}
					else{
						pcActPos_Clock->InsertActType(tAct::ACT_CLICK);
					}
				}
				else{
					pcActPos_Clock->InsertActType(tAct::ACT_CLICK);
				}
			}
			nArray=i;
		}
		else{
			if(TRUE==bClick){
				pcActPos_Clock->RemoveActType(tAct::ACT_CLICK);
			}
		}
	}
	return nArray;	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::PtInPosUp(POINT pPos, int nWidth, int nHeight, int nSelect, bool bSwitch, bool bAllSwitch)
{
	if(TRUE==m_bMove) return -1;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	int nArray=-1;
	int nSelectType=((1==nSelect)?(tAct::ACT_ONLY):(tAct::ACT_MULTY));
	if(0==nSelect){
		SetAllActPos_RemoveType(nSelectType|tAct::ACT_CLICK);
		return -1;
	}
	if(tAct::ACT_MULTY==nSelectType){
		for(int i=nTotal-1; i>=0; i--){
			if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
			if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOUSENONE)){
				if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
					nSelect++;
				}
				pcActPos_Clock->RemoveActType(nSelectType);
			}
			if(0>nSelect){
				if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
					nSelect++;
				}
				pcActPos_Clock->RemoveActType(nSelectType);
			}
			//if(0>=nSelect){
			//	pcActPos_Clock->RemoveActType(nSelectType);
			//}
			if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
				nSelect--;
			}
		}
	}
	for(int i=nTotal-1; i>=0; i--){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->RemoveActType(tAct::ACT_CLICK);
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOVE)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOUSENONE)) continue;
		if((TRUE==pcActPos_Clock->PtInPos(pPos, nWidth, nHeight))&&(-1==nArray)){
			if(TRUE==bSwitch){
				if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
					pcActPos_Clock->RemoveActType(nSelectType);
				}
				else{
					if(0<nSelect){
						pcActPos_Clock->InsertActType(nSelectType);
					}
					else if(TRUE==bAllSwitch){
						SetAllActPos_RemoveType(nSelectType);
						pcActPos_Clock->InsertActType(nSelectType);
					}
				}
			}
			else{
				if(0<nSelect){
					pcActPos_Clock->InsertActType(nSelectType);
				}
				else if(TRUE==bAllSwitch){
					SetAllActPos_RemoveType(nSelectType);
					pcActPos_Clock->InsertActType(nSelectType);
				}
			}
			nArray=i;
		}
		else if(tAct::ACT_ONLY==nSelectType){
			pcActPos_Clock->RemoveActType(nSelectType);
		}
	}
	return nArray;	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::PtInPosUp_Type(POINT pPos, int nWidth, int nHeight, int nType, int nSelect, bool bSwitch, bool bAllSwitch)
{
	if(TRUE==m_bMove) return -1;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	int nArray=-1;
	int nSelectType=nType;
	if(0==nSelect){
		SetAllActPos_RemoveType(nSelectType|tAct::ACT_CLICK);
		return -1;
	}
	for(int i=nTotal-1; i>=0; i--){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOUSENONE)){
			if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
				pcActPos_Clock->RemoveActType(nSelectType);
				nSelect++;
			}
		}
		if(0>nSelect){
			if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
				pcActPos_Clock->RemoveActType(nSelectType);
				nSelect++;
			}
		}
		//if(0>=nSelect){
		//	pcActPos_Clock->RemoveActType(nSelectType);
		//}
		if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
			nSelect--;
		}
	}
	for(int i=nTotal-1; i>=0; i--){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		pcActPos_Clock->RemoveActType(tAct::ACT_CLICK);
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOVE)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOUSENONE)) continue;
		if((TRUE==pcActPos_Clock->PtInPos(pPos, nWidth, nHeight))&&(-1==nArray)){
			if(TRUE==bSwitch){
				if(TRUE==pcActPos_Clock->IsActAndType(nSelectType)){
					pcActPos_Clock->RemoveActType(nSelectType);
				}
				else{
					if(0<nSelect){
						pcActPos_Clock->InsertActType(nSelectType);
					}
					else if(TRUE==bAllSwitch){
						SetAllActPos_RemoveType(nSelectType);
						pcActPos_Clock->InsertActType(nSelectType);
					}
				}
			}
			else{
				if(0<nSelect){
					pcActPos_Clock->InsertActType(nSelectType);
				}
				else if(TRUE==bAllSwitch){
					SetAllActPos_RemoveType(nSelectType);
					pcActPos_Clock->InsertActType(nSelectType);
				}
			}
			nArray=i;
		}
	}
	return nArray;	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::PtInPosMove(POINT pPos, int nWidth, int nHeight)
{
	if(TRUE==m_bMove) return -1;
	CActPos_Clock* pcActPos_Clock=NULL;
	int nTotal=(int)size();
	int nArray=-1;
	for(int i=nTotal-1; i>=0; i--){
		if(FALSE==GetActPos_Vector(i, &pcActPos_Clock)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOVE)) continue;
		if(TRUE==pcActPos_Clock->IsActAndType(tAct::ACT_MOUSENONE)) continue;
		if((TRUE==pcActPos_Clock->PtInPos(pPos, nWidth, nHeight))&&(-1==nArray)){
			pcActPos_Clock->InsertActType(tAct::ACT_OVER);
			nArray=i;
		}
		else{
			pcActPos_Clock->RemoveActType(tAct::ACT_OVER);
		}
	}
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CActPos_Vector::UpdateActPos_Vector(int nClock, float fPow, bool bLoop)
{
	if(TRUE==(bool)empty()) return tClock::CLOCKTYPE_NONE;
	int nResult=tClock::CLOCKTYPE_NONE;
	m_bMove=FALSE;
	m_vtEndMessage.clear();
	m_vtReturnMessage.clear();
	ForEachElmt(vector<CActPos_Clock>, *(static_cast<vector<CActPos_Clock>*>(this)), Start, End){
		int nReturn=Start->UpdatePosFromTime(nClock, fPow, bLoop);
		if(tClock::CLOCKTYPE_NONE!=nReturn){
			if(TRUE==Start->IsEnd(nReturn)){
				if(TRUE==Start->IsDelay(nReturn)){
					nResult=tClock::CLOCKTYPE_MOVING;
				}
				else{
					if(tAct::ACT_NONE!=Start->nMessage){
						m_vtEndMessage.push_back(tStateMessage((int)(Start-begin()), Start->GetMessageClear()));
					}
					if(tClock::CLOCKTYPE_NONE==nResult){
						nResult=tClock::CLOCKTYPE_MOVEEND;
					}
				}
			}
			else if(TRUE==Start->IsWait(nReturn)){
				if((tClock::CLOCKTYPE_NONE==nResult)||(tClock::CLOCKTYPE_MOVEEND==nResult)){
					nResult=tClock::CLOCKTYPE_WAIT;
				}
			}
			else{
				nResult=tClock::CLOCKTYPE_MOVING;
			}
			m_bMove=TRUE;
		}
		else{
			if(tAct::ACT_NONE!=Start->nMessage){
				m_vtEndMessage.push_back(tStateMessage((int)(Start-begin()), Start->GetMessageClear()));
			}
		}
		m_vtReturnMessage.push_back(tStateMessage((int)(Start-begin()), nReturn));
	}
	if((tClock::CLOCKTYPE_MOVEEND==nResult)||(tClock::CLOCKTYPE_NONE==nResult)){
		if(TRUE==IsClock()){
			if(FALSE==IsUpdateToEnd(nClock)){
				nResult=nResult|tClock::CLOCKTYPE_DELAY;
			}
			else{
				ClearClock();
				nResult=tClock::CLOCKTYPE_MOVEEND;
			}
		}
	}
	if(tClock::CLOCKTYPE_NONE==nResult){
		m_cUpdate.FindDelVector((unsigned int)(DWORD_PTR)(this));
	}
	else{
		m_cUpdate.FindAddVector((unsigned int)(DWORD_PTR)(this), nResult);
	}
	return nResult;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
char CResultFactor::GetOrder(int nMadeType, vector<long> vtCard, int nFindOrder)
{
	if(2<=vtCard.size()){
		return GetOrder(nMadeType, vtCard[0], vtCard[1], nFindOrder);
	}
	else if(1==vtCard.size()){
		return (char)(RESULT_ZERO+(vtCard[0])%10);
	}
	return RESULT_NONE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
char CResultFactor::GetAnother(int nMadeType, vector<long> vtCard, int nFindOrder)
{
	if(2<=vtCard.size()){
		return GetAnother(nMadeType, vtCard[0], vtCard[1], nFindOrder);
	}
	return RESULT_NOJJOK;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsFindOrder(int nMadeType, vector<long> vtCard, int nFindOrder)
{
	if(2<=vtCard.size()){
		return ((char)RESULT_FIND==GetAnother(nMadeType, vtCard[0], vtCard[1], nFindOrder));
	}
	return FALSE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::GetMade(vector<long> vtCard)
{
	if(3<=vtCard.size()){
		return GetMade(vtCard[0], vtCard[1], vtCard[2]);
	}
	return MADE_NONE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::GetMadeArray(vector<long> vtCard)
{
	if(3<=vtCard.size()){
		return GetMadeArray(vtCard[0], vtCard[1], vtCard[2]);
	}
	return MADENUM_NONE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsMade(vector<long> vtCard)
{
	if(3<=vtCard.size()){
		return (0==((vtCard[0]+1+vtCard[1]+1+vtCard[2]+1)%10));
	}
	return FALSE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
char CResultFactor::GetOrder(int nMadeType, int nCard1, int nCard2, int nFindOrder)
{
	if((0>nCard1)||(0>nCard2)) return (char)RESULT_NONE;
	int nMinCard1=Min2(nCard1, nCard2)+1;
	int nMaxCard2=Max2(nCard1, nCard2)+1;
	int nTempCard1=Min2(((nCard1+1)%10), ((nCard2+1)%10));
	int nTempCard2=Max2(((nCard1+1)%10), ((nCard2+1)%10));
	char cAndOrder=0;
	if(MADETYPE_NONE==nMadeType){
		if((3==nMinCard1)&&(8==nMaxCard2)) return (char)(RESULT_38DDANG);
		if((1==nMinCard1)&&(8==nMaxCard2)) return (char)(RESULT_18DDANG);
		if((1==nMinCard1)&&(3==nMaxCard2)) return (char)(RESULT_13DDANG);
		if(nTempCard1==nTempCard2) return (((char)(RESULT_1DDANG+((0==nTempCard2)?(10):(nTempCard2))-1)));
		if((1==nTempCard1)&&(2==nTempCard2)) return (char)(RESULT_ONE_TWO);
		if((1==nTempCard1)&&(4==nTempCard2)) return (char)(RESULT_ONE_FOUR);
		if((1==nTempCard1)&&(9==nTempCard2)) return (char)(RESULT_ONE_NINE);
		if((0==nTempCard1)&&(1==nTempCard2)) return (char)(RESULT_TEN_ONE);
		if((0==nTempCard1)&&(4==nTempCard2)) return (char)(RESULT_TEN_FOUR);
		if((4==nTempCard1)&&(6==nTempCard2)) return (char)(RESULT_FOUR_SIX);
	}
	if(MADETYPE_MADE==nMadeType){
		if(RESULT_NONE!=nFindOrder){
			if((char)nFindOrder==GetOrder(nMadeType, nCard1, nCard2, RESULT_NONE)){
				cAndOrder=(char)RESULT_FIND;
			}
		}
		if(nTempCard1==nTempCard2){
			return (char)(cAndOrder|((char)(RESULT_1DDANG+((0==nTempCard2)?(10):(nTempCard2))-1)));
		}
	}
	return (char)(cAndOrder|((char)(RESULT_ZERO+((nTempCard1)+(nTempCard2))%10)));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
char CResultFactor::GetAnother(int nMadeType, int nCard1, int nCard2, int nFindOrder)
{
	if((0>nCard1)||(0>nCard2)) return (char)RESULT_NONE;
	int nMinCard1=Min2(nCard1, nCard2)+1;
	int nMaxCard2=Max2(nCard1, nCard2)+1;
	int nTempCard1=Min2(((nCard1+1)%10), ((nCard2+1)%10));
	int nTempCard2=Max2(((nCard1+1)%10), ((nCard2+1)%10));
	if(MADETYPE_NONE==nMadeType){
		if((3==nMinCard1)&&(8==nMaxCard2)) return (char)RESULT_GHANGDDANG38;
		if((1==nMinCard1)&&(8==nMaxCard2)) return (char)RESULT_GHANGDDANG138;
		if((1==nMinCard1)&&(3==nMaxCard2)) return (char)RESULT_GHANGDDANG138;
		if(nTempCard1==nTempCard2){
			if(0==nTempCard2) return (char)RESULT_DDAND10;
			return (char)RESULT_DDAND19;
		}
		if((1==nTempCard1)&&(2==nTempCard2)) return (char)RESULT_JJOK;
		if((1==nTempCard1)&&(4==nTempCard2)) return (char)RESULT_JJOK;
		if((1==nTempCard1)&&(9==nTempCard2)) return (char)RESULT_JJOK;
		if((0==nTempCard1)&&(1==nTempCard2)) return (char)RESULT_JJOK;
		if((0==nTempCard1)&&(4==nTempCard2)) return (char)RESULT_JJOK;
		if((4==nTempCard1)&&(6==nTempCard2)) return (char)RESULT_JJOK;
		//if((3==nTempCard1)&&(7==nTempCard2))
		if((3==nMinCard1)&&(7==nMaxCard2)) return (char)RESULT_THREE_SEVEN;
		//if((4==nTempCard1)&&(7==nTempCard2))
		if((4==nMinCard1)&&(7==nMaxCard2)) return (char)RESULT_FOUR_SEVEN;
		if((4==nMinCard1)&&(9==nMaxCard2)) return (char)RESULT_FOOL_NINE_FOUR;
		if((4==nTempCard1)&&(9==nTempCard2)) return (char)RESULT_NINE_FOUR;
	}
	if(MADETYPE_MADE==nMadeType){
		if(RESULT_NONE!=nFindOrder){
			if((char)nFindOrder==GetOrder(nMadeType, nCard1, nCard2, RESULT_NONE)) return (char)RESULT_FIND;
		}
		if(nTempCard1==nTempCard2){
			if(0==nTempCard2) return (char)RESULT_DDAND10;
			return (char)RESULT_DDAND19;
		}
		//if((4==nMinCard1)&&(9==nMaxCard2))
		//	return RESULT_FOOL_NINE_FOUR;
		//if((4==nTempCard1)&&(9==nTempCard2))
		//	return RESULT_NINE_FOUR;
	}
	return (char)RESULT_NOJJOK;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsFindOrder(int nMadeType, int nCard1, int nCard2, int nFindOrder)
{
	return ((char)RESULT_FIND==GetAnother(nMadeType, nCard1, nCard2, nFindOrder));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::GetMade(int nCard1, int nCard2, int nCard3)
{
	if((0>nCard1)||(0>nCard2)||(0>nCard3)) return MADE_NONE;
	int nTempCard1=Min3(((nCard1+1)%10), ((nCard2+1)%10), ((nCard3+1)%10));
	int nTempCard2=Middle3(((nCard1+1)%10), ((nCard2+1)%10), ((nCard3+1)%10));
	int nTempCard3=Max3(((nCard1+1)%10), ((nCard2+1)%10), ((nCard3+1)%10));
	if(0==((nTempCard1+nTempCard2+nTempCard3)%10)){
		if((1==nTempCard1)&&(1==nTempCard2)&&(8==nTempCard3)) return MADE_118;
		if((1==nTempCard1)&&(2==nTempCard2)&&(7==nTempCard3)) return MADE_127;
		if((1==nTempCard1)&&(3==nTempCard2)&&(6==nTempCard3)) return MADE_136;
		if((1==nTempCard1)&&(4==nTempCard2)&&(5==nTempCard3)) return MADE_145;
		if((0==nTempCard1)&&(1==nTempCard2)&&(9==nTempCard3)) return MADE_190;
		if((2==nTempCard1)&&(2==nTempCard2)&&(6==nTempCard3)) return MADE_226;
		if((2==nTempCard1)&&(3==nTempCard2)&&(5==nTempCard3)) return MADE_235;
		if((0==nTempCard1)&&(2==nTempCard2)&&(8==nTempCard3)) return MADE_280;
		if((3==nTempCard1)&&(3==nTempCard2)&&(4==nTempCard3)) return MADE_334;
		if((0==nTempCard1)&&(3==nTempCard2)&&(7==nTempCard3)) return MADE_370;
		if((3==nTempCard1)&&(8==nTempCard2)&&(9==nTempCard3)) return MADE_389;
		if((2==nTempCard1)&&(4==nTempCard2)&&(4==nTempCard3)) return MADE_442;
		if((0==nTempCard1)&&(4==nTempCard2)&&(6==nTempCard3)) return MADE_460;
		if((4==nTempCard1)&&(7==nTempCard2)&&(9==nTempCard3)) return MADE_479;
		if((0==nTempCard1)&&(5==nTempCard2)&&(5==nTempCard3)) return MADE_550;
		if((5==nTempCard1)&&(6==nTempCard2)&&(9==nTempCard3)) return MADE_569;
		if((5==nTempCard1)&&(7==nTempCard2)&&(8==nTempCard3)) return MADE_578;
		if((6==nTempCard1)&&(6==nTempCard2)&&(8==nTempCard3)) return MADE_668;
		if((6==nTempCard1)&&(7==nTempCard2)&&(7==nTempCard3)) return MADE_776;
		if((4==nTempCard1)&&(8==nTempCard2)&&(8==nTempCard3)) return MADE_884;
		if((2==nTempCard1)&&(9==nTempCard2)&&(9==nTempCard3)) return MADE_992;
		if((0==nTempCard1)&&(0==nTempCard2)&&(0==nTempCard3)) return MADE_000;
	}
	return MADE_NONE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::GetMadeArray(int nCard1, int nCard2, int nCard3)
{
	int nMade=GetMade(nCard1, nCard2, nCard3);
	return MadeToArray(nMade);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::IsAnother(char cAnother)
{
	if(RESULT_FIND==cAnother){
		return RESULT_FIND;
	}
	if((RESULT_NINE_FOUR==cAnother)||(RESULT_NINE_FOUR_JJOK==cAnother)){
		return RESULT_NINE_FOUR;
	}
	if((RESULT_FOOL_NINE_FOUR==cAnother)||(RESULT_FOOL_NINE_FOUR_DDANG==cAnother)){
		return RESULT_FOOL_NINE_FOUR;
	}
	return RESULT_NONE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::IsAnother(int nMadeType, char cMade, char cAnother)
{
	if(MADETYPE_MADE==nMadeType){
		if(RESULT_NOMADE==cMade) return RESULT_NOMADE;
	}
	if(RESULT_FIND==cAnother){
		return RESULT_FIND;
	}
	if((RESULT_NINE_FOUR==cAnother)||(RESULT_NINE_FOUR_JJOK==cAnother)){
		return RESULT_NINE_FOUR;
	}
	if((RESULT_FOOL_NINE_FOUR==cAnother)||(RESULT_FOOL_NINE_FOUR_DDANG==cAnother)){
		return RESULT_FOOL_NINE_FOUR;
	}
	return RESULT_NONE;
}
//--------------------------------------------------------------//
//
//--------------------------------------------------------------//
int CResultFactor::MadeToArray(int nMade)
{
	switch(nMade){
	case MADE_118: return MADENUM_118;
	case MADE_127: return MADENUM_127;
	case MADE_136: return MADENUM_136;
	case MADE_145: return MADENUM_145;
	case MADE_190: return MADENUM_190;
	case MADE_226: return MADENUM_226;
	case MADE_235: return MADENUM_235;
	case MADE_280: return MADENUM_280;
	case MADE_334: return MADENUM_334;
	case MADE_370: return MADENUM_370;
	case MADE_389: return MADENUM_389;
	case MADE_442: return MADENUM_442;
	case MADE_460: return MADENUM_460;
	case MADE_479: return MADENUM_479;
	case MADE_550: return MADENUM_550;
	case MADE_569: return MADENUM_569;
	case MADE_578: return MADENUM_578;
	case MADE_668: return MADENUM_668;
	case MADE_776: return MADENUM_776;
	case MADE_884: return MADENUM_884;
	case MADE_992: return MADENUM_992;
	case MADE_000: return MADENUM_000;
	}
	return MADENUM_NONE;
}
//--------------------------------------------------------------//
//
//--------------------------------------------------------------//
int CResultFactor::MadeFromArray(int nMadeArray)
{
	switch(nMadeArray){
	case MADENUM_118: return MADE_118;
	case MADENUM_127: return MADE_127;
	case MADENUM_136: return MADE_136;
	case MADENUM_145: return MADE_145;
	case MADENUM_190: return MADE_190;
	case MADENUM_226: return MADE_226;
	case MADENUM_235: return MADE_235;
	case MADENUM_280: return MADE_280;
	case MADENUM_334: return MADE_334;
	case MADENUM_370: return MADE_370;
	case MADENUM_389: return MADE_389;
	case MADENUM_442: return MADE_442;
	case MADENUM_460: return MADE_460;
	case MADENUM_479: return MADE_479;
	case MADENUM_550: return MADE_550;
	case MADENUM_569: return MADE_569;
	case MADENUM_578: return MADE_578;
	case MADENUM_668: return MADE_668;
	case MADENUM_776: return MADE_776;
	case MADENUM_884: return MADE_884;
	case MADENUM_992: return MADE_992;
	case MADENUM_000: return MADE_000;
	}
	return MADE_NONE;
}
//--------------------------------------------------------------//
//
//--------------------------------------------------------------//
void CResultFactor::MadeLineCol(int nMade, vector<long> vtCard, vector<int>* pvtMadePos)
{
	if(NULL==pvtMadePos) return;
	pvtMadePos->clear();
	int nTempCard=0;
	int n1=(nMade/100)%10;
	int n2=(nMade/10)%10;
	int n3=(nMade/1)%10;
	//int nM1=Min3(n1, n2, n3);
	//int nM2=Middle3(n1, n2, n3);
	//int nM3=Max3(n1, n2, n3);
	int nTotal=(int)vtCard.size();
	for(int i=0; i<nTotal; i++){
		nTempCard=(vtCard[i]+1)%10;
		if(n1==nTempCard){
			n1=-1;
			//if((0==nTempCard)&&(MADE_000!=nMade)){
			//	pvtMadePos->push_back(2);
			//}
			//else{
			pvtMadePos->push_back(0);
			//}
		}
		else if(n2==nTempCard){
			n2=-1;
			pvtMadePos->push_back(1);
		}
		else if(n3==nTempCard){
			n3=-1;
			pvtMadePos->push_back(2);
		}
		else{
			pvtMadePos->push_back(-1);
		}
	}
}
//--------------------------------------------------------------//
//
//--------------------------------------------------------------//
void CResultFactor::MadeLineCol(vector<long> vtCard, vector<int> vtMadePos[MADE_TOTAL])
{
	if(NULL==vtMadePos) return;
	for(int i=0; i<MADE_TOTAL; i++){
		MadeLineCol(MadeFromArray(i+1), vtCard, &vtMadePos[i]);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::MadeList(vector<int> vtCard, vector<tInt3>* pvtMade, vector<int>* pvMade, int nSortType)
{
	if(NULL==pvtMade) return;
	vector<int> vtTempCard;
	int nSize=(int)vtCard.size();
	int nValue=0;
	for(int i=0; i<nSize; i++){
		nValue=((vtCard[i]+1)%10);
		if(0==nValue){
			vtTempCard.push_back(10);
		}
		else{
			vtTempCard.push_back(nValue);
		}
	}
	Sort_Descend(&vtTempCard);
	nSize=(int)vtTempCard.size();
	int nTotal=0;
	bool bSame=FALSE;
	for(int i=0; i<nSize-1; i++){
		if(-1==vtTempCard[i]) continue;
		for(int j=i+1; j<nSize; j++){
			if(-1==vtTempCard[j]) continue;
			bSame=FALSE;
			nTotal=(int)pvtMade->size();
			for(int m=0; m<nTotal; m++){
				if(TRUE==(*pvtMade)[m].IsSame12(vtTempCard[i], vtTempCard[j])){
					bSame=TRUE;
					break;
				}
			}
			if(FALSE==bSame){
				nValue=10-(vtTempCard[i]+vtTempCard[j])%10;
				if(0==nValue){
					pvtMade->push_back(tInt3(vtTempCard[i], vtTempCard[j], 10));
				}
				else{
					pvtMade->push_back(tInt3(vtTempCard[i], vtTempCard[j], nValue));
				}
			}
			bSame=FALSE;
			if(NULL!=pvMade){
				nValue=10-(vtTempCard[i]+vtTempCard[j])%10;
				if(0==nValue){
					nValue=10;
				}
				nTotal=(int)pvMade->size();
				for(int n=0; n<nTotal; n++){
					if(nValue==(*pvMade)[n]){
						bSame=TRUE;
						break;
					}
				}	
				if(FALSE==bSame){
					pvMade->push_back(nValue);
				}			
			}
		}
	}
	Sort_Descend3(pvtMade, nSortType);
	Sort_Descend(pvMade);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::MadeList(vector<long> vtCard, vector<tInt3>* pvtMade, vector<int>* pvMade, int nSortType)
{
	if(NULL==pvtMade) return;
	vector<int> vtTempCard;
	int nSize=(int)vtCard.size();
	int nValue=0;
	for(int i=0; i<nSize; i++){
		nValue=((vtCard[i]+1)%10);
		if(0==nValue){
			vtTempCard.push_back(10);
		}
		else{
			vtTempCard.push_back(nValue);
		}
	}
	Sort_Descend(&vtTempCard);
	nSize=(int)vtTempCard.size();
	int nTotal=0;
	bool bSame=FALSE;
	for(int i=0; i<nSize-1; i++){
		if(-1==vtTempCard[i]) continue;
		for(int j=i+1; j<nSize; j++){
			if(-1==vtTempCard[j]) continue;
			bSame=FALSE;
			nTotal=(int)pvtMade->size();
			for(int m=0; m<nTotal; m++){
				if(TRUE==(*pvtMade)[m].IsSame12(vtTempCard[i], vtTempCard[j])){
					bSame=TRUE;
					break;
				}
			}
			if(FALSE==bSame){
				nValue=10-(vtTempCard[i]+vtTempCard[j])%10;
				if(0==nValue){
					pvtMade->push_back(tInt3(vtTempCard[i], vtTempCard[j], 10));
				}
				else{
					pvtMade->push_back(tInt3(vtTempCard[i], vtTempCard[j], nValue));
				}
			}
			bSame=FALSE;
			if(NULL!=pvMade){
				nValue=10-(vtTempCard[i]+vtTempCard[j])%10;
				if(0==nValue){
					nValue=10;
				}
				nTotal=(int)pvMade->size();
				for(int n=0; n<nTotal; n++){
					if(nValue==(*pvMade)[n]){
						bSame=TRUE;
						break;
					}
				}	
				if(FALSE==bSame){
					pvMade->push_back(nValue);
				}			
			}
		}
	}
	Sort_Descend3(pvtMade, nSortType);
	Sort_Descend(pvMade);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
string CResultFactor::GetString(int nMadeType, char cAnother, char cOrder)
{
	string str;
	cOrder=(char)RemoveBITS(cOrder, (char)RESULT_FIND);
	switch(cOrder){
	case RESULT_ZERO: str="¸ÁÅë"; break;
	case RESULT_ONE: str="1²ý"; break;
	case RESULT_TWO: str="2²ý"; break;
	case RESULT_THREE: str="3²ý"; break;
	case RESULT_FOUR: str="4²ý"; break;
	case RESULT_FIVE: str="5²ý"; break;
	case RESULT_SIX: str="6²ý"; break;
	case RESULT_SEVEN: str="7²ý"; break;
	case RESULT_EIGHT: str="8²ý"; break;
	case RESULT_NINE: str="°©¿À"; break;
	case RESULT_FOUR_SIX: str="¼¼·ú"; break;
	case RESULT_TEN_FOUR: str="Àå»ç"; break;
	case RESULT_TEN_ONE: str="Àå»æ"; break;
	case RESULT_ONE_NINE: str="±¸»æ"; break;
	case RESULT_ONE_FOUR: str="µ¶»ç"; break;
	case RESULT_ONE_TWO: str="¾Ë¸®"; break;
	case RESULT_1DDANG: str="ÀÏ¶¯"; break;
	case RESULT_2DDANG: str="ÀÌ¶¯"; break;
	case RESULT_3DDANG: str="»ï¶¯"; break;
	case RESULT_4DDANG: str="»ç¶¯"; break;
	case RESULT_5DDANG: str="¿À¶¯"; break;
	case RESULT_6DDANG: str="À°¶¯"; break;
	case RESULT_7DDANG: str="Ä¥¶¯"; break;
	case RESULT_8DDANG: str="ÆÈ¶¯"; break;
	case RESULT_9DDANG: str="±¸¶¯"; break;
	case RESULT_10DDANG: str="Àå¶¯"; break;
	case RESULT_13DDANG: str="13±¤¶¯"; break;
	case RESULT_18DDANG: str="18±¤¶¯"; break;
	case RESULT_38DDANG: str="38±¤¶¯"; break;
	}
	if(MADETYPE_NOANOTHER!=nMadeType){
		switch(cAnother){
		case RESULT_NONE: str=""; break;
		case RESULT_NINE_FOUR:
		case RESULT_NINE_FOUR_JJOK:
			str="[±¸»ç]";
			break;
		case RESULT_FOOL_NINE_FOUR:
		case RESULT_FOOL_NINE_FOUR_DDANG:
			str="[¸Û±¸»ç]";
			break;
		case RESULT_THREE_SEVEN:
		case RESULT_THREE_SEVEN_DDANG:
		case RESULT_THREE_SEVEN_DDANG10:
			str+="[¶¯ÀâÀÌ]";
			break;
		case RESULT_FOUR_SEVEN:
		case RESULT_FOUR_SEVEN_GHANGDDANG138:
			str+="[¾ÏÇà¾î»ç]";
			break;
		case RESULT_JJOK: break;
		case RESULT_DDAND19: break;
		case RESULT_DDAND10: break;
		case RESULT_GHANGDDANG138: break;
		case RESULT_GHANGDDANG38: break;
		case RESULT_FIND: break;
		}
	}
	return str;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
string CResultFactor::GetMadeString(int nMade)
{
	string str;
	switch(nMade){
	case MADE_NONE: str=""; break;
	case MADE_118: str="ÄáÄáÆÈ"; break;
	case MADE_127: str="»ß¸®Ä¥"; break;
	case MADE_136: str="¹°»ïÀ°"; break;
	case MADE_145: str="»ª»õ¿À"; break;
	case MADE_190: str="»æ±¸Àå"; break;
	case MADE_226: str="´Ï´ÏÀ°"; break;
	case MADE_235: str="ÀÌ»ï¿À"; break;
	case MADE_280: str="ÀÌÆÇÀå"; break;
	case MADE_334: str="½É½É»õ"; break;
	case MADE_370: str="»ïÄ¥Àå"; break;
	case MADE_389: str="»ïºý±¸"; break;
	case MADE_442: str="»ì»ìÀÌ"; break;
	case MADE_460: str="»ç·úÀå"; break;
	case MADE_479: str="»çÄ¥±¸"; break;
	case MADE_550: str="²¿²¿Àå"; break;
	case MADE_569: str="¿À·ú±¸"; break;
	case MADE_578: str="¿À¸®¹ß"; break;
	case MADE_668: str="ÂßÂßÆÈ"; break;
	case MADE_776: str="Ã¶Ã¶À°"; break;
	case MADE_884: str="ÆÅÆÅ½Î"; break;
	case MADE_992: str="±¸±¸¸®"; break;
	case MADE_000: str="ÀåÀåÀå"; break;
	}
	return str;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
string CResultFactor::GetMadeString_Num(int nMade)
{
	string str;
	switch(nMade){
	case MADE_NONE: str=""; break;
	case MADE_118: str="1 1 8"; break;
	case MADE_127: str="1 2 7"; break;
	case MADE_136: str="1 3 6"; break;
	case MADE_145: str="1 4 5"; break;
	case MADE_190: str="1 9 10"; break;
	case MADE_226: str="2 2 6"; break;
	case MADE_235: str="2 3 5"; break;
	case MADE_280: str="2 8 10"; break;
	case MADE_334: str="3 3 4"; break;
	case MADE_370: str="3 7 10"; break;
	case MADE_389: str="3 8 9"; break;
	case MADE_442: str="4 4 2"; break;
	case MADE_460: str="4 6 10"; break;
	case MADE_479: str="4 7 9"; break;
	case MADE_550: str="5 5 10"; break;
	case MADE_569: str="5 6 9"; break;
	case MADE_578: str="5 7 8"; break;
	case MADE_668: str="6 6 8"; break;
	case MADE_776: str="7 7 6"; break;
	case MADE_884: str="8 8 4"; break;
	case MADE_992: str="9 9 2"; break;
	case MADE_000: str="10 10 10"; break;
	}
	return str;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
string CResultFactor::GetMadeArrayString(int nMadeArray)
{
	return GetMadeString(MadeFromArray(nMadeArray));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::ArrayToSelect(int nArray1, int nArray2, int nTotal)
{
	if((0>nArray1)||(0>nArray2)) return -1;
	int nCheck1=Min2(nArray1, nArray2);
	int nCheck2=Max2(nArray1, nArray2);
	int nSelect=0; 
	for(int i=0; i<nTotal-1; i++){
		for(int j=i+1; j<nTotal; j++){
			if((nCheck1==i)&&(nCheck2==j)){
				return nSelect;
			}
			nSelect++;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SelectToArray(int nSelect, int nTotal, int &nArray1, int &nArray2)
{
	if(0>nSelect){
		if(2<=nTotal){
			nArray1=0;
			nArray2=1;
		}
		else{
			nArray1=-1;
			nArray2=-1;
		}
		return;
	}
	int nCount=0; 
	for(int i=0; i<nTotal-1; i++){
		for(int j=i+1; j<nTotal; j++){
			if(nSelect==nCount){
				nArray1=i;
				nArray2=j;
				return;
			}
			nCount++;
		}
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::ResultToCard(int nMadeType, char cAnother, char cOrder, int &nCard1, int &nCard2)
{
	int nRandom=IRandom(2);
	if(TRUE==IsAndBITS(cAnother, RESULT_FIND)){
		nCard1=-1; nCard2=-1;
	}
	if(MADETYPE_NONE==nMadeType){
		switch(cAnother){
		case RESULT_NONE: nCard1=nCard2=-1; break;
		case RESULT_NOJJOK: nCard1=nCard2=-1; break;
		case RESULT_NINE_FOUR:
		case RESULT_NINE_FOUR_JJOK:
			{
				nCard1=4+((0==nRandom)?(10):(0))-1;
				nCard2=9+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_FOOL_NINE_FOUR:
		case RESULT_FOOL_NINE_FOUR_DDANG:
			{
				nCard1=4-1; nCard2=9-1; 
			}
			break;
		case RESULT_THREE_SEVEN:
		case RESULT_THREE_SEVEN_DDANG:
		case RESULT_THREE_SEVEN_DDANG10:
			{
				//nCard1=3+((0==IRandom(2))?(10):(0))-1;
				//nCard2=7+((1==IRandom(2))?(10):(0))-1;
				nCard1=3-1; nCard2=7-1; 
			}
			break;
		case RESULT_FOUR_SEVEN:
		case RESULT_FOUR_SEVEN_GHANGDDANG138:
			{
				nCard1=4-1; nCard2=7-1; 
			}
			break;
		case RESULT_JJOK: nCard1=nCard2=-1; break;
		case RESULT_DDAND19: nCard1=nCard2=-1; break;
		case RESULT_DDAND10: nCard1=10-1; nCard2=20-1; break;
		case RESULT_GHANGDDANG138: nCard1=nCard2=-1; break;
		case RESULT_GHANGDDANG38: nCard1=3-1; nCard2=8-1; break;
		case RESULT_FIND: nCard1=-1; nCard2=-1; break;
		}
	}
	if(MADETYPE_MADE==nMadeType){
		switch(cAnother){
		case RESULT_NONE: nCard1=nCard2=-1; break;
		case RESULT_NOJJOK: nCard1=nCard2=-1; break;
		//case RESULT_NINE_FOUR:
		//case RESULT_NINE_FOUR_JJOK:
		//	{
		//		nCard1=4+((0==nRandom)?(10):(0))-1;
		//		nCard2=9+((1==nRandom)?(10):(0))-1;
		//	}
		//	break;
		//case RESULT_FOOL_NINE_FOUR:
		//case RESULT_FOOL_NINE_FOUR_DDANG:
		//	{
		//		nCard1=4-1; nCard2=9-1; 
		//	}
		//	break;
		case RESULT_DDAND19: nCard1=nCard2=-1; break;
		case RESULT_DDAND10: nCard1=10-1; nCard2=20-1; break;
		case RESULT_FIND: nCard1=-1; nCard2=-1; break;
		}
	}
	int nValue=0;
	if((-1==nCard1)&&(-1==nCard2)){
		cOrder=(char)RemoveBITS(cOrder, (char)RESULT_FIND);
		switch(cOrder){
		case RESULT_NONE:
			{
				int nFind = cOrder - 1;
				int nTable[10]={0,};
				int nRandomTable[10]={0,};
				vector<int> nvValue;
				for(int i=0; i<10; i++){
					nvValue.push_back(i);
				}
				int nTotal=0;
				int nArray=0;
				for(int i=1, j=nFind; i<11; i++, j--){
					if(j<=0) j=10;
					nTable[(i%10)]=j;
					nTotal=(int)nvValue.size();
					if(0<nTotal){
						nArray=IRandom(nTotal);
						nRandomTable[i-1]=nvValue[nArray];
						nvValue.erase(nvValue.begin() + nArray);
						//nvValue.erase(&nvValue[nArray]);
					}
				}
				for(int i=0; i<10; i++){
					nCard1=nRandomTable[i]-1;
					nCard2=nTable[nRandomTable[i]]-1;
					if(RESULT_NOJJOK==GetAnother(nMadeType, nCard1, nCard2)){
						break;
					}
				}
				nCard1=nCard1+((0==IRandom(2))?(10):(0));
				nCard2=nCard2+((1==IRandom(2))?(10):(0));
			}
			break;
		case RESULT_ZERO:
			{
				nValue=IRandom(2);
				if(1==nValue){
					nCard1=2+((0==nRandom)?(10):(0))-1;
					nCard2=8+((1==nRandom)?(10):(0))-1;			
				}
				else{
					nCard1=3+((0==nRandom)?(10):(0))-1;
					nCard2=7+((1==nRandom)?(10):(0))-1;
				}
			}
			break;
		case RESULT_ONE:
		case RESULT_TWO:
		case RESULT_THREE:
		case RESULT_FOUR:
		case RESULT_FIVE:
		case RESULT_SIX:
		case RESULT_SEVEN:
		case RESULT_EIGHT:
		case RESULT_NINE:
			{
				int nFind = cOrder - 1;
				int nTable[10]={0,};
				int nRandomTable[10]={0,};
				vector<int> nvValue;
				for(int i=0; i<10; i++){
					nvValue.push_back(i);
				}
				int nTotal=0;
				int nArray=0;
				for(int i=1, j=nFind; i<11; i++, j--){
					if(j<=0) j=10;
					nTable[(i%10)]=j;
					nTotal=(int)nvValue.size();
					if(0<nTotal){
						nArray=IRandom(nTotal);
						nRandomTable[i-1]=nvValue[nArray];
						nvValue.erase(nvValue.begin() + nArray);
						//nvValue.erase(&nvValue[nArray]);
					}
				}
				for(int i=0; i<10; i++){
					nCard1=nRandomTable[i]-1;
					nCard2=nTable[nRandomTable[i]]-1;
					if(cOrder==GetOrder(nMadeType, nCard1, nCard2)){
						if(RESULT_NOJJOK==GetAnother(nMadeType, nCard1, nCard2)){
							break;
						}
					}
				}
				nCard1=nCard1+((0==IRandom(2))?(10):(0));
				nCard2=nCard2+((1==IRandom(2))?(10):(0));
			}
			break;
		case RESULT_FOUR_SIX:
			{
				nCard1=4+((0==nRandom)?(10):(0))-1;
				nCard2=6+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_TEN_FOUR:
			{
				nCard1=4+((0==nRandom)?(10):(0))-1;
				nCard2=10+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_TEN_ONE:
			{
				nCard1=1+((0==nRandom)?(10):(0))-1;
				nCard2=10+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_ONE_NINE:
			{
				nCard1=1+((0==nRandom)?(10):(0))-1;
				nCard2=9+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_ONE_FOUR:
			{
				nCard1=1+((0==nRandom)?(10):(0))-1;
				nCard2=4+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_ONE_TWO:
			{
				nCard1=1+((0==nRandom)?(10):(0))-1;
				nCard2=2+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_1DDANG:
			{
				nCard1=1+((0==nRandom)?(10):(0))-1;
				nCard2=1+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_2DDANG:
			{
				nCard1=2+((0==nRandom)?(10):(0))-1;
				nCard2=2+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_3DDANG:
			{
				nCard1=3+((0==nRandom)?(10):(0))-1;
				nCard2=3+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_4DDANG:
			{
				nCard1=4+((0==nRandom)?(10):(0))-1;
				nCard2=4+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_5DDANG:
			{
				nCard1=5+((0==nRandom)?(10):(0))-1;
				nCard2=5+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_6DDANG:
			{
				nCard1=6+((0==nRandom)?(10):(0))-1;
				nCard2=6+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_7DDANG:
			{
				nCard1=7+((0==nRandom)?(10):(0))-1;
				nCard2=7+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_8DDANG:
			{
				nCard1=8+((0==nRandom)?(10):(0))-1;
				nCard2=8+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_9DDANG:
			{
				nCard1=9+((0==nRandom)?(10):(0))-1;
				nCard2=9+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_10DDANG:
			{
				nCard1=10+((0==nRandom)?(10):(0))-1;
				nCard2=10+((1==nRandom)?(10):(0))-1;
			}
			break;
		case RESULT_13DDANG: nCard1=1-1; nCard2=3-1; break;
		case RESULT_18DDANG: nCard1=1-1; nCard2=8-1; break;
		case RESULT_38DDANG: nCard1=3-1; nCard2=8-1; break;
		}
	}
	if(MADETYPE_NOANOTHER==nMadeType){
		nCard1+=20;
		nCard2+=20;
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::ResultToCard(int nMadeType, char cMade, char cAnother, char cOrder, int &nMadeCard1, int &nMadeCard2, int &nMadeCard3, int &nCard1, int &nCard2)
{
	if(MADETYPE_MADE==nMadeType){
		int nRandom=IRandom(2);
		switch(cMade){
		case MADE_118:
		case MADENUM_118:
			{
				nMadeCard1=1+((0==nRandom)?(20):(30))-1;
				nMadeCard2=1+((1==nRandom)?(20):(30))-1;
				nMadeCard3=8+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_127:
		case MADENUM_127:
			{
				nMadeCard1=1+((0==nRandom)?(20):(30))-1;
				nMadeCard2=2+((1==nRandom)?(20):(30))-1;
				nMadeCard3=7+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_136:
		case MADENUM_136:
			{
				nMadeCard1=1+((0==nRandom)?(20):(30))-1;
				nMadeCard2=3+((1==nRandom)?(20):(30))-1;
				nMadeCard3=6+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_145:
		case MADENUM_145:
			{
				nMadeCard1=1+((0==nRandom)?(20):(30))-1;
				nMadeCard2=4+((1==nRandom)?(20):(30))-1;
				nMadeCard3=5+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_190:
		case MADENUM_190:
			{
				nMadeCard1=1+((0==nRandom)?(20):(30))-1;
				nMadeCard2=9+((1==nRandom)?(20):(30))-1;
				nMadeCard3=10+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_226:
		case MADENUM_226:
			{
				nMadeCard1=2+((0==nRandom)?(20):(30))-1;
				nMadeCard2=2+((1==nRandom)?(20):(30))-1;
				nMadeCard3=6+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_235:
		case MADENUM_235:
			{
				nMadeCard1=2+((0==nRandom)?(20):(30))-1;
				nMadeCard2=3+((1==nRandom)?(20):(30))-1;
				nMadeCard3=5+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_280:
		case MADENUM_280:
			{
				nMadeCard1=2+((0==nRandom)?(20):(30))-1;
				nMadeCard2=8+((1==nRandom)?(20):(30))-1;
				nMadeCard3=10+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_334:
		case MADENUM_334:
			{
				nMadeCard1=3+((0==nRandom)?(20):(30))-1;
				nMadeCard2=3+((1==nRandom)?(20):(30))-1;
				nMadeCard3=4+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_370:
		case MADENUM_370:
			{
				nMadeCard1=3+((0==nRandom)?(20):(30))-1;
				nMadeCard2=7+((1==nRandom)?(20):(30))-1;
				nMadeCard3=10+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_389:
		case MADENUM_389:
			{
				nMadeCard1=3+((0==nRandom)?(20):(30))-1;
				nMadeCard2=8+((1==nRandom)?(20):(30))-1;
				nMadeCard3=9+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_442:
		case MADENUM_442:
			{
				nMadeCard1=4+((0==nRandom)?(20):(30))-1;
				nMadeCard2=4+((1==nRandom)?(20):(30))-1;
				nMadeCard3=2+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_460:
		case MADENUM_460:
			{
				nMadeCard1=4+((0==nRandom)?(20):(30))-1;
				nMadeCard2=6+((1==nRandom)?(20):(30))-1;
				nMadeCard3=10+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_479:
		case MADENUM_479:
			{
				nMadeCard1=4+((0==nRandom)?(20):(30))-1;
				nMadeCard2=7+((1==nRandom)?(20):(30))-1;
				nMadeCard3=9+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_550:
		case MADENUM_550:
			{
				nMadeCard1=5+((0==nRandom)?(20):(30))-1;
				nMadeCard2=5+((1==nRandom)?(20):(30))-1;
				nMadeCard3=10+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_569:
		case MADENUM_569:
			{
				nMadeCard1=5+((0==nRandom)?(20):(30))-1;
				nMadeCard2=6+((1==nRandom)?(20):(30))-1;
				nMadeCard3=9+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_578:
		case MADENUM_578:
			{
				nMadeCard1=5+((0==nRandom)?(20):(30))-1;
				nMadeCard2=7+((1==nRandom)?(20):(30))-1;
				nMadeCard3=8+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_668:
		case MADENUM_668:
			{
				nMadeCard1=6+((0==nRandom)?(20):(30))-1;
				nMadeCard2=6+((1==nRandom)?(20):(30))-1;
				nMadeCard3=8+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_776:
		case MADENUM_776:
			{
				nMadeCard1=7+((0==nRandom)?(20):(30))-1;
				nMadeCard2=7+((1==nRandom)?(20):(30))-1;
				nMadeCard3=6+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_884:
		case MADENUM_884:
			{
				nMadeCard1=8+((0==nRandom)?(20):(30))-1;
				nMadeCard2=8+((1==nRandom)?(20):(30))-1;
				nMadeCard3=4+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_992:
		case MADENUM_992:
			{
				nMadeCard1=9+((0==nRandom)?(20):(30))-1;
				nMadeCard2=9+((1==nRandom)?(20):(30))-1;
				nMadeCard3=2+((0==nRandom)?(20):(30))-1;
			}
			break;
		case MADE_000:
		case MADENUM_000:
			{
				nMadeCard1=0+((0==nRandom)?(10):(20))-1;
				nMadeCard2=0+((1==nRandom)?(10):(20))-1;
				nMadeCard3=0+((0==nRandom)?(30):(40))-1;
			}
			break;
		default:
			{
				int nNoMade[5]={-1,-1,-1,-1,-1};
				nNoMade[0]=IRandom(40);
				nNoMade[1]=IRandom(40);
				int nFind=2;
				bool bFind=FALSE;
				while(4>=nFind){
					nNoMade[nFind]=IRandom(40);
					bFind=FALSE;
					for(int i=0; i<5-2; i++){
						if(-1==nNoMade[i]) continue;
						if(i>=nFind) continue;
						for(int j=i+1; j<5-1; j++){
							if(-1==nNoMade[j]) continue;
							if(j>=nFind) continue;
							for(int k=j+1; k<5; k++){
								if(-1==nNoMade[k]) continue;
								if(k<nFind) continue;
								if(0==(((nNoMade[i]+1)+(nNoMade[j]+1)+(nNoMade[k]+1))%10)){
									bFind=TRUE;
									goto GoFind;
								}
							}
						}
					}
GoFind:
					if(FALSE==bFind){
						nFind++;
					}
				}
				nMadeCard1=nNoMade[0];
				nMadeCard2=nNoMade[1];
				nMadeCard3=nNoMade[2];
				nCard1=nNoMade[3];
				nCard2=nNoMade[4];
			}
			return;
		}
	}
	ResultToCard(nMadeType, cAnother, cOrder, nCard1, nCard2);
}
////------------------------------------------------------------------//
////
////------------------------------------------------------------------//
//int CResultFactor::HighRestCard(vector<tRest>* pvtRestCard, bool b94)
//{
//	if(NULL==pvtRestCard) return -1;
//	int nTotal=(int)pvtRestCard->size();
//	int nArray=-1;
//	int nOrder=0;
//	for(int i=0; i<nTotal; i++){
//		if(2<=nTotal){
//			if(FALSE==b94){
//				if(-1!=IsAnother((*pvtRestCard)[i].m_nAnother)) continue;
//			}
//		}
//		if(nOrder<(*pvtRestCard)[i].m_nOrder){
//			nArray=i;
//			nOrder=(*pvtRestCard)[i].m_nOrder;
//		}
//	}
//	return nArray;
//}
////------------------------------------------------------------------//
////
////------------------------------------------------------------------//
//int CResultFactor::HighRestCard(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, bool b94)
//{
//	if(NULL==pvtRestCard) return -1;
//	char cInAnother=GetAnother(nMadeType, vCard);
//	char cInOrder=GetOrder(nMadeType, vCard);
//	int nTotal=(int)pvtRestCard->size();
//	int nArray=-1;
//	int nOrder=0;
//	for(int i=0; i<nTotal; i++){
//		if(2<=nTotal){
//			if(FALSE==b94){
//				if(-1!=IsAnother((*pvtRestCard)[i].m_nAnother)) continue;
//			}
//		}
//		if(nOrder<(*pvtRestCard)[i].m_nOrder){
//			nArray=i;
//			nOrder=(*pvtRestCard)[i].m_nOrder;
//		}
//	}
//	if(RESULT_NONE!=cInOrder){
//		if(FALSE==b94){
//			if(-1==IsAnother(cInAnother)){
//				if(cInOrder==nOrder) return -1;
//			}
//		}
//	}
//	//if(-1!=nArray){
//	//	if(2<=vCard.size()){
//	//		if(TRUE==SameCard(&((*pvtRestCard)[nArray]), vCard[0], vCard[1])) return -1;
//	//	}
//	//}
//	return nArray;
//}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::HighRestCard(vector<tRest>* pvtRestCard, int &nSelect94)
{
	if(NULL==pvtRestCard) return -1;
	int nTotal=(int)pvtRestCard->size();
	int nArray=-1;
	int nOrder=0;
	char cAnother=RESULT_NONE;
	//for(int i=0; i<nTotal; i++){
	//	if(nSelect94==IsAnother((char)(*pvtRestCard)[i].m_nAnother)){
	//		if(RESULT_NONE!=nSelect94){
	//			return i;
	//		}
	//		if(nOrder<(*pvtRestCard)[i].m_nOrder){
	//			nArray=i;
	//			nOrder=(*pvtRestCard)[i].m_nOrder;
	//		}
	//	}
	//	else{
	//		if(cAnother<=(char)(*pvtRestCard)[i].m_nAnother){
	//			cAnother=(char)(*pvtRestCard)[i].m_nAnother;
	//		}
	//	}
	//}
	for(int i=0; i<nTotal; i++){
		if(nSelect94==IsAnother((char)(*pvtRestCard)[i].m_nAnother)){
			if(RESULT_NONE!=nSelect94){
				if(cAnother<=(char)(*pvtRestCard)[i].m_nAnother){
					cAnother=(char)((*pvtRestCard)[i].m_nAnother);
					nArray=i;
				}
			}
			else{
				if(nOrder<(*pvtRestCard)[i].m_nOrder){
					nArray=i;
					nOrder=(*pvtRestCard)[i].m_nOrder;
				}
			}
		}
		else{
			if(cAnother<=(char)(*pvtRestCard)[i].m_nAnother){
				cAnother=(char)(*pvtRestCard)[i].m_nAnother;
			}
		}
	}
	if((0<nTotal)&&(-1==nArray)){
		nSelect94=IsAnother(cAnother);
		for(int i=0; i<nTotal; i++){
			if(nSelect94==IsAnother((char)(*pvtRestCard)[i].m_nAnother)){
				if(RESULT_NONE!=nSelect94){
					return i;
				}
				if(nOrder<(*pvtRestCard)[i].m_nOrder){
					nArray=i;
					nOrder=(*pvtRestCard)[i].m_nOrder;
				}
			}
		}
	}
	return nArray;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::HighRestCard(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, int nFindOrder)
{
	if(NULL==pvtRestCard) return RESULT_NONE;
	int nTotal=(int)pvtRestCard->size();
	int nArray=RESULT_NONE;
	int nOrder=RESULT_NONE;
	for(int i=0; i<nTotal; i++){
		if(nOrder<(*pvtRestCard)[i].m_nOrder){
			nArray=i;
			nOrder=(*pvtRestCard)[i].m_nOrder;
		}
	}
	return nArray;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::HighRestCard94(int nMadeType, vector<tRest>* pvtRestCard, vector<long> vCard, int &nSelect94, int nFindOrder)
{
	if(NULL==pvtRestCard) return RESULT_NONE;
	char cInAnother=GetAnother(nMadeType, vCard, nFindOrder);
	char cInOrder=GetOrder(nMadeType, vCard, nFindOrder);
	int nTotal=(int)pvtRestCard->size();
	int nArray=RESULT_NONE;
	int nOrder=RESULT_NONE;
	char cAnother=RESULT_NONE;
	for(int i=0; i<nTotal; i++){
		if(nSelect94==IsAnother((char)(*pvtRestCard)[i].m_nAnother)){
			if(RESULT_NONE!=nSelect94){
				if(cAnother<=(char)(*pvtRestCard)[i].m_nAnother){
					cAnother=(char)((*pvtRestCard)[i].m_nAnother);
					nArray=i;
				}
			}
			else{
				if(nOrder<(*pvtRestCard)[i].m_nOrder){
					nArray=i;
					nOrder=(*pvtRestCard)[i].m_nOrder;
				}
			}
		}
		else{
			if(cAnother<=(char)(*pvtRestCard)[i].m_nAnother){
				cAnother=(char)(*pvtRestCard)[i].m_nAnother;
			}
		}
	}
	if(0<nTotal){
		if(-1==nArray){
			nSelect94=IsAnother(cAnother);
			for(int i=0; i<nTotal; i++){
				if(nSelect94==IsAnother((char)(*pvtRestCard)[i].m_nAnother)){
					if(RESULT_NONE!=nSelect94){
						return i;
					}
					if(nOrder<(*pvtRestCard)[i].m_nOrder){
						nArray=i;
						nOrder=(*pvtRestCard)[i].m_nOrder;
					}
				}
			}
		}
		else{
			nOrder=(char)(*pvtRestCard)[nArray].m_nOrder;
		}
	}
	if(RESULT_NONE!=cInOrder){
		if(nSelect94==IsAnother(cInAnother)){
			if(cInOrder==nOrder) return RESULT_NONE;
		}
	}
	//if(-1!=nArray){
	//	if(2<=vCard.size()){
	//		if(TRUE==SameCard(&((*pvtRestCard)[nArray]), vCard[0], vCard[1])) return -1;
	//	}
	//}
	return nArray;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::SameCard(tRest* ptRest, int nCard1, int nCard2)
{
	if(NULL==ptRest) return FALSE;
	int nSelect1=(int)Min2(((ptRest->m_tCardArray1.m_tCard.sCard+1)%10), ((ptRest->m_tCardArray2.m_tCard.sCard+1)%10));
	int nSelect2=(int)Max2(((ptRest->m_tCardArray1.m_tCard.sCard+1)%10), ((ptRest->m_tCardArray2.m_tCard.sCard+1)%10));
	int nCheck1=Min2(((nCard1+1)%10), ((nCard2+1)%10));
	int nCheck2=Max2(((nCard1+1)%10), ((nCard2+1)%10));
	return ((nSelect1==nCheck1)&&(nSelect2==nCheck2));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::FindMade(vector<tMade>* pvtMadeCard, int nMade)
{
	if(NULL==pvtMadeCard) return FALSE;
	int nTotal=(int)pvtMadeCard->size();
	int nArray=-1;
	for(int i=0; i<nTotal; i++){
		if(nMade==(*pvtMadeCard)[i].m_nMade){
			nArray=i;
			break;
		}
	}
	return nArray;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::OrderAnother(vector<tRest>* pvtRestCard, char aAnother, char aOrder)
{
	if(NULL==pvtRestCard) return FALSE;
	int nTotal=(int)pvtRestCard->size();
	int nArray=-1;
	for(int i=0; i<nTotal; i++){
		if(RESULT_NONE!=aAnother){
			if((int)aAnother==(*pvtRestCard)[i].m_nAnother){
				nArray=i;
				break;
			}
		}
		else{
			if((int)aOrder==(*pvtRestCard)[i].m_nOrder){
				nArray=i;
				break;
			}
		}
	}
	return nArray;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsUsableArray(int nArray)
{
	return ((0<=nArray)&&(((int)m_vCard.size()-1)>=nArray));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsUsableArray(int nArray1, int nArray2)
{
	if(FALSE==((0<=nArray1)&&(((int)m_vCard.size()-1)>=nArray1))) return FALSE;
	if(FALSE==((0<=nArray2)&&(((int)m_vCard.size()-1)>=nArray2))) return FALSE;
	return (nArray1!=nArray2);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsUsableArray(int nArray1, int nArray2, int nArray3)
{
	if(FALSE==((0<=nArray1)&&(((int)m_vCard.size()-1)>=nArray1))) return FALSE;
	if(FALSE==((0<=nArray2)&&(((int)m_vCard.size()-1)>=nArray2))) return FALSE;
	if(FALSE==((0<=nArray3)&&(((int)m_vCard.size()-1)>=nArray3))) return FALSE;
	return ((nArray1!=nArray2)&&(nArray2!=nArray3)&&(nArray1!=nArray3));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsUsableMadeArray(int nMadeArray)
{
	return ((0<=nMadeArray)&&(((int)m_vtMade.size()-1)>=nMadeArray));
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::AddResultCard(int nCard)
{
	m_vCard.push_back(nCard);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultCard(vector<int> vCard)
{
	m_vCard=vCard;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultCard(vector<long> vCard)
{
	m_vCard.clear();
	int nTotal=(int)vCard.size();
	for(int i=0; i<nTotal; i++){
		m_vCard.push_back(vCard[i]);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::ChangeResultCard(int nArray, int nCard)
{
	if(FALSE==IsUsableArray(nArray)) return;
	m_vCard[nArray]=nCard;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::DelResultCard(int nCard)
{
	vector<int>::iterator Find;
	Find=find(m_vCard.begin(), m_vCard.end(), nCard);
	if(m_vCard.end()==Find){
		m_vCard.erase(Find);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactor(CResultFactor* pcResultFactor)
{
	if(NULL==pcResultFactor) return;
	m_nResult=pcResultFactor->m_nResult;
	m_nSelect=pcResultFactor->m_nSelect;
	m_tCardArray1=pcResultFactor->m_tCardArray1;
	m_tCardArray2=pcResultFactor->m_tCardArray2;
	m_nRule=pcResultFactor->m_nRule;
	m_nIndex=pcResultFactor->m_nIndex;
	m_vCard=pcResultFactor->m_vCard;
	m_vtMade=pcResultFactor->m_vtMade;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorNoMadeToSelect(int nMadeType, short sSelect, int nFindOrder)
{
	tResultFactor::Clear();
	int nArray1=0;
	int nArray2=1;
	sSelect=SelectToArray(sSelect, nArray1, nArray2);
	if(FALSE==IsUsableArray(nArray1, nArray2)){
		if(2>m_vCard.size()){
			return;
		}
		nArray1=0;
		nArray2=1;
		sSelect=ArrayToSelect(nArray1, nArray2);
	}
	Select(sSelect, 0, FALSE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cMade=MADENUM_NONE;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorNoMadeToArray(int nMadeType, int nArray1, int nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	if(FALSE==IsUsableArray(nArray1, nArray2)){
		if(2>m_vCard.size()){
			return;
		}
		nArray1=0;
		nArray2=1;
	}
	Select(ArrayToSelect(nArray1, nArray2), 0, FALSE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cMade=MADENUM_NONE;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorNoMadeToSelect(int nMadeType, short sSelect, int &nArray1, int &nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	sSelect=SelectToArray(sSelect, nArray1, nArray2);
	if(FALSE==IsUsableArray(nArray1, nArray2)){
		if(2>m_vCard.size()){
			return;
		}
		nArray1=0;
		nArray2=1;
		sSelect=ArrayToSelect(nArray1, nArray2);
	}
	Select(sSelect, 0, FALSE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cMade=MADENUM_NONE;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorNoMadeToArray(int nMadeType, short &sSelect, int nArray1, int nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	if(FALSE==IsUsableArray(nArray1, nArray2)){
		if(2>m_vCard.size()){
			return;
		}
		nArray1=0;
		nArray2=1;
	}
	sSelect=ArrayToSelect(nArray1, nArray2);
	Select(sSelect, 0, FALSE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cMade=MADENUM_NONE;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::FindResultFactorNoMade(int nMadeType, char cAnother, char cOrder, int &nArray1, int &nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	int nSize=(int)m_vCard.size();
	nArray1=-1;
	nArray2=-1;
	short sFindOrder=0;
	char cFindAnother=0;
	for(int i=0; i<nSize-1; i++){
		if(-1==m_vCard[i]) continue;
		for(int j=i+1; j<nSize; j++){
			if(-1==m_vCard[j]) continue;
			cFindAnother=GetAnother(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
			sFindOrder=GetOrder(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
			if((sFindOrder==cOrder)&&(cFindAnother==cAnother)){
				nArray1=i;
				nArray2=j;
			}
		}
	}
	SetResultFactorNoMadeToArray(nMadeType, nArray1, nArray2, nFindOrder);
	return (int)m_tSelect.sSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorMadeToSelect(int nMadeType, short sMadeSelect, int nFindOrder)
{
	tResultFactor::Clear();
	if(3>m_vCard.size()) return;
	m_tResult.cMade=MADENUM_NONE;
	MadeResultFactor();
	if(FALSE==m_vtMade.empty()){
		m_tResult.cMade=RESULT_MADE;
	}
	int nArray1=-1;
	int nArray2=-1;
	sMadeSelect=MadeSelectToArray(sMadeSelect, nArray1, nArray2);
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)) return;
	m_tSelect.sMadeSelect=sMadeSelect;
	m_tResult.cMade=(char)m_vtMade[m_tSelect.sMadeSelect].m_nMade;
	if(FALSE==IsUsableArray(nArray1, nArray2)) return;
	m_tSelect.sSelect=ArrayToSelect(nArray1, nArray2);
	Select(m_tSelect.sSelect, m_tSelect.sMadeSelect, TRUE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorMadeToArray(int nMadeType, int nMadeArray1, int nMadeArray2, int nMadeArray3, int nFindOrder)
{
	tResultFactor::Clear();
	if(3>m_vCard.size()) return;
	m_tResult.cMade=MADENUM_NONE;
	MadeResultFactor();
	if(FALSE==m_vtMade.empty()){
		m_tResult.cMade=RESULT_MADE;
	}
	int nArray1=-1;
	int nArray2=-1;
	short sMadeSelect=MadeSelectToArray(nMadeArray1, nMadeArray2, nMadeArray3, nArray1, nArray2);
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)) return;
	m_tSelect.sMadeSelect=sMadeSelect;
	m_tResult.cMade=(char)m_vtMade[m_tSelect.sMadeSelect].m_nMade;
	if(FALSE==IsUsableArray(nArray1, nArray2)) return;
	m_tSelect.sSelect=ArrayToSelect(nArray1, nArray2);
	Select(m_tSelect.sSelect, m_tSelect.sMadeSelect, TRUE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorMadeToRemain(int nMadeType, int nArray1, int nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	if(3>m_vCard.size()) return;
	m_tResult.cMade=MADENUM_NONE;
	MadeResultFactor();
	if(FALSE==m_vtMade.empty()){
		m_tResult.cMade=RESULT_MADE;
	}
	short sMadeSelect=ArrayToMadeSelect(nArray1, nArray2);
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)) return;
	m_tSelect.sMadeSelect=sMadeSelect;
	m_tResult.cMade=(char)m_vtMade[m_tSelect.sMadeSelect].m_nMade;
	if(FALSE==IsUsableArray(nArray1, nArray2)) return;
	m_tSelect.sSelect=ArrayToSelect(nArray1, nArray2);
	Select(m_tSelect.sSelect, m_tSelect.sMadeSelect, TRUE);
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorMadeToSelect(int nMadeType, short sMadeSelect, int &nArray1, int &nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	if(3>m_vCard.size()) return;
	m_tResult.cMade=MADENUM_NONE;
	MadeResultFactor();
	if(FALSE==m_vtMade.empty()){
		m_tResult.cMade=RESULT_MADE;
	}
	sMadeSelect=MadeSelectToArray(sMadeSelect, nArray1, nArray2);
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)) return;
	m_tSelect.sMadeSelect=sMadeSelect;
	m_tResult.cMade=(char)m_vtMade[m_tSelect.sMadeSelect].m_nMade;
	if(FALSE==IsUsableArray(nArray1, nArray2)) return;
	m_tSelect.sSelect=ArrayToSelect(nArray1, nArray2);
	Select(m_tSelect.sSelect, m_tSelect.sMadeSelect, TRUE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorMadeToArray(int nMadeType, int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	if(3>m_vCard.size()) return;
	m_tResult.cMade=MADENUM_NONE;
	MadeResultFactor();
	if(FALSE==m_vtMade.empty()){
		m_tResult.cMade=RESULT_MADE;
	}
	short sMadeSelect=MadeSelectToArray(nMadeArray1, nMadeArray2, nMadeArray3, nArray1, nArray2);
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)) return;
	m_tSelect.sMadeSelect=sMadeSelect;
	m_tResult.cMade=(char)m_vtMade[m_tSelect.sMadeSelect].m_nMade;
	if(FALSE==IsUsableArray(nArray1, nArray2)) return;
	m_tSelect.sSelect=ArrayToSelect(nArray1, nArray2);
	Select(m_tSelect.sSelect, m_tSelect.sMadeSelect, TRUE);
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::SetResultFactorMadeToRemain(int nMadeType, short &sMadeSelect, int nArray1, int nArray2, int nFindOrder)
{
	tResultFactor::Clear();
	if(3>m_vCard.size()) return;
	m_tResult.cMade=MADENUM_NONE;
	MadeResultFactor();
	if(FALSE==m_vtMade.empty()){
		m_tResult.cMade=RESULT_MADE;
	}
	sMadeSelect=ArrayToMadeSelect(nArray1, nArray2);
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)) return;
	m_tSelect.sMadeSelect=sMadeSelect;
	m_tResult.cMade=(char)m_vtMade[m_tSelect.sMadeSelect].m_nMade;
	if(FALSE==IsUsableArray(nArray1, nArray2)) return;
	m_tSelect.sSelect=ArrayToSelect(nArray1, nArray2);
	Select(m_tSelect.sSelect, m_tSelect.sMadeSelect, TRUE);
	m_tCardArray1.m_tCard.sArray=(short)nArray1;
	m_tCardArray1.m_tCard.sCard=(short)m_vCard[nArray1];
	m_tCardArray2.m_tCard.sArray=(short)nArray2;
	m_tCardArray2.m_tCard.sCard=(short)m_vCard[nArray2];
	m_tResult.cOrder=GetOrder(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
	m_tResult.cAnother=GetAnother(nMadeType, m_tCardArray1.m_tCard.sCard, m_tCardArray2.m_tCard.sCard, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::FindResultFactorMade(int nMadeType, char cAnother, char cOrder, short &sMadeSelect, int &nArray1, int &nArray2, int nFindOrder)
{
	int nTotal=0;
	int nSize=(int)m_vCard.size();
	int nMadeSize=(int)m_vtMade.size();
	vector<int> vCheck;
	nArray1=-1;
	nArray2=-1;
	short sFindOrder=RESULT_NONE;
	char cFindAnother=RESULT_NONE;
	for(int j=0; j<nMadeSize; j++){
		vCheck.clear();
		for(int i=0; i<nSize; i++){
			if((i!=m_vtMade[j].m_tCardArray1.m_tCard.sArray)&&(i!=m_vtMade[j].m_tCardArray2.m_tCard.sArray)&&(i!=m_vtMade[j].m_tCardArray3.m_tCard.sArray)){
				vCheck.push_back(i);
			}
		}
		nTotal=(int)vCheck.size();
		for(int k=0; k<nTotal-1; k++){
			for(int l=k+1; l<nTotal; l++){
				cFindAnother=GetAnother(nMadeType, m_vCard[vCheck[k]], m_vCard[vCheck[l]], nFindOrder);
				sFindOrder=GetOrder(nMadeType, m_vCard[vCheck[k]], m_vCard[vCheck[l]], nFindOrder);
				if((sFindOrder==cOrder)&&(cFindAnother==cAnother)){
					nArray1=vCheck[k];
					nArray2=vCheck[l];
					sMadeSelect=(short)j;
				}
			}
		}
	}
	SetResultFactorMadeToSelect(nMadeType, sMadeSelect, nArray1, nArray2, nFindOrder);
	return (int)m_tSelect.sSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::HighResultFactor(int nMadeType, int nFindOrder)
{
	int nArray1=0;
	int nArray2=1;
	return HighResultFactor(nMadeType, nArray1, nArray2, nFindOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::HighResultFactor(int nMadeType, int &nArray1, int &nArray2, int nFindOrder)
{
	int nSize=(int)m_vCard.size();
	nArray1=0;
	nArray2=1;
	short sMadeSelect=RESULT_NONE;
	char cOrder=RESULT_NONE;
	char cOldOrder=RESULT_NONE;
	if(MADETYPE_MADE==nMadeType){
		MadeResultFactor();
		int nMadeSize=(int)m_vtMade.size();
		for(int k=0; k<nMadeSize; k++){
			for(int i=0; i<nSize-1; i++){
				if(-1==m_vCard[i]) continue;
				if((i==m_vtMade[k].m_tCardArray1.m_tCard.sArray)||(i==m_vtMade[k].m_tCardArray2.m_tCard.sArray)||(i==m_vtMade[k].m_tCardArray3.m_tCard.sArray)) continue;
				for(int j=i+1; j<nSize; j++){
					if(-1==m_vCard[j]) continue;
					if((j==m_vtMade[k].m_tCardArray1.m_tCard.sArray)||(j==m_vtMade[k].m_tCardArray2.m_tCard.sArray)||(j==m_vtMade[k].m_tCardArray3.m_tCard.sArray)) continue;
					cOrder=GetOrder(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
					if(cOldOrder<cOrder){
						sMadeSelect=(short)k;
						cOldOrder=cOrder;
						nArray1=i;
						nArray2=j;
					}
				}
			}
		}
		SetResultFactorMadeToSelect(nMadeType, sMadeSelect, nArray1, nArray2, nFindOrder);
		return (int)m_tSelect.sMadeSelect;
	}
	for(int i=0; i<nSize-1; i++){
		if(-1==m_vCard[i]) continue;
		for(int j=i+1; j<nSize; j++){
			if(-1==m_vCard[j]) continue;
			cOrder=GetOrder(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
			if(cOldOrder<cOrder){
				cOldOrder=cOrder;
				nArray1=i;
				nArray2=j;
			}
		}
	}
	SetResultFactorNoMadeToArray(nMadeType, nArray1, nArray2, nFindOrder);
	return (int)m_tSelect.sSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::ResultFactor(int nMadeType, vector<tMade>* pvtMadeCard, vector<tRest>* pvtRestCard, int nFindOrder)
{
	int nSize=(int)m_vCard.size();
	if(NULL!=pvtMadeCard){ pvtMadeCard->clear(); }
	if(NULL!=pvtRestCard){ pvtRestCard->clear(); }
	tRest tTempRest;
	if((MADETYPE_MADE==nMadeType)&&(NULL!=pvtMadeCard)){
		pvtMadeCard->clear();
		tMade tTempMade;
		for(int i=0; i<nSize-2; i++){
			if(-1==m_vCard[i]) continue;
			for(int j=i+1; j<nSize-1; j++){
				if(-1==m_vCard[j]) continue;
				for(int k=j+1; k<nSize; k++){
					if(-1==m_vCard[k]) continue;
					if(0==(((m_vCard[i]+1)+(m_vCard[j]+1)+(m_vCard[k]+1))%10)){
						tTempMade.m_tCardArray1.m_tCard.sArray=(short)i;
						tTempMade.m_tCardArray1.m_tCard.sCard=(short)m_vCard[i];
						tTempMade.m_tCardArray2.m_tCard.sArray=(short)j;
						tTempMade.m_tCardArray2.m_tCard.sCard=(short)m_vCard[j];
						tTempMade.m_tCardArray3.m_tCard.sArray=(short)k;
						tTempMade.m_tCardArray3.m_tCard.sCard=(short)m_vCard[k];
						tTempMade.m_nMade=GetMadeArray(m_vCard[i], m_vCard[j], m_vCard[k]);
						pvtMadeCard->push_back(tTempMade);
					}
				}
			}
		}
		if(NULL!=pvtRestCard){
			pvtRestCard->clear();
			int nMadeSize=(int)pvtMadeCard->size();
			for(int k=0; k<nMadeSize; k++){
				for(int i=0; i<nSize-1; i++){
					if(-1==m_vCard[i]) continue;
					if((i==(*pvtMadeCard)[k].m_tCardArray1.m_tCard.sArray)||(i==(*pvtMadeCard)[k].m_tCardArray2.m_tCard.sArray)||(i==(*pvtMadeCard)[k].m_tCardArray3.m_tCard.sArray)) continue;
					for(int j=i+1; j<nSize; j++){
						if(-1==m_vCard[j]) continue;
						if((j==(*pvtMadeCard)[k].m_tCardArray1.m_tCard.sArray)||(j==(*pvtMadeCard)[k].m_tCardArray2.m_tCard.sArray)||(j==(*pvtMadeCard)[k].m_tCardArray3.m_tCard.sArray)) continue;
						tTempRest.m_nOrder=(int)GetOrder(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
						tTempRest.m_nAnother=(int)GetAnother(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
						tTempRest.m_tCardArray1.m_tCard.sCard=(short)m_vCard[i];
						tTempRest.m_tCardArray1.m_tCard.sArray=(short)i;
						tTempRest.m_tCardArray2.m_tCard.sCard=(short)m_vCard[j];
						tTempRest.m_tCardArray2.m_tCard.sArray=(short)j;
						pvtRestCard->push_back(tTempRest);
					}
				}
			}
		}
		return nSize;
	}
	if(NULL!=pvtRestCard){
		pvtRestCard->clear();
		for(int i=0; i<nSize-1; i++){
			if(-1==m_vCard[i]) continue;
			for(int j=i+1; j<nSize; j++){
				if(-1==m_vCard[j]) continue;
				tTempRest.m_nOrder=(int)GetOrder(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
				tTempRest.m_nAnother=(int)GetAnother(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
				tTempRest.m_tCardArray1.m_tCard.sCard=(short)m_vCard[i];
				tTempRest.m_tCardArray1.m_tCard.sArray=(short)i;
				tTempRest.m_tCardArray2.m_tCard.sCard=(short)m_vCard[j];
				tTempRest.m_tCardArray2.m_tCard.sArray=(short)j;
			}
		}
	}
	return nSize;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::IsResultFactor(int nMadeType, char cOrder, int nFindOrder)
{
	int nSize=(int)m_vCard.size();
	char cCurOrder=0;
	if(MADETYPE_MADE==nMadeType){
		MadeResultFactor();
		int nMadeSize=(int)m_vtMade.size();
		for(int k=0; k<nMadeSize; k++){
			for(int i=0; i<nSize-1; i++){
				if(-1==m_vCard[i]) continue;
				if((i==m_vtMade[k].m_tCardArray1.m_tCard.sArray)||(i==m_vtMade[k].m_tCardArray2.m_tCard.sArray)||(i==m_vtMade[k].m_tCardArray3.m_tCard.sArray)) continue;
				for(int j=i+1; j<nSize; j++){
					if(-1==m_vCard[j]) continue;
					if((j==m_vtMade[k].m_tCardArray1.m_tCard.sArray)||(j==m_vtMade[k].m_tCardArray2.m_tCard.sArray)||(j==m_vtMade[k].m_tCardArray3.m_tCard.sArray)) continue;
					cCurOrder=GetOrder(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
					if(cCurOrder==cOrder){
						return TRUE;
					}
				}
			}
		}
		return FALSE;
	}
	for(int i=0; i<nSize-1; i++){
		if(-1==m_vCard[i]) continue;
		for(int j=i+1; j<nSize; j++){
			if(-1==m_vCard[j]) continue;
			cCurOrder=GetOrder(nMadeType, m_vCard[i], m_vCard[j], nFindOrder);
			if(cCurOrder==cOrder){
				return TRUE;
			}
		}
	}
	return FALSE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::MadeResultFactor(void)
{
	m_vtMade.clear();
	tMade tTempMade;
	int nSize=(int)m_vCard.size();
	for(int i=0; i<nSize-2; i++){
		if(-1==m_vCard[i]) continue;
		for(int j=i+1; j<nSize-1; j++){
			if(-1==m_vCard[j]) continue;
			for(int k=j+1; k<nSize; k++){
				if(-1==m_vCard[k]) continue;
				if(0==(((m_vCard[i]+1)+(m_vCard[j]+1)+(m_vCard[k]+1))%10)){
					tTempMade.m_tCardArray1.m_tCard.sArray=(short)i;
					tTempMade.m_tCardArray1.m_tCard.sCard=(short)m_vCard[i];
					tTempMade.m_tCardArray2.m_tCard.sArray=(short)j;
					tTempMade.m_tCardArray2.m_tCard.sCard=(short)m_vCard[j];
					tTempMade.m_tCardArray3.m_tCard.sArray=(short)k;
					tTempMade.m_tCardArray3.m_tCard.sCard=(short)m_vCard[k];
					tTempMade.m_nMade=GetMadeArray(m_vCard[i], m_vCard[j], m_vCard[k]);
					m_vtMade.push_back(tTempMade);
				}
			}
		}
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultFactor::MadeResultExceptFactor(vector<tCardArray>* pvExecptCardArray)
{
	if(NULL==pvExecptCardArray) return;
	pvExecptCardArray->clear();
	int nSize=(int)m_vCard.size();
	tCardArray tTempCardArray;
	int nMadeSize=(int)m_vtMade.size();
	for(int j=0; j<nMadeSize; j++){
		for(int i=0; i<nSize; i++){
//			if((m_vCard[i]!=m_vtMade[j].m_tCardArray1.m_tCard.sCard)&&(m_vCard[i]!=m_vtMade[j].m_tCardArray2.m_tCard.sCard)&&(m_vCard[i]!=m_vtMade[j].m_tCardArray3.m_tCard.sCard)){
			if((i!=m_vtMade[j].m_tCardArray1.m_tCard.sArray)&&(i!=m_vtMade[j].m_tCardArray2.m_tCard.sArray)&&(i!=m_vtMade[j].m_tCardArray3.m_tCard.sArray)){
				tTempCardArray.m_tCard.sArray=(short)i;
				tTempCardArray.m_tCard.sCard=(short)m_vCard[i];
				pvExecptCardArray->push_back(tTempCardArray);
			}
		}
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::MadeResultExceptFactor(short sMadeSelect, vector<tCardArray>* pvExecptCardArray)
{
	if(NULL==pvExecptCardArray) return -1;
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)){
		if(0==m_vtMade.size()){
			return -1;
		}
		sMadeSelect=0;
	}
	pvExecptCardArray->clear();
	int nSize=(int)m_vCard.size();
	tCardArray tTempCardArray;
	for(int i=0; i<nSize; i++){
//		if((m_vCard[i]!=m_vtMade[sMadeSelect].m_tCardArray1.m_tCard.sCard)&&(m_vCard[i]!=m_vtMade[sMadeSelect].m_tCardArray2.m_tCard.sCard)&&(m_vCard[i]!=m_vtMade[sMadeSelect].m_tCardArray3.m_tCard.sCard)){
		if((i!=m_vtMade[sMadeSelect].m_tCardArray1.m_tCard.sArray)&&(i!=m_vtMade[sMadeSelect].m_tCardArray2.m_tCard.sArray)&&(i!=m_vtMade[sMadeSelect].m_tCardArray3.m_tCard.sArray)){
			tTempCardArray.m_tCard.sArray=(short)i;
			tTempCardArray.m_tCard.sCard=(short)m_vCard[i];
			pvExecptCardArray->push_back(tTempCardArray);
		}
	}
	return sMadeSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::SelectToArray(short sSelect, int &nArray1, int &nArray2)
{
	int nSize=(int)m_vCard.size();
	if(0>sSelect){
		if(2<=nSize){
			sSelect=0;
			nArray1=0;
			nArray2=1;
		}
		else{
			sSelect=-1;
			nArray1=-1;
			nArray2=-1;
		}
		return sSelect;
	}
	int nCount=0; 
	for(int i=0; i<nSize-1; i++){
		for(int j=i+1; j<nSize; j++){
			if((int)sSelect==nCount){
				nArray1=i;
				nArray2=j;
				return sSelect;
			}
			nCount++;
		}
	}
	return sSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::MadeSelectToArray(short sMadeSelect, int &nArray1, int &nArray2)
{
	vector<tCardArray> vExecptCardArray;
	sMadeSelect=MadeResultExceptFactor(sMadeSelect, &vExecptCardArray);
	nArray1=nArray2=-1;
	if(-1==sMadeSelect) return sMadeSelect;
	int nSize=(int)vExecptCardArray.size();
	short sArray[2]={-1, -1};
	for(int i=0; i<min(2, nSize); i++){
		sArray[i]=vExecptCardArray[i].m_tCard.sArray;
	}
	nArray1=(int)sArray[0];
	nArray2=(int)sArray[1];
	return sMadeSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::MadeSelectToArray(int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2)
{
	vector<tCardArray> vExecptCardArray;
	short sMadeSelect=ArrayToMadeSelect(nMadeArray1, nMadeArray2, nMadeArray3);
	nArray1=nArray2=-1;
	if(-1==sMadeSelect) return sMadeSelect;
	sMadeSelect=MadeResultExceptFactor(sMadeSelect, &vExecptCardArray);
	int nSize=(int)vExecptCardArray.size();
	short sArray[2]={-1, -1};
	for(int i=0; i<min(2, nSize); i++){
		sArray[i]=vExecptCardArray[i].m_tCard.sArray;
	}
	nArray1=(int)sArray[0];
	nArray2=(int)sArray[1];
	return sMadeSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::MadeSelectToMadeArray(short sMadeSelect, int &nMadeArray1, int &nMadeArray2, int &nMadeArray3)
{
	nMadeArray1=nMadeArray2=nMadeArray3=-1;
	if(FALSE==IsUsableMadeArray((int)sMadeSelect)) return -1;
	nMadeArray1=(int)m_vtMade[sMadeSelect].m_tCardArray1.m_tCard.sArray;
	nMadeArray2=(int)m_vtMade[sMadeSelect].m_tCardArray2.m_tCard.sArray;
	nMadeArray3=(int)m_vtMade[sMadeSelect].m_tCardArray3.m_tCard.sArray;
	return sMadeSelect;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::ArrayToSelect(int nArray1, int nArray2)
{
	if(FALSE==IsUsableArray(nArray1, nArray2)) return -1;
	int nSize=(int)m_vCard.size();
	int nCheck1=Min2(nArray1, nArray2);
	int nCheck2=Max2(nArray1, nArray2);
	short sSelect=0; 
	for(int i=0; i<nSize-1; i++){
		for(int j=i+1; j<nSize; j++){
			if((nCheck1==i)&&(nCheck2==j)){
				return sSelect;
			}
			sSelect++;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::ArrayToMadeSelect(int nArray1, int nArray2)
{
	if(FALSE==IsUsableArray(nArray1, nArray2)) return -1;
	int nTotal=0;
	int nSize=(int)m_vCard.size();
	int nMadeSize=(int)m_vtMade.size();
	vector<int> vCheck;
	int nCheck1=Min2(nArray1, nArray2);
	int nCheck2=Max2(nArray1, nArray2);
	for(int j=0; j<nMadeSize; j++){
		vCheck.clear();
		for(int i=0; i<nSize; i++){
			if((i!=(int)m_vtMade[j].m_tCardArray1.m_tCard.sArray)&&(i!=(int)m_vtMade[j].m_tCardArray2.m_tCard.sArray)&&(i!=(int)m_vtMade[j].m_tCardArray3.m_tCard.sArray)){
				vCheck.push_back(i);
			}
		}
		nTotal=(int)vCheck.size();
		for(int k=0; k<nTotal-1; k++){
			for(int l=k+1; l<nTotal; l++){
				if((nCheck1==vCheck[k])&&(nCheck2==vCheck[l])){
					return (short)j;
				}
			}
		}
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
short CResultFactor::ArrayToMadeSelect(int nMadeArray1, int nMadeArray2, int nMadeArray3)
{
	if(FALSE==IsUsableArray(nMadeArray1, nMadeArray2, nMadeArray3)) return -1;
	int nMadeSize=(int)m_vtMade.size();
	vector<int> vCheck;
	int nCheck1=Min3(nMadeArray1, nMadeArray2, nMadeArray3);
	int nCheck2=Middle3(nMadeArray1, nMadeArray2, nMadeArray3);
	int nCheck3=Max3(nMadeArray1, nMadeArray2, nMadeArray3);
	for(int j=0; j<nMadeSize; j++){
		if((nCheck1==(int)m_vtMade[j].m_tCardArray1.m_tCard.sArray)&&(nCheck2==(int)m_vtMade[j].m_tCardArray2.m_tCard.sArray)&&(nCheck3==(int)m_vtMade[j].m_tCardArray3.m_tCard.sArray)){
			return (short)j;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultFactor::GetResultFactor(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94)
{
	tResultFactor tTempResultFactor;
	tTempResultFactor.m_tResult.cReserve=0;
	tTempResultFactor.m_tResult.cOrder=m_tResult.cOrder;
	if(MADETYPE_MADE==nMadeType){
		if(MADENUM_NONE==m_tResult.cMade){
			tTempResultFactor.m_tResult.cMade=RESULT_NOMADE;
		}
		else{
			tTempResultFactor.m_tResult.cMade=RESULT_MADE;
		}
		tTempResultFactor.m_tResult.cAnother=GetResultAnother(nMadeType, bIsDdang19, bIsDdang10, bIsGhangDdang138, bIsGhangDdang38, bIsFool94);
	}
	else if(MADETYPE_NONE==nMadeType){
		tTempResultFactor.m_tResult.cAnother=GetResultAnother(nMadeType, bIsDdang19, bIsDdang10, bIsGhangDdang138, bIsGhangDdang38, bIsFool94);
	}
	return tTempResultFactor.m_nResult;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
char CResultFactor::GetResultAnother(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94)
{
	if(RESULT_NONE==m_tResult.cAnother) return RESULT_NONE;
	char cAnother=m_tResult.cAnother;
	if(MADETYPE_NONE==nMadeType){
		if((RESULT_FOOL_NINE_FOUR==m_tResult.cAnother)||(RESULT_FOOL_NINE_FOUR_DDANG==m_tResult.cAnother)){
			if((FALSE==bIsDdang10)&&(FALSE==bIsGhangDdang138)&&(FALSE==bIsGhangDdang38)){
				cAnother=RESULT_FOOL_NINE_FOUR_DDANG;
			}
			else{
				cAnother=RESULT_NOJJOK;
			}
		}
		if((RESULT_NINE_FOUR==m_tResult.cAnother)||(RESULT_NINE_FOUR_JJOK==m_tResult.cAnother)){
			if((FALSE==bIsDdang19)&&(FALSE==bIsDdang10)&&(FALSE==bIsGhangDdang138)&&(FALSE==bIsGhangDdang38)&&(FALSE==bIsFool94)){
				cAnother=RESULT_NINE_FOUR_JJOK;
			}
			else{
				cAnother=RESULT_NOJJOK;
			}
		}
		if((RESULT_THREE_SEVEN==m_tResult.cAnother)||(RESULT_THREE_SEVEN_DDANG==m_tResult.cAnother)||(RESULT_THREE_SEVEN_DDANG10==m_tResult.cAnother)){
			if((RESULT_THREE_SEVEN_DDANG10==m_nRule)&&(TRUE==bIsDdang10)&&(FALSE==bIsGhangDdang138)&&(FALSE==bIsGhangDdang38)){
				cAnother=RESULT_THREE_SEVEN_DDANG10;
			}
			else if((TRUE==bIsDdang19)&&(FALSE==bIsDdang10)&&(FALSE==bIsGhangDdang138)&&(FALSE==bIsGhangDdang38)&&(FALSE==bIsFool94)){
				cAnother=RESULT_THREE_SEVEN_DDANG;
			}
			else{
				cAnother=RESULT_NOJJOK;
			}
		}
		if((RESULT_FOUR_SEVEN==m_tResult.cAnother)||(RESULT_FOUR_SEVEN_GHANGDDANG138==m_tResult.cAnother)){
			if((TRUE==bIsGhangDdang138)&&(FALSE==bIsGhangDdang38)){
				cAnother=RESULT_FOUR_SEVEN_GHANGDDANG138;
			}
			else{
				cAnother=RESULT_NOJJOK;
			}
		}
	}
	else if(MADETYPE_MADE==nMadeType){
		if(RESULT_FIND==m_tResult.cAnother){
			cAnother=RESULT_FIND;
		}
		else{
			cAnother=RESULT_NOJJOK;
		}
		//if((RESULT_FOOL_NINE_FOUR==m_tResult.cAnother)||(RESULT_FOOL_NINE_FOUR_DDANG==m_tResult.cAnother)){
		//	if((FALSE==bIsDdang10)&&(FALSE==bIsGhangDdang138)&&(FALSE==bIsGhangDdang38)){
		//		cAnother=RESULT_FOOL_NINE_FOUR_DDANG;
		//	}
		//	else{
		//		cAnother=RESULT_NOJJOK;
		//	}
		//}
		//if((RESULT_NINE_FOUR==m_tResult.cAnother)||(RESULT_NINE_FOUR_JJOK==m_tResult.cAnother)){
		//	if((FALSE==bIsDdang19)&&(FALSE==bIsDdang10)&&(FALSE==bIsGhangDdang138)&&(FALSE==bIsGhangDdang38)&&(FALSE==bIsFool94)){
		//		cAnother=RESULT_NINE_FOUR_JJOK;
		//	}
		//	else{
		//		cAnother=RESULT_NOJJOK;
		//	}
		//}
	}
	return cAnother;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
string CResultFactor::GetResultString(int nMadeType, bool bIsDdang19, bool bIsDdang10, bool bIsGhangDdang138, bool bIsGhangDdang38, bool bIsFool94)
{
	return GetString(nMadeType, GetResultAnother(nMadeType, bIsDdang19, bIsDdang10, bIsGhangDdang138, bIsGhangDdang38, bIsFool94), m_tResult.cOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultFactor::OverResultFactor(int nMadeType, char cAnother, char cOrder)
{
	if(RESULT_NONE==m_tResult.cOrder) return FALSE;
	if(MADETYPE_NONE==nMadeType){
		if((RESULT_FOOL_NINE_FOUR==m_tResult.cAnother)||(RESULT_FOOL_NINE_FOUR_DDANG==m_tResult.cAnother)){
			return (RESULT_9DDANG<=cOrder);
		}
		if((RESULT_NINE_FOUR==m_tResult.cAnother)||(RESULT_NINE_FOUR_JJOK==m_tResult.cAnother)){
			return (RESULT_ONE_TWO<=cOrder);
		}
		if((RESULT_THREE_SEVEN==m_tResult.cAnother)||(RESULT_THREE_SEVEN_DDANG==m_tResult.cAnother)||(RESULT_THREE_SEVEN_DDANG10==m_tResult.cAnother)){
			if(RESULT_THREE_SEVEN_DDANG10==m_nRule){
				return ((RESULT_10DDANG<cOrder)||(cOrder>m_tResult.cOrder));
			}
			return ((RESULT_10DDANG<=cOrder)||(cOrder>m_tResult.cOrder));
		}
		if((RESULT_FOUR_SEVEN==m_tResult.cAnother)||(RESULT_FOUR_SEVEN_GHANGDDANG138==m_tResult.cAnother)){
			return ((RESULT_18DDANG==cOrder)||(RESULT_13DDANG>=cOrder)||(cOrder>m_tResult.cOrder));
		}
	}
	else if(MADETYPE_MADE==nMadeType){
		//if((RESULT_FOOL_NINE_FOUR==m_tResult.cAnother)||(RESULT_FOOL_NINE_FOUR_DDANG==m_tResult.cAnother)){
		//	return (RESULT_9DDANG<=cOrder);
		//}
		//if((RESULT_NINE_FOUR==m_tResult.cAnother)||(RESULT_NINE_FOUR_JJOK==m_tResult.cAnother)){
		//	return (RESULT_ONE_TWO<=cOrder);
		//}
	}
	return (cOrder>m_tResult.cOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddResultOrderNoMadeToSelect(int nIndex, int nCard, int nSelect)
{
	if(FALSE==FindResultOrderNoMadeToSelect(nIndex, nCard, nSelect)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.AddResultCard(nCard);
		cResultFactor.SetResultFactorNoMadeToSelect(m_nMadeType, (short)nSelect, m_nFindOrder);
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddResultOrderNoMadeToArray(int nIndex, int nCard, int nArray1, int nArray2)
{
	if(FALSE==FindResultOrderNoMadeToArray(nIndex, nCard, nArray1, nArray2)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.AddResultCard(nCard);
		cResultFactor.SetResultFactorNoMadeToArray(m_nMadeType, nArray1, nArray2, m_nFindOrder);
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderNoMadeToSelect(int nIndex, vector<int> vCard, int nSelect, bool bHigh)
{
	if(FALSE==SetResultOrderNoMadeToSelect(nIndex, vCard, nSelect, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorNoMadeToSelect(m_nMadeType, (short)nSelect, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderNoMadeToArray(int nIndex, vector<int> vCard, int nArray1, int nArray2, bool bHigh)
{
	if(FALSE==SetResultOrderNoMadeToArray(nIndex, vCard, nArray1, nArray2, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorNoMadeToArray(m_nMadeType, nArray1, nArray2, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderNoMadeToSelect(int nIndex, vector<long> vCard, int nSelect, bool bHigh)
{
	if(FALSE==SetResultOrderNoMadeToSelect(nIndex, vCard, nSelect, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorNoMadeToSelect(m_nMadeType, (short)nSelect, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderNoMadeToArray(int nIndex, vector<long> vCard, int nArray1, int nArray2, bool bHigh)
{
	if(FALSE==SetResultOrderNoMadeToArray(nIndex, vCard, nArray1, nArray2, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorNoMadeToArray(m_nMadeType, nArray1, nArray2, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::FindResultOrderNoMadeToSelect(int nIndex, int nCard, int nSelect)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].AddResultCard(nCard);
	(*this)[nArray].SetResultFactorNoMadeToSelect(m_nMadeType, (short)nSelect, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nSelect].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::FindResultOrderNoMadeToArray(int nIndex, int nCard, int nArray1, int nArray2)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].AddResultCard(nCard);
	(*this)[nArray].SetResultFactorNoMadeToArray(m_nMadeType, nArray1, nArray2, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderNoMadeToSelect(int nIndex, vector<int> vCard, int nSelect, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorNoMadeToSelect(m_nMadeType, (short)nSelect, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nSelect].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderNoMadeToArray(int nIndex, vector<int> vCard, int nArray1, int nArray2, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorNoMadeToArray(m_nMadeType, nArray1, nArray2, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderNoMadeToSelect(int nIndex, vector<long> vCard, int nSelect, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorNoMadeToSelect(m_nMadeType, (short)nSelect, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nSelect].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderNoMadeToArray(int nIndex, vector<long> vCard, int nArray1, int nArray2, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorNoMadeToArray(m_nMadeType, nArray1, nArray2, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::ChangeFactorResultOrderNoMadeToSelect(int nIndex, int nSelect, int &nArray1, int &nArray2)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultFactorNoMadeToSelect(m_nMadeType, (short)nSelect, nArray1, nArray2, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::ChangeFactorResultOrderNoMadeToArray(int nIndex, int nArray1, int nArray2)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultFactorNoMadeToArray(m_nMadeType, nArray1, nArray2, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddResultOrderMadeToSelect(int nIndex, int nCard, int nMadeSelect)
{
	if(FALSE==FindResultOrderMadeToSelect(nIndex, nCard, nMadeSelect)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.AddResultCard(nCard);
		cResultFactor.SetResultFactorMadeToSelect(m_nMadeType, (short)nMadeSelect, m_nFindOrder);
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddResultOrderMadeToArray(int nIndex, int nCard, int nMadeArray1, int nMadeArray2, int nMadeArray3)
{
	if(FALSE==FindResultOrderMadeToArray(nIndex, nCard, nMadeArray1, nMadeArray2, nMadeArray3)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.AddResultCard(nCard);
		cResultFactor.SetResultFactorMadeToArray(m_nMadeType, nMadeArray1, nMadeArray2, nMadeArray3, m_nFindOrder);
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddResultOrderMadeToRemain(int nIndex, int nCard, int nArray1, int nArray2)
{
	if(FALSE==FindResultOrderMadeToRemain(nIndex, nCard, nArray1, nArray2)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.AddResultCard(nCard);
		cResultFactor.SetResultFactorMadeToRemain(m_nMadeType, nArray1, nArray2, m_nFindOrder);
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderMadeToSelect(int nIndex, vector<int> vCard, int nMadeSelect, bool bHigh)
{
	if(FALSE==SetResultOrderMadeToSelect(nIndex, vCard, nMadeSelect, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorMadeToSelect(m_nMadeType, (short)nMadeSelect, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderMadeToArray(int nIndex, vector<int> vCard, int nMadeArray1, int nMadeArray2, int nMadeArray3, bool bHigh)
{
	if(FALSE==SetResultOrderMadeToArray(nIndex, vCard, nMadeArray1, nMadeArray2, nMadeArray3, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorMadeToArray(m_nMadeType, nMadeArray1, nMadeArray2, nMadeArray3, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderMadeToRemain(int nIndex, vector<int> vCard, int nArray1, int nArray2, bool bHigh)
{
	if(FALSE==SetResultOrderMadeToRemain(nIndex, vCard, nArray1, nArray2, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorMadeToRemain(m_nMadeType, nArray1, nArray2, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderMadeToSelect(int nIndex, vector<long> vCard, int nMadeSelect, bool bHigh)
{
	if(FALSE==SetResultOrderMadeToSelect(nIndex, vCard, nMadeSelect, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorMadeToSelect(m_nMadeType, (short)nMadeSelect, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderMadeToArray(int nIndex, vector<long> vCard, int nMadeArray1, int nMadeArray2, int nMadeArray3, bool bHigh)
{
	if(FALSE==SetResultOrderMadeToArray(nIndex, vCard, nMadeArray1, nMadeArray2, nMadeArray3, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorMadeToArray(m_nMadeType, nMadeArray1, nMadeArray2, nMadeArray3, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddSetResultOrderMadeToRemain(int nIndex, vector<long> vCard, int nArray1, int nArray2, bool bHigh)
{
	if(FALSE==SetResultOrderMadeToRemain(nIndex, vCard, nArray1, nArray2, bHigh)){
		CResultFactor cResultFactor;
		cResultFactor.SetResultIndex(nIndex);
		cResultFactor.SetResultCard(vCard);
		if(TRUE==bHigh){
			cResultFactor.HighResultFactor(m_nMadeType, m_nFindOrder);
		}
		else{
			cResultFactor.SetResultFactorMadeToRemain(m_nMadeType, nArray1, nArray2, m_nFindOrder);
		}
		AddCheck(cResultFactor.m_tResult.cAnother, cResultFactor.m_nIndex);
		push_back(cResultFactor);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::FindResultOrderMadeToSelect(int nIndex, int nCard, int nMadeSelect)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].AddResultCard(nCard);
	(*this)[nArray].SetResultFactorMadeToSelect(m_nMadeType, (short)nMadeSelect, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::FindResultOrderMadeToArray(int nIndex, int nCard, int nMadeArray1, int nMadeArray2, int nMadeArray3)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].AddResultCard(nCard);
	(*this)[nArray].SetResultFactorMadeToArray(m_nMadeType, nMadeArray1, nMadeArray2, nMadeArray3, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::FindResultOrderMadeToRemain(int nIndex, int nCard, int nArray1, int nArray2)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].AddResultCard(nCard);
	(*this)[nArray].SetResultFactorMadeToRemain(m_nMadeType, nArray1, nArray2, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderMadeToSelect(int nIndex, vector<int> vCard, int nMadeSelect, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorMadeToSelect(m_nMadeType, (short)nMadeSelect, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderMadeToArray(int nIndex, vector<int> vCard, int nMadeArray1, int nMadeArray2, int nMadeArray3, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorMadeToArray(m_nMadeType, nMadeArray1, nMadeArray2, nMadeArray3, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderMadeToRemain(int nIndex, vector<int> vCard, int nArray1, int nArray2, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorMadeToRemain(m_nMadeType, nArray1, nArray2, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderMadeToSelect(int nIndex, vector<long> vCard, int nMadeSelect, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorMadeToSelect(m_nMadeType, (short)nMadeSelect, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderMadeToArray(int nIndex, vector<long> vCard, int nMadeArray1, int nMadeArray2, int nMadeArray3, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorMadeToArray(m_nMadeType, nMadeArray1, nMadeArray2, nMadeArray3, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::SetResultOrderMadeToRemain(int nIndex, vector<long> vCard, int nArray1, int nArray2, bool bHigh)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultCard(vCard);
	if(TRUE==bHigh){
		(*this)[nArray].HighResultFactor(m_nMadeType, m_nFindOrder);
	}
	else{
		(*this)[nArray].SetResultFactorMadeToRemain(m_nMadeType, nArray1, nArray2, m_nFindOrder);
	}
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::ChangeFactorResultOrderMadeToSelect(int nIndex, int nMadeSelect, int &nArray1, int &nArray2)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultFactorMadeToSelect(m_nMadeType, (short)nMadeSelect, nArray1, nArray2, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::ChangeFactorResultOrderMadeToArray(int nIndex, int nMadeArray1, int nMadeArray2, int nMadeArray3, int &nArray1, int &nArray2)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	(*this)[nArray].SetResultFactorMadeToArray(m_nMadeType, nMadeArray1, nMadeArray2, nMadeArray3, nArray1, nArray2, m_nFindOrder);
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::ChangeFactorResultOrderMadeToRemain(int nIndex, int &nMadeSelect, int nArray1, int nArray2)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	short sMadeSelect=0;
	(*this)[nArray].SetResultFactorMadeToRemain(m_nMadeType, sMadeSelect, nArray1, nArray2, m_nFindOrder);
	nMadeSelect=(int)sMadeSelect;
	AddCheck((*this)[nArray].m_tResult.cAnother, (*this)[nArray].m_nIndex);
	return TRUE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::ResultOrder(int nIndexTotal)
{
	char cMade=CResultFactor::RESULT_NOMADE;
	char cAnother=CResultFactor::RESULT_NONE;
	char cOrder=CResultFactor::RESULT_NONE;
	MakeResultOrder(nIndexTotal, cMade, cAnother, cOrder);
	if(TRUE==m_vtResultIndex.empty()){
		return FALSE;
	}
	switch(CResultFactor::IsAnother(m_nMadeType, cMade, cAnother)){
//	case CResultFactor::RESULT_NOMADE: return (CResultFactor::MADETYPE_MADE==m_nMadeType);
//	case CResultFactor::RESULT_FIND: return TRUE;
	case CResultFactor::RESULT_NINE_FOUR: return TRUE;
	case CResultFactor::RESULT_FOOL_NINE_FOUR: return TRUE;
	}
	return FALSE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultOrder::ResultOrderValue(int nIndexTotal)
{
	char cMade=CResultFactor::RESULT_NOMADE;
	char cAnother=CResultFactor::RESULT_NONE;
	char cOrder=CResultFactor::RESULT_NONE;
	MakeResultOrder(nIndexTotal, cMade, cAnother, cOrder);
	if(TRUE==m_vtResultIndex.empty()){
		return RESULT_NONE;
	}
	switch(CResultFactor::IsAnother(m_nMadeType, cMade, cAnother)){
	case CResultFactor::RESULT_NOMADE: return RESULT_REMATCH_NOMADE;
	case CResultFactor::RESULT_FIND: return RESULT_REMATCH_FIND;
	case CResultFactor::RESULT_NINE_FOUR: return RESULT_REMATCH_94;
	case CResultFactor::RESULT_FOOL_NINE_FOUR: return RESULT_REMATCH_FOOL94;
	}
	if(2<=m_vtResultIndex.size()){
		return RESULT_REMATCH_SAME;
	}
	return RESULT_ONLY;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultOrder::ResultOrderToResult(int nIndexTotal)
{
	char cMade=CResultFactor::RESULT_NOMADE;
	char cAnother=CResultFactor::RESULT_NONE;
	char cOrder=CResultFactor::RESULT_NONE;
	MakeResultOrder(nIndexTotal, cMade, cAnother, cOrder);
	if(TRUE==m_vtResultIndex.empty()){
		return RESULT_NONE;
	}
	switch(CResultFactor::IsAnother(m_nMadeType, cMade, cAnother)){
	case CResultFactor::RESULT_NOMADE: return RESULT_REMATCH_NOMADE;
	case CResultFactor::RESULT_FIND: return RESULT_REMATCH_FIND;
	case CResultFactor::RESULT_NINE_FOUR: return RESULT_REMATCH_94;
	case CResultFactor::RESULT_FOOL_NINE_FOUR: return RESULT_REMATCH_FOOL94;
	}
	if(2<=m_vtResultIndex.size()){
		return RESULT_REMATCH_SAME;
	}
	switch(FindCheck(m_vtResultIndex[0])){
	case CResultFactor::RESULT_GHANGDDANG38: return RESULT_ONLY_GHANGDDANG38;
	case CResultFactor::RESULT_GHANGDDANG138: return RESULT_ONLY_GHANGDDANG138;
	case CResultFactor::RESULT_DDAND10: return RESULT_ONLY_DDANG10;
	case CResultFactor::RESULT_DDAND19: return RESULT_ONLY_DDANG19;
	case CResultFactor::RESULT_FOOL_NINE_FOUR: return RESULT_REMATCH_FOOL94;
	case CResultFactor::RESULT_NONE: return RESULT_ONLY;
	}
	return RESULT_ONLY;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::MakeResultOrder(int nIndexTotal, char &cMade, char &cAnother, char &cOrder)
{
	m_vtResultIndex.clear();
	m_vtResult.clear();
	int nSize=(int)size();
	if(0==nSize) return;
	char cResultAnother=CResultFactor::RESULT_NONE;
	char cResultMade=CResultFactor::MADENUM_NONE;
	cMade=CResultFactor::MADENUM_NONE;
	cAnother=CResultFactor::RESULT_NONE;
	cOrder=CResultFactor::RESULT_NONE;
	m_vtResult.resize(nIndexTotal);
	for(int i=0; i<nSize; i++){
		if((0>(*this)[i].m_nIndex)||(nIndexTotal<=(*this)[i].m_nIndex)) continue;
		m_vtResult[(*this)[i].m_nIndex]=(*this)[i].m_nResult;
		if(CResultFactor::MADETYPE_MADE==m_nMadeType){
			cResultMade=(*this)[i].m_tResult.cMade;
			if(cMade<=cResultMade){
				if(CResultFactor::MADENUM_NONE==cResultMade){
					cMade=CResultFactor::RESULT_NOMADE;
					m_vtResultIndex.push_back((*this)[i].m_nIndex);
				}
				else if(CResultFactor::MADENUM_NONE<cResultMade){
					cMade=CResultFactor::RESULT_MADE;
					cResultAnother=(char)(*this)[i].GetResultAnother(m_nMadeType, !m_vDDang19.empty(), !m_vDDang10.empty(), !m_vGhangDDang138.empty(), !m_vGhangDDang38.empty(), !m_vFool94.empty());
					if(cAnother<cResultAnother){
						cAnother=cResultAnother;
						cOrder=(*this)[i].m_tResult.cOrder;
						m_vtResultIndex.clear();
						m_vtResultIndex.push_back((*this)[i].m_nIndex);
					}
					else if(cAnother==cResultAnother){
						if(cOrder<(*this)[i].m_tResult.cOrder){
							cOrder=(*this)[i].m_tResult.cOrder;
							m_vtResultIndex.clear();
							m_vtResultIndex.push_back((*this)[i].m_nIndex);
						}
						else if(cOrder==(*this)[i].m_tResult.cOrder){
							m_vtResultIndex.push_back((*this)[i].m_nIndex);
						}
					}
				}
			}
		}
		else if(CResultFactor::MADETYPE_NOANOTHER==m_nMadeType){
			if(cOrder<(*this)[i].m_tResult.cOrder){
				cOrder=(*this)[i].m_tResult.cOrder;
				m_vtResultIndex.clear();
				m_vtResultIndex.push_back((*this)[i].m_nIndex);
			}
			else if(cOrder==(*this)[i].m_tResult.cOrder){
				m_vtResultIndex.push_back((*this)[i].m_nIndex);
			}
		}
		else{
			cResultAnother=(char)(*this)[i].GetResultAnother(m_nMadeType, !m_vDDang19.empty(), !m_vDDang10.empty(), !m_vGhangDDang138.empty(), !m_vGhangDDang38.empty(), !m_vFool94.empty());
			if(cAnother<cResultAnother){
				cAnother=cResultAnother;
				cOrder=(*this)[i].m_tResult.cOrder;
				m_vtResultIndex.clear();
				m_vtResultIndex.push_back((*this)[i].m_nIndex);
			}
			else if(cAnother==cResultAnother){
				if(cOrder<(*this)[i].m_tResult.cOrder){
					cOrder=(*this)[i].m_tResult.cOrder;
					m_vtResultIndex.clear();
					m_vtResultIndex.push_back((*this)[i].m_nIndex);
				}
				else if(cOrder==(*this)[i].m_tResult.cOrder){
					m_vtResultIndex.push_back((*this)[i].m_nIndex);
				}
			}
		}
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultOrder::MaxMadeResultOrder(void)
{
	int nSize=(int)size();
	int nCount=0;
	for(int i=0; i<nSize; i++){
		if(nCount<(*this)[i].GetMadeCount()){
			nCount=(*this)[i].GetMadeCount();
		}
	}
	return nCount;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultOrder::FindIndexToArrayResultOrder(int nIndex)
{
	int nSize=(int)size();
	for(int i=0; i<nSize; i++){
		if((*this)[i].m_nIndex==nIndex){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::FindIndexToArrayResultOrder(int nIndex, int &nArray)
{
	int nSize=(int)size();
	for(int i=0; i<nSize; i++){
		if((*this)[i].m_nIndex==nIndex){
			nArray=i;
			return TRUE;
		}
	}
	return FALSE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::IsResultFactor(int nIndex, char cOrder)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return FALSE;
	return (*this)[nArray].IsResultFactor(m_nMadeType, cOrder);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::SwapResultOrder(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return;
	if(FALSE==IsUsableArray(nArray1)) return;
	if(FALSE==IsUsableArray(nArray2)) return;
	CResultFactor cResultFactor;
	cResultFactor.SetResultFactor(&(*this)[nArray1]);
	(*this)[nArray1].SetResultFactor(&(*this)[nArray2]);
	(*this)[nArray2].SetResultFactor(&cResultFactor);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::DelResultOrder(int nIndex)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return;
	DelCheck((*this)[nArray].m_nIndex);
	erase(this->begin() + nArray);
	//erase(&(*this)[nArray]);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::ClearResultOrder(int nIndex)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return;
	DelCheck((*this)[nArray].m_nIndex);
	(*this)[nArray].ClearResultFactor();
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::HighResultOrder(int nIndex)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return;
	(*this)[nArray].HighResultFactor(m_nMadeType);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::SetResultOrder(void)
{
	ClearCheck();
	int nSize=(int)size();
	for(int i=0; i<nSize; i++){
		AddCheck((*this)[i].m_tResult.cAnother, (*this)[i].m_nIndex);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
CResultFactor* CResultOrder::GetResultOrder(int nIndex)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return NULL;
	return &(*this)[nArray];
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultOrder::GetResultOrder(int nIndex, CResultFactor** ppcResultFactor)
{
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return -1;
	if(NULL!=ppcResultFactor){
		(*ppcResultFactor)=&(*this)[nArray];
	}
	return (*this)[nArray].GetResultFactor(m_nMadeType, !m_vDDang19.empty(), !m_vDDang10.empty(), !m_vGhangDDang138.empty(), !m_vGhangDDang38.empty(), !m_vFool94.empty());
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int CResultOrder::GetResultOrderArray(int nArray, CResultFactor** ppcResultFactor)
{
	if(FALSE==IsUsableArray(nArray)) return -1;
	if(NULL!=ppcResultFactor){
		(*ppcResultFactor)=&(*this)[nArray];
	}
	return (*this)[nArray].GetResultFactor(m_nMadeType, !m_vDDang19.empty(), !m_vDDang10.empty(), !m_vGhangDDang138.empty(), !m_vGhangDDang38.empty(), !m_vFool94.empty());
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
string CResultOrder::GetResultOrderString(int nIndex)
{
	string str;
	int nArray=0;
	if(FALSE==FindIndexToArrayResultOrder(nIndex, nArray)) return str;
	str=(*this)[nArray].GetResultString(m_nMadeType, !m_vDDang19.empty(), !m_vDDang10.empty(), !m_vGhangDDang138.empty(), !m_vGhangDDang38.empty(), !m_vFool94.empty());
	return str;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::AddCheck(char cAnother, int nIndex)
{
	vector<int>::iterator Find;
	DelCheck(nIndex);
	switch(cAnother)
	{
	case CResultFactor::RESULT_DDAND19:
		{
			Find=find(m_vDDang19.begin(), m_vDDang19.end(), nIndex);
			if(m_vDDang19.end()==Find){
				m_vDDang19.push_back(nIndex);
			}
		}
		break;
	case CResultFactor::RESULT_DDAND10:
		{
			Find=find(m_vDDang10.begin(), m_vDDang10.end(), nIndex);
			if(m_vDDang10.end()==Find){
				m_vDDang10.push_back(nIndex);
			}
		}
		break;
	case CResultFactor::RESULT_GHANGDDANG138:
		{
			Find=find(m_vGhangDDang138.begin(), m_vGhangDDang138.end(), nIndex);
			if(m_vGhangDDang138.end()==Find){
				m_vGhangDDang138.push_back(nIndex);
			}
		}
		break;
	case CResultFactor::RESULT_GHANGDDANG38:
		{
			Find=find(m_vGhangDDang38.begin(), m_vGhangDDang38.end(), nIndex);
			if(m_vGhangDDang38.end()==Find){
				m_vGhangDDang38.push_back(nIndex);
			}
		}
		break;
	case CResultFactor::RESULT_FOOL_NINE_FOUR_DDANG:
	case CResultFactor::RESULT_FOOL_NINE_FOUR:
		{
			Find=find(m_vFool94.begin(), m_vFool94.end(), nIndex);
			if(m_vFool94.end()==Find){
				m_vFool94.push_back(nIndex);
			}
		}
		break;
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::DelCheck(char cAnother, int nIndex)
{
	vector<int>::iterator Find;
	switch(cAnother)
	{
	case CResultFactor::RESULT_DDAND19:
		{
			Find=find(m_vDDang19.begin(), m_vDDang19.end(), nIndex);
			if(m_vDDang19.end()!=Find){
				m_vDDang19.erase(Find);
			}
		}
		break;
	case CResultFactor::RESULT_DDAND10:
		{
			Find=find(m_vDDang10.begin(), m_vDDang10.end(), nIndex);
			if(m_vDDang10.end()!=Find){
				m_vDDang10.erase(Find);
			}
		}
		break;
	case CResultFactor::RESULT_GHANGDDANG138:
		{
			Find=find(m_vGhangDDang138.begin(), m_vGhangDDang138.end(), nIndex);
			if(m_vGhangDDang138.end()!=Find){
				m_vGhangDDang138.erase(Find);
			}
		}
		break;
	case CResultFactor::RESULT_GHANGDDANG38:
		{
			Find=find(m_vGhangDDang38.begin(), m_vGhangDDang38.end(), nIndex);
			if(m_vGhangDDang38.end()!=Find){
				m_vGhangDDang38.erase(Find);
			}
		}
		break;
	case CResultFactor::RESULT_FOOL_NINE_FOUR_DDANG:
	case CResultFactor::RESULT_FOOL_NINE_FOUR:
		{
			Find=find(m_vFool94.begin(), m_vFool94.end(), nIndex);
			if(m_vFool94.end()!=Find){
				m_vFool94.erase(Find);
			}
		}
		break;
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::DelCheck(int nIndex)
{
	vector<int>::iterator Find;
	Find=find(m_vDDang19.begin(), m_vDDang19.end(), nIndex);
	if(m_vDDang19.end()!=Find){
		m_vDDang19.erase(Find);
	}
	Find=find(m_vDDang10.begin(), m_vDDang10.end(), nIndex);
	if(m_vDDang10.end()!=Find){
		m_vDDang10.erase(Find);
	}
	Find=find(m_vGhangDDang138.begin(), m_vGhangDDang138.end(), nIndex);
	if(m_vGhangDDang138.end()!=Find){
		m_vGhangDDang138.erase(Find);
	}
	Find=find(m_vGhangDDang38.begin(), m_vGhangDDang38.end(), nIndex);
	if(m_vGhangDDang38.end()!=Find){
		m_vGhangDDang38.erase(Find);
	}
	Find=find(m_vFool94.begin(), m_vFool94.end(), nIndex);
	if(m_vFool94.end()!=Find){
		m_vFool94.erase(Find);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
char CResultOrder::FindCheck(int nIndex)
{
	vector<int>::iterator Find;
	Find=find(m_vGhangDDang38.begin(), m_vGhangDDang38.end(), nIndex);
	if(m_vGhangDDang38.end()!=Find){
		return CResultFactor::RESULT_GHANGDDANG38;
	}
	Find=find(m_vGhangDDang138.begin(), m_vGhangDDang138.end(), nIndex);
	if(m_vGhangDDang138.end()!=Find){
		return CResultFactor::RESULT_GHANGDDANG138;
	}
	Find=find(m_vDDang10.begin(), m_vDDang10.end(), nIndex);
	if(m_vDDang10.end()!=Find){
		return CResultFactor::RESULT_DDAND10;
	}
	Find=find(m_vDDang19.begin(), m_vDDang19.end(), nIndex);
	if(m_vDDang19.end()!=Find){
		return CResultFactor::RESULT_DDAND19;
	}
	Find=find(m_vFool94.begin(), m_vFool94.end(), nIndex);
	if(m_vFool94.end()!=Find){
		return CResultFactor::RESULT_FOOL_NINE_FOUR;
	}
	return CResultFactor::RESULT_NONE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
bool CResultOrder::FindCheck(char cAnother, int nIndex)
{
	vector<int>::iterator Find;
	switch(cAnother)
	{
	case CResultFactor::RESULT_DDAND19:
		{
			Find=find(m_vDDang19.begin(), m_vDDang19.end(), nIndex);
			if(m_vDDang19.end()!=Find){
				return TRUE;
			}
		}
		break;
	case CResultFactor::RESULT_DDAND10:
		{
			Find=find(m_vDDang10.begin(), m_vDDang10.end(), nIndex);
			if(m_vDDang10.end()!=Find){
				return TRUE;
			}
		}
		break;
	case CResultFactor::RESULT_GHANGDDANG138:
		{
			Find=find(m_vGhangDDang138.begin(), m_vGhangDDang138.end(), nIndex);
			if(m_vGhangDDang138.end()!=Find){
				return TRUE;
			}
		}
		break;
	case CResultFactor::RESULT_GHANGDDANG38:
		{
			Find=find(m_vGhangDDang38.begin(), m_vGhangDDang38.end(), nIndex);
			if(m_vGhangDDang38.end()!=Find){
				return TRUE;
			}
		}
		break;
	case CResultFactor::RESULT_FOOL_NINE_FOUR_DDANG:
	case CResultFactor::RESULT_FOOL_NINE_FOUR:
		{
			Find=find(m_vFool94.begin(), m_vFool94.end(), nIndex);
			if(m_vFool94.end()!=Find){
				return TRUE;
			}
		}
		break;
	}
	return FALSE;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::ClearCheck(void)
{
	m_vDDang19.clear();
	m_vDDang10.clear();
	m_vGhangDDang138.clear();
	m_vGhangDDang38.clear();
	m_vFool94.clear();
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::Sort_Index(bool bAscOrDes)
{
	if(TRUE==bAscOrDes){
		Sort_Ascend(0, ((int)GetResultOrderTotal()-1), this, Index, Swap);
	}
	else{
		Sort_Descend(0, ((int)GetResultOrderTotal()-1), this, Index, Swap);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::Sort_Made(bool bAscOrDes)
{
	if(TRUE==bAscOrDes){
		Sort_Ascend(0, ((int)GetResultOrderTotal()-1), this, Made, Swap);
	}
	else{
		Sort_Descend(0, ((int)GetResultOrderTotal()-1), this, Made, Swap);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::Sort_Another(bool bAscOrDes)
{
	if(TRUE==bAscOrDes){
		Sort_Ascend(0, ((int)GetResultOrderTotal()-1), this, Another, Swap);
	}
	else{
		Sort_Descend(0, ((int)GetResultOrderTotal()-1), this, Another, Swap);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::Sort_Order(bool bAscOrDes)
{
	if(TRUE==bAscOrDes){
		Sort_Ascend(0, ((int)GetResultOrderTotal()-1), this, Order, Swap);
	}
	else{
		Sort_Descend(0, ((int)GetResultOrderTotal()-1), this, Order, Swap);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CResultOrder::Sort_MadeOrderAndAnother(bool bAscOrDes)
{
	if(TRUE==bAscOrDes){
		Sort_Ascend(0, ((int)GetResultOrderTotal()-1), this, MadeOrderAndAnother, Swap);
	}
	else{
		Sort_Descend(0, ((int)GetResultOrderTotal()-1), this, MadeOrderAndAnother, Swap);
	}
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void Swap(void* pVoid, int nArray1, int nArray2)
{
	CResultOrder* pcResultOrder=(CResultOrder*)(pVoid);
	if(NULL==pcResultOrder) return;
	pcResultOrder->SwapResultOrder(nArray1, nArray2);
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int Index(void* pVoid, int nArray)
{
	CResultOrder* pcResultOrder=(CResultOrder*)(pVoid);
	if(NULL==pcResultOrder) return -1;
	CResultFactor* pcResultFactor=NULL;
	if(-1!=pcResultOrder->GetResultOrderArray(nArray, &pcResultFactor)){
		return pcResultFactor->m_nIndex;
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int Made(void* pVoid, int nArray)
{
	CResultOrder* pcResultOrder=(CResultOrder*)(pVoid);
	if(NULL==pcResultOrder) return -1;
	CResultFactor* pcResultFactor=NULL;
	if(-1!=pcResultOrder->GetResultOrderArray(nArray, &pcResultFactor)){
		return pcResultFactor->m_tResult.cMade;
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int Another(void* pVoid, int nArray)
{
	CResultOrder* pcResultOrder=(CResultOrder*)(pVoid);
	if(NULL==pcResultOrder) return -1;
	CResultFactor* pcResultFactor=NULL;
	if(-1!=pcResultOrder->GetResultOrderArray(nArray, &pcResultFactor)){
		return pcResultFactor->m_tResult.cAnother;
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int Order(void* pVoid, int nArray)
{
	CResultOrder* pcResultOrder=(CResultOrder*)(pVoid);
	if(NULL==pcResultOrder) return -1;
	CResultFactor* pcResultFactor=NULL;
	if(-1!=pcResultOrder->GetResultOrderArray(nArray, &pcResultFactor)){
		return pcResultFactor->m_tResult.cOrder;
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
int MadeOrderAndAnother(void* pVoid, int nArray)
{
	CResultOrder* pcResultOrder=(CResultOrder*)(pVoid);
	if(NULL==pcResultOrder) return -1;
	CResultFactor* pcResultFactor=NULL;
	if(-1!=pcResultOrder->GetResultOrderArray(nArray, &pcResultFactor)){
		return pcResultFactor->GetResultFactor(pcResultOrder->m_nMadeType, !pcResultOrder->m_vDDang19.empty(), !pcResultOrder->m_vDDang10.empty(), !pcResultOrder->m_vGhangDDang138.empty(), !pcResultOrder->m_vGhangDDang38.empty(), !pcResultOrder->m_vFool94.empty());
	}
	return -1;
}
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
//------------------------------------------------------------------//
//
//------------------------------------------------------------------//
void CPosInfo::SetPosInfo_LineCol(RECT rArea, POINT pDiff, int nLineCol, ...)
{
	m_rArea=rArea;
	m_pPos.x=m_rArea.left;
	m_pPos.y=m_rArea.top;
	m_pDiff=pDiff;
	int IntValue=0;
	va_list vl;
	va_start(vl, nLineCol);
	IntValue=nLineCol;
	while(-1!=IntValue){
		m_vLineCol.push_back(IntValue);
		IntValue=va_arg(vl, int);
	}
	va_end(vl);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
int CPosInfo::StringToInsertType(string str)
{
	int InsertType=InsertType_None;
	if(str=="InsertType_DiffToLeftRight"){ InsertType=InsertType_DiffToLeftRight; }
	if(str=="InsertType_DiffToTopBottom"){ InsertType=InsertType_DiffToTopBottom; }
	if(str=="InsertType_DiffToBoth"){ InsertType=InsertType_DiffToBoth; }
	if(str=="InsertType_AreaToCutLeftRight"){ InsertType=InsertType_AreaToCutLeftRight; }
	if(str=="InsertType_AreaToCutTopBottom"){ InsertType=InsertType_AreaToCutTopBottom; }
	if(str=="InsertType_AreaToCutBoth"){ InsertType=InsertType_AreaToCutBoth; } 
	if(str=="InsertType_AreaFillToLeftRight"){ InsertType=InsertType_AreaFillToLeftRight; }
	if(str=="InsertType_AreaFillToTopBottom"){ InsertType=InsertType_AreaFillToTopBottom; }
	if(str=="InsertType_AreaFillToBoth"){ InsertType=InsertType_AreaFillToBoth; } 
	if(str=="InsertType_LineCol"){ InsertType=InsertType_LineCol; }
	return InsertType;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
string CPosInfo::InsertTypeToString(int InsertType)
{
	string str;
	switch(InsertType){
	case InsertType_None: { str="InsertType_None"; }break;
	case InsertType_DiffToLeftRight: { str="InsertType_DiffToLeftRight"; }break;
	case InsertType_DiffToTopBottom: { str="InsertType_DiffToTopBottom"; }break;
	case InsertType_DiffToBoth: { str="InsertType_DiffToBoth"; }break;
	case InsertType_AreaToCutLeftRight: { str="InsertType_AreaToCutLeftRight"; }break;
	case InsertType_AreaToCutTopBottom: { str="InsertType_AreaToCutTopBottom"; }break;
	case InsertType_AreaToCutBoth: { str="InsertType_AreaToCutBoth"; }break;
	case InsertType_AreaFillToLeftRight: { str="InsertType_AreaFillToLeftRight"; }break;
	case InsertType_AreaFillToTopBottom: { str="InsertType_AreaFillToTopBottom"; }break;
	case InsertType_AreaFillToBoth: { str="InsertType_AreaFillToBoth"; }break;
	case InsertType_LineCol: { str="InsertType_LineCol"; }break;
	}
	return str; 
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos(int nArray, int nPosCount, int nTotal, SIZE Size, bool bFindLow)
{
	POINT pPos=m_pPos;
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToLeftRight)){ pPos=FindPos_DiffToLeftRight(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToTopBottom)){ pPos=FindPos_DiffToTopBottom(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToBoth)){ pPos=FindPos_DiffToBoth(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutLeftRight)){ pPos=FindPos_AreaToCutLeftRight(pPos, nArray, nTotal, Size); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutTopBottom)){ pPos=FindPos_AreaToCutTopBottom(pPos, nArray, nTotal, Size); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutBoth)){ pPos=FindPos_AreaToCutBoth(pPos, nArray, nTotal, Size); } 
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToLeftRight)){ pPos=FindPos_AreaFillToLeftRight(pPos, nArray, nTotal, Size); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToTopBottom)){ pPos=FindPos_AreaFillToTopBottom(pPos, nArray, nTotal, Size); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToBoth)){ pPos=FindPos_AreaFillToBoth(pPos, nArray, nTotal, Size); } 
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_LineCol)){ pPos=FindPos_LineCol(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_PointList)){ pPos=FindPos_PointList(pPos, nArray); }

	if(TRUE==bFindLow){
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToLeftRight)){ pPos=FindPos_DiffToLeftRight(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToTopBottom)){ pPos=FindPos_DiffToTopBottom(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToBoth)){ pPos=FindPos_DiffToBoth(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutLeftRight)){ pPos=FindPos_AreaToCutLeftRight(pPos, nPosCount, nTotal, Size); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutTopBottom)){ pPos=FindPos_AreaToCutTopBottom(pPos, nPosCount, nTotal, Size); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutBoth)){ pPos=FindPos_AreaToCutBoth(pPos, nPosCount, nTotal, Size); } 
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToLeftRight)){ pPos=FindPos_AreaFillToLeftRight(pPos, nPosCount, nTotal, Size); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToTopBottom)){ pPos=FindPos_AreaFillToTopBottom(pPos, nPosCount, nTotal, Size); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToBoth)){ pPos=FindPos_AreaFillToBoth(pPos, nPosCount, nTotal, Size); } 
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_LineCol)){ pPos=FindPos_LineCol(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_PointList)){ pPos=FindPos_PointList(pPos, nPosCount); }
	}
	return pPos;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos(int nArray, int nPosCount, int nTotal, int cx, int cy, bool bFindLow)
{
	POINT pPos=m_pPos;
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToLeftRight)){ pPos=FindPos_DiffToLeftRight(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToTopBottom)){ pPos=FindPos_DiffToTopBottom(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToBoth)){ pPos=FindPos_DiffToBoth(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutLeftRight)){ pPos=FindPos_AreaToCutLeftRight(pPos, nArray, nTotal, cx, cy); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutTopBottom)){ pPos=FindPos_AreaToCutTopBottom(pPos, nArray, nTotal, cx, cy); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutBoth)){ pPos=FindPos_AreaToCutBoth(pPos, nArray, nTotal, cx, cy); } 
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToLeftRight)){ pPos=FindPos_AreaFillToLeftRight(pPos, nArray, nTotal, cx, cy); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToTopBottom)){ pPos=FindPos_AreaFillToTopBottom(pPos, nArray, nTotal, cx, cy); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToBoth)){ pPos=FindPos_AreaFillToBoth(pPos, nArray, nTotal, cx, cy); } 
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_LineCol)){ pPos=FindPos_LineCol(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_PointList)){ pPos=FindPos_PointList(pPos, nArray); }

	if(TRUE==bFindLow){
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToLeftRight)){ pPos=FindPos_DiffToLeftRight(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToTopBottom)){ pPos=FindPos_DiffToTopBottom(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToBoth)){ pPos=FindPos_DiffToBoth(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutLeftRight)){ pPos=FindPos_AreaToCutLeftRight(pPos, nPosCount, nTotal, cx, cy); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutTopBottom)){ pPos=FindPos_AreaToCutTopBottom(pPos, nPosCount, nTotal, cx, cy); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutBoth)){ pPos=FindPos_AreaToCutBoth(pPos, nPosCount, nTotal, cx, cy); } 
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToLeftRight)){ pPos=FindPos_AreaFillToLeftRight(pPos, nPosCount, nTotal, cx, cy); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToTopBottom)){ pPos=FindPos_AreaFillToTopBottom(pPos, nPosCount, nTotal, cx, cy); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToBoth)){ pPos=FindPos_AreaFillToBoth(pPos, nPosCount, nTotal, cx, cy); } 
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_LineCol)){ pPos=FindPos_LineCol(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_PointList)){ pPos=FindPos_PointList(pPos, nPosCount); }
	}
	return pPos;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos(int nArray, int nPosCount, int nTotal, bool bFindLow)
{
	POINT pPos=m_pPos;
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToLeftRight)){ pPos=FindPos_DiffToLeftRight(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToTopBottom)){ pPos=FindPos_DiffToTopBottom(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_DiffToBoth)){ pPos=FindPos_DiffToBoth(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutLeftRight)){ pPos=FindPos_AreaToCutLeftRight(pPos, nArray, nTotal); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutTopBottom)){ pPos=FindPos_AreaToCutTopBottom(pPos, nArray, nTotal); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaToCutBoth)){ pPos=FindPos_AreaToCutBoth(pPos, nArray, nTotal); } 
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToLeftRight)){ pPos=FindPos_AreaFillToLeftRight(pPos, nArray, nTotal); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToTopBottom)){ pPos=FindPos_AreaFillToTopBottom(pPos, nArray, nTotal); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_AreaFillToBoth)){ pPos=FindPos_AreaFillToBoth(pPos, nArray, nTotal); } 
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_LineCol)){ pPos=FindPos_LineCol(pPos, nArray); }
	if(TRUE==IsAndBITS(m_tInsertType.High, InsertType_PointList)){ pPos=FindPos_PointList(pPos, nArray); }

	if(TRUE==bFindLow){
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToLeftRight)){ pPos=FindPos_DiffToLeftRight(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToTopBottom)){ pPos=FindPos_DiffToTopBottom(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_DiffToBoth)){ pPos=FindPos_DiffToBoth(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutLeftRight)){ pPos=FindPos_AreaToCutLeftRight(pPos, nPosCount, nTotal); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutTopBottom)){ pPos=FindPos_AreaToCutTopBottom(pPos, nPosCount, nTotal); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaToCutBoth)){ pPos=FindPos_AreaToCutBoth(pPos, nPosCount, nTotal); } 
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToLeftRight)){ pPos=FindPos_AreaFillToLeftRight(pPos, nPosCount, nTotal); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToTopBottom)){ pPos=FindPos_AreaFillToTopBottom(pPos, nPosCount, nTotal); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_AreaFillToBoth)){ pPos=FindPos_AreaFillToBoth(pPos, nPosCount, nTotal); } 
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_LineCol)){ pPos=FindPos_LineCol(pPos, nPosCount); }
		if(TRUE==IsAndBITS(m_tInsertType.Low, InsertType_PointList)){ pPos=FindPos_PointList(pPos, nPosCount); }
	}
	return pPos;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_DiffToLeftRight(POINT pPos, int nArray)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	Point.x=pPos.x+m_pDiff.x*nArray;
	Point.y=pPos.y;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_DiffToTopBottom(POINT pPos, int nArray)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	Point.x=pPos.x;
	Point.y=pPos.y+m_pDiff.y*nArray;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_DiffToBoth(POINT pPos, int nArray)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	Point.x=pPos.x+m_pDiff.x*nArray;
	Point.y=pPos.y+m_pDiff.y*nArray;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal, SIZE Size)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-Size.cx)*nArray)/nTotal;
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal, SIZE Size)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nHeight=((m_rArea.bottom-m_rArea.top-Size.cy)*nArray)/nTotal;
	Point.x=pPos.x;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal, SIZE Size)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-Size.cx)*nArray)/nTotal;
	int nHeight=((m_rArea.bottom-m_rArea.top-Size.cy)*nArray)/nTotal;
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal, int cx, int cy)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-cx)*nArray)/nTotal;
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal, int cx, int cy)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nHeight=((m_rArea.bottom-m_rArea.top-cy)*nArray)/nTotal;
	Point.x=pPos.x;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal, int cx, int cy)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-cx)*nArray)/nTotal;
	int nHeight=((m_rArea.bottom-m_rArea.top-cy)*nArray)/nTotal;
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutLeftRight(POINT pPos, int nArray, int nTotal)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left)*nArray)/nTotal;
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutTopBottom(POINT pPos, int nArray, int nTotal)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nHeight=((m_rArea.bottom-m_rArea.top)*nArray)/nTotal;
	Point.x=pPos.x;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaToCutBoth(POINT pPos, int nArray, int nTotal)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(0==nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left)*nArray)/nTotal;
	int nHeight=((m_rArea.bottom-m_rArea.top)*nArray)/nTotal;
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal, SIZE Size)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-Size.cx)*nArray)/(nTotal-1);
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal, SIZE Size)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nHeight=((m_rArea.bottom-m_rArea.top-Size.cy)*nArray)/(nTotal-1);
	Point.x=pPos.x;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal, SIZE Size)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-Size.cx)*nArray)/(nTotal-1);
	int nHeight=((m_rArea.bottom-m_rArea.top-Size.cy)*nArray)/(nTotal-1);
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal, int cx, int cy)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-cx)*nArray)/(nTotal-1);
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal, int cx, int cy)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nHeight=((m_rArea.bottom-m_rArea.top-cy)*nArray)/(nTotal-1);
	Point.x=pPos.x;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal, int cx, int cy)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left-cx)*nArray)/(nTotal-1);
	int nHeight=((m_rArea.bottom-m_rArea.top-cy)*nArray)/(nTotal-1);
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToLeftRight(POINT pPos, int nArray, int nTotal)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left)*nArray)/(nTotal-1);
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToTopBottom(POINT pPos, int nArray, int nTotal)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nHeight=((m_rArea.bottom-m_rArea.top)*nArray)/(nTotal-1);
	Point.x=pPos.x;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_AreaFillToBoth(POINT pPos, int nArray, int nTotal)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	if(1>=nTotal) return pPos;
	int nWidth=((m_rArea.right-m_rArea.left)*nArray)/(nTotal-1);
	int nHeight=((m_rArea.bottom-m_rArea.top)*nArray)/(nTotal-1);
	Point.x=pPos.x+nWidth;
	Point.y=pPos.y+nHeight;
	return Point;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_LineCol(POINT pPos, int nArray)
{
	POINT Point;
	Point.x=0;
	Point.y=0;
	int nTotal=(int)m_vLineCol.size();
	int nTempPosCount=nArray;
	int nOldCount=0;
	int nCurCount=0;
	int nCount=0;
	int nWidth=m_rArea.right-m_rArea.left;
	int nHeight=m_rArea.bottom-m_rArea.top;
	for(int i=0; i<nTotal; i++){
		nCurCount=m_vLineCol[i];
		if(0!=nOldCount){
			nCount+=nCurCount-nOldCount;
		}
		if(nCurCount<=nTempPosCount){
			nTempPosCount-=nCurCount;
			nOldCount=nCurCount;
		}
		else{
			Point.x=pPos.x+nWidth*nTempPosCount-(nWidth/2)*nCount;
			Point.y=pPos.y+nHeight*i;
			return Point;
		}
	}
	return pPos;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
POINT CPosInfo::FindPos_PointList(POINT pPos, int nArray)
{
	POINT pPoint={0,};
	if(FALSE==GetPointList(nArray, pPoint)) return pPos;
	pPos.x=pPoint.x;
	pPos.y=pPoint.y;
	return pPos;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//

bool CBetLog::SetBetLogReceive(int nBetIdenty, int nIdenty, int nBetTurn, int nBet, vector<CLineCol>* pvtSelectLine)
{
	string str;
	int nBetPos=FindBeginVector(nBetIdenty);
	if(FALSE==GetBetLog(nIdenty, str)) return FALSE;
	if(TRUE==str.empty()) str.resize(BET_STRING, '-');
	switch(nBetTurn){
	case BET_TURN_NONE:
		{
			str.clear();
			str.resize(BET_STRING, '-');
			basic_string <char>::reference str_char=str.at(0);
			int nBetPos=FindBeginVector(nIdenty);
			if(NULL!=str_char){
				str_char=GetBetOrder(nBetPos);
			}
		}
		break;
	case BET_TURN_LIVE_1:
		{
			basic_string <char>::reference str_char=str.at(0);
			if(NULL!=str_char){
				str_char=GetBetChar(nBet);
			}
		}
		break;
	case BET_TURN_LIVE_2:
		{
			basic_string <char>::reference str_char=str.at(1);
			if(NULL!=str_char){
				str_char=GetBetChar(nBet);
			}
		}
		break;
	case BET_TURN_REST_1:
	case BET_TURN_REMATCH_REST_1:
		{
			basic_string <char>::reference str_char=str.at(2+nBetPos);
			if(NULL!=str_char){
				str_char=GetBetChar(nBet);
			}
		}
		break;
	case BET_TURN_REST_2:
	case BET_TURN_REMATCH_REST_2:
		{
			basic_string <char>::reference str_char=str.at(2+5+nBetPos);
			if(NULL!=str_char){
				str_char=GetBetChar(nBet);
			}
		}
		break;
	case BET_TURN_REST_3:
	case BET_TURN_REMATCH_REST_3:
		{
			basic_string <char>::reference str_char=str.at(2+10+nBetPos);
			if(NULL!=str_char){
				str_char=GetBetChar(nBet);
			}
		}
		break;
	case BET_TURN_LINE:
		{
			if(NULL!=pvtSelectLine){
				int nSize=pvtSelectLine->size();
				for(int i=0; i<nSize; i++){
					basic_string <char>::reference str_char=str.at(i);
					if(NULL!=str_char){
						char Buffer[10]={0,};
						if(CLineCol::COL_MOL==(*pvtSelectLine)[i].m_lCol){
							Buffer[0]='G';
						}
						else{
							(char)_itoa((*pvtSelectLine)[i].m_lLine, Buffer, 10);
						}
						str_char=Buffer[0];
					}					
				}
			}
		}
		break;
	case BET_TURN_BET_1_1:
		{
			basic_string <char>::reference str_char=str.at(1);
			if(NULL!=str_char){
				if(str_char == '-'){
					str_char=GetBetChar(nBet);
				}
				else{
					basic_string <char>::reference str_char=str.at(2);
					if(NULL!=str_char){
						str_char=GetBetChar(nBet);
					}
				}
			}
		}
		break;
	case BET_TURN_BET_2_1:
		{
			basic_string <char>::reference str_char=str.at(3);
			if(NULL!=str_char){
				if(str_char == '-'){
					str_char=GetBetChar(nBet);
				}
				else{
					basic_string <char>::reference str_char=str.at(4);
					if(NULL!=str_char){
						str_char=GetBetChar(nBet);
					}
				}
			}
		}
		break;
	case BET_TURN_BET_2_2:
		{
			basic_string <char>::reference str_char=str.at(5);
			if(NULL!=str_char){
				if(str_char == '-'){
					str_char=GetBetChar(nBet);
				}
				else{
					basic_string <char>::reference str_char=str.at(6);
					if(NULL!=str_char){
						str_char=GetBetChar(nBet);
					}
				}
			}
		}
		break;
	case BET_TURN_BET_2_3:
		{
			basic_string <char>::reference str_char=str.at(7);
			if(NULL!=str_char){
				if(str_char == '-'){
					str_char=GetBetChar(nBet);
				}
				else{
					basic_string <char>::reference str_char=str.at(8);
					if(NULL!=str_char){
						str_char=GetBetChar(nBet);
					}
				}
			}
		}
		break;
	}
	if(FALSE==SetBetLog(nIdenty, str)) return FALSE;
	return TRUE;
}
char CBetLog::GetBetChar(int nBet)
{
	switch(nBet){
	case BETSTATE_DIE: return '#';
	case BETSTATE_CALL: return 'C';
	case BETSTATE_CHECK: return 'K';
	case BETSTATE_BBING: return 'B';
	case BETSTATE_DOUBLE: return 'D';
	case BETSTATE_QUARTER: return 'Q';
	case BETSTATE_HALF: return 'H';
	case BETSTATE_FULL: return 'F';
	case BETSTATE_ALLIN: return 'A';
	case BETSTATE_LIVE: return 'L';
	case BETSTATE_REST: return 'R';
	case BETSTATE_RECEIVE: return 'E';
	case BETSTATE_SAMEPOINT: return 'S';
	case BETSTATE_TENPOINT: return 'T';
	case BETSTATE_TWENTYPOINT: return 'W';
	case BETSTATE_FIFTYPOINT: return 'I';
	case BETSTATE_NINETYPOINT: return 'N';
	case BETSTATE_CUT: return 'U';
	case BETSTATE_PASS: return 'P';
	case BETSTATE_LIVE_CUT: return 'U';
	case BETSTATE_LIVE_PASS: return 'P';
	case BETSTATE_LINE: return 'G';
	}
	return '-';
}
char CBetLog::GetBetOrder(int nPos)
{
	char cOrder=0;
	char Buffer[10]={0,};
	(char)_itoa(nPos, Buffer, 10);
	cOrder=Buffer[0];
	return cOrder;
}
