/* file : jFileName.h
Coder : by icandoit ( whdnrfo@gmail.com)
Date : 2010-09-07 12:52:34
comp.: t3.co.kr
title : 
desc : 

*/

#ifndef __jFileName_header__
#define __jFileName_header__
#pragma once

namespace nMech
{
	namespace nFileSystem
	{
		struct jFileName
		{
		public:
			TCHAR buffer[_MAX_PATH];
			TCHAR drive[_MAX_DRIVE];
			TCHAR dir[_MAX_DIR];
			TCHAR fname[_MAX_FNAME];
			TCHAR ext[_MAX_EXT];

			jFileName(){memset(this, 0, sizeof(*this)); }
			jFileName(tcstr s){memset(this, 0, sizeof(*this) );Init(s);}
			void Init(tcstr s)
			{
				_tcscpy(buffer, s);
				_tcslwr(buffer);
				_tsplitpath( buffer, drive, dir, fname, ext );
			}
			void ClearPath()
			{ 
				drive[0]=0; dir[0]=0;	
				_stprintf(buffer,TEXT("%s%s"),fname,ext);
			}

			void Init(tcstr szPath, tcstr szFile)
			{
				_stprintf(buffer , TEXT("%s\\%s") , szPath, szFile);
				_tcslwr(buffer);
				_tsplitpath( buffer, drive, dir, fname, ext );
			}

			void Init(tcstr szPath, tcstr szPath2 , tcstr szFile)
			{
				_stprintf(buffer , TEXT("%s\\%s\\%s") , szPath, szPath2, szFile);
				_tcslwr(buffer);
				_tsplitpath( buffer, drive, dir, fname, ext );
			}
			//buffer = "z:\source_es\test\test_file.xml"
			//drive = "z:"
			//dir = "\source_es\test\"
			//fname= "test_file"
			//ext=".xml"
			//주의 : GetPath()의 경우 맨마지막에 "\\"가 붙는다.
			tcstr GetPath(TCHAR* buf ){	_stprintf(buf , TEXT("%s%s"),drive,dir); return buf;}
			tcstr GetName(TCHAR* buf) {	_stprintf(buf,TEXT("%s%s"),fname,ext); return buf;}

		};

	}//nFileSystem
}


#endif // __jFileName_header__
