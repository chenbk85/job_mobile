/* file : jTypedef_type.h
Coder : by icandoit ( mech12@nate.com)
Date : 2006-11-29 12:43:10
comp.: pantavision.co.kr
title : 
desc : 

*/

#ifndef __jTypedef_type_header__
#define __jTypedef_type_header__
#pragma once

#if defined(WIN32) || defined(WIN64) || defined(_WIN32) || defined(_WIN64) 
#ifndef DEF_WINDOWS
#define DEF_WINDOWS
#endif
#else 
#define DEF_LINUX
#endif

#ifndef DEF_WINDOWS
typedef struct _SYSTEMTIME {
	WORD wYear;
	WORD wMonth;
	WORD wDayOfWeek;
	WORD wDay;
	WORD wHour;
	WORD wMinute;
	WORD wSecond;
	WORD wMilliseconds;
} SYSTEMTIME, *PSYSTEMTIME, *LPSYSTEMTIME;
#else
#include <winbase.h>
#endif


#ifdef __cplusplus
namespace nMech
{
#endif
	typedef char			int8;
	typedef unsigned char	uint8;
	typedef unsigned char	uchar;
	typedef unsigned int	uint;

	typedef double real;
	typedef int index_t;

	typedef SYSTEMTIME &	SYSTEMTIME_REF;

#if defined(WIN32) && !defined(WIN64)
	typedef signed short        int16;
	typedef signed int					int32;
	typedef signed __int64			int64;
	typedef unsigned char				uint8;
	typedef unsigned short			uint16;
	typedef unsigned int				uint32;
	typedef unsigned __int64		uint64;

	typedef float               f32;
	typedef double              f64;

	// old-style (will be removed soon)
	typedef signed __int64			s64;
	typedef unsigned int				u32;
	typedef unsigned __int64		u64;
#endif

#if defined(WIN64)
#pragma warning (disable : 4267)
	typedef signed short        int16;
	typedef signed long         int32;
	typedef signed __int64			int64;
	typedef unsigned char				uint8;
	typedef unsigned short			uint16;
	typedef unsigned long				uint32;
	typedef unsigned __int64		uint64;
	typedef float               f32;
	typedef double              f64;
	// old-style (will be removed soon)
	typedef signed __int64			s64;
	typedef unsigned long				u32;
	typedef unsigned __int64		u64;
#endif

	typedef uint16 StringID;
	inline StringID make_String(int id){ return (StringID)id;}

	//--------------------------------------------------------------------------
	// string
	//--------------------------------------------------------------------------
	typedef TCHAR name12_t[12];
	typedef TCHAR name32_t[32];
	typedef TCHAR name64_t[64];
	typedef TCHAR name128_t[64];
	typedef TCHAR name256_t[256];
	typedef TCHAR name1024_t[1024];

	typedef TCHAR tname12_t[12];
	typedef TCHAR tname32_t[32];
	typedef TCHAR tname64_t[64];
	typedef TCHAR tname128_t[64];
	typedef TCHAR tname256_t[256];
	typedef TCHAR tname1024_t[1024];

	typedef CHAR aname12_t[12];
	typedef CHAR aname32_t[32];
	typedef CHAR aname64_t[64];
	typedef CHAR aname128_t[64];
	typedef CHAR aname256_t[256];
	typedef CHAR aname1024_t[1024];

	typedef WCHAR wname12_t[12];
	typedef WCHAR wname32_t[32];
	typedef WCHAR wname64_t[64];
	typedef WCHAR wname128_t[64];
	typedef WCHAR wname256_t[256];
	typedef WCHAR wname1024_t[1024];


	typedef TCHAR name_t[32];
	typedef TCHAR fname_t[256];
	typedef TCHAR path_t[260];
	typedef const TCHAR* cstr;

	typedef CHAR aname_t[32];
	typedef CHAR afname_t[256];
	typedef CHAR apath_t[260];
	typedef CHAR* achar_p;
	typedef const CHAR* acstr;

	typedef WCHAR wname_t[32];
	typedef WCHAR wfname_t[256];
	typedef WCHAR wpath_t[260];
	typedef WCHAR* wchar_p;
	typedef const WCHAR* wcstr;

	typedef TCHAR tname_t[32];
	typedef TCHAR tfname_t[256];
	typedef TCHAR tpath_t[260];
	typedef TCHAR* tchar_p;
	typedef const TCHAR* tcstr;



	//--------------------------------------------------------------------------
	// unicode support
	//--------------------------------------------------------------------------

#define js_sprintf(buf,...) jt_sprintf_s(buf,_countof(buf),__VA_ARGS__)

#ifdef UNICODE

//CRT 보안 강화 버젼
#define jt_printf_s    wprintf_s
#define jt_fprintf_s   fwprintf_s
#define jt_sprintf_s   swprintf_s
#define jt_snprintf_s  _snwprintf_s
#define jt_vprintf_s   vwprintf_s
#define jt_vfprintf_s  vfwprintf_s
#define jt_vsprintf_s  vswprintf_s
#define jt_scanf_s     wscanf_s
#define jt_fscanf_s    fwscanf_s
#define jt_sscanf_s    swscanf_s
#define jt_snscanf_s   _snwscanf_s

#define jt_strupr_s		_wcsupr_s
#define jt_strlwr_s		_wcslwr_s
#define jt_strcpy_s     wcscpy_s
#define jt_strcat_s     wcscat_s
#define jt_strncat_s    wcsncat_s
#define jt_strncpy_s    wcsncpy_s
#define jt_strtok_s     wcstok_s

	/* Time functions */
#define jt_asctime_s   _wasctime_s
#define jt_ctime_s     _wctime_s
#define jt_ctime64_s   _wctime64_s
#define jt_strdate_s   _wstrdate_s
#define jt_strtime_s   _wstrtime_s

	/* Environment/Path functions */
#define jt_getenv_s    _wgetenv_s
#define jt_makepath_s  _wmakepath_s
#define jt_splitpath_s _wsplitpath_s

#define jt_itoa_s       _itow_s
#define jt_ltoa_s       _ltow_s
#define jt_ultoa_s      _ultow_s


	/* Stdio functions */
#define jt_fopen_s     _wfopen_s
#define jt_freopen_s   _wfreopen_s

	/* Io functions */
#define jt_mktemp_s    _wmktemp_s

#define jt_access_s    _waccess_s


#define jt_unlink		_wunlink
#define jt_strnicmp wcsnicmp

	/* Formatted i/o */
#define jt_strftime wcsftime
#define jt_vsnprintf _vsnwprintf 

#define jt_printf    wprintf
#define jt_fprintf   fwprintf
#define jt_sprintf   swprintf
#define jt_snprintf  _snwprintf
#define jt_vprintf   vwprintf
#define jt_vfprintf  vfwprintf
#define jt_vsprintf  vswprintf
#define jt_scanf     wscanf
#define jt_fscanf    fwscanf
#define jt_sscanf    swscanf
#define jt_snscanf   _snwscanf

	/* Unformatted i/o */

#define jt_fgetc     fgetwc
#define jt_fgetchar  _fgetwchar
#define jt_fgets     fgetws
#define jt_fputc     fputwc
#define jt_fputchar  _fputwchar
#define jt_fputs     fputws
#define jt_getc      getwc
#define jt_getch     _getwch
#define jt_getchar   getwchar
#define jt_gets      _getws
#define jt_putc      putwc
#define jt_putchar   putwchar
#define jt_putch     _putwch
#define jt_puts      _putws


	/* String conversion functions */

#define jt_strtod     wcstod
#define jt_strtol     wcstol
#define jt_strtoul    wcstoul
#define jt_atof      _wtof
#define jt_atol      _wtol
#define jt_atoi      _wtoi
#define jt_atoi64    _wtoi64

#define jt_itoa       _itow
#define jt_ltoa       _ltow
#define jt_ultoa      _ultow
#define jt_atoi       _wtoi
#define jt_atol       _wtol

	/* String functions */
#define jt_strupr			wcsupr
#define jt_strlwr			wcslwr
#define jt_strcpy     wcscpy
#define jt_strcspn		wcscspn
#define jt_strcat     wcscat
#define jt_strchr     wcschr
#define jt_strdup     _wcsdup

#define jt_strlen     wcslen
#define jt_strncat    wcsncat
#define jt_strncpy    wcsncpy
#define jt_strrchr    wcsrchr
#define jt_strspn     wcsspn
#define jt_strstr     wcsstr
#define jt_strtok     wcstok
#define jt_strrev     _wcsrev

#define jt_strcmp     wcscmp
#define jt_stricmp    _wcsicmp
#define jt_strncmp   wcsncmp




	/* Execute functions */
#define jt_system    _wsystem


	/* Time functions */

#define jt_asctime   _wasctime
#define jt_ctime     _wctime
#define jt_ctime64   _wctime64
#define jt_strdate   _wstrdate
#define jt_strtime   _wstrtime

	/* Directory functions */

#define jt_chdir     _wchdir
#define jt_getcwd    _wgetcwd
#define jt_getdcwd   _wgetdcwd
#define jt_mkdir     _wmkdir
#define jt_rmdir     _wrmdir


	/* Environment/Path functions */

#define jt_fullpath  _wfullpath
#define jt_getenv    _wgetenv
#define jt_makepath  _wmakepath
#define jt_splitpath _wsplitpath


	/* Stdio functions */
#define jt_fopen     _wfopen
#define jt_freopen   _wfreopen


	/* Io functions */

#define jt_findfirst _wfindfirst
#define jt_findfirst64   _wfindfirst64
#define jt_findfirsti64  _wfindfirsti64
#define jt_findnext  _wfindnext
#define jt_findnext64    _wfindnext64
#define jt_findnexti64   _wfindnexti64
#define jt_mktemp    _wmktemp

#define jt_open      _wopen
#define jt_access    _waccess
#define jt_remove    _wremove
#define jt_rename    _wrename

#define jt_finddata_t    _wfinddata_t
#define jt__finddata64_t  _wfinddata64_t
#define jt_finddatai64_t _wfinddatai64_t




#else // #ifdef UNICODE

//CRT 보안 강화 버젼
#define jt_printf_s    printf_s
#define jt_fprintf_s   fprintf_s
#define jt_sprintf_s   sprintf_s
#define jt_snprintf_s  _snprintf_s
#define jt_vprintf_s   vprintf_s
#define jt_vfprintf_s  vfprintf_s
#define jt_vsprintf_s  vsprintf_s
#define jt_scanf_s     scanf_s
#define jt_fscanf_s    fscanf_s
#define jt_sscanf_s    sscanf_s
#define jt_snscanf_s   _snscanf_s

#define jt_itoa_s       _itoa_s
#define jt_ltoa_s       _ltoa_s
#define jt_ultoa_s      _ultoa_s

#define jt_strupr_s		strupr_s
#define jt_strlwr_s		strlwr_s
#define jt_strcpy_s     strcpy_s
#define jt_strcat_s     strcat_s
#define jt_strncat_s    strncat_s
#define jt_strncpy_s    strncpy_s
#define jt_strtok_s     strtok_s

/* Time functions */
#define jt_asctime_s   asctime_s
#define jt_ctime_s     ctime_s
#define jt_ctime64_s   _ctime64_s
#define jt_strdate_s   _strdate_s
#define jt_strtime_s   _strtime_s

/* Environment/Path functions */
#define jt_getenv_s    getenv_s
#define jt_makepath_s  _makepath_s
#define jt_splitpath_s _splitpath_s


/* Stdio functions */
#define jt_fopen_s     fopen_s
#define jt_freopen_s   freopen_s

/* Io functions */
#define jt_mktemp_s    _mktemp_s
#define jt_access_s    _access_s


#define jt_unlink		unlink
#define jt_strnicmp strnicmp
#define jt_strftime strftime
#define jt_vsnprintf _vsnprintf  

#define jt_printf    printf
#define jt_fprintf   fprintf
#define jt_sprintf   sprintf
#define jt_snprintf  _snprintf
#define jt_vprintf   vprintf
#define jt_vfprintf  vfprintf
#define jt_vsprintf  vsprintf
#define jt_scanf     scanf
#define jt_fscanf    fscanf
#define jt_sscanf    sscanf
#define jt_snscanf   _snscanf

	/* Unformatted i/o */

#define jt_fgetc     fgetc
#define jt_fgetchar  _fgetchar
#define jt_fgets     fgets
#define jt_fputc     fputc
#define jt_fputchar  _fputchar
#define jt_fputs     fputs
#define jt_getc      getc
#define jt_getch     _getch
#define jt_getchar   getchar
#define jt_gets      gets
#define jt_putc      putc
#define jt_putchar   putchar
#define jt_putch     _putch
#define jt_puts      puts


	/* String conversion functions */

#define jt_strtod     strtod
#define jt_strtol     strtol
#define jt_strtoul    strtoul
#define jt_atof      atof
#define jt_atol      atol
#define jt_atoi      atoi
#define jt_atoi64    _atoi64

#define jt_itoa       _itoa
#define jt_ltoa       _ltoa
#define jt_ultoa      _ultoa
#define jt_atoi       atoi
#define jt_atol       atol

	/* String functions */

	/* Note that _mbscat, _mbscpy and _mbsdup are functionally equivalent to 
	strcat, strcpy and strdup, respectively. */

#define jt_strupr			strupr
#define jt_strlwr			strlwr
#define jt_strcat     strcat
#define jt_strcpy     strcpy
#define jt_strcspn		strcspn
#define jt_strchr			strchr
#define jt_strdup     _strdup

#define jt_strlen     strlen
#define jt_strncat	strncat
#define jt_strncpy		strncpy
#define jt_strrchr    strrchr
#define jt_strspn     strspn
#define jt_strstr     strstr
#define jt_strtok     strtok
#define jt_strrev     strrev

#define jt_strcmp     strcmp
#define jt_stricmp    stricmp
#define jt_strncmp   strncmp


	/* Execute functions */
#define jt_system    system


	/* Time functions */

#define jt_asctime   asctime
#define jt_ctime     ctime
#define jt_ctime64   _ctime64
#define jt_strdate   _strdate
#define jt_strtime   _strtime


	/* Directory functions */

#define jt_chdir     _chdir
#define jt_getcwd    _getcwd
#define jt_getdcwd   _getdcwd
#define jt_mkdir     _mkdir
#define jt_rmdir     _rmdir


	/* Environment/Path functions */

#define jt_fullpath  _fullpath
#define jt_getenv    getenv
#define jt_makepath  _makepath
#define jt_splitpath _splitpath


	/* Stdio functions */
#define jt_fopen     fopen
#define jt_freopen   freopen


	/* Io functions */
#define jt_findfirst _findfirst
#define jt_findfirst64   _findfirst64
#define jt_findfirsti64  _findfirsti64
#define jt_findnext  _findnext
#define jt_findnext64    _findnext64
#define jt_findnexti64   _findnexti64
#define jt_mktemp    _mktemp

#define jt_open      _open
#define jt_access    _access
#define jt_remove    remove
#define jt_rename    rename

#define jt_finddata_t    _finddata_t
#define jt__finddata64_t  _finddata64_t
#define jt_finddatai64_t _finddatai64_t



#endif // #ifdef UNICODE

//CRT 보안 강화 버젼 시작


#define ja_printf_s    printf_s
#define ja_fprintf_s   fprintf_s
#define ja_sprintf_s   sprintf_s
#define ja_snprintf_s  _snprintf_s
#define ja_vprintf_s   vprintf_s
#define ja_vfprintf_s  vfprintf_s
#define ja_vsprintf_s  vsprintf_s
#define ja_scanf_s     scanf_s
#define ja_fscanf_s    fscanf_s
#define ja_sscanf_s    sscanf_s
#define ja_snscanf_s   _snscanf_s

#define ja_itoa_s       _itoa_s
#define ja_ltoa_s       _ltoa_s
#define ja_ultoa_s      _ultoa_s

#define ja_strupr_s		_strupr_s
#define ja_strlwr_s		_strlwr_s
#define ja_strcpy_s     strcpy_s
#define ja_strcat_s     strcat_s
#define ja_strncat_s    strncat_s
#define ja_strncpy_s    strncpy_s
#define ja_strtok_s     strtok_s

/* Time functions */
#define ja_asctime_s   asctime_s
#define ja_ctime_s     ctime_s
#define ja_ctime64_s   _ctime64_s
#define ja_strdate_s   _strdate_s
#define ja_strtime_s   _strtime_s

/* Environment/Path functions */
#define ja_getenv_s    getenv_s
#define ja_makepath_s  _makepath_s
#define ja_splitpath_s _splitpath_s


/* Stdio functions */
#define ja_fopen_s     fopen_s
#define ja_freopen_s   freopen_s

/* Io functions */
#define ja_mktemp_s    _mktemp_s
#define ja_access_s    _access_s



#define jw_printf_s    wprintf_s
#define jw_fprintf_s   fwprintf_s
#define jw_sprintf_s   swprintf_s
#define jw_snprintf_s  _snwprintf_s
#define jw_vprintf_s   vwprintf_s
#define jw_vfprintf_s  vfwprintf_s
#define jw_vsprintf_s  vswprintf_s
#define jw_scanf_s     wscanf_s
#define jw_fscanf_s    fwscanf_s
#define jw_sscanf_s    swscanf_s
#define jw_snscanf_s   _snwscanf_s

#define jw_strupr_s		wcsupr_s
#define jw_strlwr_s		wcslwr_s
#define jw_strcpy_s     wcscpy_s
#define jw_strcat_s     wcscat_s
#define jw_strncat_s    wcsncat_s
#define jw_strncpy_s    wcsncpy_s
#define jw_strtok_s     wcstok_s

/* Time functions */
#define jw_asctime_s   _wasctime_s
#define jw_ctime_s     _wctime_s
#define jw_ctime64_s   _wctime64_s
#define jw_strdate_s   _wstrdate_s
#define jw_strtime_s   _wstrtime_s

/* Environment/Path functions */
#define jw_getenv_s    _wgetenv_s
#define jw_makepath_s  _wmakepath_s
#define jw_splitpath_s _wsplitpath_s


/* Stdio functions */
#define jw_fopen_s     _wfopen_s
#define jw_freopen_s   _wfreopen_s

/* Io functions */
#define jw_mktemp_s    _wmktemp_s

#define jw_access_s    _waccess_s
//CRT 보안 강화 버젼 끝



#define jw_unlink		_wunlink
#define jw_strnicmp wcsnicmp
#define jw_strftime wcsftime
#define jw_vsnprintf _vsnwprintf
#define jw_printf    wprintf
#define jw_fprintf   fwprintf
#define jw_sprintf   swprintf
#define jw_snprintf  _snwprintf
#define jw_vprintf   vwprintf
#define jw_vfprintf  vfwprintf
#define jw_vsprintf  vswprintf
#define jw_scanf     wscanf
#define jw_fscanf    fwscanf
#define jw_sscanf    swscanf
#define jw_snscanf   _snwscanf


	/* Unformatted i/o */

#define jw_fgetc     fgetwc
#define jw_fgetchar  _fgetwchar
#define jw_fgets     fgetws
#define jw_fputc     fputwc
#define jw_fputchar  _fputwchar
#define jw_fputs     fputws
#define jw_getc      getwc
#define jw_getch     _getwch
#define jw_getchar   getwchar
#define jw_gets      _getws
#define jw_putc      putwc
#define jw_putchar   putwchar
#define jw_putch     _putwch
#define jw_puts      _putws


	/* String conversion functions */

#define jw_strtod     wcstod
#define jw_strtol     wcstol
#define jw_strtoul    wcstoul
#define jw_atof      _wtof
#define jw_atol      _wtol
#define jw_atoi      _wtoi
#define jw_atoi64    _wtoi64

#define jw_itoa       _itow
#define jw_ltoa       _ltow
#define jw_ultoa      _ultow
#define jw_atoi       _wtoi
#define jw_atol       _wtol

	/* String functions */
#define jw_strupr			wcsupr
#define jw_strlwr			wcslwr
#define jw_strcpy     wcscpy
#define jw_strcat     wcscat
#define jw_strchr     wcschr
#define jw_strdup     _wcsdup

#define jw_strlen     wcslen
#define jw_strncat    wcsncat
#define jw_strncpy    wcsncpy
#define jw_strrchr    wcsrchr
#define jw_strspn     wcsspn
#define jw_strstr     wcsstr
#define jw_strtok     wcstok
#define jw_strrev     _wcsrev

#define jw_strcmp     wcscmp
#define jw_stricmp    _wcsicmp
#define jw_strncmp   wcsncmp

	/* Execute functions */
#define jw_system    _wsystem


	/* Time functions */

#define jw_asctime   _wasctime
#define jw_ctime     _wctime
#define jw_ctime64   _wctime64
#define jw_strdate   _wstrdate
#define jw_strtime   _wstrtime

	/* Directory functions */

#define jw_chdir     _wchdir
#define jw_getcwd    _wgetcwd
#define jw_getdcwd   _wgetdcwd
#define jw_mkdir     _wmkdir
#define jw_rmdir     _wrmdir


	/* Environment/Path functions */

#define jw_fullpath  _wfullpath
#define jw_getenv    _wgetenv
#define jw_makepath  _wmakepath
#define jw_splitpath _wsplitpath


	/* Stdio functions */
#define jw_fopen     _wfopen
#define jw_freopen   _wfreopen


	/* Io functions */

#define jw_findfirst _wfindfirst
#define jw_findfirst64   _wfindfirst64
#define jw_findfirsti64  _wfindfirsti64
#define jw_findnext  _wfindnext
#define jw_findnext64    _wfindnext64
#define jw_findnexti64   _wfindnexti64
#define jw_mktemp    _wmktemp

#define jw_open      _wopen
#define jw_access    _waccess
#define jw_remove    _wremove
#define jw_rename    _wrename

#define jw_finddata_t    _wfinddata_t
#define jw__finddata64_t  _wfinddata64_t
#define jw_finddatai64_t _wfinddatai64_t



	//--------------------------------------------------------------------------
	// 
	//--------------------------------------------------------------------------
#define ja_unlink		unlink
#define ja_strnicmp strnicmp
#define ja_strftime strftime
#define ja_vsnprintf _vsnprintf
#define ja_printf    printf
#define ja_fprintf   fprintf
#define ja_sprintf   sprintf
#define ja_snprintf  _snprintf
#define ja_vprintf   vprintf
#define ja_vfprintf  vfprintf
#define ja_vsprintf  vsprintf
#define ja_scanf     scanf
#define ja_fscanf    fscanf
#define ja_sscanf    sscanf
#define ja_snscanf   _snscanf


	/* Unformatted i/o */

#define ja_fgetc     fgetc
#define ja_fgetchar  _fgetchar
#define ja_fgets     fgets
#define ja_fputc     fputc
#define ja_fputchar  _fputchar
#define ja_fputs     fputs
#define ja_getc      getc
#define ja_getch     _getch
#define ja_getchar   getchar
#define ja_gets      gets
#define ja_putc      putc
#define ja_putchar   putchar
#define ja_putch     _putch
#define ja_puts      puts


	/* String conversion functions */

#define ja_strtod     strtod
#define ja_strtol     strtol
#define ja_strtoul    strtoul
#define ja_atof      atof
#define ja_atol      atol
#define ja_atoi      atoi
#define ja_atoi64    _atoi64

#define ja_itoa       _itoa
#define ja_ltoa       _ltoa
#define ja_ultoa      _ultoa
#define ja_atoi       atoi
#define ja_atol       atol

	/* String functions */

	/* Note that _mbscat, _mbscpy and _mbsdup are functionally equivalent to 
	strcat, strcpy and strdup, respectively. */

#define ja_strupr			strupr
#define ja_strlwr			strlwr
#define ja_strcat     strcat
#define ja_strcpy     strcpy
#define ja_strchr			strchr
#define ja_strdup     _strdup

#define ja_strlen     strlen
#define ja_strncat	strncat
#define ja_strncpy		strncpy
#define ja_strrchr    strrchr
#define ja_strspn     strspn
#define ja_strstr     strstr
#define ja_strtok     strtok
#define ja_strrev     strrev

#define ja_strcmp     strcmp
#define ja_stricmp    stricmp
#define ja_strncmp   strncmp


	/* Execute functions */
#define ja_system    system


	/* Time functions */

#define ja_asctime   asctime
#define ja_ctime     ctime
#define ja_ctime64   _ctime64
#define ja_strdate   _strdate
#define ja_strtime   _strtime


	/* Directory functions */

#define ja_chdir     _chdir
#define ja_getcwd    _getcwd
#define ja_getdcwd   _getdcwd
#define ja_mkdir     _mkdir
#define ja_rmdir     _rmdir


	/* Environment/Path functions */

#define ja_fullpath  _fullpath
#define ja_getenv    getenv
#define ja_makepath  _makepath
#define ja_splitpath _splitpath


	/* Stdio functions */
#define ja_fopen     fopen
#define ja_freopen   freopen


	/* Io functions */
#define ja_findfirst _findfirst
#define ja_findfirst64   _findfirst64
#define ja_findfirsti64  _findfirsti64
#define ja_findnext  _findnext
#define ja_findnext64    _findnext64
#define ja_findnexti64   _findnexti64
#define ja_mktemp    _mktemp

#define ja_open      _open
#define ja_access    _access
#define ja_remove    remove
#define ja_rename    rename

#define ja_finddata_t    _finddata_t
#define ja__finddata64_t  __finddata64_t
#define ja_finddatai64_t _finddatai64_t

	//--------------------------------------------------------------------------
	// func
	//--------------------------------------------------------------------------
	typedef void (*VoidFunc_t)();


	//--------------------------------------------------------------------------
	// etc struct 
	//--------------------------------------------------------------------------
#ifndef LINUX
	typedef void *THREAD_HANDLE;
	typedef void *EVENT_HANDLE;
#endif


#ifdef __cplusplus
	struct jIVar;
	namespace nXML
	{
		struct jIDocument;
		struct jIElement;
		struct jIAttribute;
	}
	typedef nXML::jIDocument jID;
	typedef nXML::jIElement jIE;
	typedef nXML::jIAttribute jIA;

}
#include "jTypedef_struct.h"
#include "Namespace.h"
#endif




//X(TYPE, RETURN_TYPE, RETURN_VAL)
#define for_each_default_type_init_value(X)\
	X(int64, int64, 0)\
	X(int32, int32, 0)\
	X(int16, int16, 0)\
	X(int8, int8, 0)\
	X(uint64, uint64, 0)\
	X(uint32, uint32, 0)\
	X(uint16, uint16, 0)\
	X(uint8, uint8, 0)\
	X(bool,bool , false)\
	X(string,cstr, "")\
	X(char*,cstr,"")\
	X(SYSTEMTIME,cstr,"")\

#endif // __jTypedef_type_header__

