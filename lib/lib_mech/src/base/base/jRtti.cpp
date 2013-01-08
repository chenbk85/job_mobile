/* 
	filename:	jRTTI.cpp
	coder	:	Cho Hyun Min (by icandoit) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4337-10-20 오후 4:39:59
	title	:	
*/
#include "stdafx.h"
#include "jRTTI.h"
namespace nMech
{
	typedef std::map<std::tstring , jRTTI*> rttiByclassName_t;
	typedef rttiByclassName_t::iterator rttiByclassName_it;
	typedef std::map<std::tstring , rttiByclassName_t> classlinkByscope_t;
	typedef classlinkByscope_t::iterator classlinkByscope_it;
	classlinkByscope_t s_classlinkByscope;

	typedef std::map<std::tstring,std::tstring> scopeByclass_t;
	typedef scopeByclass_t::iterator scopeByclass_it;
	scopeByclass_t s_scopeByClass;

	//--------------------------------------
	void jRTTI::registerClassRep(jRTTI* in_pRep, bool bScopeFirst)
	{
		if(!bScopeFirst)
		{
			scopeByclass_it it = s_scopeByClass.find(in_pRep->m_szClassName);
			if(it!=s_scopeByClass.end())
			{
				tfname_t buf;
				jt_sprintf(buf, _T("jRTTI::registerClassRep(%s,%s) 중복등록"), in_pRep->m_szScope, in_pRep->m_szClassName);
				jMB(buf, _T("error"));
				jASSERT0(0);
			}
			jASSERT0(it==s_scopeByClass.end());
			s_scopeByClass[in_pRep->m_szClassName] = in_pRep->m_szScope;
		}

		rttiByclassName_t& classLink = s_classlinkByscope[in_pRep->m_szScope];
		rttiByclassName_it itRTTI = classLink.find(in_pRep->m_szClassName);
		if(itRTTI != classLink.end())
		{
			tfname_t buf;
			jt_sprintf(buf, _T("%s : %s") ,in_pRep->m_szClassName, in_pRep->m_szScope );
			jWARN(_T("%s , jRTTI OBJECT NAME DUPLICATE"),buf);
// 			jMB(buf,_T("jRTTI OBJECT NAME DUPLICATE"));
// #ifndef _WIN64
// 				__asm int 3; 	
// #else
// 			__debugbreak();
// #endif
		}
		classLink[in_pRep->m_szClassName] = in_pRep;
		jLOG(jFUNC1 _T("%s (scope = %s)"), in_pRep->m_szClassName,in_pRep->m_szScope);
	}

	//--------------------------------------

	jRttiObj* jRTTI::New(tcstr in_pClassName,tcstr szScope)
	{
		if(!jt_strlen(in_pClassName) || !jt_strcmp(in_pClassName,_T("NULL"))) return 0;
		std::tstring sScope;
		if(!szScope)
		{
			scopeByclass_it itScope = s_scopeByClass.find(in_pClassName);
			if(itScope == s_scopeByClass.end())
			{
				jLOG(jFUNC1 _T("( %s) -> not found class scope"), in_pClassName);
				return 0;
			}
			sScope = itScope->second;
		}
		else
			sScope = szScope;

		rttiByclassName_t& classLink = s_classlinkByscope[sScope];
		rttiByclassName_it itRTTI = classLink.find(in_pClassName);
		if(itRTTI == classLink.end()) 
		{
			jLOG(jFUNC1 _T("New(%s:%s) -> not found class"), sScope.c_str() ,in_pClassName);
			return 0;
		}

		return itRTTI->second->__New();
	}

	void  jRTTI::Del(jRttiObj* pO)
	{
		pO->getClassRep()->__Del(pO);
	}

}
