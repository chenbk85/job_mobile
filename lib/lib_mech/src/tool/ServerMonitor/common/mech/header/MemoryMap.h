//----------------------------------------------------------------------------
// class CEverMemmap header file...
#ifndef __CMEMMAP_H
#define __CMEMMAP_H

#pragma warning(disable:4312)
#include <tchar.h>
#include <vector>

//----------------------------------------------------------------------------
namespace nMech
{
	namespace nUtil
	{
		template<typename T> class jMemoryMap
		{
		private:
			int m_bCreateFlag;
			int m_hMemmap;
			int m_dwLength;
			int m_iTot;
			TCHAR m_szMemmapName[128];

			HANDLE	m_hMMFile;
			char*	m_lpMMFile;

			std::vector<T*> m_DataList;
		public:

			typedef typename  std::vector<T*>::iterator iterator;

			iterator begin()			{ 				return m_DataList.begin();};
			iterator end() 				{ 				return m_DataList.end();};
			size_t	size() 				{ 				return m_iTot;}
			T*		at(size_t nid)			{if ( nid < 0 || nid >= size() ) return 0;return m_DataList[nid];};

			void*	GetSharedMemoryPtr(){ 			return m_lpMMFile;};
			int		GetCreateFlag() 	{ 				return m_bCreateFlag;};

			jMemoryMap(LPCTSTR shm_name, int max_unit){	Init(shm_name,max_unit);}
			jMemoryMap()
			{
				m_hMemmap = -1;
				memset( m_szMemmapName, 0x00, 128 );
				m_dwLength = 0;
				m_bCreateFlag = 0;
				m_iTot = -1;
			}

			// 최초 메모리 생성이면 true , 기존메모리 Open이면 false리턴
			bool Init(LPCTSTR shm_name, int max_unit)
			{
				const unsigned long iOBJ_SIZE = sizeof(T);
				bool bCreate = FALSE;

				_stprintf(m_szMemmapName, TEXT("%s"), shm_name);
				unsigned long filesize = max_unit * iOBJ_SIZE;
				m_iTot = max_unit;

				m_hMMFile = OpenFileMapping( FILE_MAP_ALL_ACCESS, TRUE, m_szMemmapName );

				if( m_hMMFile == NULL )
				{
					m_hMMFile = CreateFileMapping( INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, filesize, m_szMemmapName );
					bCreate = TRUE;
				}

				if( m_hMMFile == NULL )
					throw jFUNC _T("CreateFileMapping");

				if( (m_lpMMFile = (char*)MapViewOfFile(m_hMMFile, FILE_MAP_WRITE, 0, 0, 0)) == NULL )
					throw jFUNC _T("MapViewOfFile");

				for (size_t i = 0; i < size(); i++)
				{
					T *pUnit;
					pUnit = (T *)(m_lpMMFile+(iOBJ_SIZE*i));

					if(bCreate)
						memset(pUnit, 0x00, iOBJ_SIZE);

					m_DataList.push_back(pUnit);
				}

				return bCreate;
			}

		};


	}// nUTIL
}// nMech

#endif
