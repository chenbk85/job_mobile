 /* 
	filename:	jxSchema.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com)(icq:74456993) 
	compiler:	vc++ 6.0
	date	:	2001-07-05¿ÀÀü 2:11:21
	title	:	
*/


#if !defined(AFX_JXMLUTIL_H__B8128BE6_F738_4EE8_9896_B582D0625A0C__INCLUDED_)
#define AFX_JXMLUTIL_H__B8128BE6_F738_4EE8_9896_B582D0625A0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable : 4251)

//#include "jBStr.h"
#include "interface/xml/jIXmlUtil.h"

#define MFC_XMLPARSOR_TOOL

namespace nMech
{
	namespace nXML
	{

		class jXmlUtil : public jIXmlUtil
		{
			jINTERFACE_HEADER(jIXmlUtil);

		};


	}
}

#pragma warning(default: 4251)

#endif // !defined(AFX_JXMLUTIL_H__B8128BE6_F738_4EE8_9896_B582D0625A0C__INCLUDED_)
