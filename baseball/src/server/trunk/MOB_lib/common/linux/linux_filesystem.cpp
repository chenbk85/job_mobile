
#include "stdafx.h"

#ifndef DEF_WINDOWS

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdio>
#include <stdlib.h>
#include "header/jHeader.h"
#include "linux_filesystem.h"
#include "nOS_filesystem.h"
#include <boost/asio.hpp>
#include <boost/test/unit_test.hpp>
#include <sys/time.h>

using namespace nMech;

using namespace boost;
using namespace boost::filesystem;

namespace nMech { namespace nLinux
{

	unsigned int timeGetTime()
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		return now.tv_usec/1000;
	} 

	uint64 atou64(const TCHAR *s) 
	{ 
		const uint64 max64 = (uint64)0-1; 
		uint64 v = 0; 
		int digit; 
		while (*s>=_T('0') && *s<=_T('9')) 
		{ 
			digit = *s++ - _T('0'); 
			if (v > (max64-digit)/10) 
				return 0; /* overflow */ 
			v = 10*v + digit; 
		} 
		return v; 
	} 

	char* get_home_dir(char* buf)
	{
		struct passwd *pw = getpwuid(getuid());
		const char *homedir = pw->pw_dir;
		strcpy(buf, homedir);
		return buf;
	}

	char* get_temp_fname(char* buf)
	{
		mkstemp(buf);
		return buf;

	}
	char* get_temp_dir(char* buf)
	{
		fname_t home;
		get_home_dir(home);
		path ph = unique_path();
		sprintf(buf,"%s/tmp/",home);
		create_directories(buf);
		sprintf(buf,"%s/tmp/%s",home,ph.string().c_str());
		create_directories(buf);
		return buf;
	}

	string timestamp()
	{
		char run_date[128];
#if 0
		std::time_t tod;
		std::time( &tod );
		struct tm tNow = *std::gmtime( &tod );
		std::strftime( run_date, sizeof(run_date),
			"%Y-%m-%d %H_%M_%S UTC",  &tNow);
#endif
		time_t     now = time(NULL);
		struct tm  ts = *localtime(&now);
		std::strftime( run_date, sizeof(run_date), "%Y-%m-%d %H_%M_%S",  &ts);
		return string( run_date );
	}



	void GetLocalTime(SYSTEMTIME* st)
	{
		memset(st,0,sizeof(*st));
		time_t     now = time(NULL);
		struct tm  ts = *localtime(&now);
		st->wYear = ts.tm_year+1900;
		st->wMonth = ts.tm_mon+1;
		st->wDay = ts.tm_mday;
		st->wHour = ts.tm_hour;
		st->wMinute = ts.tm_min;
		st->wSecond = ts.tm_sec;
	}



	using namespace boost::asio;
	//using boost::asio::ip;
	using boost::asio::ip::tcp;
	namespace posix = boost::asio::posix;

	class jAsyncResolveHandler   
	{   
	public :   
		std::string &m_addr;
		jAsyncResolveHandler( std::string &addr) : m_addr(addr){}

		void operator() (const boost::system::error_code& e, tcp::resolver::iterator itr )   
		{   
			if ( e )   
			{   
				std::cout << " jAsyncResolveHandler e.value(), errorcode_ : "  << e.value() <<endl;
				return;
			}   
			tcp::endpoint endpoint_ = *itr;   
			m_addr = endpoint_.address().to_string();
			std::cout << "ip = " << m_addr << " jAsyncResolveHandler endpoint_.port = " << endpoint_.port()  <<endl;
		}   
	};   


	std::string get_ip(cstr szHostName)
	{
		boost::asio::io_service io_service;   
		tcp::resolver resolver(io_service);   
		boost::system::error_code error;   
		string ip;
		tcp::resolver::query query(szHostName,"");   
		resolver.async_resolve(query,jAsyncResolveHandler(ip));   
		io_service.run_one(error);
		io_service.reset();   
		return ip;
	}

}}//namespace nMech { namespace nLinux

#endif //#ifdef DEF_WINDOWS
