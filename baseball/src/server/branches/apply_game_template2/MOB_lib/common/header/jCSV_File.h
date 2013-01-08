/* file : jCSV_File.h
Coder : by icandoit ( mech12@nate.com)
Date : 2007-10-11 18:28:24
comp.: jgame.co.kr
title : 
desc : 

*/

#ifndef __jCSV_File_header__
#define __jCSV_File_header__
#pragma once

#include "uStringParsor.h"
#include "linux/nOS_filesystem.h"
#include "uString_stl.h"

namespace nMech
{
	namespace nUtil
	{
		inline  bool ReadLineFromFile(CHAR* buf, int buf_size, FILE* pF)
		{
			if( ja_fgets( buf, buf_size-1, pF ) == NULL)
			{
				buf=NULL; return false;
			}
			size_t len = ja_strlen(buf);
			buf[len-1] = 0; // 여기까지 file로 부터 한라인 읽어서 마지막 의 개행문자를 제거.
			return true;
		}

		inline bool _LineFromFile(FILE* f, std::string& s, int eol = '\n', int oef = EOF)
		{
			// reset string
			s.clear();

			// read one char at a time
			while (true)
			{
				// read char
				int c = fgetc(f);        

				// check for EOF
				if (c == EOF || c == 13) 
					return false;

				// check for EOL
				if (c == eol) 
					return true;

				// append this character to the string
				s += c;
			};
			return true;
		};


		template<typename T/*,typename KEY=uint32*/>
		class jCSV_File
		{
			typedef map<tstring,T*>	m_Index_t;
			m_Index_t m_Index;
			vector<T> *m_List;
		public:
			size_t size(){ return m_List ? m_List->size() : 0;}
			jCSV_File():/*m_Index(0),*/m_List(0){ }
			virtual ~jCSV_File(){}

			// 주의 csv에서 sid는 항상 1부터 시작해야함.
			// 1은 첫번째 항목
			T* Index(uint32 sid)
			{
				if(!m_List || sid> (uint32)m_List->size()) return 0;
				return &(*m_List)[sid-1];
			}
			T* at(uint32 idx)
			{
				if(!m_List ||  idx >= (uint32)m_List->size()) return 0;
				return &(*m_List)[idx];
			}
			T* operator [] ( size_t iOrder){return at(iOrder);}

			T* find(tcstr idx)
			{
				if(m_Index.size())
				{
					if(!m_Index.count(idx))
						return 0;
					return m_Index.find(idx)->second;
				}
				return 0;
			}

			bool __is_unicode(tcstr szFile)
			{
				return false;
			}
			void UnLoad()
			{
				//SAFE_DELETE(m_Index);
				SAFE_DELETE(m_List);
			}

			virtual bool Load(tcstr _szFile)
			{
				if(jt_strstr(_szFile,jS(file_Sys__))) return true;
				fs::path p = _szFile;
				tstring sFile = p.make_preferred().string();
				tcstr szFile = sFile.c_str();
				//jLOG("try %s : \n%s", __FUNCTION__ ,szFile );
				m_List = new vector<T>;
				FILE* fp =0;
				try
				{
					if(m_List->size())
					{
						jWARN(_T("jCSV_File 다시 로딩함: %s"),szFile);
						return true;
						m_List->clear();
					}
					if(__is_unicode(szFile))
					{
						jERROR("unicode file");
					}
					else
					{
						fp = jt_fopen(szFile,_T("rb"));
						if(!fp) 
						{
							// Sys__로 시작하는 테이블은 상속되는 테이블이다.
							if(jt_strstr(szFile,jS(file_Sys__) ) || jt_strstr(szFile,jS(file_Sys_Base_) ))
							{
								jLOG("file load skipped: %s", szFile);
								return true;
							}
							jWARN(_T("file not found : %s"), szFile);
							return false;
						}
						int iTotSize=0;
						char szBuf[2048];
						while (ReadLineFromFile(szBuf,sizeof(szBuf),fp))
						{
							++iTotSize;
						}
						m_List->resize(iTotSize-1);
						fseek(fp,0,SEEK_SET );

						std::astring sz;
						size_t i=0;
						ReadLineFromFile(szBuf,sizeof(szBuf),fp);
						while (ReadLineFromFile(szBuf,sizeof(szBuf),fp))
						{
							tstring tstr = szBuf;
							nSTL::trim(tstr);
							std::vector<std::tstring> outLine;
							nMech::nString::jSplit(tstr ,_T(","),outLine);
							size_t idx =0;
							T& record = (*m_List)[i];
							tcstr szKEY = record.ReadCSV(i+1,outLine,idx);
							if(szKEY)
							{
								m_Index[szKEY]=&record;
							}

							jASSERT0(idx==T::Get_STRUCT_COUNT());

							++i;
						};
					}
					jLOG("LOAD OK %s",szFile );

				}
				catch(tcstr sz)
				{
					jWARN(_T("LOAD FAIL(%s) : %s"),szFile,sz);
				}
				catch(...)
				{
					jWARN(_T("LOAD FAIL(%s) :"),szFile);

				}
				if(fp)fclose(fp);
				return true;
			}

		};

	}//namespace nUtil
}//namespace nMech


#endif // __jCSV_File_header__
