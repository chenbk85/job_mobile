//
// XTMPL.h
//

#ifndef XTMPL_H
#define XTMPL_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

#ifdef MIN
#undef MIN
#endif

#ifdef MAX
#undef MAX
#endif

#pragma warning( push, 3 )
#pragma warning(disable:4702)
#include <vector>
#include <deque>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <valarray>
#include <algorithm>
#include <functional>
#include <cmath>
#include <cstdarg>
#include <utility>
#include <string>
#pragma warning( pop )

using namespace std;

template<typename T> inline void SWAP(T& a, T& b) { T c = a; a = b; b = c; }
template<typename T> inline T MIN(const T& a, const T& b) { return((a<b) ? a:b); }
template<typename T> inline T MAX(const T& a, const T& b) { return((a<b) ? b:a); }

// Do not use ForEachElmt to vector, deque, string. See Effective STL Item 9
#define ForEachFromTo(_IT, i, from, to) \
	for(_IT i = (from); ((i) != (to)); ++i)
#define ForEach(T, l, i) \
	ForEachFromTo(T::iterator, i, (l).begin(), (l).end())
#define ForCEach(T, l, i) \
	ForEachFromTo(T::const_iterator, i, (l).begin(), (l).end())
#define ForNext(i) (++(i))
#define ForEraseNext(l,i) ((i) = (l).erase(i))

#define ForEachElmtFromTo(_IT, i, j, from, to) \
	for(_IT i, j = (from); ((((i) = (j)) == (to)) ? 0 : (++(j), 1)); )

#define ForEachElmt(T, l, i, j) \
	ForEachElmtFromTo(T::iterator, i, j, (l).begin(), (l).end())

#define ForEachCElmt(_T, l, i, j) \
	ForEachElmtFromTo(_T::const_iterator, i, j, (l).begin(), (l).end())

#define ForEachElmtRvs(_T, l, i, j) \
	ForEachElmtFromTo(_T::reverse_iterator, i, j, (l).rbegin(), (l).rend())

#define ForEachCElmtRvs(_T, l, i, j) \
	ForEachCElmtFromTo(_T::const_reverse_iterator, i, j, (l).rbegin(), (l).rend())

///////////////////////////////////////////////////////////////////////////////
// template functions

template<class T, class Fn>
Fn for_each(T& t, Fn fn) 
{
	return for_each(t.begin(), t.end(), fn);
}

template<class It, class T> inline
It binary_find(It f, It l, const T& t)
{
	It i = lower_bound(f, l, t);
	return( ((i != l) && !(t < *i)) ? i : l); 
}

template<class It, class T, class Pred> inline
It binary_find(It f, It l, const T& t, Pred p)
{
	It i = lower_bound(f, l, t, p);
	return( ((i != l) && !p(t,*i)) ? i : l); 
}

///////////////////////////////////////////////////////////////////////////////
// ARRAY

template<typename T, int nSize>
class array : public std::vector<T>
{
public:
	typedef array this_type;
	typedef std::vector<T> base_type;
public:
	array() : vector<T>(nSize) {}
	array(const array& l) { insert(begin(), l.begin(), l.end()); }
public:
	array& operator=(const array& obj) { assign(obj.begin(), obj.end()); return *this; }
	void Copy(const array& obj) { operator=(obj); }
	void Copy(const array* obj) { if(!obj) return FALSE; Copy(*obj); return TRUE; }
};

///////////////////////////////////////////////////////////////////////////////
// VECTOR

template<typename T>
class pvector : public std::vector<T*> 
{
public:
	typedef pvector this_type;
	typedef std::vector<T*> base_type;
	typedef std::vector<T*>::iterator iterator;
public:
	pvector() {}
	virtual ~pvector() { clear(); }
	bool isexist(const T* t) const { return (find(t) != end()); }
	int count(T* t) const {	return count(begin(), end(), t); }

	iterator find(const T* t) { return std::find(begin(), end(), t); }
	const_iterator find(const T* t) const { return std::find(begin(), end(), t); }
	void remove(const T* t) {
		iterator i;
		while( (i = find(t)) != end() ) erase(i);
	}
	void flush() {
		for(unsigned i = 0; i < size(); i++) {
			T* p = at(i);
			delete(p);
		}
		clear();
	}
};

///////////////////////////////////////////////////////////////////////////////
// LIST

template<class T>
class plist : public std::list<T*>
{
public:
	typedef plist this_type;
	typedef std::list<T*> base_type;
	typedef std::list<T*>::iterator iterator;
public:
	plist() {}
	virtual ~plist() { clear(); }
	bool isexist(const T* t) const { return (find(t) != end());	}
	int count(T* t) const { return std::count(begin(), end(), t); }
	void flush() { 
		while(!empty()) {
			T* p = front();
			delete(p);
			pop_front();
		}
	}
	void copy(const plist<T>& l) {
		if( this == &l ) return;
		assign(l.begin(), l.end());
	}
	void copy(const plist<T>* l) {
		if( this == l ) return;
		assign(l->begin(), l->end());
	}
	iterator find(T* d) {	return std::find(begin(), end(), d); }
	const_iterator find(const T* d) const {	return std::find(begin(), end(), d); }
};

///////////////////////////////////////////////////////////////////////////////
// pdeque

template<class T>
class pdeque : public std::deque<T*>
{
public:
	typedef pdeque this_type;
	typedef std::deque<T*> base;
	typedef std::deque<T*>::iterator iterator;

public:
	pdeque() {}
	virtual ~pdeque() { clear(); }
	bool isexist(const T* t) const { return (find(t) != end());	}
	int count(T* t) const { return count(begin(), end(), t); }
	void flush() { 
		while(!empty()) {
			T* p = front();
			delete(p);
			pop_front();
		}
	}
	void copy(const pdeque<T>& l) {
		if( this == &l ) return;
		assign(l.begin(), l.end());
	}
	void copy(const pdeque<T>* l) {
		if( this == l ) return;
		assign(l->begin(), l->end());
	}
	iterator find(T* d) {	return std::find(begin(), end(), d); }
	const_iterator find(const T* d) const {	return std::find(begin(), end(), d); }
};

///////////////////////////////////////////////////////////////////////////////
// pqueue

template<class T>
class pqueue : public std::queue<T*> 
{
public:
	typedef pqueue this_type;
public:
	pqueue() {}
	virtual ~pqueue() {}
	void flush() 
	{
		while(!empty())
		{
			T* p = front();
			pop();
			delete(p);
		}
	}
};

///////////////////////////////////////////////////////////////////////////////
// PtrMap

template<typename K, typename T, typename P = std::less<K> >
class PtrMap : public std::map<K, T*, P>
{
public:
	typedef std::map<K, T*, P> base_type;
public:
	explicit PtrMap(P fn = P()) : base_type(fn) {}
	virtual ~PtrMap() { }

	bool isexist(key_type k) const { return(find(k) != end()); }
	bool add(key_type k, T* t) { pair<iterator, bool> ret = insert( value_type(k, t) ); return ret.second; }
	size_type remove(key_type k)	{ return erase(k);	}
};

///////////////////////////////////////////////////////////////////////////////
// pmap

template<typename K, typename T, typename P = std::less<K> >
class pmap : public std::map<K, T*, P>
{
public:
	typedef std::map<K, T*, P> base_type;
public:
	explicit pmap(P fn = P()) : base_type(fn) {}
	virtual ~pmap() { }

	bool isexist(key_type k) const { return(find(k) != end()); }
	bool add(key_type k, T* t) { pair<iterator, bool> ret = insert( value_type(k, t) ); return ret.second; }
	size_type remove(key_type k)	{ return erase(k);	}
};

///////////////////////////////////////////////////////////////////////////////
// MAPTBALE

template<typename T, typename PredKey, typename CompKey = std::less<PredKey::result_type> >
class MapTable
{
public:
	typedef typename PredKey::result_type key_type;
	typedef PredKey key_func;
	typedef CompKey comp_func;
	typedef std::map<key_type, T, comp_func> map_type;
	typedef typename map_type::value_type value_type;
	typedef typename map_type::iterator iterator, LI;
	typedef typename map_type::const_iterator const_iterator, CLI;
	typedef typename map_type::size_type size_type;
protected:
	key_func mFunc;
	map_type mMap;
public:
	MapTable(key_func fn = key_func(), comp_func cmp = comp_func()) : mFunc(fn), mMap(cmp) { }
	virtual ~MapTable() { }

	CLI begin() const { return mMap.begin(); }
	CLI end() const { return mMap.end(); }
	LI begin() { return mMap.begin(); }
	LI end() { return mMap.end(); }

	void clear() { mMap.clear(); }
	bool empty() const { return mMap.empty(); }
	size_type size() const { return mMap.size(); }
	bool isexist(key_type k) const { return(mMap.find(k) != end()); }
	bool isexistdata(const T& t) const { return(mMap.find(mFunc(t)) != end()); }
	bool add(const T& t) { pair<LI, bool> ret = mMap.insert( value_type(mFunc(t), t) ); return ret.second; }
	size_type remove(const T& t)	{ return mMap.erase(mFunc(t)); }
	size_type remove(key_type k)	{ return mMap.erase(k);	}
	T& lookup(key_type k) {	LI i = mMap.find(k); return (*i).second; }
	const T& lookup(key_type k) const { CLI i = mMap.find(k); return (*i).second; }
	T& operator[](key_type k) { return lookup(k); }
	const T& operator[](key_type k) const {	return lookup(k); }
};

template<typename T, typename P, typename C = std::less<P::result_type> >
class pMapTable : public MapTable<T*, P, C>
{
public:
	typedef MapTable<T*, P, C> base_type;
public:
	pMapTable(key_func fn = key_func(), comp_func cmp = comp_func()) : base_type(fn, cmp) {}
	virtual ~pMapTable() { }
public:
	void flush() { 
		while(!mMap.empty()) {
			delete((*(mMap.begin())).second);
			mMap.erase(mMap.begin());
		}
		clear();
	}
};

///////////////////////////////////////////////////////////////////////////////
// MAPTBALE

template<typename T, typename PredKey, typename CompKey = std::less<typename PredKey::result_type> >
class maptable
{
public:
	typedef typename PredKey::result_type key_type;
	typedef PredKey key_func;
	typedef CompKey comp_func;
	typedef std::map<key_type, T, comp_func> map_type;
	typedef typename map_type::value_type value_type;
	typedef typename map_type::iterator iterator, LI;
	typedef typename map_type::const_iterator const_iterator, CLI;
	typedef typename map_type::size_type size_type;
protected:
	key_func mFunc;
	map_type mMap;
public:
	maptable(key_func fn = key_func(), comp_func cmp = comp_func()) : mFunc(fn), mMap(cmp) { }
	virtual ~maptable() { }

	CLI begin() const { return mMap.begin(); }
	CLI end() const { return mMap.end(); }
	LI begin() { return mMap.begin(); }
	LI end() { return mMap.end(); }

	void clear() { mMap.clear(); }
	bool empty() const { return mMap.empty(); }
	size_type size() const { return mMap.size(); }
	bool isexist(key_type k) const { return(mMap.find(k) != end()); }
	bool isexistdata(const T& t) const { return(mMap.find(mFunc(t)) != end()); }
	bool add(const T& t) { pair<LI, bool> ret = mMap.insert( value_type(mFunc(t), t) ); return ret.second; }
	size_type remove(const T& t)	{ return mMap.erase(mFunc(t)); }
	size_type remove(key_type k)	{ return mMap.erase(k);	}
	T& lookup(key_type k) {	LI i = mMap.find(k); return (*i).second; }
	const T& lookup(key_type k) const { CLI i = mMap.find(k); return (*i).second; }
	T& operator[](key_type k) { return lookup(k); }
	const T& operator[](key_type k) const {	return lookup(k); }
};

template<typename T, typename P, typename C = std::less<typename P::result_type> >
class pmaptable : public maptable<T*, P, C>
{
public:
	typedef maptable<T*, P, C> base_type;
public:
	pmaptable(key_func fn = key_func(), comp_func cmp = comp_func()) : base_type(fn, cmp) {}
	virtual ~pmaptable() { }
public:
	void flush() { 
		while(!mMap.empty()) {
			delete((*(mMap.begin())).second);
			mMap.erase(mMap.begin());
		}
		clear();
	}
};

///////////////////////////////////////////////////////////////////////////////
// HASHTABLE

template<typename T, typename PredKey, DWORD hash_size = 1023>
class hashtable
{
public:
	typedef PredKey key_func;
	typedef typename key_func::result_type key_type;
	typedef maptable<T, PredKey> bucket_type;
	typedef std::vector<bucket_type> table_type;
protected:
	table_type mTable;
	key_func mFunc;
public:
	hashtable() : mTable(hash_size) { }
	virtual ~hashtable() { }

	void clear() { mTable.clear();	}
	bool isexist(key_type k) const { return mTable[ key2index(k) ].isexist(k); }
	void add(const T& t) { mTable[ hash_index(t) ].add(t);	}
	void remove(key_type k) { mTable[ key2index(k) ].remove(k); }
	
	T& lookup(key_type k) { return mTable[ key2index(k) ].lookup(k); }
	const T& lookup(key_type k) const	{ return mTable[ key2index(k) ].lookup(k);	}
	T& operator[](key_type k) { return lookup(k);	}
	const T& operator[](key_type k) const	{ return lookup(k);	}

	bucket_type& bucket(key_type k)	{ return mTable[ key2index(k) ]; }
	const bucket_type& bucket(key_type k) const { return mTable[ key2index(k) ]; }
protected:
	DWORD key2index(key_type k) { return DWORD(k % hash_size); }
	DWORD hash_index(const T& t) { return key2index(mFunc(t)); }
};

template<typename T, typename PredKey, DWORD hash_size = 1023>
class phashtable
{
public:
	typedef PredKey key_func;
	typedef typename PredKey::result_type key_type;
	typedef pmaptable<T, PredKey> bucket_type;
	typedef std::vector<bucket_type> table_type;
protected:
	table_type mTable;
	PredKey mFunc;
public:
	phashtable() : mTable(hash_size) { }
	virtual ~phashtable() { }

	void clear() { mTable.clear();	}
	void flush() {
		for(table_type::iterator i = mTable.begin(); i != mTable.end(); i++)
			(*i).flush();
		clear();
	}
	bool isexist(key_type k) const { return mTable[ key2index(k) ].isexist(k); }
	void add(T* p) { mTable[ hash_index(p) ].add(p);	}
	void remove(key_type k) { mTable[ key2index(k) ].remove(k); }
	
	T& lookup(key_type k) { return mTable[ key2index(k) ].lookup(k); }
	const T& lookup(key_type k) const	{ return mTable[ key2index(k) ].lookup(k);	}
	T& operator[](key_type k) { return lookup(k);	}
	const T& operator[](key_type k) const	{ return lookup(k);	}

	bucket_type& bucket(key_type k)	{ return mTable[ key2index(k) ]; }
	const bucket_type& bucket(key_type k) const { return mTable[ key2index(k) ]; }
protected:
	DWORD key2index(key_type k) { return DWORD(k % hash_size); }
	DWORD hash_index(T* p) { return key2index(mFunc(p)); }
};

#endif //!XTMPL_H
