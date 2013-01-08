/* file : jFile.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-29 17:35:38
title : 
desc : 

*/

#ifndef __jFile_header__
#define __jFile_header__
#pragma once

namespace nMech
{
	namespace nFileSystem
	{

		//****************************************************************
		class UFile
			//****************************************************************
		{
		public:
			FILE* fp;
			UFile():fp(0){}
			UFile(tcstr fname,tcstr opt):fp(0)	{ this->fopen(fname,opt);	}
			~UFile(){ this->fclose();}
			void fclose(){ if(fp) ::fclose(fp); fp=0;}
			operator FILE*(){ return fp;}
			FILE* operator->(){return fp;}
			void UFile::fopen(tcstr fname,tcstr opt)
			{
				if(fp) ::fclose(fp);
				fp = ::jt_fopen(fname,opt); 
				if(fp==NULL) 
				{
					TCHAR buf[1024];
					_stprintf(buf,_T("UFile open error : %s"),fname);
					throw buf;
				}
			}
			static long UFile::Length(FILE* fp1)
			{
				fseek(fp1, 0, SEEK_END);
				long iSize = ftell(fp1);
				fseek(fp1,0,SEEK_SET);
				return iSize;
			}
			tcstr  UFile::ReadTextAll(std::tstring& sBuf)
			{
				size_t iSize = UFile::Length(fp);
				sBuf.resize(iSize);
				assert(sBuf.capacity()>iSize);
				fread(const_cast<TCHAR*>(sBuf.c_str()) ,  iSize , 1,fp);
				return sBuf.c_str();
			}



		};


		inline void load_file_from_ifstream(std::tstring& s, std::tifstream& is)
		{
			s.erase();
			if(is.bad()) return;
			//
			// attempt to grow string buffer to match file size,
			// this doesn't always work...
			s.reserve(is.rdbuf()->in_avail());
			TCHAR c;
			while(is.get(c))
			{
				// use logarithmic growth stategy, in case
				// in_avail (above) returned zero:
				if(s.capacity() == s.size())
					s.reserve(s.capacity() * 3);
				s.append(1, c);
			}
		}

		inline tcstr  read_file(tcstr  filename , std::tstring& sBuf)
		{
#ifdef jUSE_FILE_PTR_FGETS
			FILE* fp1 = jt_fopen(filename, _T("r"));
			if(!fp1) return 0;
			TCHAR szBuf[512];
			while(NULL != jt_fgets(szBuf, 512, fp1))
			{
				sBuf += szBuf;
			}
			fclose(fp1);
#else //제일 빠름.
#if 0
			FILE* fp1 = ::jt_fopen(filename, _T("r"));
			if(!fp1) return 0;
			long iSize =UFile::Length(fp1);
			sBuf.resize(iSize);
			size_t  iT = sBuf.capacity();
			fread(const_cast<TCHAR*>(sBuf.c_str()) ,  iSize , 1,fp1);
			sBuf[iSize]=0;
			::fclose(fp1);
			assert(sBuf.size()==iSize);
#else
			std::tifstream iF(filename);
			load_file_from_ifstream(sBuf, iF);
			iF.close();
#endif
			return sBuf.c_str();

#endif
			/* *_* by icandoit : 2006-10-26 10:14:18
			RDTSC()속도 비교.

			2Mbyte 파일 로딩시...
			1129039166 = ifstream 사용
			908170532 = FILE*사용
			105906481 = FILE* fread()사용

			2kbyte미만 파일로딩시...
			2844814 = ifstream 사용
			905998 = FILE*사용

			평균 2.5배 정도 FILE*이 빠름.

			FILE* 를 사용하더라도 fgets보다 fread를 사용하여 한꺼번에 읽는것이 
			10배정도 빠름


			다음 RELEASE모드로 빌드했을때이다.

			2Mbyte 파일 로딩시...
			847710423 = ifstream 사용
			275887084 = FILE*사용
			71142076 = FILE* fread()사용

			2Kbyte 미만 파일 로딩시...
			2562240 = ifstream 사용
			314400669 = FILE*사용
			75720295 = FILE* fread()사용

			*/ //*_* by icandoit : 2006-10-26 10:14:19
		}

		inline tcstr  read_file(const std::tstring &filename , std::tstring& sBuf)	{		return read_file (filename.c_str() , sBuf);	}

		inline acstr  read_fileA(acstr  filename , std::astring& sBuf)
		{
			FILE* fp1 = ::ja_fopen(filename, "r");
			if(!fp1) return 0;
			long iSize =UFile::Length(fp1);
			sBuf.resize(iSize);
			size_t  iT = sBuf.capacity();
			fread(const_cast<CHAR*>(sBuf.c_str()) ,  iSize , 1,fp1);
			sBuf[iSize]=0;
			::fclose(fp1);
			assert(sBuf.size()==iSize);
			return sBuf.c_str();
		}

	}//nFileSystem

}

#endif // __jFile_header__
