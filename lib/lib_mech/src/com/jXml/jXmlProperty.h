/* 
	filename:	jXmlProperty.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-02-24 ¿ÀÈÄ 4:47:48
	title	:	
*/


#ifndef __jXmlProperty_h__
#define __jXmlProperty_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000
#include "interface/xml/jIDocument.h"


namespace nMech
{
	namespace nXML
	{

		// XPV = Xml Property 
		struct jXPV_base
		{
			jIElement* m_peParent;	
			jIVar* Get(cstr sz){ jIE* pe =m_peParent->Find(sz) ;return pe ? pe->GetVar():0;}
			jIVar* Get(nMech::StringID sz){ jIE* pe =m_peParent->Find(sz) ;return pe ? pe->GetVar():0;}
		};

#define jXPV_DEC_START(name)		struct name : public jXPV_base{void init(jIElement* pE);
#define jXPV_DEC(var) jIVar* var;
#define jXPV_DEC_END() };

#define jXPV_DEF_START(base,name) void base::name::init(jIElement* pE){ m_peParent = pE;
#define jXPV_DEF_START_1(name) name::init(jIElement* pE){ m_peParent = pE;
#define jXPV_DEF(var) var = m_peParent->Find(#var)->GetVar();
#define jXPV_DEF_id(var) var = m_peParent->Find(jx(var))->GetVar();
#define jXPV_DEF_END() }



	}
}





#endif //__jXmlProperty_h__
