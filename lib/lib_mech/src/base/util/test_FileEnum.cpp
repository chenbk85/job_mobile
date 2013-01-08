#include "stdafx.h"
#include "juFileEnum.h"

#include "base/jTestUnit.h"

using namespace nMech;

void find_exe(tcstr szPath)
{
	//tcout << szPath <<endl;
	/* Ãâ·Â 
	z:\tr_server\bin\release_vc80\jBase.dll
	z:\tr_server\bin\release_vc80\jBase.exp
	z:\tr_server\bin\release_vc80\jBase.lib
	z:\tr_server\bin\release_vc80\jBase.pdb
	z:\tr_server\bin\release_vc80\jGlobal.ini
	z:\tr_server\bin\release_vc80\jUtil.dll
	z:\tr_server\bin\release_vc80\jUtil.exp
	z:\tr_server\bin\release_vc80\jUtil.lib
	z:\tr_server\bin\release_vc80\jUtil.pdb
	z:\tr_server\bin\release_vc80\test_jBase_vc80.exe
	*/
}

jTEST(for_each_folder_)
{
	//nFileSystem::jFolder dir;
	//dir.Goto(g_ExeEnv.m_szModuleDir);
	try
	{
		nFileSystem::for_each_folder(g_ExeEnv.m_szModuleDir, find_exe);
		nFileSystem::for_each_folder(g_ExeEnv.m_szStartDir, find_exe);
	}
	catch (...)
	{
	}

}

