/* file : jMemoryDLL.cpp
Coder : by icandoit ( mech12@nate.com)
Date : 2007-04-11 12:56:19
comp.: pantavision.co.kr
title : 
desc : 

*/

#include "stdafx.h"
#include "MemoryModule.h"
#include "jMemoryDLL.h"
#include "header/jMemoryChunk.h"

namespace nMech
{
#if 0
	//---------------------------------------------------------------
	// memory module code
	//-----------------------------------------------------------------#if 0
	void LoadFromFile(void)
	{
		addNumberProc addNumber;
		HINSTANCE handle = LoadLibrary(DLL_FILE);
		if (handle == INVALID_HANDLE_VALUE)
			return;

		addNumber = (addNumberProc)GetProcAddress(handle, "addNumbers");
		printf("From file: %d\n", addNumber(1, 2));
		FreeLibrary(handle);
	}
	void LoadFromMemory(void)
	{
		FILE *fp;
		unsigned char *data=NULL;
		size_t size;
		HMEMORYMODULE module;
		addNumberProc addNumber;

		fp = fopen("SampleDLL.dll", "rb");
		if (fp == NULL)
		{
			printf("Can't open DLL file \"%s\".", DLL_FILE);
			goto exit;
		}

		fseek(fp, 0, SEEK_END);
		size = ftell(fp);
		data = (unsigned char *)malloc(size);
		fseek(fp, 0, SEEK_SET);
		fread(data, 1, size, fp);
		fclose(fp);

		module = MemoryLoadLibrary(data);
		if (module == NULL)
		{
			printf("Can't load library from memory.\n");
			goto exit;
		}

		addNumber = (addNumberProc)MemoryGetProcAddress(module, "addNumbers");
		int aaa = addNumber(1, 2);
		printf("From memory: %d\n", aaa);
		MemoryFreeLibrary(module);

exit:
		if (data)
			free(data);
	}
#endif

	tcstr jMemoryDLL::GetDBName()
	{
		return _T("gkrrywhd");//dll db file name
	}
	void jMemoryDLL::ReadDB(tcstr szPath)
	{
		nFileSystem::jFolder dm;
		tfname_t szBuf;
		jt_sprintf(szBuf , _T("%s\\%s"),szPath, GetDBName());
		try
		{
			nFileSystem::UFile fp(szBuf, _T("rb"));

			fseek(fp, 0, SEEK_END);
			m_iSizeMemBuffer = ftell(fp);
			jAssert0(m_iSizeMemBuffer>1);
			m_pMemBuffer = new char[m_iSizeMemBuffer];
			jAssert0(m_pMemBuffer);
			fseek(fp, 0, SEEK_SET);
			fread(m_pMemBuffer, 1, m_iSizeMemBuffer, fp);
			fp.fclose();

			nUtil::jMemoryChunk mc;
			mc.SetBuffer((CHAR*)m_pMemBuffer ,m_iSizeMemBuffer );
			int iTot;
			mc.readChunk(iTot);
			_DllEntry de;
			int assertSize=0;
			for(int i=0; i<iTot ; ++i)
			{
				if(mc.isEnd()) 
					break;
				mc.readChunk(&de.szDLL);
				mc.readChunk(de.iSize);
				assertSize+=de.iSize;
				de.pMemDLL = mc.skipChunk(de.iSize);
				de.hDLL = MemoryLoadLibrary(de.pMemDLL);
				if(!de.hDLL)
				{
					jMB(("Dll MemoryLoadLibrary fail"), de.szDLL);
					throw false;
				}
				m_DllEntryList[de.szDLL] = de;
			}
			jAssert0(assertSize == m_iSizeMemBuffer);
		}
		catch (tcstr szBuf)
		{
			jMB(_T("Can't open DLL DB file "), szBuf);
		}

	}

	void jMemoryDLL::_DllEntryClear(m_DllEntryList_vt vt)
	{
		MemoryFreeLibrary(vt.second.hDLL);
	}

	void jMemoryDLL::Close()
	{
		SAFE_DELETE_ARRAY(m_pMemBuffer);
		for_each(m_DllEntryList.begin(),m_DllEntryList.end(),_DllEntryClear);
		m_DllEntryList.clear();
	}

	HMEMORYMODULE jMemoryDLL::_LoadLibrary(acstr szDLL)
	{
		m_DllEntryList_it it = m_DllEntryList.find(szDLL);
		if(it==m_DllEntryList.end())
			return 0;
		return it->second.hDLL;
	}

	FARPROC jMemoryDLL::GetProcAddress(HMEMORYMODULE hDLL,acstr szFunc)
	{
		return MemoryGetProcAddress(hDLL, szFunc);	
	}
	using namespace std;
	void jMemoryDLL::WriteDB(tcstr szPath)
	{
		nFileSystem::jFolder dm;
		dm.Goto(szPath);
		std::tstring sBuf;
		nFileSystem::read_file(_T("mem_dll.txt"),sBuf);
		vector<std::tstring> out;
		nString::jSplit(sBuf, _T("\n\r\t "),out);
		_DllEntry de;
		nFileSystem::UFile fp,fpDB(GetDBName(), _T("wb"));
		int iTot = (int)out.size();
		fwrite(&iTot, sizeof(iTot),1, fpDB);
		afname_t buf;
		try
		{
			for(int i=0; i< iTot ; ++i)
			{
				if(!ja_strlen(jA(out[i].c_str()))) continue;
				ja_sprintf(buf, ("%s.dll"), jA(out[i].c_str()) );
				de.szDLL= buf;
				fwrite(de.szDLL, ja_strlen(de.szDLL)+1, 1, fpDB);

				fp.fopen(jT(de.szDLL),_T("rb"));
				de.iSize = nFileSystem::UFile::Length(fp);
				fwrite(&de.iSize, sizeof(de.iSize), 1,fpDB);

				void* pBuf = malloc(de.iSize);
				fread(pBuf, de.iSize, 1, fp);
				fwrite(pBuf, de.iSize, 1,fpDB);
				free(pBuf);
				fp.fclose();
			}
		}
		catch (tcstr szbuf)
		{
			jMB(_T("mem file write fail"), szbuf);
		}

	}}
