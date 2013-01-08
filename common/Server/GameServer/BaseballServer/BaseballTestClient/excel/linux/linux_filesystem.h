
/* file : linux_filesystem.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-02-08 12:22:15
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __linux_filesystem_header__
#define __linux_filesystem_header__
#pragma once

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include <iostream>


using namespace boost;
using namespace boost::filesystem;
namespace fs = boost::filesystem;



namespace nMech { namespace nLinux
{
	

	char* get_home_dir(char* buf);
	char* get_temp_fname(char* buf);
	char* get_temp_dir(char* buf);
	string timestamp();
	void GetLocalTime(SYSTEMTIME* st);
	std::string get_ip(cstr szHostName);


}}//namespace nMech { namespace nLinux

#ifdef DEF_WINDOWS
#	define getLocalTime ::GetLocalTime
#else
#	define getLocalTime nLinux::GetLocalTime
#endif


#endif // __linux_filesystem_header__

