// FileEnum.h: Interface of the class juFileEnum.
//
//////////////////////////////////////////////////////////////////////

#if !defined(__juFileEnum_H__)
#define __juFileEnum_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nFileSystem
	{
		typedef void for_each_folder_function_t(tcstr szFile,void*);
		// 중간에 함수를 종료하고 싶을땐 func에서 예외발생할것.
		extern JUTIL_API void for_each_folder( tcstr pathDest ,for_each_folder_function_t* func ,void*);
/*
		// 중간에 함수를 종료하고 싶을땐 func에서 예외발생할것.
		inline void for_each_folder( boost::filesystem::path& pathDest ,boost::function<void (boost::filesystem::path&)> func )
		{
			namespace fs = boost::filesystem;
			fs::directory_iterator end;
			fs::directory_iterator it(pathDest);
			for( ; it!=end; ++it )
			{
				if( fs::is_directory(*it) )
					for_each_folder(*it,func);
				else
					func(*it);
			}
		}
*/
#if 0 
		class juFileEnum  
		{
		public:
			static bool ScanDirectory( const tstring &path,const tstring &file,std::vector<tstring> &files, bool recursive=true );

			bool GetNextFile(struct __finddata64_t *pFile);
			bool StartEnumeration( const char *szEnumPathAndPattern, __finddata64_t *pFile);
			bool StartEnumeration( const char *szEnumPath, char szEnumPattern[], __finddata64_t *pFile);
			juFileEnum();
			virtual ~juFileEnum();
		protected:
			intptr_t m_hEnumFile;
		};
#endif

	}
}


#endif // !defined(__juFileEnum_H__)
