/* 
	filename:	jZipUtil.h
	coder	:	Cho Wook Rea (chowookrea@hotmail) 
	comp.	:	-DIGICELL-
	compiler:	vc++ 6.0
	date	:	2004-07-13오후 9:43:31
	title	:	메모리 zip 유틸 
	: 메모리상의 버퍼내용을 압축해준다. 
	 jZipBuffer와 jUnZipBuffer 클래스는 zip.cpp 모듈을 이용해 쉽게 메모리상의 버퍼를 압축/해제 해주기 위한 랩퍼 클래스이다.

	사용예.

	TCHAR *tempBuff= "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000\
							 0000000000000000000000000000000000000000000000000000000as0000000000000000000000000000000000000000000000000000000\
							 0000000000000000000000000000000000000000000000000000000as0000000000000000000000000000000000000000000000000000000";

	jZipBuffer zBuf(tempBuff, _tcslen(sss)+1);
	jUnZipBuffer uBuf(zBuf.GetZipBuff() , zBuf.GetZipSize() , zBuf.GetUnZipBuffSize() );

	TCHAR* szUnzip  = (TCHAR*)uBuf.GetUnZipBuff();
	
	assert(!_tcscmp(tempBuff,szUnzip ));
	assert(zBuf.GetUnZipBuffSize() == uBuf.GetUnZipSize() );

*/


// jZipUtil.h: interface for the jZipUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_JZIPUTIL_H__1022B1C4_C048_4FB0_8BC3_37E1A50DC09C__INCLUDED_)
#define AFX_JZIPUTIL_H__1022B1C4_C048_4FB0_8BC3_37E1A50DC09C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "interface/jIZipUtil.h"

namespace nMech
{
	namespace nUtil
	{

		//---------------------------------------------------------------
		class jZipBuffer : public jIZipBuffer
			//----------------------------------------------------------------
		{
			CHAR* pZipBuf;
			int iZipSize;
			acstr szPasswd;

			int Zip();
		public:
			jINTERFACE_HEADER(jIInterface);

			CHAR* pSrcBuf ;
			int iSrcBufSize;

			jZipBuffer():pSrcBuf(0),pZipBuf(0),iSrcBufSize(0),iZipSize(0),szPasswd(0){}
			void Init(CHAR* srcBuf, size_t srcSize)
			{
				pSrcBuf=srcBuf;
				pZipBuf=0;
				iSrcBufSize=srcSize;
				iZipSize=0;
				szPasswd=0;
				Zip();
			}
			void clear(){ SAFE_DELETE(pZipBuf); iZipSize=0;	}
			~jZipBuffer(){ clear(); }
			jZipBuffer(jZipBuffer&){ assert(0);}
			jZipBuffer & operator =(jZipBuffer&){ assert(0); return *this;}
			CHAR* GetZipBuff(){	return (iZipSize > 0) ? pZipBuf : pSrcBuf ; }
			int GetZipSize(){ return iZipSize;	}
		};

		//---------------------------------------------------------------
		class jUnZipBuffer : public jIUnZipBuffer
			//----------------------------------------------------------------
		{
			int iUnZipSize;
			CHAR* pUnZipBuf;
			acstr szPasswd;

			int UnZip();
		public:
			jINTERFACE_HEADER(jIInterface);

			CHAR* pZipSrcBuf ;
			int iSrcBufSize;

			jUnZipBuffer():pZipSrcBuf(0),pUnZipBuf(0),iSrcBufSize(0),iUnZipSize(0),szPasswd(0){}
			void Init(CHAR* srcBuf, size_t srcSize)	{iUnZipSize=0;		pZipSrcBuf = srcBuf;		iSrcBufSize = srcSize;	UnZip();}
			void clear(){SAFE_DELETE(pUnZipBuf); iUnZipSize=0;	}
			~jUnZipBuffer(){ clear(); }
			jUnZipBuffer(jUnZipBuffer&){ assert(0);}
			jUnZipBuffer& operator =(jUnZipBuffer&){ assert(0); return *this;}

			CHAR* GetUnZipBuff(){ return (iSrcBufSize  > 0) ? pUnZipBuf : pZipSrcBuf;	}
			int GetUnZipSize(){ return iSrcBufSize  > 0 ? iUnZipSize : - iSrcBufSize;}

		};

	}
}



#endif // !defined(AFX_JZIPUTIL_H__1022B1C4_C048_4FB0_8BC3_37E1A50DC09C__INCLUDED_)
