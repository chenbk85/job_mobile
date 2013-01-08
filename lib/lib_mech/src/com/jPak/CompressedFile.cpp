#include "stdafx.h"
#include "jPak.h"
#include "zlib/zlib.h"
#if defined(LINUX)
#	include <sys/io.h>
#else
#	include <io.h>
#endif
#include <fcntl.h>


namespace nMech
{
	namespace nPAK
	{

#define USE_COMPRESSION

#ifndef BITS2BYTES
		// size in bytes
#define DIV8(n)((n) >> 3)
#define MODULO8(n)((n)&0x00000007)
#define BITS2BYTES(n)(MODULO8((n))?(DIV8((n)) + 1):DIV8((n)))
#define BYTES2BITS(n)((n) << 3)
#define GET_BYTE_INDEX(n) DIV8((n))
#endif //MAX_STRING_SIZE


		bool jPak::WriteZipFile(char *filename, void *data, unsigned int bitlen)
		{
			FILE *pFile = fopen(filename, "wb+");
			if (!pFile)
				return false;

#ifdef USE_COMPRESSION
			gzFile f = gzdopen(fileno(pFile), "wb9");
			gzwrite(f, &bitlen, sizeof(int));
			gzwrite(f, data, BITS2BYTES(bitlen));
			gzclose(f);
#else
			fwrite(&bitlen, sizeof(int), 1, pFile);
			fwrite(data, BITS2BYTES(bitlen), 1, pFile);
			fclose(pFile);
#endif

			return true;
		};

		unsigned int jPak::GetZipFileSize(char *filename)
		{
			FILE *pFile=fopen(filename, "rb");
			if (!pFile) 
				return 0;

			fseek(pFile,0,SEEK_END);
			long nLen=ftell(pFile);
			fseek(pFile,0,SEEK_SET);
			if (nLen<=0)
			{
				// gzread works incorrectly if the filesize is 0
				fclose(pFile);
				return (0);
			}	

			fclose(pFile);
			pFile=fopen(filename, "rb");
			if (!pFile) 
				return 0;

			unsigned int bitlen;
			gzFile f = gzdopen(fileno(pFile), "rb9");
			gzread(f, &bitlen, sizeof(int));
			gzclose(f);
			fclose(pFile);
			return bitlen;
		}

		unsigned int jPak::ReadZipFile(char *filename, void *data, unsigned int maxbitlen)
		{
			FILE * pFile=fopen(filename, "rb");
			if (!pFile) 
				return 0;

			unsigned int bitlen;

#ifdef USE_COMPRESSION
			gzFile f = gzdopen(fileno(pFile), "rb9");
			gzread(f, &bitlen, sizeof(int));
			assert(bitlen<=maxbitlen);  // FIXME: nicer if caller doesn't need to know buffer size in advance
			gzread(f, data, BITS2BYTES(bitlen));
			gzclose(f);
			fclose(pFile);
#else	
			fread(pFile, &bitlen, sizeof(int));
			assert(bitlen<=maxbitlen);  // FIXME: nicer if caller doesn't need to know buffer size in advance
			fread(pFile, data, BITS2BYTES(bitlen));
			fclose(pFile);
#endif

			return bitlen;
		};



		int jPak::Compress( void *dest,unsigned int &destLen,const void *source, unsigned int sourceLen,int level )
		{
			unsigned long dlen = destLen;
			int res = ::compress2( (Bytef*)dest,&dlen,(const Bytef*)source,sourceLen,level );
			destLen = dlen;
			return res;
		}

		//////////////////////////////////////////////////////////////////////////
		int jPak::Uncompress( void *dest,unsigned int &destLen,const void *source, unsigned int sourceLen )
		{
			unsigned long dlen = destLen;
			int res = ::uncompress( (Bytef*)dest,&dlen,(const Bytef*)source,sourceLen );
			destLen = dlen;
			return res;
		}

	}
}
