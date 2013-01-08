/* file : jIINI_File.h
Coder : by icandoit (mech12@nate.com)
Date : 2006-10-24 16:57:35
title : 
desc : 

*/

#ifndef __jIINI_File_header__
#define __jIINI_File_header__
#pragma once
#include <boost/function.hpp>
#include <header/jDefine.h>
#include "base/jxVar.h"
#include "header/jSington.h"

namespace nMech
{
	namespace nScript
	{
		typedef jxVar* jINI_Data_t;
		typedef std::vector<std::pair<tcstr, jIVar*> > jIINI_section_find_list_t;


#define jINTERFACE_jIINI_File(x) public:	\
	\
	/* �ش�Ű�� ã�� ������ 0�� ���� */ \
	virtual jINI_Data_t FindData(tcstr sec , tcstr key) ##x \
	virtual jINI_Data_t FindData(const std::tstring &sec , const std::tstring &key) ##x \
	\
	/* �ش�Ű�� ������ �����ؼ� �������͸� ���� */ \
	virtual jINI_Data_t GetData(tcstr sec , tcstr key) ##x \
	virtual jINI_Data_t GetData(const std::tstring &sec , const std::tstring &key) ##x \
	virtual void for_each_Section(tcstr szSection , boost::function<void (tcstr szName,jIVar*)> )##x\
	virtual void for_each(boost::function<void (tcstr szSection , tcstr szName,jIVar*)> )##x\
	\
	virtual tcstr GetFileName() ##x \
	/* szFile�� ��� ���� jINI_File��ü�� ������ Update�Ѵ�. */\
	/*virtual bool ReloadFrome(tcstr szFile) ##x*/\
	virtual void Save() ##x\
	virtual void SaveAs(tcstr) ##x\

		jINTERFACE_END(jIINI_File);

#define jINTERFACE_jIINI_Manager(x) public:	\
	virtual jIINI_File* Load(tcstr szPath) ##x \
	virtual jIINI_File* Load(const std::tstring & szPath) ##x \
	virtual void UnLoad(jIINI_File*) ##x \
	virtual void clear() ##x \

		jINTERFACE_END(jIINI_Manager);

		jSINGTON_INTERFACE_HEADER(JBASE_API , jIINI_Manager);
	}
}

#endif // __jIINI_File_header__
