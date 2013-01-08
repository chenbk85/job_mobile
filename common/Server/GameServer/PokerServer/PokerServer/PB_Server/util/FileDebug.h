#ifndef __FILEDEBUG_H__
#define __FILEDEBUG_H__

#include "config_all_server.h"

#ifdef WIN32
#if !defined(DEF_LINUX)
#include <windows.h>
#endif
#endif

#define __FILE_DEBUG__

void FileDebug(LPCTSTR fmt,...);

#endif
