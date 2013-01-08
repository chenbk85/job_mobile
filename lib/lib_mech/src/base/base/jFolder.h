/* 
	filename:	jFolder.h
	coder	:	Cho Wook Rea (mech12@dreamwiz.com) 
	comp.	:	f2system 
	compiler:	vc++ 6.0
	date	:	2000 / 01 / 
	title	:	
*/

#ifndef __UDirectoryManager_h__
#define __UDirectoryManager_h__
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nFileSystem
	{
		//--------------------------------------------------------------------------
		class  JBASE_API jFolder
			//--------------------------------------------------------------------------
		{
		protected:
#pragma warning(disable : 4251)
			jLIST_TYPEDEF_vector(std::tstring, m_Stack);
#pragma warning(default: 4251)
			//static	path_t	m_szTempDir;
		public:
			jFolder::jFolder(bool isGotoStartDir=true)			;
			~jFolder();

			size_t size(){ return m_Stack.size(); } //현제 이동한 폴더 갯수.
			void clear(){	while(GoBack());}//시작 위치까지 GoBack()한다. 매처음시작위치로 이동.
			m_Stack_it begin(){ return m_Stack.begin();}
			m_Stack_it end() { return m_Stack.end();}

			// g_ExeEnv.m_szStartDir로 이동. 
			// 현제폴더와 시작폴더가 같으면 false리턴
			bool GotoStartDir();

			// 현제 폴더를 buf에 담아서 그대로 리턴한다.
			// 주의 : 마지막에 \를 붙혀서 리턴한다.
			static tcstr	GetCurDir(path_t& buf);

			tcstr GetTempDir(path_t& buf);//임시폴더를 리턴

			
			// 해당 파일이름에서 경로명만 추출하여 해당 폴더로 이동한다.
			// 주의: 상대경로일경우 g_ExeEnv.m_szStartDir 이 기준 폴더이다.
			void jFolder::GotoByFileName(tcstr s) ;

			bool jFolder::GoBack(); //이전 폴더로 이동. false를 리턴하면 맨처음으로 되돌아온것이다.
			
			// 이동하기전 현제 폴더를 스택에 저장.
			// 이동한 폴더와 이전폴더가 같다면 스텍에 저장하지 않는다. false를 리턴
			// 해당 폴더가 없으면 에러스트링 예외날림
			bool jFolder::Goto(tcstr s); // 존재하면 이동 존재하지 않으면 예외처리

			bool jFolder::GotoIf(tcstr s);// 존재하면 이동하고 존재하지 않으면 false 리턴.
			void jFolder::GotoForce(tcstr s);// 존재하지 않으면 만들어서 이동
			static bool CreateDirForce( tcstr sSrcFullPath_ );// 여러경로로 되어 있는 폴더에 대해 각각의 폴더를 강제로 만듬.
			static bool CreateDir(tcstr sz);// 해당 leaf 폴더를 만듬. 만약 경로상의 부모폴더가 없으면 실패
			static void RemoveAll(tcstr sz); //sz폴더를 하위폴더포함하여 삭제
			static bool Is_Exist(tcstr sz);// 해당 파일 or 폴더가 존재하나?
			static bool Is_Dir(tcstr sz	); // 해당 파일이 폴더인가?

			static wcstr  FindFileNameInPath (wcstr  szFilePath);
			static wcstr  FindExtension (wcstr  szFileName);

			static acstr  FindFileNameInPath (acstr  szFilePath);
			static acstr  FindExtension (acstr  szFileName);


		};
		inline std::wstring GetParentDirectory (const std::wstring& strFilePath, int nGeneration=1)
		{
			for (const WCHAR* p = strFilePath.c_str() + strFilePath.length() - 2; // -2 is for the possible trailing slash: there always must be some trailing symbol which is the file/directory name for which we should get the parent
				p >= strFilePath.c_str();
				--p)
			{
				switch (*p)
				{
				case ':':
					return std::wstring (strFilePath.c_str(), p);
					break;
				case '/':
				case '\\':
					// we've reached a path separator - return everything before it.
					if (!--nGeneration)
						return std::wstring(strFilePath.c_str(), p);
					break;
				}
			};
			// it seems the file name is a pure name, without path or extension
			return std::wstring();
		}
		inline static std::astring GetParentDirectory (const std::astring& strFilePath, int nGeneration=1)
		{
			for (const CHAR* p = strFilePath.c_str() + strFilePath.length() - 2; // -2 is for the possible trailing slash: there always must be some trailing symbol which is the file/directory name for which we should get the parent
				p >= strFilePath.c_str();
				--p)
			{
				switch (*p)
				{
				case ':':
					return std::astring (strFilePath.c_str(), p);
					break;
				case '/':
				case '\\':
					// we've reached a path separator - return everything before it.
					if (!--nGeneration)
						return std::astring(strFilePath.c_str(), p);
					break;
				}
			};
			// it seems the file name is a pure name, without path or extension
			return std::astring();
		}

	}// nFileSystem
}




#endif //__UDirectoryManager_h__
