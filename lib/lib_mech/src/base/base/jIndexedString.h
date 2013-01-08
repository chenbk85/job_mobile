/* file : jIndexedString.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-10-25 16:57:23
comp.: pantavision
title : 
desc : 

*/

#ifndef __jIndexedString_header__
#define __jIndexedString_header__
#pragma once

#include "header/jSington.h"
#include "header/jInterface.h"
namespace nMech
{
	namespace nString
	{
		typedef StringID jstring_id;
		typedef StringID jstring_cid;

		class kXmlIndex;

#define jINTERFACE_jIStringTable(tag) public:	\
	virtual void clear() ##tag\
	virtual kXmlIndex* GetTable() ##tag \
	virtual jstring_id GetIndex(tcstr ) ##tag \
	virtual tcstr GetName(jstring_cid) ##tag \
	virtual void SaveToFile(FILE* fp) ##tag \
	virtual void InitByXml()##tag \
	virtual jstring_cid RegistID(tcstr szName,jstring_id* pID)##tag \

		jINTERFACE_END(jIStringTable);

		jSINGTON_INTERFACE_HEADER(JBASE_API , jIStringTable);
	}
}

#endif // __jIndexedString_header__
