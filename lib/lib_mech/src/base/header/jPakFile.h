/* file : jPakFile.h
Coder : by icandoit (mech12@nate.com)
Where (^^;) gam_jGame_ple
Date : 2005-08-29 10:46:56
title : 
desc : 

*/

#ifndef __jPakFile_header__
#define __jPakFile_header__
#pragma once



#pragma once

#include "interface\\jIPak.h"

namespace nMech
{
	namespace nPAK
	{
		//////////////////////////////////////////////////////////////////////////
		// Wrapper on file system.
		//////////////////////////////////////////////////////////////////////////
		class jPakFile
		{
		public:
			jPakFile();
			jPakFile( tcstr filename, tcstr mode );
			virtual ~jPakFile();

			virtual bool Open( tcstr filename, tcstr mode );
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
			tcstr GetFilename() const { return m_filename.c_str(); };

			//! Check if file is opened from pak file.
			bool IsInPak() const;

			//! Get path of archive this file is in.
			const char* GetPakPath() const;

		private:
			std::tstring m_filename;
			FILE *m_file;
			jIPak *m_pIPak;
		};

		//////////////////////////////////////////////////////////////////////////
		// jPakFile implementation.
		//////////////////////////////////////////////////////////////////////////
		inline jPakFile::jPakFile()
		{
			m_file = 0;
			m_pIPak = nInterface::g_pjIPak;
		}

		//////////////////////////////////////////////////////////////////////////
		inline jPakFile::jPakFile( tcstr filename, tcstr mode )
		{
			m_file = 0;
			m_pIPak = nInterface::g_pjIPak;
			Open( filename,mode );
		}

		//////////////////////////////////////////////////////////////////////////
		inline jPakFile::~jPakFile()
		{
			Close();
		}

		//////////////////////////////////////////////////////////////////////////
		inline bool jPakFile::Open( tcstr filename, tcstr mode )
		{
			if (m_file)
				Close();
			m_filename = filename;
			m_file = m_pIPak->FOpen( jA(filename),jA(mode ));
			return m_file != NULL;
		}

		//////////////////////////////////////////////////////////////////////////
		inline void jPakFile::Close()
		{
			if (m_file)
			{
				m_pIPak->FClose(m_file);
				m_file = 0;
				m_filename = _T("");
			}
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t jPakFile::Write( void *lpBuf,size_t nSize )
		{
			assert( m_file );
			return m_pIPak->FWrite( lpBuf,1,nSize,m_file );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t jPakFile::Read( void *lpBuf,size_t nSize )
		{
			assert( m_file );
			return m_pIPak->FRead( lpBuf,1,nSize,m_file );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t jPakFile::GetLength()
		{
			assert( m_file );
			long curr = m_pIPak->FTell(m_file);
			m_pIPak->FSeek( m_file,0,SEEK_END );
			long size = m_pIPak->FTell(m_file);
			m_pIPak->FSeek(m_file,curr,SEEK_SET);
			return size;
		}

#ifdef WIN64
#pragma warning( push )									//AMD Port
#pragma warning( disable : 4267 )
#endif

		//////////////////////////////////////////////////////////////////////////
		inline size_t jPakFile::Seek( size_t seek, int mode )
		{
			assert( m_file );
			return m_pIPak->FSeek( m_file,seek,mode );
		}

#ifdef WIN64
#pragma warning( pop )									//AMD Port
#endif

		//////////////////////////////////////////////////////////////////////////
		inline void jPakFile::SeekToBegin()
		{
			Seek( 0,SEEK_SET );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t jPakFile::SeekToEnd()
		{
			Seek( 0,SEEK_END );
		}

		//////////////////////////////////////////////////////////////////////////
		inline size_t jPakFile::GetPosition()
		{
			assert(m_file);
			return m_pIPak->FTell(m_file);
		}

		//////////////////////////////////////////////////////////////////////////
		inline bool jPakFile::IsEof()
		{
			assert(m_file);
			return m_pIPak->FEof(m_file) != 0;
		}

		//////////////////////////////////////////////////////////////////////////
		inline void jPakFile::Flush()
		{
			assert( m_file );
			m_pIPak->FFlush( m_file );
		}

		//////////////////////////////////////////////////////////////////////////
		inline bool jPakFile::IsInPak() const
		{
			if (m_file)
			{
				if (m_pIPak->GetFileArchivePath(m_file) != NULL)
					return true;
			}
			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		inline const char* jPakFile::GetPakPath() const
		{
			if (m_file)
			{
				acstr sPath = m_pIPak->GetFileArchivePath(m_file);
				if (sPath != NULL)
					return sPath;
			}
			return "";
		}

	}//nPAK

}

#endif // __jPakFile_header__
