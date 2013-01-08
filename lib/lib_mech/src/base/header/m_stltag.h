
/* 
filename:	m_STLtag.h
coder	:	Cho Wook Rea (mech12@dreamwiz.com) 
comp.	:	f2system 
compiler:	vc++ 6.0
date	:	2000 / 01 / 
title	:	
*/

#ifndef __m_STLtag_h__
#define __m_STLtag_h__
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning ( disable : 4786) 
#include <list>
#include <set>
#include <map>
#include <hash_map>
#include <vector>
#include <BITSET>
#include <functional>
#include <algorithm>

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

namespace std
{
	typedef string astring ;

#ifdef UNICODE
#define tcout std::wcout
	typedef wstring tstring;
	typedef wofstream tofstream;
	typedef wifstream tifstream;
#else
#define tcout std::cout
	typedef ofstream tofstream;
	typedef ifstream tifstream;
	typedef string tstring;
#endif 

}

namespace nMech
{
	/*{by icandoit2005-01-07 오후 4:09:07
	#ifndef _WIN32
	#define _WIN32
	#endif
	using namespace std;
	#ifdef _WIN32
	using namespace std::rel_ops ;
	#endif
	}by icandoit 2005-01-07 오후 4:09:11*/

#ifndef jvector
#define jvector std::vector 
#endif
#include <xstring>

	//typedef jvector<std::tstring> nameList_t;
	//typedef nameList_t::iterator nameList_it;
	//typedef bitset<sizeof(int)*8> jBitSet;

#ifndef jLIST_TYPEDEF_YVECTOR
#define jLIST_TYPEDEF_YVECTOR(x,var) typedef nMech::nDataStruct::yVector<x> 	var##_t; typedef x var##_vt; typedef var##_t::iterator var##_it; var##_t var;
#define jLIST_TYPEDEF_YVECTOR_header(x,var) typedef nMech::nDataStruct::yVector<x> 	var##_t; typedef x var##_vt; typedef var##_t::iterator var##_it; extern var##_t var;
#define jLIST_TYPEDEF_YVECTOR_typedef(x,var) typedef nMech::nDataStruct::yVector<x> 	var##_t; \
	typedef x var##_vt; typedef var##_t::iterator var##_it;
#endif


#ifndef jLIST_TYPEDEF_list
#define jLIST_TYPEDEF_list(x,var) typedef std::list<x> 	var##_t; typedef x var##_vt; typedef var##_t::iterator var##_it; var##_t var;
#define jLIST_TYPEDEF_list_header(x,var) typedef std::list<x> 	\
	var##_t; typedef x var##_vt; typedef var##_t::iterator var##_it; extern var##_t var;
#define jLIST_TYPEDEF_list_typedef(x,var) typedef std::list<x> 	var##_t; typedef x var##_vt; \
	typedef var##_t::iterator var##_it;
#endif



#ifndef jLIST_TYPEDEF_set
#define jLIST_TYPEDEF_set(x,var) typedef std::set<x> 	var##_t; typedef x var##_vt; typedef var##_t::iterator var##_it; var##_t var;
#define jLIST_TYPEDEF_set_header(x,var) typedef std::set<x> 	\
	var##_t; typedef x var##_vt; typedef var##_t::iterator var##_it; extern var##_t var;
#define jLIST_TYPEDEF_set_typedef(x,var) typedef std::set<x> 	var##_t; typedef x var##_vt; \
	typedef var##_t::iterator var##_it;
#endif


#ifndef jLIST_TYPEDEF_vector
#define jLIST_TYPEDEF_vector(type,var) typedef std::vector<type> 	var##_t; typedef type var##_vt; typedef var##_t::iterator var##_it; var##_t var;
#define jLIST_TYPEDEF_vector_header(type,var) typedef std::vector<type> 	\
	var##_t; typedef type var##_vt; typedef var##_t::iterator var##_it; extern var##_t var;
#define jLIST_TYPEDEF_vector_typedef(type,var) typedef std::vector<type> 	var##_t; \
	typedef type var##_vt; typedef var##_t::iterator var##_it;
#endif

#ifndef jLIST_TYPEDEF_map
#define jLIST_TYPEDEF_map(key,val,var) typedef val var##_value_t; typedef std::map<key,val> 	var##_t; typedef var##_t::iterator var##_it; var##_t var;\
	typedef var##_t::value_type var##_vt; typedef std::pair<var##_it, bool>	var##_pt;
#define jLIST_TYPEDEF_map_header(key,val,var) typedef val var##_value_t; typedef std::map<key,val> 	\
	var##_t; typedef var##_t::iterator var##_it; extern var##_t var;\
	typedef var##_t::value_type var##_vt; typedef std::pair<var##_it, bool>	var##_pt;
#define jLIST_TYPEDEF_map_typedef(key,val,var) typedef val var##_value_t; typedef std::map<key,val> 	var##_t; typedef var##_t::iterator var##_it;\
	typedef var##_t::value_type var##_vt; typedef std::pair<var##_it, bool>	var##_pt;
#endif

#ifndef jLIST_TYPEDEF_hash_map
#define jLIST_TYPEDEF_hash_map(key,val,var) typedef val var##_value_t; typedef stdext::hash_map<key,val> 	var##_t; typedef var##_t::iterator var##_it; var##_t var;\
	typedef var##_t::value_type var##_vt; typedef std::pair<var##_it, bool>	var##_pt;
#define jLIST_TYPEDEF_hash_map_header(key,val,var) typedef val var##_value_t; typedef stdext::hash_map<key,val> 	\
	var##_t; typedef var##_t::iterator var##_it; extern var##_t var;\
	typedef var##_t::value_type var##_vt; typedef std::pair<var##_it, bool>	var##_pt;
#define jLIST_TYPEDEF_hash_map_typedef(key,val,var) typedef val var##_value_t; typedef stdext::hash_map<key,val> 	var##_t; typedef var##_t::iterator var##_it;\
	typedef var##_t::value_type var##_vt; typedef std::pair<var##_it, bool>	var##_pt;
#endif


#define for_each_class_ref( x, func) for_each(x.begin( ), x.end( ), mem_fun_ref ( &x##_vt::func ) );

#define jFIND(A,B) std::find(A.begin(),A.end(), B)
#define jFIND_IF(a, b) std::find_if(a.begin(),a.end(),b)
#define jFOR_EACH(a, b) std::for_each(a.begin(),a.end(),b)
#define jForEach(a) for(a##_it it = a.begin(); it!=a.end(); ++it)

#define jLIST_for(X) for( X##_it it = X.begin(), ie = X.end();  it!=ie ; ++it)
#define jLIST_for2(X,it,ie) for( X##_it it = X.begin(), ie = X.end();  it!=ie ; ++it)


}//namespace nMech


#endif //__m_STLtag_h__
