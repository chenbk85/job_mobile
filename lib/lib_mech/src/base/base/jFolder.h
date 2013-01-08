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

			size_t size(){ return m_Stack.size(); } //���� �̵��� ���� ����.
			void clear(){	while(GoBack());}//���� ��ġ���� GoBack()�Ѵ�. ��ó��������ġ�� �̵�.
			m_Stack_it begin(){ return m_Stack.begin();}
			m_Stack_it end() { return m_Stack.end();}

			// g_ExeEnv.m_szStartDir�� �̵�. 
			// ���������� ���������� ������ false����
			bool GotoStartDir();

			// ���� ������ buf�� ��Ƽ� �״�� �����Ѵ�.
			// ���� : �������� \�� ������ �����Ѵ�.
			static tcstr	GetCurDir(path_t& buf);

			tcstr GetTempDir(path_t& buf);//�ӽ������� ����

			
			// �ش� �����̸����� ��θ� �����Ͽ� �ش� ������ �̵��Ѵ�.
			// ����: ������ϰ�� g_ExeEnv.m_szStartDir �� ���� �����̴�.
			void jFolder::GotoByFileName(tcstr s) ;

			bool jFolder::GoBack(); //���� ������ �̵�. false�� �����ϸ� ��ó������ �ǵ��ƿ°��̴�.
			
			// �̵��ϱ��� ���� ������ ���ÿ� ����.
			// �̵��� ������ ���������� ���ٸ� ���ؿ� �������� �ʴ´�. false�� ����
			// �ش� ������ ������ ������Ʈ�� ���ܳ���
			bool jFolder::Goto(tcstr s); // �����ϸ� �̵� �������� ������ ����ó��

			bool jFolder::GotoIf(tcstr s);// �����ϸ� �̵��ϰ� �������� ������ false ����.
			void jFolder::GotoForce(tcstr s);// �������� ������ ���� �̵�
			static bool CreateDirForce( tcstr sSrcFullPath_ );// ������η� �Ǿ� �ִ� ������ ���� ������ ������ ������ ����.
			static bool CreateDir(tcstr sz);// �ش� leaf ������ ����. ���� ��λ��� �θ������� ������ ����
			static void RemoveAll(tcstr sz); //sz������ �������������Ͽ� ����
			static bool Is_Exist(tcstr sz);// �ش� ���� or ������ �����ϳ�?
			static bool Is_Dir(tcstr sz	); // �ش� ������ �����ΰ�?

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
