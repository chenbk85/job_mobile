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
	string get_current_dir();

	tcstr current_SYSTEMTIME(fname_t buf);

	
	typedef int month_t;
	typedef int day_t;
	typedef std::pair<month_t ,day_t> diff_day_t;
	diff_day_t diff_day(cstr szOldDay, cstr szNewDay);

	int64 get_curr_time_msec();//밀리초로 현제시간 리턴.

}}//namespace nMech { namespace nOS


#endif // __nOS_filesystem_header__
