/* 
	filename:	jFolder.cpp
	coder	:	Cho Wook Rea (mech12@dreamwiz.com) 
	comp.	:	f2system 
	compiler:	vc++ 6.0
	date	:	2000 / 01 / 
	title	:	
*/
#include "stdafx.h"
#include <windowsx.h>
#include <io.h>
#include <shellapi.h>

#include "jFolder.h"
#include "base/juExeEnv.h"
#include "header/jBoost.h"

namespace nMech
{
	namespace nFileSystem
	{
		jFolder::jFolder(bool isGotoStartDir)
		{
			if(isGotoStartDir) 
			{
				GotoStartDir();
			}
		}
		jFolder::~jFolder()
		{
			clear();
		}

		tcstr jFolder::GetTempDir(path_t& buf)//임시폴더를 리턴
		{
			afname_t buf1;
			GetTempPathA(sizeof(buf1)-1, buf1);
			jt_strcpy(buf,jT(buf1));
			return buf;
		}
		tcstr jFolder::GetCurDir(path_t& currDir)
		{
			if(!GetCurrentDirectory(_countof(currDir), currDir))
				throw false;
			jt_strlwr(currDir);
			jt_strcat(currDir,_T("\\"));
			return currDir;
		}

		bool jFolder::GotoStartDir()
		{	
			return Goto(g_ExeEnv.m_szStartDir);	
		}

		void jFolder::GotoByFileName(tcstr s) 
		{
			nFileSystem::jFileName fn(s);
			path_t buf;
			fn.GetPath(buf);
			if(!jt_strchr(s, _T(':')))
				GotoStartDir();
			Goto(buf);
		}
		static void jFolder_ch_drive(tcstr sz)
		{
			int curdrive = _getdrive();

			fname_t szDrv;
			jt_strcpy(szDrv,sz);
			jt_strlwr(szDrv);
			TCHAR* ch = jt_strchr(szDrv, ':');
			if(ch)
			{
				int iDrive = szDrv[0];
				iDrive = 'a'- iDrive + 1;
				if(curdrive!=iDrive)
					if(iDrive>=1 && iDrive<=26)
						_chdrive(iDrive);
			}
		}
		bool jFolder::GoBack()
		{
			if(!m_Stack.size())			return false;
			tstring sPrev = m_Stack.back();
			m_Stack.pop_back();
			jFolder_ch_drive(sPrev.c_str());
			jt_chdir(sPrev.c_str());
			return true;
		}

		// 이동하기전 현제 폴더를 스택에 저장.
		// 이동한 폴더와 이전폴더가 같다면 스텍에 저장하지 않는다. false를 리턴
		// 해당 폴더가 없으면 에러스트링 예외날림

		bool jFolder::Goto(tcstr s) 
		{ 
			if(!*s)		{	return false;	} 		
			path_t curr_dir;

			GetCurDir(curr_dir);
			//boost::filesystem::path sNewPath(std::tstring(s));
			//if(jt_chdir( sNewPath.native_directory_string().c_str() )!=-1) 

			jFolder_ch_drive(s);

			if(jt_chdir( s )!=-1) 
			{
				path_t new_path;
				GetCurDir(new_path);
				jt_strlwr(curr_dir);
				jt_strlwr(new_path);
				if(jt_strcmp(curr_dir, new_path)) // 이동한 폴더와 이전폴더가 다를때만 스택에 추가.
				{
					m_Stack.push_back(curr_dir);
					return true;
				}
				return false;
			}
			jERROR_T("jFolder::Goto(%s,CurDir=%s)" , s,curr_dir);
			return false;
		}

		bool jFolder::GotoIf(tcstr s)// 존재하면 이동하고 존재하지 않으면 false 리턴.
		{
			// 패스가 없으면 그냥 리턴.
			if(!s || !*s)		{ 			return false;		} 		
			if ( ::jt_access( s, 0) == -1) return false;
			return Goto(s);
		}

		void jFolder::GotoForce(tcstr s)// 존재하지 않으면 만들어서 이동. 새로생성되었으면 true;
		{
			CreateDirForce(s);
			Goto(s);
		}

		bool jFolder::CreateDir(tcstr sz)
		{
			if(jt_strcmp(sz,_T(".."))==0)
			{
				jt_chdir(sz);
				return true ;
			}
			if(jt_strcmp(sz,_T("."))==0)
			{
				return true;
			}
#if 0
			return CreateDirectory(sz,0);
#else
			return filesystem::create_directory(sz);
#endif
		}

		// d:\sample\sample\ // 끝에 \가 있어야 맨마지막 폴더가 생성됨.
		// d:/sample/sample/
		struct _divide_and_make_dir
		{
			int idx;
			TCHAR* szBuf;
			_divide_and_make_dir(TCHAR* buf):szBuf(buf),idx(0){}
			void operator()(TCHAR it)
			{
				if(it=='\\' || it=='/')
				{
					bool is = jFolder::Is_Exist(szBuf) ;
					if(!is || !filesystem::is_directory(szBuf))
						if(!jFolder::CreateDir(szBuf)) 
							throw szBuf;
				}
				szBuf[idx++]=it;
				return;
			}
		};
		bool jFolder::CreateDirForce( tcstr sSrcFullPath_ )
		{
#if 1
			TCHAR buf[1024];
			memset(buf, 0, 1024);
			try
			{
				if(jt_strchr(sSrcFullPath_,'\\') || jt_strchr(sSrcFullPath_,'/'))
					std::for_each(sSrcFullPath_ , sSrcFullPath_ +jt_strlen(sSrcFullPath_) , _divide_and_make_dir(buf));
				else
				{
					if(!jFolder::Is_Exist(sSrcFullPath_))
						if(!jFolder::CreateDir(sSrcFullPath_)) 
							throw sSrcFullPath_;
				}
			}
			catch( tcstr szErr)
			{
				jERROR_T("%s fail : error = %s",sSrcFullPath_, szErr);
			}
			catch (...)
			{
				jERROR_T("%s fail",sSrcFullPath_);
				return false;
			}
#else
			filesystem::create_directory(sSrcFullPath_);
#endif
			return true;
		}
		void jFolder::RemoveAll(tcstr sz)
		{
			//RemoveDirectory(sz);
#if 1
			filesystem::remove_all(sz);
#else
			SHFILEOPSTRUCT sh;
			fname_t temp;
			memset(temp,0,sizeof(temp));
			jt_strcpy_s(temp,sz);
			sh.hwnd = 0;
			sh.wFunc = FO_DELETE;
			sh.pFrom = temp;
			sh.fFlags = !FOF_ALLOWUNDO |FOF_NOCONFIRMATION ;
			SHFileOperation(&sh);
#endif
		}
		bool jFolder::Is_Exist(tcstr sz)
		{
			return  filesystem::exists(sz);
		}
		bool jFolder::Is_Dir(tcstr sz	)
		{
			return filesystem::is_directory(sz);
		}

		//}chowookrea@hotmail(icq74456993) 2003-04-08오후 10:13:18*/


		// returns the parent directory of the given file or directory.
		// the returned path is WITHOUT the trailing slash
		// if the input path has a trailing slash, it's ignored
		// nGeneration - is the number of parents to scan up

		// searches and returns the pointer to the extension of the given file
		wcstr  jFolder::FindExtension (wcstr  szFileName)
		{
			wcstr  szEnd = szFileName + (int)jw_strlen(szFileName);
			for (wcstr  p = szEnd-1; p >= szFileName; --p)
				if (*p == '.')
					return p+1;

			return szEnd;
		}

		// searches and returns the pointer to the file name in the given file path
		wcstr  jFolder::FindFileNameInPath (wcstr  szFilePath)
		{
			for (wcstr  p = szFilePath + (int)jw_strlen(szFilePath)-1; p >= szFilePath; --p)
				if (*p == '\\' || *p == '/')
					return p+1;
			return szFilePath;
		}
		// searches and returns the pointer to the extension of the given file
		acstr  jFolder::FindExtension (acstr  szFileName)
		{
			acstr  szEnd = szFileName + (int)ja_strlen(szFileName);
			for (acstr  p = szEnd-1; p >= szFileName; --p)
				if (*p == '.')
					return p+1;

			return szEnd;
		}

		// searches and returns the pointer to the file name in the given file path
		acstr  jFolder::FindFileNameInPath (acstr  szFilePath)
		{
			for (acstr  p = szFilePath + (int)ja_strlen(szFilePath)-1; p >= szFilePath; --p)
				if (*p == '\\' || *p == '/')
					return p+1;
			return szFilePath;
		}




	}//namespace nFileSystem

}
