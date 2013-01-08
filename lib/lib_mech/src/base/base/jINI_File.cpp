#include <stdafx.h>
#include ".\jini_file.h"
#include <cstdio>
#include "header/uString_stl.h"
#include "base/jFolder.h"
#include "header/UFile.h"


using namespace std;
namespace nMech
{
	using namespace nFileSystem;
	namespace nScript
	{

		jINI_File* g_inifile;

		//#define jLOG_DEBUG
		//static nUtil::jCriticalSection  m_CS_Load_INI;

		jSINGTON_INTERFACE_DEFINE(JBASE_API , jINI_Manager , jIINI_Manager )
		{

		}
		jINI_File::jINI_File()
		{

		}

		jINI_File::~jINI_File()
		{

		}


		jINI_Data_t jINI_File::GetData(tcstr sec, tcstr key)
		{
			return &m_sections[sec][key];
		}
		jINI_Data_t jINI_File::FindData(tcstr sec, tcstr key)
		{
			m_sections_it  it = m_sections.find(sec);
			if(it== m_sections.end()) return 0;
			section_type_it itKey =  it->second.find(key);
			if(itKey == it->second.end())		return 0;
			return &itKey->second;
		}

		void jINI_File::for_each_Section(tcstr szSection , boost::function<void (tcstr szName,jIVar*)> func)
		{
			m_sections_it  itSection = m_sections.find(szSection);
			if(itSection==m_sections.end()) return;
			section_type_it it = itSection->second.begin();
			jFOR(itSection->second , it)
			{
				func(it->first.c_str() , &it->second);
			}
		}
		void jINI_File::for_each(boost::function<void (tcstr szSection , tcstr szName,jIVar* )> func)
		{
			m_sections_it  itSection = m_sections.begin();
			jFOR( m_sections, itSection)
			{
				section_type_it itName = itSection->second.begin();
				jFOR(itSection->second , itName)
				{
					func(itSection->first.c_str(), itName->first.c_str() , &itName->second);
				}
			}
		}


		///////////////////////////////////////////////////////////////////////////
		tcstr jINI_File::GetFileName()
		{
			return m_sFile.c_str();
		}


		void jINI_File::Save()
		{

		}
		void jINI_File::SaveAs(tcstr)
		{

		}

		void jINI_Manager::UnLoad(jIINI_File* pFile)
		{
			if(!m_List.size()) return;
			//m_CS_Load_INI.Lock();
			m_List_it it = m_List.find(pFile->GetFileName());
			assert(it != m_List.end());
			m_List.erase(it);
			//m_CS_Load_INI.UnLock();
		}

		jIINI_File* jINI_Manager::Load(tcstr szPath)
		{
			enum ESkip
			{
				now_skip,
			};
			jIINI_File* pRet=0;
			try
			{
				nFileSystem::jFolder dm;
				tstring sFileName = szPath;
				transform( sFileName.begin(), sFileName.end(), sFileName.begin(), tolower ); 
				tstring sBuf;
				if(!nFileSystem::read_file(sFileName.c_str() , sBuf)) 	throw now_skip;

				//--------------------------------------------------------------------------
				// spilit파싱
				//--------------------------------------------------------------------------
				//m_CS_Load_INI.Lock();
				g_inifile = &m_List[sFileName];
				g_inifile->m_sFile = sFileName;


				vector<tstring> outLine;
				nString::jSplit(sBuf, _T("\n\r") , outLine);
				jINI_File::section_type_t* pSec=0;
				for(size_t i=0; i<outLine.size();++i)
				{
					nSTL::trim(outLine[i]);
					if(!outLine[i].size()) continue;
					if( outLine[i][0] == ';')
					{
						continue;
					}
					else if( outLine[i][0] =='[')
					{
						tstring strSec = outLine[i];
						nSTL::trim(strSec , _T("[] \n\r") );
						pSec = &g_inifile->m_sections[strSec];
					}
					else if(outLine[i].find('=') != std::tstring::npos)
					{
						vector<tstring> outVal;
						nString::jSplit(outLine[i] , _T("="), outVal);
						if(outVal.size()!=2) continue;
						nSTL::trim(outVal[0]);
						nSTL::trim(outVal[1]);
						if(outVal[1][0]=='"')
						{
							nSTL::trim(outVal[1], _T("\""));
							jIVar* pV = &(*pSec)[outVal[0]];
							pV->SetType(jIVar::EDcstr);
							pV->FromString(outVal[1].c_str());
						}
						else
						{
							if( outVal[1].find('.')==std::tstring::npos )
							{
								jIVar* pV = &(*pSec)[outVal[0]];
								pV->SetType(jIVar::EDint);
								pV->FromString(outVal[1].c_str());
							}
							else
							{
								jIVar* pV = &(*pSec)[outVal[0]];
								pV->SetType(jIVar::EDfloat);
								pV->FromString(outVal[1].c_str());
							}
						}
					}
				}

				
				pRet = g_inifile;
			}
			catch(ESkip )
			{

			}
			catch(tcstr sz)
			{
				jMB(szPath, sz);
			}
			catch (...)
			{
				jMB(szPath, _T("알수 없는 에러"));
			}

			g_inifile = 0;
			//m_CS_Load_INI.UnLock();
			return pRet;

		}

		void jINI_Manager::clear()
		{
			//m_CS_Load_INI.Lock();
			m_List.clear();
			//m_CS_Load_INI.UnLock();
		}

	}
}//namespace nMech
