// Interface to the jcGame pack files management

#ifndef _IJC_PAK_HDR_
#define _IJC_PAK_HDR_

#include "Interface/jIPak.h"
/* *_* by icandoit : 2006-05-15 16:57:31
사용 안함 nMech::nPAK::jIPak대신 nMech::nPAK::jIPak사용
struct nMech::nPAK::jIPak : public nMech::nPAK::jIPak
{
	nMech::nPAK::jIPak에 추가된내용임.


	virtual int unsigned FGetSize(FILE* f)=0;

	// system 에서 가져옴.
	virtual bool WriteZipFile(char *filename, void *data, unsigned int bitlen)=0;
	virtual unsigned int ReadZipFile(char *filename, void *data, unsigned int maxbitlen)=0;
	virtual unsigned int GetZipFileSize(char *filename)=0;

	virtual void OnMissingFile (const char* szPath)=0;

	virtual int GetPriority()=0;
	virtual int GetReadSlice()=0;
	virtual int GetLogMissingFiles()=0;

	virtual int Compress( void *dest,unsigned int &destLen,const void *source, unsigned int sourceLen,int level )=0;
	virtual int Uncompress( void *dest,unsigned int &destLen,const void *source, unsigned int sourceLen )=0;
	virtual nMech::nJC_stream::IStreamEngine *GetStreamEngine(jILog* pLog)=0;


};
*/ //*_* by icandoit : 2006-05-15 16:58:44

#endif

