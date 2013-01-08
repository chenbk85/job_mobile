////////////////////////////////////////////////////////////////////////////
//
//  jGame Source File.
//  Copyright (C), jGame, 2002.
// -------------------------------------------------------------------------
//  File name:   jcFile.h
//  Version:     v1.00
//  Created:     3/7/2003 by Timur.
//  Compilers:   Visual Studio.NET
//  Description: File wrapper.
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef __jcFile_h__
#define __jcFile_h__
#pragma once

#include "ISystem.h"
#include "interface/jIPak.h"

//////////////////////////////////////////////////////////////////////////
// Wrapper on file system.
//////////////////////////////////////////////////////////////////////////
namespace nMech
{
	namespace nJC
	{

		class CjcFile
		{
		public:
			CjcFile();
			CjcFile( const char *filename, const char *mode );
			virtual ~CjcFile();

			virtual bool Open( const char *filename, const char *mode );
			virtual void Close();

			//! Writes data in a file to the current file position.
			virtual size_t Write( void *lpBuf,size_t nSize );
			//! Reads data from a file at the current file position.
			virtual size_t Read( void *lpBuf,size_t nSize );
			//! Retrieves the length of the file.
			virtual size_t GetLength();

			//! Positions the current file pointer.
			virtual size_t Seek( size_t seek, int mode );
			//! Positions the current file pointer at the beginning of the file.
			void SeekToBegin();
			//! Positions the current file pointer at the end of the file.
			size_t SeekToEnd();
			//! Retrieves the current file pointer.
			size_t GetPosition();

			//! Tests for end-of-file on a selected file.
			virtual bool IsEof();

			//! Flushes any data yet to be written.
			virtual void Flush();

			//! A handle to a pack object.
			FILE* GetHandle() const { return m_file; };

			// Retrieves the filename of the selected file.
			const char* GetFilename() const { return m_filename.c_str(); };

			//! Check if file is opened from pak file.
			bool IsInPak() const;

			//! Get path of archive this file is in.
			const char* GetPakPath() const;

		private:
			string m_filename;
			FILE *m_file;
		};

		//////////////////////////////////////////////////////////////////////////
		// CjcFile implementation.
		//////////////////////////////////////////////////////////////////////////
		inline CjcFile::CjcFile()
		{
			m_file = 0;
		}

		//////////////////////////////////////////////////////////////////////////
		inline CjcFile::CjcFile( const char *filename, const char *mode )
		{
			m_file = 0;
			Open( filename,mode );
		}

		//////////////////////////////////////////////////////////////////////////
		inline CjcFile::~CjcFile()
		{
			Close();
		}

		//////////////////////////////////////////////////////////////////////////
		inline bool CjcFile::Open( const char *filename, const char *mode )
		{
			if (m_file)
				Close();
			m_filename = filename;
			m_file = nInterface::g_pjIPak->FOpen( filename,mode );
			return m_file != NULL;
		}

		//////////////////////////////////////////////////////////////////////////
		inline void CjcFile::Close()
		{
			if (m_file)
			{
				nInterface::g_pjIPak->FClose(m_file);
				m_file = 0;
				m_filename = "";
			}
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t CjcFile::Write( void *lpBuf,size_t nSize )
		{
			assert( m_file );
			return nInterface::g_pjIPak->FWrite( lpBuf,1,nSize,m_file );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t CjcFile::Read( void *lpBuf,size_t nSize )
		{
			assert( m_file );
			return nInterface::g_pjIPak->FRead( lpBuf,1,nSize,m_file );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t CjcFile::GetLength()
		{
			assert( m_file );
			long curr = nInterface::g_pjIPak->FTell(m_file);
			nInterface::g_pjIPak->FSeek( m_file,0,SEEK_END );
			long size = nInterface::g_pjIPak->FTell(m_file);
			nInterface::g_pjIPak->FSeek(m_file,curr,SEEK_SET);
			return size;
		}

#ifdef WIN64
#pragma warning( push )									//AMD Port
#pragma warning( disable : 4267 )
#endif

		//////////////////////////////////////////////////////////////////////////
		inline size_t CjcFile::Seek( size_t seek, int mode )
		{
			assert( m_file );
			return nInterface::g_pjIPak->FSeek( m_file,seek,mode );
		}

#ifdef WIN64
#pragma warning( pop )									//AMD Port
#endif

		//////////////////////////////////////////////////////////////////////////
		inline void CjcFile::SeekToBegin()
		{
			Seek( 0,SEEK_SET );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t CjcFile::SeekToEnd()
		{
			Seek( 0,SEEK_END );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t CjcFile::GetPosition()
		{
			assert(m_file);
			return nInterface::g_pjIPak->FTell(m_file);
		}

		//////////////////////////////////////////////////////////////////////////
		inline bool CjcFile::IsEof()
		{
			assert(m_file);
			return nInterface::g_pjIPak->FEof(m_file) != 0;
		}

		//////////////////////////////////////////////////////////////////////////
		inline void CjcFile::Flush()
		{
			assert( m_file );
			nInterface::g_pjIPak->FFlush( m_file );
		}

		//////////////////////////////////////////////////////////////////////////
		inline bool CjcFile::IsInPak() const
		{
			if (m_file)
			{
				if (nInterface::g_pjIPak->GetFileArchivePath(m_file) != NULL)
					return true;
			}
			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		inline const char* CjcFile::GetPakPath() const
		{
			if (m_file)
			{
				const char *sPath = nInterface::g_pjIPak->GetFileArchivePath(m_file);
				if (sPath != NULL)
					return sPath;
			}
			return "";
		}

	}//nJC
}//nMech


#endif // __jcFile_h__
