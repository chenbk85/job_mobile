#ifndef __CTPAIRVECTOR_H__
#define __CTPAIRVECTOR_H__

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#pragma warning(disable : 4786)


#include <list>
#include <vector>
#include <map>
using namespace std;


template <typename ID, typename TYPE>
class CTPairVector : public vector<pair<ID, TYPE> >
{
public:
	typedef pair<ID, TYPE> PairVector;
	vector<pair<ID, TYPE> >::iterator m_vtIterater;
	vector<pair<ID, TYPE> >::reverse_iterator m_vtRIterater;
public:
	CTPairVector(void){ InitTPairVector(); }
	virtual ~CTPairVector(void){ FreeTPairVector(); }
	void InitTPairVector(void){}
	void FreeTPairVector(void){ DelVector(); }
	int OvernArray(int nArray){ return max(0, nArray-((int)size()-1)); }
	bool IsUsableArray(int nArray){ return ((0<=nArray)&&((int)size()>nArray)); }
	bool IsEmpty(void){ return (bool)empty(); }
public:
	bool CreateVector(int nArray);
	bool CreateVector(int nArray, ID Id);
	bool CreateVector(int nArray, ID Id, TYPE Type);
	bool AddOverVector(int nArray, ID Id, TYPE Type);
	bool AddOverVector(int nArray, ID Id, TYPE** ppType);
	bool AddOverVector(int nArray, ID Id, TYPE Type, TYPE** ppType);
	void AddDelVector(int nCount);
	void AddDelVector(int nCount, ID Id, TYPE Type);
	int AddVector(ID Id);
	int AddVector(ID Id, TYPE Type);
	int AddVector(ID Id, TYPE** ppType);
	int AddVector(ID Id, TYPE Type, TYPE** ppType);
	int AddFrontVector(ID Id);
	int AddFrontVector(ID Id, TYPE Type);
	int AddFrontVector(ID Id, TYPE** ppType);
	int AddFrontVector(ID Id, TYPE Type, TYPE** ppType);
	int AddVector(vector<PairVector>* pvVecter);
	int AddVector(vector<PairVector>* pvVecter, int BeginnArray, int EndnArray);
	int AddVector(CTPairVector* pcVecter);
	int AddVector(CTPairVector* pcVecter, int BeginnArray, int EndnArray);
	int SetVector(vector<PairVector>* pvVecter);
	int SetVector(vector<PairVector>* pvVecter, int BeginnArray, int EndnArray);
	int SetVector(CTPairVector* pcVecter);
	int SetVector(CTPairVector* pcVecter, int BeginnArray, int EndnArray);
	int FindBeginAddVector(ID Id, TYPE Type);
	int FindBeginAddVector(ID Id, TYPE Type, TYPE** ppType);
	int FindEndAddVector(ID Id, TYPE Type);
	int FindEndAddVector(ID Id, TYPE Type, TYPE** ppType);
	bool InsertVector(int nArray, ID Id, TYPE Type);
	bool InsertVector(int nArray, ID Id, TYPE Type, TYPE** ppType);
	bool ChangeVector(int nArray, TYPE Type);
	bool ChangeVector(int nArray, ID Id, TYPE Type);
	bool ChangeID(int nArray, ID Id);
	bool IncreaseVector(int nArray, TYPE Type);
	bool DecreaseVector(int nArray, TYPE Type);
	bool IncreaseVector(int nArray, ID Id, TYPE Type);
	bool DecreaseVector(int nArray, ID Id, TYPE Type);
	bool IncreaseID(int nArray, ID Id);
	bool DecreaseID(int nArray, ID Id);
	int FindBeginChangeVector(ID Id, TYPE Type, TYPE Type_Change);
	int FindBeginChangeVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType);
	int FindEndChangeVector(ID Id, TYPE Type, TYPE Type_Change);
	int FindEndChangeVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType);
	int FindBeginChangeAddVector(ID Id, TYPE Type, TYPE Type_Change);
	int FindBeginChangeAddVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType);
	int FindEndChangeAddVector(ID Id, TYPE Type, TYPE Type_Change);
	int FindEndChangeAddVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType);
	bool SwapVector(int nArray1, int nArray2);
	bool MoveVector(int nArray1, int nArray2);
	bool MoveBeginVector(int nArray);
	bool MoveEndVector(int nArray);
	int FindVectorTotal(ID Id);
	int FindCompareVector(ID Id);
	int FindBeginVector(ID Id);
	int FindBeginVector(ID Id, TYPE &Type);
	int FindBeginVector(ID Id, TYPE** ppType);
	int FindEndVector(ID Id);
	int FindEndVector(ID Id, TYPE &Type);
	int FindEndVector(ID Id, TYPE** ppType);
	int FindBeginCompareVector(ID Id);
	int FindBeginCompareVector(ID Id, TYPE &Type);
	int FindBeginCompareVector(ID Id, TYPE** ppType);
	int FindEndCompareVector(ID Id);
	int FindEndCompareVector(ID Id, TYPE &Type);
	int FindEndCompareVector(ID Id, TYPE** ppType);
	int FindBeginDelVector(ID Id);
	int FindEndDelVector(ID Id);
	bool SwapVectorID(ID Id1, ID Id2);
	bool MoveVectorID(ID Id1, ID Id2);
	bool MoveBeginVectorID(ID Id);
	bool MoveEndVectorID(ID Id);
	bool DelVector(int nBeginArray, int nEndArray);
	bool DelVector(int nArray);
	bool DelBeginVector(void);
	bool DelEndVector(void);
	void DelVector(void);
	int TotalVector(void);
public:
	bool GetVector(int nArray, TYPE &Type);
	bool GetVectorPtr(int nArray, TYPE** ppType);
	bool GetVector(int nArray, ID &Id, TYPE &Type);
	bool GetVectorPtr(int nArray, ID &Id, TYPE** ppType);
	bool GetBeginVector(TYPE &Type);
	bool GetBeginVectorPtr(TYPE** ppType);
	bool GetBeginVector(ID &Id, TYPE &Type);
	bool GetBeginVectorPtr(ID &Id, TYPE** ppType);
	bool GetEndVector(TYPE &Type);
	bool GetEndVectorPtr(TYPE** ppType);
	bool GetEndVector(ID &Id, TYPE &Type);
	bool GetEndVectorPtr(ID &Id, TYPE** ppType);
public:
	bool GetBeginID(ID &Id);
	bool GetEndID(ID &Id);
	bool GetCurID(ID &Id);
	bool GetID(int nArray, ID &Id);
public:
	bool CurVector(int nArray);
	bool CurVector(int nArray, ID &Id, TYPE &Type);
	bool CurVector(int nArray, ID &Id, TYPE** ppType);
	bool CurVector(int nArray, TYPE &Type);
	bool CurVector(int nArray, TYPE** ppType);
	bool BeginVector(void);
	bool BeginToEndVector(void);
	bool BeginToNext(void);
	bool BeginToNext(ID &Id, TYPE &Type);
	bool BeginToNext(ID &Id, TYPE** ppType);
	bool BeginToNext(TYPE &Type);
	bool BeginToNext(TYPE** ppType);
	bool BeginToCur(ID &Id, TYPE &Type);
	bool BeginToCur(ID &Id, TYPE** ppType);
	bool BeginToCur(TYPE &Type);
	bool BeginToCur(TYPE** ppType);
	bool CurToPrev(ID &Id, TYPE &Type);
	bool CurToPrev(ID &Id, TYPE** ppType);
	bool CurToPrev(TYPE &Type);
	bool CurToPrev(TYPE** ppType);
	bool CurToNext(ID &Id, TYPE &Type);
	bool CurToNext(ID &Id, TYPE** ppType);
	bool CurToNext(TYPE &Type);
	bool CurToNext(TYPE** ppType);
	bool EndVector(void);
	bool EndToBeginVector(void);
	bool EndToPrev(void);
	bool EndToPrev(ID &Id, TYPE &Type);
	bool EndToPrev(ID &Id, TYPE** ppType);
	bool EndToPrev(TYPE &Type);
	bool EndToPrev(TYPE** ppType);
	bool EndToCur(ID &Id, TYPE &Type);
	bool EndToCur(ID &Id, TYPE** ppType);
	bool EndToCur(TYPE &Type);
	bool EndToCur(TYPE** ppType);
	bool IsEndVector(void);
	bool IsBeginVector(void);
public:
	int CurIterater(void){ return (int)(m_vtIterater-begin()); }
	int CurRIterater(void){ return (int)(m_vtRIterater-rbegin()); }
	int RearIterater(void){ return (int)(end()-m_vtIterater); }
	int RearRIterater(void){ return (int)(rend()-m_vtRIterater); }
	bool VectorBegin(void);
	bool VectorNext(void);
	bool VectorEnd(void);
	bool VectorPrev(void);
	bool VectorBegin(ID &Id, TYPE &Type);
	bool VectorNext(ID &Id, TYPE &Type);
	bool VectorEnd(ID &Id, TYPE &Type);
	bool VectorPrev(ID &Id, TYPE &Type);
	bool VectorBegin(ID &Id, TYPE** ppType);
	bool VectorNext(ID &Id, TYPE** ppType);
	bool VectorEnd(ID &Id, TYPE** ppType);
	bool VectorPrev(ID &Id, TYPE** ppType);
	bool VectorDelNext(ID &Id, TYPE** ppType);
	bool VectorDelPrev(ID &Id, TYPE** ppType);
	bool VectorBegin(TYPE &Type);
	bool VectorNext(TYPE &Type);
	bool VectorEnd(TYPE &Type);
	bool VectorPrev(TYPE &Type);
	bool VectorBegin(TYPE** ppType);
	bool VectorNext(TYPE** ppType);
	bool VectorEnd(TYPE** ppType);
	bool VectorPrev(TYPE** ppType);
	bool VectorDelNext(TYPE** ppType);
	bool VectorDelPrev(TYPE** ppType);
	bool VectorDel(void);
	bool IsNextEnd(void);
	bool IsPrevBegin(void);
public:
	virtual __int64 GetVectorToInt(int nArray);
	virtual int CompareVector(ID Id1, ID Id2);
public:
	void SortVector(bool (*CompareFunc)(const TYPE Type1, const TYPE Type2));
	void Sort_VectorAscend(void);
	void Sort_VectorDescend(void);
	void Sort_VectorAscend(int Start, int End);
	void Sort_VectorDescend(int Start, int End);
	void Sort_VectorAscend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, CTPairVector<ID, TYPE>* pVoid, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, CTPairVector<ID, TYPE>* pVoid, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
public:
	friend unsigned __int64 GetVector_Sort(CTPairVector<ID, TYPE>* pVoid, int nArray);
	friend void SwapVector_Sort(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2);
};
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
unsigned __int64 GetVector_Sort(CTPairVector<ID, TYPE>* pVoid, int nArray)
{
	CTPairVector<ID, TYPE>* pVoidVector=(CTPairVector<ID, TYPE>*)(pVoid);
	if(NULL==pVoidVector) return 0;
	return (unsigned __int64)pVoidVector->GetVectorToInt(nArray);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void SwapVector_Sort(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2)
{
	CTPairVector<ID, TYPE>* pVoidVector=(CTPairVector<ID, TYPE>*)(pVoid);
	if(NULL==pVoidVector) return;
	pVoidVector->SwapVector(nSwap1, nSwap2);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CreateVector(int nArray)
{
	if(0>=nArray) return false;
	clear();
	TYPE Type;
	ID Id;
	for(int i=0; i<nArray; i++){
		push_back(PairVector(Id, Type));
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CreateVector(int nArray, ID Id)
{
	if(0>=nArray) return false;
	clear();
	TYPE Type;
	for(int i=0; i<nArray; i++){
		push_back(PairVector(Id, Type));
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CreateVector(int nArray, ID Id, TYPE Type)
{
	if(0>=nArray) return false;
	clear();
	for(int i=0; i<nArray; i++){
		push_back(PairVector(Id, Type));
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::AddOverVector(int nArray, ID Id, TYPE Type)
{
	if(true==IsUsableArray(nArray)){
		return ChangeVector(nArray, Id, Type);
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	for(int i=0; i<OverValue; i++){
		push_back(PairVector(Id, Type));
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::AddOverVector(int nArray, ID Id, TYPE** ppType)
{
	if(true==IsUsableArray(nArray)){
		(*ppType)=&((*this)[nArray].second);
		return (NULL!=(*ppType));
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	TYPE Type;
	for(int i=0; i<OverValue; i++){
		push_back(PairVector(Id, Type));
	}
	if(NULL!=ppType) (*ppType)=&((*this)[nArray].second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::AddOverVector(int nArray, ID Id, TYPE Type, TYPE** ppType)
{
	if(true==IsUsableArray(nArray)){
		(*this)[nArray]=PairVector(Id, Type);
		(*ppType)=&((*this)[nArray].second);
		return (NULL!=(*ppType));
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	for(int i=0; i<OverValue; i++){
		push_back(PairVector(Id, Type));
	}
	if(NULL!=ppType) (*ppType)=&((*this)[nArray].second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::AddDelVector(int nCount)
{
	if((int)size()==nCount) return;
	if((int)size()>nCount){
		erase(begin()+nCount, end());
	}
	else{
		TYPE Type;
		ID Id;
		for(int i=(int)size(); i<nCount; i++){
			push_back(PairVector(Id, Type));
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::AddDelVector(int nCount, ID Id, TYPE Type)
{
	if((int)size()==nCount) return;
	if((int)size()>nCount){
		erase(begin()+nCount, end());
	}
	else{
		for(int i=(int)size(); i<nCount; i++){
			push_back(PairVector(Id, Type));
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(ID Id)
{
	TYPE Type;
	int nArray=(int)size();
	push_back(PairVector(Id, Type));
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(ID Id, TYPE Type)
{
	int nArray=(int)size();
	push_back(PairVector(Id, Type));
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(ID Id, TYPE** ppType)
{
	int nArray=(int)size();
	TYPE Type;
	push_back(PairVector(Id, Type));
	(*ppType)=&((*this)[nArray].second);
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(ID Id, TYPE Type, TYPE** ppType)
{
	int nArray=(int)size();
	push_back(PairVector(Id, Type));
	if(NULL!=ppType) (*ppType)=&((*this)[nArray].second);
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddFrontVector(ID Id)
{
	TYPE Type;
	insert(begin(), PairVector(Id, Type));
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddFrontVector(ID Id, TYPE Type)
{
	insert(begin(), PairVector(Id, Type));
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddFrontVector(ID Id, TYPE** ppType)
{
	TYPE Type;
	insert(begin(), PairVector(Id, Type));
	(*ppType)=&((*this)[nArray].second);
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddFrontVector(ID Id, TYPE Type, TYPE** ppType)
{
	insert(begin(), PairVector(Id, Type));
	if(NULL!=ppType) (*ppType)=&((*this)[nArray].second);
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(vector<PairVector>* pvVecter)
{
	if(NULL==pvVecter) return (int)size();
	insert(end(), pvVecter->begin(), pvVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(vector<PairVector>* pvVecter, int BeginnArray, int EndnArray)
{
	if(NULL==pvVecter) return (int)size();
	int Begin=max(0, BeginnArray);
	int End=min(EndnArray+1, (int)pvVecter->size());
	if(Begin>=(End-1)) return false;
	insert(end(), pvVecter->begin()+Begin, pvVecter->begin()+End);
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(CTPairVector* pcVecter)
{
	if(NULL==pcVecter) return (int)size();
	insert(end(), pcVecter->begin(), pcVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::AddVector(CTPairVector* pcVecter, int BeginnArray, int EndnArray)
{
	if(NULL==pcVecter) return (int)size();
	int Begin=max(0, BeginnArray);
	int End=min(EndnArray+1, pcVecter->TotalVector());
	if(Begin>=(End-1)) return false;
	insert(end(), pcVecter->begin()+Begin, pcVecter->begin()+End);
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::SetVector(vector<PairVector>* pvVecter)
{
	if(NULL==pvVecter) return (int)size();
	assign(pvVecter->begin(), pvVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::SetVector(vector<PairVector>* pvVecter, int BeginnArray, int EndnArray)
{
	if(NULL==pvVecter) return (int)size();
	int Begin=max(0, BeginnArray);
	int End=min(EndnArray+1, (int)pvVecter->size());
	if(Begin>=(End-1)) return false;
	assign(pvVecter->begin()+Begin, pvVecter->begin()+End);
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::SetVector(CTPairVector* pcVecter)
{
	if(NULL==pcVecter) return (int)size();
	assign(pcVecter->begin(), pcVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::SetVector(CTPairVector* pcVecter, int BeginnArray, int EndnArray)
{
	if(NULL==pcVecter) return (int)size();
	int Begin=max(0, BeginnArray);
	int End=min(EndnArray+1, pcVecter->TotalVector());
	if(Begin>=(End-1)) return false;
	assign(pcVecter->begin()+Begin, pcVecter->begin()+End);
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginAddVector(ID Id, TYPE Type)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			vtIterater->second=Type;
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Id, Type);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginAddVector(ID Id, TYPE Type, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			vtIterater->second=Type;
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Id, Type, ppType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndAddVector(ID Id, TYPE Type)
{
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Id==vtRIterater->first){
			vtRIterater->second=Type;
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Id, Type);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndAddVector(ID Id, TYPE Type, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Id==vtRIterater->first){
			vtRIterater->second=Type;
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Id, Type, ppType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::InsertVector(int nArray, ID Id, TYPE Type)
{
	if(false==IsUsableArray(nArray)){
		if(nArray==(int)size()){
			return (0<=AddVector(Id, Type));
		}
		return false;
	}
	insert(begin()+nArray, Type);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::InsertVector(int nArray, ID Id, TYPE Type, TYPE** ppType)
{
	if(false==IsUsableArray(nArray)){
		if(nArray==(int)size()){
			return (0<=AddVector(Id, Type));
		}
		return false;
	}
	insert(begin()+nArray, Type);
	if(NULL!=ppType){
		(*ppType)=(*this)[nArray].second;
		return (NULL!=(*ppType));
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::ChangeVector(int nArray, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].second=Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::ChangeVector(int nArray, ID Id, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray]=PairVector(Id, Type);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::ChangeID(int nArray, ID Id)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].first=Id;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::IncreaseVector(int nArray, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].second=(*this)[nArray].second+Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::DecreaseVector(int nArray, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].second=(*this)[nArray].second-Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::IncreaseVector(int nArray, ID Id, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].first=(*this)[nArray].first+Id;
	(*this)[nArray].second=(*this)[nArray].second+Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::DecreaseVector(int nArray, ID Id, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].first=(*this)[nArray].first-Id;
	(*this)[nArray].second=(*this)[nArray].second-Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::IncreaseID(int nArray, ID Id)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].first=(*this)[nArray].first+Id;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::DecreaseID(int nArray, ID Id)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].first=(*this)[nArray].first-Id;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginChangeVector(ID Id, TYPE Type, TYPE Type_Change)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if((Id==vtIterater->first)&&(Type==vtIterater->second)){
			vtIterater->second=Type_Change;
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginChangeVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if((Id==vtIterater->first)&&(Type==vtIterater->second)){
			vtIterater->second=Type_Change;
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndChangeVector(ID Id, TYPE Type, TYPE Type_Change)
{
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if((Id==vtRIterater->first)&&(Type==vtRIterater->second)){
			vtRIterater->second=Type_Change;
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndChangeVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if((Id==vtRIterater->first)&&(Type==vtRIterater->second)){
			vtRIterater->second=Type_Change;
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginChangeAddVector(ID Id, TYPE Type, TYPE Type_Change)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if((Id==vtIterater->first)&&(Type==vtIterater->second)){
			vtIterater->second=Type_Change;
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Id, Type_Change);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginChangeAddVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if((Id==vtIterater->first)&&(Type==vtIterater->second)){
			vtIterater->second=Type_Change;
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Id, Type_Change, ppType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndChangeAddVector(ID Id, TYPE Type, TYPE Type_Change)
{
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if((Id==vtRIterater->first)&&(Type==vtRIterater->second)){
			vtRIterater->second=Type_Change;
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Id, Type_Change);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndChangeAddVector(ID Id, TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if((Id==vtRIterater->first)&&(Type==vtRIterater->second)){
			vtRIterater->second=Type_Change;
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Id, Type_Change);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::SwapVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray1)||((int)size()<=nArray1)) return false;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	PairVector PairType=(*this)[nArray1];
	(*this)[nArray1]=(*this)[nArray2];
	(*this)[nArray2]=PairType;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::MoveVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	if(0>nArray1) return false;
	PairVector PairType=(*this)[nArray2];
	//erase(&(*this)[nArray2]);
	erase(begin()+nArray2);
	if(0==nArray1){
		insert(begin(), PairType);
		return true;
	}
	if((int)size()<=nArray1){
		insert(end(), PairType);
		return true;
	}
	insert(begin()+nArray1, PairType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::MoveBeginVector(int nArray)
{
	if(0==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairVector PairType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(begin(), PairType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::MoveEndVector(int nArray)
{
	if(((int)size()-1)==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairVector PairType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(end(), PairType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindVectorTotal(ID Id)
{
	int nCount=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			nCount++;
		}
	}
	return nCount;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindCompareVector(ID Id)
{
	int nCount=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(0==CompareVector(Id, vtIterater->first)){
			nCount++;
		}
	}
	return nCount;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginVector(ID Id)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginVector(ID Id, TYPE &Type)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			Type=vtIterater->second;
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginVector(ID Id, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndVector(ID Id)
{
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Id==vtRIterater->first){
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndVector(ID Id, TYPE &Type)
{
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Id==vtRIterater->first){
			vtIterater=vtRIterater.base();
			Type=vtIterater->second;
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndVector(ID Id, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Id==vtRIterater->first){
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginCompareVector(ID Id)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(0==CompareVector(Id, vtIterater->first)){
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginCompareVector(ID Id, TYPE &Type)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(0==CompareVector(Id, vtIterater->first)){
			Type=vtIterater->second;
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginCompareVector(ID Id, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(0==CompareVector(Id, vtIterater->first)){
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndCompareVector(ID Id)
{
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(0==CompareVector(Id, vtRIterater->first)){
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndCompareVector(ID Id, TYPE &Type)
{
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(0==CompareVector(Id, vtRIterater->first)){
			vtIterater=vtRIterater.base();
			Type=vtIterater->second;
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndCompareVector(ID Id, TYPE** ppType)
{
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(0==CompareVector(Id, vtRIterater->first)){
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=&(vtIterater->second);
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindBeginDelVector(ID Id)
{
	int nFind=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
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
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::FindEndDelVector(ID Id)
{
	int nFind=0;
	vector<PairVector>::iterator vtIterater;
	vector<PairVector>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Id==vtRIterater->first){
			nFind=(int)(rend()-vtRIterater);
			vtIterater=vtRIterater.base();
			vtIterater=erase(vtIterater);
			vtRIterater=vector<PairVector>::reverse_iterator(vtIterater);
			return nFind;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::SwapVectorID(ID Id1, ID Id2)
{
	int nArray1=0;
	int nArray2=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id1==vtIterater->first){
			nArray1=(int)(vtIterater-begin());
		}
		if(Id2==vtIterater->first){
			nArray2=(int)(vtIterater-begin());
		}
	}
	if(nArray1==nArray2) return true;
	if((0>nArray1)||((int)size()<=nArray1)) return false;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	PairVector PairType=(*this)[nArray1];
	(*this)[nArray1]=(*this)[nArray2];
	(*this)[nArray2]=PairType;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::MoveVectorID(ID Id1, ID Id2)
{
	int nArray1=0;
	int nArray2=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id1==vtIterater->first){
			nArray1=(int)(vtIterater-begin());
		}
		if(Id2==vtIterater->first){
			nArray2=(int)(vtIterater-begin());
		}
	}
	if(nArray1==nArray2) return true;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	if(0>nArray1) return false;
	PairVector PairType=(*this)[nArray2];
	//erase(&(*this)[nArray2]);
	erase(begin()+nArray2);
	if(0==nArray1){
		insert(begin(), PairType);
		return true;
	}
	if((int)size()<=nArray1){
		insert(end(), PairType);
		return true;
	}
	insert(begin()+nArray1, PairType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::MoveBeginVectorID(ID Id)
{
	int nArray=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			nArray=(int)(vtIterater-begin());
		}
	}
	if(0==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairVector PairType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(begin(), PairType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::MoveEndVectorID(ID Id)
{
	int nArray=0;
	vector<PairVector>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Id==vtIterater->first){
			nArray=(int)(vtIterater-begin());
		}
	}
	if(((int)size()-1)==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairVector PairType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(end(), PairType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::DelVector(int nBeginArray, int nEndArray)
{
	int nBegin=max(0, nBeginArray);
	int nEnd=min(nEndArray+1, (int)size());
	if(nBegin>(nEnd-1)) return false;
	if(nBegin==(nEnd-1)){
		//erase(&(*this)[nBegin]);
		erase(begin()+nBegin);
		return true;
	}
	erase(begin()+nBegin, begin()+nEnd);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::DelVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::DelBeginVector(void)
{
	if(true==empty()) return false;
	//erase(&(*this)[0]);
	pop_front();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::DelEndVector(void)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	//erase(&(*this)[nTotal-1]);
	pop_back();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::DelVector(void)
{
	clear(); 
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::TotalVector(void)
{
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetVector(int nArray, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Type=(*this)[nArray].second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetVectorPtr(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*ppType)=&((*this)[nArray].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetVector(int nArray, ID &Id, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Id=(*this)[nArray].first;
	Type=(*this)[nArray].second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetVectorPtr(int nArray, ID &Id, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Id=(*this)[nArray].first;
	(*ppType)=&((*this)[nArray].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetBeginVector(TYPE &Type)
{
	if(true==empty()) return false;
	Type=(*this)[0].second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetBeginVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	if(NULL==ppType) return false;
	(*ppType)=&((*this)[0].second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetBeginVector(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	Id=(*this)[0].first;
	Type=(*this)[0].second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetBeginVectorPtr(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(NULL==ppType) return false;
	Id=(*this)[0].first;
	(*ppType)=&((*this)[0].second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetEndVector(TYPE &Type)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	Type=(*this)[nTotal-1].second;
	//type=(*m_cvVector.end());
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetEndVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	if(NULL==ppType) return false;
	int nTotal=(int)size();
	(*ppType)=&((*this)[nTotal-1].second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetEndVector(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	Id=(*this)[nTotal-1].first;
	Type=(*this)[nTotal-1].second;
	//type=(*m_cvVector.end());
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetEndVectorPtr(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(NULL==ppType) return false;
	int nTotal=(int)size();
	Id=(*this)[nTotal-1].first;
	(*ppType)=&((*this)[nTotal-1].second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetID(int nArray, ID &Id)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Id=(*this)[nArray].first;
	return true;	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetBeginID(ID &Id)
{
	if(true==empty()) return false;
	Id=begin()->first;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetEndID(ID &Id)
{
	if(true==empty()) return false;
	Id=end()->first;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::GetCurID(ID &Id)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurVector(int nArray, ID &Id, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurVector(int nArray, ID &Id, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurVector(int nArray, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurVector(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginVector(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToEndVector(void)
{
	if(true==empty()) return false;
	m_vtIterater=end();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToNext(void)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToNext(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	Type=m_vtIterater->second;
	m_vtIterater++;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=&(m_vtIterater->second);
	m_vtIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToNext(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Type=m_vtIterater->second;
	m_vtIterater++;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=&(m_vtIterater->second);
	m_vtIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToCur(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToCur(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToCur(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::BeginToCur(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToPrev(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	Id=vtIterater->first;
	Type=vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToPrev(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToPrev(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	Type=vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToNext(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	Id=vtIterater->first;
	Type=vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToNext(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	Type=vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::CurToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndVector(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToBeginVector(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rend();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToPrev(void)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToPrev(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	Id=m_vtRIterater->first;
	Type=m_vtRIterater->second;
	m_vtRIterater++;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToPrev(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	m_vtRIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToPrev(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	Type=m_vtRIterater->second;
	m_vtRIterater++;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=&(vtIterater->second);
	m_vtRIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToCur(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	Id=m_vtRIterater->first;
	Type=m_vtRIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToCur(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToCur(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	Type=m_vtRIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::EndToCur(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::IsEndVector(void)
{
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::IsBeginVector(void)
{
	return (m_vtRIterater==rend());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorBegin(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorNext(void)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorEnd(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorPrev(void)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorBegin(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	Id=m_vtIterater->first;
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorNext(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorEnd(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	Id=m_vtRIterater->first;
	Type=m_vtRIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorPrev(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	Id=m_vtRIterater->first;
	Type=m_vtRIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorBegin(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	Id=m_vtIterater->first;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorEnd(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorPrev(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorDelNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorDelPrev(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(++m_vtRIterater).base();
	erase(vtIterater);
	if(m_vtRIterater==rend()) return false;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorBegin(TYPE &Type)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorNext(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	Type=m_vtIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorEnd(TYPE &Type)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	Type=m_vtRIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorPrev(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	Type=m_vtRIterater->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorBegin(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorEnd(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorDelNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	(*ppType)=&(m_vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorDelPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairVector>::iterator vtIterater;
	vtIterater=(++m_vtRIterater).base();
	erase(vtIterater);
	if(m_vtRIterater==rend()) return false;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::VectorDel(void)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::IsNextEnd(void)
{
	return ((m_vtIterater+1)==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairVector<ID, TYPE>::IsPrevBegin(void)
{
	return ((m_vtRIterater+1)==rend());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
__int64 CTPairVector<ID, TYPE>::GetVectorToInt(int nArray)
{
	if(true==IsUsableArray(nArray)) return 1;
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairVector<ID, TYPE>::CompareVector(ID Id1, ID Id2)
{
//	if(Type1==Type2) return 0;
//	if(Type1>Type2) return 1;
//	if(Type1<Type2) return -1;
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::SortVector(bool (*CompareFunc)(const TYPE Type1, const TYPE Type2))
{
	std::sort(begin(), end(), CompareFunc);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorAscend(void)
{
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPairVector<ID, TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorDescend(void)
{
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPairVector<ID, TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorAscend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPairVector<ID, TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorDescend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPairVector<ID, TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorAscend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray))
{
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPairVector<ID, TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorDescend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray))
{
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPairVector<ID, TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorAscend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPairVector<ID, TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorDescend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPairVector<ID, TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorAscend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPairVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorDescend(unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPairVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorAscend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPairVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorDescend(int Start, int End, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairVector<ID, TYPE>* pctVector=(CTPairVector<ID, TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPairVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 오르기
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorAscend(int Start, int End, CTPairVector<ID, TYPE>* pVoid, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	unsigned __int64 Value=0;
	unsigned __int64 pivot=Function(pVoid, Start);
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
	Sort_VectorAscend(Start, j-1, pVoid, Function, Swap);
	Sort_VectorAscend(j+1, End, pVoid, Function, Swap);
}
//------------------------------------------------------------------//
//내리기
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairVector<ID, TYPE>::Sort_VectorDescend(int Start, int End, CTPairVector<ID, TYPE>* pVoid, unsigned __int64 (*Function)(CTPairVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	unsigned __int64 Value=0;
	unsigned __int64 pivot=Function(pVoid, Start);
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
	Sort_VectorDescend(Start, j-1, pVoid, Function, Swap);
	Sort_VectorDescend(j+1, End, pVoid, Function, Swap);
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

template <typename ID, typename TYPE>
class CTPairPVector : public vector<pair<ID, TYPE*> >
{
public:
	typedef pair<ID, TYPE*> PairPVector;
	vector<pair<ID, TYPE*> >::iterator m_vtIterater;
	vector<pair<ID, TYPE*> >::reverse_iterator m_vtRIterater;
public:
	CTPairPVector(void){ InitTPairPVector(); }
	virtual ~CTPairPVector(void){ FreeTPairPVector(); }
	void InitTPairPVector(void){}
	void FreeTPairPVector(void){ DelVector(); }
	int OvernArray(int nArray){ return max(0, nArray-((int)size()-1)); }
	bool IsUsableArray(int nArray){ return ((0<=nArray)&&((int)size()>nArray)); }
	bool IsEmpty(void){ return (bool)empty(); }
public:
	bool CreateVector(int nArray);
	bool CreateVector(int nArray, ID Id);
	bool AddOverVector(int nArray, TYPE** ppType);
	bool AddOverVector(int nArray, ID Id, TYPE** ppType);
	int AddVector(TYPE** ppType);
	int AddVector(ID Id);
	int AddVector(ID Id, TYPE** ppType);
	int AddFrontVector(TYPE** ppType);
	int AddFrontVector(ID Id);
	int AddFrontVector(ID Id, TYPE** ppType);
	bool InsertVector(int nArray, TYPE** ppType);
	bool InsertVector(int nArray, ID Id, TYPE** ppType);
	bool ChangeVector(int nArray, TYPE Type);
	bool ChangeVector(int nArray, ID Id, TYPE Type);
	bool ChangeID(int nArray, ID Id);
	bool SwapVector(int nArray1, int nArray2);
	bool MoveVector(int nArray1, int nArray2);
	bool MoveBeginVector(int nArray);
	bool MoveEndVector(int nArray);
	int FindVectorTotal(ID Id);
	int FindCompareVectorTotal(ID Id);
	int FindBeginVector(ID Id);
	int FindBeginVector(ID Id, TYPE** ppType);
	int FindEndVector(ID Id);
	int FindEndVector(ID Id, TYPE** ppType);
	int FindBeginCompareVector(ID Id);
	int FindBeginCompareVector(ID Id, TYPE** ppType);
	int FindEndCompareVector(ID Id);
	int FindEndCompareVector(ID Id, TYPE** ppType);
	int FindBeginDelVector(ID Id);
	int FindEndDelVector(ID Id);
	bool SwapVectorID(ID Id1, ID Id2);
	bool MoveVectorID(ID Id1, ID Id2);
	bool MoveBeginVectorID(ID Id);
	bool MoveEndVectorID(ID Id);
	bool DelVector(int nBeginArray, int nEndArray);
	bool DelVector(int nArray);
	bool DelBeginVector(void);
	bool DelEndVector(void);
	void DelVector(void);
	int TotalVector(void);
public:
	bool GetVector(int nArray, TYPE &Type);
	bool GetVectorPtr(int nArray, TYPE** ppType);
	bool GetVector(int nArray, ID &Id, TYPE &Type);
	bool GetVectorPtr(int nArray, ID &Id, TYPE** ppType);
	bool GetBeginVector(TYPE &Type);
	bool GetBeginVectorPtr(TYPE** ppType);
	bool GetBeginVector(ID &Id, TYPE &Type);
	bool GetBeginVectorPtr(ID &Id, TYPE** ppType);
	bool GetEndVector(TYPE &Type);
	bool GetEndVectorPtr(TYPE** ppType);
	bool GetEndVector(ID &Id, TYPE &Type);
	bool GetEndVectorPtr(ID &Id, TYPE** ppType);
public:
	bool GetBeginID(ID &Id);
	bool GetEndID(ID &Id);
	bool GetCurID(ID &Id);
	bool GetID(int nArray, ID &Id);
public:
	bool CurVector(int nArray);
	bool CurVector(int nArray, ID &Id, TYPE** ppType);
	bool CurVector(int nArray, TYPE** ppType);
	bool BeginVector(void);
	bool BeginToNext(ID &Id, TYPE** ppType);
	bool BeginToCur(ID &Id, TYPE** ppType);
	bool CurToPrev(ID &Id, TYPE** ppType);
	bool CurToNext(ID &Id, TYPE** ppType);
	bool BeginToNext(TYPE** ppType);
	bool BeginToCur(TYPE** ppType);
	bool CurToPrev(TYPE** ppType);
	bool CurToNext(TYPE** ppType);
	bool IsEndVector(void);
	bool IsNextEnd(void);
	bool IsPrevBegin(void);
public:
	int CurIterater(void){ return (int)(m_vtIterater-begin()); }
	int CurRIterater(void){ return (int)(m_vtRIterater-rbegin()); }
	int RearIterater(void){ return (int)(end()-m_vtIterater); }
	int RearRIterater(void){ return (int)(rend()-m_vtRIterater); }
	bool VectorBegin(void);
	bool VectorNext(void);
	bool VectorEnd(void);
	bool VectorPrev(void);
	bool VectorBegin(ID &Id, TYPE** ppType);
	bool VectorNext(ID &Id, TYPE** ppType);
	bool VectorEnd(ID &Id, TYPE** ppType);
	bool VectorPrev(ID &Id, TYPE** ppType);
	bool VectorDelNext(ID &Id, TYPE** ppType);
	bool VectorDelPrev(ID &Id, TYPE** ppType);
	bool VectorBegin(TYPE** ppType);
	bool VectorNext(TYPE** ppType);
	bool VectorEnd(TYPE** ppType);
	bool VectorPrev(TYPE** ppType);
	bool VectorDelNext(TYPE** ppType);
	bool VectorDelPrev(TYPE** ppType);
	bool VectorDel(void);
public:
	virtual __int64 GetVectorToInt(int nArray);
	virtual int CompareVector(ID Id1, ID Id2);
public:
	void SortVector(bool (*CompareFunc)(const TYPE* pType1, const TYPE* pType2));
	void Sort_VectorAscend(void);
	void Sort_VectorDescend(void);
	void Sort_VectorAscend(int Start, int End);
	void Sort_VectorDescend(int Start, int End);
	void Sort_VectorAscend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, CTPairPVector<ID, TYPE>* pVoid, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, CTPairPVector<ID, TYPE>* pVoid, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2));
public:
	friend __int64 GetPVector_Sort(CTPairPVector<ID, TYPE>* pVoid, int nArray);
	friend void SwapPVector_Sort(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2);
};
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
__int64 GetPVector_Sort(CTPairPVector<ID, TYPE>* pVoid, int nArray)
{
	CTPairPVector<ID, TYPE>* pVoidVector=(CTPairPVector<ID, TYPE>*)(pVoid);
	if(NULL==pVoidVector) return;
	return pVoidVector->GetVectorToInt(nArray);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void SwapPVector_Sort(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2)
{
	CTPairPVector<ID, TYPE>* pVoidVector=(CTPairPVector<ID, TYPE>*)(pVoid);
	if(NULL==pVoidVector) return;
	pVoidVector->SwapVector(nSwap1, nSwap2);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CreateVector(int nArray)
{
	if(0>=nArray) return false;
	DelVector();
	for(int i=0; i<nArray; i++){
		TYPE* pType=new TYPE;
		ID Id;
		if(NULL==pType) return false;
		push_back(PairPVector(Id, pType));
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CreateVector(int nArray, ID Id)
{
	if(0>=nArray) return false;
	DelVector();
	for(int i=0; i<nArray; i++){
		TYPE* pType=new TYPE;
		if(NULL==pType) return false;
		push_back(PairPVector(Id, pType));
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::AddOverVector(int nArray, TYPE** ppType)
{
	if(true==IsUsableArray(nArray)){
		(*ppType)=(*this)[nArray].second;
		return (NULL!=(*ppType));
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	for(int i=0; i<OverValue; i++){
		TYPE* pType=new TYPE;
		ID Id;
		if(NULL==pType) return false;
		push_back(PairPVector(Id, pType));
	}
	(*ppType)=(*this)[nArray].second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::AddOverVector(int nArray, ID Id, TYPE** ppType)
{
	if(true==IsUsableArray(nArray)){
		(*ppType)=(*this)[nArray].second;
		return (NULL!=(*ppType));
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	for(int i=0; i<OverValue; i++){
		TYPE* pType=new TYPE;
		if(NULL==pType) return false;
		push_back(PairPVector(Id, pType));
	}
	(*ppType)=(*this)[nArray].second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::AddVector(TYPE** ppType)
{
	int nArray=(int)size();
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	ID Id;
	push_back(PairPVector(Id, pType));
	(*ppType)=(*this)[nArray].second;
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::AddVector(ID Id)
{
	int nArray=(int)size();
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	push_back(PairPVector(Id, pType));
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::AddVector(ID Id, TYPE** ppType)
{
	int nArray=(int)size();
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	push_back(PairPVector(Id, pType));
	(*ppType)=(*this)[nArray].second;
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::AddFrontVector(TYPE** ppType)
{
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	ID Id;
	insert(begin(), PairPVector(Id, pType));
	(*ppType)=(*this)[nArray].second;
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::AddFrontVector(ID Id)
{
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	insert(begin(), PairPVector(Id, pType));
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::AddFrontVector(ID Id, TYPE** ppType)
{
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	insert(begin(), PairPVector(Id, pType));
	(*ppType)=(*this)[nArray].second;
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::InsertVector(int nArray, ID Id, TYPE** ppType)
{
	if(false==IsUsableArray(nArray)){
		if(nArray==(int)size()){
			return (0<=AddVector(Id, ppType));
		}
		return false;
	}
	TYPE* pType=new TYPE;
	if(NULL==pType) return false;
	insert(begin()+nArray, PairPVector(Id, pType));
	if(NULL!=ppType){
		(*ppType)=(*this)[nArray].second;
		return (NULL!=(*ppType));
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::ChangeVector(int nArray, ID Id, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
//	TYPE* pType=new TYPE;
//	if(NULL==pType) return false;
//	(*pType)=Type;
//	if(NULL!=(*this)[nArray]){
//		TYPE** ppType=(&((*this)[nArray].second));
//		delete (*ppType);
//		(*ppType)=NULL;
//	}
//	(*this)[nArray]=pType;
	(*this)[nArray].first=Id;
	(*(*this)[nArray].second)=Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::ChangeID(int nArray, ID Id)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray].first=Id;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::SwapVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray1)||((int)size()<=nArray1)) return false;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	PairPVector PairPType=(*this)[nArray1];
	(*this)[nArray1]=(*this)[nArray2];
	(*this)[nArray2]=PairPType;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::MoveVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	if(0>nArray1) return false;
	PairPVector PairPType=(*this)[nArray2];
	//erase(&(*this)[nArray2]);
	erase(begin()+nArray2);
	if(0==nArray1){
		insert(begin(), PairPType);
		return true;
	}
	if((int)size()<=nArray1){
		insert(end(), PairPType);
		return true;
	}
	insert(begin()+nArray1, PairPType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::MoveBeginVector(int nArray)
{
	if(0==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairPVector PairPType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(begin(), PairPType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::MoveEndVector(int nArray)
{
	if(((int)size()-1)==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairPVector PairPType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(end(), PairPType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindVectorTotal(ID Id)
{
	int nTotal=(int)size();
	int nCount=0;
	for(int i=0; i<nTotal; i++){
		if(Id==(*this)[i].first){
			nCount++;
		}
	}
	return nCount;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindCompareVectorTotal(ID Id)
{
	int nTotal=(int)size();
	int nCount=0;
	for(int i=0; i<nTotal; i++){
		if(0==CompareVector(Id, (*this)[i].first)){
			nCount++;
		}
	}
	return nCount;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindBeginVector(ID Id)
{
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(Id==(*this)[i].first){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindBeginVector(ID Id, TYPE** ppType)
{
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(Id==(*this)[i].first){
			(*ppType)=(*this)[i].second;
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindEndVector(ID Id)
{
	int nTotal=(int)size();
	for(int i=nTotal-1; i>=0; i--){
		if(Id==(*this)[i].first){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindEndVector(ID Id, TYPE** ppType)
{
	int nTotal=(int)size();
	for(int i=nTotal-1; i>=0; i--){
		if(Id==(*this)[i].first){
			(*ppType)=(*this)[i].second;
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindBeginCompareVector(ID Id)
{
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(0==CompareVector(Id, (*this)[i].first)){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindBeginCompareVector(ID Id, TYPE** ppType)
{
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(0==CompareVector(Id, (*this)[i].first)){
			(*ppType)=(*this)[i].second;
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindEndCompareVector(ID Id)
{
	int nTotal=(int)size();
	for(int i=nTotal-1; i>=0; i--){
		if(0==CompareVector(Id, (*this)[i].first)){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindEndCompareVector(ID Id, TYPE** ppType)
{
	int nTotal=(int)size();
	for(int i=nTotal-1; i>=0; i--){
		if(0==CompareVector(Id, (*this)[i].first)){
			(*ppType)=(*this)[i].second;
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindBeginDelVector(ID Id)
{
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(Id==(*this)[i].first){
			if(NULL!=(*this)[i].second){
				TYPE** ppType=&((*this)[i].second);
				delete (*ppType);
				(*ppType)=NULL;
			}
			//erase(&(*this)[i]);
			erase(begin()+i);
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::FindEndDelVector(ID Id)
{
	int nTotal=(int)size();
	for(int i=nTotal-1; i>=0; i--){
		if(Id==(*this)[i].first){
			if(NULL!=(*this)[i].second){
				TYPE** ppType=&((*this)[i].second);
				delete (*ppType);
				(*ppType)=NULL;
			}
			//erase(&(*this)[i]);
			erase(begin()+i);
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::SwapVectorID(ID Id1, ID Id2)
{
	int nArray1=0;
	int nArray2=0;
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(Id1==(*this)[i].first){
			nArray1=i;
		}
		if(Id2==(*this)[i].first){
			nArray2=i;
		}
	}
	if(nArray1==nArray2) return true;
	if((0>nArray1)||((int)size()<=nArray1)) return false;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	PairPVector PairPType=(*this)[nArray1];
	(*this)[nArray1]=(*this)[nArray2];
	(*this)[nArray2]=PairPType;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::MoveVectorID(ID Id1, ID Id2)
{
	int nArray1=0;
	int nArray2=0;
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(Id1==(*this)[i].first){
			nArray1=i;
		}
		if(Id2==(*this)[i].first){
			nArray2=i;
		}
	}
	if(nArray1==nArray2) return true;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	if(0>nArray1) return false;
	PairPVector PairPType=(*this)[nArray2];
	//erase(&(*this)[nArray2]);
	erase(begin()+nArray2);
	if(0==nArray1){
		insert(begin(), PairPType);
		return true;
	}
	if((int)size()<=nArray1){
		insert(end(), PairPType);
		return true;
	}
	insert(begin()+nArray1, PairPType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::MoveBeginVectorID(ID Id)
{
	int nArray=0;
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(Id==(*this)[i].first){
			nArray=i;
		}
	}
	if(0==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairPVector PairPType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(begin(), PairPType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::MoveEndVectorID(ID Id)
{
	int nArray=0;
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(Id==(*this)[i].first){
			nArray=i;
		}
	}
	if(((int)size()-1)==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	PairPVector PairPType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(end(), PairPType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::DelVector(int nBeginArray, int nEndArray)
{
	int nBegin=max(0, nBeginArray);
	int nEnd=min(nEndArray+1, (int)size());
	if(nBegin>(nEnd-1)) return false;
	if(nBegin==(nEnd-1)){
		if(NULL!=(*this)[nBegin].second){
			TYPE** ppType=&((*this)[nBegin].second);
			delete (*ppType);
			(*ppType)=NULL;
		}
		//erase(&(*this)[nBegin]);
		erase(begin()+nBegin);
		return true;
	}
	for(int i=nBegin; i<nEnd; i++){
		if(NULL!=(*this)[i].second){
			TYPE** ppType=&((*this)[i].second);
			delete (*ppType);
			(*ppType)=NULL;
		}
	}
	erase(begin()+nBegin, begin()+nEnd);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::DelVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	if(NULL!=(*this)[nArray].second){
		TYPE** ppType=&((*this)[nArray].second);
		delete (*ppType);
		(*ppType)=NULL;
	}
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::DelBeginVector(void)
{
	if(true==empty()) return false;
	if(NULL!=(*this)[0].second){
		TYPE** ppType=&((*this)[0].second);
		delete (*ppType);
		(*ppType)=NULL;
	}
	//erase(&(*this)[0]);
	pop_front();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::DelEndVector(void)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	if(NULL!=(*this)[nTotal-1].second){
		TYPE** ppType=&((*this)[nTotal-1].second);
		delete (*ppType);
		(*ppType)=NULL;
	}
	//erase(&(*this)[nTotal-1]);
	pop_back();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::DelVector(void)
{
	int nTotal=(int)size();
	for(int i=0; i<nTotal; i++){
		if(NULL!=(*this)[i].second){
			TYPE** ppType=&((*this)[i].second);
			delete (*ppType);
			(*ppType)=NULL;
		}
	}
	clear(); 
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::TotalVector(void)
{
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetVector(int nArray, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Type=*((*this)[nArray].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetVectorPtr(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*ppType)=(*this)[nArray].second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetVector(int nArray, ID &Id, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Id=(*this)[nArray].first;
	Type=*((*this)[nArray].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetVectorPtr(int nArray, ID &Id, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Id=(*this)[nArray].first;
	(*ppType)=(*this)[nArray].second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetBeginVector(TYPE &Type)
{
	if(true==empty()) return false;
	Type=*((*this)[0].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetBeginVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	(*ppType)=(*this)[0].second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetBeginVector(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	Id=(*this)[0].first;
	Type=*((*this)[0].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetBeginVectorPtr(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	Id=(*this)[0].first;
	(*ppType)=(*this)[0].second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetEndVector(TYPE &Type)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	Type=*((*this)[nTotal-1].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetEndVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	(*ppType)=(*this)[nTotal-1].second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetEndVector(ID &Id, TYPE &Type)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	Id=(*this)[nTotal-1].first;
	Type=*((*this)[nTotal-1].second);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetEndVectorPtr(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	int nTotal=(int)size();
	Id=(*this)[nTotal-1].first;
	(*ppType)=(*this)[nTotal-1].second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetID(int nArray, ID &Id)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Id=(*this)[nArray].first;
	return true;	
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetBeginID(ID &Id)
{
	if(true==empty()) return false;
	Id=begin()->first;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetEndID(ID &Id)
{
	if(true==empty()) return false;
	Id=end()->first;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::GetCurID(ID &Id)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CurVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CurVector(int nArray, ID &Id, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CurVector(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::BeginVector(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::BeginToNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=m_vtIterater->second;
	m_vtIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::BeginToCur(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CurToPrev(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	Id=vtIterater->first;
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CurToNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	Id=vtIterater->first;
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::BeginToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater->second;
	m_vtIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::BeginToCur(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CurToPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::CurToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::IsEndVector(void)
{
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorBegin(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorNext(void)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorEnd(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorPrev(void)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorBegin(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	Id=m_vtIterater->first;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorEnd(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	vector<PairPVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorPrev(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorDelNext(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	TYPE* pType=m_vtIterater->second;
	if(NULL!=pType){
		delete pType;
		pType=NULL;
	}
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	Id=m_vtIterater->first;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorDelPrev(ID &Id, TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=(++m_vtRIterater).base();
	TYPE* pType=vtIterater->second;
	if(NULL!=pType){
		delete pType;
		pType=NULL;
	}
	erase(vtIterater);
	if(m_vtRIterater==rend()) return false;
	vtIterater=(--m_vtRIterater.base());
	Id=vtIterater->first;
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorBegin(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorEnd(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	vector<PairPVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorDelNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	TYPE* pType=m_vtIterater->second;
	if(NULL!=pType){
		delete pType;
		pType=NULL;
	}
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater->second;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorDelPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<PairPVector>::iterator vtIterater;
	vtIterater=(++m_vtRIterater).base();
	TYPE* pType=vtIterater->second;
	if(NULL!=pType){
		delete pType;
		pType=NULL;
	}
	erase(vtIterater);
	if(m_vtRIterater==rend()) return false;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=&(vtIterater->second);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::VectorDel(void)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	TYPE* pType=m_vtIterater->second;
	if(NULL!=pType){
		delete pType;
		pType=NULL;
	}
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::IsNextEnd(void)
{
	return ((m_vtIterater+1)==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPairPVector<ID, TYPE>::IsPrevBegin(void)
{
	return ((m_vtRIterater+1)==rend());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
__int64 CTPairPVector<ID, TYPE>::GetVectorToInt(int nArray)
{
	if(true==IsUsableArray(nArray)) return 1;
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
int CTPairPVector<ID, TYPE>::CompareVector(ID Id1, ID Id2)
{
//	if(Type1==Type2) return 0;
//	if(Type1>Type2) return 1;
//	if(Type1<Type2) return -1;
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::SortVector(bool (*CompareFunc)(const TYPE* pType1, const TYPE* pType2))
{
	std::sort(begin(), end(), CompareFunc);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorAscend(void)
{
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPairPVector<ID, TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorDescend(void)
{
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPairPVector<ID, TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorAscend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPairPVector<ID, TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorDescend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPairPVector<ID, TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorAscend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray))
{
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPairPVector<ID, TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorDescend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray))
{
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPairPVector<ID, TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPairPVector<ID, TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPairPVector<ID, TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorAscend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPairPVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorDescend(__int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPairPVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPairPVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPairPVector<ID, TYPE>* pctVector=(CTPairPVector<ID, TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPairPVector<ID, TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 오르기
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorAscend(int Start, int End, CTPairPVector<ID, TYPE>* pVoid, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	__int64 Value=0;
	__int64 pivot=Function(pVoid, Start);
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
	Sort_VectorAscend(Start, j-1, pVoid, Function, Swap);
	Sort_VectorAscend(j+1, End, pVoid, Function, Swap);
}
//------------------------------------------------------------------//
//내리기
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPairPVector<ID, TYPE>::Sort_VectorDescend(int Start, int End, CTPairPVector<ID, TYPE>* pVoid, __int64 (*Function)(CTPairPVector<ID, TYPE>* pVoid, int nArray), void (*Swap)(CTPairPVector<ID, TYPE>* pVoid, int nSwap1, int nSwap2))
{
	if(Start>End) return;
	int i=Start+1;
	int j=End;
	__int64 Value=0;
	__int64 pivot=Function(pVoid, Start);
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
	Sort_VectorDescend(Start, j-1, pVoid, Function, Swap);
	Sort_VectorDescend(j+1, End, pVoid, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//

#pragma warning(default : 4786)
#endif














