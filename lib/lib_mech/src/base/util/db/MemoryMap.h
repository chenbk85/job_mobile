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
		namespace nSharedMem
		{

			template<class T>
			class CMemoryMap
			{
			private:
				int m_bCreateFlag;
				int m_hMemmap;
				int m_dwLength;
				int m_nMaxUnit;
				TCHAR m_szMemmapName[128];

				HANDLE	m_hMMFile;
				char*	m_lpMMFile;

				typedef typename std::vector<T *> UNITARRAY;
				UNITARRAY m_UnitArray;

			public:
				CMemoryMap();
				virtual ~CMemoryMap();

				typedef typename  UNITARRAY::iterator iterator;

				iterator begin() 
				{ 
					return m_UnitArray.begin(); 
				};

				iterator end() 
				{ 
					return m_UnitArray.end(); 
				};

				BOOL Init(LPCTSTR shm_name, int max_unit, unsigned long dwOffsetsize);

				void *GetSharedMemoryPtr() 
				{ 
					return m_lpMMFile; 
				};

				T *GetUnit(int nid);

				int GetCreateFlag() 
				{ 
					return m_bCreateFlag; 
				};

				int GetMaxSize() 
				{ 
					return m_nMaxUnit; 
				};
			};

			template <class T>
				CMemoryMap<T>::CMemoryMap()
			{
				m_hMemmap = -1;
				memset( m_szMemmapName, 0x00, 128 );
				m_dwLength = 0;
				m_bCreateFlag = 0;
				m_nMaxUnit = -1;
			}

			template <class T>
				CMemoryMap<T>::~CMemoryMap()
			{
			}

			template <class T>
				BOOL CMemoryMap<T>::Init(LPCTSTR shm_name, int max_unit, unsigned long dwOffsetsize)
			{
				BOOL bCreate = FALSE;

				_stprintf(m_szMemmapName, TEXT("%s"), shm_name);
				unsigned long filesize = max_unit * dwOffsetsize;
				m_nMaxUnit = max_unit;

				m_hMMFile = OpenFileMapping( FILE_MAP_ALL_ACCESS, TRUE, m_szMemmapName );

				if( m_hMMFile == NULL )
				{
					m_hMMFile = CreateFileMapping( (HANDLE)0xFFFFFFFF, NULL, PAGE_READWRITE, 0, filesize, m_szMemmapName );
					bCreate = TRUE;
				}

				if( m_hMMFile == NULL )
					return FALSE;

				if( (m_lpMMFile = (char*)MapViewOfFile(m_hMMFile, FILE_MAP_WRITE, 0, 0, 0)) == NULL )
					return FALSE;

				for (int i = 0; i < m_nMaxUnit; i++)
				{
					T *pUnit;
					pUnit = (T *)(m_lpMMFile+(dwOffsetsize*i));

					if(bCreate)
						memset(pUnit, 0x00, dwOffsetsize);

					m_UnitArray.push_back(pUnit);
				}

				return TRUE;
			}

			template <class T>
				T* CMemoryMap<T>::GetUnit(int nid)
			{
				if ( nid < 0 || nid >= m_nMaxUnit )
					return 0;

				return m_UnitArray[nid];
			};
		}//nSharedMem
	}// nUTIL
}// nMech

#endif
