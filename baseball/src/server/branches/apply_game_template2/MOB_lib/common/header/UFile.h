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
			void fopen(tcstr fname,tcstr opt)
			{
				if(fp) ::fclose(fp);
				fp = ::ja_fopen(fname,opt); 
				if(fp==NULL) 
				{
					char buf[1024];
					ja_sprintf(buf,_T("UFile open error : %s"),fname);
					throw buf;
				}
			}
			static long Length(FILE* fp1)
			{
				fseek(fp1, 0, SEEK_END);
				long iSize = ftell(fp1);
				fseek(fp1,0,SEEK_SET);
				return iSize;
			}
			tcstr  ReadTextAll(std::tstring& sBuf)
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
			std::tifstream iF(filename);
			load_file_from_ifstream(sBuf, iF);
			iF.close();
			return sBuf.c_str();
		}
		inline tcstr  read_file(const std::tstring &filename , std::tstring& sBuf)	{		return read_file (filename.c_str() , sBuf);	}
		inline acstr  read_fileA(acstr  filename , std::astring& sBuf)
		{
			FILE* fp1 = ::ja_fopen(filename, "r");
			if(!fp1) return 0;
			size_t iSize =UFile::Length(fp1);
			sBuf.resize(iSize);
			//size_t  iT = sBuf.capacity();
			fread(const_cast<CHAR*>(sBuf.c_str()) ,  iSize , 1,fp1);
			sBuf[iSize]=0;
			::fclose(fp1);
			assert(sBuf.size()==iSize);
			return sBuf.c_str();
		}

	}//nFileSystem

}

#endif // __jFile_header__
