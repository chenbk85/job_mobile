/* 
	filename:	juFileEnum.cpp
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	2005-01-28 ¿ÀÈÄ 2:33:20
	title	:	


	juFileEnum szFindFile;
	if (szFindFile.StartEnumeration("xml", "*.xml", &sFile))
	do {
		strcat(szFilePath, sFile.name);
	} while (szFindFile.GetNextFile(&sFile));


*/
#include "stdafx.h"
#include "header/jBoost.h"
#include "juFileEnum.h"
#include <io.h>

namespace nMech
{
	namespace nFileSystem
	{
		JUTIL_API void for_each_folder( tcstr szPath,for_each_folder_function_t* func ,void* v)
		{
			namespace fs = boost::filesystem;
			fs::tdirectory_iterator end;
			fs::tpath sPath (szPath);
			fs::tpath path2;
			for( fs::tdirectory_iterator it(szPath); it!=end; ++it )
			{
				path2 = *it;
				if( fs::is_directory(*it) )
					for_each_folder(jT(path2.string()),func,v);
				else
					func(jT(path2.string()),v);
			}
		}
#if 0
		//////////////////////////////////////////////////////////////////////
		juFileEnum::juFileEnum()
		{
			m_hEnumFile = 0;
		}

		juFileEnum::~juFileEnum()
		{
			// End the enumeration
			if (m_hEnumFile)
			{
				_findclose(m_hEnumFile);
				m_hEnumFile = 0;
			}
		}

		bool juFileEnum::StartEnumeration( const char* szEnumPath, char szEnumPattern[], __finddata64_t *pFile)
		{
			//////////////////////////////////////////////////////////////////////
			// Take path and search pattern as separate arguments
			//////////////////////////////////////////////////////////////////////

			char szPath[_MAX_PATH];

			// Build enumeration path
			strcpy(szPath, szEnumPath);
			if (szPath[strlen(szPath)] != '\\' &&
				szPath[strlen(szPath)] != '/')
			{
				strcat(szPath, "\\");
			}
			strcat(szPath, szEnumPattern);

			return StartEnumeration(szPath, pFile);
		}

		bool juFileEnum::StartEnumeration( const char *szEnumPathAndPattern, __finddata64_t *pFile)
		{
			//////////////////////////////////////////////////////////////////////
			// Start a new file enumeration
			//////////////////////////////////////////////////////////////////////

			// End any previous enumeration
			if (m_hEnumFile)
			{
				_findclose(m_hEnumFile);
				m_hEnumFile = 0;
			}

			// Start the enumeration
			if ((m_hEnumFile = _findfirst64(szEnumPathAndPattern, pFile)) == -1L)
			{
				// No files found
				_findclose(m_hEnumFile);
				m_hEnumFile = 0;
				return false;
			}

			return true;
		}

		bool juFileEnum::GetNextFile(__finddata64_t *pFile)
		{
			//////////////////////////////////////////////////////////////////////
			// Start a new file enumeration
			//////////////////////////////////////////////////////////////////////

			// Fill file strcuture
			if (_findnext64(m_hEnumFile, pFile) == -1)
			{
				// No more files left
				_findclose(m_hEnumFile);
				m_hEnumFile = 0;
				return false;
			};

			// At least one file left
			return true;
		}


		// Get directory contents.
		inline bool ScanDirectoryRecursive( const tstring &root
			,const tstring &path
			,const tstring &file
			,std::vector<tstring> &listFiles
			,bool recursive )
		{
			struct __finddata64_t c_file;
			intptr_t hFile;

			bool anyFound = false;

			tstring fullPath = root + path + file;
			if( (hFile = _findfirst64( fullPath.c_str(), &c_file )) != -1L )
			{
				// Find the rest of the listFiles.
				do {
					anyFound = true;
					listFiles.push_back( path + c_file.name );
				}	while (_findnext64( hFile, &c_file ) == 0);
				_findclose( hFile );
			}

			if (recursive)
			{
				fullPath = root + path + "*.*";
				if( (hFile = _findfirst64( fullPath.c_str(), &c_file )) != -1L )
				{
					// Find directories.
					do {
						if (c_file.attrib & _A_SUBDIR)
						{
							// If recursive.
							if (c_file.name[0] != '.')
							{
								if (ScanDirectoryRecursive( root,path + c_file.name + "\\",file,listFiles,recursive ))
									anyFound = true;
							}
						}
					}	while (_findnext64( hFile, &c_file ) == 0);
					_findclose( hFile );
				}
			}

			return anyFound;
		}

		bool juFileEnum::ScanDirectory( const tstring &path,const tstring &file,std::vector<tstring> &listFiles, bool recursive )
		{
			return ScanDirectoryRecursive(path,"",file,listFiles,recursive );
		}
#endif
	}
}

