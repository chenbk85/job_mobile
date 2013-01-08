#ifndef __CTMAP_H__
#define __CTMAP_H__

#if _MSC_VER>1000
#pragma once
#endif // _MSC_VER>1000


#pragma warning(disable : 4786)

#include <list>
#include <vector>
#include <map>
using namespace std;


template <typename ID, typename TYPE>
class CTMap : public map<ID, TYPE>
{
protected:
	typedef pair<ID, TYPE>  m_Pair;
public:
	int GetMapTotal(void){ return (int)size(); }
	bool IsEmptyMap(void)  { return empty(); }
public:
	CTMap(void);
	CTMap(CTMap &cTMap);
	virtual ~CTMap(void);
	CTMap &operator=(CTMap &cTMap);
	void InitTMap(void);
	void FreeTMap(void);
	bool Error(bool result, LPCTSTR error, LPCTSTR szBuffer, int line);
	bool CalcUsableArray(int FirstArra, int EndArray, int UsableArray);
public:
	bool AddMap(ID Mapid);
	bool AddMap(ID Mapid, TYPE type);
	bool AddFindMap(ID Mapid, TYPE type);
	bool AddMap(CTMap* pcTMap);
	bool ChangeMap(ID Mapid, TYPE type);
	bool SwapMap(ID Mapid, ID Swapid);
	bool FindMap(ID Mapid);
	bool DeleteMap(ID Mapid);
	bool DeleteMap(void);
	bool GetMap(ID Mapid, TYPE &type);
	bool GetMapPtr(ID Mapid, TYPE** pptype);
};


//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTMap<ID, TYPE>::CTMap(void)
{
	InitTMap();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTMap<ID, TYPE>::CTMap(CTMap &cTMap)
{
	InitTMap();
	(this*)=cTMap;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTMap<ID, TYPE>::~CTMap(void)
{
	FreeTMap();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTMap<ID, TYPE> &CTMap<ID, TYPE>::operator=(CTMap &cTMap)
{
	FreeTMap();
	(this*)=cTMap;
	return (*this);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTMap<ID, TYPE>::InitTMap(void)
{
	DeleteMap();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTMap<ID, TYPE>::FreeTMap(void)
{
	DeleteMap();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::Error(bool result, LPCTSTR error, LPCTSTR szBuffer, int line)
{
#ifdef _DEBUG
	char szTemp[128]={0,};
	sprintf(szTemp, " Error : %s(%d)", szBuffer, line);
	OutputDebugString(error);
	OutputDebugString(szTemp);
	OutputDebugString("\n");
#endif
	return result;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::CalcUsableArray(int FirstArra, int EndArray, int UsableArray)
{
	if(FirstArra>EndArray) return false;
	if((FirstArra<=UsableArray)&&(EndArray>=UsableArray)) return true;
	return false;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::AddMap(ID Mapid)
{
	pair<map<ID, TYPE>::iterator, bool>pr;
	TYPE type;
	pr=insert(m_Pair(Mapid, type));
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::AddMap(ID Mapid, TYPE type)
{
	pair<map<ID, TYPE>::iterator, bool>pr;
	pr=insert(m_Pair(Mapid, type));
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::AddFindMap(ID Mapid, TYPE type)
{
	if(true==FindMap(Mapid)) return false;
	pair<map<ID, TYPE>::iterator, bool>pr;
	pr=insert(m_Pair(Mapid, type));
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::AddMap(CTMap* pcTMap)
{
	if(NULL==pcTMap) return false;
	insert(pcTMap->begin(), pcTMap->end());
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::ChangeMap(ID Mapid, TYPE type)
{
	map<ID, TYPE>::iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	map_interator->second=type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::SwapMap(ID Mapid, ID Swapid)
{
	map<ID, TYPE>::iterator mapid_interator=find(Mapid);
	if(mapid_interator==end()){
		return false;
	}
	map<ID, TYPE>::iterator Swapid_interator=find(Swapid);
	if(Swapid_interator==end()){
		return false;
	}
	TYPE type=mapid_interator->second;
	mapid_interator->second=Swapid_interator->second;
	Swapid_interator->second=type;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::FindMap(ID Mapid)
{
	map<ID, TYPE>::const_iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::DeleteMap(ID Mapid)
{
	map<ID, TYPE>::iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	erase(map_interator);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::DeleteMap(void)
{
	clear();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::GetMap(ID Mapid, TYPE &type)
{
	map<ID, TYPE>::iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	type=map_interator->second;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTMap<ID, TYPE>::GetMapPtr(ID Mapid, TYPE** pptype)
{
	map<ID, TYPE>::iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	if(NULL!=map_interator->second){
		(*pptype)=(&map_interator->second);
		return true;
	}
	return false;
}




template <typename ID, typename TYPE>
class CTPMap : public map<ID, TYPE*>
{
protected:
	typedef pair<ID, TYPE*> m_Pair;
public:
	int GetMapTotal(void){ return (int)size(); }
	bool IsEmptyMap(void)  { return empty(); }
public:
	CTPMap(void);
	CTPMap(CTPMap &cTPMap);
	virtual ~CTPMap(void);
	CTPMap &operator=(CTPMap &cTPMap);
	void InitTMapPtrCtrl(void);
	void FreeTMapPtrCtrl(void);
	bool Error(bool result, LPCTSTR error, LPCTSTR szBuffer, int line);
	bool CalcUsableArray(int FirstArra, int EndArray, int UsableArray);
public:
	bool AddMap(ID Mapid);
	bool AddMap(ID Mapid, TYPE* ptype);
	bool AddMap(ID Mapid, TYPE** pptype);
	bool AddFindMap(ID Mapid, TYPE* ptype);
	bool AddFindMap(ID Mapid, TYPE** pptype);
	bool AddMap(CTPMap* pcTPMap);
	bool ChangeMap(ID Mapid, TYPE* ptype);
	bool SwapMap(ID Mapid, ID Swapid);
	bool FindMap(ID Mapid);
	bool DeleteMap(ID Mapid);
	bool DeleteMap(void);
	bool GetMapPtr(ID Mapid, TYPE** pptype);
};

//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTPMap<ID, TYPE>::CTPMap(void)
{
	InitTMapPtrCtrl();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTPMap<ID, TYPE>::CTPMap(CTPMap &cTPMap)
{
	InitTMapPtrCtrl();
	(*this)=cTPMap.GetMap();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTPMap<ID, TYPE>::~CTPMap(void)
{
	FreeTMapPtrCtrl();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
CTPMap<ID, TYPE> &CTPMap<ID, TYPE>::operator=(CTPMap &cTPMap)
{
	FreeTMapPtrCtrl();
	(*this)=cTPMap;
	return (*this);
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPMap<ID, TYPE>::InitTMapPtrCtrl(void)
{
	DeleteMap();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
void CTPMap<ID, TYPE>::FreeTMapPtrCtrl(void)
{
	DeleteMap();
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::Error(bool result, LPCTSTR error, LPCTSTR szBuffer, int line)
{
#ifdef _DEBUG
	char szTemp[128]={0,};
	sprintf(szTemp, " Error : %s(%d)", szBuffer, line);
	OutputDebugString(error);
	OutputDebugString(szTemp);
	OutputDebugString("\n");
#endif
	return result;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::CalcUsableArray(int FirstArra, int EndArray, int UsableArray)
{
	if(FirstArra>EndArray) return false;
	if((FirstArra<=UsableArray)&&(EndArray>=UsableArray)) return true;
	return false;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::AddMap(ID Mapid)
{
	pair<map<ID, TYPE*>::iterator, bool> pr;
	TYPE* pTemptype=new TYPE;
	if(NULL==pTemptype) return -1;
	pr=insert(m_Pair(Mapid, pTemptype));
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::AddMap(ID Mapid, TYPE* ptype)
{
	pair<map<ID, TYPE*>::iterator, bool> pr;
	TYPE* pTemptype=new TYPE;
	if(NULL==pTemptype) return -1;
	(*pTemptype)=(*ptype);
	pr=insert(m_Pair(Mapid, pTemptype));
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::AddMap(ID Mapid, TYPE** pptype)
{
	pair<map<ID, TYPE*>::iterator, bool> pr;
	TYPE* pTemptype=new TYPE;
	if(NULL==pTemptype) return -1;
	pr=insert(m_Pair(Mapid, pTemptype));
	(*pptype)=pTemptype;
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::AddFindMap(ID Mapid, TYPE* ptype)
{
	if(true==FindMap(Mapid)) return false;
	pair<map<ID, TYPE*>::iterator, bool> pr;
	TYPE* pTemptype=new TYPE;
	if(NULL==pTemptype) return -1;
	(*pTemptype)=(*ptype);
	pr=insert(m_Pair(Mapid, pTemptype));
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::AddFindMap(ID Mapid, TYPE** pptype)
{
	if(true==FindMap(Mapid)) return false;
	pair<map<ID, TYPE*>::iterator, bool> pr;
	TYPE* pTemptype=new TYPE;
	if(NULL==pTemptype) return -1;
	pr=insert(m_Pair(Mapid, pTemptype));
	(*pptype)=pTemptype;
	return pr.second;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::AddMap(CTPMap* pcTPMap)
{
	if(NULL==pcTPMap) return false;
	map<ID, TYPE*>::iterator map_interator;
	for(map_interator=pcTPMap->begin(); map_interator!=pcTPMap->end(); map_interator++){
		AddMap(map_interator->first, map_interator->second);
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::ChangeMap(ID Mapid, TYPE* ptype)
{
	TYPE* pTemptype=new TYPE;
	if(NULL==pTemptype) return false;
	(*pTemptype)=(*ptype);
	map<ID, TYPE*>::iterator map_interator=find(id);
	if(map_interator==end()){
		return false;
	}
	if(NULL!=map_interator->second){
		TYPE** pptype=(&map_interator->second);
		delete (*pptype);
		(*pptype)=NULL;
	}
	map_interator->second=pTemptype;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::SwapMap(ID Mapid, ID Swapid)
{
	map<ID, TYPE>::iterator mapid_interator=find(Mapid);
	if(mapid_interator==end()){
		return false;
	}
	map<ID, TYPE>::iterator Swapid_interator=find(Swapid);
	if(Swapid_interator==end()){
		return false;
	}
	TYPE* ptype=mapid_interator->second;
	mapid_interator->second=Swapid_interator->second;
	Swapid_interator->second=ptype;
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::FindMap(ID Mapid)
{
	map<ID, TYPE*>::const_iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::DeleteMap(ID Mapid)
{
	map<ID, TYPE*>::iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	if(NULL!=map_interator->second){
		TYPE** pptype=(&map_interator->second);
		delete (*pptype);
		(*pptype)=NULL;
	}
	erase(map_interator);
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::DeleteMap(void)
{
	map<ID, TYPE*>::iterator map_interator;
	for(map_interator=begin(); map_interator!=end(); map_interator++){
		if(NULL!=map_interator->second){
			TYPE** pptype=(&map_interator->second);
			delete (*pptype);
			(*pptype)=NULL;
		}
	}
	clear();
	return true;
}
//------------------------------------------------------------------//
// 
//------------------------------------------------------------------//
template <typename ID, typename TYPE>
bool CTPMap<ID, TYPE>::GetMapPtr(ID Mapid, TYPE** pptype)
{
	map<ID, TYPE*>::iterator map_interator=find(Mapid);
	if(map_interator==end()){
		return false;
	}
	(*pptype)=(map_interator->second);
	return true;
}


#pragma warning(default : 4786)
#endif
