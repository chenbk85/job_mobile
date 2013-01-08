// jPak.cpp : DLL 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "jc\\jcSizer.h"
#include "jPak.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <jc\\StringUtils.h>
#include "base/jXmlDictionary.h"


/////////////////////////////////////////////////////

#ifndef _XBOX
#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
#else
#include <xtl.h>
#endif

#ifdef LINUX
#include <sys/dir.h>
#include <sys/io.h>
#else
#	include <direct.h>
#	include <io.h>
#endif

#include "StreamEngine.h"
#include "jc/jcMemoryManager.h"
_ACCESS_POOL;


using namespace nMech;

volatile float __f__=10;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	__f__++;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

namespace nMech
{
	StringID g_Current_LogLevel_jStringID = jx(jPak);

	namespace nPAK
	{

		CMTSafeHeap* g_pSmallHeap;
		CMTSafeHeap* g_pBigHeap;
		enum {
			eSMALLHEAPSIZE =
#ifndef _TEST_
			0x10000 // 64 Kb
#else
			0 // Unlimited
#endif
		};
#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif

		jPak *g_pPak;
		extern "C"
		{
			JPAK_API void* jCreateInterface(jIE* pE)
			{
				// this heap is used for small allocations - the queues
				// allocate 1 page, grow max to 64 kbytes
				g_pSmallHeap = new CMTSafeHeap(0x1000, eSMALLHEAPSIZE);

				// this heap is used for big allocations - the chunks to be loaded
				// perhaps we won't use this, so don't commit initially; grow up to 16 meg 
				// - we shouldn't need more at a time just for allocating memory to read pieces of files
				g_pBigHeap = new CMTSafeHeap(0, 0);

				nFileSystem::jFolder dm;
				dm.GotoStartDir();
				nInterface::g_pjIPak= g_pPak = new jPak(pE->GetDoc());
				g_pPak->Init("");
				g_pPak->RecordFileOpen( pE->GetAttrVar(_T("RecordFile"))->intValue() );
				tfname_t buf;
				cstr szPath = pE->GetAttr(jS(PATH));
				assert(szPath );
				cstr szExt = pE->GetAttr(jS(EXT));
				assert(szExt);

				jt_sprintf(buf, _T("*.%s") , szExt);
				g_pPak->OpenPacks( jA(buf ));
				jt_sprintf(buf, _T("%s/*.%s"),szPath, szExt);
				g_pPak->OpenPacks("", jA(buf) );
				return nInterface::g_pjIPak;
			}
			JPAK_API void jDeleteInterface()
			{
				SAFE_DELETE(g_pPak)
					SAFE_DELETE(g_pSmallHeap);
				SAFE_DELETE(g_pBigHeap);
			}

			JPAK_API acstr jGetModuleOwnerName()
			{
				return "icandoit";
			}

		}

		/////////////////////////////////////////////////////
		// Initializes the jcPak system;
		//   pVarPakPriority points to the variable, which is, when set to 1,
		//   signals that the files from pak should have higher priority than filesystem files
		jPak::jPak(jID* pD)
			:m_setCachedFiles (CCachedFileDataOrder(), CachedFileDataAllocator(g_pSmallHeap))
			,m_bRememberOpenedFiles(false)
			,m_mapMissingFiles ( std::less<string>(), MissingFileMapAllocator(g_pBigHeap) )
		{
			m_pvPriority = jCV(jIPak,sys_PakPriority,0,0,"If set to 1, tells jcPak to try to open the file in pak first, then go to file system");
			m_pvReadSlice = jCV(jIPak,sys_PakReadSlice,0,0
				,"If non-0, means number of kilobytes to use to read files in portions. Should only be used on Win9x kernels");
			m_pvLogMissingFiles = jCV(jIPak,sys_PakLogMissingFiles,0,0
				,"If non-0, missing file names go to mastercd/MissingFilesX.log. 1) only resulting report  2) \
				 run-time report is ON, one entry per file  3) full run-time report ");

			afname_t szCurrentDir;
			if (GetCurrentDirectoryA(sizeof(szCurrentDir), szCurrentDir))
			{
				// normalize it (lower-char with forward slashes and trailing slash)
				char* p;
				for (p = szCurrentDir; *p; ++p)
				{
					if (*p == g_cNonNativeSlash)
						*p = g_cNativeSlash;
					else
						*p = tolower(*p);
				}
				// add the trailing slash if needed
#if defined(LINUX)
				if (p > szCurrentDir && (p[-1] != g_cNativeSlash && p[-1] != g_cNonNativeSlash))
#else
				if (p > szCurrentDir && p[-1] != g_cNativeSlash)
#endif
				{
					*p=g_cNativeSlash;
					*++p = '\0';
				}
				m_strMasterCDRoot = szCurrentDir;
			}
		}

		//////////////////////////////////////////////////////////////////////////
		void jPak::AddMod(const char* szMod)
		{
			// remember the prefix to use to conver the file names
			string strPrepend = szMod;
			for (string::iterator it = strPrepend.begin(); it != strPrepend.end(); ++it)
			{
				if (*it==g_cNonNativeSlash)
					*it = g_cNativeSlash;
				else
					*it = tolower(*it);
			}
#if defined(LINUX)
			if (!strPrepend.empty() && (strPrepend[strPrepend.length()-1] != g_cNativeSlash && strPrepend[strPrepend.length()-1] != g_cNonNativeSlash))
#else
			if (!strPrepend.empty() && strPrepend[strPrepend.length()-1] != g_cNativeSlash)
#endif
				strPrepend += g_cNativeSlash;

			std::vector<string>::iterator strit;
			for (strit = m_arrMods.begin(); strit != m_arrMods.end(); ++strit)
			{
				string &sMOD = *strit;
				if (stricmp(sMOD.c_str(),strPrepend.c_str())==0)
					return; // already added
			}
			m_arrMods.push_back(strPrepend);
			GetjILog()->Log(jLogL,_T("Added MOD %s to jcPak"),jT(strPrepend.c_str()));
		}

		//////////////////////////////////////////////////////////////////////////
		void jPak::RemoveMod(const char* szMod)
		{
			std::vector<string>::iterator it;
			for (it = m_arrMods.begin(); it != m_arrMods.end(); ++it)
			{
				string &sMOD = *it;
				// NOTE: this check may not work with multiple mods, but
				// however multiple mods are not supported...
				if (strstr(sMOD.c_str(),szMod)==0)
				{
					m_arrMods.erase(it);
					break;
				}
			} //it
		}

		//////////////////////////////////////////////////////////////////////////
		jPak::~jPak()
		{
			unsigned numFilesForcedToClose = 0;
			// scan through all open files and close them
			for (ZipPseudoFileArray::iterator itFile = m_arrOpenFiles.begin(); itFile != m_arrOpenFiles.end(); ++itFile)
				if (itFile->GetFile())
				{
					itFile->Destruct();
					++numFilesForcedToClose;
				}

				if (numFilesForcedToClose)
					GetjILog()->Warning(jLogL, _T("\002%u files were forced to close"), numFilesForcedToClose);

				size_t numDatasForcedToDestruct = m_setCachedFiles.size();
				for (size_t i = 0; i < numDatasForcedToDestruct; ++i)
					if (m_setCachedFiles.empty())
						assert (0);
					else
						delete *m_setCachedFiles.begin();

				if (numDatasForcedToDestruct)
					GetjILog()->Warning(jLogL, _T("\002%u cached file data blocks were forced to destruct; they still have references on them, crash possible"), numDatasForcedToDestruct);

				if (!m_arrArchives.empty())
					jERROR(_T("\002 There are %d external references to archive objects: they have dangling pointers and will either lead to memory leaks or crashes"), m_arrArchives.size());

				if (!m_mapMissingFiles.empty())
				{
					FILE* f = fopen ("Missing Files Report.txt", "wt");
					if (f)
					{
						for (MissingFileMap::iterator it = m_mapMissingFiles.begin(); it != m_mapMissingFiles.end(); ++it)
							fprintf (f, "%d\t%s\n", it->second,it->first.c_str());
						fclose(f);
					}
				}
		}


		// makes the path lower-case and removes the duplicate and non native slashes
		// may make some other fool-proof stuff
		// may NOT write beyond the string buffer (may not make it longer)
		// returns: the pointer to the ending terminator \0
		char* jPak::BeautifyPath(char* dst)
		{
			// make the path lower-letters and with native slashes
			char*p,*q;
			// there's a special case: two slashes at the beginning mean UNC filepath
			p = q = dst;
			if (*p == g_cNonNativeSlash || *p == g_cNativeSlash)
				++p,++q; // start normalization/beautifications from the second symbol; if it's a slash, we'll add it, too

			while (*p)
			{
				if (*p == g_cNonNativeSlash || *p == g_cNativeSlash)
				{
					*q = g_cNativeSlash;
					++p,++q;
					while(*p == g_cNonNativeSlash || *p == g_cNativeSlash)
						++p; // skip the extra slashes
				}
				else
				{
					*q = tolower (*p);
					++q,++p;
				}
			}
			*q = '\0';
			return q;
		}

		//////////////////////////////////////////////////////////////////////////
		// given the source relative path, constructs the full path to the file according to the flags
		const char* jPak::AdjustFileName(const char *src, char dst[g_nMaxPath], unsigned nFlags,bool *bFoundInPak)
		{
			nFileSystem::jFolder dm;
			dm.GotoStartDir();
			// in many cases, the path will not be long, so there's no need to allocate so much..
			// I'd use _alloca, but I don't like non-portable solutions. besides, it tends to confuse new developers. So I'm just using a big enough array
			char szNewSrc[g_nMaxPath];
			strcpy(szNewSrc, src);
			BeautifyPath(szNewSrc);
			if (!_fullpath (dst, szNewSrc, g_nMaxPath))
			{
				src = szNewSrc;
				jERROR(_T("\002Cannot transform file name %s to absolute path, resorting to desparate measures!"), src);
				if (src[0] == '.' && (src[1] == g_cNativeSlash || src[1] == g_cNonNativeSlash))
					src+=2;
#ifdef _XBOX
				if (src[0] && src[1] != ':')
					strcpy (dst, "d:\\");
				dst += 3;
#endif
				strcpy(dst, src);
				size_t len = strlen(dst);
				for (size_t n=0; dst[n]; n++)
				{
					if ( dst[n] == '\\' )
						dst[n] = '/';

					if (n > 8 && n+3 < len && dst[n] == '/' && dst[n+1] == '.' && dst[n+2] == '.')
					{
						size_t m = n+3;
						n--;
						while (dst[n] != '/')
						{
							n--;
							if (!n)
								break;
						}
						if (n)
						{
							memmove(&dst[n], &dst[m], len-m+1);
							len -= m-n;
							n--;
						}
					}
				}
			}

			char* pEnd = BeautifyPath(dst);

#if defined(LINUX)
			//we got to adjust the filename and fetch the case sensitive one
			string adjustedFilename(dst);
			if(getFilenameNoCase(dst, adjustedFilename))
			{
				//file does exist, copy the real filename
				strcpy(dst, adjustedFilename.c_str());
			}
			if ((nFlags & FLAGS_ADD_TRAILING_SLASH) && pEnd > dst && (pEnd[-1]!=g_cNativeSlash && pEnd[-1]!=g_cNonNativeSlash))
#else
			// p now points to the end of string
			if ((nFlags & FLAGS_ADD_TRAILING_SLASH) && pEnd > dst && pEnd[-1]!=g_cNativeSlash)
#endif
			{
				*pEnd = g_cNativeSlash;
				*++pEnd = '\0';
			}

			unsigned nLength = pEnd - dst;

			if (bFoundInPak)
				bFoundInPak=false;

			if (nFlags & FLAGS_PATH_REAL)
				return dst;

			if (m_arrMods.empty())
				return dst; // no mods - no need to search or modify the path

			// now replace the root directory name (C:\Mastercd\)
			// with the filesystem prefix ("" by default).
			// try to search through the MOD directories, if it makes sense
#if defined(LINUX)
			if (!(nFlags&FLAGS_IGNORE_MOD_DIRS) && nLength > m_strMasterCDRoot.length() && !comparePathNames(dst, m_strMasterCDRoot.c_str(), m_strMasterCDRoot.length()))
#else
			if (!(nFlags&FLAGS_IGNORE_MOD_DIRS) && nLength > m_strMasterCDRoot.length() && !memcmp(dst, m_strMasterCDRoot.c_str(), m_strMasterCDRoot.length()))
#endif
			{
				// the previous mod prepend string length: as we move the string from through the loop,
				// we keep the track of the actual path substring here.
				size_t nPrevModLength = 0;

				std::vector<string>::reverse_iterator it;
				for (it = m_arrMods.rbegin(); it != m_arrMods.rend(); ++it)
				{
					string &strPrepend = *it;
					memmove (dst+strPrepend.length()+m_strMasterCDRoot.length(), dst+m_strMasterCDRoot.length()+nPrevModLength, nLength-m_strMasterCDRoot.length()+1);
					memcpy (dst+m_strMasterCDRoot.length(), strPrepend.c_str(), strPrepend.length());

					// if there's only one MOD, there's actually no need to determine whether this file exists or not
					//if (m_arrMods.size() == 1)
					//	return dst;

					//GetjILog()->Log(jLogL  ,  _T("searching for %s"),dst);

					nPrevModLength = strPrepend.length();
					if (GetFileAttributesA (dst) != INVALID_FILE_ATTRIBUTES) // there's such file in FS
					{
						if (bFoundInPak)
							*bFoundInPak=false;
						break;
					}

					// [marco] NOTE: looks like there is a flow in the implementation of this in jcPak -
					// this function never finds the file in the pak even though the file is there,
					// because of the prepended mod subdirs; however since the file is "not found"
					// in the "mod paks", it is opened correctly afterwards regardless of this, because
					// then it searches through zip files in reverse order and the mod paks are the latest
					// paks opened, so the file is found, unless replaced by other files, which is kinda what
					// we want to achieve with the pak system.
					if (HasFileEntry(dst)) // there's such file in the pak
					{
						if (bFoundInPak)
							*bFoundInPak=true;
						break;
					}
				}

				if (it == m_arrMods.rend())
				{
					if (nFlags & FLAGS_ONLY_MOD_DIRS)
						return NULL; // we didn't find the corresponding file
					else
					{
						string strPrepend; // = "";
						// there's no mod where there is such a file - fallback to the "" mod
						memmove (dst+strPrepend.length()+m_strMasterCDRoot.length(), dst+m_strMasterCDRoot.length()+nPrevModLength, nLength-m_strMasterCDRoot.length()+1);
						memcpy (dst+m_strMasterCDRoot.length(), strPrepend.c_str(), strPrepend.length());
					}
				}
			}
			else
				if (nFlags & FLAGS_ONLY_MOD_DIRS) // only in MOD dirs, but no MODs found
					return NULL;

			return dst; // the last MOD scanned, or the absolute path outside MasterCD
		}
		/*
		FILETIME jPak::GetFileTime(const char * szFileName)
		{
		FILETIME writetime;
		memset(&writetime, 0, sizeof(writetime));
		#ifdef WIN32
		HANDLE hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ,
		NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
		{
		::GetFileTime(hFile, NULL, NULL, &writetime);
		CloseHandle(hFile);
		}
		#endif
		return writetime;
		}
		*/
		/*bool jPak::IsOutOfDate(const char * szCompiledName, const char * szMasterFile)
		{
		FILE * f = FOpen(szMasterFile,"rb");
		if (f)
		FClose(f);
		else
		return (false);

		assert(f > m_OpenFiles.Num());

		f = FOpen(szCompiledName,"rb");
		if (f)
		FClose(f);
		else
		return (true);

		assert(f > m_OpenFiles.Num());

		#ifdef WIN32

		HANDLE status1 = CreateFile(szCompiledName,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);

		HANDLE status2 = CreateFile(szMasterFile,GENERIC_READ,FILE_SHARE_READ,
		NULL,OPEN_EXISTING,FILE_FLAG_SEQUENTIAL_SCAN,NULL);

		FILETIME writetime1,writetime2;

		GetFileTime(status1,NULL,NULL,&writetime1);
		GetFileTime(status2,NULL,NULL,&writetime2);

		CloseHandle(status1);
		CloseHandle(status2);

		if (CompareFileTime(&writetime1,&writetime2)==-1)
		return(true);

		return (false);
		#else

		return (false);

		#endif
		}*/


		//////////////////////////////////////////////////////////////////////////
		FILE *jPak::FOpen(const char *pName, const char *szMode,char *szFileGamePath,int nLen)
		{
			AUTO_LOCK(m_csMain);
			FILE *fp = NULL;
			char szFullPathBuf[g_nMaxPath];
			const char* szFullPath = AdjustFileName(pName, szFullPathBuf, 0);
			if (nLen>g_nMaxPath)
				nLen=g_nMaxPath;
			strncpy(szFileGamePath,szFullPath,nLen);
			fp = fopen (szFullPath, szMode);

			if (fp)
				RecordFile( pName );
			else
				OnMissingFile(pName);
			return (fp);
		}


		//////////////////////////////////////////////////////////////////////////
		FILE *jPak::FOpen(const char *pName, const char *szMode,unsigned nFlags2)
		{
			AUTO_LOCK(m_csMain);
			FILE *fp = NULL;
			char szFullPathBuf[g_nMaxPath];

			// get the priority into local variable to avoid it changing in the course of
			// this function execution (?)
			int nVarPakPriority = GetPriority();

			// maybe this file is in MOD dir - then it'll have the preference anyway

			if (!m_arrMods.empty())
			{
				bool bFoundInPak;
				const char* szModPath = AdjustFileName (pName, szFullPathBuf, FLAGS_ONLY_MOD_DIRS,&bFoundInPak);

				// [marco] will have the preference, when outside the pak, ONLY if indevmode
				// in non-devmode it always has preference inside the pak, so that we can use
				// security checks - if the file is not found in the pak and we are not in
				// devmode, do not open it

				if (szModPath && (bFoundInPak || (!bFoundInPak && !nVarPakPriority)))
				{
					fp = fopen (szModPath, szMode);
					if (fp)
					{
						RecordFile(pName);
						return fp;
					}
					else
					{
						assert (0);
						// this is strange - AdjustFileName() found a file, but fopen() didn't find one.. this should be impossible with FLAGS_ONLY_MOD_DIRS
					}
				}
			}

			const char *szFullPath = AdjustFileName(pName, szFullPathBuf, 0);

			if (!nVarPakPriority) // if the file system files have priority now..
			{
				fp = fopen (szFullPath, szMode);
				if (fp)
				{
					RecordFile( pName );
					return fp;
				}
			}

#if defined(LINUX)
			const int _fmode = _O_BINARY;//it does not exist on linux
#endif
			unsigned nFlags = (_fmode & (_O_TEXT|_O_BINARY))|_O_RDONLY;

			// check the szMode
			for (const char* pModeChar = szMode; *pModeChar; ++pModeChar)
				switch (*pModeChar)
			{
				case 'r':
					nFlags &= ~(_O_WRONLY|_O_RDWR);
					// read mode is the only mode we can open the file in
					break;
				case 'w':
					nFlags |= _O_WRONLY;
					break;
				case 'a':
					nFlags |= _O_RDWR;
					break;
				case '+':
					nFlags |= _O_RDWR;
					break;

				case 'b':
					nFlags &= ~_O_TEXT;
					nFlags |= _O_BINARY;
					break;
				case 't':
					nFlags &= ~_O_BINARY;
					nFlags |= _O_TEXT;
					break;

				case 'c':
				case 'C':
					nFlags |= CZipPseudoFile::_O_COMMIT_FLUSH_MODE;
					break;
				case 'n':
				case 'N':
					nFlags &= ~CZipPseudoFile::_O_COMMIT_FLUSH_MODE;
					break;

				case 'S':
					nFlags |= _O_SEQUENTIAL;
					break;

				case 'R':
					nFlags |= _O_RANDOM;
					break;

				case 'T':
					nFlags |= _O_SHORT_LIVED;
					break;

				case 'D':
					nFlags |= _O_TEMPORARY;
					break;

				case 'x':
				case 'X':
					nFlags2 |= FOPEN_HINT_DIRECT_OPERATION;
					break;
			}

			if (nFlags & (_O_WRONLY|_O_RDWR))
			{
				// we need to open the file for writing, but we failed to do so.
				// the only reason that can be is that there are no directories for that file.
				// now create those dirs
				if (!MakeDir (nMech::nString::nFileUtil::GetParentDirectory(string(szFullPath)).c_str()))
					return NULL;

				FILE *file = fopen (szFullPath, szMode);
				if (file)
					RecordFile( pName );
				else
				{
					if (!(nFlags2&FOPEN_HINT_QUIET))
						OnMissingFile(pName);
				}
				return file;
			}

			// try to open the pseudofile from one of the zips
			CCachedFileData_AutoPtr pFileData = GetFileData (szFullPath);
			if (!pFileData)
			{
				if (nVarPakPriority) // if the pak files had more priority, we didn't attempt fopen before- try it now
				{
					fp = fopen (szFullPath, szMode);
					if (fp)
					{
						RecordFile( pName );
						return fp;
					}
				}
				if (!(nFlags2&FOPEN_HINT_QUIET))
					OnMissingFile (pName);
				return NULL; // we can't find such file in the pack files
			}

			RecordFile( pName );

			size_t nFile;
			// find the empty slot and open the file there; return the handle
			for (nFile = 0; nFile < m_arrOpenFiles.size() && m_arrOpenFiles[nFile].GetFile(); ++nFile)
				continue;

			if (nFile == m_arrOpenFiles.size())
			{
				m_arrOpenFiles.resize (nFile+1);
			}

			if (pFileData != NULL && (nFlags2 & FOPEN_HINT_DIRECT_OPERATION))
				nFlags |= CZipPseudoFile::_O_DIRECT_OPERATION;
			m_arrOpenFiles[nFile].Construct (pFileData, nFlags);
			return (FILE*)(nFile + g_nPseudoFileIdxOffset); // the handle to the file
		}

		//////////////////////////////////////////////////////////////////////////
		// given the file name, searches for the file entry among the zip files.
		// if there's such file in one of the zips, then creates (or used cached)
		// CCachedFileData instance and returns it.
		// The file data object may be created in this function,
		// and it's important that the autoptr is returned: another thread may release the existing
		// cached data before the function returns
		// the path must be absolute normalized lower-case with forward-slashes
		CCachedFileData_AutoPtr jPak::GetFileData(const char* szName)
		{
#if defined(LINUX)
			replaceDoublePathFilename((char*)szName);
#endif
			unsigned nNameLen = (unsigned)strlen(szName);
			AUTO_LOCK(m_csZips);
			// scan through registered pak files and try to find this file
			for (ZipArray::reverse_iterator itZip = m_arrZips.rbegin(); itZip != m_arrZips.rend(); ++itZip)
			{
				size_t nBindRootLen = itZip->strBindRoot.length();
#if defined(LINUX)
				if (nNameLen > nBindRootLen	&&!comparePathNames(itZip->strBindRoot.c_str(), szName, nBindRootLen))
#else
				if (nNameLen > nBindRootLen	&&!memcmp(itZip->strBindRoot.c_str(), szName, nBindRootLen))
#endif
				{
					//const char	*szDebug1=itZip->strBindRoot.c_str();
					//const char	*szDebug2=itZip->pZip->GetFilePath();

					ZipDir::FileEntry* pFileEntry = itZip->pZip->FindFile (szName+nBindRootLen);
					if (pFileEntry)
					{
						CCachedFileData Result(NULL, itZip->pZip, pFileEntry);
						AUTO_LOCK(m_csCachedFiles);

						CachedFileDataSet::iterator it = m_setCachedFiles.find(&Result);
						if (it != m_setCachedFiles.end())
						{
							assert((*it)->GetFileEntry() == pFileEntry); // cached data
							return *it;
						}
						else
						{
							CCachedFileData* pRet = new CCachedFileData (this, itZip->pZip, pFileEntry);
							return pRet;
						}
					}
				}
			}
			return NULL;
		}


		//////////////////////////////////////////////////////////////////////////
		// tests if the given file path refers to an existing file inside registered (opened) packs
		// the path must be absolute normalized lower-case with forward-slashes
		bool jPak::HasFileEntry (const char* szPath)
		{
			unsigned nNameLen = (unsigned)strlen(szPath);
			AUTO_LOCK(m_csZips);
			// scan through registered pak files and try to find this file
			for (ZipArray::reverse_iterator itZip = m_arrZips.rbegin(); itZip != m_arrZips.rend(); ++itZip)
			{
				size_t nBindRootLen = itZip->strBindRoot.length();
				//const char	*szDebug1=itZip->strBindRoot.c_str();
				//const char	*szDebug2=itZip->pZip->GetFilePath();
#if defined(LINUX)
				if (nNameLen > nBindRootLen	&&!comparePathNames(itZip->strBindRoot.c_str(), szPath, nBindRootLen))
#else
				if (nNameLen > nBindRootLen	&&!memcmp(itZip->strBindRoot.c_str(), szPath, nBindRootLen))
#endif
				{
					ZipDir::FileEntry* pFileEntry = itZip->pZip->FindFile (szPath+nBindRootLen);
					if (pFileEntry)
					{
						return true;
					}
				}
			}
			return false;
		}


		long jPak::FTell(FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].FTell();
			else
				return ftell(hFile);
		}
		long jPak::FileLen(FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			long iLen,iRet;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
			{
				iLen = m_arrOpenFiles[nPseudoFile].FTell();
				m_arrOpenFiles[nPseudoFile].FSeek(0, SEEK_END);
				iRet = m_arrOpenFiles[nPseudoFile].FTell();
				m_arrOpenFiles[nPseudoFile].FSeek(iLen,SEEK_SET);
			}
			else
			{
				iLen = ftell(hFile);
				fseek(hFile , 0, SEEK_END);
				iRet = ftell(hFile);
				fseek(hFile , iLen, SEEK_SET);
			}
			return iRet;
		}

		// returns the path to the archive in which the file was opened
		const char* jPak::GetFileArchivePath (FILE* hFile)
		{
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].GetArchivePath();
			else
				return NULL;
		}

		FILETIME UnixTimeToFileTime(time_t t)
		{
			// Note that LONGLONG is a 64-bit value
#if defined(LINUX)
			LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000ll;
#else
			LONGLONG ll = Int32x32To64(t, 10000000) + 116444736000000000;
#endif
			return (FILETIME&)ll;
		}


		// returns the file modification time
		FILETIME jPak::GetModificationTime(FILE* hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].GetModificationTime();
			else
			{
				// TODO/TIME: implement retrieving FILETIME out of the real file handle
#if defined(LINUX)
				struct stat64 st;
				_fstat64(fileno(hFile), &st);
#else
				struct __stat64 st;
				_fstat64(_fileno(hFile), &st);
#endif
				return UnixTimeToFileTime (st.st_mtime);
			}
		}



		unsigned jPak::FGetSize(FILE* hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].GetFileSize();
			else
			{
				long nSave = ftell (hFile);
				fseek (hFile, 0, SEEK_END);
				long nSize = ftell(hFile);
				fseek (hFile, nSave, SEEK_SET);
				return nSize;
			}
		}

		int jPak::FFlush(FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return 0;
			else
				return fflush(hFile);
		}

		int jPak::FSeek(FILE *hFile, long seek, int mode)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].FSeek(seek, mode);
			else
				return fseek(hFile, seek, mode);
		}

		size_t jPak::FWrite(void *data, size_t length, size_t elems, FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return 0;
			else
				return fwrite(data, length, elems, hFile);
		}

		size_t jPak::FRead(void *pData, size_t nSize, size_t nCount, FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].FRead(pData, nSize, nCount, hFile);
			else
			{
				return fread(pData, nSize, nCount, hFile);
			}
		}

		int jPak::FClose(FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
			{
				m_arrOpenFiles[nPseudoFile].Destruct();
				return 0;
			}
			else
				return fclose(hFile);
		}

		int jPak::FEof(FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].FEof();
			else
				return feof(hFile);
		}

		int jPak::FScanf(FILE *hFile, const char *format, ...)
		{
			AUTO_LOCK(m_csMain);
			va_list arglist;
			va_start(arglist, format);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].FScanfv(format, arglist);
			else
				return 0;//vfscanf(handle, format, arglist);
			va_end(arglist);
		}

		int jPak::FPrintf(FILE *hFile, const char *szFormat, ...)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return 0; // we don't support it now

			va_list arglist;
			va_start(arglist, szFormat);

			return vfprintf(hFile, szFormat, arglist);
		}

		char *jPak::FGets(char *str, int n, FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].FGets(str, n);
			else
				return fgets(str, n, hFile);
		}

		int jPak::Getc(FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].Getc();
			else
				return getc(hFile);
		}

		int jPak::Ungetc(int c, FILE *hFile)
		{
			AUTO_LOCK(m_csMain);
			INT_PTR nPseudoFile = ((INT_PTR)hFile) - g_nPseudoFileIdxOffset;
			if ((UINT_PTR)nPseudoFile < m_arrOpenFiles.size())
				return m_arrOpenFiles[nPseudoFile].Ungetc(c);
			else
				return ungetc(c, hFile);
		}

#ifndef _XBOX
		const char *GetExtension (const char *in)
		{
			while (*in)
			{
				if (*in=='.')
					return in;
				in++;
			}
			return NULL;
		}
#else
		const char *GetExtension (const char *in);
#endif //_XBOX

		//////////////////////////////////////////////////////////////////////////
		intptr_t jPak::FindFirst(const char *pDir, struct _finddata_t *fd)
		{
			AUTO_LOCK(m_csMain);
			char szFullPathBuf[g_nMaxPath];

			//GetjILog()->Log(jLogL  ,  _T("Scanning %s",pDir);
			//const char *szFullPath = AdjustFileName(pDir, szFullPathBuf, 0);
			const char *szFullPath = AdjustFileName(pDir, szFullPathBuf,FLAGS_IGNORE_MOD_DIRS);
			CjcPakFindData_AutoPtr pFindData = new CjcPakFindData(this, szFullPath);
			if (pFindData->empty())
			{
				if (m_arrMods.empty())
					return (-1); // no mods and no files found
			}

			// now scan mod folders as well
			std::vector<string>::reverse_iterator it;
			for (it = m_arrMods.rbegin(); it != m_arrMods.rend(); ++it)
			{
				string &strPrepend = *it;
				string sModFolder=strPrepend+string(pDir);
				const char *szFullPath = AdjustFileName(sModFolder.c_str(), szFullPathBuf,FLAGS_IGNORE_MOD_DIRS);
				//GetjILog()->Log(jLogL  ,  _T("Scanning (2) %s"),szFullPath);
				pFindData->Scan(this,szFullPath);
			} //it

			if (pFindData->empty())
				return (-1);

			m_setFindData.insert (pFindData);
			pFindData->Fetch(fd);
			return (intptr_t)(CjcPakFindData*)pFindData;
		}

		//////////////////////////////////////////////////////////////////////////
		int jPak::FindNext(intptr_t handle, struct _finddata_t *fd)
		{
			AUTO_LOCK(m_csMain);
			//if (m_setFindData.find ((CjcPakFindData*)handle) == m_setFindData.end())
			//	return -1; // invalid handle

			if (((CjcPakFindData*)handle)->Fetch(fd))
				return 0;
			else
				return -1;
		}

		int jPak::FindClose(intptr_t handle)
		{
			AUTO_LOCK(m_csMain);
			m_setFindData.erase ((CjcPakFindData*)handle);
			return 0;
		}

		//======================================================================

		bool jPak::OpenPack(const char* szBindRootIn, const char *szPath, unsigned nFlags)
		{
			char szFullPathBuf[g_nMaxPath];

			const char *szFullPath = AdjustFileName(szPath, szFullPathBuf, nFlags|FLAGS_IGNORE_MOD_DIRS);

			char szBindRootBuf[g_nMaxPath];
			const char* szBindRoot = AdjustFileName(szBindRootIn, szBindRootBuf, FLAGS_ADD_TRAILING_SLASH|FLAGS_IGNORE_MOD_DIRS);

			return OpenPackCommon(szBindRoot, szFullPath, nFlags);
		}

		bool jPak::OpenPack(const char *szPath, unsigned nFlags)
		{
			char szFullPathBuf[g_nMaxPath];

			const char *szFullPath = AdjustFileName(szPath, szFullPathBuf, nFlags|FLAGS_IGNORE_MOD_DIRS);
			string strBindRoot;
			const char *pLastSlash = strrchr(szFullPath, g_cNativeSlash);
			if (pLastSlash)
				strBindRoot.assign (szFullPath, pLastSlash - szFullPath +  1);
			else
			{
				jERROR(_T("\002Pak file %s has absolute path %s, which is strange"), jT(szPath), jT(szFullPath));
				//desc.strFileName = szZipPath;
			}

			return OpenPackCommon(strBindRoot.c_str(), szFullPath, nFlags);
		}

		bool jPak::OpenPackCommon(const char* szBindRoot, const char *szFullPath, unsigned nFlags)
		{
			AUTO_LOCK(m_csZips);
			{
				// try to find this - maybe the pack has already been opened
				for (ZipArray::iterator it = m_arrZips.begin(); it != m_arrZips.end(); ++it)
					if (!stricmp(it->pZip->GetFilePath(), szFullPath)
						&&!stricmp(it->strBindRoot.c_str(), szBindRoot))
						return true; // already opened
			}
			PackDesc desc;
			desc.strBindRoot = szBindRoot;

			desc.pArchive = OpenArchive (szFullPath, jcIArchive::FLAGS_OPTIMIZED_READ_ONLY|jcIArchive::FLAGS_ABSOLUTE_PATHS);
			if (!desc.pArchive)
				return false; // couldn't open the archive

			if (desc.pArchive->GetClassId() == jcArchive::gClassId)
			{
				GetjILog()->Log(jLogL ,_T("Opening pack file %s"),jT(szFullPath));
				desc.pZip = static_cast<jcArchive*>((jcIArchive*)desc.pArchive)->GetCache();
				m_arrZips.push_back(desc);
				return true;
			}
			else
				return false; // don't support such objects yet
		}

		//int gg=1;
		// after this call, the file will be unlocked and closed, and its contents won't be used to search for files
		bool jPak::ClosePack(const char* pName, unsigned nFlags)
		{
			char szZipPathBuf[g_nMaxPath];
			const char* szZipPath = AdjustFileName(pName, szZipPathBuf, nFlags);
			AUTO_LOCK(m_csZips);

			//if (strstr(szZipPath,"huggy_tweak_scripts"))
			//	gg=0;

			for (ZipArray::iterator it = m_arrZips.begin(); it != m_arrZips.end(); ++it)
				if (!stricmp(szZipPath, it->GetFullPath()))
				{
					// this is the pack with the given name - remove it, and if possible it will be deleted
					// the zip is referenced from the archive and *it; the archive is referenced only from *it
					//
					// the pZip (cache) can be referenced from stream engine and pseudo-files.
					// the archive can be referenced from outside
					bool bResult = (it->pZip->NumRefs() == 2) && it->pArchive->NumRefs() == 1;
					if (bResult)
					{
						GetjILog()->Log(jLogL,_T("Closing pack file %s"),jT(szZipPath));
						m_arrZips.erase (it);
					}
					return bResult;
				}
				return true;
		}


		bool jPak::OpenPacks(const char *pWildcardIn, unsigned nFlags)
		{
			char cWorkBuf[g_nMaxPath];
			AdjustFileName(pWildcardIn, cWorkBuf, nFlags|FLAGS_COPY_DEST_ALWAYS);
			string strBindRoot = nMech::nString::nFileUtil::GetParentDirectory<string>(cWorkBuf);
			strBindRoot += g_cNativeSlash;
			return OpenPacksCommon(strBindRoot.c_str(), cWorkBuf, nFlags);
		}

		bool jPak::OpenPacks(const char* szBindRoot, const char *pWildcardIn, unsigned nFlags)
		{
			char cWorkBuf[g_nMaxPath];
			AdjustFileName(pWildcardIn, cWorkBuf, nFlags|FLAGS_COPY_DEST_ALWAYS);
			char cBindRootBuf[g_nMaxPath];
			const char* pBindRoot = AdjustFileName(szBindRoot, cBindRootBuf, nFlags|FLAGS_ADD_TRAILING_SLASH);
			return OpenPacksCommon(pBindRoot, cWorkBuf, nFlags);
		}

		bool jPak::OpenPacksCommon(const char* szDir, char *cWork, unsigned nFlags)
		{
			__finddata64_t fd;
			intptr_t h = _findfirst64 (cWork, &fd);

			// where to copy the filenames to form the path in cWork
			char* pDestName = strrchr (cWork, g_cNativeSlash);
			if (!pDestName)
				pDestName = cWork;
			else
				++pDestName;
			if (h != -1)
			{
				std::vector<string> files;
				do {
					strcpy (pDestName, fd.name);
					std::string sfile = strlwr(cWork);
					files.push_back(strlwr(cWork));
				}
				while(0 == _findnext64 (h, &fd));

				// Open files in alphabet order.
				std::sort( files.begin(),files.end() );
				for (int i = 0; i < files.size(); i++)
				{
					OpenPackCommon(szDir, files[i].c_str(), nFlags);
				}

				_findclose (h);
				return true;
			}

			return false;
		}


		bool jPak::ClosePacks(const char *pWildcardIn, unsigned nFlags)
		{
			bool bOk = true;
			__finddata64_t fd;
			char cWorkBuf[g_nMaxPath];
			const char* cWork = AdjustFileName(pWildcardIn, cWorkBuf, nFlags);
			intptr_t h = _findfirst64 (cWork, &fd);
			string strDir = nMech::nString::nFileUtil::GetParentDirectory<string>(pWildcardIn);
			if (h != -1)
			{
				do {
					if (!ClosePack((strDir + "\\" + fd.name).c_str(), nFlags))
						bOk = false;
				} while(0 == _findnext64 (h, &fd));
				_findclose (h);
				return true;
			}
			return false;
		}


		bool jPak::InitPack(const char *szBasePath, unsigned nFlags)
		{
			string strPath = szBasePath;
			if (szBasePath && szBasePath[0])
				strPath += "\\*.cpk";
			else
				strPath += "*.cpk";

			char cWorkBuf[g_nMaxPath];
			const char* cWork = AdjustFileName(strPath.c_str(), cWorkBuf, nFlags);

			bool bFind = false;
			struct __finddata64_t fileinfo;
			intptr_t handle = _findfirst64 (cWork, &fileinfo);
			if (handle == -1)
				return true;
			do
			{
				if (szBasePath && szBasePath[0])
					_snprintf(cWorkBuf, sizeof(cWorkBuf), "%s\\%s", szBasePath, fileinfo.name);
				else
					strcpy(cWorkBuf, fileinfo.name);
				if (!OpenPack(cWorkBuf))
				{
					jERROR(_T("\003Cannot bind pak file %s"), jT(cWork));
				}
			} while (_findnext64( handle, &fileinfo ) != -1);
			_findclose (handle);

			return true;
		}

		/////////////////////////////////////////////////////
		bool jPak::Init(const char *szBasePath)
		{
			return InitPack(szBasePath);
		}

		void jPak::Release()
		{
		}

		int CZipPseudoFile::FSeek (long nOffset, int nMode)
		{
			if (!m_pFileData)
				return -1;

			switch (nMode)
			{
			case SEEK_SET:
				m_nCurSeek = nOffset;
				break;
			case SEEK_CUR:
				m_nCurSeek += nOffset;
				break;
			case SEEK_END:
				m_nCurSeek = GetFileSize() - nOffset;
				break;
			default:
				assert(0);
				return -1;
			}
			if (m_fDirect)
				fseek (m_fDirect, m_nCurSeek + GetFile()->GetFileDataOffset(), SEEK_SET);
			return 0;
		}

		size_t CZipPseudoFile::FRead (void* pDest, size_t nSize, size_t nCount, FILE* hFile)
		{
			if (!GetFile())
				return 0;

			size_t nTotal = nSize * nCount;
			if (!nTotal || (unsigned)m_nCurSeek >= GetFileSize())
				return 0;

			if (nTotal > GetFileSize() - m_nCurSeek)
			{
				nTotal = GetFileSize() - m_nCurSeek;
				if (nTotal < nSize)
					return 0;
				nTotal -= nTotal % nSize;
			}

			if (m_fDirect)
			{
				m_nCurSeek += nTotal;
				//return fread (pDest, nSize, nCount, m_fDirect);

				// FIX [Carsten]: nTotal holds the amount of bytes we need to read!
				// Since we're in a zip archive it's very likely that we read more than actually belongs to hFile.
				// Therefore nTotal was correct in the previous "if" branch in case of we're reading over the end of the file.
				return fread (pDest, 1, nTotal, m_fDirect);
			}
			else
			{
				unsigned char * pSrc = (unsigned char *)GetFile()->GetData();
				if (!pSrc)
					return 0;
				pSrc += m_nCurSeek;

				if (!(m_nFlags & _O_TEXT))
					memcpy(pDest, pSrc, nTotal);
				else
				{
					unsigned char *itDest = (unsigned char *)pDest;
					unsigned char *itSrc = pSrc, *itSrcEnd = pSrc + nTotal;
					for (; itSrc != itSrcEnd; ++itSrc)
					{
						if (*pSrc != 0xd)
							*(itDest++) = *itSrc;
					}
					m_nCurSeek += nTotal;
					return itDest - (unsigned char*) pDest;
				}
				m_nCurSeek += nTotal;
			}
			return nTotal / nSize;
		}

		int CZipPseudoFile::FEof()
		{
			return (unsigned)m_nCurSeek >= GetFileSize();
		}

		int CZipPseudoFile::FScanfv (const char* szFormat, va_list args)
		{
			if (!GetFile())
				return 0;
			char *pSrc = (char *)GetFile()->GetData();
			if (!pSrc)
				return 0;
			// now scan the pSrc+m_nCurSeek
			return 0;
		}

		char* CZipPseudoFile::FGets(char* pBuf, int n)
		{
			if (!GetFile())
				return NULL;
			char *pData = (char *)GetFile()->GetData();
			if (!pData)
				return NULL;
			int nn = 0;
			int i;
			for (i=0; i<n; i++)
			{
				if (i+m_nCurSeek == GetFileSize())
					break;
				char c = pData[i+m_nCurSeek];
				if (c == 0xa)
				{
					pBuf[nn++] = c;
					i++;
					break;
				}
				else
					if (c == 0xd)
						continue;
				pBuf[nn++] = c;
			}
			pBuf[nn] = 0;
			m_nCurSeek += i;
			if (m_nCurSeek == GetFileSize())
				return NULL;
			return pBuf;
		}

		int CZipPseudoFile::Getc()
		{
			if (!GetFile())
				return EOF;
			char *pData = (char *)GetFile()->GetData();
			if (!pData)
				return EOF;
			int nn = 0;
			int c = EOF;
			int i;
			for (i=0; i<1; i++)
			{
				if (i+m_nCurSeek == GetFileSize())
					return c;
				c = pData[i+m_nCurSeek];
				break;
			}
			m_nCurSeek += i;
			return c;
		}

		int CZipPseudoFile::Ungetc(int c)
		{
			if (m_nCurSeek <= 0)
				return EOF;
			m_nCurSeek--;
			return c;
		}

		CCachedFileData::CCachedFileData(class jPak* pPak, ZipDir::Cache*pZip, ZipDir::FileEntry* pFileEntry)
		{
			m_pPak = pPak;
			m_pFileData = NULL;
			m_nRefCounter = 0;
			m_pZip = pZip;
			m_pFileEntry = pFileEntry;

			if (pPak)
				pPak->Register (this);
		}

		CCachedFileData::~CCachedFileData()
		{
			if (m_pPak)
				g_pPak->Unregister (this);

			// forced destruction
			if (m_pFileData)
			{
				m_pZip->Free (m_pFileData);
				m_pFileData = NULL;
			}

			m_pZip = NULL;
			m_pFileEntry = NULL;
		}

		// return the data in the file, or NULL if error
		void* CCachedFileData::GetData(bool bRefreshCache)
		{
			// first, do a "dirty" fast check without locking the critical section
			// in most cases, the data's going to be already there, and if it's there,
			// nobody's going to release it until this object is destructed.
			if (bRefreshCache && !m_pFileData)
			{
				assert ((bool)m_pZip);
				assert (m_pFileEntry && m_pZip->IsOwnerOf(m_pFileEntry));
				// Then, lock it and check whether the data is still not there.
				// if it's not, allocate memory and unpack the file
				CCritSection& csCachedFileDataLock = g_pPak->GetCachedFileLock();
				AUTO_LOCK(csCachedFileDataLock);
				if (!m_pFileData)
				{
					m_pFileData = g_pBigHeap->Alloc (m_pFileEntry->desc.lSizeUncompressed, "CCachedFileData::GetData");
					if (ZipDir::ZD_ERROR_SUCCESS != m_pZip->ReadFile (m_pFileEntry, NULL, m_pFileData))
					{
						g_pBigHeap->Free(m_pFileData);
						m_pFileData = NULL;
					}
				}
			}
			return m_pFileData;
		}

		//////////////////////////////////////////////////////////////////////////
		void CjcPakFindData::Scan(class jPak*pPak, const char* szDir)
		{
			// get the priority into local variable to avoid it changing in the course of
			// this function execution
			int nVarPakPriority = pPak->GetPriority();

			if (!nVarPakPriority)
			{
				// first, find the file system files
				ScanFS(pPak,szDir);
				ScanZips(pPak, szDir);
			}
			else
			{
				// first, find the zip files
				ScanZips(pPak, szDir);
				ScanFS(pPak,szDir);
			}
		}

		//////////////////////////////////////////////////////////////////////////
		CjcPakFindData::CjcPakFindData (class jPak*pPak, const char* szDir)
		{
			Scan(pPak,szDir);
		}

		//////////////////////////////////////////////////////////////////////////
		void CjcPakFindData::ScanFS(jPak*pPak, const char *szDirIn)
		{
			//char cWork[jPak::g_nMaxPath];
			//pPak->AdjustFileName(szDirIn, cWork);

			__finddata64_t fd;
#ifdef WIN64
			memset (&fd, 0, sizeof(fd));
#endif
			intptr_t nFS = _findfirst64 (szDirIn, &fd);
			if (nFS == -1)
				return;

			do
			{
				m_mapFiles.insert (FileMap::value_type(fd.name, FileDesc(&fd)));
			}
			while(0 == _findnext64(nFS, &fd));

			_findclose (nFS);
		}

		//////////////////////////////////////////////////////////////////////////
		void CjcPakFindData::ScanZips (jPak* pPak, const char* szDir)
		{
			size_t nLen = strlen(szDir);
			CAutoLock<CCritSection> __AL_Zips(pPak->m_csZips);
			for (jPak::ZipArray::iterator it = pPak->m_arrZips.begin(); it != pPak->m_arrZips.end(); ++it)
			{
				size_t nBindRootLen = it->strBindRoot.length();

#if defined(LINUX)
				if (nLen > nBindRootLen && !comparePathNames(szDir, it->strBindRoot.c_str(), nBindRootLen))
#else
				if (nLen > nBindRootLen && !memcmp(szDir, it->strBindRoot.c_str(), nBindRootLen))
#endif
				{
					// first, find the files
					{
						ZipDir::FindFile fd (it->pZip);
						for(fd.FindFirst (szDir + nBindRootLen); fd.GetFileEntry(); fd.FindNext())
							m_mapFiles.insert (FileMap::value_type(fd.GetFileName(), FileDesc(fd.GetFileEntry())));
					}

					{
						ZipDir::FindDir fd (it->pZip);
						for (fd.FindFirst(szDir + nBindRootLen); fd.GetDirEntry(); fd.FindNext())
							m_mapFiles.insert (FileMap::value_type(fd.GetDirName(), FileDesc ()));
					}
				}
			}
		}

		bool CjcPakFindData::empty() const
		{
			return m_mapFiles.empty();
		}

		bool CjcPakFindData::Fetch(_finddata_t* pfd)
		{
			if (m_mapFiles.empty())
				return false;

			FileMap::iterator it = m_mapFiles.begin();
			memcpy(pfd->name, it->first.c_str(), min(sizeof(pfd->name), it->first.length()+1));
			pfd->attrib = it->second.nAttrib;
			pfd->size   = it->second.nSize;
			pfd->time_access = it->second.tAccess;
			pfd->time_create = it->second.tCreate;
			pfd->time_write  = it->second.tWrite;

			m_mapFiles.erase (it);
			return true;
		}

		CjcPakFindData::FileDesc::FileDesc (struct _finddata_t* fd)
		{
			nSize   = fd->size;
			nAttrib = fd->attrib;
			tAccess = fd->time_access;
			tCreate = fd->time_create;
			tWrite  = fd->time_write;
		}

		// the conversions in this function imply that we don't support
		// 64-bit file sizes or 64-bit time values
		CjcPakFindData::FileDesc::FileDesc (struct __finddata64_t* fd)
		{
			nSize   = (unsigned)fd->size;
			nAttrib = fd->attrib;
			tAccess = (time_t)fd->time_access;
			tCreate = (time_t)fd->time_create;
			tWrite  = (time_t)fd->time_write;
		}


		CjcPakFindData::FileDesc::FileDesc (ZipDir::FileEntry* fe)
		{
			nSize = fe->desc.lSizeUncompressed;
#if defined(LINUX)
			nAttrib = _A_IN_JC_PAK; // files in zip are read-only, and
#else
			nAttrib = _A_RDONLY|_A_IN_JC_PAK; // files in zip are read-only, and
#endif
			tAccess = -1;
			tCreate = -1;
			tWrite  = -1; // we don't need it
		}

		CjcPakFindData::FileDesc::FileDesc ()
		{
			nSize = 0;
#if defined(LINUX)
			nAttrib = _A_SUBDIR;
#else
			nAttrib = _A_SUBDIR | _A_RDONLY;
#endif
			tAccess = -1;
			tCreate = -1;
			tWrite  = -1;
		}

		//! Puts the memory statistics into the given sizer object
		//! According to the specifications in interface jcISizer
		void jPak::GetMemoryStatistics(jcISizer *pSizer)
		{
			AUTO_LOCK(m_csZips);
			size_t nSize = sizeof(*this) /*+ m_arrZips.capacity() * sizeof(ZipArray::value_type)*/;
			for (ZipArray::iterator itZip = m_arrZips.begin(); itZip != m_arrZips.end(); ++itZip)
				nSize += itZip->sizeofThis();

			for (jcPakFindDataSet::iterator itFindData = m_setFindData.begin(); itFindData != m_setFindData.end(); ++itFindData)
				nSize += sizeof(jcPakFindDataSet::value_type) + (*itFindData)->sizeofThis();

			for (CachedFileDataSet::iterator itCachedData = m_setCachedFiles.begin(); itCachedData != m_setCachedFiles.end(); ++itCachedData)
				nSize += sizeof(CachedFileDataSet::value_type) + (*itCachedData)->sizeofThis();

			nSize += m_arrOpenFiles.capacity() * sizeof(CZipPseudoFile);

			pSizer->AddObject(this, nSize);
		}

		size_t CjcPakFindData::sizeofThis()const
		{
			size_t nSize = sizeof(*this);
			for (FileMap::const_iterator it = m_mapFiles.begin(); it != m_mapFiles.end(); ++it)
			{
				nSize += sizeof(FileMap::value_type);
				nSize += it->first.capacity();
			}
			return nSize;
		}


		bool jPak::MakeDir(const char* szPath)
		{
			for (const char*p = szPath; *p; )
			{
				while (*p != g_cNonNativeSlash && *p != g_cNativeSlash && *p)
					++p;

				string strSubdir(szPath, p - szPath);
				// check whether such file or dir exists
				DWORD dwAttr = GetFileAttributesA(strSubdir.c_str());
				if (strSubdir.empty() || strSubdir[strSubdir.length()-1] == ':')
				{
					// this is the disk specification - do nothing, the disk should already exist
				}
				else
					if (dwAttr == INVALID_FILE_ATTRIBUTES)
					{
						if (_mkdir (strSubdir.c_str()))
							return false; // couldn't create such directory
					}
					else
						if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
						{
							// do nothing - such a directory already exists
						}
						else
						{
							// we can't create such a directory because there's already a file with such name
							return false;
						}
						if (*p)
							++p;
			}
			return true;
		}

		//////////////////////////////////////////////////////////////////////////
		// open the physical archive file - creates if it doesn't exist
		// returns NULL if it's invalid or can't open the file
		jcIArchive* jPak::OpenArchive (const char* szPath, unsigned nFlags)
		{
			char szFullPathBuf[jPak::g_nMaxPath];
			const char* szFullPath = AdjustFileName(szPath, szFullPathBuf, nFlags);

			// if it's simple and read-only, it's assumed it's read-only
			if (nFlags & jcIArchive::FLAGS_OPTIMIZED_READ_ONLY)
				nFlags |= jcIArchive::FLAGS_READ_ONLY;

			unsigned nFactoryFlags = 0;
			if (nFlags & jcIArchive::FLAGS_DONT_COMPACT)
				nFactoryFlags |= ZipDir::CacheFactory::FLAGS_DONT_COMPACT;

			if (nFlags & jcIArchive::FLAGS_READ_ONLY)
				nFactoryFlags |= ZipDir::CacheFactory::FLAGS_READ_ONLY;

			if (nFlags & jcIArchive::FLAGS_CREATE_NEW)
				nFactoryFlags |= ZipDir::CacheFactory::FLAGS_CREATE_NEW;

			jcIArchive* pArchive = FindArchive(szFullPath);
			const unsigned nFlagsMustMatch = jcIArchive::FLAGS_RELATIVE_PATHS_ONLY | jcIArchive::FLAGS_ABSOLUTE_PATHS | jcIArchive::FLAGS_READ_ONLY;
			if (pArchive)
			{
				// check for compatibility

				if (!(nFlags & jcIArchive::FLAGS_RELATIVE_PATHS_ONLY) && (pArchive->GetFlags() & jcIArchive::FLAGS_RELATIVE_PATHS_ONLY))
					pArchive->ResetFlags(jcIArchive::FLAGS_RELATIVE_PATHS_ONLY);

				// we found one
				if (nFlags & jcIArchive::FLAGS_OPTIMIZED_READ_ONLY)
				{
					if (pArchive->GetClassId() == jcArchive::gClassId)
						return pArchive; // we can return an optimized archive

					//if (!(pArchive->GetFlags() & jcIArchive::FLAGS_READ_ONLY))
					return NULL; // we can't let it open read-only optimized while it's open for RW access
				}
				else
				{
					if (!(nFlags & jcIArchive::FLAGS_READ_ONLY) && (pArchive->GetFlags() & jcIArchive::FLAGS_READ_ONLY))
					{
						// we don't support upgrading from ReadOnly to ReadWrite
						return NULL;
					}

					return pArchive;
				}

				return NULL;
			}

			string strBindRoot;

			//if (!(nFlags & jcIArchive::FLAGS_RELATIVE_PATHS_ONLY))
			strBindRoot = nMech::nString::nFileUtil::GetParentDirectory<string>(szFullPath);

			try
			{
				ZipDir::CacheFactory factory (g_pBigHeap, ZipDir::ZD_INIT_FAST, nFactoryFlags);
				if (nFlags & jcIArchive::FLAGS_OPTIMIZED_READ_ONLY)
					return new jcArchive (this, strBindRoot, factory.New (szFullPath), nFlags);
				else
					return new jcArchiveRW(this, strBindRoot, factory.NewRW(szFullPath), nFlags);
			}
			catch(ZipDir::Error e)
			{
				jERROR(_T("can't create the archive \"%s\"==\"%s\": error %s (code %d) in %s at %s:%d. %s.")
					, jT(szPath), jT(szFullPath), e.getError(), e.nError, jT(e.szFunction), jT(e.szFile), e.nLine, jT(e.getDescription()) );
				return NULL;
			}
		}


		//////////////////////////////////////////////////////////////////////////
		// Adds a new file to the zip or update an existing one
		// adds a directory (creates several nested directories if needed)
		// compression methods supported are 0 (store) and 8 (deflate) , compression level is 0..9 or -1 for default (like in zlib)
		int jcArchiveRW::UpdateFile (const char* szRelativePath, void* pUncompressed, unsigned nSize, unsigned nCompressionMethod, int nCompressionLevel)
		{
			if (m_nFlags & FLAGS_READ_ONLY)
				return ZipDir::ZD_ERROR_INVALID_CALL;

			char szFullPath[jPak::g_nMaxPath];
			const char*pPath = AdjustPath (szRelativePath, szFullPath);
			if (!pPath)
				return ZipDir::ZD_ERROR_INVALID_PATH;
			return m_pCache->UpdateFile(pPath, pUncompressed, nSize, nCompressionMethod, nCompressionLevel);
		}


		//////////////////////////////////////////////////////////////////////////
		// deletes the file from the archive
		int jcArchiveRW::RemoveFile (const char* szRelativePath)
		{
			if (m_nFlags & FLAGS_READ_ONLY)
				return ZipDir::ZD_ERROR_INVALID_CALL;

			char szFullPath[jPak::g_nMaxPath];
			const char*pPath = AdjustPath (szRelativePath, szFullPath);
			if (!pPath)
				return ZipDir::ZD_ERROR_INVALID_PATH;
			return m_pCache->RemoveFile (pPath);
		}


		//////////////////////////////////////////////////////////////////////////
		// deletes the directory, with all its descendants (files and subdirs)
		int jcArchiveRW::RemoveDir (const char* szRelativePath)
		{
			if (m_nFlags & FLAGS_READ_ONLY)
				return ZipDir::ZD_ERROR_INVALID_CALL;

			char szFullPath[jPak::g_nMaxPath];
			const char*pPath = AdjustPath (szRelativePath, szFullPath);
			if (!pPath)
				return ZipDir::ZD_ERROR_INVALID_PATH;
			return m_pCache->RemoveDir(pPath);
		}

		int jcArchiveRW::RemoveAll()
		{
			return m_pCache->RemoveAll();

		}
		int jcArchive::RemoveAll()
		{
			return ZipDir::ZD_ERROR_INVALID_CALL;

		}

		void jPak::Register (jcIArchive* pArchive)
		{
			ArchiveArray::iterator it = std::lower_bound (m_arrArchives.begin(), m_arrArchives.end(), pArchive, jcArchiveSortByName());
			m_arrArchives.insert (it, pArchive);
		}

		void jPak::Unregister (jcIArchive* pArchive)
		{
			ArchiveArray::iterator it;
			if (m_arrArchives.size() < 16)
			{
				// for small array sizes, we'll use linear search
				it = std::find (m_arrArchives.begin(), m_arrArchives.end(), pArchive);
			}
			else
				it = std::lower_bound (m_arrArchives.begin(), m_arrArchives.end(), pArchive, jcArchiveSortByName());

			if (it != m_arrArchives.end() && *it == pArchive)
				m_arrArchives.erase (it);
			else
				assert (0); // unregistration of unregistered archive
		}

		jcIArchive* jPak::FindArchive (const char* szFullPath)
		{
			ArchiveArray::iterator it = std::lower_bound (m_arrArchives.begin(), m_arrArchives.end(), szFullPath, jcArchiveSortByName());
			if (it != m_arrArchives.end() && !stricmp(szFullPath, (*it)->GetFullPath()))
				return *it;
			else
				return NULL;
		}


		// compresses the raw data into raw data. The buffer for compressed data itself with the heap passed. Uses method 8 (deflate)
		// returns one of the Z_* errors (Z_OK upon success)
		// MT-safe
		int jPak::RawCompress (const void* pUncompressed, unsigned long* pDestSize, void* pCompressed, unsigned long nSrcSize, int nLevel)
		{
			return ZipDir::ZipRawCompress(g_pBigHeap, pUncompressed, pDestSize, pCompressed, nSrcSize, nLevel);
		}

		// Uncompresses raw (without wrapping) data that is compressed with method 8 (deflated) in the Zip file
		// returns one of the Z_* errors (Z_OK upon success)
		// This function just mimics the standard uncompress (with modification taken from unzReadCurrentFile)
		// with 2 differences: there are no 16-bit checks, and
		// it initializes the inflation to start without waiting for compression method byte, as this is the
		// way it's stored into zip file
		int jPak::RawUncompress (void* pUncompressed, unsigned long* pDestSize, const void* pCompressed, unsigned long nSrcSize)
		{
			return ZipDir::ZipRawUncompress(g_pBigHeap, pUncompressed, pDestSize, pCompressed, nSrcSize);
		}


		// returns the current game directory, with trailing slash (or empty string if it's right in MasterCD)
		// this is used to support Resource Compiler which doesn't have access to this interface:
		// in case all the contents is located in a subdirectory of MasterCD, this string is the subdirectory name with slash
		/*const char* jPak::GetGameDir()
		{
		return m_strPrepend.c_str();
		}
		*/

		//////////////////////////////////////////////////////////////////////////
		void jPak::RecordFileOpen( bool bEnable )
		{
			m_bRememberOpenedFiles = bEnable;
		};

		//////////////////////////////////////////////////////////////////////////
		void jPak::EnumerateRecordedFiles( RecordedFilesEnumCallback enumCallback )
		{
			assert( enumCallback );
			for (RecordedFilesSet::const_iterator it = m_recordedFilesSet.begin(); it != m_recordedFilesSet.end(); ++it)
			{
				enumCallback( (*it).c_str() );
			}
		}

		//////////////////////////////////////////////////////////////////////////
		void jPak::RecordFile( const char *szFilename )
		{
			if (m_bRememberOpenedFiles)
			{
				m_recordedFilesSet.insert( szFilename );
			}
		}


		void jPak::OnMissingFile (const char* szPath)
		{
			AUTO_LOCK(m_csMain);
			if (GetLogMissingFiles())
			{
				std::pair<MissingFileMap::iterator, bool> insertion = m_mapMissingFiles.insert (MissingFileMap::value_type(szPath,1));
				if (GetLogMissingFiles() >= 2 && (insertion.second || GetLogMissingFiles() >= 3))
				{
					// insertion occured
					char szFileName[64];
					sprintf (szFileName, "MissingFiles%d.log", GetLogMissingFiles());
					FILE* f = fopen (szFileName, "at");
					if (f)
					{
						fprintf (f, "%s\n", szPath);
						fclose(f);
					}
				}
				else
					++insertion.first->second;  // increase the count of missing files
			}
		}

		static char* jc_strdup(const char* szSource)
		{
			size_t len = strlen(szSource);
			char* szResult = (char*)malloc(len+1);
			memcpy (szResult, szSource, len+1);
			return szResult;
		}


		jIPak::PakInfo* jPak::GetPakInfo()
		{
			AUTO_LOCK(m_csZips);
			PakInfo* pResult = (PakInfo*)malloc (sizeof(PakInfo) + sizeof(PakInfo::Pak)*m_arrZips.size());
			pResult->numOpenPaks = m_arrZips.size();
			for (unsigned i = 0; i < m_arrZips.size(); ++i)
			{
				pResult->arrPaks[i].szBindRoot = jc_strdup(m_arrZips[i].strBindRoot.c_str());
				pResult->arrPaks[i].szFilePath = jc_strdup(m_arrZips[i].GetFullPath());
				pResult->arrPaks[i].nUsedMem = m_arrZips[i].sizeofThis();
			}
			return pResult;
		}

		void jPak::FreePakInfo (PakInfo* pPakInfo)
		{
			for (unsigned i = 0; i < pPakInfo->numOpenPaks; ++i)
			{
				free((void*)pPakInfo->arrPaks[i].szBindRoot);
				free((void*)pPakInfo->arrPaks[i].szFilePath);
			}
			free(pPakInfo);
		}
		/* *_* by icandoit : 2005-07-09 21:45:28

		CCachedFileData_AutoPtr jPak::GetFileDataI(const char* szName)
		{
		CCachedFileData_AutoPtr pRet = GetFileData(szName);
		//jICachedFileData* pRet1 = pRet;
		return pRet;
		}
		*/ //*_* by icandoit : 2005-07-09 21:45:31

		static nMech::nJC_stream::IStreamEngine *g_pStreamEngine;
		nMech::nJC_stream::IStreamEngine *jPak::GetStreamEngine(nLOG::jILog* pLog)
		{
			if(g_pStreamEngine) return g_pStreamEngine;
			g_pStreamEngine = new CStreamEngine();
			return g_pStreamEngine;
		}

		//--------------------------------------------------------------------------
		void jPak::SetStreamEngine(nMech::nJC_stream::IStreamEngine * pSE)
			//--------------------------------------------------------------------------
		{
			assert(!g_pStreamEngine);
			g_pStreamEngine = pSE;
		}


	}
}

