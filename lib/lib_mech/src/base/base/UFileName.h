/* file : nFileSystem::jFileName.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-12-29 17:43:55
title : 
desc : 

*/

#ifndef __nFileSystemUFileName_header__
#define __nFileSystemUFileName_header__
#pragma once

#include "header/jFileName.h"

namespace nMech
{
	namespace nFileSystem
	{
#pragma warning(disable : 4275)
		
		//****************************************************************
		class JBASE_API UFileName : public jFileName
			//****************************************************************
		{
#pragma warning(default : 4275)
		public:
			UFileName(){}
			UFileName(tcstr s): jFileName(s){}

			/*
			*	���ҽ��� �н��� 3���� ������ �ִ�.
			ù°�� ������ �н��� ������ ������ c:\a\a.xml�����̸� MakePath()�� �Ŀ���  buffers�� �״�� �̴�.
			2. g_ExeEnv.m_szStartDir�� ������ �н��μ�  xml\a.xml ���� MakePath()���Ŀ��� buffer�� �״���̴�.
			3. g_ExeEnv.m_szStartDir �� szPath�� ���յ� ������ ������ �������� ����� ������ �����Ȱ���.
			MakePath()���Ŀ��� szPath ("xml") + buffers("subfolder\a.xml") �� ���°� �ȴ�.  -> xml\subfolder\a.xml
			*/
			bool IsFileExist();

		};

	}//nFileSystem

}

#endif // __nFileSystemUFileName_header__
