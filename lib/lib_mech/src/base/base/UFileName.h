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
			*	리소스용 패스는 3가지 유형이 있다.
			첫째는 완전한 패스가 설정된 것으로 c:\a\a.xml형태이며 MakePath()콜 후에도  buffers는 그대로 이다.
			2. g_ExeEnv.m_szStartDir을 생략한 패스로서  xml\a.xml 형태 MakePath()콜후에도 buffer는 그대로이다.
			3. g_ExeEnv.m_szStartDir 와 szPath가 결합된 상태의 폴더를 기준으로 상대적 폴더로 지정된경우다.
			MakePath()콜후에는 szPath ("xml") + buffers("subfolder\a.xml") 의 형태가 된다.  -> xml\subfolder\a.xml
			*/
			bool IsFileExist();

		};

	}//nFileSystem

}

#endif // __nFileSystemUFileName_header__
