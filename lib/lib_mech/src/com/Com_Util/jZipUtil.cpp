// jZipUtil.cpp: implementation of the jZipUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "jZipUtil.h"
#include <tchar.h>
#include "zip.h"
#include "unzip.h"


namespace nMech
{
	namespace nUtil
	{
		//////////////////////////////////////////////////////////////////////
		// Construction/Destruction
		//////////////////////////////////////////////////////////////////////



		jCTOR_INTERFACE(nMech::nUtil::jIZipBuffer,jZipBuffer)
		{
			return new jZipBuffer;
		}
		jDTOR_INTERFACE(nMech::nUtil::jIZipBuffer,jZipBuffer)
		{
			delete this;
		}
		jCTOR_INTERFACE(nMech::nUtil::jIUnZipBuffer,jUnZipBuffer)
		{
			return new jUnZipBuffer;
		}
		jDTOR_INTERFACE(nMech::nUtil::jIUnZipBuffer,jUnZipBuffer)
		{
			delete this;
		}

		//---------------------------------------------------------------
		// return ���� ���� ������������ ���ۻ������̴�. ���� -�̸� �������ϸ� ����� ��Ŀ���� �����. 
		acstr szDEFAULT_jZipBuffer_PASSWD = "p1ad2ssd32w23dskehahffkdygkgkgk";
		jZipBuffer *g_Zip;
		int jZipBuffer::Zip()
			//----------------------------------------------------------------
		{
			g_Zip = this;
			if(!szPasswd) szPasswd = szDEFAULT_jZipBuffer_PASSWD;
			if(pZipBuf) 
			{
				assert(0);
			}
			pZipBuf = new CHAR[iSrcBufSize];
			memset(pZipBuf,0, iSrcBufSize);
			HZIP hZsrc = CreateZip(pZipBuf, iSrcBufSize,  szPasswd);
			ZRESULT hRet = ZipAdd(hZsrc, _T("test"),(void*)pSrcBuf,iSrcBufSize);

			if(hRet!=ZR_OK)
			{
				CloseZip(hZsrc);
				iZipSize=-iSrcBufSize;
				SAFE_DELETE ( pZipBuf );
				return iZipSize;
			}
			CHAR* pBuf;
			unsigned long len;
			ZipGetMemory(hZsrc, (void**)(&pBuf), &len);
			iZipSize	= len;
			assert(pBuf==pZipBuf);
			CloseZip(hZsrc);
			if(iZipSize>=iSrcBufSize)
			{
				SAFE_DELETE(pZipBuf);
				iZipSize=-iSrcBufSize;
			}
			return iZipSize;
		}

		//---------------------------------------------------------------
		// pZipSrcBuf�� ������ pUnZipBuf�� ������ Ǭ��. ���ϰ��� ������������ pUnZipBuf�� ������
		int jUnZipBuffer::UnZip()
			//----------------------------------------------------------------
		{
			if(!szPasswd) szPasswd = szDEFAULT_jZipBuffer_PASSWD;
			assert(!pUnZipBuf);
			if(iSrcBufSize <=0)
			{
				iUnZipSize = iSrcBufSize;
				return iUnZipSize;
			}
			HZIP hZ = OpenZip(pZipSrcBuf, iSrcBufSize,szPasswd);
			assert(hZ);
			ZIPENTRY ze; 
			ZRESULT hr = GetZipItem(hZ,0,&ze);
			assert(hr == ZR_OK);
			//assert(ze.unc_size == iUnZipSize);
			pUnZipBuf = new CHAR[ze.unc_size];
			iUnZipSize = ze.unc_size;
			UnzipItem(hZ,0, pUnZipBuf , ze.unc_size);
			CloseZip(hZ);
			return iUnZipSize;
		}


	}
}


