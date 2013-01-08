/* file : nOS_filesystem.h
Coder : by icandoit ( icandoit@neowiz.com)
Date : 2012-02-15 12:16:02
comp.: www.neowiz.com
title : 
desc : 

*/

#ifndef __nOS_filesystem_header__
#define __nOS_filesystem_header__
#pragma once

#include "linux_filesystem.h"


namespace nMech { namespace nOS
{

	bool is_exist_file(const char* sz);
	void create_dir_force(cstr sz);
	void print_boost_path(cstr szPath);


}}//namespace nMech { namespace nOS


#endif // __nOS_filesystem_header__
