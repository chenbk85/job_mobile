#include "stdafx.h"
#include "jExeEnv.h"
#include "base/jFolder.h"
#include "base/jTestUnit.h"

using namespace nMech;
using namespace nMech::nFileSystem;


jTEST_SUITE_BEGIN(nFileSystem_)
jTEST(jFolder_)
{
#if 1

	path_t save_start_path;
	jt_strcpy(save_start_path , g_ExeEnv.m_szStartDir); // 일단 g_ExeEnv의 정보 백업


	path_t curr_dir;
	GetCurrentDirectory(sizeof(curr_dir), curr_dir);
	jt_strlwr(curr_dir);
	jCHECK(curr_dir[jt_strlen(curr_dir)-2] != '\\');// 패스명 뒤가 \로 끝나지 않는다.
	jt_strcat(curr_dir,_T("\\")); //마지막에 \로 끝나게

	path_t temp_dir;
	path_t exe_name;
	GetModuleFileName(0, exe_name, sizeof(exe_name));
	jt_strlwr(exe_name);
	UFileName fn(exe_name);
	path_t module_path;
	fn.GetPath(module_path);
	{
		int iCount=0;
		jFolder dir(false);//시작위치로 이동안함.
		path_t buf_currpath;
		dir.GetCurDir(buf_currpath);
		jEQUAL(dir.size(), 0);
		jCHECK(dir.Goto(buf_currpath) ==false);
		jCHECK(dir.Goto(_T("..") ) ==true);
		
		//모듈폴더의 상위폴더를 시작폴더로 세팅
		jt_strcpy(g_ExeEnv.m_szStartDir,  dir.GetCurDir(temp_dir)); 

		jEQUAL(dir.size(), 1); // 

		dir.clear(); // 원상태로 복귀. 
		jEQUAL( dir.size()  ,0); 

		//GetModuleFileName()의 폴더로 이동했는지 확인.
		jCHECK(std::tstring(dir.GetCurDir(temp_dir)) ==tstring(curr_dir) );
	}

	path_t curr_dir2;
	GetCurrentDirectory(sizeof(curr_dir2), curr_dir2);
	jt_strcat(curr_dir2,_T("\\")); //마지막에 \로 끝나게

	jCHECK(std::tstring(curr_dir) ==tstring(curr_dir2) ); // 원래 폴더로 되돌아 와야함.

	{
		jFolder dir(true);//시작위치로 이동.
		jCHECK(std::tstring(dir.GetCurDir(temp_dir))==tstring(g_ExeEnv.m_szStartDir) );

		dir.GotoByFileName(exe_name);
		tstring currDir1 = dir.GetCurDir(temp_dir);
		jCHECK( currDir1 == g_ExeEnv.m_szModuleDir );

		//--------------------------------------------------------------------------
		// jFolder::Goto()의 예외상황처리
		//--------------------------------------------------------------------------
		try
		{
			dir.Goto(_T("..\\testasdfkjwoiejf923482979dflksdejoqweij"));
			jCHECK(0);
		}
		catch(...)
		{
			jCHECK(1);
		}

		//--------------------------------------------------------------------------
		//GotoForce()  사용 예
		//--------------------------------------------------------------------------
		try
		{
			path_t buf1,buf2;
			dir.GetCurDir(buf1);
			dir.Goto(_T("..")); 
			dir.GetCurDir((buf2));
			
			//주의 dir.GotoForce("..\\test\\test1\\test2") 이런식으로 용요하면 안됨.
			//--------------------------------------------------------------------------
			//주의 dir.GotoForce(_T("test\\test1\\test2"));는 test\test1까지만 폴더를 만듬.
			//--------------------------------------------------------------------------
			dir.GotoForce(_T("test\\test1\\test2\\")); // 
			dir.GetCurDir(temp_dir);
			tstring s2 = tstring(g_ExeEnv.m_szStartDir) + _T("test\\test1\\test2\\");
			//jCHECK(s2==temp_dir);
		}
		catch(...)
		{
			jCHECK(0);
		}


		tstring currDir = dir.GetCurDir(temp_dir);
		//jCHECK(*dir.begin() == tstring(g_ExeEnv.m_szStartDir));
		tstring sTestDir = tstring(g_ExeEnv.m_szStartDir) + _T("test\\test1\\test2\\");
//		jCHECK(sTestDir== currDir);
		dir.GoBack();
		dir.GoBack();
		using namespace boost::lambda;
		//jFOR_EACH(dir , tcout << _1 << _T("\n") );
		jEQUAL(dir.size() , 2);
		dir.GoBack();
		dir.GetCurDir(temp_dir);
		jCHECK(std::tstring(temp_dir) == g_ExeEnv.m_szStartDir );

		size_t iCurr = dir.size();
		dir.Goto(_T("."));
		jEQUAL(iCurr ,dir.size() );
		tcstr dir_save_curr = dir.GetCurDir(temp_dir);
		dir.Goto(_T(".."));
		dir.Goto(_T("."));
		if( dir.GotoIf(_T("C:\\WINDOWS")))
		{
			jEQUAL(dir.size() , iCurr+2);// 이동성공시
		}
		else
			jEQUAL(dir.size() , iCurr+1); // 이동 실패시
		
		dir.GotoStartDir();
		jCHECK(std::tstring(dir.GetCurDir(temp_dir) ) ==g_ExeEnv.m_szStartDir );

	}

	

	jt_strcpy(g_ExeEnv.m_szStartDir, save_start_path);
#endif
}
jTEST(jFolder_CreateDirForce)
{
	nMech::nFileSystem::jFolder dir; // 시작폴더로 이동.
	path_t buf1;
	//dir.Goto(dir.GetTempDir(buf1));
	jCHECK(dir.CreateDirForce(_T("test/../test/test12/test13\\test14")) ); // test14라는 폴더는 안만들어짐.
	jCHECK(dir.Is_Exist(_T("test/../test/test12\\test13")) );
	TCHAR buf[1024];
	dir.RemoveAll(_T("test/../test/test12"));
	jCHECK(!dir.Is_Exist(buf) );

	tcstr szTestDir = _T("test/../test/12test12/./12test13\\12test14\\");
	jCHECK(dir.CreateDirForce(szTestDir) ); // 12test14\\라는 폴더가 만들어짐.
	jCHECK(dir.Is_Exist(szTestDir) );
	dir.RemoveAll(_T("test/../test/12test12/") );
	jCHECK(!dir.Is_Exist(szTestDir) );

}

jTEST_SUITE_END(nFileSystem_)
