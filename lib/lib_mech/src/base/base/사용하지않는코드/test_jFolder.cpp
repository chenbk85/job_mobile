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
	jt_strcpy(save_start_path , g_ExeEnv.m_szStartDir); // �ϴ� g_ExeEnv�� ���� ���


	path_t curr_dir;
	GetCurrentDirectory(sizeof(curr_dir), curr_dir);
	jt_strlwr(curr_dir);
	jCHECK(curr_dir[jt_strlen(curr_dir)-2] != '\\');// �н��� �ڰ� \�� ������ �ʴ´�.
	jt_strcat(curr_dir,_T("\\")); //�������� \�� ������

	path_t temp_dir;
	path_t exe_name;
	GetModuleFileName(0, exe_name, sizeof(exe_name));
	jt_strlwr(exe_name);
	UFileName fn(exe_name);
	path_t module_path;
	fn.GetPath(module_path);
	{
		int iCount=0;
		jFolder dir(false);//������ġ�� �̵�����.
		path_t buf_currpath;
		dir.GetCurDir(buf_currpath);
		jEQUAL(dir.size(), 0);
		jCHECK(dir.Goto(buf_currpath) ==false);
		jCHECK(dir.Goto(_T("..") ) ==true);
		
		//��������� ���������� ���������� ����
		jt_strcpy(g_ExeEnv.m_szStartDir,  dir.GetCurDir(temp_dir)); 

		jEQUAL(dir.size(), 1); // 

		dir.clear(); // �����·� ����. 
		jEQUAL( dir.size()  ,0); 

		//GetModuleFileName()�� ������ �̵��ߴ��� Ȯ��.
		jCHECK(std::tstring(dir.GetCurDir(temp_dir)) ==tstring(curr_dir) );
	}

	path_t curr_dir2;
	GetCurrentDirectory(sizeof(curr_dir2), curr_dir2);
	jt_strcat(curr_dir2,_T("\\")); //�������� \�� ������

	jCHECK(std::tstring(curr_dir) ==tstring(curr_dir2) ); // ���� ������ �ǵ��� �;���.

	{
		jFolder dir(true);//������ġ�� �̵�.
		jCHECK(std::tstring(dir.GetCurDir(temp_dir))==tstring(g_ExeEnv.m_szStartDir) );

		dir.GotoByFileName(exe_name);
		tstring currDir1 = dir.GetCurDir(temp_dir);
		jCHECK( currDir1 == g_ExeEnv.m_szModuleDir );

		//--------------------------------------------------------------------------
		// jFolder::Goto()�� ���ܻ�Ȳó��
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
		//GotoForce()  ��� ��
		//--------------------------------------------------------------------------
		try
		{
			path_t buf1,buf2;
			dir.GetCurDir(buf1);
			dir.Goto(_T("..")); 
			dir.GetCurDir((buf2));
			
			//���� dir.GotoForce("..\\test\\test1\\test2") �̷������� ����ϸ� �ȵ�.
			//--------------------------------------------------------------------------
			//���� dir.GotoForce(_T("test\\test1\\test2"));�� test\test1������ ������ ����.
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
			jEQUAL(dir.size() , iCurr+2);// �̵�������
		}
		else
			jEQUAL(dir.size() , iCurr+1); // �̵� ���н�
		
		dir.GotoStartDir();
		jCHECK(std::tstring(dir.GetCurDir(temp_dir) ) ==g_ExeEnv.m_szStartDir );

	}

	

	jt_strcpy(g_ExeEnv.m_szStartDir, save_start_path);
#endif
}
jTEST(jFolder_CreateDirForce)
{
	nMech::nFileSystem::jFolder dir; // ���������� �̵�.
	path_t buf1;
	//dir.Goto(dir.GetTempDir(buf1));
	jCHECK(dir.CreateDirForce(_T("test/../test/test12/test13\\test14")) ); // test14��� ������ �ȸ������.
	jCHECK(dir.Is_Exist(_T("test/../test/test12\\test13")) );
	TCHAR buf[1024];
	dir.RemoveAll(_T("test/../test/test12"));
	jCHECK(!dir.Is_Exist(buf) );

	tcstr szTestDir = _T("test/../test/12test12/./12test13\\12test14\\");
	jCHECK(dir.CreateDirForce(szTestDir) ); // 12test14\\��� ������ �������.
	jCHECK(dir.Is_Exist(szTestDir) );
	dir.RemoveAll(_T("test/../test/12test12/") );
	jCHECK(!dir.Is_Exist(szTestDir) );

}

jTEST_SUITE_END(nFileSystem_)
