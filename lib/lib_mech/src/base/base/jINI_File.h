/* file : jINI_File.h
Coder : by icandoit (mech12@nate.com)
Date : 2006-10-24 12:16:12
title : 
desc : 

*/

#ifndef __jINI_File_header__
#define __jINI_File_header__
#pragma once

#include <string>
#include <map>
#include <Interface/jIINI_FIle.h>
#include "header/jCriticalSection.h"
#include "base/jxVar.h"
#include "header/jSington.h"

namespace nMech
{

	namespace nScript
	{
		//--------------------------------------------------------------------------
		class jINI_File : public jIINI_File
			//--------------------------------------------------------------------------
		{ 
		public:
			jINI_File();
			~jINI_File();
			typedef std::map<std::tstring , jxVar> section_type_t;
			typedef section_type_t::iterator section_type_it;
			//jLIST_TYPEDEF_map_header(std::tstring , jxVar , section_type);
			jLIST_TYPEDEF_map(std::tstring,  section_type_t,	m_sections);

			jINTERFACE_HEADER(jIINI_File);
			tstring m_sFile;
		};

		inline jINI_Data_t jINI_File::FindData(const std::tstring &sec , const std::tstring &key){	return FindData(sec.c_str() , key.c_str()); }
		inline jINI_Data_t jINI_File::GetData(const std::tstring &sec , const std::tstring &key) { return GetData(sec.c_str(), key.c_str());}

		//--------------------------------------------------------------------------
		class jINI_Manager : public jIINI_Manager
			//--------------------------------------------------------------------------
		{
		public :
			jINTERFACE_HEADER(jIINI_Manager);
			jSINGTON_INTERFACE_DECLEAR(JBASE_API , jINI_Manager,jIINI_Manager);
		private:

			jLIST_TYPEDEF_map(std::tstring,  jINI_File ,	m_List);
			friend class jINI_File;
		};

		inline jIINI_File* jINI_Manager::Load(const std::tstring & szPath) { return Load(szPath.c_str());}
	}
}

#endif // __jINI_File_header__
