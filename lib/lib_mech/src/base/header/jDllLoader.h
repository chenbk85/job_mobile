/* file : jDllLoader.h
Coder : by icandoit ( mech12@nate.com)
Date : 2008-03-05 15:39:56
comp.: www.actoz.com
title : 
desc : 

*/

#ifndef __jDllLoader_header__
#define __jDllLoader_header__
#pragma once

#include <boost/noncopyable.hpp>

namespace nMech
{
	struct jDllLoader : public boost::noncopyable
	{
	protected:
		HMODULE m_hDLL;

	public:
		HMODULE GetDLLHandle(){ return m_hDLL;}
		jDllLoader(tcstr szName) : m_hDLL(0)
		{
			if(!szName || !jt_strlen(szName)) return;
			m_hDLL = ::LoadLibrary( szName);
			if(!m_hDLL)
			{
				path_t buf;
				GetCurrentDirectory(_countof(buf),buf);
				jWARN(_T("dll load fail : %s, curr dir = %s"), szName,buf);
			}
			else
			{
				jLOG(_T("dll load ok : %s"),szName);
			}
			// NULL이면 실패
		}
		virtual ~jDllLoader()
		{
			if(m_hDLL)
				FreeLibrary(m_hDLL);
		}
		void* GetFunc(acstr szFunc)
		{
			if(m_hDLL)
				return ::GetProcAddress(m_hDLL, szFunc);
			else
				return 0;
		}
	};

	struct jDllLoader_Mech : public jDllLoader
	{
		typedef void* jCreateInterface_t(jIE*);
		typedef void jDeleteInterface_t();
		typedef acstr jGetModuleOwnerName_t();

		jCreateInterface_t* m_pjCreateInterface;
		jDeleteInterface_t* m_pjDeleteInterface;
		jGetModuleOwnerName_t* m_pjGetModuleOwnerName;
		std::tstring m_sDLL;
		void* jCreateInterface(jIE* pE=0)
		{
			if(!m_pjCreateInterface) return 0;
			void* v = m_pjCreateInterface(pE);
			m_pjCreateInterface=0;
			return v;
		}
		void jDeleteInterface()
		{
			if(!m_pjDeleteInterface) return;
			m_pjDeleteInterface();
			m_pjDeleteInterface=0;
		}

		jDllLoader_Mech(tcstr szName):jDllLoader(szName)
			,m_pjCreateInterface(0)
			,m_pjDeleteInterface(0)
			,m_pjGetModuleOwnerName(0)
			,m_sDLL(szName)
		{
			if(!m_hDLL) return;
			m_pjCreateInterface= (jCreateInterface_t*)GetFunc("jCreateInterface");
			m_pjDeleteInterface= (jDeleteInterface_t*)GetFunc("jDeleteInterface");
			m_pjGetModuleOwnerName= (jGetModuleOwnerName_t*)GetFunc("jGetModuleOwnerName");
		}

		virtual ~jDllLoader_Mech()
		{
			if(!m_hDLL) return;
			jDeleteInterface();
		}

	};

}



#endif // __jDllLoader_header__
