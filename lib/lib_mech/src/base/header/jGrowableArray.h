/* 
	filename:	jGrowableArray.h
	coder	:	Cho Hyun Min (icandoit@wemade.com) 
	comp.	:	-we_jGame_made-
	compiler:	vc++ 6.0
	date	:	4338-01-04 ¿ÀÈÄ 6:41:33
	title	:	
*/


#ifndef __jGrowableArray_h__
#define __jGrowableArray_h__
//#if _MSC_VER > 1000
#pragma once
//#endif // _MSC_VER > 1000

namespace nMech
{
	namespace nDataStruct
	{
		template< typename TYPE >
		class jGrowableArray
		{
		public:
			jGrowableArray()  { m_pData = NULL; m_nSize = 0; m_nMaxSize = 0; }
			jGrowableArray( const jGrowableArray<TYPE>& a ) { for( int i=0; i < a.m_nSize; i++ ) Add( a.m_pData[i] ); }
			~jGrowableArray() { RemoveAll(); }

			const TYPE& operator[]( int nIndex ) const { return GetAt( nIndex ); }
			TYPE& operator[]( int nIndex ) { return GetAt( nIndex ); }

			jGrowableArray& operator=( const jGrowableArray<TYPE>& a ) { if( this == &a ) return *this; RemoveAll(); for( int i=0; i < a.m_nSize; i++ ) Add( a.m_pData[i] ); return *this; }

			HRESULT SetSize( int nNewMaxSize );
			HRESULT Add( const TYPE& value );
			HRESULT Insert( int nIndex, const TYPE& value );
			HRESULT SetAt( int nIndex, const TYPE& value );
			TYPE&   GetAt( int nIndex ) { assert( nIndex >= 0 && nIndex < m_nSize ); return m_pData[nIndex]; }
			int     GetSize() const { return m_nSize; }
			TYPE*   GetData() { return m_pData; }
			bool    Contains( const TYPE& value ){ return ( -1 != IndexOf( value ) ); }

			int     IndexOf( const TYPE& value ) { return ( m_nSize > 0 ) ? IndexOf( value, 0, m_nSize ) : -1; }
			int     IndexOf( const TYPE& value, int iStart ) { return IndexOf( value, iStart, m_nSize - iStart ); }
			int     IndexOf( const TYPE& value, int nIndex, int nNumElements );

			int     LastIndexOf( const TYPE& value ) { return ( m_nSize > 0 ) ? LastIndexOf( value, m_nSize-1, m_nSize ) : -1; }
			int     LastIndexOf( const TYPE& value, int nIndex ) { return LastIndexOf( value, nIndex, nIndex+1 ); }
			int     LastIndexOf( const TYPE& value, int nIndex, int nNumElements );

			HRESULT Remove( int nIndex );
			void    RemoveAll() { SetSize(0); }

		protected:
			TYPE* m_pData;      // the actual array of data
			int m_nSize;        // # of elements (upperBound - 1)
			int m_nMaxSize;     // max allocated

			HRESULT SetSizeInternal( int nNewMaxSize );  // This version doesn't call ctor or dtor.
		};


		//--------------------------------------------------------------------------------------
		// Implementation of jGrowableArray
		//--------------------------------------------------------------------------------------

		// This version doesn't call ctor or dtor.
		template< typename TYPE >
			HRESULT jGrowableArray<TYPE>::SetSizeInternal( int nNewMaxSize )
		{
			if( nNewMaxSize < 0 )
			{
				assert( false );
				return E_INVALIDARG;
			}

			if( nNewMaxSize == 0 )
			{
				// Shrink to 0 size & cleanup
				if( m_pData )
				{
					free( m_pData );
					m_pData = NULL;
				}

				m_nMaxSize = 0;
				m_nSize = 0;
			}
			else if( m_pData == NULL || nNewMaxSize > m_nMaxSize )
			{
				// Grow array
				int nGrowBy = ( m_nMaxSize == 0 ) ? 16 : m_nMaxSize;
				nNewMaxSize = max( nNewMaxSize, m_nMaxSize + nGrowBy );

				TYPE* pDataNew = (TYPE*) realloc( m_pData, nNewMaxSize * sizeof(TYPE) );
				if( pDataNew == NULL )
					return E_OUTOFMEMORY;

				m_pData = pDataNew;
				m_nMaxSize = nNewMaxSize;
			}

			return S_OK;
		}


		//--------------------------------------------------------------------------------------
		template< typename TYPE >
			HRESULT jGrowableArray<TYPE>::SetSize( int nNewMaxSize )
		{
			int nOldSize = m_nSize;

			if( nOldSize > nNewMaxSize )
			{
				// Removing elements. Call dtor.

				for( int i = nNewMaxSize; i < nOldSize; ++i )
					m_pData[i].~TYPE();
			}

			// Adjust buffer.  Note that there's no need to check for error
			// since if it happens, nOldSize == nNewMaxSize will be true.)
			HRESULT hr = SetSizeInternal( nNewMaxSize );

			if( nOldSize < nNewMaxSize )
			{
				// Adding elements. Call ctor.

				for( int i = nOldSize; i < nNewMaxSize; ++i )
					::new (&m_pData[i]) TYPE;
			}

			return hr;
		}


		//--------------------------------------------------------------------------------------
		template< typename TYPE >
			HRESULT jGrowableArray<TYPE>::Add( const TYPE& value )
		{
			HRESULT hr;
			if( FAILED( hr = SetSizeInternal( m_nSize + 1 ) ) )
				return hr;

			// Construct the new element
			::new (&m_pData[m_nSize]) TYPE;

			// Assign
			m_pData[m_nSize] = value;
			++m_nSize;

			return S_OK;
		}


		//--------------------------------------------------------------------------------------
		template< typename TYPE >
			HRESULT jGrowableArray<TYPE>::Insert( int nIndex, const TYPE& value )
		{
			HRESULT hr;

			// Validate index
			if( nIndex < 0 || 
				nIndex > m_nSize )
			{
				assert( false );
				return E_INVALIDARG;
			}

			// Prepare the buffer
			if( FAILED( hr = SetSizeInternal( m_nSize + 1 ) ) )
				return hr;

			// Shift the array
			MoveMemory( &m_pData[nIndex+1], &m_pData[nIndex], sizeof(TYPE) * (m_nSize - nIndex) );

			// Construct the new element
			::new (&m_pData[nIndex]) TYPE;

			// Set the value and increase the size
			m_pData[nIndex] = value;
			++m_nSize;

			return S_OK;
		}


		//--------------------------------------------------------------------------------------
		template< typename TYPE >
			HRESULT jGrowableArray<TYPE>::SetAt( int nIndex, const TYPE& value )
		{
			// Validate arguments
			if( nIndex < 0 ||
				nIndex >= m_nSize )
			{
				assert( false );
				return E_INVALIDARG;
			}

			m_pData[nIndex] = value;
			return S_OK;
		}


		//--------------------------------------------------------------------------------------
		// Searches for the specified value and returns the index of the first occurrence
		// within the section of the data array that extends from iStart and contains the 
		// specified number of elements. Returns -1 if value is not found within the given 
		// section.
		//--------------------------------------------------------------------------------------
		template< typename TYPE >
			int jGrowableArray<TYPE>::IndexOf( const TYPE& value, int iStart, int nNumElements )
		{
			// Validate arguments
			if( iStart < 0 || 
				iStart >= m_nSize ||
				nNumElements < 0 ||
				iStart + nNumElements > m_nSize )
			{
				assert( false );
				return -1;
			}

			// Search
			for( int i = iStart; i < (iStart + nNumElements); i++ )
			{
				if( value == m_pData[i] )
					return i;
			}

			// Not found
			return -1;
		}


		//--------------------------------------------------------------------------------------
		// Searches for the specified value and returns the index of the last occurrence
		// within the section of the data array that contains the specified number of elements
		// and ends at iEnd. Returns -1 if value is not found within the given section.
		//--------------------------------------------------------------------------------------
		template< typename TYPE >
			int jGrowableArray<TYPE>::LastIndexOf( const TYPE& value, int iEnd, int nNumElements )
		{
			// Validate arguments
			if( iEnd < 0 || 
				iEnd >= m_nSize ||
				nNumElements < 0 ||
				iEnd - nNumElements < 0 )
			{
				assert( false );
				return -1;
			}

			// Search
			for( int i = iEnd; i > (iEnd - nNumElements); i-- )
			{
				if( value == m_pData[i] )
					return i;
			}

			// Not found
			return -1;
		}



		//--------------------------------------------------------------------------------------
		template< typename TYPE >
			HRESULT jGrowableArray<TYPE>::Remove( int nIndex )
		{
			if( nIndex < 0 || 
				nIndex >= m_nSize )
			{
				assert( false );
				return E_INVALIDARG;
			}

			// Destruct the element to be removed
			m_pData[nIndex].~TYPE();

			// Compact the array and decrease the size
			MoveMemory( &m_pData[nIndex], &m_pData[nIndex+1], sizeof(TYPE) * (m_nSize - (nIndex+1)) );
			--m_nSize;

			return S_OK;
		}

	}//nHEADER


}



#endif //__jGrowableArray_h__
