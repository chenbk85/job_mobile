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

#include "jUniAnsi_FileIO.h"

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

		//_LineFromFile는 unicode , ansi 모두 테스트 필요.
		inline bool _LineFromFile(FILE* f, std::wstring& s, wint_t eol = '\n', wint_t oef = WEOF)
		{
			// reset string
			s.clear();
			// read one wide char at a time
			while (true)
			{
				// read wide char
				wint_t c = fgetwc(f);

				// check for EOF
				if (c == EOF || c == WEOF || c==13) 
					return false;

				// check for EOL
				if (c == eol) 
					return true;

				// append the wide character to the string        
				s += c;
			};
			return true;
		};
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
				if(!m_List || sid <=0 || sid> m_List->size()) return 0;
				return &(*m_List)[sid-1];
			}
			T* at(uint32 idx)
			{
				if(!m_List || idx <0 || idx >= m_List->size()) return 0;
				return &(*m_List)[idx];
			}
			T* operator [] ( size_t iOrder){return at(iOrder);}

			T* find(tcstr idx)
			{
				if(m_Index.size())
				{
					m_Index_t::iterator it = m_Index.find(idx);
					if(it == m_Index.end())
						return 0;
					return it->second;
				}
				return 0;
			}
/*
			typedef tcstr func_t(T*);
			void MakeIndex(func_t* fn )
			{
				jRETURN(m_List);
				for(uint i =0; i < m_List->size(); ++i)
				{
					m_Index[ fn(&(*m_List)[i]) ] = &(*m_List)[i];
				}
			}
			*/

			bool __is_unicode(tcstr szFile)
			{
				HANDLE hFile = ::CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
				if(hFile==INVALID_HANDLE_VALUE)
				{
					// Sys__로 시작하는 테이블은 상속되는 테이블이다.
					nFileSystem::jFileName fn(szFile);
					if(jt_strncmp(fn.fname,jS(file_sys__) , 5)==0 )
					{
						jLOG_T("\nfile load skipped: %s", szFile);
						throw true;
					}
					jWARN(_T("\nfile not found : %s"), szFile);
					throw szFile;
				}
				WCHAR bom=0;
				DWORD dwRead;
				ReadFile(hFile,&bom,sizeof(WCHAR),&dwRead,0 );
				CloseHandle(hFile);
				return (bom == WCHAR(0xFEFF));
			}
			void UnLoad()
			{
				//SAFE_DELETE(m_Index);
				SAFE_DELETE(m_List);
			}

			bool Load(tcstr szFile)
			{
				m_List = new vector<T>;
				FILE* fp =0;
				HANDLE hFile =INVALID_HANDLE_VALUE;
				jLOG(_T("\ncsv file load : %s"), szFile);
				try
				{
					if(m_List->size())
					{
						jWARN(_T("jCSV_File 다시 로딩함: %s"),szFile);
						return true;
						m_List->clear();
					}
					T t;
					memset(&t,0,sizeof(t));

					size_t iTotS ;
					if(__is_unicode(szFile))
					{

						WCHAR bom;
						DWORD dwRead;
						HANDLE hFile = ::CreateFile(szFile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
						if(hFile==INVALID_HANDLE_VALUE)
						{
							throw szFile;
						}
						ReadFile(hFile,&bom,sizeof(bom),&dwRead,0 );
						WCHAR buffer[2048*4];
						{

							vector<wstring> out;
							{
								{
									std::wstring sUnicode=L"";
									sUnicode.reserve(1024*1024);

									for(int i=0 ;ReadFile(hFile,buffer, 4096 ,&dwRead,0 ) ;++i)
									{
										if(!dwRead)
											break;
										int iLen = dwRead / sizeof(WCHAR);
										buffer[iLen]=L'\0';
										sUnicode += buffer;
									}
									iTotS = sUnicode.size();
									nString::jSplitW(sUnicode,L"\n\r",out);
								}
								//out.erase(out.begin());
								size_t itot = out.size();

								m_List->resize(itot-1);
								for( size_t i = 0 ; i<(itot-1); ++i)
								{
									wstring str1 = out[i+1].c_str();
									std::vector<std::wstring> outLine;
									nMech::nString::jSplitW(str1.c_str() ,L",",outLine);
									size_t idx =0;
									tcstr szKEY = (*m_List)[i].ReadCSV(i+1, outLine ,idx);
									if(szKEY)
									{
										m_Index[szKEY]=&((*m_List)[i]);
									}
									jASSERT0(idx==T::Get_STRUCT_COUNT());//,_T("file(%s) Data(%s)"),szFile,str1.c_str() );
								}
								//printf("asdf1");
							}
							int ii=0;
							ii++;
							//printf("asdf2");
						}
						//printf("asdf3");

					}
					else
					{
						fp = jt_fopen(szFile,_T("rb"));
						if(!fp) 
						{
							// Sys__로 시작하는 테이블은 상속되는 테이블이다.
							nFileSystem::jFileName fn(szFile);
							if(jt_strncmp(fn.fname,jS(file_sys__) , 5)==0 )
							{
								jLOG_T("\nfile load skipped: %s", szFile);
								return true;
							}

							jWARN(_T("file not found : %s"), szFile);
							return false;
						}
						std::astring sz;
						size_t i=0;
						char szBuf[2048];
						ReadLineFromFile(szBuf,sizeof(szBuf),fp);
						m_List->push_back(t);
						size_t iRecord=0;
						while (ReadLineFromFile(szBuf,sizeof(szBuf),fp))
						{
							m_List->push_back(t);
							nUNI::StringConvertBuffer<2048> buf(szBuf);
							wstring tstr = buf.getW();
							nSTL::trim(tstr);
							std::vector<std::wstring> outLine;
							nMech::nString::jSplitW(tstr ,L",",outLine);
							size_t idx =0;
							tcstr szKEY = (*m_List)[i].ReadCSV(i+1,outLine,idx);
							if(szKEY)
							{
								m_Index[szKEY]=&((*m_List)[i]);
							}

							jASSERT0(idx==T::Get_STRUCT_COUNT());

							++i;
						};
					}
				}
				catch(tcstr sz)
				{
					jWARN(_T(": error : %s"),sz);
				}
				catch(...)
				{

				}
				if(hFile!=INVALID_HANDLE_VALUE) CloseHandle(hFile);
				if(fp)fclose(fp);
				return true;
			}

		};

	}//namespace nUtil
}//namespace nMech


#endif // __jCSV_File_header__
