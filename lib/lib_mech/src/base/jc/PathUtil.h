////////////////////////////////////////////////////////////////////////////
//
//  jGame Source File.
//  Copyright (C), jGame, 2002.
// -------------------------------------------------------------------------
//  File name:   pathutil.h
//  Version:     v1.00
//  Created:     5/11/2002 by Timur.
//  Compilers:   Visual Studio.NET
//  Description: Utility functions to simplify working with paths.
// -------------------------------------------------------------------------
//  History:
//
////////////////////////////////////////////////////////////////////////////

#ifndef __pathutil_h__
#define __pathutil_h__
#pragma once

namespace Path
{
	//! Split full file name to path and filename
	//! @param filepath [IN] Full file name inclusing path.
	//! @param path [OUT] Extracted file path.
	//! @param file [OUT] Extracted file (with extension).
	inline void Split( const CString &filepath,CString &path,CString &file )
	{
		TCHAR path_buffer[_MAX_PATH];
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		jt_splitpath( filepath,drive,dir,fname,ext );
		jt_makepath( path_buffer,drive,dir,0,0 );
		path = path_buffer;
		jt_makepath( path_buffer,0,0,fname,ext );
		file = path_buffer;
	}

	//! Split full file name to path and filename
	//! @param filepath [IN] Full file name inclusing path.
	//! @param path [OUT] Extracted file path.
	//! @param filename [OUT] Extracted file (without extension).
	//! @param ext [OUT] Extracted files extension.
	inline void Split( const CString &filepath,CString &path,CString &filename,CString &fext )
	{
		TCHAR path_buffer[_MAX_PATH];
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		jt_splitpath( filepath,drive,dir,fname,ext );
		jt_makepath( path_buffer,drive,dir,0,0 );
		path = path_buffer;
		filename = fname;
		fext = ext;
	}

	//! Extract extension from full specified file path.
	inline CString GetExt( const CString &filepath )
	{
		TCHAR ext[_MAX_EXT];
		jt_splitpath( filepath,0,0,0,ext );
		if (ext[0] == '.')
			return ext+1;
		
		return ext;
	}

	//! Extract path from full specified file path.
	inline CString GetPath( const CString &filepath )
	{
		TCHAR path_buffer[_MAX_PATH];
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		jt_splitpath( filepath,drive,dir,0,0 );
		jt_makepath( path_buffer,drive,dir,0,0 );
		return path_buffer;
	}

	//! Extract file name with extension from full specified file path.
	inline CString GetFile( const CString &filepath )
	{
		TCHAR path_buffer[_MAX_PATH];
		TCHAR fname[_MAX_FNAME];
		TCHAR ext[_MAX_EXT];
		jt_splitpath( filepath,0,0,fname,ext );
		jt_makepath( path_buffer,0,0,fname,ext );
		return path_buffer;
	}

	//! Extract file name without extension from full specified file path.
	inline CString GetFileName( const CString &filepath )
	{
		TCHAR fname[_MAX_FNAME];
		jt_splitpath( filepath,0,0,fname,0 );
		return fname;
	}

	//! Removes the trailing backslash from a given path.
	inline CString RemoveBackslash( const CString &path )
	{
		if (path.IsEmpty() || path[path.GetLength()-1] != '\\')
			return path;
		return path.Mid( 0,path.GetLength()-1 );
	}

	//! add a backslash if needed
	inline CString AddBackslash( const CString &path )
	{
		if(path.IsEmpty() || path[path.GetLength()-1] == '\\')
			return path;

		return path + _T("\\");
	}

	//! Replace extension for givven file.
	inline CString ReplaceExtension( const CString &filepath,const CString &ext )
	{
		TCHAR path_buffer[_MAX_PATH];
		TCHAR drive[_MAX_DRIVE];
		TCHAR dir[_MAX_DIR];
		TCHAR fname[_MAX_FNAME];
		jt_splitpath( filepath,drive,dir,fname,0 );
		jt_makepath( path_buffer,drive,dir,fname,ext );
		return path_buffer;
	}

	//! Makes a fully specified file path from path and file name.
	inline CString Make( const CString &path,const CString &file )
	{
		return AddBackslash(path) + file;
	}

	//! Makes a fully specified file path from path and file name.
	inline CString Make( const CString &dir,const CString &filename,const CString &ext )
	{
		TCHAR path_buffer[_MAX_PATH];
		jt_makepath( path_buffer,NULL,dir,filename,ext );
		return path_buffer;
	}
};

#endif // __pathutil_h__
