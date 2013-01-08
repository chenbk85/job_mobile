#ifndef __CTVECTOR_H__
#define __CTVECTOR_H__

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000

#pragma warning(disable : 4786)



#include <list>
#include <vector>
#include <map>
using namespace std;


template <typename TYPE>
class CTVector : public vector<TYPE>
{
public:
	vector<TYPE>::iterator m_vtIterater;
	vector<TYPE>::reverse_iterator m_vtRIterater;
public:
	CTVector(void){ InitTVector(); }
	virtual ~CTVector(void){ FreeTVector(); }
	void InitTVector(void){}
	void FreeTVector(void){ DelVector(); }
	int OvernArray(int nArray){ return max(0, nArray-((int)size()-1)); }
	bool IsUsableArray(int nArray){ return ((0<=nArray)&&((int)size()>nArray)); }
	bool IsEmpty(void){ return (bool)empty(); }
	vector<TYPE>* GetVectorPtr(void){ return (static_cast<vector<TYPE>*>(this)); }
public:
	bool CreateVector(int nArray);
	bool CreateVector(int nArray, TYPE Type);
	bool AddOverVector(int nArray, TYPE Type);
	bool AddOverVector(int nArray, TYPE** ppType);
	void AddDelVector(int nCount);
	void AddDelVector(int nCount, TYPE Type);
	int AddVector(void);
	int AddVector(TYPE Type);
	int AddVector(TYPE** ppType);
	int AddVector(TYPE Type, TYPE** ppType);
	int AddFrontVector(void);
	int AddFrontVector(TYPE Type);
	int AddFrontVector(TYPE** ppType);
	int AddFrontVector(TYPE Type, TYPE** ppType);
	int AddVector(vector<TYPE>* pvVecter);
	int AddVector(vector<TYPE>* pvVecter, int BeginnArray, int EndnArray);
	int AddVector(CTVector* pcVecter);
	int AddVector(CTVector* pcVecter, int BeginnArray, int EndnArray);
	int SetVector(vector<TYPE>* pvVecter);
	int SetVector(vector<TYPE>* pvVecter, int BeginnArray, int EndnArray);
	int SetVector(CTVector* pcVecter);
	int SetVector(CTVector* pcVecter, int BeginnArray, int EndnArray);
	int FindBeginAddVector(TYPE Type);
	int FindBeginAddVector(TYPE Type, TYPE** ppType);
	int FindEndAddVector(TYPE Type);
	int FindEndAddVector(TYPE Type, TYPE** ppType);
	bool InsertVector(int nArray, TYPE Type);
	bool InsertVector(int nArray, TYPE Type, TYPE** ppType);
	bool ChangeVector(int nArray, TYPE Type);
	bool IncreaseVector(int nArray, TYPE Type);
	bool DecreaseVector(int nArray, TYPE Type);
	int FindBeginChangeVector(TYPE Type, TYPE Type_Change);
	int FindBeginChangeVector(TYPE Type, TYPE Type_Change, TYPE** ppType);
	int FindEndChangeVector(TYPE Type, TYPE Type_Change);
	int FindEndChangeVector(TYPE Type, TYPE Type_Change, TYPE** ppType);
	int FindBeginChangeAddVector(TYPE Type, TYPE Type_Change);
	int FindBeginChangeAddVector(TYPE Type, TYPE Type_Change, TYPE** ppType);
	int FindEndChangeAddVector(TYPE Type, TYPE Type_Change);
	int FindEndChangeAddVector(TYPE Type, TYPE Type_Change, TYPE** ppType);
	bool SwapVector(int nArray1, int nArray2);
	bool MoveVector(int nArray1, int nArray2);
	bool MoveBeginVector(int nArray);
	bool MoveEndVector(int nArray);
	int CountVector(TYPE Type);
	int FindBeginVector(TYPE Type);
	int FindBeginVector(TYPE Type, TYPE** ppType);
	int FindEndVector(TYPE Type);
	int FindEndVector(TYPE Type, TYPE** ppType);
	int FindBeginCompareVector(TYPE Type);
	int FindBeginCompareVector(TYPE Type, TYPE** ppType);
	int FindEndCompareVector(TYPE Type);
	int FindEndCompareVector(TYPE Type, TYPE** ppType);
	int FindBeginDelVector(TYPE Type);
	int FindEndDelVector(TYPE Type);
	bool DelVector(int nBeginArray, int nEndArray);
	bool DelVector(int nArray);
	bool DelBeginVector(void);
	bool DelEndVector(void);
	void DelVector(void);
	int TotalVector(void);
public:
	bool GetVector(int nArray, TYPE &Type);
	bool GetVectorPtr(int nArray, TYPE** ppType);
	bool GetBeginVector(TYPE &Type);
	bool GetBeginVectorPtr(TYPE** ppType);
	bool GetEndVector(TYPE &Type);
	bool GetEndVectorPtr(TYPE** ppType);
public:
	bool CurVector(int nArray);
	bool CurVector(int nArray, TYPE &Type);
	bool CurVector(int nArray, TYPE** ppType);
	bool BeginVector(void);
	bool BeginToEndVector(void);
	bool BeginToNext(void);
	bool BeginToNext(TYPE &Type);
	bool BeginToNext(TYPE** ppType);
	bool BeginToCur(TYPE &Type);
	bool BeginToCur(TYPE** ppType);
	bool CurToPrev(TYPE &Type);
	bool CurToPrev(TYPE** ppType);
	bool CurToNext(TYPE &Type);
	bool CurToNext(TYPE** ppType);
	bool EndVector(void);
	bool EndToBeginVector(void);
	bool EndToPrev(void);
	bool EndToPrev(TYPE &Type);
	bool EndToPrev(TYPE** ppType);
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
	virtual int CompareVector(TYPE Type1, TYPE Type2);
public:
	void SortVector(bool (*CompareFunc)(const TYPE Type1, const TYPE Type2));
	void Sort_VectorAscend(void);
	void Sort_VectorDescend(void);
	void Sort_VectorAscend(int Start, int End);
	void Sort_VectorDescend(int Start, int End);
	void Sort_VectorAscend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, CTVector<TYPE>* pVoid, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, CTVector<TYPE>* pVoid, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2));
public:
	friend __int64 GetVector_Sort(CTVector<TYPE>* pVoid, int nArray);
	friend void SwapVector_Sort(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2);
};
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
__int64 GetVector_Sort(CTVector<TYPE>* pVoid, int nArray)
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)(pVoid);
	if(NULL==pctVector) return 0;
	return pctVector->GetVectorToInt(nArray);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void SwapVector_Sort(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2)
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)(pVoid);
	if(NULL==pctVector) return;
	pctVector->SwapVector(nSwap1, nSwap2);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CreateVector(int nArray)
{
	if(0>=nArray) return false;
	clear();
	TYPE Type;
	for(int i=0; i<nArray; i++){
		push_back(Type);
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CreateVector(int nArray, TYPE Type)
{
	if(0>=nArray) return false;
	clear();
	for(int i=0; i<nArray; i++){
		push_back(Type);
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::AddOverVector(int nArray, TYPE Type)
{
	if(true==IsUsableArray(nArray)){
		return ChangeVector(nArray, Type);
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	for(int i=0; i<OverValue; i++){
		push_back(Type);
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::AddOverVector(int nArray, TYPE** ppType)
{
	if(true==IsUsableArray(nArray)){
		(*ppType)=&(*this)[nArray];
		return (NULL!=(*ppType));
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	TYPE Type;
	for(int i=0; i<OverValue; i++){
		push_back(Type);
	}
	if(NULL!=ppType){
		(*ppType)=&(*this)[nArray];
		return (NULL!=(*ppType));
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::AddDelVector(int nCount)
{
	if((int)size()==nCount) return;
	if((int)size()>nCount){
		erase(begin()+nCount, end());
	}
	else{
		TYPE Type;
		for(int i=(int)size(); i<nCount; i++){
			push_back(Type);
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::AddDelVector(int nCount, TYPE Type)
{
	if((int)size()==nCount) return;
	if((int)size()>nCount){
		erase(begin()+nCount, end());
	}
	else{
		for(int i=(int)size(); i<nCount; i++){
			push_back(Type);
		}
	}
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddVector(void)
{
	int nArray=(int)size();
	TYPE Type;
	push_back(Type);
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddVector(TYPE Type)
{
	int nArray=(int)size();
	push_back(Type);
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddVector(TYPE** ppType)
{
	int nArray=(int)size();
	TYPE Type;
	push_back(Type);
	if(NULL!=ppType) (*ppType)=&(*this)[nArray];
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddVector(TYPE Type, TYPE** ppType)
{
	int nArray=(int)size();
	push_back(Type);
	if(NULL!=ppType) (*ppType)=&(*this)[nArray];
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddFrontVector(void)
{
	TYPE Type;
	insert(begin(), Type);
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddFrontVector(TYPE Type)
{
	insert(begin(), Type);
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddFrontVector(TYPE** ppType)
{
	TYPE Type;
	insert(begin(), Type);
	if(NULL!=ppType) (*ppType)=&(*this)[0];
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddFrontVector(TYPE Type, TYPE** ppType)
{
	insert(begin(), Type);
	if(NULL!=ppType) (*ppType)=&(*this)[0];
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddVector(vector<TYPE>* pvVecter)
{
	if(NULL==pvVecter) return (int)size();
	insert(end(), pvVecter->begin(), pvVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddVector(vector<TYPE>* pvVecter, int BeginnArray, int EndnArray)
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
template <typename TYPE>
int CTVector<TYPE>::AddVector(CTVector* pcVecter)
{
	if(NULL==pcVecter) return (int)size();
	insert(end(), pcVecter->begin(), pcVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::AddVector(CTVector* pcVecter, int BeginnArray, int EndnArray)
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
template <typename TYPE>
int CTVector<TYPE>::SetVector(vector<TYPE>* pvVecter)
{
	if(NULL==pvVecter) return (int)size();
	assign(pvVecter->begin(), pvVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::SetVector(vector<TYPE>* pvVecter, int BeginnArray, int EndnArray)
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
template <typename TYPE>
int CTVector<TYPE>::SetVector(CTVector* pcVecter)
{
	if(NULL==pcVecter) return (int)size();
	assign(pcVecter->begin(), pcVecter->end());
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::SetVector(CTVector* pcVecter, int BeginnArray, int EndnArray)
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
template <typename TYPE>
int CTVector<TYPE>::FindBeginAddVector(TYPE Type)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Type);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginAddVector(TYPE Type, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Type, ppType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndAddVector(TYPE Type)
{
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Type);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndAddVector(TYPE Type, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Type, ppType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::InsertVector(int nArray, TYPE Type)
{
	if(false==IsUsableArray(nArray)){
		if(nArray==(int)size()){
			return (0<=AddVector(Type));
		}
		return false;
	}
	insert(begin()+nArray, Type);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::InsertVector(int nArray, TYPE Type, TYPE** ppType)
{
	if(false==IsUsableArray(nArray)){
		if(nArray==(int)size()){
			return (0<=AddVector(Type, ppType));
		}
		return false;
	}
	insert(begin()+nArray, Type);
	if(NULL!=ppType){
		(*ppType)=(*this)[nArray];
		return (NULL!=(*ppType));
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::ChangeVector(int nArray, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray]=Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::IncreaseVector(int nArray, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray]=(*this)[nArray]+Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::DecreaseVector(int nArray, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*this)[nArray]=(*this)[nArray]-Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginChangeVector(TYPE Type, TYPE Type_Change)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			(*vtIterater)=Type_Change;
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginChangeVector(TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			(*vtIterater)=Type_Change;
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndChangeVector(TYPE Type, TYPE Type_Change)
{
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			(*vtRIterater)=Type_Change;
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndChangeVector(TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			(*vtRIterater)=Type_Change;
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginChangeAddVector(TYPE Type, TYPE Type_Change)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			(*vtIterater)=Type_Change;
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Type_Change);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginChangeAddVector(TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			(*vtIterater)=Type_Change;
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(vtIterater-begin());
		}
	}
	return AddVector(Type_Change, ppType);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndChangeAddVector(TYPE Type, TYPE Type_Change)
{
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			(*vtRIterater)=Type_Change;
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Type_Change);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndChangeAddVector(TYPE Type, TYPE Type_Change, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			(*vtRIterater)=Type_Change;
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(rend()-vtRIterater);
		}
	}
	return AddVector(Type_Change);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::SwapVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray1)||((int)size()<=nArray1)) return false;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	TYPE Type=(*this)[nArray1];
	(*this)[nArray1]=(*this)[nArray2];
	(*this)[nArray2]=Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::MoveVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	if(0>nArray1) return false;
	TYPE Type=(*this)[nArray2];
	//erase(&(*this)[nArray2]);
	erase(begin()+nArray2);
	if(0==nArray1){
		insert(begin(), Type);
		return true;
	}
	if((int)size()<=nArray1){
		insert(end(), Type);
		return true;
	}
	insert(begin()+nArray1, Type);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::MoveBeginVector(int nArray)
{
	if(0==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	TYPE Type=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(begin(), Type);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::MoveEndVector(int nArray)
{
	if(((int)size()-1)==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	TYPE Type=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(end(), Type);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::CountVector(TYPE Type)
{
	return (int)std::count(begin(), end(), Type);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginVector(TYPE Type)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginVector(TYPE Type, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndVector(TYPE Type)
{
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndVector(TYPE Type, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginCompareVector(TYPE Type)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(0==CompareVector(Type, (*vtIterater))){
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginCompareVector(TYPE Type, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(0==CompareVector(Type, (*vtIterater))){
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(vtIterater-begin());
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndCompareVector(TYPE Type)
{
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(0==CompareVector(Type, (*vtRIterater))){
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindEndCompareVector(TYPE Type, TYPE** ppType)
{
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(0==CompareVector(Type, (*vtRIterater))){
			vtIterater=vtRIterater.base();
			if(NULL!=ppType) (*ppType)=vtIterater._Myptr;
			return (int)(rend()-vtRIterater);
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::FindBeginDelVector(TYPE Type)
{
	int nFind=0;
	vector<TYPE>::iterator vtIterater;
	for(vtIterater=begin(); vtIterater!=end(); vtIterater++){
		if(Type==(*vtIterater)){
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
template <typename TYPE>
int CTVector<TYPE>::FindEndDelVector(TYPE Type)
{
	int nFind=0;
	vector<TYPE>::iterator vtIterater;
	vector<TYPE>::reverse_iterator vtRIterater;
	for(vtRIterater=rbegin(); vtRIterater!=rend(); vtRIterater++){
		if(Type==(*vtRIterater)){
			nFind=(int)(rend()-vtRIterater);
			vtIterater=vtRIterater.base();
			vtIterater=erase(vtIterater);
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
bool CTVector<TYPE>::DelVector(int nBeginArray, int nEndArray)
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
template <typename TYPE>
bool CTVector<TYPE>::DelVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::DelBeginVector(void)
{
	if(true==empty()) return false;
	erase(begin());
	//pop_front();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::DelEndVector(void)
{
	if(true==empty()) return false;
	//int Total=(int)size();
	//erase(&(*this)[Total-1]);
	pop_back();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::DelVector(void)
{
	clear(); 
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::TotalVector(void)
{
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::GetVector(int nArray, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Type=(*this)[nArray];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::GetVectorPtr(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*ppType)=&(*this)[nArray];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::GetBeginVector(TYPE &Type)
{
	if(true==empty()) return false;
	Type=(*begin());
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::GetBeginVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	if(NULL==ppType) return false;
	(*ppType)=&(*this)[0];
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::GetEndVector(TYPE &Type)
{
	if(true==empty()) return false;
	int Total=(int)size();
	Type=(*this)[Total-1];
	//	type=(*m_cvVector.end());
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::GetEndVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	if(NULL==ppType) return false;
	int Total=(int)size();
	(*ppType)=&(*this)[Total-1];
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CurVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CurVector(int nArray, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	Type=(*m_vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CurVector(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater._Myptr;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::BeginVector(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::BeginToEndVector(void)
{
	if(true==empty()) return false;
	m_vtIterater=end();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::BeginToNext(void)
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
template <typename TYPE>
bool CTVector<TYPE>::BeginToNext(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Type=(*m_vtIterater);
	m_vtIterater++;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::BeginToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater._Myptr;
	m_vtIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::BeginToCur(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	Type=(*m_vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::BeginToCur(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CurToPrev(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	Type=(*vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CurToPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	(*ppType)=vtIterater._Myptr;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CurToNext(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	Type=(*vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::CurToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	(*ppType)=vtIterater._Myptr;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::EndVector(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::EndToBeginVector(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rend();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::EndToPrev(void)
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
template <typename TYPE>
bool CTVector<TYPE>::EndToPrev(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	Type=(*m_vtRIterater);
	m_vtRIterater++;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::EndToPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=vtIterater._Myptr;
	m_vtRIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::EndToCur(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	Type=(*m_vtRIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::EndToCur(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::IsEndVector(void)
{
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::IsBeginVector(void)
{
	return (m_vtRIterater==rend());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorBegin(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorNext(void)
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
template <typename TYPE>
bool CTVector<TYPE>::VectorEnd(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorPrev(void)
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
template <typename TYPE>
bool CTVector<TYPE>::VectorBegin(TYPE &Type)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	Type=(*m_vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorNext(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	Type=(*m_vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorEnd(TYPE &Type)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	Type=(*m_vtRIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorPrev(TYPE &Type)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	Type=(*m_vtRIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorBegin(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	(*ppType)=m_vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorEnd(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	vector<TYPE>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorDelNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	(*ppType)=m_vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorDelPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=(++m_vtRIterater).base();
	erase(vtIterater);
	if(m_vtRIterater==rend()) return false;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=vtIterater._Myptr;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::VectorDel(void)
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
template <typename TYPE>
bool CTVector<TYPE>::IsNextEnd(void)
{
	return ((m_vtIterater+1)==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTVector<TYPE>::IsPrevBegin(void)
{
	return ((m_vtRIterater+1)==rend());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
__int64 CTVector<TYPE>::GetVectorToInt(int nArray)
{
	if(true==IsUsableArray(nArray)) return 1;
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTVector<TYPE>::CompareVector(TYPE Type1, TYPE Type2)
{
	//	if(Type1==Type2) return 0;
	//	if(Type1>Type2) return 1;
	//	if(Type1<Type2) return -1;
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::SortVector(bool (*CompareFunc)(const TYPE Type1, const TYPE Type2))
{
	std::sort(begin(), end(), CompareFunc);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorAscend(void)
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTVector<TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorDescend(void)
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTVector<TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorAscend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTVector<TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorDescend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTVector<TYPE>*)pctVector, GetVector_Sort, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorAscend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray))
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTVector<TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorDescend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray))
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTVector<TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTVector<TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTVector<TYPE>*)pctVector, Function, SwapVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorAscend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorDescend(__int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTVector<TYPE>* pctVector=(CTVector<TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 오르기
//------------------------------------------------------------------//
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorAscend(int Start, int End, CTVector<TYPE>* pVoid, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2))
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
template <typename TYPE>
void CTVector<TYPE>::Sort_VectorDescend(int Start, int End, CTVector<TYPE>* pVoid, __int64 (*Function)(CTVector<TYPE>* pVoid, int nArray), void (*Swap)(CTVector<TYPE>* pVoid, int nSwap1, int nSwap2))
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
//------------------------------------------------------------------//
//////////////////////////////////////////////////////////////////////
//------------------------------------------------------------------//
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//

template <typename TYPE>
class CTPVector : public vector<TYPE*>
{
public:
	vector<TYPE*>::iterator m_vtIterater;
	vector<TYPE*>::reverse_iterator m_vtRIterater;
public:
	CTPVector(void){ InitTPVector(); }
	virtual ~CTPVector(void){ FreeTPVector(); }
	void InitTPVector(void){}
	void FreeTPVector(void){ DelVector(); }
	int OvernArray(int nArray){ return max(0, nArray-((int)size()-1)); }
	bool IsUsableArray(int nArray){ return ((0<=nArray)&&((int)size()>nArray)); }
	bool IsEmpty(void){ return (bool)empty(); }
	vector<TYPE*>* GetVectorPtr(void){ return (static_cast<vector<TYPE*>*>(this)); }
public:
	bool CreateVector(int nArray);
	bool AddOverVector(int nArray, TYPE** ppType);
	int AddVector(void);
	int AddVector(TYPE** ppType);
	int AddFrontVector(void);
	int AddFrontVector(TYPE** ppType);
	bool InsertVector(int nArray, TYPE** ppType);
	bool ChangeVector(int nArray, TYPE Type);
	bool SwapVector(int nArray1, int nArray2);
	bool MoveVector(int nArray1, int nArray2);
	bool MoveBeginVector(int nArray);
	bool MoveEndVector(int nArray);
	int FindBeginVector(TYPE Type);
	int FindBeginVector(TYPE Type, TYPE** ppType);
	int FindEndVector(TYPE Type);
	int FindEndVector(TYPE Type, TYPE** ppType);
	int FindBeginCompareVector(TYPE Type);
	int FindBeginCompareVector(TYPE Type, TYPE** ppType);
	int FindEndCompareVector(TYPE Type);
	int FindEndCompareVector(TYPE Type, TYPE** ppType);
	int FindBeginDelVector(TYPE Type);
	int FindEndDelVector(TYPE Type);
	bool DelVector(int nBeginArray, int nEndArray);
	bool DelVector(int nArray);
	bool DelBeginVector(void);
	bool DelEndVector(void);
	void DelVector(void);
	int TotalVector(void);
public:
	bool GetVector(int nArray, TYPE &Type);
	bool GetVectorPtr(int nArray, TYPE** ppType);
	bool GetBeginVector(TYPE &Type);
	bool GetBeginVectorPtr(TYPE** ppType);
	bool GetEndVector(TYPE &Type);
	bool GetEndVectorPtr(TYPE** ppType);
public:
	bool CurVector(int nArray);
	bool CurVector(int nArray, TYPE** ppType);
	bool BeginVector(void);
	bool BeginToNext(TYPE** ppType);
	bool BeginToCur(TYPE** ppType);
	bool CurToPrev(TYPE** ppType);
	bool CurToNext(TYPE** ppType);
	bool IsEndVector(void);
public:
	int CurIterater(void){ return (int)(m_vtIterater-begin()); }
	int CurRIterater(void){ return (int)(m_vtRIterater-rbegin()); }
	int RearIterater(void){ return (int)(end()-m_vtIterater); }
	int RearRIterater(void){ return (int)(rend()-m_vtRIterater); }
	bool VectorBegin(void);
	bool VectorNext(void);
	bool VectorEnd(void);
	bool VectorPrev(void);
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
	virtual int CompareVector(const TYPE* pType1, const TYPE* pType2);
public:
	void SortVector(bool (*CompareFunc)(const TYPE* pType1, const TYPE* pType2));
	void Sort_VectorAscend(void);
	void Sort_VectorDescend(void);
	void Sort_VectorAscend(int Start, int End);
	void Sort_VectorDescend(int Start, int End);
	void Sort_VectorAscend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray));
	void Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray));
	void Sort_VectorAscend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorAscend(int Start, int End, CTPVector<TYPE>* pVoid, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2));
	void Sort_VectorDescend(int Start, int End, CTPVector<TYPE>* pVoid, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2));
public:
	friend __int64 GetPVector_Sort(void* pVoid, int nArray);
	friend void SwapPVector_Sort(void* pVoid, int nSwap1, int nSwap2);
};
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
__int64 GetPVector_Sort(CTPVector<TYPE>* pVoid, int nArray)
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)pVoid;
	if(NULL==pctVector) return 0;
	return pctVector->GetVectorToInt(nArray);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void SwapPVector_Sort(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2)
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)pVoid;
	if(NULL==pctVector) return;
	pctVector->SwapVector(nSwap1, nSwap2);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::CreateVector(int nArray)
{
	if(0>=nArray) return false;
	DelVector();
	for(int i=0; i<nArray; i++){
		TYPE* pType=new TYPE;
		if(NULL==pType) return false;
		push_back(pType);
	}
	return (nArray==(int)size());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::AddOverVector(int nArray, TYPE** ppType)
{
	if(true==IsUsableArray(nArray)){
		if(NULL!=ppType){
			(*ppType)=(*this)[nArray];
			return (NULL!=(*ppType));
		}
		return true;
	}
	int OverValue=OvernArray(nArray);
	if(0>=OverValue) return false;
	for(int i=0; i<OverValue; i++){
		TYPE* pType=new TYPE;
		if(NULL==pType) return false;
		push_back(pType);
	}
	if(NULL!=ppType) (*ppType)=(*this)[nArray];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::AddVector(void)
{
	int nArray=(int)size();
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	push_back(pType);
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::AddVector(TYPE** ppType)
{
	int nArray=(int)size();
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	push_back(pType);
	if(NULL!=ppType) (*ppType)=(*this)[nArray];
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::AddFrontVector(void)
{
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	insert(begin(), pType);
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::AddFrontVector(TYPE** ppType)
{
	TYPE* pType=new TYPE;
	if(NULL==pType) return -1;
	insert(begin(), pType);
	if(NULL!=ppType) (*ppType)=(*this)[0];
	int nArray=(int)size();
	return nArray;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::InsertVector(int nArray, TYPE** ppType)
{
	if(false==IsUsableArray(nArray)){
		if(nArray==(int)size()){
			return (0<=AddVector(ppType));
		}
		return false;
	}
	if(NULL==ppType) return false;
	TYPE* pType=new TYPE;
	if(NULL==pType) return false;
	insert(begin()+nArray, pType);
	if(NULL!=ppType){
		(*ppType)=(*this)[nArray];
		return (NULL!=(*ppType));
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::ChangeVector(int nArray, TYPE Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	//	TYPE* pType=new TYPE;
	//	if(NULL==pType) return false;
	//	(*pType)=Type;
	//	if(NULL!=(*this)[nArray]){
	//		TYPE** ppType=(&(*this)[nArray]);
	//		delete (*ppType);
	//		(*ppType)=NULL;
	//	}
	//	(*this)[nArray]=pType;
	(*(*this)[nArray])=Type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::SwapVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray1)||((int)size()<=nArray1)) return false;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	TYPE* pType=(*this)[nArray1];
	(*this)[nArray1]=(*this)[nArray2];
	(*this)[nArray2]=pType;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::MoveVector(int nArray1, int nArray2)
{
	if(nArray1==nArray2) return true;
	if((0>nArray2)||((int)size()<=nArray2)) return false;
	if(0>nArray1) return false;
	TYPE* pType=(*this)[nArray2];
	//erase(&(*this)[nArray2]);
	erase(begin()+nArray2);
	if(0==nArray1){
		insert(begin(), pType);
		return true;
	}
	if((int)size()<=nArray1){
		insert(end(), pType);
		return true;
	}
	insert(begin()+nArray1, pType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::MoveBeginVector(int nArray)
{
	if(0==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	TYPE* pType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(begin(), pType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::MoveEndVector(int nArray)
{
	if(((int)size()-1)==nArray) return true;
	if((0>nArray)||((int)size()<=nArray)) return false;
	TYPE* pType=(*this)[nArray];
	//erase(&(*this)[nArray]);
	erase(begin()+nArray);
	insert(end(), pType);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindBeginVector(TYPE Type)
{
	int Total=(int)size();
	for(int i=0; i<Total; i++){
		if(Type==(*(*this)[i])){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindBeginVector(TYPE Type, TYPE** ppType)
{
	int Total=(int)size();
	for(int i=0; i<Total; i++){
		if(Type==(*(*this)[i])){
			(*ppType)=(*this)[i];
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindEndVector(TYPE Type)
{
	int Total=(int)size();
	for(int i=Total-1; i>=0; i--){
		if(Type==(*(*this)[i])){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindEndVector(TYPE Type, TYPE** ppType)
{
	int Total=(int)size();
	for(int i=Total-1; i>=0; i--){
		if(Type==(*(*this)[i])){
			(*ppType)=(*this)[i];
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindBeginCompareVector(TYPE Type)
{
	int Total=(int)size();
	for(int i=0; i<Total; i++){
		if(0==CompareVector(&Type, (*this)[i])){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindBeginCompareVector(TYPE Type, TYPE** ppType)
{
	int Total=(int)size();
	for(int i=0; i<Total; i++){
		if(0==CompareVector(&Type, (*this)[i])){
			(*ppType)=(*this)[i];
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindEndCompareVector(TYPE Type)
{
	int Total=(int)size();
	for(int i=Total-1; i>=0; i--){
		if(0==CompareVector(&Type, (*this)[i])){
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindEndCompareVector(TYPE Type, TYPE** ppType)
{
	int Total=(int)size();
	for(int i=Total-1; i>=0; i--){
		if(0==CompareVector(&Type, (*this)[i])){
			(*ppType)=(*this)[i];
			return i;
		}
	}
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::FindBeginDelVector(TYPE Type)
{
	int Total=(int)size();
	for(int i=0; i<Total; i++){
		if(Type==(*(*this)[i])){
			if(NULL!=(*this)[i]){
				TYPE** ppType=(&(*this)[i]);
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
template <typename TYPE>
int CTPVector<TYPE>::FindEndDelVector(TYPE Type)
{
	int Total=(int)size();
	for(int i=Total-1; i>=0; i--){
		if(Type==(*(*this)[i])){
			if(NULL!=(*this)[i]){
				TYPE** ppType=(&(*this)[i]);
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
template <typename TYPE>
bool CTPVector<TYPE>::DelVector(int nBeginArray, int nEndArray)
{
	int nBegin=max(0, nBeginArray);
	int nEnd=min(nEndArray+1, (int)size());
	if(nBegin>(nEnd-1)) return false;
	if(nBegin==(nEnd-1)){
		if(NULL!=(*this)[nBegin]){
			TYPE** ppType=(&(*this)[nBegin]);
			delete (*ppType);
			(*ppType)=NULL;
		}
		//erase(&(*this)[nBegin]);
		erase(begin()+nBegin);
		return true;
	}
	for(int i=nBegin; i<nEnd; i++){
		if(NULL!=(*this)[i]){
			TYPE** ppType=(&(*this)[i]);
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
template <typename TYPE>
bool CTPVector<TYPE>::DelVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	if(NULL!=(*this)[nArray]){
		TYPE** ppType=(&(*this)[nArray]);
		delete (*ppType);
		(*ppType)=NULL;
	}
	erase(begin()+nArray);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::DelBeginVector(void)
{
	if(true==empty()) return false;
	if(NULL!=(*this)[0]){
		TYPE** ppType=(&(*this)[0]);
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
template <typename TYPE>
bool CTPVector<TYPE>::DelEndVector(void)
{
	if(true==empty()) return false;
	int Total=(int)size();
	if(NULL!=(*this)[Total-1]){
		TYPE** ppType=(&(*this)[Total-1]);
		delete (*ppType);
		(*ppType)=NULL;
	}
	//erase(&(*this)[Total-1]);
	pop_back();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::DelVector(void)
{
	int Size=(int)size();
	for(int i=0; i<Size; i++){
		if(NULL!=(*this)[i]){
			TYPE** ppType=(&(*this)[i]);
			delete (*ppType);
			(*ppType)=NULL;
		}
	}
	clear(); 
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::TotalVector(void)
{
	return (int)size();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::GetVector(int nArray, TYPE &Type)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	Type=*(*this)[nArray];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::GetVectorPtr(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	(*ppType)=(*this)[nArray];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::GetBeginVector(TYPE &Type)
{
	if(true==empty()) return false;
	Type=*(*this)[0];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::GetBeginVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	(*ppType)=(*this)[0];
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::GetEndVector(TYPE &Type)
{
	if(true==empty()) return false;
	int Total=(int)size();
	Type=*(*this)[Total-1];
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::GetEndVectorPtr(TYPE** ppType)
{
	if(true==empty()) return false;
	int Total=(int)size();
	(*ppType)=(*this)[Total-1];
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::CurVector(int nArray)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::CurVector(int nArray, TYPE** ppType)
{
	if((0>nArray)||((int)size()<=nArray)) return false;
	m_vtIterater=(begin()+nArray);
	if(m_vtIterater==end()) return false;
	(*ppType)=(*m_vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::BeginVector(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::BeginToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=(*m_vtIterater);
	m_vtIterater++;
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::BeginToCur(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	(*ppType)=(*m_vtIterater);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::CurToPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==begin()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=m_vtIterater-1;
	(*ppType)=(*vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::CurToNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	vector<TYPE>::iterator vtIterater;
	vtIterater=m_vtIterater+1;
	if(vtIterater==end()) return false;
	(*ppType)=(*vtIterater);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::IsEndVector(void)
{
	return (m_vtIterater==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorBegin(void)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorNext(void)
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
template <typename TYPE>
bool CTPVector<TYPE>::VectorEnd(void)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorPrev(void)
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
template <typename TYPE>
bool CTPVector<TYPE>::VectorBegin(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtIterater=begin();
	(*ppType)=(*m_vtIterater);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	m_vtIterater++;
	if(m_vtIterater==end()) return false;
	(*ppType)=(*m_vtIterater);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorEnd(TYPE** ppType)
{
	if(true==empty()) return false;
	m_vtRIterater=rbegin();
	vector<TYPE*>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=(*vtIterater);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	m_vtRIterater++;
	if(m_vtRIterater==rend()) return false;
	vector<TYPE*>::iterator vtIterater;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=(*vtIterater);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorDelNext(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	TYPE* pType=NULL;
	pType=(*m_vtIterater);
	if(NULL!=pType){
		delete pType;
		pType=NULL;
	}
	m_vtIterater=erase(m_vtIterater);
	if(m_vtIterater==end()) return false;
	(*ppType)=(*m_vtIterater);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorDelPrev(TYPE** ppType)
{
	if(true==empty()) return false;
	if(m_vtRIterater==rend()) return false;
	vector<TYPE*>::iterator vtIterater;
	vtIterater=(++m_vtRIterater).base();
	TYPE* pType=NULL;
	pType=(*vtIterater);
	if(NULL!=pType){
		delete pType;
		pType=NULL;
	}
	erase(vtIterater);
	if(m_vtRIterater==rend()) return false;
	vtIterater=(--m_vtRIterater.base());
	(*ppType)=(*vtIterater);
	return (NULL!=(*ppType));
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::VectorDel(void)
{
	if(true==empty()) return false;
	if(m_vtIterater==end()) return false;
	TYPE* pType=NULL;
	pType=(*m_vtIterater);
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
template <typename TYPE>
bool CTPVector<TYPE>::IsNextEnd(void)
{
	return ((m_vtIterater+1)==end());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
bool CTPVector<TYPE>::IsPrevBegin(void)
{
	return ((m_vtRIterater+1)==rend());
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
__int64 CTPVector<TYPE>::GetVectorToInt(int nArray)
{
	if(true==IsUsableArray(nArray)) return (int)(DWORD_PTR)(*this)[nArray];
	return -1;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
int CTPVector<TYPE>::CompareVector(const TYPE* pType1, const TYPE* pType2)
{
	//if(Type1==Type2) return 0;
	//if(Type1>Type2) return 1;
	//if(Type1<Type2) return -1;
	return 0;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::SortVector(bool (*CompareFunc)(const TYPE* pType1, const TYPE* pType2))
{
	std::sort(begin(), end(), CompareFunc);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorAscend(void)
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPVector<TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorDescend(void)
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPVector<TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorAscend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPVector<TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorDescend(int Start, int End)
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPVector<TYPE>*)pctVector, GetPVector_Sort, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorAscend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray))
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPVector<TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorDescend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray))
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPVector<TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPVector<TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPVector<TYPE>*)pctVector, Function, SwapPVector_Sort);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorAscend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorAscend(0, (int)(size()-1), (CTPVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorDescend(__int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorDescend(0, (int)(size()-1), (CTPVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorAscend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorAscend(Start, End, (CTPVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorDescend(int Start, int End, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2))
{
	End=min((int)size()-1, End);
	if(Start>End) return;
	CTPVector<TYPE>* pctVector=(CTPVector<TYPE>*)this;
	Sort_VectorDescend(Start, End, (CTPVector<TYPE>*)pctVector, Function, Swap);
}
//------------------------------------------------------------------//
// 오르기
//------------------------------------------------------------------//
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorAscend(int Start, int End, CTPVector<TYPE>* pVoid, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2))
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
template <typename TYPE>
void CTPVector<TYPE>::Sort_VectorDescend(int Start, int End, CTPVector<TYPE>* pVoid, __int64 (*Function)(CTPVector<TYPE>* pVoid, int nArray), void (*Swap)(CTPVector<TYPE>* pVoid, int nSwap1, int nSwap2))
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















